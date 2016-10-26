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
 * module to implement pli vpi_ routines
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
static int32 chk_delay_num(char *, struct h_t *, int32, struct gate_t *);
static int32 fillchk_tim(word64 *, int32 *, p_vpi_delay, t_midat *);
static void fill_vpi_delay(p_vpi_delay, word64 *, int32, word32,
 struct mod_t *);

static void get_varorparam_val(struct h_t *, p_vpi_value);
static void stscal_fill_valuep(p_vpi_value, byte *, int32);
static void stvec_fill_valuep(p_vpi_value, byte *, int32);
static void get_var_bit(struct h_t *, p_vpi_value);
static void get_arrwrd_val(struct h_t *, p_vpi_value);  
static void get_expr_val(struct h_t *, p_vpi_value);  
static int32 valp_stren_err(struct hrec_t *, p_vpi_value);  
static void get_primterm_val(struct h_t *, p_vpi_value);  
static void get_vpisfcall_retval(struct h_t *, p_vpi_value);
static void get_vpiudpdefn_val(struct h_t *, p_vpi_value);
static void get_vpitabentry_val(struct h_t *, p_vpi_value);
static void get_vpi_netdrv_val(struct h_t *, p_vpi_value);
static struct xstk_t *push_vpi_drv_val(struct h_t *, struct net_t **);
static void get_vpi_netbitdrv_val(struct h_t *, p_vpi_value);
static struct xstk_t *push_vpi_bitdrv_val(struct h_t *, struct net_t **);
static void get_gate_drv_valuep(struct h_t *, p_vpi_value, struct gate_t *);
static void get_vpiconta_drv_valuep(struct h_t *, p_vpi_value,
 struct conta_t *);
static void get_vpiport_drv_valuep(struct h_t *, p_vpi_value,
 struct mod_pin_t *);
static void get_vpiportbit_drv_valuep(struct h_t *, p_vpi_value,
 struct mod_pin_t *, int32);
static void get_vpi_attrval(struct h_t *, p_vpi_value);

static void correct_objtypval(p_vpi_value, word32, word32, word32, int32);
static void expr_correct_objtypval(struct expr_t *, p_vpi_value);
static void fill_valuep(p_vpi_value, struct xstk_t *xsp, word32, int32);
static void wrkval_grow(int32);
static void udp_line_to_str(char *, struct udp_t *, struct utline_t *);
static int32 putv_in_future(word32, p_vpi_time);
static int32 chk_putv_args(word32, struct h_t *, p_vpi_value); 
static char *putv_flag_to_str(char *, word32);
static int32 net_ongetpat_lhs(struct net_t *);
static int32 good_value_p(p_vpi_value);
static void free_putv_sched(struct h_t *);
static void free_regwir_putv_sched(struct net_t *, t_midat *, struct tev_t *); 
static void free_netbitdrv_putv_sched(struct net_t *, int32, t_midat *, 
 struct tev_t *); 
static struct h_t *add_net_driver(struct h_t *); 
static struct h_t *add_netbit_driver(struct h_t *); 
static struct vpi_drv_t *alloc_vpidrv(struct net_t *, int32);
static void putv_drvwp_allocinit(struct mod_t *, struct net_t *,
 struct vpi_drv_t *, int32);
static void chg_net_to_multfi(struct net_t *, struct mod_t *);
static int32 get_vpibit_index(struct net_t **np, struct h_t *);
static struct xstk_t *push_vpi_valuep(p_vpi_value, int32, word32, int32);
static void reg_vpi_force(struct net_t *, word32 *, word32 *);
static void reg_vpi_release(struct net_t *);
static void wire_vpi_force(struct net_t *, word32 *, word32 *, int32);
static void wire_vpi_release(struct net_t *, int32);
static void set_vpisfcall_retval(struct h_t *, p_vpi_value);
static void set_vpiparam_val(struct h_t *, p_vpi_value);
static void set_vpiudpdef_ival(struct h_t *, p_vpi_value);
static void immed_vpi_drv_assign(struct net_t *np, int32, word32 *, word32 *); 
static void immed_vpibit_drv_assign(struct net_t *np, int32, int32, word32 *,
 word32 *); 
static void emit_vpiputv_evtrmsg(struct net_t *, struct teputv_t *, int32);
static void exec_putv_reg_assign(struct net_t *, word32 *, word32 *, int32);
static void exec_putv_wire_softforce(struct net_t *, word32 *,
 word32 *, int32);
static struct h_t *setschd_var_fromvaluep(p_vpi_value, struct net_t *, int32, 
 word64, byte, int32);
static void emit_vpiputv_schd_trmsg(struct net_t *, struct xstk_t *,
 struct dltevlst_t *, word64 *, int32, char *);
static void bld_regwir_putvrec(struct net_t *);
static void cancel_vpievents_toend(struct net_t *, struct dltevlst_t *, int32);
static struct h_t *setschd_drvr_fromvaluep(p_vpi_value, struct h_t *, word64,
 byte, int32);
static struct tev_t *setschd_1bit_drvr(struct net_pin_t *, int32, 
 struct xstk_t *, word64, byte);
static int32 chk_vpi_logicval(word32);
static int32 bld_vpinewdu(struct gate_t *, struct gate_t *, p_vpi_delay,
 t_midat *, int32, int32);
static int32 do_vpi_iact_scopchg(vpiHandle);
static int32 do_vpi_cb_onoff(vpiHandle, int32);
static void init_pli_einfo(struct t_vpi_error_info *, int32, int32);
static int32 to_vpierr_level(int32);


/* extern prototypes (maybe defined in this module) */
extern struct mipd_t *__get_mipd_from_port(struct mod_pin_t *, int32);
extern void __set_vpi_time(struct t_vpi_time *, word64 *, int32, struct mod_t *);
extern int32 __get_vpinet_index(struct net_t **, struct h_t *);
extern int32 __vpitime_to_ticks(word64 *, p_vpi_time, struct mod_t *);
extern void __reinit_regwir_putvrec(struct net_t *, int32);
extern void __reinit_netdrvr_putvrec(struct net_t *, struct mod_t *);
extern void __process_vpi_varputv_ev(void);
extern void __process_vpidrv_ev(void);
extern void __pli_dofinish(int32, char *);
extern void __reinit_vpi(void);
extern void __dmp_listof_handles(struct h_t *);
extern char *__to_vpionam(char *, word32);
extern int32 __validate_otyp(word32);
extern char *__to_vpiopnam(char *, int32);
extern char *__to_vpiopchar(char *, int32);
extern void __sim_notbegun_err(char *);
extern void __still_comp_err(char *);
extern void __bad_rosync_err(char *);
extern int32 __validate_handle(char *, struct h_t *);
extern int32 __validate_nonit_handle(char *, struct h_t *);
extern int32 __validate_accessm(char *, int32, char *);
extern int32 __validate_time_type(char *, int32);
extern int32 __validate_value_fmt(char *, int32);
extern void __free_iterator(vpiHandle);
extern void __free_hp(struct h_t *); 

extern vpiHandle __mk_handle(word32, void *, t_midat *, struct task_t *);
extern int32 __get_arrwide(struct net_t *);
extern char *__msg2_idp_blditree(char *, t_midat *);
extern char *__msg2_cur_blditree(char *);
extern char *__msg_idp_blditree(char *, t_midat *, struct task_t *);
extern void __extract_delval(word64 *, int32 *, union del_u, word32);
extern char *__to_tcnam(char *, word32);
extern void __fill_16vconst(word64 *, word64 *, int32);
extern void __map_16v_to_12vform(word64 *, word64 *);
extern int32 __v64_to_real(double *, word64 *);
extern char *__to_timstr(char *, word64 *);
extern int32 __add_gate_pnd0del(struct gate_t *, struct mod_t *, char *);
extern void __chg_1inst_del(struct gate_t *, struct itree_t *, struct gate_t *);
extern void __free_del(union del_u, word32, int32);
extern char *__to_mpnam(char *, char *);
extern void __add_alloc_mipd_npp(struct net_t *, struct mod_t *);
extern void __setup_mipd(struct mipd_t *, struct net_t *, int32);
extern int32 __add_conta_pnd0del(struct conta_t *, struct mod_t *, char *);
extern void __fill_4vconst(word64 *, word64 *, word64 *, word64 *, int32, int32);
extern int32 __real_to_v64tim(word64 *, double);
extern void __grow_xstk(void);
extern void __chg_xstk_width(struct xstk_t *, int32);
extern void __grow_tevtab(void);
extern void __ld_wire_val_xstk(struct xstk_t *, struct net_t *);
extern void __ld_bit(word32 *, word32 *, struct net_t *, int32);
extern void __ld_stval(word32 *, word32 *, byte *, int32);
extern void __lhsbsel(word32 *, int32, word32);
extern struct xstk_t *__eval2_xpr(struct expr_t *);
extern struct xstk_t *__ndst_eval_xpr(struct expr_t *);
extern void __ld_arr_val(struct xstk_t *, struct expr_t *, struct net_t *, 
 int32, struct gref_t *);
extern void __cnv_stk_fromreal_toreg32(struct xstk_t *);
extern void __regab_disp(word32 *, word32 *, int32, int32, int32, int32);
extern char *__to_wtnam(char *, struct net_t *);
extern char *__to_wtnam2(char *, word32);
extern void __cnv_stk_fromreg_toreal(struct xstk_t *, int32);
extern char *__alloc_vval_to_cstr(word32 *, int32, int32, int32);
extern struct xstk_t *__cstr_to_vval(char *);
extern int32 __wide_vval_is0(word32 *, int32);
extern int32 __vval_is1(word32 *, int32);
extern char *__my_realloc(void *, size_t, size_t);
extern void __my_free(void *, size_t);
extern char *__my_malloc(size_t);
extern int32 __unnormalize_ndx(struct net_t *, int32);
extern struct dltevlst_t *__spliceout_last(struct dltevlst_t *);
extern struct dltevlst_t *__find_last_bdltevp(struct dltevlst_t *,
 word64);
extern void __insert_event(struct tev_t *);
extern struct xstk_t *__putdstr_to_val(char *, int32, int32, int32);
extern double __cnvt_stk_to_real(struct xstk_t *, int32);
extern void __sizchgxs(struct xstk_t *, int32);
extern struct net_pin_t *__alloc_npin(int32, int32, int32);
extern int32 __get_pcku_chars(int32, int32);
extern void __st_perinst_val(union pck_u, int32, word32 *,
 word32 *);
extern void __st_idp_val(word32 *, int32, word32 *, word32 *);
extern void __ld_val(word32 *, word32 *, word32 *, int32);
extern void __vpi_set_chg_proc(struct gate_t *);
extern void __allocinit_perival(union pck_u *, int32, int32, int32);
extern void __init_all_inst_conta_drv(int32, int32, struct mod_t *);
extern void __vpi_set_upiconnport_proc(struct mod_pin_t *);
extern void __vpi_set_downtomdport_proc(struct mod_pin_t *, struct net_t *);
extern void __alloc_tfdrv_wp(struct tfarg_t *, struct expr_t *, struct mod_t *);
extern void __chg_st_arr_val(struct net_t *, struct expr_t *, int32, 
 word32 *, word32 *);
extern void __st_arr_val(struct net_t *, struct expr_t *, int32, word32 *, 
 word32 *, int32);
extern void __chg_st_val(struct net_t *, word32 *, word32 *);
extern void __st_val(struct net_t *, word32 *, word32 *, int32);
extern void __chg_st_bit(struct net_t *, int32, word32, word32);
extern void __st_bit(struct net_t *, int32, word32, word32);
extern int32 __correct_forced_newwireval(struct net_t *, word32 *, word32 *);
extern void __ld_perinst_val(word32 *, word32 *,
 union pck_u, int32);
extern word32 __ld_gate_out(struct gate_t *, int32 *);
extern word32 __ld_gate_in(struct gate_t *, int32, int32 *);
extern int32 __update_tran_harddrvs(struct net_t *);
extern void __tran_wire_vpi_force(struct net_t *, word32 *, word32 *, int32); 
extern void __tran_wire_vpi_release(struct net_t *, int32); 
extern void __tran_exec_putv_wire_softforce(struct net_t *, word32 *, word32 *,
 int32);

extern void __eval_tran_bits(struct net_t *);
extern void __eval_tran_1bit(struct net_t *, int32);
extern void __sched_1mdrwire(struct net_t *);
extern void __assign_1mdrwire(struct net_t *);
extern char *__st_regab_tostr(char *, byte *, int32);
extern char *__regab_tostr(char *, word32 *, word32 *, int32, int32, int32);
extern void __evtr_resume_msg(void);
extern void __chg_param_tois(struct net_t *, struct mod_t *);
extern void __re_prep_dels(struct net_t *, struct itree_t *, struct mod_t *,
 int32);
extern void __alloc_qcval(struct net_t *);
extern void __find_call_force_cbs(struct net_t *, int32);
extern void __cb_all_rfs(struct net_t *, int32, int32);
extern void __do_qc_store(struct net_t *, struct qcval_t *, int32);
extern void __find_call_rel_cbs(struct net_t *, int32);
extern void __st_standval(byte *, struct xstk_t *, byte);
extern char *__pv_stralloc(char *);
extern word32 __mc1_fopen(char *, int32, int32);
extern word32 __close_mcd(word32, int32);
extern void __free_xtree(struct expr_t *);
extern void __vpi_plierror_trycall(void);
extern char *__to_vpipnam(char *, int32);
extern void __bld_vpi_argv(void);
extern int32 __em_suppr(int32);
extern int32 __do_vpi_stop(int32);
extern void __do_vpi_reset(int32, int32, int32);
extern void __call_misctfs_scope(void);
extern void __vpi_iactscopechg_trycall(void);
extern int32 __comp_ndx(struct net_t *, struct expr_t *);
extern int32 __expr_is_vpiconst(struct expr_t *);
extern word32 __map_tovpi_stren(word32);
extern int32 __map_frvpi_stren(int32);
extern struct expr_t *__sim_copy_expr(struct expr_t *);
extern void __exec_dumpvars(struct expr_t *, int32);
extern void __my_dv_flush(void);
extern void __push_wrkitstk(struct mod_t *, int32);
extern void __pop_wrkitstk(void);
extern int32 __chk_showobj(struct h_t *, int32 *, int32 *);
extern word32 __to_vpi_tasktyp(word32);
extern int32 __my_vpi_chk_error(void);
extern struct attr_t *__find_attrspec(struct h_t *);
extern struct itree_t *__get_npprefloc(struct net_pin_t *);
extern void __add_nchglst_el(struct net_t *);
extern void __add_select_nchglst_el(struct net_t *, int32, int32);
extern void __wakeup_delay_ctrls(struct net_t *, int32, int32);
extern void __add_dmpv_chglst_el(struct net_t *);
extern void __add_dmpv_chglst_el_sel(struct net_t *, int32);
extern void __add_dp_chglst_el(struct net_t *);
extern void __add_togglelst_el(struct net_t *);
extern char *__cb_reason_to_nam(char *, int32);
extern void __bit1_vpi_or_tran_wireforce(struct net_t *, word32 *, word32 *, int32,
 int32, int32, char *);
extern struct tenp_t *__bld_portbit_netbit_map(struct mod_pin_t *);
extern int32 __trim1_0val(word32 *, int32);
extern void __sgn_xtnd_widen(struct xstk_t *, int32);
extern void __sizchg_widen(struct xstk_t *, int32);

extern int32 __fd_do_fclose(int32);

extern void __my_fprintf(FILE *, char *, ...);
extern void __tr_msg(char *, ...);
extern void __dbg_msg(char *, ...);
extern void __arg_terr(char *, int32);
extern void __pv_terr(int32, char *, ...);
extern void __misc_terr(char *, int32);

extern void __vpi_terr(char *, int32);
extern void __vpi_err(int32, int32, char *, ...);

extern const word32 __masktab[];
extern const double __dbl_toticks_tab[];

/* vpi only storage that is defined here */
struct t_vpi_error_info __wrk_einfo;/* if err, vpi routine fills this */
struct t_vpi_error_info *__last_eip;/* if err, ptr to wrk eifo or nil */

/*
 * ROUTINES FOR ACCESSING DELAYS
 */

/*
 * get a delay
 *
 * convention for pulsere flag is to use delay for other 2
 */
extern void vpi_get_delays(vpiHandle object, p_vpi_delay delay_p)
{ 
 int32 di, di2;
 int32 ndels, nrep, ndx;
 word32 getdrep;
 word64 tim[12], timval;
 struct mod_t *mdp;
 struct h_t *hp; 
 struct gate_t *gp, ogat;
 struct mod_pin_t *mpp; 
 struct net_t *np;
 struct conta_t *cap;
 struct tchk_t *tcp;
 struct spcpth_t *pthp;
 struct delctrl_t *dctp;
 union del_u getdu;
 struct t_vpi_delay tmpdel;  
 struct t_vpi_time tmpda[12];
 struct hrec_t *hrp;
 struct mipd_t *mipdp;
 decl_idp_locals_;

 if (__run_state == SS_COMP)
  { __still_comp_err("vpi_get_delays"); return; } 
 hp = (struct h_t *) object;
 if (!__validate_handle("vpi_get_delays", hp)) return;
 hrp = hp->hrec;
 nrep = 1;
 if (delay_p->pulsere_flag) 
  {
   __vpi_err(2107, vpiNotice,
    "vpi_get_delays pulsere_flag values not supported - both same as delay");
   /* still must access from callers description */
   nrep *= 3;
  }
 if (delay_p->mtm_flag)
  {
   __vpi_err(2108, vpiNotice,
    "vpi_get_delays mtm_flag set but min-typ-max values not supported - all 3 same");
   nrep *= 3;
  }
 /* on error here, user must call error check routine */
 /* can access delays for any run state but still compiling */
 if (!chk_delay_num("vpi_get_delays", hp, delay_p->no_of_delays, &ogat))
  return;

 /* must extract using exact properties from passed vpi_delay */
 tmpdel = *delay_p;
 tmpdel.da = &(tmpda[0]);

 set_save_idp_(hp->hin_idp);
 /* need module type since need to scale delay */
 mdp = (struct mod_t *) hp->hin_idp[MD_MDP];
 /* assume if handle created, good - fill the delay union */
 switch (hrp->htyp) {
  case vpiGate: case vpiUdp: case vpiSwitch:
   gp = hrp->hu.hgp;
   getdu = gp->g_du;
   getdrep = gp->g_delrep;
   break;
  case vpiPort: case vpiPortBit:
   mpp = &(mdp->mpins[hrp->hu.hpi]);
   if (hrp->htyp == vpiPort && mpp->mpwide != 1)
    {
     __vpi_err(2109, vpiNotice,
      "vpi_get_delays of non scalar vpiPort (for MIPD) using low bit");
    }
   if (!mpp->has_mipd) { getdu.d1v = NULL; getdrep = DT_NONE; }
   else 
    {
     if (hrp->htyp == vpiPort) ndx = 0; else ndx = hrp->hi;
     mipdp = __get_mipd_from_port(mpp, ndx);
     getdu = mipdp->pb_mipd_du;
     getdrep = mipdp->pb_mipd_delrep;
    } 
   break;
  case vpiNet:
   np = hrp->hu.hnp;
   /* can check for no delay with property */
   if (np->nrngrep == NX_DWIR)
    { getdu = np->nu.rngdwir->n_du; getdrep = np->nu.rngdwir->n_delrep; }
   else { getdu.d1v = NULL; getdrep = DT_NONE; }
   break;
  case vpiContAssign:
   if (hrp->htyp2 == vpiGate)
    { gp = hrp->hu.hgp; getdu = gp->g_du; getdrep = gp->g_delrep; }
   else { cap = hrp->hu.hcap; getdu = cap->ca_du; getdrep = cap->ca_delrep; }
   break;
  case vpiTchk:
   tcp = hrp->hu.htcp;
   /* know always at least one delay */
   getdu = tcp->tclim_du;
   getdrep = tcp->tc_delrep;
   /* know limit is present */
   if (getdrep == DT_NONE) __vpi_terr(__FILE__, __LINE__);
   __extract_delval(tim, &ndels, getdu, getdrep);
   if (ndels != 1) __vpi_terr(__FILE__, __LINE__);
   __set_vpi_time(&(tmpdel.da[0]), &(tim[0]), delay_p->time_type, mdp); 
   if (tcp->tc_haslim2 && delay_p->no_of_delays == 2)
    {
     getdu = tcp->tclim2_du;
     __extract_delval(tim, &ndels, getdu, getdrep);
     if (ndels != 1) __vpi_terr(__FILE__, __LINE__);
     __set_vpi_time(&(tmpdel.da[1]), &(tim[0]), delay_p->time_type, mdp); 
    }
   restore_idp_();
   goto done;
  case vpiModPath:
   pthp = hrp->hu.hpthp; getdu = pthp->pth_du; getdrep = pthp->pth_delrep;
   break;
  /* procedural delays */  
  case vpiAssignment:
   dctp = hrp->hu.hstp->st.sdc;
   if (dctp->dctyp != DC_RHSDELAY)
    {
     __vpi_err(1882, vpiError,
      "vpi_get_delays of vpiAssignment right hand side delay control impossible - no delay control");
     restore_idp_();
     goto done; 
    }
   getdu = dctp->dc_du;
   getdrep = dctp->dc_delrep;
   break;
  case vpiDelayControl:  
   dctp = hrp->hu.hstp->st.sdc;
   /* DBG remove --- */
   if (dctp->dctyp != DC_DELAY) __vpi_terr(__FILE__, __LINE__);
   /* --- */
   getdu = dctp->dc_du;
   getdrep = dctp->dc_delrep;
   break;
  /* will not get to case if not element with delay */
  default: __vpi_terr(__FILE__, __LINE__); goto done;
 }
 if (getdrep == DT_NONE)
  {
   __vpi_err(2009, vpiWarning,
    "vpi_get_delays for object %s that has no delay - value(s) 0 but not #0",
    __to_vpionam(__wrks1, hrp->htyp));
   timval = 0ULL;
   for (di = 0; di < delay_p->no_of_delays; di++) 
    __set_vpi_time(&(tmpdel.da[di]), &timval, delay_p->time_type, mdp); 
   restore_idp_();
   goto done;
  }
 __extract_delval(tim, &ndels, getdu, getdrep);
 /* this may emit warning that can be checked by calling vpi check */
 fill_vpi_delay(&tmpdel, tim, ndels, hrp->htyp, mdp);
 restore_idp_();

done:
 /* final step is copying back into user supplied delay p from tmp */
 for (di = 0; di < delay_p->no_of_delays; di++)
  {
   for (di2 = 0; di2 < nrep; di2++)
    delay_p->da[nrep*di + di2] = tmpdel.da[di];
  }
}

/*
 * routine to check that right number of delays passed for object type
 *
 * also checks for object (handle) that can have delay and fill ogp with del 
 * if return T
 */
static int32 chk_delay_num(char *rnam, struct h_t *hp, int32 numdels,
 struct gate_t *ogp)
{
 int32 ndx;
 struct gate_t *gp;
 struct conta_t *cap;
 struct mod_t *mdp;
 struct mod_pin_t *mpp;
 struct mipd_t *mipdp;
 struct net_t *np;
 struct tchk_t *tcp;
 struct spcpth_t *pthp;
 struct delctrl_t *dctp;
 struct hrec_t *hrp;

 hrp = hp->hrec;
 switch (hrp->htyp) {
  case vpiGate: case vpiUdp: case vpiSwitch:
   gp = hrp->hu.hgp;
   ogp->g_du = gp->g_du;
   ogp->g_delrep = gp->g_delrep;
chk_prim_num:
   if (numdels != 1 && numdels != 2 && numdels != 3)
    {
     __vpi_err(1881, vpiError,
      "%s called for object %s delay number %d wrong - must be 1, 2 or 3",
      rnam, __to_vpionam(__wrks1, hrp->htyp), numdels);
     return(FALSE);
    }
   break;
  case vpiContAssign:
   if (hrp->htyp2 == vpiGate)
    {
     gp = hrp->hu.hgp;
     ogp->g_du = gp->g_du;
     ogp->g_delrep = gp->g_delrep;
    }
   else
    {
     cap = hrp->hu.hcap;
     ogp->g_du = cap->ca_du;
     ogp->g_delrep = cap->ca_delrep;
    }
   goto chk_prim_num;
  case vpiNet:
   np = hrp->hu.hnp;
   if (np->nrngrep == NX_DWIR) 
    { 
     ogp->g_du = np->nu.rngdwir->n_du;
     ogp->g_delrep = np->nu.rngdwir->n_delrep;
    }
   else { ogp->g_du.d1v = NULL; ogp->g_delrep = DT_NONE; }
   goto chk_prim_num;
  case vpiPort: case vpiPortBit:
   /* MIPD delays for vector vpiPortBit, if vpiPort use low bit with note */
   /* notice check for input or inout port handled below */
   mdp = (struct mod_t *) hp->hin_idp[MD_MDP];
   mpp = &(mdp->mpins[hrp->hu.hpi]);
   if (mpp->mptyp != IO_IN && mpp->mptyp != IO_BID)
    {
     __vpi_err(2023, vpiWarning,
      "vpi_get_delays of non input or inout %s - no values returned since no MIPD possible",
      __to_vpionam(__wrks1, hrp->htyp));
     return(FALSE);
    } 
   if (!mpp->has_mipd) { ogp->g_du.d1v = NULL; ogp->g_delrep = DT_NONE; }
   else 
    {
     if (hrp->htyp == vpiPort) ndx = 0; else ndx = hrp->hi;
     mipdp = __get_mipd_from_port(mpp, ndx);
     ogp->g_du = mipdp->pb_mipd_du;
     ogp->g_delrep = mipdp->pb_mipd_delrep;
    } 
   /* SJM 10/28/99 - 12 delay values now possible for MIPDs */ 
   if (!(numdels == 1 || numdels == 2 || numdels == 3 || numdels == 6
    || numdels == 12))
    {
     __vpi_err(1881, vpiError,
      "%s called for object %s delay number %d wrong - must be 1, 2, 3, 6, or 12",
      rnam, __to_vpionam(__wrks1, hrp->htyp), numdels);
     return(FALSE);
    }
   break; 
  case vpiModPath:
   if (!(numdels == 1 || numdels == 2 || numdels == 3 || numdels == 6
    || numdels == 12))
    {
     __vpi_err(1881, vpiError,
      "%s called for object %s delay number %d wrong - must be 1, 2, 3, 6, or 12",
      rnam, __to_vpionam(__wrks1, hrp->htyp), numdels);
     return(FALSE);
    }
   pthp = hrp->hu.hpthp;
   ogp->g_du = pthp->pth_du;
   ogp->g_delrep = pthp->pth_delrep;
   break;
  case vpiTchk:
   tcp = hrp->hu.htcp;
   /* different delay unions but type must be the same */
   ogp->g_du = tcp->tclim_du;
   ogp->g_delrep = tcp->tc_delrep;
   if (numdels != 1 && numdels != 2)
    {
     __vpi_err(1889, vpiError,
      "%s called for object %s %s delay number %d wrong - must be 1 or 2",
      rnam, __to_tcnam(__wrks2, tcp->tchktyp), __to_vpionam(__wrks1,
      hrp->htyp), numdels);
     return(FALSE);
    }
   if (tcp->tc_haslim2)
    {
     if (numdels != 2)
      {
       __vpi_err(2021, vpiWarning,
        "%s called for object %s %s delay number %d wrong - missing 2nd omitted",
        rnam, __to_tcnam(__wrks2, tcp->tchktyp), __to_vpionam(__wrks1,
        hrp->htyp), numdels);
      }
    }
   else
    {
     if (numdels != 1)
      {
       __vpi_err(2021, vpiWarning,
        "%s called for object %s %s delay number %d wrong - only 1 returned or set",
        rnam, __to_tcnam(__wrks2, tcp->tchktyp), __to_vpionam(__wrks1,
        hrp->htyp), numdels);
      }
    }
   break;
  /* procedural delays */  
  case vpiAssignment: case vpiDelayControl:  
   dctp = hrp->hu.hstp->st.sdc;
   if (numdels != 1)
    {
     __vpi_err(1881, vpiError,
      "%s called for procedural object %s delay number %d wrong - must be 1",
      rnam, __to_vpionam(__wrks1, hrp->htyp), numdels);
     return(FALSE);
    }
   ogp->g_du = dctp->dc_du;
   ogp->g_delrep = dctp->dc_delrep;
   break;
  default:
   __vpi_err(1883, vpiError, "object %s does not have delays",
    __to_vpionam(__wrks1, hrp->htyp));
   return(FALSE);
 }
 return(TRUE);
}

/*
 * given an extracted tim array, vpi_ delay
 *
 * extraction produces smallest possible number if any identical values
 * nvals can be 1, 2, 3, 6, or 12 and gives number of tim[] filled
 *
 * 2 delays (nvals) now happens for logic gates and UDPs
 * for 6 and 16, order is 0-1 (a rise), 1-0 (a fall), 0-z (a toz) 
 * so can just use
 * delay_p can need 1,2,3,6,12
 */
static void fill_vpi_delay(p_vpi_delay delay_p, word64 *tim, int32 nvals,
 word32 otyp, struct mod_t *mdp)
{
 int32 di;
 word64 ntim[16];

 /* if nvals 1, just duplicate in all */
 if (nvals == 1)
  {
   for (di = 0; di < delay_p->no_of_delays; di++) 
    __set_vpi_time(&(delay_p->da[di]), &(tim[0]), delay_p->time_type, mdp); 
   return; 
  }
 /* if nvals 2, if need 1, warn use first, if 2 if path warn and use 2 */
 if (nvals == 2)  
  {
   if (delay_p->no_of_delays == 1) 
    {
     __vpi_err(2011, vpiWarning,
      "vpi_get_delays for object %s that has 2 delays but get only 1", 
      __to_vpionam(__wrks1, otyp));
     __set_vpi_time(&(delay_p->da[0]), &(tim[0]), delay_p->time_type, mdp); 
     return;
    }
   /* if need 2 just copy */
   if (delay_p->no_of_delays == 2) goto do_copy;

   /* if need 3 fill third following normal rule and copy */ 
   /* rule is that to-z is as slow as possible */
   if (delay_p->no_of_delays == 3) 
    {
     if (tim[0] > tim[1]) tim[2] = tim[0]; else tim[2] = tim[1];
     goto do_copy;
    }

   /* if need 6 convert to 12 (then ok to just ignore high 6 */
   if (delay_p->no_of_delays >= 6)
    { __fill_16vconst(ntim, tim, nvals); __map_16v_to_12vform(tim, ntim); }
   goto do_copy;
  }
 /* if nvals 3, if need 1, use warn, use first, if 2 if path warn and */
 /* use first 2, else no warn use 1st 2 */
 if (nvals == 3)  
  {
   if (delay_p->no_of_delays == 1) 
    {
     __vpi_err(2011, vpiWarning,
      "vpi_get_delays for object %s that has 3 delays but get only 1", 
      __to_vpionam(__wrks1, otyp));
     __set_vpi_time(&(delay_p->da[0]), &(tim[0]), delay_p->time_type, mdp); 
     return;
    }
   /* 2 if different toz, warning and ignore */
   if (delay_p->no_of_delays == 2)
    {
     if (tim[0] != tim[2] && tim[1] != tim[2])
      {
       __vpi_err(2011, vpiWarning,
       "vpi_get_delays for object %s that has 3 delays but get only 2", 
        __to_vpionam(__wrks1, otyp));
      }
     goto do_copy;
    }
   /* if need 6 convert to 12 (then ok to just ignore high 6 */
   if (delay_p->no_of_delays >= 6)
    { __fill_16vconst(ntim, tim, nvals); __map_16v_to_12vform(tim, ntim); }
   goto do_copy;
  }
 /* know can not reduce to 3 - and stored as 6v form */
 if (nvals == 6)
  {
   if (delay_p->no_of_delays < 6) 
    {
     __vpi_err(2011, vpiWarning,
      "vpi_get_delays for object %s that has 6 delays but get only %d", 
      __to_vpionam(__wrks1, otyp), delay_p->no_of_delays);
     goto do_copy;
    }
   /* if need more than 6 must map to 12v form */
   if (delay_p->no_of_delays > 6)
    { __fill_16vconst(ntim, tim, nvals); __map_16v_to_12vform(tim, ntim); }
   goto do_copy;
  }
 /* know can not reduce to 6 */  
 if (nvals == 12)
  {
   if (delay_p->no_of_delays < 12) 
    {
     __vpi_err(2011, vpiWarning,
      "vpi_get_delays for object %s that has 12 delays but get only %d", 
      __to_vpionam(__wrks1, otyp), delay_p->no_of_delays);
     goto do_copy;
    }
   goto do_copy;
  }
 __arg_terr(__FILE__, __LINE__);
 
do_copy:
 /* copy for 2, 3, 6, or 12 case, know tim has enough */
 for (di = 0; di < delay_p->no_of_delays; di++) 
  __set_vpi_time(&(delay_p->da[di]), &(tim[di]), delay_p->time_type, mdp); 
}

/*
 * fill a vpi time struct from a word64
 */
extern void __set_vpi_time(struct t_vpi_time *vpitimp, word64 *timp,
 int32 timtyp, struct mod_t *mdp)
{
 int32 unit;
 double d1;

 /* for getting delays, supress times means use 0 (not real) */
 if (timtyp == vpiSuppressTime)
  { vpitimp->high = 0L; vpitimp->low = 0L; return; }
 vpitimp->type = timtyp;
 /* vpi sim time is internal ticks (lowest precision in design) */
 if (timtyp == vpiSimTime)
  {
   vpitimp->high = (int32) ((*timp >> 32) & WORDMASK_ULL);
   vpitimp->low = (int32) (*timp & WORDMASK_ULL);
   return;
  }
 /* vpiScaledRealTime case */
 /* convert module specific ticks to real then scaled real */
 if (!__v64_to_real(&d1, timp))
  {
   __vpi_err(2014, vpiWarning,
    "conversion from internal time %s to time as real lost precision",
   __to_timstr(__wrks1, timp));
  }
 if (mdp != NULL && !mdp->mno_unitcnv)
  {
   unit = __des_timeprec - mdp->mtime_units;
   d1 /= __dbl_toticks_tab[unit];
  }
 vpitimp->real = d1;
}

/*
 * set delays
 */
extern void vpi_put_delays(vpiHandle object, p_vpi_delay delay_p)
{
 int32 is_trireg, ndx, sav_num_dels, bi;
 struct mod_t *mdp;
 struct h_t *hp; 
 struct tenp_t *prtnetmap;
 struct mipd_t *mipdp;
 struct gate_t *gp, ngat, ogat;
 struct net_t *np;
 struct conta_t *cap;
 struct tchk_t *tcp;
 struct spcpth_t *pthp;
 struct delctrl_t *dctp;
 struct t_vpi_time tmpda[3];
 struct t_vpi_delay wrkdel;  
 struct mod_pin_t *mpp;
 struct hrec_t *hrp;
 struct itree_t *itp;

 if (__run_state == SS_COMP) { __still_comp_err("vpi_put_delays"); return; } 
 hp = (struct h_t *) object;
 if (!__validate_handle("vpi_put_delays", hp)) return;
 hrp = hp->hrec;

 if (__rosync_slot) { __bad_rosync_err("vpi_put_delays"); return; }
 if (__run_state == SS_RESET || __run_state == SS_SIM)
  {
   /* inform since sim delay setting may not be supported by other sims */
   __vpi_err(2106, vpiNotice,
    "vpi_put_delays to object %s after simulation started - non standard feature",
    __to_vpionam(__wrks1, hrp->htyp));
  }
 /* on error here, user must call error check routine */
 if (!chk_delay_num("vpi_put_delays", hp, delay_p->no_of_delays, &ogat))
  return;
 /* can only set MIPD and replace DT NONE during SS_LOAD */
 /* SJM - 02/16/00 - must allow changing MIPDs after start of sim */
 /* to mimic XL acc_ */
 /* ---
 if (__run_state == SS_RESET || __run_state == SS_SIM)
  {
   -* once delays elaborated (after prep, before var init) can only change *-
   -* delays if already exist *-
   if (ogat.g_delrep == DT_NONE)
    {
     __vpi_err(1891, vpiError,
      "vpi_put_delays to object %s with no delay in source illegal after simulation started",
      __to_vpionam(__wrks1, hrp->htyp));
     return;
    }
  } 
 -- */ 
 if (delay_p->pulsere_flag) 
  {
   if (hrp->htyp != vpiTchk)
    {
     __vpi_err(2107, vpiNotice,
      "vpi_put_delays pulsere_flag values ignored - delay used for both limits");
    }
   else
    {
     __vpi_err(1884, vpiError,
      "vpi_put_delays pulsere_flag illegal when setting timing check limit");
     return;
    }
  }

 /* need module type since need to scale delay */
 is_trireg = FALSE;
 mdp = (struct mod_t *) hp->hin_idp[MD_MDP];
 /* assume if handle created, good - fill the delay union */

 switch (hrp->htyp) {
  case vpiGate: case vpiUdp: case vpiSwitch:
really_gate:
   gp = hrp->hu.hgp;
   /* already checked for adding delay in non load run state */
   if (gp->g_delrep == DT_NONE)
    {
     if (!__add_gate_pnd0del(gp, mdp, (char *) NULL)) return;
    }
   ogat.g_du = gp->g_du;
   ogat.g_delrep = gp->g_delrep;
   /* build the new value, maybe using old to append to if append flag */
   /* uses itree loc. from hp if needed for append access */
   /* new delay only allocated if returns T */
   if (!bld_vpinewdu(&ngat, &ogat, delay_p, hp->hin_idp, FALSE, FALSE)) return;
   
   /* this must always recomputer toz (logic) and tox all because never */
   /* explicitly given */
   if (ngat.g_delrep == DT_4V)
    {
     if (gp->g_class == GC_UDP || gp->g_class == GC_LOGIC)
      {
       if (ngat.g_du.d4v[0] < ngat.g_du.d4v[1])
        {
         ngat.g_du.d4v[2] = ngat.g_du.d4v[0];
         ngat.g_du.d4v[3] = ngat.g_du.d4v[0];
        } 
       else
        {
         ngat.g_du.d4v[2] = ngat.g_du.d4v[1];
         ngat.g_du.d4v[3] = ngat.g_du.d4v[1];
        }
      }
     else
      {
       if (ngat.g_du.d4v[0] < ngat.g_du.d4v[1])
        ngat.g_du.d4v[3] = ngat.g_du.d4v[0];
       else ngat.g_du.d4v[3] = ngat.g_du.d4v[1];
      }
    }
   
   /* this handles freeing and realloc of delay union if needed */
   itp = (struct itree_t *) hp->hin_idp[MD_ITP];
   __chg_1inst_del(&ogat, itp, &ngat);
   gp->g_du = ogat.g_du;  
   gp->g_delrep = ogat.g_delrep;
   __free_del(ngat.g_du, ngat.g_delrep, mdp->flatinum);
   break;
  case vpiPort: case vpiPortBit:
   /* SJM 07/13/01 - notice only for (PORT form MIPD, not src-dst */
   /* know this is only for one bit, i.e. scalar port of port bit */
   mpp = &(mdp->mpins[hrp->hu.hpi]);
   if (mpp->mptyp != IO_IN && mpp->mptyp != IO_BID)
    {
     __vpi_err(1885, vpiError,
      "vpi_put_delays of non input or inout %s %s - not set because MIPD impossible",
      __to_vpionam(__wrks1, hrp->htyp), __to_mpnam(__wrks2, mpp->mpsnam));
     return;  
    } 
   if (hrp->htyp == vpiPort && mpp->mpwide != 1)
    {
     __vpi_err(2109, vpiNotice,
      "vpi_put_delays of non scalar vpiPort (for MIPD) setting low bit");
    }
   if (hrp->htyp == vpiPort) ndx = 0; else ndx = hrp->hi;

   /* build map between ports bit and connected net/bit */
   prtnetmap = __bld_portbit_netbit_map(mpp);
   if (!mpp->has_mipd) 
    {
     /* notice must build mipd table for all of every net connecting to port */
     for (bi = 0; bi < mpp->mpwide; bi++)
      {
       np = prtnetmap[bi].tenu.np;
       /* LOOKATME - think unc not possible here */
       if (np == NULL || (np->nlds != NULL
        && np->nlds->npntyp == NP_MIPD_NCHG)) continue;

       /* allocate path for every net connected to port */ 
       __add_alloc_mipd_npp(np, mdp);
      }
     mdp->mod_has_mipds = TRUE;
     mpp->has_mipd = TRUE; 
    }

   /* ndx is actual port bit that connects */ 
   np = prtnetmap[ndx].tenu.np;
   bi = prtnetmap[ndx].nbi;

   /* DBG remove -- */
   if (np->nlds == NULL || np->nlds->npntyp != NP_MIPD_NCHG)
    __misc_terr(__FILE__, __LINE__);
   /* --- */
   mipdp = &(np->nlds->elnpp.emipdbits[bi]);

   /* if no active mipd for this net/bit, must enable with 0 delay */
   if (mipdp->no_mipd) __setup_mipd(mipdp, np, mdp->flatinum);

   ogat.g_du = mipdp->pb_mipd_du;
   ogat.g_delrep = mipdp->pb_mipd_delrep;
   /* treat this as 16 value path style delay - not 3 value gate type */
   if (!bld_vpinewdu(&ngat, &ogat, delay_p, hp->hin_idp, TRUE, FALSE)) return;

   /* set to x since can never explicitly set */
   if (ngat.g_delrep == DT_4V)
    {
     if (ngat.g_du.d4v[0] < ngat.g_du.d4v[1])
      ngat.g_du.d4v[3] = ngat.g_du.d4v[0];
     else ngat.g_du.d4v[3] = ngat.g_du.d4v[1];
    }

   itp = (struct itree_t *) hp->hin_idp[MD_ITP];
   __chg_1inst_del(&ogat, itp, &ngat);
   mipdp->pb_mipd_du = ogat.g_du; 
   mipdp->pb_mipd_delrep = ogat.g_delrep; 
   __free_del(ngat.g_du, ngat.g_delrep, mdp->flatinum);
   __my_free(prtnetmap, mpp->mpwide*sizeof(struct tenp_t));
   break;
  case vpiNet:
   np = hrp->hu.hnp;
   if (np->nrngrep != NX_DWIR)
    {
     __vpi_err(1899, vpiError,
      "vpi_put_delays to wire %s with no delay in source illegal - net must have delay in source",
      __to_vpionam(__wrks1, hrp->htyp));
     return;
    }
   ogat.g_du = np->nu.rngdwir->n_du;
   ogat.g_delrep = np->nu.rngdwir->n_delrep;
   if (np->ntyp == N_TRIREG) is_trireg = TRUE;
   if (!bld_vpinewdu(&ngat, &ogat, delay_p, hp->hin_idp, FALSE, is_trireg))
    return;

   if (ngat.g_delrep == DT_4V)
    {
     /* set to x since can never explicitly set */
     if (ngat.g_du.d4v[0] < ngat.g_du.d4v[1])
      ngat.g_du.d4v[3] = ngat.g_du.d4v[0];
     else ngat.g_du.d4v[3] = ngat.g_du.d4v[1];
    }

   itp = (struct itree_t *) hp->hin_idp[MD_ITP];
   __chg_1inst_del(&ogat, itp, &ngat);
   np->nu.rngdwir->n_du = ogat.g_du;  
   np->nu.rngdwir->n_delrep = ogat.g_delrep;
   __free_del(ngat.g_du, ngat.g_delrep, mdp->flatinum);
   break;
  case vpiContAssign:
   /* 1 bit contas internally gates */
   if (hrp->htyp2 == vpiGate) goto really_gate;

   cap = hrp->hu.hcap;
   /* already checked for adding delay if non load run state */
   if (cap->ca_delrep == DT_NONE)
    { 
     if (!__add_conta_pnd0del(cap, mdp, (char *) NULL)) return;
    }
   ogat.g_du = cap->ca_du;
   ogat.g_delrep = cap->ca_delrep;

   if (!bld_vpinewdu(&ngat, &ogat, delay_p, hp->hin_idp, FALSE, FALSE))
    return;
   /* notice bld vpi new du can only produce DT 1V or DT 4V here */ 
   if (ngat.g_delrep == DT_4V)
    {
     /* set to x since can never explicitly set */
     if (ngat.g_du.d4v[0] < ngat.g_du.d4v[1])
      ngat.g_du.d4v[3] = ngat.g_du.d4v[0];
     else ngat.g_du.d4v[3] = ngat.g_du.d4v[1];
    } 
   itp = (struct itree_t *) hp->hin_idp[MD_ITP];
   __chg_1inst_del(&ogat, itp, &ngat);
   cap->ca_du = ogat.g_du;  
   cap->ca_delrep = ogat.g_delrep;

   /* must always make sure if needed ca_4vdel value changes */
   switch ((byte) cap->ca_delrep) {
    case DT_4V: case DT_IS4V: case DT_IS4V1: case DT_IS4V2: case DT_4X:
     cap->ca_4vdel = TRUE;
     break;
    default: cap->ca_4vdel = FALSE;
   }
   __free_del(ngat.g_du, ngat.g_delrep, mdp->flatinum);
   break;
  case vpiTchk:
   tcp = hrp->hu.htcp;
   /* if can have 2 set and 2 passed only, set both */
   if (tcp->tc_haslim2 && delay_p->no_of_delays == 2) 
    {
     /* 2nd need same fields as first */
     wrkdel = *delay_p;
     if (wrkdel.mtm_flag)
      {
       tmpda[0] = delay_p->da[3];
       tmpda[1] = delay_p->da[4];
       tmpda[2] = delay_p->da[5];
      }
     else tmpda[0] = delay_p->da[1];
     wrkdel.da = &(tmpda[0]);
     sav_num_dels = 2;  
     wrkdel.no_of_delays = 1;
     delay_p->no_of_delays = 1; 
    }
   else sav_num_dels = delay_p->no_of_delays;
   /* know only 1 or 2 delays (not pulserr but maybe mtm) - copies both */
   /* always set at least one */ 
   ogat.g_du = tcp->tclim_du;
   ogat.g_delrep = tcp->tc_delrep;
   /* know at least one limit is present */
   /* DBG remove -- */ 
   if (ogat.g_delrep == DT_NONE) __vpi_terr(__FILE__, __LINE__);
   /* --- */
   if (!bld_vpinewdu(&ngat, &ogat, delay_p, hp->hin_idp, FALSE, FALSE))
    goto tc_done;
   itp = (struct itree_t *) hp->hin_idp[MD_ITP];
   __chg_1inst_del(&ogat, itp, &ngat);
   tcp->tclim_du = ogat.g_du;  
   tcp->tc_delrep = ogat.g_delrep;
   __free_del(ngat.g_du, ngat.g_delrep, mdp->flatinum);

   /* has 2 and timing checks also has 2 limits */
   if (tcp->tc_haslim2 && delay_p->no_of_delays == 2) 
    {
     ogat.g_du = tcp->tclim2_du;
     ogat.g_delrep = tcp->tc_delrep2;
     if (!bld_vpinewdu(&ngat, &ogat, &wrkdel, hp->hin_idp, TRUE, FALSE))
      goto tc_done;
     itp = (struct itree_t *) hp->hin_idp[MD_ITP];
     __chg_1inst_del(&ogat, itp, &ngat);
     tcp->tclim2_du = ogat.g_du;
     tcp->tc_delrep2 = ogat.g_delrep;
     __free_del(ngat.g_du, ngat.g_delrep, mdp->flatinum);
    }
tc_done:
   /* must put back passed number so user can free */ 
   delay_p->no_of_delays = sav_num_dels; 
   break; 
  case vpiModPath:
   pthp = hrp->hu.hpthp;
   ogat.g_du = pthp->pth_du;
   ogat.g_delrep = pthp->pth_delrep;
   if (!bld_vpinewdu(&ngat, &ogat, delay_p, hp->hin_idp, TRUE, FALSE))
    return;
   itp = (struct itree_t *) hp->hin_idp[MD_ITP];
   __chg_1inst_del(&ogat, itp, &ngat);
   pthp->pth_du = ogat.g_du;  
   pthp->pth_delrep = ogat.g_delrep;
   __free_del(ngat.g_du, ngat.g_delrep, mdp->flatinum);
   break;
  /* procedural delays */  
  case vpiAssignment:
   dctp = hrp->hu.hstp->st.sdc;
   if (dctp->dctyp != DC_RHSDELAY)
    {
     __vpi_err(1886, vpiError,
      "vpi_put_delays of vpiAssignment right hand side delay control impossible - no delay control");
     return;
    }
set_dctrl_delay:
   ogat.g_du = dctp->dc_du;
   ogat.g_delrep = dctp->dc_delrep;
   if (!bld_vpinewdu(&ngat, &ogat, delay_p, hp->hin_idp, FALSE, FALSE)) return;
   itp = (struct itree_t *) hp->hin_idp[MD_ITP];
   __chg_1inst_del(&ogat, itp, &ngat);
   dctp->dc_du = ogat.g_du; 
   dctp->dc_delrep = ogat.g_delrep;
   __free_del(ngat.g_du, ngat.g_delrep, mdp->flatinum);
   break;
  case vpiDelayControl:  
   dctp = hrp->hu.hstp->st.sdc;
   /* DBG remove --- */
   if (dctp->dctyp != DC_DELAY) __vpi_terr(__FILE__, __LINE__);
   /* --- */
   goto set_dctrl_delay;
  /* will not get to this case if not legal element with delay */
  default: __vpi_terr(__FILE__, __LINE__);
 }
}

/*
 * given a vpi delay_p filled by user, build the _du for it
 *
 * know delay number correct
 * if no source delay, caller changes to #0 before calling
 */
static int32 bld_vpinewdu(struct gate_t *ngp, struct gate_t *ogp,
 p_vpi_delay delay_p, t_midat *idp, int32 is_path, int32 is_trireg)
{
 int32 di;
 int32 ndels, ondels, negdel[16];
 word64 tim[16], otim[16], ntim[16], *dtab;
 decl_idp_locals_;

 if (!fillchk_tim(tim, negdel, delay_p, idp)) return(FALSE); 
 ndels = delay_p->no_of_delays;

 /* handle appending - must be on delay_p array */ 
 if (delay_p->append_flag)
  { 
   set_save_idp_(idp);
   __extract_delval(otim, &ondels, ogp->g_du, ogp->g_delrep);
   restore_idp_();
   /* if either 1, widen with inform by replicating the 1 to width of other */
   if ((ondels == 1 || ndels == 1) && (ondels != ndels)) 
    {
     __vpi_err(2008, vpiNotice,
      "vpi_put_delays append mode old (%d) and new (%d) number of delays differ - one delay replicated",
      ondels, ndels);   

     if (ondels != 1)
      {
       for (di = 1; di < ondels; di++) tim[di] = tim[0];
       ndels = ondels;
      }
     else
      { 
       for (di = 1; di < ndels; di++) otim[di] = otim[0];
       ondels = ndels;
      }
    }
   /* here need 2 delay case that is not normally reduced to */
   if (!is_path && ondels == 3)
    {
     if (is_trireg) 
      { if (otim[3] == otim[0] || otim[3] == otim[1]) ondels = 2; }
     else
      {
       if ((otim[2] == otim[0] || otim[2] == otim[1]) 
        && (otim[3] == otim[0] || otim[3] == otim[1])) ondels = 2; 
      }
    }
   /* if too few new delays, use 0 for those (i.e. unchanged) */
   if (ndels < ondels)
    {
     __vpi_err(2005, vpiNotice,
      "vpi_put_delays append mode more old delays (%d) than new (%d) - 0 used for missing",
      ondels, ndels);   
     for (di = ndels; di < ondels; di++) tim[di] = 0ULL;
     ndels = ondels;
    }
   /* too many - ignore with warning */
   else if (ndels > ondels)
    {
     __vpi_err(2006, vpiWarning,
      "vpi_put_delays append mode more new delays (%d) than old (%d) - extra ignored",
      ndels, ondels);   
     ndels = ondels;
    }
   /* do the update - know ndels and odels same */
   for (di = 0; di < ndels; di++) ntim[di] = tim[di];
   for (di = 0; di < ndels; di++)
    {
     if (negdel[di])
      {
       if (ntim[di] > otim[di])
        {
         __vpi_err(2004, vpiWarning,
          "vpi_put_delays append result (pos. %d) negative (0 used)", di + 1);
         tim[di] = 0ULL;
        }
       else tim[di] = otim[di] - ntim[di]; 
      } 
     else tim[di] = otim[di] + ntim[di];
    }
  }
 /* now tim has right new delay value */
 /* fill dtab (always 4 or 16 for path) */
 if (ndels == 1)
  {
del1form:
   ngp->g_du.d1v = (word64 *) __my_malloc(sizeof(word64));
   *(ngp->g_du.d1v) = tim[0];
   ngp->g_delrep = DT_1V;
   return(TRUE);
  }

 /* see if can reduce to 1 - know at least 2 */
 for (di = 1; di < ndels; di++) { if (tim[0] != tim[di]) goto no_reduce1; }
 goto del1form;

no_reduce1:
 if (is_path)
  {
   dtab = (word64 *) __my_malloc(16*sizeof(word64));
   __fill_16vconst(dtab, tim, ndels);
   ngp->g_delrep = DT_16V;
   ngp->g_du.d16v = dtab;
  }
 else
  {
   dtab = (word64 *) __my_malloc(4*sizeof(word64));
   __fill_4vconst(dtab, &(tim[0]), &(tim[1]), &(tim[2]), ndels, is_trireg);
   ngp->g_delrep = DT_4V;
   ngp->g_du.d4v = dtab;
  }
 return(TRUE);
}

/*
 * fill and check internal tim[] value from delay p
 * return F on error
 *
 * mtm and pulsere possible here, pulsere no effect though 
 * scaling depends upon module of handle
 * LOOKATME - is it true only vpiScaledRealTime can be negative
 */
static int32 fillchk_tim(word64 *tim, int32 *negdel, p_vpi_delay delay_p,  
 t_midat *idp)
{
 int32 di;
 int32 stride, ofset, ndels;
 double d1;
 word64 t1;
 struct t_vpi_time *vpitimp;
 struct mod_t *mdp;

 ndels = delay_p->no_of_delays;
 for (di = 0; di < ndels; di++) negdel[di] = FALSE;
 stride = 1;
 ofset = 0;
 if (delay_p->pulsere_flag) stride *= 3;
 if (delay_p->mtm_flag)
  {
   stride *= 3;
   if (__mintypmax_sel == DEL_MIN) ofset = 0;
   else if (__mintypmax_sel == DEL_TYP) ofset = 1;
   else if (__mintypmax_sel == DEL_MAX) ofset = 2;
   else __vpi_terr(__FILE__, __LINE__);
  }
 /* step 1: convert to internal ticks and set neg - maybe needed for inc */
 for (di = 0; di < ndels; di++)
  {
   /* always ignore any pulse limits (2 and 3 or 3 through 8 if mtm) */
   vpitimp = &(delay_p->da[stride*di + ofset]);

   /* suppress ok for append - just do not change (0 if none) */
   if (vpitimp->type == vpiSuppressTime)
    {
     if (!delay_p->append_flag)
      {
       /* () form normal 0 for SDF so do no need warning */
       __vpi_err(2003, vpiWarning,
        "vpi_put_delays vpiSuppressTime (pos. %d) ignored for replace mode - 0 used",
         di + 1);
      }
     tim[di] = 0ULL;
     continue;
    }
   if (vpitimp->type == vpiScaledRealTime)
    {
     d1 = vpitimp->real;
     if (d1 < 0.0)
      {
       if (!delay_p->append_flag)
        {
         __vpi_err(2004, vpiWarning,
          "replace mode vpi_put_delays value %g (pos. %d) negative (0 used)",
          d1, di + 1);
         tim[di] = 0ULL;
         continue;
        }  
       d1 = -d1;
       negdel[di] = TRUE;
      }
     if (!__real_to_v64tim(&t1, d1))
      {
       __vpi_err(1895, vpiError,
        "vpi_put_delays value %g (pos. %d) too large for vpiScaledRealTime",
         d1, di + 1);
       return(FALSE);
      }
     mdp = (struct mod_t *) idp[MD_MDP];
     if (!mdp->mno_unitcnv) cnv_num64to_ticks_(tim[di], t1, mdp);
     else tim[di] = t1;
     continue;
    }
   if (vpitimp->type != vpiSimTime)
    {
     __vpi_err(1820, vpiError,
      "vpi_put_delays t_vpi_time type value %d illegal (pos. %d)",
      vpitimp->type, di + 1);
     return(FALSE);
    }
   /* vpiSimTime is internal ticks */
   /* SJM 02/03/00 - cast of negative (>2**31) sign extends need word32 1st */
   t1 = (word64) ((word32) vpitimp->low)
    | (((word64) ((word32) vpitimp->high)) << 32);
   tim[di] = t1;
  }
 return(TRUE);
}

/* 
 * VALUE PROCESSING ROUTINES
 */

/*
 * get value into value_p record
 *
 * LOOKATME - does fcall have a value (think not)
 *
 * SJM 10/21/99 - changed so if value not set causes vpi_ error
 */
extern void vpi_get_value(vpiHandle expr, p_vpi_value value_p)
{
 struct h_t *hp;
 struct hrec_t *hrp;
 struct gate_t *gp;
 struct mod_t *mdp;
 struct mod_pin_t *mpp;
 decl_idp_locals_;

 /* must reset at start of call to no error */
 __last_eip = NULL;
 if (__run_state == SS_COMP)
  { __still_comp_err("vpi_get_value"); return; } 

 hp = (struct h_t *) expr;
 if (!__validate_handle("vpi_get_value", hp)) return;
 hrp = hp->hrec;

 /* no access for suppress - LOOKATME - is this true */
 if (value_p->format == vpiSuppressVal) return;

 switch (hrp->htyp) {
  case vpiNet: case vpiReg: case vpiIntegerVar: case vpiTimeVar:
  case vpiRealVar: case vpiParameter: case vpiSpecParam:
    set_save_idp_(hp->hin_idp);
    get_varorparam_val(hp, value_p);
    restore_idp_();
   break;
  case vpiNetBit: case vpiRegBit: case vpiVarSelect:
   get_var_bit(hp, value_p);
   break;
  case vpiMemoryWord:
   get_arrwrd_val(hp, value_p);
   break;  
  case vpiConstant: case vpiPartSelect: case vpiOperation: case vpiFuncCall:
   set_save_idp_(hp->hin_idp);
   get_expr_val(hp, value_p);
   restore_idp_();
   break;
  case vpiPrimTerm:
   get_primterm_val(hp, value_p);
   break;
  case vpiSysFuncCall:
   /* LOOKATME - what is this supposed to do? */ 
   get_vpisfcall_retval(hp, value_p); 
   break;
  case vpiUdpDefn:
   get_vpiudpdefn_val(hp, value_p); 
   break;
  case vpiTableEntry:
   get_vpitabentry_val(hp, value_p); 
   break;
  /* LOOKATME - no get value of quasi-continue force/assign because */
  /* can build driver iterator and then access lhs expr. - is this right */

  /* remaining access drivers - i.e. access internal driving code not val */
  case vpiNetDriver:
   get_vpi_netdrv_val(hp, value_p);
   break;
  case vpiNetBitDriver:
   get_vpi_netbitdrv_val(hp, value_p);
   break;
  case vpiGate: case vpiUdp:
   gp = hrp->hu.hgp;
conta_gate:
   get_gate_drv_valuep(hp, value_p, gp);
   break;
  case vpiContAssign:
   if (hrp->htyp2 == vpiGate)
    {gp = hrp->hu.hgp; goto conta_gate; }
   get_vpiconta_drv_valuep(hp, value_p, hrp->hu.hcap);
   break;
  case vpiPort:
   mdp = (struct mod_t *) hp->hin_idp[MD_MDP];
   mpp = &(mdp->mpins[hrp->hu.hpi]);
   get_vpiport_drv_valuep(hp, value_p, mpp);
   break;
  case vpiPortBit:
   mdp = (struct mod_t *) hp->hin_idp[MD_MDP];
   mpp = &(mdp->mpins[hrp->hu.hpi]);
   get_vpiportbit_drv_valuep(hp, value_p, mpp, hrp->hi);
   break;
  case vpiAttribute:
   get_vpi_attrval(hp, value_p);
   break;
  default:
   __vpi_err(1897, vpiError,
    "vpi_get_value can not access value of %s (variable, param or expression needed)",
    __to_vpionam(__wrks1, hrp->htyp));
   return;
 } 
}

/*
 * get value of any variable or parameter include global param
 * caller has set itree loc
 */
static void get_varorparam_val(struct h_t *hp, p_vpi_value value_p)
{
 struct net_t *np;
 struct xstk_t *xsp;
 byte *sbp;
 struct xstk_t *xsp2; 

 /* no checking needed */

 np = hp->hrec->hu.hnp;
 /* correct for type determined format */
 if (value_p->format == vpiObjTypeVal)
  correct_objtypval(value_p, np->ntyp, np->n_isavec, np->n_stren, FALSE);

 /* non stren */
 if (value_p->format != vpiStrengthVal)
  {
   push_xstk_(xsp, np->nwid); 
   __ld_wire_val_xstk(xsp, np);
   fill_valuep(value_p, xsp, np->ntyp, np->nwid);
   __pop_xstk();
   return;
  }

 /* need strength */
 /* net stored as strength */
 if (np->n_stren)
  {
   sbp = (byte *) &(__idp[np->nva_ofs]);
   if (np->nwid == 1) stscal_fill_valuep(value_p, sbp, 0);
   else stvec_fill_valuep(value_p, sbp, np->nwid);
   return;
  }
 /* load as non stren and convert to stren case */
 push_xstk_(xsp, np->nwid); 
 __ld_wire_val_xstk(xsp, np);

 push_xstk_(xsp2, 4*np->nwid); 
 sbp = (byte *) xsp2->ap;
 /* add strong */
 __st_standval(sbp, xsp, ST_STRVAL); 
 if (np->nwid == 1) stscal_fill_valuep(value_p, sbp, 0);
 else stvec_fill_valuep(value_p, sbp, np->nwid);
 __pop_xstk();
 __pop_xstk();  
}

/*
 * fill a scalar strength valuep field from a strength vector
 */
static void stscal_fill_valuep(p_vpi_value value_p, byte *sbp, int32 bi)
{ 
 s_vpi_strengthval *svalp;
 int32 slen;

 slen = sizeof(struct t_vpi_strengthval);
 if (slen >= __wrkval_buflen) wrkval_grow(slen + RECLEN);
 value_p->value.strength = (struct t_vpi_strengthval *) __wrkvalbufp;

 svalp = &(value_p->value.strength[0]);
 svalp[0].logic = (int32) (sbp[bi] & 3L);
 svalp[0].s0 = __map_tovpi_stren((int32) ((sbp[bi] >> 5) & 7));
 svalp[0].s1 = __map_tovpi_stren((int32) ((sbp[bi] >> 2) & 7));
}

/*
 * fill a strength valuep field from a strength vector
 *
 * 04/01/00 - for veriog 2000 now can access/stren strength in vectors
 * user must allocate wide enough t vpi_strengthval array
 * caller must convert value to strength if non strength
 */
static void stvec_fill_valuep(p_vpi_value value_p, byte *sbp, int32 swid)
{ 
 int32 bi;
 s_vpi_strengthval *svalp;
 int32 slen;

 slen = swid*sizeof(struct t_vpi_strengthval);
 if (slen >= __wrkval_buflen) wrkval_grow(slen + RECLEN);
 value_p->value.strength = (struct t_vpi_strengthval *) __wrkvalbufp;

 svalp = &(value_p->value.strength[0]);
 for (bi = 0; bi < swid; bi++) 
  {
   svalp[bi].logic = (int32) (sbp[bi] & 3L);
   svalp[bi].s0 = __map_tovpi_stren((int32) ((sbp[bi] >> 5) & 7));
   svalp[bi].s1 = __map_tovpi_stren((int32) ((sbp[bi] >> 2) & 7));
  }
}

/*
 * map from vpi strength values to internal Cver values
 * returns -1 on bad value  
 */
extern int32 __map_frvpi_stren(int32 vpistval)
{
 int32 stval;

 /* must be left as int32 in case bad value_p record */
 switch (vpistval) {
  case vpiSupplyDrive: stval = ST_SUPPLY; break;
  case vpiStrongDrive: stval = ST_STRONG; break;
  case vpiPullDrive: stval = ST_PULL; break;
  case vpiWeakDrive: stval = ST_WEAK; break;
  case vpiLargeCharge: stval = ST_LARGE; break;
  case vpiMediumCharge: stval = ST_MEDIUM; break;
  case vpiSmallCharge: stval = ST_SMALL; break;
  case vpiHiZ: stval = ST_HIGHZ; break;
  default: return(-1);
 }
 return(stval);
}

/*
 * map from internal strength values to vpi strength constant
 */
extern word32 __map_tovpi_stren(word32 stval)
{
 word32 vpistval;

 switch ((byte) stval) {
  case ST_SUPPLY: vpistval = vpiSupplyDrive; break;
  case ST_STRONG: vpistval = vpiStrongDrive; break;
  case ST_PULL: vpistval = vpiPullDrive; break;
  case ST_WEAK: vpistval = vpiWeakDrive; break;
  case ST_LARGE: vpistval = vpiLargeCharge; break;
  case ST_MEDIUM: vpistval = vpiMediumCharge; break;
  case ST_SMALL: vpistval = vpiSmallCharge; break;
  case ST_HIGHZ: vpistval = vpiHiZ; break;
  default: __vpi_terr(__FILE__, __LINE__); return(0);
 }
 return(vpistval);
}

/*
 * get variable bit 
 *
 * this must set itree context
 */
static void get_var_bit(struct h_t *hp, p_vpi_value value_p)
{
 int32 biti;
 byte *sbp;
 struct net_t *np;
 struct xstk_t *xsp, *xsp2;
 decl_idp_locals_;

 /* nothing to check */

 /* DBG remove --- */
 if (hp->hin_idp == NULL) __vpi_terr(__FILE__, __LINE__); 
 /* --- */
 set_save_idp_(hp->hin_idp);

 biti = get_vpibit_index(&np, hp);

 if (value_p->format == vpiObjTypeVal)
  correct_objtypval(value_p, np->ntyp, np->n_isavec, np->n_stren, FALSE);

 /* non strength case */
 if (value_p->format != vpiStrengthVal)
  {
   push_xstk_(xsp, 1);
   __ld_bit(xsp->ap, xsp->bp, np, biti);
   fill_valuep(value_p, xsp, np->ntyp, 1);
   __pop_xstk();
   restore_idp_();
   return;
  }

 /* stored as stren */ 
 if (np->n_stren) 
  {
   sbp = (byte *) &(__idp[np->nva_ofs]);
   stscal_fill_valuep(value_p, sbp, biti);
   restore_idp_();
   return;
  }

 /* stored as non stren but get val asked for stren */
 push_xstk_(xsp, 1);
 __ld_bit(xsp->ap, xsp->bp, np, biti);
 push_xstk_(xsp2, 4);
 sbp = (byte *) xsp2->ap;
 __st_standval(sbp, xsp, ST_STRVAL); 
 /* SJM 02/08/01 - for (net/reg) bit object sbp is the one bit */
 stscal_fill_valuep(value_p, sbp, 0);
 __pop_xstk();
 __pop_xstk();
 restore_idp_();
}

/*
 * get value of one array word32 given a array word32 (indexed) handle 
 *
 * know passed handle is array word32 and correct index in range for well
 * formed handle
 */
static void get_arrwrd_val(struct h_t *hp, p_vpi_value value_p)  
{
 int32 arri;
 byte *sbp;
 struct net_t *np;
 struct xstk_t *xsp, *xsp2;
 decl_idp_locals_;

 /* nothing to check - stren legal */

 /* DBG remove --- */
 if (hp->hin_idp == NULL) __vpi_terr(__FILE__, __LINE__); 
 /* --- */
 set_save_idp_(hp->hin_idp);

 /* notice union field is index and since array word32 is in has itree */
 /* inst., can use for ptr to the containing handle */
 /* this uses comp_ndx that works for arrays too */
 arri = get_vpibit_index(&np, hp);

 if (value_p->format == vpiObjTypeVal)
  correct_objtypval(value_p, np->ntyp, np->n_isavec, np->n_stren, FALSE);
 
 /* never strength - but may need to convert */
 push_xstk_(xsp, np->nwid); 
 __ld_arr_val(xsp, NULL, np, arri, NULL);
 
 if (value_p->format != vpiStrengthVal)
  {
   fill_valuep(value_p, xsp, np->ntyp, np->nwid);
   __pop_xstk();
   restore_idp_();
   return;
  }

 /* always need to add stren here */
 push_xstk_(xsp2, 4*np->nwid); 
 sbp = (byte *) xsp2->ap;
 __st_standval(sbp, xsp, ST_STRVAL); 

 if (np->nwid == 1) stscal_fill_valuep(value_p, sbp, 0);
 else stvec_fill_valuep(value_p, sbp, np->nwid);
 __pop_xstk();
 __pop_xstk();
 restore_idp_();
}

/*
 * get value of expression
 * caller has set itree loc
 */
static void get_expr_val(struct h_t *hp, p_vpi_value value_p)  
{
 int32 wtyp;
 struct expr_t *xp;
 struct xstk_t *xsp;
 struct hrec_t *hrp;

 hrp = hp->hrec;

 /* only error is stren illegal */
 if (valp_stren_err(hrp, value_p)) return; 

 /* notice expr. handle itree loc. is always ref. location */   
 /* LOOKATME - these are never strength - think this is right - check */
 xp = hrp->hu.hxp;
 xsp = __eval_xpr(xp);
 if (value_p->format == vpiObjTypeVal) expr_correct_objtypval(xp, value_p);

 if (xp->is_real) wtyp = N_REAL; else wtyp = N_REG;
 fill_valuep(value_p, xsp, wtyp, xsp->xslen);
 __pop_xstk();
}

/*
 * check for illegal strength - return T if stren (error) F if non stren 
 * if error if stren
 */
static int32 valp_stren_err(struct hrec_t *hrp, p_vpi_value value_p)  
{ 
 /* for expressons - strength not allowed */
 if (value_p->format == vpiStrengthVal)
  {
   __vpi_err(1929, vpiError,
    "vpi_get_value vpiStrengthVal format illegal for expression object %s",
    __to_vpionam(__wrks1, hrp->htyp));
   return(TRUE);
  }
 return(FALSE);
}

/*
 * get value of primitve terminal
 *
 * notice legal to get any terminal including input
 *
 * SJM 11/26/00 - change so for all but tran and pull gets get internal
 * driving value for gate/udp/mos-gates in gstate
 * this now adds strengths for outputs if gate drives strength and
 * computes
 *
 * LOOKATME - for tran and pull gates think net value and driving value same?
 */
static void get_primterm_val(struct h_t *hp, p_vpi_value value_p)  
{
 int32 has_stren;
 word32 gtermwrd;
 byte sbv, *sbp;
 struct gate_t *gp;
 struct hrec_t *hrp;
 struct expr_t *xp;
 struct xstk_t *xsp;
 decl_idp_locals_;

 hrp = hp->hrec;
 /* DBG remove --- */
 if (hp->hin_idp == NULL) __vpi_terr(__FILE__, __LINE__); 
 /* --- */
 set_save_idp_(hp->hin_idp);

 gp = hrp->hu.hgp;
 /* case 1: accessing value of connecting wire as terminal value */ 
 /* know these always have stren */
 if (gp->g_class == GC_PULL || gp->g_class == GC_TRAN
  || gp->g_class == GC_TRANIF)
  {
   xp = hrp->hu.hgp->gpins[hrp->hi];
   if (value_p->format == vpiObjTypeVal) expr_correct_objtypval(xp, value_p);

   /* LOOKATME - is it possible for tran channels to not have stren? */ 
   if (value_p->format == vpiStrengthVal)
    {
     /* this adds strong if expr non strength */
     xsp = __ndst_eval_xpr(xp);
     sbp = (byte *) xsp->ap;
     stscal_fill_valuep(value_p, sbp, 0);
    }
   else
    {
     xsp = __eval_xpr(xp); 
     /* type since no net can be reg since reg can connect to input */
     fill_valuep(value_p, xsp, N_REG, xsp->xslen);
    }
   __pop_xstk();
   restore_idp_();
   return;
  }
 /* case 2: logic/udp/mos gate - this is same as gate value */
 if (hrp->hi == 0)
  {
   /* case 2a: gate output value */
   get_gate_drv_valuep(hp, value_p, gp);
   restore_idp_();
   return;
  }
 /* case 2b primitive terminal input value - first input is 1 */
 /* this gets gstate terminal value since within tick gstate may not be */
 /* updated yet after connecting expr change */ 

 /* SJM 11/26/00 - allowing strength where added as strong */
 xp = hrp->hu.hgp->gpins[hrp->hi];
 if (value_p->format == vpiObjTypeVal) expr_correct_objtypval(xp, value_p);

 gtermwrd = __ld_gate_in(gp, hrp->hi, &has_stren);
 if (value_p->format != vpiStrengthVal)
  {
   push_xstk_(xsp, 1);
   xsp->ap[0] = gtermwrd & 1L;
   xsp->bp[0] = (gtermwrd >> 1) & 1L;
   fill_valuep(value_p, xsp, N_WIRE, 1);
   __pop_xstk();
   restore_idp_();
   return;
  }
 /* need stren */
 push_xstk_(xsp, 4);
 sbv = (byte) gtermwrd;
 /* add gate driving stren if needed */
 if (!has_stren && sbv != 2) sbv |= (ST_STRVAL << 2); 
 stscal_fill_valuep(value_p, &(sbv), 0);
 restore_idp_();
}

/*
 * get return value for current user task or function only
 *
 * must be called from current system function or error
 * uses own itree context
 * LOOKATME - no internal vpi storage but LRM not clear
 * LOOKATME - what is this supposed to do - get last value? 
 */
static void get_vpisfcall_retval(struct h_t *hp, p_vpi_value value_p)
{
 int32 sf_ind;
 word32 isavec;
 p_vpi_systf_data tfdatp;
 struct systftab_t *sfp;
 struct sysfunc_t *sfbp;
 struct hrec_t *hrp;
 char s1[RECLEN];
 decl_idp_locals_;

 hrp = hp->hrec;
 /* --- DBG remove --- */
 if (hrp->hu.hxp == NULL) __vpi_terr(__FILE__, __LINE__);
 /* --- */

 if (valp_stren_err(hrp, value_p)) return; 

 if (hrp->hu.hxp != __cur_sysf_expr)
  {
   if (__cur_sysf_expr != NULL)
    {
     sf_ind = __cur_sysf_expr->lu.x->lu.sy->el.esyftbp->syfnum;
     sf_ind -= (__last_veriusertf + 1); 
     sfp = &(__systftab[sf_ind]);
     tfdatp = (p_vpi_systf_data) sfp->vpi_sytfdat;
     strcpy(s1, tfdatp->tfname);   
    }
   else strcpy(s1, "**none called**");
   __vpi_err(1848, vpiError,
    "vpi_get_value of vpiSysFuncCall %s (return value) illegal - must use from calltf cb", 
    s1);
   return; 
  }
 sf_ind = __cur_sysf_expr->lu.x->lu.sy->el.esyftbp->syfnum;
 sf_ind -= (__last_veriusertf + 1); 
 sfp = &(__systftab[sf_ind]);
 tfdatp = (p_vpi_systf_data) sfp->vpi_sytfdat;
 sfbp = sfp->sfu.sfbp;
 if (value_p->format == vpiObjTypeVal)
  {
   isavec = (sfbp->retwid == 1) ? FALSE : TRUE;
   correct_objtypval(value_p, sfbp->retntyp, isavec, FALSE, FALSE);
  }
 set_save_idp_(hp->hin_idp);
 fill_valuep(value_p, __cur_sysf_xsp, sfbp->retntyp, sfbp->retwid);
 restore_idp_();
}

/*
 * get udp definition value
 * value not per instance
 */
static void get_vpiudpdefn_val(struct h_t *hp, p_vpi_value value_p)
{
 struct hrec_t *hrp;
 struct udp_t *udpp;
 struct xstk_t *xsp;

 hrp = hp->hrec;
 /* checking */
 if (hrp->hu.hudpp->ival == NO_VAL)
  {
   __vpi_err(1939, vpiError,
    "vpi_get_value of vpiUdpDefn but no initial value - value_p unchanged"); 
   return;
  }
 if (value_p->format == vpiTimeVal)
  {
   __vpi_err(1892, vpiError,
    "vpi_get_value of vpiUdpDefn initial value VpiTimeVal value illegal - no module context"); 
    return;
  }
 if (valp_stren_err(hrp, value_p)) return; 

 /* get initial value - if get here know present */
 udpp = hrp->hu.hudpp;
 if (value_p->format == vpiObjTypeVal)
  correct_objtypval(value_p, N_REG, FALSE, FALSE, FALSE);
 push_xstk_(xsp, 1); 
 xsp->bp[0] = 0L;
 if (udpp->ival == 3) { xsp->ap[0] = 1L; xsp->bp[0] = 1L; }
 else xsp->ap[0] = (word32) udpp->ival;
 fill_valuep(value_p, xsp, N_REG, xsp->xslen);
 __pop_xstk();
}

/*
 * get udp definition value
 * value not per instance
 */
static void get_vpitabentry_val(struct h_t *hp, p_vpi_value value_p)
{
 int32 slen;
 struct hrec_t *hrp;
 struct udp_t *udpp;
 struct utline_t *utlp;

 hrp = hp->hrec;

 /* special correction of obj type here */
 if (value_p->format != vpiObjTypeVal)
  {
   if (value_p->format != vpiStringVal)
    {
     __vpi_err(1892, vpiError,
     "vpi_get_value of vpiTableEntry udp line only vpiStringVal format supported");
     return;
    }
   else value_p->format = vpiStringVal;
  }

 utlp = hrp->hu.hutlp;
 udpp = (struct udp_t *) hp->hin_idp;
 slen = 5*(udpp->numstates + 1) + 1;
 if (slen >= __wrkval_buflen) wrkval_grow(slen + RECLEN);
 value_p->value.str = __wrkvalbufp;
 udp_line_to_str(value_p->value.str, udpp, utlp);
}

/*
 * DRIVER GET VALUE ROUTINES
 */

/*
 * get net driver value
 *
 * 04/01/00 SJM - for verilog 2000 vectors of strens legal
 */
static void get_vpi_netdrv_val(struct h_t *hp, p_vpi_value value_p)
{
 byte *sbp;
 struct net_t *np;
 struct xstk_t *xsp, *xsp2;
 decl_idp_locals_;

 /* nothing to check */

 /* DBG remove --- */
 if (hp->hin_idp == NULL) __vpi_terr(__FILE__, __LINE__); 
 /* --- */
 set_save_idp_(hp->hin_idp);

 /* notice must access net value through here */
 xsp = push_vpi_drv_val(hp, &np);

 /* correct for type determined format */
 if (value_p->format == vpiObjTypeVal)
  correct_objtypval(value_p, np->ntyp, np->n_isavec, np->n_stren, FALSE);

 /* non stren case */
 if (value_p->format != vpiStrengthVal)
  {
   fill_valuep(value_p, xsp, np->ntyp, np->nwid);
   __pop_xstk();
   restore_idp_();
   return;
  }

 /* this uses net fields since stren expr value impossible */
 /* net stored as stren - loaded stren driver */
 if (np->n_stren)
  {
   sbp = (byte *) xsp->ap;
   if (np->nwid == 1) stscal_fill_valuep(value_p, sbp, 0);
   else stvec_fill_valuep(value_p, sbp, np->nwid);
   __pop_xstk();
   restore_idp_();
   return;
  }
 /* else convert to stren */
 push_xstk_(xsp2, 4*np->nwid); 
 sbp = (byte *) xsp2->ap;
 /* add strong */
 __st_standval(sbp, xsp, ST_STRVAL); 

 if (np->nwid == 1) stscal_fill_valuep(value_p, sbp, 0);
 else stvec_fill_valuep(value_p, sbp, np->nwid);

 __pop_xstk();
 __pop_xstk();
 restore_idp_();
}

/*
 * push vpi net driver value onto stack (entire net case) 
 *
 * existence of handle means all bits of this instance of net have added drvr
 */
static struct xstk_t *push_vpi_drv_val(struct h_t *hp, struct net_t **pnp)
{
 int32 inum;
 byte *sbp, *sbp2;
 struct net_t *np;
 struct xstk_t *xsp;
 struct vpi_drv_t *vpidrvp;     
 struct net_pin_t *npp;

 npp = hp->hrec->hu.hnpp;
 np = npp->elnpp.enp;
 *pnp = np;
 /* obnum is index of driver */
 vpidrvp = np->vpi_ndrvs[npp->obnum];
 if (np->n_stren)
  {
   push_xstk_(xsp, 4*np->nwid);
   sbp = (byte *) xsp->ap;
   inum = get_inum_();
   sbp2 = &(vpidrvp->vpi_drvwp.bp[inum*np->nwid]);
   memcpy(sbp, sbp2, np->nwid);
  }
 else
  {
   push_xstk_(xsp, np->nwid);
   __ld_perinst_val(xsp->ap, xsp->bp, vpidrvp->vpi_drvwp, np->nwid); 
  }
 return(xsp);
}

/*
 * get net bit driver value
 */
static void get_vpi_netbitdrv_val(struct h_t *hp, p_vpi_value value_p)
{
 byte *sbp;
 struct net_t *np;
 struct xstk_t *xsp, *xsp2;
 decl_idp_locals_;

 /* DBG remove --- */
 if (hp->hin_idp == NULL) __vpi_terr(__FILE__, __LINE__); 
 /* --- */
 set_save_idp_(hp->hin_idp);

 xsp = push_vpi_bitdrv_val(hp, &np);

 /* correct for type determined format */
 if (value_p->format == vpiObjTypeVal)
  correct_objtypval(value_p, np->ntyp, np->n_isavec, np->n_stren, TRUE);

 /* this uses net since stren expr value impossible */
 if (value_p->format != vpiStrengthVal)
  {
   fill_valuep(value_p, xsp, np->ntyp, 1);
   __pop_xstk();
   restore_idp_();
   return;
  }

 if (np->n_stren) 
  {
   sbp = (byte *) xsp->ap;
   stscal_fill_valuep(value_p, sbp, 0);
   __pop_xstk();
   restore_idp_();
   return;
  }

 /* must add strong */
 push_xstk_(xsp2, 4);
 sbp = (byte *) xsp2->ap;
 __st_standval(sbp, xsp, ST_STRVAL); 
 stscal_fill_valuep(value_p, sbp, 0);
 __pop_xstk();
 __pop_xstk();
 restore_idp_();
}

/*
 * push vpi net bit driver value onto stack
 *
 * existence of handle means handle's bit of this instance of net has add drvr
 */
static struct xstk_t *push_vpi_bitdrv_val(struct h_t *hp, struct net_t **pnp)
{
 int32 inum;
 byte *sbp;
 struct net_t *np;
 struct xstk_t *xsp, *xsp2;
 struct vpi_drv_t *vpidrvp;     
 struct net_pin_t *npp;

 npp = hp->hrec->hu.hnpp;
 np = npp->elnpp.enp;
 *pnp = np;
 /* obnum is index of driver */
 vpidrvp = np->vpi_ndrvs[npp->obnum];
 if (np->n_stren)
  {
   push_xstk_(xsp, 4);
   sbp = (byte *) xsp->ap;
 inum = get_inum_();
   sbp[0] = vpidrvp->vpi_drvwp.bp[inum*np->nwid + hp->hrec->hi];
  }
 else
  {
   push_xstk_(xsp, 1);
   push_xstk_(xsp2, np->nwid);
   __ld_perinst_val(xsp2->ap, xsp2->bp, vpidrvp->vpi_drvwp, np->nwid); 
   xsp->ap[0] = rhsbsel_(xsp2->ap, hp->hrec->hi);
   xsp->bp[0] = rhsbsel_(xsp2->bp, hp->hrec->hi);
   __pop_xstk();
  }
 return(xsp);
}

/*
 * fill a gate driver valuep
 */
static void get_gate_drv_valuep(struct h_t *hp, p_vpi_value value_p,
 struct gate_t *gp)
{
 int32 has_stren;
 word32 uwrd;
 byte *sbp;
 struct xstk_t *xsp;
 decl_idp_locals_;

 /* DBG remove --- */
 if (hp->hin_idp == NULL) __vpi_terr(__FILE__, __LINE__); 
 /* --- */
 set_save_idp_(hp->hin_idp);

 /* correct for type determined format */
 if (value_p->format == vpiObjTypeVal)
  correct_objtypval(value_p, N_WIRE, FALSE, (gp->g_hasst) ? TRUE : FALSE,
   FALSE);

 if (value_p->format != vpiStrengthVal)
  {
   push_xstk_(xsp, 1);
   uwrd = __ld_gate_out(gp, &has_stren);
   /* this must load value and remove strength since drives constant */
   /* notice this is non stren case - stren passing gates not proc. here */
   xsp->ap[0] = uwrd & 1L;
   xsp->bp[0] = (uwrd >> 1) & 1L;
   fill_valuep(value_p, xsp, N_WIRE, 1);
   __pop_xstk();
   restore_idp_();
   return;
  }
 /* need stren */
 push_xstk_(xsp, 4);
 sbp = (byte *) xsp->ap;
 sbp[0] = (byte) __ld_gate_out(gp, &has_stren);
 /* add gate driving stren if needed */
 if (!has_stren && sbp[0] != 2)
  {
   /* 04/01/00 - add gate strength since that is driven */
   /* 08/07/01 - only possibility here is both strong since no stren */
   sbp[0] |= (ST_STRVAL << 2); 
  }
 stscal_fill_valuep(value_p, sbp, 0);
 __pop_xstk();
 restore_idp_();
}

/*
 * for vpi get value - get conta driving value and assign to value p 
 *
 * 1 bit conta drivers not seen here (converted to gates) 
 * in Verilog conta strength hard coded in gate so only or in if needed
 *
 * SJM 09/28/02 - for rhs conta per bit must combine PB drv values 
 */
static void get_vpiconta_drv_valuep(struct h_t *hp, p_vpi_value value_p,
 struct conta_t *cap)
{
 int32 bi;
 int32 blen;
 byte *sbp;
 struct xstk_t *xsp, *xsp2;
 struct conta_t *pbcap;
 decl_idp_locals_;

 /* DBG remove --- */
 if (hp->hin_idp == NULL) __vpi_terr(__FILE__, __LINE__); 
 /* --- */
 set_save_idp_(hp->hin_idp);

 /* correct for type determined format - know lhs is some kind of wire */
 if (value_p->format == vpiObjTypeVal)
  correct_objtypval(value_p, N_WIRE, TRUE, (cap->ca_hasst) ? TRUE : FALSE,
   FALSE);

 blen = cap->lhsx->szu.xclen;
 if (cap->ca_pb_sim)
  {
   /* SJM 09/28/02 - for per bit rhs concat conta, must assemble val */
   push_xstk_(xsp, blen);
   for (bi = 0; bi < blen; bi++) 
    {
     pbcap = &(cap->pbcau.pbcaps[bi]);
     if (pbcap->ca_drv_ofs == 0)
      {
       xsp2 = __eval2_xpr(pbcap->rhsx);
       /* DBG remove -- */
       if (xsp2->xslen != 1) __misc_terr(__FILE__, __LINE__);
       /* --- */
      }
     else
      {
       push_xstk_(xsp2, 1);
       __ld_val(xsp2->ap, xsp2->bp, &(__idp[pbcap->ca_drv_ofs]), 1); 
      }
     __lhsbsel(xsp->ap, bi, xsp2->ap[0]);
     __lhsbsel(xsp->bp, bi, xsp2->bp[0]);
    }
  }
 else
  {
   if (cap->ca_drv_ofs == 0)
    {
     xsp = __eval2_xpr(cap->rhsx);
     if (xsp->xslen != blen)
      {
       if (xsp->xslen < blen)
        {
         /* SJM 05/10/04 - if widening and signed, must sign extend */
         if (cap->rhsx->has_sign) __sgn_xtnd_widen(xsp, blen);
         else __sizchg_widen(xsp, blen);
        }
       else __sizchgxs(xsp, blen);
      }
    }
   else
    {
     push_xstk_(xsp, blen);
     __ld_val(xsp->ap, xsp->bp, &(__idp[cap->ca_drv_ofs]), blen); 
    }
  }

 /* 04/01/00 - now for verilog 2000 handling strength vectors */
 if (value_p->format != vpiStrengthVal)
  {
   fill_valuep(value_p, xsp, N_WIRE, blen);
   __pop_xstk();
   restore_idp_();
   return;
  }

 /* else convert to stren */
 push_xstk_(xsp2, 4*blen); 
 sbp = (byte *) xsp2->ap;
 /* add stren - if does not have st val, stren is strong */
 __st_standval(sbp, xsp, cap->ca_stval); 

 /* DBG remove --
 if (blen == 1) __vpi_terr(__FILE__, __LINE__);
 --- */

 stvec_fill_valuep(value_p, sbp, blen);
 __pop_xstk();
 __pop_xstk();
 restore_idp_();
}

/*
 * for vpi get value - get mod. port driving value and assign to value p 
 *
 * port driver is just value of expr.
 */
static void get_vpiport_drv_valuep(struct h_t *hp, p_vpi_value value_p,
 struct mod_pin_t *mpp)
{
 int32 is_stren, isavec;
 byte *sbp;
 struct xstk_t *xsp, *xsp2;
 decl_idp_locals_;

 /* DBG remove --- */
 if (hp->hin_idp == NULL) __vpi_terr(__FILE__, __LINE__); 
 /* --- */
 set_save_idp_(hp->hin_idp);

 if (mpp->mpref->x_stren) is_stren = TRUE; else is_stren = FALSE; 
 if (mpp->mpwide == 1) isavec = FALSE; else isavec = TRUE;
 /* correct for type determined format - know lhs is some kind of wire */
 if (value_p->format == vpiObjTypeVal)
  correct_objtypval(value_p, N_WIRE, isavec, is_stren, FALSE);

 /* if module input port, use driving value */
 sbp = NULL;
 /* no delay - driver is expr. value */
 /* module port (down) side is expr. - no need for width change */
 if (is_stren) xsp = __ndst_eval_xpr(mpp->mpref);
 else xsp = __eval2_xpr(mpp->mpref);

 if (value_p->format != vpiStrengthVal)
  {
   if (is_stren)
    {
     /* here must remove strength */
     sbp = (byte *) xsp->ap;
     push_xstk_(xsp2, mpp->mpwide);
     __ld_stval(xsp2->ap, xsp2->bp, sbp, mpp->mpwide);
     fill_valuep(value_p, xsp2, N_WIRE, mpp->mpwide);
     __pop_xstk();
    }
   else fill_valuep(value_p, xsp, N_WIRE, mpp->mpwide);
   __pop_xstk();
   restore_idp_();
   return;
  }
 /* 04/01/00 SJM - for strength now loading entire vector */
 if (is_stren)
  {
   sbp = (byte *) xsp->ap; 
   if (mpp->mpwide == 1) stscal_fill_valuep(value_p, sbp, 0);
   else stvec_fill_valuep(value_p, sbp, mpp->mpwide);
   __pop_xstk();
   restore_idp_();
   return;
  } 
 /* driving value non strength - must add strong */
 /* load as non stren and convert to stren case */
 push_xstk_(xsp2, 4*mpp->mpwide); 
 sbp = (byte *) xsp2->ap;
 /* add strong */
 __st_standval(sbp, xsp, ST_STRVAL); 
 if (mpp->mpwide == 1) stscal_fill_valuep(value_p, sbp, 0);
 else stvec_fill_valuep(value_p, sbp, mpp->mpwide);
 __pop_xstk();
 __pop_xstk();
 restore_idp_();
}

/*
 * for vpi get value - get mod. port bit driving value and assign to value p 
 * routine for vpi Port Bit
 */
static void get_vpiportbit_drv_valuep(struct h_t *hp, p_vpi_value value_p,
 struct mod_pin_t *mpp, int32 bi)
{
 int32 is_stren, ind, inum;
 word32 av, bv;
 byte *sbp;
 struct xstk_t *xsp, *xsp2, *xsp3;
 decl_idp_locals_;

 /* DBG remove --- */
 if (hp->hin_idp == NULL) __vpi_terr(__FILE__, __LINE__); 
 /* --- */
 set_save_idp_(hp->hin_idp);

 if (mpp->mpref->x_stren) is_stren = TRUE; else is_stren = FALSE; 
 /* DBG remove --- */
 if (mpp->mpwide == 1) __vpi_terr(__FILE__, __LINE__);
 /* --- */
 /* correct for type determined format - know lhs is some kind of wire */
 if (value_p->format == vpiObjTypeVal)
  correct_objtypval(value_p, N_WIRE, FALSE, is_stren, TRUE);

 xsp2 = NULL;
 sbp = NULL;
 /* no delay - driver is expr. value */
 /* module port (down) side is expr. - no need for width change */
 if (is_stren)
  { 
   xsp2 = __ndst_eval_xpr(mpp->mpref);
   sbp = (byte *) xsp2->ap;
   inum = get_inum_();
   ind = inum*mpp->mpwide + bi; 
   sbp = &(sbp[ind]); 
  }
 else
  {
   xsp = __eval2_xpr(mpp->mpref);
   av = rhsbsel_(xsp->ap, bi);
   bv = rhsbsel_(xsp->bp, bi);
   __pop_xstk();
   push_xstk_(xsp2, 1);
   xsp2->ap[0] = av;
   xsp2->bp[0] = bv;
  }

 /* know one bit driving val on stack either stren or non stren */ 
 if (value_p->format != vpiStrengthVal)
  {
   if (is_stren)
    {
     /* remove bit's stren */
     av = sbp[0] & 1L;
     bv = ((sbp[0] & 2L) >> 1);
     __pop_xstk();
     push_xstk_(xsp2, 1);
     xsp2->ap[0] = av;
     xsp2->bp[0] = bv;
     fill_valuep(value_p, xsp2, N_WIRE, 1);
    }
   else fill_valuep(value_p, xsp2, N_WIRE, mpp->mpwide);
   __pop_xstk();
   restore_idp_();
   return;   
  }
 /* need stren in value p */
 if (!is_stren)
  {
   push_xstk_(xsp3, 4);
   /* add strong for bit */
   sbp = (byte *) xsp3->ap;
   sbp[0] = (byte) (xsp2->ap[0] | (xsp2->bp[0] << 1));
   if (sbp[0] != 2) sbp[0] |= (ST_STRVAL << 2); 
   stscal_fill_valuep(value_p, sbp, 0);
   __pop_xstk();
   __pop_xstk();
   restore_idp_();
   return;
  }
 stscal_fill_valuep(value_p, sbp, 0);
 __pop_xstk();
 restore_idp_();
}

/*
 * get attribute value
 */
static void get_vpi_attrval(struct h_t *hp, p_vpi_value value_p)
{
 int32 wtyp;
 struct expr_t *xp;
 struct xstk_t *xsp;
 struct hrec_t *hrp;
 struct attr_t *attrp;
 decl_idp_locals_;

 hrp = hp->hrec;

 /* only error is stren illegal */
 if (valp_stren_err(hrp, value_p)) return; 

 /* DBG remove --- */
 if (hp->hin_idp == NULL) __vpi_terr(__FILE__, __LINE__); 
 /* --- */
 set_save_idp_(hp->hin_idp);
 
 /* can't fail - internal error if not found */
 attrp = __find_attrspec(hp);

 xp = attrp->attr_xp;
 if (value_p->format == vpiObjTypeVal) expr_correct_objtypval(xp, value_p);
 if (xp == NULL)
  {
   /* 32 bit 1 if no expr - i.e. defaults to T */
   push_xstk_(xsp, WBITS);
   xsp->ap[0] = 1;
   xsp->bp[0] = 0; 
  }
 else xsp = __eval_xpr(xp);

 if (xp != NULL && xp->is_real) wtyp = N_REAL; else wtyp = N_REG;
 fill_valuep(value_p, xsp, wtyp, xsp->xslen);
 __pop_xstk();
 restore_idp_();
}

 
/*
 * correct value_p for vpiObjTypeVal given the net accessing value from
 *
 * notice semantics is to really change and fill in the format field
 */
static void correct_objtypval(p_vpi_value value_p, word32 ntyp,
 word32 isavec, word32 is_stren, int32 is_bsel)
{
 if (ntyp == N_INT) { value_p->format = vpiIntVal; return; }
 if (ntyp == N_REAL) { value_p->format = vpiRealVal; return; }
 if (ntyp == N_TIME) { value_p->format = vpiTimeVal; return; }
 if (!isavec || is_bsel)
  {
   if (is_stren) value_p->format = vpiStrengthVal; 
   else value_p->format = vpiScalarVal;
   return;
  }
 value_p->format = vpiVectorVal;
}

/*
 * correct value_p for vpiObjTypeVal given the net accessing value from
 *
 * notice semantics is to really change and fill in the format field
 */
static void expr_correct_objtypval(struct expr_t *xp, p_vpi_value value_p)  
{
 if (xp->is_real) { value_p->format = vpiRealVal; return; }
 if (xp->has_sign) { value_p->format = vpiIntVal; return; }
 if (xp->szu.xclen == 1)
  {
   if (xp->x_stren) value_p->format = vpiStrengthVal; 
   else value_p->format = vpiScalarVal;
   return;
  }
 value_p->format = vpiVectorVal;
}

/*
 * fill a value_p record
 *
 * only for non strength value, strength filled in other routine
 * caller loads value and places on stack 
 *
 * for reals using non real format, conversion before call 
 * for strings this uses and must enlarge a vpi get value specific work string
 * caller must place right itree location on top of itree loc. stack
 */
static void fill_valuep(p_vpi_value value_p, struct xstk_t *xsp,
 word32 vwtyp, int32 vwid)
{
 int32 wi;
 int32 slen, has_sign, blen;
 char *chp;
 int32 sav_sofs, dispfmt;
 double d1;
 word64 tim;
#ifndef __CVC32__
 word32 tmp;
 int32 vndx;
#endif

 sav_sofs = __cur_sofs;
 has_sign = FALSE; 
 switch ((byte) value_p->format) {
   case vpiBinStrVal:
    dispfmt = BBIN;
dispstr_fmt:
    /* convert real to reg */
    if (vwtyp == N_REAL) __cnv_stk_fromreal_toreg32(xsp);

    /* AIV 03/12/04 - changed so does not trim to match XL */
    __regab_disp(xsp->ap, xsp->bp, vwid, dispfmt, -1, has_sign);
    slen = __cur_sofs - sav_sofs;
    if (slen >= __wrkval_buflen) wrkval_grow(slen + RECLEN);
    value_p->value.str = __wrkvalbufp;
    strcpy(value_p->value.str, &(__exprline[sav_sofs]));
    /* exprline reset below */
    break;
   case vpiOctStrVal: dispfmt = BOCT; goto dispstr_fmt; 
   case vpiDecStrVal:
    if (vwtyp == N_INT) has_sign = TRUE; 
    dispfmt = BDEC;
    goto dispstr_fmt;
   case vpiHexStrVal: dispfmt = BHEX; goto dispstr_fmt;

   case vpiScalarVal:
    if (vwid > 1)    
     {
      __vpi_err(2017, vpiWarning,
       "vpi_get_delays format type vpiScalarVal for %s vector - low bit only",
       __to_wtnam2(__wrks1, vwtyp));
     }
    if (vwtyp == N_REAL) __cnv_stk_fromreal_toreg32(xsp);
    /* notice this assume vpi[0,1,z,x] are 0, 1, 2, 3 as stored */
    value_p->value.scalar = ((xsp->bp[0] & 1L) << 1) | (xsp->ap[0] & 1L);
    break;
   case vpiIntVal:
    if (xsp->xslen > WBITS)    
     {
      __vpi_err(2017, vpiWarning,
       "vpi_get_delays format type vpiIntVal for %s wider than 32 bits - low 32 bits only",
       __to_wtnam2(__wrks1, vwtyp));
     }
    if (vwtyp == N_REAL) __cnv_stk_fromreal_toreg32(xsp);
    /* notice integer x/z bits are always 0 - LOOKATME - is this right? */
    value_p->value.integer = (int32) (xsp->ap[0] & ~(xsp->bp[0])); 
    break;
   case vpiRealVal:
    if (vwtyp != N_REAL)
     {
      if (vwtyp == N_INT) __cnv_stk_fromreg_toreal(xsp, TRUE);
      else __cnv_stk_fromreg_toreal(xsp, FALSE);
     }
    memcpy(&d1, xsp->ap, sizeof(double));
    value_p->value.real = d1;
    break; 
   case vpiStringVal:
    /* SJM 07/30/01 - conversion to c string requires removing high pad 0's */
    blen = __trim1_0val(xsp->ap, xsp->xslen);
    /* chp malloced */
    chp = __alloc_vval_to_cstr(xsp->ap, blen, FALSE, FALSE);
    slen = strlen(chp);
    if (slen >= __wrkval_buflen) wrkval_grow(slen + RECLEN);
    value_p->value.str = __wrkvalbufp;
    strcpy(value_p->value.str, chp);
    /* expr line sofs reset before here */ 
    __my_free(chp, slen + 1);
    return;
   case vpiVectorVal:
    if (vwtyp == N_REAL) __cnv_stk_fromreal_toreg32(xsp);
    slen = wlen_(xsp->xslen)*sizeof(struct t_vpi_vecval);
    if (slen >= __wrkval_buflen) wrkval_grow(slen + RECLEN);
    value_p->value.vector = (struct t_vpi_vecval *) __wrkvalbufp; 
#ifdef __CVC32__
    for (wi = 0; wi < wlen_(xsp->xslen); wi++)
     {
      value_p->value.vector[wi].aval = (int32) xsp->ap[wi]; 
      value_p->value.vector[wi].bval = (int32) xsp->bp[wi]; 
     }
#else
    /* AIV 08/25/09 - vpiVectorVal for 64-bit is still unsigned int - 32-b */
    /* notice it is fine to go one extra +1 because __wrkvalbufp */
    /* will be large enough - just split up 64-bit tmp */
    vndx = 0;
    for (wi = 0; wi < wlen_(xsp->xslen); wi++)
     {
      tmp = xsp->ap[wi];
      value_p->value.vector[vndx].aval = (unsigned int) tmp; 
      value_p->value.vector[vndx+1].aval = (unsigned int) (tmp >> 32); 
      tmp = xsp->bp[wi];
      value_p->value.vector[vndx].bval = (unsigned int) tmp; 
      value_p->value.vector[vndx+1].bval = (unsigned int) (tmp >> 32); 
      vndx += 2;
     }
#endif
    break;
   case vpiTimeVal:
    /* value is vpiSimTime internal ticks */
    /* SJM 02/03/00 - works because stack word32 - no sign extend */
#ifdef __CVC32__
    tim = (word64) xsp->ap[0] | (((word64) xsp->ap[1]) << 32); 
#else
    /* AIV 08/25/09 - if 64-bit now fits in one word - but value.time */
    /* is still 32 */
    tim = xsp->ap[0];
#endif
    slen = sizeof(struct t_vpi_time);
    if (slen >= __wrkval_buflen) wrkval_grow(slen + RECLEN);
    value_p->value.time = (struct t_vpi_time *) __wrkvalbufp;
    value_p->value.time->type = vpiSimTime;
    value_p->value.time->high = (int32) ((tim >> 32) & WORDMASK_ULL);
    value_p->value.time->low = (int32) (tim & WORDMASK_ULL);
    break;
   /* strength value never pushed because not expression */
   default: 
    __vpi_err(1902, vpiError,
     "vpi_get_value passed s_vpi_value format value %d illegal",
     value_p->format);
  } 
 __cur_sofs = sav_sofs;
 __exprline[__cur_sofs] = '\0';
}

/*
 * grow the one work string used by get value routine
 */
static void wrkval_grow(int32 nsize)
{
 size_t osize;

 osize = __wrkval_buflen;
 if (osize == 0)
  {
   if (nsize > RECLEN) __wrkval_buflen = nsize;
   else __wrkval_buflen = RECLEN;
   __wrkvalbufp = __my_malloc(__wrkval_buflen);
   return;
  }
 __wrkvalbufp = __my_realloc(__wrkvalbufp, osize, nsize);
 __wrkval_buflen = nsize;
}

/*
 * convert one 
 * need to also dump initial value
 */
static void udp_line_to_str(char *s, struct udp_t *udpp, struct utline_t *utlp)
{
 int32 i, numins;
 char *chp, s1[RECLEN];

 numins = udpp->numins;
 strcpy(s, "");
 for (chp = utlp->tline, i = 0; i < numins; i++, chp++)
  {    
   /* the one possible edge */
   if (utlp->uledinum == i)
    {
     /* special wild card types edges are kept as original char */
     /* 01 and 10 are converted from rise-fall - convert back */
     if (utlp->utabsel == '0' && *chp == '1') strcat(s, "    r");
     else if (utlp->utabsel == '1' && *chp == '0') strcat(s, "    f");
     else if (utlp->utabsel == '*') strcat(s, "    *");
     else if (utlp->utabsel == 'p') strcat(s, "    p");
     else if (utlp->utabsel == 'n') strcat(s, "    n");
     else
      {
       sprintf(s1, " (%c%c)", (char) utlp->utabsel, *chp);
       strcat(s, s1);
      }
    }
   /* various wild cards and states left as input char */
   else { sprintf(s1, "%5c", *chp); strcat(s, s1); }
  }
 if (udpp->utyp != U_COMB)
  { sprintf(s1, " : %c ", *chp); strcat(s, s1); chp++; }
 sprintf(s1, " : %c ;", *chp);
 strcat(s, s1);
}

/*
 * VPI PUT VALUE ROUTINES
 */

/*
 * assign to an object from value_p possibly forcing or scheduled
 *
 * if vpiReturnEvent bit on in flags, return event else nil
 */
extern vpiHandle vpi_put_value(vpiHandle object, p_vpi_value value_p, 
 p_vpi_time time_p, PLI_INT32 flags)
{
 int32 ndx, bi, wid, ret_event; 
 word32 dtyp;
 struct h_t *hp, *hp2;
 word64 ticksdel;
 struct net_t *np;
 struct xstk_t *xsp;
 struct net_pin_t *npp;
 struct hrec_t *hrp;
 struct mod_t *cur_mdp;
 decl_idp_locals_;

 /* must reset at start of call to no error */
 __last_eip = NULL;
 if (__run_state == SS_COMP)
  { __still_comp_err("vpi_put_value"); return(NULL); } 
 hp = (struct h_t *) object;
 if (!__validate_handle("vpi_put_value", hp)) return(NULL);
 hrp = hp->hrec;

 /* AIV 05/29/09 - can have init for wire w = $plicall at init state */
 if (__run_state != SS_LOAD && __run_state != SS_SIM)
  {
   if (hrp->htyp != vpiSpecParam && hrp->htyp != vpiParameter)
    {
     __sim_notbegun_err("vpi_put_value of non param");
     return(NULL);
    }
  }
 /* set extra flag and remove return event bit */
 ret_event = FALSE;
 if ((flags & vpiReturnEvent) != 0)
  { dtyp = (word32) (flags & ~vpiReturnEvent); ret_event = TRUE; }
 else dtyp = (word32) flags; 

 if (__rosync_slot)
  {
   /* put value for future time is legal in ro sync slot */
   if (!putv_in_future(dtyp, time_p))
    {
     __bad_rosync_err("vpi_put_value");
     return(NULL);
    }
  }

 set_save_idp_(hp->hin_idp);

 /* check all flag and handle combinations - does not check vpi_time rec */
 if (!chk_putv_args(dtyp, hp, value_p))
  {
   restore_idp_();
   return(NULL);
  }

 switch (dtyp) {
  case vpiCancelEvent: 
   /* remove scheduled (must exist) and free dputv record */
   /* free needed because marking cancelled free does not free guts */
   /* does nothing if event (or some from vectored table done) */
   free_putv_sched(hp); 
   /* user problem to free this handle if needed */
   break;
  case vpiAddDriver:
   if (hrp->htyp == vpiNet) hp2 = add_net_driver(hp);
   else if (hrp->htyp == vpiNetBit) hp2 = add_netbit_driver(hp);
   else { __vpi_terr(__FILE__, __LINE__); hp2 = NULL; }
   restore_idp_();
   return((vpiHandle) hp2);
  case vpiForceFlag:
   /* force release on wire not on special array form driver or event */
   ndx = __get_vpinet_index(&np, hp);
   wid = (ndx == -1) ? np->nwid : 1;
   /* for vpi wire bit push the bit value will force bit ndx in wire */ 
   /* always need to push non strength even if strength wire because */
   /* must add strong not use actual strength */
   if ((xsp = push_vpi_valuep(value_p, wid, np->ntyp, FALSE)) == NULL)
    break;

   if (np->ntyp >= NONWIRE_ST) reg_vpi_force(np, xsp->ap, xsp->bp);
   else
    {
     /* SJM 11/14/00 - if wire in tran channel force all wires in it */
     /* SJM 03/15/01 - can't force all of tran channel - just soft force */
     /* this tran wire and re-eval tran channel */
     if (np->ntraux != NULL)
      {
       __tran_wire_vpi_force(np, xsp->ap, xsp->bp, ndx);
       /* SJM 03/15/01 - not sure if vector legal but for scalar -1 illegal */ 
       if (ndx == -1) __eval_tran_bits(np);
       else __eval_tran_1bit(np, ndx);
      }  
     else wire_vpi_force(np, xsp->ap, xsp->bp, ndx);
    }
   __pop_xstk();
   break;
  case vpiReleaseFlag:
   ndx = __get_vpinet_index(&np, hp);
   if (np->ntyp >= NONWIRE_ST) reg_vpi_release(np);
   else
    {
     if (np->ntraux != NULL)
      {
       /* SJM 03/15/01 - did't force all of tran channel - just release */ 
       /* this tran wire and re-eval tran channel */
       __tran_wire_vpi_release(np, ndx);
       /* SJM 02/23/05 - bit objects can be released - not just entire vecs */
       /* thanks to Greenlight for this fix */
       if (ndx == -1) __eval_tran_bits(np);
       else __eval_tran_1bit(np, ndx);
      }
     else wire_vpi_release(np, ndx);
    }
   /* nothing to pop from expr. stack here */
   break;
  case vpiNoDelay:
   switch (hrp->htyp) {
    case vpiSysFuncCall:
     /* special immediate (no schedule) assign case */
     set_vpisfcall_retval(hp, value_p);
     break;
    case vpiSpecParam: case vpiParameter:
     set_vpiparam_val(hp, value_p);
     break;
    case vpiUdpDefn:
     set_vpiudpdef_ival(hp, value_p);
     break;
    case vpiNetDriver: case vpiNetBitDriver: 
     /* can only putv to reg or wire driver which is always per bit */
     /* according to LRM - time p can be nil if not needed */
     /* handle consists of table of per bit handles */
     npp = hrp->hu.hnpp;
     np = npp->elnpp.enp;
     if (npp->npaux == NULL || npp->npaux->nbi1 == -1)
      {
       /* nothing pushed on stack if returns nil */
       if ((xsp = push_vpi_valuep(value_p, np->nwid, np->ntyp, np->n_stren))
        == NULL) break;
       immed_vpi_drv_assign(np, npp->obnum, xsp->ap, xsp->bp); 
       __pop_xstk();
       break;
      }
     bi = npp->npaux->nbi1;
     if ((xsp = push_vpi_valuep(value_p, 1, np->ntyp, np->n_stren)) == NULL)
      break;
     immed_vpibit_drv_assign(np, npp->obnum, bi, xsp->ap, xsp->bp); 
     __pop_xstk();
     /* no scheduled event handle to return */
     break;
    case vpiNet: case vpiNetBit:
     /* SJM 07/24/00 - no delay assign just changes net value */
     ndx = __get_vpinet_index(&np, hp);
     wid = (ndx == -1) ? np->nwid : 1;
     /* wire and expected can never be strength here */
     /* SJM 08/03/00 - this may be soft force of strength value */
     if ((xsp = push_vpi_valuep(value_p, wid, np->ntyp, np->n_stren)) == NULL)
      break;

     /* following acc_ routines, no delay set ignored any pending assigns */ 
     /* SJM 11/14/00 - for soft force of in tran chan (inout), now soft */
     /* all wires in tran chan */ 
     /* SJM 03/15/01 - can't force all of tran channel - just soft force */
     /* this tran wire and re-eval tran channel */
     if (np->ntraux != NULL)
      {
       __tran_exec_putv_wire_softforce(np, xsp->ap, xsp->bp, ndx);
       /* SJM 03/15/01 - not sure if vector legal but for scalar -1 illegal */ 
       if (np->n_isavec) __eval_tran_1bit(np, ndx);
       else __eval_tran_bits(np);
      }
     else exec_putv_wire_softforce(np, xsp->ap, xsp->bp, ndx);

     __pop_xstk();
     break;
    case vpiMemoryWord:
     /* SJM 09/30/06 -> thanks to Bryan Catanzaro from Tabula for this */
     /* it is legal to put value to a vpi memory word - we forgot this cae */
     /* see 2005 LRM - put value not explicitly allowed but needed - LRM typo */
     ndx = __get_vpinet_index(&np, hp);
     wid = np->nwid;
     
     /* can never be wire or strength here */
     if ((xsp = push_vpi_valuep(value_p, wid, np->ntyp, FALSE)) == NULL)
      break;
     /* following acc_ routines, no delay set ignored any pending assigns */ 
     exec_putv_reg_assign(np, xsp->ap, xsp->bp, ndx);
     __pop_xstk();
     break;
    default:
     /* all regs and vars here */
     /* know good - checking in already called putv check routine */
     /* final case is immedate assign to reg or reg bit */
     ndx = __get_vpinet_index(&np, hp);
     wid = (ndx == -1) ? np->nwid : 1;
     /* can never be wire or strength here */
     if ((xsp = push_vpi_valuep(value_p, wid, np->ntyp, FALSE)) == NULL)
      break;
     /* following acc_ routines, no delay set ignored any pending assigns */ 
     exec_putv_reg_assign(np, xsp->ap, xsp->bp, ndx);
     __pop_xstk();
   }
   break;
  case vpiInertialDelay: case vpiTransportDelay: case vpiPureTransportDelay:
   cur_mdp = get_inst_mod_();
   if (!__vpitime_to_ticks(&ticksdel, time_p, cur_mdp)) return(NULL);
   if (hrp->htyp != vpiNetDriver && hrp->htyp != vpiNetBitDriver)
    {
     /* know this is wire or reg or bit of reg (or var) or net or net bit */
     ndx = __get_vpinet_index(&np, hp);
     hp2 = setschd_var_fromvaluep(value_p, np, ndx, ticksdel, dtyp, ret_event);
    }
   else
    {
     /* wire delayed wire driver assignm (bit or table entire wire) */
     hp2 = setschd_drvr_fromvaluep(value_p, hp, ticksdel, dtyp, ret_event);
    }

   /* for release if no error, final step is getting after released value */
   if (__last_eip == NULL && (flags & ~vpiReturnEvent) == vpiReleaseFlag) 
    vpi_get_value(object, value_p);
   restore_idp_();
   return((vpiHandle) hp2);
  default:
    /* should never get here because of previous checking */
   __vpi_terr(__FILE__, __LINE__);
   break;
  }
 restore_idp_();
 return(NULL);
}

/*
 * return T if put value is for future time so is allowed in ro sync slot
 */
static int32 putv_in_future(word32 dtyp, p_vpi_time time_p)
{
 word64 ticksdel;
 struct mod_t *cur_mdp;

 switch (dtyp) {
  case vpiCancelEvent:
   /* can always cancel since only events in queue are for future */
   return(TRUE);
  case vpiAddDriver: case vpiForceFlag: case vpiReleaseFlag: case vpiNoDelay:
   /* these always immediate */
   break;
  case vpiInertialDelay: case vpiTransportDelay: case vpiPureTransportDelay:
   /* these ok if delay not 0 */
   /* LOOKATME - maybe these errors should be caught elsewhere - not stop */
   if (time_p == NULL) break;
   cur_mdp = get_inst_mod_();
   if (!__vpitime_to_ticks(&ticksdel, time_p, cur_mdp)) break;
   if (ticksdel != 0ULL) return(TRUE);  
   break;
  default: break;
 } 
 return(FALSE);
}

/*
 * PUTV CHECKING ROUTINES
 */

/*
 * routine to check combination of dtyp (flag with vpiReturnEvent) and object
 * for put value - emits errors and return F on error
 *
 * this requires pushed itree context
 */
static int32 chk_putv_args(word32 dtyp, struct h_t *hp, p_vpi_value value_p) 
{
 struct hrec_t *hrp;
 struct net_t *np;
 char s1[RECLEN];

 hrp = hp->hrec;
 switch (dtyp) {
  case vpiCancelEvent: 
   /* this can be reg (also var) or scalar net or bit of vector net */
   if (hrp->htyp != vpiSchedEvent && hrp->htyp != vpiSchedBitEvent)
    {
     __vpi_err(1904, vpiError,
      "vpi_put_value flag vpiCancelEvent requires vpiSchedEvent or vpiSchedBitEvent - %s passed",
      __to_vpionam(__wrks1, hrp->htyp));
     return(FALSE);
    }
   break; 
  case vpiAddDriver:
   if (hrp->htyp == vpiNetBit)
    {
     if (hrp->bith_ndx) np = hrp->hu.hnp;
     else np = hrp->hu.hxp->lu.x->lu.sy->el.enp;

     /* DBG remove --- */
     if (!np->n_isavec) __vpi_terr(__FILE__, __LINE__);
     /* ---*/
    }
   else if (hrp->htyp == vpiNet) np = hrp->hu.hnp;
   else
    {
     __vpi_err(1903, vpiError,
      "vpi_put_value flag vpiAddDriver object %s illegal not vpiNet or vpiNetBit", 
      __to_vpionam(__wrks1, hrp->htyp));
     return(FALSE);
    }
   /* DBG remove --- */
   if (np->ntyp >= NONWIRE_ST) __vpi_terr(__FILE__, __LINE__);
   /* --- */
   if (np->n_gone) goto net_gone;
   /* can not add driver getpat lhs wire - can only have one driver */
   if (net_ongetpat_lhs(np))
    {
     putv_flag_to_str(s1, dtyp);
     __vpi_err(1913, vpiError,
      "vpi_put_value %s flag wire %s part of $getpattern lvalue concatenate illegal - can only have one driver",
      s1, np->nsym->synam);
     return(FALSE);
    }
   /* SJM 03/23/00 - now because global nodes are XMRs can add */
   break;
  case vpiForceFlag: case vpiReleaseFlag:
   /* can not force/release vpi added driver terminals only nets and bits of */
   /* force release always immediate */
   switch (hrp->htyp) {
    case vpiNetBit:
     if (hrp->bith_ndx) np = hrp->hu.hnp;
     else np = hrp->hu.hxp->lu.x->lu.sy->el.enp;

     if (np->n_gone) goto net_gone;
     break;
    case vpiIntegerVar: case vpiTimeVar: case vpiReg: case vpiNet:
     np = hrp->hu.hnp;
     if (np->n_gone) goto net_gone;
     break;
    case vpiRegBit: case vpiVarSelect:
     putv_flag_to_str(s1, dtyp);
     __vpi_err(1914, vpiError,
      "vpi_put_value illegal %s flag for vpiRegBit/vpiVarSelect - entire variable only", s1);
     return(FALSE);
    default:
     putv_flag_to_str(s1, dtyp);
     __vpi_err(1915, vpiError,
      "vpi_put_value %s flag object %s illegal - must be variable or variable bit",
      s1, __to_vpionam(__wrks1, hrp->htyp));
     return(FALSE);
   }
   break;
  case vpiNoDelay: case vpiInertialDelay: case vpiTransportDelay:
  case vpiPureTransportDelay:
   if (!good_value_p(value_p)) return(FALSE);
   /* net type specific checking */
   switch (hrp->htyp) {
    case vpiReg: case vpiIntegerVar: case vpiTimeVar: case vpiRealVar:
     np = hrp->hu.hnp;
     break;
    case vpiRegBit: case vpiVarSelect: case vpiMemoryWord:
     /* can assign to (but not force release) reg that is word32 of array */
     if (hrp->bith_ndx) np = hrp->hu.hnp;
     else np = hrp->hu.hxp->lu.x->lu.sy->el.enp;
     break;
    case vpiNetDriver:
     np = hrp->hu.hnpp->elnpp.enp;
     if (np->n_stren && np->n_isavec)
      {
       putv_flag_to_str(s1, dtyp);
       __vpi_err(2012, vpiWarning,
        "vpi_put_value %s flag to vpiNetDriver strength vector object width %d will only assign to low bit - use vpiNetBitDriver",
       s1, np->nwid);
      }
     /* LOOKATME - maybe need warning for strength wire non strength format */
     break;
    case vpiNetBitDriver:
     np = hrp->hu.hnpp->elnpp.enp;
     /* LOOKATME - maybe need warning for strength wire non strength format */
     break;
    case vpiSpecParam: case vpiParameter:
     /* special case immediate assigns only */
     if (dtyp != vpiNoDelay)
      {
nd_nodel:
       putv_flag_to_str(s1, dtyp);
       __vpi_err(1844, vpiError,
        "vpi_put_value to %s object only vpiNoDelay flag allowed - %s illegal",
        __to_vpionam(__wrks1, hrp->htyp), s1);
       return(FALSE);
      }
     np = hrp->hu.hnp;
     break;
    case vpiSysFuncCall:
     if (dtyp != vpiNoDelay) goto nd_nodel;
     /* handle is function call expr. */ 
     return(TRUE);
    case vpiUdpDefn: 
     if (dtyp != vpiNoDelay) goto nd_nodel;
     /* will extract the needed 1 scalar bit form any value_p - no extra */
     /* checking needed */
     return(TRUE);
    case vpiNet: case vpiNetBit:
     /* SJM 07/24/00 - now supporting soft force (proc assign until next */
     /* driver change) for put value to wires */
     np = hrp->hu.hnp;
     break;
    default:
     putv_flag_to_str(s1, dtyp);
     __vpi_err(1919, vpiError,
      "vpi_put_value %s flag object %s illegal - must be non wire variable or bit of",
      s1, __to_vpionam(__wrks1, hrp->htyp));
     return(FALSE);
   }
   if (np->n_gone)
    {
net_gone:
     putv_flag_to_str(s1, dtyp);
     __vpi_err(1911, vpiError,
      "vpi_put_value %s to net %s illegal - net removed by gate eater - rerun without +gateeater",
      s1, np->nsym->synam);
     return(FALSE);
    }
   break;
  default:
   __vpi_err(1916, vpiError,
    "vpi_put_value delay mode flag %u illegal value", dtyp); 
   return(FALSE);
 }
 return(TRUE);
}

/*
 * convert a flag constant (with vpiReturnEvent bit removed) to its name
 */
static char *putv_flag_to_str(char *s, word32 dtyp)
{
 switch (dtyp) {
  case vpiAddDriver: strcpy(s, "vpiAddDriver"); break;
  case vpiCancelEvent: strcpy(s, "vpiCancelEvent"); break;
  case vpiForceFlag: strcpy(s, "vpiForceFlag"); break;
  case vpiReleaseFlag: strcpy(s, "vpiReleaseFlag"); break;
  case vpiNoDelay: strcpy(s, "vpiNoDelay"); break;
  case vpiInertialDelay: strcpy(s, "vpiInertial"); break;
  case vpiTransportDelay: strcpy(s, "vpiTransportDelay"); break;
  case vpiPureTransportDelay: strcpy(s, "vpiPureTransportDelay"); break;
  default: sprintf(s, "unknown (%lu)", dtyp);
 } 
 return(s); 
}

/*
 * return T if net is on getpattern lhs - can not putv assign to it 
 */
static int32 net_ongetpat_lhs(struct net_t *np)
{
 struct net_pin_t *npp;
 struct conta_t *cap; 

 for (npp = np->ndrvs; npp != NULL; npp = npp->npnxt)
  {
   if (npp->npntyp == NP_CONTA)
    {
     cap = npp->elnpp.ecap;
     if (cap->lhsx->getpatlhs) return(TRUE);
    }
  }
 return(FALSE);
}

/*
 * return T if value_p has good value that can be assigned from
 * also emits error
 */
static int32 good_value_p(p_vpi_value value_p)
{
 int32 sval, s0, s1; 

 if (value_p->format == vpiSuppressVal || value_p->format == vpiObjTypeVal)
  {
   if (value_p->format == vpiSuppressVal) strcpy(__wrks1, "vpiSuppressVal");
   else strcpy(__wrks1, "vpiObjTypeVal");
   __vpi_err(1908, vpiError,
    "vpi_put_value value_p record format %s illegal", __wrks1); 
   return(FALSE);
  }  
 /* strength value is only other one that can be checked */
 else if (value_p->format != vpiStrengthVal) return(TRUE); 

 /* check strength value */
 sval = value_p->value.strength->logic; 
 s0 = value_p->value.strength->s0;
 s1 = value_p->value.strength->s1;
 /* LOOKATME - XL seems to allow 0 to 7 but contradicts LRM and include */ 
 /* strength must be legal vpi_ constant value */
 if (__map_frvpi_stren(s0) == -1 || __map_frvpi_stren(s1) == -1)
  goto bad_stren;
 if (sval == vpiZ) 
  {
   /* for z both must be high z */
   if (s0 != vpiHiZ || s1 != vpiHiZ) goto bad_stren;
  }
 else if (sval == vpiX)
  {
   /* for x, both can't be hiz - but can be edge of range */
   if (s0 == vpiHiZ && s1 != vpiHiZ) goto bad_stren;
  }
 else if (sval == vpi0 || sval == vpi1)
  {
   /* for 0 and 1 both can't be hiz */
   if (s0 == vpiHiZ && s1 == vpiHiZ) goto bad_stren;
  } 
 else goto bad_stren;
 return(TRUE);

bad_stren:
 __vpi_err(1924, vpiError,
  "vpi_put_value passed illegal strength value %d <s1=%d:s0=%d>",
  sval, s1, s0);
 return(FALSE);
}

/*
 * PUTV DESCHEDULING ROUTINES
 */

/*
 * free one putv scheduled - handle is vpiSchedEvent or vpiSchedBitEvent
 *
 * this can be either schedule reg putv assign or net driver putv change
 * or net soft force putv assign
 *
 * reg/soft force can be one bit or entire reg but only one scheduled event
 * always entire reg even if one bit select because vectored
 *
 * for wire this can either be bit of vectored (vpiSchedBitEvent) or special
 * array (one for each bit) or just the one for scalared (vpiSchedEvent)
 *
 * notice users responsibility to make sure event not occurred because
 * storage this handle points to may be gone if user does not check
 * and calls will core dump
 */
static void free_putv_sched(struct h_t *hp)
{
 int32 bi;
 struct tev_t *tevp; 
 struct hrec_t *hrp;
 struct tev_t **evtabp;
 struct net_t *np;

 hrp = hp->hrec;
 /* does nothing if event completed (or maybe already cancelled) */
 if (hrp->evnt_done) return;

 /* case 1: vpi Sched Event and not scalar */
 if (hrp->bith_ndx)
  {
   /* table form only for vectored entire wire scheduled */
   /* cancel each bit event that has not already been canceled or happened */
   np = hrp->hu.hevrec->evnp;
   evtabp = hrp->hu.hevrec->evndxtab;
   for (bi = np->nwid - 1; bi >= 0; bi--)
    {
     tevp = evtabp[bi];
     if (tevp == NULL || (tevp->enterptr == __process_cancel_ev_enterp))
      continue;
     free_netbitdrv_putv_sched(np, bi, hp->hin_idp, tevp);
    }
   /* LOOKATME - maybe should free table here? */
   hrp->evnt_done = TRUE;
   return;
  } 
 tevp = hrp->hu.htevp;
 np = tevp->tu.teputvp->np;

 /* case 2: reg putv assign (not driver) - can be bit or entire vector */ 
 /* but in both case only one event */
 /* SJM 07/25/00 - also free soft force event here */  
 /* here hp set to done if event canceled */
 if (np->ntyp >= NONWIRE_ST || tevp->vpi_regwir_putv)
  {
   free_regwir_putv_sched(np, hp->hin_idp, tevp);
   hrp->evnt_done = TRUE;
   return;
  }

 /* case 3: scheduled scalar wire or bit of vectored wire */
 if (!np->n_isavec) bi = 0; else bi = tevp->tu.teputvp->nbi;
 free_netbitdrv_putv_sched(np, bi, hp->hin_idp, tevp);
 hrp->evnt_done = TRUE;
}

/*
 * free putv scheduled reg or wire soft force event either entire net or bit
 */
static void free_regwir_putv_sched(struct net_t *np, t_midat *idp,
 struct tev_t *tevp) 
{
 struct dltevlst_t *dlp;
 struct teputv_t *tepvp;
 int32 itinum;

 itinum = (int32) idp[MD_INUM];
 tepvp = tevp->tu.teputvp;
 dlp = np->regwir_putv_tedlst[itinum];
 /* find event */
 for (; dlp != NULL; dlp = dlp->terp)  
  { if (tevp == dlp->tevp) goto found_event; }

found_event:
 /* link out event - case 1: at front */
 if (dlp->telp == NULL)
  {
   np->regwir_putv_tedlst[itinum] = dlp->terp;
   if (dlp->terp != NULL) dlp->terp->telp = NULL;
  }
 /* case 2: at end and list longer than 1 */
 else if (dlp->terp == NULL) dlp->telp->terp = NULL;
 /* case 3: inside - excise out dlp */
 else { dlp->telp->terp = dlp->terp; dlp->terp->telp = dlp->telp; }

 /* never strength but can be entire vector or 1 bit for reg bit object */
 if (tepvp->nbi == -1)
  __my_free(tepvp->putv_wp, 2*wlen_(np->nwid)*WRDBYTES);
 else __my_free(tepvp->putv_wp, 2*WRDBYTES);

 tepvp->putv_wp = NULL;
 /* free te putv by linking on free list */
 tepvp->np =  (struct net_t *) __teputvfreelst;
 __teputvfreelst = tepvp;
 /* done with dlp */  
 dlp->terp = __dltevfreelst;
 __dltevfreelst = dlp;
 /* finally empty the event (not really needed) */
 tevp->tu.teputvp = NULL;
 tevp->enterptr = __process_cancel_ev_enterp;
}

/*
 * free a putv scheduled net driver bit event
 * scalar possible where index is 0 not -1
 */
static void free_netbitdrv_putv_sched(struct net_t *np, int32 bi,
 t_midat *idp, struct tev_t *tevp) 
{
 int32 evi;
 struct dltevlst_t *dlp;
 struct teputv_t *tepvp;
 struct vpi_drv_t *vpidrvp;
 int32 itinum;
 
 itinum = (int32) idp[MD_INUM];
 evi = np->nwid*itinum + bi;
 tepvp = tevp->tu.teputvp;
 vpidrvp = np->vpi_ndrvs[tepvp->di]; 
 dlp = vpidrvp->putv_drv_tedlst[evi];

 /* find event */
 for (; dlp != NULL; dlp = dlp->terp)  
  { if (tevp == dlp->tevp) goto found_event; }

found_event:
 /* link out event - case 1: at front */
 if (dlp->telp == NULL)
  {
   vpidrvp->putv_drv_tedlst[evi] = dlp->terp;
   if (dlp->terp != NULL) dlp->terp->telp = NULL;
  }
 /* case 2: at end and list longer than 1 */
 else if (dlp->terp == NULL) dlp->telp->terp = NULL;
 /* case 3: inside - excise out dlp */
 else { dlp->telp->terp = dlp->terp; dlp->terp->telp = dlp->telp; }

 /* always 1 bit */
 __my_free(tepvp->putv_wp, 2*WRDBYTES);

 tepvp->putv_wp = NULL;
 /* free te putv by linking on free list */
 tepvp->np =  (struct net_t *) __teputvfreelst;
 __teputvfreelst = tepvp;
 /* done with dlp */  
 dlp->terp = __dltevfreelst;
 __dltevfreelst = dlp;
 /* finally empty the event (not really needed) */
 tevp->tu.teputvp = NULL;
 tevp->enterptr = __process_cancel_ev_enterp;
}

/*
 * ROUTINES TO DYNAMICALLY ADD VPI DRIVER (TERMINAL) TO NET 
 */

/*
 * dynamically add a vpi put value record for entire net 
 * construct driver object
 *
 * vpi put value driver and scheduled record allocated when driver terminal
 * added using vpi_put_value with flag vpiAddDriver (this routine does it)
 *
 * only needed for vpi_ since only one possibly added tf_ driver can be added
 * during prep because only works across systf arguments and must be registered
 * in available at compile time fixed table
 *
 * added driver always initialized to hiz
 *
 * called with current itree loc on itree stack
 * LOOKATME - maybe need error for "vectored" wire 
 */
static struct h_t *add_net_driver(struct h_t *hp) 
{
 int32 di;
 struct vpi_drv_t *vpidrvp;     
 int32 drvi; 
 size_t osize, nsize;
 struct mod_t *mdp;
 struct net_t *np;
 struct net_pin_t *npp;
 struct xstk_t *xsp;
 struct h_t *hp2;

 mdp = (struct mod_t *) hp->hin_idp[MD_MDP];
 np = hp->hrec->hu.hnp;
 push_xstk_(xsp, np->nwid);
 /* build and initialize the added driver - maybe just set some active bits */
 /* case 1: no drivers */
 if (np->vpi_ndrvs == NULL)
  {
   vpidrvp = alloc_vpidrv(np, mdp->flatinum);
   /* allocate driving values and initialize to z */
   putv_drvwp_allocinit(mdp, np, vpidrvp, TRUE);

   /* build the table will nil ptr fence one past end */
   np->vpi_ndrvs =
    (struct vpi_drv_t **) __my_malloc(2*sizeof(struct vpi_drv_t *));
   np->vpi_ndrvs[0] = vpidrvp;
   np->vpi_ndrvs[1] = NULL;
   drvi = 0;
   /* since new, know will be unused */
   __ld_perinst_val(xsp->ap, xsp->bp, vpidrvp->vpi_hasdrv, np->nwid);
   goto set_vec_used;
  }
 /* case 2: some drivers and one has all vector bits for cur. itree unused */
 for (di = 0;; di++)
  {
   if ((vpidrvp = np->vpi_ndrvs[di]) == NULL) break;

   __ld_perinst_val(xsp->ap, xsp->bp, vpidrvp->vpi_hasdrv, np->nwid);
   if (vval_is0_(xsp->ap, np->nwid)) { drvi = di; goto set_vec_used; }
  }
 /* case 3: need to add new (after first) driver in pos. di */
 if (di >= MAXNUMPORTS)
  {
   char s1[RECLEN];

   strcpy(s1, np->nsym->synam);
   __pv_terr(326,
    "INTERNAL FATAL - more than %d vpi wire drivers added to %s - contact Tachyon DA",
     MAXNUMPORTS, s1);
  }
 /* alloc and fill new every inst. and every bit driver - marks inst. used */
 vpidrvp = alloc_vpidrv(np, mdp->flatinum);
 /* allocate driving values and initialize to z */
 putv_drvwp_allocinit(mdp, np, vpidrvp, TRUE);
 
 /* realloc to increase size of table - set new driver and end fence */
 osize = (di + 1)*sizeof(struct vpi_drv_t *);
 nsize = osize + sizeof(struct vpi_drv_t *); 
 np->vpi_ndrvs = (struct vpi_drv_t **)
  __my_realloc(np->vpi_ndrvs, osize, nsize);
 np->vpi_ndrvs[di] = vpidrvp;
 np->vpi_ndrvs[di + 1] = NULL;
 drvi = di;
 __ld_perinst_val(xsp->ap, xsp->bp, vpidrvp->vpi_hasdrv, np->nwid);

set_vec_used:
 /* know instance's has driver value loaded */
 one_allbits_(xsp->ap, np->nwid);
 __st_perinst_val(vpidrvp->vpi_hasdrv, np->nwid, xsp->ap, xsp->bp);
 __pop_xstk(); 

 /* convert to fi>1 (even if only the new vpi driver) */   
 if (!np->n_multfi) chg_net_to_multfi(np, mdp);


 /* build and add the npp */
 __cur_npnum = 0;
 __cur_npnp = np;
 npp = __alloc_npin(NP_VPIPUTV, -1, -1);
 /* object number for vpi driver is index among many possible added drivers */ 
 npp->obnum = drvi;
 npp->npnxt = np->ndrvs;
 np->ndrvs = npp;
 /* DBG remove --- */
 if (__debug_flg)
  {
   __dbg_msg(
    ".. mod %s adding %s wire vpi_put_value driver to front\n",
    mdp->msym->synam, np->nsym->synam);
  }
 /* --- */

 /* build the driver handle */
 hp2 = (struct h_t *) __mk_handle(vpiNetDriver, (void *) npp, hp->hin_idp,
  NULL);
 return(hp2);
}

/*
 * allocate and initialize a vpi entire wire driver 
 */
static struct vpi_drv_t *alloc_vpidrv(struct net_t *np, int32 insts)
{
 int32 nbytes;
 struct vpi_drv_t *vpidrvp;

 vpidrvp = (struct vpi_drv_t *) __my_malloc(sizeof(struct vpi_drv_t));
 nbytes = __get_pcku_chars(np->nwid, insts);
 vpidrvp->vpi_hasdrv.wp = (word32 *) __my_malloc(nbytes);
 /* to start no insts or bits have drivers */
 memset(vpidrvp->vpi_hasdrv.bp, 0, nbytes); 

 /* need scheduled list for every bit of every inst */
 nbytes = insts*np->nwid*sizeof(struct dltevlst_t *);
 vpidrvp->putv_drv_tedlst = (struct dltevlst_t **) __my_malloc(nbytes);
 memset(vpidrvp->putv_drv_tedlst, 0, nbytes); 
 return(vpidrvp);
}

/*
 * dynamically add a vpi put value record for one vpi net bit
 * construct driver object
 *
 * vpi put value driver and scheduled record allocated when driver terminal
 * added using vpi_put_value with flag vpiAddDriver (this routine does it)
 *
 * only needed for vpi_ since only one possibly added tf_ driver can be added
 * during prep because only works across systf arguments and must be registered
 * in available at compile time fixed table
 *
 * even for bit case always add entire wire driver
 *
 * added driver always initialized to hiz
 *
 * called with current itree loc on itree stack
 * LOOKATME - maybe need error for "vectored" wire 
 */
static struct h_t *add_netbit_driver(struct h_t *hp) 
{
 int32 di;
 word32 val;
 int32 bi, drvi; 
 size_t osize, nsize;
 struct mod_t *mdp;
 struct net_t *np;
 struct net_pin_t *npp;
 struct vpi_drv_t *vpidrvp;
 struct xstk_t *xsp;
 struct h_t *hp2;

 mdp = (struct mod_t *) hp->hin_idp[MD_MDP];
 bi = get_vpibit_index(&np, hp);
 push_xstk_(xsp, np->nwid);
 /* build and initialize the added driver - maybe just set some active bits */
 /* case 1: no drivers */
 if (np->vpi_ndrvs == NULL)
  {
   vpidrvp = alloc_vpidrv(np, mdp->flatinum);
   /* allocate driving values and initialize to z */
   putv_drvwp_allocinit(mdp, np, vpidrvp, TRUE);

   /* build the table will nil ptr fence one past end */
   np->vpi_ndrvs =
    (struct vpi_drv_t **) __my_malloc(2*sizeof(struct vpi_drv_t *));
   np->vpi_ndrvs[0] = vpidrvp;
   np->vpi_ndrvs[1] = NULL;
   drvi = 0;
   __ld_perinst_val(xsp->ap, xsp->bp, vpidrvp->vpi_hasdrv, np->nwid);
   goto set_bit_used;
  }
 /* case 2: some drivers and one has all vector bits for cur. itree unused */
 for (di = 0;; di++)
  {
   if ((vpidrvp = np->vpi_ndrvs[di]) == NULL) break;
   /* b part unused */
   __ld_perinst_val(xsp->ap, xsp->bp, vpidrvp->vpi_hasdrv, np->nwid);
   val = rhsbsel_(xsp->ap, bi);
   if (val == 0) { drvi = di; goto set_bit_used; }
  } 
 /* case 3: need to add new (after first) driver in pos. di */
 if (di >= MAXNUMPORTS)
  {
   char s1[RECLEN];

   strcpy(s1, np->nsym->synam);
   __pv_terr(326,
    "INTERNAL FATAL - more than %d vpi wire drivers added to %s - contact Tachyon DA",
     MAXNUMPORTS, s1);
  }
 /* alloc and fill new every inst. and every bit driver - marks inst. used */
 vpidrvp = alloc_vpidrv(np, mdp->flatinum);
 /* allocate driving values and initialize to z */
 putv_drvwp_allocinit(mdp, np, vpidrvp, TRUE);
 
 /* realloc to increase size of table - set new driver and end fence */
 osize = (di + 1)*sizeof(struct vpi_drv_t *);
 nsize = osize + sizeof(struct vpi_drv_t *); 
 np->vpi_ndrvs = (struct vpi_drv_t **)
  __my_realloc(np->vpi_ndrvs, osize, nsize);
 np->vpi_ndrvs[di] = vpidrvp;
 np->vpi_ndrvs[di + 1] = NULL;
 drvi = di;

set_bit_used:
 /* set the one inst-bit that is used */
 val = 1;
 __lhsbsel(xsp->ap, bi, val);
 __st_perinst_val(vpidrvp->vpi_hasdrv, np->nwid, xsp->ap, xsp->bp);
 __pop_xstk(); 

 /* convert to fi>1 (even if only the new vpi driver) */   
 if (!np->n_multfi) chg_net_to_multfi(np, mdp);

 /* build and add the npp */
 __cur_npnum = 0;
 __cur_npnp = np;
 npp = __alloc_npin(NP_VPIPUTV, bi, bi);
 
 /* object number for vpi driver is index among many possible added drivers */ 
 npp->obnum = drvi;
 npp->npnxt = np->ndrvs;
 np->ndrvs = npp;
 /* DBG remove --- */
 if (__debug_flg)
  {
   __dbg_msg(
    ".. mod %s adding %s[%d] wire bit vpi_put_value driver to front\n",
    mdp->msym->synam, np->nsym->synam, bi);
  }
 /* --- */

 /* build the driver handle - always bith ndx form */
 hp2 = (struct h_t *) __mk_handle(vpiNetBitDriver, (void *) npp, hp->hin_idp,
  NULL);
 hp2->hrec->hi = bi;
 return(hp2);
}

/*
 * return T if instance itp of net np has vpi_ putv drivers for npp bits
 *
 * npp (NP VPIPUTV only) either entire wire or one bit
 * this needs instance to check to be on top of itree stack
 */
extern int32 __has_vpi_driver(struct net_t *np, struct net_pin_t *npp)
{
 int32 rv;
 word32 val;
 struct vpi_drv_t *vpidrvp;     
 struct xstk_t *xsp;

 vpidrvp = np->vpi_ndrvs[npp->obnum];
 if ((vpidrvp = np->vpi_ndrvs[npp->obnum]) == NULL) return(FALSE);
 rv = FALSE;
 push_xstk_(xsp, np->nwid);
 __ld_perinst_val(xsp->ap, xsp->bp, vpidrvp->vpi_hasdrv, np->nwid);
 if (npp->npaux == NULL || npp->npaux->nbi1 == -1) 
  {
   /* all bits must be one */
   if (__vval_is1(xsp->ap, np->nwid)) rv = TRUE;
   goto done;
  }
 /* bit select case */
 val = rhsbsel_(xsp->ap, npp->npaux->nbi1);
 if (val == 1) rv = TRUE;
done:
 __pop_xstk();
 return(rv);
}

/*
 * reinitialize putvrec drivers for net
 * called when resetting from prep code
 *
 * there may be multiple so must loop thru until hitting ending fence
 *
 * leave the drivers (npps) and has drv bits sets but reset driving to z
 * and free vents
 */
extern void __reinit_netdrvr_putvrec(struct net_t *np, struct mod_t *mdp)
{
 int32 bi, di, ii;
 struct dltevlst_t *dlp, *dlp2, *last_dlp;
 struct vpi_drv_t *vpidrvp;

 for (di = 0;; di++)
  {
   if ((vpidrvp = np->vpi_ndrvs[di]) == NULL) break;

   /* DBG remove -- */
   if (vpidrvp->vpi_drvwp.wp == NULL) __arg_terr(__FILE__, __LINE__);
   /* --- */ 
   putv_drvwp_allocinit(mdp, np, vpidrvp, FALSE);

   /* events will be in event queue and already freed */ 
   /* find last and link dlp's onto it */
   for (ii = 0; ii < mdp->flatinum; ii++) 
    {
     /* ?? LOOKATME - this was low to high */
     for (bi = np->nwid - 1; bi >= 0; bi--)
      {
       if ((dlp = vpidrvp->putv_drv_tedlst[ii*np->nwid + bi]) == NULL)
        continue;
       last_dlp = NULL;
       for (dlp2 = dlp; dlp2 != NULL; dlp2 = dlp2->terp) last_dlp = dlp2;
       /* SJM 08/02/01 - add if too keep lint happy */
       if (last_dlp != NULL) last_dlp->terp = __dltevfreelst; 
       __dltevfreelst = dlp;
       vpidrvp->putv_drv_tedlst[ii*np->nwid + bi] = NULL; 
      }
    }
  }
}

/*
 * initialize and maybe allocate a a putv driver (only for wires)
 *
 * notice drivers are always one bit but need one per inst
 */
static void putv_drvwp_allocinit(struct mod_t *mdp, struct net_t *np,
 struct vpi_drv_t *vpidrvp, int32 nd_alloc)
{
 int32 ii, nbytes, sav_inum;
 byte *sbp;
 struct xstk_t *xsp;
 struct itree_t *cur_itp;

 /* for wire need drivers */
 if (np->n_stren)
  {
   if (nd_alloc)
    sbp = vpidrvp->vpi_drvwp.bp = (byte *) __my_malloc(mdp->flatinum*np->nwid);
   else sbp = vpidrvp->vpi_drvwp.bp;
   set_byteval_(sbp, mdp->flatinum*np->nwid, ST_HIZ);
  }
 else 
  {
   /* this is per inst. packed one bit non strength driver value */
   if (nd_alloc)
    {
     nbytes = __get_pcku_chars(np->nwid, mdp->flatinum);
     vpidrvp->vpi_drvwp.wp = (word32 *) __my_malloc(nbytes);
    } 
   push_xstk_(xsp, np->nwid);
   zero_allbits_(xsp->ap, np->nwid);
   one_allbits_(xsp->bp, np->nwid);
   __push_wrkitstk(mdp, 0);
//AIV INUM FIXME - isn't this dumb because pushing workitstk why get inst???
   cur_itp = get_itp_();
   sav_inum = cur_itp->itinum;
   for (ii = 0; ii < mdp->flatinum; ii++) 
    {
     cur_itp->itinum = ii;
     __idp[MD_INUM] = (t_midat) sav_inum;
     /* do not need mod con table here */
     __st_perinst_val(vpidrvp->vpi_drvwp, np->nwid, xsp->ap, xsp->bp);
    }
   cur_itp->itinum = sav_inum;
   __idp[MD_INUM] = (t_midat) sav_inum;
   __pop_wrkitstk();
   __pop_xstk();
  }    
}

/*
 * change a wire from fi==1 to multi-fi - reorganize nl data structure
 *
 * find and set x_multfi bits on driving expressions
 * notice even if no drivers so really only 1 driver, vpi drivers always fi>1
 * i.e. will never see NP_VPIPUTV in old npp loop here
 */
static void chg_net_to_multfi(struct net_t *np, struct mod_t *mdp)
{
 int32 ii, bi;
 int32 lhslen, inum;
 byte *sbp, *sbp2;
 struct net_pin_t *npp;
 struct gate_t *gp;
 struct conta_t *cap, *pbcap;
 struct mod_pin_t *mpp;
 struct xstk_t *xsp;
 struct inst_t *ip;
 struct expr_t *lhsxp;
 struct tfrec_t *tfrp;
 struct tfarg_t *tfap;
 struct mod_t *mdp2;
 struct itree_t *itp;
 struct tev_t *tevp;
 t_midat *idp;
 decl_idp_locals_;

 if (__compiled_sim)
  {
   __vpi_err(1928, vpiError,
    " vpiAddDriver not allowed with compiled simulation - run in interpreted mode (+interp)\n");
   return;
  }
 np->n_multfi = TRUE;
 for (npp = np->ndrvs; npp != NULL; npp = npp->npnxt)
  {
   switch ((byte) npp->npntyp) {
    case NP_GATE:
     gp = npp->elnpp.egp;
     /* DBG remove --- 
     if (gp->gpins[0]->x_multfi) __vpi_terr(__FILE__, __LINE__);
     --- */
     gp->gpins[0]->x_multfi = TRUE;
     /* set gchg assign routine to std unaccelerated since fi>1 now */
     __vpi_set_chg_proc(gp);
     /* must make sure all gate change events not yet processed use std */
     if (gp->schd_tevs_ofs != 0)
      {
       for (ii = 0; ii < mdp->flatinum; ii++)
        {
         idp = mdp->moditps[ii]->it_idp;
         if ((tevp = (struct tev_t *) idp[gp->schd_tevs_ofs]) != NULL)
          tevp->gev_acc = FALSE;
        }
      }
     break;
    case NP_CONTA:
     cap = npp->elnpp.ecap;
     /* DBG remove --- 
     if (cap->lhsx->x_multfi) __vpi_terr(__FILE__, __LINE__);
     --- */
     /* SJM 09/20/02 - per bit conta needs to process contained conta */
     /* and if any bits fi>1 all are */
     if (cap->ca_pb_sim)
      {
       /* must mark all per bit lhs expr, as per bit if any are */  
       cap->lhsx->x_multfi = TRUE;
       for (bi = 0; bi < cap->lhsx->szu.xclen; bi++)
        {
         pbcap = &(cap->pbcau.pbcaps[npp->pbi]);
         pbcap->lhsx->x_multfi = TRUE; 
         if (cap->ca_delrep != DT_NONE) break;

         /* DBG remove -- */ 
         if (pbcap->lhsx->szu.xclen != 1) __misc_terr(__FILE__, __LINE__);
         /* --- */
         __init_all_inst_conta_drv(pbcap->ca_drv_ofs, 1, mdp);
         /* set value from rhs conta value - now fi>1 */
         save_idp_();
         for (ii = 0; ii < mdp->flatinum; ii++)
          {
           set_idp_(mdp->moditps[ii]->it_idp);
           xsp = __eval_xpr(pbcap->rhsx);
           __st_idp_val(&(__idp[pbcap->ca_drv_ofs]), 1, xsp->ap, xsp->bp);
           __pop_xstk();
          }
         restore_idp_();
        }
      }
     else
      {
       cap->lhsx->x_multfi = TRUE;
       /* if has delay, already using ca_drv_ofs */
       if (cap->ca_delrep != DT_NONE) break;

       /* but if no delay must alloc and set schd/drv values */
       lhslen = cap->lhsx->szu.xclen;
       __init_all_inst_conta_drv(cap->ca_drv_ofs, lhslen, mdp);
       /* set value from rhs conta value - now fi>1 */
       save_idp_();
       for (ii = 0; ii < mdp->flatinum; ii++)
        {
         set_idp_(mdp->moditps[ii]->it_idp);
         xsp = __eval_xpr(cap->rhsx);
         if (xsp->xslen != lhslen)
          {
           if (xsp->xslen < lhslen)
            {
             /* SJM 05/10/04 - if widening and signed, must sign extend */
             if (cap->rhsx->has_sign) __sgn_xtnd_widen(xsp, lhslen);
             else __sizchg_widen(xsp, lhslen);
            }
           else __sizchgxs(xsp, lhslen);
          }

         __st_idp_val(&(__idp[cap->ca_drv_ofs]), lhslen, xsp->ap, xsp->bp);
         __pop_xstk();
        }
       restore_idp_();
      }
     break;
    case NP_ICONN:
     /* SJM 04/21/00 - for non local drivers, must move use right itree loc */
     if (npp->npproctyp != NP_PROC_INMOD)
      {
       /* SJM 04/17/03 - if XMR path does not match do not change here */
       if ((itp = __get_npprefloc(npp)) != NULL)
        {
         set_save_idp_itp_(itp);
         mdp2 = get_inst_mod_();
         ip = &(mdp2->minsts[npp->elnpp.eii]);
         lhsxp = ip->ipins[npp->obnum];  
         lhsxp->x_multfi = TRUE;
         /* need port for setting std assign routine */
         mpp = &(ip->imsym->el.emdp->mpins[npp->obnum]);
         __vpi_set_upiconnport_proc(mpp);
         restore_idp_();
        }
       break;
      }

     /* assignment from down to up iconn - maybe >1 inst must no accelerate */
     /* LOOKATME - maybe could find some accelerating cases but xmr prob? */ 
     ip = &(mdp->minsts[npp->elnpp.eii]);
     lhsxp = ip->ipins[npp->obnum];  
     /* DBG remove --- SJM 03/07/99 
     if (lhsxp->x_multfi) __vpi_terr(__FILE__, __LINE__);
     --- */
     lhsxp->x_multfi = TRUE;
     /* need port for setting std assign routine */
     mpp = &(ip->imsym->el.emdp->mpins[npp->obnum]);
     __vpi_set_upiconnport_proc(mpp);
     break;
    case NP_MDPRT:
     /* the elnpp is module, but already have it */
     mpp = &(mdp->mpins[npp->obnum]);
     /* DBG remove --- SJM 10/18/99 
     if (mpp->mpref->x_multfi) __vpi_terr(__FILE__, __LINE__);
     --- */
     mpp->mpref->x_multfi = TRUE;
     if (mpp->has_scalar_mpps)
      {
       for (bi = 0; bi < mpp->mpwide; bi++)
        {
         __vpi_set_downtomdport_proc(&(mpp->pbmpps[bi]), np);
        }
      }
     else __vpi_set_downtomdport_proc(mpp, np);
     break;
    case NP_TFRWARG:
     /* if this was previously fi==1, must change and alloc drv_wp */
     tfrp = npp->elnpp.etfrp;
     tfap = &(tfrp->tfargs[npp->obnum]);
     lhsxp = tfap->arg.axp;
     /* DBG remove ---
     if (lhsxp->x_multfi) __vpi_terr(__FILE__, __LINE__);
     --- */
     /* DBG remove --- */
     if (tfap->tfdrv_wp.wp != NULL) __vpi_terr(__FILE__, __LINE__);
     /* --- */ 
     lhslen = lhsxp->szu.xclen;
     lhsxp->x_multfi = TRUE;
     __alloc_tfdrv_wp(tfap, lhsxp, mdp);
     /* notice value from fi==1 case value of lhs expr - driver is hidden */
     /* must do this for every instance */
     save_idp_();
     for (ii = 0; ii < mdp->flatinum; ii++)
      {
       set_idp_(mdp->moditps[ii]->it_idp);

       xsp = __eval_xpr(lhsxp);
       /* here because lhs is width self determing should never differ */
       /* DBG remove */
       if (lhslen != xsp->xslen) __vpi_terr(__FILE__, __LINE__);
       /* -- */ 
       /* tf can drive strength */
       if (np->n_stren)
        __st_perinst_val(tfap->tfdrv_wp, lhslen, xsp->ap, xsp->bp);
       else
        { 
         sbp = (byte *) xsp->ap;
         sbp2 = tfap->tfdrv_wp.bp;
         inum = get_inum_();
         sbp2 = &(sbp2[lhslen*inum]);
         memcpy(sbp2, sbp, lhslen);
        }
       __pop_xstk();  
      }
     restore_idp_();
     break;
    default: __vpi_terr(__FILE__, __LINE__);
   }  
  }
}

/*
 * PUTV WORK ROUTINES
 */

/*
 * get index for either net or bit of net   
 */
extern int32 __get_vpinet_index(struct net_t **pnp, struct h_t *hp)
{
 int32 ndx;
 struct hrec_t *hrp;
 decl_idp_locals_;

 hrp = hp->hrec;
 /* can vpiVarSelect occur here? */
 switch (hrp->htyp) {
  case vpiRegBit: case vpiNetBit:
  case vpiMemoryWord: case vpiVarSelect:
   if (hrp->bith_ndx) { ndx = hrp->hi; *pnp = hrp->hu.hnp; }
   else
    {
     *pnp = hrp->hu.hxp->lu.x->lu.sy->el.enp;
     set_save_idp_(hp->hin_idp);
     ndx = __comp_ndx(hrp->hu.hxp->lu.sy->el.enp, hrp->hu.hxp->ru.x);
     restore_idp_();
     *pnp = hrp->hu.hxp->lu.x->lu.sy->el.enp;
    }
   return(ndx);
  default: 
   ndx = -1;
   *pnp = hrp->hu.hnp;
 }
 return(ndx);
}

/*
 * get vpiNetBit or vpiRegBit index and net for cases where know Bit handle
 *
 * LOOKATME - maybe expr. form should be illegal here 
 */
static int32 get_vpibit_index(struct net_t **pnp, struct h_t *hp)
{
 int32 ndx;
 struct hrec_t *hrp;
 decl_idp_locals_;

 hrp = hp->hrec;
 if (hrp->bith_ndx)
  { ndx = hrp->hi; *pnp = hrp->hu.hnp; return(ndx); }


 set_save_idp_(hp->hin_idp);
 ndx = __comp_ndx(hrp->hu.hxp->lu.sy->el.enp, hrp->hu.hxp->ru.x);
 restore_idp_();
 *pnp = hrp->hu.hxp->lu.x->lu.sy->el.enp;
 return(ndx);
}

/*
 * convert a value_p value for a variable (handle) into an a/b value
 * on top of the expr stack
 * returns nil on bad value that can not be converted
 *
 * value on stack matches net (handle) in both type and width with zero fill
 * also matches strength with strong added if needed
 * this must run in itree location of handle in case value is time
 *
 * wnen strength need cast to byte ptr then assigns to low bit of it
 */
static struct xstk_t *push_vpi_valuep(p_vpi_value value_p, int32 vwid,
 word32 vntyp, int32 vstren)
{
 int32 wi;
 int32 scanfmt, is_signed, s0val, s1val, i1, wlen, ubits;
 byte *sbp;
 word32 wval;
 double d1;
 word64 timval;
 struct xstk_t *xsp;
 struct mod_t *cur_mdp;
#ifndef __CVC32__
 word32 tmp;
 int32 vndx;
#endif

 is_signed = FALSE;
 xsp = NULL;
 switch ((byte) value_p->format) {
   case vpiStringVal:
    /* SJM 07/11/01 - put value of c style string needs to be supported */
    xsp = __cstr_to_vval(value_p->value.str);
    /* SJM 07/30/01 - must change to vwid (net's width) - trunc or 0 fill */
    /* SJM 05/10/04 - vpi strings can't be signed */
    if (vwid != xsp->xslen) __sizchgxs(xsp, vwid);
    break;
   case vpiBinStrVal:
    scanfmt = 'b';
    strcpy(__wrks1, "vpiBinStrVal");
do_xtract:
    /* extract value_p string into numeric value on tos */
    xsp = __putdstr_to_val(value_p->value.str, vwid, vwid, scanfmt);
    if (xsp == NULL)
     {
      __vpi_err(1917, vpiError,
       "vpi_put_value value_p record format %s value illegal", __wrks1); 
      return(NULL); 
     }
    /* if type of net is real must convert to double */
    if (vntyp == N_REAL)
     {  
      d1 = __cnvt_stk_to_real(xsp, is_signed);
      __pop_xstk();
      push_xstk_(xsp, WBITS);
      memcpy(xsp->ap, &d1, sizeof(double)); 
      return(xsp);
     }   
    break;
   case vpiOctStrVal:
    scanfmt = 'o';
    strcpy(__wrks1, "vpiOctStrVal");
    goto do_xtract; 
   case vpiDecStrVal:
    scanfmt = 'd';
    strcpy(__wrks1, "vpiDecStrVal");
    if (vwid <= WBITS) is_signed = TRUE;
    goto do_xtract; 
   case vpiHexStrVal:
    scanfmt = 'h';
    strcpy(__wrks1, "vpiHexStrVal");
    goto do_xtract; 

   case vpiScalarVal:
    push_xstk_(xsp, vwid);
    zero_allbits_(xsp->ap, vwid);
    zero_allbits_(xsp->bp, vwid);
    wval = (word32) value_p->value.scalar;
    if (!chk_vpi_logicval(wval))
     {  
      __vpi_err(1921, vpiError,
       "vpi_put_value vpiScalarVal passed illegal value %d", wval);
      __pop_xstk();
      return(NULL);
     }
    /* BEWARE this assume vpi[0,1,z,x] are 0, 1, 2, 3 as stored */
    xsp->ap[0] = (wval & 1L);
    xsp->bp[0] = (wval >> 1) & 1L;
    /* it is ok to convert scalar to real which is putved */
    if (vntyp == N_REAL)
     {
      d1 = __cnvt_stk_to_real(xsp, FALSE);
      __pop_xstk();
      push_xstk_(xsp, WBITS);
      memcpy(xsp->ap, &d1, sizeof(double)); 
      return(xsp);
     }
    break;
   case vpiIntVal:
    push_xstk_(xsp, vwid);
    zero_allbits_(xsp->ap, vwid);
    zero_allbits_(xsp->bp, vwid);
    /* know this must be good */
    xsp->ap[0] = (word32) value_p->value.integer;
    if (vntyp == N_REAL) 
     {
      d1 = __cnvt_stk_to_real(xsp, is_signed);
      __pop_xstk();
      push_xstk_(xsp, WBITS);
      memcpy(xsp->ap, &d1, sizeof(double)); 
      return(xsp);
     }  
    break;
   case vpiRealVal:
    /* destination not real */
    d1 = value_p->value.real;
    if (vntyp != N_REAL)
     {  
      if (vntyp == N_INT) 
       {
        i1 = (int32) d1;
        push_xstk_(xsp, vwid);
        xsp->ap[0] = (word32) i1;
        xsp->bp[0] = 0L;
        break;
       }
      if (!__real_to_v64tim(&timval, d1))
       {
        __vpi_err(2016, vpiWarning,  
         "precision lost in converting real %g to 64 bit unsigned", d1);
       }
      push_xstk_(xsp, 64);
#ifdef __CVC32__
      xsp->ap[0] = (word32) (timval & WORDMASK_ULL);
      xsp->ap[1] = (word32) ((timval >> 32) & WORDMASK_ULL);  
      xsp->bp[0] = xsp->bp[1] = 0L;
#else
      /* AIV 08/25/09 - this fits in one for 64-bit */
      xsp->ap[0] = (word32) timval;
      xsp->bp[1] = 0L;
#endif
      /* SJM 05/10/04 - time can't be signed */
      if (vwid != 64) __sizchgxs(xsp, vwid);
      break;
     }
    /* value real and pushing real */
    push_xstk_(xsp, WBITS);
    memcpy(xsp->ap, &d1, sizeof(double)); 
    return(xsp);
   case vpiStrengthVal:
    /* know value_p is 1 bit strength and checked in chk putv already */
    wval = (word32) value_p->value.strength->logic;
    s0val = __map_frvpi_stren(value_p->value.strength->s0);
    s1val = __map_frvpi_stren(value_p->value.strength->s1);
    /* if value is strength, but putting to non strength use logic only */
    if (!vstren)
     {
      /* this forces 8 bytes */
      push_xstk_(xsp, 1);
      xsp->ap[0] = wval; 
      xsp->bp[0] = 0L;
     }
    else
     {
      /* FIXME - should allow array of strengths here too */
      /* this forces 8 bytes */
      push_xstk_(xsp, 4);
      sbp = (byte *) xsp->ap;
      wval |= (((((byte) s0val) & 7L) << 5) | ((((byte) s1val) & 7L) << 2));
      sbp[0] = (byte) wval;
     }
    return(xsp);
   case vpiTimeVal:
    cur_mdp = get_inst_mod_();
    if (!__vpitime_to_ticks(&timval, value_p->value.time, cur_mdp)) break;

    push_xstk_(xsp, vwid);
#ifdef __CVC32__
    /* AIV 08/25/09 - if 64-bit now fits in one word */
    xsp->bp[0] = xsp->bp[1] = 0L;
    xsp->ap[0] = (word32) (timval & WORDMASK_ULL);
    xsp->ap[1] = (word32) ((timval >> 32) & WORDMASK_ULL);
#else
    xsp->ap[0] = timval;
    xsp->bp[0] = 0L;
#endif
    break;
   case vpiVectorVal:
    push_xstk_(xsp, vwid);
    wlen = wlen_(vwid);
    ubits = ubits_(vwid);
#ifdef __CVC32__
    for (wi = 0; wi < (wlen - 1); wi++)
     {
      xsp->ap[wi] = (word32) value_p->value.vector[wi].aval; 
      xsp->bp[wi] = (word32) value_p->value.vector[wi].bval; 
     }
    /* LOOKATME - P1364 problem since do not know width of vector here, */
    /* must 0 unused bits of high word32 from last used vector */
    /* if narrrowing works by accident but widening width change will */
    /* probably result in core dump - vector value_p should contain width */
    xsp->ap[wi] = ((word32) value_p->value.vector[wi].aval) & __masktab[ubits];
    xsp->bp[wi] = ((word32) value_p->value.vector[wi].bval) & __masktab[ubits];
#else
    /* AIV 08/25/09 - vpiVectorVal for 64-bit is still unsigned int - 32-b */
    /* notice it is fine to go one extra +1 because __wrkvalbufp */
    /* pack into 64-bit tmp - and mask last 64-bit if needed */
    /* better to just do extra +1 sometimes than put in a bunch of ifs */
    vndx = 0;
    for (wi = 0; wi < wlen; wi++)
     {
      tmp = value_p->value.vector[vndx].aval & 0xffffffff; 
      tmp |= (((word32) value_p->value.vector[vndx+1].aval) << 32);
      xsp->ap[wi] = tmp; 
      tmp = value_p->value.vector[vndx].bval & 0xffffffff; 
      tmp |= (((word32) value_p->value.vector[vndx+1].bval) << 32);
      xsp->bp[wi] = tmp;
      vndx += 2;
     }
    /* mask the last word if not aligned */
    if (ubits != 0)
     {
      wi = wlen - 1;
      xsp->ap[wi] &= __masktab[ubits];
      xsp->bp[wi] &= __masktab[ubits];
     }
#endif
    
    if (vntyp == N_REAL)
     {
      if (vwid > 64)
       {
        __vpi_err(1918, vpiError,
         "vpi_put_value value_p vpiVectorVal width %d too wide to convert to real",
         vwid);
        return(NULL);
       }
      d1 = __cnvt_stk_to_real(xsp, FALSE);
      __pop_xstk();
      push_xstk_(xsp, WBITS);
      memcpy(xsp->ap, &d1, sizeof(double)); 
      return(xsp);
     }
    return(xsp);
   default: 
    __vpi_err(1925, vpiError,
     "vpi_put_value passed s_vpi_value format value %d illegal",
     value_p->format);
   return(NULL);
  } 
 /* putting to strength value - must convert to 1 bid strength add strong */ 
 if (vstren)
  {
   /* convert only the one low bit */
   wval = (xsp->ap[0] & 1L) | ((xsp->bp[0] & 1L) << 1);
   __pop_xstk();
   push_xstk_(xsp, 4);
   sbp = (byte *) xsp->ap;
   s0val = s1val = __map_frvpi_stren(vpiStrongDrive);
   wval |= (((((byte) s0val) & 7L) << 5) | ((((byte) s1val) & 7L) << 2));
   sbp[0] = (byte) wval;
  }
 return(xsp);
} 

/*
 * check a 0,1,x,z vpi logic value using vpi .h constants
 */
static int32 chk_vpi_logicval(word32 wval)
{
 if (wval == vpi0 || wval == vpi1 || wval == vpiZ || wval == vpiX)
  return(TRUE);
 return(FALSE);
}

/*
 * PUTV FORCE AND RELEASE ROUTINES
 */

/*
 * vpi_ force of entire register to constant value
 * force of entire reg only overrides possible active reg assign
 * (from statement, no vpi_ assign)
 *
 * SJM 06/19/02 - since vpi forces/assign only constant values never 
 * have dces only unusual part is that qcval may need to be added at run
 * time - no run time dce changes needed
 */
static void reg_vpi_force(struct net_t *np, word32 *ap, word32 *bp)
{
 int32 inum;
 struct qcval_t *assgn_qcp, *frc_qcp;
 char s3[RECLEN], s4[RECLEN];

 strcpy(__wrks1, "");
 /* make sure force qcval allocated */
 if (!np->frc_assgn_allocated)
  {
   /* LOOKATME - since rhs value, any consequences of this at run time */
   /* SJM 12/23/02 - in src needed even when added from PLI */
   np->frc_assgn_allocated = TRUE;
   if (np->nu2.qcval == NULL) __alloc_qcval(np);
  }
 inum = get_inum_();
 frc_qcp = &(np->nu2.qcval[2*inum]);
 assgn_qcp = &(np->nu2.qcval[2*inum + 1]);
 /* case 1, vpi_ force pending - must replace with new vpi form force */
 if (frc_qcp->qc_active)
  { 
   frc_qcp->qcstp = NULL;
   frc_qcp->qcrhsbi = -1;
   frc_qcp->qclhsbi = -1;
   frc_qcp->lhsidp = NULL;
   strcat(__wrks1, " replace force");
  }
 /* if qc assign pending (both not possible), mark inactive but leave */
 /* body so can be reactivated on release */
 else if (assgn_qcp->qc_active)
  {
   assgn_qcp->qc_active = FALSE;
   strcat(__wrks1, " override assign");
  }
 else
  {
   /* LOOKATME - could avoid setting these since never used */
   frc_qcp->qcstp = NULL;
   frc_qcp->qcrhsbi = -1;
   frc_qcp->qclhsbi = -1;
   frc_qcp->lhsidp = NULL;
  }
 /* AIV 03/09/05 - inactive force was F must be T */
 frc_qcp->qc_active = TRUE;
 if (__debug_flg && __ev_tracing)
  {
   __tr_msg(":: vpi_put_value%s force of reg %s to %s in %s now %s\n",
    __wrks1, np->nsym->synam, __regab_tostr(s3, ap, bp, np->nwid, BHEX, FALSE),
    __msg2_cur_blditree(s4), __to_timstr(__wrks2, &__simtime));
  }
 __chg_st_val(np, ap, bp);
 /* notice can have both many wire specific and many all cbs */
 if (__num_vpi_force_cbs > 0) __find_call_force_cbs(np, -1);
 if (__vpi_force_cb_always) __cb_all_rfs(np, -1, TRUE);
}

/*
 * implment vpi do release (caller handles getting value from original handle)
 * releasing reg with pending active assign re-establishes assign
 */
static void reg_vpi_release(struct net_t *np)
{
 int32 inum;
 struct qcval_t *assgn_qcp, *frc_qcp;
 char s3[RECLEN];

 strcpy(__wrks1, "");
 /* SJM 12/23/02 - logic was wrong if never allocated */
 /* if no force in src or added by PLI, nothing to do */
 inum = get_inum_();
 if (np->frc_assgn_allocated) frc_qcp = &(np->nu2.qcval[2*inum]);
 else frc_qcp = NULL;

 if (frc_qcp == NULL || !frc_qcp->qc_active)
  {
   __vpi_err(2101, vpiNotice,
   "attempted vpi_put_value release of reg %s in %s failed - never forced",
    np->nsym->synam, __msg2_cur_blditree(__wrks2));
   goto done;
  }
 frc_qcp->qc_active = FALSE; 
 __force_active = FALSE;

 /* if pending assign from statement - must reactivate it */
 assgn_qcp = &(np->nu2.qcval[2*inum + 1]);
 if (assgn_qcp->qc_active)
  {
   /* do store and build dces in ref. itree loc. */ 
   /* this has assoc. stmt since assign only from Verilog statement */
   __do_qc_store(np, assgn_qcp, TRUE);
   __assign_active = TRUE;
   strcpy(__wrks1, " reactivating assign");
  }
 if (__debug_flg && __ev_tracing)
  {
   __tr_msg(":: vpi_put_value%s release of reg %s in %s now %s\n", __wrks1,
    np->nsym->synam, __msg2_cur_blditree(s3),
    __to_timstr(__wrks2, &__simtime));
  }
 /* notice can have both many wire specific and many all cbs */
done:
 if (__num_vpi_rel_cbs > 0) __find_call_rel_cbs(np, -1);
 if (__vpi_rel_cb_always) __cb_all_rfs(np, -1, FALSE);
}

/*
 * wire force is bit by bit unless vectored wire (when only entire wire)
 *
 * force which is for debugging overrides any wire delay assign
 * when wire change happens (wire event process) if force active, no assign
 */
static void wire_vpi_force(struct net_t *np, word32 *ap, word32 *bp, int32 ndx)
{
 int32 bi, ibase, inum;
 char s3[RECLEN]; 
 
 /* make sure assign/force table exists */ 
 if (!np->frc_assgn_allocated) __alloc_qcval(np);

 if (__debug_flg && __ev_tracing)
  {
   if (ndx == -1) strcpy(__wrks1, np->nsym->synam);
   else sprintf(__wrks1, "%s[%d]", np->nsym->synam,
    __unnormalize_ndx(np, ndx));
   __tr_msg(":: vpi_put_value force of wire %s in %s now %s\n", __wrks1,
    __msg2_cur_blditree(__wrks2), __to_timstr(s3, &__simtime));
  }

 inum = get_inum_();
 ibase = inum*np->nwid;
 if (!np->n_isavec)
  {
   /* SJM 11/14/00 - must also check cbs for scalar case */
   __bit1_vpi_or_tran_wireforce(np, ap, bp, ibase, 0, 0, "vpi_put_value");
   ndx = -1;
   goto chk_cbs;
  }

 /* for vpi only 2 cases: one bit or entire wire */
 if (ndx == -1)
  {
   /* ?? LOOKATME - this was low to high */
   for (bi = np->nwid - 1; bi >= 0; bi--)
    {
     __bit1_vpi_or_tran_wireforce(np, ap, bp, ibase, bi, bi,
      "vpi_put_value");
    }
   ndx = -1;
  }
 else __bit1_vpi_or_tran_wireforce(np, ap, bp, ibase, ndx, 0, "vpi_put_value");

chk_cbs:
 /* notice can have both many wire specific and many all cbs */
 if (__num_vpi_force_cbs > 0) __find_call_force_cbs(np, ndx);
 if (__vpi_force_cb_always) __cb_all_rfs(np, ndx, TRUE);
}

/*
 * do 1 bit vpi_ or switch channel form net/bit wire force 
 * caller must insure qcval records exist
 *
 * select bit rhsbi from wp and force to value of lhsbi
 * must run in possible lhs xmr itree context
 *
 * 06/19/02 SJM - for new fixed for compilation dce algorithm these
 * same since no dces (vpi no dces because rhs value) and tran because
 * assigning to tran channel is what force is
 */
extern void __bit1_vpi_or_tran_wireforce(struct net_t *np, word32 *ap, word32 *bp,
 int32 ibase, int32 lhsbi, int32 rhsbi, char *msg)
{
 int32 bi;
 byte *sbp;
 struct qcval_t *frc_qcp;
 struct xstk_t *xsp, *xsp2;

 /* even if currently forced indicate force active */
 bi = (lhsbi == -1) ? 0 : lhsbi; 
 frc_qcp = &(np->nu2.qcval[ibase + bi]);
 frc_qcp->qc_active = TRUE;

 /* get the 1 bit onto stack */
 push_xstk_(xsp, 1);
 if (rhsbi != 0) 
  {
   xsp->ap[0] = rhsbsel_(ap, rhsbi);
   xsp->bp[0] = rhsbsel_(bp, rhsbi);
  }
 else { xsp->ap[0] = ap[0] & 1L; xsp->bp[0] = bp[0] & 1L; }

 /* emit debug tracing message if needed */
 if (__debug_flg && __ev_tracing)
  {
   if (lhsbi == -1) strcpy(__wrks1, ""); else sprintf(__wrks1, "[%d]", lhsbi);
   __tr_msg("   %s force of %s into wire %s%s\n", msg,
    __regab_tostr(__wrks2, xsp->ap, xsp->bp, 1, BHEX, FALSE),
    np->nsym->synam, __wrks1);
  }

 /* quasi-continuous assign to strength wire always strong */
 if (np->n_stren)
  {
   push_xstk_(xsp2, 4);
   sbp = (byte *) xsp2->ap;
   __st_standval(sbp, xsp, ST_STRVAL);
   if (np->n_isavec) __chg_st_bit(np, lhsbi, (word32) sbp[0], 0L); 
   else __chg_st_val(np, (word32 *) sbp, (word32 *) sbp);
   __pop_xstk();
  }
 else 
  {
   if (np->n_isavec) __chg_st_bit(np, lhsbi, xsp->ap[0], xsp->bp[0]); 
   else __chg_st_val(np, xsp->ap, xsp->bp);
  }
 __pop_xstk();
}

/*
 * after possible concat unwinding, exec the wire section release
 *
 * tricky part is need to force evaluation and store of all drivers
 *
 * LOOKATME - is there any reason can not just call multi driver eval
 * even for 1 or no driver case 
 * LOOKATME - calling release vpi_ callbacks even if not forced 
 */
static void wire_vpi_release(struct net_t *np, int32 ndx)
{
 int32 bi, ibase;
 int32 biti, bitj, all_forced, none_forced, inum;
 struct qcval_t *frc_qcp;
 char s3[RECLEN];
 
 if (!np->frc_assgn_allocated) 
  {
   strcpy(__wrks1, " - no bits ever forced");
no_force: 
   if (ndx == -1) strcpy(__wrks2, np->nsym->synam);  
   else sprintf(__wrks2, "%s[%d]", np->nsym->synam, __unnormalize_ndx(np, ndx));
   __vpi_err(2102, vpiNotice,
    "attempted vpi_put_value release of wire %s in %s failed%s", __wrks2,
    __msg2_cur_blditree(s3), __wrks1);
   goto done;
  }

 if (__debug_flg && __ev_tracing)
  {
   if (ndx == -1) strcpy(__wrks2, np->nsym->synam);  
   else sprintf(__wrks2, "%s[%d]", np->nsym->synam, __unnormalize_ndx(np, ndx));
   __tr_msg(":: vpi_put_value release of wire %s in %s now %s\n", __wrks2,
    __msg2_cur_blditree(__wrks1), __to_timstr(s3, &__simtime));
  }

 /* possible for no active forces but still must check every bit */
 inum = get_inum_();
 ibase = inum*np->nwid;
 all_forced = TRUE;
 /* SJM 12/23/02 - must exec if frc qcp allocated but maybe none forced */
 none_forced = TRUE;
 if (ndx == -1) { biti = np->nwid - 1; bitj = 0; } else biti = bitj = ndx;
 for (bi = biti; bi >= bitj; bi--)
  {
   frc_qcp = &(np->nu2.qcval[ibase + bi]);
   if (!frc_qcp->qc_active) { all_forced = FALSE; continue; }
   /* notice this also turns off non vpi forces */  
   frc_qcp->qc_active = FALSE;
   none_forced = FALSE;
  }
 
 if (none_forced)
  {
   strcpy(__wrks1, " - no bits currently forced");
   goto done;
  }
 /* release is immedate assign even if wire has delay no schedule */
 __assign_1mdrwire(np);
 if (!all_forced && ndx == -1)
  { strcpy(__wrks1, " - some bits forced"); goto no_force; } 

done:
 /* notice can have both many wire specific and many all cbs */
 if (__num_vpi_rel_cbs > 0) __find_call_rel_cbs(np, ndx);
 if (__vpi_rel_cb_always) __cb_all_rfs(np, ndx, FALSE);
}

/*
 * IMMEDIATE PUTV ASSIGN ROUTINES
 */

/*
 * set return value for current user task or function only
 * must be called from current system function or error
 * this pushes and pops itree loc. from handle
 */
static void set_vpisfcall_retval(struct h_t *hp, p_vpi_value value_p)
{
 int32 sf_ind;
 p_vpi_systf_data tfdatp;
 struct sysfunc_t *sfbp;
 struct systftab_t *sfp;
 struct xstk_t *xsp;
 char s1[RECLEN];
 decl_idp_locals_;

 /* --- DBG remove --- */
 if (hp->hrec->hu.hxp == NULL) __vpi_terr(__FILE__, __LINE__);
 /* --- */
 if (hp->hrec->hu.hxp != __cur_sysf_expr)
  {
   if (__cur_sysf_expr == NULL)
    {
     sf_ind = __cur_sysf_expr->lu.x->lu.sy->el.esyftbp->syfnum;
     sf_ind -= (__last_veriusertf + 1); 
     sfp = &(__systftab[sf_ind]);
     tfdatp = (p_vpi_systf_data) sfp->vpi_sytfdat;
     strcpy(s1, tfdatp->tfname);   
    }
   else strcpy(s1, "**none called**");

   __vpi_err(1876, vpiError,
    "vpi_put_value of vpiSysFuncCall %s (return value) illegal - must use from calltf cb", 
    s1);
   return; 
  }

 sf_ind = __cur_sysf_expr->lu.x->lu.sy->el.esyftbp->syfnum;
 sf_ind -= (__last_veriusertf + 1); 
 sfp = &(__systftab[sf_ind]);
 tfdatp = (p_vpi_systf_data) sfp->vpi_sytfdat;
 sfbp = sfp->sfu.sfbp;
 set_save_idp_(hp->hin_idp);
 /* if error do not change global xsp */ 
 xsp = push_vpi_valuep(value_p, sfbp->retwid, sfbp->retntyp, FALSE);
 restore_idp_();
 if (xsp == NULL) return;
 if (__cur_sysf_xsp->xslen != xsp->xslen) __vpi_terr(__FILE__, __LINE__);
 cp_walign_(__cur_sysf_xsp->ap, xsp->ap, xsp->xslen);
 cp_walign_(__cur_sysf_xsp->bp, xsp->bp, xsp->xslen);
 __pop_xstk();
}

/*
 * set either a def or specparam value - always per inst
 * not used for global params
 *
 * probably changes from PNUM to PISNUM rep
 * this never changes original param width and type (maybe real) so value
 * is converted to already determined type 
 * user must define wide enough in source if used for delay annotation
 * or probably truncated with delay loss
 *
 * this pushes and pops itree loc. from handle
 */
static void set_vpiparam_val(struct h_t *hp, p_vpi_value value_p)
{
 int32 wlen, inum;
 word32 *wp;
 struct net_t *np;
 struct xstk_t *xsp;
 struct mod_t *mdp;
 struct itree_t *itp;
 decl_idp_locals_;

 np = hp->hrec->hu.hnp;

 set_save_idp_(hp->hin_idp);
 itp = (struct itree_t *) hp->hin_idp[MD_ITP];
 mdp = itp->itip->imsym->el.emdp;
 /* DBG remove --- */ 
 if (!np->n_isaparam) __arg_terr(__FILE__, __LINE__);
 /* --- */
 /* if error nil, know xsp right width and type (i.e. maybe real) */ 
 xsp = push_vpi_valuep(value_p, np->nwid, np->ntyp, FALSE);
 if (xsp == NULL) goto done;

 /* DBG remove --- */
 if (np->nwid != xsp->xslen) __misc_terr(__FILE__, __LINE__);
 /* --- */

 /* change range rep to IS if needed */
 if (np->srep == SR_PNUM && mdp->flatinum > 1) __chg_param_tois(np, mdp);
 wlen = wlen_(np->nwid);
 inum = get_inum_();
 wp = &(np->prm_nva.wp[2*wlen*inum]);
 memcpy(wp, xsp->ap, 2*WRDBYTES*wlen);
 __pop_xstk();
 /* final step is to re-compute (and prep) all delays param effects */
 /* if called after delay elaboration, param net pin d.s. will be nil */
 __re_prep_dels(np, itp, mdp, TRUE);

done:
 restore_idp_();
}


/*
 * set a vpi udp definition initial value
 * this pushes and pops itree loc. from handle
 *
 * this is per udp type
 * LOOKATME - LRM implies assign to vpiUdp primitive (i.e. per inst.)
 * this must be wrong
 */
static void set_vpiudpdef_ival(struct h_t *hp, p_vpi_value value_p)
{
 word32 nival;
 struct udp_t *udpp;
 struct xstk_t *xsp;

 udpp = hp->hrec->hu.hudpp;
 /* if error nil, know xsp right width and type (i.e. maybe real) */ 
 xsp = push_vpi_valuep(value_p, 1, N_REG, FALSE);
 if (xsp == NULL) return;

 nival = xsp->ap[0] & ((xsp->bp[0] & 1L) << 1);
 __pop_xstk();
 if (nival == 2)
  {
   __vpi_err(1871, vpiError,
    "vpi_put_value of vpiUdpDefn initial value 1'bz illegal - value not changed");
   return;
  }
 udpp->ival = nival;
}

/*
 * immediate assign to vpi_ wire driver handle from value_p 
 * assign one bit using npp's index
 *
 * this is entire net for immediate no delay case only but can be 1 bit scalar
 * know if net is strength ap will be sbp (push converts to stren if needed)
 */
static void immed_vpi_drv_assign(struct net_t *np, int32 di, word32 *ap, word32 *bp)
{
 byte *sbp, *sbp2;
 struct vpi_drv_t *vpidrvp;     
 int32 inum;

 /* immedate assign to wire driver (handle is ptr to npp) */
 vpidrvp = np->vpi_ndrvs[di]; 
 /* update driver - for vpi_ strength always 1 bit (use low bit) */
 if (np->n_stren) 
  {
   sbp = (byte *) ap;
   inum = get_inum_();
   sbp2 = &(vpidrvp->vpi_drvwp.bp[inum*np->nwid]);
   sbp2[0] = sbp[0]; 
  }
 /* assign entire vector */
 else __st_perinst_val(vpidrvp->vpi_drvwp, np->nwid, ap, bp);

 /* do fi>1 wire assign */
 /* handle fi>1 eval and store of bits - maybe in tran channel */
 /* LOOKATME - because of 1 bit only drivers this is inefficient because */
 /* muste re-eval all drivers of entire net */
 if (np->ntraux != NULL)
  {
   /* if hard drivers of np do not change, channel cannot change */
   /* SJM 12/18/00 - for tran/tranif switch channels may just add to list */
   if (__update_tran_harddrvs(np)) __eval_tran_bits(np);
  }
 else
  {
   if (np->nrngrep == NX_DWIR) __sched_1mdrwire(np);
   else __assign_1mdrwire(np);
  }
}

/*
 * immediate assign to vpi_ wire bit driver handle from value_p 
 *
 * this is for vpi Net Bit Driver so can never be -1 (no bit for scalar)
 */
static void immed_vpibit_drv_assign(struct net_t *np, int32 di, int32 bi,
 word32 *ap, word32 *bp)
{
 byte *sbp, *sbp2;
 struct vpi_drv_t *vpidrvp;     
 struct xstk_t *xsp;
 int32 inum;

 vpidrvp = np->vpi_ndrvs[di]; 
 /* DBG remove --- */
 if (bi == -1) __vpi_terr(__FILE__, __LINE__);
 /* --- */
 /* update driver - for vpi_ strength always 1 bit (use low big) */
 if (np->n_stren) 
  {
   sbp = (byte *) ap;
   inum = get_inum_();
   sbp2 = &(vpidrvp->vpi_drvwp.bp[inum*np->nwid + bi]);
   sbp2[0] = sbp[0]; 
  }
 /* low bit into 1 bit per inst. vector */
 else
  {
   push_xstk_(xsp, np->nwid);
   __ld_perinst_val(xsp->ap, xsp->bp, vpidrvp->vpi_drvwp, np->nwid);
   __lhsbsel(xsp->ap, bi, ap[0]);
   __lhsbsel(xsp->bp, bi, bp[0]);
   __st_perinst_val(vpidrvp->vpi_drvwp, np->nwid, xsp->ap, xsp->bp);
   __pop_xstk();
  }
 /* do fi>1 wire assign */
 /* handle fi>1 eval and store of bits - maybe in tran channel */
 /* LOOKATME - because of 1 bit only drivers this is inefficient because */
 /* muste re-eval all drivers of entire net */
 if (np->ntraux != NULL)
  {
   /* if hard drivers of np do not change, channel cannot change */
   /* SJM 12/18/00 - for tran/tranif switch channels may just add to list */
   if (__update_tran_harddrvs(np)) __eval_tran_bits(np);
  }
 else
  {
   if (np->nrngrep == NX_DWIR) __sched_1mdrwire(np);
   else __assign_1mdrwire(np);
  }
}

/*
 * VPI EVENT PROCESSING ROUTINES
 */

/*
 * process a vpi put value handle assign event
 *
 * for regs (also variables) array words, and variable bits
 * and wires (here softforce is used)
 *
 * assigning either entire reg or reg bit but only one pending event allowed
 *
 * SJM 07/22/00 - although originally for regs also used for soft force
 * of wire
 * SJM 11/14/00 - now wire soft force is more like wire force except no 
 * release
 */
extern void __process_vpi_varputv_ev(void)
{
 int32 wlen, inum;
 word32 *ap, *bp;
 struct net_t *np;
 struct dltevlst_t *dlp;
 struct h_t *hp;
 struct tev_t *tevp;
 struct teputv_t *tepvp;

 tevp = __cur_tevp;
 tepvp = tevp->tu.teputvp;
 tevp->tu.teputvp = NULL;

 np = tepvp->np;
 if (__ev_tracing) emit_vpiputv_evtrmsg(np, tepvp, tepvp->nbi);

 /* if putv scheduled event saved, turn on event happened flag in handle */
 /* because since user has handle later incorrect cancel might be tried */
 /* for registers only only event per inst allowed (i.e lhs bsel or assign) */
 if ((hp = tepvp->evnt_hp) != NULL) hp->hrec->evnt_done = TRUE;
 /* do the proc. assign, or driver change and fi>1 eval */
 wlen = wlen_(np->nwid);
 ap = tepvp->putv_wp;
 bp = &(ap[wlen]);

 if (np->ntyp < NONWIRE_ST)
  {
   /* following acc_ routines, no delay set ignored any pending assigns */ 
   /* SJM 11/14/00 - for soft force of in tran chan (inout), now soft */
   /* all wires in tran chan */ 
   /* SJM 03/15/01 - can't force all of tran channel - just soft force */
   /* this tran wire and re-eval tran channel */
   if (np->ntraux != NULL)
    {
      __tran_exec_putv_wire_softforce(np, ap, bp, tepvp->nbi);
      __eval_tran_1bit(np, tepvp->nbi);
     }
   else exec_putv_wire_softforce(np, ap, bp, tepvp->nbi);
  }
 /* reg assign event */
 else exec_putv_reg_assign(np, ap, bp, tepvp->nbi);

 /* free the the reg putv event auxiliary record - never strength*/ 
 __my_free(ap, 2*wlen*WRDBYTES);
 inum = get_inum_();
 dlp = np->regwir_putv_tedlst[inum];
 np->regwir_putv_tedlst[inum] = dlp->terp;

 /* link on putv event contents record free list */
 tepvp->np = (struct net_t *) __teputvfreelst;
 __teputvfreelst = tepvp;

 /* also link out dltevlst element - must be on front */
 /* DBGMAYBELEAVE */
 if (dlp == NULL || tevp != dlp->tevp) __vpi_terr(__FILE__, __LINE__);
 /* --- */
 dlp->telp = NULL;
 /* put this telst elemnt on free list */
 dlp->terp = __dltevfreelst;
 __dltevfreelst = dlp;
}

/*
 * emit a delayed scheduled vpi put_value trace message 
 *
 * handled both reg proc. assign and driver assign of added vpi wire drvr
 */
static void emit_vpiputv_evtrmsg(struct net_t *np, struct teputv_t *tepvp,
 int32 nbi)
{ 
 int32 wid;
 word32 *ap, *bp;
 byte *sbp;
 char ts1[RECLEN], ts2[IDLEN], ts3[RECLEN], ts4[RECLEN];

 if (np->n_isarr)
  {
   sprintf(ts3, "array word32 %s[%d]", np->nsym->synam,
    __unnormalize_ndx(np, nbi));
   wid = np->nwid;
  }
 else if (nbi != -1) 
  {
   sprintf(ts3, "%s %s[%d]", __to_wtnam(ts1, np), np->nsym->synam,
    __unnormalize_ndx(np, nbi));
   wid = 1;
  }
 else
  {
   sprintf(ts3, "%s %s", __to_wtnam(ts1, np), np->nsym->synam);
   wid = np->nwid;
  }
 if (np->ntyp >= NONWIRE_ST)
  {
   strcpy(ts1, "procedural");
   /* DBG remove --- */
   if (np->regwir_putv_tedlst == NULL) __vpi_terr(__FILE__, __LINE__);
   /* --- */
  }
 else
  {
   if (np->ntraux) strcpy(ts1, "vpi_ inout or tran channel driver"); 
   else if (np->n_multfi) strcpy(ts1, "vpi_ wire driver");
   /* SJM  11/25/0 - tracing also for soft force to wire - so fi==1 ok */
   /* and must leave wid as is */
   else strcpy(ts1, "wire");
  }

 /* strength must be driver - other can be one bit or reg width */
 if (np->n_stren)
  { sbp = (byte *) tepvp->putv_wp; __st_regab_tostr(ts2, sbp, 1); }
 else
  { 
   ap = tepvp->putv_wp;
   bp = &(ap[wlen_(wid)]);
   __regab_tostr(ts2, ap, bp, wid, BHEX, FALSE);
  }
 __evtr_resume_msg();
 __tr_msg("== processing vpi_put_value %s event in %s value %s\n",
  ts3, __msg2_cur_blditree(ts4), ts2);
} 

/*
 * exec a vpi put value assign to reg - no delay or event processing
 */
static void exec_putv_reg_assign(struct net_t *np, word32 *ap, word32 *bp,
 int32 ndx)
{
 int32 arrwid, bi, inum;
 
 /* case 1: array */
 if (np->n_isarr)
  {
   /* array never forced or assigned */ 
   arrwid = __get_arrwide(np);
   if (np->nchg_nd_chgstore)
    {
     __chg_st_arr_val(np, NULL, ndx, ap, bp);
     if (__lhs_changed) record_sel_nchg_(np, ndx, ndx);
    }
   else __st_arr_val(np, NULL, ndx, ap, bp, np->nwid);
   return;
  }
 /* case 2: entire reg */
 inum = get_inum_();
 if (ndx == -1)
  {
   /* AIV 07/12/07 - BEWARE local inum now is used in reg_fr_inhibit_ macro */
   if (np->nu2.qcval != NULL && reg_fr_inhibit_(np)) return; 
   if (np->nchg_nd_chgstore) __chg_st_val(np, ap, bp);
   else __st_val(np, ap, bp, np->nwid);
   return;
  }
 /* case 3: reg bit select - if active force, no assign */
 /* know ndx never -1 here */
 bi = (ndx == -1) ? 0 : ndx;
 if (!np->frc_assgn_allocated
  || !np->nu2.qcval[np->nwid*inum + bi].qc_active)
  {
   /* SJM - 07/24/00 - now do not use chg st bit unless needed */
   if (np->nchg_nd_chgstore) __chg_st_bit(np, ndx, ap[0], bp[0]);
   else __st_bit(np, ndx, ap[0], bp[0]); 
  }
}

/*
 * exec a vpi tput value soft force procedural style assign to reg
 * no delay or event processing (may be called from delay assign ev handler)
 */
static void exec_putv_wire_softforce(struct net_t *np, word32 *ap, word32 *bp,
 int32 ndx)
{
 int32 inum;

 /* case 1: entire wire */
 if (ndx == -1)
  {
   /* this add the changed wire to nchglst if needed */
   if (np->nu2.qcval != NULL)
    {
     /* return F if all of wire forced, nothing to do */ 
     /* if T, this will correct bits in ap and bp so actual assign is right */
     if (!__correct_forced_newwireval(np, ap, bp)) return;
    }
   if (np->nchg_nd_chgstore) __chg_st_val(np, ap, bp);
   else __st_val(np, ap, bp, np->nwid);
   return;
  }
 /* case 2: wire bit select */
 /* if the 1 bit is forced nothing to do */
 /* know ndx never -1 since -1 case handled above */
 inum = get_inum_();
 if (np->frc_assgn_allocated
  && np->nu2.qcval[np->nwid*inum + ndx].qc_active) return;

 /* else simple bit assign */
 /* SJM 03/15/01 - change to fields in net record */
 if (np->nchg_nd_chgstore) __chg_st_bit(np, ndx, ap[0], bp[0]);
 else __st_bit(np, ndx, ap[0], bp[0]); 
}

/*
 * process a vpi driver put value assign event
 *
 * for scheduled (delayed) assigns to drivers of wires (like contas)
 *
 * know a/b value always 1 bit and type known and called from ev itree loc 
 * for added entire vectored wire driver each bit still has separate event
 */
extern void __process_vpidrv_ev(void)
{
 int32 ndx, evi, inum;
 word32 *ap, *bp;
 struct net_t *np;
 struct dltevlst_t *dlp;
 struct tev_t *tevp;
 struct teputv_t *tepvp;
 struct tev_t **evtabp; 
 struct h_t *hp;
 struct hrec_t *hrp;

 tevp = __cur_tevp;
 tepvp = tevp->tu.teputvp;
 tevp->tu.teputvp = NULL;

 np = tepvp->np;
 if (__ev_tracing) emit_vpiputv_evtrmsg(np, tepvp, tepvp->nbi);

 /* if putv scheduled event saved, turn on event happened flag in handle */
 /* because since user has handle later incorrect cancel might be tried */
 /* also at end of time slot canceled tev will be reused */ 
 if ((hp = tepvp->evnt_hp) != NULL)
  {
   hrp = hp->hrec;
   if (hrp->bith_ndx)
    {
     /* here hp is master entire vector scheduled object */
     evtabp = hrp->hu.hevrec->evndxtab;
     evtabp[tepvp->nbi] = NULL;
    }
   else hrp->evnt_done = TRUE;
  }
 /* do the proc. assign, or driver change and fi>1 eval */
 ap = tepvp->putv_wp;
 /* for scalar bit is 0 for right index - else the vector's index */
 if (np->n_stren) bp = ap; else bp = &(ap[1]);
 if (tepvp->nbi == -1)
  {
   immed_vpi_drv_assign(np, tepvp->di, ap, bp);
   ndx = 0;
  }
 else
  {
   ndx = tepvp->nbi;
   immed_vpibit_drv_assign(np, tepvp->di, ndx, ap, bp);
  }

 /* free the the driver putv event auxiliary record */ 
 __my_free(ap, 2*WRDBYTES);
 /* excise out first being processed event */
 inum = get_inum_();
 evi = np->nwid*inum + ndx;
 dlp = np->vpi_ndrvs[tepvp->di]->putv_drv_tedlst[evi];
 np->vpi_ndrvs[tepvp->di]->putv_drv_tedlst[evi] = dlp->terp;

 /* link on putv event contents record free list */
 tepvp->np = (struct net_t *) __teputvfreelst;
 __teputvfreelst = tepvp;

 /* also link out dltevlst element - must be on front */
 /* DBGMAYBELEAVE */
 if (dlp == NULL || tevp != dlp->tevp) __vpi_terr(__FILE__, __LINE__);
 /* --- */
 dlp->telp = NULL;
 /* put this telst elemnt on free list */
 dlp->terp = __dltevfreelst;
 __dltevfreelst = dlp;
}

/*
 * convert a passed delay time to internal ticks
 */
extern int32 __vpitime_to_ticks(word64 *timp, p_vpi_time time_p,
 struct mod_t *mdp) 
{
 word64 tim;

 if (time_p->type == vpiScaledRealTime)
  {
   if (!__real_to_v64tim(&tim, time_p->real))
    {
     __vpi_err(1926, vpiError,
      "vpiTimeVal type vpiScaledRealTime too large for 64 bit time - not converted");
     *timp = 0ULL;
     return(FALSE);
    }
   if (mdp != NULL && !mdp->mno_unitcnv) cnv_num64to_ticks_(*timp, tim, mdp);
   else *timp = tim;
  }
 else
  {
   if (time_p->type != vpiSimTime)
    {
     __vpi_err(2018, vpiWarning,
      "vpiTimeVal of type vpiSuppressTime meaningless here - using vpiSimTime");
    }
   /* sim time is internal ticks (lowest time precision in design) */
   /* SJM 02/03/00 since PLI time values int32 not word32 cast make 64 */
   /* bits of 1 for -1 not word32 32 bits value as needed */
   *timp = ((word64) ((word32) (time_p->low)))
     | (((word64) ((word32) time_p->high)) << 32);
  }
 return(TRUE);
}

/*
 * PUTV DELAY SCHEDULING ROUTINES
 */

/*
 * implement delayed assign (usually scheduled) of value_p value to reg var
 * or bit select of reg var or soft force of wire or wire bit  
 *
 * inertial replaces pending sched ev with later and removes earlier 
 * but documentation says something else
 *
 * only for delays - * must run in itree loc. of handle 
 *
 * SJM 07/25/00 - this routine used also for soft force to nets and net bits
 *                exactly same algorithm
 *
 * no driving values stored for registers or nets
 * LOOKATME - does this work with strengths - think so
 */
static struct h_t *setschd_var_fromvaluep(p_vpi_value value_p,
 struct net_t *np, int32 ndx, word64 ticksdel, byte dtyp, int32 ret_event)
{ 
 int32 wlen, ewid, inum;
 word64 schtim;
 struct dltevlst_t *dlp, *dlp2, *ins_after_dlp;
 struct tev_t *tevp;
 struct xstk_t *xsp;
 struct teputv_t *tepvp;
 struct h_t *hp;

 /* AIV 04/21/10 - this was wrong width for an array element */
 /* was assuming no index or bsel - need to check for array as well */
 if (ndx == -1 || np->n_isarr) ewid = np->nwid; 
 else ewid = 1;

 /* this can be strength if soft force to wire */
 if ((xsp = push_vpi_valuep(value_p, ewid, np->ntyp, np->n_stren)) == NULL)
  return(NULL);

 /* allocate per inst but not per bit pending event list if needed */ 
 /* SJM 07/24/00 - net putv tedlst also used for soft force of wires */
 if (np->regwir_putv_tedlst == NULL) bld_regwir_putvrec(np);

 schtim = __simtime + ticksdel;
 inum = get_inum_();
 if (__ev_tracing) 
  {
   char s1[RECLEN]; 

   dlp = np->regwir_putv_tedlst[inum];
   if (np->ntyp >= NONWIRE_ST) strcpy(s1, "reg");
   else strcpy(s1, "wire soft force");
   emit_vpiputv_schd_trmsg(np, xsp, dlp, &schtim, dtyp, "reg");
  }

 ins_after_dlp = NULL;
 /* eliminate new and/or cancel any olds */
 if ((dlp = np->regwir_putv_tedlst[inum]) != NULL)
  {
   /* case 1: inertial - remove all but one latest - return if no effect */
   /* inertial follows Verilog normal convention - keep only latest */
   /* and eliminate any earlier */
   if (dtyp == vpiInertialDelay)
    {
     /* start by removing all of list but last (if needed) - know >= 2 */
     if (dlp->terp != NULL)
      {
       dlp2 = __spliceout_last(dlp);
       cancel_vpievents_toend(np, dlp, ewid);
       dlp = dlp2;
       np->regwir_putv_tedlst[inum] = dlp;
       dlp->telp = NULL;
      }
     /* by here list has exactly one element (last) */
     /* if new one earlier - do not schedule, same time, use new */
     tevp = dlp->tevp;
     if (tevp->etime > schtim) { __pop_xstk(); return(NULL); }

     /* know new event time is later - cancel all of one element list */
     cancel_vpievents_toend(np, dlp, ewid);
     np->regwir_putv_tedlst[inum] = NULL;
     ins_after_dlp = NULL;
     goto bld_tev;
    }
   /* case 2: modified transport - remove all delays >= than new */
   /* notice if same time delays must leave and insert this after all */
   /* currently scheduled for this time */
   if (dtyp == vpiTransportDelay)
    {
     /* SJM 09/05/99 - think elmination when scheduled wrong */
     /* nothing to remove, just put on end of active pnd0 queue */
     /* SJM - if (schtim == 0ULL) goto bld_tev; WRONG */
     /* AIV 03/09/05 - for 0 delay schedule time will not be 0 */
     if (ticksdel == 0ULL) goto bld_tev;

     /* know delay list in time order */
     /* dlp2 is one before first after (maybe last), nil is before all */ 
     if ((dlp2 = __find_last_bdltevp(dlp, schtim)) == NULL) 
      { 
       /* new delay is before all - empty list */
       dlp2 = np->regwir_putv_tedlst[inum];
       cancel_vpievents_toend(np, dlp2, ewid);
       np->regwir_putv_tedlst[inum] = NULL;
       ins_after_dlp = NULL;
       goto bld_tev; 
      } 
     /* new delay is after all - nothing to remove */
     if (dlp2->terp == NULL) { ins_after_dlp = dlp2; goto bld_tev; } 
     /* new delay is after some and before some */
     ins_after_dlp = dlp2;
     if (dlp2->terp != NULL)  
      { cancel_vpievents_toend(np, dlp2->terp, ewid); dlp2->terp = NULL; }
     goto bld_tev;
    }
   /* DBG remove --- */
   if (dtyp != vpiPureTransportDelay) __vpi_terr(__FILE__, __LINE__);
   /* --- */
   /* pure transport - insert in right place in list */
   /* if new delay is before all - insert at front */
   if ((dlp2 = __find_last_bdltevp(dlp, schtim)) == NULL) 
    { ins_after_dlp = NULL; goto bld_tev; }
   /* if goes after list, end of list returned else place to ins after */
   ins_after_dlp = dlp2; 
  }   

bld_tev:
 /* allocate and schedule event */ 
 alloc_cur_tev_(tevp, __process_vpi_varputv_enterp, schtim);
 /* need to store scheduled driving value in event because can be many */
 if (__teputvfreelst != NULL)
  {
   tepvp = __teputvfreelst;
   __teputvfreelst = (struct teputv_t *) __teputvfreelst->np;
  }
 else tepvp = (struct teputv_t *) __my_malloc(sizeof(struct teputv_t));
 tepvp->nbi = ndx;
 tepvp->np = np;
 /* assume non handle returning mode */
 tepvp->evnt_hp = NULL;
 wlen = wlen_(ewid);
 tepvp->putv_wp = (word32 *) __my_malloc(2*WRDBYTES*wlen);
 memcpy(tepvp->putv_wp, xsp->ap, 2*WRDBYTES*wlen);
 tevp->tu.teputvp = tepvp;
 tevp->vpi_regwir_putv = TRUE;
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
   dlp2 = np->regwir_putv_tedlst[inum];
   dlp->terp = dlp2;
   if (dlp2 != NULL) dlp2->telp = dlp;
   dlp->telp = NULL;
   np->regwir_putv_tedlst[inum] = dlp;
  }
 /* insert after */
 else
  {  
   dlp->terp = ins_after_dlp->terp; 
   if (dlp->terp != NULL) dlp->terp->telp = dlp;
   ins_after_dlp->terp = dlp;
   dlp->telp = ins_after_dlp;
  }
 if (ret_event)
  {
   /* need itree loc. so can get right pending event list */
   /* notice if bith ndx on handle is ev rec (table of tev's) else just ev */
   /* this is 1 bit using tev index not table because bith ndx off */ 
   hp = (struct h_t *) __mk_handle(vpiSchedEvent, (void *) tevp,
    __idp, NULL);
   hp->hrec->evnt_done = FALSE;
   tevp->tu.teputvp->evnt_hp = hp;
   return(hp);
  }
 return(NULL);
}

/*
 * emit a vpi_put_value scheduled assign part
 * 
 * LOOKATME - no tracing currently for immediate assigns 
 */
static void emit_vpiputv_schd_trmsg(struct net_t *np, struct xstk_t *xsp,
 struct dltevlst_t *dlp, word64 *schdtimp, int32 dtyp, char *putvnam)
{
 char ts1[RECLEN], ts2[RECLEN], ts3[RECLEN];

 if (np->n_stren) __st_regab_tostr(ts1, (byte *) xsp->ap, 1);
 else __regab_tostr(ts1, xsp->ap, xsp->bp, np->nwid, BHEX, FALSE);

 __evtr_resume_msg();
 __tr_msg("== schedule %s vpi_put_value to %s (in %s) value %s for %s:\n",
  putvnam, np->nsym->synam, __msg2_cur_blditree(ts2), ts1, 
  __to_timstr(ts3, schdtimp));

 if (dlp != NULL)
  {
   __tr_msg("   <%s update of scheduled events>\n",
    putv_flag_to_str(ts1, dtyp));
  }
 else __tr_msg("   <no scheduled events>\n");
}

/*
 * for first putv to reg allocate and zero per inst. scheduled list 
 * must be called from right (on itstk) itree loc. 
 */
static void bld_regwir_putvrec(struct net_t *np)
{
 int32 nbytes;
 struct mod_t *cur_mdp;

 cur_mdp = get_inst_mod_();
 nbytes = cur_mdp->flatinum*sizeof(struct dltevlst_t *);
 np->regwir_putv_tedlst = (struct dltevlst_t **) __my_malloc(nbytes);
 memset(np->regwir_putv_tedlst, 0, nbytes); 
}

/*
 * reinitialize putvrec for reg or wire by freeing any pending events
 *
 * called when resetting from prep code
 * only called if putvrec non nil
 *
 * SJM 07/25/00 - also putv recs for soft force of regs and wires
 */
extern void __reinit_regwir_putvrec(struct net_t *np, int32 insts)
{
 int32 ii;
 struct dltevlst_t *dlp, *dlp2, *last_dlp;

 for (ii = 0; ii < insts; ii++)
  {
   /* notice events will be in event queue and already freed */ 
   if ((dlp = np->regwir_putv_tedlst[ii]) == NULL) continue;
   last_dlp = NULL;
   for (dlp2 = dlp; dlp2 != NULL; dlp2 = dlp2->terp) last_dlp = dlp2;
   last_dlp->terp = __dltevfreelst; 
   __dltevfreelst = dlp;
  }
}

/*
 * for vpi delayed putv cancel all events starting at passed to end 
 *
 * for change to inertial - free all but last and return last (latest)
 * this list for the one given parameter must be ordered by time
 * caller must set previous next field to nil or nil out list
 * differs from tf_ dputp only in removing either entire wire or bit 
 */
static void cancel_vpievents_toend(struct net_t *np, struct dltevlst_t *frdlp,
 int32 ewid)
{
 struct dltevlst_t *dlp, *last_dlp;
 struct tev_t *tevp;
 struct teputv_t *tepvp;
 struct h_t *hp;
 struct hrec_t *hrp;

 for (last_dlp = NULL, dlp = frdlp; dlp != NULL; dlp = dlp->terp)  
  {
   tevp = dlp->tevp;
   /* need to leave event, gets processed as cancelled and freed en masse */  
   tevp->enterptr = __process_cancel_ev_enterp;
   tepvp = tevp->tu.teputvp;
   /* tricky part for tab form vector driver must fix table ptr */
   if ((hp = tepvp->evnt_hp) != NULL)
    {
     hrp = hp->hrec;
     if (hrp->bith_ndx)
      {   
       struct tev_t **evtabp;

       /* DBG remove --- */
       if (np->nwid < 2) __vpi_terr(__FILE__, __LINE__);
       if (hrp->htyp != vpiSchedEvent) __vpi_terr(__FILE__, __LINE__);
       /* --- */
       /* only mark event done for non vectored entire wire schd. */ 
       evtabp = hrp->hu.hevrec->evndxtab;
       evtabp[tepvp->nbi] = NULL;
       /* LOOKATME - could check entire table and mark event done here */
      }
     else hrp->evnt_done = TRUE; 
    }

   /* free the value since te cancel implies guts never freed */
   __my_free(tepvp->putv_wp, 2*wlen_(ewid)*WRDBYTES);

   /* free tevputv by linking on free list */
   tepvp->np = (struct net_t *) __teputvfreelst;
   __teputvfreelst = tepvp;
   last_dlp = dlp;
  }
 /* finally link all of dltevlst onto free list */
 /* SJM 08/02/01 - add if to keep lint happy */
 if (last_dlp != NULL) last_dlp->terp = __dltevfreelst; 
 __dltevfreelst = frdlp;
}

/*
 * delayed schedule of wire driver either scalar, bit, or entire vector
 *
 * returns schedule event handle if ret event T else nil
 * handle type either vpi net or net bit driver
 */
static struct h_t *setschd_drvr_fromvaluep(p_vpi_value value_p,
 struct h_t *hp, word64 ticksdel, byte dtyp, int32 ret_event)
{ 
 int32 bi;
 int32 some_sched;
 struct net_t *np;
 struct tev_t *tevp, **evtabp;
 struct h_t *hp2;
 struct net_pin_t *npp;
 struct xstk_t *xsp, *xsp2;
 struct schdev_t *schd_ev;

 npp = hp->hrec->hu.hnpp;
 np = npp->elnpp.enp;
 /* case 1: net bit */
 if (hp->hrec->htyp == vpiNetBitDriver)
  {
   if ((xsp = push_vpi_valuep(value_p, 1, np->ntyp, np->n_stren)) == NULL)
    return(NULL);
   /* DBG remove --- */
   if (!np->n_isavec) __vpi_terr(__FILE__, __LINE__);
   /* --- */
   tevp = setschd_1bit_drvr(npp, npp->npaux->nbi1, xsp, ticksdel, dtyp);

   if (ret_event && tevp != NULL)
    {
     /* need itree loc. so can get right pending event list */
     /* notice if bith ndx on handle is ev rec (table of tev's) else just ev */
     hp2 = (struct h_t *) __mk_handle(vpiSchedBitEvent, (void *) tevp,
      __idp, NULL);
     hp2->hrec->evnt_done = FALSE;
     tevp->tu.teputvp->evnt_hp = hp2;
    }
   else hp2 = NULL; 
   __pop_xstk();
   return(hp2);
  }
 /* case 2: entire net */
 /* case 2a: scalar net */
 if (!np->n_isavec)
  {
   if ((xsp = push_vpi_valuep(value_p, 1, np->ntyp, np->n_stren)) == NULL)
    return(NULL);
   tevp = setschd_1bit_drvr(npp, 0, xsp, ticksdel, dtyp);

   if (ret_event && tevp != NULL)
    {
     /* need itree loc. so can get right pending event list */
     hp2 = (struct h_t *) __mk_handle(vpiSchedEvent, (void *) tevp,
      __idp, NULL);
     hp2->hrec->evnt_done = FALSE;
     /* bith ndx not set indicates not ev tab table */ 
     tevp->tu.teputvp->evnt_hp = hp2;
    }
   else hp2 = NULL; 
   __pop_xstk();
   return(hp2);
  }

 /* case 2b: vector net */
 if ((xsp = push_vpi_valuep(value_p, np->nwid, np->ntyp, np->n_stren))
  == NULL) return(NULL);

 evtabp = (struct tev_t **) __my_malloc(np->nwid*sizeof(struct tev_t *));
 /* ?? LOOKATME - this was low to high */
 for (bi = np->nwid - 1; bi >= 0; bi--) evtabp[bi] = NULL;
 some_sched = FALSE;
 /* for strength vectors just assign to low bit - also warning */
 if (np->n_stren)
  {
   /* BEWARE big endian problem, works providing always pass and cast ptrs */
   /* i.e. can not pass word32 here on suns will get high not low */
   tevp = setschd_1bit_drvr(npp, 0, xsp, ticksdel, dtyp);
   if (tevp != NULL) some_sched = TRUE;
   evtabp[0] = tevp;
  }
 else
  { 
   push_xstk_(xsp2, 1);
   /* ?? LOOKATME - this was low to high */
   for (some_sched = FALSE, bi = np->nwid - 1; bi >= 0; bi--)
    {
     /* this works because if net stren value will be always also be stren */
     /* conversion made in push vpi value if needed */
     /* also know all bits but low are 0 */
     xsp2->ap[0] = rhsbsel_(xsp->ap, bi);
     xsp2->bp[0] = rhsbsel_(xsp->bp, bi);

     /* may return -1 if no event scheduled */
     /* can pass address of stacked words since never strengths */
     tevp = setschd_1bit_drvr(npp, bi, xsp2, ticksdel, dtyp);
     if (tevp != NULL) some_sched = TRUE;
     evtabp[bi] = tevp;
    }
   __pop_xstk();
  }
 __pop_xstk();
 if (ret_event && some_sched)
  {
   /* need itree loc. so can get right pending event list */
   /* notice if bith ndx on handle is ev rec (table of tev's) else just ev */
   schd_ev = (struct schdev_t *) __my_malloc(sizeof(struct schdev_t));
   schd_ev->evnp = np;
   schd_ev->evndxtab = evtabp;
   
   hp2 = (struct h_t *) __mk_handle(vpiSchedEvent, (void *) schd_ev,
    __idp, NULL);
   hp2->hrec->evnt_done = FALSE;
   /* BEWARE - using 2 different form for vpiSched.. object this field */
   /* is used as special case (need evndxtab case) */
   hp2->hrec->bith_ndx = TRUE;
   for (bi = np->nwid - 1; bi >= 0; bi--)
    {
     tevp = evtabp[bi];
     /* SJM 04/20/00 - possible for only some to have events */
     if (tevp != NULL) tevp->tu.teputvp->evnt_hp = hp2;
    }
  }
 else
  {
   __my_free(evtabp, np->nwid*sizeof(struct tev_t *));
   hp2 = NULL; 
  }
 return(hp2);
}

/*
 * implement assign (scheduled) of 1 bit on xstk to 1 wire driver bit 
 * delayed assign to driver for either driver bit or 1 bit of scalar
 * 
 * always returned scheduled event on sucess (caller creates handle if needed)
 * if no event scheduled returns nil (possible inertial not schedule)
 *
 * inertial replaces pending sched ev with later and removes earlier 
 * but documentation says something else
 *
 * only for delays - no delay handled as special case above here
 * must run in itree loc. of handle 
 */
static struct tev_t *setschd_1bit_drvr(struct net_pin_t *npp, int32 bi,
 struct xstk_t *xsp, word64 ticksdel, byte dtyp)
{ 
 int32 evi, inum;
 word64 schtim;
 struct dltevlst_t *dlp, *dlp2, *ins_after_dlp;
 struct tev_t *tevp; 
 struct net_t *np;
 struct vpi_drv_t *vpidrvp;     
 struct teputv_t *tepvp;

 np = npp->elnpp.enp;
 schtim = __simtime + ticksdel;
 ins_after_dlp = NULL;
 vpidrvp = np->vpi_ndrvs[npp->obnum]; 
 /* notice bit index 0 for scalar */ 
 /* table of scheduled events is one list for each net bit per inst. */
 inum = get_inum_();
 evi = np->nwid*inum + bi;

 if (__ev_tracing) 
  {
   char ts1[RECLEN];

   if (np->n_isavec) sprintf(ts1, "bit %d driver", bi);
   else strcpy(ts1, "scalar driver");
   dlp = vpidrvp->putv_drv_tedlst[evi];
   emit_vpiputv_schd_trmsg(np, xsp, dlp, &schtim, (int32) dtyp, ts1);
  }

 /* eliminate new and/or cancel any olds */
 if ((dlp = vpidrvp->putv_drv_tedlst[evi]) != NULL)
  {
   /* case 1: inertial - remove all but one latest - return if no effect */
   /* inertial follows Verilog normal convention - keep only latest */
   /* and eliminate any earlier */
   if (dtyp == vpiInertialDelay)
    {
     /* start by removing all of list but last (if needed) - know >= 2 */
     if (dlp->terp != NULL)
      {
       dlp2 = __spliceout_last(dlp);
       cancel_vpievents_toend(np, dlp, 1);
       dlp = dlp2;
       vpidrvp->putv_drv_tedlst[evi] = dlp;
       dlp->telp = NULL;
      }
     /* by here list has exactly one element (last) */
     /* if new one earlier - do not schedule, same time, use new */
     tevp = dlp->tevp;
     if (tevp->etime > schtim) return(NULL);

     /* know new event time is later - cancel all of one element list */
     cancel_vpievents_toend(np, dlp, 1);
     vpidrvp->putv_drv_tedlst[evi] = NULL;
     ins_after_dlp = NULL;
     goto bld_tev;
    }
   /* case 2: modified transport - remove all delays >= than new */
   /* notice if same time delays must leave and insert this after all */
   /* currently scheduled for this time */
   if (dtyp == vpiTransportDelay)
    {
     /* SJM 09/05/99 - think elmination when scheduled wrong */
     /* nothing to remove, just put on end of active pnd0 queue */
     /* SJM - if (schtim == 0ULL) goto bld_tev; WRONG */

     /* know delay list in time order */
     /* dlp2 is one before first after (maybe last), nil is before all */ 
     if ((dlp2 = __find_last_bdltevp(dlp, schtim)) == NULL) 
      { 
       /* new delay is before all - empty list */
       dlp2 = vpidrvp->putv_drv_tedlst[evi];
       cancel_vpievents_toend(np, dlp2, 1);
       vpidrvp->putv_drv_tedlst[evi] = NULL;
       ins_after_dlp = NULL;
       goto bld_tev; 
      } 
     /* new delay is after all - nothing to remove */
     if (dlp2->terp == NULL) { ins_after_dlp = dlp2; goto bld_tev; } 
     /* new delay is after some and before some */
     ins_after_dlp = dlp2;
     if (dlp2->terp != NULL)  
      { cancel_vpievents_toend(np, dlp2->terp, 1); dlp2->terp = NULL; }
     goto bld_tev;
    }
   /* DBG remove --- */
   if (dtyp != vpiPureTransportDelay) __vpi_terr(__FILE__, __LINE__);
   /* --- */
   /* pure transport - insert in right place in list */
   /* if new delay is before all - insert at front */
   if ((dlp2 = __find_last_bdltevp(dlp, schtim)) == NULL) 
    { ins_after_dlp = NULL; goto bld_tev; }
   /* if goes after list, end of list returned else place to ins after */
   ins_after_dlp = dlp2; 
  }   

bld_tev:
 /* allocate and schedule event */ 
 alloc_cur_tev_(tevp, __process_vpidrv_enterp, schtim);
 /* need to store scheduled driving value in event because can be many */
 if (__teputvfreelst != NULL)
  {
   tepvp = __teputvfreelst;
   __teputvfreelst = (struct teputv_t *) __teputvfreelst->np;
  }
 else tepvp = (struct teputv_t *) __my_malloc(sizeof(struct teputv_t));
 /* this will be -1 for scalar else bit index */
 tepvp->nbi = (!np->n_isavec) ? -1 : bi;
 tepvp->np = np;
 /* index from all vpi_ added drivers of the one being driven */
 tepvp->di = npp->obnum;
 /* assume non handle returning mode */
 tepvp->evnt_hp = NULL;
 /* drivers always 1 bit - i.e. for vector will only set low bit */
 /* always allocate 8 byte unpacked */
 tepvp->putv_wp = (word32 *) __my_malloc(2*WRDBYTES); 
 if (np->n_stren)
  {
  /* copy the 1 low bit */
   memcpy(tepvp->putv_wp, xsp->ap, 1);
  }
 else
  {
   /* this is 1 bit but still need the 8 byte unpacked */
   /* need to access just the low bit */
   tepvp->putv_wp[0] = (xsp->ap[0] & 1L);
   tepvp->putv_wp[1] = (xsp->bp[0] & 1L);
  }  
 tevp->tu.teputvp = tepvp;
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
   dlp2 = vpidrvp->putv_drv_tedlst[evi];
   dlp->terp = dlp2;
   if (dlp2 != NULL) dlp2->telp = dlp;
   dlp->telp = NULL;
   vpidrvp->putv_drv_tedlst[evi] = dlp;
  }
 /* insert after */
 else
  {  
   dlp->terp = ins_after_dlp->terp; 
   if (dlp->terp != NULL) dlp->terp->telp = dlp;
   ins_after_dlp->terp = dlp;
   dlp->telp = ins_after_dlp;
  }
 return(tevp);
}

/*
 * TIME PROCESSING ROUTINES
 */

/*
 * get current time
 */
extern void vpi_get_time(vpiHandle object, p_vpi_time time_p)
{
 struct h_t *hp; 
 struct mod_t *mdp;

 if (__run_state != SS_SIM) { __sim_notbegun_err("vpi_get_time"); return; } 
 hp = (struct h_t *) object;
 if (hp != NULL) if (!__validate_handle("vpi_get_time", hp)) return;
 if (!__validate_time_type("vpi_get_time", time_p->type)) return;

 if (hp != NULL) 
  {
   mdp = (struct mod_t *) hp->hin_idp[MD_MDP];
  }
 else mdp = NULL;
 __set_vpi_time(time_p, &__simtime, time_p->type, mdp); 
}

/*
 * VPI I/O ROUTINES
 */

/*
 * open an mcd channel
 *
 * SJM 09/22/03 - LRM does not allow open file descriptor except in HDL
 * but can open mcd channel - if fd opened in HDL, PLI routines can use
 */
extern PLI_UINT32 vpi_mcd_open(PLI_BYTE8 *filename)
{
 char *chp;

 chp = __pv_stralloc(filename);
 return(__mc1_fopen(chp, strlen(chp), TRUE));
}

/*
 * close an mcd channel 
 */
extern PLI_UINT32 vpi_mcd_close(PLI_UINT32 mcd)
{
 if ((mcd & FIO_MSB) != 0)
  {
   return(__fd_do_fclose(mcd & ~FIO_FD));
  }
 return(__close_mcd(mcd, TRUE));
}

/*
 * get the name of a channel descriptor (use first if more on)
 */
extern PLI_BYTE8 *vpi_mcd_name(PLI_UINT32 mcd)
{
 int32 i, fd;

 if ((mcd & FIO_MSB) != 0)
  {
   fd = mcd & ~(FIO_FD);
   /* AIV 06/27/05 - fd cannot be greater than max file size */
   if (fd >= MY_FOPEN_MAX || __fio_fdtab[fd] == NULL) return(NULL);
   else return(__fio_fdtab[fd]->fd_name);
  }
 for (i = 2; i < 31; i++)
  {
   if (((mcd >> i) & 1L) == 0L) continue;
   if (__mulchan_tab[i].mc_s == NULL)
    {
     __vpi_err(1894, vpiError,
      "vpi_mcd_name bit %d on for channel that is unused", i + 1);
     return(NULL);
    }
   return(__mulchan_tab[i].mc_fnam);
  }
 __vpi_err(1898, vpiError,
  "vpi_mcd_name passed empty (0) multi-channel descriptor");
 return(NULL);
}

/*
 * printf to multi-channel descriptor - modern VPI form
 *
 * notice here mcd is word32 in in tf_ routines it is int32 by standard
 * but functions almost same - returns value for last if many
 */
/*VARARGS*/
extern PLI_INT32 vpi_mcd_printf(PLI_UINT32 mcd, PLI_BYTE8 *format, ...)
{
 va_list va, va2;
 int32 i, fd;
 PLI_INT32 numch_prtfed = 0;

 if ((mcd & FIO_MSB) != 0)
  {
   fd = mcd & ~(FIO_FD);
   va_start(va, format);
   /* AIV 06/27/05 - fd cannot be greater than max file size */
   if (fd >= MY_FOPEN_MAX || __fio_fdtab[fd] == NULL) 
    {
     numch_prtfed = -1;
    }
   else
    {
     numch_prtfed = vfprintf(__fio_fdtab[fd]->fd_s, format, va);
    }
   va_end(va);
   return(numch_prtfed);
  }

 /* SJM 03/26/00 - mcd 1 (bit 0) know both stdout and std log if open */
 /* may be other mcd bits on (files open) too */
 if ((mcd & 1) != 0)
  {
   va_start(va, format);
   va_start(va2, format);
   numch_prtfed = vprintf(format, va);
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
       __vpi_err(2010, vpiWarning,
        "vpi_mcd_printf: multi-channel descriptor bit %d on, but file not open",
        i + 1);
       numch_prtfed = -1;
      }
     /* using last since will always be same */
     else
      {
       /* SJM 10/13/99 - ansii std says varargs not usable after vfprintf */
       va_start(va, format);
       numch_prtfed = vfprintf(__mulchan_tab[i].mc_s, format, va);
       va_end(va);
      }
    }
  }
 if (((mcd >> 31) & 1) != 0)
  {
   __vpi_err(2020, vpiWarning,
    "vpi_mcd_printf: multi-channel descriptor bit 31 on but file not open - unusable because reserved for new Verilog 2000 file I/O");
  }
 return(numch_prtfed);
}

/*
 * formatted print to both standard output and log file (if open) 
 *
 * modern but almost same as io (tf_) form - code no larger to just duplicated 
 * because of var args, return number of printed chars following ansi  
 */
/*VARARGS*/
extern PLI_INT32 vpi_printf(PLI_BYTE8 *format, ...)
{
 va_list va, va2;
 PLI_INT32 num_prtfed = 0;

 va_start(va, format);
 va_start(va2, format);
 num_prtfed = vprintf(format, va);
 if (__log_s != NULL) vfprintf(__log_s, format, va2);
 va_end(va);
 va_end(va2);
 return(num_prtfed);
}

/*
 * var args vpi_ printf routine
 *
 * this is vpi printf variant (goes to stdio and log file) where user
 * has called va_start(ap) before and must call va_end(ap) after
 *
 * this must format to string so use giant (16k for now) buffer because
 * can't effect varargs since caller started
 */
extern int32 vpi_vprintf(char *format, va_list ap)
{
 int32 num_prtfed;
 char buf[RDBUFSIZ];

 num_prtfed = vsnprintf(buf, RDBUFSIZ, format, ap);

 fputs(buf, stdout);
 if (__log_s != NULL) fputs(buf, __log_s);
 return(num_prtfed);
}

/*
 * var args vpi_ mcd_printf routine (can handle either file desc or mcd)
 *
 * this is vpi printf variant (goes to stdio and log file) where user
 * has called va_start(ap) before and must call va_end(ap) after
 *
 * must print to string buffer since do not have
 */
extern PLI_INT32 vpi_mcd_vprintf(PLI_UINT32 mcd, PLI_BYTE8 *format,
 va_list ap)
{
 int32 i;
 int32 fd;
 char buf[RDBUFSIZ];
 PLI_INT32 numch_prtfed = 0;

 if ((mcd & FIO_MSB) != 0)
  {
   fd = mcd & ~(FIO_FD);
   /* AIV 06/27/05 - fd cannot be greater than max file size */
   if (fd >= MY_FOPEN_MAX || __fio_fdtab[fd] == NULL) 
    {
     numch_prtfed = -1;
    }
   else
    {
     numch_prtfed = vfprintf(__fio_fdtab[fd]->fd_s, format, ap);
    }
   return(numch_prtfed);
  }

 /* assume at least one mcd or fd open */
 numch_prtfed = vsnprintf(buf, RDBUFSIZ, format, ap);

 /* SJM 03/26/00 - mcd 1 (bit 0) know both stdout and std log if open */
 /* may be other mcd bits on (files open) too */
 if ((mcd & 1) != 0)
  {
   fputs(buf, stdout);
   if (__log_s != NULL) fputs(buf, __log_s);
  }

 /* mcd's may require writing to lots of files */
 for (i = 1; i < 31; i++) 
  {
   if (((mcd >> i) & 1L) != 0L)
    { 
     if (__mulchan_tab[i].mc_s == NULL)
      {
       __vpi_err(1896, vpiError,
        "vpi_mcd_printf: multi-channel descriptor bit %d on, but file not open",
        i + 1);
       numch_prtfed = -1;
      }
     /* using last since will always be same */
     else fputs(buf, __mulchan_tab[i].mc_s);
    }
  }
 if (((mcd >> 31) & 1) != 0)
  {
   __vpi_err(1896, vpiError,
    "vpi_mcd_vprintf: multi-channel descriptor bit 31 on but file not open - unusable because reserved for new Verilog 2000 file I/O");
  }
 return(numch_prtfed);
}

/*
 * flush std out and log file
 *
 * WRITEME
 */
extern PLI_INT32 vpi_flush(void)
{
 fflush(stdout);
 if (__log_s != NULL) fflush(__log_s);
 return(0);
}

extern PLI_INT32 vpi_mcd_flush(PLI_UINT32 mcd)
{
 int32 i, fd;

 if ((mcd & FIO_MSB) != 0)
  {
   fd = mcd & ~(FIO_FD);
   /* know fd in range but if not open error */ 
   /* AIV 06/27/05 - fd cannot be greater than max file size */
   if (fd >= MY_FOPEN_MAX || __fio_fdtab[fd] == NULL) 
    {
     __vpi_err(1896, vpiError,
      "vpi_mcd_vprintf: new 2001 style file descriptor %d - file not open",
      fd);
     return(1);
    }
      
   fflush(__fio_fdtab[fd]->fd_s);
   return(0);
  } 

 /* SJM 09/09/03 - bit 31 now not used for mcds */   
 for (i = 1; i < 30; i++)
  {
   if (((mcd >> i) & 1L) != 0L)
    {
     if (__mulchan_tab[i].mc_s == NULL)
      {
       __vpi_err(2010, vpiWarning,
        "multi-channel descriptor bit %d on, but file not open", i);
      }
     else fflush(__mulchan_tab[i].mc_s);
    }
  }
 return(0);
}

/*
 * NEW 2001 ROUTINES TO GET AND PUT DATA
 */

/*
 * get and put data for $save/$restart
 * 
 * get/put user data for XL/NC save/restart but not supported since using
 * OS process image save mechanism much better and no need to explicitly
 * save anything
 */
extern PLI_INT32 vpi_get_data(PLI_INT32 id, PLI_BYTE8 *dataLoc,
 PLI_INT32 numOfBytes)
{
 __vpi_err(1801, vpiError,
  "new P1364 2001 vpi_get_data routine unsupported because $save/$restart not implemented - use OS save/restart");
 return(0);
}

extern PLI_INT32 vpi_put_data(PLI_INT32 id, PLI_BYTE8 *dataLoc,
 PLI_INT32 numOfBytes)
{
 __vpi_err(1801, vpiError,
  "new P1364 2001 vpi_put_data routine unsupported because $save/$restart not implemented - use OS save/restart");
 return(0);
}

/*
 * get/put data associated with most recent user sys task or function call
 *
 * SJM 04/15/04 - add vpi save/get user data routines since PLI 1.0 deprecated 
 */
extern void *vpi_get_userdata(vpiHandle obj)
{
 int32 inum;
 word32 *wp;
 struct h_t *hp;
 struct hrec_t *hrp;
 struct tskcall_t *tkcp;

 /* notice can't get or put user data in compile tf cb - need elab. n.l. */
 if (__run_state != SS_RESET && __run_state != SS_SIM)
  {
   __sim_notbegun_err("vpi_get_userdata");
   return(NULL);
  } 

 hp = (struct h_t *) obj;
 hrp = hp->hrec;
 /* AIV 06/19/12 - this was incorrect of the multiple instance case */
 /* need to access per instance (inum) */
 if (hrp->htyp == vpiSysFuncCall)
  {
   inum = get_inum_();
   wp = hrp->hu.hxp->lu.x->szu.vpi_sysf_datap;
   if (wp == NULL) return(NULL);
   return((void *) wp[inum]);
  }
 else if (hrp->htyp == vpiSysTaskCall)
  {
   tkcp = &(hrp->hu.hstp->st.stkc);
   inum = get_inum_();
   wp = tkcp->tkcaux.vpi_syst_datap;
   if (wp == NULL) return(NULL);
   return((void *) wp[inum]);
  }
 __vpi_err(1839, vpiError,
  "vpi_get_userdata argument %s illegal - must be vpiSysFuncCall or vpiSysTaskCall", 
  __to_vpionam(__wrks1, hrp->htyp));
 return(NULL);
}

extern PLI_INT32 vpi_put_userdata (vpiHandle obj, void *userdata) 
{
 int32 inum;
 word32 *wp;
 struct h_t *hp;
 struct hrec_t *hrp;
 struct tskcall_t *tkcp;
 struct mod_t *mdp;

 /* notice can't get or put user data in compile tf cb - need elab. n.l. */
 if (__run_state != SS_RESET && __run_state != SS_SIM)
  {
   __sim_notbegun_err("vpi_put_userdata");
   return(0);
  } 

 hp = (struct h_t *) obj;
 hrp = hp->hrec;
 /* AIV 06/19/12 - this was incorrect of the multiple instance case */
 /* need to alloc word * array to old one per instance */
 if (hrp->htyp == vpiSysFuncCall)
  {
   wp = hrp->hu.hxp->lu.x->szu.vpi_sysf_datap;
   if (wp == NULL)
    {
     mdp = (struct mod_t *) hp->hin_idp[MD_MDP];
     wp = (word32 *) __my_malloc(mdp->flatinum*sizeof(void *));
     memset(wp, 0, mdp->flatinum*sizeof(void *));
     hrp->hu.hxp->lu.x->szu.vpi_sysf_datap = wp;
    }
   inum = get_inum_();
   wp[inum] = (word32) userdata;
   return(1);
  }
 else if (hrp->htyp == vpiSysTaskCall)
  {
   tkcp = &(hrp->hu.hstp->st.stkc);
   wp = tkcp->tkcaux.vpi_syst_datap;
   if (wp == NULL)
    {
     mdp = (struct mod_t *) hp->hin_idp[MD_MDP];
     wp = (word32 *) __my_malloc(mdp->flatinum*sizeof(void *));
     memset(wp, 0, mdp->flatinum*sizeof(void *));
     tkcp->tkcaux.vpi_syst_datap = wp;
    }
   inum = get_inum_();
   wp[inum] = (word32) userdata;
   return(1);
  }
 __vpi_err(1839, vpiError,
  "vpi_put_userdata first argument %s illegal - must be vpiSysFuncCall or vpiSysTaskCall", 
  __to_vpionam(__wrks1, hrp->htyp));
 return(0);
}

/* 
 * VPI UTLITY ROUTINES
 */

/*
 * compare two handle to determine if same object
 * (i.e. same object in same itree instance)
 * maybe better way than to compare all fields except links for freeing
 */
extern PLI_INT32 vpi_compare_objects(vpiHandle object1, vpiHandle object2)
{
 int32 biti;
 struct h_t *hp1, *hp2;
 struct hrec_t *hrp1, *hrp2;
 decl_idp_locals_;

 hp1 = (struct h_t *) object1;
 if (!__validate_handle("vpi_compare_objects (first)", hp1)) return(0);
 hrp1 = hp1->hrec;
 hp2 = (struct h_t *) object2;
 if (!__validate_handle("vpi_compare_objects (second)", hp2)) return(0);
 hrp2 = hp2->hrec;

 /* types of handles must be same in same itre loc or can't compare equal */
 if (hrp1->htyp != hrp2->htyp || hrp1->htyp2 != hrp2->htyp2) return(0);
 if (hp1->hin_idp != hp2->hin_idp || hrp1->hin_tskp != hrp2->hin_tskp)
  return(0);

 /* only tricky part is for bit handles - bith ndx and expr can match */
 switch (hrp1->htyp) {
  case vpiNetBit: case vpiRegBit: case vpiVarSelect: case vpiMemoryWord:
   if (hrp1->bith_ndx && hrp2->bith_ndx)
    {
     if (hrp1->hu.hanyp != hrp2->hu.hanyp) return(0);
     if (hrp1->hi == hrp2->hi) return(1);
     return(0);
    }
   /* if both expressions must be identical */ 
   if (!hrp1->bith_ndx && !hrp2->bith_ndx)
    {
     if (hrp1->hu.hanyp != hrp2->hu.hanyp) return(0);
     if (hrp1->hu.hxp == hrp2->hu.hxp) return(1);
     return(0);
    }
   /* one expr. one not - only match if constant - can not compare hanyp */
   if (hrp1->bith_ndx)
    {
     if (hrp1->hu.hnp != hrp2->hu.hxp->lu.sy->el.enp) return(0L);
     /* if non constant mixed form never same */
     if (!__expr_is_vpiconst(hrp2->hu.hxp->ru.x)) return(0);
     set_save_idp_(hp2->hin_idp);
     biti = __comp_ndx(hrp2->hu.hxp->lu.sy->el.enp, hrp2->hu.hxp->ru.x);
     restore_idp_();
     /* out of range can never match bith ndx form */
     if (biti == -1) return(0);
     if (hrp1->hi == biti) return(1); 
     return(0);
    }
   if (hrp2->bith_ndx)
    {
     if (hrp2->hu.hnp != hrp1->hu.hxp->lu.sy->el.enp) return(0);
     /* if non constant mixed form never same */
     if (!__expr_is_vpiconst(hrp1->hu.hxp->ru.x)) return(0);
     set_save_idp_(hp1->hin_idp);
     biti = __comp_ndx(hrp1->hu.hxp->lu.sy->el.enp, hrp1->hu.hxp->ru.x);
     restore_idp_();
     if (biti == -1) return(0);
     if (hrp1->hi == biti) return(1); 
     return(0);
    }
 }
 if (hrp1->hu.hanyp != hrp2->hu.hanyp) return(0);
 if (hrp1->hi != hrp2->hi) return(0);
 return(1);
}

/*
 * check to see if last vpi routine returned an error
 *
 * always needs to be checked even if routine worked for warnings
 * returns T on error
 */
extern int32 vpi_chk_error(p_vpi_error_info error_info_p)
{
 if (__last_eip == NULL) return(FALSE);
 if (error_info_p == NULL) return(TRUE);
 *error_info_p = __wrk_einfo;
 return(TRUE);
}

/*
 * ROUTINES TO FREE HANDLES
 */

/*
 * free a handle and associated storage - return F on no free else T
 *
 * for iterator frees entire handle table
 */
extern PLI_INT32 vpi_free_object(vpiHandle object)
{
 struct h_t *hp;
 struct hrec_t *hrp;

 hp = (struct h_t *) object;
 if (!__validate_handle("vpi_free_object", hp)) return(0);
 hrp = hp->hrec;
 if (hrp->in_iter)
  {
   /* SJM 06-22-10 - now unless undocumented old vpi freeing algorithm, */
   /* now can free handle by marking */
   if (!__old_vpi_obj_after_iter_free_only) 
    {
     /* mark handle to be freed later - will be around so user problem */
     /* if used before iter freed */
     hrp->free_with_iter = TRUE;
     return(TRUE);    
    }
   else
    {
     __vpi_err(2019, vpiWarning,
      "using old vpi_ freeing algorithm, component of iterator can not be freed - use vpi_copy_object to save if needed");
     return(FALSE);
    }
  }
 if (hrp->htyp == vpiIterator) { __free_iterator(object); return(TRUE); }
 if (hrp->htyp == vpiCallback || hrp->htyp == vpiUserSystf)
  {
   __vpi_err(2020, vpiWarning, "unable to free %s object - can not be freed",
    __to_vpionam(__wrks1, hp->hrec->htyp));
   return(FALSE);
  }
 /* for tab form scheduled entire vector must free ev. ptr table */
 if (hrp->bith_ndx && hrp->htyp == vpiSchedEvent)
  {
   struct net_t *np;

   np = hrp->hu.hevrec->evnp;
   __my_free(hrp->hu.hevrec->evndxtab, np->nwid*sizeof(struct tev_t *));
   __my_free(hrp->hu.hevrec, sizeof(struct schdev_t));
   hrp->hu.hevrec = NULL;
  }
 /* maybe free expr. */
 if (hrp->free_xpr) __free_xtree(hrp->hu.hxp);
 /* BEWARE - to free handle can only link on free list since may be in */
 /* large iterator table */ 
 __free_hp(hp);
 return(TRUE);
}

/*
 * free an iterator contents and handle
 *
 * only way to free in iterator handle and called automaticaly
 * when iterator done or error
 * internal routine always called with iterator handle
 *
 * FIXME - need to change to 8 bytes handle with rest in fixed type memory
 *
 * transitional algorithm - normally just turn off in_iter so user
 * can free later if wanted if auto free option free handles and iter
 * array (with real free)
 */
extern void __free_iterator(vpiHandle ihref)
{
 int32 hi;
 struct h_t *hp, *hp2;
 struct hrec_t *hrp;
 struct pviter_t *iterp;

 hp = (struct h_t *) ihref;
 hrp = hp->hrec;
 /* DBG remove --- */
 if (hrp->htyp != vpiIterator) __vpi_terr(__FILE__, __LINE__);
 /* --- */
 /* mark handles as separately freeable if user wants to later */
 iterp = hrp->hu.hiterp;
 /* must look for and free any expressions */
 for (hi = 0; hi < iterp->numhs; hi++)
  {
   hp2 = iterp->scanhptab[hi];
   hp2->hrec->in_iter = FALSE;
   /* SJM 06-22-10 - new algorithm - allowing free of handles in iterators */
   /* when free, just mark - remove here */
   if (hp2->hrec->free_with_iter)
    {
     /* free with iter should never be on if old vpi_ iter free selected */
     /* DBG remove */
     if (__old_vpi_obj_after_iter_free_only) __vpi_terr(__FILE__, __LINE__);
     /* --- */
     /* need vpi free object because of special unfreeable cases */
     vpi_free_object((vpiHandle) hp2);
    }
  }

 /* SJM 06-22-10 - this is reason for change to scan h_t ptr tab - can free */
 __my_free(iterp->scanhptab, iterp->numhs*sizeof(struct h_t *));
 /* but free the small iterator record - stops further accessing of iter */
 /* needed so handle magic number will fail */
 __my_free(iterp, sizeof(struct pviter_t));
 __free_hp(hp);
}

/*
 * free handle contents hp
 *
 * caller must have validated hp before calling this routine
 * caller must also free hxp if needed
 *
 * notice this works because if freeing handle from iterator table puts
 * all or some on free list for reuse
 */
extern void __free_hp(struct h_t *hp) 
{
 struct hrec_t *hrp; 

 hrp = hp->hrec;
 /* zero so magic number test fails and link hrec onto hrec free list */
 memset(hrp, 0, sizeof(struct hrec_t));
 hrp->hu.hfreenxt = __vpi_hrecfree_hdr;
 __vpi_hrecfree_hdr = hrp; 

 /* zero and link hrp onto hp free list */
 memset(hp, 0, sizeof(struct h_t));
//AIV INUM FIXME
//AIV IDP FIXME - case ok????
 hp->hin_idp = (t_midat *) __vpi_hfree_hdr;
 __vpi_hfree_hdr = hp;
}

/*
 * copy a handle and associated storage
 * can not copy iterator (must recreate)
 */
extern vpiHandle vpi_copy_object(vpiHandle object)
{
 struct h_t *hp, *hp2;
 struct hrec_t *hrp2;

 /* SJM 08/08/99 - vpi scan may return nil and free so copy of nil is nil */
 if (object == NULL) return(NULL);

 hp = (struct h_t *) object;
 if (!__validate_handle("vpi_copy_object", hp)) return(0);
 if (hp->hrec->htyp == vpiIterator)
  {
   __vpi_err(1842, vpiError,
    "iterator handle can not be copied - call vpi_iterate to create same contents handle");
   return(NULL);
  }
 hp2 = (struct h_t *) __mk_handle(hp->hrec->htyp, (void *) NULL, NULL, NULL);
 hp2->hin_idp = hp->hin_idp; 
 hrp2 = hp2->hrec;
 *(hrp2) = *(hp->hrec);
 /* if copy from iterator, no longer in iterator */
 hrp2->in_iter = FALSE; 
 if (hrp2->free_xpr)
  {
   hrp2->hu.hxp = __sim_copy_expr(hp->hrec->hu.hxp);
  }
 return((vpiHandle) hp2);
}

/*
 * ROUTINES TO IMPLEMENT SIM CONTROL MECHANISM
 */

/*
 * send information from user application back to simulator
 *
 * main use is elminating need for tf_dofinish and tf_dostop but also for
 * cver specific extensions 
 */
/*VARARGS*/
extern PLI_INT32 vpi_control(PLI_INT32 operation, ...)
{
 int32 sav_err_cnt;
 va_list va;
 PLI_INT32 retv;
 int32 diag_level, stop_val, reset_val;
 vpiHandle scopobj, cbobj;

 /* assume success */
 retv = TRUE;
 va_start(va, operation);
 switch (operation) {
  case vpiStop:
   diag_level = va_arg(va, int32);
   retv = __do_vpi_stop(diag_level);
   break;
  case vpiFinish:
   diag_level = va_arg(va, int32);
   __pli_dofinish(diag_level, "vpi_control");
   break;
  case vpiReset:
   stop_val = va_arg(va, int32); 
   reset_val = va_arg(va, int32);
   diag_level = va_arg(va, int32);
   /* this never returns */
   __do_vpi_reset(stop_val, reset_val, diag_level);
   break;
  case vpiSetInteractiveScope:
   scopobj = va_arg(va, vpiHandle);
   retv = do_vpi_iact_scopchg(scopobj);
   break;
  case vpiDumpVars:
   if (!__can_exec)
    {
     __vpi_err(1900, vpiError,
      "vpi_control vpiDumpVars operation illegal - only callable during simulation");
     retv = FALSE; 
     break;
    }
   sav_err_cnt = __pv_err_cnt;
   __exec_dumpvars(NULL, FALSE);
   if (__pv_err_cnt > sav_err_cnt) retv = FALSE; else retv = TRUE;
   break;
  case vpiFlushLog:
   /* flush internal files */
   if (__dv_fd != -1) __my_dv_flush();
//AIV? - look at me - why are these being flushed - not part of log file?
 //  if (__dp_fd != -1) __my_dp_flush();
   if (__log_s != NULL) fflush(__log_s);
   if (__tr_s != NULL) fflush(__tr_s);
   break; 
  case vpiDisableCb:
   cbobj = va_arg(va, vpiHandle);
   retv = do_vpi_cb_onoff(cbobj, FALSE);
   break;
  case vpiEnableCb:
   cbobj = va_arg(va, vpiHandle);
   retv = do_vpi_cb_onoff(cbobj, TRUE);
   break;
  default:
   __vpi_err(1888, vpiError,
    "vpi_control first operation argument value %d illegal", operation);
   retv = FALSE;
 }
 va_end(va);
 return(retv);
}

/*
 * change interactive scope from vpi_ user code
 *
 * notice need to call call back on scope change although may never
 * actually enter interactive code
 */
static int32 do_vpi_iact_scopchg(vpiHandle newscopobj)
{
 struct h_t *hp;

 hp = (struct h_t *) newscopobj;
 if (!__validate_handle("vpi_control vpiSetInteractiveScope operation", hp))
  return(FALSE);

 switch (hp->hrec->htyp) {
  case vpiModule:
   __scope_idp = hp->hin_idp;
   __scope_tskp = NULL;
   break;
  case vpiTask: case vpiFunction: case vpiNamedBegin: case vpiNamedFork:
   __scope_idp = hp->hin_idp;
   __scope_tskp = hp->hrec->hin_tskp;
   break;
  default:
   __vpi_err(1870, vpiError,
    "vpi_control vpiSetInteractiveScope argument not scope handle - %s illegal",
    __to_vpionam(__wrks1, hp->hrec->htyp));
   return(FALSE);
  }

 /* because not really entering interactive mode no db line change */
 if (__tfrec_hdr != NULL) __call_misctfs_scope();
 if (__have_vpi_actions) __vpi_iactscopechg_trycall();
 return(TRUE);
}

/*
 * some error message output routines that need vpi_ mechanism
 */
extern void __emit_vpi_noiact_warn(void)
{
 __vpi_err(2029, vpiWarning,
  "vpi_control vpiStop no effect - interactive environment disabled");
}

extern void __emit_vpi_iniact_warn(void)
{
 __vpi_err(2031, vpiWarning,
  "vpi_control vpiStop no effect - already in interactive debugger");
}

/*
 * turn on (enable) or off (disable) call back 
 *
 * works for any call back except time related
 * LOOKATME - maybe should always re-enable on reset
 */
static int32 do_vpi_cb_onoff(vpiHandle cbobj, int32 turn_cb_on)
{
 struct dceauxlst_t *dceauxlp;
 struct h_t *hp;
 struct hrec_t *hrp;
 struct cbrec_t *cbp;
 char s1[RECLEN], s2[RECLEN];

 if (turn_cb_on) strcpy(s1, "vpiEnableCb"); else strcpy(s1, "vpiDisableCb");
 hp = (struct h_t *) cbobj;
 sprintf(s2, "vpi_control %s operation", s1); 
 if (!__validate_handle(s2, hp)) return(FALSE);
 hrp = hp->hrec;
 cbp = hrp->hu.hcbp;

 if (hrp->htyp != vpiCallback)
  {
   __vpi_err(1832, vpiError,
    "vpi_control %s operation requires vpiCallback handle - %s illegal",
    s1,__to_vpionam(__wrks1, hrp->htyp));
   return(FALSE);
  }

 switch (cbp->cb_reason) {
  case cbAtStartOfSimTime: case cbReadWriteSynch: case cbReadOnlySynch: 
  case cbNextSimTime: case cbAfterDelay:
   __vpi_err(1930, vpiError,
    "vpi_control %s illegal for time related %s call back",
    s1, __cb_reason_to_nam(__xs, cbp->cb_reason));
   return(FALSE);
  default: break;
 }

 if (turn_cb_on) 
  {
   if (!cbp->cb_user_off)
    {
     /* SJM 07/26/00 - if call back run with reentry to itself turned off */
     /* allow enabling so can be re-entered */
     if (cbp->cb_reason == cbValueChange || cbp->cb_reason == cbForce
      || cbp->cb_reason == cbRelease)
      {
       /* turn on all dce's - temporarily off */
       for (dceauxlp = cbp->cbdcep; dceauxlp != NULL;
        dceauxlp = dceauxlp->dclnxt)
        {
         dceauxlp->ldcep->dce_off = FALSE;
        }
       return(TRUE);
      }
     
     __vpi_err(2033, vpiWarning,
      "vpi_control %s no effect - attempt to enable already enabled %s call back",
      s1, __cb_reason_to_nam(__xs, cbp->cb_reason));
     return(FALSE);
    }
  }
 else 
  {
   if (cbp->cb_user_off)
    {
     __vpi_err(2033, vpiWarning,
      "vpi_control %s no effect - attempt to disable already disabled %s call back",
     s1, __cb_reason_to_nam(__xs, cbp->cb_reason));
     return(FALSE);
    }
  }
 cbp->cb_user_off = (turn_cb_on) ? FALSE : TRUE;

 /* change on/off state of each dc evetn */
 /* LOOKATME - what happen with all forms force/release */
 for (dceauxlp = cbp->cbdcep; dceauxlp != NULL; dceauxlp = dceauxlp->dclnxt)
  {
   dceauxlp->ldcep->dce_off = (turn_cb_on) ? FALSE : TRUE;
  }
 return(TRUE);
}


/*
 * ROUTINES TO FREE VPI_ OBJECTS FOR RESET
 */

/*
 * reinitialize the vpi_ mechanism
 *
 * possible net's putv rec left but driver reinitialized to z elsewhere
 * do not free handles - DOCUMENT can be large source of memory drain
 */
extern void __reinit_vpi(void) 
{
 int32 save_simstate;
 struct cbrec_t *cbp, *cbp2;

 /* free time related in lists that are not in event queues */ 
 __rosync_slot = FALSE;

 /* remove time related call backs only */ 
 for (cbp = __vpi_cbrec_hdr; cbp != NULL;)
  {
   cbp2 = cbp->cbnxt;
   /* only remove scheduled time related or value change related */
   switch (cbp->cb_reason) {
    /* remove all time and change cbs but leave all actions */
    case cbAtStartOfSimTime: case cbReadWriteSynch: case cbReadOnlySynch:
    case cbNextSimTime: case cbAfterDelay:
     /* this links out but works because nxt if present always remains */
     /* using user level routine but before sim has begun (fake sim) */
     save_simstate = __run_state;
     __run_state = SS_SIM;
     if (!vpi_remove_cb((vpiHandle) cbp->cb_cbhp))
       __vpi_terr(__FILE__, __LINE__);
     __run_state = save_simstate;
     break;
    default:
     break;
   }
   if (cbp2 == NULL) break;
   cbp = cbp2;
  }
}

/*
 * ROUTINES TO ACCESS INTERNAL INFO
 */

/*
 * get version information and set pointers to argv/argc
 *
 * this is passed struct - routines fills in ptrs
 */
extern PLI_INT32 vpi_get_vlog_info(p_vpi_vlog_info vlog_info_p)
{
 char s1[RECLEN];

 /* only build nested vpi format argv if first time */
 if (__vpi_argv == NULL) __bld_vpi_argv();

 vlog_info_p->argc = __vpi_argc; 
 vlog_info_p->argv = __vpi_argv; 

 sprintf(s1, "%s%s of %s (%s).\n", __vers, __vers2, __ofdt, __platform);
 /* AIV 09/14/09 - changed product name */
 vlog_info_p->product = __pv_stralloc("CVC Verilog Simulator");
 vlog_info_p->version = __pv_stralloc(s1);
 return(TRUE);
}

/*
 * undocumented (to users) debug routine for showing contents of handle
 *
 * LOOKATME - maybe should dump more information for some object types 
 * LOOKATME - not portable because of addr cast
 */
extern int32 __vpi_show_object(vpiHandle obj)
{
 int32 bad_inst, bad_tsk, first_time, ttyp, tryget_name;
 struct h_t *hp;
 struct hrec_t *hrp;
 char *chp, s1[RECLEN], s2[RECLEN]; 

 __my_fprintf(stdout, ">>> showing vpi_ object:\n");
 hp = (struct h_t *) obj;

 if (!__chk_showobj(hp, &(bad_inst), &(bad_tsk))) return(0);
 hrp = hp->hrec;

 tryget_name = TRUE;
 if (!__validate_otyp(hrp->htyp))
  {
   __my_fprintf(stdout,
    "**object bad: object type %d illegal - showing anyway\n", hrp->htyp);
   tryget_name = FALSE;
  }
 else
  {
   __my_fprintf(stdout, "Object type: %s (addr %lx)",
    __to_vpionam(s1, hrp->htyp), (word32) hp);
  }
 if (hrp->htyp2 != 0) 
  {
   if (!__validate_otyp(hrp->htyp2))
    {
     __my_fprintf(stdout,
      "\n**object bad: secondary type %d illegal\n", hrp->htyp2);
     tryget_name = FALSE;
    }
   else
    {
     __my_fprintf(stdout, " (secondary type: %s)",
      __to_vpionam(s1, hrp->htyp2));
    }
  }
 if (!bad_inst && !bad_tsk)
  {
   if (hp->hin_idp == NULL)
    {
     __my_fprintf(stdout, " **no associated instance**");
    }
   else
    {
     __my_fprintf(stdout, " in %s", __msg_idp_blditree(s1, hp->hin_idp,
      hrp->hin_tskp));
     if (hrp->hin_tskp != NULL)
      {
       ttyp = __to_vpi_tasktyp(hrp->hin_tskp->tsktyp); 
       __my_fprintf(stdout, " (%s)\n", __to_vpionam(s1, ttyp));
      }
    }
  }
 else if (!bad_inst && bad_tsk)
  {
   if (hp->hin_idp != NULL)
    {
     __my_fprintf(stdout, " in %s (**task/func bad**)",
      __msg2_idp_blditree(s1, hp->hin_idp));
    }
   tryget_name = FALSE;
  }
 else if (bad_inst && !bad_tsk)
  {
   ttyp = __to_vpi_tasktyp(hrp->hin_tskp->tsktyp); 
   __my_fprintf(stdout, " **bad instance** but in %s %s",
    __to_vpionam(s1, ttyp), hrp->hin_tskp->tsksyp->synam);
   tryget_name = FALSE;
  }
 else
  {
   __my_fprintf(stdout, " **bad instance and bad task**");
   tryget_name = FALSE;
  }

 /* LOOKATME - maybe should try to get def name if can */
 if (tryget_name)
  {
   __acc_vpi_erroff = TRUE;
   /* this access error vpi_ error info and turns off vpi error cbs */  
   /* for objects without names, expect fail here */
   chp = vpi_get_str(vpiName, obj);
   if (chp != NULL && !__my_vpi_chk_error())
    {
     __my_fprintf(stdout, " name=%s", chp); 
    }
  }
 __my_fprintf(stdout, "\n");

 /* build the telltales */
 strcpy(s2, "  [");
 first_time = TRUE;
 if (hrp->hi != -1)
  {
   sprintf(s1, "index=%d", hrp->hi);
   strcat(s2, s1);
   if (first_time) first_time = FALSE; 
  }
 if (hrp->in_iter)
  {
   if (!first_time) strcat(s2, ", "); else first_time = FALSE;
   strcat(s2, "in interator");
  }
 if (hrp->free_xpr)
  {
   if (!first_time) strcat(s2, ", "); else first_time = FALSE;
   strcat(s2, "Created object");
  }
 if (hrp->htyp == vpiSchedEvent || hrp->htyp == vpiSchedBitEvent)
  {
   if (!first_time) strcat(s2, ", "); else first_time = FALSE;
   sprintf(s1, "Schedule event done=%d", hrp->evnt_done);
   strcat(s2, s1);
  }
 if (hrp->bith_ndx)
  {
   if (!first_time) strcat(s2, ", "); else first_time = FALSE;
   strcat(s2, "Variable index");
  }

 if (!first_time) __my_fprintf(stdout, "%s]\n", s2); 

 /* set globals for user to look at in case debugging turned on */
 __cur_vpi_inst = hp;  
 __cur_vpi_obj = hrp;
 return(1);
}

/*
 * show object check handle
 */
extern int32 __chk_showobj(struct h_t *hp, int32 *bad_inst, int32 *bad_task)
{
 struct hrec_t *hrp; 

 /* if low value bad since ptr */
 /* SJM 07/08/01 - need to compare to uint32 not int32 since >2G high bit on */
 if (hp == NULL || ((word32) hp) < 256)
  {
   __my_fprintf(stdout, 
    "**object bad: address (%p) null or illegal low address\n", hp);
   return(FALSE);
  }
 hrp = hp->hrec;
 /* SJM 07/08/01 - need to compare to uint32 not int32 since >2G high bit on */
 if (hrp == NULL || ((word32) hrp) < 256)
  {
   __my_fprintf(stdout,
    "**object bad: net list pointer (%p) null or illegal low address\n", hrp);
   return(FALSE);
  }
 if (hrp->h_magic != PVH_MAGIC)
  {
   __my_fprintf(stdout,
    "**object bad: illegal magic number (%x) - showing anyway\n",
    hrp->h_magic);
  }
 *bad_inst = FALSE;
 /* SJM 07/08/01 - need to compare to uint32 not int32 since >2G high bit on */
 /* AIV 04/10/07 - now comparing integers (identifier) no longer needed
 if (hp->hin_idp != -1 && ((word32) hp->hin_idp) < 256)
  {
   __my_fprintf(stdout, 
    "**object bad: instance address (%p) probably illegal\n", hp->hin_idp);
   *bad_inst = TRUE;
  }
 */
 *bad_task = FALSE;
 /* SJM 07/08/01 - need to compare to uint32 not int32 since >2G high bit on */
 if (hrp->hin_tskp != NULL && ((word32) (hrp->hin_tskp)) < 256)
  {
   __my_fprintf(stdout, 
    "**object bad: task/func address (%p) probably illegal\n",
    hrp->hin_tskp);
   *bad_task = TRUE;
  }
 return(TRUE);
}

/*
 * VPI CONSTANT TO NAME CONVERSION ROUTINES
 */

/* dense table indexed by constant object value */
/* fast indexing of dense table works because vpi object numbers */
/* fixed for .o file interchangeabiliy */	 

/* if vpi_user.h official LRM constant values change, must change this */
/* constant in table so can use debugging code to check for dense order */
static struct onamvpi_t onames_vpi[] = {
 /* notice object types can also sometimes be access methods */
 { "**unused-obj-const**", 0 }, 
 { "vpiAlways", vpiAlways },
 { "vpiAssignStmt", vpiAssignStmt },
 { "vpiAssignment", vpiAssignment },
 { "vpiBegin", vpiBegin },
 { "vpiCase", vpiCase },
 { "vpiCaseItem", vpiCaseItem },
 { "vpiConstant", vpiConstant },
 { "vpiContAssign", vpiContAssign },
 { "vpiDeassign", vpiDeassign },
 { "vpiDefParam", vpiDefParam },
 { "vpiDelayControl", vpiDelayControl },
 { "vpiDisable", vpiDisable },
 { "vpiEventControl", vpiEventControl },
 { "vpiEventStmt", vpiEventStmt },
 { "vpiFor", vpiFor },
 { "vpiForce", vpiForce },
 { "vpiForever", vpiForever },
 { "vpiFork", vpiFork },
 { "vpiFuncCall", vpiFuncCall },
 { "vpiFunction", vpiFunction },
 { "vpiGate", vpiGate },
 { "vpiIf", vpiIf },
 { "vpiIfElse", vpiIfElse },
 { "vpiInitial", vpiInitial },
 { "vpiIntegerVar", vpiIntegerVar },
 { "vpiInterModPath", vpiInterModPath },
 { "vpiIterator", vpiIterator },
 { "vpiIODecl", vpiIODecl },
 { "vpiMemory", vpiMemory },
 { "vpiMemoryWord", vpiMemoryWord },
 { "vpiModPath", vpiModPath },
 { "vpiModule", vpiModule },
 { "vpiNamedBegin", vpiNamedBegin },
 { "vpiNamedEvent", vpiNamedEvent },
 { "vpiNamedFork", vpiNamedFork },
 { "vpiNet", vpiNet },
 { "vpiNetBit", vpiNetBit },
 { "vpiNullStmt", vpiNullStmt },
 { "vpiOperation", vpiOperation },
 { "vpiParamAssign", vpiParamAssign },
 { "vpiParameter", vpiParameter },
 { "vpiPartSelect", vpiPartSelect },
 { "vpiPathTerm", vpiPathTerm },
 { "vpiPort", vpiPort },
 { "vpiPortBit", vpiPortBit },
 { "vpiPrimTerm", vpiPrimTerm },
 { "vpiRealVar", vpiRealVar },
 { "vpiReg", vpiReg },
 { "vpiRegBit", vpiRegBit },
 { "vpiRelease", vpiRelease },
 { "vpiRepeat", vpiRepeat },
 { "vpiRepeatControl", vpiRepeatControl },
 { "vpiSchedEvent", vpiSchedEvent },
 { "vpiSpecParam", vpiSpecParam },
 { "vpiSwitch", vpiSwitch },
 { "vpiSysFuncCall", vpiSysFuncCall },
 { "vpiSysTaskCall", vpiSysTaskCall },
 { "vpiTableEntry", vpiTableEntry },
 { "vpiTask", vpiTask },
 { "vpiTaskCall", vpiTaskCall },
 { "vpiTchk", vpiTchk },
 { "vpiTchkTerm", vpiTchkTerm },
 { "vpiTimeVar", vpiTimeVar },
 { "vpiTimeQueue", vpiTimeQueue },
 { "vpiUdp", vpiUdp },
 { "vpiUdpDefn", vpiUdpDefn },
 { "vpiUserSystf", vpiUserSystf },
 { "vpiVarSelect", vpiVarSelect },
 { "vpiWait", vpiWait },
 { "vpiWhile", vpiWhile },
 /* methods */
 { "vpiCondition", vpiCondition },
 { "vpiDelay", vpiDelay },
 { "vpiElseStmt", vpiElseStmt },
 { "vpiForIncStmt", vpiForIncStmt },
 { "vpiForInitStmt", vpiForInitStmt },
 { "vpiHighConn", vpiHighConn },
 { "vpiLhs", vpiLhs },
 { "vpiIndex", vpiIndex },
 { "vpiLeftRange", vpiLeftRange },
 { "vpiLowConn", vpiLowConn },
 { "vpiParent", vpiParent },
 { "vpiRhs", vpiRhs },
 { "vpiRightRange", vpiRightRange },
 { "vpiScope", vpiScope },
 /* notice this is only an iterator or 1-to-1 method */
 { "vpiSysTfCall", vpiSysTfCall },
 { "vpiTchkDataTerm", vpiTchkDataTerm },
 { "vpiTchkNotifier", vpiTchkNotifier },
 { "vpiTchkRefTerm", vpiTchkRefTerm },
 /* 1 to many methods */
 { "vpiArgument", vpiArgument },
 { "vpiBit", vpiBit },
 { "vpiDriver", vpiDriver },
 { "vpiInternalScope", vpiInternalScope },
 { "vpiLoad", vpiLoad },
 { "vpiModDataPathIn", vpiModDataPathIn },
 { "vpiModPathIn", vpiModPathIn },
 { "vpiModPathOut", vpiModPathOut },
 { "vpiOperand", vpiOperand },
 { "vpiPortInst", vpiPortInst },
 { "vpiProcess", vpiProcess },
 { "vpiVariables", vpiVariables  },
 { "vpiUse", vpiUse },
 /* 1-to-1 or 1 to many methods */
 { "vpiExpr", vpiExpr },
 { "vpiPrimitive", vpiPrimitive },
 { "vpiStmt", vpiStmt },

 /* object types added for Verilog 2000 - some moved from cv vpi inc file */
 { "vpiAttribute", vpiAttribute },
 { "vpiBitSelect", vpiBitSelect },
 { "vpiCallback", vpiCallback },
 { "vpiDelayTerm", vpiDelayTerm },
 { "vpiDelayDevice", vpiDelayDevice },
 { "vpiFrame", vpiFrame },
 { "vpiGateArray", vpiGateArray },
 { "vpiModuleArray", vpiModuleArray },
 { "vpiPrimitiveArray", vpiPrimitiveArray },
 { "vpiNetArray", vpiNetArray },
 { "vpiRange", vpiRange },
 { "vpiRegArray", vpiRegArray },
 { "vpiSwitchArray", vpiSwitchArray },
 { "vpiUdpArray", vpiUdpArray },
 /* methods added for Verilog 2000 - some moved from cv vpi inc file */
 { "vpiActiveTimeFormat", vpiActiveTimeFormat },
 { "vpiInTerm", vpiInTerm },
 { "vpiInstanceArray", vpiInstanceArray },
 { "vpiLocalDriver", vpiLocalDriver },
 { "vpiLocalLoad", vpiLocalLoad },
 { "vpiOutTerm", vpiOutTerm },
 { "vpiPorts", vpiPorts },
 { "vpiSimNet", vpiSimNet },
 { "vpiTaskFunc", vpiTaskFunc },
 { "vpiContAssignBit", vpiContAssignBit },
 { "vpiNamedEventArray", vpiNamedEventArray }
};
#define NVOTYPS (sizeof(onames_vpi) / sizeof(struct onamvpi_t))

/* added for Cver handles in separate range */
/* Cver added handles - pending to be added to P1364 */
/* position must match offset constant in .h file (not alphabetical) */
static struct onamvpi_t cv_onames_vpi[] = {
 { "vpiNetDriver", vpiNetDriver },
 { "vpiNetBitDriver", vpiNetBitDriver },
 { "vpiSchedBitEvent", vpiSchedBitEvent },
 { "vpiPoundParam", vpiPoundParam },
 { "vpiOneOfEachMod", vpiOneOfEachMod }
};
#define CV_NVOTYPS (sizeof(cv_onames_vpi) / sizeof(struct onamvpi_t))


/*
 * convert the vpi object constant value to a name 
 * if out of range returns nil
 * table dense and starting at 0
 */
extern char *__to_vpionam(char *s, word32 vpioval)
{
 if (vpioval < 1) goto outofrng;
 if (vpioval < NVOTYPS)
  {
   strcpy(s, onames_vpi[vpioval].vpiobjnam);
   return(s);
  }
 if (vpioval >= CV_START_ONUMS && vpioval < (CV_START_ONUMS + CV_NVOTYPS))
  {
   strcpy(s, cv_onames_vpi[vpioval - CV_START_ONUMS].vpiobjnam);
   return(s);
  }

outofrng:
 sprintf(s, "**out of range (%lu)", vpioval);
 return(s);
}

/*
 * return T if object type legal
 * if out of range returns nil
 * table dense and starting at 0
 */
extern int32 __validate_otyp(word32 vpioval)
{
 if (vpioval < 1) return(FALSE);
 if (vpioval < NVOTYPS) return(TRUE);
 if (vpioval >= CV_START_ONUMS && vpioval < (CV_START_ONUMS + CV_NVOTYPS))
  return(TRUE);

 return(FALSE);
}

/* dense array of vpi properties */
/* position must match offset constant in .h file */
static struct pnamvpi_t pnames_vpi[] = {
 { "**unused-prop-const**", 0 }, 
 { "vpiType", vpiType },
 { "vpiName", vpiName },
 { "vpiFullName", vpiFullName },
 { "vpiSize", vpiSize },
 { "vpiFile", vpiFile },
 { "vpiLineNo", vpiLineNo },
 /* module properties */
 { "vpiTopModule", vpiTopModule },
 { "vpiCellInstance", vpiCellInstance },
 { "vpiDefName", vpiDefName },
 { "vpiProtected", vpiProtected },
 { "vpiTimeUnit", vpiTimeUnit },
 { "vpiTimePrecision", vpiTimePrecision },
 { "vpiDefNetType", vpiDefNetType },
 { "vpiUnconnDrive", vpiUnconnDrive },
 { "vpiDefFile", vpiDefFile },
 { "vpiDefLineNo", vpiDefLineNo },
 /* port and net properties */
 { "vpiScalar", vpiScalar },
 { "vpiVector", vpiVector },
 { "vpiExplictName", vpiExplicitName },
 { "vpiDirection", vpiDirection },
 { "vpiConnByName", vpiConnByName },
 { "vpiNetType", vpiNetType },
 { "vpiExplicitScalared", vpiExplicitScalared },
 { "vpiExplicitVectored", vpiExplicitVectored },
 { "vpiExpanded", vpiExpanded },
 { "vpiImplicitDecl", vpiImplicitDecl },
 { "vpiChargeStrength", vpiChargeStrength  },
 { "vpiArray", vpiArray },
 { "vpiPortIndex", vpiPortIndex },
 /* gate and terminal properties */
 { "vpiTermIndex", vpiTermIndex },
 { "vpiStrength0", vpiStrength0 },
 { "vpiStrength1", vpiStrength1 },
 { "vpiPrimType", vpiPrimType },
 /* path, path terminal, timing check properties */
 { "vpiPolarity", vpiPolarity },
 { "vpiDataPolarity", vpiDataPolarity },
 { "vpiEdge", vpiEdge },
 { "vpiPathType", vpiPathType },
 { "vpiTchkType", vpiTchkType },
 /* expression properties */
 { "vpiOpType", vpiOpType },
 { "vpiConstType", vpiConstType },
 { "vpiBlocking", vpiBlocking },
 { "vpiCaseType", vpiCaseType },
 { "vpiNetDeclAssign", vpiNetDeclAssign },
 /* system taskfunc properties */
 { "vpiFuncType", vpiFuncType },
 { "vpiUserDefn", vpiUserDefn },
 { "vpiScheduled", vpiScheduled },
 { "vpiDefDelayMode", vpiDefDelayMode },
 { "vpiDefDecayTime", vpiDefDecayTime },
 { "vpiActive", vpiActive },
 { "vpiAutomatic", vpiAutomatic },
 { "vpiCell", vpiCell },
 { "vpiConfig", vpiConfig },
 { "vpiConstantSelect", vpiConstantSelect },
 { "vpiDecompile", vpiDecompile },
 { "vpiDefAttribute", vpiDefAttribute },
 { "vpiDelayType", vpiDelayType },
 { "vpiIteratorType", vpiIteratorType },
 { "vpiLibrary", vpiLibrary },
 { "vpiMultiArray", vpiMultiArray },
 { "vpiOffset", vpiOffset },
 { "vpiResolvedNetType", vpiResolvedNetType },
 { "vpiSaveRestartID", vpiSaveRestartID },
 { "vpiSaveRestartLocation", vpiSaveRestartLocation },
 { "vpiValid", vpiValid },
 { "vpiSigned", vpiSigned },
 { "vpiStop", vpiStop },
 { "vpiFinish", vpiFinish },
 { "vpiReset", vpiReset },
 { "vpiSetInteractiveScope", vpiSetInteractiveScope },
 { "vpiLocalParam", vpiLocalParam },
 { "vpiModPathHasIfNone", vpiModPathHasIfNone },
};
#define NVPTYPS (sizeof(pnames_vpi) / sizeof(struct pnamvpi_t))


/* LOOKATME - is it true there are no Cver added properties? */


/*
 * routine to acess vpi property name given constant value
 * could index but would not catch inconsistencies after standard changes
 */
extern char *__to_vpipnam(char *s, int32 pval)
{
 if (pval == vpiUndefined) { strcpy(s, "vpiUndefined"); return(s); }

 if (pval >= 1 && pval < NVPTYPS) 
  {
   strcpy(s, pnames_vpi[pval].vpipropnam);
   return(s);
  }
 sprintf(s, "**property out of range (%d)", pval);
 return(s);
}

/* table of vpi_ operator names */
static struct opnamvpi_t opnames_vpi[] = {
 { "**unused-operator-const**", 0, "UNUSED" }, 
 { "vpiMinusOp", vpiMinusOp, "-" },
 { "vpiPlusOp", vpiPlusOp, "+" },
 { "vpiNotOp", vpiNotOp, "!" },
 { "vpiBitNegOp", vpiBitNegOp, "~" },
 { "vpiUnaryAndOp", vpiUnaryAndOp, "&" },
 { "vpiUnaryNandOp", vpiUnaryNandOp, "&~" },
 { "vpiUnaryOrOp", vpiUnaryOrOp, "|" },
 { "vpiUnaryNorOp", vpiUnaryNorOp, "^~" },
 { "vpiUnaryXorOp", vpiUnaryXorOp, "^" },
 { "vpiUnaryXNorOp", vpiUnaryXNorOp, "^~" },
 { "vpiSubOp", vpiSubOp, "-" },
 { "vpiDivOp", vpiDivOp, "/"  },
 { "vpiModOp", vpiModOp, "%"  },
 { "vpiEqOp", vpiEqOp, "==" },
 { "vpiNeqOp", vpiNeqOp, "!=" },
 { "vpiCaseEqOp", vpiCaseEqOp, "==="  },
 { "vpiCaseNeqOp", vpiCaseNeqOp, "!=="  },
 { "vpiGtOp", vpiGtOp, ">" },
 { "vpiGeOp", vpiGeOp, ">=" },
 { "vpiLtOp", vpiLtOp, "<" },
 { "vpiLeOp", vpiLeOp, "<=" },
 { "vpiLShiftOp", vpiLShiftOp, "<<" },
 { "vpiRShiftOp", vpiRShiftOp, ">>" },
 { "vpiAddOp", vpiAddOp, "+" },
 { "vpiMultOp", vpiMultOp, "*" },
 { "vpiLogAndOp", vpiLogAndOp, "&" },
 { "vpiLogOrOp", vpiLogOrOp, "||" },
 { "vpiBitAndOp", vpiBitAndOp, "&" },
 { "vpiBitOrOp", vpiBitOrOp, "|" },
 { "vpiBitXorOp", vpiBitXorOp, "^" },
 { "vpiBitXNorOp", vpiBitXNorOp, "^~" },
 { "vpiConditionOp", vpiConditionOp, "?" },
 { "vpiConcatOp", vpiConcatOp, "{" },
 { "vpiMultiConcatOp", vpiMultiConcatOp, "{" },
 { "vpiEventOrOp", vpiEventOrOp, "OR" },
 { "vpiNullOp", vpiNullOp, "" },
 { "vpiListOp", vpiListOp, "," },
 { "vpiMinTypMaxOp", vpiMinTypMaxOp, "(::)" },
 { "vpiPosedgeOp", vpiPosedgeOp, "posedge" },
 { "vpiNegedgeOp", vpiNegedgeOp, "negedge" }
};
#define NVOPTYPS (sizeof(opnames_vpi) / sizeof(struct opnamvpi_t))

/*
 * routine to acess vpi expression operator name given constant value
 * could index but would not catch inconsistencies after standard changes
 */
extern char *__to_vpiopnam(char *s, int32 opval)
{
 if (opval == vpiUndefined) { strcpy(s, "vpiUndefined"); return(s); }
 if (opval < 1 || opval >= NVOPTYPS)
  { sprintf(s, "**operator out of range (%d)", opval); return(s); }
 strcpy(s, opnames_vpi[opval].vpiopnam);
 return(s);
}

/*
 * routine to acess vpi expression operator name given constant value
 * could index but would not catch inconsistencies after standard changes
 */
extern char *__to_vpiopchar(char *s, int32 opval)
{
 if (opval == vpiUndefined) { strcpy(s, "<UNDEF>"); return(s); }
 if (opval < 1 || opval >= NVOPTYPS)
  { sprintf(s, "**operator out of range (%d)", opval); return(s); }
 strcpy(s, opnames_vpi[opval].vpiopchar);
 return(s);
}

/*
 * emit common simulation has not begun (or reset in progress) error
 */
extern void __sim_notbegun_err(char *rnam)
{
 __vpi_err(1927, vpiError,
  "%s - routine not callable - simulation not started (or reset in progress)",
  rnam); 
}

/*
 * emit common compilation in progress (no n.l to traverse) message
 */
extern void __still_comp_err(char *rnam)
{
 __vpi_err(1923, vpiError,
  "%s routine not callable - design translation not completed", rnam); 
}

/*
 * emit common write or schedule during ro_synch section
 */
extern void __bad_rosync_err(char *rnam)
{
 __vpi_err(1922, vpiError,
  "%s routine not callable during ro sync - schedule for current time or write", rnam);
}

/*
 * validate a non iterator handle
 */
extern int32 __validate_nonit_handle(char *rnam, struct h_t *hp) 
{
 if (!__validate_handle(rnam, hp)) return(FALSE); 
 if (hp->hrec->htyp != vpiIterator) return(TRUE);
 __vpi_err(1815, vpiError,
  "%s: iterator handle illegal in this context", rnam); 
 return(FALSE);
}

/*
 * validate a handle - returns F on error
 * 
 * LOOKATME - acc_ handle passed to here may work and not checked for
 * FIXME - need compile -D switch than turns off most checking
 */
extern int32 __validate_handle(char *rnam, struct h_t *hp) 
{
 struct hrec_t *hrp;

 /* if low value bad since ptr */
 /* SJM 07/08/01 - need to compare to uint32 not int32 since >2G high bit on */
 if (hp == NULL || ((word32) hp) < 256)
  {
   strcpy(__wrks1, "** NULL OR LOW NUMBER **");
   goto bad_handle;
  }
 hrp = hp->hrec;
 /* SJM 07/08/01 - need to compare to uint32 not int32 since >2G high bit on */
 if (hrp == NULL || ((word32) hrp) < 256 || hrp->h_magic != PVH_MAGIC)
  {
   strcpy(__wrks1, "** PTR INTO DATA BASE ILLEGAL **");
   goto bad_handle;
  }
 if (!__validate_otyp(hrp->htyp))
  {
   sprintf(__wrks1, "%d", hrp->htyp);
   goto bad_handle;
  }
 return(TRUE);

bad_handle:
 __vpi_err(1818, vpiError,
  "%s: handle illegal magic number or type %s illegal", rnam, __wrks1); 
 return(FALSE);
}

/*
 * validate access method handle
 * returns F on error
 */
extern int32 __validate_accessm(char *rnam, int32 otype, char *accessm)
{
 if (!__validate_otyp(otype))
  {
   __vpi_err(1819, vpiError,
    "%s: access method type (can be handle type) %d for %s illegal or out of range",
    rnam, otype, accessm); 
   return(FALSE);
  }
 return(TRUE);
}

/*
 * validate a vpi time type field
 */
extern int32 __validate_time_type(char *rnam, int32 timtyp)
{
 if (timtyp == vpiScaledRealTime || timtyp == vpiSimTime 
  || timtyp == vpiSuppressTime) return(TRUE);
 __vpi_err(1820, vpiError,
  "%s: vpi time type value (%d) illegal", rnam, timtyp);
 return(FALSE);
}

/*
 * validate a vpi value format field
 */
extern int32 __validate_value_fmt(char *rnam, int32 fmt)
{
 switch (fmt) {
  case vpiBinStrVal: case vpiOctStrVal: case vpiHexStrVal:
  case vpiDecStrVal: case vpiScalarVal: case vpiIntVal:
  case vpiRealVal: case vpiStringVal: case vpiVectorVal:
  case vpiStrengthVal: case vpiSuppressVal: case vpiTimeVal:
  case vpiObjTypeVal:
   return(TRUE);
  default:
   __vpi_err(1822, vpiError,
   "%s: vpi value format value (%d) illegal", rnam, fmt);
 }
 return(FALSE);
}

/*
 * vpi internal fatal error 
 */
extern void __vpi_terr(char *fnam, int32 lno)
{
 __vpi_err(303, vpiInternal,
  "VPI INTERNAL ERROR** - source line **%s(%d) - maybe at **%s(%d) or **%s(%d)",
  fnam, lno, __in_fils[__vpifnam_ind], __vpilin_cnt, __in_fils[__sfnam_ind],
  __slin_cnt);
}

/*VARARGS*/
extern void __vpi_err(int32 id_num, int32 level, char *s, ...)
{
 va_list va;

 /* update error counts */
 if (level == vpiNotice) __inform_cnt++;
 else if (level == vpiWarning) __pv_warn_cnt++;
 else if (level == vpiError) __pv_err_cnt++;

 /* by line number suppression means inform or warring never seen */
 /* command line opions ignored here since can be controlled by error */
 /* handler */
 if (level == vpiNotice || level == vpiWarning)
  {
   if (__em_suppr(id_num)) return;
  }

 init_pli_einfo(&__wrk_einfo, level, id_num);
 va_start(va, s);
 vsprintf(__wrk_vpiemsg, s, va);
 va_end(va);
 __wrk_einfo.message = __wrk_vpiemsg;
 __last_eip = &(__wrk_einfo);
 if (__have_vpi_actions) __vpi_plierror_trycall();
}

/*
 * for cbError (called from Cver error routine) fill einfo record
 *
 * in cbError callback user must call vpi chk error to get error info
 */
extern void __cberror_fill_einfo(int32 esev, int32 ernum, char *emsg,
 char *efnam, int32 elcnt)
{
 struct t_vpi_error_info *einfop;

 einfop = &(__wrk_einfo);
 __last_eip = einfop;

 if (__run_state == SS_SIM) einfop->state = vpiRun;
 else einfop->state = vpiCompile; 

 einfop->level = to_vpierr_level(esev);
 einfop->message = emsg;
 /* FIXME - move to initialize routine */
 sprintf(__wrk_vpi_product, "%s%s", __vers, __vers2);

 einfop->product = __wrk_vpi_product;
 einfop->code = __wrk_vpi_errcode;
 sprintf(__wrk_vpi_errcode, "%d", ernum); 

 einfop->file = efnam;
 einfop->line = elcnt;
}


/*
 * convert error message severity to vpi_ error message level
 */
static int32 to_vpierr_level(int32 esev)
{
 switch (esev) {
  case INFORM: return(vpiNotice);
  case WARN: return(vpiWarning);
  case ERROR: return(vpiError);
  case FATAL: return(vpiInternal); 
  default:  __vpi_terr(__FILE__, __LINE__);
 }
 return(vpiInternal);
}

/*
 * initialize constant for Cver and set else values for vpi error info rec
 * when have more types, can pass args here
 */
static void init_pli_einfo(struct t_vpi_error_info *einfop, int32 elev, int32 ernum)
{
 einfop->state = vpiPLI;
 einfop->level = elev;
 einfop->message = __wrk_vpiemsg;

 /* FIXME - move to initialize routine */
 sprintf(__wrk_vpi_product, "%s%s", __vers, __vers2);

 einfop->product = __wrk_vpi_product;
 einfop->code = __wrk_vpi_errcode;
 sprintf(__wrk_vpi_errcode, "%d", ernum); 
 einfop->file = __in_fils[__vpifnam_ind];
 einfop->line = __vpilin_cnt;
} 

/*
 * clear wrk einfo record - can only call after user callback returns
 */
extern void __clear_wrk_einfo(void)
{
 __wrk_einfo.level = 0;
 __wrk_einfo.message = NULL;
 __wrk_einfo.file = NULL;
 __wrk_vpi_timedbl = 0;
}
