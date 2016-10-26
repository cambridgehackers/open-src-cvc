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
 * run time execution routines - assigns, strength and gate evaluation
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdarg.h>
#include <pthread.h>

#include <sys/types.h>
#include <unistd.h>

#ifdef __DBMALLOC__
#include "../malloc.h"
#endif

#include "v.h"
#include "cvmacros.h"

#include "fstapi.h"

/* sytem stuff */
extern int32 errno;

/* local prototypes */
static void set_from_mpp_unopts(struct mod_t *, struct mod_pin_t *, int32);
static void set_from_hconn_unopts(struct mod_t *, struct inst_t *, int32,
 struct expr_t *, struct mod_pin_t *, int32);
static void dbg_unopt_msg(struct mod_t *, struct mod_pin_t *, int32, char *);
static void dbg_unopt2_msg(struct mod_t *, struct inst_t *, int32,
 struct mod_pin_t *, int32, char *);
static void std_downtomdport(struct expr_t *, struct expr_t *,
 struct itree_t *);
static void prt_assignedto_val(struct expr_t *, char *);
static void multfi_acc_downtomdport( struct expr_t *, struct expr_t *,
 struct itree_t *);
static void stacc_downtomdport(struct expr_t *, struct expr_t *,
 struct itree_t *);
static void stbsel_acc_downtomdport(struct expr_t *, struct expr_t *,
 struct itree_t *);
static void acc_downtomdport(struct expr_t *, struct expr_t *,
 struct itree_t *);
static void bsel_acc_downtomdport(struct expr_t *, struct expr_t *,
 struct itree_t *);
static void std_uptoiconn(struct expr_t *, struct expr_t *, struct itree_t *);
static void multfi_acc_uptoiconn(struct expr_t *, struct expr_t *,
 struct itree_t *);
static void stacc_uptoiconn(struct expr_t *, struct expr_t *,
 struct itree_t *);
static void stbsel_acc_uptoiconn(struct expr_t *, struct expr_t *,
 struct itree_t *);
static void acc_uptoiconn(struct expr_t *, struct expr_t *,
 struct itree_t *);
static void bsel_acc_uptoiconn(struct expr_t *, struct expr_t *,
 struct itree_t *);
static void ldcomb_driver(struct xstk_t *, struct net_t *, struct net_pin_t *);
static word32 widegate_ld_bit(word32 *, int32, int32);
static void ldcomb_stdriver(byte *, struct net_t *, struct net_pin_t *);
static struct xstk_t *init_stwire_accum(struct net_t *);
static struct xstk_t *ld_stgate_driver(struct net_pin_t *);
static struct xstk_t *ld_stconta_driver(struct net_pin_t *);
static struct xstk_t *ld_stvpiputv_driver(struct net_pin_t *);
static struct xstk_t *ld_sticonn_up_driver(struct net_pin_t *);
static struct xstk_t *ld_pb_sticonn_up_driver(struct net_pin_t *);
static struct xstk_t *ld_stmodport_down_driver(struct net_pin_t *);
static struct xstk_t *ld_pb_stmodport_down_driver(struct net_pin_t *);
static struct xstk_t *ld_stpull_driver(struct net_pin_t *);
static void ndst_eval2_xpr(byte *, struct expr_t *);
static void access_stpsel(byte *, struct expr_t *);
static void access_width_index_stpsel(byte *, struct expr_t *);
static void rhs_stconcat(byte *, struct expr_t *);
static void adds_evgate_ins(word32 *, word32 *, int32);
static void show2_allvars(struct itree_t *);
static void showvars_dmp_mda_arr(struct net_t *, int32);
static void unmap_arri_to_ndxnums(int32, struct net_t *, int32 *);
static char *bld_mda_index_label(char *, struct net_t *, int32 *);
static void emit1_driver(struct net_t *, struct net_pin_t *, int32);
static char *drive_tostr(char *, word32 *, word32 *, struct net_pin_t *,
 int32, int32);
static char *stdrive_tostr(char *, byte *, struct net_pin_t *, int32, int32);
static char *bld_wire_telltale(char *, struct net_t *);
static void emit1_load(struct net_t *, struct net_pin_t *);
static struct mdvmast_t *alloc_mdvmast(void);
static int32 *build_mda_indices(struct expr_t *, struct mda_t *, int32);
static void add_mdvp_for_each_array_element(struct net_t *, t_midat *);
static void setup_all_dvars(void);
static void setup_1argdvars(struct mdvmast_t *);
static void setup_1subtree_allvars(struct itree_t *, int32);
static void setup_1installvars(struct mod_t *, struct itree_t *);
static void turnon_1net_dmpv(struct net_t *, struct itree_t *,
 struct task_t *, struct mod_t *, int32, int32);
static void wr_1argdvhdr(struct mdvmast_t *);
static void wr_1subtree_allvars(struct itree_t *, int32);
static void wr_1inst_dvhdrs(struct itree_t *);
static void wr_tasks_dvhdrs(struct itree_t *, struct symtab_t *);
static char *to_dvtsktyp(char *, word32);
static void wr_fromtop_iscopeto(struct itree_t *);
static void wr_totop_iscopeback(struct itree_t *);
static void wr_tskscopeto(struct symtab_t *);
static void wr_tskscopeback(struct symtab_t *);
static void wr_1vectored_dvdef(struct net_t *, char *, t_midat *, int32, 
 int32 *);
static void wr_1vectored_dvdef_array(struct net_t *, struct itree_t *);
static int32 can_dump_entire_array(struct net_t *);
static void dump_allvars_vals(void);
static void dmp_insts_ofwire(struct mod_t *, struct net_t *);
static void dmp_insts_ofwire_array(struct mod_t *, struct net_t *);
static void bld1_xdvval(struct net_t *, char *);
static void dmpv_sdispb(word32 *ap, word32 *bp, int32);
static void dmpv_sdispb_1w(word32, word32, int32);
static void dmpv_sdispb_2state(word32 *ap, int32);
static void dmpv_sdispb_1w_2state(word32, int32);
static void set_dmpv_bld_func(struct net_t *);
static void bld1_dmpv_event(struct net_t *, t_midat *);
static void bld1_dmpv_real(struct net_t *, t_midat *);
static void bld1_dmpv_real_array(struct net_t *, t_midat *);
static void bld1_dmpv_vector_1w(struct net_t *, t_midat *);
static void bld1_dmpv_vector_notpacked_1w_array(struct net_t *, t_midat *);
static void bld1_dmpv_vector_1w_packed_array(struct net_t *, t_midat *);
static void bld1_dmpv_vector_wide(struct net_t *, t_midat *);
static void bld1_dmpv_vector_wide_array(struct net_t *, t_midat *);
static void bld1_dmpv_vector_svec(struct net_t *, t_midat *);
static void bld1_dmpv_scalar(struct net_t *, t_midat *);
static void bld1_dmpv_scalar_array(struct net_t *, t_midat *);
static void bld1_dmpv_vector_2state_wide_array(struct net_t *, t_midat *); 
static void bld1_dmpv_vector_2state_1w_array(struct net_t *, t_midat *); 
static void bld1_dmpv_vector_2state_wide(struct net_t *, t_midat *); 
static void bld1_dmpv_vector_2state_1w(struct net_t *, t_midat *); 
static void bld1_dmpv_scalar_2state_array(struct net_t *, t_midat *); 
static void dv_wr(int32);
static char *to_dvtimstr(char *, word64);
static void access_stbsel(byte *, struct expr_t *);

static void fst_setup(void);
static char *fst_to_timunitnam(char *, word32);
static void fst_1argdvhdr(struct mdvmast_t *);
static void fst_tskscopeback(struct symtab_t *);
static void fst_tskscopeto(struct symtab_t *);
static void fst_totop_iscopeback(struct itree_t *);
static void fst_fromtop_iscopeto(struct itree_t *);
static void fst_1subtree_allvars(struct itree_t *, int32);
static void fst_1inst_dvhdrs(struct itree_t *);
static void fst_create_vars(struct net_t *, t_midat *, int32, 
 struct mdvmast_t *);
static void fst_create_one_var(struct net_t *, t_midat *, struct dvchgnets_t *,
 int32, int32, int32, int32);
static const char *fst_rmv_dollar_module_name(const char *); // AJB
static enum fstVarDir fst_dir_type(int32); // AJB
static enum fstVarType fst_net_type(int32);
static void fst_insts_ofwire(struct mod_t *, struct net_t *, int32);
static void fst_insts_ofwire_array(struct mod_t *, struct net_t *, int32);
static void fst_set_time(void);
static void fst_tasks_dvhdrs(struct itree_t *, struct symtab_t *);
static enum fstScopeType fst_dvtsktyp(word32);
static void *fst_writer_thread(void *);

static void fst_dmpv_sdispb(word32 *, word32 *, int32);
static void fst_dmpv_sdispb_1w(word32, word32, int32);
static void fst_dmpv_sdispb_2state(word32 *, int32);
static void fst_dmpv_sdispb_1w_2state(word32, int32);
static void fst_set_dmpv_bld_func(struct net_t *);
static void fst_set_dmpv_bld_func_thrd(struct net_t *);

static void fst_bld1_dmpv_event(struct net_t *, t_midat *);
static void fst_bld1_dmpv_real(struct net_t *, t_midat *);
static void fst_bld1_dmpv_vector_1w(struct net_t *, t_midat *);
static void fst_bld1_dmpv_vector_wide(struct net_t *, t_midat *);
static void fst_bld1_dmpv_vector_svec(struct net_t *, t_midat *);
static void fst_bld1_dmpv_scalar(struct net_t *, t_midat *);
static void fst_bld1_dmpv_real_array(struct net_t *, t_midat *);
static void fst_bld1_dmpv_vector_notpacked_1w_array(struct net_t *, t_midat *);
static void fst_bld1_dmpv_vector_1w_packed_array(struct net_t *, t_midat *);
static void fst_bld1_dmpv_vector_wide_array(struct net_t *, t_midat *);
static void fst_bld1_dmpv_scalar_array(struct net_t *, t_midat *);
static void fst_bld1_dmpv_vector_2state_wide_array(struct net_t *, 
 t_midat *); 
static void fst_bld1_dmpv_vector_2state_1w_array(struct net_t *, t_midat *); 
static void fst_bld1_dmpv_vector_2state_wide(struct net_t *, t_midat *); 
static void fst_bld1_dmpv_vector_2state_1w(struct net_t *, t_midat *); 
static void fst_bld1_dmpv_scalar_2state_array(struct net_t *, t_midat *); 

/* thread version of the same */
static void fst_bld1_dmpv_event_thrd(struct net_t *, t_midat *, 
 struct dmp_buf_t *);
static void fst_bld1_dmpv_real_thrd(struct net_t *, t_midat *, 
 struct dmp_buf_t *);
static void fst_bld1_dmpv_vector_1w_thrd(struct net_t *, t_midat *, 
 struct dmp_buf_t *);
static void fst_bld1_dmpv_vector_wide_thrd(struct net_t *, t_midat *, 
 struct dmp_buf_t *);
static void fst_bld1_dmpv_vector_svec_thrd(struct net_t *, t_midat *, 
 struct dmp_buf_t *);
static void fst_bld1_dmpv_scalar_thrd(struct net_t *, t_midat *, 
 struct dmp_buf_t *);
static void fst_bld1_dmpv_real_array_thrd(struct net_t *, t_midat *, 
 struct dmp_buf_t *);
static void fst_bld1_dmpv_vector_notpacked_1w_array_thrd(struct net_t *, 
 t_midat *, struct dmp_buf_t *);
static void fst_bld1_dmpv_vector_1w_packed_array_thrd(struct net_t *, 
 t_midat *, struct dmp_buf_t *);
static void fst_bld1_dmpv_vector_wide_array_thrd(struct net_t *, t_midat *, 
 struct dmp_buf_t *);
static void fst_bld1_dmpv_scalar_array_thrd(struct net_t *, t_midat *, 
 struct dmp_buf_t *);
static void fst_bld1_dmpv_vector_2state_wide_array_thrd(struct net_t *, 
 t_midat *, struct dmp_buf_t *); 
static void fst_bld1_dmpv_vector_2state_1w_array_thrd(struct net_t *, 
 t_midat *, struct dmp_buf_t *); 
static void fst_bld1_dmpv_vector_2state_wide_thrd(struct net_t *, t_midat *, 
 struct dmp_buf_t *); 
static void fst_bld1_dmpv_vector_2state_1w_thrd(struct net_t *, t_midat *, 
 struct dmp_buf_t *); 
static void fst_bld1_dmpv_scalar_2state_array_thrd(struct net_t *, t_midat *, 
 struct dmp_buf_t *); 

extern void __fst_do_vars_chg(void);
extern void __fst_do_vars_chg_parallel(void);
extern void __fst_do_vars_baseline(char *, int32);
extern void __fst_close(void);

static struct dpinstel_t *alloc_dpinstel(void);
static void free_dpinst_lst(struct dpinstel_t *);
static void init_dp_fildesc(struct dp_fildesc_t *);
static int32 dpfildesc_ndx_from_fnam(char *);
static void chk_set_dp_limits(struct dp_fildesc_t *, word32);
static void chk_set_dp_on(struct dp_fildesc_t *);
static void chk_set_dp_off(struct dp_fildesc_t *);
static void wr_1inst_dp_scope_and_def(struct dp_fildesc_t *,
 struct dpinstel_t *);
static void turn_on_1inst_dumpports(struct dpinstel_t *);
static void wr_1inst_allports_dphdrs(struct dp_fildesc_t *, t_midat *);
static void wr_1vectored_dpdef(struct dp_fildesc_t *, struct net_t *, char *);
static void dp_wr(struct dp_fildesc_t *, int32);
static void wr_fromtop_iscopeto_ports(struct dp_fildesc_t *, t_midat *);
static void wr_totop_iscopeback_ports(struct dp_fildesc_t *, t_midat *);
static void dump_1inst_allports_vals(struct dpinstel_t *);
static void dmp_one_dp_val(struct dpinstel_t *, struct net_t *);
static void bld1_scal_dpval(struct dpinstel_t *, struct net_t *, char *);
static void bld1_vec_dpval(struct dpinstel_t *, struct net_t *, char *);
static void bld1_scal_dpval(struct dpinstel_t *, struct net_t *, char *);
static void bld1_xdpval(struct net_t *, char *);
static void bld1_xdpval(struct net_t *, char *);
static char bld_1bit_dptriple(int32 *, int32 *, struct dpinstel_t *,
 struct net_t *, int32);
static char eval_st_1drvr(int32 *, int32 *, struct net_t *, int32, t_midat *,
  int32);
static char eval_in_1drvr(int32 *, int32 *, struct net_t *, int32, t_midat *);
static char eval_out_1drvr(int32 *, int32 *, struct net_t *, int32, t_midat *);
static void dp_set_cnt_driving_vals(int32 *, int32 *, struct dpctrl_t *,
 int32, int32);
static word32 dp_ld_stdriver(int32, struct net_pin_t *);
static word32 dp_ld_driver(int32, struct net_pin_t *);

static void bld_instel_dumpports_eval_ds(struct dpinstel_t *);
static void set_1bit_dp_eval_type(struct net_t *, struct dpctrl_t *);
static void init_1bit_dpctrl_rec(struct dpctrl_t *);
static void bld_1inst_dpctrl_lists(struct dpinstel_t *, struct mod_t *);
static int32 drvr_netbit_vtx_is_hiconn(struct itree_t *, struct itree_t *);
static void linkin_pb_npp_drvr(struct dpctrl_t *, struct itree_t *,
 struct net_pin_t *, int32, int32);
static void init_dpdrv(struct dpdrvr_t *);
static void dmp1_fildesc(struct dp_fildesc_t *); 
static void dmp1_dpinstel(struct dpinstel_t *);
static void dmp1_dpctrl_rec(struct dpctrl_t *, struct mod_t *, struct net_t *,
 int32);
static char *dp_evaltyp_to_str(char *, int32);

/* extern prototypes (maybe defined in this module) */
extern void __set_mpp_assign_routines(void);
extern void __set_pb_mpp_assign_routines(void);
extern void __set_mpp_aoff_routines(void);
extern void __vpi_set_downtomdport_proc(struct mod_pin_t *, struct net_t *);
extern void __vpi_set_upiconnport_proc(struct mod_pin_t *);
extern void __init_instdownport_contas(struct itree_t *, struct itree_t *);
extern void __init_instupport_contas(struct itree_t *);
extern void __mdr_assign_or_sched(struct expr_t *);
extern void __assign_1mdrwire(struct net_t *);
extern void __sched_1mdrwire(struct net_t *);
extern struct xstk_t *__load_mdrwire(struct net_t *);
extern struct itree_t *__get_npprefloc(struct net_pin_t *);
extern struct xstk_t *__ld_wire_driver(struct net_pin_t *);
extern struct xstk_t *__ld_tfrwarg_driver(struct net_pin_t *);
extern struct xstk_t *__ld_conta_driver(struct net_pin_t *);
extern struct xstk_t *__ld_vpiputv_driver(struct net_pin_t *);
extern struct xstk_t *__ld_gate_driver(struct net_pin_t *);
extern struct xstk_t *__ld_iconn_up_driver(struct net_pin_t *);
extern struct xstk_t *__ld_pb_iconn_up_driver(struct net_pin_t *);
extern struct xstk_t *__ld_modport_down_driver(struct net_pin_t *);
extern struct xstk_t *__ld_pb_modport_down_driver(struct net_pin_t *);

extern word32 __ld_gate_out(struct gate_t *, int32 *);
extern void __eval_wire(word32 *, word32 *, struct net_t *,
 struct net_pin_t *); 
extern void __eval_wide_wire(word32 *, word32 *, word32 *, word32 *, int32,
 word32);
extern void __eval_1w_nonstren(word32 *, word32 *, word32, word32,
 word32);
extern struct xstk_t *__stload_mdrwire(struct net_t *);
extern struct xstk_t *__ld_stwire_driver(struct net_pin_t *);
extern struct xstk_t *__ld_sttfrwarg_driver(struct net_pin_t *);
extern struct xstk_t *__ndst_eval_xpr(struct expr_t *);
extern int32 __get_itp_const_bselndx(struct expr_t *);
extern int32 __get_idp_const_bselndx(struct expr_t *);
extern void __st_standval(byte *, struct xstk_t *, byte);
extern void __eval_stwire(byte *, word32, int32, int32, byte *);
extern word32 __comb_1bitsts(word32, word32, word32);
extern char *__gstate_tostr(char *, struct gate_t *, int32);
extern void __show_allvars(void);
extern void __emit_1showvar(struct net_t *, struct gref_t *);
extern char *__bld_valofsched(char *, struct tev_t *);
extern char *__bld_showvars_prefix(char *, struct net_t *, struct gref_t *);
extern void __exec_dumpvars(struct expr_t *, int32);
extern void __setup_dmpvars(void);
extern void __do_dmpvars_baseline(char *);
extern void __do_dmpvars_chg(void);
extern int32 __cnt_dcelstels(struct dcevnt_t *);
extern char *__to_dvcode(char *, int32);

extern void __setup_1file_dmpports(struct dp_fildesc_t *);
extern void __turnon_1file_all_dumpports(struct dp_fildesc_t *);
extern void __turnoff_1file_all_dumpports(struct dp_fildesc_t *);
extern void __do_dmpports_chg(struct dp_fildesc_t *);
extern void __do_dmpports_baseline(struct dp_fildesc_t *, char *);
extern void __my_dp_flush(struct dp_fildesc_t *);
extern void __cleanup_dumpports(void); 
extern void __wr_vcdclose_section(struct dp_fildesc_t *);

extern char *__to_ptnam(char *, word32);
extern char *__to_mpnam(char *, char *);
extern char *__bld_lineloc(char *, word32, int32);
extern void __strenwiden_sizchg(struct xstk_t *, int32);
extern struct xstk_t *__eval2_xpr(struct expr_t *);
extern void __sgn_xtnd_widen(struct xstk_t *, int32);
extern void __sizchg_widen(struct xstk_t *, int32);
extern void __narrow_sizchg(struct xstk_t *, int32);
extern void __fix_widened_toxs(struct xstk_t *, int32);
extern void __stren_exec_ca_concat(struct expr_t *, byte *, int32);
extern void __exec_conta_assign(struct expr_t *, word32 *, word32 *, int32);
extern void __exec_ca_concat(struct expr_t *, word32 *, word32 *, int32);
extern char *__msgexpr_tostr(char *, struct expr_t *);
extern char *__to_gassign_str(char *, struct expr_t *);
extern void __ld_perinst_val(word32 *, word32 *, union pck_u, int32);
extern void __ld_val(word32 *, word32 *, word32 *, int32);
extern void __grow_xstk(void);
extern void __chg_xstk_width(struct xstk_t *, int32);
extern void __lhsbsel(word32 *, int32, word32);
extern void __my_free(void *, size_t);
extern char *__my_malloc(size_t);
extern char *__pv_stralloc(char *);
extern char *__to_vvstnam(char *, word32);
extern char *__to_vvnam(char *, word32);
extern char *__to_timstr(char *, word64 *);
extern int32 __correct_forced_newwireval(struct net_t *, word32 *, word32 *);
extern void __chg_st_val(struct net_t *, word32 *, word32 *);
extern void __ld_wire_val_xstk(struct xstk_t *, struct net_t *);
extern void __ld_wire_val_wrds(word32 *, word32 *, struct net_t *);
extern void __ld_stval(word32 *, word32 *, byte *, int32);
extern int32 __comp_ndx(struct net_t *, struct expr_t *);
extern int32 __compute_mda_index(struct mda_t *, struct net_t *, 
 struct expr_t *, int32, struct expr_t **);
extern int32 __comp_mda_dim_ndx(struct mda_t *, struct expr_t *, int32);
extern void __getarr_range_mda(struct net_t *, int32 *, int32 *, int32 *, 
 int32);
extern void __ld_bit(word32 *, word32 *, struct net_t *, int32);
extern int32 __forced_inhibit_bitassign(struct net_t *, struct expr_t *,
 struct expr_t *);
extern void __assign_to_bit(struct net_t *, struct expr_t *, struct expr_t *,
 word32 *, word32 *);
extern t_midat *__xmrget_refgrp_to_targ(struct gref_t *);
extern int32 __has_vpi_driver(struct net_t *np, struct net_pin_t *npp);
extern int32 __update_tran_harddrvs(struct net_t *);
extern void __eval_tran_bits(struct net_t *);
extern void __ld_addr(word32 **, word32 **, struct net_t *);
extern void __st_val(struct net_t *, word32 *, word32 *, int32);
extern char *__st_regab_tostr(char *, byte *, int32);
extern char *__regab_tostr(char *, word32 *, word32 *, int32, int32, int32);
extern void __pth_stren_schd_allofwire(struct net_t *, byte *, int32);
extern void __wdel_stren_schd_allofwire(struct net_t *, byte *,
 int32);
extern void __pth_schd_allofwire(struct net_t *, word32 *,
 word32 *, int32);
extern void __wdel_schd_allofwire(struct net_t *, word32 *, word32 *, int32);
extern void __rhspsel(word32 *, word32 *, int32, int32);
extern void __lhspsel(word32 *, int32, word32 *, int32);
extern char *__to_wtnam(char *, struct net_t *);
extern char *__to_wtnam2(char *, word32);
extern void __adds(char *);
extern void __chg_xprline_size(int32);
extern void __disp_itree_idp_path(t_midat *, struct task_t *);
extern void __ld_gate_wide_val(word32 *, word32 *, word32 *, int32);
extern void __trunc_cstr(char *, int32, int32);
extern char *__msg2_blditree(char *, struct itree_t *);
extern int32 __get_arrwide(struct net_t *);
extern char *__var_tostr(char *, struct net_t *, int32, int32, int32);
extern void __disp_var(struct net_t *, int32, int32, int32, char);
extern int32 __unnormalize_ndx(struct net_t *, int32);
extern int32 __unnormalize2_ndx(int32, int32, int32);
extern void __get_cor_range(int32, union intptr_u, int32 *, int32 *);
extern void __getarr_range(struct net_t *, int32 *, int32 *, int32 *);
extern void __getwir_range(struct net_t *, int32 *, int32 *);
extern int32 __unmap_ndx(int32, int32, int32);
extern char *__schop(char *, char *);
extern char *__get_tfcellnam(struct tfrec_t *);
extern int32 __vval_isallzs(word32 *, word32 *, int32);
extern int32 __vval_isall_xs(word32 *, word32 *, int32);
extern int32 __bin_trim_abval(word32 *, word32 *, int32);
extern int32 __st_vval_isallzs(byte *, int32);
extern char *__to_wrange(char *, struct net_t *);
extern char *__to_arr_range(char *, struct net_t *);
extern char *__to1_stren_nam(char *, int32, int32);
extern int32 __fr_cap_size(int32);
extern void __bld_forcedbits_mask(word32 *, struct net_t *);
extern int32 __wide_vval_is0(word32 *, int32);
extern struct itree_t *__match_targ_to_ref(word32, struct gref_t *);
extern char *__to_tcnam(char *, word32);
extern int32 __get_eval_word(struct expr_t *, word32 *);
extern int32 __ip_indsrch(char *);
extern char *__to_timunitnam(char *, word32);
extern char *__msg_blditree(char *, struct itree_t *, struct task_t *);
extern int32 __trim1_0val(word32 *, int32);
extern struct task_t *__getcur_scope_tsk(void);
extern void __add_nchglst_el(struct net_t *);
extern void __add_dmpv_chglst_el(struct net_t *);
extern void __add_dmpv_chglst_el_sel(struct net_t *, int32);
extern void __add_dp_chglst_el(struct net_t *);
extern void __add_togglelst_el(struct net_t *);
extern void __wakeup_delay_ctrls(struct net_t *, int32, int32);
extern char *__to_npptyp(char *, struct net_pin_t *);
extern struct net_t *__get_indexed_psel_range(struct expr_t *, int32 *, 
 int32 *);
extern char *__get_eval_cstr(struct expr_t *, int32 *);
extern void __my_close(int32);
extern void __dmp1_nplstel(struct mod_t *, struct net_t *, struct net_pin_t *);
extern int32 __bld_xl_drvld_vtxtab(struct net_t *, int32, struct itree_t *,
 int32);
extern void __get_bidnpp_sect(struct net_t *, struct net_pin_t *, int32 *,
 int32 *);
extern int32 __is_net_dumped(struct net_t *);

extern void __cv_msg(char *, ...);
extern void __pv_err(int32, char *, ...);
extern void __cvsim_msg(char *, ...);
extern void __tr_msg(char *, ...);
extern void __sgfwarn(int32, char *, ...);
extern void __pv_warn(int32, char *, ...);
extern void __gfwarn(int32, word32, int32, char *, ...);
extern void __sgferr(int32, char *, ...);
extern void __dbg_msg(char *, ...);
extern void __sgfinform(int32, char *, ...);
extern void __arg_terr(char *, int32);
extern void __case_terr(char *, int32);
extern void __misc_terr(char *, int32);

extern void __process_gatechg_ev(void);
extern void __process_mipd_nchg_ev(void);
extern void __process_conta_ev(void);
extern void __process_trpthdst_ev(void);
extern void __process_wire_ev(void);

extern const word32 __masktab[];
extern const byte __stren_map_tab[];
extern const word32 __cap_to_stren[];

static int32 __dvars_array_ndx = -1; /* the local dumpvars array index */

/*
 * ROUTINES TO SET PORT ASSIGN
 */

/*
 * set module port assign routines (type of acceleration)
 */ 
extern void __set_mpp_assign_routines(void)
{
 int32 pi, ii, pnum;
 struct mod_pin_t *mpp;
 struct mod_t *mdp, *imdp;
 struct inst_t *ip;
 struct expr_t *xp;

 /* step 1: set the - down from iconn to mod port from module ports */
 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   if ((pnum = mdp->mpnum) == 0) continue;

   /* SJM - PORT REMOVE */
   /* for top module set assign routine to nil - will force early core dump */
   /* if error */
   if (mdp->minstnum == 0)
    {
     /* leave port assign routines as nil for top level */
     for (pi = 0; pi < mdp->mpnum; pi++) 
      { mpp = &(mdp->mpins[pi]); mpp->assgnfunc_set = TRUE; }
     continue;
    }

   for (pi = 0; pi < mdp->mpnum; pi++) 
    {
     mpp = &(mdp->mpins[pi]);

     /* never have NP ICONN or NP MDPRT for inout */
     if (mpp->mptyp == IO_BID) { mpp->assgnfunc_set = TRUE; continue; }

     /* need iconn lhs info for setting output assign routines */
     if (mpp->mptyp == IO_OUT) continue;


     set_from_mpp_unopts(mdp, mpp, -1);
    }
  }
 /* step 2: look at all up instance connections to see if can optimize */ 
 /* can only be down after all low conn mod ports processed in step 1 */
 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   /* first process all instances in module */
   for (ii = 0; ii < mdp->minum; ii++)
    {
     ip = &(mdp->minsts[ii]);
     imdp = ip->imsym->el.emdp;
     if ((pnum = imdp->mpnum) == 0) continue;

     for (pi = 0; pi < pnum; pi++)
      {
       mpp = &(imdp->mpins[pi]);
       if (mpp->assgnfunc_set)
        {
         /* if assgn func set turned on, must not try to optimize more */
         continue;
        }

       /* port (either in or out) down must be simple ID for any accelerate */
       if (mpp->mpref->optyp != ID)  
        {
         if (__debug_flg)
          dbg_unopt2_msg(imdp, ip, pi, mpp, -1, "port is expression");
         if (mpp->mptyp == IO_IN)
          mpp->mpaf.mpp_downassgnfunc = std_downtomdport;
         else mpp->mpaf.mpp_upassgnfunc = std_uptoiconn;
         mpp->assgnfunc_set = TRUE;
         continue;
        }

       /* if assign not know, down must be simple wire */
       xp = ip->ipins[pi];

       /* set the best possible optimization routine from highconn */
       set_from_hconn_unopts(imdp, ip, pi, xp, mpp, -1);
      }
    }
  } 
}

/*
 * set decomposed from hconn concat per bit mod port assign routines
 * i.e. set type of acceleration for interpreter
 *
 * -O does much better job of optimizing these
 */ 
extern void __set_pb_mpp_assign_routines(void)
{
 int32 pi, ii, pbi;
 int32 pnum;
 struct mod_pin_t *mpp;
 struct mod_pin_t *mast_mpp;
 struct mod_t *mdp, *imdp;
 struct inst_t *ip;
 struct expr_t *xp;

 /* step 1: set the - down from iconn to mod port from module ports */
 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   if ((pnum = mdp->mpnum) == 0) continue;

   /* no top level ports do not have any highconn - so never decomposed */
   if (mdp->minstnum == 0) continue;

   for (pi = 0; pi < mdp->mpnum; pi++) 
    {
     mast_mpp = &(mdp->mpins[pi]);
     if (!mast_mpp->has_scalar_mpps) continue; 

     for (pbi = 0; pbi < mast_mpp->mpwide; pbi++)
      {
       mpp = &(mast_mpp->pbmpps[pbi]);
       
       /* need iconn lhs info for setting output assign routines */
       if (mpp->mptyp == IO_OUT) continue;
       set_from_mpp_unopts(mdp, mpp, pbi);
      }
    }
  }
 /* step 2: look at all up instance connections to see if can optimize */ 
 /* can only be down after all low conn mod ports processed in step 1 */
 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   /* first process all instances in module */
   for (ii = 0; ii < mdp->minum; ii++)
    {
     ip = &(mdp->minsts[ii]);
     imdp = ip->imsym->el.emdp;
     if ((pnum = imdp->mpnum) == 0) continue;

     for (pi = 0; pi < pnum; pi++)
      {
       mast_mpp = &(imdp->mpins[pi]);
       /* if low conn of this high conn not dcomposed into per bit, done */
       if (!mast_mpp->has_scalar_mpps) continue; 

       /* if this one's up iconn not separable - ignore for setting accel */
       if (ip->pb_ipins_tab == NULL || ip->pb_ipins_tab[pi] == NULL)
        continue;

       for (pbi = 0; pbi < mast_mpp->mpwide; pbi++)
        {
         mpp = &(mast_mpp->pbmpps[pbi]);
         if (mpp->assgnfunc_set) continue;

         /* LOOKATME ??? - down will almost always be bsel for these */ 
         /* port (in or out) down must be simple ID for any accelerate */
         if (mpp->mpref->optyp != ID)  
          {
           if (__debug_flg)
            dbg_unopt2_msg(imdp, ip, pi, mpp, pbi,
             "per bit port is expression");

           if (mpp->mptyp == IO_IN)
            mpp->mpaf.mpp_downassgnfunc = std_downtomdport;
           else mpp->mpaf.mpp_upassgnfunc = std_uptoiconn;
           mpp->assgnfunc_set = TRUE;

           continue;
          }

         /* if assign not know, down must be simple wire */
         xp = ip->pb_ipins_tab[pi][pbi];
         /* set the best possible optimization routine from highconn */
         set_from_hconn_unopts(imdp, ip, pi, xp, mpp, pbi);
        }
      }
    }
  } 
}

/*
 * set ports that can't be optimized determinable only from down mpp
 * also sets input port fi>1 down assign since independent of iconn 
 *
 * if pbi not -1 then this is bit of per bit decomposed input port
 */
static void set_from_mpp_unopts(struct mod_t *mdp, struct mod_pin_t *mpp,
 int32 pbi)
{
 struct net_t *down_np;

 if (mpp->mpref->optyp != ID)
  {  
   if (__debug_flg) dbg_unopt_msg(mdp, mpp, pbi, "port is expression");
   mpp->mpaf.mpp_downassgnfunc = std_downtomdport;
   mpp->assgnfunc_set = TRUE;
   return;
  }
 down_np = mpp->mpref->lu.sy->el.enp;
 /* path destinations are stored as delay wires */
 if (down_np->ntraux != NULL || down_np->nrngrep == NX_DWIR)
  {
   if (__debug_flg)
    dbg_unopt_msg(mdp, mpp, pbi, "port in tran chan., delay or path dest.");
   mpp->mpaf.mpp_downassgnfunc = std_downtomdport;
   mpp->assgnfunc_set = TRUE;
   return;
  }
 /* if port wire multfi - all will be so now know fits fi>1 acc case */
 if (down_np->n_multfi)
  {
   if (__debug_flg) dbg_unopt_msg(mdp, mpp, pbi,
    "port fi>1 - optimized some");
   mpp->mpaf.mpp_downassgnfunc = multfi_acc_downtomdport;
   mpp->assgnfunc_set = TRUE;
  }
}

/*
 * set optimized routines from high conn iconn info
 *
 * uses up iconn expr info and optimize info set in step 1 mpp processing 
 * know down is simple ID or not called 
 *
 * works for both normal ports and per bit decomposed input ports
 * from concat high conns where pbi is bit, and xp/mpp are per bit decomposed
 */
static void set_from_hconn_unopts(struct mod_t *imdp, struct inst_t *ip,
 int32 pi, struct expr_t *xp, struct mod_pin_t *mpp, int32 pbi)
{
 struct net_t *up_np, *down_np;

 down_np = mpp->mpref->lu.sy->el.enp;
 /* always non acc if not same width */
 if (mpp->mpref->szu.xclen != xp->szu.xclen)
  {
   if (__debug_flg) dbg_unopt2_msg(imdp, ip, pi, mpp, pbi, "widths differ");
set_unoptim:
   if (mpp->mptyp == IO_IN) mpp->mpaf.mpp_downassgnfunc = std_downtomdport;
   else mpp->mpaf.mpp_upassgnfunc = std_uptoiconn;
   mpp->assgnfunc_set = TRUE;
   return;
  }
 if (mpp->mptyp == IO_IN)
  {
   /* down input port assign, know port lhs is optimizable */
   /* make sure rhs up iconn optimizable */
   if (xp->optyp == ID)
    {
     up_np = xp->lu.sy->el.enp;
     /* both up and down must be have or not have stren */
     if ((up_np->n_stren && !down_np->n_stren)
      || (!up_np->n_stren && down_np->n_stren))
      { 
       if (__debug_flg) dbg_unopt2_msg(imdp, ip, pi, mpp, pbi,
        "strength needed differs");
       goto set_unoptim;
      }  
     if (down_np->n_stren) 
      {
       if (xp->szu.xclen == 1) 
        mpp->mpaf.mpp_downassgnfunc = stbsel_acc_downtomdport;
       else mpp->mpaf.mpp_downassgnfunc = stacc_downtomdport;
       return;
      }
     /* non strength ID case */  
     if (xp->szu.xclen == 1)
      mpp->mpaf.mpp_downassgnfunc = bsel_acc_downtomdport;
     else mpp->mpaf.mpp_downassgnfunc = acc_downtomdport;
     return;
    }
   /* bit select for this up iconn case */
   /* SJM 07/24/03 - bit select from XMR high conn must not be optimized */
   if (xp->optyp != LSB || xp->lu.x->optyp != ID
    || mpp->mpref->szu.xclen != 1)
    {   
     if (__debug_flg)
      dbg_unopt2_msg(imdp, ip, pi, mpp, pbi,
       "vector port but not bit select from ID highconn");
     goto set_unoptim;
    } 
   /* maybe up bit select or scalar - must be constant index */
   if (xp->ru.x->optyp != NUMBER)
    {
     if (__debug_flg)
      dbg_unopt2_msg(imdp, ip, pi, mpp, pbi, "bit select highconn expr.");
     goto set_unoptim;
    }
   up_np = xp->lu.x->lu.sy->el.enp;
   /* both must be same strength */
   if ((up_np->n_stren && !down_np->n_stren)
    || (!up_np->n_stren && down_np->n_stren))
    {  
     if (__debug_flg)
      dbg_unopt2_msg(imdp, ip, pi, mpp, pbi, "bsel strength needed differs");
     goto set_unoptim;
    }
   /* may reduce optimlzation level to bsel form */ 
   if (down_np->n_stren)
    mpp->mpaf.mpp_downassgnfunc = stbsel_acc_downtomdport;
   else mpp->mpaf.mpp_downassgnfunc = bsel_acc_downtomdport;
   return;
  }

 /* hard output port case - assign to varying up iconns */ 
 /* know mod port is ID and widths same or will not get here */
 if (xp->optyp == ID) up_np = xp->lu.sy->el.enp; 
 else if (xp->optyp == LSB) up_np = xp->lu.x->lu.sy->el.enp;
 /* no debug message needed here because assign never happens */
 else if (xp->optyp == OPEMPTY) goto set_unoptim;
 else
  {
   if (__debug_flg)
    dbg_unopt2_msg(imdp, ip, pi, mpp, pbi, "iconn not bsel or wire");
   goto set_unoptim;
  }

 /* cannot have delay (also path dest.) or be in tran channel */
 if (up_np->nrngrep == NX_DWIR || up_np->ntraux != NULL)
  {
   if (__debug_flg)
    dbg_unopt2_msg(imdp, ip, pi, mpp, pbi,
    "iconn in tran chan or delay/path dest.");
   goto set_unoptim;
  }
 if (up_np->n_multfi)
  {
   if (mpp->mpaf.mpp_upassgnfunc == NULL)
    { mpp->mpaf.mpp_upassgnfunc = multfi_acc_uptoiconn; return; }
   /* if some instance connections, fi>1 and other not, not acc */ 
   if (mpp->mpaf.mpp_upassgnfunc != multfi_acc_uptoiconn)
    goto mixed_multfi;
   return;
  }
 if (mpp->mpaf.mpp_upassgnfunc == multfi_acc_uptoiconn)
  {
mixed_multfi:
   if (__debug_flg)
    dbg_unopt2_msg(imdp, ip, pi, mpp, pbi, 
     "mixed fi>1 and non fi>1 highconns");
   goto set_unoptim;
  }  

 /* both strengths must be same */
 if ((up_np->n_stren && !down_np->n_stren)
  || (!up_np->n_stren && down_np->n_stren)) goto set_unoptim;
 if (xp->optyp == ID)
  {
   if (up_np->n_stren) 
    {
     /* must be acc. bsel */
     if (xp->szu.xclen == 1) mpp->mpaf.mpp_upassgnfunc = stbsel_acc_uptoiconn;
     else mpp->mpaf.mpp_upassgnfunc = stacc_uptoiconn;
     return;
    }
   if (xp->szu.xclen == 1) mpp->mpaf.mpp_upassgnfunc = bsel_acc_uptoiconn;
   else mpp->mpaf.mpp_upassgnfunc = acc_uptoiconn;
   return;
  }
 /* bit select case */
 if (down_np->n_stren) mpp->mpaf.mpp_upassgnfunc = stbsel_acc_uptoiconn;
 else mpp->mpaf.mpp_upassgnfunc = bsel_acc_uptoiconn;
}

/*
 * assign std port assign routines if accelerate (port assign optimize off)
 */
extern void __set_mpp_aoff_routines(void)
{
 int32 pi, pbi;
 struct mod_t *mdp;
 struct mod_pin_t *mpp, *mpp2;

 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   if (mdp->minstnum == 0)
    {
     for (pi = 0; pi < mdp->mpnum; pi++)
      {
       mpp = &(mdp->mpins[pi]);
       mpp->assgnfunc_set = TRUE;
      }
     continue;
    }

   for (pi = 0; pi < mdp->mpnum; pi++) 
    {
     mpp = &(mdp->mpins[pi]);
     mpp->assgnfunc_set = TRUE;

     /* lhs destination from port type determines routine */
     if (mpp->mptyp == IO_OUT) mpp->mpaf.mpp_upassgnfunc = std_uptoiconn;
     else if (mpp->mptyp == IO_IN)
      mpp->mpaf.mpp_downassgnfunc = std_downtomdport;
     else continue;

     /* SJM 09/18/06 - if not simulated as decomposed bits, avoid this code */
     if (!mpp->has_scalar_mpps) continue;

     for (pbi = 0; pbi < mpp->mpwide; pbi++)    
      {
       mpp2 = &(mpp->pbmpps[pbi]);
       /* only per bit for input ports */
       mpp2->mpaf.mpp_downassgnfunc = std_downtomdport;
       mpp2->assgnfunc_set = TRUE;
      }
    }
  }
}

/*
 * set new routine when mod port wire has added vpi put value driver added 
 *
 * SJM 09/20/02 - this may be separated per bit mod port 
 */
extern void __vpi_set_downtomdport_proc(struct mod_pin_t *mpp,
 struct net_t *np)
{
 /* if not accelerated when fi==1, then cannot be when fi>1 */
 if (mpp->mpaf.mpp_downassgnfunc == std_downtomdport) return;

 /* driver of wire np in module is module port from up inst. */
 if (mpp->mpref->optyp == ID && np->ntraux == NULL && np->nrngrep != NX_DWIR)
   mpp->mpaf.mpp_downassgnfunc = multfi_acc_downtomdport;
 else mpp->mpaf.mpp_downassgnfunc = std_downtomdport;
}

/*
 * for up to iconn that is now multfi, cannot optimize
 * because do not know other instances  
 */
extern void __vpi_set_upiconnport_proc(struct mod_pin_t *mpp)
{
 mpp->mpaf.mpp_upassgnfunc = std_uptoiconn;
}

/*
 * write a debug reason message for why port not optimized 
 * this is port side message for input ports
 */
static void dbg_unopt_msg(struct mod_t *mdp, struct mod_pin_t *mpp, int32 pbi,
 char *reason)
{
 char s1[RECLEN], s2[RECLEN], s3[RECLEN];

 if (pbi == -1) __to_mpnam(s2, mpp->mpsnam);
 else sprintf(s2, "%s bit %d", __to_mpnam(s3, mpp->mpsnam), pbi);
 __dbg_msg("module %s %s port %s unoptimized: %s\n", mdp->msym->synam,
  __to_ptnam(s1, mpp->mptyp), s2, reason);  
}

/*
 * write a debug reason message for why port not optimized 
 * this is inst conn. side message for output ports
 */
static void dbg_unopt2_msg(struct mod_t *mdp, struct inst_t *ip, int32 pi,
 struct mod_pin_t *mpp, int32 pbi, char *reason)
{
 char s1[RECLEN], s2[RECLEN], s3[RECLEN], s4[RECLEN];

 if (pbi == -1) __to_mpnam(s3, mpp->mpsnam);
 else sprintf(s3, "%s bit %d", __to_mpnam(s4, mpp->mpsnam), pbi);

 __dbg_msg("inst. %s(%s) at %s %s port %s (pos. %d) unoptimized: %s\n",
  ip->isym->synam, mdp->msym->synam, __bld_lineloc(s1, ip->isym->syfnam_ind,
  ip->isym->sylin_cnt), __to_ptnam(s2, mpp->mptyp), s3, pi, reason);  
}

/*
 * PORT UP AND DOWN ASSIGN ROUTINES
 */

/*
 * assign all input ports downward into lower itree instance
 * called from up_itp where itp (down) is under itree place
 *
 * assumes called with nothing pushed on itree stack
 * never called for inout in tran channel - initialized elsewhere
 */
extern void __init_instdownport_contas(struct itree_t *up_itp,
 struct itree_t *down_itp)
{
 int32 pi;
 int32 pnum;
 struct mod_pin_t *mpp;
 struct expr_t *xp;
 struct inst_t *ip;
 struct mod_t *down_mdp;
 decl_idp_locals_;

 ip = down_itp->itip;
 down_mdp = ip->imsym->el.emdp;
 if ((pnum = down_mdp->mpnum) == 0) return;

 /* this must work from up itree loc */
 set_save_idp_itp_(up_itp); 
 for (pi = 0; pi < pnum; pi++) 
  {
   xp = ip->ipins[pi];
   mpp = &(down_mdp->mpins[pi]);
   if (mpp->mptyp != IO_IN) continue;
   
   __immed_assigns++;
   /* must be call with current itree location up (rhs) but passed down */
   /* exec inst. input expr. downward to port changed assign */
   /* notice down always take only 4 args, down do not have first mpp */
   (*mpp->mpaf.mpp_downassgnfunc)(mpp->mpref, xp, down_itp);
  }
 restore_idp_();
}

/*
 * initialize cross module out instance ports continuous assigns 
 *
 * can get to up itree loc. but following up ptr
 * never called for inout in tran channel - initialized elsewhere
 */
extern void __init_instupport_contas(struct itree_t *down_itp)
{
 int32 pi;
 int32 pnum;
 struct mod_pin_t *mpp;
 struct expr_t *xp;
 struct inst_t *ip;
 struct mod_t *down_mdp;
 struct itree_t *up_itp;
 decl_idp_locals_;

 ip = down_itp->itip;
 down_mdp = ip->imsym->el.emdp;
 if ((pnum = down_mdp->mpnum) == 0) return;

 /* cannot assume current itree location - need down starting */
 set_save_idp_itp_(down_itp); 
 for (pi = 0; pi < pnum; pi++) 
  {
   xp = ip->ipins[pi];
   mpp = &(down_mdp->mpins[pi]);
   
   if (mpp->mptyp != IO_OUT) continue;

   __immed_assigns++;
   /* called from down module itree location */ 
   /* SJM - PORT REMOVE - no assign if top level module - ports remain */
   if ((up_itp = down_itp->up_it) == NULL) continue;

   /* assign from rhs down mpp ref. to up lhs iconn */
   /* notice up always take only 3 args, down have extra 1st arg mpp */
   (*mpp->mpaf.mpp_upassgnfunc)(xp, mpp->mpref, up_itp);
  }
 restore_idp_();
}

/*
 * ROUTINES FOR VARIOUS CASES OF DOWN INPUT PORT FROM ICONN TO MDPRT ASSIGN
 */

/*
 * down from iconn to port assign - for all non special cases
 *
 * called from up iconn rhs itree loc.
 * this is standard (general) function that must handle all cases 
 *
 * if any inst. size change, in tran channel, lhs has delay, some but not
 * all fi>1, any iconn is xmr, any iconn is concat, down port is expr.,
 * up is not wire or reg expr, this routine used - must be some more reasons?
 * called from up rhs iconn itree loc.
 */
static void std_downtomdport(struct expr_t *lhsx, struct expr_t *rhsx,
 struct itree_t *down_itp)
{
 struct xstk_t *xsp;
 int32 schd_wire, orhslen;
 decl_idp_locals_;

 if (lhsx->x_multfi)
  {
   /* always must evaluate drivers with itstk of lhs (i.e. down) */
   set_save_idp_itp_(down_itp); 
   /* all lhs expr. containging tran chan wire mult fi and handled here */
   __mdr_assign_or_sched(lhsx);

   /* assigned to down (destination) wire loads of this new assigned to */
   /* wire will be added to net chg list */
   /* DBG remove ---
   if (__debug_flg && __ev_tracing)
    prt_assignedto_val(lhsx, "fi>1 down port assign");
   --- */
   restore_idp_();
   return;
  }

 /* if inst. input expr. is empty, nothing to do */
 if (rhsx->optyp == OPEMPTY) return;
 if (lhsx->x_stren)
  {
   /* handle lhs stren assign - pass strength through */
   /* other side always marked strength and if rhs reg, will add in strong */ 
   xsp = __ndst_eval_xpr(rhsx);
   /* widen to lhs width with z's - if too narrow, high part just unused */
   /* SJM 05/10/04 - no sign extension because widening to z'x */
   /* AIV 03/15/07 - strength for xsp->xslen was wrong for same reaston */
   /* as one fixed on 11/21/06 */
   /* SJM 11/21/06 - for stren's xsp is 4 times width for byte per bit */
   /* problem is xslen for stren is not the expr bit width */
   if (rhsx->szu.xclen < lhsx->szu.xclen)
    __strenwiden_sizchg(xsp, lhsx->szu.xclen);
  }
 else
  {
   xsp = __eval_xpr(rhsx);
   if (lhsx->szu.xclen != xsp->xslen)
    {
     orhslen = xsp->xslen;

     /* SJM 09/29/03 - change to handle sign extension and separate types */
     if (xsp->xslen > lhsx->szu.xclen)
      __narrow_sizchg(xsp, lhsx->szu.xclen);
     else if (xsp->xslen < lhsx->szu.xclen)
      {
       if (rhsx->has_sign) __sgn_xtnd_widen(xsp, lhsx->szu.xclen);
       else __sizchg_widen(xsp, lhsx->szu.xclen);
      }

     /* widened, set bits higher than orhslen to z */ 
     /* LOOKATME - only strength continuous assignments widen to z */
     /* all others widen to 0 */
     /* ??? if (orhslen < xsp->xslen) __fix_widened_tozs(xsp, orhslen); */
     /* SJM 05/10/04 - widening to x's eliminates need for sign difference */
     if (__wire_init) __fix_widened_toxs(xsp, orhslen);
    }
  }
 /* eval. in up itree side but assign on to lhs in down */ 
 set_save_idp_itp_(down_itp); 
 if (lhsx->lhsx_ndel && !__wire_init) schd_wire = TRUE;
 else schd_wire = FALSE;
 if (lhsx->x_stren)
  {
   /* port conta just assigns strengths */ 
   if (lhsx->optyp == LCB)
    __stren_exec_ca_concat(lhsx, (byte *) xsp->ap, schd_wire);
   else __exec_conta_assign(lhsx, xsp->ap, xsp->bp, schd_wire);
  }
 else
  {
   if (lhsx->optyp == LCB)
    __exec_ca_concat(lhsx, xsp->ap, xsp->bp, schd_wire);
   else __exec_conta_assign(lhsx, xsp->ap, xsp->bp, schd_wire);
  }
 __pop_xstk();
 /* DBG remove --
 if (__debug_flg && __ev_tracing)
  prt_assignedto_val(lhsx, "port down assign");
 --- */  
 /* notice cannot pop until here since lhs is down */
 restore_idp_();
}

/*
 * print value of assign to output wire 
 * only called when debug flag and some kind of tracing on
 */
static void prt_assignedto_val(struct expr_t *xp, char *nppnam)
{
 char s1[RECLEN], s2[RECLEN];

 if (xp->x_stren) strcpy(s2, "strength "); else strcpy(s2, "");
 __tr_msg("== %s lvalue %swire %s set or scheduled to %s\n", nppnam, s2,
  __msgexpr_tostr(__xs, xp), __to_gassign_str(s1, xp));
}

/*
 * mulfi lhs upward instance port assign from down module port assign 
 * for output port
 *
 * only for down port multi-fi wire (could handle selects but rare)
 * since port expressions rare
 * since down lhs is module port all will be same 
 * if port expr. or inout in tran channel, cannot use this routine
 * can be either strength or non strength
 * called from up rhs iconn itree location
 */
static void multfi_acc_downtomdport(struct expr_t *lhsx, struct expr_t *rhsx,
 struct itree_t *down_itp)
{
 decl_idp_locals_;

 /* for mdport fi>1, eval all drivers */
 /* must evaluate drivers with itstk of lhs (i.e. down here) */
 set_save_idp_itp_(down_itp); 
 __assign_1mdrwire(lhsx->lu.sy->el.enp);
 /* DBG remove ---
 if (__debug_flg && __ev_tracing)
  prt_assignedto_val(lhsx, "fi>1 down port assign");
 --- */
 restore_idp_();
} 

/*
 * stren both wire/reg up iconn down to mod port assign special case routine 
 * only called if all instances both same width IDs
 * never for scalar - use bit select version for that 
 *
 * called from up rhs iconn itree location
 */
static void stacc_downtomdport(struct expr_t *lhsx, struct expr_t *rhsx,
 struct itree_t *down_itp)
{
 byte *bp, *sbp;
 struct net_t *lhsnp;
 struct xstk_t *xsp;
 decl_idp_locals_;

 push_xstk_(xsp, 4*rhsx->szu.xclen);
 sbp = (byte *) xsp->ap;
 bp = (byte *) &(__idp[rhsx->lu.sy->el.enp->nva_ofs]);
 memcpy(sbp, bp, rhsx->szu.xclen); 

 /* assign in down */
 set_save_idp_itp_(down_itp); 
 lhsnp = lhsx->lu.sy->el.enp;
 /* this adds the changed wire to nchglst if needed */
 /* return F if all of wire forced, nothing to do */ 
 if (lhsnp->frc_assgn_allocated)
  {
   if (!__correct_forced_newwireval(lhsnp, (word32 *) sbp, (word32 *) NULL))
    { 
     restore_idp_();
     __pop_xstk(); 
     return; 
    }
  }
 __chg_st_val(lhsnp, (word32 *) sbp, (word32 *) NULL);
 __pop_xstk();
 /* DBG remove ---
 if (__debug_flg && __ev_tracing)
  prt_assignedto_val(lhsx, "strength mod. port down assign");
 --- */
 restore_idp_();
}

/*
 * stren both wire/reg up iconn down to mod port assign special case routine 
 * this is also called for all scalars on up inst. 
 *
 * only called if all instances both scalar IDs or up bsel and down
 * and nothing special such as delay wire
 * only strength scalars handled here
 */
static void stbsel_acc_downtomdport(struct expr_t *lhsx,
 struct expr_t *rhsx, struct itree_t *down_itp)
{
 struct net_t *lhsnp;
 byte sb2, *bp, *sbp;
 decl_idp_locals_;

 /* eval rhs up iconn in current itree up loc. */
 if (rhsx->optyp == LSB) access_stbsel(&sb2, rhsx);
 else
  {
   bp = (byte *) &(__idp[rhsx->lu.sy->el.enp->nva_ofs]);
   sb2 = bp[0];
  }

 /* assign in down */
 set_save_idp_itp_(down_itp); 
 lhsnp = lhsx->lu.sy->el.enp;
 /* this is needed so for endian differences - cast of ptr does nothing */
 sbp = &sb2;
 /* this adds the changed wire to nchglst if needed */
 /* return F if all of wire forced, nothing to do */ 
 if (lhsnp->frc_assgn_allocated)
  {
   if (!__correct_forced_newwireval(lhsnp, (word32 *) sbp, (word32 *) NULL))
    { 
     restore_idp_();
     return; 
    }
  }
 __chg_st_val(lhsnp, (word32 *) sbp, (word32 *) NULL);
 /* DBG remove ---
 if (__debug_flg && __ev_tracing)
  prt_assignedto_val(lhsx, "strength scalar mod. port assign");
 --- */
 restore_idp_();
}

/*
 * non stren both wire upward to instance port assign special case routine 
 * only called if all instances both same width IDs
 * acc bsel routine called for scalars 
 */
static void acc_downtomdport(struct expr_t *lhsx, struct expr_t *rhsx,
 struct itree_t *down_itp)
{
 struct xstk_t *xsp;
 struct net_t *lhsnp;
 decl_idp_locals_;

 /* up rhs always wire/reg or not fast routine */
 /* eval rhs up iconn in current itree up loc. */
 push_xstk_(xsp, rhsx->szu.xclen);
 __ld_wire_val_xstk(xsp, rhsx->lu.sy->el.enp);

 /* assign in down */
 set_save_idp_itp_(down_itp); 
 lhsnp = lhsx->lu.sy->el.enp;
 /* this adds the changed wire to nchglst if needed */
 /* return F if all of wire forced, nothing to do */ 
 if (lhsnp->frc_assgn_allocated)
  {
   if (!__correct_forced_newwireval(lhsnp, xsp->ap, xsp->bp))
    { 
     restore_idp_();
     __pop_xstk(); 
     return; 
    }
  }
 __chg_st_val(lhsnp, xsp->ap, xsp->bp);
 __pop_xstk();
 /* DBG remove ---
 if (__debug_flg && __ev_tracing)
  prt_assignedto_val(lhsx, "mod. port assign");
 --- */
 restore_idp_();
}

/*
 * up wire bsel to instance port scalar assign special case routine 
 *
 * only called if up rhs is scalar or bit select and down port
 * is scalar wire - all insts must also be simple and not in tran channel
 * this is only for scalars and at least one bsel
 */
static void bsel_acc_downtomdport(struct expr_t *lhsx, struct expr_t *rhsx,
 struct itree_t *down_itp)
{
 int32 biti, indi;
 word32 av, bv, tmpw;
 struct net_t *lhsnp, *rhsnp;
 decl_idp_locals_;

 /* down rhs always wire/reg or not accelerated routine */
 if (rhsx->optyp == LSB)
  {
   rhsnp = rhsx->lu.x->lu.sy->el.enp;
   biti = __comp_ndx(rhsnp, rhsx->ru.x);
   /* AIV 06/04/07 - need to handle the scalar array case */ 
   if (rhsnp->n_isarr) 
    {
     /* here arri is real twice real index to get bit index */
     /* AIV 09/01/10 - 2-state now stored with 2x */
     if (rhsnp->n_2state) 
      {
       tmpw = __idp[rhsnp->nva_ofs + get_wofs_(biti)] >> (get_bofs_(biti));
       av = tmpw & 1L;
       bv = 0;
      }
     else 
      {
       indi = 2*biti;
       tmpw = __idp[rhsnp->nva_ofs + get_wofs_(indi)] >> (get_bofs_(indi));
       av = tmpw & 1L;
       bv = (tmpw >> 1) & 1L;
      }
    }
   else
    {
     /* know biti never -1 since only fixed non -1 for this routine */
     __ld_bit(&av, &bv, rhsnp, biti);
    }
  }
 else __ld_wire_val_wrds(&av, &bv, rhsx->lu.sy->el.enp);

 /* assign in down - never an expr. */
 set_save_idp_itp_(down_itp); 
 lhsnp = lhsx->lu.sy->el.enp;
 /* this adds the changed wire to nchglst if needed */
 /* return F if all of wire forced, nothing to do */ 
 if (lhsnp->frc_assgn_allocated)
  {
   if (!__correct_forced_newwireval(lhsnp, &av, &bv))
    { 
     restore_idp_();
     return;
    }
  }
 __chg_st_val(lhsnp, &av, &bv);
 /* DBG remove ---
 if (__debug_flg && __ev_tracing)
  prt_assignedto_val(lhsx, "mod. port scalar assign");
 --- */
 restore_idp_();
}

/*
 * ROUTINES FOR THE VARIOUS CASES OF FROM DOWN MDPRT TO UP ICONN ASSIGN
 */

/*
 * upward to instance port assign - for all non special cases
 * this is standard (general) function that must handle all cases 
 *
 * if any inst. size change, in tran channel, lhs has delay, some but not
 * all fi>1, any iconn is xmr, any iconn is concat, down port is expr.,
 * up is not wire or reg expr, this routine used - must be some more reasons?
 */
static void std_uptoiconn(struct expr_t *lhsx, struct expr_t *rhsx,
 struct itree_t *up_itp)
{
 struct xstk_t *xsp;
 int32 schd_wire, orhslen;
 decl_idp_locals_;

 /* if destination driven by module output is empty, nothing to do */
 if (lhsx->optyp == OPEMPTY) return;

 /* for iconn part of fi>1, eval all drivers code */
 if (lhsx->x_multfi)
  {
   /* always must evaluate drivers with itstk of lhs (i.e. up here) */
   set_save_idp_itp_(up_itp); 
   __mdr_assign_or_sched(lhsx);

   /* DBG remove ---
   if (__debug_flg && __ev_tracing)
    prt_assignedto_val(lhsx, "fi>1 upto highconn assign");
   --- */
   restore_idp_();
   return;
  }
 /* load rhs according to lhs expr. type and make size equal to lhs */
 /* if port has no connections - LOOKATME maybe illegal, nothing to do */
 if (rhsx->optyp == OPEMPTY) return;

 /* eval rhs on current itree down loc. */
 if (lhsx->x_stren)
  {
   /* handle lhs stren assign - pass strength through */
   /* if reg, will add strong strength */
   xsp = __ndst_eval_xpr(rhsx);
   /* widen to lhs width with z's - if too narrow, high part just unused */
   /* SJM 05/10/04 - no sign extension because widening to z'x */
   /* SJM 11/21/06 - for stren's xsp is 4 times width for byte per bit */
   /* problem is xslen for stren is not the expr bit width */
   if (rhsx->szu.xclen < lhsx->szu.xclen)
    __strenwiden_sizchg(xsp, lhsx->szu.xclen);
  }
 else
  {
   xsp = __eval_xpr(rhsx);
   if (lhsx->szu.xclen != xsp->xslen)
    {
     orhslen = xsp->xslen;

     /* SJM 09/29/03 - change to handle sign extension and separate types */
     if (xsp->xslen > lhsx->szu.xclen)
      __narrow_sizchg(xsp, lhsx->szu.xclen);
     else if (xsp->xslen < lhsx->szu.xclen)
      {
       if (rhsx->has_sign) __sgn_xtnd_widen(xsp, lhsx->szu.xclen);
       else __sizchg_widen(xsp, lhsx->szu.xclen);
      }

     /* widened, set bits higher than orhslen to z */ 
     /* LOOKATME - only strength continuous assignments widen to z */
     /* all others widen to 0 except x during initialization */
     /* ??? if (orhslen < xsp->xslen) __fix_widened_tozs(xsp, orhslen); */
     /* SJM 05/10/04 - widening to x's eliminates need for sign difference */
     if (__wire_init) __fix_widened_toxs(xsp, orhslen);
    }
  }
 /* but assign on lhs up iconn itree location */
 set_save_idp_itp_(up_itp); 
 if (lhsx->lhsx_ndel && !__wire_init) schd_wire = TRUE;
 else schd_wire = FALSE;
 /* notice here is lhs is gref, assign handles finding right itree loc. */
 if (lhsx->x_stren)
  {
   /* port conta just assigns strengths */ 
   if (lhsx->optyp == LCB)
    __stren_exec_ca_concat(lhsx, (byte *) xsp->ap, schd_wire);
   else __exec_conta_assign(lhsx, xsp->ap, xsp->bp, schd_wire);
  }
 else
  {
   if (lhsx->optyp == LCB)
    __exec_ca_concat(lhsx, xsp->ap, xsp->bp, schd_wire);
   else __exec_conta_assign(lhsx, xsp->ap, xsp->bp, schd_wire);
  }
 __pop_xstk();
 /* DBG remove ---
 if (__debug_flg && __ev_tracing)
  prt_assignedto_val(lhsx, "inst. conn. up assign");
 --- */
 restore_idp_();
}

/*
 * mulfi lhs upward instance port assign from down module port assign 
 *
 * only for down wire and up any multi-fi non concat simple and non tran
 * if one multfi and any other not, std all cases routine must be used
 * can be either strength or non strength
 */
static void multfi_acc_uptoiconn(struct expr_t *lhsx,
 struct expr_t *rhsx, struct itree_t *up_itp)
{
 decl_idp_locals_;
 struct gref_t *grp;
 struct net_t *np;
 t_midat *xmr_idp;

 /* for iconn part of fi>1, eval all drivers code */
 /* must evaluate drivers with itstk of lhs (i.e. up here) */
 set_save_idp_itp_(up_itp); 
 if (lhsx->optyp == ID) __assign_1mdrwire(lhsx->lu.sy->el.enp);
 else 
  {
   np = lhsx->lu.x->lu.sy->el.enp;
   /* strength accesses the __idp so if global need to push correct idp */
   if (np->n_stren && lhsx->lu.x->optyp == GLBREF)
    {
     /* AIV 08/01/07 - if global location for net need to get the grp idp */
     /* location for the correct idp of nva_ofs for the global */
     grp = lhsx->lu.x->ru.grp;
     xmr_idp = __xmrget_refgrp_to_targ(grp);
     set_save_idp_(xmr_idp); 
     __assign_1mdrwire(lhsx->lu.x->lu.sy->el.enp);
    }
  }
 /* DBG remove ---
 if (__debug_flg && __ev_tracing)
  prt_assignedto_val(lhsx, "fi>1 up to highconn assign");
 --- */
 restore_idp_();
} 

/*
 * stren both wire upward to instance port assign special case routine 
 * only called if all instances both same width IDs
 */
static void stacc_uptoiconn(struct expr_t *lhsx, struct expr_t *rhsx,
 struct itree_t *up_itp)
{
 byte *bp, *sbp;
 struct net_t *lhsnp;
 struct xstk_t *xsp;
 decl_idp_locals_;

 /* eval rhs mod port in current itree down loc. */
 /* for accelerated know down port rhs is not an expression */
 push_xstk_(xsp, 4*rhsx->szu.xclen);
 sbp = (byte *) xsp->ap;
 bp = (byte *) &(__idp[rhsx->lu.sy->el.enp->nva_ofs]);
 memcpy(sbp, bp, rhsx->szu.xclen); 

 /* assign in up */
 set_save_idp_itp_(up_itp); 
 lhsnp = lhsx->lu.sy->el.enp;
 /* this adds the changed wire to nchglst if needed */
 /* return F if all of wire forced, nothing to do */ 
 if (lhsnp->frc_assgn_allocated)
  {
   if (!__correct_forced_newwireval(lhsnp, (word32 *) sbp, (word32 *) NULL))
    { 
     restore_idp_();
     __pop_xstk(); 
     return; 
    }
  }
 __chg_st_val(lhsnp, (word32 *) sbp, (word32 *) NULL);
 __pop_xstk();
 /* DBG remove ---
 if (__debug_flg && __ev_tracing)
  prt_assignedto_val(lhsx, "strength inst. conn. up assign");
 --- */
 restore_idp_();
}

/*
 * stren up wire bsel to instance port scalar assign special case routine 
 *
 * only called if up lhs is strength bit select or scalar and down
 * is scalar wire, all insts must also be simple and not in tran channel
 */
static void stbsel_acc_uptoiconn(struct expr_t *lhsx, struct expr_t *rhsx,
 struct itree_t *up_itp)
{
 byte *bp, sb2, *sbp;
 struct net_t *lhsnp;
 struct expr_t *idndp, *ndx1;
 decl_idp_locals_;

 /* eval rhs mod port in current itree down loc. */
 /* for accelerated know down port rhs is not an expression */
 bp = (byte *) &(__idp[rhsx->lu.sy->el.enp->nva_ofs]);
 sb2 = bp[0];
 sbp = &sb2;

 set_save_idp_itp_(up_itp); 
 /* here can be either stren scalar or bit select */
 if (lhsx->optyp == ID)
  {
   lhsnp = lhsx->lu.sy->el.enp;
   if (lhsnp->frc_assgn_allocated)
    {
     if (!__correct_forced_newwireval(lhsnp, (word32 *) sbp, (word32 *) NULL))
      { 
       restore_idp_();
       return; 
      }
    }
   __chg_st_val(lhsnp, (word32 *) sbp, (word32 *) NULL);
  }
 else
  {
   idndp = lhsx->lu.x;
   ndx1 = lhsx->ru.x;
   lhsnp = idndp->lu.sy->el.enp;
   /* the 1 bit is forced nothing to do else normal assign */
   if (lhsnp->frc_assgn_allocated
    && __forced_inhibit_bitassign(lhsnp, idndp, ndx1))
    { 
     restore_idp_();
     return; 
    }
   __assign_to_bit(lhsnp, idndp, ndx1, (word32 *) sbp, (word32 *) NULL);
  }  
 /* DBG remove --
 if (__debug_flg && __ev_tracing)
  prt_assignedto_val(lhsx, "strength scalar inst. conn. up assign");
 --- */
 restore_idp_();
}

/*
 * non stren both wire upward to instance port assign special case routine 
 * only called if all instances both same width IDs
 */
static void acc_uptoiconn(struct expr_t *lhsx, struct expr_t *rhsx,
 struct itree_t *up_itp)
{
 struct xstk_t *xsp;
 struct net_t *lhsnp;
 decl_idp_locals_;

 /* down rhs always wire/reg or not accerated routine */
 push_xstk_(xsp, rhsx->szu.xclen);
 __ld_wire_val_xstk(xsp, rhsx->lu.sy->el.enp);

 /* assign in up */
 set_save_idp_itp_(up_itp); 
 lhsnp = lhsx->lu.sy->el.enp;
 /* this adds the changed wire to nchglst if needed */
 /* return F if all of wire forced, nothing to do */ 
 if (lhsnp->frc_assgn_allocated)
  {
   if (!__correct_forced_newwireval(lhsnp, xsp->ap, xsp->bp))
    { 
     restore_idp_();
     __pop_xstk(); 
     return;
    }
  }
 __chg_st_val(lhsnp, xsp->ap, xsp->bp);
 __pop_xstk();
 /* DBG remove ---
 if (__debug_flg && __ev_tracing)
  prt_assignedto_val(lhsx, "inst. conn. up assign");
 --- */
 restore_idp_();
}

/*
 * up wire bsel to instance port scalar assign special case routine 
 *
 * only called if up lhs is strength bit select and down is scalar wire
 * all insts must also be simple and not in tran channel
 */
static void bsel_acc_uptoiconn(struct expr_t *lhsx, struct expr_t *rhsx,
 struct itree_t *up_itp)
{
 word32 av, bv;
 struct net_t *lhsnp;
 struct expr_t *idndp, *ndx1;
 decl_idp_locals_;

 /* down rhs always wire/reg or not accerated routine */
 __ld_wire_val_wrds(&av, &bv, rhsx->lu.sy->el.enp);

 /* assign in up */
 set_save_idp_itp_(up_itp); 
 /* here can be either stren scalar or bit select */
 if (lhsx->optyp == ID)
  {
   lhsnp = lhsx->lu.sy->el.enp;
   if (lhsnp->frc_assgn_allocated)
    {
     if (!__correct_forced_newwireval(lhsnp, &av, &bv))
      { 
       restore_idp_();
       return;
      }
    }
   __chg_st_val(lhsnp, &av, &bv);
  }
 else if (lhsx->optyp == LSB)
  {
   idndp = lhsx->lu.x;
   ndx1 = lhsx->ru.x;
   lhsnp = idndp->lu.sy->el.enp;
   /* the 1 bit is forced nothing to do else normal assign */
   if (lhsnp->frc_assgn_allocated
    && __forced_inhibit_bitassign(lhsnp, idndp, ndx1))
    { 
     restore_idp_();
     return; 
    }
   __assign_to_bit(lhsnp, idndp, ndx1, &av, &bv);
  }  
 /* DBG remove (also above bsel if) -- */
 else __case_terr(__FILE__, __LINE__);
 /* --- */

 /* DBG remove ---
 if (__debug_flg && __ev_tracing)
  prt_assignedto_val(lhsx, "strength scalar inst. conn. up assign");
 --- */
 restore_idp_();
}

/*
 * MULTI FAN IN NON STRENGTH WIRE ASSIGN ROUTINES
 * ASSIGN BY EVALUATING ALL DRIVERS
 */

/*
 * continuous assign for multi-fi and stren (even if fi=1) wires
 * conta, mod and inst. ports
 *
 * this is called from itree loc. of lhsx, each driver eval may need
 * to move to driving itree loc. load driver routine handles moving
 *
 * notice even if only a few bits are changed - must reevaluate all bits
 * idea is that strengths are almost always scalars and multi-fi
 */
extern void __mdr_assign_or_sched(struct expr_t *lhsx)
{
 struct net_t *np;
 t_midat *xmr_idp;
 struct expr_t *idndp, *catndp;
 struct gref_t *grp;
 decl_idp_locals_;

 save_idp = NULL;
 switch (lhsx->optyp) {
  case GLBREF:
   idndp = lhsx;
mdr_glb:
   grp = idndp->ru.grp;
   /* move from xmr ref. itree location to wire definition location */
   xmr_idp = __xmrget_refgrp_to_targ(grp);
   set_save_idp_(xmr_idp); 
   goto mdr_id;
  case ID:
   idndp = lhsx;
mdr_id:
   np = idndp->lu.sy->el.enp;
   /* handle fi>1 eval and store of bits not in any tran channel */
   if (np->ntraux != NULL)
    {
     /* if hard drivers of np do not change, channel cannot change */
     /* SJM 12/18/00 - for tran/tranif switch channels may just add to list */
     if (__update_tran_harddrvs(np))
      {
       /* can't eval (relax) tran channels until all hard drivers known */
       /* so first relax can be done */
       __eval_tran_bits(np);
      }
     break;
    }
   if (np->nrngrep == NX_DWIR) __sched_1mdrwire(np);
   else __assign_1mdrwire(np);
   break;
  case LSB:
  case PARTSEL:
   idndp = lhsx->lu.x;
   if (idndp->optyp == GLBREF) goto mdr_glb; else goto mdr_id;
  case LCB:
   /* must treat all wires in lhs multi-fan-in concat as special */ 
   /* this means every lhs element needs re-eval of rhs */
   for (catndp = lhsx->ru.x; catndp != NULL; catndp = catndp->ru.x)
    __mdr_assign_or_sched(catndp->lu.x);
   break;
  default: __case_terr(__FILE__, __LINE__);
 }
 if (save_idp != NULL)
  {
   restore_idp_();
  }
}

/*
 * assign to one entire wire with multiple fan-in
 *
 * it can have strength (or not) but delayed wire handled elsewhere
 * cannot be either inout iconn or inout port wire
 * called in lhs itree loc. of np (wire definition)
 */
extern void __assign_1mdrwire(struct net_t *np)
{
 int32 sbi;
 byte *sbp;
 byte *abp;
 word32 *app, *bpp;
 struct xstk_t *xsp;

 /* separate routines for rare multi-fi wires with delay */
 /* here since schedule lhs changed always off */
 sbp = NULL;
 /* first most common strength case since know muliple drive */
 if (np->n_stren)
  {
   /* get new value of wire from combination of all drivers */
   xsp = __stload_mdrwire(np);
   sbp = (byte *) xsp->ap;

   /* notice any force overrides even tri reg */
   if (np->frc_assgn_allocated
    && !__correct_forced_newwireval(np, xsp->ap, xsp->bp))
    { __pop_xstk(); return; }

   /* short circuit chg store into strength wire */
   abp = (byte *) &(__idp[np->nva_ofs]);

   /* no delay form trireg wire, correct for same value cap. strength */
   if (np->ntyp == N_TRIREG)
    {
     for (sbi = 0; sbi < np->nwid; sbi++)
      {
       if (sbp[sbi] == ST_HIZ)
        sbp[sbi] = (byte) ((abp[sbi] & 3) | __cap_to_stren[np->n_capsiz]);
      }
    }
   if (memcmp(abp, sbp, np->nwid) != 0)
    {
     memcpy(abp, sbp, np->nwid);
     __lhs_changed = TRUE;
    }
  }
 else
  {
   /* multiple driver non strength no delay case */
   /* xsp is new wire value */
   /* load address and store value use current (np lhs) itree place */
   xsp = __load_mdrwire(np);

   if (np->frc_assgn_allocated
    && !__correct_forced_newwireval(np, xsp->ap, xsp->bp))
    { __pop_xstk(); return; }

   /* notice this address because of packing cannot be stored into */
   __ld_addr(&app, &bpp, np);
   if (np->nwid <= WBITS)
    { if (app[0] == xsp->ap[0] && bpp[0] == xsp->bp[0]) goto done; }
   else
    {
     if (cmp_vval_(app, xsp->ap, np->nwid) == 0
      && cmp_vval_(bpp, xsp->bp, np->nwid) == 0) goto done;
    }
   __st_val(np, xsp->ap, xsp->bp, xsp->xslen); 
   __lhs_changed = TRUE;
  }

done:
 if (__ev_tracing)
  {
   char s1[RECLEN];

   if (np->n_stren) strcpy(s1, " strength"); else strcpy(s1, "");
   __tr_msg(" drivers of%s wire %s combined", s1, np->nsym->synam);
   if (__lhs_changed)
    {
     if (np->n_stren) __st_regab_tostr(__xs, sbp, np->nwid); 
     else __regab_tostr(__xs, xsp->ap, xsp->bp, xsp->xslen, BHEX, FALSE);
     __tr_msg(" and assigned value %s\n", __xs);
    }
   else __tr_msg(" value unchanged\n"); 
  }
 if (__lhs_changed) record_nchg_(np);
 __pop_xstk();
}

/*
 * sched assign for one entire wire with multiple fan-in
 * that has delay and be strength (or not)
 * but cannot be either inout iconn or inout port wire
 *
 * if forced, still must schedule because by assign force may be off later 
 */
extern void __sched_1mdrwire(struct net_t *np)
{
 struct xstk_t *xsp;
 byte *sbp;

 /* separate routines for rare multi-fi wires with delay */
 /* here since schedule lhs changed always off */
 sbp = NULL;
 if (np->n_stren)
  {
   /* this must run in location of ref. not dest. target */
   xsp = __stload_mdrwire(np);
   sbp = (byte *) xsp->ap;
   /* but rest for xmr must store into dest. target */
   /* if np is trireg this will handle (decays known from sbp z's) */ 
   if (np->nu.rngdwir->n_delrep == DT_PTHDST)
    __pth_stren_schd_allofwire(np, sbp, np->nwid);
   else __wdel_stren_schd_allofwire(np, sbp, np->nwid);
  } 
 else
  {
   xsp = __load_mdrwire(np);
   if (np->nu.rngdwir->n_delrep == DT_PTHDST)
    __pth_schd_allofwire(np, xsp->ap, xsp->bp, np->nwid);
   else __wdel_schd_allofwire(np, xsp->ap, xsp->bp, np->nwid);
  }
 if (__ev_tracing)
  {
   char s1[RECLEN];

   if (np->n_stren) strcpy(s1, " strength"); else strcpy(s1, "");
   __tr_msg(" drivers of%s wire %s combined", s1, 
    np->nsym->synam);
   if (np->n_stren) __st_regab_tostr(__xs, sbp, np->nwid); 
   else __regab_tostr(__xs, xsp->ap, xsp->bp, xsp->xslen, BHEX, FALSE);
   __tr_msg(" and scheduled to value %s\n", __xs);
  }
 __pop_xstk();
}

/*
 * ROUTINES TO LOAD AND COMBINE NON STRENGTH MULTI DRIVER WIRE
 */

/* 
 * load entire wire with at least some bits of multiple fan-in
 * onto stack - leaves value on top of stack that caller must pop
 *
 * this is for non strength case 
 * for xmr the drivers are drivers for wire target wire
 * loads only hard drivers - tran channel code handles tran components
 */
extern struct xstk_t *__load_mdrwire(struct net_t *np)
{
 struct net_pin_t *npp;
 struct xstk_t *xsp;

 /* allocate accumulator with undriven bits set to z */
 push_xstk_(xsp, np->nwid);
 /* initialize to high z - only possibility in non strength case */
 zero_allbits_(xsp->ap, np->nwid);
 one_allbits_(xsp->bp, np->nwid);

 /* must reevaluate every driver since no algorithm for undoing */
 /* 1 driver to add new one even if could store old value somewhere */
 for (npp = np->ndrvs; npp != NULL; npp = npp->npnxt)
  {
   /* filter new rooted and up. rel col. forms */ 
   if (npp->npproctyp == NP_PROC_FILT
    && npp->npaux->npu.filtidp != __idp) continue;
   ldcomb_driver(xsp, np, npp);
  }
 return(xsp);
}

/*
 * load and combine in to passed z initial acumulator one npp driver
 *
 * filters for downward relative xmrs if npp does not match this inst.
 * know definition itree loc on itstk
 */
static void ldcomb_driver(struct xstk_t *acc_xsp, struct net_t *np,
 struct net_pin_t *npp)
{
 struct xstk_t *xsp, *tmpxsp;
 int32 lhswid;
 struct npaux_t *npauxp;
 struct itree_t *itp;
 decl_idp_locals_;

 /* --- DBG remove
 if (__debug_flg && __ev_tracing)
  {
   __tr_msg("## loading %s driver of wire %s\n",
    __to_npptyp(__xs, npp), np->nsym->synam);
  }
 --- */
 save_idp = NULL;
 if (npp->npproctyp != NP_PROC_INMOD)
  {
   /* SJM 04/17/03 - if XMR does not match - do not combine in */
   if ((itp = __get_npprefloc(npp)) == NULL) return;
   set_save_idp_itp_(itp); 
  }

 /* this puts the driving value (normal rhs with rhs width) on stack */
 /* notice tran strength only so error if appears here */
 switch ((byte) npp->npntyp) {
  case NP_CONTA: xsp = __ld_conta_driver(npp); break;
  case NP_TFRWARG: xsp = __ld_tfrwarg_driver(npp); break;
  case NP_VPIPUTV: xsp = __ld_vpiputv_driver(npp); break;
  case NP_GATE: xsp = __ld_gate_driver(npp); break;
  /* these are up to highconn output port drivers */
  case NP_ICONN: xsp = __ld_iconn_up_driver(npp); break;
  case NP_PB_ICONN: xsp = __ld_pb_iconn_up_driver(npp); break;
  /* these are down to lowconn input port drivers */
  case NP_MDPRT: xsp = __ld_modport_down_driver(npp); break;
  case NP_PB_MDPRT: xsp = __ld_pb_modport_down_driver(npp); break;
  default: __case_terr(__FILE__, __LINE__); xsp = NULL; 
 }
 if (save_idp != NULL)
  { 
   restore_idp_();
  }

 /* if lhs of concatenate, must select section out of rhs value */
 if ((npauxp = npp->npaux) != NULL && npauxp->lcbi1 != -1)
  {
   /* loaded value always matches lhs width exactly with z extension */
   /* if too wide just will not rhs psel from section */
   lhswid = npauxp->lcbi1 - npauxp->lcbi2 + 1;
   push_xstk_(tmpxsp, lhswid);
   __rhspsel(tmpxsp->ap, xsp->ap, npauxp->lcbi2, lhswid); 
   __rhspsel(tmpxsp->bp, xsp->bp, npauxp->lcbi2, lhswid); 

   __eval_wire(acc_xsp->ap, tmpxsp->ap, np, npp);
   __pop_xstk();
  }
 else __eval_wire(acc_xsp->ap, xsp->ap, np, npp);
 __pop_xstk();
}

/*
 * routine to move from xmr definition location of wire npp driver
 * or load net on back to reference location so can get gate/conta
 * driving or conducting value
 *
 * push onto itstk and leave on
 */
extern struct itree_t *__get_npprefloc(struct net_pin_t *npp)
{
 struct itree_t *itp;

 if (npp->npproctyp == NP_PROC_GREF)
  {
   itp = __match_targ_to_ref(npp->np_xmrtyp, npp->npaux->npu.npgrp);
   return(itp);
  }
 /* all rooted xmrs here */
 else return(npp->npaux->npdownitp);
}

/*
 * load a wire driver for use by count drivers
 * puts the driving value (normal rhs with rhs width) on stack 
 *
 * this is not normal routine - for case where just need one with fi>1 comb.
 * must set returned NULL to all z's
 */
extern struct xstk_t *__ld_wire_driver(struct net_pin_t *npp)
{
 struct xstk_t *xsp;
 struct itree_t *itp;
 decl_idp_locals_;

 /* for new col or xmr npp forms that need to match inst */
 /* instance filter already done */  
 save_idp = NULL;
 if (npp->npproctyp != NP_PROC_INMOD)
  {
   /* SJM 04/17/03 - if XMR does not match - do not combine in */
   if ((itp = __get_npprefloc(npp)) == NULL) return(NULL);
   set_save_idp_itp_(itp); 
  }

 /* iconn and mod port may return xsp of nil - caller does not pop */
 switch ((byte) npp->npntyp) {
  case NP_CONTA: xsp = __ld_conta_driver(npp); break;
  case NP_TFRWARG: xsp = __ld_tfrwarg_driver(npp); break;
  case NP_VPIPUTV: xsp = __ld_vpiputv_driver(npp); break;
  case NP_GATE: xsp = __ld_gate_driver(npp); break;
  /* these are up to highconn output port drivers */
  case NP_ICONN: xsp = __ld_iconn_up_driver(npp); break;
  case NP_PB_ICONN: xsp = __ld_pb_modport_down_driver(npp); break;
  /* these are down to lowconn input port drivers */
  case NP_MDPRT: xsp = __ld_modport_down_driver(npp); break;
  case NP_PB_MDPRT: xsp = __ld_pb_modport_down_driver(npp); break;
  /* tran strength only */
  default: __case_terr(__FILE__, __LINE__); return(NULL);
 }
 if (save_idp != NULL)
  {
   restore_idp_();
  }
 return(xsp);
}

/*
 * load a continuous assignment driver npp
 * caller must have moved to right itree loc. for xmr form
 *
 * if rhs conta concat causes sep into bits, this is PB conta
 */
extern struct xstk_t *__ld_conta_driver(struct net_pin_t *npp)
{
 int32 blen, orhslen;
 struct xstk_t *xsp;
 struct conta_t *cap;

 /* SJM 09/18/02 - no separate per bit NP type, check for pb sim on */
 cap = npp->elnpp.ecap; 
 if (cap->ca_pb_sim)
  {
   cap = &(cap->pbcau.pbcaps[npp->pbi]);
  }

 blen = cap->lhsx->szu.xclen;
 /* case 1: fi=1 - for showvars driver is wire section [nbi1:nbi2] itself */
 /* for fi == 1 and no delay need this for wire display */
 /* will never get here normally since just assign */
 /* accessing rhs for consistency check but lhs should always be same */ 
 if (cap->ca_drv_ofs == 0)
  {
   xsp = __eval2_xpr(cap->rhsx);
   if (blen != xsp->xslen)
    {
     orhslen = xsp->xslen;

     /* SJM 09/29/03 - change to handle sign extension and separate types */
     if (xsp->xslen > blen) __narrow_sizchg(xsp, blen);
     else if (xsp->xslen < blen)
      {
       if (cap->rhsx->has_sign) __sgn_xtnd_widen(xsp, blen);
       else __sizchg_widen(xsp, blen);
      }

     /* LOOKATME - only strength continuous assignments widen to z */
     /* all others widen to 0 unless during initialization when x */
     /* ??? if (orhslen < xsp->xslen) __fix_widened_tozs(xsp, orhslen); */
     /* SJM 05/10/04 - widening to x's eliminates need for sign difference */
     if (__wire_init) __fix_widened_toxs(xsp, orhslen);
    }
   return(xsp);
  }
 /* case 2: multi-fi or delay - know driver rhs exists */
 /* but if delay 0 no scheduled (since same) */
 push_xstk_(xsp, blen);
 /* know this is exactly lhs width */
 __ld_val(xsp->ap, xsp->bp, &(__idp[cap->ca_drv_ofs]), blen); 
 return(xsp);
}

/*
 * load a tf_ task/func argument rw parameter driver
 *
 * caller must have moved to right itree loc. for xmr form
 * never strength
 */
extern struct xstk_t *__ld_tfrwarg_driver(struct net_pin_t *npp)
{
 int32 blen;
 struct xstk_t *xsp;
 struct tfrec_t *tfrp;
 struct tfarg_t *tfap;
 struct expr_t *xp;

 tfrp = npp->elnpp.etfrp;
 tfap = &(tfrp->tfargs[npp->obnum]);
 xp = tfap->arg.axp;
 blen = xp->szu.xclen;
 if (tfap->tfdrv_wp.wp == NULL)
  {
   xsp = __eval2_xpr(xp);
   /* here because lhs is width self determing should never differ */
   /* DBG remove */
   if (blen != xsp->xslen) __misc_terr(__FILE__, __LINE__);
   /* -- */ 
   return(xsp);
  }
 /* case 2: multi-fi */
 push_xstk_(xsp, blen);
 /* know this is exactly lhs r/w arg width */
 __ld_perinst_val(xsp->ap, xsp->bp, tfap->tfdrv_wp, blen); 
 return(xsp);
}

/*
 * load a vpi put value wire driver (non strength case)
 *
 * always entire wire stored (bits with no drivers will be z)
 * obnum is index into possibly multiple drivers
 *
 * for the net bit case must load entire (allowing sharing of driver storage
 * for per bit) then select out the needed bit which is later combined in
 *
 * if any bits unused z's will never be seen
 */
extern struct xstk_t *__ld_vpiputv_driver(struct net_pin_t *npp)
{
 int32 bi;
 struct net_t *np;
 struct xstk_t *xsp;
 struct vpi_drv_t *drvp;

 np = npp->elnpp.enp;
 drvp = np->vpi_ndrvs[npp->obnum];
 push_xstk_(xsp, np->nwid);
 __ld_perinst_val(xsp->ap, xsp->bp, drvp->vpi_drvwp, np->nwid); 
 if (npp->npaux != NULL && (bi = npp->npaux->nbi1) != -1)
  {
   word32 av, bv;
    
   av = rhsbsel_(xsp->ap, bi);
   bv = rhsbsel_(xsp->bp, bi);
   __pop_xstk();
   push_xstk_(xsp, 1);
   xsp->ap[0] = av;
   xsp->bp[0] = bv;
  }
 return(xsp);
}

/*
 * load a gate driver npp - also for strength case
 * caller must have moved to right itree loc. for xmr form
 */
extern struct xstk_t *__ld_gate_driver(struct net_pin_t *npp)
{
 struct xstk_t *xsp;
 word32 uwrd;
 int32 has_stren;

 /* load output port - must remove strengths since wire is non strength */
 push_xstk_(xsp, 1);
 uwrd = __ld_gate_out(npp->elnpp.egp, &has_stren);
 /* this must load value and remove strength since drives constant */
 /* notice this is non stren case - stren passing gates not proc. here */
 xsp->ap[0] = uwrd & 1L;
 xsp->bp[0] = (uwrd >> 1) & 1L;
 return(xsp);
}

/*
 * load a gate or udp output - value determined from gate type
 * and set has_stren and return stren byte value if gate drives st.
 * some gates always drive varying stren or some have constant non
 * (st0,st1) strength
 *
 * this is passed net pin since need pin number for trans
 */
extern word32 __ld_gate_out(struct gate_t *gp, int32 *has_stren)
{
 int32 nins;
 word32 wrd, uwrd;
 struct udp_t *udpp;

 /* here just using a part of stack */ 
 *has_stren = FALSE;
 nins = gp->gpnum - 1;
 switch ((byte) gp->g_class) {
  case GC_UDP:
   udpp = gp->gmsym->el.eudpp;
   if (!udpp->u_wide)
    wrd = (__idp[gp->gstate_ofs] >> (2*nins)) & 3L;
   else wrd = (__idp[gp->gstate_ofs] >> (2*nins)) & 3L;
   /* must or in driving strength - if (st0,st1) already removed */
   /* key here is that know wire driven is n_stren */
   /* state here does not have strength */
adjust_stren:
   if (gp->g_hasst)
    {
     /* z value does not have strength */
     if (wrd != 2) wrd |= (gp->g_stval << 2L);
     wrd = (word32) __stren_map_tab[wrd];
     *has_stren = TRUE;
    }
   break;
  case GC_LOGIC:
   /* AIV 06/13/07 - can still get here during compilation due to */
   /* __eval_tran_drvrs need to handle new code which uses seperated */
   /* output storage area */
   if (nins > 15) wrd = widegate_ld_bit(&(__idp[gp->gstate_ofs]), nins + 1,
     nins);
   else
    {
     /* AIV 06/13/07 - if compiled sim output is stored seperately */
     /* just access according to inum and return */
     if (__compiled_sim)
      {
       wrd = __idp[gp->gate_out_ofs];
      }
     else
      {
       wrd = __idp[gp->gstate_ofs];
       wrd = ((wrd >> nins) & 1L) | (((wrd >> (2*nins + 1)) & 1L) << 1);
      }
    }
   if (gp->g_hasst) goto adjust_stren;
   break;
  case GC_BUFIF:
   /* AIV 06/13/07 - can still get here during compilation due to */
   /* __eval_tran_drvrs need to handle new code which uses seperated */
   /* AIV 06/13/07 - if compiled sim output is stored seperately */
   /* just access according from idp and return */
   if (__compiled_sim)
    {
     wrd = __idp[gp->gate_out_ofs];
    }
   else
    {
     uwrd = __idp[gp->gstate_ofs];
     wrd = (uwrd >> 4) & 0xff;
    }
   *has_stren = TRUE;
  break;
  case GC_MOS: 
   /* state here has strength */
   /* AIV 11/20/07 - can still get here during compilation due to */
   /* count drivers, etc */
   if (__compiled_sim) wrd = __idp[gp->gate_out_ofs];
   else wrd = (__idp[gp->gstate_ofs] >> 16) & 0xffL;
   *has_stren = TRUE;
   break;
  case GC_CMOS:
   *has_stren = TRUE;
   /* AIV 11/20/07 - can still get here during compilation due to */
   /* count drivers, etc */
   if (__compiled_sim) wrd = __idp[gp->gate_out_ofs];
   else wrd = (__idp[gp->gstate_ofs] >> 24) & 0xffL;
   break;
  default: __case_terr(__FILE__, __LINE__); wrd = 0;
 }
 return(wrd);
}

/*
 * load a gate or udp input - value determined from gate type
 * and set has_stren and return stren byte value if input has strength
 *
 * pin number pi starts from 1 for first input since output is 0
 */
extern word32 __ld_gate_in(struct gate_t *gp, int32 pi, int32 *has_stren)
{
 int32 nins;
 word32 wrd, uwrd, tmp;

 /* here just using a part of stack */ 
 *has_stren = FALSE;
 nins = gp->gpnum - 1;
 wrd = 0;
 switch ((byte) gp->g_class) {
  case GC_UDP:
   uwrd = (__idp[gp->gstate_ofs]);
   wrd = (uwrd >> (pi - 1)) & 1;
   tmp = (uwrd >> (nins + pi - 1)) & 1;
   wrd |= (tmp << 1);
   break;
  case GC_LOGIC:
   if (nins > 15) 
    {
     wrd = widegate_ld_bit(&(__idp[gp->gstate_ofs]), nins + 1, pi - 1);
    }
   else
    {
     wrd = __idp[gp->gstate_ofs];
     wrd = ((wrd >> (pi - 1)) & 1L) | (((wrd >> (nins + pi - 1)) & 1L) << 1);
    }
   break;
  case GC_BUFIF:
   uwrd = __idp[gp->gstate_ofs];
   if (pi == 1) wrd = (uwrd & 3);
   else if (pi == 2) wrd = (uwrd >> 2) & 3;
   else __case_terr(__FILE__, __LINE__);
   break;
  case GC_MOS: 
   /* state here has strength */
   uwrd = __idp[gp->gstate_ofs];
   if (pi == 1) { *has_stren = TRUE; wrd = (uwrd & 0xff); }
   else if (pi == 2) wrd = ((uwrd >> 8) & 3);
   else __case_terr(__FILE__, __LINE__);
   break;
  case GC_CMOS:
   /* this has one stren data input and 2 control inputs */
   uwrd = __idp[gp->gstate_ofs];
   if (pi == 1) { *has_stren = TRUE; wrd = uwrd & 0xff; }
   /* AIV 10/17/11 - this should be uwrd not wrd - was always wrong */
   else if (pi == 2) wrd = (uwrd >> 8) & 3;
   else if (pi == 3) wrd = (uwrd >> 16) & 3;
   else __case_terr(__FILE__, __LINE__);
   break;
  default: __case_terr(__FILE__, __LINE__); wrd = 0;
 }
 return(wrd);
}

/* 
 * load the output bit for wide gate
 * format for wide gate is a part in one word32 group, b in other  
 * bit 0 is 0 (inputs [0:nins - 1]), output is bit nins
 */
static word32 widegate_ld_bit(word32 *gsp, int32 gwid, int32 biti)
{
 int32 wlen, inum;
 word32 av, bv, *rap;

 /* rap is start of instance coded vector a b groups */
 wlen = wlen_(gwid);
 inum = get_inum_();
 rap = &(gsp[2*wlen*inum]);
 av = rhsbsel_(rap, biti);
 bv = rhsbsel_(&(rap[wlen]), biti);
 return(av | (bv << 1));
}

/*
 * load a iconn (down module port rhs to up iconn lhs) driver npp
 * caller must have moved to right itree loc. for xmr form
 *
 * driver is down module output port (inout handled in switch channel) 
 * called from up iconn itree location
 */
extern struct xstk_t *__ld_iconn_up_driver(struct net_pin_t *npp)
{
 int32 orhslen;
 struct mod_pin_t *mpp;
 struct expr_t *xlhs;
 struct itree_t *itp;
 struct xstk_t *xsp;
 struct mod_t *downmdp;
 struct itree_t *cur_itp;
 decl_idp_locals_;

 cur_itp = get_itp_();
 itp = &(cur_itp->in_its[npp->elnpp.eii]);
 downmdp = itp->itip->imsym->el.emdp;
 mpp = &(downmdp->mpins[npp->obnum]);
 /* notice this can never be xmr */
 set_save_idp_itp_(itp); 
 xsp = __eval2_xpr(mpp->mpref);

 /* lvalue is iconn pos. port number */ 
 xlhs = itp->itip->ipins[npp->obnum];
 /* needed iconn connection width may differ from port width */
 if (xlhs->szu.xclen != xsp->xslen)
  {
   orhslen = xsp->xslen;

   /* SJM 09/29/03 - change to handle sign extension and separate types */
   if (xsp->xslen > xlhs->szu.xclen)
    __narrow_sizchg(xsp, xlhs->szu.xclen);
   else if (xsp->xslen < xlhs->szu.xclen)
    {
     if (mpp->mpref->has_sign) __sgn_xtnd_widen(xsp, xlhs->szu.xclen);
     else __sizchg_widen(xsp, xlhs->szu.xclen);
    }

   /* LOOKATME - only strength continuous assignments widen to z */
   /* all others widen to 0 */
   /* ??? if (orhslen < xlhs->szu.xclen) __fix_widened_tozs(xsp, orhslen); */
   /* SJM 05/10/04 - widening to x's eliminates need for sign difference */
   if (__wire_init) __fix_widened_toxs(xsp, orhslen);
  }
 restore_idp_();
 return(xsp);
}

/*
 * load per bit iconn (down module port rhs to up iconn lhs) driver npp
 * caller must have moved to right itree loc. if xmr form
 *
 * driver is down module output port (inouts handled in tran channels)
 * called from up iconn itree location
 */
extern struct xstk_t *__ld_pb_iconn_up_driver(struct net_pin_t *npp)
{
 struct mod_pin_t *mpp;
 struct itree_t *itp;
 struct xstk_t *xsp;
 struct mod_t *downmdp;
 struct itree_t *cur_itp;
 decl_idp_locals_;

 cur_itp = get_itp_();
 itp = &(cur_itp->in_its[npp->elnpp.eii]);
 downmdp = itp->itip->imsym->el.emdp;
 mpp = &(downmdp->mpins[npp->obnum]);
 mpp = &(mpp->pbmpps[npp->pbi]);
 /* notice this can never be xmr */
 set_save_idp_itp_(itp); 
 xsp = __eval2_xpr(mpp->mpref);
 restore_idp_();

 /* lvalue is iconn pos. port number */ 
 /* since per bit, never need size convert */
 /* DBG remove --
 {
  struct expr_t *xlhs;

  xlhs = itp->itip->pb_ipins_tab[npp->obnum][npp->pbi];
  if (mpp->mpref->szu.xclen != xsp->xslen) __misc_terr(__FILE__, __LINE__);
 }
 --- */

 return(xsp);
}

/*
 * load a mod. port (up iconn rhs to down mod port lhs) driver npp
 *
 * xmr form impossible here
 * driver is up iconn rhs connection for input port
 * called from down module itree location
 */
extern struct xstk_t *__ld_modport_down_driver(struct net_pin_t *npp)
{
 int32 orhslen;
 struct xstk_t *xsp;
 struct mod_pin_t *mpp;
 struct itree_t *itp;
 struct mod_t *downmdp;
 struct expr_t *xlhs, *up_rhsx;
 decl_idp_locals_;

 itp = get_itp_();
 /* --- DBG remove
 if (itp->up_it == NULL) __misc_terr(__FILE__, __LINE__);
 --- */
 downmdp = get_inst_mod_();

 /* instance of lhs has module type that provides port lhs expr. */
 up_rhsx = itp->itip->ipins[npp->obnum];
 /* but variables in ndp come from inside up instance's module */
 set_save_idp_itp_(itp->up_it); 
 /* this may access from different itree place if iconn xmr */
 xsp = __eval2_xpr(up_rhsx);

 /* up iconn width may differ from port width */
 mpp = &(downmdp->mpins[npp->obnum]);
 xlhs = mpp->mpref;
 if (xlhs->szu.xclen != xsp->xslen)
  {
   orhslen = xsp->xslen;
   /* SJM 09/29/03 - change to handle sign extension and separate types */
   if (xsp->xslen > xlhs->szu.xclen)
    __narrow_sizchg(xsp, xlhs->szu.xclen);
   else if (xsp->xslen < xlhs->szu.xclen)
    {
     if (up_rhsx->has_sign) __sgn_xtnd_widen(xsp, xlhs->szu.xclen);
     else __sizchg_widen(xsp, xlhs->szu.xclen);
    }

   /* LOOKATME - only strength continuous assignments widen to z */
   /* all others widen to 0 */
   /* ?? if (orhslen < xlhs->szu.xclen) __fix_widened_tozs(xsp, orhslen); */
   /* SJM 05/10/04 - widening to x's eliminates need for sign difference */
   if (__wire_init) __fix_widened_toxs(xsp, orhslen);
  }
 restore_idp_();
 return(xsp); 
}

/*
 * load per bit mod. port (up iconn rhs to down mod port lhs) driver npp
 * for input ports where high conn is concat
 *
 * xmr form impossible here
 * driver of this down iput port is up highconn iconn rhs expr
 * called from down module itree location
 */
extern struct xstk_t *__ld_pb_modport_down_driver(struct net_pin_t *npp)
{
 struct xstk_t *xsp;
 struct itree_t *itp;
 struct expr_t *up_rhsx;
 decl_idp_locals_;

 itp = get_itp_();
 /* --- DBG remove
 if (itp->up_it == NULL) __misc_terr(__FILE__, __LINE__);
 --- */

 /* instance of lhs has module type that provides port lhs expr. */
 up_rhsx = itp->itip->pb_ipins_tab[npp->obnum][npp->pbi];
 /* but variables in ndp come from inside up instance's module */

 set_save_idp_itp_(itp->up_it); 
 /* this may access from different itree place if iconn xmr */
 /* FIXME ??? - since up rhs decomposes into 1 bit, this can be faster */
 xsp = __eval2_xpr(up_rhsx);
 restore_idp_();

 /* since per bit, never need size convert */
 /* DBG remove --
 {
  struct mod_pin_t *mpp;
  struct mod_t *downmdp;

  downmdp = itp->itip->imsym->el.emdp;
  mpp = &(downmdp->mpins[npp->obnum]);
  mpp = &(mpp->pbmpps[npp->pbi]);
  if (mpp->mpref->szu.xclen != xsp->xslen) __misc_terr(__FILE__, __LINE__);
 }
 --- */

 return(xsp); 
}

/*
 * ROUTINES TO COMBINE DRIVERS USING NON-STRENGTH RULES
 */

/*
 * apply values from npp npcxsp to a/b accumulator for net pin npp
 *
 * this is for non strength case
 * wire here is used for type - does not need itree place
 * can pass entire wire since section evaled determined by passed npp
 *
 * SJM 11/13/02 - not handling IS -2 per inst param range select right
 * SJM 11/15/02 - need to pass the a/b word32 ptr so can call from compiled
 *
 * FIXME - think this can never happen
 */
extern void __eval_wire(word32 *acc_wp, word32 *drv_wp, struct net_t *np,
 struct net_pin_t *npp)
{
 struct npaux_t *npauxp;
 word32 resa, resb, *wp;
 int32 wlen, pselwid, i1, i2, inum;
 struct xstk_t *tmpxsp;

 wlen = wlen_(np->nwid);
 /* entire wire */
 if ((npauxp = npp->npaux) == NULL || npauxp->nbi1 == -1)
  {
   if (np->nwid > WBITS)
    {
     __eval_wide_wire(acc_wp, &(acc_wp[wlen]), drv_wp, &(drv_wp[wlen]),
      np->nwid, np->ntyp);
    } 
   else __eval_1w_nonstren(acc_wp, &(acc_wp[1]), drv_wp[0], drv_wp[1],
    np->ntyp);
   return;
  }

 /* know that driver is section of lhs wire - i.e. lhs select decl assign */
 /* know npaux field exists */
 if (npauxp->nbi1 == -2)
  {
   /* SJM 10/12/04 - because contab realloced, must be ndx base of IS */
   inum = get_inum_();
   wp = &(__contab[npauxp->nbi2.xvi]);
   wp = &(wp[2*inum]);
   i1 = i2 = (int32) wp[0];
  }
 else { i1 = npauxp->nbi1; i2 = npauxp->nbi2.i; }
 if (i1 == i2) 
  {
   resa = rhsbsel_(acc_wp, i1);
   resb = rhsbsel_(&(acc_wp[wlen]), i1);
   /* know thing driving wire is 1 bit - will eval. to 1 bit */
   __eval_1w_nonstren(&resa, &resb, drv_wp[0], drv_wp[1], np->ntyp);
   /* assign back to bit */
   __lhsbsel(acc_wp, i1, resa);
   __lhsbsel(&(acc_wp[wlen]), i1, resb);
   return;
  }

 /* part select inefficient but think still better than if done bit by bit */
 /* part select - net pin range is normalized */
 pselwid = i1 - i2 + 1; 
 /* load accumulator region into tmp xsp */ 
 push_xstk_(tmpxsp, pselwid);
 __rhspsel(tmpxsp->ap, acc_wp, i2, pselwid); 
 __rhspsel(tmpxsp->bp, &(acc_wp[wlen]), i2, pselwid); 

 /* eval. - notice if fits in 1 word32 do not need width */
 if (pselwid > WBITS)
  __eval_wide_wire(tmpxsp->ap, tmpxsp->bp, drv_wp, &(drv_wp[wlen_(pselwid)]),
   pselwid, np->ntyp);
 /*11/21/2002 AIV was nwid for the last arg should be type*/
 else __eval_1w_nonstren(tmpxsp->ap, tmpxsp->bp, drv_wp[0], drv_wp[1],
  np->ntyp);

 /* store back into accumulator */
 __lhspsel(acc_wp, i2, tmpxsp->ap, pselwid); 
 __lhspsel(&(acc_wp[wlen]), i2, tmpxsp->bp, pselwid); 
 __pop_xstk();
}

/*
 * evaluate stack elements into depending on wire type
 * any selection handled above here rxsp and xsp1 can be same
 * since all have same width here, no need to remove unused bits
 *
 * SJM 11/15/02 - change so pass a/b word32 ptrs so compiled code can call
 */
extern void __eval_wide_wire(word32 *acc_ap, word32 *acc_bp,
 word32 *drv_ap, word32 *drv_bp, int32 opbits, word32 wtyp)
{
 int32 wi;

 /* DBG remove - only these can have multi-fi and no strength */
 /* tri0, tri1 and trireg always strength -- 
 switch ((byte) wtyp) {
  case N_WIRE: case N_TRI: case N_TRIAND: case N_WA: case N_TRIOR: case N_WO:
   break;
  default: __case_terr(__FILE__, __LINE__);
 }
 --- */
 for (wi = 0; wi < wlen_(opbits); wi++)
  {
   __eval_1w_nonstren(&(acc_ap[wi]), &(acc_bp[wi]), drv_ap[wi],
    drv_bp[wi], wtyp);
  }
}

/*
 * evaluate a 1 word32 normal tri wire
 * notice res and op can be same object since op by value
 * for non strength case if one z, use other, if both z leave as z 
 * since fits in one bit do not need width - high bits will just be 0
 *
 * eval is word32 by word32 then after stren competition, used section
 * extracted with select if needed
 *
 * LOOKATME - think this can never happen
 */
extern void __eval_1w_nonstren(word32 *resa, word32 *resb, word32 op2a,
 word32 op2b, word32 wtyp)
{
 word32 zmask, donemask;
 word32 op1a, op1b;

 op1a = resa[0];
 op1b = resb[0];
 /* first all bits that are the same - common case */
 /* notice wand and wor same bits always same */
 /* unused bits handled here - since will both be 0 */
 /* mask has 1 if same else 0 */
 zmask = ~((op1a ^ op2a) | (op1b ^ op2b));
 resa[0] = op1a & zmask;
 resb[0] = op1b & zmask;
 donemask = zmask;
 if (donemask == __masktab[0]) goto done;

 /* next op1 z bits, use op2 bits */
 zmask = (op1a ^ op1b) & op1b; 
 /* if z in op1, value is op2 */
 resa[0] |= (op2a & zmask);
 resb[0] |= (op2b & zmask);
 donemask |= zmask;
 if (donemask == __masktab[0]) goto done;

 /* next op2 zbits, use op1 bits */
 zmask = (op2a ^ op2b) & op2b; 
 /* if z in op2, value is op2 */
 resa[0] |= op1a & zmask;
 resb[0] |= op1b & zmask;
 donemask |= zmask; 
 if (donemask == __masktab[0]) goto done;

 zmask = ~donemask;
 /* finally net type determines algorithm - know b bit 0 for these bits */
 switch ((byte) wtyp) {
  case N_WIRE: case N_TRI:
   /* know remaining bits must be x, neither and not the same */
   resa[0] |= zmask; resb[0] |= zmask;
   break;
  case N_TRIAND: case N_WA:
   /* if either 0, result 0, else x, since 1 1 done */ 
   resa[0] |= ((op1a | op1b) & (op2a | op2b)) & zmask;
   resb[0] |= (resa[0] & (op1b | op2b)) & zmask;
   break;  
  case N_TRIOR: case N_WO:
   resb[0]
    |= ((op2b ^ op1b ^ ((op1a | op1b) & (op2b | (op2a & op1b)))) & zmask);
   resa[0] |= ((resb[0] | op2a | op1a) & zmask);
   break;
  default: __case_terr(__FILE__, __LINE__);
 }
done:
 /* DBG --- */
 if (__debug_flg && __ev_tracing) 
  {
   char s1[RECLEN];

   __tr_msg(
    "+> fi>1 nonstren: %s op1a=%lx,op1b=%lx,op2a=%lx,op2b=%lx,resa=%lx,resb=%lx,zmask=%lx\n", 
    __to_wtnam2(s1, wtyp), op1a, op1b, op2a, op2b, resa[0], resb[0], zmask);
  }
 /* --- */
}

/*
 * MULTI FAN IN STRENGTH WIRE ASSIGN ROUTINES
 * ALL STRENGTH ASSIGN THROUGH HERE
 */

/*
 * load an entire strength wire value onto top of stack
 * by evaluating all drivers
 *
 * for normal wire itstk must be lhs wire place - for mod. in this is down
 * (rhs up) and for inst. output this is up (rhs down) 
 * for xmr wire current itree place is target (define) inst of wire
 *
 * the driver evaluation may change to xmr itree place but always restores
 *
 * loads only hard drivers - tran channel code handles tran components
 */
extern struct xstk_t *__stload_mdrwire(struct net_t *np)
{
 struct net_pin_t *npp;
 struct xstk_t *xsp;
 byte *sbp;

 /* allocate accumulator - initialize all bits to z in case not driven */
 /* notice built in 8 bits per byte but also no b part so need half size */
 xsp = init_stwire_accum(np);
 sbp = (byte *) xsp->ap;

 /* evaluation of every net and channel driver against current accum. value */
 for (npp = np->ndrvs; npp != NULL; npp = npp->npnxt)
  {
   /* filter new rooted and up. rel col. forms */ 
   if (npp->npproctyp == NP_PROC_FILT && npp->npaux->npu.filtidp != __idp)
    continue;

   ldcomb_stdriver(sbp, np, npp);
  }
 return(xsp);
}

/*
 * load and combine in to passed z initial acumulator the driver for 1 val
 * may not add if npp does not apply to this inst. or driver off
 */
static void ldcomb_stdriver(byte *acc_sbp, struct net_t *np,
 struct net_pin_t *npp)
{
 int32 i1, inum;
 byte *sbp2;
 struct xstk_t *xsp;
 word32 *wp;
 byte *sbp;
 struct npaux_t *npauxp;
 struct itree_t *itp;
 decl_idp_locals_;

 /* DBG remove ---
 if (__debug_flg && __ev_tracing)
  {
   __tr_msg("## loading %s strength driver of wire %s\n",
    __to_npptyp(__xs, npp), np->nsym->synam);
  }
 --- */

 /* trace from target (definition location) back to ref. inst. itree loc */
 save_idp = NULL;
 if (npp->npproctyp != NP_PROC_INMOD)
  {
   /* SJM 04/17/03 - if XMR does not match - do not combine in */
   if ((itp = __get_npprefloc(npp)) == NULL) return;
   set_save_idp_itp_(itp); 
  }

 /* load driver onto new top of stack (this always pushes) */
 /* know rhs driver width will be changed to match lhs width exactly */

 switch ((byte) npp->npntyp) {
  case NP_CONTA: xsp = ld_stconta_driver(npp); break;
  case NP_TFRWARG: xsp = __ld_sttfrwarg_driver(npp); break;
  case NP_VPIPUTV: xsp = ld_stvpiputv_driver(npp); break;
  case NP_GATE: xsp = ld_stgate_driver(npp); break;
  /* these are up to highconn strength output port drivers */
  case NP_ICONN: xsp = ld_sticonn_up_driver(npp); break;
  case NP_PB_ICONN: xsp = ld_pb_sticonn_up_driver(npp); break;
  /* these are down to lowconn strength input port drivers */
  case NP_MDPRT: xsp = ld_stmodport_down_driver(npp); break;
  case NP_PB_MDPRT: xsp = ld_pb_stmodport_down_driver(npp); break;
  case NP_PULL: xsp = ld_stpull_driver(npp); break;
  /* TRAN impossible here */
  default: __case_terr(__FILE__, __LINE__); xsp = NULL;
 }
 if (save_idp != NULL)
  {
   restore_idp_();
  }

 /* SJM 07/08/00 - need high z's if gate driver or narrow conta */
 /* need at least when stren gate output drives vector */ 
 /* SJM 11/11/02 - slightly wrong - works because only needed for gate */
 /* wich never has lhs concat sink */

 /* SJM 05/10/04 - no sign extension because widening to z'x */
 if (xsp->xslen/4 < np->nwid) __strenwiden_sizchg(xsp, np->nwid);

 sbp = (byte *) xsp->ap;

 /* first if this is lhs concat, must isolate relevant from rhs (sbp2) */
 /* all indices normalized here to h:0 */
 if ((npauxp = npp->npaux) != NULL && npauxp->lcbi1 != -1)
  sbp2 = &(sbp[npauxp->lcbi2]);
 else sbp2 = sbp;
 /* first entire wire case */
 if (npauxp == NULL || npauxp->nbi1 == -1)
  {
   __eval_stwire(acc_sbp, np->ntyp, np->nwid - 1, 0, sbp2);
   goto done;
  }
 /* IS bit select cases */
 if (npauxp->nbi1 == -2)
  {
   /* SJM 10/12/04 - because contab realloced, must be ndx base of IS */
   wp = &(__contab[npauxp->nbi2.xvi]);
   inum = get_inum_();
   wp = &(wp[2*inum]);
   i1 = (int32) wp[0];
   /* here strength competition of sbp2[0] against sbp[i1] accum. */
   __eval_stwire(acc_sbp, np->ntyp, i1, i1, sbp2);
   goto done;
  }
 /* --- DBG
 if (__debug_flg) __st_regab_tostr(s1, acc_sbp, np->nwid);
 --- */ 

 /* finally competition of accum sbp[nbi1:nbi2] to low of sbp2 */
 __eval_stwire(acc_sbp, np->ntyp, npauxp->nbi1, npauxp->nbi2.i, sbp2);

 /* --- DBG 
 if (__debug_flg)
  {
   int32 ti1, ti2, lci1, lci2;
   char s2[RECLEN], s3[RECLEN];

   if ((npauxp = npp->npaux) != NULL) 
    {
     ti1 = npauxp->nbi1;
     ti2 = npauxp->nbi2.i;
     lci1 = npauxp->lcbi1;
     lci2 = npauxp->lcbi2;
    }
   else ti1 = ti2 = lci1 = lci2 = -1;

   __dbg_msg(
    "## stren driver before %s, after %s,\n  value %s, rhs [%d:%d] lhs [%d:%d]\n",
    s1, __st_regab_tostr(s2, acc_sbp, np->nwid), __st_regab_tostr(s3, sbp2,
    ti1 - ti2 + 1), lci1, lci2, ti1, ti2);
  }
 --- */
done: 
 __pop_xstk();
}

/*
 * initialize a wire for multi-fi combination (depends on wire type)
 * this push value on to expr. stack
 */
static struct xstk_t *init_stwire_accum(struct net_t *np)
{
 byte *sbp;
 struct xstk_t *xsp;
 byte stval;

 push_xstk_(xsp, 4*np->nwid);
 sbp = (byte *) xsp->ap;

 /* 0,0,2 is high z */
 /* initialize in case unc., */
 switch ((byte) np->ntyp) {
  case N_TRI0: stval = ST_PULL0; goto set_stren;
  case N_TRI1: stval = ST_PULL1; goto set_stren;
  case N_SUPPLY0:
   set_byteval_(sbp, np->nwid, ST_SUPPLY0);
   return(xsp);
  case N_SUPPLY1:
   set_byteval_(sbp, np->nwid, ST_SUPPLY1);
   return(xsp);
  default:
   stval = ST_HIZ;
set_stren:
  set_byteval_(sbp, np->nwid, stval);
 }
 return(xsp);
}

/*
 * load a wire's driven value (maybe not driven z) on to top of stack
 * routines called from here must do stack pushing themselves
 *
 * this is only called by count drivers
 */
extern struct xstk_t *__ld_stwire_driver(struct net_pin_t *npp)
{
 struct xstk_t *xsp; 
 struct itree_t *itp;
 decl_idp_locals_;

 /* move from target back to itree loc of ref. */ 
 save_idp = NULL;
 if (npp->npproctyp != NP_PROC_INMOD)
  {
   /* SJM 04/17/03 - if XMR does not match - do not combine in */
   if ((itp = __get_npprefloc(npp)) == NULL) return(NULL);
   set_save_idp_itp_(itp); 
  }

 /* this puts the driving value (normal rhs with rhs width) on stack */
 /* notice md port or tran or iconn may return nil, caller does not pop */
 switch ((byte) npp->npntyp) {
  case NP_CONTA: xsp = ld_stconta_driver(npp); break;
  case NP_TFRWARG: xsp = __ld_sttfrwarg_driver(npp); break;
  case NP_VPIPUTV: xsp = ld_stvpiputv_driver(npp); break;
  case NP_GATE: xsp = ld_stgate_driver(npp); break;
  /* these are up to highconn strength output port drivers */
  case NP_ICONN: xsp = ld_sticonn_up_driver(npp); break;
  case NP_PB_ICONN: xsp = ld_pb_sticonn_up_driver(npp); break;
  /* these are down to lowconn strength input port drivers */
  case NP_MDPRT: xsp = ld_stmodport_down_driver(npp); break;
  case NP_PB_MDPRT: xsp = ld_pb_stmodport_down_driver(npp); break;
  default: __case_terr(__FILE__, __LINE__); return(NULL);
 }
 if (save_idp != NULL)
  {
   restore_idp_();
  }
 return(xsp);
}

/*
 * load a strength gate driver npp
 * caller must have moved to right itree loc. for xmr form
 */
static struct xstk_t *ld_stgate_driver(struct net_pin_t *npp)
{
 int32 has_stren;
 struct xstk_t *xsp;
 byte *sbp;

 /* here must add (st0,st0) if no strength */
 push_xstk_(xsp, 4);
 sbp = (byte *) xsp->ap;
 sbp[0] = (byte) __ld_gate_out(npp->elnpp.egp, &has_stren);
 if (!has_stren && sbp[0] != 2) sbp[0] |= (ST_STRVAL << 2); 
 return(xsp);
}

/*
 * load a strength continuous assignment (not port conta) driver npp
 * caller must have moved to right itree loc. for xmr form
 *
 * for rhs concat separated into per bit, this is PB conta el
 */
static struct xstk_t *ld_stconta_driver(struct net_pin_t *npp)
{
 int32 blen;
 struct xstk_t *xsp;
 struct conta_t *cap;
 int32 orhslen;
 byte *sbp; 
 struct xstk_t *xsp2;

 /* case 1: fi of 1 - driver if npp range of net itself */
 /* fi == 1 subcase only for driver (show vars) display */
 /* SJM 09/18/02 - no separate per bit NP type, checkfor pb sim on */
 cap = npp->elnpp.ecap;
 if (cap->ca_pb_sim) cap = &(cap->pbcau.pbcaps[npp->pbi]);

 blen = cap->lhsx->szu.xclen;
 /* if fi == 1 and no delay, no driver field driver is size changed rhs */
 /* could access lhs since should be same but this is consistency check */
 /* notice display whole wire with range value printed if cat */
 push_xstk_(xsp, 4*blen); 
 sbp = (byte *) xsp->ap;
 if (cap->ca_drv_ofs == 0)
  {
   xsp2 = __eval2_xpr(cap->rhsx);
   if (blen != xsp2->xslen)
    {
     orhslen = xsp2->xslen;

     /* SJM 09/29/03 - change to handle sign extension and separate types */
     /* SJM 06/20/05 - rare case but needs signed widen (stren maybe added?) */
     if (xsp2->xslen > blen) __narrow_sizchg(xsp2, blen);
     else if (xsp2->xslen < blen)
      {
       if (cap->rhsx->has_sign) __sgn_xtnd_widen(xsp2, blen);
       else __sizchg_widen(xsp2, blen);
      }

     if (__wire_init) __fix_widened_toxs(xsp2, orhslen);
    }
  }
 else
  {
   /* complicated has delay or multi-fi case, driver is saved value */
   /* know width will always be correct lhs */
   /* for multi-fi, must save driver else rhs may re-eval too many times */
   push_xstk_(xsp2, blen);
   __ld_val(xsp2->ap, xsp2->bp, &(__idp[cap->ca_drv_ofs]), blen);
  }
 /* add strength */
 __st_standval(sbp, xsp2, cap->ca_stval);
 __pop_xstk();
 return(xsp);
}

/*
 * load a tf_ task/func argument rw parameter strength driver
 * caller must have moved to right itree loc. for xmr form
 */
extern struct xstk_t *__ld_sttfrwarg_driver(struct net_pin_t *npp)
{
 int32 blen, inum;
 struct xstk_t *xsp;
 struct tfrec_t *tfrp;
 byte *sbp, *sbp2;
 struct tfarg_t *tfap;
 struct expr_t *xp;

 tfrp = npp->elnpp.etfrp;
 tfap = &(tfrp->tfargs[npp->obnum]);
 xp = tfap->arg.axp;
 blen = xp->szu.xclen;
 /* tf arg fi == 1 case */  
 if (tfap->tfdrv_wp.wp == NULL)
  {
   xsp = __ndst_eval_xpr(xp);
   /* know this is lhs so width loaded must be arg width */
   /* DBG remove */
   if (blen != xsp->xslen/4) __misc_terr(__FILE__, __LINE__);
   /* --- */
  }
 else
  {
   /* tf arg r/w lhs wire has multiple drivers */ 
   push_xstk_(xsp, 4*blen); 
   sbp = (byte *) xsp->ap;
   inum = get_inum_();
   sbp2 = &(tfap->tfdrv_wp.bp[inum*blen]);
   memcpy(sbp, sbp2, blen); 
  }
 return(xsp);
}

/*
 * load a putv added terminal strength driver
 *
 * inst. or bit may not have added driver if so will just load z's
 * z's do not hurt and faster to load entire wire
 */
static struct xstk_t *ld_stvpiputv_driver(struct net_pin_t *npp)
{
 int32 bi, inum;
 struct net_t *np;
 struct xstk_t *xsp;
 struct vpi_drv_t *drvp;
 byte *sbp, *sbp2;

 np = npp->elnpp.enp;
 drvp = np->vpi_ndrvs[npp->obnum];
 if (npp->npaux != NULL && (bi = npp->npaux->nbi1) != -1)
  {
   push_xstk_(xsp, 4);
   sbp = (byte *) xsp->ap;
   inum = get_inum_();
   sbp[0] = drvp->vpi_drvwp.bp[np->nwid*inum + bi];
   return(xsp);
  }
 /* SJM 08/11/00 - was wrongly not 4 times width so widen over-wrote hiz */
 push_xstk_(xsp, 4*np->nwid);
 sbp = (byte *) xsp->ap;
 inum = get_inum_();
 sbp2 = &(drvp->vpi_drvwp.bp[np->nwid*inum]);
 memcpy(sbp, sbp2, np->nwid);
 return(xsp);
}

/*
 * load a strength iconn (down module port rhs to up iconn lhs) driver npp
 * caller must have moved to right itree loc. for xmr form
 *
 * called from up iconn itree location
 */
static struct xstk_t *ld_sticonn_up_driver(struct net_pin_t *npp)
{
 struct xstk_t *xsp;
 struct mod_pin_t *mpp;
 struct expr_t *xlhs;
 struct itree_t *itp, *cur_itp;
 struct mod_t *downmdp;
 decl_idp_locals_;

 /* assign from down module port rhs into up iconn lhs expr. */
 /* driver is down module port - called with itree location of up */
 cur_itp = get_itp_();
 itp = &(cur_itp->in_its[npp->elnpp.eii]);
 downmdp = itp->itip->imsym->el.emdp;
 mpp = &(downmdp->mpins[npp->obnum]);
 xlhs = itp->itip->ipins[npp->obnum];

 /* this must load preserving strengths - here know mod. port has stren */
 /* inout port output half driver is always port value */
 set_save_idp_itp_(itp); 
 /* if down rhsx is reg, will add stron strength */ 
 xsp = __ndst_eval_xpr(mpp->mpref);

 /* only if rhs too narrow, need to add in HIZ and maybe widen alloc area */
 /* if too wide just ignores high bytes */
 if (xlhs->szu.xclen > mpp->mpref->szu.xclen)
  {
   /* SJM 05/10/04 - no sign extension because widening to z'x */
   __strenwiden_sizchg(xsp, xlhs->szu.xclen);
  }
 restore_idp_();
 return(xsp);
}

/*
 * load per bit stren iconn (down module port rhs to up iconn lhs) driver
 *
 * driver is down module output port
 * called from up iconn itree location
 * caller must have moved to right itree loc. for xmr form
 */
static struct xstk_t *ld_pb_sticonn_up_driver(struct net_pin_t *npp)
{
 struct xstk_t *xsp;
 struct mod_pin_t *mpp;
 struct itree_t *itp;
 struct mod_t *downmdp;
 struct itree_t *cur_itp;
 decl_idp_locals_;

 /* assign from down module port rhs into up iconn lhs expr. */
 /* driver is down module port - called with itree location of up */
 cur_itp = get_itp_();
 itp = &(cur_itp->in_its[npp->elnpp.eii]);
 downmdp = itp->itip->imsym->el.emdp;
 mpp = &(downmdp->mpins[npp->obnum]);
 mpp = &(mpp->pbmpps[npp->pbi]);

 /* this must load preserving strengths - here know mod. port has stren */
 /* inout port output half driver is always port value */
 set_save_idp_itp_(itp); 
 /* if down rhsx is reg, will add stron strength */ 
 xsp = __ndst_eval_xpr(mpp->mpref);
 restore_idp_();

 /* since per bit, never need size convert */
 /* DBG remove --
 {
  struct expr_t *lhsx;

  lhsx = itp->itip->pb_ipins_tab[npp->obnum][npp->pbi];
  if (lhsx->szu.xclen != xsp->xslen) __misc_terr(__FILE__, __LINE__);
 }
 --- */
 return(xsp);
}

/*
 * load a mod. port (up iconn rhs to down mod port lhs) driver npp
 *
 * xmr form impossible here
 * driver is down module input or inout port (strength model)
 * called from down module itree location
 */
static struct xstk_t *ld_stmodport_down_driver(struct net_pin_t *npp)
{
 struct mod_pin_t *mpp;
 struct itree_t *itp;
 struct xstk_t *xsp;
 struct mod_t *downmdp;
 struct expr_t *xlhs, *up_rhsx;
 decl_idp_locals_;

 itp = get_itp_();
 /* --- DBG remove
 if (itp->up_it == NULL) __misc_terr(__FILE__, __LINE__);
 --- */

 up_rhsx = itp->itip->ipins[npp->obnum];
 downmdp = get_inst_mod_();
 mpp = &(downmdp->mpins[npp->obnum]);
 xlhs = mpp->mpref;
 set_save_idp_itp_(itp->up_it); 
 /* if down rhsx is reg, will add strong */ 
 xsp = __ndst_eval_xpr(up_rhsx);
 /* only if rhs too narrow, need to add in HIZ and maybe widen alloc area */
 /* if too wide just ignores high bytes */
 /* SJM 05/10/04 - no sign extension because widening to z'x */
 if (xlhs->szu.xclen > up_rhsx->szu.xclen)
  __strenwiden_sizchg(xsp, xlhs->szu.xclen);
 restore_idp_();
 return(xsp);
}

/*
 * load a mod. port (up iconn rhs to down mod port lhs) driver npp
 *
 * xmr form impossible here
 * driver is down module input or inout port (strength model)
 * called from down module itree location
 */
static struct xstk_t *ld_pb_stmodport_down_driver(
 struct net_pin_t *npp)
{
 struct xstk_t *xsp;
 struct itree_t *itp;
 struct expr_t *up_rhsx;
 decl_idp_locals_;

 itp = get_itp_();
 /* --- DBG remove
 if (itp->up_it == NULL) __misc_terr(__FILE__, __LINE__);
 --- */

 set_save_idp_itp_(itp->up_it); 
 up_rhsx = itp->itip->pb_ipins_tab[npp->obnum][npp->pbi];
 /* if down rhsx is reg, will add strong */ 
 xsp = __ndst_eval_xpr(up_rhsx);

 /* since per bit never need size change */
 /* DBG remove --
 {
  struct mod_pin_t *mpp;
  struct mod_t *downmdp;

  downmdp = itp->itip->imsym->el.emdp;
  mpp = &(downmdp->mpins[npp->obnum]);
  mpp = &(mpp->pbmpps[npp->pbi]);
  if (mpp->mpref->szu.xclen > up_rhsx->szu.xclen)
   __misc_terr(__FILE__, __LINE__);
 }
 --- */

 restore_idp_();
 return(xsp);
}

/*
 * load a strength pull driver (only strength possible) 
 */
static struct xstk_t *ld_stpull_driver(struct net_pin_t *npp)
{
 struct xstk_t *xsp;
 byte *sbp;
 struct gate_t *gp;
 struct expr_t *ndp;

 /* get pull out lhs wire or select */
 gp = npp->elnpp.egp;
 ndp = gp->gpins[npp->obnum]; 
 push_xstk_(xsp, 4*ndp->szu.xclen);
 sbp = (byte *) xsp->ap;
 set_byteval_(sbp, ndp->szu.xclen, (byte) ((gp->g_stval << 2) | npp->pullval));
 return(xsp);
}

/*
 * STRENGTH EXPRESSION EVALUATION ROUTINES 
 */

/*
 * evaluate a rhs expression producing a strength format result
 * even if needs to add (st0,st1) for non strength expr.
 * this is equivalent of __eval_xpr when strength required
 *
 * pushes and pops temps and leaves result on top of reg stack
 * caller must pop value from stack
 * no stack checks underflow checks - maybe would help debugging
 */
extern struct xstk_t *__ndst_eval_xpr(struct expr_t *ndp)
{
 byte *sbp;
 struct xstk_t *stxsp;

 /* strength uses only a part of stack register */
 push_xstk_(stxsp, 4*ndp->szu.xclen);
 sbp = (byte *) stxsp->ap;
 ndst_eval2_xpr(sbp, ndp);
 return(stxsp);
}

/*
 * in place evaluate at least top node strength expression
 * this is for port feed thru assignments that pass strength thru
 * this does not leave value on top of stack
 */
static void ndst_eval2_xpr(byte *sbp, struct expr_t *ndp)
{
 byte *bp; 
 t_midat *xmr_idp;
 struct net_t *np;
 struct expr_t *idndp;
 struct gref_t *grp;
 struct xstk_t *xsp;
 decl_idp_locals_;

 /* possible for this to be non stength reg. where strong added */
 if (!ndp->x_stren)
  {
   xsp = __eval2_xpr(ndp);
   __st_standval(sbp, xsp, ST_STRVAL);
   __pop_xstk();
   return;
  }

 /* in this case, must put value on tos */
 save_idp = NULL;
 switch (ndp->optyp) {
  case UNCONNPULL:
   /* connection is unconnected but directives causes unc. to be pulled */
   /* know width here always exactly port width and stren */
   set_byteval_(sbp, ndp->szu.xclen, (ndp->unc_pull == UNCPULL0) ? ST_PULL0
    : ST_PULL1);
   return;
  case GLBREF:
   grp = ndp->ru.grp;
   xmr_idp = __xmrget_refgrp_to_targ(grp);
   set_save_idp_(xmr_idp); 
   /*FALLTHRU */
  case ID:
   np = ndp->lu.sy->el.enp;
   /* RELEASE remove ---
   if (!np->n_stren) __misc_terr(__FILE__, __LINE__);
   --- */
   /* get strength wire address */
   bp = (byte *) &(__idp[np->nva_ofs]);
   memcpy(sbp, bp, ndp->szu.xclen); 
   break;
  case LSB:
   /* can never be array */
   idndp = ndp->lu.x;
   /* SJM - 03/26/00 - was setting grp to bsel node not lhs id */
   if (idndp->optyp == GLBREF)
    { 
     grp = idndp->ru.grp;
     xmr_idp = __xmrget_refgrp_to_targ(grp);
     set_save_idp_(xmr_idp); 
    }
   access_stbsel(sbp, ndp);
   break;
  case PARTSEL:
   idndp = ndp->lu.x;
   /* SJM - 03/26/00 - was setting grp to bsel node not lhs id */
   if (idndp->optyp == GLBREF)
    { 
     grp = idndp->ru.grp; 
     xmr_idp = __xmrget_refgrp_to_targ(grp);
     set_save_idp_(xmr_idp); 
    }
   access_stpsel(sbp, ndp);
   break;
  case PARTSEL_NDX_PLUS:
  case PARTSEL_NDX_MINUS:
   access_width_index_stpsel(sbp, ndp);
   break;
  case LCB: rhs_stconcat(sbp, ndp); break;
  default: __case_terr(__FILE__, __LINE__);
 }
 if (save_idp != NULL)
  {
   restore_idp_();
  }
}

/*
 * access a selected bit to sbp (width 1 for bit)
 *
 * this if for cases where accessing strength and know it is needed and
 * know value has strength
 */
static void access_stbsel(byte *sbp, struct expr_t *ndp)
{
 int32 biti;
 byte *bp;
 struct net_t *np;

 np = ndp->lu.x->lu.sy->el.enp;
 biti = __get_idp_const_bselndx(ndp);
 /* unknown index is strong x - cannot emit warning happens too often */
 /* strong x 6,6,3 - 11011011 */
 if (biti == -1) { *sbp = 0xdb; return; }
 /* get strength wire address */
 bp = (byte *) &(__idp[np->nva_ofs]);
 *sbp = bp[biti]; 
}

/*
 * get a bit select index from an expr. node
 *
 * SJM 08-10-07 - version for prep where there is no idp area yet
 * i.e. caller must do a push itstk before calling this 
 *
 * only for constant index cases
 */
extern int32 __get_itp_const_bselndx(struct expr_t *ndp)
{
 int32 biti;
 word32 *wp;

 /* know will either be constant or expr. here */
 if (ndp->ru.x->optyp == NUMBER)
  {
   wp = &(__contab[ndp->ru.x->ru.xvi]);
   if (wp[1] != 0) biti = -1; else biti = (int32) wp[0];
  }
 else if (ndp->ru.x->optyp == ISNUMBER)
  {
   wp = &(__contab[ndp->ru.x->ru.xvi]);
   wp = &(wp[2*__inum]);
   if (wp[1] != 0) biti = -1; else biti = (int32) wp[0];
  }
 else { __case_terr(__FILE__, __LINE__); biti = -1; }
 return(biti);
}

/*
 * get a bit select index from an expr. node for run time when __idp set
 *
 * SJM 08-10-07 - version for simulation where there is an idp area
 * i.e. caller must have set __idp
 *
 * only for constant index cases
 */
extern int32 __get_idp_const_bselndx(struct expr_t *ndp)
{
 int32 biti, inum;
 word32 *wp;

 /* know will either be constant or expr. here */
 if (ndp->ru.x->optyp == NUMBER)
  {
   wp = &(__contab[ndp->ru.x->ru.xvi]);
   if (wp[1] != 0) biti = -1; else biti = (int32) wp[0];
  }
 else if (ndp->ru.x->optyp == ISNUMBER)
  {
   wp = &(__contab[ndp->ru.x->ru.xvi]);
   inum = get_inum_();
   wp = &(wp[2*inum]);
   if (wp[1] != 0) biti = -1; else biti = (int32) wp[0];
  }
 else { __case_terr(__FILE__, __LINE__); biti = -1; }
 return(biti);
}

/*
 * push (access) a selected range into sbp
 * one bit ok but cannot part select from scalar
 */
static void access_stpsel(byte *sbp, struct expr_t *ndp)
{
 int32 bi2;
 byte *abp;
 struct expr_t *idndp, *ndx2;
 struct net_t *np;

 /* know these are both constant nodes, in range, and are h:0 normalized */
 /* and non IS form */
 idndp = ndp->lu.x;
 np = idndp->lu.sy->el.enp;
 /* notice 2nd range is low */
 ndx2 = ndp->ru.x->ru.x;

 /* bi2 cannot be -1 (out of range) or will not get here */
 bi2 = (int32) __contab[ndx2->ru.xvi];

 /* get strength wire address */
 abp = (byte *) &(__idp[np->nva_ofs]);

 memcpy(sbp, &(abp[bi2]), ndp->szu.xclen);
}

/*
 * push (access) a selected range into sbp
 * for indexed width psel +: and -:
 */
static void access_width_index_stpsel(byte *sbp, struct expr_t *ndp)
{
 int32 bi1, bi2;
 byte *abp;
 struct net_t *np;

 /* just get indices and do psel */
 np = __get_indexed_psel_range(ndp, &bi1, &bi2);

 /* AIV 02/07/11 - if out of range do not store value */
 /* according to LRM - x/z values have no effect on written values */
 if (bi1 == -1) return;

 /* get strength wire address */
 abp = (byte *) &(__idp[np->nva_ofs]);

 memcpy(sbp, &(abp[bi2]), ndp->szu.xclen);
}

/*
 * evaluate a known strength expr node rhs concatenate
 * key is that { op. node width is same as starting high bit of value
 *
 * notice that subexpressions of strength concat can be non strength
 * strength stored low bit (0) to high bit (n)
 */
static void rhs_stconcat(byte *sbp, struct expr_t *lcbndp)
{
 int32 i, bi2;
 struct expr_t *ndp; 
 byte *sbp2;
 struct expr_t *catndp;

 for (ndp = lcbndp->ru.x; ndp != NULL; ndp = ndp->ru.x)
  {
   catndp = ndp->lu.x;

   /* bi2 is low bit, LCB node xclen start high bit, catndp is id/num width */
   bi2 = ndp->szu.xclen - catndp->szu.xclen;
   sbp2 = &(sbp[bi2]);
   /* here know cat width must match rhs width */
   ndst_eval2_xpr(sbp2, catndp);
  }
 if (__debug_flg && __ev_tracing)
  {
   __cur_sofs = 0;
   for (i = lcbndp->szu.xclen - 1; i >= 0; i--)
    {
     __adds(__to_vvstnam(__xs, (word32) sbp[i]));
     addch_('|');
     __exprline[__cur_sofs] = '\0';
    }
   __tr_msg("++ strength concatenate result: %s\n", __exprline);
   __cur_sofs = 0;
  }
}

/*
 * store a/b value into strength byte array - set value or in new stregth
 * byte order for strength bytes [h:l] just like word32 bits
 * notice this needs to be called with blen less that actual stacked blen
 * also must and off possibly unused parts
 *
 * notice z must not have strong added for non strength case
 * and need to map to right 0 val/1 val strengths
 */
extern void __st_standval(byte *sbp, struct xstk_t *xsp, byte new_st)
{
 int32 bi, aw, bw;

 /* short circuit for 1 bit case */
 if (xsp->xslen == 1)
  {
   aw = (xsp->ap[0] & 1L) | ((xsp->bp[0] << 1) & 2L);
   /* if z, no strength */
   if (aw == 2) sbp[0] = (byte) aw;
   else
     {
      /* SJM 08/07/01 - need to use stren map table so val 0 has 0 stren etc */
      aw |= (new_st << 2);
      sbp[0] = __stren_map_tab[aw];
     }
   return;
  }

 for (bi = 0; bi < xsp->xslen; bi++)
  {
   aw = rhsbsel_(xsp->ap, bi);
   bw = rhsbsel_(xsp->bp, bi);
   aw |= (bw << 1);
   /* if z no strength */
   if (aw == 2) sbp[bi] = (byte) aw;
   else
    {
     /* SJM 08/07/01 - need to use stren map table so val 0 has 0 stren etc */
     aw |= (new_st << 2);
     /* SJM 08/15/01 - this is vector - from typo was only set 0 */
     sbp[bi] = __stren_map_tab[aw];
    }
  }
}

/*
 * pairwise combine driving value into section (or all) of wire
 * know abi1 (high) and abi2 (low) already corrected for h:0 form
 */
extern void __eval_stwire(byte *accsbp, word32 wtyp, int32 abi1, int32 abi2,
 byte *sbp)
{
 int32 bi, bi2;
 
 for (bi = abi2, bi2 = 0; bi <= abi1; bi++, bi2++)
  {
   accsbp[bi] = (byte) __comb_1bitsts(wtyp, (word32) accsbp[bi],
    (word32) sbp[bi2]);
  }
}

/*
 * combine into first 2nd 1 bit (byte form) strength value that is not
 * wired logic
 *
 * format [s000,s111,vv] - 3 high bits st 0, 3 middle bits st 1, 2 low val 
 * convention for non x/z value s0 is highest and s1 is lowest
 *
 * routine works for everything except trireg - need special "array" for it
 * because for tri0/tri1 initialized to state if no drivers
 * supply0 nets cannot be effected by driver so just init and return above
 *
 * notice storing H and L as x value with 1 or other strength 0 - since
 * no different from real way where strengths same but value z (2)
 *
 * LOOKATME - myabe this should use word32 variables
 */
extern word32 __comb_1bitsts(word32 wtyp, word32 acc, word32 op)
{
 word32 str0acc, str1acc, vacc, str0op, str1op, vop;
 word32 s0hop, s0lop, s1hop, s1lop, s0hacc, s0lacc, s1hacc, s1lacc;
 word32 s0h, s0l, s1h, s1l, s0, s1;

 /* eliminate either HiZ because HiZ loses to anything */
 /* notice H and L cannot be eliminated here */
 if (acc == 2)
  {
   /* DBG remove -- */
   if (__debug_flg && __ev_tracing) { vop = op; goto do_outmsg; }
   /* --- */
   return(op);
  }
 if (op == 2)
  {
   /* DBG remove - */
   if (__debug_flg && __ev_tracing) { vop = acc; goto do_outmsg; }
   /* --- */
   return(acc);
  }

 /* extract values, */
 vacc = acc & 3; 
 vop = op & 3; 
 str0acc = (acc >> 5) & 7;  
 str1acc = (acc >> 2) & 7;
 str0op = (op >> 5) & 7;  
 str1op = (op >> 2) & 7;

 /* handle special cases that are independent of wired logic type */
 /* both 1 or both 0 - strength always largest */
 if ((vacc == 1 && vop == 1) || (vacc == 0 && vop == 0))
  {
   /* in case of both strength in 0 or 1 region, 0 st higher than 1 st */ 
   s0 = (str0acc >= str0op) ? str0acc : str0op;
   s1 = (str1acc >= str1op) ? str1acc : str1op;
   goto done;
  }
 /* both have fixed strength (<s:s>=? and <t:t>=?) */ 
 /* notice for H and L, strength never same */
 if (str0acc == str1acc && str0op == str1op) 
  {
   /* case 1: strengths same - may need wired logic compare */
   s0 = s1 = str0acc;
   if (str0acc == str0op)
    {
     switch ((byte) wtyp) {
      /* since know differ and know stren same, non wired must be x */
      case N_TRI: case N_WIRE: case N_TRI0: case N_TRIREG: case N_TRI1:
      /* SJM 11/16/00 - supplies possible here, but how */
      case N_SUPPLY0: case N_SUPPLY1:
       vacc = 3;
       break;
      case N_WA: case N_TRIAND: 
       /* if either 0, result 0, else result X */
       if (vacc == 0 || vop == 0) vacc = 0; else vacc = 3;
       break;
      case N_WO: case N_TRIOR:
       /* if either 1, result 1, else result X */
       if (vacc == 1 || vop == 1) vacc = 1; else vacc = 3;
       break;
      default: __case_terr(__FILE__, __LINE__);
     }
     goto done; 
    }
   /* case 1: strengths differ - value of stronger stren wins */
   if (str0acc <= str0op) { s0 = s1 = str0op; vacc = vop; }
   goto done;
  }

 /* separate into low-high for both 0 and 1 for both operands */
 s0hacc = s0lacc = s1hacc = s1lacc = 0;
 switch ((byte) vacc) {
  case 0: s0hacc = str0acc; s0lacc = str1acc; break; 
  case 1: s1hacc = str0acc; s1lacc = str1acc; break; 
  case 3: s0hacc = str0acc; s1hacc = str1acc; break;
  default: __case_terr(__FILE__, __LINE__);
 }
 s0hop = s0lop = s1hop = s1lop = 0;
 switch ((byte) vop) {
  case 0: s0hop = str0op; s0lop = str1op; break; 
  case 1: s1hop = str0op; s1lop = str1op; break; 
  case 3: s0hop = str0op; s1hop = str1op; break;
  default: __case_terr(__FILE__, __LINE__);
 }
 /* tournament 1 - op and acc 0 strengths and 1 strengths */
 s0h = (s0hacc >= s0hop) ? s0hacc : s0hop; 
 s0l = (s0lacc >= s0lop) ? s0lacc : s0lop;
 s1h = (s1hacc >= s1hop) ? s1hacc : s1hop; 
 s1l = (s1lacc >= s1lop) ? s1lacc : s1lop;

 /* tournament 2 - 0 and 1 strengths */
 /* if lowest 0 higher than highest 1, remove 1 strengths */
 if (s0l > s1h) { s0 = s0h; s1 = s0l; vacc = 0; }
 /* if lowest 1 higher than highest 0, remove 0 strengths */  
 else if (s1l > s0h) { s0 = s1h; s1 = s1l; vacc = 1; } 
 /* x - strengths in both regions (fill in smaller gap) */
 else { s0 = s0h; s1 = s1h; vacc = 3; }

 /* ? believe that for wired logic, if 1 strength range */
 /* then value is outer range x - no wired logic here - is it true */

done:
 /* --- DBG remove */
 if (__debug_flg && __ev_tracing)
  {
   char vs1[10], vs2[10], vs3[10];

   vop = (s0 << 5) | (s1 << 2) | vacc;
do_outmsg:
   __tr_msg("+> fi>1 strength: %s acc=%s,op=%s,res=%s\n", 
    __to_wtnam2(__xs, (word32) wtyp), __to_vvstnam(vs1, (word32) acc),   
    __to_vvstnam(vs2, (word32) op), __to_vvstnam(vs3, (word32) vop));
   return(vop);
  }
/* --- */
 return((s0 << 5) | (s1 << 2) | vacc); 
}

/*
 * EXECUTION OUTPUT ROUTINES INCLUDING SHOWVARS (NEEDS EXEC VALUES)
 */

/*
 * build the state of a gate into string
 * can only be called during exec when current inst. on itstk
 * caller must do any needed truncating
 *
 * handles strengths and bufif and mos style gates
 * all values extracted from gate state
 */
extern char *__gstate_tostr(char *s, struct gate_t *gp, int32 fullpath)
{
 int32 srep, pi, nins, sav_sofs, conducting;
 word32 tmp, tmp2, uwrd, av, bv;
 struct tev_t *tevp;
 struct xstk_t *xsp;
 struct udp_t *udpp;
 char s1[RECLEN], s2[10], s3[10], s4[10];

 sav_sofs = __cur_sofs;
 __adds(gp->gmsym->synam);

 addch_(' ');
 if (fullpath)
  {
   __disp_itree_idp_path(__idp, (struct task_t *) NULL);
   addch_('.');
  }
 __adds(gp->gsym->synam);
 addch_('(');

 nins = gp->gpnum - 1;
 switch ((byte) gp->g_class) {
  case GC_LOGIC:
   if (gp->gpnum > 16) srep = SR_VEC; else srep = SR_PVEC;
   push_xstk_(xsp, nins + 1);
   if (srep == SR_VEC)
    {
     __ld_gate_wide_val(xsp->ap, xsp->bp, &(__idp[gp->gstate_ofs]), nins + 1); 
     /* SJM 11/26/00 - need to select from multi-word32 xsp if wider than 16 */
     /* put output value in tmp - since low bit is 0 right index is nins **/
     tmp = rhsbsel_(xsp->ap, nins);
     tmp2 = rhsbsel_(xsp->bp, nins);
     tmp |= (tmp2 << 1);
     __adds(__to_vvnam(s1, tmp));
     adds_evgate_ins(xsp->ap, xsp->bp, nins);
    }
   else
    {
     /* extract current output value */
     uwrd = __idp[gp->gstate_ofs];
     tmp = ((uwrd >> nins) & 1L) | ((uwrd >> (2*nins)) & 2L);
     __adds(__to_vvnam(s1, tmp));
     av = uwrd & __masktab[nins + 1];
     bv = uwrd >> (nins + 1);
     adds_evgate_ins(&av, &bv, nins);
    }
   addch_(')');
   __pop_xstk();
   break;
  case GC_UDP:
   udpp = gp->gmsym->el.eudpp;
   nins = udpp->numins;
   uwrd = __idp[gp->gstate_ofs];
   tmp = (uwrd >> (2*nins)) & 3L;
   /* DBG remove ---
   if (tmp == 2) __misc_terr(__FILE__, __LINE__);
   --- */
   __adds(__to_vvnam(s1, tmp));
   for (pi = 0; pi < nins; pi++)
    {
     __adds(", ");
     tmp = (uwrd >> (2*pi)) & 3L;
     /* DBG remove ---
     if (tmp == 2) __misc_terr(__FILE__, __LINE__);
     --- */
     __adds( __to_vvnam(s1, tmp));
    }
   addch_(')');
   /* --- RELEASE REMOVE --- 
   if (udpp->u_wide)
    {
     tmp = __idp[gp->gstate_ofs];
     sprintf(s1, "<%lu>", tmp);
     __adds(s1);
    }
   --- */
   break;
  case GC_BUFIF:
   uwrd = __idp[gp->gstate_ofs];
   __adds(__to_vvstnam(s1, (uwrd >> 4) & 0xffL));
   __adds(", ");
   __adds(__to_vvnam(s2, (uwrd & 0x3L)));
   __adds(", ");
   __adds(__to_vvnam(s3, (uwrd >> 2) & 3L));
   addch_(')');
   break;
  case GC_MOS:
   /* notice packing bit ranges for mos and bufif different */
   uwrd = __idp[gp->gstate_ofs];
   __adds(__to_vvstnam(s1, ((uwrd >> 16) & 0xffL)));
   __adds(", ");
   __adds(__to_vvstnam(s2, (uwrd & 0xffL)));
   __adds(", ");
   __adds(__to_vvnam(s3, ((uwrd >> 8) & 0x3L)));
   addch_(')');
   break;
  case GC_CMOS:
   uwrd = __idp[gp->gstate_ofs];
   __adds(__to_vvstnam(s1, ((uwrd >> 24) & 0xffL)));
   __adds(", ");
   __adds(__to_vvstnam(s2, (uwrd & 0xffL)));
   __adds(", ");
   __adds(__to_vvnam(s3, ((uwrd >> 8) & 0x3L)));
   __adds(", ");
   __adds(__to_vvnam(s4, ((uwrd >> 16) & 0x3L)));
   addch_(')');
   break;
  case GC_TRANIF:
   /* only called for tranif input gate */
   conducting = (__idp[gp->gstate_ofs] & 3L);
   if (conducting == 1) __adds("**ON**)");
   else if (conducting == 0) __adds("**OFF**)");
   else __adds("**UNKNOWN**)");
   break;
  default: __case_terr(__FILE__, __LINE__);
 }
 /* if pending event, write it */
 if (gp->schd_tevs_ofs != 0
     && (tevp = (struct tev_t *) __idp[gp->schd_tevs_ofs]) != NULL)
  { __bld_valofsched(s1, tevp); __adds(s1); }
 __exprline[__cur_sofs] = '\0';
 
 /* finally truncate suffix */
 __trunc_cstr(&(__exprline[sav_sofs]), MSGTRUNCLEN, FALSE);
 strcpy(s, &(__exprline[sav_sofs]));
 __cur_sofs = sav_sofs;
 __exprline[__cur_sofs] = '\0'; 
 return(s);
}

/*
 * write gate inputs - only for normal logic gates
 * notice ports are numbered 0 (output) to gpnum (rightmost input)
 * but storage is inputs bit 0 to gpnum and output in gpnum (sep. a and b) 
 */
static void adds_evgate_ins(word32 *gatap, word32 *gatbp, int32 nins)
{
 int32 bi;
 word32 tmp, tmp2;
 char s1[RECLEN];
 
 for (bi = 0; bi < nins; bi++)
  {
   tmp = rhsbsel_(gatap, bi);
   tmp2 = rhsbsel_(gatbp, bi);
   tmp |= (tmp2 << 1);
   __adds(", ");
   __adds(__to_vvnam(s1, tmp));
  }
}

/*
 * SIMULATION TIME DUMP (SHOWVARS) ROUTINES
 */

/*
 * dump all variables in a design
 * this can only be called after prep done
 */
extern void __show_allvars(void)
{
 int32 ii;
 struct itree_t *itp; 

 for (ii = 0; ii < __numtopm; ii++)
  { itp = __it_roots[ii]; show2_allvars(itp); }
 __cvsim_msg("\n");
}

/*
 * convert global for module whose type corresponds to itree itp
 */
static void show2_allvars(struct itree_t *itp)
{
 int32 ii; 
 struct net_t *np;
 struct mod_t *imdp;
 struct itree_t *itp2;
 decl_idp_locals_;

 imdp = itp->itip->imsym->el.emdp;
 __cvsim_msg("==> showing all variables in %s type %s.\n",
  __msg2_blditree(__xs, itp), imdp->msym->synam);

 /* notice using ii as ni here */
 if (imdp->mnnum != 0)
  {
   for (ii = 0, np = &(imdp->mnets[0]); ii < imdp->mnnum; ii++, np++) 
    { 
     set_save_idp_itp_(itp); 
     __emit_1showvar(np, NULL); 
     restore_idp_();
    }
  }
 for (ii = 0; ii < imdp->minum; ii++)
  { itp2 = &(itp->in_its[ii]); show2_allvars(itp2); }
}

/*
 * show variable prefix from current itp instance
 * assumes scope location already emitted
 *
 * expects __stlevel to be set to 0 here
 * this must happen after all processing within one time unit
 * itree must be on top of stack to call this
 */
extern void __emit_1showvar(struct net_t *np, struct gref_t *grp)
{
 int32 i, bi, ndx;
 struct net_pin_t *npp;
 int32 arrwid, obwid, inum;
 struct tev_t *tevp, **teviarr;
 char s1[RECLEN], s2[RECLEN];

 /* for parameters (still in symb. table but replace) no showvars */ 
 if (np->n_isaparam) return;

 __cur_sofs = 0;
 /* emit the variable information prefix */
 __bld_showvars_prefix(s1, np, grp);

 if (np->ntyp == N_EVENT)
  { __cvsim_msg("%s **event**\n", s1); goto disp_drvs; }

 /* emit the current value of entire variable */
 if (np->n_isarr)
  {
   arrwid = __get_arrwide(np);
   addch_('\n');
   if (np->mda != NULL) showvars_dmp_mda_arr(np, BHEX);
   else
    {
     /* one dimensional - really dump it */ 
     /* this should be setable in the debugger by the user */
     /* SJM 02-24-14 - made area of array printed one per line and more */
     if (arrwid > 1024) obwid = 1024; else obwid = arrwid;
     for (i = 0; i < obwid; i++)
      {
       ndx = __unnormalize_ndx(np, i);
       sprintf(s2, "POS %d NDX %d: ", i, ndx);
       __adds(s2);
       __var_tostr(s2, np, i, i, BHEX);
       __adds(s2);
       addch_('\n');
      }
     if (arrwid > obwid)
      {
       sprintf(__xs, ", ... <%d more>\n", arrwid - obwid);
       __adds(__xs);
      }
    }
  }
 /* emit variable current value - also handles strength variables */ 
 /* LOOKATME - this should use base from net or at least give base */
 else __disp_var(np, -1, -1, BHEX, '?');
 __cvsim_msg("%s = %s\n", s1, __exprline);
 __cur_sofs = 0;

 /* if wire has delay or path dest., there may be a scheduled value */
 if (np->nrngrep == NX_DWIR)
  {
   /* access per bit array of possibly scheduled values for wire */
   /* pointer to array element that is first bit of current inst. */
   inum = get_inum_();
   teviarr = &(np->nu.rngdwir->wschd_pbtevs[np->nwid*inum]);
   if (np->n_isavec)
    {
     __cvsim_msg("   Per bit wire with delay scheduled values:\n"); 
     for (bi = np->nwid - 1; bi >= 0; bi--)
      {
       if ((tevp = teviarr[bi]) != NULL) 
        {
         /* form: [i] (schedule %s at %s) */
         __cvsim_msg("    [%d] %s\n", __unnormalize_ndx(np, bi),
          __bld_valofsched(s1, tevp));
        }
      }
    }
   else if ((tevp = teviarr[0]) != NULL)
    {
    __cvsim_msg("scalar wire scheduled %s\n",
      __bld_valofsched(s1, tevp));
    }
  }

 /* emit drivers - regs never have drivers but can have loads */
disp_drvs:
 /* here no filter for rooted xmr since one inst is driver */
 for (npp = np->ndrvs; npp != NULL; npp = npp->npnxt)
  emit1_driver(np, npp, FALSE);
 /* emit loads - no inst. filter for rooted xmr npp */
 for (npp = np->nlds; npp != NULL; npp = npp->npnxt) emit1_load(np, npp);
 __cur_sofs = 0;
}

/*
 * for showvars dump a multi-dim array 
 * proc some what more general than needed for showvars
 */
static void showvars_dmp_mda_arr(struct net_t *np, int32 base)
{
 int32 arri, arrwid, obwid;
 struct mda_t *mdap;
 int32 *mda_ndxies;
 char arrndxnam[RECLEN], s2[RECLEN];
 
 /* DBG remove -- */
 if (np->mda == NULL) __arg_terr(__FILE__, __LINE__);
 /* --- */

 mdap = np->mda;
 /* alloc and fill the current ndx value dimension size array */
 mda_ndxies = (int32 *) __my_malloc(mdap->dimension*sizeof(int32));

 arrwid = __get_arrwide(np);
 if (arrwid > 1024) obwid = 1024; else obwid = arrwid;
 for (arri = 0; arri < obwid; arri++) 
  {
   /* get linearized index and dump array cell info and val */
   unmap_arri_to_ndxnums(arri, np, mda_ndxies);
   bld_mda_index_label(arrndxnam, np, mda_ndxies);
   sprintf(s2, "INDEX %s (POS %d): ", arrndxnam, arri);
   __adds(s2);
   __var_tostr(s2, np, arri, arri, base);
   __adds(s2);
   addch_('\n');
  }
 if (arrwid > obwid)
  {
   sprintf(__xs, ", ... <%d more>\n", arrwid - obwid);
   __adds(__xs);
  }
}

/*
 * map linearized array to array of dimensions
 *
 * low dim always 1 because that is number of cells
 * next lowest dim number of elements in lowest dim
 * next after than dim number of elments in one right of it dim
 *
 * SJM 03-24-14 - this builds internal array storage always each dimension
 * [h:0] (size to 0 just like vector bits) - in Verilog low bit in word
 * (unrelated to endianness usually) is bit 0 (h:0) and arrays are low
 * word 
 */
static void unmap_arri_to_ndxnums(int32 arri, struct net_t *np,
 int32 *mda_ndxies)
{
 int32 dimi, ndxval;
 struct mda_t *mdap;
 
 mdap = np->mda;
 ndxval = arri;
 for (dimi = 0; dimi < mdap->dimension - 1; dimi++)
  {
   mda_ndxies[dimi] = ndxval/mdap->dim_mult[dimi];
   ndxval = ndxval % mdap->dim_mult[dimi];
  }
 /* for low one just the value - really divided by 1 */ 
 mda_ndxies[mdap->dimension - 1] = ndxval;
}

/*
 * bld a string of an array index label (cell indices) from an array of
 * mda indices
 *
 * rightmost highest varies fastest - leftmost varies slowest
 * first index array of arrays of rest of indicies following SV terminology
 */
static char *bld_mda_index_label(char *s, struct net_t *np, int32 *mda_ndxies)
{
 int32 dimi, ndxval, mr1, mr2, dwid;
 struct mda_t *mdap;
 char s1[RECLEN];

 mdap = np->mda;
 strcpy(s, "");
 /* SJM 03-27-04 - must print high index first */
 for (dimi = 0; dimi < mdap->dimension; dimi++)
  {
   __getarr_range_mda(np, &(mr1), &(mr2), &(dwid), dimi);
   ndxval = __unnormalize2_ndx(mda_ndxies[dimi], mr1, mr2);
   sprintf(s1, "[%d]", ndxval);
   strcat(s, s1);
  }
 return(s);
}

/*
 * emit a driver string - if nonz_only only emit non floating drivers
 *
 * only for use at end of time unit
 * when called itree location is wire from which npp driver connected to
 * notice np tchg can never be a driver
 */
static void emit1_driver(struct net_t *np, struct net_pin_t *npp,
 int32 nonz_only)
{
 int32 i1, i2, obwid, ri1, ri2;
 struct tev_t *tevp;
 word32 wrd;
 byte *sbp;
 struct gate_t *gp;
 struct conta_t *cap, *cap2;
 struct xstk_t *xsp;
 struct itree_t *dritp;
 struct inst_t *ip;
 struct mod_t *mdp;
 struct mod_pin_t *mpp;
 struct npaux_t *npauxp;
 struct tfrec_t *tfrp;
 struct tfarg_t *tfap;
 char ndxs[RECLEN], s1[RECLEN], s2[RECLEN], s3[RECLEN];
 struct itree_t *itp;
 decl_idp_locals_;

 /* think sbp and xsp always set here - lint warning from  if separation */
 sbp = NULL;
 xsp = NULL;
 ri1 = ri2 = -1;
 save_idp = NULL;
 /* this is needed to get this instances pattern for IS form */ 
 
 if ((npauxp = npp->npaux) == NULL) i1 = i2 = -1;
 else __get_cor_range(npauxp->nbi1, npauxp->nbi2, &i1, &i2);
 /* also need to print lhs select range but leave rhs width as is */
 /* assignment will widen or truncate if needed but driver is rhs */
 if (i1 != -1)
  {
   /* need range of array for umapping index for message */
   if (np->n_isarr) __getarr_range(np, &ri1, &ri2, &obwid);
   else if (np->n_isavec) __getwir_range(np, &ri1, &ri2);
   else __arg_terr(__FILE__, __LINE__);
   if (i1 == i2) sprintf(ndxs, " [%d]", __unmap_ndx(i1, ri1, ri2));
   else sprintf(ndxs, " [%d:%d]", __unmap_ndx(i1, ri1, ri2),
   __unmap_ndx(i2, ri1, ri2));
  }
 else strcpy(ndxs, "");

 /* this traces from target (where var. is) back to ref. itree loc. */
 if (npp->npproctyp != NP_PROC_INMOD)
  {
   /* SJM 04/17/03 - if XMR does not match - do not combine in */
   if ((itp = __get_npprefloc(npp)) == NULL) return;
   set_save_idp_itp_(itp); 
  }

 /* special handling for getpattern on rhs */
 if (npp->npntyp == NP_CONTA)
  { 
   cap = npp->elnpp.ecap;
   if (cap->lhsx->getpatlhs)
    { 
     __cvsim_msg("%s   driver: continuous assign of $getpattern to %s\n",
      ndxs, __msgexpr_tostr(__xs, cap->lhsx)); 
     if (save_idp != NULL)
      {
       restore_idp_();
      }
     return;
    }
  }

 /* here for inouts (up iconn and down mdprt) and trans need driver value */ 
 /* notice this insure that returned xsp never nil */
 switch ((byte) npp->npntyp) {
  case NP_GATE:
   /* current value of gate is state output - next value is event state */
   /* if driver (gate output) wide just accesses low bit here */
   gp = npp->elnpp.egp;
   /* get driving value */ 
   if (np->n_stren)
    {
     xsp = ld_stgate_driver(npp);
     sbp = (byte *) xsp->ap;
     /* high impedance z will always have z value and 0 strengths */
     if (nonz_only && sbp[0] == 2) break;
     __to_vvstnam(s1, (word32) sbp[0]);
    }
   else
    {
     xsp = __ld_gate_driver(npp);
     wrd = xsp->ap[0] | (xsp->bp[0] << 1);
     if (nonz_only && wrd == 2L) break;
     __to_vvnam(s1, wrd);
    }
   if (gp->g_class == GC_UDP)
    sprintf(s2, "%s udp %s", __schop(__xs, gp->gmsym->synam),
    __schop(__xs2, gp->gsym->synam));
   else
    {
     if (gp->gmsym->el.eprimp->gateid == G_ASSIGN)
      strcpy(s2,  "1 bit continuous assign"); 
     else sprintf(s2, "%s gate %s", __schop(__xs, gp->gmsym->synam),
      __schop(__xs2, gp->gsym->synam));
    }
   if (gp->schd_tevs_ofs != 0
      && (tevp = (struct tev_t *) __idp[gp->schd_tevs_ofs]) != NULL)
    __bld_valofsched(s3, tevp);
   else strcpy(s3, ""); 

   __cvsim_msg("%s   driver: %s (port %d) at %s = %s%s\n", ndxs, s2,
    npp->obnum + 1, __bld_lineloc(__xs, gp->gsym->syfnam_ind,
    gp->gsym->sylin_cnt), s1, s3);
   break;
  case NP_CONTA:
   /* value for driver that is cont. assign is: 1) ca driver wp per inst if */
   /* set, 2) ca_rhsval if for 0 delay case, else evaled lhs if fi == 1 */
   cap = npp->elnpp.ecap;
   if (cap->ca_pb_sim) cap2 = &(cap->pbcau.pbcaps[npp->pbi]);
   else cap2 = cap;
   if (np->n_stren)
    {
     xsp = ld_stconta_driver(npp);
     sbp = (byte *) xsp->ap;  
     /* this returns NULL on all drivers z if nonz only on */
     /* SJM 11/13/00 - must use lhs width here in rhs wider truncated */
     if (stdrive_tostr(s1, sbp, npp, cap2->lhsx->szu.xclen, nonz_only)
      == NULL) break;
    }
   else
    {
     xsp = __ld_conta_driver(npp);
     if (drive_tostr(s1, xsp->ap, xsp->bp, npp, cap2->rhsx->szu.xclen,
      nonz_only) == NULL) break;
    }
   if (cap2->caschd_tevs_ofs != 0
      && (tevp = (struct tev_t *) __idp[cap2->caschd_tevs_ofs]) != NULL)
     __bld_valofsched(s2, tevp);
   else strcpy(s2, ""); 

   if (cap->ca_pb_sim)
    {
     __cvsim_msg(
      "%s   driver: continuous assign to %s per bit %d at %s = %s%s\n",
      ndxs, __msgexpr_tostr(__xs, cap2->lhsx), npp->pbi, 
      __bld_lineloc(__xs2, cap->casym->syfnam_ind, cap->casym->sylin_cnt),
      s1, s2);
    }
   else
    {
     __cvsim_msg("%s   driver: continuous assign to %s at %s = %s%s\n",
      ndxs, __msgexpr_tostr(__xs, cap->lhsx), 
      __bld_lineloc(__xs2, cap->casym->syfnam_ind, cap->casym->sylin_cnt),
      s1, s2);
    }
   break;
  case NP_TFRWARG:
   tfrp = npp->elnpp.etfrp;
   tfap = &(tfrp->tfargs[npp->obnum]);
   if (np->n_stren)
    {
     xsp = __ld_sttfrwarg_driver(npp);
     sbp = (byte *) xsp->ap;  
     /* this returns NULL on all drivers z if nonz only on */
     if (stdrive_tostr(s1, sbp, npp, tfap->arg.axp->szu.xclen, nonz_only)
      == NULL) break;
    }
   else
    {
     xsp = __ld_tfrwarg_driver(npp);
     if (drive_tostr(s1, xsp->ap, xsp->bp, npp, tfap->arg.axp->szu.xclen,
      nonz_only) == NULL) break;
    }
   __cvsim_msg("%s   driver: tf_ call of %s arg %s (pos. %d) at %s = %s\n",
    ndxs, __get_tfcellnam(tfrp), __msgexpr_tostr(__xs, tfap->arg.axp),
    npp->obnum, __bld_lineloc(__xs2, tfrp->tffnam_ind, tfrp->tflin_cnt), s1);
   break;
  case NP_VPIPUTV:
   /* DBG remove -- */
   if (npp->elnpp.enp != np) __arg_terr(__FILE__, __LINE__);
   /* --- */
   /* if this instance does not have driver, do not emit */
   if (!__has_vpi_driver(np, npp))
    {
     if (save_idp != NULL)
      {
       restore_idp_();
      }
     return;
    }

   if (np->n_stren)
    {
     xsp = ld_stvpiputv_driver(npp); 
     sbp = (byte *) xsp->ap;  
     /* this returns NULL on all drivers z if nonz only on */
     if (stdrive_tostr(s1, sbp, npp, np->nwid, nonz_only) == NULL) break;
    }
   else
    {
     xsp = __ld_vpiputv_driver(npp); 
     if (drive_tostr(s1, xsp->ap, xsp->bp, npp, np->nwid, nonz_only) == NULL)
      break;
    }
   __cvsim_msg("%s   driver: vpi_put_value driving %s %s = %s\n", ndxs,
    np->nsym->synam, __to_wtnam(__xs2, np), s1);
   break;
  case NP_ICONN:
   /* called from up itree loc. */
   itp = get_itp_();
   dritp = &(itp->in_its[npp->elnpp.eii]);
   ip = dritp->itip;
   /* need to make sure driver is loaded - no concept of changing one here */
   if (np->n_stren)
    {
     xsp = ld_sticonn_up_driver(npp);
     sbp = (byte *) xsp->ap;
     /* this returns NULL on all drivers z if nonz only on */
     if (stdrive_tostr(s1, sbp, npp, xsp->xslen/4, nonz_only) == NULL) break;
    }
   else
    {
     xsp = __ld_iconn_up_driver(npp);
     if (drive_tostr(s1, xsp->ap, xsp->bp, npp, xsp->xslen, nonz_only)
      == NULL) break;
    }
   __cvsim_msg("%s   driver: instance %s port %s at %s = %s\n",
    ndxs, ip->isym->synam, np->nsym->synam, __bld_lineloc(__xs,
    ip->isym->syfnam_ind, ip->isym->sylin_cnt), s1);
   break;
  case NP_PB_ICONN:
   /* called from up itree loc. */
   itp = get_itp_();
   dritp = &(itp->in_its[npp->elnpp.eii]);
   ip = dritp->itip;
   /* need to make sure driver is loaded - no concept of changing one here */
   if (np->n_stren)
    {
     xsp = ld_pb_sticonn_up_driver(npp);
     sbp = (byte *) xsp->ap;
     /* this returns NULL on all drivers z if nonz only on */
     if (stdrive_tostr(s1, sbp, npp, xsp->xslen/4, nonz_only) == NULL) break;
    }
   else
    {
     xsp = __ld_pb_iconn_up_driver(npp);
     if (drive_tostr(s1, xsp->ap, xsp->bp, npp, xsp->xslen, nonz_only)
      == NULL) break;
    }
   __cvsim_msg("%s   driver: instance %s port %s bit %d at %s = %s\n",
    ndxs, ip->isym->synam, np->nsym->synam, npp->pbi, __bld_lineloc(__xs,
    ip->isym->syfnam_ind, ip->isym->sylin_cnt), s1);
   break;
  case NP_MDPRT:
   /* called from down mod port itree loc. */
   mdp = npp->elnpp.emdp;
   mpp = &(mdp->mpins[npp->obnum]);
   if (np->n_stren)
    {
     xsp = ld_stmodport_down_driver(npp);
     sbp = (byte *) xsp->ap;      
     /* this returns NULL on all drivers z if nonz only on */
     if (stdrive_tostr(s1, sbp, npp, xsp->xslen/4, nonz_only) == NULL)
      break;
    }
   else
    {
     xsp = __ld_modport_down_driver(npp);
     if (drive_tostr(s1, xsp->ap, xsp->bp, npp, xsp->xslen, nonz_only)
      == NULL) break;
    }
   __cvsim_msg("%s   driver: module %s port %s at %s = %s\n",
    ndxs, mdp->msym->synam, np->nsym->synam, __bld_lineloc(__xs,
    mpp->mpfnam_ind, mpp->mplin_cnt), s1);
   break;
  case NP_PB_MDPRT:
   /* called from down mod port itree loc. */
   mdp = npp->elnpp.emdp;
   mpp = &(mdp->mpins[npp->obnum]);
   mpp = &(mpp->pbmpps[npp->pbi]);
   if (np->n_stren)
    {
     xsp = ld_pb_stmodport_down_driver(npp);
     sbp = (byte *) xsp->ap;      
     /* this returns NULL on all drivers z if nonz only on */
     if (stdrive_tostr(s1, sbp, npp, xsp->xslen/4, nonz_only) == NULL)
      break;
    }
   else
    {
     xsp = __ld_pb_modport_down_driver(npp);
     if (drive_tostr(s1, xsp->ap, xsp->bp, npp, xsp->xslen, nonz_only)
      == NULL) break;
    }
   __cvsim_msg("%s   driver: module %s port %s bit %d at %s = %s\n",
    ndxs, mdp->msym->synam, np->nsym->synam, npp->pbi, __bld_lineloc(__xs,
    mpp->mpfnam_ind, mpp->mplin_cnt), s1);
   break;
  case NP_PULL:
   /* notice do not need to call ld_pull stren - fixed so get from gstate */
   gp = npp->elnpp.egp;
   __cvsim_msg("%s   driver: pull to %s at %s of %s\n",
    ndxs, __to_vvstnam(s1, (word32) ((gp->g_stval << 2) | npp->pullval)),
    __bld_lineloc(__xs, gp->gsym->syfnam_ind, gp->gsym->sylin_cnt),
    __msgexpr_tostr(__xs2, gp->gpins[npp->obnum]));
   if (save_idp != NULL)
    {
     restore_idp_();
    }
   return;
  default: __case_terr(__FILE__, __LINE__); return;
 }
 __pop_xstk();
 if (save_idp != NULL)
  {
   restore_idp_();
  }
}

/*
 * convert driver to string with non z only processing
 * ap and bp rhs conta expr. 
 * rhs is driver of entire conta which is right unless lhs is
 * concat, if so lcb i1 used to select part driving this net
 *
 * notice truncating this then truncating entire drive message
 */
static char *drive_tostr(char *s, word32 *ap, word32 *bp,
 struct net_pin_t *npp, int32 rhswid, int32 nonz_only)
{
 int32 nd_xpop;
 int32 wlen, ubits;
 struct xstk_t *tmpxsp;
 struct npaux_t *npauxp;

 nd_xpop = FALSE;
 /* if lhs is concatenate, must isolate part dirving this npp wire section */ 
 if ((npauxp = npp->npaux) != NULL && npauxp->lcbi1 != -1)
  {
   rhswid = npauxp->lcbi1 - npauxp->lcbi2 + 1;
   if (npauxp->lcbi2 != 0)
    {
     push_xstk_(tmpxsp, rhswid);
     __rhspsel(tmpxsp->ap, ap, npauxp->lcbi2, rhswid); 
     __rhspsel(tmpxsp->bp, bp, npauxp->lcbi2, rhswid); 
     nd_xpop = TRUE;
     ap = tmpxsp->ap; 
     bp = tmpxsp->bp;
    }
   else
    {
     /* conta lhs concatenate section starts at low bit */
     wlen = wlen_(rhswid);
     if ((ubits = ubits_(rhswid)) != 0)
      { ap[wlen - 1] &= __masktab[ubits]; bp[wlen - 1] &= __masktab[ubits]; }
    }
  }
 /* notice all z test after selection of actual bits that drive this net */
 if (nonz_only && !__vval_isallzs(ap, bp, rhswid)) return(FALSE);

 __regab_tostr(s, ap, bp, rhswid, BBIN, FALSE);
 if (nd_xpop) __pop_xstk();
 return(s);
}

/*
 * copy a strength driving expr. value to a string with select if lhs concat
 */
static char *stdrive_tostr(char *s, byte *sbp, struct net_pin_t *npp,
 int32 rhswid, int32 nonz_only)
{
 struct npaux_t *npauxp;

 /* if conta has lhs concat, only emit bits that drive this wire */
 /* know form here always internal h:l */
 if ((npauxp = npp->npaux) != NULL && npauxp->lcbi1 != -1)
  {
   sbp = &(sbp[npauxp->lcbi2]);
   rhswid = npauxp->lcbi1 - npauxp->lcbi2 + 1;
  }
 /* notice all z test after selection of actual bits that drive this net */
 if (nonz_only && !__st_vval_isallzs(sbp, rhswid)) return(NULL);
 __st_regab_tostr(s, sbp, rhswid);
 return(s);
}

/*
 * for message build event value and time in passed string
 *
 * notice cannot use __xs strings here since caller will pass as s 
 * this must only be called if there is a scheduled value
 */
extern char *__bld_valofsched(char *s, struct tev_t *tevp)
{
 word32 outv;
 int32 blen;
 byte *sbp;
 struct gate_t *gp;
 struct conta_t *cap;
 struct tenp_t *tenp;
 struct xstk_t *xsp, *xsp2;
 char s1[RECLEN], s2[RECLEN];

 if (tevp->enterptr == __process_gatechg_ev)
  {
   gp = tevp->tu.tegp;
   outv = tevp->outv;
   /* only input TRANIF separate gate can have delay */
   if (gp->g_class == GC_TRANIF)
    {
     if (gp->gpnum != 1) __case_terr(__FILE__, __LINE__);
     if (tevp->outv == 0) strcpy(s1, "**OFF**");
     else if (tevp->outv == 1) strcpy(s1, "**ON**");
     else strcpy(s1, "**UNKNOWN**");  
     
    }
   else
    {
     if (gp->g_hasst) __to_vvstnam(s1, outv);
     else __to_vvnam(s1, outv);
    }
  }
 else if (tevp->enterptr == __process_conta_ev) 
  {
   /* SJM 09/28/02 - this is passed the per bit conta indexed above */
   cap = tevp->tu.tecap;
   /* first access the rhs value - that is thing scheduled to change to */
   /* if rhs changed, previous scheduled replaced with new */
   /* if delay and multi-fi know schedule will exist */
   blen = cap->lhsx->szu.xclen;
   push_xstk_(xsp, blen);
   /* FIXME - think this should not be called from lhs itree loc. for xmr */
   __ld_val(xsp->ap, xsp->bp, &(__idp[cap->schd_drv_ofs]), blen);
   if (cap->ca_hasst)
    {
     push_xstk_(xsp2, 4*blen);
     sbp = (byte *) xsp2->ap;
     /* since rhs eval or saved, never stored with strength - must add here */
     /* conta may drive strength but any input strengths removed */ 
     __st_standval(sbp, xsp, cap->ca_stval);
     __st_regab_tostr(s1, sbp, blen);
     __pop_xstk();
    }
   else __regab_tostr(s1, xsp->ap, xsp->bp, blen, BBIN, FALSE);
   __pop_xstk();
  }
 else if (tevp->enterptr == __process_wire_ev ||
   tevp->enterptr == __process_trpthdst_ev)
  {
   tenp = tevp->tu.tenp;
   outv = tevp->outv;
   if (tenp->tenu.np->n_stren) __to_vvstnam(s1, outv);
   else __to_vvnam(s1, outv);
  }
 else if (tevp->enterptr == __process_mipd_nchg_ev)
  {
   strcpy(s1, "*NONE*");
  }
 else __case_terr(__FILE__, __LINE__);
 sprintf(s, "(scheduled %s at %s)", s1, __to_timstr(s2, &(tevp->etime))); 
 return(s);
}

/*
 * emit the showvars variable information prefix
 */
extern char *__bld_showvars_prefix(char *s, struct net_t *np,
 struct gref_t *grp)
{
 int32 dimi, mr1, mr2, arrwid;
 char s1[RECLEN], s2[RECLEN], s3[RECLEN], s4[RECLEN], s5[RECLEN];

 /* always emit prefix info */
 if (np->iotyp != NON_IO) sprintf(s1, " %s", __to_ptnam(s3, np->iotyp));
 else strcpy(s1, "");
 if (np->n_isavec && np->ntyp != N_INT && np->ntyp != N_TIME
  && np->ntyp != N_REAL) sprintf(s2, " %s", __to_wrange(s3, np));
 else strcpy(s2, "");
 if (np->n_isarr)
  {
   if (np->mda != NULL)
    {
     strcpy(s4, "");
     for (dimi = 0; dimi < np->mda->dimension; dimi++)
      { 
       __getarr_range_mda(np, &(mr1), &(mr2), &(arrwid), dimi);
       sprintf(s5, "[%d:%d]", mr1, mr2);
       strcat(s4, s5); 
      }
     sprintf(s5, "(CELLS=%d)", __get_arrwide(np));
     strcat(s4, s5);
    }
   else sprintf(s4, "%s", __to_arr_range(s3, np));
  } 
 else strcpy(s4, "");

 /* if xmr form must emit path given as arg */
 if (grp == NULL) __schop(s3, np->nsym->synam); else __schop(s3, grp->gnam); 
 sprintf(s, "%s%s %s%s %s", s1, s2, s3, s4, bld_wire_telltale(s5, np));
 return(s);
}

/*
 * build special flag tell-tale
 * know NX_CT gone after prep before this called
 */
static char *bld_wire_telltale(char *s, struct net_t *np)
{
 char s1[RECLEN], s2[RECLEN];
 struct xstk_t *xsp;
 int32 inum;

 sprintf(s, "<%s", __to_wtnam(s1, np));
 if (np->n_signed) strcat(s, " signed");
 if (np->n_isavec && !np->vec_scalared) strcat(s, " vectored");
 if (np->nrngrep == NX_DWIR)
  {
   if (np->nu.rngdwir->n_delrep == DT_PTHDST) strcat(s, " path dest.");
   else strcat(s, " delay");
  }
 if (np->n_isapthsrc) strcat(s, " path src.");
 if (np->n_stren) strcat(s, " strength");
 if (np->n_capsiz != CAP_NONE)
  {
   sprintf(s1, " %s capacitor", __to1_stren_nam(s2,
    __fr_cap_size((int32) np->n_capsiz), 0));
   strcat(s, s1); 
  }
 if (np->n_multfi) strcat(s, " multi-fi");
 if (np->ntraux != NULL) strcat(s, " in tran channel");
 if (np->nlds != NULL) strcat(s, " fo"); 
 if (np->n_hasdvars) strcat(s, " dumpvar"); 
 /* SJM 07/19/02 - if all off no events */
 if (np->dcelst != NULL && __cnt_dcelstels(np->dcelst) > 0)
  strcat(s, " evnts");
 if (np->n_gone) strcat(s, " disconnected");
 if (np->frc_assgn_allocated)
  {
   if (np->ntyp >= NONWIRE_ST)
    {
     inum = get_inum_();
     if (np->nu2.qcval[2*inum].qc_active) strcat(s, " forced");
     else if (np->nu2.qcval[2*inum + 1].qc_active) strcat(s, " assigned");
    }
   else
    {
     push_xstk_(xsp, np->nwid);
     __bld_forcedbits_mask(xsp->ap, np);
     if (!vval_is0_(xsp->ap, np->nwid)) strcat(s, " forced");
     __pop_xstk();
    }
  }
 strcat(s, ">");
 return(s);
}

/*
 * emit a load string - static information - should be emitted only once 
 * load on xmr target 
 */
static void emit1_load(struct net_t *np, struct net_pin_t *npp)
{
 int32 i1, i2, obwid, ri1, ri2;
 struct inst_t *ip;
 struct itree_t *dritp;
 struct mod_t *mdp;
 struct mod_pin_t *mpp;
 struct gate_t *gp;
 struct conta_t *cap, *cap2;
 struct tchk_t *tcp;
 struct spcpth_t *pthp;
 struct npaux_t *npauxp;
 char ndxs[RECLEN];
 struct itree_t *itp;
 decl_idp_locals_;

 /* SJM 06/03/02 - only call get cor range if npaux exists */
 if ((npauxp = npp->npaux) == NULL) i1 = i2 = -1;
 else __get_cor_range(npauxp->nbi1, npauxp->nbi2, &i1, &i2);
 if (i1 != -1)
  {
   if (np->n_isarr) __getarr_range(np, &ri1, &ri2, &obwid);
   else if (np->n_isavec) __getwir_range(np, &ri1, &ri2);
   else { __arg_terr(__FILE__, __LINE__); ri1 = ri2 = 0; }

   if (i1 == i2) sprintf(ndxs, " [%d]", __unmap_ndx(i1, ri1, ri2));
   else sprintf(ndxs, " [%d:%d]", __unmap_ndx(i1, ri1, ri2),
   __unmap_ndx(i2, ri1, ri2));
  }
 else strcpy(ndxs, "");

 save_idp = NULL;
 switch ((byte) npp->npproctyp) {
  case NP_PROC_INMOD: break; 
  case NP_PROC_GREF:
   /* SJM 04/17/03 - if not end instance of matching downrel path do not */ 
   /* print */
//AIV INUM FIXME
   itp = __match_targ_to_ref(npp->np_xmrtyp, npp->npaux->npu.npgrp);
   if (itp == NULL) return;
   set_save_idp_itp_(itp); 
   break;
  case NP_PROC_FILT:
   /* all rooted xmrs here */
   set_save_idp_itp_(npp->npaux->npdownitp); 
   break;
  default: __case_terr(__FILE__, __LINE__);
 }

 switch ((byte) npp->npntyp) {
  case NP_ICONN:
   itp = get_itp_();
   dritp = &(itp->in_its[npp->elnpp.eii]);
   ip = dritp->itip;
   mdp = ip->imsym->el.emdp;
   mpp = &(mdp->mpins[npp->obnum]);
   __cvsim_msg("%s   load: instance %s port %s at %s\n",
    ndxs, ip->imsym->el.emdp->msym->synam, __to_mpnam(__xs2, mpp->mpsnam),
    __bld_lineloc(__xs, ip->isym->syfnam_ind, ip->isym->sylin_cnt));
   break;
  case NP_PB_ICONN:
   /* per bit load same except know scalar/bsel */
   itp = get_itp_();
   dritp = &(itp->in_its[npp->elnpp.eii]);
   ip = dritp->itip;
   mdp = ip->imsym->el.emdp;
   /* notic since not emitting decomposed per bit exprs, need master port */
   mpp = &(mdp->mpins[npp->obnum]);
   __cvsim_msg("%s   load: instance %s port %s bit %d at %s\n",
    ndxs, ip->imsym->el.emdp->msym->synam, __to_mpnam(__xs2, mpp->mpsnam),
    npp->pbi, __bld_lineloc(__xs, ip->isym->syfnam_ind, ip->isym->sylin_cnt));
   break;
  case NP_GATE:
   /* current value of gate is state output - next value is event state */
   gp = npp->elnpp.egp;
   if (gp->g_class == GC_UDP) strcpy(__xs2, "udp");
   else strcpy(__xs2, "gate");
   __cvsim_msg("%s   load: %s %s %s (port %d) at %s\n" , ndxs, __xs2,
    gp->gmsym->synam, gp->gsym->synam, npp->obnum + 1, __bld_lineloc(__xs,
    gp->gsym->syfnam_ind, gp->gsym->sylin_cnt));
   break;
  case NP_TRANIF:
   /* this is only for third port of tranif */
   gp = npp->elnpp.egp;
   __cvsim_msg("%s   load: %s %s (port %d - enable) at %s\n" , ndxs,
    gp->gmsym->synam, gp->gsym->synam, npp->obnum + 1, __bld_lineloc(__xs,
    gp->gsym->syfnam_ind, gp->gsym->sylin_cnt));
   break;
  case NP_CONTA:
   cap = npp->elnpp.ecap;
   if (cap->ca_pb_sim)
    {
     cap2 = &(cap->pbcau.pbcaps[npp->pbi]);
     __cvsim_msg("%s   load: continuous assign to %s per bit %d at %s\n",
      ndxs, __msgexpr_tostr(__xs, cap2->lhsx), npp->pbi, 
      __bld_lineloc(__xs2, cap->casym->syfnam_ind, cap->casym->sylin_cnt));
    }
   else
    {
     __cvsim_msg("%s   load: continuous assign to %s at %s\n", ndxs,
      __msgexpr_tostr(__xs, cap->lhsx), 
      __bld_lineloc(__xs2, cap->casym->syfnam_ind, cap->casym->sylin_cnt));
    } 
   break;
  case NP_MDPRT:
   /* notice mipd module port is only driver not load */
   mdp = npp->elnpp.emdp;
   mpp = &(mdp->mpins[npp->obnum]);
   __cvsim_msg("%s   load: module %s port %s at %s\n", ndxs,
    mdp->msym->synam, __to_mpnam(__xs2, mpp->mpsnam),
    __bld_lineloc(__xs, mpp->mpfnam_ind, mpp->mplin_cnt));
   break;
  case NP_PB_MDPRT:
   /* notice mipd module port is only driver not load */
   mdp = npp->elnpp.emdp;
   mpp = &(mdp->mpins[npp->obnum]);
   mpp = &(mpp->pbmpps[npp->pbi]);
   /* here since not emitting exprs, need master mod port */
   __cvsim_msg("%s   load: module %s port %s bit %d at %s\n", ndxs,
    mdp->msym->synam, __to_mpnam(__xs2, mpp->mpsnam), npp->pbi,
    __bld_lineloc(__xs, mpp->mpfnam_ind, mpp->mplin_cnt));
   break;
  case NP_TCHG:
   switch ((byte) npp->chgsubtyp) {
    case NPCHG_TCSTART:
     tcp = npp->elnpp.etchgp->chgu.chgtcp;
     __cvsim_msg(
     "%s   change: %s timing check line %s reference change event\n",
      ndxs, __to_tcnam(__xs, tcp->tchktyp), __bld_lineloc(__xs2,
      tcp->tcsym->syfnam_ind, tcp->tcsym->sylin_cnt));
     break; 
    case NPCHG_TCCHK:
     tcp = npp->elnpp.echktchgp->startchgp->chgu.chgtcp;
     __cvsim_msg("%s   change: %s timing check line %s data check event\n",
      ndxs, __to_tcnam(__xs, tcp->tchktyp),__bld_lineloc(__xs2,
      tcp->tcsym->syfnam_ind, tcp->tcsym->sylin_cnt));
     break; 
    case NPCHG_PTHSRC:
     pthp = npp->elnpp.etchgp->chgu.chgpthp;
     __cvsim_msg("%s   change: path source and %s source port bit change\n",
      ndxs, __bld_lineloc(__xs, pthp->pthsym->syfnam_ind,
      pthp->pthsym->sylin_cnt));
     break; 
    default: __case_terr(__FILE__, __LINE__);
   }  
   break;
  case NP_MIPD_NCHG:
   /* LOOKATME - should maybe add more details to data structure */
   __cvsim_msg("%s   load: MIPD delay device\n", ndxs);
   break;
  /* pull or tfrw arg can only be driver */
  default: __case_terr(__FILE__, __LINE__);
 }

 if (save_idp != NULL)
  {
   restore_idp_();
  }
}

/*
 * ROUTINES TO IMPLEMENT $DUMPVARS SYSTEM TASK
 */

/*
 * ROUTINES TO COLLECT DUMPVARS INFO DURING ONE TIME
 */

/*
 * execute a dumpvars system task - just collect information - written 
 * at end of this time unit __dv_calltime triggers end of slot dump var
 * file output - if off must still always write header 
 *
 * this must be called with nil if none or func. call. operator (hd of list) 
 */
extern void __exec_dumpvars(struct expr_t *argx, int32 is_fst)
{
 struct mdvmast_t *mdvp;
 int32 dpth, anum, ii, arri;
 t_midat *xmr_idp, *idp;
 word32 tmp;
 struct mdvmast_t *mdvp2;
 struct gref_t *grp;
 struct sy_t *syp;
 char sysnam[20];
 struct net_t *np;
 struct mda_t *mdap;
 struct expr_t *ndx1, *sel_ndx, *idndp;
 int32 *ip;

 /* AIV 04/22/10 - -1 if FST, F => VCD */
 if (is_fst == -1) strcpy(sysnam, "$fstDumpvars");
 else strcpy(sysnam, "$dumpvars");

 /* multiple dumpvars legal during first time where dumpvars seen */
 /* dv seen means previous dumpvars call failed */
 if (__dv_seen)
  {
   __sgferr(729,
    "all %s calls must be at same time - previously called at %s",
    sysnam, __to_timstr(__xs, &__dv_calltime));
   return;
  }
 __dv_calltime = __simtime;
 
 mdvp = NULL;
 if (argx == NULL)
  {
   if (__dv_hdr != NULL)
    {
     __sgfwarn(516,
      "%s no argument form replaces previous %s call", sysnam, sysnam);
     /* free master records - wire records will be reused if present */
     for (mdvp = __dv_hdr; mdvp->mdvnxt != NULL;)
      {
       mdvp2 = mdvp->mdvnxt;
       if ((ip = mdvp->mdv_mda_indices) != NULL)
        {
         np = mdvp->mdv_np;
         mdap = np->mda;
         __my_free(ip, mdap->dimension*sizeof(int32));
        }
       __my_free(mdvp, sizeof(struct mdvmast_t));
       mdvp = mdvp2;
      }
     __dv_hdr = __dv_end = NULL;
    }
   /* mdv_iprt NULL means entire design - common case */
   mdvp = alloc_mdvmast();
   __dv_hdr = __dv_end = mdvp;
   __dv_isall_form = TRUE; 
   goto done;
  }
 /* argument list form, know first is level */
 if (!__get_eval_word(argx->lu.x, &tmp))
  {
   __sgferr(715,
    "%s depth argument illegal numeric expression %s - 1 used",
    sysnam, __msgexpr_tostr(__xs, argx->lu.x));
   tmp = 1;
  }
 dpth = (int32) tmp; 
 argx = argx->ru.x;
 for (anum = 0; argx != NULL; argx = argx->ru.x, anum++)
  {
   if (__dv_isall_form)
    {
     __sgfwarn(500,
      "%s argument %s (number %d) ignored - follows all of design form",
      sysnam, __msgexpr_tostr(__xs, argx->lu.x), anum);
     continue;
    }

   /* do not need checking since checked at fixup time */
   if (argx->lu.x->optyp == GLBREF)
    {
     grp = argx->lu.x->ru.grp;
     syp =  grp->targsyp; 
     /* xmr wire */
     switch ((byte) syp->sytyp) {
      case SYM_N:
       xmr_idp = __xmrget_refgrp_to_targ(grp);
       np = syp->el.enp;
       if (np->n_isarr)
        {
         if (can_dump_entire_array(np))
          {
           add_mdvp_for_each_array_element(np, xmr_idp);
          }
         continue;
        }
       else
        {
         mdvp = alloc_mdvmast();
         mdvp->mdv_itprt_idp = xmr_idp;
         mdvp->mdv_tskp = grp->targtskp;
         mdvp->mdv_np = np;
        }
       break;
      case SYM_I:
       xmr_idp = __xmrget_refgrp_to_targ(grp);
       goto inst_form;
      case SYM_M:
       if ((ii = __ip_indsrch(syp->synam)) == -1)
        __case_terr(__FILE__, __LINE__);
       xmr_idp = __it_roots[ii]->it_idp;
inst_form:
       mdvp = alloc_mdvmast();
       mdvp->mdv_itprt_idp = xmr_idp;
       mdvp->mdv_levels = dpth;
       break;
      default: __case_terr(__FILE__, __LINE__);
     }
    }
   /* know this is local wire form */
   else
    {
     /* AIV 07/14/10 - allowing array elements */
     if (argx->lu.x->optyp == LSB)
      {
       idndp = argx->lu.x->lu.x;
       /* if global get array idp area */
       if (idndp->optyp == GLBREF) 
        {
         idp = __xmrget_refgrp_to_targ(idndp->ru.grp);
        }
       else idp = __idp;
       np = idndp->lu.sy->el.enp;
       ndx1 = argx->lu.x->ru.x;
       arri = __comp_ndx(np, ndx1);
       /* if out of range emit warning and do not add */
       if (arri == -1)
        {
         __sgfwarn(630,
          "%s argument %s (number %d) array is out of range - ignored ",
          sysnam, __msgexpr_tostr(__xs, argx->lu.x), anum);
         continue;
        }
       if ((mdap = np->mda) != NULL)
        {
         /* expression cannot be folded here need to build indices as strs */
         /* DBG remove -- */
         if (ndx1->folded_ndx) __misc_terr(__FILE__, __LINE__);
         /* ---- */
         sel_ndx = NULL;
         ip = build_mda_indices(ndx1, mdap, arri);
         arri = __compute_mda_index(mdap, np, ndx1, arri, &sel_ndx);
         /* if out of range emit warning and do not add */
         if (ip == NULL)
          {
           __sgfwarn(630,
            "%s argument %s (number %d) array is out of range - ignored ",
            sysnam, __msgexpr_tostr(__xs, argx->lu.x), anum);
           continue;
          }
         mdvp = alloc_mdvmast();
         mdvp->mdv_itprt_idp = idp;
	 mdvp->mdv_flat_ndx = arri;
         mdvp->mdv_mda_indices = ip;
        }
       else
        {
         mdvp = alloc_mdvmast();
         mdvp->mdv_itprt_idp = idp;
         mdvp->mdv_flat_ndx = arri;
        }
      }
     else 
      {
       np = argx->lu.x->lu.sy->el.enp;
       if (np->n_isarr)
        {
         if (can_dump_entire_array(np))
          {
           add_mdvp_for_each_array_element(np, __idp);
          }
         continue;
        }
       else
        {
         mdvp = alloc_mdvmast();
         mdvp->mdv_itprt_idp = __idp;
        }
      }

     mdvp->mdv_np = np;
     if (__cur_thd == NULL) __misc_terr(__FILE__, __LINE__);  

     /* SJM 02/29/00 - need to also get var's containing func task */
     /* LOOKATME - should $dumpvars work in functions - think yes? */
     /* SJM 07/05/01 - if var form dumpvars called not task no no task cntxt */
     if (__cur_thd->assoc_tsk != NULL) mdvp->mdv_tskp = __getcur_scope_tsk();
     syp = mdvp->mdv_np->nsym; 
    }
   if (__dv_end == NULL) __dv_hdr = mdvp; else __dv_end->mdvnxt = mdvp; 
   __dv_end = mdvp;
  }
done:
 __slotend_action |= SE_DUMPVARS;
 __dv_seen = FALSE;
}

/*
 * allocate a new dumpvars argument master record
 * notice these can never be freed - needed for dumping all vars
 */
static struct mdvmast_t *alloc_mdvmast(void)
{
 struct mdvmast_t *mdvp;

 mdvp = (struct mdvmast_t *) __my_malloc(sizeof(struct mdvmast_t));
 mdvp->mdv_flat_ndx = -1;
 mdvp->mdv_mda_indices = NULL;
 mdvp->mdv_levels = 0;
 mdvp->mdv_itprt_idp = NULL;
 mdvp->mdv_tskp = NULL;
 mdvp->mdv_np = NULL;
 mdvp->mdvnxt = NULL;
 return(mdvp);
}
         
/*
 * ad a dump mdvp for each element in an array
 */
static void add_mdvp_for_each_array_element(struct net_t *np, t_midat *idp)
{
 int32 i, j, dwid, ri1, ri2, ri1_2, ri2_2, dwid_2, fndx;
 struct mdvmast_t *mdvp;
 struct mda_t *mdap;
 int32 *ip;

 mdap = np->mda;
 /* single dimension */
 if (mdap == NULL)
  {
   for (i = 0; i < np->arr_num_els; i++)
    {
     mdvp = alloc_mdvmast();
     mdvp->mdv_itprt_idp = idp;
     mdvp->mdv_np = np;
     mdvp->mdv_flat_ndx = i;
     if (__cur_thd->assoc_tsk != NULL) mdvp->mdv_tskp = __getcur_scope_tsk();
     if (__dv_end == NULL) __dv_hdr = mdvp; else __dv_end->mdvnxt = mdvp; 
     __dv_end = mdvp;
    }
  }
 else
  {
   /* multi dimensional array */
   //AIV LOOKATME - going to cap at 2-dim for now
   /* DBG remove -- */
   if (mdap->dimension > 2) __misc_terr(__FILE__, __LINE__);
   /* ----- */

   __getarr_range_mda(np, &ri1, &ri2, &dwid, 0);
   __getarr_range_mda(np, &ri1_2, &ri2_2, &dwid_2, 1);
   fndx = 0;
   for (i = 0; i < dwid; i++)
    {
     for (j = 0; j < dwid_2; j++)
      {
       ip = (int32 *) __my_malloc(2*sizeof(int32));
       ip[0] = __unnormalize2_ndx(i, ri1, ri2);
       ip[1] = __unnormalize2_ndx(j, ri1_2, ri2_2);
       mdvp = alloc_mdvmast();
       mdvp->mdv_itprt_idp = idp;
       mdvp->mdv_np = np;
       mdvp->mdv_flat_ndx = fndx++;
       mdvp->mdv_mda_indices = ip;
       if (__cur_thd->assoc_tsk != NULL) mdvp->mdv_tskp = __getcur_scope_tsk();
       if (__dv_end == NULL) __dv_hdr = mdvp; else __dv_end->mdvnxt = mdvp; 
       __dv_end = mdvp;
      }
    }
  }
}

         
/*
 * build the idices of a multi-dimensional array to later be used to 
 * create the variable name for dumping
 * AIV LOOKATME - capping a 2-d arrays so this could be simplified
 */
static int32 *build_mda_indices(struct expr_t *ndx1, struct mda_t *mdap, 
 int32 arri)
{
 int32 i, ndx, ri1, ri2;
 int32 *ip;
 struct expr_t *xp;

 ip = (int32 *) __my_malloc(mdap->dimension*sizeof(int32));

 ri1 = mdap->rng1[0];
 ri2 = mdap->rng2[0];
 ip[0] = __unnormalize2_ndx(arri, ri1, ri2);

 xp = ndx1->next_ndx;
 for (i = 1; i < mdap->dimension; i++)
  {
   ndx = __comp_mda_dim_ndx(mdap, xp, i);
   if (ndx == -1) return(NULL);
   ri1 = mdap->rng1[i];
   ri2 = mdap->rng2[i];
   ndx = __unnormalize2_ndx(ndx, ri1, ri2);

   ip[i] = ndx;
   xp = xp->next_ndx;
  }
 return(ip);
}


/*
 * ROUTINES TO SETUP DMPV EVENTS AND DUMP DUMPVARS HEADER AT SETUP SLOT END
 */

/*
 * setup the dumpvars header
 * called at end of time when first $dumpvars executed
 */
extern void __setup_dmpvars()
{
 struct mdvmast_t *mdvp;

 /* SJM 04/20/00 - in case of reset, must not reallocate */ 
 /* but possible for after reset to invoke dumpvars but not original */
 if (__dv_buffer == NULL) __dv_buffer = __my_malloc(DVBUFSIZ);
 __dv_nxti = 0;
 /* case 1 - all form - know only one mdv master */
 if (__dv_isall_form)
  {
   /* DBG remove -- */
   if (__dv_hdr == NULL || __dv_hdr->mdvnxt != NULL
    || __dv_hdr->mdv_itprt_idp != NULL) __misc_terr(__FILE__, __LINE__);
   /* ---- */

   setup_all_dvars();
  }
 else
  {
   for (mdvp = __dv_hdr; mdvp != NULL; mdvp = mdvp->mdvnxt)
    setup_1argdvars(mdvp);
  }

 /* AIV 04/22/10 - setup FST file for writing */
 if (__is_fst) 
  {
   fst_setup();
   return;
  }
 sprintf(__xs2, "$date\n    %s\n$end\n", __pv_timestamp);
 __adds(__xs2);
 dv_wr(FALSE);

 sprintf(__xs2, "$version\n    %s%s of %s\n$end\n", __vers, __vers2, __ofdt);
 __adds(__xs2);
 dv_wr(FALSE);

 /* need to use actual time scale - is default right */
 sprintf(__xs2, "$timescale\n    %s\n$end\n", __to_timunitnam(__xs,
  __des_timeprec));
 __adds(__xs2);
 dv_wr(FALSE);

 /* first write the header info for variables form */
 for (mdvp = __dv_hdr; mdvp != NULL; mdvp = mdvp->mdvnxt)
  wr_1argdvhdr(mdvp);
 sprintf(__xs2, "$enddefinitions $end\n");
 __adds(__xs2);
 dv_wr(FALSE);
}

/* size (number) of buffer - 256MB + number of nets dumped */
#define WRITE_NET_NUM (1024*1024*256)/sizeof(struct dmp_buf_t)

/*
 * ROUTINES TO HANDLE FST SETUP
 *
 * routines name conventions all start with fst_ and usually correspond
 * to the dumpvars routines with just a fst_ pended to the routine name
 */

/* 
 * setup fst file 
 */
static void fst_setup(void)
{
 int32 i, num_mb;
 struct mdvmast_t *mdvp;
 struct dmp_buf_t *dbp;
 char *chp;

 if (__fst_ctx != NULL) __misc_terr(__FILE__, __LINE__);

 /* use_compressed_hier => TRUE just packs the info at the end of the file */
 /* if FALSE can read into GTKWave prior to end of sim with the made .hier */
 /* file - so setting to TRUE to remove */
 if ((__fst_ctx = fstWriterCreate(__dv_fnam, TRUE)) == NULL)
  {
   if (strcmp(__dv_fnam, DFLFSTFNAM) == 0)
    {
bad_fst_fnam:
     __pv_err(759,
      "cannot open $fstvars output file at %s - $fstvars not executed",
      __to_timstr(__xs, &__simtime));
      /* not setup but dv seen stops any future setup */
      __dv_seen = TRUE;
      __dv_state = DVST_NOTSETUP;
      return;
     }
    else
     {
      __pv_warn(589, "cannot open $fstvars output file %s trying %s",
       __dv_fnam, DFLFSTFNAM);
      strcpy(__dv_fnam, DFLFSTFNAM);
      if ((__fst_ctx = fstWriterCreate(__dv_fnam, TRUE)) == NULL)
       goto bad_fst_fnam;
     }
  }

 /* lz4 is fastest so using it */
 fstWriterSetPackType(__fst_ctx, FST_WR_PT_LZ4); 	

 /* repack on close can shrink the file even more but takes time to recomp */
 /* so it is an option turned - off be default */
 fstWriterSetRepackOnClose(__fst_ctx, __fst_repack);

 fstWriterSetDate(__fst_ctx, __pv_timestamp); 
 sprintf(__xs2, "%s%s of %s", __vers, __vers2, __ofdt);
 fstWriterSetVersion(__fst_ctx, __xs2); 

 /* if user called $fstDumplimit set the value */
 if (__dv_dumplimit_size != 0) 
  {
   fstWriterSetDumpSizeLimit(__fst_ctx, __dv_dumplimit_size);
  }

 /* set time scale */
 fstWriterSetTimescaleFromString(__fst_ctx, 
   fst_to_timunitnam(__xs, __des_timeprec));

 /* create idcode tree scopes */
 for (mdvp = __dv_hdr; mdvp != NULL; mdvp = mdvp->mdvnxt)
  fst_1argdvhdr(mdvp);

 /* create the work area to copy into for fst vector values */
 __fst_work_area = (byte *) __my_malloc(__fst_max_work_area);

 /* AIV 04/06/12 - FST dumping can now be done in parallel mode */
 /* default is off */
 /* if +fst+parallel=on or environment variable CVC_FST_PARALLEL set */
 /* turn on parallel mode */
 if (getenv ("CVC_FST_PARALLEL") != NULL) 
  {
   if (__verbose) __cv_msg("  FST Parallel mode turned on.\n");
   __fst_parallel = TRUE;
  }
 
 /* if parallel mode 2 - do FST and buffering */
 if (getenv ("CVC_FST_PARALLEL2") != NULL) 
  {
   if (__verbose) __cv_msg("  FST Parallel mode 2 turned on.\n");
   __fst_parallel = TRUE;
   __fst_parallel2 = TRUE;
  }

 /* AIV 04/25/12 - if FST parallel mode 1 - just do FST parallel */
 if (__fst_parallel)
  {
   fstWriterSetParallelMode(__fst_ctx, TRUE);
  }

 if (__fst_parallel2)
  {
   pthread_mutex_init(&__dump_mutex, NULL);
   pthread_attr_init(&__thread_attr);
   pthread_attr_setdetachstate(&__thread_attr, PTHREAD_CREATE_DETACHED);
   pthread_cond_init(&__buffer_empty, NULL);
   pthread_create(&__dump_thread, &__thread_attr, fst_writer_thread, NULL);

   /* if CVC_WRITE_MEMORY set change to X MB write buffer */
   if ((chp = getenv ("CVC_WRITE_MEMORY")) != NULL) 
    {
     num_mb = atoi(chp);
     if (num_mb <= 0 || num_mb > 0x0fffffff)
      {
       __dump_buffer_size = WRITE_NET_NUM;
      }
     else
      {
       if (__verbose) 
        {
         __cv_msg("  FST Parallel memory changed to %dMB.\n", num_mb);
        }
       __dump_buffer_size = (num_mb*(1024*1024))/sizeof(struct dmp_buf_t);
      } 
    }
   else
    {
     /* if extra large fst design - just set to size of buffer */
     if (__fst_next_idcode > WRITE_NET_NUM) __dump_buffer_size = WRITE_NET_NUM;
     else
      {
       /* otherwise buffer + num nets dumping */
       __dump_buffer_size = WRITE_NET_NUM + __fst_next_idcode;
      }
    }
   __dump_buffer = (struct dmp_buf_t *) 
    __my_malloc(sizeof(struct dmp_buf_t)*__dump_buffer_size);
   for (i = 0; i < __dump_buffer_size; i++)
    {
     dbp = &(__dump_buffer[i]);
     dbp->dvsu.buf = NULL;
     dbp->idcode = -1;
     dbp->bval = 0;
     dbp->np = NULL;
     dbp->arr_flat_ndx = -1;
    }
   __write_ndx = 0;
   __dump_next_ndx = 0;
   __fst_work_svec = (byte *) __my_malloc(__fst_max_work_area);
  }
}

/*
 * set conversion function for FST dump vars formatting 
 */
static void fst_set_dmpv_bld_func(struct net_t *np)
{
 /* if parallel set to parallel function pointers */
 /* AIV 04/25/12 - now only paralel buffer if parallel mode 2 */
 if (__fst_parallel2)
  {
   fst_set_dmpv_bld_func_thrd(np);
   return;
  }

 if (np->ntyp == N_EVENT) np->dmpv_funcu.single = fst_bld1_dmpv_event; 
 else if (np->n_isavec) 
  {
   if (np->ntyp == N_REAL)
    {
     /* AIV 07/26/10 - need to handle the real array case as well */
     if (np->n_isarr) 
      {
       np->dmpv_funcu.single = fst_bld1_dmpv_real_array; 
      }
     else np->dmpv_funcu.single = fst_bld1_dmpv_real; 
    }
   else if (np->n_stren)
    {
     np->dmpv_funcu.single = fst_bld1_dmpv_vector_svec; 
    }
   else if (np->n_2state)
    {
     if (np->n_isarr)
      {
       if (np->nwid > WBITS) 
        {
         np->dmpv_funcu.single = fst_bld1_dmpv_vector_2state_wide_array; 
        }
       else np->dmpv_funcu.single = fst_bld1_dmpv_vector_2state_1w_array; 
      }
     else
      {
       if (np->nwid > WBITS) 
        {
         np->dmpv_funcu.single = fst_bld1_dmpv_vector_2state_wide; 
        }
       else np->dmpv_funcu.single = fst_bld1_dmpv_vector_2state_1w; 
      }
    }
   else if (np->nwid <= WBITS)
    {
     if (np->n_isarr) 
      {
       /* if blen > WBITS/2 for array it is still wide */
       if (np->nwid > WBITS/2) 
        {
         np->dmpv_funcu.single = fst_bld1_dmpv_vector_notpacked_1w_array; 
        }
       else np->dmpv_funcu.single = fst_bld1_dmpv_vector_1w_packed_array; 
      }
     else np->dmpv_funcu.single = fst_bld1_dmpv_vector_1w; 
    }
   else 
    {
     if (np->n_isarr) np->dmpv_funcu.single = fst_bld1_dmpv_vector_wide_array; 
     else np->dmpv_funcu.single = fst_bld1_dmpv_vector_wide; 
    }
  }
 else 
  {
   if (np->n_isarr) 
    {
     if (np->n_2state) 
      {
       np->dmpv_funcu.single = fst_bld1_dmpv_scalar_2state_array; 
      }
     else np->dmpv_funcu.single = fst_bld1_dmpv_scalar_array; 
    }
   else 
    {
     /* 2-state scalar uses the same routine */
     np->dmpv_funcu.single = fst_bld1_dmpv_scalar; 
    }
  }
}

/*
 *
 */
static void fst_set_dmpv_bld_func_thrd(struct net_t *np)
{
 if (np->ntyp == N_EVENT) np->dmpv_funcu.parallel = fst_bld1_dmpv_event_thrd; 
 else if (np->n_isavec) 
  {
   if (np->ntyp == N_REAL)
    {
     /* AIV 07/26/10 - need to handle the real array case as well */
     if (np->n_isarr) 
      {
       np->dmpv_funcu.parallel = fst_bld1_dmpv_real_array_thrd; 
      }
     else np->dmpv_funcu.parallel = fst_bld1_dmpv_real_thrd; 
    }
   else if (np->n_stren)
    {
     np->dmpv_funcu.parallel = fst_bld1_dmpv_vector_svec_thrd; 
    }
   else if (np->n_2state)
    {
     if (np->n_isarr)
      {
       if (np->nwid > WBITS) 
        {
         np->dmpv_funcu.parallel = fst_bld1_dmpv_vector_2state_wide_array_thrd; 
        }
       else 
        {
         np->dmpv_funcu.parallel = fst_bld1_dmpv_vector_2state_1w_array_thrd; 
        }
      }
     else
      {
       if (np->nwid > WBITS) 
        {
         np->dmpv_funcu.parallel = fst_bld1_dmpv_vector_2state_wide_thrd; 
        }
       else np->dmpv_funcu.parallel = fst_bld1_dmpv_vector_2state_1w_thrd; 
      }
    }
   else if (np->nwid <= WBITS)
    {
     if (np->n_isarr) 
      {
       /* if blen > WBITS/2 for array it is still wide */
       if (np->nwid > WBITS/2) 
        {
         np->dmpv_funcu.parallel = 
           fst_bld1_dmpv_vector_notpacked_1w_array_thrd; 
        }
       else 
        {
         np->dmpv_funcu.parallel = fst_bld1_dmpv_vector_1w_packed_array_thrd; 
        }
      }
     else np->dmpv_funcu.parallel = fst_bld1_dmpv_vector_1w_thrd; 
    }
   else 
    {
     if (np->n_isarr) 
      {
       np->dmpv_funcu.parallel = fst_bld1_dmpv_vector_wide_array_thrd; 
      }
     else np->dmpv_funcu.parallel = fst_bld1_dmpv_vector_wide_thrd; 
    }
  }
 else 
  {
   if (np->n_isarr) 
    {
     if (np->n_2state) 
      {
       np->dmpv_funcu.parallel = fst_bld1_dmpv_scalar_2state_array_thrd; 
      }
     else np->dmpv_funcu.parallel = fst_bld1_dmpv_scalar_array_thrd; 
    }
   else 
    {
     /* 2-state scalar uses the same routine */
     np->dmpv_funcu.parallel = fst_bld1_dmpv_scalar_thrd; 
    }
  }
}


/*
 * convert all time units to Novas string to set time scale
 * same expcept no spaces
 * AIV LOOKATME - maybe just remove the space from to_timunitnam????
 */
static char *fst_to_timunitnam(char *s, word32 unit)
{
 switch ((byte) unit) {
  case 0: strcpy(s, "1s"); break; 
  case 1: strcpy(s, "100ms"); break;
  case 2: strcpy(s, "10ms"); break;
  case 3: strcpy(s, "1ms"); break;
  case 4: strcpy(s, "100us"); break;
  case 5: strcpy(s, "10us"); break;
  case 6: strcpy(s, "1us"); break;
  case 7: strcpy(s, "100ns"); break;
  case 8: strcpy(s, "10ns"); break;
  case 9: strcpy(s, "1ns"); break;
  case 10: strcpy(s, "100ps"); break;
  case 11: strcpy(s, "10ps"); break;
  case 12: strcpy(s, "1ps"); break;
  case 13: strcpy(s, "100fs"); break;
  case 14: strcpy(s, "10fs"); break;
  case 15: strcpy(s, "1fs"); break;
  default: __case_terr(__FILE__, __LINE__);
 }
 return(s);
}

/*
 * setup the fst scope and variable declarations
 */
static void fst_1argdvhdr(struct mdvmast_t *mdvp)
{
 int32 ii;
 struct itree_t *itp, *itp2, *mdv_itp;
 struct mod_t *mdp;
 struct task_t *tskp;
 struct net_t *np;

 /* case 0: all of design */
 if (mdvp->mdv_itprt_idp == NULL)
  {
   for (ii = 0; ii < __numtopm; ii++)
    {
     itp = __it_roots[ii];
     fstWriterSetSourceInstantiationStem(__fst_ctx, __in_fils[itp->itip->isym->syfnam_ind], itp->itip->isym->sylin_cnt - 1, 1); // line number is off by one
     fstWriterSetSourceStem(__fst_ctx, __in_fils[itp->itip->imsym->syfnam_ind], itp->itip->imsym->sylin_cnt, 1);
     fstWriterSetScope(__fst_ctx, FST_ST_VCD_MODULE, itp->itip->isym->synam,
      fst_rmv_dollar_module_name(itp->itip->imsym->synam)); 
     fst_1subtree_allvars(itp, 0);
     fstWriterSetUpscope(__fst_ctx);
    }
   /* AIV 09/13/11  for the removed -y top level generated modules that */
   /* are now linked out of __it_roots - see mdp->m_gened_remove  */
   /* fstvars are never generated and still may need to be setup because */
   /* other calls use __modhdr - and cannot link out of this list */
   /* AIV FIXME if remove need for m_gened_remove - remove this */
   for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
    {
     if (!mdp->m_gened_fstvars)
      {
       for (ii = 0; ii < mdp->flatinum; ii++)
        {
         itp = mdp->moditps[ii];
         fstWriterSetSourceInstantiationStem(__fst_ctx, __in_fils[itp->itip->isym->syfnam_ind], itp->itip->isym->sylin_cnt - 1, 1); // line number is off by one
         fstWriterSetSourceStem(__fst_ctx, __in_fils[itp->itip->imsym->syfnam_ind], itp->itip->imsym->sylin_cnt, 1);
         fstWriterSetScope(__fst_ctx, FST_ST_VCD_MODULE, itp->itip->isym->synam,
           fst_rmv_dollar_module_name(itp->itip->imsym->synam)); 
         fst_1subtree_allvars(itp, 0);
         fstWriterSetUpscope(__fst_ctx);
        }
      }
    }
   return;
  }

 /* case 1 simple variable */
 mdv_itp = (struct itree_t *) mdvp->mdv_itprt_idp[MD_ITP];
 if ((np = mdvp->mdv_np) != NULL)
  {
   /* no need to check for array 1 wire form - illegal if array */
   tskp = mdvp->mdv_tskp;
   fst_fromtop_iscopeto(mdv_itp);
   /* AIV 05/04/10 - this was missing the task scope call */
   if (tskp != NULL) fst_tskscopeto(tskp->tsksymtab);

   itp2 = mdv_itp;
   mdp = itp2->itip->imsym->el.emdp;
   fst_create_vars(np, itp2->it_idp, mdp->flatinum, mdvp);
   if (tskp != NULL) fst_tskscopeback(mdvp->mdv_tskp->tsksymtab);
   fst_totop_iscopeback(mdv_itp);
  }
 else
  {
   /* case 2 inst. scope */
   /* this handles all its own scope movements */
   /* case inst. with some levels underneath */
   /* descend number of levels - 0 is all, 1 is just current */
   fst_fromtop_iscopeto(mdv_itp);
   fst_1subtree_allvars(mdv_itp, mdvp->mdv_levels);
   fst_totop_iscopeback(mdv_itp);
   /* AIV 01/28/05 - removed an extra upscope printing */ 
  }
}

/*
 * write commands to scope to an itree place
 */
static void fst_fromtop_iscopeto(struct itree_t *itp)
{
 int32 i;
 int32 frtoplevs;
 struct itree_t *witp;
 struct itree_t **itps;

 /* AIV 09/02/08 - there was completely wrong and must have been */
 /* since converting to idp - was only using the last scope name */
 /* method needs stack mechanism to print up scopes in reverse order */

 /* count number of scopes */
 frtoplevs = 0;
 for (witp = itp; witp != NULL; witp = witp->up_it)
  { 
   frtoplevs++;
  }
 /* alloc array only - needed to setup so extra pass ok */
 itps = (struct itree_t **) __my_malloc(frtoplevs*sizeof(struct itree_t *));
 i = 0;
 /* reverse the order to print */
 for (witp = itp; witp != NULL; witp = witp->up_it)
  { 
   i++;
   itps[frtoplevs-i] = witp;
  }
 /* print the scope */
 for (i = 0; i < frtoplevs; i++) 
  {
   witp = itps[i];
   fstWriterSetSourceInstantiationStem(__fst_ctx, __in_fils[witp->itip->isym->syfnam_ind], witp->itip->isym->sylin_cnt - 1, 1); // line number is off by one
   fstWriterSetSourceStem(__fst_ctx, __in_fils[witp->itip->imsym->syfnam_ind], witp->itip->imsym->sylin_cnt, 1);
   fstWriterSetScope(__fst_ctx, FST_ST_VCD_MODULE, witp->itip->isym->synam, 
     fst_rmv_dollar_module_name(witp->itip->imsym->synam)); 
   /* AIV 04/11/12 - removed dv_wr - here this is for VCD not FST */
  }
 /* free temp array */
 __my_free(itps, frtoplevs*sizeof(struct itree_t *));
}

static void fst_totop_iscopeback(struct itree_t *itp)
{
 struct itree_t *witp;

 for (witp = itp;;)
  {
   fstWriterSetUpscope(__fst_ctx);
   if ((witp = witp->up_it) == NULL) break;  
  }
}

/*
 * write the scope into the task/lb/func - must pass tasks symbol
 */
static void fst_tskscopeto(struct symtab_t *sytp)
{
 enum fstScopeType fst_type;
 struct task_t *tskp;

 if (sytp->sytpar != NULL && sytp->sytpar->sypofsyt->sytyp != SYM_M)
  fst_tskscopeto(sytp->sytpar);
 tskp = sytp->sypofsyt->el.etskp;
 fst_type = fst_dvtsktyp(tskp->tsktyp),
 fstWriterSetScope(__fst_ctx, fst_type, tskp->tsksyp->synam, NULL); 
}

static void fst_tskscopeback(struct symtab_t *sytp)
{
 struct symtab_t *wsytp;

 for (wsytp = sytp->sytpar;;)
  {
   fstWriterSetUpscope(__fst_ctx);

   /* keep going until back to containing module scope */
   if (wsytp->sypofsyt->sytyp == SYM_M) break;
  }
}

/*
 * FST version
 * write the variables for all instances in and under 1 itree module loc.
 * descends level numbers 0 - all
 * when called expects scope to be moved upon return leaves scope at itp
 */
static void fst_1subtree_allvars(struct itree_t *itp, int32 level)
{
 int32 ii;
 struct mod_t *imdp;
 struct symtab_t *sytp;
 struct itree_t *down_itp;

 fst_1inst_dvhdrs(itp);
 imdp = itp->itip->imsym->el.emdp;
 /* when done scope left at instance same as called */
 if ((sytp = imdp->msymtab->sytofs) != NULL) fst_tasks_dvhdrs(itp, sytp);
 if (level != 1)
  { 
   for (ii = 0; ii < imdp->minum; ii++)
    { 
     down_itp = &(itp->in_its[ii]);
     fstWriterSetSourceInstantiationStem(__fst_ctx, __in_fils[down_itp->itip->isym->syfnam_ind], down_itp->itip->isym->sylin_cnt - 1, 1); // line number is off by one
     fstWriterSetSourceStem(__fst_ctx, __in_fils[down_itp->itip->imsym->syfnam_ind], down_itp->itip->imsym->sylin_cnt, 1);
     fstWriterSetScope(__fst_ctx, FST_ST_VCD_MODULE, 
      down_itp->itip->isym->synam, fst_rmv_dollar_module_name(down_itp->itip->imsym->synam)); 
     fst_1subtree_allvars(down_itp, (level != 0) ? level - 1 : 0);
     fstWriterSetUpscope(__fst_ctx);
    }
  }
}

/*
 * create a fst variable declarations for all nets in a module 
 */
static void fst_1inst_dvhdrs(struct itree_t *itp)
{
 int32 ni;
 struct net_t *np;
 struct mod_t *mdp;
 t_midat *idp;

 mdp = itp->itip->imsym->el.emdp;
 /* AIV 09/13/11 - now need to mark gened modules */
 mdp->m_gened_fstvars = TRUE;
 /* write all wires */
 if (mdp->mnnum == 0) return;
 for (ni = 0, np = &(mdp->mnets[0]); ni < mdp->mnnum; ni++, np++)
  {
   /* SJM - 07/02/00 - now dvcods pre-built as strings */
   idp = itp->it_idp;   
   if ((idp[np->nchgaction_ofs] & NCHG_DMPVARED) == 0) continue;

   fst_create_vars(np, idp, mdp->flatinum, NULL);
  }
}

/*
 * AIV 07/20/10 - this routine now handles the creating of fst variable
 * names by handling arrays as well.
 */
static void fst_create_vars(struct net_t *np, t_midat *idp, int32 ninsts,
 struct mdvmast_t *mdvp)
{
 int32 inum, num_els, ri1, ri2, dwid, ri1_2, ri2_2, dwid_2;
 int32 ndx1, ndx2, i, j, fndx, flatndx;
 int32 *ip;
 struct dvchgnets_t *dvchgp;
 struct mda_t *mdap;

 inum = (int32) idp[MD_INUM];
 /* check if variable is an array */
 if (np->n_isarr)
  {
   num_els = np->arr_num_els;
   mdap = np->mda;
   if (mdvp == NULL)
    {
     /* if not index - check if entire array dumping is on */
     if (!can_dump_entire_array(np)) return;

     /* single dim - just dump entire array */
     if (mdap == NULL)
      {
       ri1 = np->nu.rngarr->ai1;
       ri2 = np->nu.rngarr->ai2;
       for (i = 0; i < num_els; i++)
        {
         dvchgp = &(np->dvns[(inum*num_els)+i]);
         ndx1 = __unnormalize2_ndx(i, ri1, ri2);
         fst_create_one_var(np, idp, dvchgp, ninsts, ndx1, -1, i); 
        }
      }
     else
      {
       /* 2-dim - just dump entire array */
       /* DBG remove -- */
       if (mdap->dimension > 2) __misc_terr(__FILE__, __LINE__);
       /* ----- */

       __getarr_range_mda(np, &ri1, &ri2, &dwid, 0);
       __getarr_range_mda(np, &ri1_2, &ri2_2, &dwid_2, 1);
       fndx = 0;
       for (i = 0; i < dwid; i++)
        {
         for (j = 0; j < dwid_2; j++)
          {
           ndx1 = __unnormalize2_ndx(i, ri1, ri2);
           ndx2 = __unnormalize2_ndx(j, ri1_2, ri2_2);
           dvchgp = &(np->dvns[(inum*num_els)+fndx]);
           fst_create_one_var(np, idp, dvchgp, ninsts, ndx1, ndx2, fndx); 
           fndx++;
          }
        }
      }
    }
   else
    {
     /* AIV 01/24/11 - if original wire array do not dump */
     /* individual elements - this are converted to vectors */
     if (np->ntyp < NONWIRE_ST) return;
     if (!__dump_arrays) return;

     /* index array element */
     flatndx = mdvp->mdv_flat_ndx;
     dvchgp = &(np->dvns[(inum*num_els)+flatndx]);
     if (mdap != NULL) 
      {
       ip = mdvp->mdv_mda_indices;
       fst_create_one_var(np, idp, dvchgp, ninsts, ip[0], ip[1], flatndx); 
      }
     else fst_create_one_var(np, idp, dvchgp, ninsts, -1, -1, flatndx); 
    }
  }
 else
  {
   /* regular non-array element */ 
   /* AIV 05/17/10 - new fixed dv struct scheme */
   dvchgp = &(np->dvns[inum]);
   fst_create_one_var(np, idp, dvchgp, ninsts, -1, -1, -1); 
  }
}
   
/*
 * create one net declaration in fst
 */
static void fst_create_one_var(struct net_t *np, t_midat *idp, 
 struct dvchgnets_t *dvchgp, int32 ninsts, int32 ndx1, int32 ndx2, 
 int32 flatndx)
{
 int32 r1, r2;
 enum fstVarType ntype;
 enum fstVarDir iotyp;
 fstHandle idcode;
 char *cp;

 /* AIV 01/26/11 - no automatic tasks or wire arrays should be seen here */
 /* DBG remove -- */
 if (np->n_is_auto_var) __misc_terr(__FILE__, __LINE__);
 if (np->n_isarr && np->ntyp < NONWIRE_ST) __misc_terr(__FILE__, __LINE__);
 /* ---- */

 /* set conversion function set the net type */
 fst_set_dmpv_bld_func(np);

 /* handle the real case and return */
 if (np->ntyp == N_REAL)
  {
   /* AIV 07/26/10 - need to handle real case */
   /* AIV 09/02/10 - index was wrong here */
   /* AIV 09/15/10 - reals have no range */
   if (flatndx != -1)
    {
     dvchgp->dv_flat_ndx = flatndx;
     sprintf(__xs2, "%s[%d]", np->nsym->synam, ndx1);
     cp = __xs2;
    }
   else cp = np->nsym->synam;

   iotyp = fst_dir_type(np->iotyp);
   idcode = fstWriterCreateVar(__fst_ctx, FST_VT_VCD_REAL, iotyp, 
       8, cp, 0);
   __fst_next_idcode++;
   dvchgp->idu.idcode = idcode; 
   /* AIV 07/26/10 - this doesn't need to set max work area - in fact */
   /* it was wrong to set here since a later real could shrink size */
   return;
  }
 else if (flatndx != -1)
  {
   dvchgp->dv_flat_ndx = flatndx;
   __getwir_range(np, &r1, &r2);
   /* AIV 04/07/09 - shouldn't be adding \n to this string */
   /* handle the 2-dim case */
   if (ndx2 != -1)
    {
     sprintf(__xs2, "%s[%d][%d] [%d:%d]", np->nsym->synam, ndx1, ndx2, r1, 
      r2);
    }
   else
    {
     sprintf(__xs2, "%s[%d] [%d:%d]", np->nsym->synam, ndx1, r1, r2);
    }
   cp = __xs2;
   /* max work area must be at least as large as greatest vector */
   if (np->nwid > __fst_max_work_area) __fst_max_work_area = np->nwid;
  }
 /* if vector get the range */
 else if (np->n_isavec)
  {
   __getwir_range(np, &r1, &r2);
   /* AIV 04/07/09 - shouldn't be adding \n to this string */
   sprintf(__xs2, "%s[%d:%d]", np->nsym->synam, r1, r2);
   cp = __xs2;
   /* max work area must be at least as large as greatest vector */
   if (np->nwid > __fst_max_work_area) __fst_max_work_area = np->nwid;
  } 
 /* scalar case range is 0 */
 else
  {
   r1 = r2 = 0;
   cp = np->nsym->synam;
  }

 ntype = fst_net_type(np->ntyp);
 iotyp = fst_dir_type(np->iotyp);
 idcode = fstWriterCreateVar(__fst_ctx, ntype, iotyp, np->nwid, cp, 
  0);
 __fst_next_idcode++;
 dvchgp->idu.idcode = idcode; 
}

/*
 * setup all tasks scope/variables in fst
 */
static void fst_tasks_dvhdrs(struct itree_t *itp,
 struct symtab_t *sytp)
{
 int32 ni;
 struct net_t *np;
 enum fstScopeType fst_type;
 struct task_t *tskp;
 struct mod_t *mdp;

 mdp = itp->itip->imsym->el.emdp;
 /* write all contained tasks/funcs/lbs - through symbol table list */
 for (; sytp != NULL; sytp = sytp->sytsib)
  {
   tskp = sytp->sypofsyt->el.etskp;
#ifdef __XPROP__
   /* if dummy xprop task must skip here */
   if (tskp == mdp->xprop_nb_taskp) return;
#endif
   if (tskp->is_inter_blk) continue;
   /* notice must set up scope even if no variables */
   /* if (tskp->tsk_regs == NULL) continue; */
   fst_type = fst_dvtsktyp(tskp->tsktyp),
   fstWriterSetScope(__fst_ctx, fst_type, tskp->tsksyp->synam, NULL); 

   if (tskp->trnum != 0)
    {
     for (ni = 0, np = &(tskp->tsk_regs[0]); ni < tskp->trnum; ni++, np++)
      {
       /* AIV 01/26/11 - if automatic array do not dump value */
       if (np->n_is_auto_var) continue;
       fst_create_vars(np, itp->it_idp, mdp->flatinum, NULL);
      } 
    }
   if (sytp->sytofs != NULL) fst_tasks_dvhdrs(itp, sytp->sytofs);
   fstWriterSetUpscope(__fst_ctx);
  } 
}

/*
 * build string name of task for $dumpvars - all blocks labeled
 */
static enum fstScopeType fst_dvtsktyp(word32 tskt)
{
 switch (tskt) {
  case Begin: return(FST_ST_VCD_BEGIN);
  case FORK: return(FST_ST_VCD_FORK);
  case FUNCTION: return(FST_ST_VCD_FUNCTION);
  case TASK: return(FST_ST_VCD_TASK);
  default: __case_terr(__FILE__, __LINE__);
 }
 return(-1);
}
   
/*
 * return FST_ wire type
 */
static enum fstVarType fst_net_type(int32 ntyp)
{
 /* SJM 08-04-10 SV - hack so can make logic and reg both be bit for dbg */
 /* this makes routine just sort of stupid */

 switch ((byte) ntyp) {
  case N_WIRE: return(FST_VT_VCD_WIRE);
  case N_TRI: return(FST_VT_VCD_TRI);
  case N_TRI0: return(FST_VT_VCD_TRI0);
  case N_TRI1: return(FST_VT_VCD_TRI1);
  case N_TRIOR: return(FST_VT_VCD_TRIOR);
  case N_TRIAND: return(FST_VT_VCD_TRIAND);
  case N_TRIREG: return(FST_VT_VCD_TRIREG);
  case N_WA: return(FST_VT_VCD_WAND);
  case N_WO: return(FST_VT_VCD_WOR);
  case N_SUPPLY0: return(FST_VT_VCD_SUPPLY0);
  case N_SUPPLY1: return(FST_VT_VCD_SUPPLY1);
  case N_BIT: return(FST_VT_VCD_REG);
  case N_REG: return(FST_VT_VCD_REG);
  case N_LOGIC: return(FST_VT_VCD_REG);
  case N_INT: return(FST_VT_VCD_INTEGER);
  case N_CINT: return(FST_VT_VCD_INTEGER);
  case N_TIME: return(FST_VT_VCD_TIME);
  case N_REAL: return(FST_VT_VCD_REAL);
  case N_EVENT: return(FST_VT_VCD_EVENT);
  default: __case_terr(__FILE__, __LINE__);
 }
 return(-1);
}

/* FST - version precomputed using fixed values - see table.c */
/* AIV 05/17/10 - table to go from one byte 1/0 to word64 for conversion */
/* on byte boundary */
/* this is currently the same as byte_to_chars - but may change so leaving */
/* table for future FST changes */
static const word64 fst_byte_to_chars[256] = {
0x3030303030303030ULL, 
0x3130303030303030ULL, 0x3031303030303030ULL, 0x3131303030303030ULL, 
0x3030313030303030ULL, 0x3130313030303030ULL, 0x3031313030303030ULL, 
0x3131313030303030ULL, 0x3030303130303030ULL, 0x3130303130303030ULL, 
0x3031303130303030ULL, 0x3131303130303030ULL, 0x3030313130303030ULL, 
0x3130313130303030ULL, 0x3031313130303030ULL, 0x3131313130303030ULL, 
0x3030303031303030ULL, 0x3130303031303030ULL, 0x3031303031303030ULL, 
0x3131303031303030ULL, 0x3030313031303030ULL, 0x3130313031303030ULL, 
0x3031313031303030ULL, 0x3131313031303030ULL, 0x3030303131303030ULL, 
0x3130303131303030ULL, 0x3031303131303030ULL, 0x3131303131303030ULL, 
0x3030313131303030ULL, 0x3130313131303030ULL, 0x3031313131303030ULL, 
0x3131313131303030ULL, 0x3030303030313030ULL, 0x3130303030313030ULL, 
0x3031303030313030ULL, 0x3131303030313030ULL, 0x3030313030313030ULL, 
0x3130313030313030ULL, 0x3031313030313030ULL, 0x3131313030313030ULL, 
0x3030303130313030ULL, 0x3130303130313030ULL, 0x3031303130313030ULL, 
0x3131303130313030ULL, 0x3030313130313030ULL, 0x3130313130313030ULL, 
0x3031313130313030ULL, 0x3131313130313030ULL, 0x3030303031313030ULL, 
0x3130303031313030ULL, 0x3031303031313030ULL, 0x3131303031313030ULL, 
0x3030313031313030ULL, 0x3130313031313030ULL, 0x3031313031313030ULL, 
0x3131313031313030ULL, 0x3030303131313030ULL, 0x3130303131313030ULL, 
0x3031303131313030ULL, 0x3131303131313030ULL, 0x3030313131313030ULL, 
0x3130313131313030ULL, 0x3031313131313030ULL, 0x3131313131313030ULL, 
0x3030303030303130ULL, 0x3130303030303130ULL, 0x3031303030303130ULL, 
0x3131303030303130ULL, 0x3030313030303130ULL, 0x3130313030303130ULL, 
0x3031313030303130ULL, 0x3131313030303130ULL, 0x3030303130303130ULL, 
0x3130303130303130ULL, 0x3031303130303130ULL, 0x3131303130303130ULL, 
0x3030313130303130ULL, 0x3130313130303130ULL, 0x3031313130303130ULL, 
0x3131313130303130ULL, 0x3030303031303130ULL, 0x3130303031303130ULL, 
0x3031303031303130ULL, 0x3131303031303130ULL, 0x3030313031303130ULL, 
0x3130313031303130ULL, 0x3031313031303130ULL, 0x3131313031303130ULL, 
0x3030303131303130ULL, 0x3130303131303130ULL, 0x3031303131303130ULL, 
0x3131303131303130ULL, 0x3030313131303130ULL, 0x3130313131303130ULL, 
0x3031313131303130ULL, 0x3131313131303130ULL, 0x3030303030313130ULL, 
0x3130303030313130ULL, 0x3031303030313130ULL, 0x3131303030313130ULL, 
0x3030313030313130ULL, 0x3130313030313130ULL, 0x3031313030313130ULL, 
0x3131313030313130ULL, 0x3030303130313130ULL, 0x3130303130313130ULL, 
0x3031303130313130ULL, 0x3131303130313130ULL, 0x3030313130313130ULL, 
0x3130313130313130ULL, 0x3031313130313130ULL, 0x3131313130313130ULL, 
0x3030303031313130ULL, 0x3130303031313130ULL, 0x3031303031313130ULL, 
0x3131303031313130ULL, 0x3030313031313130ULL, 0x3130313031313130ULL, 
0x3031313031313130ULL, 0x3131313031313130ULL, 0x3030303131313130ULL, 
0x3130303131313130ULL, 0x3031303131313130ULL, 0x3131303131313130ULL, 
0x3030313131313130ULL, 0x3130313131313130ULL, 0x3031313131313130ULL, 
0x3131313131313130ULL, 0x3030303030303031ULL, 0x3130303030303031ULL, 
0x3031303030303031ULL, 0x3131303030303031ULL, 0x3030313030303031ULL, 
0x3130313030303031ULL, 0x3031313030303031ULL, 0x3131313030303031ULL, 
0x3030303130303031ULL, 0x3130303130303031ULL, 0x3031303130303031ULL, 
0x3131303130303031ULL, 0x3030313130303031ULL, 0x3130313130303031ULL, 
0x3031313130303031ULL, 0x3131313130303031ULL, 0x3030303031303031ULL, 
0x3130303031303031ULL, 0x3031303031303031ULL, 0x3131303031303031ULL, 
0x3030313031303031ULL, 0x3130313031303031ULL, 0x3031313031303031ULL, 
0x3131313031303031ULL, 0x3030303131303031ULL, 0x3130303131303031ULL, 
0x3031303131303031ULL, 0x3131303131303031ULL, 0x3030313131303031ULL, 
0x3130313131303031ULL, 0x3031313131303031ULL, 0x3131313131303031ULL, 
0x3030303030313031ULL, 0x3130303030313031ULL, 0x3031303030313031ULL, 
0x3131303030313031ULL, 0x3030313030313031ULL, 0x3130313030313031ULL, 
0x3031313030313031ULL, 0x3131313030313031ULL, 0x3030303130313031ULL, 
0x3130303130313031ULL, 0x3031303130313031ULL, 0x3131303130313031ULL, 
0x3030313130313031ULL, 0x3130313130313031ULL, 0x3031313130313031ULL, 
0x3131313130313031ULL, 0x3030303031313031ULL, 0x3130303031313031ULL, 
0x3031303031313031ULL, 0x3131303031313031ULL, 0x3030313031313031ULL, 
0x3130313031313031ULL, 0x3031313031313031ULL, 0x3131313031313031ULL, 
0x3030303131313031ULL, 0x3130303131313031ULL, 0x3031303131313031ULL, 
0x3131303131313031ULL, 0x3030313131313031ULL, 0x3130313131313031ULL, 
0x3031313131313031ULL, 0x3131313131313031ULL, 0x3030303030303131ULL, 
0x3130303030303131ULL, 0x3031303030303131ULL, 0x3131303030303131ULL, 
0x3030313030303131ULL, 0x3130313030303131ULL, 0x3031313030303131ULL, 
0x3131313030303131ULL, 0x3030303130303131ULL, 0x3130303130303131ULL, 
0x3031303130303131ULL, 0x3131303130303131ULL, 0x3030313130303131ULL, 
0x3130313130303131ULL, 0x3031313130303131ULL, 0x3131313130303131ULL, 
0x3030303031303131ULL, 0x3130303031303131ULL, 0x3031303031303131ULL, 
0x3131303031303131ULL, 0x3030313031303131ULL, 0x3130313031303131ULL, 
0x3031313031303131ULL, 0x3131313031303131ULL, 0x3030303131303131ULL, 
0x3130303131303131ULL, 0x3031303131303131ULL, 0x3131303131303131ULL, 
0x3030313131303131ULL, 0x3130313131303131ULL, 0x3031313131303131ULL, 
0x3131313131303131ULL, 0x3030303030313131ULL, 0x3130303030313131ULL, 
0x3031303030313131ULL, 0x3131303030313131ULL, 0x3030313030313131ULL, 
0x3130313030313131ULL, 0x3031313030313131ULL, 0x3131313030313131ULL, 
0x3030303130313131ULL, 0x3130303130313131ULL, 0x3031303130313131ULL, 
0x3131303130313131ULL, 0x3030313130313131ULL, 0x3130313130313131ULL, 
0x3031313130313131ULL, 0x3131313130313131ULL, 0x3030303031313131ULL, 
0x3130303031313131ULL, 0x3031303031313131ULL, 0x3131303031313131ULL, 
0x3030313031313131ULL, 0x3130313031313131ULL, 0x3031313031313131ULL, 
0x3131313031313131ULL, 0x3030303131313131ULL, 0x3130303131313131ULL, 
0x3031303131313131ULL, 0x3131303131313131ULL, 0x3030313131313131ULL, 
0x3130313131313131ULL, 0x3031313131313131ULL, 0x3131313131313131ULL};

/*
 * FST version
 * AIV 05/17/10 - new optimized dsipb version for VCD dumping
 * this is the wide version where trimmed blen may be >= WBITS
 * see base - dmpv_sdispb - for more comments - basically the same routine
 */
static void fst_dmpv_sdispb(word32 *ap, word32 *bp, int32 blen)
{
 int32 wi, bi;
 word32 tmpa, tmpb;
 int32 swlen, i, nbytes, r;
 byte *byte_bp;
 word64 *wp;
 char ch;
 char *cp;

 cp = (char *) __fst_work_area;
 swlen = wlen_(blen);
 bi = ubits_(blen);
 if (bi == 0) bi = WBITS - 1; else bi--;

 wi = swlen - 1;
 /* AIV 04/27/10 - removed worthless tmpa/tmpb assign */
 if (bp[wi] == 0)
  {
   r = ((bi+1) % 8);
   for (i = 0; i < r; i++)
    {
     ch = (ap[wi] >> bi) & 1L;
     *cp = '0' + ch;
     cp++;
     bi--;
    }
   if (bi != -1) 
    {
     byte_bp = (byte *) &(ap[wi]);
     nbytes = bi/8;
     byte_bp = &(byte_bp[nbytes]);
     wp = (word64 *) cp;
     cp += (bi + 1);
     for (i = 0; i <= nbytes; i++)
      {
       *wp = fst_byte_to_chars[*byte_bp];
       byte_bp--;
       wp++;
      }
    }
  }
 else
  {
   for (;bi >= 0; bi--)
    {
     tmpa = (ap[wi] >> bi) & 1L;
     tmpb = (bp[wi] >> bi) & 1L;
     if (tmpb != 0L) { if (tmpa != 0L) ch = 'x'; else ch = 'z'; }
     else ch = '0' + ((char) tmpa);
     *cp = ch;
     cp++;
    }
  }
 wi--;
 for (; wi >= 0; wi--)
  {
   if (bp[wi] == 0)
    {
     byte_bp = (byte *) &(ap[wi]);
     wp = (word64 *) cp;
     cp += WBITS;
#ifdef __CVC32__
     wp[0] = fst_byte_to_chars[byte_bp[3]];
     wp[1] = fst_byte_to_chars[byte_bp[2]];
     wp[2] = fst_byte_to_chars[byte_bp[1]];
     wp[3] = fst_byte_to_chars[byte_bp[0]];
#else
     wp[0] = fst_byte_to_chars[byte_bp[7]];
     wp[1] = fst_byte_to_chars[byte_bp[6]];
     wp[2] = fst_byte_to_chars[byte_bp[5]];
     wp[3] = fst_byte_to_chars[byte_bp[4]];
     wp[4] = fst_byte_to_chars[byte_bp[3]];
     wp[5] = fst_byte_to_chars[byte_bp[2]];
     wp[6] = fst_byte_to_chars[byte_bp[1]];
     wp[7] = fst_byte_to_chars[byte_bp[0]];
#endif
    }
   else
    {
     for (bi = WBITS-1; bi >= 0; bi--)
      {
       tmpa = (ap[wi] >> bi) & 1L;
       tmpb = (bp[wi] >> bi) & 1L;
       if (tmpb != 0L) { if (tmpa != 0L) ch = 'x'; else ch = 'z'; }
       else ch = '0' + ((char) tmpa);
       *cp = ch;
       cp++;
      }
    }
  }
}

/*
 * 2-state version
 * same as above expect no bpart
 */
static void fst_dmpv_sdispb_2state(word32 *ap, int32 blen)
{
 int32 wi, bi;
 int32 swlen, i, nbytes, r;
 byte *byte_bp;
 word64 *wp;
 char ch;
 char *cp;

 cp = (char *) __fst_work_area;
 swlen = wlen_(blen);
 bi = ubits_(blen);
 if (bi == 0) bi = WBITS - 1; else bi--;

 wi = swlen - 1;
 r = ((bi+1) % 8);
 for (i = 0; i < r; i++)
  {
   ch = (ap[wi] >> bi) & 1L;
   *cp = '0' + ch;
   cp++;
   bi--;
  }
 if (bi != -1) 
  {
   byte_bp = (byte *) &(ap[wi]);
   nbytes = bi/8;
   byte_bp = &(byte_bp[nbytes]);
   wp = (word64 *) cp;
   cp += (bi + 1);
   for (i = 0; i <= nbytes; i++)
    {
     *wp = fst_byte_to_chars[*byte_bp];
     byte_bp--;
     wp++;
    }
  }
 wi--;
 for (; wi >= 0; wi--)
  {
   byte_bp = (byte *) &(ap[wi]);
   wp = (word64 *) cp;
   cp += WBITS;
#ifdef __CVC32__
   wp[0] = fst_byte_to_chars[byte_bp[3]];
   wp[1] = fst_byte_to_chars[byte_bp[2]];
   wp[2] = fst_byte_to_chars[byte_bp[1]];
   wp[3] = fst_byte_to_chars[byte_bp[0]];
#else
   wp[0] = fst_byte_to_chars[byte_bp[7]];
   wp[1] = fst_byte_to_chars[byte_bp[6]];
   wp[2] = fst_byte_to_chars[byte_bp[5]];
   wp[3] = fst_byte_to_chars[byte_bp[4]];
   wp[4] = fst_byte_to_chars[byte_bp[3]];
   wp[5] = fst_byte_to_chars[byte_bp[2]];
   wp[6] = fst_byte_to_chars[byte_bp[1]];
   wp[7] = fst_byte_to_chars[byte_bp[0]];
#endif
  }
}

/*
 * AIV 05/17/10 - new optimized dsipb version for VCD dumping
 * this is the 1 word version version where trimmed blen is known <= WBITS
 */
static void fst_dmpv_sdispb_1w(word32 aval, word32 bval, int32 blen)
{
 int32 bi;
 word32 tmpa, tmpb;
 int32 i, nbytes, r;
 byte *byte_bp;
 word64 *wp;
 char ch;
 char *cp;

 /* set char ptr to the begin of current char */
 bi = blen - 1;
 cp = (char *) __fst_work_area;
 /* AIV 04/27/10 - removed worthless tmpa/tmpb assign */
 if (bval == 0)
  {
   r = ((bi+1) % 8);
   for (i = 0; i < r; i++)
    {
     ch = (aval >> bi) & 1L;
     *cp = '0' + ch;
     cp++;
     bi--;
    }
   if (bi != -1) 
    {
     byte_bp = (byte *) &aval;
     nbytes = bi/8;
     byte_bp = &(byte_bp[nbytes]);
     wp = (word64 *) cp;
     cp += (bi + 1);
     for (i = 0; i <= nbytes; i++)
      {
       *wp = fst_byte_to_chars[*byte_bp];
       byte_bp--;
       wp++;
      }
    }
  }
 else
  {
   for (;bi >= 0; bi--)
    {
     tmpa = (aval >> bi) & 1L;
     tmpb = (bval >> bi) & 1L;
     if (tmpb != 0L) { if (tmpa != 0L) ch = 'x'; else ch = 'z'; }
     else ch = '0' + ((char) tmpa);
     *cp = ch;
     cp++;
    }
  }
}

/*
 * 2-state version - no bpart
 */
static void fst_dmpv_sdispb_1w_2state(word32 aval, int32 blen)
{
 int32 bi;
 int32 i, nbytes, r;
 byte *byte_bp;
 word64 *wp;
 char ch;
 char *cp;

 /* set char ptr to the begin of current char */
 bi = blen - 1;
 cp = (char *) __fst_work_area;
 r = ((bi+1) % 8);
 for (i = 0; i < r; i++)
  {
   ch = (aval >> bi) & 1L;
   *cp = '0' + ch;
   cp++;
   bi--;
  }
 if (bi != -1) 
  {
   byte_bp = (byte *) &aval;
   nbytes = bi/8;
   byte_bp = &(byte_bp[nbytes]);
   wp = (word64 *) cp;
   cp += (bi + 1);
   for (i = 0; i <= nbytes; i++)
    {
     *wp = fst_byte_to_chars[*byte_bp];
     byte_bp--;
     wp++;
    }
  }
}

/*
 * FST => convert one event it changes is always 1
 */
static void fst_bld1_dmpv_event(struct net_t *np, t_midat *idp)
{
 /* when changed written with 1 - never have value 0 and always 1 bit */
 /* will only be on changed list if cause during this time slot */
 *__fst_work_area = '1';
}

/*
 * FST => convert one real value
 */
static void fst_bld1_dmpv_real(struct net_t *np, t_midat *idp)
{
 memcpy(__fst_work_area, &(idp[np->nva_ofs]), sizeof(double));
}

/*
 * FST => convert a vector which is known to be <= WBITS
 */
static void fst_bld1_dmpv_vector_1w(struct net_t *np, t_midat *idp)
{
 int32 blen;
 word32 *ap;

 blen = np->nwid;
 ap = &(idp[np->nva_ofs]);

 fst_dmpv_sdispb_1w(ap[0], ap[1], blen);
}

/*
 * FST => convert a vector which is > WBITS
 */
static void fst_bld1_dmpv_vector_wide(struct net_t *np, t_midat *idp)
{
 int32 blen;
 word32 *ap, *bp;

 blen = np->nwid;
 ap = &(idp[np->nva_ofs]);
 bp = &(ap[wlen_(blen)]);

 fst_dmpv_sdispb(ap, bp, blen);
}

/*
 * FST => convert a vector which is has strength
 * just call ld routine and print as binary
 */
static void fst_bld1_dmpv_vector_svec(struct net_t *np, t_midat *idp)
{
 decl_idp_locals_;
 struct xstk_t *xsp;
 word32 *ap;

 set_save_idp_(idp); 
 push_xstk_(xsp, np->nwid);
 ap = &(idp[np->nva_ofs]);
 __ld_stval(xsp->ap, xsp->bp, (byte *) ap, np->nwid);
 fst_dmpv_sdispb(xsp->ap, xsp->bp, np->nwid);
 __pop_xstk();
 restore_idp_();
}

static const char fst_valtoch_tab[] = { '0', '1', 'z', 'x' };
/*
 * FST => convert one scalar value 
 */
static void fst_bld1_dmpv_scalar(struct net_t *np, t_midat *idp)
{
 byte sval;

 /* AIV 04/25/08 - has caculating the idp index inefficiently */
 sval = idp[np->nva_ofs] & 3;
 *__fst_work_area = fst_valtoch_tab[sval];
}

/*
 * FST => convert one real value array
 */
static void fst_bld1_dmpv_real_array(struct net_t *np, t_midat *idp)
{
 word32 *ap;
 int32 arri;

 ap = &(idp[np->nva_ofs]);
 arri = __dvars_array_ndx;
 /* find element arri that may be a vector */
 ap = &(ap[arri*2]);
  
 /* double is always 8 bytes stored using b part as extra 4 bytes */
 /* net width is 32 */
 memcpy(__fst_work_area, ap, sizeof(double));
}

/*
 * FST => convert an array vector element which is known to be <= WBITS 
 */
static void fst_bld1_dmpv_vector_1w_packed_array(struct net_t *np, t_midat *idp)
{
 int32 blen, arri;
 word32 av, bv, tmpw;
 word32 *ap;

 blen = np->nwid;
 ap = &(idp[np->nva_ofs]);
 arri = __dvars_array_ndx;
 /* find element arri that may be a vector */
 tmpw = get_packintowrd_(ap, arri, blen);
 av = tmpw & __masktab[blen];
 bv = (tmpw >> blen);

 fst_dmpv_sdispb_1w(av, bv, blen);
}

/*
 * FST => convert an array vector element which is known to be <= WBITS 
 */
static void fst_bld1_dmpv_vector_notpacked_1w_array(struct net_t *np, 
 t_midat *idp)
{
 int32 blen, wlen, arri;
 word32 *ap, *bp;

 blen = np->nwid;
 ap = &(idp[np->nva_ofs]);
 wlen = wlen_(blen);
 arri = __dvars_array_ndx;
 /* find element arri that may be a vector */
 ap = &(ap[arri*2*wlen]);
 bp = &(ap[wlen]);
 fst_dmpv_sdispb_1w(ap[0], bp[0], blen);
}

/*
 * FST => convert an array vector element which is known to be > WBITS 
 */
static void fst_bld1_dmpv_vector_wide_array(struct net_t *np, t_midat *idp)
{
 int32 blen, wlen, arri;
 word32 *ap, *bp;

 blen = np->nwid;
 ap = &(idp[np->nva_ofs]);
 wlen = wlen_(blen);
 /* find element arri that may be a vector */
 arri = __dvars_array_ndx;
 ap = &(ap[arri*2*wlen]);
 bp = &(ap[wlen]);

 fst_dmpv_sdispb(ap, bp, blen);
}


/*
 * FST => convert one array element scalar value 
 */
static void fst_bld1_dmpv_scalar_array(struct net_t *np, t_midat *idp)
{
 word32 sval;
 int32 arri, indi;
 word32 *rap;

 arri = __dvars_array_ndx;
 indi = 2*arri;
 rap = &(idp[np->nva_ofs]);
 sval = rap[get_wofs_(indi)] >> (get_bofs_(indi));
 *__fst_work_area = fst_valtoch_tab[sval & 3];
}

/*
 * 2-state wide vector
 */
static void fst_bld1_dmpv_vector_2state_wide_array(struct net_t *np, 
  t_midat *idp) 
{
 int32 blen, wlen, arri;
 word32 *ap;

 blen = np->nwid;
 ap = &(idp[np->nva_ofs]);
 wlen = wlen_(blen);
 arri = __dvars_array_ndx;
 ap = &(ap[arri*wlen]);
 fst_dmpv_sdispb_2state(ap, blen);
}

/*
 * 2-state 1w array element
 */
static void fst_bld1_dmpv_vector_2state_1w_array(struct net_t *np, t_midat *idp)
{
 int32 blen, wlen, arri;
 word32 *ap;

 blen = np->nwid;
 ap = &(idp[np->nva_ofs]);
 wlen = wlen_(blen);
 arri = __dvars_array_ndx;
 ap = &(ap[arri*wlen]);
 fst_dmpv_sdispb_1w_2state(ap[0], blen);
}

/*
 * 2-state wide array element
 */
static void fst_bld1_dmpv_vector_2state_wide(struct net_t *np, t_midat *idp)
{
 int32 blen;
 word32 *ap;

 blen = np->nwid;
 ap = &(idp[np->nva_ofs]);
 fst_dmpv_sdispb_2state(ap, blen);
}

/*
 * 2-state 1-word vector
 */
static void fst_bld1_dmpv_vector_2state_1w(struct net_t *np, t_midat *idp)
{
 int32 blen;
 word32 *ap;

 blen = np->nwid;
 ap = &(idp[np->nva_ofs]);
 fst_dmpv_sdispb_1w_2state(ap[0], blen);
}

/*
 * 2-state - convert one array element scalar value 
 * same as above with no 2x index
 */
static void fst_bld1_dmpv_scalar_2state_array(struct net_t *np, t_midat *idp)
{
 word32 sval;
 int32 arri;
 word32 *rap;

 arri = __dvars_array_ndx;
 rap = &(idp[np->nva_ofs]);
 sval = rap[get_wofs_(arri)] >> (get_bofs_(arri));
 *__fst_work_area = fst_valtoch_tab[sval & 1];
}

/*
 * FST THREADED DUMPING ROUTINES
 */

/*
 * FST => convert one event it changes is always 1
 */
static void fst_bld1_dmpv_event_thrd(struct net_t *np, t_midat *idp, 
 struct dmp_buf_t *dbp)
{
 /* AIV 04/24/12 - cannot override fst_work area nothing to do when packing */
 if (idp != NULL)
  {
   return;
  }
 /* when changed written with 1 - never have value 0 and always 1 bit */
 /* will only be on changed list if cause during this time slot */
 *__fst_work_area = '1';
}

/*
 * FST => convert one real value
 */
static void fst_bld1_dmpv_real_thrd(struct net_t *np, t_midat *idp,
 struct dmp_buf_t *dbp)
{
 if (idp != NULL)
  {
#ifdef __CVC32__
   dbp->dvsu.val = idp[np->nva_ofs];
   dbp->bval = idp[np->nva_ofs+1];
#else
   dbp->dvsu.val = idp[np->nva_ofs];
#endif
   return;
  }
#ifdef __CVC32__
 memcpy(__fst_work_area, &(dbp->dvsu.val), sizeof(word32));
 memcpy(&(__fst_work_area[4]), &(dbp->bval), sizeof(word32));
#else
 memcpy(__fst_work_area, &(dbp->dvsu.val), sizeof(double));
#endif
}

/*
 * FST => convert a vector which is known to be <= WBITS
 */
static void fst_bld1_dmpv_vector_1w_thrd(struct net_t *np, t_midat *idp,
 struct dmp_buf_t *dbp)
{
 if (idp != NULL)
  {
   dbp->dvsu.val = idp[np->nva_ofs];
   dbp->bval = idp[np->nva_ofs+1];
   return;
  }
 fst_dmpv_sdispb_1w(dbp->dvsu.val, dbp->bval, np->nwid);
}

/*
 * FST => convert a vector which is > WBITS
 */
static void fst_bld1_dmpv_vector_wide_thrd(struct net_t *np, t_midat *idp,
 struct dmp_buf_t *dbp)
{
 int32 blen, nbytes;
 word32 *ap, *bp;

 blen = np->nwid;
 nbytes = 2*wlen_(np->nwid)*WRDBYTES;
 if (idp != NULL)
  {
   dbp->dvsu.buf = (byte *) __my_malloc(nbytes);
   memcpy(dbp->dvsu.buf, &(idp[np->nva_ofs]), nbytes);
   return;
  }

 ap = (word32 *) dbp->dvsu.buf;
 bp = &(ap[wlen_(blen)]);
 fst_dmpv_sdispb(ap, bp, blen);
 __my_free(dbp->dvsu.buf, nbytes);
}

/*
 * FST => convert a vector which is has strength
 * just call ld routine and print as binary
 */
static void fst_bld1_dmpv_vector_svec_thrd(struct net_t *np, t_midat *idp,
 struct dmp_buf_t *dbp)
{
 int32 nwid;
 word32 *ap, *bp;
 
 nwid = np->nwid;
 if (idp != NULL)
  {
   dbp->dvsu.buf = (byte *) __my_malloc(nwid);
   memcpy(dbp->dvsu.buf, &(idp[np->nva_ofs]), nwid);
   return;
  }

 /* notice cannot use push_xstk here since it uses __xspi global */
 /* have malloc another known wide enough global __fst_work_svec */
 ap = (word32 *) __fst_work_svec;
 bp = &(ap[wlen_(nwid)]);
 __ld_stval(ap, bp, dbp->dvsu.buf, nwid);
 fst_dmpv_sdispb(ap, bp, nwid);
 __my_free(dbp->dvsu.buf, nwid);
}

/*
 * FST => convert one scalar value 
 */
static void fst_bld1_dmpv_scalar_thrd(struct net_t *np, t_midat *idp,
 struct dmp_buf_t *dbp)
{
 byte sval;

 /* AIV 04/25/08 - has caculating the idp index inefficiently */
 if (idp != NULL)
  {
   dbp->dvsu.val = idp[np->nva_ofs];
   return;
  }
 sval = (byte) dbp->dvsu.val & 3;
 *__fst_work_area = fst_valtoch_tab[sval];
}

/*
 * FST => convert one real value array
 */
static void fst_bld1_dmpv_real_array_thrd(struct net_t *np, t_midat *idp,
 struct dmp_buf_t *dbp)
{
 word32 *ap;
 int32 arri;

 if (idp != NULL)
  {
   ap = &(idp[np->nva_ofs]);
   arri = dbp->arr_flat_ndx;
   /* find element arri that may be a vector */
   ap = &(ap[arri*2]);
#ifdef __CVC32__
   dbp->dvsu.val = ap[0];
   dbp->bval = ap[1];
#else
   dbp->dvsu.val = ap[0];
#endif
   return;
  }
#ifdef __CVC32__
 memcpy(__fst_work_area, &(dbp->dvsu.val), sizeof(word32));
 memcpy(&(__fst_work_area[4]), &(dbp->bval), sizeof(word32));
#else
 memcpy(__fst_work_area, &(dbp->dvsu.val), sizeof(double));
#endif
}

/*
 * FST => convert an array vector element which is known to be <= WBITS 
 */
static void fst_bld1_dmpv_vector_1w_packed_array_thrd(struct net_t *np, 
 t_midat *idp, struct dmp_buf_t *dbp)
{
 int32 blen, arri;
 word32 av, bv, tmpw;
 word32 *ap;

 blen = np->nwid;
 if (idp != NULL)
  {
   arri = dbp->arr_flat_ndx;
   ap = &(idp[np->nva_ofs]);
   /* find element arri that may be a vector */
   tmpw = get_packintowrd_(ap, arri, blen);
   av = tmpw & __masktab[blen];
   bv = (tmpw >> blen);
   dbp->dvsu.val = av;
   dbp->bval = bv;
   return;
  }

 fst_dmpv_sdispb_1w(dbp->dvsu.val, dbp->bval, blen);
}

/*
 * FST => convert an array vector element which is known to be <= WBITS 
 */
static void fst_bld1_dmpv_vector_notpacked_1w_array_thrd(struct net_t *np, 
 t_midat *idp, struct dmp_buf_t *dbp)
{
 int32 blen, wlen, arri;
 word32 *ap, *bp;

 blen = np->nwid;
 if (idp != NULL)
  {
   arri = dbp->arr_flat_ndx;
   ap = &(idp[np->nva_ofs]);
   wlen = wlen_(blen);
   /* find element arri that may be a vector */
//AIV LOOKATME - is this wlen always 1 for <= WBITS???
   ap = &(ap[arri*2*wlen]);
   bp = &(ap[wlen]);
   dbp->dvsu.val = *ap;
   dbp->bval = *bp;
   return;
  }

 fst_dmpv_sdispb_1w(dbp->dvsu.val, dbp->bval, blen);
}

/*
 * FST => convert an array vector element which is known to be > WBITS 
 */
static void fst_bld1_dmpv_vector_wide_array_thrd(struct net_t *np, 
 t_midat *idp, struct dmp_buf_t *dbp)
{
 int32 blen, wlen, arri, nbytes;
 word32 *ap, *bp;

 blen = np->nwid;
 wlen = wlen_(blen);
 nbytes = 2*wlen*WRDBYTES;
 if (idp != NULL)
  {
   dbp->dvsu.buf = (byte *) __my_malloc(nbytes);
   arri = dbp->arr_flat_ndx;
   ap = &(idp[np->nva_ofs]);
   /* find element arri that may be a vector */
   ap = &(ap[arri*2*wlen]);
   memcpy(dbp->dvsu.buf, ap, nbytes); 
   return;
  }

 ap = (word32 *) dbp->dvsu.buf;
 bp = &(ap[wlen_(blen)]);
 fst_dmpv_sdispb(ap, bp, blen);
 __my_free(dbp->dvsu.buf, nbytes);
}


/*
 * FST => convert one array element scalar value 
 */
static void fst_bld1_dmpv_scalar_array_thrd(struct net_t *np, t_midat *idp,
 struct dmp_buf_t *dbp)
{
 word32 sval;
 int32 arri, indi;
 word32 *rap;

 if (idp != NULL)
  {
   arri = dbp->arr_flat_ndx;
   indi = 2*arri;
   rap = &(idp[np->nva_ofs]);
   sval = rap[get_wofs_(indi)] >> (get_bofs_(indi));
   dbp->dvsu.val = sval;
   return;
  }
 sval = dbp->dvsu.val;
 *__fst_work_area = fst_valtoch_tab[sval & 3];
}

/*
 * 2-state wide vector
 */
static void fst_bld1_dmpv_vector_2state_wide_array_thrd(struct net_t *np, 
  t_midat *idp, struct dmp_buf_t *dbp) 
{
 int32 blen, wlen, arri, nbytes;
 word32 *ap;

 blen = np->nwid;
 nbytes = wlen_(blen)*WRDBYTES;
 if (idp != NULL)
  {
   dbp->dvsu.buf = (byte *) __my_malloc(nbytes);
   arri = dbp->arr_flat_ndx;
   /* SJM 03-28-14 FIXME? why is ap here at all? */
   ap = &(idp[np->nva_ofs]);
   wlen = wlen_(blen);
   ap = &(ap[arri*wlen]);
   memcpy(dbp->dvsu.buf, &(idp[np->nva_ofs]), nbytes);
   return;
  }
 fst_dmpv_sdispb_2state((word32 *) dbp->dvsu.buf, blen);
 __my_free(dbp->dvsu.buf, nbytes);
}

/*
 * 2-state 1w array element
 */
static void fst_bld1_dmpv_vector_2state_1w_array_thrd(struct net_t *np, 
 t_midat *idp, struct dmp_buf_t *dbp)
{
 int32 blen, wlen, arri;
 word32 *ap;

 blen = np->nwid;
 if (idp != NULL)
  {
   arri = dbp->arr_flat_ndx;
   ap = &(idp[np->nva_ofs]);
   wlen = wlen_(blen);
   ap = &(ap[arri*wlen]);
   dbp->dvsu.val = *ap;
   return;
  }
 fst_dmpv_sdispb_1w_2state(dbp->dvsu.val, blen);
}

/*
 * 2-state wide vector element
 */
static void fst_bld1_dmpv_vector_2state_wide_thrd(struct net_t *np, 
 t_midat *idp, struct dmp_buf_t *dbp)
{
 int32 nbytes;

 nbytes = wlen_(np->nwid)*WRDBYTES;
 if (idp != NULL)
  {
   dbp->dvsu.buf = (byte *) __my_malloc(nbytes);
   memcpy(dbp->dvsu.buf, &(idp[np->nva_ofs]), nbytes);
   return;
  }
 fst_dmpv_sdispb_2state((word32 *) dbp->dvsu.buf, np->nwid);
 __my_free(dbp->dvsu.buf, nbytes);
}

/*
 * 2-state 1-word vector
 */
static void fst_bld1_dmpv_vector_2state_1w_thrd(struct net_t *np, 
 t_midat *idp, struct dmp_buf_t *dbp)
{
 if (idp != NULL)
  {
   dbp->dvsu.val = idp[np->nva_ofs];
   return;
  }
 fst_dmpv_sdispb_1w_2state(dbp->dvsu.val, np->nwid);
}

/*
 * 2-state - convert one array element scalar value 
 * same as above with no 2x index
 */
static void fst_bld1_dmpv_scalar_2state_array_thrd(struct net_t *np, 
 t_midat *idp, struct dmp_buf_t *dbp)
{
 word32 sval;
 int32 arri;
 word32 *rap;

 if (idp != NULL)
  {
   arri = dbp->arr_flat_ndx;
   rap = &(idp[np->nva_ofs]);
   sval = rap[get_wofs_(arri)] >> (get_bofs_(arri));
   dbp->dvsu.val = sval;
   return;
  }
 sval = dbp->dvsu.val;
 *__fst_work_area = fst_valtoch_tab[sval & 1];
}

/*
 * set up dumpvars for all instances of all variables of all modules
 * called at end of time slot, $dumpvars called in
 */
static void setup_all_dvars(void)
{
 int32 ni, ndx;
 struct net_t *np;
 struct mod_t *mdp;
 struct task_t *tskp; 

 /* each module */
 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  { 
   /* add to each variable */
   if (mdp->mnnum != 0)
    {
     for (ni = 0, np = &(mdp->mnets[0]); ni < mdp->mnnum; ni++, np++)
      {
       if (np->n_isarr)
        {
         if (can_dump_entire_array(np))
          {
           for (ndx = 0; ndx < np->arr_num_els; ndx++)
            {
             turnon_1net_dmpv(np, NULL, NULL, mdp, TRUE, ndx);
            }
          }
        }
       else
        {
         turnon_1net_dmpv(np, NULL, NULL, mdp, FALSE, -1);
        }
      }
    }
   for (tskp = mdp->mtasks; tskp != NULL; tskp = tskp->tsknxt) 
    {

     if (tskp->trnum != 0) 
      {
       for (ni = 0, np = &(tskp->tsk_regs[0]); ni < tskp->trnum; ni++, np++)
        {
         /* AIV 01/26/11 - if automatic array do not dump value */
         if (np->n_is_auto_var) continue;
         if (np->n_isarr)
          {
           if (can_dump_entire_array(np))
            {
             for (ndx = 0; ndx < np->arr_num_els; ndx++)
              {
               turnon_1net_dmpv(np, NULL, tskp, mdp, TRUE, ndx);
              }
            }
          }
         else 
          {
           turnon_1net_dmpv(np, NULL, tskp, mdp, FALSE, -1);
          }
        }
      }
    }
  }
}

     
//AIV  ARRAY;
static int32 can_dump_entire_array(struct net_t *np)
{
 /* AIV 01/24/11 - if original wire array do not dump */
 /* individual elements - this are converted to vectors */
 if (np->ntyp < NONWIRE_ST) return(FALSE);
 return(__dump_arrays && !__dump_array_cells);
}

/*
 * setup the dumpvar delays controls for 1 master dumpvars arg record
 *
 * separate routine writes the headers 
 * know if dump entire design will not get here
 */
static void setup_1argdvars(struct mdvmast_t *mdvp)
{
 struct net_t *np;
 struct mod_t *mdp;
 struct itree_t *itp;

 /* case 1 simple variable */
 itp = (struct itree_t *) mdvp->mdv_itprt_idp[MD_ITP];
 if ((np = mdvp->mdv_np) != NULL)
  {
   /* think flatinum not needed here since 1 itree loc. place */

   mdp = itp->itip->imsym->el.emdp;
   turnon_1net_dmpv(np, itp, mdvp->mdv_tskp, mdp, np->n_isarr, 
     mdvp->mdv_flat_ndx);
  }
 else
  {
   /* case 2 subtree */
   /* descend number of levels - 0 is all, 1 is just current */
   setup_1subtree_allvars(itp, mdvp->mdv_levels);
  }
}

/*
 * set all varaibles in an instance and under for dumping
 */
static void setup_1subtree_allvars(struct itree_t *itp, int32 level)
{
 int32 ii;
 struct mod_t *mdp; 
 struct itree_t *down_itp;

 /* must always try to do current */
 mdp = itp->itip->imsym->el.emdp;
 /* notice cannot stop if one mod dv setup since level may have been less */
 /* than current level (i.e. this ones descends more) */ 
 setup_1installvars(mdp, itp);
 mdp->mod_hasdvars = TRUE;

 if (level == 1) return; 
 for (ii = 0; ii < mdp->minum; ii++)
  { 
   down_itp = &(itp->in_its[ii]);
   setup_1subtree_allvars(down_itp, (level != 0) ? level - 1 : 0);
  }
}

/*
 * set up dumpvars for all variables of module at one itree location 
 */
static void setup_1installvars(struct mod_t *mdp, struct itree_t *itp)
{
 int32 ni, ndx;
 struct net_t *np;
 struct task_t *tskp; 

 /* add to each variable */
 if (mdp->mnnum != 0)
  {
   for (ni = 0, np = &(mdp->mnets[0]); ni < mdp->mnnum; ni++, np++)
    {
     /* AIV 08/04/10 - this should have been an else call if not an array */
     if (np->n_isarr)
      {
       if (can_dump_entire_array(np))
        {
         for (ndx = 0; ndx < np->arr_num_els; ndx++)
          {
           turnon_1net_dmpv(np, itp, NULL, mdp, TRUE, ndx);
          }
        }
      }
     else turnon_1net_dmpv(np, itp, NULL, mdp, FALSE, -1);
    }
  }
 for (tskp = mdp->mtasks; tskp != NULL; tskp = tskp->tsknxt) 
  {
   if (tskp->trnum != 0)
    {
     for (ni = 0, np = &(tskp->tsk_regs[0]); ni < tskp->trnum; ni++, np++)
      {
       /* AIV 03/09/11 - didn't merge this in correctly from 4.xx */
       /* AIV 01/26/11 - if automatic array do not dump value */
       if (np->n_is_auto_var) continue;

       if (np->n_isarr)
        {
         if (can_dump_entire_array(np))
          {
           for (ndx = 0; ndx < np->arr_num_els; ndx++)
            {
             turnon_1net_dmpv(np, itp, tskp, mdp, TRUE, -1);
            }
          }
        }
       else turnon_1net_dmpv(np, itp, tskp, mdp, FALSE, -1);
      }
    } 
  }
}

/*
 * turn on dumpvars for one net - called only at end of time slot
 *
 * if already turned on for for other instance, just set bit
 * if itp nil, set all bits
 *
 * only get here if at least one net in mod
 */
static void turnon_1net_dmpv(struct net_t *np, struct itree_t *itp,
 struct task_t *tskp, struct mod_t *mdp, int32 repeat_ok, int32 arr_ndx)
{ 
 int32 ni, ii, jj; 
 int32 num_dvns, num_els;
 char s1[RECLEN];
 t_midat *idp;
 struct dvchgnets_t *dvchgp;
 size_t tsize;

 /* if is an array and flag is not set return */
 if (np->n_isarr)
  {
   /* AIV 01/24/11 - if original wire array do not dump */
   /* individual elements - this are converted to vectors */
   if (!__dump_arrays) return;
   if (np->ntyp < NONWIRE_ST) return;
  }
 /* AIV 10/07/10 - strings, etc are not dumped */
 if (!__is_net_dumped(np)) return;

 mdp->mod_hasdvars = TRUE;

 /* assign dump vars id numbers for every inst. even if only some used */
 /* LOOKATME - could eliminate bad (hard to read) codes, but for now no */
 /* reason to bother - also problem with continuous regions */
 /* would need to find good contiguous region */
 /* __next_dvnum = skip_bad_codes(np, __next_dvnum); */ 

 /* if this net already has some instance dumpvared do not set up codes */
 if (!np->n_hasdvars)
  {
   np->n_hasdvars = TRUE;
   /* if net has any dumpvars must always use change stores */
   /* but recording now unrelated to dumpvars */ 

   /* SJM 10/10/06 - for interpreter only - if dmpv in src legal to turn */
   /* the nchg nd chgstore bit on because needed for dumpvars and starts */
   /* using nchg processing from here on when know no dces */
   if (!np->nchg_nd_chgstore)
    {
     /* DBG remove -- */
     if (!np->dmpv_in_src) __misc_terr(__FILE__, __LINE__);
     /* AIV 03/19/07 - can now get here for pli code */
     if (__compiled_sim && !__pli_access_level) __misc_terr(__FILE__, __LINE__);
     /* -- */
     np->nchg_nd_chgstore = TRUE;
    }

   num_els = 1;
   if (np->n_isarr)
    {
     /* if array need to alloc an array to hold - hasdvars flag */
     num_els = np->arr_num_els;
     /* DBG remove -- 
     if (num_els < 0 || arr_ndx < 0) __misc_terr(__FILE__, __LINE__);
     ----- */
     if (np->n_arr_hasdvars == NULL)
      {
       tsize = sizeof(int32)*num_els;
       np->n_arr_hasdvars = (int32 *) __my_malloc(tsize);
       memset(np->n_arr_hasdvars, 0, tsize);
      }
     np->n_arr_hasdvars[arr_ndx] = TRUE;
     num_dvns = mdp->flatinum*num_els;
    }
   else num_dvns = mdp->flatinum;

   /* 07/02/00 - SJM - fill module net dvcod table for this net */
   /* FIXME - think size should be 8 for alignment */
   /* AIV 05/17/10 - each dump var struct is now fixed - it is never freed */
   np->dvns = (struct dvchgnets_t *) 
      __my_malloc(sizeof(struct dvchgnets_t)*num_dvns);
   ni = np - mdp->mnets;
   for (ii = 0; ii < mdp->flatinum; ii++)
    {
     idp = mdp->moditps[ii]->it_idp;

     /* need to create one for each array element as well */
     for (jj = 0; jj < num_els; jj++)
      {
       dvchgp = &(np->dvns[(ii*num_els)+jj]);
       dvchgp->dvchg_np = np;
       dvchgp->on_list = FALSE;
       dvchgp->dvchg_idp = idp;
       dvchgp->dvchgnxt = NULL;
       dvchgp->dv_flat_ndx = jj;
       /* if FST will later set idcode */
       /* AIV 07/20/10 - no need for the mdp->mndvcodatb - has bee removed */
       if (__is_fst)
        {
         dvchgp->idu.idcode = 0;
        }
       else
        {
         /* VCD set dvcodp - character id code and set print format func */
         dvchgp->idu.dvcodp = __pv_stralloc(__to_dvcode(s1, __next_dvnum + jj));
         set_dmpv_bld_func(np);
        }
      }
     __next_dvnum += num_els;
    }
   /* RELEASE remove ---
   if (__debug_flg)
    {
    __dbg_msg("$$$ setting dvnum base %d for net %s (%d) in %s\n",
     __next_dvnum, np->nsym->synam, ni, mdp->msym->synam); 
    }
   --- */
  }
 else if (np->n_isarr)
  {
   np->n_arr_hasdvars[arr_ndx] = TRUE;
  }

 /* set bits in nets nchg action tab for this dumpvared net and maybe inst */
 if (itp == NULL)
  {
   for (ii = 0; ii < mdp->flatinum; ii++)
    {
     idp = mdp->moditps[ii]->it_idp;
     /* LOOKATME - here just turn on fact that dumpvared */
     /* otherwide would start too early - before next time step */
     /* i.e. mark not changed but set master dmpv copied to now flag */ 
     idp[np->nchgaction_ofs] |=
      (NCHG_DMPVARED | NCHG_DMPVARNOW | NCHG_DMPVNOTCHGED);
    }
   return;
  }
 idp = itp->it_idp;
 if (!repeat_ok && ((idp[np->nchgaction_ofs] & NCHG_DMPVARED) != 0))
  {
   __sgfinform(435, "variable %s in instance %s repeated in $dumpvars list",
    np->nsym->synam, __msg_blditree(__xs, itp, tskp));
  }
 idp[np->nchgaction_ofs]
  |= (NCHG_DMPVARED | NCHG_DMPVARNOW | NCHG_DMPVNOTCHGED);
}

/*
 * convert a number to a special character base 93 char number
 * this should be moved to v_cnv
 * notice requires ascii
 * LOOKATME - code ! is possible - is it legal?
 */
extern char *__to_dvcode(char *s, int32 vnum)
{
// AJB: this is now the same scheme used by VCS/NC/nWave
// SJM 07-07-14 LOOKATME - not using base 96 formula other simulators are
// using because too many regression tests fail - fix something
/* =====
char *pnt = s;
vnum++;
while (vnum)
        {
        vnum--;   
        *(pnt++) = (char)('!' + vnum % 94);
        vnum = vnum / 94;
        }
*pnt = 0;
==== */

 s[4] = '\0';
 s[3] = '!' + vnum % 93;
 if (vnum < 93) return(&(s[3]));
 vnum /= 93;
 s[2] = '!' + vnum % 93;
 if (vnum < 93) return(&(s[2]));
 vnum /= 93;
 s[1] = '!' + vnum % 93;
 if (vnum < 93) return(&(s[1]));
 vnum /= 93;
 s[0] = '!' + vnum;

 return(s);
}

/*
 * routine which skip number that are illegal codes
 * for now # (must be illegal) plus one digit and one letter x, z, X, Z 
 */
/* --
static int32 skip_bad_codes(struct net_t *np, int32 nextcod)
{
 char *cp;
 int32 fr, to, bad;
 char s1[RECLEN];

 if (nextcod > 93) return(nextcod);

 -- notice this list must be in numerical order --
 strcpy(s1, "#0123456789XZxz");
 fr = nextcod;
 to = nextcod + np->nwid - 1; 

 for (cp = s1; *cp != '\0'; cp++) 
  {
   bad = *cp - '!';
   if (fr <= bad && bad <= to)
    {
     if (isdigit(*cp)) nextcod = '9' - '!' + 1;
     else nextcod = bad + 1;
     fr = nextcod;
     to = nextcod + np->nwid - 1;
    }
  }
 return(nextcod);
}
--- */

/*
 * ROUTINES TO WRITE THE DUMPVAR HEADER REFERENCE INFO
 */

/*
 * write the header for 1 master dumpvars arg record
 * done at end of setup time slot 
 */
static void wr_1argdvhdr(struct mdvmast_t *mdvp)
{
 int32 ii, num_els;
 struct itree_t *itp, *itp2, *mdv_itp;
 struct mod_t *mdp;
 struct task_t *tskp;
 struct net_t *np;
 char *dvcodp;
 struct dvchgnets_t *dvchgp;

 /* case 0: all of design */
 if (mdvp->mdv_itprt_idp == NULL)
  {
   for (ii = 0; ii < __numtopm; ii++)
    {
     itp = __it_roots[ii];
     sprintf(__xs2, "$scope module %s $end\n", itp->itip->isym->synam); 
     __adds(__xs2);
     dv_wr(FALSE);

     wr_1subtree_allvars(itp, 0);
     sprintf(__xs2, "$upscope $end\n");
     __adds(__xs2);
     dv_wr(FALSE);
    }
   return;
  }

 /* case 1 simple variable */
 mdv_itp = (struct itree_t *) mdvp->mdv_itprt_idp[MD_ITP];
 if ((np = mdvp->mdv_np) != NULL)
  {
   /* AIV 07/14/10 - now allowing array elements */
   /* no need to check for array 1 wire form - illegal if array */
   wr_fromtop_iscopeto(mdv_itp);
   itp2 = mdv_itp;
   mdp = itp2->itip->imsym->el.emdp;
   if ((tskp = mdvp->mdv_tskp) != NULL)
    {
     wr_tskscopeto(tskp->tsksymtab);
     /* 07/02/00 - SJM - find right dvcod table code */
     dvchgp = &(np->dvns[itp2->itinum]);
     dvcodp = dvchgp->idu.dvcodp;
    }  
   else  
    {
     /* 07/02/00 - SJM - find right dvcod table code */
     dvchgp = &(np->dvns[itp2->itinum]);
     dvcodp = dvchgp->idu.dvcodp;
    }
   if (np->n_isarr)
    {
     num_els = np->arr_num_els;
     dvchgp = &(np->dvns[(itp2->itinum*num_els)+mdvp->mdv_flat_ndx]);
     dvcodp = dvchgp->idu.dvcodp;
     wr_1vectored_dvdef(np, dvcodp, itp2->it_idp, mdvp->mdv_flat_ndx, 
      mdvp->mdv_mda_indices);
    }
   else
    {
     wr_1vectored_dvdef(np, dvcodp, itp2->it_idp, -1, NULL);
    }
   if (tskp != NULL) wr_tskscopeback(mdvp->mdv_tskp->tsksymtab);
   wr_totop_iscopeback(mdv_itp);
  }
 else
  {
   /* case 2 inst. scope */
   /* this handles all its own scope movements */
   /* case inst. with some levels underneath */
   /* descend number of levels - 0 is all, 1 is just current */
   wr_fromtop_iscopeto(mdv_itp);
   wr_1subtree_allvars(mdv_itp, mdvp->mdv_levels);
   wr_totop_iscopeback(mdv_itp);
   /* AIV 01/28/05 - removed an extra upscope printing */ 
  }
}

/*
 * write the variables for all instances in and under 1 itree module loc.
 * descends level numbers 0 - all
 * when called expects scope to be moved upon return leaves scope at itp
 */
static void wr_1subtree_allvars(struct itree_t *itp, int32 level)
{
 int32 ii;
 struct mod_t *imdp;
 struct symtab_t *sytp;
 struct itree_t *down_itp;

 wr_1inst_dvhdrs(itp);
 imdp = itp->itip->imsym->el.emdp;
 /* when done scope left at instance same as called */
 if ((sytp = imdp->msymtab->sytofs) != NULL) wr_tasks_dvhdrs(itp, sytp);
 if (level != 1)
  { 
   for (ii = 0; ii < imdp->minum; ii++)
    { 
     down_itp = &(itp->in_its[ii]);
     sprintf(__xs2, "$scope module %s $end\n", down_itp->itip->isym->synam); 
     __adds(__xs2);
     dv_wr(FALSE);

     wr_1subtree_allvars(down_itp, (level != 0) ? level - 1 : 0);
     sprintf(__xs2, "$upscope $end\n");
     __adds(__xs2);
     dv_wr(FALSE);
    }
  }
}

/*
 * write the dv header variables in one module
 * scope set and does not descend or change scope
 */
static void wr_1inst_dvhdrs(struct itree_t *itp)
{
 int32 ni;
 struct net_t *np;
 struct mod_t *mdp;
 struct itree_t *itp2;
 char *dvcodp;
 struct dvchgnets_t *dvchgp;

 mdp = itp->itip->imsym->el.emdp;
 /* write all wires */
 if (mdp->mnnum == 0) return;
 for (ni = 0, np = &(mdp->mnets[0]); ni < mdp->mnnum; ni++, np++)
  {
   if (!np->n_hasdvars) continue;

   if (np->n_isarr)
    {
     if (can_dump_entire_array(np))
      {
       wr_1vectored_dvdef_array(np, itp);
      }
    }
   else
    {
     /* SJM - 07/02/00 - now dvcods pre-built as strings */
     dvchgp = &(np->dvns[itp->itinum]);
     dvcodp = dvchgp->idu.dvcodp;

     itp2 = itp;   
     wr_1vectored_dvdef(np, dvcodp, itp2->it_idp, -1, NULL);
    }
  } 
}
     
/*
 * create variable dvcodes for all elements of an array
 */
static void wr_1vectored_dvdef_array(struct net_t *np, struct itree_t *itp)
{
 int32 num_els;
 char *dvcodp;
 struct dvchgnets_t *dvchgp;
 int32 i, j, dwid, ri1, ri2, ri1_2, ri2_2, dwid_2, fndx;
 struct mda_t *mdap;
 int32 *ip;

 mdap = np->mda;
 num_els = np->arr_num_els;
 /* single dimension */
 if (mdap == NULL)
  {
   for (i = 0; i < num_els; i++)
    {
     dvchgp = &(np->dvns[(itp->itinum*num_els)+i]);
     dvcodp = dvchgp->idu.dvcodp;
     wr_1vectored_dvdef(np, dvcodp, itp->it_idp, i, NULL);
    }
  }
 else
  {
   /* 2-d array */
   /* DBG remove -- */
   if (mdap->dimension > 2) __misc_terr(__FILE__, __LINE__);
   /* ----- */

   __getarr_range_mda(np, &ri1, &ri2, &dwid, 0);
   __getarr_range_mda(np, &ri1_2, &ri2_2, &dwid_2, 1);
   fndx = 0;
   for (i = 0; i < dwid; i++)
    {
     for (j = 0; j < dwid_2; j++)
      {
       ip = (int32 *) __my_malloc(2*sizeof(int32));
       ip[0] = __unnormalize2_ndx(i, ri1, ri2);
       ip[1] = __unnormalize2_ndx(j, ri1_2, ri2_2);
       dvchgp = &(np->dvns[(itp->itinum*num_els)+fndx]);
       dvcodp = dvchgp->idu.dvcodp;
       wr_1vectored_dvdef(np, dvcodp, itp->it_idp, fndx, ip);
       __my_free(ip, 2*sizeof(int32));
       fndx++;
      }
    }
  }
}

/*
 * dump the header info for task and all contained tasks
 * handles scoping but assume all dmpvar dces already set up
 */
static void wr_tasks_dvhdrs(struct itree_t *itp, struct symtab_t *sytp)
{
 int32 ni;
 struct net_t *np;
 struct task_t *tskp;
 struct mod_t *mdp;
 char *dvcodp;
 struct dvchgnets_t *dvchgp;

 mdp = itp->itip->imsym->el.emdp;
 /* write all contained tasks/funcs/lbs - through symbol table list */
 for (; sytp != NULL; sytp = sytp->sytsib)
  {
   tskp = sytp->sypofsyt->el.etskp;
#ifdef __XPROP__
   /* if dummy xprop task must skip here */
   if (tskp == mdp->xprop_nb_taskp) return;
#endif
   /* notice must set up scope even if no variables */
   /* if (tskp->tsk_regs == NULL) continue; */
   if (tskp->is_inter_blk) continue;
   sprintf(__xs2, "$scope %s %s $end\n", to_dvtsktyp(__xs, tskp->tsktyp),
    tskp->tsksyp->synam);
   __adds(__xs2);
   dv_wr(FALSE);

   if (tskp->trnum != 0)
    {
     for (ni = 0, np = &(tskp->tsk_regs[0]); ni < tskp->trnum; ni++, np++)
      {
       /* AIV 01/26/11 - if automatic array do not dump value */
       if (np->n_is_auto_var) continue;

       if (np->n_isarr)
        {
         if (can_dump_entire_array(np))
          {
           wr_1vectored_dvdef_array(np, itp);
          }
        }
       else
        {
         dvchgp = &(np->dvns[itp->itinum]);
         dvcodp = dvchgp->idu.dvcodp;
         wr_1vectored_dvdef(np, dvcodp, itp->it_idp, -1, NULL);
        } 
      }
    }
   if (sytp->sytofs != NULL) wr_tasks_dvhdrs(itp, sytp->sytofs);
   sprintf(__xs2, "$upscope $end\n");
   __adds(__xs2);
   dv_wr(FALSE);
  } 
}

/*
 * build string name of task for $dumpvars - all blocks labeled
 */
static char *to_dvtsktyp(char *s, word32 tskt) 
{
 switch (tskt) {
  case Begin: strcpy(s, "begin"); break;
  case FORK: strcpy(s, "fork"); break;
  case FUNCTION: strcpy(s, "function"); break;
  case TASK: strcpy(s, "task"); break;
 }
 return(s);
}

/*
 * write commands to scope to an itree place
 */
static void wr_fromtop_iscopeto(struct itree_t *itp)
{
 int32 i;
 struct itree_t *witp;
 int32 frtoplevs;
 struct itree_t **itps;

 /* AIV 09/02/08 - there was completely wrong and must have been */
 /* since converting to idp - was only using the last scope name */
 /* method needs stack mechanism to print up scopes in reverse order */

 /* count number of scopes */
 frtoplevs = 0;
 for (witp = itp; witp != NULL; witp = witp->up_it)
  { 
   frtoplevs++;
  }
 /* alloc array only - needed to setup so extra pass ok */
 itps = (struct itree_t **) __my_malloc(frtoplevs*sizeof(struct itree_t *));
 i = 0;
 /* reverse the order to print */
 for (witp = itp; witp != NULL; witp = witp->up_it)
  { 
   i++;
   itps[frtoplevs-i] = witp;
  }
 /* print the scope */
 for (i = 0; i < frtoplevs; i++) 
  {
   witp = itps[i];
   sprintf(__xs2, "$scope module %s $end\n", witp->itip->isym->synam); 
   __adds(__xs2);
   dv_wr(FALSE);

  }
 /* free temp array */
 __my_free(itps, frtoplevs*sizeof(struct itree_t *));
}

static void wr_totop_iscopeback(struct itree_t *itp)
{
 struct itree_t *witp;

 for (witp = itp;;)
  {
   sprintf(__xs2, "$upscope $end\n");
   __adds(__xs2);
   dv_wr(FALSE);

   if ((witp = witp->up_it) == NULL) break;  
  }
}

/*
 * write the scope into the task/lb/func - must pass tasks symbol
 */
static void wr_tskscopeto(struct symtab_t *sytp)
{
 struct task_t *tskp;

 if (sytp->sytpar != NULL && sytp->sytpar->sypofsyt->sytyp != SYM_M)
  wr_tskscopeto(sytp->sytpar);
 tskp = sytp->sypofsyt->el.etskp;
 sprintf(__xs2, "$scope %s %s $end\n", to_dvtsktyp(__xs, tskp->tsktyp),
  tskp->tsksyp->synam);
 __adds(__xs2);
 dv_wr(FALSE);
}

static void wr_tskscopeback(struct symtab_t *sytp)
{
 struct symtab_t *wsytp;

 for (wsytp = sytp->sytpar;;)
  {
   sprintf(__xs2, "$upscope $end\n");
   __adds(__xs2);
   dv_wr(FALSE);

   /* keep going until back to containing module scope */
   if (wsytp->sypofsyt->sytyp == SYM_M) break;
  }
}

/*
 * write dv define for 1 scalar or vectored wire 
 * never call for array
 */
static void wr_1vectored_dvdef(struct net_t *np, char *dvcod, t_midat *idp,
 int32 arr_ndx, int32 *mda_indices)
{
 int32 r1, r2, i, ri1, ri2, ndx;
 char s1[15];
 char s2[RECLEN];
 char arr_name[RECLEN];
 struct mda_t *mdap;

 if ((idp[np->nchgaction_ofs] & NCHG_DMPVARED) == 0) return;

 if (arr_ndx != -1)
  {
   /* DBG remove -- */
   if (!np->n_isarr) __misc_terr(__FILE__, __LINE__); 
   /* --- */
   /* check it this is a md array and build name */ 
   if ((mdap = np->mda) != NULL)
    {
     /* DBG remove -- */
     if (mda_indices == NULL) __misc_terr(__FILE__, __LINE__); 
     /* --- */
     sprintf(arr_name, "%s[%d]", np->nsym->synam, mda_indices[0]);
     for (i = 1; i < mdap->dimension; i++)
      {
       sprintf(s2, "[%d]", mda_indices[i]);
       strcat(arr_name, s2);
      }
    }
   else 
    {
     /* single dim array */
     ri1 = np->nu.rngarr->ai1;
     ri2 = np->nu.rngarr->ai2;
     ndx = __unnormalize2_ndx(arr_ndx, ri1, ri2);
     sprintf(arr_name, "%s[%d]", np->nsym->synam, ndx);
    }

   __getwir_range(np, &r1, &r2);
   sprintf(__xs2, "$var %s ", __to_wtnam2(s1, np->ntyp)); 
   __adds(__xs2);
   dv_wr(FALSE);

   /* AIV 09/15/10 - reals have no range */
   if (np->ntyp == N_REAL)
    {
     sprintf(__xs2, "%7d %-4s %s $end\n", 64, dvcod, arr_name);
    }
   else
    {
     sprintf(__xs2, "%7d %-4s %s [%d:%d] $end\n", np->nwid, dvcod,
      arr_name, r1, r2);
    }
   __adds(__xs2);
   dv_wr(FALSE);
   return;
  }

 if (np->n_isavec || np->ntyp == N_REAL)
  {
   __getwir_range(np, &r1, &r2);
   /* this must be wire name */ 
   sprintf(__xs2, "$var %s ", __to_wtnam2(s1, np->ntyp)); 
   __adds(__xs2);
   dv_wr(FALSE);

   /* SJM 06/18/01 - no range for dumpvar of reals and width 64 */
   if (np->ntyp == N_REAL)
    {
     sprintf(__xs2, "     64 %-4s %s $end\n", dvcod, np->nsym->synam);
    }
   else
    {
     /* SJM 09/13/99 - range but be MSB to LSB - was internal h:0 */
     sprintf(__xs2, "%7d %-4s %s [%d:%d] $end\n", np->nwid, dvcod,
      np->nsym->synam, r1, r2);
    }
   __adds(__xs2);
   dv_wr(FALSE);
  }
 else
  {
   sprintf(__xs2, "$var %s ", __to_wtnam2(s1, np->ntyp)); 
   __adds(__xs2);
   dv_wr(FALSE);
   sprintf(__xs2, "      1 %-4s %s $end\n", dvcod, np->nsym->synam);
   __adds(__xs2);
   dv_wr(FALSE);
  }
}

/* 07/02/00 - now only one dvcod for each net - never scalared */

/*
 * ROUTINES TO TURN ON/OFF DUMPVARS RECORDING
 */

/*
 * turn off all dumpvars - uses being dumpvared template
 */
extern void __turnoff_all_dumpvars(void)
{
 int32 ii, ni;
 struct net_t *np;
 struct task_t *tskp;
 struct mod_t *mdp;
 t_midat *idp;

 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   if (!mdp->mod_hasdvars) continue;

   for (ni = 0, np = &(mdp->mnets[0]); ni < mdp->mnnum; ni++, np++)
    {
     if (!np->n_hasdvars) continue;

     for (ii = 0; ii < mdp->flatinum; ii++)
      {
       idp = mdp->moditps[ii]->it_idp;
       /* if not dumpvared nothing to do */
       if ((idp[np->nchgaction_ofs] & NCHG_DMPVARED) == 0) continue;

       /* dumpv now off and not changed on (even if changed in slot) */
       idp[np->nchgaction_ofs] &= ~NCHG_DMPVARNOW;
       idp[np->nchgaction_ofs] |= NCHG_DMPVNOTCHGED;
      }
    }
   for (tskp = mdp->mtasks; tskp != NULL; tskp = tskp->tsknxt)
    {
     for (ni = 0, np = &(tskp->tsk_regs[0]); ni < tskp->trnum; ni++, np++)
      {
       if (!np->n_hasdvars) continue;

       for (ii = 0; ii < mdp->flatinum; ii++)
        {
         idp = mdp->moditps[ii]->it_idp;
         if ((idp[np->nchgaction_ofs] & NCHG_DMPVARED) == 0) continue;

         /* dumpv now off and not changed on (even if changed in slot) */
         idp[np->nchgaction_ofs] &= ~NCHG_DMPVARNOW;
         idp[np->nchgaction_ofs] |= NCHG_DMPVNOTCHGED;
        }
      }
    }
  }
}

/*
 * turn on all dumpvars (from previous turn-off) 
 */
extern void __turnon_all_dumpvars(void)
{
 int32 ii, ni;
 struct net_t *np;
 struct task_t *tskp;
 struct mod_t *mdp;
 t_midat *idp;

 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   if (!mdp->mod_hasdvars) continue;

   for (ni = 0, np = &(mdp->mnets[0]); ni < mdp->mnnum; ni++, np++)
    {
     if (!np->n_hasdvars) continue;

     for (ii = 0; ii < mdp->flatinum; ii++)
      {
       idp = mdp->moditps[ii]->it_idp;
       /* if not dumpvared nothing to do */
       if ((idp[np->nchgaction_ofs] & NCHG_DMPVARED) == 0) continue;

       /* dumpv now off and not changed on (even if changed in slot) */
       idp[np->nchgaction_ofs] |= NCHG_DMPVARNOW;
       /* not changed bit already on */
      }
    }
   for (tskp = mdp->mtasks; tskp != NULL; tskp = tskp->tsknxt)
    {
     for (ni = 0, np = &(tskp->tsk_regs[0]); ni < tskp->trnum; ni++, np++)
      {
       if (!np->n_hasdvars) continue;

       for (ii = 0; ii < mdp->flatinum; ii++)
        {
         idp = mdp->moditps[ii]->it_idp;
         if ((idp[np->nchgaction_ofs] & NCHG_DMPVARED) == 0) continue;

         /* dumpv now off and not changed on (even if changed in slot) */
         idp[np->nchgaction_ofs] |= NCHG_DMPVARNOW;
         /* not changed bit already on */
        }
      }
    }
  }
}
/*
 * ROUTINES TO ACTUALLY DUMP VARIABLES
 */

/*
 * dump all variables for baseline - for start ($dumpvars), dumpon,
 * dumpoff (need x's) and dumpall - keywrds determines which
 * set flags
 */
extern void __do_dmpvars_baseline(char *keyws)
{
 __cur_sofs = 0;
 if (__dv_outlinpos != 0)
  {
   addch_('\n');
   __exprline[__cur_sofs] = '\0'; 
   dv_wr(FALSE);
  }
 if (!__dv_time_emitted)
  {
   sprintf(__xs2, "#%s\n", to_dvtimstr(__xs, __simtime));
   __adds(__xs2);
   __dv_time_emitted = TRUE;
   dv_wr(FALSE);
  }
 
 __adds(keyws);
 dv_wr(TRUE);
 __dv_outlinpos = 0;
 if (strcmp(keyws, "$dumpoff") == 0) __dv_func = DMPV_DUMPX;
 else __dv_func = DMPV_DMPALL; 
 dump_allvars_vals();
 if (__dv_outlinpos != 0) addch_('\n');
 __adds("$end\n");
 dv_wr(FALSE);
 __dv_outlinpos = 0;
}

/*
 * dump all variables for baseline - fst version
 */
extern void __fst_do_vars_baseline(char *keyws, int32 is_dumpoff)
{
 int32 ni;
 struct mod_t *mdp;
 struct net_t *np;
 struct task_t *tskp;

 /* fst version of dump_allvars_vals */
 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   if (!mdp->mod_hasdvars) continue; 
   if (mdp->mnnum != 0)
    {
     for (ni = 0, np = &(mdp->mnets[0]); ni < mdp->mnnum; ni++, np++)
      {
       /* if using default only dump vals for col. to col will never */
       /* have dumpvars so do not need special checking */
       /* if dump all even col. from, this is normal code */ 
       if (np->n_hasdvars)
        {
         if (np->n_isarr) fst_insts_ofwire_array(mdp, np, is_dumpoff);
         else fst_insts_ofwire(mdp, np, is_dumpoff);
        }
      }
    }
   for (tskp = mdp->mtasks; tskp != NULL; tskp = tskp->tsknxt)
    {
     if (tskp->trnum == 0) continue;
     if (tskp->is_inter_blk) continue;
     for (ni = 0, np = &(tskp->tsk_regs[0]); ni < tskp->trnum; ni++, np++)
      { 
       /* AIV LOOKATME - think this should be setting task scope */
       if (np->n_hasdvars) 
        {
         if (np->n_isarr) fst_insts_ofwire_array(mdp, np, is_dumpoff);
         else fst_insts_ofwire(mdp, np, is_dumpoff);
        }
      }
    }
  }
}

/*
 * fst version of insts_ofwire
 * for a given net dump all instances of it - do not check change bit
 * this is for base lines and any change info left unchanged
 */
static void fst_insts_ofwire(struct mod_t *mdp, struct net_t *np, 
 int32 is_dumpoff)
{
 int32 ii; 
 fstHandle idcode; 
 struct itree_t *itp;
 double d;
 struct dvchgnets_t *dvchgp;
 t_midat *idp;
 char sval;
 void (*dfp)(struct net_t *, t_midat *);
 void (*dfpp)(struct net_t *, t_midat *, struct dmp_buf_t *);
 struct dmp_buf_t *dbp;

 fst_set_time();
 /* dump all dumpvared instances */
 /* LOOKATME - this is only step much slower in new approach - problem? */ 
 for (ii = 0; ii < mdp->flatinum; ii++) 
  {
   itp = mdp->moditps[ii];
   idp = itp->it_idp;
   if ((idp[np->nchgaction_ofs] & NCHG_DMPVARED) == 0) continue;

   /* AIV 07/19/10 - should just use ii here */
   dvchgp = &(np->dvns[ii]);
   idcode = dvchgp->idu.idcode;

   /* set value to x */
   if (is_dumpoff)
    {
     /* real x is 0.0 */
     if (np->ntyp == N_REAL) 
      {
       d = 0.0;
       fstWriterEmitValueChange(__fst_ctx, idcode, (void *) &d);
       continue;
      }
     if (np->ntyp == N_EVENT) 
      {
       /* event x is 1 */
       sval =  '1';
      }
     else sval =  'x';
     fstWriterEmitValueChange(__fst_ctx, idcode, (void *) &sval);
    }
   else
    {

     /* if new parallel code do this is 2 step tmp setting */
     /* AIV 04/25/12 - now only paralel buffer if parallel mode 2 */
     if (__fst_parallel2)
      {
       /* just use 0 one at time */
       dbp = &(__dump_buffer[0]);
       dbp->np = np;
       dbp->idcode = idcode;
       dbp->arr_flat_ndx = dvchgp->dv_flat_ndx; 
       /* first uses tmp storag then set */
       dfpp = np->dmpv_funcu.parallel;
       (dfpp)(np, idp, dbp);
       (dfpp)(np, NULL, dbp);
      }
     else 
      {
       dfp = np->dmpv_funcu.single;
       __dvars_array_ndx = dvchgp->dv_flat_ndx; 
       (dfp)(np, idp);
      }
     fstWriterEmitValueChange(__fst_ctx, idcode, (void *) __fst_work_area);
    }
  }
} 

/*
 * FST - dump all instances of the array 
 */
static void fst_insts_ofwire_array(struct mod_t *mdp, struct net_t *np, 
 int32 is_dumpoff)
{
 int32 ii, jj, num_els; 
 struct itree_t *itp;
 fstHandle idcode; 
 t_midat *idp;
 double d;
 char sval;
 struct dvchgnets_t *dvchgp;
 void (*dfp)(struct net_t *, t_midat *);
 void (*dfpp)(struct net_t *, t_midat *, struct dmp_buf_t *);
 struct dmp_buf_t *dbp;

 /* dump all dumpvared instances */
 /* LOOKATME - this is only step much slower in new approach - problem? */ 
 for (ii = 0; ii < mdp->flatinum; ii++) 
  {
   itp = mdp->moditps[ii];
   idp = itp->it_idp;
   if ((idp[np->nchgaction_ofs] & NCHG_DMPVARED) == 0) continue;


   num_els = np->arr_num_els;
   /* these are flattened index values - so work for 2-d as well */
   for (jj = 0; jj < num_els; jj++) 
    {
     if (!np->n_arr_hasdvars[jj]) continue;
     dvchgp = &(np->dvns[(ii*num_els)+jj]);
     idcode = dvchgp->idu.idcode;

     /* set value to x */
     if (is_dumpoff)
      {
       /* real x is 0.0 */
       if (np->ntyp == N_REAL) 
        {
         d = 0.0;
         fstWriterEmitValueChange(__fst_ctx, idcode, (void *) &d);
         continue;
        }
       if (np->ntyp == N_EVENT) 
        {
         /* event x is 1 */
         sval =  '1';
        }
       else sval =  'x';
       fstWriterEmitValueChange(__fst_ctx, idcode, (void *) &sval);
      }
     else
      {
       /* AIV 04/25/12 - now only paralel buffer if parallel mode 2 */
       if (__fst_parallel2)
        {
         /* just use 0 one at time */
         dbp = &(__dump_buffer[0]);
         dbp->np = np;
         dbp->idcode = idcode;
         dbp->arr_flat_ndx = dvchgp->dv_flat_ndx; 
         /* first uses tmp storag then set */
         dfpp = np->dmpv_funcu.parallel;
         (dfpp)(np, idp, dbp);
         (dfpp)(np, NULL, dbp);
        }
       else
        {
         dfp = np->dmpv_funcu.single;
         __dvars_array_ndx = dvchgp->dv_flat_ndx; 
         (dfp)(np, idp);
         fstWriterEmitValueChange(__fst_ctx, idcode, (void *) __fst_work_area);
        }
      }
    }
  }
} 

/*
 * dumpvars convert a 64 bit internal tick time to a decimal string
 *
 * AIV 02/15/09 - removed code to handle special OSX handling now works fine
 * SJM 11/21/03 - now all systems but OSX support word32 64 printf
 */
static char *to_dvtimstr(char *s, word64 t)
{
#ifdef __CVC32__
 sprintf(s, "%llu", t);
#else
 sprintf(s, "%lu", t);
#endif
 return(s);
}

/*
 * dump all variables for various types of check pointing
 * know when this called positioned at beginning of new line
 */
static void dump_allvars_vals(void)
{
 int32 ni;
 struct mod_t *mdp;
 struct net_t *np;
 struct task_t *tskp;

 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   if (!mdp->mod_hasdvars) continue; 
   if (mdp->mnnum != 0)
    {
     for (ni = 0, np = &(mdp->mnets[0]); ni < mdp->mnnum; ni++, np++)
      {
       /* if using default only dump vals for col. to col will never */
       /* have dumpvars so do not need special checking */
       /* if dump all even col. from, this is normal code */ 
       if (np->n_hasdvars)
        {
         if (np->n_isarr) dmp_insts_ofwire_array(mdp, np);
         else dmp_insts_ofwire(mdp, np);
        }
      }
    }
   for (tskp = mdp->mtasks; tskp != NULL; tskp = tskp->tsknxt)
    {
     if (tskp->trnum == 0) continue;
     if (tskp->is_inter_blk) continue;
     for (ni = 0, np = &(tskp->tsk_regs[0]); ni < tskp->trnum; ni++, np++)
      { 
       if (np->n_hasdvars)
        {
         if (np->n_isarr) dmp_insts_ofwire_array(mdp, np);
         else dmp_insts_ofwire(mdp, np);
        }
      }
    }
  }
}

/*
 * for a given net dump all instances of it - do not check change bit
 * this is for base lines and any change info left unchanged
 *
 * loop here could be unwound to make it faster
 * must never be called for arrays
 *
 * bld1 dvval uses global xs strings
 */
static void dmp_insts_ofwire(struct mod_t *mdp, struct net_t *np)
{
 int32 ii; 
 struct itree_t *itp;
 t_midat *idp;
 char *dvcodp;
 struct dvchgnets_t *dvchgp;
 void (*dfp)(struct net_t *, t_midat *);

 /* dump all dumpvared instances */
 /* LOOKATME - this is only step much slower in new approach - problem? */ 
 for (ii = 0; ii < mdp->flatinum; ii++) 
  {
   itp = mdp->moditps[ii];
   idp = itp->it_idp;
   if ((idp[np->nchgaction_ofs] & NCHG_DMPVARED) == 0) continue;

   /* 07/02/00 - SJM - find right dvcod table code */
   /* AIV 07/19/10 - should just use ii here */
   dvchgp = &(np->dvns[ii]);
   dvcodp = dvchgp->idu.dvcodp;

   /* here for strength vector pass 0th (first-low) bit of vector */
   if (__dv_func == DMPV_DUMPX) bld1_xdvval(np, dvcodp);
   else
    {
     __cur_sofs = 0;
     dfp = np->dmpv_funcu.single;
     __dvars_array_ndx = dvchgp->dv_flat_ndx; 
     (dfp)(np, idp);
     __adds(dvcodp);  
    }
   dv_wr(TRUE);
  }
} 

/*
 * array version fo dump all instances of array elements
 */
static void dmp_insts_ofwire_array(struct mod_t *mdp, struct net_t *np)
{
 int32 ii, jj, num_els; 
 struct itree_t *itp;
 t_midat *idp;
 char *dvcodp;
 struct dvchgnets_t *dvchgp;
 void (*dfp)(struct net_t *, t_midat *);

 /* dump all dumpvared instances */
 /* LOOKATME - this is only step much slower in new approach - problem? */ 
 for (ii = 0; ii < mdp->flatinum; ii++) 
  {
   itp = mdp->moditps[ii];
   idp = itp->it_idp;
   if ((idp[np->nchgaction_ofs] & NCHG_DMPVARED) == 0) continue;


   num_els = np->arr_num_els;
   /* these are flattened index values - so work for 2-d as well */
   for (jj = 0; jj < num_els; jj++) 
    {
     if (!np->n_arr_hasdvars[jj]) continue;
     dvchgp = &(np->dvns[(ii*num_els)+jj]);
     dvcodp = dvchgp->idu.dvcodp;

     /* here for strength vector pass 0th (first-low) bit of vector */
     if (__dv_func == DMPV_DUMPX) bld1_xdvval(np, dvcodp);
     else
      {
       __cur_sofs = 0;
       __dvars_array_ndx = jj; 
       dfp = np->dmpv_funcu.single;
       (dfp)(np, idp);
       __adds(dvcodp);  
      }
     dv_wr(TRUE);
    }
  }
} 

/*
 * do the dumpvars changes 
 * this routine requires at least one dv change entry
 */
extern void __do_dmpvars_chg()
{ 
 struct dvchgnets_t *dvchgnp;
 struct net_t *np;
 t_midat *idp;
 char *dvcodp;
 void (*dfp)(struct net_t *, t_midat *);

 if (__dv_outlinpos != 0)
  {
   addch_('\n'); 
   __exprline[__cur_sofs] = '\0'; 
   dv_wr(FALSE);
  }
 if (!__dv_time_emitted)
  {
   sprintf(__xs2, "#%s\n", to_dvtimstr(__xs, __simtime));
   __adds(__xs2);
   dv_wr(FALSE);
   __dv_time_emitted = TRUE;
   /* notice can only check for over limit when emitting new change time */
   if (__dv_dumplimit_size != 0)
    {
     if (__dv_file_size > __dv_dumplimit_size)
      {
       __dv_outlinpos = 0;
       sprintf(__xs2,
        "$comment - Note: $dumplimit %d limit exceeded at %s $end\n",
        __dv_dumplimit_size, __to_timstr(__xs, &__simtime));
       __adds(__xs2);
       dv_wr(FALSE);

       __dv_state = DVST_OVERLIMIT;
       __turnoff_all_dumpvars();

       __cv_msg(
        "  *** Dumping of variables stopped at %s because $dumplimit %d exceeded.\n",
        __to_timstr(__xs, &__simtime), __dv_dumplimit_size);

      }
    }
  }
 __dv_outlinpos = 0;
 __dv_func = DMPV_CHGONLY;

 for (dvchgnp = __dv_chgnethdr; dvchgnp != NULL; dvchgnp = dvchgnp->dvchgnxt)
  {
   /* do the dumpvars for one var instance */
   dvchgnp->on_list = FALSE;
   np = dvchgnp->dvchg_np;
   idp = dvchgnp->dvchg_idp;
   dvcodp = dvchgnp->idu.dvcodp;

   __cur_sofs = 0;
   __dvars_array_ndx = dvchgnp->dv_flat_ndx; 
   dfp = np->dmpv_funcu.single;
   (dfp)(np, idp);
   __adds(dvcodp);  

   dv_wr(TRUE);
   /* reset this inst. not changed flag - i.e. must be on (not changed) */
   /* for next time */ 
   idp[np->nchgaction_ofs] |= NCHG_DMPVNOTCHGED;
  }
 __dv_chgnethdr = NULL;
}

/*
 * record all fst time changes
 */
extern void __fst_do_vars_chg(void)
{ 
 struct dvchgnets_t *dvchgnp;
 struct net_t *np;
 t_midat *idp;
 int32 idcode;
 void (*dfp)(struct net_t *, t_midat *);

 __dv_outlinpos = 0;
 __dv_func = DMPV_CHGONLY;

 /* AIV 04/20/12 - if parallel mode will place in the buffer and return */
 /* AIV 04/25/12 - now only paralel buffer if parallel mode 2 */
 if (__fst_parallel2)
  {
   __fst_do_vars_chg_parallel();
   return;
  }

 fst_set_time();

 for (dvchgnp = __dv_chgnethdr; dvchgnp != NULL; dvchgnp = dvchgnp->dvchgnxt)
  {
   /* do the dumpvars for one var instance */
   dvchgnp->on_list = FALSE;
   np = dvchgnp->dvchg_np;
   idp = dvchgnp->dvchg_idp;

   __dvars_array_ndx = dvchgnp->dv_flat_ndx; 
   dfp = np->dmpv_funcu.single;
   (dfp)(np, idp);

   idcode = dvchgnp->idu.idcode;
   fstWriterEmitValueChange(__fst_ctx, idcode, (void *) __fst_work_area);

   /* for next time */ 
   idp[np->nchgaction_ofs] |= NCHG_DMPVNOTCHGED;
  }
 /* AIV 05/03/10 - this is known to never be NULL here at least one */
 /* change or this routine is never called */
 /* splice list on front of change free list all at once */
 /* if last nil, no changes */
 __dv_chgnethdr = NULL;
}

/*
 * parallel version of FST change dumping
 * places all end of time change events in a buffer which is converted and
 * written in another thread
 * AIV LOOKATME - this does not lock/block until the end of buffer is reached
 * at which point it will empty the buffer causing a stall, but the plus
 * side is this does not block simulation.  Think a ring buffer could be
 * better but call I tried the locking/sync was worse????
 */
extern void __fst_do_vars_chg_parallel(void)
{
 struct dvchgnets_t *dvchgnp;
 struct net_t *np;
 t_midat *idp;
 struct dmp_buf_t *dbp;
 void (*dfp)(struct net_t *, t_midat *, struct dmp_buf_t *);


 
 /* mark a change to time event in the buffer */
 dbp = &(__dump_buffer[__dump_next_ndx]);
 dbp->idcode = 0;
 dbp->np = NULL;
 dbp->arr_flat_ndx = -1;
#ifdef __CVC32__
 dbp->dvsu.mtime = (word32) __simtime;
 dbp->bval = (word32) (__simtime >> 32);
#else
 dbp->dvsu.mtime = __simtime;
#endif
   
 /* make sure has not reached end of buffer - if so wait to empty */
 __dump_next_ndx++;
 if (__dump_next_ndx == __dump_buffer_size) 
  {
   pthread_mutex_lock(&__dump_mutex);
   pthread_cond_wait(&__buffer_empty, &__dump_mutex);
   __dump_next_ndx = 0;
   __write_ndx = 0;
   pthread_mutex_unlock(&__dump_mutex);
  }
 
 for (dvchgnp = __dv_chgnethdr; dvchgnp != NULL; dvchgnp = dvchgnp->dvchgnxt)
  {
   /* do the dumpvars for one var instance */
   /* reset this inst. not changed flag - i.e. must be on (not changed) */
   dvchgnp->on_list = FALSE;

   /* get fixed buffer struct */
   dbp = &(__dump_buffer[__dump_next_ndx]);

   np = dvchgnp->dvchg_np;
   dbp->np = np;
   dbp->idcode = dvchgnp->idu.idcode;
   dfp = np->dmpv_funcu.parallel;
   idp = dvchgnp->dvchg_idp;
   /* this will fill buffer struct to type */
   (dfp)(np, idp, dbp);
   __dump_next_ndx++;
   
   /* make sure has not reached end of buffer - if so wait to empty */
   //AIV LOOKATME - think this can use a ring buffer would be better -no stall
   if (__dump_next_ndx == __dump_buffer_size) 
    {
     pthread_mutex_lock(&__dump_mutex);
     pthread_cond_wait(&__buffer_empty, &__dump_mutex);
     __dump_next_ndx = 0;
     __write_ndx = 0;
     pthread_mutex_unlock(&__dump_mutex);
    }

   /* for next time */ 
   idp[np->nchgaction_ofs] |= NCHG_DMPVNOTCHGED;
  }
 /* splice list on front of change free list all at once */
 /* if last nil, no changes */
 /* AIV 05/03/10 - this is known to never be NULL here at least one */
 /* change or this routine is never called */
 __dv_chgnethdr = NULL;
}

/*
 * thread which does actual calls to FST change value API calls
 */
static void *fst_writer_thread(void *pa)
{
 struct dmp_buf_t *dbp;
 int32 idcode;
 word64 mstime;
 struct net_t *np;
 void (*dfp)(struct net_t *, t_midat *, struct dmp_buf_t *);
#ifdef __CVC32__
 word32 lwordloc, hwordloc;
#endif

 while (1)
  {
   /* always cycle looking from-to values to write in the buffer */
   pthread_mutex_lock(&__dump_mutex);
   for (; __write_ndx < __dump_next_ndx; __write_ndx++)
    {
     dbp = &(__dump_buffer[__write_ndx]);

     idcode = dbp->idcode;
     /* DBG REMOVE
      if (mstime < last_time) __misc_terr(__FILE__, __LINE__);
     */
     /* if idcode is zero - this is a time change marker emit time change */
     if (idcode == 0)
      {
#ifdef __CVC32__
       lwordloc = dbp->dvsu.mtime;
       hwordloc = dbp->bval;
       mstime = ((word64) lwordloc) | (((word64) hwordloc) << 32);
       fstWriterEmitTimeChange(__fst_ctx, mstime);
#else
       mstime = dbp->dvsu.mtime;
       fstWriterEmitTimeChange(__fst_ctx, mstime);
#endif
      }
     else 
      {
       /* value change convert and call FST API change value */
       np = dbp->np;
       dfp = np->dmpv_funcu.parallel;
       (dfp)(np, NULL, dbp);
       fstWriterEmitValueChange(__fst_ctx, idcode, (void *) __fst_work_area);
      }
    }
   pthread_cond_signal(&__buffer_empty);
   pthread_mutex_unlock(&__dump_mutex);

   //AIV LOOKATME - could sync if stalled???
   //ffw_Sync(__fst_obj);
  }
 return(NULL);
}


/*
 * set the fst time
 */
static void fst_set_time(void)
{
 fstWriterEmitTimeChange(__fst_ctx, __simtime);
}

/*
 * close FST object file
 */
extern void __fst_close(void)
{
 /* if parallel dumping must wait until all vars are dumped to close file */
 if (__fst_parallel2)
  {
   pthread_mutex_lock(&__dump_mutex);
   /* if has pending elements must wait until done */
   if (__write_ndx != __dump_next_ndx) 
     pthread_cond_wait(&__buffer_empty, &__dump_mutex);
   pthread_mutex_unlock(&__dump_mutex);
 }
 fstWriterClose(__fst_ctx);
 __fst_ctx = NULL;
}

/*
 * special routine to emit time stamp at end of dumpvars file
 *
 * LOOKATME - does not write if over file size limit but maybe should 
 */
extern void __wr_dvtimstr(void)
{
 if (__dv_state != DVST_DUMPING) return;
 sprintf(__xs2, "#%s\n", to_dvtimstr(__xs, __simtime));
 __adds(__xs2);
 dv_wr(FALSE);
}

/* AIV 05/17/10 - table to go from one byte 1/0 to word64 for conversion */
/* on byte boundary - see table.c for making this table */
static const word64 byte_to_chars[256] = {
0x3030303030303030ULL, 
0x3130303030303030ULL, 0x3031303030303030ULL, 0x3131303030303030ULL, 
0x3030313030303030ULL, 0x3130313030303030ULL, 0x3031313030303030ULL, 
0x3131313030303030ULL, 0x3030303130303030ULL, 0x3130303130303030ULL, 
0x3031303130303030ULL, 0x3131303130303030ULL, 0x3030313130303030ULL, 
0x3130313130303030ULL, 0x3031313130303030ULL, 0x3131313130303030ULL, 
0x3030303031303030ULL, 0x3130303031303030ULL, 0x3031303031303030ULL, 
0x3131303031303030ULL, 0x3030313031303030ULL, 0x3130313031303030ULL, 
0x3031313031303030ULL, 0x3131313031303030ULL, 0x3030303131303030ULL, 
0x3130303131303030ULL, 0x3031303131303030ULL, 0x3131303131303030ULL, 
0x3030313131303030ULL, 0x3130313131303030ULL, 0x3031313131303030ULL, 
0x3131313131303030ULL, 0x3030303030313030ULL, 0x3130303030313030ULL, 
0x3031303030313030ULL, 0x3131303030313030ULL, 0x3030313030313030ULL, 
0x3130313030313030ULL, 0x3031313030313030ULL, 0x3131313030313030ULL, 
0x3030303130313030ULL, 0x3130303130313030ULL, 0x3031303130313030ULL, 
0x3131303130313030ULL, 0x3030313130313030ULL, 0x3130313130313030ULL, 
0x3031313130313030ULL, 0x3131313130313030ULL, 0x3030303031313030ULL, 
0x3130303031313030ULL, 0x3031303031313030ULL, 0x3131303031313030ULL, 
0x3030313031313030ULL, 0x3130313031313030ULL, 0x3031313031313030ULL, 
0x3131313031313030ULL, 0x3030303131313030ULL, 0x3130303131313030ULL, 
0x3031303131313030ULL, 0x3131303131313030ULL, 0x3030313131313030ULL, 
0x3130313131313030ULL, 0x3031313131313030ULL, 0x3131313131313030ULL, 
0x3030303030303130ULL, 0x3130303030303130ULL, 0x3031303030303130ULL, 
0x3131303030303130ULL, 0x3030313030303130ULL, 0x3130313030303130ULL, 
0x3031313030303130ULL, 0x3131313030303130ULL, 0x3030303130303130ULL, 
0x3130303130303130ULL, 0x3031303130303130ULL, 0x3131303130303130ULL, 
0x3030313130303130ULL, 0x3130313130303130ULL, 0x3031313130303130ULL, 
0x3131313130303130ULL, 0x3030303031303130ULL, 0x3130303031303130ULL, 
0x3031303031303130ULL, 0x3131303031303130ULL, 0x3030313031303130ULL, 
0x3130313031303130ULL, 0x3031313031303130ULL, 0x3131313031303130ULL, 
0x3030303131303130ULL, 0x3130303131303130ULL, 0x3031303131303130ULL, 
0x3131303131303130ULL, 0x3030313131303130ULL, 0x3130313131303130ULL, 
0x3031313131303130ULL, 0x3131313131303130ULL, 0x3030303030313130ULL, 
0x3130303030313130ULL, 0x3031303030313130ULL, 0x3131303030313130ULL, 
0x3030313030313130ULL, 0x3130313030313130ULL, 0x3031313030313130ULL, 
0x3131313030313130ULL, 0x3030303130313130ULL, 0x3130303130313130ULL, 
0x3031303130313130ULL, 0x3131303130313130ULL, 0x3030313130313130ULL, 
0x3130313130313130ULL, 0x3031313130313130ULL, 0x3131313130313130ULL, 
0x3030303031313130ULL, 0x3130303031313130ULL, 0x3031303031313130ULL, 
0x3131303031313130ULL, 0x3030313031313130ULL, 0x3130313031313130ULL, 
0x3031313031313130ULL, 0x3131313031313130ULL, 0x3030303131313130ULL, 
0x3130303131313130ULL, 0x3031303131313130ULL, 0x3131303131313130ULL, 
0x3030313131313130ULL, 0x3130313131313130ULL, 0x3031313131313130ULL, 
0x3131313131313130ULL, 0x3030303030303031ULL, 0x3130303030303031ULL, 
0x3031303030303031ULL, 0x3131303030303031ULL, 0x3030313030303031ULL, 
0x3130313030303031ULL, 0x3031313030303031ULL, 0x3131313030303031ULL, 
0x3030303130303031ULL, 0x3130303130303031ULL, 0x3031303130303031ULL, 
0x3131303130303031ULL, 0x3030313130303031ULL, 0x3130313130303031ULL, 
0x3031313130303031ULL, 0x3131313130303031ULL, 0x3030303031303031ULL, 
0x3130303031303031ULL, 0x3031303031303031ULL, 0x3131303031303031ULL, 
0x3030313031303031ULL, 0x3130313031303031ULL, 0x3031313031303031ULL, 
0x3131313031303031ULL, 0x3030303131303031ULL, 0x3130303131303031ULL, 
0x3031303131303031ULL, 0x3131303131303031ULL, 0x3030313131303031ULL, 
0x3130313131303031ULL, 0x3031313131303031ULL, 0x3131313131303031ULL, 
0x3030303030313031ULL, 0x3130303030313031ULL, 0x3031303030313031ULL, 
0x3131303030313031ULL, 0x3030313030313031ULL, 0x3130313030313031ULL, 
0x3031313030313031ULL, 0x3131313030313031ULL, 0x3030303130313031ULL, 
0x3130303130313031ULL, 0x3031303130313031ULL, 0x3131303130313031ULL, 
0x3030313130313031ULL, 0x3130313130313031ULL, 0x3031313130313031ULL, 
0x3131313130313031ULL, 0x3030303031313031ULL, 0x3130303031313031ULL, 
0x3031303031313031ULL, 0x3131303031313031ULL, 0x3030313031313031ULL, 
0x3130313031313031ULL, 0x3031313031313031ULL, 0x3131313031313031ULL, 
0x3030303131313031ULL, 0x3130303131313031ULL, 0x3031303131313031ULL, 
0x3131303131313031ULL, 0x3030313131313031ULL, 0x3130313131313031ULL, 
0x3031313131313031ULL, 0x3131313131313031ULL, 0x3030303030303131ULL, 
0x3130303030303131ULL, 0x3031303030303131ULL, 0x3131303030303131ULL, 
0x3030313030303131ULL, 0x3130313030303131ULL, 0x3031313030303131ULL, 
0x3131313030303131ULL, 0x3030303130303131ULL, 0x3130303130303131ULL, 
0x3031303130303131ULL, 0x3131303130303131ULL, 0x3030313130303131ULL, 
0x3130313130303131ULL, 0x3031313130303131ULL, 0x3131313130303131ULL, 
0x3030303031303131ULL, 0x3130303031303131ULL, 0x3031303031303131ULL, 
0x3131303031303131ULL, 0x3030313031303131ULL, 0x3130313031303131ULL, 
0x3031313031303131ULL, 0x3131313031303131ULL, 0x3030303131303131ULL, 
0x3130303131303131ULL, 0x3031303131303131ULL, 0x3131303131303131ULL, 
0x3030313131303131ULL, 0x3130313131303131ULL, 0x3031313131303131ULL, 
0x3131313131303131ULL, 0x3030303030313131ULL, 0x3130303030313131ULL, 
0x3031303030313131ULL, 0x3131303030313131ULL, 0x3030313030313131ULL, 
0x3130313030313131ULL, 0x3031313030313131ULL, 0x3131313030313131ULL, 
0x3030303130313131ULL, 0x3130303130313131ULL, 0x3031303130313131ULL, 
0x3131303130313131ULL, 0x3030313130313131ULL, 0x3130313130313131ULL, 
0x3031313130313131ULL, 0x3131313130313131ULL, 0x3030303031313131ULL, 
0x3130303031313131ULL, 0x3031303031313131ULL, 0x3131303031313131ULL, 
0x3030313031313131ULL, 0x3130313031313131ULL, 0x3031313031313131ULL, 
0x3131313031313131ULL, 0x3030303131313131ULL, 0x3130303131313131ULL, 
0x3031303131313131ULL, 0x3131303131313131ULL, 0x3030313131313131ULL, 
0x3130313131313131ULL, 0x3031313131313131ULL, 0x3131313131313131ULL};

/*
 * AIV 05/17/10 - new optimized dsipb version for VCD dumping
 * this is the wide version where trimmed blen may be >= WBITS
 *
 * similar to sdispb in v_cnv.c - in fact could change this routine
 * to be more like this optimized routine
 *
 * uses byte table to assign 1/0 characters aligned on bytes
 */
static void dmpv_sdispb(word32 *ap, word32 *bp, int32 blen)
{
 int32 wi, bi;
 word32 tmpa, tmpb;
 int32 swlen, trimmed_blen, cur_ndx, i, nbytes, r;
 byte *byte_bp;
 word64 *wp;
 char ch;
 char *cp;

 trimmed_blen = __bin_trim_abval(ap, bp, blen);
 if (trimmed_blen == 0) { addch_('0'); return; }
 if (__vval_isall_xs(ap, bp, blen)) { addch_('x'); return; }
 else if (__vval_isallzs(ap, bp, blen)) { addch_('z'); return; }

 /* AIV 04/27/10 - should just use macro not ifdef CVC32 */
 /* know the string is going to add as many characters as there are bytes */
 cur_ndx = __cur_sofs;
 __cur_sofs += trimmed_blen;
 if (__cur_sofs >= __exprlinelen - 1) 
  {
   __chg_xprline_size(trimmed_blen); 
  }
 /* set char ptr to the begin of current char */
 cp = &(__exprline[cur_ndx]);
 swlen = wlen_(trimmed_blen);
 bi = ubits_(trimmed_blen);
 if (bi == 0) bi = WBITS - 1; else bi--;
 wi = swlen - 1;
 /* first word may not be aligned on a word/byte boundary */
 /* firt get the common bpart zero case */
 if (bp[wi] == 0)
  {
   r = ((bi+1) % 8);
   /* assign bit/char at a time until aligned on byte boundary */
   for (i = 0; i < r; i++)
    {
     ch = (ap[wi] >> bi) & 1L;
     *cp = '0' + ch;
     cp++;
     bi--;
    }
   /* now assign aligned on bytes using table */ 
   if (bi != -1) 
    {
     byte_bp = (byte *) &(ap[wi]);
     nbytes = bi/8;
     byte_bp = &(byte_bp[nbytes]);
     wp = (word64 *) cp;
     cp += (bi + 1);
     for (i = 0; i <= nbytes; i++)
      {
       *wp = byte_to_chars[*byte_bp];
       byte_bp--;
       wp++;
      }
    }
  }
 else
  {
   for (;bi >= 0; bi--)
    {
     tmpa = (ap[wi] >> bi) & 1L;
     tmpb = (bp[wi] >> bi) & 1L;
     if (tmpb != 0L) { if (tmpa != 0L) ch = 'x'; else ch = 'z'; }
     else ch = '0' + ((char) tmpa);
     *cp = ch;
     cp++;
    }
  }
 /* now do a word at a time - known to be aligned on words */
 wi--;
 for (; wi >= 0; wi--)
  {
   if (bp[wi] == 0)
    {
     byte_bp = (byte *) &(ap[wi]);
     wp = (word64 *) cp;
     cp += WBITS;
     /* assign a 32/64 word from the byte values */
#ifdef __CVC32__
     wp[0] = byte_to_chars[byte_bp[3]];
     wp[1] = byte_to_chars[byte_bp[2]];
     wp[2] = byte_to_chars[byte_bp[1]];
     wp[3] = byte_to_chars[byte_bp[0]];
#else
     wp[0] = byte_to_chars[byte_bp[7]];
     wp[1] = byte_to_chars[byte_bp[6]];
     wp[2] = byte_to_chars[byte_bp[5]];
     wp[3] = byte_to_chars[byte_bp[4]];
     wp[4] = byte_to_chars[byte_bp[3]];
     wp[5] = byte_to_chars[byte_bp[2]];
     wp[6] = byte_to_chars[byte_bp[1]];
     wp[7] = byte_to_chars[byte_bp[0]];
#endif
    }
   else
    {
     for (bi = WBITS-1; bi >= 0; bi--)
      {
       tmpa = (ap[wi] >> bi) & 1L;
       tmpb = (bp[wi] >> bi) & 1L;
       if (tmpb != 0L) { if (tmpa != 0L) ch = 'x'; else ch = 'z'; }
       else ch = '0' + ((char) tmpa);
       *cp = ch;
       cp++;
      }
     }
  }
}

/*
 * AIV 09/07/10 - 2-state version
 * - no bparts
 */
static void dmpv_sdispb_2state(word32 *ap, int32 blen)
{
 int32 wi, bi;
 int32 swlen, trimmed_blen, cur_ndx, i, nbytes, r;
 byte *byte_bp;
 word64 *wp;
 char ch;
 char *cp;

 trimmed_blen =  __trim1_0val(ap, blen);
 if (trimmed_blen == 0) { addch_('0'); return; }

 /* AIV 04/27/10 - should just use macro not ifdef CVC32 */
 /* know the string is going to add as many characters as there are bytes */
 cur_ndx = __cur_sofs;
 __cur_sofs += trimmed_blen;
 if (__cur_sofs >= __exprlinelen - 1) 
  {
   __chg_xprline_size(trimmed_blen); 
  }
 /* set char ptr to the begin of current char */
 cp = &(__exprline[cur_ndx]);
 swlen = wlen_(trimmed_blen);
 bi = ubits_(trimmed_blen);
 if (bi == 0) bi = WBITS - 1; else bi--;
 wi = swlen - 1;
 /* first word may not be aligned on a word/byte boundary */
 r = ((bi+1) % 8);
 /* assign bit/char at a time until aligned on byte boundary */
 for (i = 0; i < r; i++)
  {
   ch = (ap[wi] >> bi) & 1L;
   *cp = '0' + ch;
   cp++;
   bi--;
  }
 /* now assign aligned on bytes using table */ 
 if (bi != -1) 
  {
   byte_bp = (byte *) &(ap[wi]);
   nbytes = bi/8;
   byte_bp = &(byte_bp[nbytes]);
   wp = (word64 *) cp;
   cp += (bi + 1);
   for (i = 0; i <= nbytes; i++)
    {
     *wp = byte_to_chars[*byte_bp];
     byte_bp--;
     wp++;
    }
  }
 /* now do a word at a time - known to be aligned on words */
 wi--;
 for (; wi >= 0; wi--)
  {
   byte_bp = (byte *) &(ap[wi]);
   wp = (word64 *) cp;
   cp += WBITS;
   /* assign a 32/64 word from the byte values */
#ifdef __CVC32__
   wp[0] = byte_to_chars[byte_bp[3]];
   wp[1] = byte_to_chars[byte_bp[2]];
   wp[2] = byte_to_chars[byte_bp[1]];
   wp[3] = byte_to_chars[byte_bp[0]];
#else
   wp[0] = byte_to_chars[byte_bp[7]];
   wp[1] = byte_to_chars[byte_bp[6]];
   wp[2] = byte_to_chars[byte_bp[5]];
   wp[3] = byte_to_chars[byte_bp[4]];
   wp[4] = byte_to_chars[byte_bp[3]];
   wp[5] = byte_to_chars[byte_bp[2]];
   wp[6] = byte_to_chars[byte_bp[1]];
   wp[7] = byte_to_chars[byte_bp[0]];
#endif
  }
}

/*
 * AIV 05/17/10 - new optimized dsipb version for VCD dumping
 * this is the 1 word version version where trimmed blen is known <= WBITS
 */
static void dmpv_sdispb_1w(word32 aval, word32 bval, int32 blen)
{
 int32 bi;
 word32 tmpa, tmpb;
 int32 trimmed_blen, cur_ndx, i, nbytes, r;
 byte *byte_bp;
 word64 *wp;
 char ch;
 char *cp;

 trimmed_blen = __bin_trim_abval(&aval, &bval, blen);
 if (trimmed_blen == 0) { addch_('0'); return; }
 if (__vval_isall_xs(&aval, &bval, blen)) { addch_('x'); return; }
 else if (__vval_isallzs(&aval, &bval, blen)) { addch_('z'); return; }

 /* AIV 04/27/10 - should just use macro not ifdef CVC32 */
 /* know the string is going to add as many characters as there are bytes */
 cur_ndx = __cur_sofs;
 __cur_sofs += trimmed_blen;
 /* set char ptr to the begin of current char */
 cp = &(__exprline[cur_ndx]);

 bi = trimmed_blen;
 if (bi == 0) bi = WBITS - 1; else bi--;

 /* AIV 04/27/10 - removed worthless tmpa/tmpb assign */
 if (bval == 0)
  {
   r = ((bi+1) % 8);
   for (i = 0; i < r; i++)
    {
     ch = (aval >> bi) & 1L;
     *cp = '0' + ch;
     cp++;
     bi--;
    }
   if (bi != -1) 
    {
     byte_bp = (byte *) &aval;
     nbytes = bi/8;
     byte_bp = &(byte_bp[nbytes]);
     wp = (word64 *) cp;
     cp += (bi + 1);
     for (i = 0; i <= nbytes; i++)
      {
       *wp = byte_to_chars[*byte_bp];
       byte_bp--;
       wp++;
      }
    }
  }
 else
  {
   for (;bi >= 0; bi--)
    {
     tmpa = (aval >> bi) & 1L;
     tmpb = (bval >> bi) & 1L;
     if (tmpb != 0L) { if (tmpa != 0L) ch = 'x'; else ch = 'z'; }
     else ch = '0' + ((char) tmpa);
     *cp = ch;
     cp++;
    }
  }
}

/*
 * 2-state version of dmpv_sdisp_1w 
 * - no bparts
 */
static void dmpv_sdispb_1w_2state(word32 aval, int32 blen)
{
 int32 bi;
 int32 trimmed_blen, cur_ndx, i, nbytes, r;
 byte *byte_bp;
 word64 *wp;
 char ch;
 char *cp;

 trimmed_blen =  __trim1_0val(&(aval), blen);
 if (trimmed_blen == 0) { addch_('0'); return; }

 /* AIV 04/27/10 - should just use macro not ifdef CVC32 */
 /* know the string is going to add as many characters as there are bytes */
 cur_ndx = __cur_sofs;
 __cur_sofs += trimmed_blen;
 /* set char ptr to the begin of current char */
 cp = &(__exprline[cur_ndx]);

 bi = trimmed_blen;
 if (bi == 0) bi = WBITS - 1; else bi--;

 r = ((bi+1) % 8);
 for (i = 0; i < r; i++)
  {
   ch = (aval >> bi) & 1L;
   *cp = '0' + ch;
   cp++;
   bi--;
  }
 if (bi != -1) 
  {
   byte_bp = (byte *) &aval;
   nbytes = bi/8;
   byte_bp = &(byte_bp[nbytes]);
   wp = (word64 *) cp;
   cp += (bi + 1);
   for (i = 0; i <= nbytes; i++)
    {
     *wp = byte_to_chars[*byte_bp];
     byte_bp--;
     wp++;
    }
  }
}

/*
 * convert one event it changes is always 1
 */
static void bld1_dmpv_event(struct net_t *np, t_midat *idp)
{
 /* when changed written with 1 - never have value 0 and always 1 bit */
 /* will only be on changed list if cause during this time slot */
 addch_('1');
}

/*
 * convert one real value
 */
static void bld1_dmpv_real(struct net_t *np, t_midat *idp)
{
 double d1; 
  
 /* double is always 8 bytes stored using b part as extra 4 bytes */
 /* net width is 32 */
 /* AIV 04/25/08 - has caculating the idp index inefficiently */
 memcpy(&d1, &(idp[np->nva_ofs]), sizeof(double));
 sprintf(__xs2, "r%.16g ", d1);   
 __adds(__xs2);
}

/*
 * convert a vector which is known to be <= WBITS
 */
static void bld1_dmpv_vector_1w(struct net_t *np, t_midat *idp)
{
 int32 blen;
 word32 *ap;

 blen = np->nwid;
 ap = &(idp[np->nva_ofs]);

 /* BEWARE - known to fit in __exprline - since it is narrow case */
 __exprline[__cur_sofs++] = 'b'; 
 dmpv_sdispb_1w(ap[0], ap[1], blen);
 __exprline[__cur_sofs++] = ' '; 
}

/*
 * convert a vector which is > WBITS
 */
static void bld1_dmpv_vector_wide(struct net_t *np, t_midat *idp)
{
 int32 blen;
 word32 *ap, *bp;

 blen = np->nwid;
 ap = &(idp[np->nva_ofs]);
 bp = &(ap[wlen_(blen)]);

 addch_('b');
 dmpv_sdispb(ap, bp, blen);
 addch_(' ');
}

/*
 * convert one real array value
 */
static void bld1_dmpv_real_array(struct net_t *np, t_midat *idp)
{
 word32 *ap;
 int32 arri;
 double d1; 

 ap = &(idp[np->nva_ofs]);
 arri = __dvars_array_ndx;
 /* find element arri that may be a vector */
 ap = &(ap[arri*2]);
  
 /* double is always 8 bytes stored using b part as extra 4 bytes */
 /* net width is 32 */
 /* AIV 04/25/08 - has caculating the idp index inefficiently */
 memcpy(&d1, ap, sizeof(double));
 sprintf(__xs2, "r%.16g ", d1);   
 __adds(__xs2);
}

/*
 * convert an array vector element which is known to be <= WBITS 
 */
static void bld1_dmpv_vector_1w_packed_array(struct net_t *np, t_midat *idp)
{
 int32 blen, arri;
 word32 av, bv, tmpw;
 word32 *ap;

 blen = np->nwid;
 ap = &(idp[np->nva_ofs]);
 arri = __dvars_array_ndx;
 /* find element arri that may be a vector */
 tmpw = get_packintowrd_(ap, arri, blen);
 av = tmpw & __masktab[blen];
 bv = (tmpw >> blen);

 addch_('b');
 dmpv_sdispb_1w(av, bv, blen);
 addch_(' ');
}

/*
 * convert an array vector element which is known to be <= WBITS 
 */
static void bld1_dmpv_vector_notpacked_1w_array(struct net_t *np, t_midat *idp)
{
 int32 blen, wlen, arri;
 word32 *ap, *bp;

 blen = np->nwid;
 ap = &(idp[np->nva_ofs]);
 wlen = wlen_(blen);
 arri = __dvars_array_ndx;
 /* find element arri that may be a vector */
 ap = &(ap[arri*2*wlen]);
 bp = &(ap[wlen]);

 addch_('b');
 dmpv_sdispb_1w(ap[0], bp[0], blen);
 addch_(' ');
}

/*
 * convert an array vector element which is known to be > WBITS 
 */
static void bld1_dmpv_vector_wide_array(struct net_t *np, t_midat *idp)
{
 int32 blen, wlen, arri;
 word32 *ap, *bp;

 blen = np->nwid;
 ap = &(idp[np->nva_ofs]);
 wlen = wlen_(blen);
 /* find element arri that may be a vector */
 arri = __dvars_array_ndx;
 ap = &(ap[arri*2*wlen]);
 bp = &(ap[wlen]);

 addch_('b');
 dmpv_sdispb(ap, bp, blen);
 addch_(' ');
}


/*
 * convert a vector which is has strength
 * just call ld routine and print as binary
 */
static void bld1_dmpv_vector_svec(struct net_t *np, t_midat *idp)
{
 decl_idp_locals_;
 struct xstk_t *xsp;
 word32 *ap;

 set_save_idp_(idp); 
 push_xstk_(xsp, np->nwid);
 addch_('b');
 ap = &(idp[np->nva_ofs]);
 __ld_stval(xsp->ap, xsp->bp, (byte *) ap, np->nwid);
 dmpv_sdispb(xsp->ap, xsp->bp, np->nwid);
 addch_(' ');
 __pop_xstk();
 restore_idp_();
}

static const char valtoch_tab[] = { '0', '1', 'z', 'x' };

/*
 * convert one scalar value 
 */
static void bld1_dmpv_scalar(struct net_t *np, t_midat *idp)
{
 word32 v;

 /* AIV 04/25/08 - has caculating the idp index inefficiently */
 v = idp[np->nva_ofs];
 /* BEWARE - known to fit in __exprline - since it is narrow case */
 __exprline[__cur_sofs++] = valtoch_tab[v & 3];
}

/*
 * convert one array element scalar value 
 */
static void bld1_dmpv_scalar_array(struct net_t *np, t_midat *idp)
{
 word32 v;
 int32 arri, indi;
 word32 *rap;

 arri = __dvars_array_ndx;
 indi = 2*arri;
 rap = &(idp[np->nva_ofs]);
 v = rap[get_wofs_(indi)] >> (get_bofs_(indi));

 /* BEWARE - known to fit in __exprline - since it is narrow case */
 __exprline[__cur_sofs++] = valtoch_tab[v & 3];
}

/*
 * 2-state wide vector
 */
static void bld1_dmpv_vector_2state_wide_array(struct net_t *np, 
  t_midat *idp) 
{
 int32 blen, wlen, arri;
 word32 *ap;

 blen = np->nwid;
 ap = &(idp[np->nva_ofs]);
 wlen = wlen_(blen);
 arri = __dvars_array_ndx;
 ap = &(ap[arri*wlen]);

 addch_('b');
 dmpv_sdispb_2state(ap, blen);
 addch_(' ');
}

/*
 * 2-state 1w array element
 */
static void bld1_dmpv_vector_2state_1w_array(struct net_t *np, t_midat *idp)
{
 int32 blen, wlen, arri;
 word32 *ap;

 blen = np->nwid;
 ap = &(idp[np->nva_ofs]);
 wlen = wlen_(blen);
 arri = __dvars_array_ndx;
 ap = &(ap[arri*wlen]);

 addch_('b');
 dmpv_sdispb_1w_2state(ap[0], blen);
 addch_(' ');

}

/*
 * 2-state wide array element
 */
static void bld1_dmpv_vector_2state_wide(struct net_t *np, t_midat *idp)
{
 int32 blen;
 word32 *ap;

 blen = np->nwid;
 ap = &(idp[np->nva_ofs]);

 addch_('b');
 dmpv_sdispb_2state(ap, blen);
 addch_(' ');
}

/*
 * 2-state 1-word vector
 */
static void bld1_dmpv_vector_2state_1w(struct net_t *np, t_midat *idp)
{
 int32 blen;
 word32 *ap;

 blen = np->nwid;
 ap = &(idp[np->nva_ofs]);

 /* BEWARE - known to fit in __exprline - since it is narrow case */
 __exprline[__cur_sofs++] = 'b'; 
 dmpv_sdispb_1w_2state(ap[0], blen);
 __exprline[__cur_sofs++] = ' '; 
}

/*
 * 2-state - convert one array element scalar value 
 * same as above with no 2x index
 */
static void bld1_dmpv_scalar_2state_array(struct net_t *np, t_midat *idp)
{
 word32 v;
 int32 arri;
 word32 *rap;

 arri = __dvars_array_ndx;
 rap = &(idp[np->nva_ofs]);
 v = rap[get_wofs_(arri)] >> (get_bofs_(arri));
 __exprline[__cur_sofs++] = valtoch_tab[v & 1];
}

/*
 * build 1 variable's dumpvar x value string into exprline
 * format is x[up to 4 char id name] for scalar or bx [id] for vector
 */
static void bld1_xdvval(struct net_t *np, char *dvcodp)
{
 __cur_sofs = 0;
 if (!np->n_isavec)
  { if (np->ntyp == N_EVENT) addch_('1'); else addch_('x'); }
 /* real x is 0.0 */
 else if (np->ntyp == N_REAL) __adds("r0.0 ");
 else __adds("bx ");
 __adds(dvcodp);
}

/*
 * write the built dump var value
 * know by here line always has ending new line
 */
static void dv_wr(int32 nd_nl)
{
 int32 new_fsiz;

 if (__cur_sofs == 0) return;
 if (__dv_dumplimit_size != 0)
  {
   if (__dv_state == DVST_OVERLIMIT) return;

   /* LOOKATME - +1 right since it points to \0? */
   /* SJM 11/13/99 - no adding one makes file too small (now matches 1862) */
   new_fsiz = __dv_file_size + __cur_sofs; 
   __dv_file_size = new_fsiz;
  }
 /* know __cur_sofs points one past end of buffer */
 /* 2 overflow cases current line bigger than buffer or does not fit */
 if (__dv_nxti + __cur_sofs >= DVBUFSIZ - 2) 
  {
   /* SJM 03/03/00 - no longer adding nil to end of dv buffer */
   if (__dv_nxti > 0)
    {
     /* DBG remove --
     __cv_msg("writing dumpvars buffer of size %d\n", __dv_nxti);
     --- */
     write(__dv_fd, __dv_buffer, __dv_nxti);
    }
   __dv_nxti = 0;
   /* immediate write if larger than buffer */
   if (__cur_sofs >= DVBUFSIZ - 2)
    {
     if (nd_nl)
      {
       __exprline[__cur_sofs++] = '\n';
       __dv_file_size++;
      }
     write(__dv_fd, __exprline, __cur_sofs); 
     /* DBG remove --
     __cv_msg("writing dumpvars buffer of size %d\n", __cur_sofs + 1);
     --- */
     goto done;
    }
  }
 memcpy(&(__dv_buffer[__dv_nxti]), __exprline, __cur_sofs);

 __dv_nxti += __cur_sofs;
 if (nd_nl)
  {
   __dv_file_size++;
   __dv_buffer[__dv_nxti++] = '\n';
  }

done:
 /* FIXME - what if wrote without new line to add or in string - then wrong? */
 __dv_outlinpos = 0;
 __cur_sofs = 0;
}

/*
 * flush a dumpvars - empty buffer then do OS flush 
 */
extern void __my_dv_flush(void)
{
 if (__dv_nxti > 0) write(__dv_fd, __dv_buffer, __dv_nxti);
 __dv_nxti = 0;

 /* SJM 07/02/00 - now avoiding fwrite buffering -- 
 if (fflush(__dv _ s) == EOF)
  {
   __sgferr(701, "OS failure when flushing $dumpvars file %s: %s",
    __dv_fnam, strerror(errno));
  }
 --- */
}

/*
 * ROUTINES TO IMPLEMENT $DUMPPORTS 
 */  

/*
 * execute a dumpports system task in source - just collect information
 * - written at end of this time unit
 *
 * even if off must still always write header 
 * this must be called with nil if none or func. call. operator (hd of list) 
 */  
extern void __exec_dumpports(struct expr_t *argx)
{
 int32 anum, ii, slen, has_args, dpd_ndx;
 t_midat *xmr_idp, *idp;
 struct dpinstel_t *dpip, *dpi_hdr, *dpi_end;
 struct dp_fildesc_t *new_fdescp;
 struct gref_t *grp;
 struct sy_t *syp;
 struct itree_t *itp;
 char s1[RECLEN], *chp;

 /* multiple dumpports legal during first time where dumpports seen */
 /* dp seen means previous time tick dumpports call */
 if (__dp_seen)
  {
   __sgferr(729,
    "all $dumpports calls must be at same time - previously called at %s",
     __to_timstr(__xs, &__dp_calltime));
   return;
  }
 __dp_calltime = __simtime;

 /* SJM 09-25-08 no arg forms allowed here */
 xmr_idp = NULL;
 has_args = TRUE;
 dpi_hdr = dpi_end = NULL;
 if (argx == NULL) 
  {
   /* no args use default for both scope (current module) */  
   /* first inst of current mod(should only be one) and file "dumpports.vcd" */ 
   strcpy(s1, DFLTDPFNAM);
   dpip = alloc_dpinstel();
   dpip->dpinst_idp = __idp;
   dpip->dpinxt = NULL;
   dpi_hdr = dpi_end = dpip;
   has_args = FALSE;
  }
 else if (argx->ru.x == NULL)
  {
   /* one argument - it is the file name */
   dpip = alloc_dpinstel();
   dpip->dpinst_idp = __idp;
   dpip->dpinxt = NULL;
   dpi_hdr = dpi_end = dpip;

   chp = __get_eval_cstr(argx->lu.x, &slen);
   strcpy(s1, chp);
   has_args = FALSE;
  }
 
 if (has_args)
  {
   /* argument list form, know first is level */
   for (anum = 0; ; anum++)
    {
     /* ,, form, seemingly legal but just ignore */
     if (argx->lu.x->optyp == OPEMPTY)
      {
       argx = argx->ru.x;
       continue;
      } 
     if (argx->ru.x == NULL) break;

     /* do not need checking since checked at fixup time */
     xmr_idp = NULL;
     if (argx->lu.x->optyp == GLBREF)
      {
       grp = argx->lu.x->ru.grp;
       syp =  grp->targsyp; 
       dpip = alloc_dpinstel();
       /* xmr wire */
       switch ((byte) syp->sytyp) {
        case SYM_I:
         xmr_idp = __xmrget_refgrp_to_targ(grp);
         goto inst_form;
        case SYM_M:
         if ((ii = __ip_indsrch(syp->synam)) == -1)
          __case_terr(__FILE__, __LINE__);
         xmr_idp = __it_roots[ii]->it_idp;
inst_form:
         dpip->dpinst_idp = xmr_idp;
         break;
        default: __case_terr(__FILE__, __LINE__);
       }
      }
     else
      {
       /* SJM 09-25-08 - only module identifiers (XMRs) allowed here */ 
       __sgferr(715,
        "$dumpports scope list argument %s not module scope identifier",
        __msgexpr_tostr(__xs, argx->lu.x));
       return;
      }
     /* SJM 09-29-08 know one instance dumpports (dumps all ports) can only */
     /* appear once in entire design (multiple calls to $dumpports legal) */
     if (dpip->dpinst_idp[MD_DPIP] != 0)
      {
       itp = (struct itree_t *) dpip->dpinst_idp[MD_ITP];
       __sgferr(715,
        "$dumpports repeated for module type %s instance %s - this replaces\n",
        itp->itip->imsym->synam, __msg2_blditree(__xs, itp));
      }
     /* save the instance fd */
     dpip->dpinst_idp[MD_DPIP] = (t_midat) dpip;

     if (dpi_end == NULL) dpi_hdr = dpip; else dpi_end->dpinxt = dpip;
     dpi_end = dpip;
     dpip->dpinxt = NULL;
     argx = argx->ru.x;
    } 
   /* know has one last argument that is the file name */
   chp = __get_eval_cstr(argx->lu.x, &slen);
   strcpy(s1, chp);
  } 

 /* possible to have (, [file name]) args - no mod insts - catch here */
 if (dpi_hdr == NULL)
  {
   dpip = alloc_dpinstel();
   dpip->dpinst_idp = __idp;
   dpip->dpinxt = NULL;
   dpi_hdr = dpi_end = dpip;
   has_args = FALSE;
  }
 if (!has_args)
  {
   /* set the one dumpports instel fixed idp offset to point to one instel */
   /* SJM 09-29-08 know one instance dumpports (dumps all ports) can only */
   /* appear once in entire design (multiple calls to $dumpports legal) */
   if (dpi_hdr->dpinst_idp[MD_DPIP] != 0)
    {
     itp = (struct itree_t *) dpi_hdr->dpinst_idp[MD_ITP];
     __sgferr(715,
      "$dumpports no arg list form repeated for module type %s instance %s - this replaces\n",
      itp->itip->imsym->synam, __msg2_blditree(__xs, itp));
    }
   /* save the instance fd */
   dpi_hdr->dpinst_idp[MD_DPIP] = (t_midat) dpi_hdr;
  }

 /* if file name already used - error and ignore - also free dpip list */
 if ((dpd_ndx = dpfildesc_ndx_from_fnam(s1)) != -1)
  {
   __sgferr(715,
    "$dumpports file name %s used more than once - this one ignored", s1); 
   free_dpinst_lst(dpi_hdr);
   return;
  }

 /* if first time, no dump ports file descriptor table, alloc it */ 
 if (__dp_fildesc_tab == NULL)
  {
   __dp_fildesc_tab = (struct dp_fildesc_t *)
    __my_malloc(MAX_DMPPRTS_FILES*sizeof(struct dp_fildesc_t));  
  }
 if (__dp_fildesc_nxti + 1 >= MAX_DMPPRTS_FILES)
  {
   __sgferr(715, "$dumpports too many open file (%d) - file %s ignored\n", 
    MAX_DMPPRTS_FILES, s1);

   /* free the dpinstel records */
   free_dpinst_lst(dpi_hdr);
   return;
  }

 /* init idp area to point to file desc */
 if (xmr_idp != NULL) idp = xmr_idp;
 else idp = __idp;
     
 new_fdescp = &(__dp_fildesc_tab[__dp_fildesc_nxti]);
 init_dp_fildesc(new_fdescp);
 /* can't open file or set states yet, but need to save the file name */
 new_fdescp->dp_fnam = __pv_stralloc(s1);
 /* next one to use if there are more */
 __dp_fildesc_nxti++;
 new_fdescp->dpi_hdr = dpi_hdr;
 new_fdescp->dpi_end = dpi_end;

  /* SJM 10-06-08 need to set the file desc addr in each dpi because */
  /* needed quickly during recording - control recording so much set here */
  /* this sets the back link - fdesc's have list of ptrs to dpip too */
  for (dpip = dpi_hdr; dpip != NULL; dpip = dpip->dpinxt)
   {
    dpip->dpi_fdescp = new_fdescp;
   }

 __slotend_action |= SE_DUMPPORTS;
}
 
/*
 * allocate a new dumpports argument inst element (of one file) record
 */
static struct dpinstel_t *alloc_dpinstel(void)
{
 struct dpinstel_t *dpip;

 dpip = (struct dpinstel_t *) __my_malloc(sizeof(struct dpinstel_t));
 dpip->dpinst_idp = NULL;
 dpip->dpinxt = NULL;
 return(dpip);
}

/*
 * initialize a dump ports file descriptor table 
 */
static void init_dp_fildesc(struct dp_fildesc_t *fdescp)
{
 fdescp->dp_fnam = NULL;
 fdescp->dp_func = DMPP_DMPALL;
 fdescp->dp_state = DPST_NOTSETUP;
 fdescp->dp_dumplimit_size = 0;
 fdescp->dp_file_size = 0;
 fdescp->dp_time_emitted = 0ULL;
 fdescp->dp_fd = -1;
 fdescp->dp_buffer = NULL;
 fdescp->dp_nxti = 0;
 fdescp->dp_outlinpos = -1;
 fdescp->dp_slotend_action = 0;
 
 fdescp->dpi_hdr = NULL;
 fdescp->dpi_end = NULL;
 fdescp->dp_chgnethdr = NULL;
}

/*
 * free from passed (know not nil) to end of a dp master itree/file list 
 */
static void free_dpinst_lst(struct dpinstel_t *dpi_hd)
{
 struct dpinstel_t *dpip, *dpip2;

 if (dpi_hd == NULL) return;
 for (dpip = dpi_hd; dpip != NULL;)
  {
   dpip2 = dpip->dpinxt;
   __my_free(dpip, sizeof(struct dpinstel_t));
   dpip = dpip2;
  }
}

/*
 * find a dump ports file descriptor index given file name
 */  
static int32 dpfildesc_ndx_from_fnam(char *fnam)
{
 int32 dpdi;

 for (dpdi = 0; dpdi < __dp_fildesc_nxti; dpdi++)
  {
   if (strcmp(__dp_fildesc_tab[dpdi].dp_fnam, fnam) == 0) return(dpdi);
  }
 return(-1);
}

/*
 * $DUMPPORTS DURING SIM EXEC ROUTINES
 */

/*
 * execute a dumpportsflush system task in source
 * 
 * if no args applies to every open dumpports file
 */  
extern void __exec_dumpportsflush(struct expr_t *argx)
{
 int32 dpdi, slen;
 struct dp_fildesc_t *fdescp;
 struct expr_t *argvx;
 char *chp;

 /* SJM 07-27-08 can check before know which file because all set up at */
 /* same time */
 if (__dp_seen)
  {
   __sgferr(703,
    "$dumpports at %s ignored because: dumping of ports not begun",
     __to_timstr(__xs, &__simtime));
   return;
  }
 /* flush when called - i.e. flush is before this time's dumping */
 /* this calls OS functions that may set errno */
 if (argx == NULL)
  {
   /* no args, semantics is to flush every open dumpports file */
   for (dpdi = 0; dpdi < __dp_fildesc_nxti; dpdi++)
    {
     fdescp = &(__dp_fildesc_tab[dpdi]);
     /* DBG remove -- */
     if (fdescp->dp_fd == -1) __arg_terr(__FILE__, __LINE__);
     /* -- */
     __my_dp_flush(fdescp);
    }
   return;
  }
 /* find and flush the one file - know first and only arg */
 argvx = argx->lu.x;
 chp = __get_eval_cstr(argvx, &slen);
 dpdi = dpfildesc_ndx_from_fnam(chp);
 if (dpdi == -1)
  {
   __sgferr(1036, "$dumpportsflush file argument not found or illegal %s",
    __msgexpr_tostr(__xs, argvx));
  }
 /* set the file to dump too */
 fdescp = &(__dp_fildesc_tab[dpdi]);
 /* DBG remove -- */
 if (fdescp->dp_fd == -1) __arg_terr(__FILE__, __LINE__);
 /* -- */
 __my_dp_flush(fdescp);
}

/*
 * execute a dumpportslimit system task in source
 * 
 * if no args applies to every open dumpports file
 */  
extern void __exec_dumpportslimit(struct expr_t *argx)
{
 int32 dpdi;
 int32 slen;
 word32 wval;
 struct dp_fildesc_t *fdescp;
 struct expr_t *argvx;
 char *chp;

 /* DBG remove -- */
 if (argx == NULL) __misc_terr(__FILE__, __LINE__);
 /* --- */

 /* SJM 07-27-08 can check before know which file because all set up at */
 /* same time */
 if (__dp_seen)
  {
   __sgferr(703,
    "$dumpportslimit at %s ignored because: dumping of ports not begun",
    __to_timstr(__xs, &__simtime));
   return;
  }

 /* notice can call even if not set up and can change if not over limit */
 argvx = argx->lu.x;
 if (!__get_eval_word(argvx, &wval) || ((wval & (1UL << (WBITS - 1))) != 0))
  {
   __sgferr(1036, "$dumpportslimit value %s illegal positive value - not set",
    __msgexpr_tostr(__xs, argvx));
   return;
  }
 /* move to optional second arg */
 argx = argx->ru.x;

 /* if no second arg, applies to evey dumpports file */
 if (argx == NULL)
  {
   /* no args, semantics is to flush every open dumpports file */
   for (dpdi = 0; dpdi < __dp_fildesc_nxti; dpdi++)
    {
     fdescp = &(__dp_fildesc_tab[dpdi]);
     chk_set_dp_limits(fdescp, wval);
    }
   return;
  }
 /* find and flush the one file - know first and only arg */
 argvx = argx->lu.x;
 chp = __get_eval_cstr(argvx, &slen);
 dpdi = dpfildesc_ndx_from_fnam(chp);
 if (dpdi == -1)
  {
   __sgferr(1036, "$dumpportslimit file argument not found or illegal %s",
    __msgexpr_tostr(__xs, argvx));
   return;
  }
 /* set the file to dump too */
 fdescp = &(__dp_fildesc_tab[dpdi]);
 chk_set_dp_limits(fdescp, wval);
}

/*
 * routine to check and set dumpports limit for one file
 */
static void chk_set_dp_limits(struct dp_fildesc_t *fdescp, word32 wval)
{
 /* if already over limit cannot change */
 if (fdescp->dp_state == DPST_OVERLIMIT)
  {
   __sgferr(1069,
    "$dumpportslimit not set to %d - dumpports file already over previous limit %d",
    (int32) wval, fdescp->dp_dumplimit_size);
   return;
  }
 /* else inform if already set */
 if (__dv_dumplimit_size != 0)
  {
   __sgfinform(449, "for file %s - $dumpportslimit changed from %d to %d",
    fdescp->dp_fnam, fdescp->dp_dumplimit_size, (int32) wval);
  }
 fdescp->dp_dumplimit_size = (int32) wval; 
}

/*
 * exec system task to turn dumpports on or off
 */
extern void __exec_dumpports_on_off(struct expr_t *argx, int32 dump_on)
{
 int32 dpdi, slen;
 struct dp_fildesc_t *fdescp;
 struct expr_t *argvx;
 char s1[RECLEN], *chp;

 if (dump_on) strcpy(s1, "$dumpportson"); else strcpy(s1, "$dumpportsoff");

 /* SJM 07-27-08 can check before know which file because all set up at */
 /* same time */
 if (__dp_seen)
  {
   __sgferr(703, "%s at %s ignored because: dumping of ports not begun",
    s1, __to_timstr(__xs, &__simtime));
   return;
  }
 
 if (argx == NULL)
  {
   /* no args, semantics is to turn on/off every open dumpports file */
   for (dpdi = 0; dpdi < __dp_fildesc_nxti; dpdi++)
    {
     fdescp = &(__dp_fildesc_tab[dpdi]);
     if (dump_on) chk_set_dp_on(fdescp); else chk_set_dp_off(fdescp);
    }
   return;
  }
 /* find and flush the one file - know first and only arg */
 argvx = argx->lu.x;
 chp = __get_eval_cstr(argvx, &slen);
 dpdi = dpfildesc_ndx_from_fnam(chp);
 if (dpdi == -1)
  {
   __sgferr(1036, "%s file argument not found or illegal %s",
    s1, __msgexpr_tostr(__xs, argvx));
   return;
  }
 /* set the file to dump too */
 fdescp = &(__dp_fildesc_tab[dpdi]);
 /* DBG remove -- */
 if (fdescp->dp_fd == -1) __arg_terr(__FILE__, __LINE__);
 /* -- */
 if (dump_on) chk_set_dp_on(fdescp); else chk_set_dp_off(fdescp);
}

/*
 * routine to check and set dumpports on
 */
static void chk_set_dp_on(struct dp_fildesc_t *fdescp)
{
 switch ((byte) fdescp->dp_state) {
  /* if over limit silently ignore */
  case DPST_NOTSETUP: __case_terr(__FILE__, __LINE__); break;
  case DPST_OVERLIMIT: break;
  case DPST_DUMPING:
   if ((fdescp->dp_slotend_action & SE_DUMPPORTSOFF) != 0)
    {
     __sgfinform(453,
      "$dumpportson overrides $dumpportsoff executed at this time");
     fdescp->dp_slotend_action &= ~SE_DUMPPORTSOFF;
    }
   __sgfinform(446, "$dumpportson ignored because: port dumping already on");
   break;
  case DPST_NOTDUMPING:
   if ((fdescp->dp_slotend_action & SE_DUMPPORTSON) != 0)
    {
     __sgfinform(445,
      "$dumpportson ignored because: $dumpportson already executed at this time");
    }
   /* also indicate need some dumpportss action */
   fdescp->dp_slotend_action |= (SE_DUMPPORTSON | SE_DUMPPORTS);
   break;
  default: __case_terr(__FILE__, __LINE__);
 }
}

/*
 * routine to check and set dumpports off
 */
static void chk_set_dp_off(struct dp_fildesc_t *fdescp)
{
 switch ((byte) fdescp->dp_state) {
  /* if over limit silently ignore */
  case DPST_NOTSETUP: __case_terr(__FILE__, __LINE__); break;
  case DPST_OVERLIMIT: break;
  case DPST_NOTDUMPING:
   if ((fdescp->dp_slotend_action & SE_DUMPPORTSON) != 0)
    {
     __sgfinform(453, "$dumpportsoff overrides $dumpportson executed at this time");
     fdescp->dp_slotend_action &= ~SE_DUMPPORTSON;
    }
   __sgfinform(446, "$dumpportsoff ignored because: port dumping already off");
   break;
  case DPST_DUMPING:
   if ((fdescp->dp_slotend_action & SE_DUMPPORTSON) != 0)
    {
     __sgfinform(445,
     "$dumpportsoff ignored because: $dumpportsoff already executed at this time");
    }
   /* also indicate need some dumpportss action */
   fdescp->dp_slotend_action |= (SE_DUMPPORTSOFF | SE_DUMPVARS);
   break;
  default: __case_terr(__FILE__, __LINE__);
 }
}

/*
 * $DUMPPORTS ROUTINES CALLED DURING INITIAL END OF TIME SLOT SETUP 
 */  

/*
 * setup and write dumpports header for one file
 * 
 * called at end of time when first $dumpports executed
 * know all dump ports files already opened and all dump files and instances
 * within files must be setup at the end of the same time tick
 */
extern void __setup_1file_dmpports(struct dp_fildesc_t *fdescp)
{
 struct dpinstel_t *dpip;

 /* first build the separate highconn/loconn driver d.s and set driver eval */
 /* type access from the list of instel going into passed file */
 for (dpip = fdescp->dpi_hdr; dpip != NULL; dpip = dpip->dpinxt)
  {
   bld_instel_dumpports_eval_ds(dpip);
  }
/* DBG remove --- */
 if (__debug_flg)
  {
   dmp1_fildesc(fdescp);
  }
/* --- */

 fdescp->dp_buffer = __my_malloc(DVBUFSIZ);
 fdescp->dp_nxti = 0;

 sprintf(__xs2, "$date\n    %s\n$end\n", __pv_timestamp);
 __adds(__xs2);
 dp_wr(fdescp, FALSE);

 sprintf(__xs2, "$version\n    %s%s of %s\n$end\n", __vers, __vers2, __ofdt);
  __adds(__xs2);
 dp_wr(fdescp, FALSE);

   /* need to use actual time scale - is default right */
 sprintf(__xs2, "$timescale\n    %s\n$end\n", __to_timunitnam(__xs,
  __des_timeprec));
 __adds(__xs2);
 dp_wr(fdescp, FALSE);

 for (dpip = fdescp->dpi_hdr; dpip != NULL; dpip = dpip->dpinxt)
  {
   /* setup the bits to do the recording */
   turn_on_1inst_dumpports(dpip);

   /* write the header info for the ports of each instance (mod type) in list */
   wr_1inst_dp_scope_and_def(fdescp, dpip);
  }
 sprintf(__xs2, "$enddefinitions $end\n");
 __adds(__xs2);
 dp_wr(fdescp, FALSE);
}

/*
 * turn on dumpport bits and alloc module's code table if not already alloc from
 * dumpports
 */
static void turn_on_1inst_dumpports(struct dpinstel_t *dpip)
{
 int32 ni, ii;
 struct net_t *np;
 struct mod_t *mdp;
 struct itree_t *itp;
 char s1[RECLEN];
 t_midat *idp, *idp2;
 struct dvchgnets_t *dvchgp;
   
 idp = dpip->dpinst_idp;
 itp = (struct itree_t *) idp[MD_ITP];
 mdp = itp->itip->imsym->el.emdp;

 for (ni = 0, np = &(mdp->mnets[0]); ni < mdp->mnnum; ni++, np++)
  {
   if (np->iotyp == NON_IO) continue;
   idp[np->nchgaction_ofs] |= (NCHG_DMPP_VARNOW | NCHG_DMPP_NOTCHGED);
   /* 07/02/00 - SJM - fill module net dvcod table for this net */
   /* FIXME - think size should be 8 for alignment */
   np->dvns = (struct dvchgnets_t *) 
      __my_malloc(sizeof(struct dvchgnets_t)*mdp->flatinum);
   for (ii = 0; ii < mdp->flatinum; ii++)
    {
     idp2 = mdp->moditps[ii]->it_idp;
     dvchgp = &(np->dvns[ii]);
     dvchgp->dvchg_np = np;
     dvchgp->on_list = FALSE;
     dvchgp->dvchg_idp = idp2;
     dvchgp->dvchgnxt = NULL;
     /* AIV 07/20/10 - no need for the mdp->mndvcodatb - has bee removed */
     if (__is_fst)
      {
       dvchgp->idu.idcode = 0;
      }
     else
      {
       dvchgp->idu.dvcodp = __pv_stralloc(__to_dvcode(s1, __next_dvnum + ii));
       set_dmpv_bld_func(np);
      }
    }
   __next_dvnum += mdp->flatinum;
  }
}
     
/*
 * set conversion function for VCD dump vars formatting 
 * AIV 07/14/10 - now allowing dumping of array elements
 * AIV 09/07/10 - added new routines for 2-state values
 */
static void set_dmpv_bld_func(struct net_t *np)
{
 if (np->ntyp == N_EVENT) np->dmpv_funcu.single = bld1_dmpv_event; 
 else if (np->n_isavec) 
  {
   if (np->ntyp == N_REAL)
    {
     /* AIV 07/26/10 - need to handle the real array case as well */
     if (np->n_isarr) 
      {
       np->dmpv_funcu.single = bld1_dmpv_real_array; 
      }
     else np->dmpv_funcu.single = bld1_dmpv_real; 
    }
   else if (np->n_stren)
    {
     np->dmpv_funcu.single = bld1_dmpv_vector_svec; 
    }
   else if (np->n_2state)
    {
     if (np->n_isarr)
      {
       if (np->nwid > WBITS) 
        {
         np->dmpv_funcu.single = bld1_dmpv_vector_2state_wide_array; 
        }
       else np->dmpv_funcu.single = bld1_dmpv_vector_2state_1w_array; 
      }
     else
      {
       if (np->nwid > WBITS) 
        {
         np->dmpv_funcu.single = bld1_dmpv_vector_2state_wide; 
        }
       else np->dmpv_funcu.single = bld1_dmpv_vector_2state_1w; 
      }
    }
   else if (np->nwid <= WBITS)
    {
     if (np->n_isarr) 
      {
       /* if blen > WBITS/2 for array it is still wide */
       if (np->nwid > WBITS/2) 
        {
         np->dmpv_funcu.single = bld1_dmpv_vector_notpacked_1w_array; 
        }
       else np->dmpv_funcu.single = bld1_dmpv_vector_1w_packed_array; 
      }
     else np->dmpv_funcu.single = bld1_dmpv_vector_1w; 
    }
   else 
    {
     if (np->n_isarr) np->dmpv_funcu.single = bld1_dmpv_vector_wide_array; 
     else np->dmpv_funcu.single = bld1_dmpv_vector_wide; 
    }
  }
 else 
  {
   if (np->n_isarr) 
    {
     if (np->n_2state) np->dmpv_funcu.single = bld1_dmpv_scalar_2state_array; 
     else np->dmpv_funcu.single = bld1_dmpv_scalar_array; 
    }
   else 
    {
     /* 2-state scalar uses the same routine */
     np->dmpv_funcu.single = bld1_dmpv_scalar; 
    }
  }
}

/*
 * write the scope movement and port net code definition area values 
 * for one inst (all ports of inst)
 */
static void wr_1inst_dp_scope_and_def(struct dp_fildesc_t *fdescp,
 struct dpinstel_t *dpip)
{
 /* DBG remove */
 if (dpip->dpinst_idp == NULL) __misc_terr(__FILE__, __LINE__);
 /* --- */

 /* only module instance scopes where all ports dump ported allowed */
 /* this handles all its own scope movements */
 wr_fromtop_iscopeto_ports(fdescp, dpip->dpinst_idp);

 wr_1inst_allports_dphdrs(fdescp, dpip->dpinst_idp);

 wr_totop_iscopeback_ports(fdescp, dpip->dpinst_idp);
 /* AIV 01/28/05 - removed an extra upscope printing */ 
}

/*
 * write the dump ports definition area headers for all ports in the one inst
 */
static void wr_1inst_allports_dphdrs(struct dp_fildesc_t *fdescp,
 t_midat *idp)
{
 int32 ni;
 struct net_t *np;
 struct mod_t *mdp;
 struct itree_t *itp;
 char *dvcodp;
 struct dvchgnets_t *dvchgp;

 itp = (struct itree_t *) idp[MD_ITP];
 mdp = itp->itip->imsym->el.emdp;
 /* write all port */
 if (mdp->mnnum == 0) return;
 for (ni = 0, np = &(mdp->mnets[0]); ni < mdp->mnnum; ni++, np++)
  {
   if (np->iotyp == NON_IO) continue;

   /* SJM - 07/02/00 - now dvcods pre-built as strings */
   dvchgp = &(np->dvns[itp->itinum]);
   dvcodp = dvchgp->idu.dvcodp;
   wr_1vectored_dpdef(fdescp, np, dvcodp);
  } 
}

/*
 * write a variable (port) definition to ae dump ports file 
 * always writes the port since dump ports by inst (mod type) not net
 */
static void wr_1vectored_dpdef(struct dp_fildesc_t *fdescp, struct net_t *np,
 char *dvcod)
{
 int32 r1, r2;

 if (np->n_isavec)
  {
   __getwir_range(np, &r1, &r2);
   /* this must be wire name */ 
   strcpy(__xs2, "$var port");
   __adds(__xs2);
   dp_wr(fdescp, FALSE);

   /* SJM 09/13/99 - range but be MSB to LSB - was internal h:0 */
   sprintf(__xs2, "%7d %-4s %s [%d:%d] $end\n", np->nwid, dvcod,
    np->nsym->synam, r1, r2);
   __adds(__xs2);
   dp_wr(fdescp, FALSE);
  }
 else
  {
   strcpy(__xs2, "$var port");
   __adds(__xs2);
   dp_wr(fdescp, FALSE);
   sprintf(__xs2, "      1 %-4s %s $end\n", dvcod, np->nsym->synam);
   __adds(__xs2);
   dp_wr(fdescp, FALSE);
  }
}

/*
 * turn on all the dump ports nchg processing for all insts output into 1 file
 *
 * SJM 09-27-08 - crucial rule is that any inst (its ports) port can only be 
 * written to dumpports file for at most one file
 */
extern void __turnon_1file_all_dumpports(struct dp_fildesc_t *fdescp)
{
 int32 ni;
 t_midat *idp;
 struct dpinstel_t *dpip;
 struct net_t *np;
 struct mod_t *mdp;
 struct itree_t *itp;

 /* for every inst that is dump ported to this file, turn on dump porting */
 for (dpip = fdescp->dpi_hdr; dpip != NULL; dpip = dpip->dpinxt)
  {
   idp = dpip->dpinst_idp;
   itp = (struct itree_t *) idp[MD_ITP];
   mdp = itp->itip->imsym->el.emdp;

   for (ni = 0, np = &(mdp->mnets[0]); ni < mdp->mnnum; ni++, np++)
    {
     if (np->iotyp == NON_IO) continue;
     idp[np->nchgaction_ofs] |= NCHG_DMPP_VARNOW;
    }
  }
}

/*
 * turn off all the dump ports nchg processing for all insts output into 1 file
 *
 * SJM 09-27-08 - crucial rule is that any inst (its ports) port can only be 
 * written to dumpports file for at most one file
 */
extern void __turnoff_1file_all_dumpports(struct dp_fildesc_t *fdescp)
{
 int32 ni;
 t_midat *idp;
 struct dpinstel_t *dpip;
 struct net_t *np;
 struct mod_t *mdp;
 struct itree_t *itp;

 /* for every inst that is dump ported to this file, turn on dump porting */
 for (dpip = fdescp->dpi_hdr; dpip != NULL; dpip = dpip->dpinxt)
  {
   idp = dpip->dpinst_idp;
   itp = (struct itree_t *) idp[MD_ITP];
   mdp = itp->itip->imsym->el.emdp;

   for (ni = 0, np = &(mdp->mnets[0]); ni < mdp->mnnum; ni++, np++)
    {
     if (np->iotyp == NON_IO) continue;

     /* dumpports now off and not changed on (even if changed in slot) */
     idp[np->nchgaction_ofs] &= ~NCHG_DMPP_VARNOW;
     idp[np->nchgaction_ofs] |= NCHG_DMPP_NOTCHGED;
    }
  }
}

/*
 * write all changed port nets from the list of instances and ports that
 * go into the one file fdescp
 */
extern void __do_dmpports_chg(struct dp_fildesc_t *fdescp)
{ 
 struct dvchgnets_t *dpchgnp;
 struct net_t *np;
 int32 itinum;
 t_midat *idp;
 struct dpinstel_t *dpip;
 char *dpcodp;
 struct dvchgnets_t *dvchgp;

 if (fdescp->dp_outlinpos != 0)
  {
   addch_('\n'); 
   __exprline[__cur_sofs] = '\0'; 
   dp_wr(fdescp, FALSE);
  }
 if (!fdescp->dp_time_emitted)
  {
   sprintf(__xs2, "#%s\n", to_dvtimstr(__xs, __simtime));
   __adds(__xs2);
   dp_wr(fdescp, FALSE);
   fdescp->dp_time_emitted = TRUE;
   /* notice can only check for over limit when emitting new change time */
   if (fdescp->dp_dumplimit_size != 0)
    {
     if (fdescp->dp_file_size > fdescp->dp_dumplimit_size)
      {
       fdescp->dp_outlinpos = 0;
       sprintf(__xs2,
        "$comment - Note: $dumpportslimit %d limit exceeded at %s $end\n",
        fdescp->dp_dumplimit_size, __to_timstr(__xs, &__simtime));
       __adds(__xs2);
       dp_wr(fdescp, FALSE);

       fdescp->dp_state = DVST_OVERLIMIT;
       __turnoff_1file_all_dumpports(fdescp);

       __cv_msg(
        "  *** Dumpports stopped at %s for file %s because $dumpportslimit %d exceeded.\n",
        __to_timstr(__xs, &__simtime), fdescp->dp_fnam,
        fdescp->dp_dumplimit_size);

      }
    } 
  }
 fdescp->dp_outlinpos = 0;
 fdescp->dp_func = DMPP_CHGONLY;

 for (dpchgnp = fdescp->dp_chgnethdr; dpchgnp != NULL;
  dpchgnp = dpchgnp->dvchgnxt)
  {
   /* do the dumpvars for one var instance */
   np = dpchgnp->dvchg_np;
   idp = dpchgnp->dvchg_idp;
   /* know inst (itree loc) can never be dumpported in more than one file */
   dpip = (struct dpinstel_t *) idp[MD_DPIP];

   itinum = (int32) idp[MD_INUM];
   dvchgp = &(np->dvns[itinum]);
   dpcodp = dvchgp->idu.dvcodp;

   if (np->n_isavec) bld1_vec_dpval(dpip, np, dpcodp);
   else bld1_scal_dpval(dpip, np, dpcodp);

   dp_wr(fdescp, TRUE);
   /* reset this inst. not changed flag - i.e. must be on (not changed) */
   /* for next time */ 
   idp[np->nchgaction_ofs] |= NCHG_DMPP_NOTCHGED;
  }
 /* AIV 04/22/11 - need to set hdr back to NULL for next time list */
 fdescp->dp_chgnethdr = NULL;
}

/*
 * optimized write routine for writing to a dump ports file
 *
 * SJM 09-26-08 - can reuse expr line because know all changes for one
 * file are processed before repeating for other files
 */
static void dp_wr(struct dp_fildesc_t *fdescp, int32 nd_nl)
{
 int32 new_fsiz;

 if (__cur_sofs == 0) return;
 if (fdescp->dp_dumplimit_size != 0)
  {
   if (fdescp->dp_state == DVST_OVERLIMIT) return;

   /* LOOKATME - +1 right since it points to \0? */
   /* SJM 11/13/99 - no adding one makes file too small (now matches 1862) */
   new_fsiz = fdescp->dp_file_size + __cur_sofs; 
   fdescp->dp_file_size = new_fsiz;
  }
 /* know __cur_sofs points one past end of buffer */
 /* 2 overflow cases current line bigger than buffer or does not fit */
 if (fdescp->dp_nxti + __cur_sofs >= DVBUFSIZ - 2) 
  {
   /* SJM 03/03/00 - no longer adding nil to end of dv buffer */
   if (fdescp->dp_nxti > 0)
    {
     /* DBG remove --
     __cv_msg("writing dumpvars file %s buffer of size %d\n",
      fdescp->dp_fnam, fdescp->dp_nxti);
     --- */
     write(fdescp->dp_fd, fdescp->dp_buffer, fdescp->dp_nxti);
    }
   fdescp->dp_nxti = 0;
   /* immediate write if larger than buffer */
   if (__cur_sofs >= DVBUFSIZ - 2)
    {
     if (nd_nl)
      {
//AIV? - need exprline copy too? 
       /* SJM 08-25-08 - ??? think exprline here is just work string */ 
       /* since do all writing per file at once think can use it */
       __exprline[__cur_sofs++] = '\n';
       fdescp->dp_file_size++;
      }
     write(fdescp->dp_fd, __exprline, __cur_sofs); 
     /* DBG remove --
     __cv_msg("writing dumpvars buffer of size %d to file %s\n",
      fdescp->dp_fnam, __cur_sofs + 1);
     --- */
     goto done;
    }
  }
 memcpy(&(fdescp->dp_buffer[fdescp->dp_nxti]), __exprline, __cur_sofs);

 fdescp->dp_nxti += __cur_sofs;
 if (nd_nl)
  {
   fdescp->dp_file_size++;
   fdescp->dp_buffer[fdescp->dp_nxti++] = '\n';
  }

done:
 /* FIXME - what if wrote without new line to add or in string - then wrong? */
 fdescp->dp_outlinpos = 0;
 __cur_sofs = 0;
}

/*
 * write from top scope to dumpports instance tree location into fdescp file
 */
static void wr_fromtop_iscopeto_ports(struct dp_fildesc_t *fdescp,
 t_midat *idp)
{
 int32 i, frtoplevs;
 struct itree_t *witp;
 struct itree_t **itps, *itp;

 itp = (struct itree_t *) idp[MD_ITP];

 /* AIV 09/02/08 - there was completely wrong and must have been */
 /* since converting to idp - was only using the last scope name */
 /* method needs stack mechanism to print up scopes in reverse order */

 /* count number of scopes */
 frtoplevs = 0;
 for (witp = itp; witp != NULL; witp = witp->up_it)
  { 
   frtoplevs++;
  }
 /* alloc array only - needed to setup so extra pass ok */
 itps = (struct itree_t **) __my_malloc(frtoplevs*sizeof(struct itree_t *));
 i = 0;
 /* reverse the order to print */
 for (witp = itp; witp != NULL; witp = witp->up_it)
  { 
   i++;
   itps[frtoplevs-i] = witp;
  }
 /* print the scope */
 for (i = 0; i < frtoplevs; i++) 
  {
   witp = itps[i];
   sprintf(__xs2, "$scope module %s $end\n", witp->itip->isym->synam); 
   __adds(__xs2);
   dp_wr(fdescp, FALSE);
  }
 /* free temp array */
 __my_free(itps, frtoplevs*sizeof(struct itree_t *));
}

/*
 * write scope change commands to move back up to top into fdescp file 
 */
static void wr_totop_iscopeback_ports(struct dp_fildesc_t *fdescp,
 t_midat *idp)
{
 struct itree_t *witp;
 struct itree_t *itp;

 itp = (struct itree_t *) idp[MD_ITP];
 for (witp = itp;;)
  {
   sprintf(__xs2, "$upscope $end\n");
   __adds(__xs2);
   dp_wr(fdescp, FALSE);

   if ((witp = witp->up_it) == NULL) break;  
  }
}

/*
 * called from slotend action - dump current values of all ports of all the
 * insts that go into one file
 */
extern void __do_dmpports_baseline(struct dp_fildesc_t *fdescp, char *keyws)
{
 struct dpinstel_t *dpip;

 __cur_sofs = 0;
 if (fdescp->dp_outlinpos != 0)
  {
   addch_('\n');
   __exprline[__cur_sofs] = '\0'; 
   dp_wr(fdescp, FALSE);
  }
 if (!fdescp->dp_time_emitted)
  {
   sprintf(__xs2, "#%s\n", to_dvtimstr(__xs, __simtime));
   __adds(__xs2);
   fdescp->dp_time_emitted = TRUE;
   dp_wr(fdescp, FALSE);
  }
 
 __adds(keyws);
 dp_wr(fdescp, TRUE);
 fdescp->dp_outlinpos = 0;
 if (strcmp(keyws, "$dumpportsoff") == 0) fdescp->dp_func = DMPP_DUMPX;
 else fdescp->dp_func = DMPP_DMPALL; 

 /* each file may need to have dumports from many different insts/mods */ 
 for (dpip = fdescp->dpi_hdr; dpip != NULL; dpip = dpip->dpinxt)
  {
   dump_1inst_allports_vals(dpip);
  }

 if (fdescp->dp_outlinpos != 0) addch_('\n');
 __adds("$end\n");
 dp_wr(fdescp, FALSE);
 fdescp->dp_outlinpos = 0;
}

/*
 * dump to one dumpports file all ports of one instance  
 *
 * SJM 09-29-08 - this needs to be from the dp instel d.s entry since
 * need the itree loc for each
 */
static void dump_1inst_allports_vals(struct dpinstel_t *dpip)
{
 int32 ni;
 struct mod_t *mdp;
 struct net_t *np;
 t_midat *idp; 

 idp = dpip->dpinst_idp;
 mdp = (struct mod_t *) idp[MD_MDP];
 if (mdp->mnnum == 0) return;

 for (ni = 0, np = &(mdp->mnets[0]); ni < mdp->mnnum; ni++, np++)
  {
   /* if using default only dump vals for col. to col will never */
   /* have dumpvars so do not need special checking */
   /* if dump all even col. from, this is normal code */ 
   if (np->iotyp == NON_IO) continue;

   dmp_one_dp_val(dpip, np);
  }
}

/*
 * dump a value line for one port using current value  
 *
 * this is used for all inst dumping - not from chg dumping
 */  
static void dmp_one_dp_val(struct dpinstel_t *dpip, struct net_t *np)
{
 t_midat *idp;
 struct itree_t *itp;
 struct dp_fildesc_t *fdescp;
 char *dvcodp;
 struct dvchgnets_t *dvchgp;

 fdescp = dpip->dpi_fdescp;
 idp = dpip->dpinst_idp;
 itp = (struct itree_t *) idp[MD_ITP];
 /* 07/02/00 - SJM - find right dvcod table code */

 dvchgp = &(np->dvns[itp->itinum]);
 dvcodp = dvchgp->idu.dvcodp;

 /* do not need stren competition for dumping just stren strong x's */
 if (fdescp->dp_func == DMPV_DUMPX) bld1_xdpval(np, dvcodp);
 else
  {
   if (np->n_isavec) bld1_vec_dpval(dpip, np, dvcodp);
   else bld1_scal_dpval(dpip, np, dvcodp);
  }
 dp_wr(fdescp, TRUE);
} 

/*
 * build 1 vector dumpports line
 */  
static void bld1_vec_dpval(struct dpinstel_t *dpip, struct net_t *np,
 char *dvcodp)
{
 int32 bi;
 int32 st0, st1;
 char valch, *valchp, *st0chp, *st1chp;
 char s0[RECLEN], s1[RECLEN];

 __cur_sofs = 0;
 valchp = alloca(np->nwid + 1);
 st0chp = alloca(np->nwid + 1);
 st1chp = alloca(np->nwid + 1);

 /* SJM 10-13-08 must fill string H:L since right most bit is low string bit */
 /* SJM 10-14-08 but order of eval can still be low to high */
 for (bi = 0; bi < np->nwid; bi++)
  { 
   valch = bld_1bit_dptriple(&(st0), &(st1), dpip, np, bi);
   valchp[np->nwid - bi - 1] = valch;
   sprintf(s0, "%d", st0);
   sprintf(s1, "%d", st1);
   st0chp[np->nwid - bi - 1] = s0[0];
   st1chp[np->nwid - bi - 1] = s1[0];
  }
 valchp[np->nwid] = '\0';
 st0chp[np->nwid] = '\0';
 st1chp[np->nwid] = '\0';

 addch_('p');
 __adds(valchp);
 addch_(' ');
 __adds(st0chp); 
 addch_(' ');
 __adds(st1chp); 
 addch_(' ');
 __adds(dvcodp);
}

/*
 * build 1 scalar port dumpports value and add to work string
 */
static void bld1_scal_dpval(struct dpinstel_t *dpip, struct net_t *np,
 char *dvcodp)
{
 int32 st0, st1;
 char valch, s1[RECLEN];

 valch = bld_1bit_dptriple(&(st0), &(st1), dpip, np, 0);
 sprintf(s1, "p%c %d %d ", valch, st0, st1); 
 __adds(s1);
 __adds(dvcodp);  
}

/*
 * ROUTINES TO COMPUTE THE VALUE LINE STRING FOR DUMPPORTS 
 */  

static const char dp_invaltoch_tab[] = { 'D', 'U', 'Z', 'N' };
static const char dp_outvaltoch_tab[] = { 'L', 'H', 'T', 'X' };
//SJM? - LOOKATME 09-29-08 - one driver hiz maybe should be 'f' not 'F'
static const char dp_inoutvaltoch_tab[] = { '0', '1', 'F', '?' };

/*
 * return 1 bit of a port's dumpports value triple (valch, st0, st1) 
 *
 * this routine uses dumpports instel record to set port's itree location
 * algorithm uses idea that hiconn (in tester) drivers are above in itree
 * while loconn (in DUT) drivers are in dumpports itree loc or under
 * then two sets are combined and result determines output value char
 *  
 * AIV 10-11-08 - LOOKATME - how should net val access be done?
 */
static char bld_1bit_dptriple(int32 *retst0, int32 *retst1,
 struct dpinstel_t *dpip, struct net_t *np, int32 drvbi)
{
 int32 ni, active_in_drvnum, active_out_drvnum;
 word32 v, st0, st1, hiconn_v, loconn_v, hi_v, lo_v, comb_v;
 t_midat *loc_idp;
 struct mod_t *mdp;
 struct dpctrl_t *dpcp;
 struct dpdrvr_t *dpdrvp;
 char valch;

 loc_idp = dpip->dpinst_idp;
 mdp = (struct mod_t *) loc_idp[MD_MDP];

 st0 = st1 = 0;
 /* not sure if logic is right - can val ch be unchanged */
 valch = '$';
 ni = np - mdp->mnets; 
 dpcp = &(dpip->net_dpctrl_tab[ni][drvbi]);
 switch (dpcp->dp_eval_typ) { 
  case DP_IN_1DRVR:
   /* max 1 input driver - just use val including tristate non connected */
   if (np->n_stren)
    {
     valch = eval_st_1drvr(retst0, retst1, np, drvbi, loc_idp, TRUE);
    }
   else valch = eval_in_1drvr(retst0, retst1, np, drvbi, loc_idp);
   return(valch);
 case DP_OUT_1DRVR:
   /* max 1 output driver - just use val including tristate non connected */
   if (np->n_stren)
    {
     valch = eval_st_1drvr(retst0, retst1, np, drvbi, loc_idp, FALSE);
    } 
   else valch = eval_out_1drvr(retst0, retst1, np, drvbi, loc_idp);
   return(valch);
  case DP_IN_DRVRS:
   dp_set_cnt_driving_vals(&(active_in_drvnum), &(active_out_drvnum), dpcp,
    drvbi, np->n_stren);
   /* DBG remove --- */
   if (active_out_drvnum != 0) __misc_terr(__FILE__, __LINE__);
   /* -- */
inout_in_only_state:
   if (active_in_drvnum <= 1)
    {
     if (np->n_stren)
      {
       valch = eval_st_1drvr(retst0, retst1, np, drvbi, loc_idp, TRUE);
      } 
     else valch = eval_in_1drvr(retst0, retst1, np, drvbi, loc_idp);
     return(valch);
    }
   /* hard case - there is bus contention among hiconns for this input */ 
   /* only stren model possible */
   v = 2;
   for (dpdrvp = dpcp->dp_indrvs; dpdrvp != NULL; dpdrvp = dpdrvp->dpdrvnxt)
    {
     v = __comb_1bitsts(np->ntyp, v, dpdrvp->drv_val);
    }
   /* SJM 10-14-08 - 3 bit wide strens - was masking with only 2 bits */
   st0 = (v >> 5) & 7;
   st1 = (v >> 2) & 7;
   valch = dp_invaltoch_tab[v & 3];
   break;
  case DP_OUT_DRVRS:
   dp_set_cnt_driving_vals(&(active_in_drvnum), &(active_out_drvnum), dpcp,
    drvbi, np->n_stren);
   /* DBG remove --- */
   if (active_in_drvnum != 0) __misc_terr(__FILE__, __LINE__);
   /* -- */
inout_out_only_state:
   if (active_out_drvnum <= 1)
    {
     if (np->n_stren)
      {
       valch = eval_st_1drvr(retst0, retst1, np, drvbi, loc_idp, FALSE);
      }
     else valch = eval_out_1drvr(retst0, retst1, np, drvbi, loc_idp);
     return(valch);
    }
   /* hard case - there is bus contention among loconns for this output */ 
   /* only stren model possible */
   v = 2;
   for (dpdrvp = dpcp->dp_indrvs; dpdrvp != NULL; dpdrvp = dpdrvp->dpdrvnxt)
    {
     v = __comb_1bitsts(np->ntyp, v, dpdrvp->drv_val);
    }
   st0 = (v >> 5) & 7;
   st1 = (v >> 2) & 7;
   valch = dp_outvaltoch_tab[v & 3];
   break;
  case DP_INOUT_1DRVR:
   /* SJM 10-14-08 - for now treating known max possible one connected (non */
   /* tristated) driver - can be either in or out as general case */
   /* SJM 10-14-08 - if require +change_port_type option should never happen */
  case DP_INOUT_DRVRS:
   /* SJM 10-14-08 - algorithm was wrong because if all in drivers tristated */
   /* (unconnected at this tick) because out and vice versa */
   /* if no active drivers need inout 'f' - input and output tristated */

   /* calc number of non tristated (connected) drvrs and set driving val */ 
   dp_set_cnt_driving_vals(&(active_in_drvnum), &(active_out_drvnum), dpcp,
    drvbi, np->n_stren);
   if (active_in_drvnum == 0 && active_out_drvnum == 0) 
    { valch = 'F'; st0 = 0; st1 = 0; break; }
   if (active_in_drvnum == 0) goto inout_out_only_state;
   if (active_out_drvnum == 0) goto inout_in_only_state;

   /* inout has hiconn and loconn drivers - combine separately and use tab */
   hiconn_v = 2;
   for (dpdrvp = dpcp->dp_outdrvs; dpdrvp != NULL; dpdrvp = dpdrvp->dpdrvnxt)
    {
     hiconn_v = __comb_1bitsts(np->ntyp, hiconn_v, dpdrvp->drv_val);
    }
   /* compute the lo conn driving value and strens */
   loconn_v = 2;
   for (dpdrvp = dpcp->dp_indrvs; dpdrvp != NULL; dpdrvp = dpdrvp->dpdrvnxt)
    {
     loconn_v = __comb_1bitsts(np->ntyp, loconn_v, dpdrvp->drv_val);
    }
   /* see LRM section 18.4.3.2 */
   /* case 1 - values are same */
   if ((hiconn_v & 3) == (loconn_v & 3)) 
    {
     /* small f because the drivers are present but tri-stated (z) */
     if (hiconn_v == 2) { valch = 'f'; st0 = 0; st1 = 0; }
     else 
      {
       comb_v = __comb_1bitsts(np->ntyp, loconn_v, hiconn_v);
  
       st0 = (comb_v >> 5) & 7;
       st1 = (comb_v >> 2) & 7;
       valch = dp_inoutvaltoch_tab[comb_v & 3];
      }
     break;
    }
   /* know values different - result is stronger stren */
   hi_v = hiconn_v & 3;
   lo_v = loconn_v & 3;

   /* hiconn is stronger 1 - loconn is weaker x or 0 */
   /* input side is high conn */
   if (((hiconn_v >> 5) & 7) > ((loconn_v >> 2) & 7))
    {
//AIV? - 10-11-08 FIXME - maybe need table for these hi/lo are symmetric
     /* case 1a: input (hiconn) stronger */
     /* high conn value 0 - stren it's 0 component */
     if (hi_v == 0) { valch = '0'; st0 = (hiconn_v >> 5) & 7; st1 = 0; }    
     /* high conn value 1 - stren it's 1 component */
     else if (hi_v == 1) { valch = '1'; st0 = 0; st1 = (hiconn_v >> 2) & 7; }  
     else
      {
       /* high conn value x - need stronger or same */
       valch = '?'; 
       if (((hiconn_v >> 5) & 7) >= ((hiconn_v >> 2) & 7))
        {
         /* hiconn 0 stren stronger */ 
         st0 = st1 = (hiconn_v >> 5) & 7;
        }
       else
        {
         /* hiconn 1 stren stronger */ 
         st0 = st1 = (hiconn_v >> 2) & 7;
        }
      }
    }
   else if (((hiconn_v >> 5) & 7) == ((loconn_v >> 2) & 7))
    {
     /* case 1b: strengths are the same */
     st0 = st1 = ((hiconn_v >> 5) & 7);
     if (hi_v == 0 && lo_v == 1) valch = 'A';
     else if (hi_v == 0 && lo_v == 3) valch = 'a'; 
     else if (hi_v == 1 && lo_v == 0) valch = 'B'; 
     else if (hi_v == 1 && lo_v == 3) valch = 'b'; 
     else if (hi_v == 3 && lo_v == 0) valch = 'C'; 
     else if (hi_v == 3 && lo_v == 1) valch = 'c'; 
    }
   else
    {
     /* case 1c: output (loconn) stronger */ 
     /* lo conn value 0 - stren it's 0 component */
     if (lo_v == 0) { valch = '0'; st0 = (loconn_v >> 5) & 7; st1 = 0; }    
     /* lo conn value 1 - stren it's 1 component */
     else if (lo_v == 1) { valch = '1'; st0 = 0; st1 = (loconn_v >> 2) & 7; }   
     else
      {
       /* low conn value x - need stronger or same */
       valch = '?'; 
       if (((loconn_v >> 5) & 7) >= ((loconn_v >> 2) & 7))
        {
         /* loconn 0 stren stronger */ 
         st0 = st1 = (loconn_v >> 5) & 7;
        }
       else
        {
         /* loconn 1 stren stronger */ 
         st0 = st1 = (loconn_v >> 2) & 7;
        }
      }
    }
   break;
  default: __case_terr(__FILE__, __LINE__);
 }
 *retst0 = st0;
 *retst1 = st1;
 return(valch);
}

/*
 * eval know max possible 1 drvr case stren input or inout dp value
 *
 * also depending on is input setting, for inout port with exactly one
 * hiconn (in) or loconn (out) driver
 */
static char eval_st_1drvr(int32 *retst0, int32 *retst1, struct net_t *np,
 int32 drvbi, t_midat *loc_idp, int32 is_input)
{
 char valch;
 byte *sbp;
 word32 v;

//AIV? 10-11-08 LOOKATME - is there a routine for this???
 if (np->n_isavec) 
  { sbp = (byte *) &(loc_idp[np->nva_ofs]); v = (word32) sbp[drvbi]; }
 else v = loc_idp[np->nva_ofs];

 /* SJM 09-30-08 - had stren extraction backward - st0 is high 3 bits */
 *retst0 = (v >> 5) & 7;
 *retst1 = (v >> 2) & 7;
 if (is_input) valch = dp_invaltoch_tab[v & 3];
 else valch = dp_outvaltoch_tab[v & 3];
 return(valch);
}

/*
 * eval know max possible 1 drvr non stren case input port
 *
 * also for inout ports with exactly 1 non tri-stated in drvr and no out drvr 
 * since uses if stmts input and output routines differ 
 */
static char eval_in_1drvr(int32 *retst0, int32 *retst1, struct net_t *np,
 int32 drvbi, t_midat *loc_idp)
{
 char valch;
 word32 av, bv, v;

//AIV? 10-11-08 LOOKATME - is there a routine for this???
 if (np->n_isavec)
  {
   av = rhsbsel_(&(loc_idp[np->nva_ofs]), drvbi);
   bv = rhsbsel_(&(loc_idp[np->nva_ofs + wlen_(np->nwid)]), drvbi);
   v = av | (bv << 1);
  }
 else v = loc_idp[np->nva_ofs];

 valch = 0;
 if (v == 0) { valch = 'D'; *retst0 = 6; *retst1 = 0; }  
 else if (v == 1) { valch = 'U'; *retst0 = 0; *retst1 = 6; }  
 else if (v == 2) { valch = 'Z'; *retst0 = 0; *retst1 = 0; }  
 else if (v == 3) { valch = 'N'; *retst0 = 6; *retst1 = 6; }
 else __case_terr(__FILE__, __LINE__);

 return(valch);
}

/*
 * eval know max possible 1 drvr non stren case output port
 *
 * also for inout ports with exactly 1 non tri-stated out drvr and no in drvr 
 * since uses if stmts input and output routines differ 
 */
static char eval_out_1drvr(int32 *retst0, int32 *retst1, struct net_t *np,
 int32 drvbi, t_midat *loc_idp)
{
 char valch;
 word32 av, bv, v;

//AIV? 10-11-08 LOOKATME - is there a routine for this???
 if (np->n_isavec)
  {
   av = rhsbsel_(&(loc_idp[np->nva_ofs]), drvbi);
   bv = rhsbsel_(&(loc_idp[np->nva_ofs + wlen_(np->nwid)]), drvbi);
   v = av | (bv << 1);
  }
 else v = loc_idp[np->nva_ofs];

 valch = 0;
 if (v == 0) { valch = 'L'; *retst0 = 6; *retst1 = 0; }  
 else if (v == 1) { valch = 'H'; *retst0 = 0; *retst1 = 6; }  
 else if (v == 2) { valch = 'T'; *retst0 = 0; *retst1 = 0; }  
 else if (v == 3) { valch = 'X'; *retst0 = 6; *retst1 = 6; }
 else __case_terr(__FILE__, __LINE__);

 return(valch);
}

/*
 * routine to count and set input and output driver driving values
 *  
 * know at least one possibly non tri-stated driver or not called
 * if any driver stren, then know all are
 *
 * SJM 10-11-08 - must get driver vtx itree loc from the xl style drvr
 * SJM 10-14-08 - for inputs and outputs could avoid one of the loops
 */
static void dp_set_cnt_driving_vals(int32 *num_indrvs, int32 *num_outdrvrs,
 struct dpctrl_t *dpcp, int32 drvbi, int32 is_st)
{
 word32 sval;
 struct dpdrvr_t *dpdrvp;
 decl_idp_locals_;

 *num_indrvs = *num_outdrvrs = 0;
 /* first find value for each driver both hiconn and loconn */
 save_idp_();
 /* first get driving values for in drivers - hiconns */
 for (dpdrvp = dpcp->dp_indrvs; dpdrvp != NULL; dpdrvp = dpdrvp->dpdrvnxt)
  {
   /* SJM 10-11-08 - must get driver vtx itree loc from the xl style drvr */ 
   __idp = (t_midat *) dpdrvp->dpd_itp->it_idp;

   if (is_st) sval = dp_ld_stdriver(drvbi, dpdrvp->dpd_npp);
   else sval = dp_ld_driver(drvbi, dpdrvp->dpd_npp);
   dpdrvp->drv_val = sval;
   if (sval != 2) (*num_indrvs)++;
  }
 for (dpdrvp = dpcp->dp_outdrvs; dpdrvp != NULL; dpdrvp = dpdrvp->dpdrvnxt)
  {
   /* SJM 10-11-08 - must get driver vtx itree loc from the xl style drvr */ 
   __idp = (t_midat *) dpdrvp->dpd_itp->it_idp;

   if (is_st) sval = dp_ld_stdriver(drvbi, dpdrvp->dpd_npp);
   else sval = dp_ld_driver(drvbi, dpdrvp->dpd_npp);
   dpdrvp->drv_val = sval;

   if (sval != 2) (*num_outdrvrs)++;
  }
 restore_idp_();
}

/*
 * load a stren npp driver and extract correct port net bit for dumpports 
 *
 * this must run in the idp context of the driver (i.e. the highconn for
 * input and the lowconn for ouputs)
 */
static word32 dp_ld_stdriver(int32 drvbi, struct net_pin_t *npp)
{
 int32 drvwid;
 word32 retval;
 struct xstk_t *xsp;
 byte *sbp;

 /* load driver onto new top of stack (this always pushes) */
 /* know rhs driver width will be changed to match port net's width exactly */
 switch ((byte) npp->npntyp) {
  case NP_CONTA: xsp = ld_stconta_driver(npp); break;
  case NP_TFRWARG: xsp = __ld_sttfrwarg_driver(npp); break;
  case NP_VPIPUTV: xsp = ld_stvpiputv_driver(npp); break;
  case NP_GATE: xsp = ld_stgate_driver(npp); break;
  /* these are up to highconn strength output port drivers */
  case NP_ICONN: xsp = ld_sticonn_up_driver(npp); break;
  case NP_PB_ICONN: xsp = ld_pb_sticonn_up_driver(npp); break;
  /* these are down to lowconn strength input port drivers */
  case NP_MDPRT: xsp = ld_stmodport_down_driver(npp); break;
  case NP_PB_MDPRT: xsp = ld_pb_stmodport_down_driver(npp); break;
  case NP_PULL: xsp = ld_stpull_driver(npp); break;
  /* TRAN impossible here */
  default: __case_terr(__FILE__, __LINE__); xsp = NULL;
 }
 drvwid = xsp->xslen/4;

 if (drvbi >= drvwid) retval = 2;
 else
  {
   sbp = (byte *) xsp->ap;
   retval = (word32) sbp[drvbi];
  }

 __pop_xstk();
 return(retval);
}

/*
 * load a non stren npp driver and extract correct port net bit for dumpports 
 *
 * this must run in the idp context of the driver (i.e. the highconn for
 * input and the lowconn for ouputs)
 */
static word32 dp_ld_driver(int32 drvbi, struct net_pin_t *npp)
{
 struct xstk_t *xsp;
 word32 av, bv, retval;

 /* this puts the driving value (normal rhs with rhs width) on stack */
 /* notice tran strength only so error if appears here */
 switch ((byte) npp->npntyp) {
  case NP_CONTA: xsp = __ld_conta_driver(npp); break;
  case NP_TFRWARG: xsp = __ld_tfrwarg_driver(npp); break;
  case NP_VPIPUTV: xsp = __ld_vpiputv_driver(npp); break;
  case NP_GATE: xsp = __ld_gate_driver(npp); break;
  /* these are up to highconn output port drivers */
  case NP_ICONN: xsp = __ld_iconn_up_driver(npp); break;
  case NP_PB_ICONN: xsp = __ld_pb_iconn_up_driver(npp); break;
  /* these are down to lowconn input port drivers */
  case NP_MDPRT: xsp = __ld_modport_down_driver(npp); break;
  case NP_PB_MDPRT: xsp = __ld_pb_modport_down_driver(npp); break;
  default: __case_terr(__FILE__, __LINE__); xsp = NULL; 
 }
 if (drvbi >= xsp->xslen) retval = 2;
 else
  {
   av = rhsbsel_(xsp->ap, drvbi);
   bv = rhsbsel_(xsp->bp, drvbi);
   retval = av | (bv << 1);
   if (retval != 2) retval |= (ST_STRVAL << 2);
  }
 __pop_xstk();
 return(retval);
}

/*
 * dump 1 port net from one inst of the possibly many associated with 1 file
 *
 * always dump strong stren x here but still depends on port type 
 */
static void bld1_xdpval(struct net_t *np, char *dvcodp)
{
 char xch, *chp;

 /* DBG remove -- */
 if (np->ntyp == N_EVENT) __misc_terr(__FILE__, __LINE__);
 if (np->ntyp == N_REAL) __misc_terr(__FILE__, __LINE__);
 /* --- */

 __cur_sofs = 0;
 addch_('p');
 if (np->iotyp == IO_IN) xch = 'N';
 else if (np->iotyp == IO_OUT) xch = 'X';
 else xch = '?';

 chp = alloca(np->nwid + 1);
 memset(chp, xch, np->nwid); 
 chp[np->nwid] = '\0';
 __adds(chp);
 addch_(' ');
 memset(chp, '6', np->nwid);
 chp[np->nwid] = '\0';
 __adds(chp);
 addch_(' ');
 __adds(chp);
 addch_(' ');
 __adds(dvcodp);
}

/*
 * flush a dumpports - empty buffer then do OS flush 
 */
extern void __my_dp_flush(struct dp_fildesc_t *fdescp)
{
 if (fdescp->dp_nxti > 0)
  {
   write(fdescp->dp_fd, fdescp->dp_buffer, fdescp->dp_nxti);
  }
 fdescp->dp_nxti = 0;
}

/*
 * routine to clean up dump ports - close all files and free dp fildesc tab
 * called from $reset (re-init to 0) and my exit 
 *
 * SJM 09-27-08 - must emit the EVCD file vcdclose to the end of each file
 */  
extern void __cleanup_dumpports(void) 
{
 int32 dpdi;
 struct dp_fildesc_t *fdescp;

 for (dpdi = 0; dpdi < __dp_fildesc_nxti; dpdi++)
  {
   fdescp = &(__dp_fildesc_tab[dpdi]);
   /* AIV 04/22/11 - can not run any time setup - therefore nothing to flush */
   /* rare but can happen - no dumpport has taken place then there is no file */
   if (fdescp->dp_fd == -1) continue;

   /* need to write the new evcd close section */
   __wr_vcdclose_section(fdescp);

   /* flush and close the file */
   __my_dp_flush(fdescp);
   __my_close(fdescp->dp_fd);
   __my_free(fdescp->dp_fnam, strlen(fdescp->dp_fnam) + 1);
   fdescp->dp_fnam = NULL;
   __my_free(fdescp->dp_buffer, DVBUFSIZ);
   fdescp->dp_buffer = NULL;
   free_dpinst_lst(fdescp->dpi_hdr);
   fdescp->dpi_hdr = NULL;

//AIV - LOOKATME 09-27-08
   /* this should be gone since removed at end of time step */
   if (fdescp->dp_chgnethdr != NULL) __misc_terr(__FILE__, __LINE__);
  }
 /* final step is freeing fixed sing fildesc tab */
 __my_free(__dp_fildesc_tab, MAX_DMPPRTS_FILES*sizeof(struct dp_fildesc_t)); 
}

/*
 * write the vcdclose section at end of only dumpports file(s)
 */  
extern void __wr_vcdclose_section(struct dp_fildesc_t *fdescp)
{
 sprintf(__xs2, "$vcdclose\n#%s\n$end\n", to_dvtimstr(__xs, __simtime));
 __adds(__xs2);
 dp_wr(fdescp, FALSE);
}

/*
 * ROUTINES TO BUILD THE DMP PORTS EVAL DATA STRUCTURE
 */

/*
 * build the dumpports eval data structure for one module
 *  
 * know some instance of this module needs all ports to be written to
 * dumpports file
 */  
static void bld_instel_dumpports_eval_ds(struct dpinstel_t *dpip)
{
 int32 ni, bi;
 struct net_t *np;
 t_midat *idp; 
 struct itree_t *itp;
 struct mod_t *imdp;
 struct dpctrl_t *dpcp;

 idp = dpip->dpinst_idp;
 itp = (struct itree_t *) idp[MD_ITP];
 imdp = (struct mod_t *) idp[MD_MDP];
 /* AIV 04/22/11 - can have zero ports here - really just user error will */
 /* now dump any values */
 /* DBG remove -- */
 if (imdp->mnnum == 0) __misc_terr(__FILE__, __LINE__);
 /* --- */ 

 /* this is an index for each net, only port nets non nil, points to p/b tab */
 dpip->net_dpctrl_tab = (struct dpctrl_t **)
  __my_malloc(imdp->mnnum*sizeof(struct dpctrl_t *));

 /* initialize the per net bit dp ctrl records */
 for (ni = 0, np = &(imdp->mnets[0]); ni < imdp->mnnum; ni++, np++)
  {
   if (np->iotyp == NON_IO)
    {
     dpip->net_dpctrl_tab[ni] = NULL;
     continue;
    }
   /* each bit needs possibility of different dump ports eval control record */
   dpip->net_dpctrl_tab[ni] = (struct dpctrl_t *)
    __my_malloc(np->nwid*sizeof(struct dpctrl_t));
   dpcp = dpip->net_dpctrl_tab[ni];
   for (bi = 0; bi < np->nwid; bi++)
    {
     init_1bit_dpctrl_rec(&(dpcp[bi]));
     dpcp[bi].dpc_np = np;
     dpcp[bi].dpc_bi = bi;
    }
  }

 /* now build the dpdrv lists */
 bld_1inst_dpctrl_lists(dpip, imdp);

 /* final calculate the eval type for each bit */
 for (ni = 0, np = &(imdp->mnets[0]); ni < imdp->mnnum; ni++, np++)
  {
   if (np->iotyp == NON_IO) continue;
   dpcp = dpip->net_dpctrl_tab[ni];
   for (bi = 0; bi < np->nwid; bi++)
    {
     set_1bit_dp_eval_type(np, &(dpcp[bi]));
    }
  }
}

/*
 * initialize one net bit's dump ports eval control record  
 */ 
static void init_1bit_dpctrl_rec(struct dpctrl_t *dpcp)
{
 dpcp->dp_eval_typ = DP_DRV_UNKN;
 dpcp->dp_indrvs = NULL;
 dpcp->dp_outdrvs = NULL;

 dpcp->dpc_np = NULL;
 dpcp->dpc_bi = -1;
}

/*
 * build the drivers highconn and loconn XL style driver lists for one
 * module
 *
 * assumes dp ctrl data structure initialized and this fills the in and out 
 * driver lists 
 *
 * SJM 10-08-08 FIXME - also need to somehow handle force/assign drivers
 */
static void bld_1inst_dpctrl_lists(struct dpinstel_t *dpip, struct mod_t *mdp)
{
 int32 ni, bi, vti, vtxnum, bi2, frbi, tobi, is_hiconn_in;
 struct net_t *np, *np2;
 struct net_pin_t *npp;
 struct xldlvtx_t *xldlvp;
 struct itree_t *itp, *vtx_itp;
 struct dpctrl_t *dpcp;
 char s1[RECLEN], s2[RECLEN], s3[RECLEN];

 itp = (struct itree_t *) dpip->dpinst_idp[MD_ITP];
 for (ni = 0, np = &(mdp->mnets[0]); ni < mdp->mnnum; ni++, np++)
  {
   if (np->iotyp == NON_IO) continue;

   for (bi = 0; bi < np->nwid; bi++)
    {
     /* DBG remove --- */ 
     if (__debug_flg)
      {
       __dbg_msg("&&& calculating xl style drivers of net %s bit %d in %s\n",
        np->nsym->synam, bi, __msg2_blditree(s1, itp));
      }
     /* --- */

     /* SJM 10-08-08 - must be sure glb table is empty */  
     __num_xldlvtxs = 0;
     /* 4th arg F for building table in fixed global mem of the bits */ 
     /* that drive the given net anywhere in the design */
     vtxnum = __bld_xl_drvld_vtxtab(np, bi, itp, FALSE);
     /* if no real (not iconn or mdports) drivers - lists empty */ 
     if (vtxnum == 0) continue;

     dpcp = &(dpip->net_dpctrl_tab[ni][bi]);
     for (vti = 0; vti < vtxnum; vti++)
      {
       xldlvp = __xldlvtxind[vti];

       /* DBG remove -- */
       if (xldlvp == NULL) __misc_terr(__FILE__, __LINE__);
       /* --- */
       np2 = xldlvp->dlnp;
       bi2 = xldlvp->dlbi;
       vtx_itp = xldlvp->dlitp; 

       for (npp = np2->ndrvs; npp != NULL; npp = npp->npnxt)
        {
         if (npp->npntyp != NP_GATE && npp->npntyp != NP_CONTA 
          && npp->npntyp != NP_PULL) continue;

         __get_bidnpp_sect(np2, npp, &(frbi), &(tobi));
         if (bi2 == -1 || (bi2 <= frbi && bi2 >= tobi))
          {
           /* range matches - add to list */
           if (drvr_netbit_vtx_is_hiconn(vtx_itp, itp)) is_hiconn_in = TRUE;
           else is_hiconn_in = FALSE;

           /* DBG remove -- */
           if (__debug_flg)
            {
             __dbg_msg(
              "$$$ inst %s xl drvr for %s net[%d] vtx %s[%d] in %s - %s drvr\n",  
              __msg2_blditree(s1, itp), np->nsym->synam, bi, np2->nsym->synam,
               bi2, __msg2_blditree(s3, vtx_itp), __to_npptyp(s2, npp));
             }
            /* --- */

           linkin_pb_npp_drvr(dpcp, vtx_itp, npp, bi2, is_hiconn_in);
          }
        }
       /* free the driving net/bit vertex */
       __my_free(xldlvp, sizeof(struct xldlvtx_t));
       __xldlvtxind[vti] = NULL;
      }
    }
  }
}

/*
 * return T if itree location of driving bit above dump port itree loc (inst) 
 */
static int32 drvr_netbit_vtx_is_hiconn(struct itree_t *vtx_itp,
 struct itree_t *dp_itp)
{
 struct itree_t *itp;

 for (itp = vtx_itp; itp != NULL; itp = itp->up_it)
  {
   /* SJM 11-14-08 - case 1 vtx in or under dumpports itree instance */  
   if (itp == dp_itp) return(FALSE);

   /* case 2: in or under dumpports hiconn (parent) - this is a hiconn */ 
   /* but not under the dumpports instance */
   if (itp == dp_itp->up_it) return(TRUE);
  }
 /* case 3 - some kind of XMR - illegal? */
 __case_terr(__FILE__, __LINE__);
 return(TRUE);
}

/*
 * link a per bit npp onto either hiconn input driver list or loconn output
 */
static void linkin_pb_npp_drvr(struct dpctrl_t *dpcp, struct itree_t *vtx_itp,
 struct net_pin_t *npp, int32 bi, int32 is_hiconn_in_drv)
{
 struct dpdrvr_t *dpdrvp;

 dpdrvp = (struct dpdrvr_t *) __my_malloc(sizeof(struct dpdrvr_t));
 init_dpdrv(dpdrvp);
 dpdrvp->drv_biti = bi;
 dpdrvp->dpd_npp = npp; 
 dpdrvp->dpd_itp = vtx_itp;

 /* think ok to put on front */
 if (is_hiconn_in_drv)
  {
   dpdrvp->dpdrvnxt = dpcp->dp_indrvs;
   dpcp->dp_indrvs = dpdrvp;
  }
 else
  {
   dpdrvp->dpdrvnxt = dpcp->dp_outdrvs;
   dpcp->dp_outdrvs = dpdrvp;
  }
}

/*
 * initialize a dp driver (holder of the npp/bit) element
 */
static void init_dpdrv(struct dpdrvr_t *dpdrvp)
{
 /* make the value an illegal stren x */
 dpdrvp->drv_val = ST_STRONGX;
 dpdrvp->drv_biti = -1;
 dpdrvp->dpd_npp = NULL;
 dpdrvp->dpdrvnxt = NULL;
}

/*
 * set the evaluation types for the dump ports value eval routines
 */
static void set_1bit_dp_eval_type(struct net_t *np, struct dpctrl_t *dpcp)
{
 int32 hiconn_drv_num, loconn_drv_num; 

 if (np->iotyp == IO_IN)
  {
   /* DBG remove -- */ 
   if (dpcp->dp_outdrvs != NULL) __misc_terr(__FILE__, __LINE__);
   /* --- */
   if (dpcp->dp_indrvs != NULL && dpcp->dp_indrvs->dpdrvnxt != NULL)
    {
     /* more than 1 driver for this input mod port bit */ 
     dpcp->dp_eval_typ = DP_IN_DRVRS;
    }
   /* no drivers same as one since just get value - no conflict possible */
   else dpcp->dp_eval_typ = DP_IN_1DRVR;
  }
 else if (np->iotyp == IO_OUT)
  {
   /* DBG remove -- */ 
   if (dpcp->dp_indrvs != NULL) __misc_terr(__FILE__, __LINE__);
   /* --- */
   if (dpcp->dp_outdrvs != NULL && dpcp->dp_outdrvs->dpdrvnxt != NULL)
    {
     /* more than 1 driver for this input mod port bit */ 
     dpcp->dp_eval_typ = DP_OUT_DRVRS;
    }
   /* no drivers same as one since just get value - no conflict possible */
   else dpcp->dp_eval_typ = DP_OUT_1DRVR;
  }
 else if (np->iotyp == IO_BID)
  {
   if (dpcp->dp_indrvs != NULL && dpcp->dp_indrvs->dpdrvnxt != NULL)
    hiconn_drv_num = 2;
   else hiconn_drv_num = 1; 
   if (dpcp->dp_outdrvs != NULL && dpcp->dp_outdrvs->dpdrvnxt != NULL)
    loconn_drv_num = 2;
   else loconn_drv_num = 1; 

   /* case 1: no hiconn (input flow) drivers */
   if (dpcp->dp_indrvs == NULL)
    {
     if (loconn_drv_num == 1) dpcp->dp_eval_typ = DP_INOUT_1DRVR;
     else if (loconn_drv_num == 2) dpcp->dp_eval_typ = DP_INOUT_DRVRS; 
     return;
    }
   /* case 1: no loconn (out flow) drivers */
   if (dpcp->dp_indrvs == NULL)
    {
     if (hiconn_drv_num == 1) dpcp->dp_eval_typ = DP_INOUT_1DRVR;
     else if (hiconn_drv_num == 2) dpcp->dp_eval_typ = DP_INOUT_DRVRS; 
     return;
    }
   /* all other case even if only 1 in and 1 out drivers still need */
   /* full both sides eval for inouts */
   dpcp->dp_eval_typ = DP_INOUT_DRVRS;
  }
}

/*
 * DUMPPORTS DEBUG ROUTINES
 */  

/*
 * DBG routine to dump one dumpports file descriptor
 *  
 * for dumpports always dump every port of selected itree inst, but
 * different insts of ports or different ports can go in different
 * files each one can be controlled separately
 */
static void dmp1_fildesc(struct dp_fildesc_t *fdescp) 
{
 struct dpinstel_t *dpip;

 __dbg_msg("++ FILDESC(%d) - name %s - func %d state %d dumplimit %d\n",
  fdescp - __dp_fildesc_tab, fdescp->dp_fnam, fdescp->dp_func,
  fdescp->dp_state, fdescp->dp_dumplimit_size); 
 __dbg_msg("   file size %d emited %d dp_fd %d nxti %d lpos %d slot bits %x\n",
  fdescp->dp_file_size, fdescp->dp_time_emitted, fdescp->dp_fd, 
  fdescp->dp_nxti, fdescp->dp_outlinpos, fdescp->dp_slotend_action);

 for (dpip = fdescp->dpi_hdr; dpip != NULL; dpip = dpip->dpinxt)
  {
   dmp1_dpinstel(dpip);
  }
}

/*
 * dump one dumpports instance element
 */
static void dmp1_dpinstel(struct dpinstel_t *dpip)
{
 int32 ni, pnetnum, bi;
 struct itree_t *itp;
 struct mod_t *mdp;
 struct net_t *np;
 struct dpctrl_t *dpcp;

 itp = (struct itree_t *) dpip->dpinst_idp[MD_ITP];
 mdp = (struct mod_t *) dpip->dpinst_idp[MD_MDP];
 pnetnum = 0;
 for (ni = 0, np = &(mdp->mnets[0]); ni < mdp->mnnum; ni++, np++)
  {
   if (np->iotyp != NON_IO) pnetnum++;
  }
 __dbg_msg("++ DP INSTEL ALL PORTS (%s)- fdesc %d - %d port nets\n",
  __msg2_blditree(__xs, itp), dpip->dpi_fdescp - __dp_fildesc_tab, pnetnum);
 for (ni = 0, np = &(mdp->mnets[0]); ni < mdp->mnnum; ni++, np++)
  {
   if (np->iotyp != NON_IO)
    {
     for (bi = 0; bi < np->nwid; bi++)
      {
       dpcp = &(dpip->net_dpctrl_tab[ni][bi]);

       /* DBG remove -- */
       if (dpcp->dpc_np != np) __misc_terr(__FILE__, __LINE__);
       if (dpcp->dpc_bi != bi) __misc_terr(__FILE__, __LINE__);
       /* --- */

       /* DBG remove --- */
       if (__debug_flg) dmp1_dpctrl_rec(dpcp, mdp, np, bi);
       /* --- */
      }
    }
   else
    {
     if (dpip->net_dpctrl_tab[ni] != NULL) __misc_terr(__FILE__, __LINE__);
    }
  }
}

/*
 * DBG routine to dump one dp ctrl record
 */
static void dmp1_dpctrl_rec(struct dpctrl_t *dpcp, struct mod_t *mdp,
 struct net_t *np, int32 bi)
{
 struct dpdrvr_t *dpdrvp;

 __dbg_msg("++ DUMPPORTS - eval type %s from net %s bit %d:\n",
  dp_evaltyp_to_str(__xs, dpcp->dp_eval_typ), np->nsym->synam, bi); 
 /* dump input (HICONN) drivers first */
 if (dpcp->dp_indrvs == NULL) __dbg_msg("   - No input (HICONN) drivers.\n"); 
 else
  {
   /* DJM 10/10/08 - this was backwards was in drvs too */
   for (dpdrvp = dpcp->dp_indrvs; dpdrvp != NULL; dpdrvp = dpdrvp->dpdrvnxt)
    {
     __dbg_msg("   ++ input (HICONN) driver value %s select bit %d in %s:\n",
      __to_vvstnam(__xs, dpdrvp->drv_val), dpdrvp->drv_biti,
      __msg2_blditree(__xs2, dpdrvp->dpd_itp));
     __dmp1_nplstel(mdp, np, dpdrvp->dpd_npp);
    }
  }
 /* then output (LOCONN) drivers */
 if (dpcp->dp_outdrvs == NULL) __dbg_msg("   - No output (LOCONN) drivers.\n"); 
 else
  {
   for (dpdrvp = dpcp->dp_outdrvs; dpdrvp != NULL; dpdrvp = dpdrvp->dpdrvnxt)
    {
     __dbg_msg(
      "   ++ output (LOCONN) driver value %s select bit %d in %s:\n",
      __to_vvstnam(__xs, dpdrvp->drv_val), dpdrvp->drv_biti,
      __msg2_blditree(__xs2, dpdrvp->dpd_itp));  
     __dmp1_nplstel(mdp, np, dpdrvp->dpd_npp);
    }
  }
}

/*
 * convert a dumpports control eval type to a string 
 */  
static char *dp_evaltyp_to_str(char *s, int32 eval_typ)
{
 switch (eval_typ) {
  case DP_DRV_UNKN:
   strcpy(s, "DP_DRV_UNKN");
   break;
  case DP_IN_1DRVR:
   strcpy(s, "DP_IN_1DRVR");
   break;
  case DP_IN_DRVRS:
   strcpy(s, "DP_IN_DRVRS");
   break;
  case DP_OUT_1DRVR:
   strcpy(s, "DP_OUT_1DRVR");
   break;
  case DP_OUT_DRVRS:
   strcpy(s, "DP_OUT_DRVRS");
   break;
  case DP_INOUT_1DRVR:
   strcpy(s, "DP_INOUT_1DRVR");
   break;
  case DP_INOUT_DRVRS:
   strcpy(s, "DP_INOUT_DRVRS");
   break;
  default: __case_terr(__FILE__, __LINE__);
 }
 return(s);
}


// AJB: added to remove $ uniquifier for parameterized modules

static const char *fst_rmv_dollar_module_name(const char *s)
{
static char namefix[IDLEN + 1];

char *c = strchr(s, '$');
if((!c) || ((c-s) > IDLEN) || (c==s))
	{
	return(s);
	}
	else
	{
	memcpy(namefix, s, c-s);
	namefix[c-s] = 0;
	return(namefix);
	}
}


// AJB : add var direction for enhanced SST filtering
static enum fstVarDir fst_dir_type(int32 iotyp)
{
 switch ((byte) iotyp) {
  case IO_IN: return(FST_VD_INPUT);
  case IO_OUT: return(FST_VD_OUTPUT);
  case IO_BID: return(FST_VD_INOUT);
  case IO_UNKN:
  case NON_IO: return(FST_VD_IMPLICIT);
  default: __case_terr(__FILE__, __LINE__);
 }
 return(-1);
}

