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
 * module to implement pli acc routines
 */

/*
 * CONVENTION: assumption here is that vpi_ objects and acc_ objects
 * are all pointers to struct h_t and can be cast between each other 
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
#include "veriuser.h"
#include "cv_veriuser.h"
#include "acc_user.h"
#include "cv_acc_user.h"

/* LOOKATME - maybe move to include file */
#define ACCSTRBUFSIZ 65536    /* size of reused str buf (must be 4k) */   

#define ACCMAPTOMIP_MAX 0
#define ACCMAPTOMIP_MIN 1
#define ACCMAPTOMIP_LAST 2

#define ACCTOHIZ_AVG 0
#define ACCTOHIZ_MAX 1
#define ACCTOHIZ_MIN 2
#define ACCTOHIZ_FROMUSER 3

struct vpi_to_acc_t {
 int32 vpiotyp;
 int32 acc_otyp;
};

struct accnam_t {
 char *accnam;
 int32 accval;
};

/* two way list (so can release) of active acc iterators */
struct acciter_t {
 struct h_t *aiter;
 struct acciter_t *aiternxt;
 struct acciter_t *aiterprev;
};

/* user data field for vpi_ val change call backs with acc_ vcl record */
struct vclrec_t {
 unsigned vclflg : 8;         /* user passed vcl flag */
 unsigned vcl_oldstval : 8;   /* old stren val not vpi for chg of val only */
 unsigned vcl_reason : 8;     /* object determined change reason */
 handle vclobj;               /* acc_ handle of object vcl on */
 int32 (*vcl_cb_rtn)();       /* acc_ vcl call back routine */
 char *vcl_udata;             /* user's user data (not vpi_ cb) */
 struct cbrec_t *vclcbp;      /* internal cver cbrec */
};

/* internal acc varaible declarations */ 
char *__acc_strbuf;           /* ptr to reused acc_ str buf */ 
int32 __acc_strbuf_nxti;      /* next free ndx - gets rewound */
int32 __acc_open;             /* T => acc initialize routine called */
int32 __acc_scope_set;        /* T => acc scope changed from call tf inst */
vpiHandle __acc_scope_vpiobj; /* currently set acc_ scope as vpi objec */

/* need separate work tables for acc_ since sometimes call vpi iterators */
/* that may reuse normal ith word32 tables */ 
int32 __aithtsiz;             /* size of acc work handle table */
struct h_t **__aithptab;      /* and the work ptr to handle tab */
int32 __aithtsiz2;            /* size of acc 2nd work handle table */
struct h_t **__aithptab2;     /* 2nd work ptr tab for in subtree handles */

/* indexed by vpi type table of active acc iters (next and collect) */
struct acciter_t **__aiter_tab; /* table by vpi type of acc next iters */
struct acciter_t *__last_aiter; /* for count/collect need last */
struct acciter_t *__aiter_freelst;
struct acciter_t *__aiter_accnxt_list; /* list for all acc next (no type) */

/* configure parameter variables - see P1364 acc LRM chapter */
int32 __acc_pathdelaycount;
char *__acc_pathdelimstr;
int32 __acc_displayerrors;
int32 __acc_defaultattr0;
int32 __acc_tohizdelay;
int32 __acc_enableargs_pth;
int32 __acc_enableargs_tchk;
int32 __acc_enableargs_setscope;
int32 __acc_displaywarnings;
char *__acc_developmentversion;
int32 __acc_maptomipd;
int32 __acc_mintypmaxdelays;

/* declaration (definition) of acc_user variables */
bool acc_error_flag;

/* acc extern prototypes */
extern bool acc_append_delays(handle object, ...);
extern bool acc_append_pulsere(handle object, double val1, double val1x, ...);
extern void acc_close(void);
extern handle *acc_collect(handle (*p_next_routine)(), handle scope_object,
 int32 *aof_count);
extern bool acc_compare_handles(handle h1, handle h2);
extern int32 acc_count(handle (*next_function)(), handle object_handle);
extern bool acc_configure(int32 item, char *value);
extern int32 acc_fetch_argc(void);
extern void **acc_fetch_argv(void);
extern double acc_fetch_attribute(handle object, ...);
extern int32 acc_fetch_attribute_int(handle object, ...);
extern char *acc_fetch_attribute_str(handle object, ...);
extern char *acc_fetch_defname(handle object_handle);
extern int32 acc_fetch_delay_mode(handle object_p);
extern bool acc_fetch_delays(handle object, ...);
extern int32 acc_fetch_direction(handle object_handle);
extern int32 acc_fetch_edge(handle acc_object);
extern char *acc_fetch_fullname(handle object_handle);
extern int32 acc_fetch_fulltype(handle object_h);
extern int32 acc_fetch_index(handle object_handle);
extern double acc_fetch_itfarg(int32 n, handle tfinst);
extern int32 acc_fetch_itfarg_int(int32 n, handle tfinst);
extern char *acc_fetch_itfarg_str(int32 n, handle tfinst);
extern int32 acc_fetch_location(p_location location_p, handle object);
extern char *acc_fetch_name(handle object_handle);
extern int32 acc_fetch_paramtype(handle param_p);
extern double acc_fetch_paramval(handle param);
extern int32 acc_fetch_polarity(handle path);
extern int32 acc_fetch_precision(void);
extern bool acc_fetch_pulsere(handle path_p, double *val1r,
 double *val1e, ...);
extern int32 acc_fetch_range(handle node, int32 *msb, int32 *lsb);
extern int32 acc_fetch_size(handle obj_h);
extern double acc_fetch_tfarg(int32 n);
extern int32 acc_fetch_tfarg_int(int32 n);
extern char *acc_fetch_tfarg_str(int32 n);
extern void acc_fetch_timescale_info(handle obj,
 p_timescale_info aof_timescale_info);
extern int32 acc_fetch_type(handle object_handle);
extern char *acc_fetch_type_str(int32 type);
extern char *acc_fetch_value(handle object_handle, char *format_str,
 p_acc_value acc_value_p);
extern void acc_free(handle *array_ptr);
extern handle acc_handle_by_name(char *inst_name, handle scope_p);
extern handle acc_handle_condition(handle obj);
extern handle acc_handle_conn(handle term_p);
extern handle acc_handle_datapath(handle path);
extern handle acc_handle_hiconn(handle port_ref);
extern handle acc_handle_interactive_scope(void);
extern handle acc_handle_itfarg(int32 n, handle tfinst);
extern handle acc_handle_loconn(handle port_ref);
extern handle acc_handle_modpath(handle mod_p, char *pathin_name,
 char *pathout_name, ...);
extern handle acc_handle_notifier(handle tchk);
extern handle acc_handle_object(char *object_name);
extern handle acc_handle_parent(handle object_p);
extern handle acc_handle_path(handle source, handle destination);
extern handle acc_handle_pathin(handle path_p);
extern handle acc_handle_pathout(handle path_p);
extern handle acc_handle_port(handle mod_handle, int32 port_num);
extern handle acc_handle_scope(handle object);
extern handle acc_handle_simulated_net(handle net_h);
extern handle acc_handle_tchk(handle mod_p, int32 tchk_type,
 char *arg1_conn_name, int32 arg1_edgetype, ...);
extern handle acc_handle_tchkarg1(handle tchk);
extern handle acc_handle_tchkarg2(handle tchk);
extern handle acc_handle_terminal(handle gate_handle, int32 terminal_index);
extern handle acc_handle_tfarg(int32 n);
extern handle acc_handle_tfinst(void);
extern bool acc_initialize(void);
extern handle acc_next(int32 *type_list, handle h_scope, handle h_object);
extern handle acc_next_bit(handle vector, handle bit);
extern handle acc_next_cell(handle scope, handle cell);
extern handle acc_next_cell_load(handle net_handle, handle load);
extern handle acc_next_child(handle mod_handle, handle child);
extern handle acc_next_driver(handle net, handle driver);
extern handle acc_next_hiconn(handle port, handle hiconn);
extern handle acc_next_input(handle path, handle pathin);
extern handle acc_next_load(handle net, handle load);
extern handle acc_next_loconn(handle port, handle loconn);
extern handle acc_next_modpath(handle mod_p, handle path);
extern handle acc_next_net(handle mod_handle, handle net);
extern handle acc_next_output(handle path, handle pathout);
extern handle acc_next_parameter(handle module_p, handle param);
extern handle acc_next_port(handle ref_obj_p, handle port);
extern handle acc_next_portout(handle mod_p, handle port);
extern handle acc_next_primitive(handle mod_handle, handle prim);
extern handle acc_next_scope(handle ref_scope_p, handle scope);
extern handle acc_next_specparam(handle module_p, handle sparam);
extern handle acc_next_tchk(handle mod_p, handle tchk);
extern handle acc_next_terminal(handle gate_handle, handle term);
extern handle acc_next_topmod(handle topmod);
extern bool acc_object_of_type(handle object, int32 type);
extern bool acc_object_in_typelist(handle object, int32 *type_list);
extern int32 acc_product_type(void);
extern char *acc_product_version(void);
extern int32 acc_release_object(handle obj);
extern bool acc_replace_delays(handle object, ...);
extern bool acc_replace_pulsere(handle object, double val1r,
 double val1x, ...);
extern void acc_reset_buffer(void);
extern bool acc_set_interactive_scope(handle scope, int32 callback_flag);
extern bool acc_set_pulsere(handle path_p, double val1r, double val1e);
extern char *acc_set_scope(handle object, ...);
extern int32 acc_set_value(handle obj, p_setval_value setval_p,
 p_setval_delay delay_p);
extern void acc_vcl_add(handle object_p, int32 (*consumer)(), char *user_data,
 int32 vcl_flags);
extern void acc_vcl_delete(handle object_p, int32 (*consumer)(),
 char *user_data, int32 vcl_flags);
extern char *acc_version(void);
extern int32 __primtermprop_vpiget(struct h_t *, int32);
extern char *__to_sytyp(char *, word32);
extern struct sy_t *__get_sym(char *, struct symtab_t *);
extern char * __get_eval_cstr(struct expr_t *, int32 *);

/* local prototypes */
static int32 str_truefalse(char *);
static int32 legal_delimstr(char *);
static struct h_t *find_acc_attr_param(struct h_t *, char *, char *);
static struct net_t *tryfnd_param(char *, struct symtab_t *, char *, char *); 
static void init_acc_config(void);
static int32 bld_accnext_iter(int32 *, handle);
static int32 nd_modscope(struct h_t *);
static int32 nd_anyscope(struct h_t *);
static int32 cellinst_addto_iter(vpiHandle, int32, int32);
static void acc_internal_itfree(struct h_t *);
static int32 var_addto_iter(vpiHandle, int32, int32);
static int32 param_addto_iter(vpiHandle, int32, int32);
static int32 prim_addto_iter(vpiHandle, int32, int32, int32);
static handle portbit_accnext(handle, handle);
static void linkout_aiter(struct acciter_t *, int32, int32);
static void linkout_accnext_aiter(struct acciter_t *);
static handle netbit_accnext(handle, handle);
static struct acciter_t *find_aiter_rec(struct acciter_t *, struct h_t *); 
static vpiHandle bld_acc_cells_iter(struct h_t *);
static int32 collect_loc_insts(struct h_t *);
static int32 addto_acc_cells_iter(struct h_t *, int32, int32);
static handle do_acc_next_ld_drv(char *, handle, handle);
static int32 map_acc_delaymode_to_vpi(int32);
static char *get_acc_delmode_nam(char *, int32);
static int32 fill_vpival_fromacc(struct t_vpi_value *, struct t_setval_value *);
static int32 chk_add_del_vclobj(char *, struct h_t **, int32 (*)(), char *);
static int32 set_vcl_reason(struct net_t *, int32);
static struct vclrec_t *findmatch_net_vcl_dce(struct h_t *, int32 (*)(), char *);
static struct vclrec_t *findmatch_term_vcl_dce(struct h_t *, int32 (*)(),
 char *);
static int32 exec_acc_vclcb(struct t_cb_data *);
static int32 exec_acc_gateout_vclcb(struct t_cb_data *);
static int32 map_to_accvclval(word32);
static int32 map_vpi_to_accvclval(word32);
static int32 map_vpi_to_accval(word32);
static int32 map_acc_to_vpival(word32);
static int32 map_vpi_to_accstren(word32);
static vpiHandle bld_cell_load_iter(struct h_t *);
static vpiHandle bld_driver_iter(struct h_t *);
static handle do_acc_next_hilo_conn(char *, handle, handle, int32);
static vpiHandle bld_load_iter(struct h_t *);

static vpiHandle rem_ins_from_iter(struct mod_t *, vpiHandle); 

static char *add_accstrbuf(char *);
static char *get_cfgconst_nam(char *, int32);
static struct vpi_to_acc_t *get_acc_typerec(struct h_t *);
static vpiHandle get_acc_current_systf(char *);
static int32 get_systf_acc_expr_val(int32, struct expr_t *, s_vpi_value *,
 struct h_t *, char *);
static int32 fr_accfmt_to_vpifmt(int32);
static char *to_accfmtnam(char *, int32);
static int32 copy_vpival_to_accval(s_setval_value *, s_vpi_value *, int32);
static handle get_systf_accargobj(struct h_t *, int32, struct expr_t *, char *);
static int32 get_acc_fulltype(vpiHandle, struct vpi_to_acc_t *);
static char *get_accnam(int32);
static void acc_not_sim_err(char *);
static int32 validate_acc_handle(char *, struct h_t *); 
extern int32 __validate_otyp(word32);
static char *to_acc_onam(char *, word32);
static void wrong_nxtobj_error(char *, int32, int32);
static struct acciter_t *alloc_aiter(void);
static void init_aiter(struct acciter_t *);
static handle do_acc_child_topmod(char *, handle);
static int32 exec_acc_set_delays(struct h_t *, int32, va_list);

/* extern prototypes (maybe defined in this module) */
extern char *__my_malloc(size_t);
extern char *__my_realloc(void *, size_t, size_t);
extern void __my_free(void *, size_t);
extern char *__to_vpionam(char *, word32);
extern char *__msg_idp_blditree(char *, t_midat *, struct task_t *);
extern char *__msg2_idp_blditree(char *, t_midat *);
extern vpiHandle __mk_exprclass_handle(struct expr_t *, t_midat *, 
 struct task_t *);
extern char *__to_vvstnam(char *, word32);
extern int32 __map_frvpi_stren(int32);
extern vpiHandle __mk_handle(word32, void *, t_midat *, struct task_t *);
extern void __free_iterator(vpiHandle);
extern word32 __to_vpi_tasktyp(word32);
extern word32 __gate_to_vpiprimtyp(struct gate_t *);
extern void __bld_vpi_argv(void);
extern void __init_hrec(struct hrec_t *);
extern void __grow_acc_hptab(int32);
extern void __grow_acc_hptab2(int32);
extern char *__to_timstr(char *, word64 *);
extern struct pviter_t *__alloc_empty_iter(int32, vpiHandle *);
extern void __iter_fill_with_empty(struct pviter_t *);
extern void __cberror_fill_einfo(int32, int32, char *, char *, int32);
extern void __vpi_error_trycall(void);
extern word32 __map_tovpi_stren(word32);
extern int32 __v64_to_real(double *, word64 *);
extern void __free_hp(struct h_t *); 
extern void __call_misctfs_scope(void);
extern int32 __my_vpi_chk_error(void);
extern int32 __chk_showobj(struct h_t *, int32 *, int32 *);
extern struct h_t *__get_hp_from_freelst(void);
extern struct hrec_t *__get_hrec_from_freelst(void);
extern struct h_t *__get_new_hp_handle(void);

/* misc extern prototypes */
extern void __pv_terr(int32, char *, ...);
extern void __my_fprintf(FILE *, char *, ...);
extern void __my_vfprintf(FILE *, char *, va_list, va_list);

extern void __acc_err(int32, char *fmt, ...);
extern void __acc_sferr(int32, char *fmt, ...);
extern void __acc_warn(int32, char *fmt, ...);
extern void __acc_sfwarn(int32, char *, ...);
extern void __acc_terr(char *, int32);
extern void __acc_vpi_terr(char *, int32);
 
static struct vpi_to_acc_t vpi_to_acc[];

/* extern word32 __masktab[]; */

/*
 * EXTRA ACC INTIALIZATION ROUTINES
 */

/*
 * initialize acc when Cver starts (not after acc close)
 *
 * cver acc_ setup during simulation startup - acc_initialize and 
 * acc_close not needed - acc_close does free all handles
 *
 * LOOKATME - is an error call back needed
 */
extern void __init_acc(void)
{
 int32 aii;

 __acc_open = FALSE;
 acc_error_flag = FALSE;
 __acc_scope_set = FALSE;
 __acc_scope_vpiobj = NULL;
 __aiter_freelst = NULL;

 /* set up string buffer */
 if (__acc_strbuf == NULL) __acc_strbuf = __my_malloc(ACCSTRBUFSIZ);
 __acc_strbuf_nxti = 0; 

 /* always setup acc_next tables */ 
 __aiter_tab = (struct acciter_t **)
  __my_malloc((TOPVPIVAL + 1)*(sizeof(struct acciter_t *)));
 for (aii = 0; aii <= TOPVPIVAL; aii++) __aiter_tab[aii] = NULL;
 __last_aiter = NULL;
 __aiter_accnxt_list = NULL;

 __aithtsiz = 0;
 __aithptab = NULL;
 __aithtsiz2 = 0;
 __aithptab2 = NULL;

 /* must call init acc config in case user doesn't */ 
 init_acc_config();
}

/*
 * ACC_ ROUTINES IN ALPHABETICAL ORDER
 */

/*
 * append (add to) delays - acc style just wrapper for vpi put delays
 * with append flag set
 */
/*VARARGS*/
extern bool acc_append_delays(handle object, ...)
{
 int32 rv;
 va_list va;

 va_start(va, object);
 rv = exec_acc_set_delays((struct h_t *) object, TRUE, va);
 va_end(va);
 return(rv);
}

/*
 * appende pulse handling limits
 * notice these never array form 
 *
 * FIXME - simulator needs to support these
 */
/*VARARGS*/
extern bool acc_append_pulsere(handle object, double val1, double val1x, ...)
{
 struct h_t *hp;
 struct hrec_t *hrp;
 
 acc_error_flag = FALSE;

 hp = (struct h_t *) object; 
 if (!validate_acc_handle("acc_append_pulsere", hp)) return(0); 
 hrp = hp->hrec;
 if (hrp->htyp != vpiModPath && hrp->htyp != vpiPort
  && hrp->htyp != vpiPortBit)  
  {
   __acc_err(1764, "acc_append_pulsere: object %s illegal - path required",
    to_acc_onam(__wrks1, hrp->htyp));
   return(0);
  }
 __acc_warn(2052,
  "acc_append_pulsere no effect - pulse limits not stored by tool");
 return(1);
}

/*
 * close acc - end acc routines to not interfere with other acc apps 
 */
extern void acc_close(void)
{
 if (!__acc_open)
  {
   __acc_warn(2047, "acc_close: acc_initialize was not called");
  }

 /* reset string buffer */
 /* LOOKATME - probably not needed */
 __acc_strbuf_nxti = 0;
 
 /* reset acc configuration parameters to defaults */
 init_acc_config();
 __acc_open = FALSE;
 acc_error_flag = FALSE;
 /* LOOKATME - must leave all next state to match XL */
 /* LOOKATME - more to do??? */
}

/*
 * collect iterator into an array of handle (outside of iterator)
 *
 * uses normal next object with nil to build iterator 
 * finds iterator from last var, then copies into array
 * finally frees iterator
 *
 * need fence NULL at end so know how many to free
 * array of handles has no place to store size
 */
extern handle *acc_collect(handle (*p_next_routine)(), handle scope_object,
 int32 *aof_count)
{
 int32 hi, isize;
 struct h_t *hp, *hp2, *hp3, *hp4;
 struct acciter_t *aip;
 struct pviter_t *iterp; 
 vpiHandle *htabref;

 acc_error_flag = FALSE;

 hp = (struct h_t *) scope_object;
 if (hp != NULL)
  { if (!validate_acc_handle("acc_collect", hp)) return(NULL); }

 if (p_next_routine == acc_next_topmod)
  {
   __acc_err(1995,
    "acc_collect: acc_next_topmod illegal p_next_routine - use acc_next_child with NULL mod_handle"); 
   return(NULL);
  }

 /* get first which builds iterator */
 hp2 = (struct h_t *) (*(p_next_routine))(scope_object, NULL);
 /* will always return nil on error and emit error message */ 
 if (hp2 == NULL) return(NULL);

 /* know iterator just constructed always pointed to by this */
 aip = __last_aiter;
 hp3 = aip->aiter;
 iterp = hp3->hrec->hu.hiterp;
 isize = iterp->numhs;
 htabref = (vpiHandle *) __my_malloc((isize + 1)*sizeof(vpiHandle));
 /* need to copy handles because may need to copy non bith exprs */

 for (hi = 0; hi < isize; hi++)
  {
   __acc_vpi_erroff = TRUE;
   hp4 = (struct h_t *) vpi_copy_object((vpiHandle) iterp->scanhptab[hi]);
   htabref[hi] = (vpiHandle) hp4;
   /* this access error vpi_ error info and turns off vpi error cbs */  
   if (__my_vpi_chk_error())
    {
     __acc_err(1953, "acc_collect error building collected handle array");
     __my_free(htabref, isize*sizeof(vpiHandle));
     htabref = NULL;
     *aof_count = 0;
     goto do_free;
    }
  }
 htabref[isize] = NULL;

do_free:
 /* LOOKATME - here think always must free - guts copied no longer needed */
 linkout_aiter(aip, hp2->hrec->htyp, FALSE);
 *aof_count = isize;
 return((handle *) htabref);
}

/*
 * compare acc handle that are really just vpi_ objects
 */
extern bool acc_compare_handles(handle h1, handle h2)
{
 int32 rv;
 struct h_t *hp1, *hp2; 

 acc_error_flag = FALSE;

 hp1 = (struct h_t *) h1; 
 hp2 = (struct h_t *) h2; 
 if (!validate_acc_handle("acc_compare_handles(first)", hp1))
  return(FALSE); 
 if (!validate_acc_handle("acc_compare_handles(second)", hp2))
  return(FALSE); 

 __acc_vpi_erroff = TRUE;
 rv = vpi_compare_objects((vpiHandle) h1, (vpiHandle) h2);

 /* this access error vpi_ error info and turns off vpi error cbs */  
 if (__my_vpi_chk_error())
  {
   __acc_err(1954,
    "acc_compare_handles error during compare (handles %s or %s corrupted?)",
    to_acc_onam(__wrks1, hp1->hrec->htyp),
    to_acc_onam(__wrks2, hp2->hrec->htyp));
   return(FALSE);
  }
 return(rv);
}

/*
 * configure acc configureation parameter to value value 
 */
extern bool acc_configure(int32 item, char *value)
{
 int32 boolval, dnum;

 acc_error_flag = FALSE;
 switch (item) {
  case accDefaultAttr0:
   if ((boolval = str_truefalse(value)) == -1)
    {
bad_true_false:
     __acc_err(1950,
      "acc_configure configuration item %s %s illegal value - must be \"true\" or \"false\"",
      get_cfgconst_nam(__xs, item), value);
     return(FALSE);
    }
   __acc_defaultattr0 = boolval;
   break;
  case accDevelopmentVersion:
   if (__acc_developmentversion != NULL)
    __my_free(__acc_developmentversion, strlen(__acc_developmentversion) + 1);
   __acc_developmentversion = __my_malloc(strlen(value) + 1);
   strcpy(__acc_developmentversion, value);
   break;
  case accDisplayErrors:
   if ((boolval = str_truefalse(value)) == -1) goto bad_true_false;
   __acc_displayerrors = boolval;
   break;
  case accDisplayWarnings:
   if ((boolval = str_truefalse(value)) == -1) goto bad_true_false;
   __acc_displaywarnings = boolval;
   break;
  case accEnableArgs:
   if (strcmp(value, "acc_handle_modpath") == 0) __acc_enableargs_pth = TRUE;
   else if (strcmp(value, "no_acc_handle_modpath") == 0)
     __acc_enableargs_pth = FALSE;
   else if (strcmp(value, "acc_handle_tchk") == 0)
    __acc_enableargs_tchk = TRUE;
   else if (strcmp(value, "no_acc_handle_tchk") == 0)
    __acc_enableargs_tchk = FALSE;
   else if (strcmp(value, "acc_set_scope") == 0)
    __acc_enableargs_setscope = TRUE;
   else if (strcmp(value, "no_acc_set_scope") == 0)
    __acc_enableargs_setscope = FALSE;
   else
    {
     __acc_err(1943,
      "acc_configure accEnableArgs configuration value %s illegal",
      value);
     return(FALSE);
    }
   break;
  case accMapToMipd:
   if (strcmp(value, "max") == 0) __acc_maptomipd = ACCMAPTOMIP_MAX;
   else if (strcmp(value, "min") == 0) __acc_maptomipd = ACCMAPTOMIP_MIN;
   else if (strcmp(value, "latest") == 0) __acc_maptomipd = ACCMAPTOMIP_LAST;
   else
    {
     __acc_err(1943,
      "acc_configure accMapToMipd configuration value %s illegal", value);
     return(FALSE);
    }
   break;
  case accMinTypMaxDelays:
   if ((boolval = str_truefalse(value)) == -1) goto bad_true_false;
   if (boolval)
    {
     __acc_warn(2051,
      "acc_configure accMinTypMaxDelays same delay for all three - option selects the one value");
    }
   __acc_mintypmaxdelays = boolval;
   break;
  case accPathDelayCount:
   if (sscanf(value, "%d", &dnum) != 1)
    {
bad_delcnt:
     __acc_err(1943,
      "acc_configure accPathDelayCount configuration value %s illegal - one of \"1\", \"2\", \"3\", \"6\", \"12\" required",
      value);
     return(FALSE);
    }
   if (dnum != 1 && dnum != 2 && dnum != 3 && dnum != 6 && dnum != 12)
    goto bad_delcnt;
   __acc_pathdelaycount = dnum;
   break;
  case accPathDelimStr:
   if (!legal_delimstr(value))
    {
     __acc_err(1945,
      "acc_configure accPathDelimStr configuration value %s illegal Verilog identifier",
      value);
     return(FALSE);
    }
   if (__acc_pathdelimstr != NULL)
    __my_free(__acc_pathdelimstr, strlen(__acc_pathdelimstr) + 1);
   __acc_pathdelimstr = __my_malloc(strlen(value) + 1);
   strcpy(__acc_pathdelimstr, value);
   break;
  case accToHiZDelay:
   if (strcmp(value, "average") == 0) __acc_tohizdelay = ACCTOHIZ_AVG;
   else if (strcmp(value, "max") == 0) __acc_tohizdelay = ACCTOHIZ_MAX;
   else if (strcmp(value, "min") == 0) __acc_tohizdelay = ACCTOHIZ_MIN;
   else if (strcmp(value, "from_user") == 0)
    __acc_tohizdelay = ACCTOHIZ_FROMUSER;
   else
    {
     __acc_err(1943,
      "acc_configure accToHiZDelay configuration value %s illegal", value);
     return(FALSE);
    }
   break;
  default:
   __acc_err(1944, "acc_configure parameter item value %d illegal", item);
   return(FALSE);
 }
 return(TRUE);
}

/*
 * check a string true/false value (returns -1 on error)
 */
static int32 str_truefalse(char *s)
{
 if (strcmp(s, "true") == 0 || strcmp(s, "TRUE") == 0) return(TRUE);
 else if (strcmp(s, "false") == 0 || strcmp(s, "FALSE") == 0) return(FALSE);
 return(-1);
} 

/*
 * return T if path delimiter string legal - else F
 */
static int32 legal_delimstr(char *s)
{
 char *chp;

 for (chp = s; *chp != '\0'; chp++)
  {
   if (*chp == '$' || *chp == '_' || isalnum(*chp)) continue;
   return(FALSE);
  }
 return(TRUE);
}

/*
 * count number of objects acc_collect would return
 *
 * same as acc_collect but no allocating and copying of handle array 
 */
extern int32 acc_count(handle (*next_function)(), handle object_handle)
{
 int32 isize;
 struct acciter_t *aip;
 struct pviter_t *iterp;
 struct h_t *hp, *hp2, *hp3;

 acc_error_flag = FALSE;

 hp = (struct h_t *) object_handle;
 if (hp != NULL)
  { if (!validate_acc_handle("acc_collect", hp)) return(0); }

 if (next_function == acc_next_topmod)
  {
   __acc_err(1995,
    "acc_count: acc_next_topmod illegal next_function routine - use acc_next_child with NULL mod_handle"); 
   return(0);
  }

 /* get first which builds iterator */
 hp2 = (struct h_t *) (*(next_function))(object_handle, NULL);
 /* will always return nil on error and emit error message */ 
 if (hp2 == NULL) return(0);

 /* know iterator just constructed always pointed to by this */
 aip = __last_aiter;
 hp3 = aip->aiter;
 iterp = hp3->hrec->hu.hiterp;
 isize = iterp->numhs;

 /* done with iterator free */ 
 /* LOOKATME - here think always must free - iterator needed only or size */
 linkout_aiter(aip, hp2->hrec->htyp, FALSE);
 return(isize);
}

/*
 * ACC FETCH ROUTINES IN ALPHABETICAL ORDER EXCEPT TFARG TOGETHER
 */

/*
 * get processed (-f are ** argv) argument count
 */
extern int32 acc_fetch_argc(void)
{
 acc_error_flag = FALSE;
 /* know error can't happen here */
 if (__vpi_argv == NULL) __bld_vpi_argv();
 return(__vpi_argc); 
}

/*
 * get processed (-f are ** argv) argument list ptr
 *
 * LOOKATME - is this really void?
 */
extern void **acc_fetch_argv(void)
{
 acc_error_flag = FALSE;
 /* know error can't happen here */
 if (__vpi_argv == NULL) __bld_vpi_argv();
 return((void **) __vpi_argv); 
}

/*
 * get acc_ style attribute value as real
 * attr is param or specparam value where name matches
 */
/*VARARGS*/
extern double acc_fetch_attribute(handle object, ...)
{
 struct h_t *hp, *rhp;
 double d1;
 va_list va;
 s_vpi_value tmpval;
 char *attrstr;

 acc_error_flag = FALSE;

 hp = (struct h_t *) object; 
 if (!validate_acc_handle("acc_fetch_attribute", hp)) return(0.0); 

 va_start(va, object);
 attrstr = va_arg(va, char *);

 if ((rhp = find_acc_attr_param(hp, attrstr, "acc_fetch_attribute")) == NULL)
  {
ret_def:
   /* T return 0.0 - ignore any possible pass default value */
   if (__acc_defaultattr0) return(0.0);
   /* F return user passed default attribute value */
   d1 = va_arg(va, double);
   va_end(va);
   return(d1);
  }
 /* access object value as real */
 __acc_vpi_erroff = TRUE;
 tmpval.format = vpiRealVal; 
 vpi_get_value((vpiHandle) rhp, &tmpval);
 if (__my_vpi_chk_error())
  {
   __acc_err(1956,
    "acc_fetch_attribute: error accessing real value for attribute %s",
    rhp->hrec->hu.hnp->nsym->synam);
   goto ret_def;
  }
 va_end(va);
 return(tmpval.value.real);
}

/*
 * find attribute matching parameter - NULL if not found
 * passed attribute and ref. object, returns param as h_t if found else nil 
 */
static struct h_t *find_acc_attr_param(struct h_t *hp, char *anam, char *rtnam)
{
 int32 sav_acc_disperrs;
 struct mod_t *mdp;
 struct net_t *np;
 struct h_t *rhp;
 char *chp, sname[2*IDLEN];

 /* make handle for object's module (inst) */
 mdp = (struct mod_t *) hp->hin_idp[MD_MDP];

 /* if module no params, then can't possible match */ 
 if (mdp->mprmnum == 0 && (mdp->mspfy == NULL || mdp->mspfy->sprmnum == 0))
  return(NULL);

 /* turn off acc error displaying and then get acc name */
 sav_acc_disperrs = __acc_displayerrors;
 __acc_displayerrors = FALSE;
 chp = acc_fetch_name((handle) hp);
 __acc_displayerrors = sav_acc_disperrs;

 /* LOOKATME - assumining if object no name only look for 2nd no name attr */
 if (chp == NULL || acc_error_flag) 
  {
   __acc_err(1993,
    "%s: object %s unnamed - searching without associated name",
    rtnam, to_acc_onam(__wrks1, hp->hrec->htyp));
   chp = NULL;
  }
 acc_error_flag = FALSE;
 
 /* search with object name */
 if (chp != NULL)
  {
   sprintf(sname, "%s%s", anam, chp);
   if ((np = tryfnd_param(sname, mdp->msymtab, rtnam, "parameter")) != NULL)
    {
     rhp = (struct h_t *) __mk_handle(vpiParameter, (void *) np, hp->hin_idp,
      NULL); 
     return(rhp);
    }
   if (mdp->mspfy == NULL || mdp->mspfy->spfsyms == NULL) goto try_no_name;
   np = tryfnd_param(sname, mdp->mspfy->spfsyms, rtnam, "specparam");
   if (np != NULL)
    {
     rhp = (struct h_t *) __mk_handle(vpiSpecParam, (void *) np, hp->hin_idp,
      NULL); 
     return(rhp);
    }
  }
try_no_name:
 /* look up attribute name with no object name */
 if ((np = tryfnd_param(anam, mdp->msymtab, rtnam, "parameter")) != NULL)
  {
   rhp = (struct h_t *) __mk_handle(vpiParameter, (void *) np, hp->hin_idp,
    NULL); 
   return(rhp);
  }
 if (mdp->mspfy == NULL || mdp->mspfy->spfsyms == NULL) return(NULL);
 np = tryfnd_param(anam, mdp->mspfy->spfsyms, rtnam, "specparam");
 if (np != NULL)
  {
   rhp = (struct h_t *) __mk_handle(vpiSpecParam, (void *) np, hp->hin_idp,
    NULL); 
   return(rhp);
  }
 return(NULL);
}

/*
 * search for an attr param/sparam in passed symbol table for attribte
 */
static struct net_t *tryfnd_param(char *anam, struct symtab_t *sytp,
 char *rtnam, char *ptnam) 
{
 struct sy_t *syp;

 if ((syp = __get_sym(anam, sytp)) == NULL) return(NULL);
 if (syp->sytyp != SYM_N)
  {
   __acc_warn(2054,
    "%s: attribute %s not found - looking for %s object is a %s", rtnam, 
    anam, ptnam, __to_sytyp(__xs, syp->sytyp));
   return(NULL);
  }
 if (!syp->el.enp->n_isaparam)
  {
   __acc_warn(2054,
    "%s: attribute %s not found - object is not a %s", rtnam, anam, ptnam); 
   return(NULL);
  }
 /* FIXME - when specparams in modules need to make sure right parm type */
 return(syp->el.enp);
}

/*
 * acc fetch attribute - return as int32 variant
 */
/*VARARGS*/
extern int32 acc_fetch_attribute_int(handle object, ...)
{
 struct h_t *hp, *rhp;
 int32 i1;
 va_list va;
 s_vpi_value tmpval;
 char *attrstr;

 acc_error_flag = FALSE;

 hp = (struct h_t *) object; 
 if (!validate_acc_handle("acc_fetch_attribute_int", hp)) return(0); 

 va_start(va, object);
 attrstr = va_arg(va, char *);

 if ((rhp = find_acc_attr_param(hp, attrstr, "acc_fetch_attribute_int"))
  == NULL)
  {
ret_def:
   /* T return 0 - ignore any possible pass default value */
   if (__acc_defaultattr0) return(0);
   /* F return user passed default attribute value */
   i1 = va_arg(va, int32);
   va_end(va);
   return(i1);
  }
 /* access object value as real */
 __acc_vpi_erroff = TRUE;
 tmpval.format = vpiIntVal; 
 vpi_get_value((vpiHandle) rhp, &tmpval);
 if (__my_vpi_chk_error())
  {
   __acc_err(1956,
    "acc_fetch_attribute_int: error accessing int32 value for attribute %s",
    rhp->hrec->hu.hnp->nsym->synam);
   goto ret_def;
  }
 va_end(va);
 return(tmpval.value.integer);
}

/*
 * acc fetch attribute - return as str variant
 */
/*VARARGS*/
extern char *acc_fetch_attribute_str(handle object, ...)
{
 struct h_t *hp, *rhp;
 va_list va;
 s_vpi_value tmpval;
 char *attrstr, *valchp;

 acc_error_flag = FALSE;

 hp = (struct h_t *) object; 
 if (!validate_acc_handle("acc_fetch_attribute_str", hp)) return(NULL); 

 va_start(va, object);
 attrstr = va_arg(va, char *);

 if ((rhp = find_acc_attr_param(hp, attrstr, "acc_fetch_attribute_str")) == NULL)
  {
ret_def:
   /* LOOKATME - should this be empty string */
   /* T return NULL - ignore any possible pass default value */
   if (__acc_defaultattr0) return(NULL);
   /* F return user passed default attribute value */
   valchp = va_arg(va, char *);
   va_end(va);
   return(valchp);
  }
 /* access object value as real */
 __acc_vpi_erroff = TRUE;
 tmpval.format = vpiStringVal; 
 vpi_get_value((vpiHandle) rhp, &tmpval);
 if (__my_vpi_chk_error())
  {
   __acc_err(1956,
    "acc_fetch_attribute_int: error accessing int32 value for attribute %s",
    rhp->hrec->hu.hnp->nsym->synam);
   goto ret_def;
  }
 va_end(va);
 return(tmpval.value.str);
}

/*
 * get a definition name
 */
extern char *acc_fetch_defname(handle object_handle)
{
 struct h_t *hp;
 char *chp;

 acc_error_flag = FALSE;

 hp = (struct h_t *) object_handle; 
 if (!validate_acc_handle("acc_fetch_defname", hp)) return(NULL); 

 /* works because acc handles are same as vpi handles */
 __acc_vpi_erroff = TRUE;
 chp = vpi_get_str(vpiDefName, (vpiHandle) object_handle);

 /* this access error vpi_ error info */  
 /* only error is object not having vpi_ property */
 if (__my_vpi_chk_error())
  {
   __acc_err(1716,
    "acc_fetch_defname: object %s does not have defname - must be instances or primitive",
    to_acc_onam(__wrks1, hp->hrec->htyp));
   return(NULL);
  }
 /* finally add to acc_ string buffer */ 
 return(add_accstrbuf(chp));
}

/*
 * add string to acc string buffer
 */
static char *add_accstrbuf(char *s)
{
 int32 slen;
 char *chp;

 slen = strlen(s);
 /* if won't fit, reset string buffer */
 if (__acc_strbuf_nxti + (slen + 1) >= ACCSTRBUFSIZ) 
  {
   __acc_warn(2042,
    "acc string buffer reset - not enough room to add new string (%d needed)",
    slen + 1); 
   __acc_strbuf_nxti = 0;
   /* DBG remove --- */
   if (slen + 1 >= ACCSTRBUFSIZ) __acc_terr(__FILE__, __LINE__);
   /* --- */
  }
 chp = &(__acc_strbuf[__acc_strbuf_nxti]);
 strcpy(chp, s);
 __acc_strbuf_nxti += slen + 1;
 return(chp);
}

/*
 * get delay mode - delay modes not supported in Cver
 *
 * only supported delay mode is accDelayModePath
 * Cver tool does not store 3 values for MTM delays because it is a
 * simulator
 */
extern int32 acc_fetch_delay_mode(handle object_p)
{
 struct h_t *hp; 

 acc_error_flag = FALSE;

 hp = (struct h_t *) object_p; 
 if (!validate_acc_handle("acc_fetch_delay_mode", hp)) return(0); 
 if (hp->hrec->htyp != vpiModule)
  {
   __acc_err(1725, "acc_next: scope object %s illegal must be accModule",
    to_acc_onam(__wrks1, hp->hrec->htyp));
   return(0);
  }
 return(accDelayModePath);
}

/*
 * fetch delays first into vpi_ delay struct then set rigth values
 *
 * number or arguments for primitives determined by gate class not
 * configure setting
 *
 * LOOKATME - LRM says tranif turn-on/off 2 but think needs to be 3
 */
/*VARARGS*/
extern bool acc_fetch_delays(handle object, ...)
{
 int32 i, j;
 double *d1p, *d2p, *d3p, *da;
 va_list va;
 struct h_t *hp; 
 struct hrec_t *hrp;
 struct gate_t *gp;
 struct mod_pin_t *mpp;
 s_vpi_delay vpideltmp;
 /* need to be able to store 3*12 (same min:typ:max) for each */
 s_vpi_time delarr[36]; 
 struct mod_t *mdp;

 acc_error_flag = FALSE;

 hp = (struct h_t *) object; 
 if (!validate_acc_handle("acc_fetch_delays", hp)) return(0); 
 hrp = hp->hrec;

 for (i = 0; i < 36; i++) delarr[0].type = vpiScaledRealTime;
 vpideltmp.da = &(delarr[0]);
 vpideltmp.time_type = vpiScaledRealTime;
 vpideltmp.mtm_flag = FALSE;
 vpideltmp.append_flag = FALSE;
 vpideltmp.pulsere_flag = FALSE;
 
 switch (hrp->htyp) {
  case vpiGate: case vpiUdp: case vpiSwitch:
   /* 3 values */
   __acc_vpi_erroff = TRUE;
   /* always get 3 delays - although ignore 3rd for logic/udp with only 2 */
   gp = hrp->hu.hgp;
   vpideltmp.no_of_delays = 3;
   vpi_get_delays((vpiHandle) hp, &vpideltmp);

   /* this access error vpi_ error info */  
   /* only error is object not having property */
   if (__my_vpi_chk_error())
    {
     __acc_err(1718,
      "acc_fetch_delays: unable to access delays for object %s",
      to_acc_onam(__wrks1, hp->hrec->htyp));
     return(0);
    }
   va_start(va, object);
   /* notice gates always return 3 */ 
   vpideltmp.no_of_delays = 2;
   if (__acc_mintypmaxdelays)
    {
     da = va_arg(va, double *);
     da[0] = da[1] = da[2] = vpideltmp.da[0].real; 
     da[3] = da[4] = da[5] = vpideltmp.da[1].real; 
     if (gp->g_class != GC_UDP && gp->g_class != GC_LOGIC)
      {
       da[6] = da[7] = da[8] = vpideltmp.da[2].real; 
      }
    }
   else
    {
     d1p = va_arg(va, double *);
     *d1p = vpideltmp.da[0].real; 
     d2p = va_arg(va, double *);
     *d2p = vpideltmp.da[1].real; 
     if (gp->g_class != GC_UDP && gp->g_class != GC_LOGIC)
      {
       d3p = va_arg(va, double *);
       *d3p = vpideltmp.da[2].real; 
      }
    }
   va_end(va);
   break;
  case vpiPort: case vpiPortBit: 
   /* up to 12 - see draft 3 or later new LRM */
   mdp = (struct mod_t *) hp->hin_idp[MD_MDP];
   mpp = &(mdp->mpins[hrp->hu.hpi]);
   if (mpp->mptyp != IO_IN && mpp->mptyp != IO_BID)
    {
     __acc_err(1761,
      "acc_fetch_delays: unable to access delays for %s - output port illegal",
      to_acc_onam(__wrks1, hp->hrec->htyp));
     return(0); 
    }
   if (hrp->htyp == vpiPort && mpp->mpwide != 1)
    {
     __acc_err(1761,
      "acc_fetch_delays: unable to access delays for accPort - must be scalar");
     return(0);
    }
   if (!mpp->has_mipd)
    {
     __acc_warn(2045,
      "acc_fetch_delays: %s does not have MIPD - delays all 0",
     to_acc_onam(__wrks1, hp->hrec->htyp));
      
     va_start(va, object);
     if (__acc_mintypmaxdelays)
      {
       da = va_arg(va, double *);
       for (i = 0; i < 3*__acc_pathdelaycount; i += 3)
        { da[i] = da[i + 1] = da[i + 2] = 0.0; }
      }
     else
      {
       for (i = 0; i < __acc_pathdelaycount; i++)
        { d1p = va_arg(va, double *); *d1p = 0.0; }
      }
     va_end(va);
     return(1);
    }
   /* FALLTHRU */
  case vpiModPath:
   __acc_vpi_erroff = TRUE;
   /* port MIPD since inter module paths not supported) and paths from cfg */
   vpideltmp.no_of_delays = __acc_pathdelaycount;
   vpi_get_delays((vpiHandle) hp, &vpideltmp);

   /* this access error vpi_ error info */  
   /* only error is object not having property */
   if (__my_vpi_chk_error())
    {
     __acc_err(1718,
      "acc_fetch_delays: unable to access path or MIPD delays for object %s",
      to_acc_onam(__wrks1, hp->hrec->htyp));
     return(0);
    }
   va_start(va, object);
   if (__acc_mintypmaxdelays)
    {
     da = va_arg(va, double *);
     for (i = 0, j = 0; i < 3*__acc_pathdelaycount; i +=3, j++)
      {
       da[i + 0] = da[i + 1] = da[i + 2] = vpideltmp.da[j].real; 
      } 
    }
   else
    {
     for (i = 0; i < __acc_pathdelaycount; i++)
      {
       d1p = va_arg(va, double *);
       *d1p = vpideltmp.da[i].real; 
      } 
    }
   va_end(va);
   break;
  case vpiTchk:
   /* 1 value - for 2 limit cases only first accessible in acc_ */
   __acc_vpi_erroff = TRUE;
   /* always get 1 delay (first limit) */
   vpideltmp.no_of_delays = 1;
   vpi_get_delays((vpiHandle) hp, &vpideltmp);

   /* this access error vpi_ error info */  
   /* only error is object not having property */
   if (__my_vpi_chk_error())
    {
     __acc_err(1718,
      "acc_fetch_delays: unable to access delays for object %s",
      to_acc_onam(__wrks1, hp->hrec->htyp));
     return(0);
    }
   va_start(va, object);
   if (__acc_mintypmaxdelays)
    {
     da = va_arg(va, double *);
     da[0] = da[1] = da[2] = vpideltmp.da[0].real; 
    }
   else
    {
     d1p = va_arg(va, double *);
     *d1p = vpideltmp.da[0].real; 
    }
   va_end(va);
   break;
  default:
   __acc_err(1759,
    "acc_fetch_delays: object %s illegal - does not have acc_ accessible delays",
    to_acc_onam(__wrks1, hrp->htyp));
   return(0);
  }
 return(1);
}

/*
 * get direction of acc port or terminal (also tchk terminals)
 *
 * LOOKATME - does acc support timing check terminal directions?
 * this returns 0 on error
 */
extern int32 acc_fetch_direction(handle object_handle)
{
 int32 rv;
 struct h_t *hp;
 struct hrec_t *hrp;

 acc_error_flag = FALSE;

 hp = (struct h_t *) object_handle; 
 if (!validate_acc_handle("acc_fetch_directon", hp)) return(0); 

 hrp = hp->hrec;
 if (hrp->htyp != vpiPort && hrp->htyp != vpiPortBit
  && hrp->htyp != vpiPrimTerm)
  {
   __acc_err(1757,
    "acc_fetch_direction: object %s does not have direction - must be port or primitive terminal",
    to_acc_onam(__wrks1, hrp->htyp));
   return(0);
  }

 __acc_vpi_erroff = TRUE;
 rv = vpi_get(vpiDirection, (vpiHandle) object_handle);

 /* this access error vpi_ error info */  
 /* only error is object not having property */
 if (__my_vpi_chk_error())
  {
   __acc_err(1718,
   "acc_fetch_direction: unable to access direction for object %s",
    to_acc_onam(__wrks1, hp->hrec->htyp));
   return(0);
  }
 switch (rv) {
  case vpiInput: rv = accInput; break;
  case vpiOutput: rv = accOutput; break;
  case vpiInout: rv = accInout; break;
  case vpiMixedIO: rv = accMixedIo; break;
  case vpiNoDirection:
   __acc_err(1719,
    "acc_fetch_direction failed - object %s direction unknown",
    to_acc_onam(__wrks1, hp->hrec->htyp));
   rv = 0;
 } 
 return(rv);
}

/*
 * get an acc edge (same values as vpi edge)
 *
 * FIXME - although acc and vpi edge values same need routine to convert
 * LOOKATME - is returning 0 on error correct? 
 */
extern int32 acc_fetch_edge(handle acc_object)
{
 int32 rv;
 struct h_t *hp;

 acc_error_flag = FALSE;

 hp = (struct h_t *) acc_object; 
 if (!validate_acc_handle("acc_fetch_edge", hp)) return(0); 

 __acc_vpi_erroff = TRUE;
 rv = vpi_get(vpiEdge, (vpiHandle) acc_object);

 /* this access error vpi_ error info */  
 /* only error is object not having property */
 if (__my_vpi_chk_error())
  {
   __acc_err(1721,
   "acc_fetch_edge: object %s does not have edge - must be path or timing check",
    to_acc_onam(__wrks1, hp->hrec->htyp));
   return(0);
  }
 /* same edge encoding between acc and vpi_ */
 return(rv);
}

/*
 * fetch full (xmr if needed) name
 */
extern char *acc_fetch_fullname(handle object_handle)
{
 struct h_t *hp;
 struct mod_t *mdp;
 struct mod_pin_t *mpp;
 char *chp, s1[3*RECLEN], s2[6*RECLEN], s3[6*RECLEN];
 struct itree_t *itp;

 acc_error_flag = FALSE;

 hp = (struct h_t *) object_handle; 
 if (!validate_acc_handle("acc_fetch_fullname", hp)) return(NULL); 

 itp = (struct itree_t *) hp->hin_idp[MD_ITP];
 /* only acc not vpi_ returns full heirarchical path name for ports */ 
 if (hp->hrec->htyp == vpiPort || hp->hrec->htyp == vpiPortBit)
  {
   mdp = itp->itip->imsym->el.emdp;
   mpp = &(mdp->mpins[hp->hrec->hu.hpi]);
   if (mpp->mpsnam == NULL)
    {
     __acc_err(1762, "acc_fetch_fullname: accPort object unnamed");
     return(NULL);
    }
   if (itp->up_it != NULL)
    {
     sprintf(s1, "%s.%s", __msg2_idp_blditree(s2, hp->hin_idp), mpp->mpsnam);
    }
   else strcpy(s2, mpp->mpsnam);
   chp = s1;
   goto add_str;
  }

 /* acc constructs path names from terminals */
 if (hp->hrec->htyp == vpiModPath || hp->hrec->htyp == vpiInterModPath)
  {
   sprintf(s1, "%s%s%s", hp->hrec->hu.hpthp->peins[0].penp->nsym->synam, 
    __acc_pathdelimstr, hp->hrec->hu.hpthp->peouts[0].penp->nsym->synam);
   if (itp->up_it != NULL)
    sprintf(s2, "%s.%s", __msg2_idp_blditree(s3, hp->hin_idp), s1);
   else strcpy(s2, s1);
   chp = s2;
   goto add_str;
  }

 __acc_vpi_erroff = TRUE;
 chp = vpi_get_str(vpiFullName, (vpiHandle) object_handle);

 /* this access error vpi_ error info */  
 /* only error is object not having vpi_ property */
 if (__my_vpi_chk_error())
  {
   __acc_err(1722, "acc_fetch_fullname: object %s does not have fullname",
    to_acc_onam(__wrks1, hp->hrec->htyp));
   return(NULL);
  }

add_str:
 /* finally add to acc_ string buffer */ 
 return(add_accstrbuf(chp));
}

/*
 * get acc full type (usually same as type)
 */
extern int32 acc_fetch_fulltype(handle object_h)
{
 struct h_t *hp;
 struct vpi_to_acc_t *accvpip;

 acc_error_flag = FALSE;
 hp = (struct h_t *) object_h; 

 if (!validate_acc_handle("acc_fetch_fulltype", hp)) return(0); 
 /* once handle validated this can never fail */
 accvpip = get_acc_typerec(hp);
 return(get_acc_fulltype((vpiHandle) object_h, accvpip));
}

/*
 * get index (pos. starting at 0) of a port or terminal
 *
 * LOOKATME - does acc port index also start at 0
 */
extern int32 acc_fetch_index(handle object_handle)
{
 int32 rv;
 struct h_t *hp;

 acc_error_flag = FALSE;

 hp = (struct h_t *) object_handle; 
 if (!validate_acc_handle("acc_fetch_index", hp)) return(0); 

 __acc_vpi_erroff = TRUE;
 if (hp->hrec->htyp == vpiPrimTerm)
  rv = vpi_get(vpiTermIndex, (vpiHandle) object_handle);
 else if (hp->hrec->htyp == vpiPort)
  rv = vpi_get(vpiPortIndex, (vpiHandle) object_handle);
 else goto bad_arg;

 /* this access error vpi_ error info */  
 /* only error is object not having property */
 if (__my_vpi_chk_error())
  {
bad_arg:
   __acc_err(1723,
   "acc_fetch_index: object %s does not have list index - must be port or terminal",
    to_acc_onam(__wrks1, hp->hrec->htyp));
   rv = 0;
  }
 return(rv);
}

/*
 * fetch line number and file name location of acc object
 */
extern int32 acc_fetch_location(p_location location_p, handle object)
{
 int32 lineno;
 struct h_t *hp;
 char *chp;

 acc_error_flag = FALSE;

 hp = (struct h_t *) object; 
 if (!validate_acc_handle("acc_fetch_location", hp)) return(FALSE); 

 __acc_vpi_erroff = TRUE;
 lineno = vpi_get(vpiLineNo, (vpiHandle) object);

 /* this access error vpi_ error info */  
 /* only error is object not having vpi_ property */
 if (__my_vpi_chk_error())
  {
bad_arg:
   __acc_err(1958, "acc_fetch_location: object %s does not have location",
    to_acc_onam(__wrks1, hp->hrec->htyp));
   return(FALSE);
  }
 __acc_vpi_erroff = TRUE;
 chp = vpi_get_str(vpiFile, (vpiHandle) object);
 if (__my_vpi_chk_error()) goto bad_arg;

 location_p->line_no = lineno;
 location_p->filename = add_accstrbuf(chp);
 return(FALSE);
}

/*
 * access objects name (in module local name)
 *
 * notice because of path needing 3 elements - work string 3x ID size 
 */
extern char *acc_fetch_name(handle object_handle)
{
 struct h_t *hp;
 struct mod_t *mdp;
 struct mod_pin_t *mpp;
 char *chp, s1[3*RECLEN];
 struct hrec_t *hrp;

 acc_error_flag = FALSE;

 hp = (struct h_t *) object_handle; 
 if (!validate_acc_handle("acc_fetch_name", hp)) return(NULL); 
 hrp = hp->hrec;

 /* only acc not vpi_ returns full heirarchical path name for ports */ 
 if (hrp->htyp == vpiPort || hrp->htyp == vpiPortBit)
  {
   mdp = (struct mod_t *) hp->hin_idp[MD_MDP];
   mpp = &(mdp->mpins[hrp->hu.hpi]);
   if (mpp->mpsnam == NULL)
    {
     __acc_err(1763, "acc_fetch_name: accPort object unnamed");
     return(NULL);
    }
   chp = mpp->mpsnam;
   goto add_str;
  }

 /* acc constructs port names from terminals */
 if (hrp->htyp == vpiModPath || hrp->htyp == vpiInterModPath)
  {
   sprintf(s1, "%s%s%s", hrp->hu.hpthp->peins[0].penp->nsym->synam, 
    __acc_pathdelimstr, hrp->hu.hpthp->peouts[0].penp->nsym->synam);
   chp = s1;
   goto add_str;
  }

 __acc_vpi_erroff = TRUE;
 chp = vpi_get_str(vpiName, (vpiHandle) object_handle);

 /* this access error vpi_ error info */  
 /* only error is object not having vpi_ property */
 if (__my_vpi_chk_error())
  {
   __acc_err(1724, "acc_fetch_name: object %s does not have name",
    to_acc_onam(__wrks1, hrp->htyp));
   return(NULL);
  }

add_str:
 /* finally add to acc_ string buffer */ 
 return(add_accstrbuf(chp));
}

/*
 * get declaration type of parameter
 *
 * LOOKATME is non string and non real always int32 algorithm right? 
 */
extern int32 acc_fetch_paramtype(handle param_p)
{
 struct h_t *hp;
 struct net_t *np;

 acc_error_flag = FALSE;

 hp = (struct h_t *) param_p; 
 if (!validate_acc_handle("acc_fetch_paramtype", hp)) return(0); 
 
 np = hp->hrec->hu.hnp;
 /* DBG remove --- */
 if (!np->n_isaparam) __acc_terr(__FILE__, __LINE__);
 /* --- */

 if (np->ntyp == N_REAL) return(accRealParam);
 if (np->nu.ct->pstring) return(accStringParam);
 return(accIntegerParam);
}

/*
 * fetch value of a parameter (def or spec) in a double
 *
 * caller can convert int32 back to int32 by cast
 * for string parameter double is really ptr to char * that user
 * must cast double back to char * by first casting to int32 then to char *
 */
extern double acc_fetch_paramval(handle param)
{
 word32 w;
 double d1;
 struct h_t *hp;
 struct net_t *np;
 s_vpi_value tmpval;
 char *chp;

 acc_error_flag = FALSE;

 hp = (struct h_t *) param; 
 if (!validate_acc_handle("acc_fetch_paramval", hp)) return(0.0); 
 
 np = hp->hrec->hu.hnp;
 /* DBG remove --- */
 if (!np->n_isaparam) __acc_terr(__FILE__, __LINE__);
 /* --- */

 if (np->ntyp == N_REAL)
  {
   __acc_vpi_erroff = TRUE;
   tmpval.format = vpiRealVal; 
   vpi_get_value((vpiHandle) param, &tmpval);
   if (__my_vpi_chk_error())
    {
bad_getval:
     __acc_err(1956, "acc_fetch_paramval: error accessing parameter value");
     return(0.0);
    }
   d1 = tmpval.value.real;
  }
 else if (np->nu.ct->pstring)
  {
   __acc_vpi_erroff = TRUE;
   tmpval.format = vpiStringVal; 
   vpi_get_value((vpiHandle) param, &tmpval);
   if (__my_vpi_chk_error()) goto bad_getval;
   /* PORTABILITY - acc standard here requires strange cast */ 
   chp = add_accstrbuf(tmpval.value.str);
   w = (word32) chp;
   d1 = (double) w;
  }
 else
  {
   __acc_vpi_erroff = TRUE;
   /* LOOKATME - notice getting vpi_ to do conversion to double */
   tmpval.format = vpiRealVal; 
   vpi_get_value((vpiHandle) param, &tmpval);
   if (__my_vpi_chk_error()) goto bad_getval;
   d1 = tmpval.value.real;
  }
 return(d1);
}

/*
 * get polarity - type of vpi object
 *
 * LOOKATME - what about data path polarity
 */
extern int32 acc_fetch_polarity(handle path)
{
 int32 rv;
 struct h_t *hp;
 struct hrec_t *hrp;

 acc_error_flag = FALSE;

 hp = (struct h_t *) path; 
 if (!validate_acc_handle("acc_fetch_polarity", hp)) return(0); 
 hrp = hp->hrec;

 if (hrp->htyp != vpiModPath)
  {
   __acc_err(1946,
    "acc_fetch_polarity: object %s does not have polarity - accModPath required",
    to_acc_onam(__wrks1, hp->hrec->htyp));
   return(0);
  }

 __acc_vpi_erroff = TRUE;
 rv = vpi_get(vpiPolarity, (vpiHandle) path);

 /* this access error vpi_ error info */  
 /* only error is object not having property */
 if (__my_vpi_chk_error())
  {
   __acc_err(1959,
    "acc_fetch_polarity: unable to access polarity for object %s",
    to_acc_onam(__wrks1, hp->hrec->htyp));
   return(0);
  }
 /* same edge encoding between acc and vpi_ */
 return(rv);
}

/*
 * get design wide precicison (minimum time scale)
 */
extern int32 acc_fetch_precision(void)
{
 acc_error_flag = FALSE;

 if (!__des_has_timescales)
  {
   __acc_warn(2046,
    "acc_fetch_precision meaningless - design contains no `timescale directives");
   return(0);
  }
 return(-((int32) __des_timeprec));
}

/*
 * fetch pulsere (inertial glitch error ranges)
 *
 * almost same as acc_fetch_delays except mintypmax flag off
 * this never uses min:typ:max flags and never array form
 *
 * Cver does not yet store and simulate so use 0 and delay
 * works by getting one delay not "faked" vpi_ pulsere
 * although LRM says only mod path either type of path legal arg
 * return 0 for reject limit and delay for e_limit
 */
/*VARARGS*/
extern bool acc_fetch_pulsere(handle path_p, double *val1r, double *val1e, ...)
{
 int32 i;
 int32 sav_acc_mintypmaxdelays, rv;
 double *rp, *ep;
 va_list va;
 struct h_t *hp; 
 struct hrec_t *hrp;
 struct mod_pin_t *mpp;
 s_vpi_delay vpideltmp;
 /* need to be able to store 3*12 (same min:typ:max) for each */
 s_vpi_time delarr[36]; 
 struct mod_t *mdp;

 __acc_warn(1954,
  "acc_fetch_pulsere reject value always 0 - e_limit same as delay - tools does not support");

 acc_error_flag = FALSE;

 hp = (struct h_t *) path_p; 
 if (!validate_acc_handle("acc_fetch_pulsere", hp)) return(FALSE); 
 hrp = hp->hrec;

 vpideltmp.da = &(delarr[0]);
 vpideltmp.time_type = vpiScaledRealTime;
 vpideltmp.mtm_flag = FALSE;
 vpideltmp.append_flag = FALSE;
 vpideltmp.pulsere_flag = FALSE;
 
 sav_acc_mintypmaxdelays = __acc_mintypmaxdelays;
 __acc_mintypmaxdelays = FALSE;
 switch (hrp->htyp) {
  case vpiPort: case vpiPortBit: 
   /* up to 12 - see draft 3 or later new LRM */
   mdp = (struct mod_t *) hp->hin_idp[MD_MDP];
   mpp = &(mdp->mpins[hrp->hu.hpi]);
   if (mpp->mptyp != IO_IN && mpp->mptyp != IO_BID)
    {
     __acc_err(1761,
      "acc_fetch_pulsere: unable to access pulsere for %s - output port illegal",
      to_acc_onam(__wrks1, hp->hrec->htyp));
     rv = FALSE;
     goto done;
    }
   if (hrp->htyp == vpiPort && mpp->mpwide != 1)
    {
     __acc_err(1761,
      "acc_fetch_pulsere: unable to access pulsere for accPort - must be scalar");
     rv = FALSE;
     goto done;
    }
   if (!mpp->has_mipd)
    {
     __acc_warn(2045,
      "acc_fetch_pulsere: %s does not have MIPD - pulsere all 0",
     to_acc_onam(__wrks1, hp->hrec->htyp));
      
     *val1r = 0.0;
     *val1e = 0.0;
     va_start(va, val1e);
     for (i = 1; i < __acc_pathdelaycount; i++)
      {
       rp = va_arg(va, double *);
       *rp = 0.0;
       ep = va_arg(va, double *);
       *ep = 0.0;
      }
     va_end(va);
     break;
    }
   /* FALLTHRU */
  case vpiModPath:
   __acc_vpi_erroff = TRUE;
   /* port MIPD since inter module paths not supported) and paths from cfg */
   vpideltmp.no_of_delays = __acc_pathdelaycount;
   vpi_get_delays((vpiHandle) hp, &vpideltmp);

   /* this access error vpi_ error info */  
   /* only error is object not having property */
   if (__my_vpi_chk_error())
    {
     __acc_err(1718,
      "acc_fetch_pulsere: unable to access path or MIPD pulsere for object %s",
      to_acc_onam(__wrks1, hp->hrec->htyp));
     rv = FALSE;
     goto done;
    }
   *val1r = 0.0;
   *val1e = vpideltmp.da[0].real; 
   va_start(va, val1e);
   for (i = 1; i < __acc_pathdelaycount; i++)
    {
     rp = va_arg(va, double *);
     *rp = 0.0;
     ep = va_arg(va, double *);
     *ep = vpideltmp.da[i].real; 
    }
   va_end(va);
   break;
  default:
   __acc_err(1759,
    "acc_fetch_pulsere: object %s illegal - only path has pulsere's",
    to_acc_onam(__wrks1, hrp->htyp));
   rv = FALSE;
   goto done;
  }
 rv = TRUE;
done:
 __acc_mintypmaxdelays = sav_acc_mintypmaxdelays;
 return(rv);
}

/*
 * fetch a range of only a vector 
 *
 * notice msb is first range although may be less than lsb
 * LOOKATME - what are objects for this (allowing vpiMemoryWord)
 */
extern int32 acc_fetch_range(handle node, int32 *msb, int32 *lsb)
{
 int32 r1, r2;
 struct hrec_t *hrp;
 struct h_t *hp;
 vpiHandle rrng, lrng;
 s_vpi_value tmpval;

 acc_error_flag = FALSE;

 hp = (struct h_t *) node; 
 if (!validate_acc_handle("acc_fetch_range", hp)) return(FALSE); 
 hrp = hp->hrec;

 if (hrp->htyp != vpiNet && hrp->htyp != vpiReg && hrp->htyp != vpiMemoryWord)
  {
bad_obj:
   __acc_err(1961,
    "acc_fetch_range: object %s illegal - not a vector net or reg",
    to_acc_onam(__wrks1, hrp->htyp));
   return(FALSE);
  }
 if (!hrp->hu.hnp->n_isavec) goto bad_obj;

 __acc_vpi_erroff = TRUE;
 lrng = vpi_handle(vpiLeftRange, (vpiHandle) node);
 if (__my_vpi_chk_error())
  {
bad_rng:
   __acc_err(1962, "acc_fetch_range: unable to access range value");
   return(FALSE);
  }
 __acc_vpi_erroff = TRUE;
 rrng = vpi_handle(vpiRightRange, (vpiHandle) node);
 if (__my_vpi_chk_error()) goto bad_rng;

 __acc_vpi_erroff = TRUE;
 tmpval.format = vpiIntVal; 
 vpi_get_value(lrng, &tmpval);
 if (__my_vpi_chk_error()) goto bad_rng;
 r1 = tmpval.value.integer;

 __acc_vpi_erroff = TRUE;
 tmpval.format = vpiIntVal; 
 vpi_get_value(rrng, &tmpval);
 if (__my_vpi_chk_error()) goto bad_rng;
 r2 = tmpval.value.integer;
 *msb = r1;
 *lsb = r2;

 return(TRUE);
}

/*
 * get size of a net type object
 *
 * LOOKATME - what are objects allowed for this
 */
extern int32 acc_fetch_size(handle obj_h)
{
 struct hrec_t *hrp;
 struct h_t *hp;
 struct mod_t *mdp;
 struct mod_pin_t *mpp; 

 acc_error_flag = FALSE;

 hp = (struct h_t *) obj_h; 
 if (!validate_acc_handle("acc_fetch_size", hp)) return(0); 
 hrp = hp->hrec;

 switch (hrp->htyp) {
  case vpiNetBit: case vpiRegBit: case vpiPortBit: case vpiVarSelect:
   return(1);
  case vpiNet: case vpiReg: case vpiIntegerVar: case vpiTimeVar:
   return(hrp->hu.hnp->nwid);
  case vpiPort:
   mdp = (struct mod_t *) hp->hin_idp[MD_MDP];
   mpp = &(mdp->mpins[hrp->hu.hpi]);
   return(mpp->mpwide);
  case vpiMemoryWord:
   return(hrp->hu.hnp->nwid);
  default: break;
 }
 __acc_err(1963,
  "acc_fetch_size: object %s illegal - not a net/reg/port or bit thereof",
  to_acc_onam(__wrks1, hrp->htyp));
 return(0);
}

/*
 * SIX ALMOST IDENTICAL ROUTINES TO ACCESS CALLED TF ARG AS VALUE
 */

/*
 * fetch nth tf arg for current tf object as real 
 *
 * special handling of string values (constants) required where value
 * returned is pointer cast to double
 */
extern double acc_fetch_tfarg(int32 n)
{
 word32 w;
 struct hrec_t *shrp;
 vpiHandle systfp;
 struct h_t *shp;
 struct tskcall_t *tkcp;
 struct expr_t *argxp;
 s_vpi_value tmpval;
 char *chp;

 acc_error_flag = FALSE;

 /* returns 0.0 if not called from user defined systf */
 if ((systfp = get_acc_current_systf("acc_fetch_tfarg")) == NULL) return(0.0);

 shp = (struct h_t *) systfp;
 shrp = shp->hrec;

 if (shrp->htyp == vpiSysFuncCall) argxp = shrp->hu.hxp->ru.x;
 else if (shrp->htyp == vpiSysTaskCall) 
  {
   tkcp = &(shrp->hu.hstp->st.stkc);
   argxp = tkcp->targs;
  }
 else { __acc_terr(__FILE__, __LINE__); return(0.0); }

 tmpval.format = vpiRealVal;

 if (!get_systf_acc_expr_val(n, argxp, &tmpval, shp, "acc_fetch_tfarg"))
  return(0.0);
 if (tmpval.format == vpiStringVal)
  {
   /* string value returned as pointer to string converted to double */
   chp = add_accstrbuf(tmpval.value.str);
   w = (word32) chp;
   return((double) w);
  }
 return(tmpval.value.real);
}

/*
 * for current context fetch tfarg, get systf handle
 */
static vpiHandle get_acc_current_systf(char *rnam)
{
 vpiHandle systfp;

 if (__tfinst == NULL)
  { 
   __acc_err(1955,
    "%s: unable to access calling tfinst because no PLI tf called", rnam);  
   return(NULL);
  }

 /* know this is run with current instance on itree stack */
 if (__tfinst->callx != NULL)
  systfp = __mk_handle(vpiSysFuncCall, (void *) __tfinst->callx, __idp,
   __tfrec->tf_intskp);
 else systfp = __mk_handle(vpiSysTaskCall, (void *) __tfinst->tfstp,
  __idp, __tfrec->tf_intskp);
 return(systfp);
}

/*
 * access systf argument value from expression
 * fills value and returns T - if error returns F
 * caller must set expected type in valp
 * notice for literal strings passed get value type changed to string
 *
 * FIXME - what happen when argument is instance form (no value?)
 */
static int32 get_systf_acc_expr_val(int32 n, struct expr_t *argxp,
 s_vpi_value *valp, struct h_t *shp, char *rnam)
{
 int32 argi;
 struct expr_t *xp2;
 vpiHandle arghp;

 /* get expression corresponding to nth argument */
 if (n < 1)
  {
outofrng:
   __acc_warn(2047, "%s: argument position %d out of range", rnam, n);
   /* error flag not set here */
   return(FALSE);
  }

 for (argi = 0, xp2 = argxp; xp2 != NULL; xp2 = xp2->ru.x, argi++)
  {
   if (argi == n - 1) goto found_it;
  }
 goto outofrng; 

found_it:
 /* FIXME - tf arg instance argument core dumps */
 /* this can not currently fail */
 arghp = __mk_exprclass_handle(xp2->lu.x, shp->hin_idp, shp->hrec->hin_tskp);

 /* literal strings always accessed as strings */
 if (xp2->lu.x->is_string) valp->format = vpiStringVal;

 __acc_vpi_erroff = TRUE;
 vpi_get_value(arghp, valp);
 if (__my_vpi_chk_error())
  {
   __acc_err(1756, "%s: error accessing %s argument %d value", rnam,
    vpi_get_str(vpiName, (vpiHandle) shp), n);  
   return(FALSE);
  }
 return(TRUE);
}

/*
 * fetch nth tf arg for task function object tfinst as real 
 *
 * LOOKATME - LRM does say whether expressions (not net/reg and selects
 * of)
 *
 * FIXME - need special case for ports where expression is low conn
 */
extern double acc_fetch_itfarg(int32 n, handle tfinst)
{
 struct hrec_t *shrp;
 word32 w;
 struct h_t *shp;
 struct tskcall_t *tkcp;
 struct expr_t *argxp;
 s_vpi_value tmpval;
 char *chp;

 acc_error_flag = FALSE;

 if (tfinst == NULL)
  {
   __acc_err(1755,
    "acc_fetch_itfarg: no argument accessed because tfinst argument NULL");
   return(0.0);
  }
 
 shp = (struct h_t *) tfinst;
 if (!validate_acc_handle("acc_fetch_itfarg", shp)) return(0.0); 
 shrp = shp->hrec;

 if (shrp->htyp == vpiSysFuncCall) argxp = shrp->hu.hxp->ru.x;
 else if (shrp->htyp == vpiSysTaskCall) 
  {
   tkcp = &(shrp->hu.hstp->st.stkc);
   argxp = tkcp->targs;
  }
 else
  {
   __acc_err(1957,
    "acc_fetch_itfarg: tfinst %s argument illegal - must be acc system tf call",
    to_acc_onam(__wrks1, shrp->htyp));
   return(0.0);
  }

 tmpval.format = vpiRealVal;
 if (!get_systf_acc_expr_val(n, argxp, &tmpval, shp, "acc_fetch_itfarg"))
  return(0.0);

 if (tmpval.format == vpiStringVal)
  {
   /* string value returned as pointer to string converted to double */
   chp = add_accstrbuf(tmpval.value.str);

   /* LOOKATME - this cast looks wrong and unportable ?? */
   w = (word32) chp;
   return((double) w);
  }
 else return(tmpval.value.real);
}

/*
 * fetch nth tf arg for current tf object as int32 
 */
extern int32 acc_fetch_tfarg_int(int32 n)
{
 struct hrec_t *shrp;
 vpiHandle systfp;
 word32 w;
 struct h_t *shp;
 struct tskcall_t *tkcp;
 struct expr_t *argxp;
 s_vpi_value tmpval;
 char *chp;

 acc_error_flag = FALSE;

 if ((systfp = get_acc_current_systf("acc_fetch_tfarg_int")) == NULL)
  return(0);

 shp = (struct h_t *) systfp;
 shrp = shp->hrec;

 if (shrp->htyp == vpiSysFuncCall) argxp = shrp->hu.hxp->ru.x;
 else if (shrp->htyp == vpiSysTaskCall) 
  {
   tkcp = &(shrp->hu.hstp->st.stkc);
   argxp = tkcp->targs;
  }
 else { __acc_terr(__FILE__, __LINE__); return(0); }

 tmpval.format = vpiIntVal;
 
 if (!get_systf_acc_expr_val(n, argxp, &tmpval, shp, "acc_fetch_tfarg_int"))
  return(0);

 if (tmpval.format == vpiStringVal)
  {
   /* string value returned as pointer to string converted to double */
   chp = add_accstrbuf(tmpval.value.str);
   /* FIXME ??? - NOT 64 bit portable */
   w = (word32) chp;
   return((int32) w);
  }

 return(tmpval.value.integer);
}

/*
 * fetch nth tf arg for task function object tfinst as int
 */
extern int32 acc_fetch_itfarg_int(int32 n, handle tfinst)
{
 struct hrec_t *shrp;
 word32 w;
 struct h_t *shp;
 struct tskcall_t *tkcp;
 struct expr_t *argxp;
 s_vpi_value tmpval;
 char *chp;

 acc_error_flag = FALSE;

 if (tfinst == NULL)
  {
   __acc_err(1756,
    "acc_fetch_itfarg_int: no argument accessed because tfinst argument NULL");
   return(0);
  }
 
 shp = (struct h_t *) tfinst;
 if (!validate_acc_handle("acc_fetch_itfarg_int", shp)) return(0); 
 shrp = shp->hrec;

 if (shrp->htyp == vpiSysFuncCall) argxp = shrp->hu.hxp->ru.x;
 else if (shrp->htyp == vpiSysTaskCall) 
  {
   tkcp = &(shrp->hu.hstp->st.stkc);
   argxp = tkcp->targs;
  }
 else
  {
   __acc_err(1957,
    "acc_fetch_itfarg_int: tfinst %s argument illegal - must be acc system tf call",
    to_acc_onam(__wrks1, shrp->htyp));
   return(0);
  }
 tmpval.format = vpiIntVal;
 if (!get_systf_acc_expr_val(n, argxp, &tmpval, shp, "acc_fetch_itfarg_int"))
  return(0);

 if (tmpval.format == vpiStringVal)
  {
   /* string value returned as pointer to string converted to double */
   chp = add_accstrbuf(tmpval.value.str);
   /* FIXME ??? - NOT 64 bit portable */
   w = (word32) chp;
   return((int32) w);
  }
 return(tmpval.value.integer);
}

/*
 * fetch nth tf arg for current tf object as str 
 * must copy string value to acc string table
 *
 * following LRM interpret value as string no matter what it is
 */
extern char *acc_fetch_tfarg_str(int32 n)
{
 struct hrec_t *shrp;
 vpiHandle systfp;
 struct h_t *shp;
 struct tskcall_t *tkcp;
 struct expr_t *argxp;
 s_vpi_value tmpval;

 acc_error_flag = FALSE;

 if ((systfp = get_acc_current_systf("acc_fetch_tfarg_str")) == NULL)
  return(NULL);

 shp = (struct h_t *) systfp;
 shrp = shp->hrec;

 if (shrp->htyp == vpiSysFuncCall) argxp = shrp->hu.hxp->ru.x;
 else if (shrp->htyp == vpiSysTaskCall) 
  {
   tkcp = &(shrp->hu.hstp->st.stkc);
   argxp = tkcp->targs;
  }
 else { __acc_terr(__FILE__, __LINE__); return(NULL); }

 tmpval.format = vpiStringVal;
 
 /* string val goes into vpi get value specific internal big enough buf */ 
 if (!get_systf_acc_expr_val(n, argxp, &tmpval, shp, "acc_fetch_tfarg_str"))
  return(NULL);

 return(add_accstrbuf(tmpval.value.str));
}

/*
 * fetch nth tf arg for task function object tfinst as string
 * must copy string value to acc string table
 *
 * following LRM interpret value as string no matter what it is
 */
extern char *acc_fetch_itfarg_str(int32 n, handle tfinst)
{
 struct hrec_t *shrp;
 struct h_t *shp;
 struct tskcall_t *tkcp;
 struct expr_t *argxp;
 s_vpi_value tmpval;

 acc_error_flag = FALSE;

 if (tfinst == NULL)
  {
   __acc_err(1755,
    "acc_fetch_itfarg_str: no argument accessed because tfinst argument NULL");
   return(NULL);
  }
 
 shp = (struct h_t *) tfinst;
 if (!validate_acc_handle("acc_fetch_itfarg_str", shp)) return(NULL); 
 shrp = shp->hrec;

 if (shrp->htyp == vpiSysFuncCall) argxp = shrp->hu.hxp->ru.x;
 else if (shrp->htyp == vpiSysTaskCall) 
  {
   tkcp = &(shrp->hu.hstp->st.stkc);
   argxp = tkcp->targs;
  }
 else
  {
   __acc_err(1957,
    "acc_fetch_itfarg_str: tfinst %s argument illegal - must be acc system tf call",
    to_acc_onam(__wrks1, shrp->htyp));
   return(NULL);
  }

 tmpval.format = vpiStringVal;
 
 if (!get_systf_acc_expr_val(n, argxp, &tmpval, shp, "acc_fetch_tfarg_str"))
  return(NULL);
 return(add_accstrbuf(tmpval.value.str));
}

/*
 * get timescale info or active $timeformat value
 */
extern void acc_fetch_timescale_info(handle obj,
 p_timescale_info aof_timescale_info)
{
 struct h_t *hp;
 struct mod_t *mdp;

 acc_error_flag = FALSE;

 hp = (struct h_t *) obj;
 /* case 1: get active timeformat info */
 if (hp == NULL)
  {
   aof_timescale_info->unit = -((int32) __tfmt_units);
   aof_timescale_info->precision = __tfmt_precunits; 
   return;
  }

 /* get module's timescale */
 if (!validate_acc_handle("acc_fetch_timescale_info", hp)) return; 
 
 mdp = (struct mod_t *) hp->hin_idp[MD_MDP];
 if (mdp->mno_unitcnv)
  {
   aof_timescale_info->unit = -((short int) __des_timeprec);
   aof_timescale_info->precision = -((short int) __des_timeprec);
  }
 else
  {
   aof_timescale_info->unit = -((short int) mdp->mtime_units);
   aof_timescale_info->precision =
    -((short int) (mdp->mtime_units + mdp->mtime_prec));
  }
 /* SJM 09/01/00 - this is wrong since over-writes --- 
 REMOVED - aof_timescale_info->unit = -((int32) mdp->mtime_units);
 REMOVED - aof_timescale_info->precision = -((int32) mdp->mtime_prec); 
 --- */
}

/*
 * get type of object
 */
extern int32 acc_fetch_type(handle object_handle)
{
 struct h_t *hp;
 struct vpi_to_acc_t *accvpip;
 s_vpi_systf_data systfdat;

 acc_error_flag = FALSE;
 hp = (struct h_t *) object_handle; 

 if (!validate_acc_handle("acc_fetch_type", hp)) return(0); 

 accvpip = get_acc_typerec(hp);

 /* DBG remove --- */
 if (accvpip->acc_otyp == -1) __acc_terr(__FILE__, __LINE__);
 /* --- */

 if (accvpip->acc_otyp != accUserFunction
  && accvpip->acc_otyp != accSystemFunction)
  {
   return(accvpip->acc_otyp);
  }

 /* handle 2 systf acc objects that require checking to distinguish */
 /* distinguish real from non real case */
 __acc_vpi_erroff = TRUE;
 vpi_get_systf_info((vpiHandle) object_handle, &systfdat);
 if (__my_vpi_chk_error())
  {
   __acc_err(1952,
    "acc_fetch_type unable to access systf_info for %s object",
    to_acc_onam(__wrks1, hp->hrec->htyp));
   return(0);
  }
 if (systfdat.sysfunctype == vpiRealFunc)
  {
   if (hp->hrec->htyp == vpiUserSystf) return(accUserRealFunction);
   if (hp->hrec->htyp == vpiSysFuncCall) return(accSystemRealFunction);
   __acc_terr(__FILE__, __LINE__);
  }
 if (hp->hrec->htyp == vpiUserSystf) return(accUserFunction);
 if (hp->hrec->htyp == vpiSysFuncCall) return(accSystemFunction);
 __acc_terr(__FILE__, __LINE__);
 return(0);
}

/*
 * access type as string name (not constant value)
 */
extern char *acc_fetch_type_str(int32 type)
{
 char *chp;

 acc_error_flag = FALSE;

 if ((chp = get_accnam(type)) == NULL)
  {
   __acc_err(1964,
    "acc_fetch_type_str type value %d illegal - no type or fulltype matches", 
    type);
   return(NULL);
  }
 return(add_accstrbuf(chp));
}

/*
 * fetch acc value using either %% or acc value structure 
 *
 * FIXME - need checking for legal objects
 * LOOKATME - what returned for %% case
 */
extern char *acc_fetch_value(handle object_handle, char *format_str,
 p_acc_value acc_value_p)
{
 int32 fvfmt, owid;
 word32 wval, s0val, s1val;
 struct h_t *hp;
 s_vpi_value tmpval;
 char s1[RECLEN];

 acc_error_flag = FALSE;
 hp = (struct h_t *) object_handle; 

 if (!validate_acc_handle("acc_fetch_value", hp)) return(NULL); 

 if (strcmp(format_str, "%b") == 0) fvfmt = vpiBinStrVal; 
 else if (strcmp(format_str, "%d") == 0) fvfmt = vpiDecStrVal; 
 else if (strcmp(format_str, "%h") == 0) fvfmt = vpiHexStrVal; 
 else if (strcmp(format_str, "%o") == 0) fvfmt = vpiOctStrVal; 
 /* notice this is strength string not vpi style strength record */
 else if (strcmp(format_str, "%v") == 0) fvfmt = vpiStrengthVal; 
 else if (strcmp(format_str, "%%") == 0)
  {
   if (acc_value_p == NULL)
    {
     __acc_err(1967,
      "acc_fetch_value %% format illegal - value structure argument NULL");
     return(NULL);
    }
   if ((fvfmt = fr_accfmt_to_vpifmt(acc_value_p->format)) == -1)
    {
     __acc_err(1968,
     "acc_fetch_value %% format s_setval_value argument record format value %d illegal",
     acc_value_p->format);
     return(NULL);
    }
   __acc_vpi_erroff = TRUE;
   tmpval.format = fvfmt;
   /* notice for vector a/b value arrays, vpi_ allocates work storage */
   vpi_get_value((vpiHandle) object_handle, &tmpval);
   if (__my_vpi_chk_error())
    {
     __acc_err(1969, "acc_fetch_value unable to access %% format type %s",
      to_accfmtnam(__wrks1, fvfmt));
     return(NULL);
    }
   /* final step - convert vpi value format to acc */
   owid = 1;
   if (acc_value_p->format == accVectorVal)
    {
     __acc_vpi_erroff = TRUE;
     owid = vpi_get(vpiSize, (vpiHandle) object_handle);
     if (__my_vpi_chk_error())
      {
       __acc_err(1970,
        "acc_fetch_value %% format accVectorVal type - unable to access object size");
       return(NULL);
      }
    }
   if (!copy_vpival_to_accval(acc_value_p, &tmpval, owid))
    {
     __acc_err(1971,
      "acc_fetch_value %% format unable to fill acc_value_p record");
    }
   return(NULL);
  }
 else 
  {
   __acc_err(1965, "acc_fetch_value format string %s illegal", format_str);
   return(NULL);
  }
 /* simple string case */
 __acc_vpi_erroff = TRUE;
 tmpval.format = fvfmt;
 vpi_get_value((vpiHandle) object_handle, &tmpval);
 if (__my_vpi_chk_error())
  {
   __acc_err(1966,
    "acc_fetch_value unable to access %s format_str value of %s object",
    format_str, to_acc_onam(__wrks1, hp->hrec->htyp));
   return(NULL);
  }
 if (fvfmt == vpiStrengthVal)
  {
   /* LOOKATME - what happens if value is non strength? */
   /* build 1 byte internal Cver strength value in word32 form vpi_ */
   wval = (word32) tmpval.value.strength->logic;
   if (wval != 2) 
    {
     s0val = __map_frvpi_stren(tmpval.value.strength->s0);
     s1val = __map_frvpi_stren(tmpval.value.strength->s1);
     /* form into byte and return in acc string buf */
     wval |= (((((byte) s0val) & 7L) << 5) | ((((byte) s1val) & 7L) << 2));
    }
   return(add_accstrbuf(__to_vvstnam(s1, wval)));
  }
 return(add_accstrbuf(tmpval.value.str));
}

/*
 * map from a acc format constant to a vpi_ format constant 
 */
static int32 fr_accfmt_to_vpifmt(int32 accfmt)
{
 switch (accfmt) {
  case accBinStrVal: return(vpiBinStrVal);
  case accOctStrVal: return(vpiOctStrVal);
  case accDecStrVal: return(vpiDecStrVal);
  case accHexStrVal: return(vpiHexStrVal);
  case accScalarVal: return(vpiScalarVal);
  case accIntVal: return(vpiIntVal);
  case accRealVal: return(vpiRealVal);
  case accStringVal: return(vpiStringVal);
  case accVectorVal: return(vpiVectorVal);
  default: break;
 }
 return(-1);
}

/*
 * map from acc format constant to its name
 */
static char *to_accfmtnam(char *s, int32 accfmt)
{
 switch (accfmt) {
  case accBinStrVal: strcpy(s, "accBinStrVal"); break;
  case accOctStrVal: strcpy(s, "accOctStrVal"); break;
  case accDecStrVal: strcpy(s, "accDecStrVal"); break;
  case accHexStrVal: strcpy(s, "accHexStrVal"); break;
  case accScalarVal: strcpy(s, "accScalarVal"); break;
  case accIntVal: strcpy(s, "accIntVal"); break;
  case accRealVal: strcpy(s, "accRealVal"); break;
  case accStringVal: strcpy(s, "accStringVal"); break;
  case accVectorVal: strcpy(s, "accVectorVal"); break;
  default: __acc_terr(__FILE__, __LINE__); strcpy(s, "");
 }
 return(s);
}


/*
 * copy a t_vpi_value record to a acc t_setval_value record
 * this can fail if vpi value not compatible - returns F if fails
 *
 * caller must have allocated any needed fields in acc value record
 */
static int32 copy_vpival_to_accval(s_setval_value *avp, s_vpi_value *vvp,
 int32 owid)
{
 int32 wlen;
 char *chp;

 /* SJM 12/17/02 - selection was from wrong vpi but almost worked */
 /* because constants the same except for vec val gap */ 
 switch (avp->format) {
  case accBinStrVal: case accOctStrVal: case accDecStrVal:
  case accHexStrVal: case accStringVal:
   /* easy case - just copy string */
   chp = add_accstrbuf(vvp->value.str);
   avp->value.str = chp;
   break;
  case accScalarVal:
   avp->value.scalar = vvp->value.scalar;
   break;
  case accIntVal:
   avp->value.integer = vvp->value.integer;
   break;
  case accRealVal:
   /* SJM 11/19/02 - this must copy real not int32 - need 8 byte copy */
   avp->value.real = vvp->value.real;
   break;
  case accVectorVal:
   wlen = wlen_(owid);
   /* caller must have allocated right size p_acc_vecval area */
   memmove(avp->value.vector, vvp->value.vector, 2*WRDBYTES*wlen);
   break;
  default: return(FALSE);
 }
 return(TRUE); 
}

/*
 * free an array of objects collected by acc collect
 *
 * know object array has NULL ending fence
 */
extern void acc_free(handle *array_ptr)
{
 int32 htabsiz;
 struct h_t *hp;

 acc_error_flag = FALSE;

 hp = (struct h_t *) array_ptr[0];
 if (!validate_acc_handle("acc_free (first handle)", hp)) return; 

 /* count and free handles inside array */
 for (htabsiz = 0;; htabsiz++)
  {
   if (array_ptr[htabsiz] == NULL) break; 
   hp = (struct h_t *) array_ptr[htabsiz];
   __acc_vpi_erroff = TRUE;
   /* FIXME this free is wrong because links out of vpi not acc list */
   /* SJM 03/15/00 - must not free since following XL acc_ free does */
   /* nothing */
   /* ---
   if (!vpi_free_object((vpiHandle) hp))
    {
     __acc_err(1996,
      "acc_free free of object %s (pos. %d) in array failed (possible internal error)",
      to_acc_onam(__wrks1, hp->hrec->htyp));
    }
   --- */
  }
 /* finally, free array itself */
 __my_free(array_ptr, (htabsiz + 1)*sizeof(vpiHandle));
}

/*
 * ACC HANDLE ACCESS ROUTINES
 */

/*
 * access an object from a local nmae
 *
 * LOOKATME inst_name and scope_p name meaningless
 */
extern handle acc_handle_by_name(char *inst_name, handle scope_p)
{
 struct h_t *hp;
 vpiHandle objp;

 acc_error_flag = FALSE;

 hp = (struct h_t *) scope_p;
 if (hp != NULL)
  {
   if (!validate_acc_handle("acc_handle_by_name scope", hp)) return(NULL); 
  } 

 /* SJM 05/21/01 - following other simulators - allow in qualified name */
 __acc_vpi_erroff = TRUE;
 objp = vpi_handle_by_name(inst_name, (vpiHandle) scope_p); 
 /* if just can not find name - no error just returns nil */
 if (__my_vpi_chk_error())
  {
   __acc_err(1714,
    "acc_handle_by_name for object %s failed (possible internal error)",
    inst_name);
   return(NULL);
  }
 return((handle) objp);
}

/*
 * get a timincg check terminal or module path condition expression 
 * as handle
 */
extern handle acc_handle_condition(handle obj)
{
 vpiHandle termp;
 struct h_t *hp;
 struct hrec_t *hrp;

 acc_error_flag = FALSE;
 hp = (struct h_t *) obj;
 if (!validate_acc_handle("acc_handle_condition", hp)) return(NULL); 
 hrp = hp->hrec;

 if (hrp->htyp != vpiTchkTerm && hrp->htyp != vpiModPath)
  {
   __acc_err(1701,
    "acc_handle_condition object type %s illegal - must be accModPath or accTchkTerminal",
    to_acc_onam(__wrks1, hrp->htyp));
   return(NULL);
  }
 __acc_vpi_erroff = TRUE;
 termp = vpi_handle(vpiCondition, (vpiHandle) obj); 
 /* if just can not find name - no error just returns nil */
 if (__my_vpi_chk_error())
  {
   __acc_err(1975,
    "acc_handle_condition for object %s failed (possible internal error)",
    to_acc_onam(__wrks1, hrp->htyp));
   return(NULL);
  }
 return((handle) termp);
}

/*
 * access expression object connected to 
 *
 * LOOKATME - think vpi_ vpiExpr 1-to-1 method works because 1 bit exprs
 */
extern handle acc_handle_conn(handle term_p)
{
 struct hrec_t *hrp;
 vpiHandle expr;
 struct h_t *hp;

 acc_error_flag = FALSE;

 hp = (struct h_t *) term_p;
 if (!validate_acc_handle("acc_handle_conn", hp)) return(NULL); 
 hrp = hp->hrec;
 if (hrp->htyp != vpiTchkTerm && hrp->htyp != vpiModPath
  && hrp->htyp != vpiPrimTerm)
  {
   __acc_err(1702,
    "acc_handle_conn object type %s illegal - must be accPathTerminal or accTchkTerminal or accTerminal",
    to_acc_onam(__wrks1, hrp->htyp));
   return(NULL);
  }
 __acc_vpi_erroff = TRUE;
 expr = vpi_handle(vpiExpr, (vpiHandle) term_p); 
 /* if just can not find name - no error just returns nil */
 if (__my_vpi_chk_error())
  {
   __acc_err(1975,
    "acc_handle_conn for object %s failed (possible internal error)",
    to_acc_onam(__wrks1, hrp->htyp));
   return(NULL);
  }
 return((handle) expr);
}

/*
 * get acc handle for data path associated with mod path if exists
 *
 * FIXME - this is wrong acc data path access different - how work?
 * FIXME - need to distinguish paths with datasrcx in acc
 * same as module path but has datapthin and datapthout
 */
extern handle acc_handle_datapath(handle path)
{
 struct h_t *hp;

 acc_error_flag = FALSE;

 hp = (struct h_t *) path;
 if (!validate_acc_handle("acc_handle_datapath", hp)) return(NULL); 
 if (hp->hrec->htyp != vpiModPath)
  {
   __acc_err(1703,
    "acc_handle_datapath object type %s illegal - must be edge sensitive accModPath",
    to_acc_onam(__wrks1, hp->hrec->htyp));
   return(NULL);
  }
 if (hp->hrec->hu.hpthp->datasrcx != NULL) return(NULL);
 /* maybe need acc copy of this? */
 return(path);
}

/*
 * get highconn expression for a accPort or accPortBit 
 *
 * returns nil if vectored port (not passed port bit or scalar port)
 */
extern handle acc_handle_hiconn(handle port_ref)
{
 int32 bithtyp;
 vpiHandle expr;
 struct h_t *hp, *hp2, *hp3;
 struct hrec_t *hrp;

 acc_error_flag = FALSE;

 hp = (struct h_t *) port_ref;
 if (!validate_acc_handle("acc_handle_hiconn", hp)) return(NULL); 
 hrp = hp->hrec;

 if (hrp->htyp != vpiPort && hrp->htyp != vpiPortBit)
  {
   __acc_err(1704,
    "acc_handle_hiconn object type %s illegal - must be accPort or accPortBit",
    to_acc_onam(__wrks1, hrp->htyp));
   return(NULL);
  }
 if (hrp->htyp == vpiPort && !vpi_get(vpiScalar, (vpiHandle) port_ref))
  { 
   __acc_err(1976,
    "acc_handle_hiconn failed port_ref is not accPortBit or scalar accPort");
   return(NULL);
  }
 __acc_vpi_erroff = TRUE;
 expr = vpi_handle(vpiHighConn, (vpiHandle) port_ref); 
 /* if just can not find name - no error just returns nil */
 if (__my_vpi_chk_error())
  {
   __acc_err(1975,
    "acc_handle_hiconn for object %s failed (possible internal error)",
    to_acc_onam(__wrks1, hrp->htyp));
   return(NULL);
  }
 /* must be one bit or concatenate in acc */
 hp2 = (struct h_t *) expr;
 switch (hp2->hrec->htyp) {
  case vpiNet:
   bithtyp = vpiNetBit;
   goto bld_hiconn; 
  case vpiReg: case vpiIntegerVar: case vpiTimeVar:
   bithtyp = vpiRegBit;
bld_hiconn:
   /*for int32 or time, know this will always be T */
   if (hp2->hrec->hu.hnp->nwid != 1)
    {
     /* here need to construct accBit handle of low bit */
     hp3 = (struct h_t *) __mk_handle(bithtyp, (void *) hp->hrec->hu.hnp,
      hp2->hin_idp, NULL); 
     hp3->hrec->hi = 0;
     hp3->hrec->bith_ndx = TRUE;
     /* free object here right since copied guts and returning other handle */
     if (!vpi_free_object(expr))
      { __acc_terr(__FILE__, __LINE__); }
     return((handle) hp3);
    }
   return((handle) expr);
  case vpiRegBit: case vpiNetBit:
   return((handle) expr);
  default:
   __acc_err(1976,
    "acc_handle_hiconn failed - highconn object %s is not net/reg or net/reg bit select",
    to_acc_onam(__wrks1, hp2->hrec->htyp));
   break;
 }
 return(NULL);
}

/*
 * return current interactive scope (know there always is one) 
 * this can't fail
 */
extern handle acc_handle_interactive_scope(void)
{
 int32 typ;
 struct mod_t *mdp;

 acc_error_flag = FALSE;

 if (__scope_tskp != NULL) 
  {
   typ = __to_vpi_tasktyp(__scope_tskp->tsktyp);
   return((handle) __mk_handle(typ, (void *) __scope_tskp, __scope_idp,
    (struct task_t *) NULL)); 
  }
 mdp = (struct mod_t *) __scope_idp[MD_MDP];
 return((handle) __mk_handle(vpiModule, (void *) mdp, __scope_idp,
  (struct task_t *) NULL)); 
}

/*
 * get loconn expression for a accPort or accPortBit 
 *
 * returns nil if vectored port (not passed port bit)
 */
extern handle acc_handle_loconn(handle port_ref)
{
 vpiHandle expr;
 struct h_t *hp, *hp2;
 struct hrec_t *hrp2;

 acc_error_flag = FALSE;

 hp = (struct h_t *) port_ref;
 if (!validate_acc_handle("acc_handle_loconn", hp)) return(NULL); 
 if (hp->hrec->htyp != vpiPort && hp->hrec->htyp != vpiPortBit)
  {
   __acc_err(1905,
    "acc_handle_loconn object type %s illegal - must be accPort or accPortBit",
    to_acc_onam(__wrks1, hp->hrec->htyp));
   return(NULL);
  }
 __acc_vpi_erroff = TRUE;
 expr = vpi_handle(vpiLowConn, (vpiHandle) port_ref); 
 /* if just can not find name - no error just returns nil */
 if (__my_vpi_chk_error())
  {
   __acc_err(1975,
    "acc_handle_loconn for object %s failed (possible internal error)",
    to_acc_onam(__wrks1, hp->hrec->htyp));
   return(NULL);
  }
 /* must be one bit or concatenate in acc */
 hp2 = (struct h_t *) expr;
 hrp2 = hp2->hrec;
 switch (hrp2->htyp) {
  case vpiReg: case vpiNet: 
   if (hrp2->hu.hnp->nwid != 1) goto bad_loconn;
   break;
  case vpiRegBit: case vpiNetBit:
   break;
  default:
bad_loconn:
   __acc_err(1976,
    "acc_handle_loconn failed - loconn object %s is not scalar or bit select",
    to_acc_onam(__wrks1, hrp2->htyp));
   return(NULL);
 }
 return((handle) expr);
}

/*
 * get handle to module path - tricky because must construct name
 * WRITEME
 */
/*VARARGS*/
extern handle acc_handle_modpath(handle mod_p, char *pathin_name,
 char *pathout_name, ...)
{
 /* va_list va; */
 __acc_err(1941, "acc_handle_modpath not yet implemented");
 /* va_end(va); */
 return(NULL);
}

/*
 * access a timing check's notifier if it exists
 */
extern handle acc_handle_notifier(handle tchk)
{
 vpiHandle notifp;
 struct h_t *hp;

 acc_error_flag = FALSE;

 hp = (struct h_t *) tchk;
 if (!validate_acc_handle("acc_handle_notifier", hp)) return(NULL); 
 if (hp->hrec->htyp != vpiTchk)
  {
   __acc_err(1706,
    "acc_handle_notifier object type %s illegal - must be accTchk",
    to_acc_onam(__wrks1, hp->hrec->htyp));
   return(NULL);
  }
 __acc_vpi_erroff = TRUE;
 notifp = vpi_handle(vpiTchkNotifier, (vpiHandle) tchk); 
 /* if just can not find name - no error just returns nil */
 if (__my_vpi_chk_error())
  {
   __acc_err(1975,
    "acc_handle_notifier for object %s failed (possible internal error)",
    to_acc_onam(__wrks1, hp->hrec->htyp));
   return(NULL);
  }
 return((handle) notifp);
}

/*
 * get acc handle from object name
 *
 * LOOKATME - new LRM drafts say paths using acc_ $ convention illegal
 *            see if true?
 */
extern handle acc_handle_object(char *object_name)
{
 vpiHandle objp, scoph;
 char s1[RECLEN];

 acc_error_flag = FALSE;

 if (__acc_scope_set) scoph = __acc_scope_vpiobj;
 else
  {
   scoph = get_acc_current_systf("acc_handle_object");
   if (acc_error_flag) return(NULL);
  }

 /* nil or empty string return current scope defaults to cur systf scope */
 /* LOOKATME - should this also be used for empty string */ 
 if (object_name == NULL)
  {
   objp = vpi_copy_object(scoph);
   return((handle) objp);
  }

 __acc_vpi_erroff = TRUE;
 /* first search for rooted - use scope next if not found */
 objp = vpi_handle_by_name(object_name, NULL);
 if (__my_vpi_chk_error()) goto bad_vpi;
 if (objp != NULL) return((handle) objp);

 /* then search in scope for relative */
 objp = vpi_handle_by_name(object_name, (vpiHandle) scoph);
 /* if just can not find name - no error just returns nil */
 if (__my_vpi_chk_error())
  {
bad_vpi:
   if (scoph == NULL) strcpy(s1, "**NONE**");
   else sprintf(s1, "%s", vpi_get_str(vpiName, scoph));
   __acc_err(1975,
    "acc_handle_object search for %s in scope %s failed (possible internal error)",
    object_name, s1);
   return(NULL);
  }
 return((handle) objp);
}

/*
 * get parent
 *
 * notice acc algorithm differs from vpi_ in that parent of bit of
 * something is module not variable - cannot use vpiParent
 *
 * for other than port bit and prim terminal, this is like vpiModule
 * 1-to-1 access method not parent
 *
 * if passed good handle, this can not fail
 */
extern handle acc_handle_parent(handle object_p)
{
 struct hrec_t *hrp;
 int32 typ;
 struct h_t *hp;
 struct itree_t *itp, *hp_itp;
 struct mod_t *mdp;

 acc_error_flag = FALSE;

 hp = (struct h_t *) object_p;
 if (!validate_acc_handle("acc_handle_parent", hp)) return(NULL); 
 hrp = hp->hrec;

 if (hrp->htyp == vpiPrimTerm)
  {
   /* this is internal vpi primitive type (i.e. vpi Switch) */
   typ = __gate_to_vpiprimtyp(hrp->hu.hgp);
   return((handle) __mk_handle(typ, (void *) hrp->hu.hgp, hp->hin_idp, NULL)); 
  }
 if (hrp->htyp == vpiPortBit)
  {
   /* task here always nil - port indicated by hpi bit by hi */
   /* AIV 08/25/09 - cast this to word64 to avoid warn is fine to cast */
   /* since it is known to be a bit index value */
   return((handle) __mk_handle(vpiPort, (void *) (word32) hrp->hu.hpi, 
       hp->hin_idp, hrp->hin_tskp));
  }
 if (hrp->htyp == vpiModule)
  {
   hp_itp = (struct itree_t *) hp->hin_idp[MD_ITP];
   if ((itp = hp_itp->up_it) == NULL) return(NULL);  
   return((handle) __mk_handle(vpiModule, (void *) itp->itip->imsym->el.emdp,
    itp->it_idp, NULL));
  }
 /* finally - anything else gets containing module */
 mdp = (struct mod_t *) hp->hin_idp[MD_MDP];
 return((handle)__mk_handle(vpiModule, (void *) mdp, hp->hin_idp, NULL));
}

/*
 * WRITEME 
 */
extern handle acc_handle_path(handle source, handle destination)
{
 __acc_err(1941, "acc_handle_path not yet implemented (only MIPDs supported)");
 return(NULL);
}

/*
 * get first net used in path source (path input)
 *
 * this directly get first pathin net - general acc_next_input method
 * return accPathTerminal for which acc_handle_conn is used to get
 * connected object including possible bit selects
 *
 * LOOKATME - for bit select LRM says still returns accNet object - check?
 * LOOKATME - using short cut to directly access net instead of using
 *            normal vpi 2 step to get object so is dependent on storage
 *            of paths but eliminates dealing with bit objects
 */
extern handle acc_handle_pathin(handle path_p)
{
 struct h_t *hp, *hp2;
 struct spcpth_t *pthp;
 struct net_t *np;

 acc_error_flag = FALSE;

 hp = (struct h_t *) path_p;
 if (!validate_acc_handle("acc_handle_pathin", hp)) return(NULL); 

 if (hp->hrec->htyp != vpiModPath)
  { 
   __acc_err(1734, "acc_handle_pathin: %s object illegal - accModPath required",
    to_acc_onam(__wrks1, hp->hrec->htyp));
   return(NULL);
  }
 pthp = hp->hrec->hu.hpthp;
 np = pthp->peins[0].penp;
 /* can't be a task context here */
 hp2 = (struct h_t *) __mk_handle(vpiNet, (void *) np, hp->hin_idp, NULL); 
 return((handle) hp2);
}

/*
 * get first net used in path dest (path output)
 *
 * this directly get first pathout net - general acc_next_output method
 * return accPathTerminal for which acc_handle_conn is used to get
 * connected object including possible bit selects
 *
 * LOOKATME - for bit select LRM says still returns accNet object - check?
 * LOOKATME - using short cut to directly access net instead of using
 *            normal vpi 2 step to get object so is dependent on storage
 *            of paths but eliminates dealing with bit objects
 */
extern handle acc_handle_pathout(handle path_p)
{
 struct h_t *hp, *hp2;
 struct spcpth_t *pthp;
 struct net_t *np;

 acc_error_flag = FALSE;

 hp = (struct h_t *) path_p;
 if (!validate_acc_handle("acc_handle_pathout", hp)) return(NULL); 

 if (hp->hrec->htyp != vpiModPath)
  { 
   __acc_err(1734, "acc_handle_pathout: %s object illegal - accModPath required",
    to_acc_onam(__wrks1, hp->hrec->htyp));
   return(NULL);
  }
 pthp = hp->hrec->hu.hpthp;
 np = pthp->peouts[0].penp;
 /* can't be a task context here */
 hp2 = (struct h_t *) __mk_handle(vpiNet, (void *) np, hp->hin_idp, NULL); 
 return((handle) hp2);
}

/*
 * access a module port handle using port index (order pos.) 
 */
/*VARARGS*/
extern handle acc_handle_port(handle port, int32 port_num)
{
 struct h_t *hp, *hp2;
 struct mod_t *mdp;

 acc_error_flag = FALSE;

 hp = (struct h_t *) port;
 if (!validate_acc_handle("acc_handle_port", hp)) return(NULL); 

 if (hp->hrec->htyp != vpiModule)
  {
   __acc_err(1708,
    "acc_handle_port object type %s illegal - must be type accModule",
    to_acc_onam(__wrks1, hp->hrec->htyp));
   return(NULL);
  }
 mdp = hp->hrec->hu.hmdp;
 if (port_num < 0 || port_num >= mdp->mpnum) 
  {
   __acc_err(1977,
    "acc_handle_port accmodule port index value %d out of range", port_num);
   return(NULL);
  }
 /* notice unusual vpi_ object - index is only type indicator */
 hp2 = (struct h_t *) __mk_handle(vpiPort, NULL, hp->hin_idp, NULL); 
 hp2->hrec->hi = port_num;
 return((handle) hp2);
}

/*
 * get scope that contains object
 *
 * LOOKATME - are acc and vpi_ scopes same?
 */
extern handle acc_handle_scope(handle object)
{
 vpiHandle scopeptr;
 struct h_t *hp;

 acc_error_flag = FALSE;

 hp = (struct h_t *) object;
 
 if (!validate_acc_handle("acc_handle_scope", hp)) return(NULL); 
 __acc_scope_set = FALSE;
 __acc_scope_vpiobj = NULL;

 __acc_vpi_erroff = TRUE;
 scopeptr = vpi_handle(vpiScope, (vpiHandle) object);
 /* if just can not find name - no error just returns nil */
 if (__my_vpi_chk_error())
  {
   __acc_err(1709, "acc_handle_scope %s object scope access failed",
    to_acc_onam(__wrks1, hp->hrec->htyp));
   return(NULL);
  }
 return((handle) scopeptr);
}

/*
 * get simulated net - always same so can not fail
 *
 * LOOKATME - allowing any net/var type thing
 */
extern handle acc_handle_simulated_net(handle net_h)
{
 struct h_t *hp;

 acc_error_flag = FALSE;

 hp = (struct h_t *) net_h; 
 if (!validate_acc_handle("acc_handle_simulated_net", hp)) return(NULL); 
 /* only nets can be collapsed and not collapsed in Cver */
 switch (hp->hrec->htyp) {
  case vpiNet: case vpiNetBit:
  case vpiReg: case vpiRegBit:
  case vpiIntegerVar: case vpiTimeVar:
   break;
  default:
   __acc_err(1710,
    "acc_handle_simulated_net object type %s illegal - must be HDL net or net bit object",
    to_acc_onam(__wrks1, hp->hrec->htyp));
   return(NULL);
 }
 return(net_h);
}

/*
 * WRITEME
 */
/*VARARGS*/
extern handle acc_handle_tchk(handle mod_p, int32 tchk_type,
 char *arg1_conn_name, int32 arg1_edgetype, ...)
{
 /* va_list va; */
 __acc_err(1941, "acc_handle_tchk not yet implemented");
 /*va_end(va); */
 return(NULL);
}

/*
 * WRITEME
 */
extern handle acc_handle_tchkarg1(handle tchk)
{
 __acc_err(1941, "acc_handle_tchkarg1 not yet implemented");
 return(NULL);
}

/*
 * WRITEME
 */
extern handle acc_handle_tchkarg2(handle tchk)
{
 __acc_err(1941, "acc_handle_tchkarg2 not yet implemented");
 return(NULL);
}

/*
 * access acc primitive (gate/switch/udp) terminal by index (out is 0)
 */
extern handle acc_handle_terminal(handle gate_handle, int32 terminal_index)
{
 struct hrec_t *hrp;
 struct h_t *hp, *hp2;
 struct gate_t *gp;

 acc_error_flag = FALSE;

 hp = (struct h_t *) gate_handle;
 if (!validate_acc_handle("acc_handle_terminal", hp)) return(NULL); 
 hrp = hp->hrec;

 if (hrp->htyp != vpiGate && hrp->htyp != vpiSwitch && hrp->htyp != vpiUdp)
  {
   __acc_err(1711,
    "acc_handle_terminal object type %s illegal - must be accPrimitive",
    to_acc_onam(__wrks1, hrp->htyp));
   return(NULL);
  }
 gp = hrp->hu.hgp;
 if (terminal_index < 0 || terminal_index >= gp->gpnum) 
  {
   __acc_err(1977,
    "acc_handle_terminal accPrimitive (%s) terminal index %d out of range",
    to_acc_onam(__wrks1, hrp->htyp), terminal_index);
   return(NULL);
  }
 hp2 = (struct h_t *) __mk_handle(vpiPrimTerm, (void *) gp, hp->hin_idp, NULL); 
 hp2->hrec->hi = terminal_index;
 return((handle) hp2);
}

/*
 * access handle to currently called PLI sys tf nth argument
 *
 * FIXME - must also allow instances and gates are args to PLI
 * sys tasks and funcs
 *
 * FIXME - special non vpi_ argument processing -
 * must be either variable (lhs) or quoted string where look up
 * using acc_handle_object rules
 */
extern handle acc_handle_tfarg(int32 n)
{
 struct hrec_t *shrp;
 vpiHandle systfp;
 struct h_t *shp;
 struct tskcall_t *tkcp;
 struct expr_t *argxp;

 acc_error_flag = FALSE;

 if ((systfp = get_acc_current_systf("acc_handle_tfarg")) == NULL)
  return(NULL);

 /* no need to validate */
 shp = (struct h_t *) systfp;
 shrp = shp->hrec;

 if (shrp->htyp == vpiSysFuncCall) argxp = shrp->hu.hxp->ru.x;
 else if (shrp->htyp == vpiSysTaskCall) 
  {
   tkcp = &(shrp->hu.hstp->st.stkc);
   argxp = tkcp->targs;
  }
 else { __acc_terr(__FILE__, __LINE__); return(NULL); }

 return(get_systf_accargobj(shp, n, argxp, "acc_handle_tfarg"));
}

/*
 * access handle to PLI sys tf object tfinst nth argument
 *
 * FIXME - must also allow instances and gates are args to PLI
 * sys tasks and funcs
 *
 * special non vpi_ argument processing -
 * must be either variable (lhs) or quoted string where look up
 * using acc_handle_object rules
 */
extern handle acc_handle_itfarg(int32 n, handle tfinst)
{
 struct hrec_t *shrp;
 struct h_t *shp;
 struct expr_t *argxp;
 struct tskcall_t *tkcp;

 acc_error_flag = FALSE;

 if (tfinst == NULL)
  {
   __acc_err(1755,
    "acc_handle_itfarg: no argument accessed because tfinst argument NULL");
   return(NULL);
  }
 
 shp = (struct h_t *) tfinst;
 if (!validate_acc_handle("acc_handle_itfarg", shp)) return(NULL); 
 shrp = shp->hrec;

 if (shrp->htyp == vpiSysFuncCall) argxp = shrp->hu.hxp->ru.x;
 else if (shrp->htyp == vpiSysTaskCall)
  {
   tkcp = &(shrp->hu.hstp->st.stkc);
   argxp = tkcp->targs;
  }
 else
  {
   __acc_err(1957,
    "acc_handle_itfarg: tfinst %s argument illegal - must be acc system tf call",
    to_acc_onam(__wrks1, shrp->htyp));
   return(NULL);
  }
 return(get_systf_accargobj(shp, n, argxp, "acc_handle_itfarg"));
}

/*
 * access systf nth argument handle (arguments in acc_ start at 1)
 *
 * FIXME - what happen when argument is instance form (no value?)
 * FIXME - must treat literal string as argument to look up handle of
 */
static handle get_systf_accargobj(struct h_t *shp, int32 n,
 struct expr_t *argxp, char *rnam)
{
 int32 argi;
 struct expr_t *xp2;
 int32 arglen, free_shp3;
 vpiHandle arghp, objp;
 struct h_t *shp2, *shp3;
 struct mod_t *mdp;
 char *argchp, s1[RECLEN];

 /* get expression corresponding to nth argument */
 if (n < 1)
  {
outofrng:
   __acc_warn(2047, "%s: argument position %d out of range", rnam, n);
   return(NULL);
  }

 for (argi = 0, xp2 = argxp; xp2 != NULL; xp2 = xp2->ru.x, argi++)
  {
   if (argi == n - 1) goto found_it;
  }
 goto outofrng; 

found_it:
 /* literal string is special case - must look up */
 if (xp2->lu.x->is_string)
  {
   argchp = __get_eval_cstr(xp2->lu.x, &arglen);

   objp = NULL;
   shp3 = NULL;
   free_shp3 = FALSE;
   /* if scope set, search there first */
   if (__acc_scope_set)
    {
     shp2 = (struct h_t *) __acc_scope_vpiobj;
     __acc_vpi_erroff = TRUE;
     /* first search for rooted - use scope next if not found */
     objp = vpi_handle_by_name(argchp, (vpiHandle) shp2);
     if (__my_vpi_chk_error())
      {
bad_vpi:
       sprintf(s1, "%s", vpi_get_str(vpiName, (vpiHandle) shp2));
       __acc_err(1975,
        "%s: search for %s in scope %s failed (possible internal error)",
        rnam, argchp, s1);
       if (free_shp3)
        {
         if (!vpi_free_object((vpiHandle) shp3))
          { __acc_terr(__FILE__, __LINE__); }
        }
       return(NULL);
      }
     if (objp != NULL)
      {
       __my_free(argchp, arglen + 1);
       return((handle) objp);
      }
    }
   else shp2 = NULL;

   /* if not found try scope of current systf */
   if (shp2 == NULL)
    {
     mdp = (struct mod_t *) shp->hin_idp[MD_MDP];
     /* convert from systf call vpi object to its scope object */
     shp3 = (struct h_t *) __mk_handle(vpiModule, (void *) mdp,
      shp->hin_idp, shp->hrec->hin_tskp);
     free_shp3 = TRUE;

     /* if current scope and systf scope name, no reason to search again */
     objp = NULL;
     if (shp2 != NULL
      && vpi_compare_objects((vpiHandle) shp3, (vpiHandle) shp2) == 0)
      goto done_ret;

     __acc_vpi_erroff = TRUE;
     /* first search for rooted - use scope next if not found */
     objp = vpi_handle_by_name(argchp, (vpiHandle) shp3);
     if (__my_vpi_chk_error()) goto bad_vpi;
     if (objp != NULL) goto done_ret;

     /* finally see if rooted XMR */
     __acc_vpi_erroff = TRUE;
     /* first search for rooted - use scope next if not found */
     objp = vpi_handle_by_name(argchp, NULL);
     if (__my_vpi_chk_error()) goto bad_vpi;

done_ret:
     if (!vpi_free_object((vpiHandle) shp3))
      { __acc_terr(__FILE__, __LINE__); }
    }
   __my_free(argchp, arglen + 1);
   return((handle) objp);
  }
 /* think anything legal here except LCB */
 if (xp2->lu.x->optyp == LCB)
  {
   __acc_err(1960,
    "%s: argument %d illegal argument - must be lvalue or literal string",
    rnam, n);
   return(NULL);
  }

 /* FIXME - tf arg instance argument core dumps */
 /* this can not currently fail */
 arghp = __mk_exprclass_handle(xp2->lu.x, shp->hin_idp, shp->hrec->hin_tskp);

 return((handle) arghp);
}

/*
 * get acc handle of calling accSysFunc[type] or accSysTask
 */
extern handle acc_handle_tfinst(void)
{
 vpiHandle systfp;
 
 acc_error_flag = FALSE;

 systfp = get_acc_current_systf("acc_handle_tfinst");
 return((handle) systfp);
}

/*
 * initialize acc interface
 *
 * usually each acc application calls this to start and acc cloxe to end 
 * following XL, initialial values are used if this is not called
 *
 * LOOKATME - think normal way to use acc_ is to start with this
 * and end processing with close - way of freeing storage
 */
extern bool acc_initialize(void)
{
 if (__acc_open)
  {
   __acc_warn(2044,
    "acc_initialize called more than once - re-initializing anyway");
  }

 /* LOOKATME - must not change internal state */

 /* LRM requires reset of configuration parameters at initialize anc close */
 init_acc_config();
 __acc_open = TRUE;
 return(TRUE);
}

/*
 * initialize routine acc config 
 */
static void init_acc_config(void)
{
 char s1[RECLEN];

 __acc_defaultattr0 = FALSE;

 sprintf(s1, "%s%s of %s\n", __vers, __vers2, __ofdt);
 if (__acc_developmentversion != NULL)
  __my_free(__acc_developmentversion, strlen(__acc_developmentversion) + 1);
 __acc_developmentversion = __my_malloc(strlen(s1) + 1);
 strcpy(__acc_developmentversion, s1);

 __acc_displayerrors = TRUE;
 __acc_displaywarnings = FALSE;
 __acc_enableargs_pth = FALSE;
 __acc_enableargs_tchk = FALSE;
 __acc_enableargs_setscope = FALSE;
 __acc_maptomipd = ACCMAPTOMIP_MAX;
 __acc_mintypmaxdelays = FALSE;
 __acc_pathdelaycount = 6;

 strcpy(s1, "$");
 if (__acc_pathdelimstr != NULL)
   __my_free(__acc_pathdelimstr, strlen(__acc_pathdelimstr) + 1);
 __acc_pathdelimstr = __my_malloc(strlen(s1) + 1);
 strcpy(__acc_pathdelimstr, s1);

 __acc_tohizdelay = ACCTOHIZ_FROMUSER;
}

/*
 * ROUTINES TO IMPLEMENT TYPE LIST GENERAL ACC NEXT 
 */

/*
 * repeatedly call acc_next for each element of array
 *
 * first time call this construct iterator containing all objects
 * iterator will contain various types of handles
 *
 * FIXME - why is accSpecParam not in this list?
 * LOOKATME - assuming for cells only cells in given cell or module scope
 * LOOKATME - for parameters assuming reg is acc int32 param type
 */
extern handle acc_next(int32 *type_list, handle h_scope, handle h_object)
{
 int32 iti, itsiz;
 struct h_t *hp, *hp2;
 vpiHandle ihref, nxth;
 struct pviter_t *iterp;
 struct acciter_t *aip;

 acc_error_flag = FALSE;

 if (h_scope != NULL)
  {
   hp = (struct h_t *) h_scope;
   if (!validate_acc_handle("acc_next", hp)) return(NULL); 
  } 

 /* first time build "giant" all inclusive iterator */
 if (h_object == NULL)
  {
   itsiz = bld_accnext_iter(type_list, h_scope);
   /* now have constructed tmp ai hptab wrk  iterator in itsiz tab */
   if (itsiz == 0) return(NULL);

   /* build the new real iterator since aith tab only tmp work tab */
   iterp = __alloc_empty_iter(itsiz, &ihref);
   for (iti = 0; iti < iterp->numhs; iti++)
    {
     /* just moving (relink) h_t rec handled used part of ai h_t ptr tab to */
     iterp->scanhptab[iti] = __aithptab[iti];
     __aithptab[iti] = NULL;
    }

   /* add iterator to special acc_next list and return */
   aip = alloc_aiter();
   /* insert on front since expect last new to be used until done */
   aip->aiter = (struct h_t *) ihref;
   __last_aiter = aip;
   __aiter_accnxt_list = NULL; 
   aip->aiternxt = __aiter_accnxt_list;
   __aiter_accnxt_list = aip;
   aip->aiterprev = NULL;
   nxth = vpi_scan(ihref);
   /* DBG reomve --- */
   if (nxth == NULL) __acc_terr(__FILE__, __LINE__);
   /* --- */
   return((handle) nxth);
  }

 /* get next - find previously built iterator */
 hp2 = (struct h_t *) h_object;
 if (!validate_acc_handle("acc_next", hp2)) return(NULL); 
 if ((aip = find_aiter_rec(__aiter_accnxt_list, hp2)) == NULL)
  {
   __acc_err(1984,
    "acc_next last object not returned by previous acc_next call");
   return(NULL);
  }
 nxth = vpi_scan((vpiHandle) aip->aiter);
 if (nxth == NULL)
  { linkout_accnext_aiter(aip); return(NULL); }

 return((handle) nxth);
}

/*
 * routine to build iterator for each legal acc next() acc_ object type
 *
 * checks, emit errors and returns iterator if one is built
 * return NULL if nothing in iterator or error
 *
 * this allocates iterator first time then adds to one passed
 */
static int32 bld_accnext_iter(int32 *atyp_list, handle scope_h)
{
 int32 iti, iti2;
 int32 oi, accnum, has_err, rm_cells, vntyp, vpiotyp, gclass, gtyp;
 vpiHandle ihref;
 struct h_t *scope_hp, *ihp; 
 struct pviter_t *iterp;
 char *onamchp;

 has_err = FALSE;
 scope_hp = (struct h_t *) scope_h;
 ihref = NULL;
 for (oi = 0, iti2 = 0;; oi++)
  {
   if ((accnum = atyp_list[oi]) == 0) break;
   
   if ((onamchp = get_accnam(accnum)) == NULL)
    {
     __acc_err(1971,
      "acc_next type_list array (pos. %d) illegal acc_ object number %d",
      oi + 1, accnum);
     has_err = TRUE;
     continue;
    }
   /* know legal acc object but nil only legal for module (insts) */
   if (scope_hp == NULL)
    {
     /* acc Top module is full type of acc Module so either legal */
     if (accnum != accTopModule && accnum != accModule)
      {
       __acc_warn(2048,
        "acc_next array (pos. %d) %s object not accTopModule but h_scope handle NULL - no objects found",
        oi + 1, onamchp);
       continue;
      }
    }
   else
    {
     if (accnum == accTopModule)
      {
       __acc_warn(2053,
       "acc_next array (pos. %d) accTopModule object but h_scope handle non NULL - no objects found",
        oi + 1);
       continue;
      }
    }

   switch (accnum) {
    /* type is module - any module (including top) */
    case accModule: case accTopModule:
    case accModuleInstance: case accCellInstance:
     if (scope_hp != NULL)
      {
       if (!nd_modscope(scope_hp)) { has_err = TRUE; continue; }
      }
   
     /* know scope consistent with module type or full type */ 
     __acc_vpi_erroff = TRUE;
     /* scope handle can be nil */
     ihref = vpi_iterate(vpiModule, (vpiHandle) scope_h);
     if (__my_vpi_chk_error())
      {
       __acc_err(1983,
        "acc_next with type_list element %s - error finding first",
        onamchp);
       has_err = TRUE;
       continue;
      }
     /* nothing in iterator - nothing to add */
     if (ihref == NULL) continue;

     /* no filtering needed - copy all elements to iterator */
     if (accnum == accModule || accnum == accTopModule) break; 
     ihp = (struct h_t *) ihref;
     rm_cells = (accnum == accModuleInstance) ? TRUE : FALSE;
     iti2 = cellinst_addto_iter(ihref, iti2, rm_cells);
     continue;

    /* variables that are types themselves but grouped together in vpi_ */ 
    case accIntegerVar: vntyp = N_INT; goto do_varnxt;
    case accRealVar: vntyp = N_REAL; goto do_varnxt;
    case accTimeVar: vntyp = N_TIME;

do_varnxt:
     /* know scope hp not nil, if nil will not get here */
     if (!nd_anyscope(scope_hp)) { has_err = TRUE; continue; }

     __acc_vpi_erroff = TRUE;
     ihref = vpi_iterate(vpiVariables, (vpiHandle) scope_h);
     if (__my_vpi_chk_error())
      {
       __acc_err(1983,
        "acc_next with type_list element %s - error finding first", onamchp);
       has_err = TRUE;
       continue;
      }
     /* nothing in iterator - nothing to add */
     if (ihref == NULL) continue;
     /* filter only right variable type */
     iti2 = var_addto_iter(ihref, iti2, vntyp);
     continue;

    case accNamedEvent:
     vpiotyp = vpiNamedEvent;  
     goto do_regnxt;
    case accRegister:
     vpiotyp = vpiReg;
     /* these have exact vpi iterators defined */
do_regnxt:
     /* know scope hp not nil, if nil will not get here */
     if (!nd_anyscope(scope_hp)) { has_err = TRUE; continue; }

     __acc_vpi_erroff = TRUE;
     ihref = vpi_iterate(vpiotyp, (vpiHandle) scope_h);
     if (__my_vpi_chk_error())
      {
       __acc_err(1983,
        "acc_next with type_list element %s - error finding first", onamchp);
       has_err = TRUE;
       continue;
      }
     /* nothing in iterator - nothing to add */
     if (ihref == NULL) continue;
     /* entire iterator added */
     break;

     /* net is type - no subtype include entire iterator */
     case accNet:
      /* net type unused but set to catch error */
      vntyp = 0;
      goto do_netnxt;
      
     /* these are full types of net */
     /* notice wand, triand, etc. same function but separated here */
     case accWire: vntyp = N_WIRE; goto do_netnxt;
     case accTri: vntyp = N_TRI; goto do_netnxt; 
     case accWand: vntyp = N_WA; goto do_netnxt;
     case accTriand: vntyp = N_TRIAND; goto do_netnxt;
     case accWor: vntyp = N_WO; goto do_netnxt;
     case accTrior: vntyp = N_TRIOR; goto do_netnxt;
     case accTri0: vntyp = N_TRI0; goto do_netnxt;
     case accTri1: vntyp = N_TRI1; goto do_netnxt;
     case accSupply0: vntyp = N_SUPPLY0; goto do_netnxt;
     case accSupply1: vntyp = N_SUPPLY1; goto do_netnxt;
     case accTrireg:
      vntyp = N_TRIREG;

do_netnxt:
     /* know scope hp not nil, if nil will not get here */
     if (!nd_anyscope(scope_hp)) { has_err = TRUE; continue; }

     __acc_vpi_erroff = TRUE;
     ihref = vpi_iterate(vpiNet, (vpiHandle) scope_h);
     if (__my_vpi_chk_error())
      {
       __acc_err(1983,
        "acc_next with type_list element %s - error finding first", onamchp);
       has_err = TRUE;
       continue;
      }
     /* nothing in iterator - nothing to add */
     if (ihref == NULL) continue;
     /* entire iterator added if net */
     if (accnum == accNet) break;

     /* filter net fulltypes */
     iti2 = var_addto_iter(ihref, iti2, vntyp);
     break; 

    /* any parameter */
    case accParameter:
    /* these are full types of parameter */
    case accIntegerParam: case accRealParam: case accStringParam:
     /* know scope hp not nil, if nil will not get here */
     /* parameters can be in any scope */
     if (!nd_anyscope(scope_hp)) { has_err = TRUE; continue; }

     __acc_vpi_erroff = TRUE;
     ihref = vpi_iterate(vpiParameter, (vpiHandle) scope_h);
     if (__my_vpi_chk_error())
      {
       __acc_err(1983,
        "acc_next with type_list element %s - error finding first", onamchp);
       has_err = TRUE;
       continue;
      }
     /* nothing in iterator - nothing to add */
     if (ihref == NULL) continue;
     /* entire iterator added if net */
     if (accnum == accParameter) break;

     /* filter net fulltypes */
     iti2 = param_addto_iter(ihref, iti2, accnum);
     continue;

    /* primitives - first is all others need full type filtering */
    case accPrimitive: gclass = 0; gtyp = 0; goto do_primnxt;

    /* these are full types of primitive */
    case accAndGate: gclass = vpiGate; gtyp = G_BITREDAND; goto do_primnxt;
    case accNandGate: gclass = vpiGate; gtyp = G_NAND; goto do_primnxt;
    case accNorGate: gclass = vpiGate; gtyp = G_NOR; goto do_primnxt;
    case accOrGate: gclass = vpiGate; gtyp = G_BITREDOR; goto do_primnxt;
    case accXnorGate: gclass = vpiGate; gtyp = G_REDXNOR; goto do_primnxt;
    case accXorGate: gclass = vpiGate; gtyp = G_BITREDXOR; goto do_primnxt;
    case accBufGate: gclass = vpiGate; gtyp = G_BUF; goto do_primnxt;
    case accNotGate: gclass = vpiGate; gtyp = G_NOT; goto do_primnxt;
    case accBufif0Gate: gclass = vpiGate; gtyp = G_BUFIF0; goto do_primnxt;
    case accBufif1Gate: gclass = vpiGate; gtyp = G_BUFIF1; goto do_primnxt;
    case accNotif0Gate: gclass = vpiGate; gtyp = G_NOTIF0; goto do_primnxt;
    case accNotif1Gate: gclass = vpiGate; gtyp = G_NOTIF1; goto do_primnxt;
    case accNmosGate: gclass = vpiGate; gtyp = G_NMOS; goto do_primnxt;
    case accPmosGate: gclass = vpiGate; gtyp = G_PMOS; goto do_primnxt;
    case accRnmosGate: gclass = vpiGate; gtyp = G_RNMOS; goto do_primnxt;
    case accRpmosGate: gclass = vpiGate; gtyp = G_RPMOS; goto do_primnxt;
    case accCmosGate: gclass = vpiGate; gtyp = G_CMOS; goto do_primnxt;
    case accRcmosGate: gclass = vpiGate; gtyp = G_RCMOS; goto do_primnxt;
    case accRtranGate: gclass = vpiSwitch; gtyp = G_RTRAN; goto do_primnxt;
    case accRtranif0Gate:
     gclass = vpiSwitch; gtyp = G_RTRANIF0; goto do_primnxt;
    case accRtranif1Gate:
     gclass = vpiSwitch; gtyp = G_RTRANIF1; goto do_primnxt;
    case accTranGate: gclass = vpiSwitch; gtyp = G_TRAN; goto do_primnxt;
    case accTranif0Gate: gclass = vpiSwitch; gtyp = G_TRANIF0; goto do_primnxt;
    case accTranif1Gate: gclass = vpiSwitch; gtyp = G_TRANIF1; goto do_primnxt;
    case accPulldownGate: gclass = vpiGate; gtyp = G_PULLDOWN; goto do_primnxt;
    case accPullupGate: gclass = vpiGate; gtyp = G_PULLUP; goto do_primnxt;
    case accSeqPrim: gclass = vpiUdp; gtyp = vpiSeqPrim; goto do_primnxt;
    case accCombPrim: gclass = vpiUdp; gtyp = vpiCombPrim; 

do_primnxt:
     /* know scope hp not nil, if nil will not get here */
     if (!nd_anyscope(scope_hp)) { has_err = TRUE; continue; }

     __acc_vpi_erroff = TRUE;
     ihref = vpi_iterate(vpiNet, (vpiHandle) scope_h);
     if (__my_vpi_chk_error())
      {
       __acc_err(1983,
        "acc_next with type_list element %s - error finding first", onamchp);
       has_err = TRUE;
       continue;
      }
     /* nothing in iterator - nothing to add */
     if (ihref == NULL) continue;
     /* entire iterator added if net */
     if (accnum == accNet) break;

     /* filter net fulltypes */
     iti2 = prim_addto_iter(ihref, iti2, gclass, gtyp);
     continue;

    default:
     __acc_err(1971,
      "acc_next array (pos. %d) %s object illegal in object_type_array",
      oi + 1, onamchp);
     has_err = TRUE;
     continue;
   }

   /* non filtering case, copy entire iterator into accumulator */
   ihp = (struct h_t *) ihref;
   iterp = ihp->hrec->hu.hiterp;
   if (iterp->numhs + iti2 >= __aithtsiz)
    {
    /* arg is num to add, so just add size of entire iter to be added */
     __grow_acc_hptab(iterp->numhs);
    }

   /* copy iterator into ia wrk h_t rec ptr tab starting at iti2 */ 
   for (iti = 0; iti < iterp->numhs; iti++)
    { 
     __aithptab[iti2] = iterp->scanhptab[iti];
     iterp->scanhptab[iti] = NULL;
     iti2++;
    }
   acc_internal_itfree(ihp);
  }
 return(iti2);
}

/*
 * check for scope that must be module
 */
static int32 nd_modscope(struct h_t *hp)
{
 if (hp->hrec->htyp != vpiModule)
  {
   __acc_err(1725, "acc_next: scope object %s illegal must be accModule",
    to_acc_onam(__wrks1, hp->hrec->htyp));
   return(FALSE);
  }
 return(TRUE);
}

/*
 * check for scope that must be module
 */
static int32 nd_anyscope(struct h_t *hp)
{
 switch (hp->hrec->htyp) {
  case vpiModule: case vpiTask: case vpiFunction:
  case vpiNamedBegin: case vpiNamedFork:
   break;
  default:
   __acc_err(1726, "acc_next: scope_h %s illegal - not required scope object",
    to_acc_onam(__wrks1, hp->hrec->htyp));
   return(FALSE);
  }
 return(TRUE);
}

/*
 * add to accumlator tmp work iterator with cell/inst filtering
 * returns new size of accumulator iterator table
 *
 * know iterator contains at least one element but may not add any
 * area inserted is from passed iti2 to iti2 + num hs in new iterator
 */
static int32 cellinst_addto_iter(vpiHandle ihref, int32 iti2, int32 rm_cells)
{
 int32 iti;
 struct h_t *hp2;
 struct pviter_t *iterp;
 struct mod_t *mdp;
 struct h_t *ihp;

 ihp = (struct h_t *) ihref;
 iterp = ihp->hrec->hu.hiterp;
 for (iti = 0; iti < iterp->numhs; iti++)
  {
   hp2 = iterp->scanhptab[iti];
   mdp = (struct mod_t *) hp2->hin_idp[MD_MDP];
   /* remove if wrong full type */
   if (rm_cells)
    {
     if (mdp->m_iscell) continue;
    }
   else
    { 
     if (!mdp->m_iscell) continue;
    }
   /* SJM 11/02/04 - previous fix was wrong - this must be htab size not 2 */
   if (iti2 >= __aithtsiz) __grow_acc_hptab(1);

   /* move h_t hp handle object from iterator h_t rec ptrs to wrk tab */
   __aithptab[iti2] = hp2;
   iterp->scanhptab[iti] = NULL;
   iti2++;
  }
 acc_internal_itfree(ihp);
 return(iti2);
}

/*
 * free internal work acc_ iterator (version one - know know alloc exprs)
 *
 * free iterator struct and tables but know no allocated expr
 */
static void acc_internal_itfree(struct h_t *ihp)
{
 int32 iti;
 struct h_t *hp;
 struct pviter_t *iterp;

 iterp = ihp->hrec->hu.hiterp;
 for (iti = 0; iti < iterp->numhs; iti++)
  {
   hp = iterp->scanhptab[iti];
   if (hp != NULL) { __free_hp(hp); iterp->scanhptab[iti] = NULL; }
  }
 __my_free(iterp->scanhptab, iterp->numhs*sizeof(struct h_t **));
 iterp->scanhptab = NULL;
 __my_free(iterp, sizeof(struct pviter_t));
 /* zero and free and put on vpi handle free list */
 __free_hp(ihp);
}

/*
 * add to accumlator iterator with filtered net type for variables
 * returns new size of accumulator iterator table
 *
 * 2 uses: separates variable (real, time, int32) and separate nets
 * into subtype
 *
 * know iterator contains at least one element but may not add any
 */
static int32 var_addto_iter(vpiHandle ihref, int32 iti2, int32 vntyp)
{
 int32 iti;
 struct h_t *hp2;
 struct pviter_t *iterp;
 struct net_t *np;
 struct h_t *ihp;

 ihp = (struct h_t *) ihref;
 iterp = ihp->hrec->hu.hiterp;

 for (iti = 0; iti < iterp->numhs; iti++)
  {
   hp2 = iterp->scanhptab[iti];
   np = hp2->hrec->hu.hnp;
   /* know this is one of real, integer, or time */
   if (np->ntyp != vntyp) continue;
   if (iti2 >= __aithtsiz) __grow_acc_hptab(1);

   /* know no malloced expr to deal with - but must copy 2 parts */
   __aithptab[iti2] = hp2;
   iterp->scanhptab[iti] = NULL; 
   iti2++;
  }
 acc_internal_itfree(ihp);
 return(iti2);
}

/*
 * add to accumlator iterator with filtered param type 
 * returns new size of accumulator iterator table
 *
 * LOOKATME - making all non string and non real 
 *
 * know iterator contains at least one element but may not add any
 */
static int32 param_addto_iter(vpiHandle ihref, int32 iti2, int32 aotyp)
{
 int32 iti;
 struct h_t *hp2;
 struct pviter_t *iterp;
 struct h_t *ihp;
 struct net_t *np;

 ihp = (struct h_t *) ihref;
 iterp = ihp->hrec->hu.hiterp;

 for (iti = 0; iti < iterp->numhs; iti++)
  {
   hp2 = iterp->scanhptab[iti];
   np = hp2->hrec->hu.hnp;

   if (aotyp == accIntegerParam)
    {
     if (np->ntyp == N_REAL || np->nu.ct->pstring) continue;
    }
   else if (aotyp == accRealParam)
    {
     if (np->ntyp != N_REAL) continue;
    }
   else if (aotyp == accStringParam)
    {
     if (np->ntyp == N_REAL) continue;
     if (!np->nu.ct->pstring) continue;
    }
   else __acc_terr(__FILE__, __LINE__);

   if (iti2 >= __aithtsiz) __grow_acc_hptab(1);
   /* know no malloced expr to deal with */
   /* just relinking h_t rec from iterator to work ait hp tab */
   __aithptab[iti2] = hp2;
   iterp->scanhptab[iti] = NULL;
   iti2++;
  }
 acc_internal_itfree(ihp);
 return(iti2);
}

/*
 * add to accumlator iterator with filtered primitive full type
 * returns new size of accumulator iterator table
 *
 * called with primitive full type and filters out all but passed gate
 * full type
 *
 * know iterator contains at least one element but may not add any
 */
static int32 prim_addto_iter(vpiHandle ihref, int32 iti2, int32 gclass,
 int32 gtyp)
{
 int32 iti;
 int32 pclasstyp;
 struct h_t *hp2;
 struct pviter_t *iterp;
 struct primtab_t *ptp;
 struct h_t *ihp;
 struct gate_t *gp;

 ihp = (struct h_t *) ihref;
 iterp = ihp->hrec->hu.hiterp;

 for (iti = 0; iti < iterp->numhs; iti++)
  {
   hp2 = iterp->scanhptab[iti];

   gp = hp2->hrec->hu.hgp;

   /* filter out non full type matching by continuing */
   if (gp->g_class == GC_UDP)
    {
     if (gclass != vpiUdp) continue;

     if (gp->gmsym->el.eudpp->utyp == U_COMB)
      { if (gtyp != vpiCombPrim) continue; }
     else { if (gtyp != vpiSeqPrim) continue; }
    }
   else
    {
     /* if gate class do not match, do not check more */
     pclasstyp = __gate_to_vpiprimtyp(gp);
     if (pclasstyp != gclass) continue;
     ptp = gp->gmsym->el.eprimp; 
     if (ptp->gateid != gtyp) continue;
    } 

   /* grow by 3/2 fibronacci + 1 for new element */
   if (iti2 >= __aithtsiz) __grow_acc_hptab(1);
   /* know no malloced expr to deal with */
   __aithptab[iti2] = hp2;
   iterp->scanhptab[iti] = NULL; 
   iti2++;
  }
 acc_internal_itfree(ihp);
 return(iti2);
}

/*
 * grow acc work handle table (must add at least addnum) but do not
 * see the ptrs to the h_t records
 *
 * SJM 06-22-10 - this now just grows the word tmp h_t record ptr tab
 * old part ptrs to h_t records will be right - others set to nil
 */
extern void __grow_acc_hptab(int32 addnum)
{
 int32 iti;
 int32 nnum;
 size_t old_aithtsiz, osize, nsize;

 /* only allocate if accessing driver/load style handles at all */ 
 if (__aithtsiz == 0)
  {
   nnum = 1000 + addnum;
   __aithptab = (struct h_t **) __my_malloc(nnum*sizeof(struct h_t *));
   __aithtsiz = nnum; 
   /* set new elements to nil so will alloc the h_t rec */
   for (iti = 0; iti < __aithtsiz; iti++) __aithptab[iti] = NULL;
   return;
  }

 old_aithtsiz = __aithtsiz;
 osize = old_aithtsiz*sizeof(struct h_t *);
 __aithtsiz = addnum + (3*__aithtsiz)/2; 
 nsize = __aithtsiz*sizeof(struct h_t *);
 __aithptab = (struct h_t **) __my_realloc(__aithptab, osize, nsize);
 /* SJM 06-22-10 - the iterator tab is now just ptrs to h_t recs */
 /* set new ones to pt to nil */
 for (iti = old_aithtsiz; iti < __aithtsiz; iti++) __aithptab[iti] = NULL;
}


/*
 * grow 2nd for subtree processing  global work handle table
 */
extern void __grow_acc_hptab2(int32 addnum)
{
 int32 iti;
 int32 nnum;
 size_t old_aithtsiz2, osize, nsize, ohrsize, nhrsize;

 /* only allocate if accessing driver/load style handles at all */ 
 if (__aithtsiz2 == 0)
  {
   nnum = 1000 + addnum;
   __aithptab2 = (struct h_t **) __my_malloc(nnum*sizeof(struct h_t *));
   __aithtsiz2 = nnum; 
   /* set new elements to nil so will alloc the h_t rec */
   for (iti = 0; iti < __aithtsiz2; iti++) __aithptab2[iti] = NULL;
   return;
  }
 old_aithtsiz2 = __aithtsiz2;
 osize = old_aithtsiz2*sizeof(struct h_t);
 ohrsize = old_aithtsiz2*sizeof(struct hrec_t);
 __aithtsiz2 = addnum + (3*__aithtsiz2)/2; 
 nsize = __aithtsiz2*sizeof(struct h_t);
 nhrsize = __aithtsiz2*sizeof(struct hrec_t);
 __aithptab2 = (struct h_t **) __my_realloc(__aithptab2, osize, nsize);

 /* SJM 06-22-10 - the iterator tab is now just ptrs to h_t recs */
 /* set new ones to pt to nil */
 for (iti = old_aithtsiz2; iti < __aithtsiz2; iti++) __aithptab2[iti] = NULL;
}

/*
 * ROUTINES TO IMPLEMENT OBJECT SPECIFIC ACC NEXT
 */

/*
 * get next bit from port, vector, or path terminal
 *
 * scalars (one bit) treated as one bit vector here (returns object itself)
 */
extern handle acc_next_bit(handle vector, handle bit)
{  
 struct hrec_t *hrp;
 struct h_t *hp;
  
  acc_error_flag = FALSE;
  
  hp = (struct h_t *) vector;
  if (!validate_acc_handle("acc_next_bit", hp)) return(NULL); 
  hrp = hp->hrec;
  
  if (hrp->htyp == vpiPort) return(portbit_accnext(vector, bit));
  
  /* LOOKATME - are bits of int32 and time var accessible - think yes */
  if (hrp->htyp == vpiNet || hrp->htyp == vpiReg || hrp->htyp == vpiIntegerVar
   || hrp->htyp == vpiTimeVar) 
   {
    return(netbit_accnext(vector, bit));
   }
  if (hrp->htyp == vpiPathTerm)
   {
    /* WRITEME */
    __acc_err(1941, "acc_next_bit for accPathTerminal not yet implemented");
    return(NULL);
   }
  __acc_err(1728, "acc_next_bit: object %s does not have next bit",
   to_acc_onam(__wrks1, hrp->htyp));
  return(NULL);
}

/*
 * do acc next bit for port bits
 */
static handle portbit_accnext(handle port, handle bit)
{
 struct h_t *hp2; 
 vpiHandle ihref, nxth;
 struct acciter_t *aip;

 /* build the iterator since this is first time */
 if (bit == NULL)
  {
   __acc_vpi_erroff = TRUE;
   ihref = vpi_iterate(vpiBit, (vpiHandle) port);
   if (__my_vpi_chk_error())
    {
     __acc_err(1983, "acc_next_bit error finding first accPortBit");
     return(NULL);
    }
   if (ihref == NULL) return(NULL);
 
   aip = alloc_aiter();
   /* insert on front since expect last new to be used until done */
   aip->aiter = (struct h_t *) ihref;
   __last_aiter = aip;

   /* SJM 02/11/00 - table indexed by object returned not by iterator */
   aip->aiternxt = __aiter_tab[vpiPortBit]; 
   __aiter_tab[vpiPortBit] = aip;
   aip->aiterprev = NULL;
   nxth = vpi_scan(ihref);
   /* DBG reomve --- */
   if (nxth == NULL) __acc_terr(__FILE__, __LINE__);
   /* --- */
   return((handle) nxth);
  }
 /* get next - find previously built iterator */
 hp2 = (struct h_t *) bit;
 if (!validate_acc_handle("acc_next_bit", hp2)) return(NULL); 
 if (hp2->hrec->htyp != vpiPortBit)
  {
   wrong_nxtobj_error("acc_next_bit", hp2->hrec->htyp, accPortBit); 
   return(NULL);
  }
 if ((aip = find_aiter_rec(__aiter_tab[vpiPortBit], hp2)) == NULL)
  {
   __acc_err(1984,
    "acc_next_bit last accPortBit object not returned by previous acc_next_bit call");
   return(NULL);
  }
 nxth = vpi_scan((vpiHandle) aip->aiter);
 if (nxth == NULL)
  { linkout_aiter(aip, vpiPortBit, FALSE); return(NULL); }

 return((handle) nxth);
}

/*
 * do acc next bit for net/reg bits
 */
static handle netbit_accnext(handle vector, handle bit)
{
 int32 vpibtyp;
 struct h_t *hp, *hp2; 
 struct net_t *np;
 vpiHandle ihref, nxth;
 struct pviter_t *iterp;
 struct acciter_t *aip;
 struct hrec_t *hrp;

 hp = (struct h_t *) vector;
 hrp = hp->hrec;
 np = hrp->hu.hnp;
 if (hrp->htyp == vpiReg) vpibtyp = vpiRegBit;
 else if (hrp->htyp == vpiIntegerVar || hrp->htyp == vpiTimeVar)
  vpibtyp = vpiVarSelect;
 else if (hrp->htyp == vpiNet) vpibtyp = vpiNetBit;
 else 
  { 
   __acc_err(1983, "acc_next_bit for object %s llegal",
    to_acc_onam(__wrks1, hrp->htyp));
   return(NULL);
  }

 /* build the iterator since this is first time */
 if (bit == NULL)
  {
   /* scalars are legal and just return the one bit */
   if (!np->n_isavec)
    {
     /* can not use vpi iterate for scalars */
     /* LOOKATME - is this really a bit handle for a scalar - LRM say so */
     /* build special 1 element acc iterator - then treat as normal case */
     iterp = __alloc_empty_iter(1, &ihref);
     __iter_fill_with_empty(iterp);

     hp2 = iterp->scanhptab[0];
     if (np->ntyp >= NONWIRE_ST) hp2->hrec->htyp = vpiRegBit;
     else hp2->hrec->htyp = vpiNetBit;
     hp2->hrec->hu.hnp = np; 
     hp2->hrec->bith_ndx = TRUE;
     hrp->hi = 0;
     hp2->hin_idp = hp->hin_idp;
    }
   else
    {
     __acc_vpi_erroff = TRUE;
     ihref = vpi_iterate(vpiBit, (vpiHandle) vector);
     if (__my_vpi_chk_error())
      {
       __acc_err(1983, "acc_next_bit error finding first %s",
        to_acc_onam(__wrks1, vpibtyp));
       return(NULL);
      }
     /* can only happen if empty or error for bit of iterators */
     if (ihref == NULL) return(NULL);
    }

   aip = alloc_aiter();
   /* insert on front since expect last new to be used until done */
   aip->aiter = (struct h_t *) ihref;
   __last_aiter = aip;
   /* using type of vector handle (master object) */ 
   /* SJM 02/11/00 - table indexed by object returned not by iterator */
   aip->aiternxt = __aiter_tab[vpibtyp]; 
   __aiter_tab[vpibtyp] = aip;
   aip->aiterprev = NULL;
   nxth = vpi_scan(ihref);
   /* DBG reomve --- */
   if (nxth == NULL) __acc_terr(__FILE__, __LINE__);
   /* --- */
   return((handle) nxth);
  }
 /* get next - find previously built iterator */
 hp2 = (struct h_t *) bit;
 if (!validate_acc_handle("acc_next_bit", hp2)) return(NULL); 

 if (hp2->hrec->htyp != vpibtyp)
  {
   struct vpi_to_acc_t *accvpip;

   /* SJM 05/14/01 - error needs acc type not vpi */
   accvpip = &(vpi_to_acc[hp->hrec->htyp]);
   wrong_nxtobj_error("acc_next_bit", hp2->hrec->htyp,
    accvpip->acc_otyp);
   return(NULL);
  }

 if ((aip = find_aiter_rec(__aiter_tab[vpibtyp], hp2)) == NULL)
  {
   __acc_err(1984,
    "acc_next_bit last %s object not returned by previous acc_next_bit call",
    to_acc_onam(__wrks1, hp2->hrec->htyp));
   return(NULL);
  }
 ihref = (vpiHandle) aip->aiter;
 nxth = vpi_scan(ihref);
 if (nxth == NULL) { linkout_aiter(aip, vpibtyp, FALSE); return(NULL); }
 return((handle) nxth);
}

/*
 * find right iterator given type (vpi) and previous 
 *
 * linear search needed but will normally be only one
 */
static struct acciter_t *find_aiter_rec(struct acciter_t *aip,
 struct h_t *lasthp)
{
 struct pviter_t *iterp; 
 struct h_t *ihp, *hp2;

 for (; aip != NULL; aip = aip->aiternxt)
  {
   ihp = aip->aiter;
   /* DBG remove -- */
   if (ihp->hrec == NULL) __acc_terr(__FILE__, __LINE__);
   /* -- */
   iterp = ihp->hrec->hu.hiterp;
   
   /* DBG remove -- */
   if (iterp->nxthi == 0) __acc_terr(__FILE__, __LINE__);
   /* --- */
   hp2 = iterp->scanhptab[iterp->nxthi - 1];
   /* last object must be point to exactly same address */ 
   /* ??? FIXME - this must match last returned or error - where emitted */
   if (lasthp == hp2) return(aip); 
  }
 return(NULL);
}

/*
 * get next cell for all module instances under scope
 *
 * stop at cells but descend into module instances
 * no vpi_ iterator for all cells under - must build special acc iterator
 */
extern handle acc_next_cell(handle scope, handle cell)
{
 struct h_t *hp, *hp2, *ihp; 
 vpiHandle ihref, nxth;
 struct acciter_t *aip;
 struct mod_t *mdp;

 acc_error_flag = FALSE;

 hp = (struct h_t *) scope;
 if (!validate_acc_handle("acc_next_cell", hp)) return(NULL); 

 if (hp->hrec->htyp != vpiModule)
  {
   __acc_err(1729, "acc_next_cell: scope object %s illegal must be accModule",
    to_acc_onam(__wrks1, hp->hrec->htyp));
   return(NULL);
  }

 hp = (struct h_t *) scope;
 /* build the iterator since this is first time */
 if (cell == NULL)
  {
   /* SJM 10/23/00 - no vpi iterator since need special acc cells build */
   /* although this is not vpi_ iterator build as special inst (mod) type */
   /* if empty iterator so nothing ih tab this returns nil */
   ihp = (struct h_t *) bld_acc_cells_iter(hp);
   if (ihp == NULL) return(NULL);
   ihref = (vpiHandle) ihp;
 
   aip = alloc_aiter();
   /* insert on front since expect last new to be used until done */
   aip->aiter = (struct h_t *) ihref;
   __last_aiter = aip;

   aip->aiternxt = __aiter_tab[vpiModule]; 
   __aiter_tab[vpiModule] = aip;
   aip->aiterprev = NULL;
   nxth = vpi_scan(ihref);
   /* DBG reomve --- */
   if (nxth == NULL) __acc_terr(__FILE__, __LINE__);
   /* --- */
   return((handle) nxth);
  }
 /* get next - find previously built iterator */
 hp2 = (struct h_t *) cell;
 if (!validate_acc_handle("acc_next_cell", hp2)) return(NULL); 

 mdp = (struct mod_t *) hp2->hin_idp[MD_MDP];
 if (hp2->hrec->htyp != vpiModule || !mdp->m_iscell)
  {
   wrong_nxtobj_error("acc_next_cell", hp2->hrec->htyp, accModule); 
   return(NULL);
  }

 /* LOOKATME could emit error if not under scope - but caught here */ 
 if ((aip = find_aiter_rec(__aiter_tab[vpiModule], hp2)) == NULL)
  {
   __acc_err(1984,
    "acc_next_cell last accModule (accCellInstance) object not returned by previous acc_next_cell call");
   return(NULL);
  }
 nxth = vpi_scan((vpiHandle) aip->aiter);
 if (nxth == NULL) { linkout_aiter(aip, vpiModule, FALSE); return(NULL); }
 return((handle) nxth);
}

/*
 * build cells under instance scope iterator - only for acc
 */
static vpiHandle bld_acc_cells_iter(struct h_t *hp)
{
 int32 iti;
 int32 num, cnum;
 vpiHandle ihref;
 struct pviter_t *iterp;

 /* collect all cells and instances into first ith tab iterator */
 /* number used is num */
 if ((num = collect_loc_insts(hp)) == 0) return(NULL);

 /* copy from ait hp tab to ait hp tab2 descending into inst to find cells */ 
 cnum = addto_acc_cells_iter(hp, num, 0);
 if (cnum == 0) return(NULL);

 /* build the new iterator from 2nd work ithtab */
 iterp = __alloc_empty_iter(cnum, &ihref);
 for (iti = 0; iti < iterp->numhs; iti++)
  {
   iterp->scanhptab[iti] = __aithptab2[iti];
   __aithptab2[iti] = NULL;
  }
 return(ihref);
}

/*
 * collect local cells and instances into iterator
 * hp is scope under which all instances are collected
 *
 * places cells into work ith tab that is over-written
 */
static int32 collect_loc_insts(struct h_t *hp)
{
 int32 ii;
 struct hrec_t *hrp2;
 struct itree_t *itp, *itp2;
 struct h_t *hp2;
 struct mod_t *mdp;

 itp = (struct itree_t *) hp->hin_idp[MD_ITP];
 mdp = itp->itip->imsym->el.emdp;
 for (ii = 0; ii < mdp->minum; ii++)
  {
   if (ii >= __aithtsiz) __grow_acc_hptab(1);

  hp2 = __get_new_hp_handle();
  __aithptab[ii] = hp2;

   /* not using alloc iter so need to set in iter bit explicitly */
   hrp2 = hp2->hrec;
   hrp2->in_iter = TRUE;
   hrp2->htyp = vpiModule;
   itp2 = &(itp->in_its[ii]);
   hrp2->hu.hmdp = itp2->itip->imsym->el.emdp;
   hp2->hin_idp = itp2->it_idp;
  }
 return(mdp->minum);
}

/*
 * add to local loads inside itree loc as net/bit handle hp
 *
 * know first work ith tab filled with local loads 
 * fill (add to) second work ith tab2 starting at cnum
 *
 * FIXME why is hp not used
 */
static int32 addto_acc_cells_iter(struct h_t *hp, int32 locnum, int32 cnum)
{
 int32 ii;
 int32 newcnum;
 struct h_t *hp2;
 struct mod_t *mdp;

 for (ii = 0; ii < locnum; ii++)
  {
   hp2 = __aithptab[ii]; 
   mdp = (struct mod_t *) hp2->hin_idp[MD_MDP];
   /* if cell add (move copying guts) and do not descend */
   if (mdp->m_iscell)
    {
     if (cnum >= __aithtsiz2)
      { 
       __grow_acc_hptab2(cnum - __aithtsiz2 + 1);
      }
     /* this just moves link */
     __aithptab2[cnum] = hp2;
     __aithptab[ii] = NULL;
     cnum++;
     continue;
    }

   /* if instance descend and copy cells in */
   /* this fills (and over-writes) first ith tab that is then copied */
   /* into final table starting at point just after last one added */
   newcnum = collect_loc_insts(hp2);
   if (newcnum == 0) continue;
   cnum = addto_acc_cells_iter(hp2, newcnum, cnum);
  }
 return(cnum);
}

/*
 * get primitive terminal in cell (only one) loads (inputs) of a net 
 *
 * this is same as vpiLoad except 1) only primitive terminals,
 * 2) only terminals in cells, 3) only one terminal per cell
 */
extern handle acc_next_cell_load(handle net_handle, handle load)
{
 return(do_acc_next_ld_drv("acc_next_cell_load", net_handle, load));
}

/*
 * execute any acc_next load or drivers iterators
 *
 * all the same except for building the vpi iterator
 */
static handle do_acc_next_ld_drv(char *rtnnam, handle net_handle, 
 handle ld_drv)
{
 struct h_t *hp, *hp2; 
 vpiHandle ihref, nxth;
 struct acciter_t *aip;

 acc_error_flag = FALSE;

 hp = (struct h_t *) net_handle;
 if (!validate_acc_handle(rtnnam, hp)) return(NULL); 

 /* net handle must be scalar reg/net or reg/net bit */
 if (hp->hrec->htyp == vpiNet || hp->hrec->htyp == vpiReg)
  {
   if (hp->hrec->hu.hnp->nwid != 1)
    {
     __acc_err(1982,
      "%s %s vector illegal - only net/reg bit or scalar allowed",
      rtnnam, to_acc_onam(__wrks1, hp->hrec->htyp));
     return(NULL);
    }
  }
 else if (hp->hrec->htyp != vpiNetBit && hp->hrec->htyp != vpiRegBit)
  { 
   __acc_err(1731, "%s: %s object illegal net_handle", rtnnam,
    to_acc_onam(__wrks1, hp->hrec->htyp));
   return(NULL);
  }

 /* build the iterator since this is first time */
 if (ld_drv == NULL)
  {
   if (strcmp(rtnnam, "acc_next_cell_load") == 0)
    ihref = bld_cell_load_iter(hp);
   else if (strcmp(rtnnam, "acc_next_load") == 0)
    ihref = bld_load_iter(hp);
   else if (strcmp(rtnnam, "acc_next_driver") == 0)
    ihref = bld_driver_iter(hp);
   else { __acc_terr(__FILE__, __LINE__); return(NULL); }

   /* can only happen if error for bit of iterators */
   if (ihref == NULL) return(NULL);

   aip = alloc_aiter();
   /* insert on front since expect last new to be used until done */
   aip->aiter = (struct h_t *) ihref;
   __last_aiter = aip;

   /* using vpiPrimitive since that is "acc" only(?) possible driver/load */
   aip->aiternxt = __aiter_tab[vpiPrimTerm]; 
   __aiter_tab[vpiPrimTerm] = aip;
   aip->aiterprev = NULL;
   nxth = vpi_scan(ihref);
   /* DBG reomve --- */
   if (nxth == NULL) __acc_terr(__FILE__, __LINE__);
   /* --- */
   return((handle) nxth);
  }
 /* get next - find previously built iterator */
 hp2 = (struct h_t *) ld_drv;
 if (!validate_acc_handle(rtnnam, hp2)) return(NULL); 

 if (hp2->hrec->htyp != vpiPrimTerm)
  {
   wrong_nxtobj_error(rtnnam, hp2->hrec->htyp, accTerminal); 
   return(NULL);
  }

 /* LOOKATME could emit error if not in subtree - but caught here */ 
 if ((aip = find_aiter_rec(__aiter_tab[vpiPrimTerm], hp2)) == NULL)
  {
   __acc_err(1984,
    "%s last accTerminal object not returned by previous %s call",
    rtnnam, rtnnam);
   return(NULL);
  }
 ihref = (vpiHandle) aip->aiter;
 nxth = vpi_scan(ihref);
 /* SJM 02/11/99 - this must be prim terminal - was wrong net */
 if (nxth == NULL) { linkout_aiter(aip, vpiPrimTerm, FALSE); return(NULL); }
 return((handle) nxth);
}

/*
 * build the cell load prim term only iterator
 *
 * build vpi load iterator then filter out any not primitive terminals,
 * and not in cells and >1 terminal per cell
 *
 * this builds free then builds final iterator
 */
static vpiHandle bld_cell_load_iter(struct h_t *hp)
{
 int32 iti;
 int32 iti2, iti3, *ndcptab;
 struct h_t *hp2, *hp3, *ihp;
 vpiHandle ihref;
 struct pviter_t *iterp;
 struct mod_t *mdp;

 __acc_vpi_erroff = TRUE;
 ihref = vpi_iterate(vpiLoad, (vpiHandle) hp);
 if (__my_vpi_chk_error())
  {
   __acc_err(1983, "acc_next_cell_load error finding first %s",
    to_acc_onam(__wrks1, hp->hrec->htyp));
   return(NULL);
  }
 /* if no loads, must pass nil up */
 if (ihref == NULL) return(NULL);

 ihp = (struct h_t *) ihref;
 iterp = ihp->hrec->hu.hiterp;
 /* go through iterator copying only terminals in cells into ait hp tab */
 /* also elminate non primitive vpi but not acc_ terminals here */
 for (iti = iti2 = 0; iti < iterp->numhs; iti++)
  {
   hp2 = iterp->scanhptab[iti];

   mdp = (struct mod_t *) hp2->hin_idp[MD_MDP];
   if (!mdp->m_iscell) continue;

   /* SJM 11/02/04 - ### ??? does this need to be removed not match PLI book */
   if (hp2->hrec->htyp != vpiPrimTerm) continue;

   if (iti2 >= __aithtsiz) __grow_acc_hptab(1);
   __aithptab[iti2] = hp2;
   /* set iterator nil since moved handle to work scan h_t rec ptr tab */
   /* SJM 06-22-10 - need special case iterator free here */
   iterp->scanhptab[iti] = NULL;
   iti2++;
  }
 /* SJM 06-22-10 - can free iterator here and need to for empty case */
 acc_internal_itfree(ihp);
 if (iti2 == 0) return(NULL);

 /* filter out more than one terminal in cell copying by marking */
 /* FIXME - this is slow (n**2) - should build array and sort for next */
 /* marking needed because must always return first in cell */

 ndcptab = (int32 *) __my_malloc(iti2*sizeof(int32));
 /* assume all are copied */
 for (iti = 0; iti < iti2; iti++) ndcptab[iti] = TRUE; 

 for (iti = 0; iti < iti2; iti++)
  {
   /* since copying only first, if this is repeated after first ignore */
   if (!ndcptab[iti]) continue;
   hp2 = __aithptab[iti];
   for (iti3 = iti + 1; iti3 < iti2; iti3++)
    {
     /* already marked not to copy */
     if (!ndcptab[iti3]) continue;

     hp3 = __aithptab[iti3];
     if (hp2->hin_idp == hp3->hin_idp) 
      {
       /* mark after first to not copy - must keep looking */
       ndcptab[iti3] = FALSE;
      }
    }
  }
 /* now copy into second ith tab */
 for (iti = 0, iti3 = 0; iti < iti2; iti++)
  {
   if (ndcptab[iti])
    {
     /* SJM 11/30/04 - since growning htab2 must test against htab2 size */
     if (iti3 >= __aithtsiz2) __grow_acc_hptab2(1);

     /* can copy guts because know these are prim terms with no ptrs */
     __aithptab2[iti3] = __aithptab[iti];
     __aithptab[iti] = NULL; 
     iti3++;
    }
  }
 iterp = __alloc_empty_iter(iti3, &ihref);
 __my_free(ndcptab, iti2*sizeof(int32));

 /* copy h_t ptr into iterator */
 for (iti = 0; iti < iti3; iti++)
  {
   iterp->scanhptab[iti] = __aithptab2[iti];
   __aithptab2[iti] = NULL;
  }
 return(ihref);
}

/*
 * get accModule (instances) inside mod_handle 
 *
 * if mod_handle is nil, get top modules
 */
extern handle acc_next_child(handle mod_handle, handle child)
{
 struct h_t *hp, *hp2; 
 vpiHandle ihref, nxth;
 struct acciter_t *aip;
 struct itree_t *itp;

 acc_error_flag = FALSE;

 /* nil scope case - same as acc next topmod */
 if (mod_handle == NULL)
  {
   return(do_acc_child_topmod("acc_next_child (NULL scope)", child));
  }

 hp = (struct h_t *) mod_handle;
 if (!validate_acc_handle("acc_next_child", hp)) return(NULL); 

 if (hp->hrec->htyp != vpiModule)
  {
   __acc_err(1732, "acc_next_child: scope object %s illegal must be accModule",
    to_acc_onam(__wrks1, hp->hrec->htyp));
   return(NULL);
  }

 /* build the iterator since this is first time */
 if (child == NULL)
  {
   __acc_vpi_erroff = TRUE;
   ihref = vpi_iterate(vpiModule, (vpiHandle) mod_handle);
   if (__my_vpi_chk_error())
    {
     __acc_err(1983, "acc_next_child error finding first child accModule");
     return(NULL);
    }
   if (ihref == NULL) return(NULL);
 
   aip = alloc_aiter();
   /* insert on front since expect last new to be used until done */
   aip->aiter = (struct h_t *) ihref;
   __last_aiter = aip;

   aip->aiternxt = __aiter_tab[vpiModule]; 
   __aiter_tab[vpiModule] = aip;
   aip->aiterprev = NULL;
   nxth = vpi_scan(ihref);
   /* DBG reomve --- */
   if (nxth == NULL) __acc_terr(__FILE__, __LINE__);
   /* --- */
   return((handle) nxth);
  }
 /* get next - find previously built iterator */
 hp2 = (struct h_t *) child;
 if (!validate_acc_handle("acc_next_child", hp2)) return(NULL); 
 if (hp2->hrec->htyp != vpiModule)
  {
   wrong_nxtobj_error("acc_next_child", hp2->hrec->htyp, accModule); 
   return(NULL);
  }
 /* last object must be inside mod_handle instance */
 itp = (struct itree_t *) hp2->hin_idp[MD_ITP];
 if (itp->up_it->it_idp != hp->hin_idp)
  {
   __acc_err(1979,
    "acc_next_child previous child handle wrong - not contained in %s",
    __msg2_idp_blditree(__wrks1, hp->hin_idp));  
   return(NULL);
  } 
 if ((aip = find_aiter_rec(__aiter_tab[vpiModule], hp2)) == NULL)
  {
   __acc_err(1984,
    "acc_next_child last accModule object not returned by previous acc_next_child call");
   return(NULL);
  }
 nxth = vpi_scan((vpiHandle) aip->aiter);
 if (nxth == NULL) { linkout_aiter(aip, vpiModule, FALSE); return(NULL); }
 return((handle) nxth);
}

/*
 * get primitive terminal in cell (only one) drivers (outputs) of a net 
 *
 * this is same as vpiDriver except 1) only primitive terminals,
 */
extern handle acc_next_driver(handle net, handle driver)
{
 return(do_acc_next_ld_drv("acc_next_driver", net, driver));
}

/*
 * build the acc driver prim term only iterator
 *
 * build vpi driver iterator then filter out any non primitive terminals
 * this maniplates (reallocs) guts of iterator
 */
static vpiHandle bld_driver_iter(struct h_t *hp)
{
 int32 iti;
 int32 iti2;
 struct h_t *hp2, *ihp;
 vpiHandle ihref;
 struct pviter_t *iterp;

 __acc_vpi_erroff = TRUE;
 ihref = vpi_iterate(vpiDriver, (vpiHandle) hp);
 if (__my_vpi_chk_error())
  {
   __acc_err(1983, "acc_next_driver error finding first %s",
    to_acc_onam(__wrks1, hp->hrec->htyp));
   return(NULL);
  }
 /* if no drivers, must pass nil up */
 if (ihref == NULL) return(NULL);

 ihp = (struct h_t *) ihref;
 iterp = ihp->hrec->hu.hiterp;
 /* go through iterator copying only terminals in cells into ait hp tab */
 /* also elminate non primitive vpi but not acc_ terminals here */
 for (iti = iti2 = 0; iti < iterp->numhs; iti++)
  {
   hp2 = iterp->scanhptab[iti];
   if (hp2->hrec->htyp != vpiPrimTerm) continue;

   if (iti2 >= __aithtsiz) __grow_acc_hptab(1);
   __aithptab[iti2] = hp2;
   iterp->scanhptab[iti] = NULL;
   iti2++;
  }
 /* final step is to free old iterator and build new one */
 acc_internal_itfree(ihp);

 if (iti2 == 0) return(NULL);

 iterp = __alloc_empty_iter(iti2, &ihref);
 for (iti = 0; iti < iti2; iti++)
  {
   iterp->scanhptab[iti] = __aithptab[iti];
   __aithptab[iti] = NULL;
  }
 return(ihref);
}

/*
 * get next hiconn bit of a port
 *
 * this is for vector ports (or scalar where just one bit is returned)
 * works for bit selects, part selects, and vectored ports (not concat?)
 */
extern handle acc_next_hiconn(handle port, handle hiconn)
{
 return(do_acc_next_hilo_conn("acc_next_hiconn", port, hiconn, TRUE));
}

/*
 * get next hiconn or loconn bit of a port (routine does both)
 *
 * this is for vector ports (or scalar where just one bit is returned)
 * works for bit selects, part selects, and vectored ports (not concat?)
 *
 * best way in acc_ to do this is first get port bit then use
 * acc handle hicon to get the high conn bit
 * 
 * if scalar port just returns the highconn (at most one) else gets
 * each bit of vector in turn
 *
 * LOOKATME - what happens for hiconn that is not reg/net scalar or bit
 *
 * LOOKATME - there is discussion in P1364 task force notes on problems
 * with this
 */
static handle do_acc_next_hilo_conn(char *rtnnam, handle port, handle conn,
 int32 is_hiconn)
{
 int32 iti;
 int32 nbits;
 struct h_t *hp, *hp2, *hp3, *ihp;
 vpiHandle ihref, nxth;
 struct acciter_t *aip;
 struct pviter_t *iterp;

 acc_error_flag = FALSE;

 hp = (struct h_t *) port;
 if (!validate_acc_handle(rtnnam, hp)) return(NULL); 

 if (hp->hrec->htyp != vpiPort)
  {
   __acc_err(1733, "%s: object %s illegal must be accPort", rtnnam,
    to_acc_onam(__wrks1, hp->hrec->htyp));
   return(NULL);
  }

 /* build the iterator since this is first time */
 if (conn == NULL)
  {
   /* case 1: scalar port - special case with only one to return */
   if (vpi_get(vpiScalar, (vpiHandle) port))
    {
     if (is_hiconn) return(acc_handle_hiconn((handle) port));
     else return(acc_handle_loconn((handle) port));
    }

   /* case 2: vector - first build vpiPortBit iterator */
   __acc_vpi_erroff = TRUE;
   ihref = vpi_iterate(vpiPortBit, (vpiHandle) port);
   if (__my_vpi_chk_error())
    {
     __acc_err(1985, "%s error separating port into accPortBit(s)", rtnnam);
     return(NULL);
    }
   if (ihref == NULL) return(NULL);

   ihp = (struct h_t *) ihref;
   iterp = ihp->hrec->hu.hiterp;
   /* must build each of the acc highconn */  
   nbits = iterp->numhs;
   /* DBG remove -- */
   if (nbits <= 0) __acc_terr(__FILE__, __LINE__);
   /* --- */
   for (iti = 0; iti < nbits; iti++)
    {
     hp2 = iterp->scanhptab[iti];
     /* unc. (NULL) possible here */
     if (is_hiconn) hp3 = (struct h_t *) acc_handle_hiconn((handle) hp2);
     else hp3 = (struct h_t *) acc_handle_loconn((handle) hp2);
     if (hp3 == NULL)
      {
       __acc_err(1986,
        "%s error - iterator imposible - some bits unconnected", rtnnam);
       /* no hiconn to free since returned nil */
       acc_internal_itfree(hp2);
       return(NULL);
      }
     if (iti >= __aithtsiz) __grow_acc_hptab(1);
     __aithptab[iti] = hp3;
     /* SJM 06-22-10 - now just pointing iter to gened handle - no free */
    }
   /* free old iterator and build new one */
   acc_internal_itfree(ihp);
   iterp = __alloc_empty_iter(nbits, &ihref);
   for (iti = 0; iti < nbits; iti++)
    {
     iterp->scanhptab[iti] = __aithptab[iti];
     __aithptab[iti] = NULL;
    }

   aip = alloc_aiter();
   /* insert on front since expect last new to be used until done */
   aip->aiter = (struct h_t *) ihref;
   __last_aiter = aip;

   aip->aiternxt = __aiter_tab[vpiPortBit]; 
   __aiter_tab[vpiPortBit] = aip;
   aip->aiterprev = NULL;

   /* LOOKATME - much faster to just get object from scan hp tab but for */
   /* now leaving extra checking */
   nxth = vpi_scan(ihref);
   /* DBG reomve --- */
   if (nxth == NULL) __acc_terr(__FILE__, __LINE__);
   /* --- */
   return((handle) nxth);
  }

 /* get next from previously built iterator */
 hp2 = (struct h_t *) conn;
 /* case 1: scalar port - know at most one connection */
 if (vpi_get(vpiScalar, (vpiHandle) port))
  { 
   /* free vpi_object since contents copied */
   /* SJM 03/15/00 - must not free since not part of copied iterator */  
   /* ---
   if (!vpi_free_object((vpiHandle) hp2))
    { __acc_terr(__FILE__, __LINE__); }
   -- */
   return(NULL);
  }
 /* case 2: vector port */
 if (!validate_acc_handle(rtnnam, hp2)) return(NULL); 
 /* lots of different types of handles possible here */
 if ((aip = find_aiter_rec(__aiter_tab[vpiPortBit], hp2)) == NULL)
  {
   __acc_err(1984,
    "%s last net or reg scalar or bit object not returned by previous %s call",
    rtnnam, rtnnam);
   return(NULL);
  }

 nxth = vpi_scan((vpiHandle) aip->aiter);
 if (nxth == NULL) { linkout_aiter(aip, vpiPortBit, FALSE); return(NULL); }
 return((handle) nxth);
}

/*
 * WRITEME
 */
extern handle acc_next_input(handle path, handle pathin)
{
 __acc_err(1941, "acc_next_input (for path inputs) not yet implemented");
 return(NULL);
}

/*
 * get primitive terminal loads (inputs) of a net 
 *
 * this is same as vpiLoad except 1) only primitive terminals,
 */
extern handle acc_next_load(handle net, handle load)
{
 return(do_acc_next_ld_drv("acc_next_load", net, load));
}

/*
 * build the acc load prim term only iterator
 *
 * build vpi driver iterator then filter out any non primitive terminals
 * this maniplates (reallocs) guts of iterator
 *
 * differs from cell load iterator because includes all prim term
 * drivers on net and also include instances that are not cells
 */
static vpiHandle bld_load_iter(struct h_t *hp)
{
 int32 iti;
 int32 iti2;
 struct h_t *ihp, *hp2;
 vpiHandle ihref;
 struct pviter_t *iterp;

 __acc_vpi_erroff = TRUE;
 ihref = vpi_iterate(vpiLoad, (vpiHandle) hp);
 if (__my_vpi_chk_error())
  {
   __acc_err(1983, "acc_next_load error finding first %s",
    to_acc_onam(__wrks1, hp->hrec->htyp));
   return(NULL);
  }
 if (ihref == NULL) return(NULL);
 ihp = (struct h_t *) ihref;
 iterp = ihp->hrec->hu.hiterp;
 /* go through iterator copying only terminals in cells into ait hp tab */
 /* also elminate non primitive vpi but not acc_ terminals here */
 for (iti = iti2 = 0; iti < iterp->numhs; iti++)
  {
   hp2 = iterp->scanhptab[iti];
   if (hp2->hrec->htyp != vpiPrimTerm) continue;

   if (iti2 >= __aithtsiz) __grow_acc_hptab(1);
   /* can copy guts because know these are prim terms with no ptrs */
   __aithptab[iti2] = hp2;
   iterp->scanhptab[iti] = NULL;
   iti2++;
  }

 /* to free old iterator and probably build new one unless empty */
 acc_internal_itfree(ihp);
 if (iti2 == 0) return(NULL);

 iterp = __alloc_empty_iter(iti2, &ihref);
 for (iti = 0; iti < iti2; iti++)
  {
   iterp->scanhptab[iti] = __aithptab[iti];
   __aithptab[iti] = NULL;
  }
 return(ihref);
}

/*
 * get next loconn bit of a port
 *
 * this is for vector ports (or scalar where just one bit is returned)
 * works for bit selects, part selects, and vectored ports (not concat?)
 *
 * loconn at least must be lhs and never width mismatch (vpi handles)
 */
extern handle acc_next_loconn(handle port, handle loconn)
{
 return(do_acc_next_hilo_conn("acc_next_loconn", port, loconn, FALSE));
}

/*
 * return next module path in module mod_p
 * normal contents of module iterator
 */
extern handle acc_next_modpath(handle mod_p, handle path)
{
 struct h_t *hp, *hp2; 
 vpiHandle ihref, nxth;
 struct acciter_t *aip;

 acc_error_flag = FALSE;

 hp = (struct h_t *) mod_p;
 if (!validate_acc_handle("acc_next_modpath", hp)) return(NULL); 

 if (hp->hrec->htyp != vpiModule)
  { 
   __acc_err(1734, "acc_next_modpath: %s object illegal - accModule required",
    to_acc_onam(__wrks1, hp->hrec->htyp));
   return(NULL);
  }

 /* build the iterator since this is first time */
 if (path == NULL)
  {
   __acc_vpi_erroff = TRUE;
   ihref = vpi_iterate(vpiModPath, (vpiHandle) mod_p);
   if (__my_vpi_chk_error())
    {
     __acc_err(1983, "acc_next_modpath error finding first accModPath");
     return(NULL);
    }
   if (ihref == NULL) return(NULL);
 
   aip = alloc_aiter();
   /* insert on front since expect last new to be used until done */
   aip->aiter = (struct h_t *) ihref;
   __last_aiter = aip;

   aip->aiternxt = __aiter_tab[vpiModPath]; 
   __aiter_tab[vpiModPath] = aip;
   aip->aiterprev = NULL;
   nxth = vpi_scan(ihref);
   /* DBG reomve --- */
   if (nxth == NULL) __acc_terr(__FILE__, __LINE__);
   /* --- */
   return((handle) nxth);
  }
 /* get next - find previously built iterator */
 hp2 = (struct h_t *) path;
 if (!validate_acc_handle("acc_next_modpath", hp2)) return(NULL); 
 if (hp2->hrec->htyp != vpiModPath)
  {
   wrong_nxtobj_error("acc_next_modpath", hp2->hrec->htyp, accModPath); 
   return(NULL);
  }
 if ((aip = find_aiter_rec(__aiter_tab[vpiModPath], hp2)) == NULL)
  {
   __acc_err(1984,
    "acc_next_modpath last accModPath object not returned by previous acc_next_modpath call");
   return(NULL);
  }
 nxth = vpi_scan((vpiHandle) aip->aiter);
 if (nxth == NULL) { linkout_aiter(aip, vpiModPath, FALSE); return(NULL); }
 return((handle) nxth);
}

/*
 * get next net
 *
 * notice this is only for nets - use acc_next with array to get other
 * variable tupes
 */
extern handle acc_next_net(handle mod_handle, handle net)
{
 struct h_t *hp, *hp2; 
 vpiHandle ihref, nxth;
 struct acciter_t *aip;

 acc_error_flag = FALSE;

 hp = (struct h_t *) mod_handle;
 if (!validate_acc_handle("acc_next_net", hp)) return(NULL); 

 if (hp->hrec->htyp != vpiModule)
  { 
   __acc_err(1735, "acc_next_net: %s object illegal - accModule required",
    to_acc_onam(__wrks1, hp->hrec->htyp));
   return(NULL);
  }

 /* build the iterator since this is first time */
 if (net == NULL)
  {
   __acc_vpi_erroff = TRUE;
   ihref = vpi_iterate(vpiNet, (vpiHandle) mod_handle);
   if (__my_vpi_chk_error())
    {
     __acc_err(1983, "acc_next_net error finding first accNet");
     return(NULL);
    }
   if (ihref == NULL) return(NULL);


   aip = alloc_aiter();
   /* insert on front since expect last new to be used until done */
   aip->aiter = (struct h_t *) ihref;
   __last_aiter = aip;

   aip->aiternxt = __aiter_tab[vpiNet]; 
   __aiter_tab[vpiNet] = aip;
   aip->aiterprev = NULL;
   nxth = vpi_scan(ihref);
   /* DBG reomve --- */
   if (nxth == NULL) __acc_terr(__FILE__, __LINE__);
   /* --- */
   return((handle) nxth);
  }
 /* get next - find previously built iterator */
 hp2 = (struct h_t *) net;
 if (!validate_acc_handle("acc_next_net", hp2)) return(NULL); 
 if (hp2->hrec->htyp != vpiNet)
  {
   wrong_nxtobj_error("acc_next_net", hp2->hrec->htyp, accNet); 
   return(NULL);
  }
 if ((aip = find_aiter_rec(__aiter_tab[vpiNet], hp2)) == NULL)
  {
   __acc_err(1984,
    "acc_next_net last accNet object not returned by previous acc_next_net call");
   return(NULL);
  }
 nxth = vpi_scan((vpiHandle) aip->aiter);
 if (nxth == NULL) { linkout_aiter(aip, vpiNet, FALSE); return(NULL); }
 return((handle) nxth);
}

/*
 * link out iterator that is finished from list
 *
 * SJM 10/11/99 - scan frees iterator when nil reached so do not do here
 * unless free iter flag true
 */
static void linkout_aiter(struct acciter_t *aip, int32 otyp, int32 iter_free)
{
 if (iter_free) __free_iterator((vpiHandle) aip->aiter); 

 /* always link out from acc_ iterator list */
 if (aip->aiterprev != NULL) aip->aiterprev->aiternxt = aip->aiternxt;
 else __aiter_tab[otyp] = aip->aiternxt;
 if (aip->aiternxt != NULL) aip->aiternxt->aiterprev = aip->aiterprev;
}

/*
 * link out iterator that is finished from accnext list
 */
static void linkout_accnext_aiter(struct acciter_t *aip)
{
 /* always link out from acc_ iterator list */
 if (aip->aiterprev != NULL) aip->aiterprev->aiternxt = aip->aiternxt;
 else __aiter_accnxt_list = aip->aiternxt;
 if (aip->aiternxt != NULL) aip->aiternxt->aiterprev = aip->aiterprev;
}


/*
 * WRITEME
 */
extern handle acc_next_output(handle path, handle pathout)
{
 __acc_err(1941, "acc_next_output (for path outputs) not yet implemented");
 return(NULL);
}

/*
 * get next parameter 
 *
 * parameter arrays never seen here
 */
extern handle acc_next_parameter(handle module_p, handle param)
{
 struct h_t *hp, *hp2; 
 vpiHandle ihref, nxth;
 struct acciter_t *aip;

 acc_error_flag = FALSE;

 hp = (struct h_t *) module_p;
 if (!validate_acc_handle("acc_next_parameter", hp)) return(NULL); 

 if (hp->hrec->htyp != vpiModule)
  { 
   __acc_err(1736,
    "acc_next_parameter: %s object illegal - accModule required",
    to_acc_onam(__wrks1, hp->hrec->htyp));
   return(NULL);
  }

 /* build the iterator since this is first time */
 if (param == NULL)
  {
   __acc_vpi_erroff = TRUE;
   ihref = vpi_iterate(vpiParameter, (vpiHandle) module_p);
   if (__my_vpi_chk_error())
    {
     __acc_err(1983, "acc_next_parameter error finding first accParameter");
     return(NULL);
    }
   if (ihref == NULL) return(NULL);
 
   aip = alloc_aiter();
   /* insert on front since expect last new to be used until done */
   aip->aiter = (struct h_t *) ihref;
   __last_aiter = aip;

   aip->aiternxt = __aiter_tab[vpiParameter]; 
   __aiter_tab[vpiParameter] = aip;
   aip->aiterprev = NULL;
   nxth = vpi_scan(ihref);
   /* DBG reomve --- */
   if (nxth == NULL) __acc_terr(__FILE__, __LINE__);
   /* --- */
   return((handle) nxth);
  }
 /* get next - find previously built iterator */
 hp2 = (struct h_t *) param;
 if (!validate_acc_handle("acc_next_parameter", hp2)) return(NULL); 
 if (hp2->hrec->htyp != vpiParameter)
  {
   wrong_nxtobj_error("acc_next_parameter", hp2->hrec->htyp, accParameter); 
   return(NULL);
  }
 if ((aip = find_aiter_rec(__aiter_tab[vpiParameter], hp2)) == NULL)
  {
   __acc_err(1984,
    "acc_next_parameter last accParameter object not returned by previous acc_next_parameter call");
   return(NULL);
  }
 nxth = vpi_scan((vpiHandle) aip->aiter);
 if (nxth == NULL) { linkout_aiter(aip, vpiParameter, FALSE); return(NULL); }
 return((handle) nxth);
}

/*
 * get next port (all port types including inputs)
 *
 * if ref obj is a net or reg - all ports connected to net or reg
 */
extern handle acc_next_port(handle ref_obj_p, handle port)
{
 struct h_t *hp, *hp2; 
 vpiHandle ihref, nxth;
 struct acciter_t *aip;

 acc_error_flag = FALSE;

 hp = (struct h_t *) ref_obj_p;
 if (!validate_acc_handle("acc_next_port", hp)) return(NULL); 

 switch (hp->hrec->htyp) {
  case vpiModule: case vpiNet: case vpiNetBit: case vpiReg: case vpiRegBit:
  case vpiIntegerVar: case vpiTimeVar: case vpiVarSelect:
   break;
  default: 
   __acc_err(1737, "acc_next_port: object %s illegal ref_obj_p - must be accModule or net/reg object",
    to_acc_onam(__wrks1, hp->hrec->htyp));
   return(NULL);
  }

 /* build the iterator since this is first time */
 if (port == NULL)
  {
   /* if ref obj is net or reg, vpi iterator works right and gets ports */ 
   /* connected to net - this can not be bit form */
   __acc_vpi_erroff = TRUE;
   ihref = vpi_iterate(vpiPort, (vpiHandle) ref_obj_p);
   if (__my_vpi_chk_error())
    {
     __acc_err(1983, "acc_next_port error finding first accPort");
     return(NULL);
    }
   if (ihref == NULL) return(NULL);
 
   aip = alloc_aiter();
   /* insert on front since expect last new to be used until done */
   aip->aiter = (struct h_t *) ihref;
   __last_aiter = aip;

   aip->aiternxt = __aiter_tab[vpiPort]; 
   __aiter_tab[vpiPort] = aip;
   aip->aiterprev = NULL;
   nxth = vpi_scan(ihref);
   /* DBG reomve --- */
   if (nxth == NULL) __acc_terr(__FILE__, __LINE__);
   /* --- */
   return((handle) nxth);
  }
 /* get next - find previously built iterator */
 hp2 = (struct h_t *) port;
 if (!validate_acc_handle("acc_next_port", hp2)) return(NULL); 
 if (hp2->hrec->htyp != vpiPort)
  {
   wrong_nxtobj_error("acc_next_port", hp2->hrec->htyp, accPort); 
   return(NULL);
  }
 if ((aip = find_aiter_rec(__aiter_tab[vpiPort], hp2)) == NULL)
  {
   __acc_err(1984,
    "acc_next_port last accPort object not returned by previous acc_next_port call");
   return(NULL);
  }
 nxth = vpi_scan((vpiHandle) aip->aiter);
 if (nxth == NULL) { linkout_aiter(aip, vpiPort, FALSE); return(NULL); }
 return((handle) nxth);
}

/*
 * get next port (only outputs and inouts)
 *
 * here mod_p can not
 */
extern handle acc_next_portout(handle mod_p, handle port)
{
 struct h_t *hp, *hp2; 
 vpiHandle ihref, nxth;
 struct acciter_t *aip;
 struct mod_t *mdp;

 acc_error_flag = FALSE;
 hp = (struct h_t *) mod_p;
 if (!validate_acc_handle("acc_next_portout", hp)) return(NULL); 

 if (hp->hrec->htyp != vpiModule)
  {
   __acc_err(1738, "acc_next_portout: object %s illegal - accModule required",
    to_acc_onam(__wrks1, hp->hrec->htyp));
   return(NULL);
  }

 /* build the iterator since this is first time */
 if (port == NULL)
  {
   __acc_vpi_erroff = TRUE;
   ihref = vpi_iterate(vpiPort, (vpiHandle) mod_p);
   if (__my_vpi_chk_error())
    {
     __acc_err(1983, "acc_next_portout error finding first output accPort");
     return(NULL);
    }
   if (ihref == NULL) return(NULL);

   /* remove input ports from iterator */
   mdp = (struct mod_t *) hp->hin_idp[MD_MDP];
   if ((ihref = rem_ins_from_iter(mdp, ihref)) == NULL) return(NULL); 
 
   aip = alloc_aiter();
   /* insert on front since expect last new to be used until done */
   aip->aiter = (struct h_t *) ihref;
   __last_aiter = aip;

   aip->aiternxt = __aiter_tab[vpiPort]; 
   __aiter_tab[vpiPort] = aip;
   aip->aiterprev = NULL;
   nxth = vpi_scan(ihref);
   /* DBG reomve --- */
   if (nxth == NULL) __acc_terr(__FILE__, __LINE__);
   /* --- */
   return((handle) nxth);
  }
 /* get next - find previously built iterator */
 hp2 = (struct h_t *) port;
 if (!validate_acc_handle("acc_next_portout", hp2)) return(NULL); 
 if (hp2->hrec->htyp != vpiPort)
  {
   wrong_nxtobj_error("acc_next_portout", hp2->hrec->htyp, accPort); 
   return(NULL);
  }
 if ((aip = find_aiter_rec(__aiter_tab[vpiPort], hp2)) == NULL)
  {
   __acc_err(1984,
    "acc_next_portout last accPort object not returned by previous acc_next_portout call");
   return(NULL);
  }
 nxth = vpi_scan((vpiHandle) aip->aiter);
 if (nxth == NULL) { linkout_aiter(aip, vpiPort, FALSE); return(NULL); }
 return((handle) nxth);
}

/*
 * go through port iterator removing all input ports
 * 
 * know iterator only contains ports
 * must pass containing module because iterator objects no itree loc.
 */
static vpiHandle rem_ins_from_iter(struct mod_t *mdp, vpiHandle ihref) 
{
 int32 iti, iti2;
 struct h_t *hp2, *ihp; 
 struct pviter_t *iterp;
 struct mod_pin_t *mpp;

 ihp = (struct h_t *) ihref;
 iterp = ihp->hrec->hu.hiterp;
 /* go through iterator copying only terminals in cells into ait hp tab */
 /* also elminate non primitive vpi but not acc_ terminals here */
 for (iti = iti2 = 0; iti < iterp->numhs; iti++)
  {
   hp2 = iterp->scanhptab[iti];
   mpp = &(mdp->mpins[hp2->hrec->hu.hpi]);
   if (mpp->mptyp == IO_IN) continue;

   if (iti2 >= __aithtsiz) __grow_acc_hptab(1);
   __aithptab[iti2] = hp2;
   iterp->scanhptab[iti] = NULL;
   iti2++; 
  }
 /* final step is to free old iterator and build new one */
 acc_internal_itfree(ihp);
 if (iti2 == 0) return(NULL);

 iterp = __alloc_empty_iter(iti2, &ihref);
 for (iti = 0; iti < iti2; iti++)
  {
   iterp->scanhptab[iti] = __aithptab[iti];
   __aithptab[iti] = NULL;
  }
 return(ihref);
}

/*
 * return handle to next primitive - gate, udp, switch
 *
 * can not use vpi_ iterators because acc_ no internal storage
 * always just uses last (or nil) to get next 
 */
extern handle acc_next_primitive(handle mod_handle, handle prim)
{
 struct h_t *hp, *hp2; 
 vpiHandle ihref, nxth;
 struct acciter_t *aip;

 acc_error_flag = FALSE;

 hp = (struct h_t *) mod_handle;
 if (!validate_acc_handle("acc_next_primitive", hp)) return(NULL); 

 if (hp->hrec->htyp != vpiModule)
  {
   __acc_err(1739, "acc_next_primitive: object %s illegal - accModule required",
    to_acc_onam(__wrks1, hp->hrec->htyp));
   return(NULL);
  }

 /* build the iterator since this is first time */
 if (prim == NULL)
  {
   __acc_vpi_erroff = TRUE;
   ihref = vpi_iterate(vpiPrimitive, (vpiHandle) mod_handle);
   if (__my_vpi_chk_error())
    {
     __acc_err(1983, "acc_next_primitive error finding first accPrimitive");
     return(NULL);
    }
   if (ihref == NULL) return(NULL);
 
   aip = alloc_aiter();
   /* insert on front since expect last new to be used until done */
   aip->aiter = (struct h_t *) ihref;
   __last_aiter = aip;

   /* LOOKATME - this is slightly wrong since returned object are one of */
   /* 3 gate types - using iterator access object works since consistent */
   aip->aiternxt = __aiter_tab[vpiPrimitive]; 
   __aiter_tab[vpiPrimitive] = aip;
   aip->aiterprev = NULL;
   nxth = vpi_scan(ihref);
   /* DBG reomve --- */
   if (nxth == NULL) __acc_terr(__FILE__, __LINE__);
   /* --- */
   return((handle) nxth);
  }
 /* get next - find previously built iterator */
 hp2 = (struct h_t *) prim;
 if (!validate_acc_handle("acc_next_primitive", hp2)) return(NULL); 
 if (hp2->hrec->htyp != vpiGate && hp2->hrec->htyp != vpiUdp
  && hp2->hrec->htyp != vpiSwitch)
  {
   wrong_nxtobj_error("acc_next_primitive", hp2->hrec->htyp, accPrimitive); 
   return(NULL);
  }
 if ((aip = find_aiter_rec(__aiter_tab[vpiPrimitive], hp2)) == NULL)
  {
   __acc_err(1984,
    "acc_next_primitive last accPrimitive object not returned by previous acc_next_primitive call");
   return(NULL);
  }
 nxth = vpi_scan((vpiHandle) aip->aiter);
 if (nxth == NULL) { linkout_aiter(aip, vpiPrimitive, FALSE); return(NULL); }
 return((handle) nxth);
}

/*
 * emit current handle wrong type error
 */
static void wrong_nxtobj_error(char *nxtrtnam, int32 htyp, int32 ndacctyp)
{
 char *chp, s1[RECLEN];

 /* should never happen since vpi handles validated */
 /* DBG remove -- */
 if (ndacctyp == -1)__acc_terr(__FILE__, __LINE__);
 /* --- */

 chp = get_accnam(ndacctyp);
 /* DBG remove -- */
 if (chp == NULL) __acc_terr(__FILE__, __LINE__);
 /* --- */
 __acc_err(1981, "%s current handle wrong type (%s) - %s required",
  nxtrtnam, to_acc_onam(s1, htyp), chp);
}

/*
 * allocate new acc iterator record
 */
static struct acciter_t *alloc_aiter(void)
{
 struct acciter_t *aip;

 if (__aiter_freelst != NULL)
  { 
   aip = __aiter_freelst;
   aip = __aiter_freelst->aiternxt;
  }
 else aip = (struct acciter_t *) __my_malloc(sizeof(struct acciter_t));
 init_aiter(aip);
 return(aip); 
}

/*
 * initialize acc iterator record
 */
static void init_aiter(struct acciter_t *aiterp)
{
 aiterp->aiter = NULL;
 aiterp->aiternxt = NULL;
 aiterp->aiterprev = NULL;
}

/*
 * return
 */
extern handle acc_next_scope(handle ref_scope_p, handle scope)
{
 struct h_t *hp, *hp2; 
 vpiHandle ihref, nxth;
 struct acciter_t *aip;

 acc_error_flag = FALSE;

 hp = (struct h_t *) ref_scope_p;
 if (!validate_acc_handle("acc_next_scope", hp)) return(NULL); 

 switch (hp->hrec->htyp) {
  case vpiModule: case vpiTask: case vpiFunction:
  case vpiNamedBegin: case vpiNamedFork:
   break;
  default:
   __acc_err(1741, "acc_next_scope: object %s illegal - scope object required",
    to_acc_onam(__wrks1, hp->hrec->htyp));
   return(NULL);
 } 

 /* build the iterator since this is first time */
 if (scope == NULL)
  {
   __acc_vpi_erroff = TRUE;
   ihref = vpi_iterate(vpiInternalScope, (vpiHandle) ref_scope_p);
   if (__my_vpi_chk_error())
    {
     __acc_err(1983, "acc_next_scope error finding first scope object");
     return(NULL);
    }
   if (ihref == NULL) return(NULL);
 
   aip = alloc_aiter();
   /* insert on front since expect last new to be used until done */
   aip->aiter = (struct h_t *) ihref;
   __last_aiter = aip;

   /* LOOKATME - this is access method but since table big enough */
   /* just using as header - next returns varied contained scope objects */ 
   aip->aiternxt = __aiter_tab[vpiScope]; 
   __aiter_tab[vpiScope] = aip;
   aip->aiterprev = NULL;
   nxth = vpi_scan((vpiHandle) aip->aiter);
   /* DBG reomve --- */
   if (nxth == NULL) __acc_terr(__FILE__, __LINE__);
   /* --- */
   return((handle) nxth);
  }
 /* get next - find previously built iterator */
 hp2 = (struct h_t *) scope;
 if (!validate_acc_handle("acc_next_scope", hp2)) return(NULL); 
 /* many scope object types can't check */
 if ((aip = find_aiter_rec(__aiter_tab[vpiScope], hp2)) == NULL)
  {
   __acc_err(1984,
    "acc_next_scope last accPrimitive object not returned by previous acc_next_scope call");
   return(NULL);
  }
 nxth = vpi_scan((vpiHandle) aip->aiter);
 if (nxth == NULL) { linkout_aiter(aip, vpiScope, FALSE); return(NULL); }
 return((handle) nxth);
}

/*
 * get next specparam
 */
extern handle acc_next_specparam(handle module_p, handle sparam)
{
 struct h_t *hp, *hp2; 
 vpiHandle ihref, nxth;
 struct acciter_t *aip;

 acc_error_flag = FALSE;

 hp = (struct h_t *) module_p;
 if (!validate_acc_handle("acc_next_specparam", hp)) return(NULL); 

 if (hp->hrec->htyp != vpiModule)
  { 
   __acc_err(1742,
    "acc_next_specparam: %s object illegal - accModule required",
    to_acc_onam(__wrks1, hp->hrec->htyp));
   return(NULL);
  }

 /* build the iterator since this is first time */
 if (sparam == NULL)
  {
   __acc_vpi_erroff = TRUE;
   ihref = vpi_iterate(vpiSpecParam, (vpiHandle) module_p);
   if (__my_vpi_chk_error())
    {
     __acc_err(1983, "acc_next_specparam error finding first accSpecparam");
     return(NULL);
    }
   if (ihref == NULL) return(NULL);
 
   aip = alloc_aiter();
   /* insert on front since expect last new to be used until done */
   aip->aiter = (struct h_t *) ihref;
   __last_aiter = aip;

   aip->aiternxt = __aiter_tab[vpiSpecParam]; 
   __aiter_tab[vpiSpecParam] = aip;
   aip->aiterprev = NULL;
   nxth = vpi_scan(ihref);
   /* DBG reomve --- */
   if (nxth == NULL) __acc_terr(__FILE__, __LINE__);
   /* --- */
   return((handle) nxth);
  }
 /* get next - find previously built iterator */
 hp2 = (struct h_t *) sparam;
 if (!validate_acc_handle("acc_next_specparam", hp2)) return(NULL); 
 if (hp2->hrec->htyp != vpiSpecParam)
  {
   wrong_nxtobj_error("acc_next_specparam", hp2->hrec->htyp, accSpecparam); 
   return(NULL);
  }
 if ((aip = find_aiter_rec(__aiter_tab[vpiSpecParam], hp2)) == NULL)
  {
   __acc_err(1984,
    "acc_next_specparam last accSpecparam object not returned by previous acc_next_specparam call");
   return(NULL);
  }
 nxth = vpi_scan((vpiHandle) aip->aiter);
 if (nxth == NULL) { linkout_aiter(aip, vpiSpecParam, FALSE); return(NULL); }
 return((handle) nxth);
}

/*
 * get next timing checking
 */
extern handle acc_next_tchk(handle mod_p, handle tchk)
{
 struct h_t *hp, *hp2; 
 vpiHandle ihref, nxth;
 struct acciter_t *aip;

 acc_error_flag = FALSE;

 hp = (struct h_t *) mod_p;
 if (!validate_acc_handle("acc_next_tchk", hp)) return(NULL); 

 if (hp->hrec->htyp != vpiModule)
  { 
   __acc_err(1743, "acc_next_tchk: %s object illegal - accModule required",
    to_acc_onam(__wrks1, hp->hrec->htyp));
   return(NULL);
  }

 /* build the iterator since this is first time */
 if (tchk == NULL)
  {
   __acc_vpi_erroff = TRUE;
   ihref = vpi_iterate(vpiTchk, (vpiHandle) mod_p);
   if (__my_vpi_chk_error())
    {
     __acc_err(1983, "acc_next_tchk error finding first accTchk");
     return(NULL);
    }
   if (ihref == NULL) return(NULL);
 
   aip = alloc_aiter();
   /* insert on front since expect last new to be used until done */
   aip->aiter = (struct h_t *) ihref;
   __last_aiter = aip;

   aip->aiternxt = __aiter_tab[vpiTchk]; 
   __aiter_tab[vpiTchk] = aip;
   aip->aiterprev = NULL;
   nxth = vpi_scan(ihref);
   /* DBG reomve --- */
   if (nxth == NULL) __acc_terr(__FILE__, __LINE__);
   /* --- */
   return((handle) nxth);
  }
 /* get next - find previously built iterator */
 hp2 = (struct h_t *) tchk;
 if (!validate_acc_handle("acc_next_tchk", hp2)) return(NULL); 
 if (hp2->hrec->htyp != vpiTchk)
  {
   wrong_nxtobj_error("acc_next_tchk", hp2->hrec->htyp, accTchk); 
   return(NULL);
  }
 if ((aip = find_aiter_rec(__aiter_tab[vpiTchk], hp2)) == NULL)
  {
   __acc_err(1984,
    "acc_next_tchk last accTchk object not returned by previous acc_next_tchk call");
   return(NULL);
  }
 nxth = vpi_scan((vpiHandle) aip->aiter);
 if (nxth == NULL) { linkout_aiter(aip, vpiTchk, FALSE); return(NULL); }
 return((handle) nxth);
}

/*
 * get next gate (primive terminal) 
 */
extern handle acc_next_terminal(handle gate_handle, handle term)
{
 struct h_t *hp, *hp2; 
 vpiHandle ihref, nxth;
 struct acciter_t *aip;

 acc_error_flag = FALSE;

 hp = (struct h_t *) gate_handle;
 if (!validate_acc_handle("acc_next_terminal", hp)) return(NULL); 

 /* SJM 02/11/00 - vpiPrimtive is iterator that include all 3 different */
 /* vpi_ primitive types not type itself must allow all 3 */
 if (hp->hrec->htyp != vpiGate && hp->hrec->htyp != vpiUdp
  && hp->hrec->htyp != vpiSwitch)
  { 
   __acc_err(1744,
    "acc_next_terminal: %s object illegal - accPrimitive required",
    to_acc_onam(__wrks1, hp->hrec->htyp));
   return(NULL);
  }

 /* build the iterator since this is first time */
 if (term == NULL)
  {
   __acc_vpi_erroff = TRUE;
   ihref = vpi_iterate(vpiPrimTerm, (vpiHandle) gate_handle);
   if (__my_vpi_chk_error())
    {
     __acc_err(1983, "acc_next_terminal error finding first accTerminal");
     return(NULL);
    }
   if (ihref == NULL) return(NULL);
 
   aip = alloc_aiter();
   /* insert on front since expect last new to be used until done */
   aip->aiter = (struct h_t *) ihref;
   __last_aiter = aip;

   aip->aiternxt = __aiter_tab[vpiPrimTerm]; 
   __aiter_tab[vpiPrimTerm] = aip;
   aip->aiterprev = NULL;
   nxth = vpi_scan(ihref);
   /* DBG reomve --- */
   if (nxth == NULL) __acc_terr(__FILE__, __LINE__);
   /* --- */
   return((handle) nxth);
  }
 /* get next - find previously built iterator */
 hp2 = (struct h_t *) term;
 if (!validate_acc_handle("acc_next_terminal", hp2)) return(NULL); 
 if (hp2->hrec->htyp != vpiPrimTerm)
  {
   wrong_nxtobj_error("acc_next_terminal", hp2->hrec->htyp, accTerminal); 
   return(NULL);
  }
 if ((aip = find_aiter_rec(__aiter_tab[vpiPrimTerm], hp2)) == NULL)
  {
   __acc_err(1984,
    "acc_next_terminal last accTerminal object not returned by previous acc_next_terminal call");
   return(NULL);
  }
 nxth = vpi_scan((vpiHandle) aip->aiter);
 if (nxth == NULL) { linkout_aiter(aip, vpiPrimTerm, FALSE); return(NULL); }
 return((handle) nxth);
}

/*
 * get next returns all top level instances (modules because 1-1)
 *
 * no reference object handle here
 * routine does not work with acc_collect type routines - need next child
 */
extern handle acc_next_topmod(handle topmod)
{
 acc_error_flag = FALSE;

 return(do_acc_child_topmod("acc_next_topmod", topmod));
}

/*
 * implement get next top module
 * acc next child no scope case or acc next topmod
 */
static handle do_acc_child_topmod(char *rtnnam, handle child)
{
 struct h_t *hp2; 
 vpiHandle ihref, nxth;
 struct acciter_t *aip;

 if (child == NULL)
  {
   __acc_vpi_erroff = TRUE;
   ihref = vpi_iterate(vpiModule, NULL);
   if (__my_vpi_chk_error())
    {
     __acc_err(1983, "%s error finding first top level instance", rtnnam);
     return(NULL);
    }
   if (ihref == NULL) return(NULL);
 
   aip = alloc_aiter();
   /* insert on front since expect last new to be used until done */
   aip->aiter = (struct h_t *) ihref;
   __last_aiter = aip;

   aip->aiternxt = __aiter_tab[vpiModule]; 
   __aiter_tab[vpiModule] = aip;
   aip->aiterprev = NULL;
   nxth = vpi_scan((vpiHandle) aip->aiter);
   /* DBG reomve --- */
   if (nxth == NULL) __acc_terr(__FILE__, __LINE__);
   /* --- */
   return((handle) nxth);
  }
 /* get next - find previously built iterator */
 hp2 = (struct h_t *) child;
 if (!validate_acc_handle(rtnnam, hp2)) return(NULL); 
 if (hp2->hrec->htyp != vpiModule)
  {
   wrong_nxtobj_error(rtnnam, hp2->hrec->htyp, accModule); 
   return(NULL);
  }
 /* last object must be top level module */
 if ((aip = find_aiter_rec(__aiter_tab[vpiModule], hp2)) == NULL)
  {
   __acc_err(1984,
    "%s last accModule object not returned by previous %s call",
    rtnnam, rtnnam);
   return(NULL);
  }
 nxth = vpi_scan((vpiHandle) aip->aiter);
 if (nxth == NULL) { linkout_aiter(aip, vpiModule, FALSE); return(NULL); }
 return((handle) nxth);
}

/*
 * return T if object is of given type
 *
 * type can be any type, full type, or special property 
 * (see case for special object properties)
 */
extern bool acc_object_of_type(handle object, int32 type)
{
 int32 objtyp, objfulltyp;
 struct h_t *hp;

 acc_error_flag = FALSE;

 hp = (struct h_t *) object;
 if (!validate_acc_handle("acc_object_of_type", hp)) return(FALSE); 

 /* handle special properties in case */
 switch (type) {
  case accScalar:
   if (hp->hrec->htyp == vpiNet || hp->hrec->htyp == vpiReg)
    { if (hp->hrec->hu.hnp->n_isavec) return(FALSE); else return(TRUE); }
   return(FALSE);
  case accVector:
   if (hp->hrec->htyp == vpiNet || hp->hrec->htyp == vpiReg)
    { if (hp->hrec->hu.hnp->n_isavec) return(TRUE); else return(FALSE); }
   if (hp->hrec->htyp == vpiIntegerVar || hp->hrec->htyp == vpiTimeVar)
    return(TRUE);
   return(FALSE);
  case accCollapsedNet:
   /* Cver nets never collapses nets aways so always F */
   return(FALSE);
  case accExpandedVector:
   /* no unexpanded nets in Cver */
   /* LOOKATME - are time and ints really unexpanded? */
   if (hp->hrec->htyp == vpiNet || hp->hrec->htyp == vpiReg
    || hp->hrec->htyp == vpiIntegerVar || hp->hrec->htyp == vpiTimeVar)
    return(TRUE);
   return(FALSE);
  case accUnExpandedVector:
   return(FALSE);
  case accScope:
   switch (hp->hrec->htyp) {
    case vpiFunction: case vpiModule: case vpiNamedBegin:
    case vpiNamedFork: case vpiTask: case vpiFuncCall:
     return(TRUE);
    default: break;
   }
   return(FALSE);
  case accModPathHasIfnone:
   if (hp->hrec->htyp == vpiModPath)
    { if (hp->hrec->hu.hpthp->pth_ifnone) return(TRUE); else return(FALSE); }
   return(FALSE);
  default:
   /* only way to exit loop is here */
   break;
 }
 /* know either type or full type */
 objtyp = acc_fetch_type((handle) hp);
 if (objtyp == type) return(TRUE);
 objfulltyp = acc_fetch_fulltype((handle) hp);
 if (objfulltyp == type) return(TRUE);
 return(FALSE);
}

/*
 * version of object of type that works with list (T if on 1st match)
 */
extern bool acc_object_in_typelist(handle object, int32 *type_list)
{
 int32 li;
 struct h_t *hp;

 acc_error_flag = FALSE;

 hp = (struct h_t *) object;
 if (!validate_acc_handle("acc_object_in_typelist", hp)) return(FALSE); 

 for (li = 0;; li++)
  {
   if (type_list[li] == 0) break;
   if (acc_object_of_type(object, type_list[li])) return(TRUE);
  }
 return(FALSE);
}

/*
 * return predefined acc constant for tool type
 */
extern int32 acc_product_type(void)
{
 return(accSimulator);
}

/*
 * get a string indicating product version
 */
extern char *acc_product_version(void)
{
 char s1[RECLEN], s2[RECLEN];

 sprintf(s1, "%s%s of %s (%s).\n", __vers, __vers2, __ofdt, __platform);
 sprintf(s2, "Cver Verilog simulator Version %s", s1); 
 return(add_accstrbuf(s2));
}

/*
 * release acc_next_input or acc_next_output (for path src/dst) aux. storage
 *
 * does nothing in Cver since no extra storage
 * LOOKATME - is there something that can be freed
 */
extern int32 acc_release_object(handle obj)
{
 return(1);
}

/*
 * replace (set) delays - acc style just wrapper for vpi put delays
 */
/*VARARGS*/
extern bool acc_replace_delays(handle object, ...)
{
 int32 rv;
 va_list va;

 va_start(va, object);
 rv = exec_acc_set_delays((struct h_t *) object, FALSE, va);
 va_end(va);
 return(rv);
}

/*
 * do acc_ replace or append routines (same except for append flag)
 *
 * caller calls va_start and va_end
 * LOOKATME - is this use of varargs Posix compatible?
 */
static int32 exec_acc_set_delays(struct h_t *hp, int32 is_append, va_list va)
{
 int32 i;
 double *d1p, *d2p, *d3p, *da;
 double mintoz, typtoz, maxtoz; 
 struct hrec_t *hrp;
 struct mod_pin_t *mpp;
 struct mod_t *mdp;
 s_vpi_delay vpideltmp;
 s_vpi_time delarr[36]; 
 char s1[RECLEN];

 if (is_append) strcpy(s1, "acc_append_delays");
 else strcpy(s1, "acc_replace_delays");
 acc_error_flag = FALSE;

 if (!validate_acc_handle(s1, hp)) return(0); 
 hrp = hp->hrec;

 for (i = 0; i < 36; i++) delarr[i].type = vpiScaledRealTime;
 vpideltmp.da = &(delarr[0]);
 vpideltmp.time_type = vpiScaledRealTime;
 vpideltmp.mtm_flag = FALSE;
 /* append must be off since replacing */
 if (is_append) vpideltmp.append_flag = TRUE;
 else vpideltmp.append_flag = FALSE;
 vpideltmp.pulsere_flag = FALSE;
 
 switch (hrp->htyp) {
  case vpiGate: case vpiUdp: case vpiSwitch:
   /* 3 values */
   __acc_vpi_erroff = TRUE;
   /* always get 3 delays - LOOKATME - what about 2 delay prims? */
   vpideltmp.no_of_delays = 3;

   if (__acc_mintypmaxdelays)
    {
     da = va_arg(va, double *);
     /* need to compute hiz delay according to acc config setting */
     if (__acc_tohizdelay == ACCTOHIZ_AVG)
      {
       mintoz = (da[0] + da[3])/2.0;
       typtoz = (da[1] + da[4])/2.0;
       maxtoz = (da[2] + da[5])/2.0;
      }
     else if (__acc_tohizdelay == ACCTOHIZ_MAX)
      {
       if (da[0] > da[3]) mintoz = da[0]; else mintoz = da[3];
       if (da[1] > da[4]) typtoz = da[1]; else typtoz = da[4];
       if (da[2] > da[5]) maxtoz = da[2]; else maxtoz = da[5];
      }
     else if (__acc_tohizdelay == ACCTOHIZ_MIN)
      {
       if (da[0] < da[3]) mintoz = da[0]; else mintoz = da[3];
       if (da[1] < da[4]) typtoz = da[1]; else typtoz = da[4];
       if (da[2] < da[5]) maxtoz = da[2]; else maxtoz = da[5];
      }
     /* ACCTOHIZ_FROMUSER */
     else { mintoz = da[6]; typtoz = da[7]; maxtoz = da[8]; }
     if (__mintypmax_sel == DEL_MIN) 
      {
       vpideltmp.da[0].real = da[0]; 
       vpideltmp.da[1].real = da[3];
       vpideltmp.da[2].real = mintoz;
      }
     else if (__mintypmax_sel == DEL_TYP) 
      {
       vpideltmp.da[0].real = da[1]; 
       vpideltmp.da[1].real = da[4];
       vpideltmp.da[2].real = typtoz;
      }
     else if (__mintypmax_sel == DEL_MAX) 
      {
       vpideltmp.da[0].real = da[2]; 
       vpideltmp.da[1].real = da[5];
       vpideltmp.da[2].real = maxtoz;
      }
     else __acc_terr(__FILE__, __LINE__);
    }
   else
    {
     d1p = va_arg(va, double *);
     vpideltmp.da[0].real = *d1p; 
     d2p = va_arg(va, double *);
     vpideltmp.da[1].real = *d2p;

     if (__acc_tohizdelay == ACCTOHIZ_AVG)
      vpideltmp.da[2].real = (*d1p + *d2p)/2.0;
     else if (__acc_tohizdelay == ACCTOHIZ_MAX)
      {
       if (*d1p > *d2p) vpideltmp.da[2].real = *d1p;
       else vpideltmp.da[2].real = *d2p;
      }
     else if (__acc_tohizdelay == ACCTOHIZ_MIN)
      {
       if (*d1p < *d2p) vpideltmp.da[2].real = *d1p;
       else vpideltmp.da[2].real = *d2p;
      }
     else
      {
       /* ACCTOHIZ_FROMUSER */
       d3p = va_arg(va, double *);
       vpideltmp.da[3].real = *d3p;
      }
    }

   vpi_put_delays((vpiHandle) hp, &vpideltmp);

   /* this access error vpi_ error info */  
   /* only error is hp not having property */
   if (__my_vpi_chk_error())
    {
     __acc_err(1718, "%s: unable to change delays for object %s", s1,
      to_acc_onam(__wrks1, hp->hrec->htyp));
     return(0);
    }
   break;
  case vpiPort: case vpiPortBit: 
   /* up to 12 - see draft 3 or later new LRM */
   mdp = (struct mod_t *) hp->hin_idp[MD_MDP];
   mpp = &(mdp->mpins[hrp->hu.hpi]);
   if (mpp->mptyp != IO_IN && mpp->mptyp != IO_BID)
    {
     __acc_err(1761,
      "%s: unable to change delays for %s - output port illegal", s1,
      to_acc_onam(__wrks1, hp->hrec->htyp));
     return(0); 
    }
   if (hrp->htyp == vpiPort && mpp->mpwide != 1)
    {
     __acc_err(1761,
      "%s: unable to change delays for accPort object - must be scalar", s1);
     return(0);
    }
   /* FALLTHRU */
  case vpiModPath:
   __acc_vpi_erroff = TRUE;
   /* port MIPD since inter module paths not supported) and paths from cfg */
   vpideltmp.no_of_delays = __acc_pathdelaycount;

   if (__acc_mintypmaxdelays)
    {
     da = va_arg(va, double *);
     for (i = 0; i < __acc_pathdelaycount; i++)
      {
       if (__mintypmax_sel == DEL_MIN) vpideltmp.da[i].real = da[3*i + 0]; 
       else if (__mintypmax_sel == DEL_TYP) vpideltmp.da[i].real = da[3*i + 1]; 
       else if (__mintypmax_sel == DEL_MAX) vpideltmp.da[i].real = da[3*i + 2]; 
       else __acc_terr(__FILE__, __LINE__);
      }
    }
   else
    {
     for (i = 0; i < __acc_pathdelaycount; i++)
      {
       d1p = va_arg(va, double *);
       vpideltmp.da[i].real = *d1p; 
      } 
    }
   vpi_put_delays((vpiHandle) hp, &vpideltmp);

   /* this access error vpi_ error info */  
   /* only error is hp not having property */
   if (__my_vpi_chk_error())
    {
     __acc_err(1718,
      "%s: unable to change path or MIPD delays for object %s", s1,
      to_acc_onam(__wrks1, hp->hrec->htyp));
     return(0);
    }
   break;
  case vpiTchk:
   /* 1 value - for 2 limit cases only first accessible in acc_ */
   __acc_vpi_erroff = TRUE;
   /* always set 1 delay (first limit) */
   if (__acc_mintypmaxdelays)
    {
     da = va_arg(va, double *);
     if (__mintypmax_sel == DEL_MIN) vpideltmp.da[0].real = da[0]; 
     else if (__mintypmax_sel == DEL_TYP) vpideltmp.da[0].real = da[1]; 
     else if (__mintypmax_sel == DEL_MAX) vpideltmp.da[0].real = da[2]; 
     else __acc_terr(__FILE__, __LINE__);
    }
   else
    {
     d1p = va_arg(va, double *);
     vpideltmp.da[0].real = *d1p; 
    }

   vpideltmp.no_of_delays = 1;
   vpi_put_delays((vpiHandle) hp, &vpideltmp);

   /* this access error vpi_ error info */  
   /* only error is hp not having property */
   if (__my_vpi_chk_error())
    {
     __acc_err(1718, "%s: unable to access delays for object %s",
      s1, to_acc_onam(__wrks1, hp->hrec->htyp));
     return(0);
    }
   break;
  default:
   __acc_err(1759,
    "%s: object %s illegal - does not have acc_ changeable delays",
    s1, to_acc_onam(__wrks1, hrp->htyp));
   return(0);
  }
 return(1);
}

/*
 * replace pulse handling limits
 * notice these never array form
 *
 * FIXME - simulator needs to support these for now does nothing
 */
/*VARARGS*/
extern bool acc_replace_pulsere(handle object, double val1r, double val1x, ...)
{
 struct h_t *hp;
 struct hrec_t *hrp;
 
 acc_error_flag = FALSE;

 hp = (struct h_t *) object; 
 if (!validate_acc_handle("acc_replace_pulsere", hp)) return(0); 
 hrp = hp->hrec;
 if (hrp->htyp != vpiModPath && hrp->htyp != vpiPort
  && hrp->htyp != vpiPortBit)  
  {
   __acc_err(1765, "acc_replace_pulsere: object %s illegal - path required",
    to_acc_onam(__wrks1, hrp->htyp));
   return(FALSE);
  }
 __acc_warn(2052,
  "acc_replace_pulsere no effect - pulse limits not stored by tool");
 return(TRUE);
}

/*
 * reset string buffer
 *
 * doesn't do much because user can not assume strings stay in string
 * buf since any addition can cause reset with warning
 */
extern void acc_reset_buffer(void)
{
 __acc_strbuf_nxti = 0;
}

/*
 * set interactive scope
 * call all misctfs with reason reason_scope if flag T
 */
extern bool acc_set_interactive_scope(handle scope, int32 callback_flag)
{
 struct h_t *hp;
 
 hp = (struct h_t *) scope;
 if (!validate_acc_handle("acc_set_interactive_scope", hp)) return(FALSE); 

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
   __acc_err(1745, "acc_set_interactive_scope: object %s is not a scope object",
    to_acc_onam(__wrks1, hp->hrec->htyp));
   return(FALSE); 
  }

 /* LOOKATME - think vpi_ call backs should not be called here */
 if (callback_flag && __tfrec_hdr != NULL) __call_misctfs_scope();
 return(TRUE);
}

/*
 * set pulse handling limits from percentages
 *
 * FIXME - simulator needs to support these for now does nothing
 */
extern bool acc_set_pulsere(handle path_p, double val1r, double val1e)
{
 struct h_t *hp;
 struct hrec_t *hrp;
 
 acc_error_flag = FALSE;

 hp = (struct h_t *) path_p; 
 if (!validate_acc_handle("acc_set_pulsere", hp)) return(0); 
 hrp = hp->hrec;
 if (hrp->htyp != vpiModPath && hrp->htyp != vpiPort
  && hrp->htyp != vpiPortBit)  
  {
   __acc_err(1766, "acc_set_pulsere: object %s illegal - path required",
    to_acc_onam(__wrks1, hrp->htyp));
   return(FALSE);
  }

 __acc_warn(2052,
  "acc_set_pulsere no effect - pulse limits not stored by tool");
 return(TRUE);
}

/*
 * set acc working scope 
 *
 * interpretation of arguments effected by configuration 
 */
/*VARARGS*/
extern char *acc_set_scope(handle object, ...)
{
 vpiHandle scopobj;
 struct h_t *hp;
 struct itree_t *itp;
 struct mod_t *mdp;
 va_list va;
 char *chp, *module_name;

 /* case 1, object is not nil */
 if (object != NULL)
  {
   hp = (struct h_t *) object;
   if (!validate_acc_handle("acc_set_scope", hp)) return(FALSE); 
   if (hp->hrec->htyp != vpiModule)
    {
     __acc_err(1712,
      "acc_set_scope object has illegal type %s - must be type accModule",
      to_acc_onam(__wrks1, hp->hrec->htyp));
     return(NULL);
    }
   __acc_scope_set = TRUE;
   __acc_scope_vpiobj = vpi_copy_object((vpiHandle) object);
   goto bld_path;
  }

 /* case 2a: object nil and name nil or acc_no_set_scope configure set */
 if (!__acc_enableargs_setscope)
  {
do_first_root:
   itp = __it_roots[0];
   mdp = itp->itip->imsym->el.emdp;
   __acc_scope_set = TRUE;
   __acc_scope_vpiobj = __mk_handle(vpiModule, (void *) mdp, itp->it_idp,
      NULL); 
   goto bld_path;
  }
 va_start(va, object);
 module_name = va_arg(va, char *);
 if (module_name == NULL)
  {
   va_end(va);
   goto do_first_root;  
  }

 /* case 3: look up name - must be rooted */
 __acc_vpi_erroff = TRUE;
 /* name must be rooted */
 scopobj = vpi_handle_by_name(module_name, NULL);
 /* if just can not find name - no error just returns nil */
 if (__my_vpi_chk_error())
  {
   __acc_err(1715,
    "acc_set_scope with acc_set_scope configuration - unable to find module scope for %s",
    module_name);
   va_end(va);
   return(NULL);
  }
 
 hp = (struct h_t *) scopobj;
 if (hp->hrec->htyp != vpiModule)
  {
   __acc_err(1713,
    "acc_set_scope module_name %s wrong object type %s - accModule required",
    module_name, to_acc_onam(__wrks1, hp->hrec->htyp));
   va_end(va);
   return(NULL);
  }
 va_end(va);
 __acc_scope_set = TRUE;
 __acc_scope_vpiobj = vpi_copy_object(scopobj);
 
bld_path:
 hp = (struct h_t *) __acc_scope_vpiobj;
 chp = __msg2_idp_blditree(__xs, hp->hin_idp);
 return(add_accstrbuf(chp));
}

/*
 * implement acc_set_value - almost the same as vpi set value  
 *
 * LOOKATME - are bit objects allowed (LRM says no)
 *
 * FIXME - somehow on acc_close and reset need to remove events?
 *
 * SJM 12/17/02 - this is exception to rest of acc_ - return 0 on success
 * and 1 on error
 */
extern int32 acc_set_value(handle obj, p_setval_value setval_p,
 p_setval_delay delay_p)
{
 int32 vpi_delflag;
 struct t_vpi_time tmptim; 
 struct t_vpi_value tmpval;
 struct h_t *hp;
 word64 timv;
 double d1;

 acc_error_flag = FALSE;
 if (__run_state != SS_SIM)
  { acc_not_sim_err("acc_set_value"); return(1); } 

 hp = (struct h_t *) obj;
 if (!validate_acc_handle("acc_set_value", hp)) return(1); 

 /* check for legal object to set value to */
 switch (hp->hrec->htyp) {
  case vpiNet: case vpiReg: case vpiIntegerVar: case vpiTimeVar:
  /* SJM 05/14/01 - misread LRM - all vpi put values legal */
  case vpiNetBit: case vpiRegBit: case vpiRealVar:
  /* SJM 05/14/01 - LOOKATME- indistinguishable from reg bit in acc? */
  case vpiVarSelect:
   break;
  case vpiUdp: 
   /* WRITEME */ 
   __acc_err(1941,
    "acc_set_value: accUdp initial value setting not yet implemented");
   return(1);
  case vpiUserSystf:
   /* WRITEME */ 
   __acc_err(1941,
    "acc_set_value: accUserFunction (PLI) value setting not yet implemented");
   return(1);
  default:
   __acc_err(1746, "acc_set_value: value cannot be set for %s object",
    to_acc_onam(__wrks1, hp->hrec->htyp));
   return(1);
 }

 /* build the vpi set value d.s. */ 
 /* idea here is to alloc vpi records in local (stack) memory */
 /* because vpi put value copies into its internal storage */

 /* copy acc time record into vpi time record */   
 if (delay_p->time.type == accTime)
  {
   /* this is 64 bit scaled (containing module of object) time */
   /* no matching vpi_ time type */
   /* use vpi real - think 52 bits of time is enough for scaled */
   timv = ((word64) ((word32) delay_p->time.low))
    | (((word64) ((word32) delay_p->time.high)) << 32);
   if (!__v64_to_real(&d1, &timv))
    {
     __acc_warn(2049,
      "conversion from scaled accTime to time as real lost precision");
    }
   tmptim.type = vpiScaledRealTime;
   tmptim.real = d1;
  }
 else if (delay_p->time.type == accSimTime)
  {
   /* this is internal ticks */
   tmptim.type = vpiSimTime;
   tmptim.low = delay_p->time.low;
   tmptim.high = delay_p->time.high;
  }
 else if (delay_p->time.type == accRealTime)
  {
   /* this is real scaled (containing module of object) time */
   tmptim.type = vpiScaledRealTime;
   tmptim.real = delay_p->time.real;
  }
 else 
  {
   /* SJM 04/15/01 - remove internal error for bad delay time type field */
   if (delay_p->model == accNoDelay)
    {
     /* acc delay model is no delay, delay_p can be nil but emit warn */
     tmptim.type = vpiSimTime;
     tmptim.low = 0;
     tmptim.high = 0;

     __acc_warn(2043,
      "acc_set_value: delay_p time type field value (%d) illegal - used anyway since accNoDelay model",
     delay_p->time.type);
    }
   else
    {
     __acc_err(1994,
      "acc_set_value: delay_p time type field value (%d) illegal",
      delay_p->time.type);
     return(1);
    }
  }

 /* SJM 04/15/01 - if delay_p model is no delay - time need not be set */
 /* convert acc delay model to vpi */
 if ((vpi_delflag = map_acc_delaymode_to_vpi(delay_p->model)) == -1)
  return(1);

 /* build the vpi_ value record */
 if (!fill_vpival_fromacc(&tmpval, setval_p)) return(1);

 /* actually do the vpi put value */ 
 /* this may be immediate or schedule event but storage copied so */
 /* can be freed after here */
 /* since not saving scheduled event handle, no need to check return */ 
 vpi_put_value((vpiHandle) hp, &tmpval, &tmptim, vpi_delflag);
 /* ??? FIXME - need to vpi check here in case this fails */
 return(0);
}

/*
 * map from acc delay models to vpi_ delay
 *
 * one-to-one except need to add assign/deassign for Verilog 99 vpi_
 * return -1 on error
 */
static int32 map_acc_delaymode_to_vpi(int32 accdmode)
{
 int32 vpidmode;

 /* extract delay type from acc_ setval_delay value */ 
 switch (accdmode) {
  case accNoDelay: vpidmode = vpiNoDelay; break;
  case accInertialDelay: vpidmode = vpiInertialDelay; break;
  case accTransportDelay: vpidmode = vpiTransportDelay; break;
  case accPureTransportDelay: vpidmode = vpiPureTransportDelay; break;
  case accForceFlag: vpidmode = vpiForceFlag; break; 
  case accReleaseFlag: vpidmode = vpiReleaseFlag; break; 
  case accAssignFlag: case accDeassignFlag:
   /* WRITEME */ 
   __acc_err(1988,
    "acc_set_value: %s s_setval_delay model value not yet implemented - use force/release for now",
    get_acc_delmode_nam(__wrks1, accdmode));
   return(-1);
  default:
   __acc_err(1992, "acc_set_value: s_setval_delay model value %d illegal",
    accdmode);
   return(-1);
 }
 return(vpidmode);
}

/*
 * convert acc delay mode value to string
 */
static char *get_acc_delmode_nam(char *s, int32 accdmode)
{
 switch (accdmode) {
  case accNoDelay: strcpy(s, "accNoDelay"); break;
  case accInertialDelay: strcpy(s, "accInertialDelay");  break;
  case accTransportDelay: strcpy(s, "accTransportDelay"); break;
  case accPureTransportDelay: strcpy(s, "accPureTransportDelay"); break;
  case accForceFlag: strcpy(s, "accForceFlag"); break;
  case accReleaseFlag: strcpy(s, "accReleaseFlag"); break;
  case accAssignFlag: strcpy(s, "accAssignFlag"); break;
  case accDeassignFlag: strcpy(s, "accDeassignFlag"); break;
  default: sprintf(s, "[?? Unknown: %d]", accdmode); break;
 }
 return(s);
}

/*
 * fill vpi t_vpi_value record from acc t_setval_value
 * returns F on error else T
 *
 * call must allocate vpi value record
 * because vpi copies value contents - this mostly just copies ptrs
 *
 * this works because both use same vector aval/bval format
 * and acc value types are subset of vpi_ 
 */
static int32 fill_vpival_fromacc(struct t_vpi_value *vpivalp,
 struct t_setval_value *accvalp)
{
 switch (accvalp->format) {
  /* string forms same except for constant */
  case accBinStrVal:
   vpivalp->format = vpiBinStrVal; 
   vpivalp->value.str = accvalp->value.str;
   break;
  case accOctStrVal:
   vpivalp->format = vpiOctStrVal; 
   vpivalp->value.str = accvalp->value.str;
   break;
  case accDecStrVal:
   vpivalp->format = vpiDecStrVal; 
   vpivalp->value.str = accvalp->value.str;
   break;
  case accHexStrVal:
   vpivalp->format = vpiHexStrVal; 
   vpivalp->value.str = accvalp->value.str;
   break;
  case accScalarVal:
   vpivalp->format = vpiScalarVal; 
   /* notice vpi and acc 4 values different */
   vpivalp->value.scalar = map_acc_to_vpival(accvalp->value.scalar);
   break;
  case accIntVal:
   vpivalp->format = vpiIntVal; 
   vpivalp->value.integer = accvalp->value.integer;
   break;
  case accRealVal:
   vpivalp->format = vpiRealVal; 
   vpivalp->value.real = accvalp->value.real;
   break;
  case accStringVal:
   vpivalp->format = vpiStringVal; 
   /* can just use same ptr here */
   vpivalp->value.str = accvalp->value.str;
   break;
  case accVectorVal:
   /* BEWARE - this assumes internal vec val a/b values same */
   vpivalp->format = vpiVectorVal; 
   vpivalp->value.vector = (struct t_vpi_vecval *) accvalp->value.vector;
   break;
  default:
   __acc_err(1992, "acc_set_value: s_setval_value foramt value %d illegal",
    accvalp->format);
   return(FALSE);
 }
 return(TRUE);
}

/*
 * add a value change call back to a net 
 *
 * can add to reg/net/var and bit select of vector reg/net
 * also loconns expr of port and exprs connected to of terminals
 *
 * loconn must not be concatenate or part select - must catch
 *
 * Cver allows any vector reg/net (not just unexpanded)
 * FIXME - allow vpi_ cbs and therefore also acc_ vcls on declared events
 */
extern void acc_vcl_add(handle object_p, int32 (*consumer)(), char *user_data,
 int32 vcl_flags)
{
 struct h_t *hp, *hp2, *hp3;
 struct net_t *np;
 struct gate_t *gp;
 struct expr_t *xp;
 struct t_cb_data cbrec; 
 struct t_vpi_time tmptim;
 struct t_vpi_value tmpval;
 struct vclrec_t *vclp;

 acc_error_flag = FALSE;
 if (__run_state != SS_SIM)
  { acc_not_sim_err("acc_vcl_add"); return; } 

 /* check arguments */
 if (consumer == NULL)
  {
   __acc_err(1987,
    "acc_vcl_add call illegal - consumer routine must not be NULL");
   return;
  }

 hp = (struct h_t *) object_p;
 if (!validate_acc_handle("acc_vcl_add", hp)) return; 

 /* SJM 11/28/00 - if tran terminal, must replace with connected expr */
 if (hp->hrec->htyp == vpiPrimTerm)
  {
   gp = hp->hrec->hu.hgp;
   if (gp->g_class == GC_PULL || gp->g_class == GC_TRAN
    || gp->g_class == GC_TRANIF)
    {
     if (gp->g_class == GC_TRANIF && hp->hrec->hi == 2)
      {
       __acc_err(1980,
        "acc_vcl_add for accTerminal (pos. %d) of tranif %s.%s illegal input - only inout allowed",
       hp->hrec->hi + 1, __msg2_idp_blditree(__xs, hp->hin_idp),
       gp->gsym->synam);
       return;
      }
     xp = hp->hrec->hu.hgp->gpins[hp->hrec->hi];
     /* SJM 11/28/00 - also must change handle to terminal index handle */
     hp3 = (struct h_t *) __mk_exprclass_handle(xp, hp->hin_idp,
      hp->hrec->hin_tskp);
     hp = hp3;
    }
  }

 /* if already added or error, done */ 
 if (!chk_add_del_vclobj("acc_vcl_add", &hp, consumer, user_data)) return;

 /* add it */
 /* if monitoring for strength, must be 1 bit object */ 
 if (hp->hrec->htyp == vpiNetBit && hp->hrec->htyp == vpiRegBit)
  {
   if (vcl_flags == vcl_verilog_strength) 
    {
     np = hp->hrec->hu.hnp;
     if (np->nwid != 1)
      {
       __acc_err(1949,
        "acc_vcl_add - vcl_flags value VCL_VERILOG_STRENGTH illegal for vector object %s",
        to_acc_onam(__wrks1, hp->hrec->htyp));
       return;
      }
    }
  }

 /* allocate and fill internal vclrec */
 vclp = (struct vclrec_t *) __my_malloc(sizeof(struct vclrec_t));
 vclp->vclflg = vcl_flags;
 vclp->vcl_oldstval = ST_STRONGX;
 /* SJM 11/22/00 - for primitive output terminal must set by gate type */
 if (hp->hrec->htyp == vpiPrimTerm)
  {
   /* flag determines if vpi_ call back monitors strength */
   /* LOOKATME - minor bug since for mos/buf gates, all stren changes */
   /* reported */
   if (vcl_flags == vcl_verilog_strength)
    vclp->vcl_reason = strength_value_change;
   else vclp->vcl_reason = logic_value_change;
  }
 else vclp->vcl_reason = set_vcl_reason(hp->hrec->hu.hnp, vcl_flags);

 /* LOOKATME - why not make field h_t not handle */
 vclp->vclobj = (handle) hp;
 vclp->vcl_cb_rtn = consumer;  
 vclp->vcl_udata = user_data; 
 vclp->vclcbp = NULL;

 /* register vpi callback */
 /* local vars used because always copied here and when cb occurs */
 cbrec.reason = cbValueChange;

 /* SJM 11/22/00 - need special routine for prim output terminal */
 if (hp->hrec->htyp == vpiPrimTerm) cbrec.cb_rtn = exec_acc_gateout_vclcb;
 else cbrec.cb_rtn = exec_acc_vclcb;

 tmptim.type = vpiSimTime;
 tmptim.high = tmptim.low = 0;
 cbrec.time = &tmptim;
 tmpval.format = vpiSuppressVal;
 /* SJM 11/27/00 - use suppress value since need to get value as part */
 /* of vcl processing */
 tmpval.value.str = NULL;
 cbrec.value = &tmpval;

 cbrec.obj = (vpiHandle) hp;
 cbrec.user_data = (char *) vclp;

 hp2 = (struct h_t *) vpi_register_cb(&cbrec);
 __acc_vpi_erroff = TRUE;
 if (__my_vpi_chk_error())
  {
   __acc_err(1749, "acc_vcl_add: error adding value change callback for %s",
    to_acc_onam(__wrks1, hp->hrec->htyp));
   __my_free(vclp, sizeof(struct vclrec_t));
   return;
  }
 vclp->vclcbp = hp2->hrec->hu.hcbp;
}

/*
 * check vcl add and vcl object handle
 * return F is error or already added0
 */
static int32 chk_add_del_vclobj(char *rtnnam, struct h_t **hpp,
 int32 (*consumer)(), char *user_data)
{
 vpiHandle loconn, hiconn;
 struct h_t *hp;
 char s1[RECLEN];

 strcpy(s1, "");
 hp = *hpp;
 /* make sure handle object legal for acc_ vcl callback */
 switch (hp->hrec->htyp) {
  case vpiNet: case vpiReg: case vpiIntegerVar: case vpiTimeVar:
   break;
  case vpiNetBit: case vpiRegBit:
   break;
  case vpiPrimTerm:
   /* BEWARE must be vpiDirection since this short circuits prop checking */
   if (__primtermprop_vpiget(hp, vpiDirection) == vpiInput)
    {
     __acc_err(1753,
      "%s: primitive input port can not be monitored by acc_ vcl", rtnnam);
     return(FALSE);
    }
   /* SJM 11/22/00 - now vpi_ cb really goes on output terminal itself */
   *hpp = hp;
   break;
  case vpiPort: case vpiPortBit:
   /* SJM 03/15/04 - for port acc vcl's was not putting change cb on the */  
   /* hiconn for input ports */
   __acc_vpi_erroff = TRUE;
   if (vpi_get(vpiDirection, (vpiHandle) hp) == vpiInput)
    {
     hiconn = vpi_handle(vpiHighConn, (vpiHandle) hp);
     if (__my_vpi_chk_error())
      {
       __acc_err(1753, "%s: error accessing hiconn of input accPort",
        rtnnam);
       return(FALSE);
      }
     hp = (struct h_t *) hiconn;
     *hpp = hp;
    }
   else
    {
     loconn = vpi_handle(vpiLowConn, (vpiHandle) hp);
     if (__my_vpi_chk_error())
      {
       __acc_err(1753, "%s: error accessing loconn of ouput/inout accPort",
        rtnnam);
       return(FALSE);
      }
     hp = (struct h_t *) loconn;
     *hpp = hp;
    }
   break;
   case vpiRealVar: case vpiNamedEvent:
   /* WRITEME */
   /* LOOKATME - does this work in vpi_ */
   __acc_err(1941, "%s: %s%s object not yet implemented", rtnnam,
    to_acc_onam(__wrks1, hp->hrec->htyp), s1);
    return(FALSE);
  default:
   __acc_err(1747, "%s: %s%s object can not be monitored by acc_ vcl",
    rtnnam, to_acc_onam(__wrks1, hp->hrec->htyp), s1);
   return(FALSE);
 }
 /* find and only add if different arguments (not counting vcl_flag) */
 /* if already added, do not add again */
 /* SJM 11/28/00 - need separate match routine to find already registered */
 /* for gate output terminals */
 if (hp->hrec->htyp == vpiPrimTerm)
  {
   if (findmatch_term_vcl_dce(hp, consumer, user_data) != NULL)
    {
     __acc_err(1989,
      "%s failed - identical (all args but vcl_flags) vcl primitive output termininal monitor already added",
      rtnnam);
     return(FALSE);
    }
  }
 else
  {
   if (findmatch_net_vcl_dce(hp, consumer, user_data) != NULL)
    {
     __acc_err(1989,
      "%s failed - identical (all args but vcl_flags) vcl variable monitor already added",
      rtnnam);
     return(FALSE);
    }
  }
 return(TRUE);
}

/*
 * routine to set vcl call back reason field from net and vcl flag
 */
static int32 set_vcl_reason(struct net_t *np, int32 vclflg)
{
 int32 reason;

 if (np->nwid == 1)
  {
   if (vclflg == vcl_verilog_strength) reason = strength_value_change;
   else
    {
     if (np->ntyp >= NONWIRE_ST) reason = sregister_value_change;
     else reason = logic_value_change;
    }
  }
 else
  {
   if (np->ntyp == N_INT) reason = integer_value_change; 
   else if (np->ntyp == N_TIME) reason = time_value_change;
   else 
    {
     if (np->ntyp >= NONWIRE_ST) reason = vregister_value_change;
     else reason = vector_value_change;
    }
  }
 return(reason);
}

/*
 * find matching CBR vpi_ dce if has one
 *
 * know dce's here are either entire net/reg or one bit
 */
static struct vclrec_t *findmatch_net_vcl_dce(struct h_t *hp, int32 (*consumer)(),
 char *user_data)
{
 struct dcevnt_t *dcep;
 struct hrec_t *hrp;
 int32 cv;
 struct net_t *np; 
 struct vclrec_t *vclp;
 struct h_t *hp2;

 hrp = hp->hrec;
 np = hrp->hu.hnp;
 for (dcep = np->dcelst; dcep != NULL; dcep = dcep->dcenxt)
  {
   /* eliminate if not vpi callback type */
   if (dcep->dce_typ != DCE_CBVC && dcep->dce_typ != DCE_RNG_CBVC)   
    continue;

   /* eliminate if vcl call back routine not match acc_ vcl wrapper */
   if (dcep->dceu.dce_cbp->cb_rtn != exec_acc_vclcb) continue;

   /* make sure instance and bit ranges match */
   if (dcep->dce_matchu.idp != hp->hin_idp) continue;
   /* if vcl being added to bit - dce must match bit */
   if (hrp->htyp == vpiNetBit || hrp->htyp == vpiRegBit)
    {
     /* vector form never matches bit form */
     if (dcep->dci1 == -1) continue;
     if (dcep->dci1 != hrp->hi) continue;
    }
   /* found match providing all 3 vcl add args match */
   /* vpi_ user data is vclrec */
   vclp = (struct vclrec_t *) dcep->dceu.dce_cbp->cb_user_data;
   if ((struct h_t *) vclp->vclobj != hp) continue;
   if (vclp->vcl_cb_rtn != consumer) continue;
   if (vclp->vcl_udata != user_data) continue;

   hp2 = (struct h_t *) vclp->vclobj;
   __acc_vpi_erroff = TRUE;
   cv = vpi_compare_objects((vpiHandle) hp, (vpiHandle) hp2);
   /* this access error vpi_ error info */  
   if (__my_vpi_chk_error())
    {
     __acc_err(1754,
      "acc_vcl_add problem comparing other added vcl object %s",
       to_acc_onam(__wrks1, hp2->hrec->htyp));
     continue;
    }
   /* cv 0 if different - if different did not find match */
   if (cv == 0) continue; 
   return(vclp);
  }
 return(NULL);
}

/*
 * find matching gate output terminal vcl triple to see if registered
 */
static struct vclrec_t *findmatch_term_vcl_dce(struct h_t *hp,
 int32 (*consumer)(), char *user_data)
{
 struct tev_t *tevp;
 int32 gi, cv, itinum;
 struct gate_t *gp;
 struct mod_t *mdp;
 struct cbrec_t *cbp; 
 struct vclrec_t *vclp;
 struct h_t *hp2;

 /* if this gate terminal has no terminal output value change call backs */ 
 /* can't match */
 gp = hp->hrec->hu.hgp; 
 mdp = (struct mod_t *) hp->hin_idp[MD_MDP];
 itinum = (int32) hp->hin_idp[MD_INUM];
 gi = gp - mdp->mgates;
 if (mdp->mgateout_cbs == NULL || mdp->mgateout_cbs[gi] == NULL)
  return(NULL);
 if ((tevp = mdp->mgateout_cbs[gi][itinum]) == NULL)
  return(NULL);
 
 for (; tevp != NULL; tevp = tevp->tenxtp)
  {
   /* LOOKATME - think this is impossible, removed from list when removed */
   /* but does not hurt */
   if (tevp->enterptr == __process_cancel_ev_enterp) continue;

   cbp = tevp->tu.tehp->hrec->hu.hcbp;
   /* eliminate if not acc_ call back */
   if (cbp->cb_rtn != exec_acc_gateout_vclcb) continue;

   /* notice acc specific vcl fields stored in call back user data field */
   vclp = (struct vclrec_t *) cbp->cb_user_data;

   /* found match providing all 3 vcl add args match */
   /* LOOKATME - why is this exactly same handle not just same object */
   if ((struct h_t *) vclp->vclobj != hp) continue;
   if (vclp->vcl_cb_rtn != consumer) continue;
   if (vclp->vcl_udata != user_data) continue;

   hp2 = (struct h_t *) vclp->vclobj;
   __acc_vpi_erroff = TRUE;
   cv = vpi_compare_objects((vpiHandle) hp, (vpiHandle) hp2);
   /* this access error vpi_ error info */  
   if (__my_vpi_chk_error())
    {
     __acc_err(1754,
      "acc_vcl_add problem comparing other added primitive output terminal vcl object %s",
       to_acc_onam(__wrks1, hp2->hrec->htyp));
     continue;
    }
   /* cv 0 if different - if different did not find match */
   if (cv == 0) continue; 
   return(vclp);
  }
 return(NULL);
}

/*
 * routine to execute acc_ vcl callback 
 *
 * this is routine executed by vpi_ cb mechanism when variable changed
 */
static int32 exec_acc_vclcb(struct t_cb_data *cbp)
{
 int32 bi, itinum;
 byte *bp, sbv;
 word32 st0, st1, *wrk_idp;
 struct vclrec_t *vclp;
 struct h_t *hp;
 struct net_t *np;
 struct t_vc_record wrkvcl;
 struct t_strengths wrkstval;
 struct t_vpi_value tmpval;
 struct mod_t *mdp;

 /* suppress vcl callbacks during reset */
 /* LOOKATME - is this needed */
 if (__run_state == SS_RESET) return(FALSE); 

 vclp = (struct vclrec_t *) cbp->user_data; 
 /* DBG remove --- */
 if (vclp == NULL) __acc_terr(__FILE__, __LINE__);
 /* --- */
 hp = (struct h_t *) cbp->obj;
 np = hp->hrec->hu.hnp;

 /* access value and store in vc record unless vector - add sets right */
 switch (vclp->vcl_reason) {
  case logic_value_change: case sregister_value_change:
   if (np->n_stren)
    {
     /* must filter out strength - no callback if non value part change */
     if (np->n_isavec) bi = hp->hrec->hi; else bi = 0;
     /* BEWARE - strength internal storage byte vector dependent */
     itinum = (int32) hp->hin_idp[MD_INUM];
     /* SJM 06-18-07 - FIXME - this is stupid hack? */
     mdp = (struct mod_t *) hp->hin_idp[MD_MDP];
     wrk_idp = &(mdp->mod_idata[itinum*mdp->mod_idata_siz]);
     
     bp = (byte *) &(wrk_idp[np->nva_ofs]);
     sbv = bp[bi];
     if ((vclp->vcl_oldstval & 3) == (sbv & 3))
      { vclp->vcl_oldstval = sbv; return(FALSE); }
     vclp->vcl_oldstval = sbv;
     wrkvcl.out_value.logic_value = map_to_accvclval((word32) (sbv & 3));
    }
   else
    {
     __acc_vpi_erroff = TRUE;
     tmpval.format = vpiScalarVal; 
     vpi_get_value((vpiHandle) hp, &tmpval);
     if (__my_vpi_chk_error())
      {
       __acc_err(1756,
        "acc_add_vcl callback on %s - interal error accessing logic value",
        to_acc_onam(__wrks1, hp->hrec->htyp));
       return(FALSE);
      }
     wrkvcl.out_value.logic_value
      = map_vpi_to_accvclval((word32) tmpval.value.scalar);   
    }
   break;
  case strength_value_change:
   if (np->n_stren)
    {
     if (np->n_isavec) bi = hp->hrec->hi; else bi = 0;
     /* BEWARE - strength internal storage byte vector dependent */
     itinum = (int32) hp->hin_idp[MD_INUM];

     /* SJM 06-18-07 - FIXME - this is stupid hack? */
     mdp = (struct mod_t *) hp->hin_idp[MD_MDP];

     wrk_idp = &(mdp->mod_idata[itinum*mdp->mod_idata_siz]);
     bp = (byte *) &(wrk_idp[np->nva_ofs]);
     sbv = bp[bi];

     wrkstval.logic_value = map_vpi_to_accvclval((word32) (sbv & 3));
     st0 = __map_tovpi_stren(((((word32) sbv) >> 5) & 7));
     st1 = __map_tovpi_stren(((((word32) sbv) >> 2) & 7));
     wrkstval.strength1 = (int32) map_vpi_to_accstren(st0);
     wrkstval.strength2 = (int32) map_vpi_to_accstren(st1);
    }
   else  
    {
     __acc_vpi_erroff = TRUE;
     tmpval.format = vpiScalarVal; 
     vpi_get_value((vpiHandle) hp, &tmpval);
     if (__my_vpi_chk_error())
      {
       __acc_err(1756,
        "acc_add_vcl callback on %s - interal error accessing logic value",
        to_acc_onam(__wrks1, hp->hrec->htyp));
       return(FALSE);
      }
     wrkstval.logic_value 
      = map_vpi_to_accvclval((word32) tmpval.value.scalar);   
     wrkstval.strength1 = vclStrong; 
     wrkstval.strength2 = vclStrong;
    }
   /* notice in acc_ struct is record not ptr */
   wrkvcl.out_value.strengths_s = wrkstval;
   break;
  case vector_value_change: case vregister_value_change:
  case integer_value_change: case time_value_change:
   wrkvcl.out_value.vector_handle = (handle) hp;
   break;
  /* these impossible 
  case real_value_change: case event_value_change: case realtime_value_change:
  --- */
  default: __acc_terr(__FILE__, __LINE__);
 }
 /* fill rest of vc record */
 wrkvcl.vc_reason = vclp->vcl_reason; 
 wrkvcl.vc_hightime = (int32) ((__simtime >> 32) & WORDMASK_ULL);
 wrkvcl.vc_lowtime = (int32) (__simtime & WORDMASK_ULL);
 wrkvcl.user_data = vclp->vcl_udata;

 /* final step exec acc vcl consumer routine */
 (*(vclp->vcl_cb_rtn))(&wrkvcl);
 /* all storage automatic (on stack) so no need to free */
 return(TRUE);
}

/*
 * routine to execute acc_ special case prim terminal output vcl callback 
 *
 * this is routine executed by vpi_ cb mechanism when gate output driver
 * changes
 */
static int32 exec_acc_gateout_vclcb(struct t_cb_data *cbp)
{
 struct vclrec_t *vclp;
 struct h_t *hp;
 struct t_vc_record wrkvcl;
 struct t_strengths wrkstval;
 struct t_vpi_value tmpval;

 /* suppress vcl callbacks during reset */
 /* LOOKATME - is this needed */
 if (__run_state == SS_RESET) return(FALSE); 

 vclp = (struct vclrec_t *) cbp->user_data; 
 /* DBG remove --- */
 if (vclp == NULL) __acc_terr(__FILE__, __LINE__);
 /* --- */
 hp = (struct h_t *) cbp->obj;
 /* DBG remove --- */
 if (hp->hrec->htyp != vpiPrimTerm) __acc_terr(__FILE__, __LINE__);
 /* --- */

 /* DBG remove -- */
 if (cbp->value == NULL) __acc_terr(__FILE__, __LINE__);
 /* --- */ 

 /* access value and store in vc record unless vector - add sets right */
 switch (vclp->vcl_reason) {
  case logic_value_change:
   __acc_vpi_erroff = TRUE;
   tmpval.format = vpiScalarVal; 
   vpi_get_value((vpiHandle) hp, &tmpval);
   if (__my_vpi_chk_error())
    {
     __acc_err(1756,
      "acc_add_vcl callback on %s - interal error accessing logic value",
      to_acc_onam(__wrks1, hp->hrec->htyp));
     return(FALSE);
    }
   wrkvcl.out_value.logic_value
    = map_vpi_to_accvclval((word32) tmpval.value.scalar);   
   break;
  case strength_value_change:
   __acc_vpi_erroff = TRUE;
   tmpval.format = vpiStrengthVal; 
   vpi_get_value((vpiHandle) hp, &tmpval);
   if (__my_vpi_chk_error())
    {
     __acc_err(1756,
      "acc_add_vcl callback on %s - interal error accessing logic value",
      to_acc_onam(__wrks1, hp->hrec->htyp));
     return(FALSE);
    }
   wrkstval.logic_value = map_vpi_to_accvclval(tmpval.value.strength->logic);
   wrkstval.strength1 = (int32) map_vpi_to_accstren(tmpval.value.strength->s0);
   wrkstval.strength2 = (int32) map_vpi_to_accstren(tmpval.value.strength->s1);
   /* notice in acc_ struct is record not ptr */
   wrkvcl.out_value.strengths_s = wrkstval;
   break;
  default: __acc_terr(__FILE__, __LINE__);
 }
 /* fill rest of vc record */
 wrkvcl.vc_reason = vclp->vcl_reason; 
 wrkvcl.vc_hightime = (int32) ((__simtime >> 32) & WORDMASK_ULL);
 wrkvcl.vc_lowtime = (int32) (__simtime & WORDMASK_ULL);
 wrkvcl.user_data = vclp->vcl_udata;

 /* final step exec acc vcl consumer routine */
 (*(vclp->vcl_cb_rtn))(&wrkvcl);
 /* all storage automatic (on stack) so no need to free */
 return(TRUE);
}

/*
 * convert internal cver value to acc vcl value
 */
static int32 map_to_accvclval(word32 ival)
{
 switch ((byte) ival) {
  case 0: return(vcl0);
  case 1: return(vcl1);
  case 2: return(vclZ);
  case 3: return(vclX);
  default: 
   __acc_err(1992,
    "illegal internal value %d - unable to map toi vcl value", ival);
   break;
 }
 return(vclX);
}

/*
 * convert vpi value to acc vcl value
 */
static int32 map_vpi_to_accvclval(word32 vpival)
{
 switch ((byte) vpival) {
  case vpi0: return(vcl0);
  case vpi1: return(vcl1);
  case vpiZ: return(vclZ);
  case vpiX: return(vclX);
  default:
   __acc_err(1992,
    "illegal internal PLI value %d - unable to map to vcl value", vpival);
   break;
 }
 return(vclX);
}

/*
 * convert vpi value to acc value
 * LOOKATME - why is this not used
 */
static int32 map_vpi_to_accval(word32 vpival)
{
 switch ((byte) vpival) {
  case vpi0: return(acc0);
  case vpi1: return(acc1);
  case vpiZ: return(accZ);
  case vpiX: return(accX);
  default:
   __acc_err(1992,
    "illegal internal PLI value %d - unable to map to acc value", vpival);
   break;
 }
 return(accX);
}

/*
 * convert acc value to vpi value
 */
static int32 map_acc_to_vpival(word32 accval)
{
 switch ((byte) accval) {
  case acc0: return(vpi0);
  case acc1: return(vpi1);
  case accZ: return(vpiZ);
  case accX: return(vpiX);
  default:
   __acc_err(1992,
    "illegal acc value %d - unable to map to internal PLI value", accval);
   break;
 }
 return(vpiX);
}

/*
 * map from vpi strength values to acc strength
 */
static int32 map_vpi_to_accstren(word32 stval)
{
 word32 accstval;

 switch ((byte) stval) {
  case vpiSupplyDrive: accstval = vclSupply; break;
  case vpiStrongDrive: accstval = vclStrong; break;
  case vpiPullDrive: accstval = vclPull; break;
  case vpiWeakDrive: accstval = vclLarge; break;
  case vpiLargeCharge: accstval = vclWeak; break;
  case vpiMediumCharge: accstval = vclMedium; break;
  case vpiSmallCharge: accstval = vclSmall; break;
  case vpiHiZ: accstval = vclHighZ; break;
  default:
   __acc_err(1992,
    "illegal internal PLI value %d - unable to map to acc strength value",
    stval);
   accstval = vclStrong;
 }
 return(accstval);
}

/*
 * find and remove previously added vcl callback
 */
extern void acc_vcl_delete(handle object_p, int32 (*consumer)(),
 char *user_data, int32 vcl_flags)
{
 struct h_t *hp, *hp2;
 struct gate_t *gp;
 struct expr_t *xp;
 struct vclrec_t *vclp;

 acc_error_flag = FALSE;
 if (__run_state != SS_SIM)
  { acc_not_sim_err("acc_vcl_delete"); return; } 

 /* check arguments */
 if (consumer == NULL)
  {
   __acc_err(1987,
    "acc_vcl_delete call illegal - consumer routine must not be NULL");
   return;
  }

 hp = (struct h_t *) object_p;
 if (!validate_acc_handle("acc_vcl_delete", hp)) return; 

 if (hp->hrec->htyp == vpiPrimTerm)
  {
   /* SJM 11/28/00 - must change handle to terminal for trans */
   gp = hp->hrec->hu.hgp; 
   if (gp->g_class == GC_PULL || gp->g_class == GC_TRAN
    || gp->g_class == GC_TRANIF)
    {
     xp = hp->hrec->hu.hgp->gpins[hp->hrec->hi];
     /* SJM 11/28/00 - also must change handle to terminal index handle */
     hp2 = (struct h_t *) __mk_exprclass_handle(xp, hp->hin_idp,
      hp->hrec->hin_tskp);
     hp = hp2;
     vclp = findmatch_net_vcl_dce(hp, consumer, user_data);
    }
   else vclp = findmatch_term_vcl_dce(hp, consumer, user_data);
  }
 else { vclp = findmatch_net_vcl_dce(hp, consumer, user_data); }

 if (vclp == NULL)
  {
   __acc_err(1989,
    "acc_vcl_delete failed for object %s - no matching vcl change monitor present",
    to_acc_onam(__wrks1, hp->hrec->htyp));
   return;
  }
 /* remove the vpi_ callback and free the vcl record */
 __acc_vpi_erroff = TRUE;

 if (!vpi_remove_cb((vpiHandle) vclp->vclcbp->cb_cbhp))
  {
bad_rem:
   __acc_err(1991,
    "acc_vcl_delete for object %s - internal problem removing change monitor",
    to_acc_onam(__wrks1, hp->hrec->htyp));
   return;
  }
 if (__my_vpi_chk_error()) goto bad_rem;
 __my_free(vclp, sizeof(struct vclrec_t));
}

/*
 * allow user to get version
 */
extern char *acc_version(void)
{
 char s1[RECLEN];

 sprintf(s1, "acc_ access routines Version %s%s of %s\n", __vers,
  __vers2, __ofdt);
 return(add_accstrbuf(s1));
}

/*
 * ROUTINES TO FREE ACC_ OBJECTS FOR RESET
 */

/*
 * VPI TO ACC CONSTANT CONVERSION ROUTINES
 */

/* dense table to map vpi object numbers to acc fulltypes */   
/* BEWARE - this require first vpi object to be dense */
/* -1 for vpi objects with no acc type (existance)  */
static struct vpi_to_acc_t vpi_to_acc[] = {
 { 0, -1 }, 
 { vpiAlways, -1 },
 { vpiAssignStmt, accStatement },
 { vpiAssignment, accStatement },
 { vpiBegin, accStatement },
 { vpiCase, accStatement },
 { vpiCaseItem, -1 },
 { vpiConstant, accConstant },
 { vpiContAssign, -1 },
 { vpiDeassign, accStatement },
 { vpiDefParam, -1 },
 { vpiDelayControl, accStatement },
 { vpiDisable, accStatement },
 { vpiEventControl, accStatement },
 { vpiEventStmt, accStatement },
 { vpiFor, accStatement },
 { vpiForce, accStatement },
 { vpiForever, accStatement },
 { vpiFork, accStatement },
 { vpiFuncCall, -1 },
 { vpiFunction, accFunction },
 /* primitives in acc are also switches */
 { vpiGate, accPrimitive },
 { vpiIf, accStatement },
 { vpiIfElse, accStatement },
 { vpiInitial, -1 },
 { vpiIntegerVar, accIntegerVar },
 /* this is fulltype in acc */
 { vpiInterModPath, accInterModPath },
 { vpiIterator, -1 },
 { vpiIODecl, -1 },
 { vpiMemory, accReg },
 { vpiMemoryWord, accReg },
 { vpiModPath, accModPath },
 { vpiModule, accModule },
 { vpiNamedBegin, accNamedBeginStat },
 { vpiNamedEvent, accNamedEvent },
 { vpiNamedFork, accNamedForkStat },
 { vpiNet, accNet },
 { vpiNetBit, accNetBit },
 { vpiNullStmt, accStatement },
 { vpiOperation, accOperator },
 { vpiParamAssign, -1 },
 { vpiParameter, accParameter },
 { vpiPartSelect, accPartSelect },
 { vpiPathTerm, accPathTerminal },
 { vpiPort, accPort },
 { vpiPortBit, accPortBit },
 { vpiPrimTerm, accTerminal },
 { vpiRealVar, accRealVar },
 { vpiReg, accReg },
 { vpiRegBit, accRegBit },
 { vpiRelease, accStatement },
 { vpiRepeat, accStatement },
 { vpiRepeatControl, accStatement },
 { vpiSchedEvent, -1 },
 { vpiSpecParam, accSpecparam },
 { vpiSwitch, accPrimitive },
 /* special case need to distinquish: accSystemFunction, and real form */
 { vpiSysFuncCall, accSystemFunction },
 { vpiSysTaskCall, accSystemTask },
 { vpiTableEntry, -1 },
 { vpiTask, accTask },
 { vpiTaskCall, -1 },
 { vpiTchk, accTchk },
 { vpiTchkTerm, accTchkTerminal },
 { vpiTimeVar, accTimeVar },
 { vpiTimeQueue, -1 },
 { vpiUdp, accPrimitive },
 { vpiUdpDefn, -1 },
 /* special case maps to: accUserFunction, accUserRealFunction */
 /* LOOKATME - also accSystemTask ?? */
 { vpiUserSystf, accUserFunction },
 { vpiVarSelect, accRegBit },
 { vpiWait, accStatement },
 { vpiWhile, accStatement }
};

/* BEWARE if vpi_user.h changes this must change to highest vpi obj val */
#define LAST_VPIOBJTYP vpiWhile

/*
 * get acc type - know handle already validated
 *
 * must be called with known good (checked) vpi handle 
 */
static struct vpi_to_acc_t *get_acc_typerec(struct h_t *hp)
{
 struct vpi_to_acc_t *accvpip;

 accvpip = &(vpi_to_acc[hp->hrec->htyp]);
 /* DBG remove -- */
 if (accvpip->acc_otyp == -1) __acc_terr(__FILE__, __LINE__);
 if (accvpip->vpiotyp != hp->hrec->htyp) __acc_terr(__FILE__, __LINE__);
 /* --- */
 return(accvpip);
}

/*
 * routine to access acc fulltype constant from type
 *
 * for most fulltype is same as type
 */
static int32 get_acc_fulltype(vpiHandle vpiop, struct vpi_to_acc_t *accvpip)
{
 int32 rv;
 struct h_t *hp; 
 s_vpi_systf_data systfdat;
 struct net_t *np;
 struct mod_pin_t *mpp;
 struct gate_t *gp;
 struct primtab_t *ptp;
 struct st_t *stp;
 struct tchk_t *tcp;
 struct mod_t *mdp;

 hp = (struct h_t *) vpiop; 

 if (accvpip->acc_otyp == accUserFunction
  || accvpip->acc_otyp == accSystemFunction)
  {
   /* here need to distinguish real from non real case */
   __acc_vpi_erroff = TRUE;
   vpi_get_systf_info(vpiop, &systfdat);
   if (__my_vpi_chk_error())
    {
     __acc_err(1952,
      "acc_fetch_fulltype unable to access systf_info for %s object",
      to_acc_onam(__wrks1, hp->hrec->htyp));
     return(0);
    }
   if (systfdat.sysfunctype == vpiRealFunc)
    {
     if (hp->hrec->htyp == vpiUserSystf) return(accUserRealFunction);
     if (hp->hrec->htyp == vpiSysFuncCall) return(accSystemRealFunction);
     __acc_terr(__FILE__, __LINE__);
    }
   if (hp->hrec->htyp == vpiUserSystf) return(accUserFunction);
   if (hp->hrec->htyp == vpiSysFuncCall) return(accSystemFunction);
   __acc_terr(__FILE__, __LINE__);
   return(0);
  }

 hp = (struct h_t *) vpiop; 
 switch (accvpip->acc_otyp) {
  case accModule:
   mdp = hp->hrec->hu.hmdp;
   if (mdp->minstnum == 0) return(accTopModule);
   if (mdp->m_iscell) return(accCellInstance);
   return(accModuleInstance);
  case accNet: 
   np = hp->hrec->hu.hnp;
   switch ((byte) np->ntyp) {
    case N_WIRE: rv = accWire; break;
    case N_TRI: rv = accTri; break;
    case N_TRI0: rv = accTri0; break;
    case N_TRI1: rv = accTri1; break;
    case N_TRIAND: rv = accTriand; break;
    case N_TRIOR: rv = accTrior; break;
    case N_TRIREG: rv = accTrireg; break;
    case N_WA: rv = accWand; break;
    case N_WO: rv = accWor; break;
    case N_SUPPLY0: rv = accSupply0; break;
    case N_SUPPLY1: rv = accSupply1; break;
    default: rv = -1; __acc_terr(__FILE__, __LINE__);
   }
   return(rv);
  case accParameter: case accSpecparam:
   np = hp->hrec->hu.hnp;
   /* DBG remove --- */
   if (!np->n_isaparam) __acc_terr(__FILE__, __LINE__);
   /* --- */
   if (np->ntyp == N_REAL) return(accRealParam);
   if (np->nu.ct->pstring) return(accStringParam);
   return(accIntegerParam);
  case accModPath:
   /* LOOKATME - where do intermodule paths come from ?? */
   return(accModPath);
  case accPathTerminal:
   if (hp->hrec->htyp2 == vpiModPathIn || hp->hrec->htyp2 == vpiModDataPathIn)
    return(accPathInput);
   if (hp->hrec->htyp2 == vpiModPathOut) return(accPathOutput);
   /* DBG remove --- */
   __acc_terr(__FILE__, __LINE__);
   /* --- */
   break;
  case accPort:
   mdp = (struct mod_t *) hp->hin_idp[MD_MDP];
   mpp = &(mdp->mpins[hp->hrec->hu.hpi]);
   if (mpp->mpref->optyp == LCB) return(accConcatPort);
   if (mpp->mpref->optyp == PARTSEL) return(accPartSelectPort);
   if (mpp->mpref->optyp == PARTSEL_NDX_PLUS) return(accPartSelectPort);
   if (mpp->mpref->optyp == PARTSEL_NDX_MINUS) return(accPartSelectPort);
   if (mpp->mpref->optyp == LSB && !mpp->mpref->lu.x->lu.sy->el.enp->n_isarr) 
    return(accBitSelectPort);
   if (mpp->mpwide == 1) return(accScalarPort);
   return(accVectorPort);
  case accPrimitive:
   gp = hp->hrec->hu.hgp;
   if (gp->g_class == GC_UDP)
    {
     if (gp->gmsym->el.eudpp->utyp == U_COMB) return(accCombPrim);
     return(accSeqPrim);
    }
   ptp = gp->gmsym->el.eprimp; 
   switch ((byte) ptp->gateid) {
    /* LOOKATM - where are pullup/pulldown "gates" */
    case G_BITREDAND: return(accAndGate);
    case G_NAND: return(accNandGate);
    case G_NOR: return(accNorGate);
    case G_BITREDOR: return(accOrGate);
    case G_BITREDXOR: return(accXorGate);
    case G_REDXNOR: return(accXnorGate);
    case G_BUF: return(accBufGate);
    case G_NOT: return(accNotGate);
    case G_BUFIF0: return(accBufif0Gate);
    case G_BUFIF1: return(accBufif1Gate);
    case G_NOTIF0: return(accNotif0Gate);
    case G_NOTIF1: return(accNotif1Gate);
    case G_NMOS: return(accNmosGate);
    case G_RNMOS: return(accRnmosGate);
    case G_PMOS: return(accPmosGate);
    case G_RPMOS: return(accRpmosGate);
    case G_CMOS: return(accCmosGate);
    case G_RCMOS: return(accRcmosGate);
    case G_TRAN: return(accTranGate);
    case G_RTRAN: return(accRtranGate);
    case G_TRANIF0: return(accTranif0Gate);
    case G_RTRANIF0: return(accRtranif0Gate);
    case G_TRANIF1: return(accTranif1Gate);
    case G_RTRANIF1: return(accRtranif1Gate);
    default: __acc_terr(__FILE__, __LINE__);
   }
   break;
  case accStatement:
   stp = hp->hrec->hu.hstp;
   if (stp->stmttyp == S_NAMBLK)
    {
     if (stp->st.snbtsk->tsktyp == Begin) return(accNamedBeginStat);
     if (stp->st.snbtsk->tsktyp == FORK) return(accNamedForkStat);
     __acc_terr(__FILE__, __LINE__);
     break;
    }
   /* any other statement type, not distinguished in acc */
   return(accStatement);
  case accTchk:
   tcp = hp->hrec->hu.htcp; 
   switch ((byte) tcp->tchktyp) {
    case TCHK_SETUP: return(accSetup);
    case TCHK_HOLD: return(accHold);  
    case TCHK_WIDTH: return(accWidth);
    case TCHK_PERIOD: return(accPeriod);
    case TCHK_SKEW: return(accSkew);
    case TCHK_RECOVERY: return(accRecovery);
    case TCHK_NOCHANGE: return(accNoChange);
    case TCHK_SETUPHOLD: return(accSetuphold);
    /* SJM 01/16/04 - notice the new 2001 LRM timing checks not in acc_ */
    default: __acc_terr(__FILE__, __LINE__);
   }
   break;
  case accTerminal:
   gp = hp->hrec->hu.hgp; 
   switch (gp->g_class) { 
    case GC_LOGIC: case GC_UDP: case GC_BUFIF: case GC_MOS: case GC_CMOS:
     if (hp->hrec->hi > 1) return(accInputTerminal);
     return(accOutputTerminal);
    case GC_TRAN: return(accInoutTerminal);
    case GC_TRANIF:
     if (hp->hrec->hi >= 2) return(accInputTerminal);
     return(accInoutTerminal);
    case GC_PULL: return(accOutputTerminal);
    default: __acc_terr(__FILE__, __LINE__);
   }
   break;
  case accWirePath: return(accInterModPath); 
 }
 /* otherwise full type same as type */
 return(accvpip->acc_otyp);
}

/* 
 * table of acc configuration constants (from acc user .h) 
 *
 * table must be sorted but is not dense or numeric ordered 
 */
static struct pnamvpi_t accconfig_names[] = {
 { "accDefaultAttr0", accDefaultAttr0 },
 { "accDevelopmentVersion", accDevelopmentVersion },
 { "accDisplayErrors", accDisplayErrors },
 { "accDisplayWarnings", accDisplayWarnings },
 { "accEnableArgs", accEnableArgs },
 { "accMapToMipd", accMapToMipd },
 { "accMinTypMaxDelays", accMinTypMaxDelays },
 { "accPathDelayCount", accPathDelayCount },
 { "accPathDelimStr", accPathDelimStr },
 { "accToHiZDelay", accToHiZDelay }
};
#define NCGFCONS (sizeof(accconfig_names) / sizeof(struct pnamvpi_t))

/*
 * given configuration constant value - table index
 * returns -1 if not found
 *
 * names sorted but not contiguous values
 * LOOKATME - using vpi_ tables so maybe should make acc duplicates
 */
static char *get_cfgconst_nam(char *s, int32 cfg_connum)
{
 int32 i;

 for (i = 0; i < NCGFCONS; i++)
  {
   if (accconfig_names[i].vpiproptyp == cfg_connum)
    {
     strcpy(s, accconfig_names[i].vpipropnam);
     return(s);
    }
  }
 strcpy(s, "**UNKNOWN**");
 return(s);
}

/*
 * ACC VALUE TO NAME CONVERSION ROUTINES
 */

struct accnam_t accnamtab[] = {
 { "accModule", accModule },
 { "accScope", accScope },
 { "accNet", accNet },
 { "accReg", accReg },
 { "accPort", accPort },
 { "accTerminal", accTerminal },
 { "accInputTerminal", accInputTerminal },
 { "accOutputTerminal", accOutputTerminal },
 { "accInoutTerminal", accInoutTerminal },
 { "accCombPrim", accCombPrim },
 { "accSeqPrim", accSeqPrim },
 { "accAndGate", accAndGate },
 { "accNandGate", accNandGate },
 { "accNorGate", accNorGate },
 { "accOrGate", accOrGate },
 { "accXorGate", accXorGate },
 { "accXnorGate", accXnorGate },
 { "accBufGate", accBufGate },
 { "accNotGate", accNotGate },
 { "accBufif0Gate", accBufif0Gate },
 { "accBufif1Gate", accBufif1Gate },
 { "accNotif0Gate", accNotif0Gate },
 { "accNotif1Gate", accNotif1Gate },
 { "accNmosGate", accNmosGate },
 { "accPmosGate", accPmosGate },
 { "accCmosGate", accCmosGate },
 { "accRnmosGate", accRnmosGate },
 { "accRpmosGate", accRpmosGate },
 { "accRcmosGate", accRcmosGate },
 { "accRtranGate", accRtranGate },
 { "accRtranif0Gate", accRtranif0Gate },
 { "accRtranif1Gate", accRtranif1Gate },
 { "accTranGate", accTranGate },
 { "accTranif0Gate", accTranif0Gate },
 { "accTranif1Gate", accTranif1Gate },
 { "accPullupGate", accPullupGate },
 { "accPulldownGate", accPulldownGate },
 { "accIntegerParam", accIntegerParam },
 { "accRealParam", accRealParam },
 { "accStringParam", accStringParam },
 { "accTchk", accTchk },
 { "accPrimitive", accPrimitive },
 { "accPortBit", accPortBit },
 { "accNetBit", accNetBit },
 { "accRegBit", accRegBit },
 { "accParameter", accParameter },
 { "accSpecparam", accSpecparam },
 { "accTopModule", accTopModule },
 { "accModuleInstance", accModuleInstance },
 { "accCellInstance", accCellInstance },
 { "accModPath", accModPath },
 { "accWirePath", accWirePath },
 { "accInterModPath", accInterModPath },
 { "accScalarPort", accScalarPort },
 { "accPartSelectPort", accPartSelectPort },
 { "accVectorPort", accVectorPort },
 { "accConcatPort", accConcatPort },
 { "accWire", accWire },
 { "accWand", accWand },
 { "accWor", accWor },
 { "accTri", accTri },
 { "accTriand", accTriand },
 { "accTrior", accTrior },
 { "accTri0", accTri0 },
 { "accTri1", accTri1 },
 { "accTrireg", accTrireg },
 { "accSupply0", accSupply0 },
 { "accSupply1", accSupply1 },
 { "accNamedEvent", accNamedEvent },
 { "accIntegerVar", accIntegerVar },
 { "accIntVar", accIntVar },
 { "accRealVar", accRealVar },
 { "accTimeVar", accTimeVar },
 { "accScalar", accScalar },
 { "accVector", accVector },
 /* LOOKATME - where does this come from */
 { "accCollapsedNet", accCollapsedNet },
 { "accExpandedVector", accExpandedVector },
 { "accUnExpandedVector", accUnExpandedVector },
 { "accSetup", accSetup },
 { "accHold", accHold },
 { "accWidth", accWidth },
 { "accPeriod", accPeriod },
 { "accRecovery", accRecovery },
 { "accSkew", accSkew },
 { "accNochange", accNochange },
 { "accSetuphold", accSetuphold },
 { "accInput", accInput },
 { "accOutput", accOutput },
 { "accInout", accInout },
 { "accMixedIo", accMixedIo },
 { "accPositive", accPositive },
 { "accNegative", accNegative },
 { "accUnknown", accUnknown },
 { "accPathTerminal", accPathTerminal },
 { "accPathInput", accPathInput },
 { "accPathOutput", accPathOutput },
 { "accDataPath", accDataPath },
 { "accTchkTerminal", accTchkTerminal },
 { "accBitSelect", accBitSelect },
 { "accPartSelect", accPartSelect },
 { "accTask", accTask },
 { "accFunction", accFunction },
 { "accStatement", accStatement },
 { "accSystemTask", accSystemTask },
 { "accSystemFunction", accSystemFunction },
 { "accSystemRealFunction", accSystemRealFunction },
 { "accUserTask", accUserTask },
 { "accUserFunction", accUserFunction },
 { "accUserRealFunction", accUserRealFunction },
 /* LOOKATME - where are these ??? */
 { "accNamedBeginStat", accNamedBeginStat },
 { "accNamedForkStat", accNamedForkStat },

 { "accConstant", accConstant },
 { "accConcat", accConcat },
 { "accOperator", accOperator },
 { "accMinTypMax", accMinTypMax },
 /* LOOKATME - where as this ??? */
 { "accModPathHasIfnone", accModPathHasIfnone }
};
#define NACC_CONS (sizeof(accnamtab) / sizeof(struct accnam_t))

/*
 * routine to return name of acc type or fulltype constant
 *
 * LOOKATME - could use binary search but should be rare
 */
static char *get_accnam(int32 accnum)
{
 int32 i;

 for (i = 0; i < NACC_CONS; i++) 
  { if (accnamtab[i].accval == accnum) return(accnamtab[i].accnam); }
 /* nil on no match - caller emits error */
 return(NULL);
}

/*
 * ROUTINES TO ACCESS INTERNAL INFO 
 */

/*
 * undocumented (to users) debug routine for showing contents of acc_ handle
 *
 * LOOKATME - maybe should dump more information for some object types 
 * LOOKATME - not portable because of addr cast
 */
extern int32 __acc_show_object(handle obj)
{
 int32 bad_inst, bad_tsk, first_time, ttyp, tryget_name;
 struct h_t *hp;
 struct hrec_t *hrp;
 struct vpi_to_acc_t *accvpip;
 char *chp, s1[RECLEN], s2[RECLEN]; 

 __my_fprintf(stdout, ">>> showing acc_ object:\n");
 hp = (struct h_t *) obj;

 if (!__chk_showobj(hp, &(bad_inst), &(bad_tsk))) return(0);
 hrp = hp->hrec;

 tryget_name = TRUE;
 accvpip = &(vpi_to_acc[hrp->htyp]);
 if (accvpip->acc_otyp <= 0)
  {
   /* notice access vpi Name here */
   __my_fprintf(stdout, 
    "**acc handle %s invalid (probably vpi_ not acc_) - showing anyway\n",
    __to_vpionam(__wrks1, hrp->htyp));
  }

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
     __my_fprintf(stdout, " scope %s", __msg_idp_blditree(s1, hp->hin_idp,
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
     __my_fprintf(stdout, " scope %s (**task/func bad**)",
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
   __my_fprintf(stdout, " **bad instance and bad task scope**");
   tryget_name = FALSE;
  }

 /* LOOKATME - maybe should try to get def name if can */
 if (tryget_name)
  {
   __acc_vpi_erroff = TRUE;
   /* this access error vpi_ error info and turns off vpi error cbs */  
   /* for objects without names, expect fail here */
   chp = vpi_get_str(vpiName, (vpiHandle) obj);
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
   sprintf(s1, "Scheduled event done=%d", hrp->evnt_done);
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
 * COMMON ERROR CONDITION ERROR ROUTINES
 */

/*
 * emit common compilation in progress (no n.l to traverse) message
 */
static void acc_not_sim_err(char *rnam)
{
 __acc_err(1748, 
  "%s routine not callable - simulation not started or reset in progress",
  rnam);
}

/*
 * validate vpi_ handle underneath acc handle
 */
static int32 validate_acc_handle(char *rnam, struct h_t *hp) 
{
 struct vpi_to_acc_t *accvpip;
 struct hrec_t *hrp;

 /* if low value bad since ptr */
 /* SJM 07/08/01 - high bit can be on and 4 64 bit ptr just look at low 32 */
 if (hp == NULL || ((word32) hp) < 256)
  {
   strcpy(__wrks1, "** NULL OR LOW NUMBER **");
bad_acc_handle:
   __acc_err(1947,
    "%s: handle illegal magic number or object type %s out of range",
    rnam, __wrks1); 
   return(FALSE);
  }
 hrp = hp->hrec;
 if (hrp == NULL || ((word32) hrp) < 256 || hrp->h_magic != PVH_MAGIC)
  {
   strcpy(__wrks1, "** PTR INTO DATA BASE ILLEGAL **");
   goto bad_acc_handle;
  }
 if (__to_vpionam(__wrks1, hrp->htyp) == NULL || hrp->htyp > LAST_VPIOBJTYP) 
  {
   sprintf(__wrks1, "underlying vpi: %d", hrp->htyp);
   goto bad_acc_handle;
  }
 accvpip = &(vpi_to_acc[hrp->htyp]);
 if (accvpip->acc_otyp <= 0)
  {
   /* notice access vpi Name here */
   __acc_err(1948, "acc handle %s invalid (object probably vpi_ not acc_)",
    __to_vpionam(__wrks1, hrp->htyp));
   goto bad_acc_handle;
  }
 return(TRUE);
}

/*
 * convert acc object to its type name
 */
static char *to_acc_onam(char *s, word32 vpioval)
{
 int32 accoval;

 if (vpioval < 1 || vpioval > LAST_VPIOBJTYP)
  {
out_of_rng:
   sprintf(s, "**out of range or invalid (vpi_ type %lu)", vpioval);
   return(s);
  }
 if ((accoval = vpi_to_acc[vpioval].acc_otyp) == -1) goto out_of_rng;

 /* once -1 checked for - know this will succeed */
 strcpy(s, get_accnam(accoval));
 return(s);
}

/*
 * ACC VPI ERROR INTERFACE ROUTINES
 */

/*
 * my wrapper around vpi_ check error
 *
 * must die on fatal error
 * this resets vpi error indicator in case acc_ and vpi_ mixed
 */
extern int32 __my_vpi_chk_error(void)
{
 struct t_vpi_error_info einfotab;
 struct t_vpi_error_info *einfop;

 __acc_vpi_erroff = FALSE;
 if (!vpi_chk_error(&einfotab)) return(FALSE);
 einfop = &einfotab;
 /* notices and warning are not acc_ problems */
 if (einfop->level == vpiNotice || einfop->level == vpiWarning)
  return(FALSE);

 /* for internal and system errors give up */
 /* LOOKATME - maybe system should not be fatal */
 if (einfop->level == vpiInternal || einfop->level == vpiSystem)
  {
   /* this never returns */
   __acc_vpi_terr(einfop->file, einfop->line);
  }
 return(TRUE);
}

/*
 * ACC ERROR ROUTINES
 */

/*
 * emit acc error (statement location know version)
 * notice user errors emitted with tf_err or tf_warning
 */
/*VARARGS*/
extern void __acc_sferr(int32 id_num, char *fmt, ...)
{
 char s1[RECLEN], s2[RECLEN];
 va_list va, va2, va3;

 __pv_err_cnt++;
 acc_error_flag = TRUE;
 if (!__acc_displayerrors) return;

 if (__run_state == SS_SIM)
  sprintf(s1, " now %s", __to_timstr(s2, &__simtime)); 
 else strcpy(s1, "");

 if (__vpierr_cb_active && !__iact_state)
  {
   int32 slen;
   char vpis1[IDLEN], vpis2[4*IDLEN], *vpichp; 

   /* reset in case user called sim control operation from wrong place */
   __errorcb_suppress_msg = FALSE;

   sprintf(vpis1, "**%s(%d) ACC PLI ERROR**%s [%d] ", __in_fils[__sfnam_ind],
    __slin_cnt, s1, id_num);
   va_start(va, fmt);
   vsprintf(vpis2, vpis1, va);
   va_end(va);
   
   slen = strlen(vpis1) + strlen(vpis2) + 1;
   vpichp = __my_malloc(slen);
   strcpy(vpichp, vpis1);
   strcat(vpichp, vpis2);

   __cberror_fill_einfo(ERROR, id_num, vpichp, __in_fils[__sfnam_ind],
    __slin_cnt);
   __vpi_error_trycall();

   __my_free(vpichp, slen);
   /* if vpi_control used to suppress emsg, used up so turn off here */ 
   if (__errorcb_suppress_msg)
    { __errorcb_suppress_msg = FALSE; return; }
   }

 __my_fprintf(stdout, "**%s(%d) ACC PLI ERROR**%s [%d] ",
  __in_fils[__sfnam_ind], __slin_cnt, s1, id_num);

 /* SJM 10/13/99 - ansii std says varargs not usable after vprintf called */
 va_start(va2, fmt);
 va_start(va3, fmt);
 __my_vfprintf(stdout, fmt, va2, va3);
 va_end(va2);
 va_end(va3);

 my_putc_('\n', stdout);
 /* no maximum error count*/
}

/*
 * emit acc error (location not known)
 * notice user errors emitted with tf_error or tf_warning
 */
/*VARARGS*/
extern void __acc_err(int32 id_num, char *fmt, ...)
{
 va_list va, va2, va3;
 char s1[RECLEN], s2[RECLEN];

 acc_error_flag = TRUE;
 __pv_err_cnt++;
 if (!__acc_displayerrors) return;

 if (__run_state == SS_SIM)
  sprintf(s1, " now %s", __to_timstr(s2, &__simtime)); 
 else strcpy(s1, "");

 if (__vpierr_cb_active && !__iact_state)
  {
   int32 slen;
   char vpis1[IDLEN], vpis2[4*IDLEN], *vpichp; 

   /* reset in case user called sim control operation from wrong place */
   __errorcb_suppress_msg = FALSE;

   sprintf(vpis1, "**ACC PLI ERROR**%s [%d] ", s1, id_num);
   va_start(va, fmt);
   vsprintf(vpis2, vpis1, va);
   va_end(va);
   
   slen = strlen(vpis1) + strlen(vpis2) + 1;
   vpichp = __my_malloc(slen);
   strcpy(vpichp, vpis1);
   strcat(vpichp, vpis2);

   __cberror_fill_einfo(WARN, id_num, vpichp, "[NONE]", 0);
   __vpi_error_trycall();

   __my_free(vpichp, slen);
   /* if vpi_control used to suppress emsg, used up so turn off here */ 
   if (__errorcb_suppress_msg)
    { __errorcb_suppress_msg = FALSE; return; }
   }

 __my_fprintf(stdout, "**ACC PLI ERROR**%s [%d] ", s1, id_num);

 /* SJM 10/13/99 - ansii std says varargs not usable after vprintf called */
 va_start(va2, fmt);
 va_start(va3, fmt);
 __my_vfprintf(stdout, fmt, va2, va3);
 va_end(va2);
 va_end(va3);

 my_putc_('\n', stdout);
 /* no maximum error count*/
}

/*
 * emit acc warn (statement location know version)
 * notice user errors emitted with tf_err or tf_warn
 */
/*VARARGS*/
extern void __acc_sfwarn(int32 id_num, char *fmt, ...)
{
 va_list va, va2, va3;
 char s1[RECLEN], s2[RECLEN];

 __pv_warn_cnt++;
 if (!__acc_displaywarnings) return;

 if (__run_state == SS_SIM)
  sprintf(s1, " now %s", __to_timstr(s2, &__simtime)); 
 else strcpy(s1, "");

 if (__vpierr_cb_active && !__iact_state)
  {
   int32 slen;
   char vpis1[IDLEN], vpis2[4*IDLEN], *vpichp; 

   /* reset in case user called sim control operation from wrong place */
   __errorcb_suppress_msg = FALSE;

   sprintf(vpis1, "**%s(%d) ACC PLI WARN**%s [%d] ", __in_fils[__sfnam_ind],
    __slin_cnt, s1, id_num);
   va_start(va, fmt);
   vsprintf(vpis2, vpis1, va);
   va_end(va);
   
   slen = strlen(vpis1) + strlen(vpis2) + 1;
   vpichp = __my_malloc(slen);
   strcpy(vpichp, vpis1);
   strcat(vpichp, vpis2);

   __cberror_fill_einfo(WARN, id_num, vpichp, __in_fils[__sfnam_ind],
    __slin_cnt);
   __vpi_error_trycall();

   __my_free(vpichp, slen);
   /* if vpi_control used to suppress emsg, used up so turn off here */ 
   if (__errorcb_suppress_msg)
    { __errorcb_suppress_msg = FALSE; return; }
   }

 __my_fprintf(stdout, "**%s(%d) ACC PLI WARN**%s [%d] ",
  __in_fils[__sfnam_ind], __slin_cnt, s1, id_num);

 /* SJM 10/13/99 - ansii std says varargs not usable after vprintf called */
 va_start(va2, fmt);
 va_start(va3, fmt);
 __my_vfprintf(stdout, fmt, va2, va3);
 va_end(va2);
 va_end(va3);

 my_putc_('\n', stdout);
 /* no maximum error count*/
}

/*
 * emit acc warn
 * notice user errors emitted with tf_err or tf_warn
 */
/*VARARGS*/
extern void __acc_warn(int32 id_num, char *fmt, ...)
{
 va_list va, va2, va3;
 char s1[RECLEN], s2[RECLEN];

 __pv_warn_cnt++;
 if (!__acc_displaywarnings) return;

 if (__run_state == SS_SIM)
  sprintf(s1, " now %s", __to_timstr(s2, &__simtime)); 
 else strcpy(s1, "");

 if (__vpierr_cb_active && !__iact_state)
  {
   int32 slen;
   char vpis1[IDLEN], vpis2[4*IDLEN], *vpichp; 

   /* reset in case user called sim control operation from wrong place */
   __errorcb_suppress_msg = FALSE;

   sprintf(vpis1, "**ACC PLI WARN**%s [%d] ", s1, id_num);
   va_start(va, fmt);
   vsprintf(vpis2, vpis1, va);
   va_end(va);
   
   slen = strlen(vpis1) + strlen(vpis2) + 1;
   vpichp = __my_malloc(slen);
   strcpy(vpichp, vpis1);
   strcat(vpichp, vpis2);

   __cberror_fill_einfo(WARN, id_num, vpichp, "[NONE]", 0);
   __vpi_error_trycall();

   __my_free(vpichp, slen);
   /* if vpi_control used to suppress emsg, used up so turn off here */ 
   if (__errorcb_suppress_msg)
    { __errorcb_suppress_msg = FALSE; return; }
   }

 __my_fprintf(stdout, "**ACC PLI WARN**%s [%d] ", s1, id_num);

 /* SJM 10/13/99 - ansii std says varargs not usable after vprintf called */
 va_start(va2, fmt);
 va_start(va3, fmt);
 __my_vfprintf(stdout, fmt, va2, va3);
 va_end(va2);
 va_end(va3);

 my_putc_('\n', stdout);
 /* no maximum error count*/
}

/*
 * acc internal fatal error 
 */
extern void __acc_terr(char *fnam, int32 lno)
{
 __pv_terr(331,
  "ACC PLI INTERNAL - source line **%s(%d) - maybe at **%s(%d)\n",
  fnam, lno, __in_fils[__sfnam_ind], __slin_cnt);
}

/*
 * acc internal fatal error occurring in vpi_ routine 
 */
extern void __acc_vpi_terr(char *fnam, int32 lno)
{
 __pv_terr(332,
  "ACC PLI INTERNAL (IN VPI) - source line **%s(%d) - maybe at **%s(%d)\n",
  fnam, lno, __in_fils[__sfnam_ind], __slin_cnt);
}
