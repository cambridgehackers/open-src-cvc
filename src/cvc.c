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
 * main module - command option and license manager code
 */

/*
 * main module
 */
#include <stdio.h>
#include <time.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/time.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <pthread.h>

#include <ctype.h>

#ifndef __NOSIGS__
#include <signal.h>
#endif

#include <setjmp.h>

#ifdef __DBMALLOC__
#include "../malloc.h"
#endif

#include "v.h"
#include "cvmacros.h"

static char copyright[]
 = "Copyright (c) 1991-2014 Tachyon Design Automation Corp.";

/* declares from v.h */
/* various simulation counting variables */
char *__vers;          /* actual product info */
char *__vers2;
char *__ofdt;
char *__platform;
char *__start_sp, *__end_sp;/* pointer for "big" memory allocator */
char *__pvdate;        /* date in unix form */
char *__pv_timestamp;  /* timestamp for design */
time_t __start_time;   /* start wall clock times in secs. */
time_t __start_mstime; /* start millisecond part */
time_t __end_comp_time;/* end of compilation time */
time_t __end_comp_mstime;
time_t __end_prep_time;/* end of preparation time */
time_t __end_prep_mstime;
time_t __end_time;     /* start and end wall clock times */
time_t __end_mstime;   /* start and end wall clock times */

/* various file variables and global data base flags (i/o vars) */
char **__in_fils;      /* malloced input file list from args */
int32 __siz_in_fils;   /* current size of input files */
int32 __last_inf;      /* last input file in list */
int32 __last_optf;     /* last option file */
int32 __last_lbf;      /* last lib/inc file (starts last_inf + 1) */
int32 __last_srcf;     /* last src containing file for debugger */
struct incloc_t *__inclst_hdr; /* header of included files list */
struct incloc_t *__inclst_end; /* end of included files list */
struct filpos_t *__filpostab; /* in fils size tab of file line pos. */
FILE *__save_log_s;    /* if $nolog executed, value to use if log */
int32 __echo_iactcmds_tolog; /* T => echo interactive cmds to log file */
FILE *__save_key_s;    /* if $nolog executed, value to use if log */
int32 __nokey_seen;    /* $nokey executed and no key */
FILE *__in_s;
FILE *__log_s;
FILE *__cmd_s;         /* command file source or null for tty */ 
FILE *__key_s;         /* if key_s nil but key_fnam not, must open */
struct optlst_t *__opt_hdr;   /* header of expanded option list */
struct optlst_t *__opt_end;   /* wrk end of expanded option list */
//AIV 06-31-09 - FIXME??? this can be right since setting bit numbers up to 64 
word32 *__wsupptab;    /* tab (1 bit/msg) for warn and iact suppress */
char *__blnkline;      /* work blank line */
char __pv_homedir[RECLEN]; /* home dir - . if HOME env. not set */
struct mcchan_t __mulchan_tab[32];/* mc desc. tab (32 built in Ver) */ 
struct fiofd_t **__fio_fdtab; /* array of ptrs to file io stream */
char *__fiolp;         /* fio file input work string ptr */
char *__fiofp;         /* fio file input work fmt string ptr */
long __scanf_pos;      /* byte offset position of scanf in file */
sighandler *__old_int_sig;  /* value of quit (^c) signal on entry */
int32 __force_base;    /* for output force base if not BASENONE */
struct vinstk_t **__vinstk;/* open file/macro list in stack form */
struct vinstk_t *__visp;/* pointer to top of open input stack */
int32 __vin_top;       /* index of top of current file stack */
char *__log_fnam;      /* log file for all terminal output */
char *__sdf_opt_log_fnam; /* sdf log file if set by cmd arg */
FILE *__sdf_opt_log_s; /* and open file ptr */
int32 __sdf_no_warns;  /* T => don't print any SDF warning msgs */
int32 __sdf_no_errs;   /* T => don't print any SDF error msgs */
char *__cmd_fnam;      /* command interact. input file name */
char *__cmd_start_fnam;/* -i startup interactive input file name */
char *__key_fnam;      /* key file name and stream */
FILE *__tr_s;          /* trace output file - can be stdout */
char *__tr_fnam;
int32 __cmd_ifi;       /* constant command in_fils index */
char *__lic_path;      /* +licpath [path] if option used */
FILE *__sdf_s;         /* current SDF back annotate file/stream */
struct sdfnamlst_t *__sdflst; /* list of sdf annotate option files */
struct sdf_tskenlst_t *__sdftskenlst; /* sdf annotate tsks in src lst */
struct sdf_tskenlst_t *__sdftelst_end;/* end of list for src order */
int32 __sdf_sav_enum;  /* saved error num. for annotate inhibit */
int32 __sdf_sav_maxerrs; /* saved max errors so won't stop */
int32 __has_sdfann_calls;/* T => no sdf annotate systsk calls in src */ 
int32 __sdf_active;    /* T => annotating SDF - for PLI erro code  */
int32 __sdf_during_sim;/* T => can't compile SDF file before sim */
struct mod_t *__sdf_mdp; /* special sdf context mod */

/* cfg variables */
char *__cmdl_library;  /* library name to file off the command line */
struct mapfiles_t *__map_files_hd; /* hdr of map files from cmd args */
struct mapfiles_t *__map_files_tail; /* end of map file list */
struct cfglib_t *__cfglib_hd; /* head of list of libs for cfg */
struct cfglib_t *__cfglib_tail; /* and tail */
struct cfg_t *__cfg_hd;/* head of list of cfgs */
struct cfg_t *__cur_cfg;/* current cfg */
struct mod_t *__cfg_mdp;/* SJM - remove me - why global */
char **__bind_inam_comptab;/* during cfg binding, comp descent comps */ 
int32 __siz_bind_comps;/* current malloc size of table */
int32 __last_bind_comp_ndx;/* last currently used comp end index */ 
int32 __cfg_verbose;   /* T => emit cfg reading verbose messages */ 

/* option config and plitab processing variables */
struct ocfil_lst_t *__optcfg_fils; /* optconfig file names */
struct ocfil_lst_t *__last_optcfg_fil; /* and tail */
struct ocfg_stmt_t *__ocfg_stmts; /* o cfg stmts from all opts lst */ 
struct oc_vtok_t *__wrk_ocvtok_hd; /* opt cfg wrd token list hd */
struct oc_vtok_t *__wrk_ocvtok_end;/* and current end */
char __cur_optcfg_cntxt_str[RECLEN]; /* cntxt name for optcfg warns */ 

/* file variables */
int32 __cur_infi;      /* index in in_fils of current file */
struct optlst_t *__new_opt_hdr;/* header of expanded option list */
struct optlst_t *__new_opt_end;/* wrk end of expanded option list */
struct optlst_t *__log_olp;   /* log option, nil if none */
struct optlst_t *__help_olp;  /* help option, nil if none */
struct optlst_t *__quiet_olp; /* quiet option, nil if none */
struct optlst_t *__verb_olp;  /* verbose option, nil if none */  
struct optlst_t *__verb_mem_olp;  /* verbose mem option, nil if none */  
int32 __vpi_argc;      /* global arg count for vpi */
char **__vpi_argv;     /* global arg array for vpi */
char *__vpi_argv0;     /* argv execed program name */
char *__cur_fnam;      /* being read file name for errors */
int32 __cur_fnam_ind;  /* index in in_fils of cur_fnam */
int32 __sfnam_ind;     /* global file index for current stmt. */
int32 __slin_cnt;      /* global line no. for currently check stmt */
int32 __vpifnam_ind;   /* vpi_ global current file index */
int32 __vpilin_cnt;    /* vpi_ global current line no. */
struct expr_t *__srm_xp; /* current string 'file' for sreadmem */
char *__srm_strp;      /* char. pos. in sreadmem string */
char *__srm_strp_beg;  /* work alloced location for sreadmem string */
int32 __srm_strp_len;  /* alloced length */
int32 __srm_stargi;    /* current string position number */
int32 __in_ifdef_level;/* current processing `ifdef level */ 
int32 __have_t_ignore_elsif[MAXLEVELS]; /* T in else(if), seen a T */
int32 __ifdef_skipping;/* T = skipping not included ifdef section */
int32 __rding_top_level; /* T => reading outside top level construct */

/* variables for batch tracing */
word64 __last_trtime;  /* last trace statement time */
word64 __last_evtrtime;/* last event trace time */
t_midat *__last_tridp; /* last event traced inst. itree index */ 

/* command processing variables and temps */
int32 __pv_err_cnt, __pv_warn_cnt; /* error counts */
int32 __inform_cnt;    /* number of informs */
int32 __outlinpos;     /* current trunc. output line pos. */
long __mem_use;        /* counts allocated mem for debugging */
long __mem_allocated;  /* bytes allocated */
long __mem_freed;      /* bytes freed */
long __memstr_use;     /* counts allocated string mem for debugging */
long __arrvmem_use;    /* allocated bytes for Verilog arrays */
long __mem_udpuse;     /* number of bytes used by udp tables */
word64 __tim_zero;     /* place for time of constant 0 */
int32 __num_glbs;      /* total no. of globals in design */
int32 __num_inmodglbs; /* glbs thar resolve to intra module refs. */
int32 __num_uprel_glbs;/* number of upward relative globals */
int32 __nets_removable;/* flat no. of deletable nets */
int32 __flnets_removable;/* removable static nets */
int32 __gates_removable; /* removable static gates */
int32 __flgates_removable; /* flat no. of deletable gates */
int32 __contas_removable; /* removabale static cont. assigns */
int32 __flcontas_removable; /* flat no. of deletable cont. assigns */

/* special allocate free variables */
struct ncablk_t *__hdr_ncablks; /* blocks used for ncomp recs */
int32 __ncablk_nxti;   /* index of next free pos. */
struct cpblk_t *__hdr_cpblks; /* blocks used for cell recs*/
int32 __cpblk_nxti;    /* index of next free pos. */
struct cppblk_t *__hdr_cppblks; /* blocks used for cell pin recs*/
int32 __cppblk_nxti;   /* index of next free pos. */
struct tnblk_t *__hdr_tnblks;  /* blocks of symb table tree nodes */
int32 __tnblk_nxti;    /* index of next free pos. */ 
struct cpnblk_t *__hdr_cpnblks;  /* blocks of explicit cell pnames */

/* source processing variables */
int32 __lin_cnt;       /* line number while reading a file */
int32 __saverr_cnt;    /* counter to inhibit more than a err in xpr */
int32 __max_errors;    /* maximum errors before stopping */
int32 __rding_comment; /* flag so comment non printable chars ok */
int32 __total_rd_lines;/* total number of lines read */

/* SV source reading and fixup variables */

/* new P1364-2005 generate processing variables */ 
int32 __dsgn_uses_generate; /* T => some use of generate in design */
int32 __in_gen_region; /* T => processing generate mod item */
int32 __gen_fnam_ind;  /* location of most recent generate */
int32 __gen_lin_cnt;   /* location of most recent generate */
int32 __in_gen_for;    /* T => no task/func decl in gen for */
int32 __mod_gen_id;    /* need unique per mod id num for each gen */
struct genitem_t *__last_gip;/* end of cur mod gen item list */
void *__save_last_mitem; /* ptr for remove mod items end of list */
struct genblk_t *__cur_cntxt_gblk;/* if rd src in gen blk, the cur blk */
struct gen_sens_t *__gen_sens_hd; /* hd of gen param sensivity list */
struct gen_sens_t *__gen_sens_tail; /* and tail of same list */
struct genitem_t *__gitems_hd; /* list of non meta gen items in mod */
struct genitem_t *__gitems_tail; 
struct genitem_t *__gref_gitems_hd; /* lst of xmr gen items (sep list) */
struct genitem_t *__gref_gitems_tail; 
struct genitem_t *__dfp_gitems_hd; /* lst of dfp gen items (sep list) */
struct genitem_t *__dfp_gitems_tail; 
char __wrk_gi_nam[RECLEN]; /* gbl wrk string for saving gen item nam */
int32 __fixup_round;   /* counter for fixup nl repeat for generates */ 
int32 __all_topm_gen_xpnd; /* T - all top modules gen expanded */
int32 __forblk_index; /* foreach/for(int local block index counter */

/* booleans for program options (flags) */
int32 __verbose;       /* T => emit various extra messages */
int32 __quiet_msgs;    /* T => do not emit msgs just errors */
int32 __no_warns;      /* T => don't print warning msgs */
int32 __no_errs;       /* T => don't print error msgs */
int32 __no_informs;    /* T => don't print inform msgs (dflt) */
int32 __debug_flg;     /* T => turn on debugging output */
int32 __opt_debug_flg; /* T => turn on vm compiler debugging output */
int32 __missing_nchg_trace; /* undocumented tracing of late nchg add */
int32 __opt_prt_stats; /* T => print cvc bblk and m insn stats */
int32 __st_tracing;    /* T => trace statement execution */
int32 __ev_tracing;    /* T => trace event schedules and processes */
int32 __pth_tracing;   /* T => trace path delays in detail */
int32 __dump_arrays;   /* T => dump array values (vcd,fst,fsdb) */
int32 __dump_array_cells; /* T => dump array values per element */
int32 __verbose_mem;     /* T => verbose memory cvc usage */ 
int32 __opt_block_trace; /* T => block tracing for compiler */
int32 __opt_valtrk;      /* T => turn on value tracking optimizing */
int32 __opt_trk_verbose; /* T => value tracking verbose msgs printed */
int32 __opt_emit_var_names;/* T => for debug, emit var name if short */
int32 __use_pwd_as_tmp;   /* T => use pwd as the work space directory */ 
char * __usedir_cp;        /* use named dir as the work space dir */ 
int32 __real_warns;            /* turn on sim time NaN real warns */
int32 __prt_stats;     /* T => print design statics tables */
int32 __prt_allstats;  /* T => print design and mod content tabs */
int32 __show_cancel_e; /* T => chg val to x on pulse cancelled event */
int32 __showe_onevent; /* T => if showing cancel e, drive x on event */
int32 __warn_cancel_e; /* T => emit warn cancel_e (indep. of cancel) */
int32 __mipd_cycle_pnd0_schd; /* T => MIPD del chg on nchg - pnd0 sched */
int32 __rm_gate_pnd0s; /* T => remove #0 from all gates */
int32 __rm_path_pnd0s; /* T => (default) remove all 0 delay paths */
int32 __dmpvars_all;   /* T => dumpvars all variables */
int32 __has_dmpv_sys_calls; /* T => design as dumpvar sys calls */

/* dumpport globals */
int32 __has_dumpports_sys_calls; /* T => design as dumpport sys calls */
word64 __dp_calltime;  /* time dump ports first (and only) called */
int32 __dp_seen;       /* glb flag to insure dp all at same tick */
struct dp_fildesc_t *__dp_fildesc_tab; /* table of dumpports open files */
int32 __dp_fildesc_nxti; /* next free open file slot */

int32 __is_fst;   /* T => is FST dumping on */
int32 __fst_repack; /* T => do FST repacking on close */
int32 __fst_parallel; /* T => do FST using multiple threads */
int32 __fst_parallel2; /* T => do FST multiple threads with buffering */
void *__fst_ctx;  /* FST format handle */
int32 __fst_max_work_area; /* max number of bytes for work area */
byte *__fst_work_area; /* work area to do the conversions */
int32 __fst_convert_dump2fst; /* T => convert $dump calls to $fst */
byte *__fst_work_svec; /* work area to do stren conversions */
int32 __fst_next_idcode; /* count the number of nets dumping */

/* command option booleans */
int32 __lib_verbose;   /* T => emit src.file/lib source messages */
int32 __sdf_verbose;   /* T => emit msgs for SDF annotated delays */
int32 __tgl_verbose;   /* T => emit tgldat non match warning msgs */
int32 __ignore_sdf_iopath_edges; /* T => ignore io path edges to match MS */
int32 __switch_verbose;/* T => emit msgs for switch/tran chan build */
int32 __no_vec_bid_tran_channels; /* T => leave bid switch chans scalared */ 
int32 __chg_portdir;   /* T => chg port dir to bid. for XL compat */
int32 __sched_always_blocks_first; /* T init all alw before init */
int32 __decompile;     /* T => decompile and print Verilog source */
int32 __repl_gen_dot_uline;/* T => decompile with gen dots as '_' */ 
int32 __repl_gen_dot_esc;/* T => decompile with gen dots escaped */ 
int32 __compile_only;  /* T => check syntax (inc. lib.) no quads */
int32 __parse_only;    /* T => first pass parse only to chk sep mod */
int32 __dflt_ntyp;     /* Verilog wire type for normal nets */
int32 __dflt_ntyp_is_none;  /* '`defaul_nettype none' - no implicit */
int32 __mintypmax_sel; /* for (e:e:e) expressions value to use */
int32 __sdf_mintypmax_sel; /* min:nom_max over-ride for $sdf_annotate */
int32 __gateeater_on;  /* T => attempt to remove (disconnect) gates */ 
int32 __no_expand;     /* T => make all wire vectors vectored */
int32 __in_cell_region;/* T => turn on cell bit for every module */
int32 __unconn_drive;  /* if none TOK_NONE else PULL 0 or PULL 1 */
int32 __no_specify;    /* T => check but no simulate with specify */
int32 __no_tchks;      /* T => check but no simulate with tim chks */
int32 __lib_are_cells; /* T => if in lib, the mark as cell (dflt.) */
int32 __design_has_cells;/* T => cells somewhere in design */
int32 __accelerate;    /* T => use short circuits g/prt code if can */
int32 __pli_keep_src;  /* T => keep more source stmt info for pli */
int32 __use_impthdels; /* T => use src-dst im path dels */
int32 __old_vpi_obj_after_iter_free_only; /* old vpi in iter free */

/* source input variables and temps */
char __lasttoken[IDLEN];/* current last pushed back symbol name */
char __token[IDLEN];   /* current symbol (in canonical (lc) form) */
int32 __toktyp;        /* place for current toktyp value */
int32 __lasttoktyp;    /* push back token type (= UNDEF if none) */
int32 __last_attr_prefix;/* push back pending attr prefix state */
int32 __itoklen;       /* current number token bit length */
int32 __itoksized;     /* T => token is sized */
int32 __itokbase;      /* base constant for number token */
int32 __itoksizdflt;   /* '[base] form with width (uses dflt.) */
int32 __itok_signed;   /* T => token is signed number */
int32 __itok_sv_unbas_unsiz;   /* T => token is SV '0 number */
double __itok_realval; /* actual scannoer double val */
char *__strtoken;      /* growable token to hold string */
int32 __strtok_wid;    /* current size of string token */    
char *__numtoken;      /* growable token to hold numbers */
int32 __numtok_wid;    /* current size of number token */    
int32 __letendnum_state; /* T => letter can end unsized num. */
int32 __macro_sep_width; /* T => possible beginning of macro 2 tok num */
int32 __maybe_2tok_sized_num; /* T => seeing number after macro num */
int32 __macro_sav_nwid;/* value of saved first tok width */
int32 __first_linetok; /* T => token first on line */
int32 __file_just_op;  /* T => new file and no token yet returned */
int32 __first_num_eol; /* T => first tok because number ended line */
char *__macwrkstr;     /* work string for macros */ 
int32 __mac_line_len;  /* actual length of macro line in wrk str */   
int32 __macwrklen;     /* allocated len of mac. work string */
struct macarg_t *__macarg_hdr; /* hdr of list of format mac. args */
int32 __macbs_flag;    /* T=> 8'h`DEFINE catch multiple bases errors */
char *__attrwrkstr;    /* work string for attributes */
int32 __attr_line_len; /* actual length of attribute string */ 
int32 __attrwrklen;    /* alloced len of attr work string - grows */
char *__attrparsestr;  /* string to parse attr out of */
int32 __attrparsestrlen; /* string to parse attr out of */
int32 __attr_prefix;   /* T => token has attribute prefix */
int32 __attr_fnam_ind; /* location of attr inst. */
int32 __attr_lin_cnt;  /* location of attr inst. */
struct attr_t __wrk_attr; /* latest read attribute */
char *__xs, *__xs2;    /* places to put expr to str trunc messages */
int32 __pv_ctv;        /* tmp for white space skipping macros */
int32 __syncto_class;  /* token class sync skipping halted at */
char *__exprline;      /* expr. output line work string */
int32 __exprlinelen;   /* expr. line length */
int32 __cur_sofs;      /* ndx of next ofs (position) in expr line */
word32 *__acwrk;       /* a value work string for scanning number */
word32 *__bcwrk;       /* b value work string for scanning number */
word32 __addrtmp[2];   /* up to 32 bit temp with addr. */
word32 *__addr_2state_zero; /* 2-state empty bpart */
int32  __max_net_blen; /* maximum declared net size */
int32 __abwrkwlen;     /* current acwrk a half length in words */
char __portnam[IDLEN];
char __pv_varnam[IDLEN]; /* variable name */
int32 __expr_is_lval;  /* T => parsing proc. assign lhs */
int32 __allow_scope_var; /* T => process systask arg can be scope */
int32 __allow_scope_lsb; /* T => process systask arg be XMR lsb */
int32 __rd_auto_task;    /* T => is reading automatic task */
int32 __rd_loop;         /* T => is reading a loop */
int32 __rd_continue;     /* T => read 'continue' */
int32 __rd_break;        /* T => read 'break' */
int32 __rd_always_ff;    /* T => read always_ff */
struct st_t *__st_loop_continue; /* prep loop continue statement */
struct st_t *__st_loop_break;    /* prep loop break statement */

/* toggle processing work variables */
char *__tglbits01;       /* for init from .tgldat file 01 list */
char *__tglbits10;       /* 10 list */
int32 __siz_tgl_lst;     /* current alloc size of list */
char *__tgl_modnam;      /* name of module for tgl net line */
char *__tgl_rtpthnam;    /* for init from .tgldat line rooted path */ 
int32 __siz_tgl_rtpthnam;/* and alloc size */
int32 *__tgl01tab;       /* int (0/1 for now) tab of 0->1 toggle cnt */
int32 *__tgl10tab;       /* and 1->0 tab */ 
int32 __siz_tgltabs;     /* alloc size of tgl cnt tabs */
int32 __tgl_r1;          /* first tgldat line range */
int32 __tgl_r2;          /* 2nd tgldat line range */
int32 __se_reset_to_untgled; /* T => slot end set recorded nets untgl */

#ifdef __XPROP__
int32 __xprop_copying;   /* T => copying x propagation stmt block */
struct net_t **__xprop_lhs_nets; /* lhs net prep building */
int32 *__xprop_lhs_other_than_id;  /* lhs net id only */
struct st_t **__xprop_stmts;        /* lhs stmt prep building */
int32 __xprop_net_ndx;              /* lhs net ndx */
struct net_t **__xprop_lhs_nets_top; /* top lhs net prep building */
int32 *__xprop_lhs_other_than_id_top;      /* top lhs net id only */
struct st_t **__xprop_stmts_top;     /* top lhs stmt prep building */
int32 __xprop_net_ndx_top;         /* top lhs net ndx */
struct xprop_t *__current_xprop;   /* last xprop struct */
word32 *__xprop_max_net_1_wp;        /* max width 1 wp */
int32 __xprop_max_net_width;         /* max xprop net width */
struct st_list_t *__added_xprop_stlst_hdr; /* alloc xprop stmt hdr */
struct st_list_t *__added_xprop_stlst_tail; /* alloc xprop stmt tail */
int32 __xprop_xedge;             /* T => xedge global */
int32 __xprop_expr_has_cneq; /* expr mark has === or !=== */
FILE *__xprop_trace_fp;          /* xprop trace info file */
int32 __xprop_trace_on;          /* xprop tracing on */
int32 __xprop_xtrace_suppress;   /* T => do not emit trace message */
FILE *__xprop_not_eligible_fp;   /* xprop not eligible stmt file */
int32 __xprop_not_eligible;      /* xprop not eligible stmts on */
int32 __xprop_cond_hit;          /* x conditions hit */
int32 __xprop_cond_max;          /* max hit before stopping log */
#endif

/* vars needed for pushing back numbers (see var. comment) */
int32 __lastitokbase;
int32 __lastitoksized;
int32 __lastitoksizdflt;
int32 __lastitok_signed;
int32 __lastitok_sv_unbas_unsiz;  
int32 __lastitoklen;
word32 *__lastacwrk;   /* special malloced push back num value */
word32 *__lastbcwrk; 
double __lastitok_realval;

/* the module and module subtask specific work variables */
struct mod_t *__oinst_mod;/* ptr. to old current module for copying */
struct mod_t *__end_mdp; /* end of module def. list */
struct cell_t *__end_cp; /* end of module inst. list */
int32 __cp_num;          /* counter for unnamed gate/inst pos. */ 
struct conta_t *__end_ca; /* end of module conta list */
int32 __conta_num;     /* counter for building symbol for conta */
struct varinitlst_t *__end_mod_varinitlst; /* end of mod var inits */
struct symtab_t *__tfcall_wrksytp;/* wrk tf tab for undecl xmr uprel */  

struct dfparam_t *__end_dfp;/* module current end of defparam list */
struct task_pin_t *__end_tpp; /* end of task port list */
struct task_t *__end_tbp;/* end of top level task/functions/blocks */
struct task_t *__cur_tsk;/* ptr. to current task */
struct net_t *__end_loc_paramnp; /* end of ordered parm loc decl. list */
struct net_t *__end_paramnp; /* end of ordered parm decl. list */
struct net_t *__end_impparamnp; /* end of ordered imprt parm decl lst */
struct net_t *__end_glbparamnp; /* end of ordered glb parm decl. lst */
struct net_t *__end_tskparamnp; /* end of task param decl. list */
struct net_t *__end_tsk_loc_paramnp; /* end of task param decl. list */
struct ialst_t *__end_ialst; /* end of module initial/always list */
struct gref_t *__grwrktab;  /* work table for building mod glbs */
int32 __grwrktabsiz;        /* its size */
int32 __grwrknum;      /* current number of glbs in work table */ 
struct gref_t *__dfp_grwrktab;  /* wrk tab for building mod dfp glbs */
int32 __dfp_grwrktabsiz;        /* its size */
int32 __dfp_grwrknum;           /* current num of glbs in table */ 

int32 __cur_declobj;   /* token type of declared mod or task */
int32 __pv_stlevel;    /* tmp. for current stmt nesting level */
int32 __design_no_strens;/* T => no strengths used in design */
int32 __strenprop_chg; /* during propagate pass at least one chged */
int32 __splitting;     /* T => in process of splitting module */
int32 __confunc_copying; /* T => expr copy is conf func copy */
int32 __genblk_copying; /* T => expr copy is gen blk copy */
int32 __gentsk_copying; /* T => copying gen tsk, complex special case */
int32 __processing_pnd0s;/* T => in time unit, in end #0 region */
struct dce_expr_t *__cur_dce_expr; /* glb for edge events eval expr */
int32 __lofp_port_decls; /* T => exclusive hdr port decls appeared */ 
struct exprlst_t *__impl_evlst_hd; /* hdr of impl @(*) ev expr list */
struct exprlst_t *__impl_evlst_tail; /* and its tail */
int32 __canbe_impl_evctrl; /* glb switch to allow @(*) as ev ctrl */

/* variables for dumpvars */
int32 __dv_seen;       /* dumpvars seen but not yet setup */
int32 __dv_state;      /* processing state of dumpvars */
word64 __dv_calltime;  /* time dump var. first (and only) called */
int32 __dv_dumplimit_size; /* user set limit of dv file size (0 none) */
int32 __dv_file_size;  /* current size of dumpvars file */
int32 __dv_time_emitted; /* flag to stop repeated same #[time] */
char *__dv_fnam;       /* name of dumpvars output file */
int32 __dv_func;       /* global set with type of dumpvar dumping */
struct mdvmast_t *__dv_hdr; /* hdr of mast dumpvar rec. list */
struct mdvmast_t *__dv_end; /* end of dumpvar rec. list */
int32 __dv_fd;         /* file number of dmpvars fd */
char *__dv_buffer;     /* buffer to speed up dumpvars output */
int32 __dv_nxti;       /* next free location */
int32 __dv_outlinpos;  /* line postion in dump vars file */ 
int32 __next_dvnum;    /* highest so far used dumpvars number */
struct dvchgnets_t *__dv_chgnethdr;  /* curr. time var chg list hdr */
int32 __dv_isall_form; /* T doing all of design dumpvar setup */
int32 __dv_allform_insrc;/* T dumpvars all form in source */
/* AIV 04/19/12 - variables for parallel dumping */
pthread_mutex_t __dump_mutex;    /* dump mutex */
pthread_cond_t __buffer_empty;   /* buffer is empty */
pthread_attr_t __thread_attr; /* thread attributes */
pthread_t __dump_thread;      /* dumping thread */
struct dmp_buf_t *__dump_buffer; /* dump buffer */
int32 __dump_buffer_size;        /* size of dump buffer */
int32 __write_ndx;               /* current write of dump buffer */
int32 __dump_next_ndx;           /* next index */

struct rt_tgl_t *__toggle_chghdr;  /* rt toggle change header list */
int32 __tgl_record_on;             /* tgl record (add to lst) now on */
char *__toggle_coverage_file_name; /* name of coverage file */
int32 __toggle_coverage;           /* T => turn on tgl cover record */

/* old style toggle coverage variables */
int32 __old_toggle_rpt_instance;   /* T => old report per instance */
int32 __old_toggle_rpt_bits;       /* T => old style report per bit */
int32 __old_toggle_rpt_uncovered;  /* T => old style rpt uncoverd bits */
int32 __old_toggle_rpt_covered;    /* T => old style rpt covered bits */

int32 __wr_tgldat_on;              /* at end, write .tgldat file */
char *__wr_tgldat_file;            /* name of .tgldat output file */
struct tgldat_in_lst_t *__tgldat_infils_lst_hd; /* init tgldat hd */
struct tgldat_in_lst_t *__tgldat_infils_lst_end; /* and tail */
char __tgldat_writer_vers[RECLEN]; /* id info from input .tgldat file */
char __tgldat_writer_date[RECLEN]; /* id info from input .tgldat file */

/* new concise style toggle coverage variables - if used ignore old style */
int32 __drvn_const_as_tgled;       /* T => driven const made tgled */
int32 __drvn_const_rpt_concise;    /* T => output rpt drvn const bits */
int32 __untgled_rpt_concise;       /* T => concise untgl rpt only */
int32 __has_tgl_optcfg_stmt;       /* T => optconfigfil tgl stmts used */

char *__event_coverage_file_name; /* name event coverage file */
word32 *__event_covered;          /* marked events array */
int32 __event_coverage;           /* T => report event coverage */

char *__stmt_coverage_file_name; /* name event coverage file */
word32 *__stmt_covered;          /* marked stmts array */
int32 __stmt_coverage;           /* T => report stmt coverage */
int32 __stmt_coverage_tasks;     /* T => report tasks stmt coverage */
FILE *__force_dmp_fp;            /* when set for dmp_stmt to file */

/* time scale - precision variables */
word32 __cur_units;    /* current units (0 (1s) - 15 (1ft) */ 
word32 __cur_prec;     /* current digits of precision (0-15) */
word32 __des_timeprec; /* assume -, 0-15 design sim. tick prec. */
word32 __tfmt_units;   /* %t output units (also interact. units) */
word32 __tfmt_precunits;/* %t number of prec. digits */
int32 __des_has_timescales;/* T => design has at least one timescale */
char *__tfmt_suf;      /* suffix for %t */
int32 __tfmt_minfwid;  /* minimum field width for %t */
word64 __itoticks_tab[16];/* table of scales amount from prec. */
char __timstr_unitsuf[4];/* to_timstr units suffix if needed */
word64 __timstr_mult;  /* multiplier if needed */
int32  __nd_timstr_suf;/* T => need to_timstr units */

/* veriusertfs pli user function and task work variables */ 
/* SJM 07/16/02 - need internal veriuser tfs for new +loadpli1 option */
struct t_tfcell *__shadow_veriusertfs; /* internal copy of table */
int32 __last_veriusertf; /* last user veriusertfs tf number */
struct tfinst_t *__tfinst;/* current tf_ inst loc. */
struct tfrec_t *__tfrec;/* current tf_ record */ 
struct dceauxlst_t *__pvc_dcehdr; /* header of current pvc dces */
struct tfrec_t *__tfrec_hdr; /* header of design wide tfrec list */ 
struct tfrec_t *__tfrec_end; /* last el of design wide tfrec list */ 
struct tev_t *__tehdr_rosyncp; /* hdr ndx of slot end ro sync ev lst */ 
struct tev_t *__teend_rosyncp; /* end of slot end ro sync ev lst */ 
int32 __now_resetting; /* reset in progress - for cbs and misctf */  
int32 __rosync_slot;   /* T => processing tf or vpi  ro synch events */
struct loadpli_t *__pli1_dynlib_hd; /* hd of ld pli1 dynamic lb list */
struct loadpli_t *__pli1_dynlib_end; /* and its end */

/* vpi_ work variables */
int32 __last_systf;    /* last vpi_ registered sytfs number */
int32 __num_vpi_force_cbs; /* number of registered vpi force cbs */
int32 __vpi_force_cb_always; /* T => always call back on force */
int32 __num_vpi_rel_cbs; /* number of registered vpi rel cbs */
int32 __vpi_rel_cb_always; /* T => always call back on release */
int32 __allforce_cbs_off; /* T => can't reenter any of all force cbs */
int32 __allrel_cbs_off;/* T => can't reenter any of all release cbs */
char *__wrks1;         /* work string - can not use xs if func */
char *__wrks2;
char __wrk_vpiemsg[IDLEN];/* error msg. work string */
char __wrk_vpiget_str[IDLEN];/* standard required vpi get str string */
char __wrk_vpi_product[256];/* product version */
char __wrk_vpi_errcode[256];/* error codes are Cver err num as str */
double __wrk_vpi_timedbl;/* time double for vpi error rec */
char *__wrkvalbufp;    /* buf for vpi get value value_p contents */ 
int32 __wrkval_buflen; /* and current length */
int32 __vpi_vlog_start_done;/* T => startup done, no systf registering */
struct systftab_t *__systftab; /* table of vpi_ systf records */
int32 __size_systftab; /* current size of systf data rec. table */
struct xstk_t *__cur_sysf_xsp; /* tmp stk_t for vpi sysf ret val */
struct expr_t *__cur_sysf_expr;/* tmp calling expr. for vpi sysf*/
struct st_t *__cur_syst_stp; /* tmp stmt for vpi syst*/
struct dceauxlst_t *__cbvc_dcehdr; /* header of current vc cb dces */
struct rfcblst_t *__rel_allcb_hdr;
struct rfcblst_t *__rel_allcb_end;
struct rfcblst_t *__force_allcb_hdr;
struct rfcblst_t *__force_allcb_end;
struct tev_t **__vpicb_tehdri; /* hdr of fixed cb tev list - 1 per class */
struct tev_t **__vpicb_teendi; /* end of fixed cb tev list - 1 per class */
int32 __have_vpi_actions;/* some use of __vpi actions */
int32 __have_vpi_gateout_cbs;/* some use of gate out term cbs */
struct h_t *__vpi_hfree_hdr;  /* handle free list hdr */ 
struct hrec_t *__vpi_hrecfree_hdr;  /* handle record free list hdr */ 
struct cbrec_t *__vpi_cbrec_hdr; /* all cbs list header */
int32 __ithtsiz;       /* size of global work ld/drv handle table */
struct h_t **__ithptab; /* and the work ld/drv handle ptr table */
int32 __ithtsiz2;      /* size of global work ld/drv handle table */
struct h_t **__ithptab2; /* 2nd work for ptrs to in subtree handles */
struct vpisystf_t *__vpi_sysf_hdr; /* hdr sys func call src locs */
struct vpisystf_t *__vpi_syst_hdr; /* hdr sys task enable src locs */
int32 __in_vpi_errorcb;/* T => if sim ctrl, suppress error msg error */
int32 __vpierr_cb_active; /* T => at least one cbError reged */
int32 __acc_vpi_erroff;/* acc_ flag to stop internal acc_ error cbs */
int32 __errorcb_suppress_msg; /* T => sim control suppress error msg */
struct h_t *__cur_vpi_inst;
struct hrec_t *__cur_vpi_obj;
struct loadpli_t *__vpi_dynlib_hd; /* hd of ld vpi dynamic lib list */
struct loadpli_t *__vpi_dynlib_end; /* and its end */
struct dcevnt_t *__cbvc_causing_dcep; /* glb for vc cb if it is remed */

/* specify work variables */
struct spfy_t *__cur_spfy;/* current specify block */
struct spcpth_t *__end_spcpths; /* end of specify path st. list */
int32 __path_num;      /* counter for unnamed paths */
struct tchk_t *__end_tchks;/* end of specify time check st. list */
struct net_t *__end_msprms;/* end of specify specparam net list */
struct tchk_t *__cur_tchk;
int32 __tchk_num;      /* counter for unnamed paths */
struct symtab_t *__sav_spsytp;/* save loc. of sym tab in spfy sect. */

/* work compile global variables accessed by routines */
int32 __v1stren;       /* wire/inst. Ver. 1 strength */
int32 __v0stren;       /* wire/inst. Ver. 0 strength */
word32 __pr_iodir;     /* glb. for port ref. expr. I/O direction */
int32 __pr_wid;        /* global for total port ref. expr. width */
int32 __mpref_explicit;/* T => mod def header port ref explicit */
int32 __sym_is_new;    /* set when new symbol added */
struct sy_t **__wrkstab;/* malloced work symbol table area */
int32 __last_sy;       /* last symbol in work area */
struct sy_t **__wrkstab2;/* malloced 2nd work symbol table area */
int32 __last_sy2;      /* last symbol in work area */
int32 __mod_specparams;/* number of declared specparams in mod */
int32 __name_assigned_to;/* glb set if func. def. name assigned to */
struct sy_t *__locfnamsyp; /* place for func. def. chk func. symbol */
int32 __processing_func; /* T => prep or exec of function occuring */
struct st_t **__nbstk; /* func. nest nblock stack (nxt for exec) */
int32 __nbsti;      
struct sy_t *__ca1bit_syp; /* gmsym for 1 bit conta converted gate */
int32 __chking_conta;  /* T => checking a continuous assignment */
int32 __rhs_isgetpat;  /* T => flag for checking stylized getpat */
int32 __lhs_changed;   /* T => assignment changed lhs */
word32 __badind_a;     /* place for a part of in error index value */
word32 __badind_b;     /* and for b part */
int32 __badind_wid;    /* width for bad ind (<32 expr can eval to x) */
int32 __expr_has_real; /* T => know some real in expr. */
int32 __expr_has_sv_string; /* T => know some SV string in expr. */
int32 __isform_bi_xvi; /* glbl for IS net pin bit index in contab */
int32 __lhsxpr_has_ndel; /* T => component wire of lhs has wire del */
int32 __checking_only; /* T => no error msg, looking for something */ 
int32 __task_has_tskcall;/* T => task calls other task (not name blk) */
int32 __task_has_xmrcall;/* T => task has no reachable xmr task */
int32 __task_has_disable;/* T => task call has disable needs thread */
int32 __task_has_delay;/* T => task call has del. needs thread */
int32 __disp_uses_scope;/* T => $display fam of functions uses %m */
int32 __ia_has_vpicall;/* init/alwasy has a vpi call - needs thread */
int32 __func_has_fcall;/* T => func contains has non sys fcall */
int32 __iact_must_sched; /* T => iact stmt(s) have $stop or loop */
int32 __expr_rhs_decl; /* T current expr. is decl. not proc. rhs */ 
int32 __chg_rng_direct;/* T => change rng dir. for implicitly decl */
int32 __has_top_mtm;   /* T => for parameter rhs non () m:t:m */
int32 __nd_0width_catel_remove; /* fx3 file 0 width concat glb */
struct gref_t * __wire_array_grp; /* gref use to convert wire arrays */

/* current Verilog module/task/block symbol environment */
struct symtab_t **__venviron;
int32 __top_sti;
struct symtab_t *__modsyms;/* separate symbol table for type names */
struct symtab_t *__pv_defsyms;/* global table for `defines */
struct symtab_t *__syssyms;/* global tab for system tasks and funcs */
struct sy_t **__glbsycmps; /* work global name symbols */
struct expr_t **__glbxcmps;/* work glbal exprs */
int32 __last_gsc;

/* n.l. access headers and tables */
struct mod_t *__modhdr;/* header of top level module list */
struct udp_t *__udphead; /* header udps */
struct udp_t *__udp_last;/* end udp list */
struct inst_t **__top_itab; /* tab of virt inst ptrs of top mods */
int32 *__top_ipind;    /* binary searchable top insts index */
int32 __numtopm;       /* number of uninstanciated top modules */

struct mod_t **__dsgn_mod_ndx; /* dsgn per mod ndx number index array */
int32 __dsgn_num_mods; /* num of module in modhdr list for ndxing */
struct udp_t **__dsgn_udp_ndx; /* dsgn all udp tab index array */
int32 __dsgn_num_udps; /* num of upds in udp list */ 

struct itree_t **__it_roots; /* table of root itree entries */
int32 __ualtrepipnum;  /* udp rep. change threshold */
struct thread_t *__initalw_thrd_hdr; /* list hd of per inst in/al thds */
struct tev_t *__tevtab;/* reallocable tab of events and free evs */
int32 __numused_tevtab;/* num used at least once in tev tab */
int32 __size_tevtab;   /* num tev's allocated in tev tab */ 
word32 *__contab;      /* design wide constant table */
int32 __contabwsiz;    /* currrent size of const tab in words */
int32 __contabwi;      /* next free word32 slot in const tab */
int32 __opempty_contabi; /* special contab ndx for opempty expr leaf */
struct contab_info_t **__contab_hash; /* contab hash information */

/* n.l. access routines */  
struct dfparam_t *__dfphdr; /* design wide defparam list header */
int32 __num_dfps;      /* number of defparams in source */
int32 __num_glbdfps;   /* number of defparams in design */
int32 __num_locdfps;   /* number of local defparams */
int32 __num_inst_pndparams;/* static number of inst. pound params */
int32 __design_gia_pndparams;/* T => at least one gia range pnd params */
int32 __design_gi_arrays;  /* T => design has arrays of g/i */ 
int32 __pndparam_splits; /* T => at least one split from pound params */
int32 __defparam_splits; /* T => at least one split from def params */
int32 __dagmaxdist;    /* max. nested mod. inst. level */
struct mod_t **__mdlevhdr; /* array of ptrs to ith lev linked mods */ 
struct cell_pin_t *__cphdr;   /* header of temp. cell pin list */
struct cell_pin_t *__cpp_last;/* current last cell pin*/
struct tnode_t *__tmp_head;

struct xldlnpp_t *__xldl_hdr; /* other side unproc. xl drv/ld npps */
struct xldlnpp_t *__last_xldl;/* end of list - place to add after */
struct xldlvtx_t **__xldlvtxind; /* table of xl drv/ld net/bit vtx */
int32 __num_xldlvtxs;  /* number of lements in table */
int32 __siz_xldlvtxtab;/* current size of table */

/* udp table building variables */
struct wcard_t *__wcardtab; /* level wildcard table */
int32 __last_wci;      /* last wild card index for line */
word32 *__cur_utab;    /* current udp table */
struct utline_t *__cur_utlp; /* current line info struct */
word32 __cur_uoval;    /* current udp line output value */
int32 __cur_unochange; /* T => cur line has '-' no change output */
struct udp_t *__cur_udp; /* current udp struct */
word32 __cur_upstate;  /* current last input (state) for wide */
int32 __cur_ueipnum;   /* cur. input pos. num of edge (NO_VAL none) */
int32 __cur_utabsel;   /* current edge 1st char - 2nd in state line */

/* expression and function processing variables */
int32 __xndi;          /* next place in collected expression list */
struct expr_t **__exprtab;/* table to collect expressions into */
struct expridtab_t **__expr_idtab; /* expr parse id name info */ 
int32 __exprtabsiz;    /* current operator precedence expr tab siz */
int32 __last_xtk;
struct expr_t *__root_ndp;/* root of built and alloced expression */
struct xstk_t **__xstk;/* expr work vals */
int32 __xspi;          /* expr. pointer */
int32 __maxxnest;      /* current size of expr. stack - must grow */ 
int32 __maxfcnest;     /* size of func. call task stk - must grow */
struct task_t **__fcstk; /* function call nesting stack */
int32 __fcspi;           /* fcall tos index */
int32 __lhs_has_4state;  /* T=> lhs has 4-state values */ 
int32 __rhs_has_4state;  /* T=> rhs has 4-state values */ 
int32 __rding_defparam;  /* T=> parsing dfp stmt - for dfp gref tab */

/* -y and -v library variables */
struct vylib_t *__vyhdr; /* header of lib. file list */
struct vylib_t *__end_vy;/* last entry on vy lib. list */
int32 __num_ylibs;     /* number of ylibs in options */
int32 __num_vlibs;     /* number of vlibs in options */

struct undef_t *__undefhd;/* head of undefined mod/udp list */   
struct undef_t *__undeftail; /* tail of undefined mod/udp list */
int32 __undef_mods;    /* count of undefined modules */

int32 __lib_rescan;    /* T => rescan from start after each */
int32 __cur_passres;   /* num mods resolved in current pass */
int32 __rescanning_lib;/* T => for `language exclude after 1st pass */ 
int32 __num_ys;        /* number of -y options in lib. */
char **__lbexts;       /* tab of -y library extension suffixes */
int32 __last_lbx;
char **__incdirs;      /* tab of +incdir paths (always / end) */
int32 __last_incdir;
int32 __leaf_modules_already_merged; /* leaf modules already merged */

/* simulation preparation variables */
int32 __cur_npii;      /* current index of inst. in cur. mod */
struct gate_t *__cur_npgp;/* current net-pin processing gate */
struct mod_t *__cur_npmdp;/* current net-pin processing module */
struct conta_t *__cur_npcap; /* current net pin proc. conta */
struct tfrec_t *__cur_nptfrp; /* current net pin tf arg drvr rec */
struct net_t *__cur_npnp; /* current net pin net for vpi putv driver */
int32 __cur_npnum;     /* current port number (from 0) */
int32 __cur_pbi;       /* current bit number for PB ICONN npp */
int32 num_optim_cats;  /* number of optimized concats */
int32 num_optim_catels;/* number of all elements in optim concats */
int32 __cur_lhscati1;  /* if lhs concat, high rhs psel index */
int32 __cur_lhscati2;  /* if lhs concat, low rhs psel index */
struct st_t **__prpstk;/* during prep., continue stp */
int32 __prpsti;        /* top of nested stmt. stack */
int32 __nd_parmpnp_free; /* T => after 1st parmnpp need copy not orig */
int32 __num_rem_gate_pnd0s; /* number of removed source #0 gates */
int32 __num_flat_rem_gate_pnd0s; /* and flat number */
int32 __num_rem_mipds; /* number of per bit flat MIPDs 0 delays rmed */
int32 __last_modsti;   /* and counter for statements */
int32 __compiled_sim;  /* generate asm, compile and dl link */
#ifndef __CVC32__
int32 __cvc_use_large_model;   /* large model needs to be used */
#endif
struct st_t **__prp_mstmt_ndx;/* during prep tmp stmt tab for idp add */
int32 __last_mstndx;   /* last used prep tmp stmt tab index */
int32 __size_prp_mstmts;/* alloc size of tmp prp mstmt tab */
int32 __dump_flowg;    /* dump flow graph for debugging */
int32 __optimize_level;/* for cvc, optimize leve (now only 2?) */
char  *__exe_name;   /* name of already compiled .so library */
int32  __show_asm;     /* show assmebly files */     
int32 __use_interp_dpi_mk; /* T => for dbg, interp dpi use mk file */
char  *__objdir_path;  /* path to object dir to get compiled .so */
int32 __asm_emit_loc;  /* val controls asm out printed location info */
int32 __pli_access_level;    /* hold pli access value */
int32 __inline_code;   /* inline generated code */
int32 __opt_reg_alloc; /* optimize reg allocation */
int32 __opt_two_state; /* use two state optimization */
int32 __opt_two_state_no_wires; /* 2-state does not include wires */
int32 __my_popen;      /* use special faster piping */
#ifdef __XPROP__
int32 __xprop;           /* T => x propagation  */
int32 __xprop2;          /* T => x2 propagation  */
int32 __xprop_and_or_xs; /* T => preserve xs for |,&, ||, &&  */
int32 __no_xprop_edges;  /* T => do not include always @ edges */
int32 __no_xprop_vectors;  /* T => do not include always @vectored vars */
int32 __xprop_pos_neg_only;  /* T => only include pos/neg edge */
int32 __do_xprop_xedge_vectors;/* T => need to calc xprop vectors */
#endif
int32 __random_init;     /* T => random initialize is on */
int32 __random_init_2state; /* T => random 2state initialize is on */
int32 __sv_parse; /* T => parse system verilog keywords */
/* SJM 02-11-13 - need to trace dl open sb lib finding */ 
int32 __dpi_verbose;  /* T => trace dpi -sv_lib finding checking */
int32 __wr_dpi_c_hdrs; /* T => write DPI c prototype hdrs to file */
int32 __override_change; /* T => do not check for cvcsim changes */
int32 __same_param_must_split;/* T => off inhibit splt same parms */
int32 __opt_nbaopt;    /* ignore the time delay for nb <= # */
int32 __opt_unroll_loops;   /* T => turn on loop unrolling */
int32 __cap_seq_no;    /* counter for conta enter points */
int32 __dctrl_seq_no;  /* counter for merged dlctrl */
int32 __dctrl_depth;   /* design delay ctrl depth - for marking */
int32 __nested_dctrl;  /* has nested delay dctrl */
struct npopt_t *__opt_npptab; /* global array for rm/del of npps */
int32 __siz_opt_npptab;/* current allocated size - just grows */
int32 __total_lds_removed; /* count of total lds merged away */
int32 __total_lds_from_nets; /* count of number of nets with lds del */
long __mem_cvc_use;    /* counts allocated cvc mem after argmnts read */
long *__dsnmemp;       /* ptr for load lib option size validation */
struct avlhd_t *__xpr_dup_tree; /* tree to hold all sysf calls */
struct avlhd_t *__xpr_isnum_tree; /* tree to hold all IS num exprs */
void *__process_wire_ev_enterp; /* enter pointer for wire events */
void *__process_compiled_thrd_ev_enterp; /* enter pointer for thrd ev */
void *__process_trpthdst_ev_enterp; /* enter pointer for tran ev */
void *__process_gatechg_ev_enterp;  /* enter process for gate ev */
void *__process_cancel_ev_enterp;   /* cancel event addresss ptr  */
void *__process_free_ev_enterp; /* done with tev list enterp */
void *__process_free_ev_pnd0_enterp; /* done with tev list ent pnd0 */
void *__process_next_ev_enterp; /* done with cur tev - get next event */
void *__delay_callback_enterp;  /* delay call back event */
void *__process_putpdel_enterp;      /* vpi putdel event */
void *__setdel_call_misctf_enterp;  /* set del pli event */
void *__sync_call_misctf_enterp;    /* sync del pli event */
void *__process_vpi_varputv_enterp; /* vpi putv event */
void *__process_vpidrv_enterp;      /* vpi drv event */
struct tev_t *__free_event_tevp;    /* free event index */
struct tev_t *__free_event_pnd0_tevp;   /* free event pnd0 index */
int32 __nchg_ndx; /* nchg index counter (identifier) */
int32 __ctev_ndx; /* tev index counter (identifier) */
struct nchglst_t **__nchg_freed; /* nchgs freed - available for reuse */
int32 __nchg_free_ndx; /* nchgs freed ndx */
int32 __nchg_free_size;/* nchgs freed array size */
int32 __const_expr_has_isnums; /* flag to control is IS nums constant */
int32 __ludptab_ndx;  /* design wide l udp index (identifier) */
int32 __eudptab_ndx;  /* design wide e udp index (identifier) */
int32 __dc_id_ndx;    /* design wide delay control index */
int32 __stmt_id_ndx;    /* design wide statement index */
int32 __fold_for_value; /* folded for loop index */
int32 __folding_for_loop; /* T => folding for loop */

/* timing queue scheduling variables */
word64 __simtime;      /* current simulaton time (make 64 bits ?) */
word32 __num_execstmts;/* total number of executed statements */
word32 __num_addedexec;/* number of executed added statements */
word32 __num_proc_tevents;/* total num simulation events processed */
word32 __nxtstmt_freq_update; /* next ev count for xbig freq upd. */ 
word32 __num_cancel_tevents; /* total num sim events processed */
int32 __num_init_events; /* num of initial events */
word32 __inertial_cancels; /* num resched form later inertial del */
word32 __newval_rescheds; /* num rescheduled for same time */
word32 __num_netchges; /* num of processed net change records */
word32 __immed_assigns;/* num immed assign (not scheduled) */ 
word32 __proc_thrd_tevents;/* number of processed thread events */
struct q_hdr_t *__qlist_hdr; /* for $q_ system task q list header */
int32 __num_switch_vtxs_processed; /* total num tranif chan vtx done */
int32 __num_switch_chans; /* total num tranif channels in design */ 
int32 __num_inout_chans; /* total num inout switch chans design */ 

/* storage tables variables */
size_t __nxt_ofs;       /* next module all nets offset */

/* simulation control and state values */
/* AIV 04/11/12 - this should be word32 - override for 64-bit movq */
word32 __stmt_suspend;  /* set when behavioral code suspends */
int32 __run_state;     /* state of current simulation run */
int32 __can_exec;      /* T => for vpi sim ctrl - can now exec */
int32 __wire_init;     /* T => initializing wires */
int32 __no_tmove_levels; /* T => infinite 0 delay loop warn path dist */
struct thread_t *__cur_thd;  /* currently executing thread addr. */
struct thread_t *__suspended_thd; /* cur thread before suspend */
struct thread_t *__thd_freelst; /* free list of threads */
t_midat *__suspended_idp; /* cur inst ptr before suspend */
struct itree_t *__inst_ptr; /* current if flattened itree place */ 
struct mod_t *__inst_mod;   /* module of current itree inst */
int32 __inum;          /* iti num  of current inst (always set) */
t_midat *__idp;        /* current inst net (for now) data area ptr */
struct itree_t **__itstk; /* stack of saved itrees */
int32 __itspi;         /* top of itree stack */
struct tev_t *__fsusp_tevp;/* in func. step, event to undo(cancel) */
struct itree_t *__tmpitp_freelst; /* free list of wrk itps */
struct inst_t *__tmpip_freelst; /* free list of wrk ips */
struct mod_t *__last_libmdp; /* libary module just read */
int32 __seed;          /* SJM 01/27/04 - glb seed needed if no arg */
int32 __init_seed;     /* init random seed for +random option */

/* execution state variables */
word32 __new_gateval;  /* new gate out val (st. possible) */
word32 __old_gateval;  /* before gate change (st. possible) */
word32 __new_inputval; /* new input value for tracing message */
word32 __old_inputval; /* prev. value of input for wide udp eval */
word64 __pdlatechgtim; /* for path tracing latest path chg time */
word64 __pdmindel;     /* for path minimum path delay */
int32 __nd_neg_del_warn; /* T => must emit warn (or err) for <0 del */ 
int32 __force_active;  /* T => for trace deassign while force */ 
int32 __assign_active; /* T => for trace release activates assgn */
struct dceauxlst_t *__qcaf_dcehdr; /* header of current qcaf dces */
int32 __nxt_chan_id;   /* cnter and size for assigning chan ids */
int32 __num_repl_scal_chans;/* number of replaced scalar channels */
size_t __chanallocsize; /* size of allocated chan tables */
struct chanrec_t *__chantab;/* tab of channel records (one per id) */
int32 *__sort_chan_ndx;/* for bid comb, selected/sorted chantab ndx */
int32 __nxt_maybe_vec; /* and ndx of next to fill */
struct vtxlst_t *__stvtxtab[8]; /* per stren value vertex list */ 
struct vtxlst_t *__stvtxtabend[8]; /* and ptr to last el on each */
struct vtxlst_t *__chg_vtxlst_hdr; /* list of chged vertices to store */
struct vtxlst_t *__chg_vtxlst_end; /* and ptr to end */
struct vtxlst_t *__off_vtxlst_hdr; /* bid chan vtx list for marks off */
struct vtxlst_t *__off_vtxlst_end; /* and ptr to end */
struct vtxlst_t *__vtxlst_freelst; /* free list for vtx lists */
struct vtx_t *__vtx_freelst;  /* free list for re-using vtxs */   
struct edge_t *__edge_freelst; /* free list for re-using edges */
int32 __nxt_bidvtx;    /* glb for next bid vtx index tab pos to fill */

word32 __acum_sb;      /* accumulator for stren tran chan combined */
word32 __acum_a;       /* accumulator for tran chan non stren */
word32 __acum_b;
byte *__acum_sbp;      /* ptr to stacked strength byte */
struct xstk_t *__acum_xsp; /* ptr to stacked strength byte */

/* end of time slot variables, strobe, monitor, time check */
struct strblst_t *__strobe_hdr; /* list strobe display at slot end */
struct strblst_t *__strobe_end; /* end of strobe display list */
struct strblst_t *__strb_freelst; /* head of free strobe elements */
struct st_t *__monit_stp;/* monit if chg display at slot end stmt */
t_midat *__monit_idp;    /* current monitor itree element */
word32 __slotend_action; /* word32 of 1 bit switches set for action */
int32 __monit_active;  /* T => monitor can trigger (default) */
struct dceauxlst_t *__monit_dcehdr; /* header of current dces */
struct fmonlst_t *__fmon_hdr; /* list of execed (enabled) fmonitors */
struct fmonlst_t *__fmon_end;
struct fmonlst_t *__cur_fmon; /* current fmon list entry */
struct fmselst_t *__fmonse_hdr; /* this slot end fmon eval list */
struct fmselst_t *__fmonse_end;
struct fmselst_t *__fmse_freelst; /* fmon slot end free list head */

/* interactive execution variables */
t_midat *__scope_idp;     /* from $scope itree place */
struct task_t *__scope_tskp; /* from $scope task if present */ 
struct symtab_t *__last_iasytp; /* last found symbol symbol table */
struct iahist_t *__iahtab;/* table of history commands */
int32 __iahsiz;        /* current size of history cmd table */
int32 __iah_lasti;     /* current (latest) command */
struct hctrl_t *__hctrl_hd; /* head of active iact stmts */
struct hctrl_t *__hctrl_end;/* and end */
int32 __history_on;    /* collecting and saving history is on */
int32 __hist_cur_listnum;/* number to list for :history command */
int32 __iasetup;       /* F until interactive entered */
int32 __ia_entered;    /* F (also for reset) until iact entered */
int32 __iact_state;    /* T => in interactive processing */
int32 __iact_can_free; /* T => non monitor/strobe, can free */
int32 __no_iact;       /* T => no interactive processing for run */
int32 __intsig_prt_snapshot; /* T => on no iact end, print shapshot */
int32 __reset_count;   /* count of the number of rests ($reset) */
int32 __reset_value;   /* 2nd $reset value preserved after reset */ 
int32 __list_cur_ifi;  /* index in in fils of current source file */
int32 __list_cur_fd;   /* current opened file no. (-1 if none) */
int32 __list_cur_lini; /* current line no. in current dbg file */
int32 __list_cur_listnum;/* number of lines to list at once */
int32 __list_arg_lini; /* for :b (:ib), user list argument */
int32 __iact_scope_chg;/* T => always move scope to cur on iact st. */
struct brkpt_t *__bphdr;/* header of breakpoint list */ 
int32 __nxt_bpnum;     /* next breakpoint number to use */
struct dispx_t *__dispxhdr;/* header of display list */ 
int32 __nxt_dispxnum;  /* next display number to use */
t_midat *__last_stepidp;  /* last step inst. itree loc. */ 
struct task_t *__last_steptskp;/* last step task */
int32 __last_stepifi;  /* last step in fils index */
word64 __last_brktime; /* last break or step time */
int32 __dbg_dflt_base; /* :print debugger default base */ 
int32 __iact_stmt_err; /* T => syntax error for iact stmt */
struct mod_t *__iact_mdp; /* current iact dummy module */
int32 __sav_mtime_units; /* prep of iact statements needs tfmt units */

/* interactive variables */
char *__iahwrkline;    /* interactive command line work area */
int32 __iahwrklen;     /* allocated len of iah work string */
int32 __pending_enter_iact;/* T => enter iact as soon as can */
int32 __iact_reason;   /* reason for entering interactive state */
int32 __single_step;   /* T => need to single step */
int32 __step_rep_cnt;  /* number of times to repeat step */
int32 __step_from_thread;/* T step from non thread loc. (^c?) */
t_midat *__step_match_idp; /* for istep, exec itp must match */
int32 __step_lini;     /* line stepping from (must step to next) */  
int32 __step_ifi;      /* and file */ 
int32 __verbose_step;  /* T => emit location each step */
int32 __stop_before_sim; /* T => enter interactive before sim */
int32 __dbg_stop_before; /* if >100, T (-100) stop before sim */ 
struct st_t *__blklast_stp; /* stmt loc. saved last stmt in block */
struct dceauxlst_t *__iact_dcehdr; /* header of current iact dces */

/* event list variables */
struct telhdr_t *__cur_timehdr;
struct tev_t *__p0_te_hdrp;/* pound 0 event list header */
struct tev_t *__p0_te_endp;/* pound 0 event list end */
struct tev_t *__cur_te_hdrp;
struct tev_t *__cur_tevp; /* ptr to event list for adding to front */
struct tev_t *__cur_te_endp;
struct tev_t *__tefreelstp;/* free list for events */
struct tev_t *__nb_te_hdrp; /* non-blocking new end queue hd */ 
struct tev_t *__nb_te_endp; /* and tail */

struct tedputp_t *__tedpfreelst; /* tf_ putp rec free list header */
struct teputv_t *__teputvfreelst; /* vpi_ put value free list hdr */ 
struct nchglst_t *__nchgfreelst; /* change element free list */
struct tc_pendlst_t *__tcpendfreelst; /* free slot end changed tchks */
struct dltevlst_t *__dltevfreelst; /* pend double event free list */
struct tevlst_t *__ltevfreelst; /* pend event free list */

struct dpi_t *__dpi_hdrp;     /* DPI hdr structs */
struct dpi_t *__dpi_endp;     /* DPI end structs */
struct dpi_t *__cur_dpip;     /* currently scanning dpi */
int32 __can_have_array_on_rhs; /* DPI can pass array to DPI calls */
struct sv_lib_t *__sv_lib_hdrp; /* hdr of sv DPI lib paths */
struct sv_lib_t *__sv_lib_endp; /* hdr of sv DPI lib paths */
int32 __dpi_file_writing; /* T => wrap puts with only fp wr */
char *__dpi_interp_wrapper_fnam; /* file name of interp wrapper */

/* net change list variables */
struct nchglst_t *__nchg_futhdr; /* header of future net chg list */
struct nchglst_t *__nchg_futend; /* end (for add) of future net chgs */
struct tc_pendlst_t *__tcpendlst_hdr; /* header of pending */ 
struct tc_pendlst_t *__tcpendlst_end; /* end of pending */
struct tev_t **__wrkevtab; /* for exit, trace of pending events */
int32 __last_wevti;    /* last filled */
int32 __size_wrkevtab; /* and current allocated size */ 

#ifdef __STREE__
/* variables for new red-black timing tree */
struct tqnode_t __sentinel;     /* empty node holder */
struct tqnode_t *__tree_root;   /* root of tree */
struct tqnode_t *__min_time_node; /* current minimum node */
struct tqnode_t *__max_time_node; /* current maximum node */

struct tqnode_t **__free_nodes;   /* nodes freed - available for reuse */
int32 __free_node_size;         /* size of freed node array */
int32 __free_node_ndx;          /* current freed node index */

#else
struct heap_t **__heap;
int32 __heap_size;
int32 __heap_maxsize;
struct heap_t *__time_hash[THASH_SIZE];
struct heap_t **__free_heap;
int32 __free_heap_ndx;        
int32 __collision_count;
#endif

struct tev_t **__free_tevs;    /* tevs freed - available for reuse */
int32 __free_tev_size;         /* size of freed tev array */
int32 __free_tev_ndx;          /* current freed tev index */

int32 __insn_count;            /* total insn count */
int32 __insn_print_count;      /* actually printed insn count */
int32 __coalesce_count;        /* coalesce insn count */
int32 __spill_count;           /* spill insn count */
int32 __spill_nonw_count;      /* spill non-wide insn count */
int32 __design_has_ld_pli_libs;  /* design has +pli/+vpi on cmmnd ln*/
int32 __cvc_nd_old_gate_store; /* nd to store gate_out_ofs value */
int32 __design_has_auto_task;  /* T => design has auto task/func */
/* end of declares from v.h */

/* AIV NOTICE - these must be init here because they are changed */
/* in exe_main.c */
int32 __running_cvc_exe = FALSE; /* T => running compiled executable */
void (*__dsgn_initp)(void) = NULL;
int32 __gbl_argc = -1;       /* global to hold orig argc num */
char **__gbl_argv = NULL;    /* global to hold orig argv addr */
t_midat **__idpdat_areasp = NULL;  /* mod idp area pointers */

int32 __execute_compiled; /* execute compiled executable */

/* local prototypes */
#ifndef __NOSIGS__
static void segv_handle(void);
#endif

static void open_logfile(void);
static void init_glbs(void);
static void set_tfmt_dflts(void);
static void init_ds(void);
static void xpnd_args(int32, char **);
static struct optlst_t *alloc_optlst(void);
static void copy_xpnd_onelev_args(void);
static void try_to_expand_environment_var(char *, char *);
static void ins_optlst_marker(int32, int32);
static void dmp_xpnd_olist(struct optlst_t *);
static int32 find_opt(char *);
static void do_args(void);
static void bld_inflist(void);
static void do_sdflocdef(char *, char *, int32);
static void do_cmdmacdef(char *, struct optlst_t *);
static int32 bld_incdtab(char *, struct optlst_t *);
static struct loadpli_t *bld_loadpli_lbs(char *, struct optlst_t *, int32);
static int32 bld_boot_rout_list(struct loadpli_t *, char *);
static int32 check_rnam_str(char *);
static int32 bld_lbxtab(char *, struct optlst_t *);
static void add_lbfil(char *, char);
static struct vylib_t *alloc_vylib(char *);
static int32 add_suppwarn(char *, struct optlst_t *);
static void wrhelp(void);
static void init_modsymtab(void);
static void init_stsymtab(void);
static void add_systsksym(struct systsk_t *);
static void add_sysfuncsym(struct sysfunc_t *);
static void chk_toggle_opt_consistent(void);
static void prep_vflist(void);
static void do_timescale(void);
static int32 prt_summary(void);
static void prt_deswide_stats(void);
static int32 count_tran_nets(void);
static void mem_use_msg(int32);
static void prt_alldesmod_tabs(void);
static void prt2_desmod_tab(void);
static void bld_modnam(char *, struct mod_t *, int32);
static int32 count_cells(struct mod_t *);
static int32 count_gates(struct mod_t *, int32 *);
static void prt2_permod_wiretab(void);
static int32 cnt_modprt_bits(struct mod_t *);
static void cnt_modwires(struct mod_t *, int32 *, int32 *, int32 *, int32 *, int32 *,
 int32 *, int32 *);
static void st_prt2_permod_wiretab(void);
static void st_cnt_modprt_bits(struct mod_t *, int32 *, int32 *, int32 *);
static void st_cnt_modwires(struct mod_t *, int32 *, int32 *, int32 *, int32 *);
static void prt2_permod_tasktabs(void);
static void cnt_modtasks(struct mod_t *, int32 *, int32 *, int32 *, int32 *, int32 *,
 int32 *);
static void prt_modhdr(struct mod_t *);
static void reset_cntabs(int32 *, int32 *, int32 *, int32 *, int32 *, int32, int32 *,
 int32 *, int32 *, int32);
static void accum_usecnts(struct mod_t *, int32 *, int32 *, int32 *, int32 *, int32 *,
 int32 *, int32 *, int32 *, int32 *);
static void prt_elapsed_time(void);
static void flush_verbose_dumpports_files(void);

/* extern prototypes (maybe defined in this module) */
extern int32 __dig_main(int32, char **);
extern void __done_sim(void);
extern void __setup_dbmalloc(void);
extern void __start_chkchain(void);
extern void __my_ftime(time_t *, time_t *);
extern void __prt_end_msg(void);
extern void __add_infil(char *);
extern void __grow_infils(int32);
extern int32 __open_sfil(void);
extern void __push_vinfil(void);
extern int32 __pop_vifstk(void);
extern void __do_decompile(void);
extern void __process_cdir(void);
extern char *__get_tmult(char *, word32 *);
extern void __prt2_mod_typetab(int32);
extern int32 __enum_is_suppressable(int32);

/* extern prototypes defined in other module */
extern void __xform_nl_stmts(void);
extern void __initialize_dsgn_dces(void);
extern int32 __comp_sigint_handler(void);
extern char *__my_malloc(size_t);
extern char *__my_realloc(void *, size_t, size_t);
/* pv stralloc is fast small section string alloc but can't be freed */ 
extern char *__pv_stralloc(char *);
extern struct symtab_t *__alloc_symtab(int32);
extern char *__prt_vtok(void);
extern char *__to_wtnam2(char *, word32);
extern int32 __fr_wtnam(int32);
extern int32 __get_arrwide(struct net_t *);
extern struct tnode_t *__vtfind(char *, struct symtab_t *);
extern void __init_acc(void);
extern void __my_dv_flush(void);
extern void __my_dp_flush(struct dp_fildesc_t *);
extern void __push_wrkitstk(struct mod_t *, int32);
extern void __pop_wrkitstk(void);
extern void __setup_contab(void);
extern void __my_exit(int32, int32);
extern struct sy_t *__get_sym(char *, struct symtab_t *);
extern void __try_to_fold_for_loops(void);
extern void __rd_optcfg_files(void);

extern char *__to_timunitnam(char *, word32);
extern FILE *__tilde_fopen(char *, char *);
extern char *__bld_lineloc(char *, word32, int32);
extern char *__schop(char *, char *);
extern void __my_fprintf(FILE *, char *, ...);
extern void __cv_msg(char *s, ...);
extern void __dbg_msg(char *, ...);
extern void __crit_msg(char *s, ...);
extern void __ip_msg(char *s, ...);
extern void __ip2_msg(char *s, ...);
extern void __pv_ferr(int32, char *, ...);
extern void __pv_err(int32, char *, ...);
extern void __pv_warn(int32, char *, ...);
extern void __gfwarn(int32, word32, int32, char *, ...);
extern void __pv_fwarn(int32, char *, ...);
extern void __gfinform(int32, word32, int32, char *, ...);
extern void __gferr(int32, word32, int32, char *, ...);
extern void __finform(int32, char *, ...);
extern void __inform(int32, char *, ...);
extern void __fterr(int32, char *, ...);
extern void __pv_terr(int32, char *, ...);
extern void __arg_terr(char *, int32);
extern void __case_terr(char *, int32);
extern void __misc_terr(char *, int32);
extern int32 __pre_fixup_nl(void);
extern int32 __fixup_and_gen_nl(void);
extern int32 __fixup2_nl(void);
extern void __prep_sim(void);
extern void __unget_vtok(void);
extern void __call_all_checktfs(void);
extern int32 __get1_vtok(FILE *);
extern void __skipover_line(void);
extern int32 __chk_beg_line(int32);
extern void __collect_line(void);
extern void __exec_all_compiletf_routines(void);
extern void __vpi_endcomp_trycall(void);
extern void __free_design_pnps(void);
extern void __prep_dpi(void);
extern void __rem_0path_dels(void);
extern void __init_sim(void);
extern void __call_misctfs_streset(void);
extern void __vpi_startreset_trycall(void);
extern void __reset_to_time0(void);
extern void __pv_sim(void);
extern void __vpi_endsim_trycall(void);
extern void __alloc_xsval(struct xstk_t *, int32);
extern void __my_fclose(FILE *);
extern void __my_free(void *, size_t);
extern void __maybe_open_trfile(void);
extern int32 __get_cmdtok(FILE *);
extern void __do_macdefine(char *, char *);
extern void __add_sym(char *, struct tnode_t *);
extern void __setup_veriusertf_systfs(void);
extern void __call_vlog_startup_procs(void);
extern void __dmp_mod(FILE *, struct mod_t *, int32);
extern void __dmp_udp(FILE *, struct udp_t *);
extern void __get_vtok(void);
extern void __rd_ver_src(void);
extern void __rd_ver_mod(void);
extern int32 __bqline_emptytail(char *);
extern void __process_pli_dynamic_libs(struct loadpli_t *);
extern int32 __rd_cfg(void);
extern void __expand_lib_wildcards(void); 
extern void __rd_ver_cfg_src(void);
extern void __sym_addprims(void);

static void running_bin_setup(void);
static void init_mdprt_ofs(struct mod_t *);
static void run_executable(void);

extern void __setup_dummy_events(void);
extern struct tev_t *__alloc_cur_tev(void *, word64);
extern void __convert_mipd_val_inumdels_to_const(void);
extern struct avlhd_t *__allocinit_avlhd(void);
extern int32 __set_mark_mdprt_flags(struct net_pin_t *, int32 *, int32 *, 
 int32 *, int32 *, int32 *, int32 *, int32 *, int32 *, int32 *);
extern struct net_chg_t *__find_nchg_range(struct net_t *, int32, int32);
extern int32 __net_chg_nd_store(struct net_t *, int32, int32);
extern int32 __needs_netchg_record(struct net_t *);
extern int32 __comp_ndx(struct net_t *, struct expr_t *);
#ifndef __CVC_RT__
extern int32 __cvc_driver(void);
#endif
extern void __process_wire_ev(void);
extern void __process_thrd_ev(void);
extern void __process_trpthdst_ev(void);
extern void __process_gatechg_ev(void);
extern void __process_cancel_ev(void); 
extern void __delay_callback(void);
extern void __sync_call_misctf(void);
extern void __setdel_call_misctf(void);
extern void __process_putpdel_ev(void);
extern void __process_vpi_varputv_ev(void); 
extern void __process_vpidrv_ev(void); 
extern void __set_mod_ent_bits(struct mod_t *);
extern void __free_mod_npp_dce_table(void);
extern void __free_sysfcall_expr(void);
#ifdef __XPROP__
extern void __prep_xprop_stmts(int32);
extern void __setup_xprop_not_eligible_file(struct optlst_t *);
#endif

extern void __fst_close(void);

/* externs for system error messages */
 extern int32 errno;

/* special external for setjmp environment - reset environment */ 
extern jmp_buf __reset_jmpbuf;
extern const char __pv_ctab[];

/*
 * main
 */
extern int32 __dig_main(int32 argc, char **argv)
{
 int32 rv; 
 long t1;
 double timd1;
 char s1[RECLEN];
#ifndef __CVC_RT__
 int32 save_quiet;
 struct stat st;
#endif

 /* only does something if db malloc define set */ 
 __setup_dbmalloc();

 __start_sp = __end_sp = NULL;
 __log_s = NULL;
 /* set compilation int32 signal and save entry signal so can restore */
#ifndef __NOSIGS__
#if defined(INTSIGS)
 __old_int_sig = (sighandler *) signal(SIGINT, __comp_sigint_handler);
#else
 __old_int_sig = (sighandler *) signal(SIGINT,
   (void (*)()) __comp_sigint_handler);
#endif
#endif

 init_glbs();


 /* vpi argument special format argv only set if needed */
 __vpi_argc = 0;
 __vpi_argv = NULL;
 /* no by convention argv 0 always has program name */
 __vpi_argv0 = __pv_stralloc(argv[0]);

 /* expand options so have list that looks as if all on command line */
 xpnd_args(argc, argv);

 /* process special early options - any errors here only to std out */
 /* notice no verbose message for quiet */
 if (__quiet_olp != NULL)
  {
   __quiet_msgs = TRUE;
   /* vendor1 runs with -q need to allow verbose switches to be turned on */ 
   __verbose = FALSE;
  }
 open_logfile();

#ifdef __linux__
#ifdef __ELF__
 __platform = __pv_stralloc("Linux-elf");
#else
 __platform = __pv_stralloc("Linux-aout");
#endif
#endif

 /* SJM 12-28-12 - this is the major version used by RLM license manager */
 __vers = __pv_stralloc(VERS);
 __vers2 = __pv_stralloc(VERS2);
 __ofdt = __pv_stralloc(OFDT);
 __ip2_msg("%s%s of %s (%s).\n", __vers, __vers2, __ofdt, __platform);

 __ip_msg("Copyright (c) 1991-2014 Tachyon Design Automation Corp.\n");
 __ip_msg(
  "  All Rights reserved.  Licensed software subject to prohibitions and\n");
 __ip_msg(
  "  restrictions.  See OSS CVC artistic license included with release.\n");  

 __cv_msg("Today is %s.\n", __pvdate);

 if (__help_olp != NULL)
  {
   wrhelp();
   __cv_msg("**Special help mode successfully completed.\n");
   return(0);
  }

 if (__verb_olp != NULL)
  {
   if (!__quiet_msgs)
    { __verbose = TRUE; __cv_msg("  Verbose mode is on.\n"); }
  }
 if (__log_s != NULL && strcmp(__log_fnam, DFLT_LOGFNAM) != 0)
  {
   if (__verbose)
    __cv_msg("  Output log will be written to \"%s\".\n", __log_fnam);
  }
 if (__verbose) __cv_msg("  Invoked by: \"%s\".\n", argv[0]);  

 do_args();

/* SJM 12-05-12 - REMOVED EXCEPT FOR PLI SEGV should not happen and for ==
// for PLI want to be able to trace back not exit
// #ifndef __NOSIGS__
 =* AIV 09/10/09 need to catch segv and print message *=
 signal(SIGSEGV, (void (*)()) segv_handle);
// #endif
=== */

 bld_inflist();

 __modhdr = __end_mdp = NULL;

 __init_acc();

 init_modsymtab();
 /* must initialize pli table after file processed */
 init_stsymtab();

 /* AIV 12/14/10 - there was a bug with compiling on 32-bit and running */
 /* the compiled sim on 64-bit (with PLI?) moving this down here fixes it */
 /* AIV 03/07/07 - save the memory use after arguments read */
 __mem_cvc_use = __mem_use; 
 __dsnmemp = NULL;

 /* --- DBG remove
 if (__verbose) 
  __cv_msg("  Initialization used %ld bytes of allocated memory (%ld free).\n",
  __memstr_use + __mem_use + __mem_free);
 --- */

 /* SJM 12/05/03 - for now assuming if +config options to specify lib map */ 
 /* file, then do not read default lib.map in cwd - is that correct? */ 
 if (__map_files_hd == NULL)
  {
   FILE *fp;

   if ((fp = __tilde_fopen("lib.map", "r")) != NULL)
    {
     __my_fclose(fp); 
     __map_files_hd = __map_files_tail = (struct mapfiles_t *) 
      __my_malloc(sizeof(struct mapfiles_t));
     __map_files_hd->mapfnam = __pv_stralloc("lib.map");
     __map_files_hd->mapfnxt = NULL;
#ifndef __CVC_RT__
     if (__verbose)
      {
       __cv_msg(
        "  Using map.lib config file because no +config options specified.\n");
      }
#endif
    }
#ifndef __CVC_RT__
   else if (__verbose)
    {
     __cv_msg(
      "  P1364 2001 config map library not specified - using -y/-v libraries.\n"); 
    }
#endif
  }

 /* SJM 12-11-10 - read the config opt file into char strings */
 /* need to read before parsing src in case any errors in arg (opt) file */
 /* just read and save here, opt cfg (mostly net tgl) set up happens near */
 /* end of prep just before setting up idp area */
 __rd_optcfg_files();

#ifndef __CVC_RT__
 /* SJM 02-17-13 - need to warn if toggle report options but toggle not on */
 /* and vice versa - need checking before elaborating src */
 chk_toggle_opt_consistent();
#endif

 /* read the cfg lib.map file list and build internal d.s. */ 
#ifndef __CVC_RT__
 if (__verbose) __cv_msg("  Begin Translation:\n");
#endif

 if (__map_files_hd != NULL)
  {
   /* SJM - 05/26/04 if config used, ignore any command line .v files */
#ifndef __CVC_RT__
   if (__last_inf != __last_optf)
    {
     __pv_warn(3138,
      "library config used but verilog files specified on command line - files ignored");
    }
   if (__verbose) __cv_msg("  Reading library config map.lib files:\n");
#endif
   __rd_cfg();
   if (__cmdl_library == NULL) __cmdl_library = __pv_stralloc("work");
   /* after expansion, each library element is a concrete file name */
   __expand_lib_wildcards(); 
   __rd_ver_cfg_src();
  }
 else
  {
   /* use pre-2001 files reading routines */
   prep_vflist();
   __rd_ver_src();
  }

 rv = 0;
 if (__parse_only)
  {
   __cv_msg("  Parsing only run complete.\n");
   __my_ftime(&__end_time, &__end_mstime);
   if (__pv_err_cnt != 0) rv = 1; else rv = 0;
   goto done2;
  }

#ifndef __CVC_RT__
 if (__in_ifdef_level != 0)
  {
   __pv_err(924, "last `ifdef unterminated in source stream");
  }
 if (__end_mdp == NULL)
  {
   if (__pv_err_cnt != 0)
    {
     rv = 1;
     goto err_done;
    }
   __crit_msg("**Design contains no modules - nothing to do.\n");
   goto set_etime;
  }

 /* calls to fixup routines here */
 if (__verbose)
  {
   __cv_msg("  Begin Elaboration pass 2:\n");
  }
 /* if verbose off will not print anything */
 mem_use_msg(FALSE); 
#endif
 /* AIV 03/07/07 - memory usage is now current minus what is was when */
 /* command line arguments read */
 /* AIV 10/30/08 - moved this back to here - memory can be from source */
 /* reading just as good - was not getting exact match from executable */
 /* for some reason */
 __mem_cvc_use = __mem_use - __mem_cvc_use;

 /* SJM 02-27- 09 - pre fix up (pass 2) that are before gen converge loop */
 /* AIV 07/26/10 - now if there is any error return an exit code 1 */
 /* this was 0 for historical reasons from the Antrim days now do exit */
 if (!__pre_fixup_nl()) { rv = 1; goto err_done; }

 /* SJM 01-19-09 - if errors occur in preping con funcs, can't copy wrk sp */ 
 if (__pv_err_cnt != 0) { rv = 1; goto err_done; }

 /* 03-03-09 - this becomes fixup nl if no generates in design */
 if (!__fixup_and_gen_nl()) { rv = 1; goto err_done; }
 if (__pv_err_cnt != 0) { rv = 1; goto err_done; }

 /* this is new post instance tree, param, xmr fixups - expr chking mostly */
 if (!__fixup2_nl()) { rv = 1; goto err_done; }
 if (__pv_err_cnt != 0) { rv = 1; goto err_done; }

 if (__decompile) __do_decompile();

 /* AIV 04/01/11 - if compiled sim and inline for loop option turned on */
 if (__opt_unroll_loops && __compiled_sim) __try_to_fold_for_loops();

 __my_ftime(&__end_comp_time, &__end_comp_mstime);
 if (__numtopm == 0)
  {
   __crit_msg("  Unable to begin simulation - no top level modules.\n");   
#ifndef __CVC_RT__
set_etime:
#endif
   __my_ftime(&__end_time, &__end_mstime);
   rv = 1;
   goto done2;
  }

 /* SJM 02/26/08 - now also need to bld the various IDP for each module */ 
 /* per instance storage areas for each instance of variable storage */
 /* and know at compile time net list elements such as fixed events */
 /* and nchgs */
 __prep_sim();

#ifndef __CVC_RT__
 if (__pv_err_cnt == 0)
  {
   if (__prt_stats || __prt_allstats)
    {
     save_quiet = __quiet_msgs;
     __quiet_msgs = FALSE;
     prt_alldesmod_tabs();
     __quiet_msgs = save_quiet;
    }
   else if (__verbose)
    {
     save_quiet = __quiet_msgs;
     __quiet_msgs = FALSE;
     prt_deswide_stats();
     __quiet_msgs = save_quiet;
    }
  }
#endif
 if (__compile_only)
  {
   __cv_msg("  Translation only run complete.\n");
   __my_ftime(&__end_time, &__end_mstime);
   goto done;
  }
 if (__pv_err_cnt != 0) { rv = 1; goto err_done; }

#ifndef __CVC_RT__
 if (__verbose) __cv_msg("  Begin elaborator load/optimize:\n");
#else
 if (__verbose) __cv_msg("  Begin compiled design load:\n");
#endif

 __run_state = SS_LOAD;
 __can_exec = FALSE;

 /* prepare and compiled dpi c wrapper file and dl open and dl sym link */
 /* the one routine */
 /* AIV 12/30/10 - this is now done for the compiler as well */
 /* when the compiler enters the interpreter needs the interp wrapper */
 if (__dpi_hdrp != NULL)
  {
   /* SJM 11-28-10 - only preprocess dpi import/export routines if at */
   /* least one dpi routine */
   if (__dpi_hdrp != NULL) __prep_dpi();
   if (__pv_err_cnt != 0) { rv = 1; goto err_done; }

   /* SJM 10-07-10 LOOAKTME??? - for now even if dpi does not link still */
   /* try to link other PLI - will exit if errors after there */
  }

#ifdef __CVC_DEBUG__
 /* RELEASE remove -- */
 /* LOOKATME - for now need this even when read source only mode */
 if (__verbose && !__compiled_sim)
  {
   struct mod_t *mdp;
   int32 tot_var_wrds;
   tot_var_wrds = 0;
   for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
    {
     if (mdp->mod_idata_siz == 0) continue;
     tot_var_wrds += mdp->mod_idata_siz;
    }
   __cv_msg( "  Variable storage in bytes: %d.\n", WRDBYTES*tot_var_wrds);
  }
#endif

 __sfnam_ind = 0;
 __slin_cnt = 0;
 /* final step in loading is calling vpi_ systf checktf routines */ 
 /* can not do until here because d.s. built */ 
 if (__vpi_sysf_hdr != NULL || __vpi_syst_hdr != NULL)
  {
   /* compiletf run in reset state because no time and no events */
   /* AIV 06/22/10 - no reason to handle vpi for compiling of cvcsim */
   /* only if running compiled executable does this need to be executed */
   if (!__compiled_sim || __running_cvc_exe)
    {
     __run_state = SS_RESET;
     __exec_all_compiletf_routines();
     __run_state = SS_LOAD;
    }
  }

 /* still can use changed params (either type) to elaborate delays */
 /* from params and set delays even where no delay in source here */
 /* 08-07-07 - notice now can't and don't need to xform expressions */
 /* AIV 06/22/10 - no reason to handle vpi for compiling of cvcsim */
 /* only if running compiled executable does this need to be executed */
 if (__have_vpi_actions && (!__compiled_sim || __running_cvc_exe))
  {
    __vpi_endcomp_trycall();
  }

 if (__pv_err_cnt != 0) { rv = 1; goto err_done; }

 /* SJM 01/14/00 - always can free design pnps since (LABEL does not work */
 /*                (error emitted) in $sdf_annotate systask calls */
 /* SJM for sdf do not free - see if works  
 __free_design_pnps();
 -- */

 /* after here, delays elaborated - only vpi change of delays now possible */
 /* but vpi_ change probably not alloed under P1364 */
 /* SJM 01/14/00 - must allow param changes from label during sim */
 /*                for sdf annotate calls - undefined change points */ 
 /*                also can't remove all 0 paths delays may change still */ 
 if (!__has_sdfann_calls)
  {
   /* go through disable all 0 delay only paths - never causes error */
   if (__rm_path_pnd0s) __rem_0path_dels();
  }

 /* but can remove gates and any added all 0 mipds (maybe added again if */
 /* annotate systask used later) so need messages here */ 
#ifndef __CVC_RT__
 if (__num_rem_gate_pnd0s != 0 && __verbose)
  {
   __cv_msg(
    "  %d (%d flat) gate or udp zero delays coded in source removed.\n",
    __num_rem_gate_pnd0s, __num_flat_rem_gate_pnd0s);
  }
 if (__num_rem_mipds != 0 && __verbose)
  {
   __cv_msg("  %d flattened bits of 0 delay MIPDS removed - no effect.\n",
    __num_rem_mipds);
  } 
#endif

 /* SJM 08-07-07 - changed name of xform routine since just xform stmts */ 
 __xform_nl_stmts();

#ifdef __XPROP__
 /* for xprop (not xprop2) find eligible xprop stmts and alloc xprop info */
 if (__xprop && !__xprop2)
  {
   __prep_xprop_stmts(FALSE);
  }
#endif

 /* AIV 05/01/07 - if comiled and have sdf try to fold mipd delays */
 if (__compiled_sim && __has_sdfann_calls)
  {
   __convert_mipd_val_inumdels_to_const();
  }

 if (__compiled_sim)
  {
   long sav_mem_use;
   time_t start_cgen, start_mscgen, end_cgen, end_mscgen;
  
   __my_ftime(&(start_cgen), &(start_mscgen));
   sav_mem_use =__mem_use;
#ifndef __CVC_RT__
   if (__verbose) __cv_msg("  Begin CVC code generation:\n");
#endif

   if (!__running_cvc_exe)
    {
     /* AIV 02/03/09 - special directive to make runtime CVC binary */
     /* do not link in __cvc_driver to do code generation */
#ifndef __CVC_RT__
     if (!__cvc_driver())
      {
       __cv_msg(
        "  CVC assembly code generation failed - unable to continue.\n");
       __my_ftime(&__end_time, &__end_mstime);
       goto done;
      }
#endif
     }
    else running_bin_setup();
   __my_ftime(&(end_cgen), &(end_mscgen));
   if (!__running_cvc_exe)
    {
     if (__verbose)
      {
#ifdef __CVC_DEBUG__
       double d1;

       if (__mem_use - sav_mem_use > 0)
        {
         d1 = 100.0*((double) __mem_use - sav_mem_use)/((double) sav_mem_use);
         __cv_msg("  Memory unfreed by CVC %ld bytes (%.2lf%% more)\n", 
          __mem_use - sav_mem_use, d1);
        }
#endif
       __my_ftime(&end_cgen, &end_mscgen);
       timd1 = (double) (end_cgen - start_cgen)
        + ((double) (end_mscgen - start_mscgen))/1000.0;
       __cv_msg("  CVC compilation %.1lf seconds elapsed.\n", timd1);

#ifdef __CVC_DEBUG__
       /* AIV 11/02/07 - print the insn info for devel */
       __cv_msg(
       "  CVC total instructions %d spilled %d coalesced %d wide spilled %d printed insn %d.\n", 
       __insn_count, __spill_nonw_count, __coalesce_count, __spill_count, __insn_print_count);
#endif
      }
     else
      {
       /* AIV 12/21/07 - always print the total compilation time */
       /* users think that the compilation time is part of the runtime */
       /* notice this is printf to prevent dumping to log file */
       if (!__quiet_msgs)
        {
         __my_ftime(&end_cgen, &end_mscgen);
          timd1 = (double) (end_cgen - start_cgen)
            + ((double) (end_mscgen - start_mscgen))/1000.0;
         printf("\n  CVC compilation %.1lf seconds elapsed.\n", timd1);
        }
      }
    }
  }
 /* if compile only print message and go to done */
#ifndef __CVC_RT__
 if (__compiled_sim)
  { 
   /* if DPI import/exports C code may not have linked properly */
   /* due to naming/linking issues caused by user code */
   if (__dpi_hdrp != NULL)
    {
     if (stat(__exe_name, &st) != 0)
      {
       __pv_ferr(4836, "EXECUTABLE %s failed to link - probably due to inconsistent naming of DPI functions", __exe_name);
      }
    }
   else
    {
     __cv_msg("\n  EXECUTABLE SAVED TO '%s'.\n\n", __exe_name); 
    }
   __my_ftime(&__end_time, &__end_mstime);
   goto done;
  }
#endif

 /* now that all storage allocated and given some val, call checktf */
 /* routines, these can call anything not sim queue depended but shouldn't */
 if (__tfrec_hdr != NULL)
  {
   __run_state = SS_RESET;
   __call_all_checktfs();
   __run_state = SS_LOAD;
  }

 /* SJM 05/04/05 - now can only initialize dce previous values */
 __initialize_dsgn_dces();

 __init_sim();
 __my_ftime(&__end_prep_time, &__end_prep_mstime);

 if (__verbose) __cv_msg("  Begin simulation:\n");
 if (__verbose) __cv_msg("\n");

 /* on setup returns 0, on lng jmp returns 1, but always just exec sim */
 /* since restart */
 /* on set returns 0, do not run re-init code */
 if (setjmp(__reset_jmpbuf) != 0)
  {
   if (__tfrec_hdr != NULL) __call_misctfs_streset();
   if (__have_vpi_actions) __vpi_startreset_trycall();
   __now_resetting = TRUE;
   __run_state = SS_RESET;
   /* change to sim run state in here */
   __reset_to_time0();
   /* by here state back to SIM */
  }

#ifdef __XPROP__
 /* if xprop and compiled sim remove dummy non-blocking task modules */
 if (__xprop && __compiled_sim)
  {
   struct mod_t *mdp;

   for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
    {
     /* DBG remove -- */
     if (mdp->xprop_nb_taskp == NULL) __misc_terr(__FILE__, __LINE__);
     /* --- */
     /* just point to the first real task */
     mdp->mtasks = mdp->mtasks->tsknxt;
    }
  }
#endif

 __pv_sim();

 /* LOOKATME - think also call end sim cb here but LRM says $finish */
 if (__have_vpi_actions) __vpi_endsim_trycall();

 /* LOOKATME - remove since does not match ovi __cv_msg("\n"); */
 /* notice must know current end time */
 __my_ftime(&__end_time, &__end_mstime);
 __prt_end_msg();
 goto done;

err_done:
 __cv_msg("  Unable to begin simulation.\n");
 __my_ftime(&__end_time, &__end_mstime);

done:
 if (__dv_fd != -1) __my_dv_flush();
 if (__verbose)
  {
   if (__dv_fd != -1)
    {
     if ((t1 = lseek(__dv_fd, 0, SEEK_END)) != -1) 
      {
       __cv_msg("  $dumpvars %ld bytes written to file \"%s\".\n", t1,
        __dv_fnam); 
      }
    } 
  }
 flush_verbose_dumpports_files();

 /* close FST file */
 if (__fst_ctx != NULL) __fst_close();
done2:
 /* DBG remove --- */
 if (__xspi != -1 || __itspi != -1 || __fcspi != -1)
  __misc_terr(__FILE__, __LINE__);
 /* --- */
 strcpy(s1, ctime(&__end_time));

 s1[24] = '\0';
 __pvdate = __pv_stralloc(s1);
 timd1 = (double) (__end_time - __start_time)
  + ((double) (__end_mstime - __start_mstime))/1000.0;
 __cv_msg("End of %s%s at %s (elapsed %.1lf seconds).\n",
  __vers,__vers2, __pvdate, timd1);
 /* AIV 07/26/10 - now if errors will return with exit 1 */
 if (rv != 0) __my_exit(rv, TRUE);
 else __my_exit(rv, FALSE);
 /* needed to stop warns but exit prevents control from reaching here */
 return(0);
}

/*
 * for executable just run the compiled init code and setup remaining   
 * enter locations
 */
static void running_bin_setup(void)
{
 struct mod_t *mdp;

 /* AIV 02/13/09 - this should be done there - only for executable */
 __setup_dummy_events();

 /* SJM 08/24/08 - process slotend handler also gone from psel8 */

 /* SJM 05/11/08 - last part of linking in solib must be to call the */
 /* comm c init program - this is beginning point of ALNK (after link) time */
 /* when move to a.out where main calls this proc then called from new a.out */

 /* SJM 09/05/08 - FIXME - for now need to dlsym link the ptr to the */
 /* one after link time routine that executes the generated and assmebled */
 /* init - static linker name resolutions */
 (__dsgn_initp)();

 /* AIV 12/13/10 - used for debugging when users get this unexpectedly */
 if (__override_change)
  {
   if (__verbose)
    {
     __cv_msg("  Override model changes - executable [ %ld ] current [ %ld ]\n",
      __dsnmemp[0], __mem_cvc_use);
    }
  }
 else if (__mem_cvc_use != __dsnmemp[0])
  {
   __pv_terr(2906,
    "compiled executable does not match compiled source - must recompile");
   return;
  }

 /* AIV LOOKATME - don't really need the actual enter bits set */
 /* but need the ialp->needs_thread bit set - could fix this */
 /* put this pass doesn't really take any time */
 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   /* AIV 07/22/09 - setup optimized scalar mdprt idp data */
   /* doing this here because it produces large amount of alnk code */
   init_mdprt_ofs(mdp);

   mdp->mod_ndx_seq_no = 0;
   __set_mod_ent_bits(mdp);
  }

 /* SJM 09/05/08 - could be handled with awr ll routines in alnk wrappers */
 __free_event_pnd0_tevp->enterptr = __process_free_ev_pnd0_enterp;
 __free_event_tevp->enterptr = __process_free_ev_enterp;
 /* AIV 05/09/07 - if load solib know using static addrs */
 __free_mod_npp_dce_table();
 __free_sysfcall_expr(); 
}

/*
 * set up an instances optimize NP_MDPRT code by setting value into __idp
 * area
 *
 * AIV 07/22/09 - this cannot be alnk produces way too much code 
 */
static void init_mdprt_ofs(struct mod_t *mdp)
{
 int32 ni, ii, ndx, biti;
 int32 has_some_nchg, has_all_nchg, has_dmpvs, has_dmpps, has_empty; 
 int32 has_all_bsel, all_bsel_1w, mixed_exprs, all_empty, has_toggle;
 struct mod_t *downmdp, *upmdp;
 struct net_t *np, *up_np;
 struct net_pin_t *npp;
 struct expr_t *up_lhsx;
 struct itree_t *itp;
 struct net_chg_t *ncp;
 struct inst_t *ip;
 size_t ofs;
 t_midat *idp_ofs, *mod_idp_base;

  
 for (ni = 0, np = &(mdp->mnets[0]); ni < mdp->mtotvarnum; ni++, np++) 
  {
   for (npp = np->nlds; npp != NULL; npp = npp->npnxt)
    {
     /* not optimized continue */
     if (npp->scalar_mdprt_ofs == 0) continue;

     /* DBG remove -- */
     if (npp->npntyp != NP_MDPRT) __misc_terr(__FILE__, __LINE__);
     /* --- */

     /* AIV 12/06/10 - add to record changes for toggle coverage */
     mixed_exprs = __set_mark_mdprt_flags(npp, &has_all_nchg, &has_some_nchg, 
      &has_dmpvs, &has_dmpps, &has_empty, &has_all_bsel, &all_bsel_1w, 
      &all_empty, &has_toggle);
    
     downmdp = npp->elnpp.emdp;
     for (ii = 0; ii < downmdp->flatinum; ii++) 
      {
       itp = downmdp->moditps[ii];
       /* this is an instance of mod containing rhs output port load */
       ip = itp->itip;
       if (npp->npntyp == NP_PB_MDPRT)
        { up_lhsx = ip->pb_ipins_tab[npp->obnum][npp->pbi]; }
       else up_lhsx = ip->ipins[npp->obnum];
         
       mod_idp_base = downmdp->mod_idata;
       idp_ofs = &(mod_idp_base[ii*downmdp->mod_idata_siz]);
       /* set the net up lhsx scalar offset */
       /* AIV BEWARE these offsets are order dependent */
       if (up_lhsx->optyp == OPEMPTY) 
        {
         ofs = npp->scalar_mdprt_ofs;
         idp_ofs[ofs] = 0;
         ofs++;

         /* -2 is the marker to determine uncon */
         idp_ofs[ofs] = -2;
         if (has_some_nchg)
          {
           ofs++;
           idp_ofs[ofs] = 0;
          }
         if (has_dmpvs || has_dmpps || has_toggle) 
          {
           ofs++;
           idp_ofs[ofs] = 0;
          }
         continue;
        }

       /* if lsb get the bit */
       if (up_lhsx->optyp == LSB)
        {
         up_np = up_lhsx->lu.x->lu.sy->el.enp;
         biti = __comp_ndx(up_np, up_lhsx->ru.x);
        }
       else 
        {
         up_np = up_lhsx->lu.sy->el.enp;
         biti = -1;
        }
       ofs = npp->scalar_mdprt_ofs;
       idp_ofs[ofs] = WRDBYTES*up_np->nva_ofs;

       /* uses a mix of uconn/lsb/scalar - not just scalar */
       if (mixed_exprs)
        {
         ofs++;
         if (up_lhsx->optyp == ID)
          {
           idp_ofs[ofs] = -1;
          }
         else if (up_lhsx->optyp == LSB)
          {
           /* if all bsel are one word just store the bit index */
           if (all_bsel_1w)
            {
             idp_ofs[ofs] = biti;
            }
           else idp_ofs[ofs] = (word32) up_lhsx;
          }
         else if (up_lhsx->optyp == OPEMPTY) __case_terr(__FILE__, __LINE__);
        }
       /* DBG remove -- */
       else if (up_lhsx->optyp != ID) __misc_terr(__FILE__, __LINE__);
       /* ---- */


       /* if needs net change pass the nchg offset else 0 */
       if (__needs_netchg_record(up_np) && 
           __net_chg_nd_store(up_np, biti, biti)) 
        {
         ofs++;
         ncp = __find_nchg_range(up_np, biti, biti);

         /* DBG remove -- */
         if (ncp == NULL)  __misc_terr(__FILE__, __LINE__);
         /* --- */

         idp_ofs[ofs] = WRDBYTES*ncp->nchg_idp_ofs;
        }
       else if (has_some_nchg)
        {
         ofs++;
         idp_ofs[ofs] = 0;
        }

       /* pass the net index - if contains dumpv */
       if (has_dmpvs || has_dmpps || has_toggle) 
        {
         upmdp = itp->up_it->itip->imsym->el.emdp;
         ndx = up_np - upmdp->mnets;
         ofs++;
         idp_ofs[ofs] = (word32) &(upmdp->mnets[ndx]);
        }
      }
    }
  }
}
 
/*
 * when done with CVC runtime this exits simulation
 */
extern void __done_sim(void)
{
 double timd1;
 long t1;
 int32 rv;
 char s1[RECLEN];

 rv = 0;
 /* LOOKATME - think also call end sim cb here but LRM says $finish */
 if (__have_vpi_actions) __vpi_endsim_trycall();

 /* LOOKATME - remove since does not match ovi __cv_msg("\n"); */
 /* notice must know current end time */
 __my_ftime(&__end_time, &__end_mstime);
 /* AIV 12/21/07 - compiler no longer keeps counts just print elapsed times */
 /* __prt_end_msg(); */
 prt_elapsed_time();

 if (__dv_fd != -1) __my_dv_flush();
 if (__verbose)
  {
   if (__dv_fd != -1)
    {
     if ((t1 = lseek(__dv_fd, 0, SEEK_END)) != -1) 
      {
       __cv_msg("  $dumpvars %ld bytes written to file \"%s\".\n", t1,
        __dv_fnam); 
      }
    } 
  }
 flush_verbose_dumpports_files();
 /* close FST file */
 if (__fst_ctx != NULL) __fst_close();
 rv = prt_summary();
 /* DBG remove --- */
 if (__xspi != -1 || __itspi != -1 || __fcspi != -1)
  __misc_terr(__FILE__, __LINE__);
 /* --- */
 strcpy(s1, ctime(&__end_time));

 s1[24] = '\0';
 __pvdate = __pv_stralloc(s1);
 timd1 = (double) (__end_time - __start_time)
  + ((double) (__end_mstime - __start_mstime))/1000.0;
 __cv_msg("End of %s%s at %s (elapsed %.1lf seconds).\n",
  __vers,__vers2, __pvdate, timd1);
//AIV FIXME ???? NEED TO RETURN 0 not do the exit with TRUE flag
 __my_exit(rv, TRUE);
 /* needed to stop warns but exit prevents control from reaching here */
}

#ifdef __DBMALLOC__
/*
 * start malloc debugging - can call from anywhere
 */
extern void __setup_dbmalloc(void)
{
 union dbmalloptarg m;

 /* m.i = M_HANDLE_IGNORE; */
 m.i = M_HANDLE_ABORT;
 dbmallopt(MALLOC_WARN,&m);
 m.str = "malloc.log";
 dbmallopt(MALLOC_ERRFILE,&m);

 /* set to 1 to turn on */
 /* --- */
  m.i = 1;
//  m.i = 0;
 dbmallopt(MALLOC_CKCHAIN,&m);
 /* -- */

 /* 0 means don't check str/mem func args */
 /* --- */
  m.i = 0;
//  m.i = 1;
 dbmallopt(MALLOC_CKDATA,&m);
 /* --- */
 /* --- */
// m.i = 1;
 m.i = 0;
 dbmallopt(MALLOC_REUSE,&m);
 /* --- */
 /* -- */
 m.i = 3;
 dbmallopt(MALLOC_FILLAREA, &m);
 /* -- */
}

extern void __start_chkchain(void)
{
 union dbmalloptarg m;

 m.i = 1;
 dbmallopt(MALLOC_CKCHAIN,&m);
 /* -- */
 m.i = 1;
 dbmallopt(MALLOC_CKDATA,&m);
 /* -- */
}
#else
/* nil if db malloc not used */
extern void __setup_dbmalloc(void)
{ 
}
extern void __start_chkchain(void)
{
}
#endif

/*
 * routine to compute current time in seconds and milliseconds (if possible)
 */
extern void __my_ftime(time_t *secs, time_t *msecs)
{
 struct timeval tv;
 struct timezone tz;

 if (gettimeofday(&tv, &tz) == EINVAL) __arg_terr(__FILE__, __LINE__);
 
 *secs = (long) tv.tv_sec;
 *msecs = (long) (tv.tv_usec/1000);
}

/*
 * print ending verbose message 
 */
extern void __prt_end_msg()
{
 int32 t1;
#ifdef __METERING_ON__
 extern void __print_hash_stats(void);

 __print_hash_stats();
#endif

 t1 = (int32) __num_proc_tevents - (int32) __proc_thrd_tevents;
 if (t1 < 0) t1 = 0;
 /* AIV 01/10/08 - if get here from $finish counts no longer correct for 
    compiler */
 if (!__compiled_sim)
  {
   __cv_msg(
    "%d simulation events and %u declarative immediate assigns processed.\n",
     t1 , __immed_assigns);
   /* number of cancelled should equal newval (0 del.) and inertial cancels? */ 
   if (__num_execstmts - __num_addedexec > 0)
    {
     __cv_msg("%u behavioral statements executed (%u procedural suspends).\n",
      __num_execstmts - __num_addedexec, __proc_thrd_tevents);
    }
   else
    {
     if (__proc_thrd_tevents > 0 && __compiled_sim)
      {
       __cv_msg("Optimized code execution (%u procedural suspends).\n",
        __proc_thrd_tevents);
      }
    }
   if (__verbose && __debug_flg)
    {
     __cv_msg(
      "  %u(%u) inertial reschedules, %u net changes, %u continuous assigns,\n",
      __num_cancel_tevents, __inertial_cancels + __newval_rescheds,
      __num_netchges, __immed_assigns);
     __cv_msg("  and %d tran/tranif switch vertices processed.\n",
      __num_switch_vtxs_processed);
    }
  }
 prt_elapsed_time();
}


/*
 * print elapsed times 
 */
static void prt_elapsed_time(void)
{
 double timd1, timd2, timd3;

 timd1 = (double) (__end_comp_time - __start_time)
  + ((double) (__end_comp_mstime - __start_mstime))/1000.0;
 timd2 = (double) (__end_prep_time - __end_comp_time)
  + ((double) (__end_prep_mstime - __end_comp_mstime + 50))/1000.0;
 timd3 = (double) (__end_time - __end_prep_time)
  + ((double) (__end_mstime - __end_prep_mstime + 50))/1000.0;
 __cv_msg(
  "  Times (in sec.):  Translate %.1f, load/optimize %.1f, simulation %.1f.\n",
  timd1, timd2, timd3);
}

/*
 * routine to flush and if verbose on print file sizes for all dumpports files 
 */
static void flush_verbose_dumpports_files(void)
{
 int32 dpdi;
 struct dp_fildesc_t *fdescp;
 long t1;

 if (__dp_fildesc_nxti <= 0) return;

 for (dpdi = 0; dpdi < __dp_fildesc_nxti; dpdi++)
  {
   fdescp = &(__dp_fildesc_tab[dpdi]);
   /* AIV 04/22/11 - can not run any time setup - therefore nothing to flush */
   /* rare but can happen - no dumpport has taken place then there is no file */
   if (fdescp->dp_fd == -1) continue;
   __my_dp_flush(fdescp);
   if (__verbose)
    {
     if ((t1 = lseek(fdescp->dp_fd, 0, SEEK_END)) != -1) 
      {
       __cv_msg("  $dumpports %ld bytes written to file \"%s\".\n", t1,
        fdescp->dp_fnam); 
      }
    } 
  }
}

/*
 * STARTUP INITIALIZATION ROUTINES
 */

/*
 * initialize various globals (including flags)
 *
 * sets things that are set and then returned to initial value when done
 * but routine that uses variable
 */
static void init_glbs(void)
{
 int32 i;
#ifdef __STREE__
 struct tqnode_t *n;
#else
 struct heap_t *hp;
#endif
 char *cp;
 char s1[RECLEN];

 /* initialize things needed before any memory can be allocated */
 __mem_use = __mem_freed = __mem_allocated = __memstr_use = 0L;
 __mem_udpuse = __arrvmem_use = 0L;

 /* initialize some vars */
 __pv_err_cnt = __pv_warn_cnt = __inform_cnt = 0;
 __max_errors = MAX_ERRORS;

 /* initialize flags */
 __verbose = FALSE;
 __quiet_msgs = FALSE;
 __lib_verbose = FALSE;
 __cfg_verbose = FALSE;
 __lib_rescan = FALSE;
 __rescanning_lib = FALSE;
 __switch_verbose = FALSE;
 __chg_portdir = FALSE;
 /* SJM 05-13-13 - new change init/always thread start code to */
 /* start (arm) all always blocks first */
 __sched_always_blocks_first = FALSE;
 __cmd_s = NULL;
 __cmd_fnam = NULL;
 __cmd_start_fnam = NULL;
 __key_s = __save_key_s = NULL;
 /* default for trace output if stdout */
 __tr_s = stdout; 
 __tr_fnam = __pv_stralloc("stdout");
 __sdflst = NULL;
 __sdf_s = NULL;
 __sdf_mdp = NULL;
 __sdf_verbose = FALSE; 
 __ignore_sdf_iopath_edges = FALSE;
 __sdf_opt_log_fnam = NULL;
 __sdf_opt_log_s = NULL;
 __has_sdfann_calls = FALSE;

 __map_files_hd = __map_files_tail = NULL;
 __cmdl_library = NULL;
 __cfglib_hd = __cfglib_tail = NULL;
 __cfg_hd = NULL;
 __cur_cfg = NULL;
 __cfg_mdp = NULL;
 __bind_inam_comptab = NULL;
 __siz_bind_comps = 0;
 __last_bind_comp_ndx = -1;
 __optcfg_fils = NULL;
 __last_optcfg_fil = NULL;
 __ocfg_stmts = NULL;
 __wrk_ocvtok_hd = NULL;
 __wrk_ocvtok_end = NULL; 
 strcpy(__cur_optcfg_cntxt_str, "*NONE*");

 /* init of glbs for new P1364-2005 generate feature */
 __dsgn_uses_generate = FALSE;
 __in_gen_region = FALSE;
 __gen_fnam_ind = -1;
 __gen_lin_cnt = -1;
 __mod_gen_id = -1;
 __last_gip = NULL;
 __save_last_mitem = NULL;
 __cur_cntxt_gblk = NULL;
 __gen_sens_hd = NULL;
 __gen_sens_tail = NULL;
 __fixup_round = 1;
 __forblk_index = 0; 

 __sdf_active = FALSE;
 __sdf_during_sim = FALSE;
 __sdf_no_warns = FALSE;
 __sdf_no_errs = FALSE;
 __nokey_seen = FALSE;
 __key_fnam = NULL;
 /* notice warns on by default */
 /* should be more selective about which warnings turned off */
 __no_warns = FALSE;
 __no_errs = FALSE;
 __outlinpos = 0;
 /* notice informs off by default */
 __no_informs = TRUE;
 __compile_only = FALSE;
 __parse_only = FALSE;
 __compiled_sim = FALSE;
 __verbose_mem = FALSE; 
 /* SJM 12/08/05 - now for cvc compiled sim on by default */
 __compiled_sim = TRUE;
 __optimize_level = 0;
 
 __show_asm = FALSE;
 __exe_name = NULL; 

 /* SJM 02-07-13 - making these long strings - if dpi there is a realloc */
 /* so better to copy - also dpi can have mem alloc problems */
 __objdir_path = __my_malloc(4*RECLEN + 1);
  strcpy(__objdir_path, "");
 __usedir_cp = __my_malloc(4*RECLEN + 1);
  strcpy(__usedir_cp, "");
 __use_pwd_as_tmp = FALSE;

 /* default is no location information in generated asm file */
 __asm_emit_loc = 0;
 __opt_block_trace = FALSE;
 __opt_valtrk = FALSE;
 __opt_trk_verbose = FALSE;
 __opt_emit_var_names = FALSE;
 __real_warns = FALSE;
 
 /* pli access level from +acc+ */
 /* SJM 12-16-10 - now using -optconfig file for setting mod/net +acc+ */
 __pli_access_level = 0;   
 __inline_code = FALSE;
 __opt_reg_alloc = FALSE; 
 __opt_two_state = FALSE;
 __opt_two_state_no_wires = FALSE;
 __my_popen = FALSE;
#ifdef __XPROP__
 __xprop_copying = FALSE;
 __xprop_lhs_nets = NULL;
 __xprop_lhs_other_than_id = NULL; 
 __xprop_stmts = NULL; 
 __xprop_net_ndx = -1;
 __xprop_lhs_nets_top = NULL;
 __xprop_lhs_other_than_id_top = NULL; 
 __xprop_stmts_top = NULL; 
 __xprop_net_ndx_top = -1;
 __current_xprop = NULL;
 __xprop_max_net_1_wp = NULL;
 __xprop_max_net_width = 1;
 __added_xprop_stlst_hdr = NULL;
 __added_xprop_stlst_tail = NULL; 
 __xprop_xedge = -1;
 __xprop_trace_fp = NULL;
 __xprop_not_eligible_fp = NULL;
 __xprop_not_eligible = FALSE; 
 __xprop_cond_hit = 0;
 __xprop_cond_max = 1000;
 __xprop_expr_has_cneq = FALSE;
 __xprop_trace_on = FALSE;
 __xprop_xtrace_suppress = FALSE;
 __xprop = FALSE;
 __xprop2 = FALSE;
 __xprop_and_or_xs = FALSE; 
 __no_xprop_edges = FALSE;
 __no_xprop_vectors = FALSE; 
 __xprop_pos_neg_only = FALSE; 
 __do_xprop_xedge_vectors = TRUE;
#endif
 __random_init = FALSE;
 __random_init_2state = FALSE;
 __sv_parse = FALSE;
 __wr_dpi_c_hdrs = FALSE;
 /* SJM 11-30-10 - BEWARE - this wrecks error msg cvsim wr so must only */
 /* be turned on in dpi src dumping and turned off at end of proc */
 __dpi_file_writing = FALSE;
 __dpi_interp_wrapper_fnam = NULL;

 __opt_nbaopt = FALSE;
 __opt_unroll_loops = FALSE;

#ifndef __CVC32__
 __cvc_use_large_model = FALSE;
#endif
 __cap_seq_no = -1;
 __dctrl_seq_no = -1;
 __dctrl_depth = 0; 
 __nested_dctrl = FALSE; 
 __dump_flowg = FALSE;
 __use_interp_dpi_mk = FALSE;
 __opt_debug_flg = FALSE;
 __missing_nchg_trace = FALSE;
 __opt_prt_stats = FALSE;
 __siz_opt_npptab = -1;
 __opt_npptab = NULL; 
 __total_lds_removed = 0;
 __total_lds_from_nets = 0;
 __xpr_dup_tree = __allocinit_avlhd();
 __xpr_isnum_tree = __allocinit_avlhd();
 /* AIV 08/29/07 - currently compiler can reach __schd_1pthwirebit from */
 /* the wrapper for mfi gate change code need to lower all gate code */
 /* and this wouldn't be needed */
 /* actually only schedules from gate_init code - could fix gate init code */
 __process_wire_ev_enterp = __process_wire_ev;
 /* same thing with thread events - exec_disable code is shared via wrapper */
 __process_compiled_thrd_ev_enterp = __process_thrd_ev;
 __process_trpthdst_ev_enterp = __process_trpthdst_ev;
 __process_gatechg_ev_enterp = __process_gatechg_ev; 
 __process_cancel_ev_enterp = __process_cancel_ev;  
 __process_free_ev_enterp = NULL;
 __process_free_ev_pnd0_enterp = NULL;
 __process_next_ev_enterp = NULL; 

 /* pli event wrappers */
 __delay_callback_enterp = __delay_callback; 
 __process_putpdel_enterp = __process_putpdel_ev;
 __setdel_call_misctf_enterp = __setdel_call_misctf;
 __sync_call_misctf_enterp = __sync_call_misctf;
 __process_vpi_varputv_enterp = __process_vpi_varputv_ev; 
 __process_vpidrv_enterp = __process_vpidrv_ev; 
 __const_expr_has_isnums = FALSE;
 __ludptab_ndx = 0; 
 __eudptab_ndx = 0; 
 __dc_id_ndx = 0;
 __stmt_id_ndx = 0;
 __fold_for_value = -1;
 __folding_for_loop = FALSE;
  /* SJM 04-21-14 - assumes using compiler - if +interp option iact turned on */
 __no_iact = TRUE;
 __iact_state = FALSE;
 __intsig_prt_snapshot = FALSE;
 __pending_enter_iact = FALSE;
 __stop_before_sim = FALSE;
 /* this is for :reset so off (< 100) on start */
 __dbg_stop_before = 0;
 __decompile = FALSE;
 __repl_gen_dot_uline = FALSE;
 __repl_gen_dot_esc = FALSE;
 __debug_flg = FALSE;
 __mintypmax_sel = DEL_TYP;
 __sdf_mintypmax_sel = __mintypmax_sel;
 __chking_conta = FALSE;
 __rhs_isgetpat = FALSE;
 __expr_rhs_decl = FALSE;
 __chg_rng_direct = FALSE;
 __has_top_mtm = FALSE;
 __nd_0width_catel_remove = FALSE;
 __wire_array_grp = NULL; 
 __next_dvnum = 0;
 __dv_allform_insrc = FALSE;
 __st_tracing = FALSE;
 __ev_tracing = FALSE;
 __pth_tracing = FALSE;
 __dump_arrays = FALSE;
 __dump_array_cells = FALSE;
 __old_vpi_obj_after_iter_free_only = FALSE;
 /* SJM 07/13/01 - add option and get code to support src-dst MIPDs working */
 __use_impthdels = FALSE;
 __gateeater_on = FALSE;
 __prt_stats = FALSE;
 __prt_allstats = FALSE;
 /* show cancel event pulse handling all off (Verilog default inertial) */ 
 __show_cancel_e = FALSE;
 __showe_onevent = TRUE;
 __warn_cancel_e = FALSE;
 /* SJM 09-09-08 - change name of only MIPD nchg only to better name */
 __mipd_cycle_pnd0_schd = FALSE;
 /* always want to remove all 0 delay path unless turned off */
 __rm_path_pnd0s = TRUE;
 __rm_gate_pnd0s = FALSE;
 __num_rem_gate_pnd0s = 0;
 __num_flat_rem_gate_pnd0s = 0;
 __num_rem_mipds = 0;
 __dmpvars_all = FALSE;
 __toggle_coverage = FALSE; 
 /* SJM 06-30-13 - was not initializing the tgl hdr list vars */
 /* this is run both during compile time (interp) elaboration and */
 /* during cvc sim - once inited to 0 gened wrappers will keep right */
 __tgl_record_on = TRUE; 
 __toggle_chghdr = NULL; 
 __se_reset_to_untgled = FALSE;

 __tgl_verbose = FALSE;
 __wr_tgldat_on = FALSE;
 __tgldat_infils_lst_hd = __tgldat_infils_lst_end = NULL;

 __old_toggle_rpt_instance = FALSE;
 __old_toggle_rpt_bits = FALSE;
 __old_toggle_rpt_uncovered = FALSE; 
 __old_toggle_rpt_covered = FALSE;
//SJM 11-01-12 LOOKATME? - think this should be on by default - const can't tgl
 __drvn_const_as_tgled = FALSE;
 __drvn_const_rpt_concise = FALSE;
 __untgled_rpt_concise = FALSE;
 __has_tgl_optcfg_stmt = FALSE;

 __event_coverage = FALSE;
 __event_covered = NULL; 
 __stmt_covered = NULL; 
 __stmt_coverage = FALSE; 
 __stmt_coverage_tasks = FALSE;
 __same_param_must_split = FALSE;

 __force_dmp_fp = NULL;
 __has_dmpv_sys_calls = FALSE;
 /* SJM - 09-27-08 - this is design wide even though dumpports is per file */
 __has_dumpports_sys_calls = FALSE; 

 __dp_fildesc_tab = NULL;
 __dp_fildesc_nxti = 0;
 __dp_seen = FALSE;
 __dp_calltime = 0ULL;

  __is_fst = FALSE;
  __fst_repack = FALSE;
  __fst_parallel = FALSE; 
  __fst_parallel2 = FALSE; 
  __fst_ctx = NULL;
  __fst_max_work_area = 8;
  __fst_work_area = NULL;
  __fst_convert_dump2fst = FALSE; 
  __fst_work_svec = NULL;
  __fst_next_idcode = 0;
 __num_execstmts = 0;
 __num_addedexec = 0;
 /* this may get turned on for good in timformat fixup code */ 
 __nd_timstr_suf = FALSE;
 __num_glbs = 0;
 __num_uprel_glbs = 0;
 __num_dfps = __num_glbdfps = __num_locdfps = 0;
 __num_inst_pndparams = 0;
 __design_gi_arrays = FALSE;
 __design_gia_pndparams = FALSE;
 __mdlevhdr = NULL;
 __xldl_hdr = __last_xldl = NULL; 
 __xldlvtxind = NULL;
 __num_xldlvtxs = 0;
 __siz_xldlvtxtab = 0;

 /* SJM 01-17-09 - for gen now running fixup nl twice - so need to init */
 __numtopm = 0;
 __top_itab = NULL;
 __it_roots = NULL;
 __top_ipind = NULL;
 __mdlevhdr = NULL;
 __dfphdr = NULL;

 /* SJM 08/02/08 - need to init new indices to empty */
 __dsgn_mod_ndx = NULL;
 __dsgn_num_mods = 0;
 __dsgn_udp_ndx = NULL;
 __dsgn_num_mods = 0;

 __prp_mstmt_ndx = NULL;
 __last_mstndx = -1; 
 __size_prp_mstmts = -1;

 __nets_removable = __flnets_removable = 0;
 __gates_removable = __flgates_removable = 0;
 __contas_removable = __flcontas_removable = 0;
 __num_ys = 0;
 __num_inmodglbs = 0;
 __accelerate = TRUE;
 __history_on = TRUE;

 /* set compiler directive values - can be reset to these with `resetall */
 set_tfmt_dflts();
 __dflt_ntyp = N_WIRE;
 __dflt_ntyp_is_none = FALSE; 
 __in_cell_region = FALSE;
 __unconn_drive = TOK_NONE;
 __no_expand = FALSE;
 __no_specify = FALSE;
 __no_tchks = FALSE;
 __lib_are_cells = TRUE;
 __design_has_cells = FALSE;

 /* 06/22/00 - SJM - possible cross macro 2 token must start off */
 __macro_sep_width = FALSE;
 __maybe_2tok_sized_num = FALSE;
 __macro_sav_nwid = FALSE;

 __rding_comment = FALSE;
 __splitting = FALSE;
 __confunc_copying = FALSE;
 __genblk_copying = FALSE;
 __gentsk_copying = FALSE;
 __run_state = SS_COMP;
 __no_tmove_levels = INFLOOP_MAX;
 __checking_only = TRUE;
 __iasetup = FALSE;
 __ia_entered = FALSE;
 __force_active = FALSE;
 __assign_active = FALSE;
 __qcaf_dcehdr = NULL;
 __expr_has_real = FALSE; 
 __expr_has_sv_string = FALSE;

 /* need to leave these so stmt chking does not do special func body chk */
 __name_assigned_to = TRUE;
 __locfnamsyp = NULL;
 /* assume no strengths - if unc. pull, turned off before stren marking*/
 __design_no_strens = TRUE;
 __cur_dce_expr = NULL;
 __impl_evlst_hd = NULL;
 __impl_evlst_tail = NULL;
 __canbe_impl_evctrl = FALSE;

 __my_ftime(&__start_time, &__start_mstime);
 cp = ctime(&__start_time);
 strcpy(s1, cp);
 s1[24] = '\0';
 __pvdate = __pv_stralloc(s1);
 __pv_timestamp = __pv_stralloc(s1);
 __end_comp_time = 0L;
 __end_comp_mstime = 0L;
 __end_prep_time = 0L;
 __end_prep_mstime = 0L;
 /* sim time need for possible pli calls */ 
 __simtime = 0ULL;
 init_ds();

#ifdef __STREE__
 /* initialize timing tree root/min/max nodes */
 __sentinel.time = 0;
 __sentinel.color = BLACK;
 __sentinel.parent = SENTINEL;
 __sentinel.left = SENTINEL;
 __sentinel.right = SENTINEL;
 __sentinel.te_hdrp = NULL;
 __sentinel.te_endp = NULL;
 __tree_root = SENTINEL;
 __min_time_node = SENTINEL;
 __max_time_node = SENTINEL;
 /* AIV 10/31/07 - should start with a certain amount already alloced */
 /* to avoid alloc at runtime */
 /* free nodes removed from timing tree */
 __free_node_size = 2048;
 __free_nodes = (struct tqnode_t **)
  __my_malloc(__free_node_size*sizeof(struct tqnode_t *));
 /* start at one to save a + 1 for move_time free node realloc */
 __free_node_ndx = __free_node_size/2 - 1;
 for (i = 1; i < __free_node_size/2; i++) 
  {
   n = (struct tqnode_t *) __my_malloc(sizeof(struct tqnode_t));
   __free_nodes[i] = n;
  }
#else
 __heap_maxsize = HEAP_INIT_SIZE;
 __heap = (struct heap_t **) 
  __my_malloc(sizeof(struct heap_t *)*HEAP_INIT_SIZE);
 __heap_size = 1;
 hp = (struct heap_t *) __my_malloc(sizeof(struct heap_t));
 hp->hash = -1;
 hp->time = 0xffffffffffffffffULL;
 hp->te_hdrp = NULL;
 hp->te_endp = NULL;
 hp->nb_hdrp = NULL;
 hp->nb_endp = NULL;
 hp->next = NULL;
 for (i = 0; i < HEAP_INIT_SIZE; i++)
  {
   __heap[i] = hp;
  }

 __free_heap = (struct heap_t **)
  __my_malloc(__heap_maxsize*sizeof(struct heap_t *));
 /* start at one to save a + 1 for move_time free heap realloc */
 __free_heap_ndx = __heap_maxsize;
 for (i = 1; i < __heap_maxsize; i++) 
  {
   hp = (struct heap_t *) __my_malloc(sizeof(struct heap_t));
   hp->hash = -1;
   hp->time = 0xffffffffffffffffULL;
   hp->te_hdrp = NULL;
   hp->te_endp = NULL;
   hp->next = NULL;
   hp->nb_hdrp = NULL;
   hp->nb_endp = NULL;
   __free_heap[i] = hp;
  }
 for (i = 0; i < THASH_SIZE; i++)
  {
   __time_hash[i] = NULL;
  }
 __collision_count = 0;
#endif

 __execute_compiled = FALSE; 
 __design_has_ld_pli_libs = FALSE;
 __design_has_auto_task = FALSE; 
 __cvc_nd_old_gate_store = FALSE; 

 /* AIV 06/18/09 - these were never init to NULL */
 __log_olp = NULL;  
 __help_olp = NULL; 
 __quiet_olp = NULL;
 __verb_olp = NULL; 
 __verb_mem_olp = NULL; 

 __allow_scope_var = FALSE;
 __allow_scope_lsb = FALSE;
 __dpi_verbose = FALSE;
 __dpi_hdrp = NULL;
 __dpi_endp = NULL;     
 __cur_dpip = NULL;
 __can_have_array_on_rhs = FALSE; 
 __sv_lib_hdrp = NULL; 
 __sv_lib_endp = NULL;
 __max_net_blen = 0; /* maximum declared net size */
 __lhs_has_4state = FALSE;  
 __rhs_has_4state = FALSE;  
 __toggle_coverage_file_name = __pv_stralloc(DEFAULT_TOGGLE_FILE_NAME);
 __event_coverage_file_name = __pv_stralloc(DEFAULT_EVENT_FILE_NAME);
 __stmt_coverage_file_name = __pv_stralloc(DEFAULT_STMT_FILE_NAME);

 __wr_tgldat_file = __pv_stralloc(DEFAULT_TGLDAT_OUT_FILE_NAME);
 __slotend_action = 0;
 __leaf_modules_already_merged = FALSE;
 __nchg_ndx = -1;
}

/*
 * set various time format defaults
 */
static void set_tfmt_dflts(void)
{
 /* default is 1 ns. */
 __cur_units = 9;
 __cur_prec = 0;
 /* this is always set to min. of all modules (and is total) */
 __des_timeprec = 9;
 __tfmt_units = 9;
 /* next three default values required by LRM */
 __tfmt_precunits = 0;
 __tfmt_suf = __pv_stralloc("");

 /* this includes space + suffix if suffix is non empty string */
 __tfmt_minfwid = 20;    
 __des_has_timescales = FALSE;
}

/*
 * initialize data structures if needed
 */
static void init_ds(void)
{
 int32 i, len;
 word64 p, u;
 char *chp;

 /* HOME env. variable for use by tilde */
 if ((chp = (char *) getenv ("HOME")) == NULL) strcpy(__pv_homedir, ".");
 else
  {
   strcpy(__pv_homedir, chp);
   len = strlen(__pv_homedir);
   if (__pv_homedir[len - 1] == '/') __pv_homedir[len - 1] = '\0';
  }

 __blnkline = __my_malloc(RECLEN + 1);
 for (i = 0; i < OUTLINLEN; i++) __blnkline[i] = ' ';
 __blnkline[OUTLINLEN] = '\0';

 __venviron = (struct symtab_t **)
  __my_malloc(MAXLEVELS*sizeof(struct symtab_t *));
 for (i = 0; i < MAXLEVELS; i++) __venviron[i] = NULL;

 __glbsycmps = (struct sy_t **) __my_malloc(MAXGLBCOMPS*sizeof(struct sy_t *));
 __glbxcmps = (struct expr_t **)
  __my_malloc(MAXGLBCOMPS*sizeof(struct expr_t *));
 for (i = 0; i < MAXGLBCOMPS; i++)
  { __glbsycmps[i] = NULL; __glbxcmps[i] = NULL; }

 /* allocate a work table for building per module global refs */
 __grwrktab = (struct gref_t *) __my_malloc(100*sizeof(struct gref_t));
 __grwrktabsiz = 100; 
 __grwrknum = 0;

 /* SJM 08-27-11 - for new sep defparam grtab - also need dfp wrk tab */
 __rding_defparam = FALSE;
 __dfp_grwrktab = (struct gref_t *) __my_malloc(100*sizeof(struct gref_t));
 __dfp_grwrktabsiz = 100; 
 __dfp_grwrknum = 0;

 /* initialize expr. parse table and ID name/loc table */
 __exprtabsiz = 1000;
 __exprtab = (struct expr_t **)
  __my_malloc(__exprtabsiz*sizeof(struct expr_t *));
 /* need first node in case of null expr. */
 __exprtab[0] = (struct expr_t *) __my_malloc(sizeof(struct expr_t));
 for (i = 1; i < __exprtabsiz; i++) __exprtab[i] = NULL;
 __expr_is_lval = FALSE;

 __expr_idtab = (struct expridtab_t **) 
  __my_malloc(__exprtabsiz*sizeof(struct expridtab_t *));
 for (i = 0; i < __exprtabsiz; i++) __expr_idtab[i] = NULL;

 /* allocate and initialize eval stack - must grow for recursive functions */
 __maxxnest = MAXXNEST;
 __xstk = (struct xstk_t **) __my_malloc(__maxxnest*sizeof(struct xstk_t *));
 /* assume 1 work dummy size here - just need some value */
 for (i = 0; i < __maxxnest; i++)
  {
   __xstk[i] = (struct xstk_t *) __my_malloc(sizeof(struct xstk_t));
   /* this fills xstack table fields */ 
   __alloc_xsval(__xstk[i], 1);
  }
 /* notice this is dynamic nesting of recursive func. calls - must grow */ 
 __maxfcnest = MAXFCNEST;
 __fcstk = (struct task_t **)
  __my_malloc(__maxfcnest*sizeof(struct task_t *));
 for (i = 0; i < __maxfcnest; i++) __fcstk[i] = NULL;

 __nbstk = (struct st_t **) __my_malloc(MAXPRPSTNEST*sizeof(struct st_t *));
 for (i = 0; i < MAXPRPSTNEST; i++) __nbstk[i] = NULL;
 __nbsti = -1;

 /* allocate macro definition work string (it grows)*/
 __macwrklen = IDLEN;
 __macwrkstr = __my_malloc(__macwrklen);
 __mac_line_len = 0;
 __macarg_hdr = NULL;
 __macbs_flag = FALSE;

 /* allocate attribute collection work string (it grows)*/
 __attrwrklen = IDLEN;
 __attrwrkstr = __my_malloc(__attrwrklen);
 __attr_line_len = 0;
 __attr_prefix = FALSE; 

 __attrparsestrlen = IDLEN;
 __attrparsestr = __my_malloc(__attrparsestrlen);

 /* make this so big that even if IDLEN length 2 IDs still will fit */
 __xs = __my_malloc(2*IDLEN);
 __xs2 = __my_malloc(2*IDLEN);
 __wrks1 = __my_malloc(2*IDLEN);
 __wrks2 = __my_malloc(2*IDLEN);
 /* SJM 03/20/00 alloc start size for string and number assembly tokens */
 __strtoken = __my_malloc(IDLEN + 1);
 __strtok_wid = IDLEN + 1;
 __numtoken = __my_malloc(IDLEN + 1);
 __numtok_wid = IDLEN + 1;

 /* need malloc since need to be re-allocated */ 
 __acwrk = (word32 *) __my_malloc(WRDBYTES*DFLTIOWORDS);
 __bcwrk = (word32 *) __my_malloc(WRDBYTES*DFLTIOWORDS);
 __abwrkwlen = DFLTIOWORDS;
 /* to turn off number, set to TRUE but must be left in F state */
 __exprline = __my_malloc(IDLEN);
 __cur_sofs = 0;
 __exprlinelen = IDLEN;
 __force_base = BNONE;
 /* first to use is base */
 __last_veriusertf = BASE_VERIUSERTFS - 1; 
 /* SJM 07/16/02 - nee internal shdown table for dynamic pli1 boostrap ret */
 __shadow_veriusertfs = NULL;
 /* this is used as counter then added to veriuser tf last */
 __last_systf = __last_veriusertf;

 /* globals for $q_ system tasks */
 __qlist_hdr = NULL;

 /* not used until sim, but init here */
 __tfinst = NULL;
 __tfrec = NULL;
 __tfrec_hdr = __tfrec_end = NULL;
 /* lists of locationss for every registered vpi systf that has compiletf */
 __vpi_sysf_hdr = __vpi_syst_hdr = NULL;
 /* SJM 07/08/02 - now pli loads dynamic library with bootstrp func */  
 __vpi_dynlib_hd = __vpi_dynlib_end = NULL;
 __pli1_dynlib_hd = __pli1_dynlib_end = NULL;

 __siz_in_fils = MAXFILS;
 __in_fils = (char **) __my_malloc(__siz_in_fils*sizeof(char *));
 __last_lbf = 0;
 __last_srcf = 0;
 __inclst_hdr = __inclst_end = NULL;
 __vinstk = (struct vinstk_t **)
  __my_malloc(MAXFILNEST*sizeof(struct vinstk_t *));
 __vyhdr = NULL;
 __end_vy = NULL;
 __num_ylibs = __num_vlibs = 0;

 /* initialized here since built-in and define + options are added */
 __pv_defsyms = __alloc_symtab(FALSE);
 /* LOOKATME - need more than thes 6 defines */
 /* AIV 07/15/09 - macros should be cvc not cver */
 __do_macdefine("`__cvc__", "");
 __do_macdefine("`__CVC__", "");
 __do_macdefine("`__P1364__", "");
 __do_macdefine("`__p1364__", "");

 __last_lbx = -1;
 __lbexts = (char **) __my_malloc(MAXLBEXTS*sizeof(char *));
 __lbexts[0] = NULL;

 __last_incdir = -1;
 __incdirs = (char **) __my_malloc(MAXINCDIRS*sizeof(char *));
 __incdirs[0] = NULL;

 __undefhd = __undeftail = NULL;
 __undef_mods = 0;

 __wsupptab = (word32 *) __my_malloc(MAXWSWRDS*sizeof(word32));
 for (i = 0; i < MAXWSWRDS; i++) __wsupptab[i] = 0L;
 __in_ifdef_level = 0;
 /* SJM 08-05-09 - now have a different have t ignore state for each level */ 
 for (i = 0; i < MAXLEVELS; i++) __have_t_ignore_elsif[i] = FALSE;
 __ifdef_skipping = FALSE;
 __processing_func = FALSE;
 __first_num_eol = FALSE;
 __rding_top_level = TRUE;

 __itstk = (struct itree_t **)
  __my_malloc((MAXITDPTH + 1)*sizeof(struct itree_t *));
 for (i = 0; i <= MAXITDPTH; i++) __itstk[i] = NULL;
 __itstk[0] = (struct itree_t *) ALL1W;
 __itstk = &(__itstk[1]);

 __xspi = __itspi = __fcspi = -1;
 __inst_ptr = NULL;
 __inst_mod = NULL;
 __idp = NULL; 
 /* change to test different udp reps. */
 __ualtrepipnum = UALTREPIPNUM;
 /* DBG all wide __ualtrepipnum = 1; */ 

 /* filled when used */
 __wcardtab = (struct wcard_t *)
  __my_malloc((MAXUPRTS + 1)*sizeof(struct wcard_t));

 __prpstk = (struct st_t **) __my_malloc(MAXPRPSTNEST*sizeof(struct st_t *));
 for (i = 0; i < MAXPRPSTNEST; i++) __prpstk[i] = NULL;

 __tmpitp_freelst = NULL;
 __tmpip_freelst = NULL;
 
 __last_libmdp = NULL;

 /* SJM 01/27/04 - initializing global seed for $random and other dist */
 /* systfs in case uses omits the seed inout arg */ 
 /* guessing that 0 will match 2001 LRM rand generator standard */
 __seed = 0;

 __init_seed = 0;

 __dv_fnam = __pv_stralloc(DFLTDVFNAM);
 __dv_fd = -1;
 __dv_file_size = 0;
 __dv_buffer = NULL;
 __dv_nxti = 0;

 /* BEWARE - since this table reallocated for cgen access must index */
 /* not use address ptr because when reallated to grow ptr will be wrong */
 /* do not need to initialize because freed and reused where init needed */
 __tevtab = (struct tev_t *) 
  __my_malloc(TEVTAB_ALLOC_SIZE*sizeof(struct tev_t));

 /* AIV 10/31/07 - should start with a certain amount already alloced */
 __free_tev_size = 2048;
 __free_tevs = (struct tev_t **)
  __my_malloc(__free_tev_size*sizeof(struct tev_t *));
 /* start at one to save a + 1 for move_time free node realloc */
 __free_tev_ndx = __free_tev_size/2 - 1;
 __free_tevs[0] = NULL;
 for (i = 1; i < __free_tev_size/2; i++) 
  {
   __free_tevs[i] = (struct tev_t *) __my_malloc(sizeof(struct tev_t));
  }
 
 /* pre-allocate design wide constant table and set some fixed values */
 __setup_contab();

 /* least first one unused */
 __numused_tevtab = 0; 

 if (__compiled_sim)
  {
   __free_event_tevp = __alloc_cur_tev(__process_free_ev_enterp, 0);  
 
   /* freed nchglst structs may not be alloc in the compiler */
   __nchg_free_size = 2048;
   __nchg_freed = (struct nchglst_t **)
    __my_malloc(__nchg_free_size*sizeof(struct nchglst_t *));
   /* start at one to save a + 1 for move_time free node realloc */
   __nchg_free_ndx = __nchg_free_size/2 - 1;
   __nchg_freed[0] = NULL;
   for (i = 1; i < __nchg_free_size/2; i++) 
    {
     __nchg_freed[i] = 
      (struct nchglst_t *) __my_malloc(sizeof(struct nchglst_t));
    }
  }

 /* need to set tev list empty because need to allocate for action cbs */
 /* this makes sure at start event table empty */
 __tefreelstp = NULL;

 /* set ticks long structs - 16 (built into lang.) by word64 values */
 __itoticks_tab[0] = 1ULL;
 u = 10ULL;
 for (i = 1; i < 16; i++) 
  {
   p = u *__itoticks_tab[i - 1];
   __itoticks_tab[i] = p;
  }
 __tim_zero = 0ULL;
 /* initialize multichannel descriptor table */
 /* notice on reset will be overwritten */
 /* SJM 03/26/00 - 32 is unusable for new Verilog 2000 file I/O but */
 /* init here so wil show as not open */
 for (i = 2; i < 32; i++)
  {
   __mulchan_tab[i].mc_s = NULL;
   __mulchan_tab[i].mc_fnam = NULL;
  }
 /* desc. 0 is hardwired as stdout and 1 to stderr */
 __mulchan_tab[0].mc_s = stdout;
 __mulchan_tab[0].mc_fnam = __pv_stralloc("stdout"); 
 __mulchan_tab[1].mc_s = stderr;
 __mulchan_tab[1].mc_fnam = __pv_stralloc("stderr"); 

 /* AIV 09/05/03 - initialization code for new P1364 2001 fileio streams */
 /* SJM 09/05/03 - rewrote to match mulchan I/O program organization */

 /* use first free with closing and freeing algorithm per Unix and mcds */
 /* SJM 05/17/04 - LOOKATME - stdio.h 16 value is wrong - trying 1024 */ 
 __fio_fdtab = (struct fiofd_t **)
  __my_malloc(MY_FOPEN_MAX*sizeof(struct fiofd_t *));

 for (i = 0; i < MY_FOPEN_MAX; i++) __fio_fdtab[i] = NULL; 

 /* numbers probably same as unix but LRM requires predefined 0,1,2 */
 __fio_fdtab[0] = (struct fiofd_t *) __my_malloc(sizeof(struct fiofd_t));
 __fio_fdtab[0]->fd_error = FALSE;
 /* name only needed for user opened in case stdio fopen fails */
 __fio_fdtab[0]->fd_name = __pv_stralloc("stdin"); 
 __fio_fdtab[0]->fd_s = stdin;

 __fio_fdtab[1] = (struct fiofd_t *) __my_malloc(sizeof(struct fiofd_t));
 __fio_fdtab[1]->fd_error = FALSE;
 __fio_fdtab[1]->fd_name = __pv_stralloc("stdout"); 
 __fio_fdtab[1]->fd_s = stdout;

 __fio_fdtab[2] = (struct fiofd_t *) __my_malloc(sizeof(struct fiofd_t));
 __fio_fdtab[2]->fd_error = FALSE;
 __fio_fdtab[2]->fd_name = __pv_stralloc("stdout"); 
 __fio_fdtab[2]->fd_s = stdout;

 __fiolp = NULL;
 __fiofp = NULL;
 __scanf_pos = -1;

 /* start with no array for ncomp elements */
 __ncablk_nxti = -1;
 __hdr_ncablks =  NULL;
 __cpblk_nxti = -1;
 __hdr_cpblks = NULL;
 __cppblk_nxti = -1;
 __hdr_cppblks = NULL;
 __tnblk_nxti = -1;
 __hdr_tnblks = NULL;

 /* initialize the vpi_ variables - reset must leave */
 /* AIV 04/12/07 - BEWARE - keeping old method which is used to save */
 /* one integer from a vpi handle for freeing list */
 __vpi_hfree_hdr = NULL;
 __vpi_hrecfree_hdr = NULL;
 __have_vpi_actions = FALSE;
 __have_vpi_gateout_cbs = FALSE; 
 /* normal mode is not free iterator handles unless user does explicitly */
 __wrkval_buflen = 0;

 __num_vpi_force_cbs = 0;
 __vpi_force_cb_always = FALSE;
 __vpi_rel_cb_always = FALSE;
 __num_vpi_rel_cbs = 0;
 /* SJM 07/24/00 - add flag so no all force/rel vc reentry - off until call */
 __allforce_cbs_off = FALSE;
 __allrel_cbs_off = FALSE;

 __vpi_cbrec_hdr = NULL;
 __errorcb_suppress_msg = FALSE;
 /* debugging values - set when vpi dump obj routine called */
 __cur_vpi_inst = NULL;
 __cur_vpi_obj = NULL;
 __cbvc_causing_dcep = NULL;
 __in_vpi_errorcb = FALSE;
 __acc_vpi_erroff = FALSE;
 __ithtsiz = 0;
 __ithptab = NULL;
 __ithtsiz2 = 0;
 __ithptab2 = NULL;

 __vpicb_tehdri = (struct tev_t **)
  __my_malloc((TOPVPIVAL + 1)*sizeof(struct tev_t *));
 __vpicb_teendi = (struct tev_t **)
  __my_malloc((TOPVPIVAL + 1)*sizeof(struct tev_t *));
 for (i = 0; i <= TOPVPIVAL; i++)
  __vpicb_tehdri[i] = __vpicb_teendi[i] = NULL;

 __rosync_slot = FALSE;
 __tehdr_rosyncp = __teend_rosyncp = NULL;
 __vpifnam_ind = 0;
 __vpilin_cnt = 0;

 /* must allocate first block */
 __hdr_cpnblks = (struct cpnblk_t *) __my_malloc(sizeof(struct cpnblk_t));
 __hdr_cpnblks->cpnblknxt = NULL;
 __hdr_cpnblks->cpnblks = __hdr_cpnblks->cpn_start_sp 
  = __my_malloc(BIG_ALLOC_SIZE);
 __hdr_cpnblks->cpn_end_sp = __hdr_cpnblks->cpn_start_sp + BIG_ALLOC_SIZE - 16;

 /* reading automatic task flag init to false */
 __rd_auto_task = FALSE;
 /* loop continue/break globals */
 __rd_loop = FALSE;
 __rd_continue = FALSE;
 __rd_break = FALSE;
 __rd_always_ff = FALSE;
 __st_loop_continue = NULL; 
 __st_loop_break = NULL;   

 /* init init from .tgldat file variables */
 __tglbits01 = __tglbits10 = NULL;
 __siz_tgl_lst = -1;
 __tgl_rtpthnam = NULL;
 __tgl_modnam = NULL;
 __siz_tgl_rtpthnam = -1;
 __tgl01tab = NULL;
 __tgl10tab = NULL;
 __siz_tgltabs = -1;
 __tgl_r1 = __tgl_r2 = -1;
}

/*
 * OPTION AND COMMAND FILE ARGUMENT PROCESSING ROUTINES
 */

/* these must be positive word32 up to 16 bit values - gaps ok */
#define CO_HELP 1
#define CO_F 2
#define CO_LOG 3
#define CO_KEY 4
#define CO_IAINPUT 5
#define CO_VERB 6
#define CO_QUIET 7
#define CO_MAXERRS 8
#define CO_C 9
#define CO_PARSEONLY 10
#define CO_D 11
#define CO_A 12
#define CO_AOFF 13
#define CO_X 14
#define CO_STOP 15
#define CO_E 16
#define CO_W 17
#define CO_INFORM 18
#define CO_UC 19
#define CO_V 20
#define CO_Y 21
#define CO_LBVERB 22
#define CO_LIBORD 23
#define CO_LIBRESCAN 24
#define CO_LIBNOHIDE 25
#define CO_DEBUG 26
#define CO_MINDEL 27
#define CO_TYPDEL 28
#define CO_MAXDEL 29
/* options than need to be changed to system tasks */
/* also $cleartrace here */
#define CO_SETTRACE 30 
#define CO_SETEVTRACE 31
#define CO_SETPTHTRACE 32
#define CO_TRACEFILE 33
/* this uses assumed lengths - if change option name must change consts */
/* also not in normal table */
#define CO_LBEXT 34
#define CO_SUPPWARNS 35
#define CO_DEFINE 36
#define CO_INCDIR 37
#define CO_GATE_EATER 38
#define CO_NO_GATE_EATER 39
#define CO_PRTSTATS 40
#define CO_PRTALLSTATS 41
#define CO_SPIKEANAL 42
#define CO_SDFANNOTATE 43
#define CO_SDFVERB 44
#define CO_SDF_DURING_SIM 45 
#define CO_NOIACT 46
#define CO_NOSPFY 47
#define CO_NOTCHKS 48
#define CO_LIBNOCELL 49
#define CO_IGNORE_SDF_IOPATH_EDGES 50

#define CO_SHOWCANCELE 53
#define CO_NOSHOWCANCELE 54
#define CO_PULSEX_ONEVENTE 55
#define CO_PULSEX_ONDETECT 56
#define CO_WARNCANCELE 57
#define CO_NOWARNCANCELE 58
#define CO_MIPD_CYCLE_PND0_SCHD 59
#define CO_RMGATEPND0S 60
#define CO_NORMPTHPND0S 61
#define CO_NOKEEPCOMMANDS 62
#define CO_PLIKEEPSRC 63
#define CO_SNAPSHOT 64
#define CO_FRSPICE 65
#define CO_SWITCHVERB 66
#define CO_CHG_PORTDIR 67
#define CO_SCHD_ALW_FIRST 68
#define CO_NB_NOSEP_QUEUE 69
#define CO_SDF_LOG 70
#define CO_SDF_NO_ERRS 71
#define CO_SDF_NO_WARNS 72
#define CO_LOADPLI1 73
#define CO_LOADVPI 74
#define CO_DPI_SVLIB 75
/* SJM 02-11-13 - need to trace dpi sv lib routines since not finding */
#define CO_DPIVERB 76
#define CO_LIBLIST 77
#define CO_LIBMAP 78
#define CO_D_ULINE 79
#define CO_D_ESC 80
#define CO_DMP_ARRAYS 81
#define CO_DMP_ARRAY_CELLS 82
#define CO_SV_PARSE 83
#define CO_SV_PARSE2 84
#define CO_DPI_WR_HDRS 85
#define CO_OPTCFGFIL 86
#define CO_TOGGLE 87
#define CO_TOGGLE_FILE 88
#define CO_TOGGLE_REPORT_INSTANCE 89
#define CO_TOGGLE_REPORT_BITS 90
#define CO_TOGGLE_UNCOVERED 91
#define CO_TOGGLE_COVERED 92
#define CO_DRVN_CONST_AS_TGL 93
#define CO_DRVN_CONST_RPT_CONCISE 94 
#define CO_UNTGL_RPT_CONCISE 95
#define CO_WRITE_TGLDAT 96
#define CO_WRITE_TGLDAT_FILE 97 
#define CO_SET_TGLED_FROM_FILE 98 
#define CO_TGLVERBOSE 99

#define CO_EVENT_COVERAGE 100
#define CO_EVENT_COVERAGE_FILE 101
#define CO_STMT_COVERAGE 102
#define CO_STMT_TASKS_COVERAGE 103
#define CO_STMT_COVERAGE_FILE 104
#define CO_OVERRIDE_CHANGE 105
#define CO_SAME_PARAM_MUST_SPLIT 106
#define CO_RANDOM 107
#define CO_RANDOM_SEED 108
#define CO_RANDOM_2STATE 109
#define CO_RANDOM_2STATE_SEED 110

#define CO_INTERPRETER 111
#define CO_COMPILE 112
#define CO_ACC 113
#define CO_ACC_NO_NUM 114
#define CO_COMPILED_OPT_SIM 115
#define CO_COMPILED_OPT_SIM_GATE 116
#define CO_EXECUTE 117
#define CO_TWO_STATE 118
#define CO_TWO_STATE_NO_WIRE 119
#define CO_PIPE 120
#ifdef __XPROP__
#define CO_XPROP 121
#define CO_XPROP2 122
#define CO_XPROP_TRACE 123
#define CO_XPROP_TRACE_SUPPRESS 124
#define CO_XPROP_TRACE_MAX 125
#define CO_XPROP_AND_OR 126
#define CO_XPROP_EXCLUDED 127
#define CO_XPROP_NO_EDGES 128
#define CO_XPROP_NO_VECTORED_EDGES 129
#define CO_XPROP_ONLY_EDGES 130
#endif
#define CO_NBAOPT 131
#define CO_UNROLL_LOOPS 132
#define CO_OLD_VPI_AFTER_ITER_FREE 133
#ifndef __CVC32__
#define CO_LARGE_MODEL 134
#endif
#define CO_DMP_VARS 135
#define CO_FST_DUMP2FST 139
#define CO_FST_VARS 140
#define CO_FST_VARS_REPACK 141
#define CO_FST_PARALLEL 142
#define CO_FST_PARALLEL2 143

#define CO_OPT_LEVEL_2 144
#define CO_OPT_DEBUG 145
#define CO_CVC_STATS 146
#define CO_DMP_FLOWG 147
#define CO_SHOW_ASM 148
#define CO_ASM_EMIT_LOC 149
#define CO_OPT_BLOCK_TRACE 150
#define CO_ASM_VAR_NAMES 151
#define CO_OPT_VALTRK 152
#define CO_TRK_VERBOSE 153
#define CO_USE_INTERP_DPI_MK 154
#define CO_PWD_TMP 155
#define CO_REAL_WARNS 156
#define CO_VERB_MEM 157
//SJM 11-07-12 - when fixed remove this or move to only debug release
#define CO_NCHG_TRACE 158
#define CO_USEDIR 160

/* command line option table */
/* this does not need to be alphabetical */
/* single token but parsed options not here */
static struct namlst_t cmdopts[] = {
 { CO_HELP, "-h" },
 { CO_HELP, "-H" },
 { CO_HELP,  "-?" },
 { CO_F , "-f" },
 { CO_LOG, "-l" },
 { CO_SDF_LOG, "+sdf_log_file" },
 { CO_KEY, "-k" },
 { CO_IAINPUT, "-i" },
 { CO_VERB, "+verbose" },
 { CO_QUIET, "-q" },
 { CO_MAXERRS, "+maxerrors" },
 { CO_C, "-c" },
 { CO_PARSEONLY, "+parseonly" },
 { CO_D, "-d" },
 { CO_D_ULINE, "-d_gen_uline" },
 { CO_D_ESC, "-d_gen_esc" },
 { CO_DMP_ARRAYS, "+dump_arrays" },
 { CO_DMP_ARRAY_CELLS, "+dump_array_cells" },
 { CO_A, "-a" }, 
 { CO_AOFF, "-aoff" },
 { CO_X, "-x" }, 
 { CO_STOP,  "-s" },
 { CO_E , "-e" },
 { CO_W , "-w" },
 { CO_INFORM,  "-informs" },
 { CO_UC, "-u"},
 { CO_V, "-v" },
 { CO_Y, "-y" },
 { CO_LBVERB, "+libverbose" },
 { CO_LIBORD, "+liborder" },
 { CO_LIBRESCAN, "+librescan" },
 { CO_LIBNOHIDE, "+libnohide" },
 { CO_DEBUG, "+debug" },
 { CO_MINDEL, "+mindelays" },
 { CO_TYPDEL , "+typdelays" },
 { CO_MAXDEL , "+maxdelays" },
 { CO_SETTRACE, "-t" },
 { CO_SETEVTRACE, "-et" },
 { CO_SETPTHTRACE, "-pt" },
 { CO_TRACEFILE, "+tracefile" },
 { CO_NO_GATE_EATER, "+nogateeater" },
 { CO_GATE_EATER, "+gateeater" },
 { CO_PRTSTATS, "+printstats" },
 { CO_PRTALLSTATS, "+printallstats" },
 { CO_SDFANNOTATE, "+sdfannotate" },  
 { CO_SDFANNOTATE, "+sdf_annotate" },  
 { CO_SDFVERB, "+sdfverbose" },
 { CO_SDFVERB, "+sdf_verbose" },
 { CO_IGNORE_SDF_IOPATH_EDGES, "+ignore_sdf_iopath_edges"},
 { CO_SDF_DURING_SIM, "+sdf_during_sim" },
 { CO_NOIACT, "+nointeractive" },
 { CO_NOSPFY, "+nospecify" },
 { CO_NOTCHKS, "+notimingchecks" },
 { CO_NOTCHKS, "+notimingcheck" },
 { CO_LIBNOCELL, "+libnocell" },
 { CO_NCHG_TRACE, "+nchg_trace" },
 { CO_SPIKEANAL, "+spikes" },
 { CO_SHOWCANCELE, "+show_canceled_e" },
 { CO_NOSHOWCANCELE, "+noshow_canceled_e" },
 { CO_PULSEX_ONEVENTE, "+pulse_e_style_onevent" },
 { CO_PULSEX_ONDETECT, "+pulse_e_style_ondetect" },
 { CO_WARNCANCELE, "+warn_canceled_e" },
 { CO_NOWARNCANCELE, "+nowarn_canceled_e" },
 { CO_MIPD_CYCLE_PND0_SCHD, "+mipdopt" },
 { CO_RMGATEPND0S, "+remove_gate_0delays" },
 { CO_NORMPTHPND0S, "+noremove_path_0delays" },
 { CO_NOKEEPCOMMANDS, "+nokeepcommands" },
 { CO_INTERPRETER, "+interp" },
 { CO_COMPILE, "-o" },
 { CO_COMPILED_OPT_SIM, "-O" },
 { CO_COMPILED_OPT_SIM_GATE, "-Ogate" },
 { CO_ACC_NO_NUM, "+acc" },
 { CO_EXECUTE, "+exe" },
 { CO_TWO_STATE, "+2state" },
 { CO_TWO_STATE_NO_WIRE, "+2state_no_wires" },
 { CO_PIPE, "-pipe" },
#ifdef __XPROP__
 { CO_XPROP, "+xprop"},
 { CO_XPROP2, "+xprop2"},
 { CO_XPROP_TRACE, "+xtrace"},
 { CO_XPROP_TRACE_SUPPRESS, "+xtrace_suppress"},
 { CO_XPROP_AND_OR, "+xprop_eval"},
 { CO_XPROP_EXCLUDED, "+xprop_excluded"}, 
 { CO_XPROP_NO_EDGES, "+no_xedges"}, 
 { CO_XPROP_NO_VECTORED_EDGES, "+no_vector_xedges"}, 
 { CO_XPROP_ONLY_EDGES, "+only_pos_neg_xedges"}, 
#endif
 { CO_OLD_VPI_AFTER_ITER_FREE, "+old_vpi_after_iter_free" },
 { CO_NBAOPT, "+nbaopt"},
 { CO_UNROLL_LOOPS, "+unroll_loops"},
 { CO_DMP_VARS, "+dumpvars"},
 { CO_VERB_MEM, "+verbosemem" },
 { CO_PWD_TMP, "+work" },
 { CO_REAL_WARNS, "+realwarns" },
#ifndef __CVC32__
 { CO_LARGE_MODEL, "+large" },
#endif
 { CO_FST_DUMP2FST, "+dump2fst"},
 { CO_FST_VARS, "+fstvars"},
 { CO_FST_VARS_REPACK, "+fstvars_repack"},
 { CO_FST_PARALLEL, "+fst+parallel=on"}, 
 { CO_FST_PARALLEL2, "+fst+parallel2=on"}, 
 /* SJM 04-25-14 - these are for debugging output asm code - to prevent */
 /* .s asm file gen comment out argument options to turn them on - these */
 /* then are just unused */ 
 { CO_OPT_LEVEL_2, "-O2" }, 
 { CO_OPT_DEBUG, "+Odebug" },
 { CO_OPT_BLOCK_TRACE, "+Oblktrace" },
 { CO_OPT_VALTRK, "+Ovaltrack" },
 { CO_TRK_VERBOSE, "+opt_trk_verbose" },
 { CO_ASM_VAR_NAMES, "+asm_var_names" },
 { CO_CVC_STATS, "+Ostats" },
 { CO_DMP_FLOWG, "+dumpfg"},
 { CO_SHOW_ASM, "+show_asm" },
 { CO_ASM_EMIT_LOC, "+asm_emit_loc" },
 { CO_USE_INTERP_DPI_MK, "+dpi_interp_use_mk" },
 { CO_SNAPSHOT, "+snapshot" },
 { CO_FRSPICE, "+fromspice" },
 { CO_SWITCHVERB, "+switchverbose" },
 { CO_CHG_PORTDIR, "+change_port_type" },
 { CO_SCHD_ALW_FIRST, "+sched_always_first" },
 { CO_NB_NOSEP_QUEUE, "+no_separate_nb_queue" },
 { CO_SDF_NO_ERRS, "+sdf_noerrors" },
 { CO_SDF_NO_WARNS, "+sdf_nowarns" },
 { CO_LIBLIST, "-L"},
 { CO_LIBMAP, "+config"},
 { CO_DPI_SVLIB, "-sv_lib" },
 { CO_DPIVERB, "+dpiverbose" },
 { CO_DPI_WR_HDRS, "+write_dpi_hdrs" },
 { CO_SV_PARSE, "-sv" },
 { CO_SV_PARSE2, "-sverilog" },
 { CO_OPTCFGFIL, "-optconfigfile" },
 { CO_TOGGLE, "-toggle" },
 { CO_TOGGLE_FILE, "-toggle_file" },
 { CO_TOGGLE_REPORT_INSTANCE, "-ti" },
 { CO_TOGGLE_REPORT_BITS, "-tb" },
 { CO_TOGGLE_UNCOVERED, "-tu" },
 { CO_TOGGLE_COVERED, "-tc" },
 { CO_EVENT_COVERAGE, "-event_coverage"}, 
 { CO_EVENT_COVERAGE_FILE, "-event_coverage_file"},
 { CO_STMT_COVERAGE, "-stmt_coverage"}, 
 { CO_STMT_TASKS_COVERAGE, "-stmt_tasks"}, 
 { CO_STMT_COVERAGE_FILE, "-stmt_coverage_file"},
 /* SJM 04-20-13 - these are the new options */ 
 { CO_DRVN_CONST_AS_TGL, "-mark_driven_const_wires_toggled" },
 { CO_DRVN_CONST_RPT_CONCISE, "-driven_const_report_concise"},
 { CO_UNTGL_RPT_CONCISE, "-untoggled_report_concise" },
 { CO_WRITE_TGLDAT, "-write_toggle_data" }, 
 { CO_WRITE_TGLDAT_FILE, "-write_toggle_data_file" },
 { CO_SET_TGLED_FROM_FILE, "-set_toggled_from_file" },
 { CO_TGLVERBOSE, "-toggle_verbose" },
 { CO_OVERRIDE_CHANGE, "-override_model_change"},
 { CO_SAME_PARAM_MUST_SPLIT, "+same_param_must_split" },
 { CO_RANDOM, "+random" },
 { CO_RANDOM_2STATE, "+random_2state" }
};
#define NCMDOPTS (sizeof(cmdopts) / sizeof(struct namlst_t))

/*
 * build command option linked list
 *
 * only fatal errors here since still no log file
 */
static void xpnd_args(int32 argc, char **argv)
{
 int32 i, oi;
 struct optlst_t *olp;
 char *chp;

#ifdef __CVC_RT__
 /* AIV 03/26/09 - new method allows only +TEST= for testvars command line */
 /* user defined args to be passed */
 /* first used fixed argc/argv from compile time arguments - then add */
 /* passed arguments from the compiled command line */
 int32 orig_argc, ondx; 
 char **orig_argv;

 orig_argc = -1;
 orig_argv = NULL;
 orig_argc = argc;
 orig_argv = argv;
 argc = __gbl_argc;
 argv = __gbl_argv;
#endif

 /* first convert arg list to option list */
 /* know argv[0] is name of program */
 /* for command args "file" name is [arg] and lin cnt is arg. no. */
 /* 0 is [arg] and later none, and 1 is stdin */
 __opt_hdr = __opt_end = NULL;
 __last_inf = -1;
 __add_infil("[args]");
 __cur_fnam = __in_fils[__last_inf];
 /* for command number, location indicator - literal index for this */
 __add_infil("CMD");
 __cmd_ifi = __last_inf;

 for (olp = NULL, i = 1; i < argc; i++)
  {
   if ((int32) strlen(argv[i]) >= IDLEN - 1)
    {
     __lin_cnt = i;
     __pv_ferr(919, "command argument too long (%d) - ignored", IDLEN - 1);
     continue;
    }
   olp = alloc_optlst();
   if (__opt_end == NULL) __opt_hdr = __opt_end = olp;
   else { __opt_end->optlnxt = olp; __opt_end = olp; }
   olp->opt = __pv_stralloc(argv[i]);
   /* level is 0 for top */
   olp->optlev = 0;
   /* this must be index of args */
   olp->optfnam_ind = 0;
   olp->optlin_cnt = i;
  }

#ifdef __CVC_RT__
 /* now add the compiled executables command line options */
 /* not allowing any arguments except user defined +TEST= */
 ondx = i;
 for (olp = NULL, i = 1; i < orig_argc; i++)
  {
   if ((int32) strlen(orig_argv[i]) >= IDLEN - 1)
    {
     __lin_cnt = ondx+i;
     __pv_ferr(919, "command argument too long (%d) - ignored", IDLEN - 1);
     continue;
    }
   olp = alloc_optlst();
    
   if (__opt_end == NULL) __opt_hdr = __opt_end = olp;
   else { __opt_end->optlnxt = olp; __opt_end = olp; }
   olp->opt = __pv_stralloc(orig_argv[i]);
   chp = olp->opt;
   if (*chp == '+' || *chp == '-')
    {
     oi = find_opt(chp);
     /* better be -1 for the undefined - otherwise force a recompile */
     /* AIV LOOKATME - could check for other allowed commands here */
     if (oi != -1) 
      {
       __pv_ferr(1480, "Option (%s) not allowed for compiled design - recompile with desired options.\n", chp);
       __my_exit(2, TRUE);
      }
    }

   /* level is 0 for top */
   olp->optlev = 0;
   /* this must be index of args */
   olp->optfnam_ind = 0;
   olp->optlin_cnt = ondx;
   ondx++;
  }
#endif

 /* repeatedly pass through list and expand good -fs */
 copy_xpnd_onelev_args();
 /* DBG --- notice no debug flag at this point ---
 dmp_xpnd_olist(__opt_hdr);
 --- */

 /* final step sets some pointers for special options into tab */
 for (olp = __opt_hdr; olp != NULL; olp = olp->optlnxt)
  {
   chp = olp->opt;
   if (olp->is_bmark || olp->is_emark) continue;

   if (*chp == '+' || *chp == '-')
    {
     oi = find_opt(chp);
     olp->optnum = oi;
     /* notice - algorithm is to use last if repeated */
     switch (oi) {
      case CO_LOG: __log_olp = olp; break;   
      case CO_HELP: __help_olp = olp; break;
      case CO_QUIET: __quiet_olp = olp; break;
      case CO_VERB: __verb_olp = olp; break;
      case CO_VERB_MEM: __verb_mem_olp = olp; break;
     }
    }
  }
}

/*
 * allocate and initialize an option list element
 */
static struct optlst_t *alloc_optlst(void)
{
 struct optlst_t *olp;

 olp = (struct optlst_t *) __my_malloc(sizeof(struct optlst_t)); 
 olp->opt = NULL;
 olp->optnum = 0;
 olp->optlev = 0;
 olp->is_bmark = FALSE;
 olp->is_emark = FALSE;
 olp->is_argv = FALSE;
 olp->argv_done = FALSE;
 olp->optfnam_ind = 0;
 olp->optlin_cnt = -1;
 olp->optlnxt = NULL;
 return(olp);
}

/*
 * copy from 1 level from hdr liast to new list
 */
static void copy_xpnd_onelev_args(void)
{
 int32 savlast_inf, savlin_cnt, some_expanded, lev;
 struct optlst_t *olp, *olp2, *new_olp;
 FILE *opt_s;
 char s1[IDLEN];
 char *chp;

 __new_opt_end = __new_opt_hdr = NULL;
 for (lev = 1;; lev++)
  {
   some_expanded = FALSE;
   for (olp = __opt_hdr; olp != NULL;) 
    {
     /* anything but -f just remains in list */
     /* optnum only CO_F if previous error */
     if (olp->is_bmark || olp->is_emark
       || strcmp(olp->opt, "-f") != 0 || olp->optnum == CO_F)
      {
       olp2 = olp->optlnxt;
       if (__new_opt_end == NULL) __new_opt_hdr = __new_opt_end = olp;
       else { __new_opt_end->optlnxt = olp; __new_opt_end = olp; }
       olp->optlnxt = NULL;
       olp = olp2;
       continue;
      } 
     /* logic to possibly (if can be opened) a -f [file] element */
     olp2 = olp->optlnxt; 

     if (olp2 == NULL) { olp->optnum = CO_F; break; }
     chp = olp2->opt;

     /* if cannot open, or not followed by file name, leave - error later */
     /* but leave both -f and [arg] but move 1 past arg */
     if (chp == NULL || *chp == '+' || *chp == '-'
      || (opt_s = __tilde_fopen(chp, "r")) == NULL)
      {
       olp->optnum = CO_F;
       if (__new_opt_end == NULL) __new_opt_hdr = __new_opt_end = olp;
       else { __new_opt_end->optlnxt = olp; __new_opt_end = olp; }
       __new_opt_end->optlnxt = olp2;
       __new_opt_end = olp2;
       olp = olp2->optlnxt;
       olp2->optlnxt = NULL;
       continue;
      }

     /* move olp one past -f and [file name] */
     olp = olp2->optlnxt;
     __add_infil(chp);   
     __cur_fnam = __in_fils[__last_inf];
     savlin_cnt =  __lin_cnt;
     savlast_inf = __last_inf;
     __lin_cnt = 1;

     /* add beginning marker */
     ins_optlst_marker(TRUE, lev);
     /* fill a new option list */
     for (;;)
      {
       if ((__toktyp = __get_cmdtok(opt_s)) == TEOF) break;

       new_olp = alloc_optlst();
       if (__new_opt_end == NULL) __new_opt_hdr = __new_opt_end = new_olp;
       else { __new_opt_end->optlnxt = new_olp; __new_opt_end = new_olp; }

       /* AIV 12/07/10 - now supporint expanding of $ENV variables in -f file */
       try_to_expand_environment_var(s1, __token);
       new_olp->opt = __pv_stralloc(s1);
       new_olp->optlev = lev;
       new_olp->optfnam_ind = __last_inf;
       new_olp->optlin_cnt = __lin_cnt;
       some_expanded = TRUE;
      }
     /* add end marker */
     ins_optlst_marker(FALSE, lev);
     __my_fclose(opt_s); 
     __cur_fnam = __in_fils[savlast_inf];
     __lin_cnt = savlin_cnt;
    }
   /* DBG --- no debug flag at this point ---
   dmp_xpnd_olist(__new_opt_hdr);
   --- */
   __opt_hdr = __new_opt_hdr;
   __opt_end = __new_opt_end;
   if (!some_expanded) break;
   __new_opt_hdr = __new_opt_end = NULL;
  } 
 /* DBG remove --- no debug flag at this point ---
 dmp_xpnd_olist(__opt_hdr);
 --- */
}

/*
 * expand a token which may or may not contain an environment variable
 * if a $ is found may be an environment variable - search for every char
 * left in the token
 */
static void try_to_expand_environment_var(char *s1, char *token)
{
 int32 slen, ci, slen2, si;
 char *tokp, *tokp2, *chp;
 char s2[IDLEN];

 tokp = token;
 for (ci = 0; *tokp != '\0'; tokp++, ci++)
  {
   /* might be an environment variable */
   if (*tokp == '$')
    {
     tokp++;
     si = ci;
     /* search all remaining combinations of remaining string */
     for (tokp2 = tokp; ; tokp2++)
      {
       /* make string */
       slen = tokp2-tokp;
       if (slen == 0) continue;
       strncpy(s2, tokp, slen);
       s2[slen] = '\0';
       /* check if it is an env variable */
       if ((chp = (char *) getenv (s2)) != NULL) 
        {
         slen2 =  strlen(chp);
         strncpy(&(s1[ci]), chp, slen2);
         ci += (slen2-1);
         /* AIV 12/23/10 - this was off by one char need -1 */
         tokp += (slen-1);
         break;
        }
       if (*tokp2 == '\0') break;
      }
     /* if ci == si - none was found - add char */
     if (ci == si) 
      {
       tokp--;
       s1[ci] = *tokp;
      }
    }
   /* make string as normal */
   else s1[ci] = *tokp;
  }
 s1[ci] = '\0';
}

/*
 * insert a marker
 */
static void ins_optlst_marker(int32 is_bmark, int32 lev)
{
 struct optlst_t *new_olp;
 
 /* this also initializes */
 new_olp = alloc_optlst();
 if (__new_opt_end == NULL) __new_opt_hdr = __new_opt_end = new_olp;
 else { __new_opt_end->optlnxt = new_olp; __new_opt_end = new_olp; }
 /* must not be seen as input file */
 new_olp->optnum = -2;
 if (is_bmark) new_olp->is_bmark = TRUE;
 else new_olp->is_emark = TRUE;
 new_olp->optlev = lev;
 new_olp->optfnam_ind = __last_inf;
 new_olp->optlin_cnt = __lin_cnt;
}

/*
 * dump expanded option list
 */
static void dmp_xpnd_olist(struct optlst_t *olp)
{
 int32 olnum;

 if (olp == NULL)
  {
   __dbg_msg("&& argument list empty.\n");
   return;
  }
 __dbg_msg("&&& start of expanded argument list dump.\n"); 
 for (olnum = 1; olp != NULL; olp = olp->optlnxt, olnum++)
  {
   if (olp->is_bmark || olp->is_emark)
    {
     if (olp->is_bmark)
      {
       __dbg_msg(">> no. %d lev %d: BEGIN MARK at %s\n", olnum, olp->optlev,
        __bld_lineloc(__xs, olp->optfnam_ind, olp->optlin_cnt));
      }
     else
      {
       __dbg_msg("<< no. %d lev %d: END MARK at %s\n", olnum, olp->optlev,
       __bld_lineloc(__xs, olp->optfnam_ind, olp->optlin_cnt));
      }
    }
   else
    {
     __dbg_msg("&& no. %d level %d: %s (value %d) at %s\n", olnum,
      olp->optlev, olp->opt, olp->optnum, __bld_lineloc(__xs,
      olp->optfnam_ind, olp->optlin_cnt));
    }
  }
 __dbg_msg("&&& expanded argument list end.\n"); 
}

/*
 * find an option from table
 * scheme assume no options with arguments but directions can have arguments
 * assuming then end with ;
 */
static int32 find_opt(char *aval)
{
 int32 i;

 /* first search for normal option (if arg white space separated) */ 
 for (i = 0; i < NCMDOPTS; i++)
  {
   if (strcmp(aval, cmdopts[i].lnam) == 0) return((int32) cmdopts[i].namid);
  }
 /* notice these special options are not in cmdopts table */
 if (strncmp(aval, "+libext+", 8) == 0) return(CO_LBEXT);
 if (strncmp(aval, "+incdir+", 8) == 0) return(CO_INCDIR);
 if (strncmp(aval, "+suppress_warns+", 16) == 0) return(CO_SUPPWARNS);
 if (strncmp(aval, "+define+", 8) == 0) return(CO_DEFINE);
 if (strncmp(aval, "+acc+", 5) == 0) return(CO_ACC); 
 /* notice next 2 unusual because use = instead of + since only one pair */
 if (strncmp(aval, "+loadpli1=", 10) == 0) return(CO_LOADPLI1);
 if (strncmp(aval, "+loadvpi=", 9) == 0) return(CO_LOADVPI);
#ifdef __XPROP__
 if (strncmp(aval, "+xtracemax=", 11) == 0) return(CO_XPROP_TRACE_MAX);
#endif
 /* AIV 11/16/11 - get a random with a seed setting */
 if (strncmp(aval, "+random=", 8) == 0) return(CO_RANDOM_SEED);
 /* AIV 05/09/12 - get a random with a seed setting - 2 state */
 if (strncmp(aval, "+random_2state=", 15) == 0) return(CO_RANDOM_2STATE_SEED);
 /* AIV 07/16/12 - now allowing +usedir= to setting working directory */
 /* to use instead of /tmp for temp work area */
 if (strncmp(aval, "+usedir=", 8) == 0) return(CO_USEDIR);

 return(-1);
}

/*
 * open log file (need if at all possible)
 */
static void open_logfile(void)
{
 char *chp;
 struct optlst_t *arg_olp;
 char s1[RECLEN];
 
 strcpy(s1, DFLT_LOGFNAM);
 __save_log_s = NULL;
 if (__log_olp != NULL)
  {
   arg_olp = __log_olp->optlnxt;
   if (arg_olp != NULL) chp = arg_olp->opt; else chp = NULL;
   if (chp == NULL || *chp == '+' || *chp == '-')
    {
     __gfwarn(505, __log_olp->optfnam_ind, __log_olp->optlin_cnt,
      "-l option not followed by log file name - %s used", DFLT_LOGFNAM); 
     goto no_explicit;
    }
   /* must mark so not seen as input file */
   arg_olp->optnum = -2;
   if ((__log_s = __tilde_fopen(chp, "w")) == NULL)
    {
     __gfwarn(505, arg_olp->optfnam_ind, arg_olp->optlin_cnt,
      "cannot open -l log file %s - trying default", chp);
     goto no_explicit;
    }
   __log_fnam = __pv_stralloc(chp);
   goto done;
  }

no_explicit:
 if ((__log_s = __tilde_fopen(s1, "w")) == NULL)
  {
   __pv_fwarn(505, "cannot open default log file %s - no log file", s1);
   return;
  }
 else __log_fnam = __pv_stralloc(s1);

done:;
 /* SM 03/26/00 - 2 (bit 4) no longer used for log file - lumped in with 1 */
 /* ---
 __mulchan_tab[2].mc_s = __log_s;
 --- */
 /* know this is closed so no previous name to free */
 /* ---
 __mulchan_tab[2].mc_fnam = __pv_stralloc(__log_fnam);
 --- */
}

/*
 * read command line args
 */
static void do_args(void )
{
 struct optlst_t *olp, *olp2; 
 int32 oi, tmp, len, level;
 FILE *f;
 struct optlst_t *sav_olp;
 struct loadpli_t *ldp;
 struct mapfiles_t *mapfp;
 struct sv_lib_t *svlp;
 struct ocfil_lst_t *ocfnlp;
 struct tgldat_in_lst_t *tgldat_ifp;
 struct stat st;
 char *chp, *chp2, *chp3;
 char s1[2*RECLEN];

 /* notice for options with arguments must mark arg as -2 or will be */
 /* seen as input file */ 
 for (olp = __opt_hdr; olp != NULL;)
  {
   /* ignore markers added for building vpi argc/argv */
   if (olp->is_bmark || olp->is_emark)
    { olp = olp->optlnxt; continue; }

   chp = olp->opt;
   /* no + or -, ignore for now - next pass add to file list */
   if (*chp != '-' && *chp != '+') { olp = olp->optlnxt; continue; }

   /* unrecognized +/-, if -, warning, else inform */ 
   if (olp->optnum == -1)
    {
     if (strlen(chp) == 1)
      {
       __gfwarn(506, olp->optfnam_ind, olp->optlin_cnt,
        "%s option prefix without following option name illegal - ignored",
         chp);
       olp = olp->optlnxt;
       continue;
      } 

     if (*chp == '-')
      __gfwarn(506, olp->optfnam_ind, olp->optlin_cnt,
       "unrecogized option %s - ignored ", olp->opt);
     else __gfinform(410, olp->optfnam_ind, olp->optlin_cnt,
      "assuming unrecognized option %s for pli or other simulator",
      olp->opt);
     
     olp = olp->optlnxt;
     continue;
    }
   oi = olp->optnum;
   switch (oi) {
    /* ignore already processed */
    case CO_LOG: case CO_HELP: case CO_QUIET: case CO_VERB: break;
    case CO_VERB_MEM: break;

    /* if was not able to open nest file error here */
    case CO_F: 
     /* if -f option expanded - will be removed before here */
     /* left only if error (cannot open file) */
     if (olp->optlnxt == NULL)
      {
       __gferr(920, olp->optfnam_ind, olp->optlin_cnt,
        "-f include argument not followed by file name");
       continue;
      }
     olp = olp->optlnxt; 
     /* -f not followed by file name in nested -f file */
     if (olp->is_emark)
      {
       /* here may have long list of emarks that must be skipped */
       __gferr(920, olp->optfnam_ind, olp->optlin_cnt,
        "nested -f include argument not followed by file name");
       break;
      }
     __gferr(920, olp->optfnam_ind, olp->optlin_cnt,
      "cannot open -f include argument file %s", olp->opt);
     olp->optnum = -2;
     break;

    /* options followed by 1 white space separated argument */
    case CO_IAINPUT:
     sav_olp = olp;
     olp = olp->optlnxt; 
     if (olp != NULL) chp = olp->opt;
     if (olp == NULL || olp->is_emark || chp == NULL || *chp == '+'
      || *chp == '-')
      {
       __gfwarn(505, sav_olp->optfnam_ind, sav_olp->optlin_cnt,
        "-i option not followed by startup interactive input file name"); 
       continue;
      }
     olp->optnum = -2;
     /* make sure it can be opened */
     if ((f = __tilde_fopen(chp, "r")) == NULL)
      {
       __gfwarn(505, sav_olp->optfnam_ind, sav_olp->optlin_cnt,
        "cannot open -i startup interactive input file %s - input from stdin",
        chp);
       break;
      }
     __my_fclose(f);
     __cmd_start_fnam = __pv_stralloc(chp);
     if (__verbose)
      {
       __cv_msg("  Startup interactive input will be read from file \"%s\".\n",
        __cmd_start_fnam);
      }
     /* SJM 04-02-09 - for interpreter/debugger only options, if have not */
     if (__compiled_sim || __no_iact)
      {
       __gfwarn(642, olp->optfnam_ind, olp->optlin_cnt,
        "interpreter only option %s before +interp option  - will be ignored for compiled sim",
        sav_olp->opt);
      }
     break; 
    case CO_KEY:
     sav_olp = olp;
     olp = olp->optlnxt; 
     if (olp != NULL) chp = olp->opt;
     if (olp == NULL || olp->is_emark || *chp == '+' || *chp == '-')
      {
       __gfwarn(505, sav_olp->optfnam_ind, sav_olp->optlin_cnt,
        "-k option not followed by file name for transcript of typed keys");
       continue; 
      }  
     olp->optnum = -2;
     __gfwarn(621, sav_olp->optfnam_ind, sav_olp->optlin_cnt,
      "-k option no effect - key files not supported (use $input scripts)");
     /* only open if needed (must go in malloc as separate) */
     break;
    case CO_TRACEFILE:
     sav_olp = olp;
     olp = olp->optlnxt; 
     if (olp != NULL) chp = olp->opt;
     if (olp == NULL || olp->is_emark || *chp == '+' || *chp == '-')
      {
       __gfwarn(509, sav_olp->optfnam_ind, sav_olp->optlin_cnt,
       "+tracefile option not followed by file name - previous (stdout?) used");
       continue; 
      }  
     olp->optnum = -2;
     /* only open when tracing enabled */
     if (strcmp(chp, "STDOUT") == 0) strcpy(chp, "stdout"); 
     if (__tr_fnam != NULL) __my_free(__tr_fnam, strlen(__tr_fnam) + 1);
     __tr_fnam = __pv_stralloc(chp);
     __tr_s = NULL;
     if (__verbose)
      __cv_msg(
       "  Statement and/or event trace output will be written to file \"%s\".\n",
       __tr_fnam);
      /* in case -t or -et precedes this option open now */
     if (__st_tracing || __ev_tracing || __pth_tracing) __maybe_open_trfile();
     break;
    case CO_SDF_LOG:
     sav_olp = olp;
     olp = olp->optlnxt; 
     if (olp != NULL) chp = olp->opt;
     if (olp == NULL || olp->is_emark || *chp == '+' || *chp == '-')
      {
       __gfwarn(505, sav_olp->optfnam_ind, sav_olp->optlin_cnt,
        "+sdf_log_file setting option not followed by file name");
       continue; 
      }  
     olp->optnum = -2;
     if (__sdf_opt_log_fnam != NULL)
      __my_free(__sdf_opt_log_fnam, strlen(__sdf_opt_log_fnam) + 1);
     __sdf_opt_log_fnam = __pv_stralloc(chp);

     if (__verbose)
      {
       __cv_msg(
        "  SDF messages and errors will be written to separate SDF log file %s.\n",
        __sdf_opt_log_fnam);
      }
     break;
    case CO_SDFANNOTATE:
     sav_olp = olp;
     olp = olp->optlnxt; 
     if (olp != NULL) chp = olp->opt;
     if (olp == NULL || olp->is_emark || *chp == '+' || *chp == '-')
      {
       __gfwarn(593, sav_olp->optfnam_ind, sav_olp->optlin_cnt,
        "+sdf_annotate option not followed by [file][+<optional scope name>] - ignored");
       continue;
      }
     olp->optnum = -2;
     do_sdflocdef(chp, __in_fils[sav_olp->optfnam_ind], sav_olp->optlin_cnt);
     break;
    case CO_MAXERRS:
     sav_olp = olp;
     olp = olp->optlnxt; 
     if (olp != NULL) chp = olp->opt;
     if (olp == NULL || olp->is_emark || *chp == '+' || *chp == '-')
      {
bad_maxerrs:
       __gfwarn(502, sav_olp->optfnam_ind, sav_olp->optlin_cnt,
        "maximum error number must be 0 (no limit) or positive");
       continue;
      }
     olp->optnum = -2;
     if (sscanf(chp, "%d", &tmp) != 1 || tmp < 0) goto bad_maxerrs;
     __max_errors = tmp; 
     if (__max_errors != 0 && __verbose)
      __cv_msg(
       "  Translation will stop after %d errors instead of default %d.\n",
       __max_errors, MAX_ERRORS); 
     else
      {
       if (__verbose)
        __cv_msg("  Default error termination limit disabled.\n");
      }
     break;
    case CO_V:
     sav_olp = olp;
     olp = olp->optlnxt; 
     if (olp != NULL) chp = olp->opt;
     if (olp == NULL || olp->is_emark || *chp == '+' || *chp == '-')
      {
       __gfwarn(501, sav_olp->optfnam_ind, sav_olp->optlin_cnt,
        "-v library file option not followed by file name - ignored");
       continue;
      }
     olp->optnum = -2;
     if (strcmp(chp, ".") == 0 || strcmp(chp, "..") == 0)
      {
       __gfwarn(623, sav_olp->optfnam_ind, sav_olp->optlin_cnt,
        "-v library file %s illegal", chp);
      }
     add_lbfil(chp, 'v');
#ifndef __CVC_RT__
     /* AIV 11/14/09 - don't need to see this at compiled rt */
     if (__verbose)
      __cv_msg("  File \"%s\" in library from -v option.\n", chp); 
#endif
     break;
    case CO_LIBLIST:
     /* -L library */
     sav_olp = olp;
     olp = olp->optlnxt; 
     if (olp != NULL) chp = olp->opt;
     if (olp == NULL || olp->is_emark || *chp == '+' || *chp == '-')
      {
       __gfwarn(501, sav_olp->optfnam_ind, sav_olp->optlin_cnt,
        "-L library map file option not followed by file name - ignored");
       continue;
      }
     olp->optnum = -2;
     /* set the global name of the -L library name */
     __cmdl_library = __pv_stralloc(chp);
#ifndef __CVC_RT__
     if (__verbose)
      __cv_msg("  File \"%s\" in library from -L option.\n", chp); 
#endif
     break;
    case CO_LIBMAP:
     /* +config [filename] */
     sav_olp = olp;
     olp = olp->optlnxt; 
     if (olp != NULL) chp = olp->opt;
     if (olp == NULL || olp->is_emark || *chp == '+' || *chp == '-')
      {
       __gfwarn(501, sav_olp->optfnam_ind, sav_olp->optlin_cnt,
        "+config [file] library map file option not followed by file name - ignored");
       continue;
      }
     olp->optnum = -2;

     mapfp = (struct mapfiles_t *) __my_malloc(sizeof(struct mapfiles_t));
     mapfp->mapfnam = __pv_stralloc(chp);
     mapfp->mapfnxt = NULL;

     if (__map_files_hd == NULL) __map_files_hd = __map_files_tail = mapfp;
     else
      {
       __map_files_tail->mapfnxt = mapfp;
       __map_files_tail = mapfp;
      }
#ifndef __CVC_RT__
     if (__verbose)
      __cv_msg(
       "  Will read \"%s\" map lib file specified by +config [file] option.\n",
       mapfp->mapfnam); 
#endif
     break;
    case CO_FRSPICE:
     break;
    case CO_Y:
     sav_olp = olp;
     olp = olp->optlnxt; 
     if (olp != NULL) chp = olp->opt;
     if (olp == NULL || olp->is_emark || *chp == '+' || *chp == '-')
      {
       __gfwarn(593, sav_olp->optfnam_ind, sav_olp->optlin_cnt,
        "-y library directory option not followed by path name - ignored");
       continue;
      }
     olp->optnum = -2;
     add_lbfil(chp, 'y');
#ifndef __CVC_RT__
     if (__verbose)
      __cv_msg("  Directory \"%s\" searched for libraries from -y option.\n",
      olp->opt); 
#endif
     break;
    case CO_DEFINE:
     chp = olp->opt;
     do_cmdmacdef(&(chp[8]), olp);
     break;
    case CO_INCDIR:
     chp2 = olp->opt;
     /* error message on bad format emitted inside here */
     if (!bld_incdtab(&(chp2[8]), olp)) break;
#ifndef __CVC_RT__
     if (__verbose)
      {
       __cv_msg(
        "  %s additional +incdir+ paths searched to find `include files.\n",
        &(olp->opt[7])); 
      }
#endif
     break;
    case CO_LOADPLI1:
#ifdef __STATIC_PLI__
    __gfwarn(3123, olp->optfnam_ind, olp->optlin_cnt,
     "+loadpli1 = option illegal when using old style statically linked cverobj.o - ignored");
#else
     chp2 = olp->opt;
     if ((ldp = bld_loadpli_lbs(&(chp2[10]), olp, TRUE)) == NULL) break;
     if (__verbose)
      {
       /* this can't fail since know well formed */
       chp3 = strrchr(chp2, ':');
       /* DBG LINT remove -- */
       if (chp3 == NULL) __misc_terr(__FILE__, __LINE__);
       /* -- */
       if (strcmp(chp3, "") == 0) strcpy(__xs, "[none]");
       else strcpy(__xs, chp3);
       __cv_msg(
        "  +loadpli1 dynamic library %s loaded with bootstrap routine(s) %s\n",
        ldp->libnam, __xs);
      }
#endif
     break;
    case CO_LOADVPI:
#ifdef __STATIC_PLI__
    __gfwarn(3123, olp->optfnam_ind, olp->optlin_cnt,
     "+loadvpi= option illegal when using old style statically linked cverobj.o - ignored");
#else
     chp2 = olp->opt;
     if ((ldp = bld_loadpli_lbs(&(chp2[9]), olp, FALSE)) == NULL) break;
     if (__verbose)
      {
       /* this can't fail since know well formed */
       chp3 = strrchr(chp2, ':');
       /* DBG LINT remove -- */
       if (chp3 == NULL) __misc_terr(__FILE__, __LINE__);
       /* -- */
       if (strcmp(chp3, "") == 0) strcpy(__xs, "[none]");
       else strcpy(__xs, chp3);
       __cv_msg(
        "  +loadvpi= dynamic library %s loaded with bootstrap routine(s) %s\n",
        ldp->libnam, __xs);
      }
#endif
     break;
 
    case CO_DPI_WR_HDRS:
     __wr_dpi_c_hdrs = TRUE;
     if (__verbose)
      {
       __cv_msg(
        "  Writing DPI C routine header prototypes to file dpi_hdrs.h\n");
      }
     break;
    case CO_DPI_SVLIB:
     /* if users is using -sv_lib assume SV parsing */
     __sv_parse = TRUE;
     sav_olp = olp;
     olp = olp->optlnxt; 
     if (olp != NULL) chp = olp->opt;
     if (olp == NULL || olp->is_emark || *chp == '+' || *chp == '-')
      {
       __gfwarn(4302, sav_olp->optfnam_ind, sav_olp->optlin_cnt,
        "+sv_lib option not followed by required [path] - ignored");
       continue;
      }
     olp->optnum = -2;
     svlp = (struct sv_lib_t *) __my_malloc(sizeof(struct sv_lib_t));
     /* SJM 02-12-13 - bug was assuming paths are relative */
     if (*chp == '/')
      {
       __gfwarn(4311, sav_olp->optfnam_ind, sav_olp->optlin_cnt,
        "-sv_lib option library path name %s is absolute - not portable but still used",
        chp);
       strcpy(s1, chp);
      }
     else if (strncmp(chp, "./", 2) == 0)
      {
       /* SJM 02-12-13 - if the ./ already there, do not add */
      strcpy(s1, chp);
      }
     else
      {
       /* SJM 02-12-13 - add the "./" - this makes simple leave -sv lib .so */
       /* in dircvc runs in works (handles most common relative paths too) */
       strcpy(s1, "./");
       strcat(s1, chp);
      }
     if (stat(s1, &st) != 0)
      {
       __gfwarn(4303, olp->optfnam_ind, olp->optlin_cnt,
        "-sv_lib library file %s - cannot be opened or does not exist", chp);
      }
     svlp->does_not_exist = FALSE;
     svlp->path = __pv_stralloc(s1);
     svlp->svnxt = NULL;
     if (__sv_lib_hdrp == NULL) __sv_lib_hdrp = __sv_lib_endp = svlp;
     else
      {
       __sv_lib_endp->svnxt = svlp;
       __sv_lib_endp = svlp;
      }
     if (__verbose)
      {
       __cv_msg("  Linking in DPI library \"%s\".\n", chp);
      }
     break;
    case CO_SV_PARSE:
    case CO_SV_PARSE2:
     __sv_parse = TRUE;
     if (__verbose)
      __cv_msg("  Will parse source with System Verilog keywords allowed.\n");
     break;
    case CO_OPTCFGFIL:
     sav_olp = olp;
     olp = olp->optlnxt; 
     if (olp != NULL) chp = olp->opt;
     if (olp == NULL || olp->is_emark || *chp == '+' || *chp == '-')
      {
       __gfwarn(4305, sav_olp->optfnam_ind, sav_olp->optlin_cnt,
        "-optconfigfile file name missing");
        continue;
      }
     /* mark not input file */
     olp->optnum = -2;
     if (stat(chp, &st) != 0)
      {
       __gfwarn(4306, olp->optfnam_ind, olp->optlin_cnt,
        "-optconfigfile file %s - can not be opened", chp);
      }
     ocfnlp = (struct ocfil_lst_t *)__my_malloc(sizeof(struct ocfil_lst_t));
     ocfnlp->ocfnam = __pv_stralloc(olp->opt);
     ocfnlp->oc_stmts = NULL;
     ocfnlp->oclnxt = NULL;
     /* SJM 12-11-10 - file order must be preserved */ 
     if (__last_optcfg_fil == NULL) __optcfg_fils = __last_optcfg_fil = ocfnlp; 
     else
      {
       ocfnlp->oclnxt = __last_optcfg_fil;
       __last_optcfg_fil = ocfnlp;
      }
     if (__verbose) 
      {
       /* SJM 12-17-10 - need to print actual opt config fil name */
       __cv_msg(
        "  Adding -optconfigfile %s containing config attributes.\n",
        ocfnlp->ocfnam);
      }
     break;
    case CO_TOGGLE:
     if (__verbose) __cv_msg("  Toggle coverage report on.\n");
     __toggle_coverage = TRUE;
     break;
    case CO_TOGGLE_FILE:
     olp2 = olp;
     olp = olp->optlnxt;
     if (olp == NULL)
      {
       /* AIV 08/17/11 - need to use olp2 not next arg */
       __gferr(920, olp2->optfnam_ind, olp2->optlin_cnt,
        "-toggle_file not followed by file name");
        continue;
      }
     olp->optnum = -2;
     __toggle_coverage_file_name = __pv_stralloc(olp->opt);
     if (__verbose) 
      {
       __cv_msg("  Toggle coverage report on writing to file %s.\n",
        __toggle_coverage_file_name);
      }
     /* SJM 04-26-13 - now when setting toggle file - do not turn on toggle */
     /* coverage - do not know yet - may be turned on in optcfg file */
     break;
    case CO_TOGGLE_REPORT_INSTANCE:
     if (__verbose) __cv_msg("  Toggle reporting per instance.\n");
     __old_toggle_rpt_instance = TRUE;
     break;
    case CO_DRVN_CONST_AS_TGL:
//SJM 11-03-12 - LOOKATME? - think this should be default
     if (__verbose)
      {
       __cv_msg(
        "  Wires driven by constants will not appear in untoggled report.\n");
      } 
     __drvn_const_as_tgled = TRUE;
     break;
    case CO_DRVN_CONST_RPT_CONCISE:
     if (__verbose)
      { 
       __cv_msg(
        "  New concise format report lists wire bits driven by constants.\n");
      }
     __drvn_const_rpt_concise = TRUE;
     break;
    case CO_UNTGL_RPT_CONCISE:
     if (__verbose)
      { 
       __cv_msg(
        "  New concise untoggled only report - ignores non concise report options.\n");
      }
     __untgled_rpt_concise = TRUE;
     break;
// SJM 04-18-13 - START OF NEW TGLDAT OPTIONS
    case CO_WRITE_TGLDAT:
     /* this will write to the toggle.tgldat file unless explicit opt used */
     __wr_tgldat_on = TRUE;
     if (__verbose)
      { 
       __cv_msg(
        "  Toggle coverage results for this run written to default verilog.tgldat file.\n");
      }
     break;
    case CO_WRITE_TGLDAT_FILE:
     /* AIV 08/17/11 - need to use olp2 not next arg */
     olp2 = olp;
     olp = olp->optlnxt;
     if (olp == NULL)
      {
       __gferr(920, olp2->optfnam_ind, olp2->optlin_cnt,
        "-write_toggle_data_file option not followed by file name");
        continue;
      }
     olp->optnum = -2;
     __wr_tgldat_file = __pv_stralloc(olp->opt);
     if (__verbose) 
      {
       __cv_msg(
        "  Toggle coverage results for this run written to .tgldat file %s.\n",
        __wr_tgldat_file);
      }
     /* must turn on too */  
     __wr_tgldat_on = TRUE;
     break;
    case CO_SET_TGLED_FROM_FILE:
     olp2 = olp;
     olp = olp->optlnxt;
     if (olp != NULL) chp = olp->opt;
     if (olp == NULL || olp->is_emark || *chp == '+' || *chp == '-')
      {
       __gferr(920, olp2->optfnam_ind, olp2->optlin_cnt,
        "-set_toggled_from_file option not followed by .tgldat file name");
        continue;
      }
     olp->optnum = -2;
     if (stat(chp, &st) != 0)
      {
       __gfwarn(4301, olp->optfnam_ind, olp->optlin_cnt,
        "-set_togled_from_file .tgldat file %s - can not be opened", chp);
      }

     /* build the .tgldat input file name record */
     tgldat_ifp = (struct tgldat_in_lst_t *)
      __my_malloc(sizeof(struct tgldat_in_lst_t));
     tgldat_ifp->in_tgldat_fnam = __pv_stralloc(olp->opt);
     tgldat_ifp->tgldat_in_nxt = NULL;
     if (__tgldat_infils_lst_hd == NULL)
      { 
        __tgldat_infils_lst_hd = __tgldat_infils_lst_end = tgldat_ifp;
      }
     else __tgldat_infils_lst_end->tgldat_in_nxt = tgldat_ifp;
     if (__verbose) 
      {
       __cv_msg(
        "  .tgldat file %s read and used to set toggled bits from previous run.\n",
        tgldat_ifp->in_tgldat_fnam);
      }
     break;
    case CO_TGLVERBOSE:
     if (__verbose)
      {
       __cv_msg(
        "  .tgldat file reading mis-match verbose warnings will be printed.\n");
      }
     __tgl_verbose = TRUE;
     break;
    case CO_TOGGLE_REPORT_BITS:
     if (__verbose) __cv_msg("  Old style toggle reporting per bits.\n");
     __old_toggle_rpt_bits = TRUE;
     break;
    case CO_TOGGLE_UNCOVERED:
     if (__verbose) __cv_msg("  Old style toggle reporting uncovered bits.\n");
     __old_toggle_rpt_uncovered = TRUE;
     break;
    case CO_TOGGLE_COVERED:
     if (__verbose) __cv_msg("  Old style toggle reporting covered bits.\n");
     __old_toggle_rpt_covered = TRUE;
     break;
    case CO_EVENT_COVERAGE:
     if (__verbose) __cv_msg("  Event coverage reporting on.\n");
     __event_coverage = TRUE;
     break;
    case CO_EVENT_COVERAGE_FILE:
     if (__verbose) __cv_msg("  Event coverage reporting on.\n");
     __event_coverage = TRUE;
     olp2 = olp;
     olp = olp->optlnxt;
     if (olp == NULL)
      {
       /* AIV 08/17/11 - need to use olp2 not next arg */
       __gferr(920, olp2->optfnam_ind, olp2->optlin_cnt,
        "-event_coverage_file not followed by file name");
        continue;
      }
     olp->optnum = -2;
     __event_coverage_file_name = __pv_stralloc(olp->opt);
     if (__verbose) 
      {
       __cv_msg("  Event coverage report on writing to file %s.\n",
        __event_coverage_file_name);
      }
     break;
    case CO_STMT_COVERAGE:
     if (__verbose) __cv_msg("  Statement coverage reporting on.\n");
     __stmt_coverage = TRUE;
     break;
    case CO_STMT_TASKS_COVERAGE:
     if (__verbose) __cv_msg("  Statement coverage for tasks reporting on.\n");
     __stmt_coverage = TRUE;
     __stmt_coverage_tasks = TRUE;
     break;
    case CO_STMT_COVERAGE_FILE:
     if (__verbose) __cv_msg("  Statement coverage reporting on.\n");
     __stmt_coverage = TRUE;
     olp2 = olp;
     olp = olp->optlnxt;
     if (olp == NULL)
      {
       /* AIV 08/17/11 - need to use olp2 not next arg */
       __gferr(920, olp2->optfnam_ind, olp2->optlin_cnt,
        "-stmt_coverage_file not followed by file name");
        continue;
      }
     olp->optnum = -2;
     __stmt_coverage_file_name = __pv_stralloc(olp->opt);
     if (__verbose) 
      {
       __cv_msg(" Statement coverage report on writing to file %s.\n",
        __stmt_coverage_file_name);
      }
     break;
    case CO_OVERRIDE_CHANGE:
     /* SJM 04-18-13 - option for internal debug - lets exec not match src */ 
     __override_change = TRUE;
     if (__verbose)
      {
       __cv_msg("  Overriding model change check\n");
      }
     break;
    case CO_SAME_PARAM_MUST_SPLIT:
     __same_param_must_split = TRUE;
     if (__verbose)
      {
       __cv_msg(
        "  turn off optimization that merges split same param types.\n");
      }
     break;
    case CO_RANDOM:
     __random_init = TRUE;
     if (__verbose) __cv_msg("  Random initialization turned on.\n");
     break;
    case CO_RANDOM_2STATE:
     /* must turn on both flags */
     __random_init = TRUE;
     __random_init_2state = TRUE;
     if (__verbose) __cv_msg("  Random 2-state initialization turned on.\n");
     break;
    case CO_RANDOM_SEED:
    case CO_RANDOM_2STATE_SEED:
     /* +xtracemax=10 - set the new max value */
     chp2 = strchr(olp->opt, '=');
     /* DBG remove -- */
     if (chp2 == NULL) __misc_terr(__FILE__, __LINE__);
     /* ---- */
     chp2++;
     __init_seed = atoi(chp2);   
     __random_init = TRUE;
     if (oi == CO_RANDOM_SEED)
      {
        if (__verbose) 
         {
          __cv_msg("  Random initialization turned on with seed=%d.\n", 
            __init_seed);
         }
      }
     else
      {
       __random_init_2state = TRUE;
       if (__verbose) 
        {
         __cv_msg("  Random 2-state initialization turned on with seed=%d.\n", 
           __init_seed);
        }
      }
     break;
    case CO_LBEXT:
     chp2 = olp->opt;
     if (__last_lbx != -1)
      {
       __gfwarn(598, olp->optfnam_ind, olp->optlin_cnt,
        "+libext+ option for -y library directories cannot be repeated - ignored");
       /* need to move to next option */
       break;
      }
    
     if (!bld_lbxtab(&(chp2[8]), olp)) break;
#ifndef __CVC_RT__
     if (__verbose)
      {
       __cv_msg(
        "  %s suffix(es) used for -y library extensions from +libext+ options.\n",
        &(olp->opt[7])); 
      }
#endif
     break;
    /* options where arg is suffix of option */
    case CO_SUPPWARNS:
     chp2 = olp->opt;
     len = strlen(chp2);
     /* if optional ending plus left out - add here */
     if (chp2[len - 1] != '+')
      {
       /* SJM - 12/20/02 - must copy to work string because no room to add */
       /* plus if not added by user */
       strcpy(s1, chp2);
       s1[len] = '+'; s1[len + 1] = '\0';
       chp2 = s1;
      }

     /* returns F on error, so tracing for not emitted on T */
     if (add_suppwarn(chp2, olp)) 
      {
       if (__verbose)
        __cv_msg(
         "  Following warning or interactive message(s) %s will not be emitted.\n",
         &(chp2[16]));
      }
     break;
    /* options without arguments */
    case CO_C:
     if (__verbose)
      {
       __cv_msg(
        "  Translate only - all files and library directories will be checked.\n");
      }
     __compile_only = TRUE;
     break;
    case CO_PARSEONLY:
     if (__verbose)
      {
       __cv_msg(
        "  Parse only - for quick syntax check of separate modules.\n");
      }
     __parse_only = TRUE;
     break;
    case CO_STOP:
     if (__verbose)
      __cv_msg("  Stopping into interactive mode before simulation begins.\n");
     /* this is not checked until sim begins (if it does) */
     __stop_before_sim = TRUE;

     /* SJM 04-02-09 - for interpreter/debugger only options, if have not */
     if (__compiled_sim || __no_iact)
      {
       __gfwarn(642, olp->optfnam_ind, olp->optlin_cnt,
        "interpreter only option %s before +interp option  - will be ignored for compiled sim",
        olp->opt);
      }
     break;
    case CO_E:
     __no_errs = TRUE;
     if (__verbose) __cv_msg("  Error messages will not be printed.\n");
     break;
    case CO_D:
     __decompile = TRUE;
     if (__verbose)
      __cv_msg(
       "  Source after generate and defparam expansion will be decompiled and printed.\n");
     break;
    case CO_D_ULINE:
     __decompile = TRUE;
     __repl_gen_dot_uline = TRUE;
     if (__verbose)
      __cv_msg(
       "  Source after generate decompiled with generated dots in names replaced by underscore.\n");
     break;
    case CO_DMP_ARRAYS:
     __dump_arrays = TRUE;
     if (__verbose) __cv_msg("  Dumping array values.\n");
     break;
    case CO_DMP_ARRAY_CELLS:
     __dump_array_cells = TRUE;
     __dump_arrays = TRUE;
     if (__verbose) __cv_msg("  Dumping array cell values.\n");
     break;
    case CO_D_ESC:
     __decompile = TRUE;
     __repl_gen_dot_esc = TRUE;
     if (__verbose)
      __cv_msg(
       "  Source after generate decompiled with generated dots in names changed to escaped.\n");
     break;
    case CO_A:
     if (__verbose)
      __cv_msg("-a accelerate option no effect - on by default.\n");
     break;
    case CO_AOFF:
     if (__verbose)
      __cv_msg("port and gate assignments will not be accelerated.\n");
     __accelerate = FALSE;
     break;
    case CO_X:
     if (__verbose)
      __cv_msg("-x option no effect - vector wires expanded by default.\n");
     break;
    case CO_DEBUG:
     __debug_flg = TRUE;
     if (__verbose)
      __cv_msg("  Debugging information will be printed.\n");
     break;
    case CO_MINDEL:
     __mintypmax_sel = DEL_MIN;
     if (__verbose)
      __cv_msg("  Min:typ:max expressions will use the minimum value.\n");
     break;
    case CO_TYPDEL:
     __mintypmax_sel = DEL_TYP;
     if (__verbose)
      __cv_msg(
       "  Min:typ:max expressions will use the typical value (default).\n");
     break;
    case CO_MAXDEL:
     __mintypmax_sel = DEL_MAX;
     if (__verbose)
      __cv_msg("  Min:typ:max expressions will use the maximum value.\n");
     break;
    case CO_SETTRACE:
     __st_tracing = TRUE;
     __maybe_open_trfile();
     if (__verbose)
      __cv_msg("  Execution of behavioral statements will be traced.\n");
     break;
    case CO_SETEVTRACE:
     __ev_tracing = TRUE;
     __maybe_open_trfile();
     if (__verbose) __cv_msg("  Event processing will be traced.\n");
     break;
    case CO_SETPTHTRACE:
     __pth_tracing = TRUE;
     __maybe_open_trfile();
     if (__verbose)
      __cv_msg("  Specify delay Path will be traced in detail.\n");
     break;
    case CO_GATE_EATER: case CO_NO_GATE_EATER:
     __gfwarn(507, olp->optfnam_ind, olp->optlin_cnt,
      "  +gateeater option obsolete - option ignored");
     break;
    case CO_W:
     __no_warns = TRUE;
     if (__verbose) __cv_msg("  Warning messages will not be printed.\n");
     break;
    case CO_INFORM:
     __no_informs = FALSE;
     if (__verbose) __cv_msg("  Inform messages will be printed.\n");
     break;
    case CO_UC:
     __gfwarn(507, olp->optfnam_ind, olp->optlin_cnt,
      "  -u option unsupported - input is case sensitive");
     break;
    case CO_SDFVERB:
     __sdf_verbose = TRUE;
     
     if (__verbose)
      __cv_msg("  SDF annotation tracing verbose mode is on.\n");
     break;
    case CO_DPIVERB:
     __dpi_verbose = TRUE;
     if (__verbose)
      __cv_msg("  DPI IMPORT -svlib existence checking verbose mode is on.\n");
     break;
    case CO_IGNORE_SDF_IOPATH_EDGES:
     __ignore_sdf_iopath_edges = TRUE;
     
     if (__verbose)
      __cv_msg("  Ignoring SDF (IOPATH edges when matching specify paths.\n");
     break;
    case CO_SDF_DURING_SIM:
     __sdf_during_sim = TRUE;
     if (__verbose)
      {
       __cv_msg("  SDF annotation executed during sim - won't work with compiler");
      }
     break;
    case CO_SDF_NO_ERRS:
     __sdf_no_errs = TRUE;
     if (__verbose) __cv_msg("  SDF error messages will not be printed.\n");
     break;
    case CO_SDF_NO_WARNS:
     __sdf_no_warns = TRUE;
     if (__verbose) __cv_msg("  SDF warning messages will not be printed.\n");
     break;
    case CO_LBVERB:
     __lib_verbose = TRUE;
     __cfg_verbose = TRUE;
     if (__verbose) __cv_msg("  Library tracing verbose mode is on.\n");
     break;
    case CO_SWITCHVERB:
     /* AIV 03/30/12 - this should only turn on for compile time */
     if (__compiled_sim && __running_cvc_exe) break;
     __switch_verbose = TRUE;
     /* SJM 11/29/00 - message only output if verbose not switch verbose */
     if (__verbose)
      __cv_msg("  Switch channel construction verbose mode is on.\n");
     break;
    case CO_CHG_PORTDIR:
     /* SJM 11/29/00 - new option that changes port direction if connected */  
     /* as inout, most designs do not need this option but some do */
     __chg_portdir = TRUE;
     if (__verbose)
      __cv_msg(
       "  Changing port type (direction) to inout for ports connected as inout.\n");
     break;
    case CO_SCHD_ALW_FIRST:
     /* SJM 05-13-13 - have request to change so always blocks are */
     /* all initialized (armed) before init blocks - made an option */
     /* because some bug reports wanted old order some new - think */
     /* option needed to get altera libraries to work */ 
     __sched_always_blocks_first = TRUE;
     if (__verbose)
      __cv_msg(
       "  Initialization event order changed so always blocks armed before any initial blocks started at time 0.\n");
     break;
    case CO_NB_NOSEP_QUEUE:
     /* AIV 06/28/05 - new option that changes causes old non blocking */
     /* algorithm that did not have separate after pnd0 (each section) */
     /* event queue to be used */
     /* AIV 04/16/07 - this option has been deprecated - never really used */
     __gfwarn(595, olp->optfnam_ind, olp->optlin_cnt,
      "+no_separate_nb_queue option has been deprecated");
     break;
    case CO_LIBRESCAN:
     __lib_rescan = TRUE;
     if (__verbose)
      __cv_msg(
       "  Library rescanned from beginning after every name resolved.\n");
     break;
    case CO_LIBORD:
     __gfwarn(503, olp->optfnam_ind, olp->optlin_cnt,
      "+liborder option unsupported");
lib_mth:
     if (__verbose)
      __cv_msg("  Using default or +librescan library scanning method.\n");
     break;
    case CO_LIBNOHIDE:
     __gfwarn(594, olp->optfnam_ind, olp->optlin_cnt,
      "+libnohide option unsupported");
     goto lib_mth;
    case CO_NCHG_TRACE:
     __missing_nchg_trace = TRUE;
     if (__verbose)
      __cv_msg("  Tracing late nchg adding - shouldn't be needed.\n");
     break;
    case CO_PRTSTATS:
     /* AIV 03/30/12 - this should only turn on for compile time */
     if (__compiled_sim && __running_cvc_exe) break;
     __prt_stats = TRUE;
     if (__verbose) __cv_msg("  Design content tables will be written.\n");
     break;
    case CO_PRTALLSTATS:
     /* AIV 03/30/12 - this should only turn on for compile time */
     if (__compiled_sim && __running_cvc_exe) break;
     __prt_allstats = TRUE;
     if (__verbose)
      __cv_msg(
       "  Voluminous design and module content tables will be written.\n");
     break;
    case CO_SPIKEANAL:
     __gfwarn(591, olp->optfnam_ind, olp->optlin_cnt,
      "+spikes option name changed - use standardized +show_canceled_e instead");
     break;
    case CO_SHOWCANCELE:
     __show_cancel_e = TRUE;
     if (__verbose)
      __cv_msg("  Pulse canceled events X shown (glitches cause X output).\n");
     break;
    case CO_NOSHOWCANCELE:
     __show_cancel_e = FALSE;
     if (__verbose)
      __cv_msg(
       "  Pulse canceled events not shown (glitches removed - default).\n");
     break;
    case CO_PULSEX_ONEVENTE:
     __showe_onevent = TRUE;
     if (__verbose)
      __cv_msg("  Pulse shown Xs scheduled at pulse leading edge (default).\n");
     break;
    case CO_PULSEX_ONDETECT:
     __showe_onevent = FALSE;
     if (__verbose)
      __cv_msg("  Pulse shown Xs set when pulse (glitch) detected.\n");
     break;
    case CO_WARNCANCELE:
     __warn_cancel_e = TRUE;
     if (__verbose)
      __cv_msg("  Warning message emitted when pulse (glitch) detected.\n");
     break;
    case CO_NOWARNCANCELE: 
     __warn_cancel_e = FALSE;
     if (__verbose)
      {
       __cv_msg(
        "  No warning message emitted when pulse (glitch) detected (detected).\n");
      }
     break;
    case CO_MIPD_CYCLE_PND0_SCHD:
     __mipd_cycle_pnd0_schd = TRUE;
     if (__verbose)
      {
       __cv_msg(
        "  Use cycle mode for MIPDS - delay input port change similar to #0.\n");
      }
     break;
    case CO_RMGATEPND0S:
     __rm_gate_pnd0s = TRUE;  
     if (__verbose)
      {
       __cv_msg(
        "  All gate #0 delays converted to no delay to speed up simulation.\n");
      }
     break;
    case CO_NORMPTHPND0S:
     /* remove path pound 0 delays by default */
     __rm_path_pnd0s = FALSE;  
     if (__verbose)
      {
       __cv_msg("  Disabling removal of all 0 (no effect) path delays.\n");
      }
     break;
    case CO_NOKEEPCOMMANDS:
     __history_on = FALSE;
     if (__verbose)
      {
       __cv_msg(
       "  Entered (or $input or piped in) commands not kept on history list.\n");
      }
     /* SJM 04-02-09 - for interpreter/debugger only options, if have not */
     if (__compiled_sim || __no_iact)
      {
       __gfwarn(642, olp->optfnam_ind, olp->optlin_cnt,
        "interpreter only option %s before +interp option  - will be ignored for compiled sim",
        olp->opt);
      }
     break;
    case CO_OLD_VPI_AFTER_ITER_FREE:
     __old_vpi_obj_after_iter_free_only = TRUE;
     if (__verbose)
      { 
       __cv_msg(
        "To match old CVC vpi_, only allow freeing of objects in iterators after iterator freed.\n");
      }
     break;
    case CO_PLIKEEPSRC:
     if (__verbose)
      { 
       __cv_msg(
        "  +pli_keep_source option removed - all PLI source access kept");
      }
     break;
    case CO_NOIACT:
#ifndef __NOSIGS__
     /* if no signal - then no interactive automatic but flag must be */
     /* off since still need callbacks for invoking signal handler */
     __no_iact = TRUE;
     if (__verbose)
      __cv_msg("  No interactive commands for this run - ^c causes finish.\n");
#endif
     break;
    case CO_SNAPSHOT:
#ifndef __NOSIGS__
     __intsig_prt_snapshot = TRUE;
     if (__verbose)
      __cv_msg(
       "  Activity snap shot printed upon interrupt signal (^c) termination");
     break;
#endif
    case CO_NOSPFY:
     __no_specify = TRUE;
     if (__verbose)
      __cv_msg("  Specify section(s) will be discarded before simulation.\n");
     break;
    case CO_NOTCHKS:
     __no_tchks = TRUE;
     if (__verbose)
      __cv_msg("  Timing checks will be discarded before simulation.\n");
     break;
    case CO_LIBNOCELL:
     __lib_are_cells = FALSE;
     if (__verbose)
      __cv_msg(
       "  Library modules will not be cells unless in `celldefine region.\n");
     break;
    case CO_DMP_VARS:
     __dmpvars_all = TRUE; 
     /* if already using fsdb - continue to use fsdb */
     if (__is_fst)
      {
       __gfwarn(679, olp->optfnam_ind, olp->optlin_cnt,
        "+dumpvars used along with +fstvars - +using fstvars");
      }
     if (__verbose)
      {
       __cv_msg("  All variables will be dumped in VCD format.\n");
      }
     break;
    /* AIV 11/21/07 - need to dump all variables via the command line */
    /* this is used for running regression tests on dumpvars */
    case CO_FST_DUMP2FST:
     __fst_convert_dump2fst = TRUE;
     if (__dv_fnam != NULL) __my_free(__dv_fnam, strlen(__dv_fnam));
     __dv_fnam = __pv_stralloc(DFLFSTFNAM);
     __is_fst = TRUE; 
     if (__verbose)
      {
       __cv_msg("  Converting all $dump* calls to $fst format.\n");
      }
     break;
    /* AIV 04/21/10 - fst dumping on the command line */
    case CO_FST_PARALLEL:
     if (__verbose)
      {
       __cv_msg("  FST Parallel mode turned on.\n");
      }
     __fst_parallel = TRUE;
     break;
    /* AIV 04/25/10 - fst dumping with buffering on the command line */
    case CO_FST_PARALLEL2:
     if (__verbose)
      {
       __cv_msg("  FST Parallel mode 2 turned on.\n");
      }
     __fst_parallel = TRUE;
     __fst_parallel2 = TRUE;
     break;
    case CO_FST_VARS_REPACK:
     if (__verbose)
      {
       __cv_msg("  FST Repacking turned on.\n");
      }
     __fst_repack = TRUE;
    /*FALLTHRU */
    case CO_FST_VARS:
     /* if already using dumpvars continue to use - don't switch to fst */
     if (__dmpvars_all)
      {
       __gfwarn(679, olp->optfnam_ind, olp->optlin_cnt,
        "+fstvars used along with +dumpvars - using +dumpvars");
       break;
      }
     if (__dv_fnam != NULL) __my_free(__dv_fnam, strlen(__dv_fnam));
     __dv_fnam = __pv_stralloc(DFLFSTFNAM);
     __is_fst = TRUE; 
     __dmpvars_all = TRUE; 
     if (__verbose)
      {
       __cv_msg("  All variables will be dumped in FST format.\n");
      }
     break;
/* SJM 04-25-14 - for binary that can't gen .s files (piped only) */
/* could if def this out with: "#ifdef __CVC_DEBUG" */
    case CO_OPT_DEBUG:
     /* turn on vm insn compiler debug output (mode) */
     __opt_debug_flg = TRUE;
     if (__verbose)
      __cv_msg("  CVC debugging information will be printed.\n");
     break;

    case CO_OPT_BLOCK_TRACE:
     /* turn on vm insn compiler debug output (mode) */
     __opt_block_trace = TRUE;
     if (__verbose)
      __cv_msg("  CVC block tracing will be printed.\n");
     break;
    case CO_OPT_VALTRK:
     __opt_valtrk = TRUE;
     if (__verbose)
      __cv_msg("  CVC value tracking optimization will be used.\n");
     break;
    case CO_TRK_VERBOSE:
     /* special case of verbose message for TRK optimizer */
     __opt_trk_verbose = TRUE;
     if (__verbose)
      __cv_msg("  CVC value tracking verbose messages will be printed.\n");
     break;
    case CO_ASM_VAR_NAMES:
     /* turn on vm insn compiler debug output (mode) */
     __opt_emit_var_names = TRUE;
     if (__verbose)
      __cv_msg("  CVC ASM will use variable names if short enough.\n");
     break;
    case CO_CVC_STATS: 
     __opt_prt_stats = TRUE;
     if (__verbose)
      __cv_msg("  CVC compilation statistics will be printed.\n");
     break;
    case CO_OPT_LEVEL_2:
     __compiled_sim = TRUE;
     __optimize_level = 2;
     __no_iact = TRUE;
     if (__verbose) __cv_msg("  Optimization level 2 selected.\n");
     break;
    case CO_DMP_FLOWG:
     __dump_flowg = TRUE; 
     if (__verbose) __cv_msg("  Dumping the flow graph.\n");
     break;
    case CO_SHOW_ASM:
     __show_asm = TRUE; 
     if (__verbose)
      {
       __cv_msg("  Creating actual .s files instead of piping to as cmd.\n");
      }
     break;
    case CO_ASM_EMIT_LOC:
     sav_olp = olp;
     olp = olp->optlnxt; 
     if (olp != NULL) chp = olp->opt;
     if (olp == NULL || olp->is_emark || *chp == '+' || *chp == '-')
      {
bad_asm_loc:
       __gfwarn(999, sav_olp->optfnam_ind, sav_olp->optlin_cnt,
        "+asm_emit_loc [value] option illegal - ignored");
       continue;
      }
     olp->optnum = -2;
     if (sscanf(chp, "%d", &tmp) != 1 || tmp < 0 || tmp > 4)
      goto bad_asm_loc;

     /* SJM 02/14/06 - 1 no longer possible - emit error */
     if (tmp == 1) goto bad_asm_loc;

     __asm_emit_loc = tmp;
     break;
    case CO_USE_INTERP_DPI_MK:
     /* SJM 12-29-10 - need separate option for debugging interp dpi wrapper */
     /* .so lib creation */
     __use_interp_dpi_mk = TRUE; 
     if (__verbose)
      {
       __cv_msg("  For debugging interpreter dpi will use a makefile.\n");
      }
     break;
/* SJM 04-25-14 - if do not want to allow .s file gen at all */
/* __CVC_DEBUG #endif would go here */
    case CO_PWD_TMP:
     __use_pwd_as_tmp = TRUE;  
     if (strcmp(__usedir_cp, "") != 0)
      {
       __gfwarn(4310, olp->optfnam_ind, olp->optlin_cnt,
        "previous +usedir=%s directory name for temp files option selected - +work overrides",
        __usedir_cp);
      }
     if (__verbose)
      __cv_msg("  CVC using pwd as work directory.\n");
     break;
    case CO_USEDIR:
     /* AIV 07/16/12 - now allowing +usedir= to setting working directory */
     /* to use instead of /tmp for temp work area */
     /* +usedir=10 - set the new max value */
     chp2 = strchr(olp->opt, '=');
     /* DBG remove -- */
     if (chp2 == NULL) __misc_terr(__FILE__, __LINE__);
     /* ---- */
     chp2++;

     /* SJM 02-01-13 - now checking for both plus work and use dir */
     if (__use_pwd_as_tmp)
      {
       __gfwarn(4304, olp->optfnam_ind, olp->optlin_cnt,
        "both +usedir= work directory name for temp files and +work to use PWD directory options used - +work overrides");
       break;
      }

     if (__verbose) __cv_msg("  CVC using %s as work directory.\n", chp2);
     /* AIV 08/06/12 - should not emit error if tmp directory is removed */
     /* for cvcsim executable */
     if (stat(chp2, &st) != 0 && !__running_cvc_exe)
      {
       __gfwarn(4308, olp->optfnam_ind, olp->optlin_cnt,
        "+usedir directory does not exist %s - using /tmp/", chp2);
      }
     else strcpy(__usedir_cp, chp2);
     break;
    case CO_REAL_WARNS:
     __real_warns = TRUE;
     if (__verbose) __cv_msg("  CVC emitting real NaN/Inf warnings.\n");
     break;
    case CO_COMPILED_OPT_SIM:
     __compiled_sim = TRUE;
     /* AIV 10/14/08 - -O now turns on inlining of code generation */
     __inline_code = TRUE;   
     /* AIV 01/12/09 - -O now turns on optimizing of register allocation */
     __opt_reg_alloc = TRUE;
     /* AIV LOOKATME - only supporting one level -O for now */
     /* __optimize_level = 0; */
     __no_iact = TRUE;
#ifndef __CVC_RT__
     if (__verbose) __cv_msg("  CVC optimized compiled simulation on.\n");
#endif
     break;
    case CO_COMPILED_OPT_SIM_GATE:
     __compiled_sim = TRUE;
     __opt_reg_alloc = TRUE;
     __no_iact = TRUE;
#ifndef __CVC_RT__
     if (__verbose) __cv_msg("  CVC optimized gate simulation on.\n");
#endif
     break;
    case CO_TWO_STATE:
     __opt_two_state = TRUE;
     if (__verbose) __cv_msg("  CVC running in two state mode.\n");
     break;
    case CO_TWO_STATE_NO_WIRE:
     __opt_two_state = TRUE;
     __opt_two_state_no_wires = TRUE;
     if (__verbose) 
      {
       __cv_msg("  CVC running in two state mode with 4-state wires.\n");
      }
     break;
    case CO_NBAOPT:
     __opt_nbaopt = TRUE;
     if (__verbose) __cv_msg("  CVC ignoring non-blocking delays.\n");
     break;
    case CO_PIPE:
     __my_popen = TRUE;
     if (__verbose) __cv_msg("  CVC using faster piping during compilation.\n");
     break;
#ifdef __XPROP__
    /* turn on xprop */
    case CO_XPROP:
     /* cannot use xprop and xprop2 */
     if (__xprop2)
      {
       __gferr(1990, olp->optfnam_ind, olp->optlin_cnt,
        "+xprop cannot be used with +xprop2 - only one may be used");
      }
     __xprop = TRUE;
     if (__verbose) 
      {
       __cv_msg("  CVC running in X propagation mode.\n");
      }
     break;
    /* turn on xprop - style 2 */
    case CO_XPROP2:
     /* cannot use xprop and xprop2 */
     if (__xprop)
      {
       __gferr(1990, olp->optfnam_ind, olp->optlin_cnt,
        "+xprop cannot be used with +xprop2 - only one may be used");
      }
     __xprop = TRUE;
     __xprop2 = TRUE;
     if (__verbose) 
      {
       __cv_msg("  CVC running in X propagation 2 mode.\n");
      }
     break;
    /* turn on xprop tracing */
    case CO_XPROP_TRACE:
     __xprop_trace_on = TRUE;
     if (__verbose) 
      {
       __cv_msg("  CVC running in X propagation tracing mode.\n");
      }
     //AIV XPROP - also need option to pass xprop file name - using default
     if ((__xprop_trace_fp = __tilde_fopen(DFLT_XPROPFNAM, "w")) == NULL)
      {
        __gfwarn(641, olp->optfnam_ind, olp->optlin_cnt,
         "cannot open xprop trace file %s", DFLT_XPROPFNAM);
       return;
      }
     break;
    case CO_XPROP_TRACE_SUPPRESS:
     if (__verbose) 
      {
       __cv_msg("  CVC suppressing X propagation tracing at initialization.\n");
      }
     __xprop_xtrace_suppress = TRUE;
     break;
    /* set a max value of xprop stmt to trace */
    case CO_XPROP_TRACE_MAX:
     /* +xtracemax=10 - set the new max value */
     chp2 = strchr(olp->opt, '=');
     /* DBG remove -- */
     if (chp2 == NULL) __misc_terr(__FILE__, __LINE__);
     /* ---- */
     chp2++;
      __xprop_cond_max = atoi(chp2);   

     /* if 0 set to large int */
     if (__xprop_cond_max == 0) 
       __xprop_cond_max = 0xfffffff0;

     if (__verbose)
      {
       __cv_msg("  CVC X propagation tracing will max changed to %d.\n",
        __xprop_cond_max);
      }
     break;
    /* setup xprop with exprs evaled to preserve xs */
    case CO_XPROP_AND_OR:
     /* T => preserve xs for |,&, ||, &&  */
     __xprop_and_or_xs = TRUE; 
     if (__verbose)
      {
       __cv_msg("  CVC X propagation will include |, &, ||, && statements.\n");
      }
     break;
    /* record xprop excluded stmts */
    case CO_XPROP_EXCLUDED: 
     __xprop_not_eligible = TRUE;
     if (__verbose) 
      {
       __cv_msg("  CVC X propagation not eligible statement recording turned on.\n");
      }
     __setup_xprop_not_eligible_file(olp);
     break;
    case CO_XPROP_NO_EDGES:
     /* turn off always @(x) edge X detection and X-propagation */
     __no_xprop_edges = TRUE;
     __do_xprop_xedge_vectors = FALSE;
     if (__verbose)
      {
       __cv_msg("  CVC X propagation will not check for always @(x) edges.\n");
      }
     break;
    case CO_XPROP_NO_VECTORED_EDGES:
     __no_xprop_vectors = TRUE;
     __do_xprop_xedge_vectors = FALSE;
     if (__verbose)
      {
       __cv_msg("  CVC X propagation will only check for always @(x) scalar edges.\n");
      }
     break;
    case CO_XPROP_ONLY_EDGES:
     /* turn off always @(x) where edge X does not have posedge/negedge */
     __xprop_pos_neg_only = TRUE;
     __do_xprop_xedge_vectors = FALSE;
     if (__verbose)
      {
       __cv_msg("  CVC X propagation will only check for always @(posedge/negedge) edges.\n");
      }
     break;
#endif
    case CO_UNROLL_LOOPS:
     /* AIV 04/04/11 - turn on loop unrolling - now just for loops */
     __opt_unroll_loops = TRUE;
     if (__verbose) __cv_msg("  CVC loop unrolling on.\n");
     break;

#ifndef __CVC32__
    /* AIV 08/28/09 - use large 64-bit model - large gate level designs */ 
    case CO_LARGE_MODEL:
     __cvc_use_large_model = TRUE;
#ifndef __CVC_RT__
     if (__verbose) __cv_msg("  CVC compiling large model.\n");
#endif
     break;
#endif
    case CO_EXECUTE:
     /* compile and execute the compiled binary */
     __execute_compiled = TRUE;
     if (__verbose) __cv_msg("  CVC auto execute on.\n");
     break;
    case CO_INTERPRETER:
     __compiled_sim = FALSE;
     __optimize_level = 0;
     __no_iact = FALSE;
     if (__verbose)
      {
       __cv_msg("  Interpreted Simulation.\n");
      }
     break;
    case CO_COMPILE:
     sav_olp = olp;
     olp = olp->optlnxt; 
     if (olp != NULL) chp = olp->opt;
     if (olp == NULL || olp->is_emark || chp == NULL || *chp == '+'
     || *chp == '-')
      {
       /* AIV 05/13/09 - noticed this was missing string but passed %s */
       __gferr(999, sav_olp->optfnam_ind, sav_olp->optlin_cnt,
        "%s output executable not followed by file name -o", chp);
       continue;
      }
     olp->optnum = -2;
     __exe_name = __pv_stralloc(chp); 
     if (__verbose)
      {
       __cv_msg( "  Compiled simulation executable saved to file %s\n",
        __exe_name);
      }
     break;
    /* same as +acc+1 - need two seperate CO_'s to avoid NC +access naming */
    case CO_ACC_NO_NUM:
     if (__verbose)
      {
       __cv_msg("  Design compiled for VPI_ PLI access level 1.\n");
      }
     __pli_access_level = 1;
     break;
    case CO_ACC:
     chp = &(olp->opt[5]);
     /* go one pass for the +acc+ */
     level = atoi(chp);   
     if (level <= 0 || level > 4)
      {
       __gferr(999, olp->optfnam_ind, olp->optlin_cnt,
       "+acc+ must be passed a level as an integer between 1 and 4");
      level = 0;
      }
     if (__verbose)
      {
       __cv_msg("  Design compiled for VPI_ PLI access level %d.\n", level);
      }
     __pli_access_level = level;
     break;
    default: __case_terr(__FILE__, __LINE__);
   }
   olp = olp->optlnxt; 
  }
 /* some option consistency checks */
 if (__intsig_prt_snapshot && !__no_iact)
  {
   __pv_warn(508,
    "+snapshot option no effect because +nointeractive used or CVC +interp not used");
  }
}

/*
 * build input file list after freeing list for argumnts
 * know now done with arguments
 */
static void bld_inflist(void)
{
 struct optlst_t *olp, *olp2; 

 /* must not free option files - need for mc scan args pli task ? */
 /* notice can copy because [args] and *none* same length */
 strcpy(__in_fils[0], "*none*");
 __last_optf = __last_inf;

 for (olp = __opt_hdr; olp != NULL; olp = olp->optlnxt) 
  {
   /* -1 are unrecognized +/- options, -2 is file used as arg, > 0 is opt */
   /* so 0 is verilog input file */ 
   if (olp->optnum == CO_F)
    {
     olp2 = olp->optlnxt;
     if (olp2 != NULL) olp = olp2;
     continue;
    }
   /* added markers automaticaly ignored */
   if (olp->optnum == 0) __add_infil(olp->opt);
  }
}

/*
 * add an in file
 * used first for -f command file and then reused for source and include
 * files
 * last inf is location of new file
 * fatal error if more than 64k in files
 */
extern void __add_infil(char *fnam)
{
 if (++__last_inf >= __siz_in_fils) __grow_infils(__last_inf);
 __in_fils[__last_inf] = __pv_stralloc(fnam);
}

/*
 * re allocate in fils pointer table 
 */
extern void __grow_infils(int32 new_last)
{
 size_t osize, nsize;
 size_t save_mem_size;

 /* file index must fit in word32 16 bits still */
 if (new_last >= 0xfffe)
  {
   __fterr(305,
    "too many comand -f , input, `include and library files (%d)",
    0xfffe);
  }
 /* re-alloc area */
 osize = __siz_in_fils*sizeof(char *); 
 __siz_in_fils *= 2;
 /* if hits fffd this will do a realloc that does nothing */
 if (__siz_in_fils >= 0xfffd) __siz_in_fils = 0xffff;
 nsize = __siz_in_fils*sizeof(char *); 
 /* notice realloc may move but works because ptrs to the strings */
 /* AIV 11/12/09 - this causes the memory checking scheme to see if */
 /* comp so if > 500 files was doing this - just save and put back */
 /* AIV BEWARE - memory off slightly here - but rarely reached */
 save_mem_size = __mem_use;
 __in_fils = (char **) __my_realloc(__in_fils, osize, nsize);
 __mem_use = save_mem_size;
}
     
/*
 * extract SDF annotation file name and optional scope and save in list
 */
static void do_sdflocdef(char *sdfloc, char *optfnam, int32 oplin_cnt)
{
 struct sdfnamlst_t *sdfp, *sdfp2, *last_sdfp;
 char *chp, *chp2; 
 char fnam[IDLEN], pthnam[IDLEN]; 

 /* form is [file name]+[optional scope] */
 strcpy(pthnam, "");
 if ((chp = strchr(sdfloc, '+')) == NULL) strcpy(fnam, sdfloc);
 else  
  {
   if (chp == sdfloc || chp[-1] == '\\')
    {
     chp2 = chp + 1;
     for (;;)
      {
       if ((chp = strchr(chp2, '+')) == NULL)
        { strcpy(fnam, sdfloc); goto sep_done; }

       if (chp[-1] != '\\') goto bld_both;
       chp2 = chp + 1;
      }
    }
bld_both:
   strncpy(fnam, sdfloc, chp - sdfloc);
   fnam[chp - sdfloc] = '\0';  
   strcpy(pthnam, ++chp);
  }
  
sep_done:
 sdfp = (struct sdfnamlst_t *) __my_malloc(sizeof(struct sdfnamlst_t));
 sdfp->fnam = __pv_stralloc(fnam); 
 sdfp->scopnam = __pv_stralloc(pthnam);  
 sdfp->optfnam = __pv_stralloc(optfnam);
 sdfp->opt_slcnt = oplin_cnt;
 sdfp->sdfnamnxt = NULL;
 last_sdfp = NULL;

 /* put on end since must do in order */
 for (sdfp2 = __sdflst; sdfp2 != NULL; sdfp2 = sdfp2->sdfnamnxt)
  last_sdfp = sdfp2;
 if (last_sdfp == NULL) __sdflst = sdfp; else last_sdfp->sdfnamnxt = sdfp;
 if (strcmp(sdfp->scopnam, "") == 0) 
  {
   if (__verbose)
    {
     __cv_msg(
      "  Delay annotation values read from SDF 3.0 file \"%s\" design context.\n",
      sdfp->fnam); 
    }
  }
 else
  {
   if (__verbose)
    {  
     __cv_msg(
      "  Delay annotation values read from SDF 3.0 file \"%s\" scope context %s.\n",
     sdfp->fnam, sdfp->scopnam); 
    }
  }
}

/*
 * process a +define argument and do the define and emit verbose msg 
 *
 * know defarg starts just after +define+
 */
static void do_cmdmacdef(char *defarg, struct optlst_t *olp) 
{
 int32 slen; 
 char *chp, *chp2, *chp3;
 char optnam[IDLEN], optval[IDLEN], s1[3*IDLEN];

 for (chp = defarg;;)
  {
   /* know chp pointer to char after current + */ 
   /* separate off string to next '+' */
   if ((chp2 = strchr(chp, '+')) == NULL) { strcpy(s1, chp); goto got_def; } 

got_plus:
   chp2--;
   /* if escaped +, keep looking until find end non escaped */
   if (*chp2 == '\\')
    {
     chp2++; chp2++;
     chp3 = chp2;
     if ((chp2 = strchr(chp3, '+')) == NULL)
      { strcpy(s1, chp); goto got_def; }
     goto got_plus;
    }
   /* nove back to point to + */
   chp2++;
   strncpy(s1, chp, chp2 - chp);
   s1[chp2 - chp] = '\0'; 

got_def:
   /* now have define in s1 with chp2 either name nil */
   optnam[0] = '`'; 
   if ((chp = strchr(s1, '=')) == NULL)
    {
     if (strcmp(s1, "") == 0)
      {
bad_nam:
       __gferr(962, olp->optfnam_ind, olp->optlin_cnt,
        "+define+[name]+ ... or +define+[name]=[value] option empty [name] illegal");
       return;
      }
     strcpy(&(optnam[1]), s1);
#ifndef __CVC_RT__
     if (__verbose)
      __cv_msg("  `define of %s (no value form) added from command option.\n",
       s1); 
#endif
     __do_macdefine(optnam, "");
    }
   else
    {
     strncpy(&(optnam[1]), s1, chp - s1); 
     /* notice plus 1 because 1st char of optnam already filled */
     optnam[chp - s1 + 1] = '\0';  
     if (strcmp(optnam, "`") == 0) goto bad_nam;
     chp++;
     if (*chp == '\\' && *chp == '"') chp++;
     strcpy(optval, chp);
     slen = strlen(optval);
     /* if escaped " remove escape */
     if (slen > 1)
      {
       if (optval[slen - 2] == '\\' && optval[slen - 1] == '"')
        { optval[slen - 2] = optval[slen - 1]; optval[slen - 1] = '\0'; }
      }
#ifndef __CVC_RT__
     if (__verbose)
      __cv_msg("  `define of %s value %s added from command option.\n",
       &(optnam[1]), optval); 
#endif
     __do_macdefine(optnam, optval);
    }
   /* chp2 either points to NULL or ending '+' */
   /* end can be NULL or final '+' */
   if (chp2 == NULL) break;
   chp2++;
   if (*chp2 == '\0') break;
   chp = chp2;
  }
}

/*
 * build (add to) +incdir path table
 *
 * concatenate on end (in option order) for +incdir+ list
 * if path does not end in / one is added - `include cated on end
 * and attempt is made to open that path
 */
static int32 bld_incdtab(char *incdirptr, struct optlst_t *olp) 
{
 int32 len;
 char *cp, *cpbg, *chp2;
 char s1[IDLEN], s2[IDLEN];

 len = strlen(incdirptr);
 if (len == 0)
  {
   __gfwarn(505, olp->optfnam_ind, olp->optlin_cnt,
    "+incdir+ option missing include file path name list - option ignored");
   return(FALSE);
  }

 /* if optional ending plus left out - add here */
 if (incdirptr[len - 1] != '+')
  {
   chp2 = s2;
   strcpy(chp2, incdirptr);
   chp2[len] = '+';
   chp2[len + 1] = '\0';
  }
 else chp2 = incdirptr;

 for (cpbg = chp2, len = 0;;)
  {
   /* notice - if no + will just be one - this is internal fmt screw up */
   if ((cp = strchr(cpbg, '+')) == NULL || (len = cp - cpbg) >= IDLEN - 1)
    __misc_terr(__FILE__, __LINE__);

   if (++__last_incdir >= MAXINCDIRS)
    __pv_terr(306, "+incdir+ option - too many include file paths (%d)",
     MAXINCDIRS);
   if (len > 0)
    {
     strncpy(s1, cpbg, len);
     if (s1[len - 1] != '/') { s1[len] = '/'; len++; }
     s1[len] = '\0';
     __incdirs[__last_incdir] = __pv_stralloc(s1);
    }
   else
    {
     __gfwarn(514, olp->optfnam_ind, olp->optlin_cnt,
      "+incdir+ path list contains empty (++) path - just skipping"); 
     __last_incdir--;
    }
   cpbg = ++cp;
   if (*cpbg == '\0') break;
  }
 return(TRUE);
}

/*
 * process +loadpli1 or +loadvpi PLI dynamic library and bootstrap load arg
 *
 * formats exactly:
 *   +loadpli1=[.so lib]:[boostrap routines (, sep - none legal)]
 *   +loadvpi=[.so lib]:[boostrap routines (, sep - none legal)]
 *
 * LOOKATME - option must be contiguous - some shells may require
 * quoting on command line (not in -f files) but quotes stripped by shell 
 */
static struct loadpli_t *bld_loadpli_lbs(char *loadpliptr,
 struct optlst_t *olp, int32 is_pli1)
{
 int32 len;
 char *cp;
 char lbnam[IDLEN], rnams[IDLEN], onam[RECLEN];
 struct loadpli_t *ldp;

 /* AIV 04/07/09 - need to record if using PLI *.so libraries */
 __design_has_ld_pli_libs = TRUE; 

 if (is_pli1) strcpy(onam, "+loadpli1="); else strcpy(onam, "+loadvpi=");
 len = strlen(loadpliptr);
 if (len == 0)
  {
   __gfwarn(505, olp->optfnam_ind, olp->optlin_cnt,
    "%s option missing [dynamic lib]:[bootstrap routine list] pair - option ignored",
    onam);
   return(NULL);
  }
 /* if dynamic library missing - use dlsym look up in all other libs */
 if (loadpliptr[0] == ':')
  { 
   /* library missing - ok if boot routine defined in some other dyn lib */
   __gfwarn(505, olp->optfnam_ind, olp->optlin_cnt,
    "%s [dynamic lib] omitted - required because mixed static/dynamic not supported - option ignored",
    onam);
   return(NULL);
  }
 for (cp = &(loadpliptr[len - 1]);;)
  {
   if (*cp == ':') break;
   if (--cp == loadpliptr)
    {
     __gfwarn(505, olp->optfnam_ind, olp->optlin_cnt,
    "%s [dynamic lib] and [bootstrap routine] ':' separator missing - option ignored",
     onam);
     return(NULL);
    }
  }
 strncpy(lbnam, loadpliptr, cp - loadpliptr);
 lbnam[cp - loadpliptr] = '\0'; 
 cp++;
 strcpy(rnams, cp);
 /* FIXME ??? - think should allow omitted lib and static and dynamic  */
 if (strcmp(rnams, "") == 0)
  {
   /* missing bootstrap ok since other load pli option can supply boostrap */ 
   __gfwarn(505, olp->optfnam_ind, olp->optlin_cnt,
    "%s [bootstrap routine] missing - ok since not required", onam);
   return(NULL);
  }

 /* LOOKATME - maybe should remove extra ' or " */
 /* fill the load pli record */
 ldp = (struct loadpli_t *) __my_malloc(sizeof(struct loadpli_t));
 if (is_pli1) ldp->pli1_option = TRUE; else ldp->pli1_option = FALSE;
 ldp->libnam = __pv_stralloc(lbnam);
 ldp->load_plinxt = NULL;
 if (!bld_boot_rout_list(ldp, rnams))
  {
   __my_free(ldp, sizeof(struct loadpli_t));
   return(NULL);   
  }

 if (is_pli1)
  {
   /* need separate lists since pli1 can add user systf tfcell elements */
   if (__pli1_dynlib_hd == NULL)
    { __pli1_dynlib_hd = __pli1_dynlib_end = ldp; }
   else
    {
     /* add to end - libs must be processed in option order */  
     __pli1_dynlib_end->load_plinxt = ldp;
     __pli1_dynlib_end = ldp;
    }
   return(ldp);
  }

 /* build the vpi list */
 if (__vpi_dynlib_hd == NULL) { __vpi_dynlib_hd = __vpi_dynlib_end = ldp; }
 else
  {
   /* add to end - libs must be processed in option order */  
   __vpi_dynlib_end->load_plinxt = ldp;
   __vpi_dynlib_end = ldp;
  }
 return(ldp);
}

/*
 * routine to check 
 */
static int32 bld_boot_rout_list(struct loadpli_t *ldp, char *rnams)
{
 int32 len;
 struct dynboot_t *dnbp, *last_dnbp;
 char *chp2, *chp;
 char s1[RECLEN];

 /* first check for one routine name or , separated list - no spaces */  
 if (!check_rnam_str(rnams)) return(FALSE);

 last_dnbp = NULL;
 chp2 = rnams;
 for (chp = rnams;; chp++)
  {
   if (*chp == ',' || *chp == '\0')
    {
     len = chp - chp2;
     strncpy(s1, chp2, len);
     s1[len] = '\0';
     dnbp = (struct dynboot_t *) __my_malloc(sizeof(struct dynboot_t));
     dnbp->bootrout_nam = __pv_stralloc(s1);
     dnbp->dynu.vpi_rout = NULL;
     dnbp->ret_veriusertf = NULL;
     dnbp->dynbootnxt = NULL;

     if (last_dnbp == NULL) ldp->dynblst = dnbp;
     else last_dnbp->dynbootnxt = dnbp;
     last_dnbp = dnbp;

     if (*chp == '\0') break;
     chp2 = chp;
     chp2++;
    }
  }
 return(TRUE);
}

/*
 * check to make sure boot routine has legal no space , sep list
 */
static int32 check_rnam_str(char *rnams)
{
 int32 len;
 char *chp, *chp2;

 if (strlen(rnams) == 1 && rnams[0] == ',') return(FALSE);
 chp2 = rnams;
 for (chp = rnams; *chp != '\0'; chp++)
  {
   if (isspace(*chp)) return(FALSE);
   if (*chp == '.') return(FALSE);
   if (*chp == ',')
    {
     len = chp - chp2;
     if (len == 0) return(FALSE);
     chp2 = chp + 1;
    }
  }
 chp--;
 if (*chp == ',') return(FALSE);
 return(TRUE);
}

/*
 * build (add to) lib. ext. table
 * concatenate on end (in option order) for +libext+ list
 *
 * LOOKATME - following XL only one +libext+ option allowed - maybe should
 * allow more (this routine never called if __last lbx > -1)
 */
static int32 bld_lbxtab(char *lbxptr, struct optlst_t *olp)
{
 int32 len;
 char *cp, *cpbg, *chp2;
 char s1[IDLEN], s2[IDLEN];

 len = strlen(lbxptr);
 if (len == 0)
  {
   __gfwarn(505, olp->optfnam_ind, olp->optlin_cnt,
    "+libext+ option missing libary extension list - ignored");
   return(FALSE);
  }
 
 /* if optional ending plus left out - add here */
 if (lbxptr[len - 1] != '+')
  { chp2 = s2; strcpy(chp2, lbxptr); chp2[len] = '+'; chp2[len + 1] = '\0'; }
 else chp2 = lbxptr;

 for (cpbg = chp2, len = 0;;)
  {
   /* notice - if no + will just be one - this is internal fmt screw up */
   if ((cp = strchr(cpbg, '+')) == NULL || (len = cp - cpbg) >= IDLEN - 1)
    __misc_terr(__FILE__, __LINE__);

   if (++__last_lbx >= MAXLBEXTS)
    {
     __pv_terr(306, "+libext+ option - too many library suffixes (%d)",
      MAXLBEXTS);
    }
   /* notice empty is legal extension - name as is */
   if (len > 0) strncpy(s1, cpbg, len);
   s1[len] = '\0';
   __lbexts[__last_lbx] = __pv_stralloc(s1);
   cpbg = ++cp;
   if (*cpbg == '\0') break;
  }
 return(TRUE);
}

/*
 * add one library file to list
 */
static void add_lbfil(char *fnam, char tlet)
{
 struct vylib_t *vyp;

 vyp = alloc_vylib(fnam);
 if (tlet == 'y') __num_ylibs++;
 else if (tlet == 'v') __num_vlibs++;
 else __case_terr(__FILE__, __LINE__);
 vyp->vytyp = tlet;
 if (__vyhdr == NULL) __vyhdr = vyp; else __end_vy->vynxt = vyp;
 __end_vy = vyp;
}

/*
 * allocate a vylib entry
 */
static struct vylib_t *alloc_vylib(char *nam)
{
 struct vylib_t *vyp;

 vyp = (struct vylib_t *) __my_malloc(sizeof(struct vylib_t));
 vyp->vyu.vyfnam = __pv_stralloc(nam);
 vyp->vyfnam_ind = 0;
 vyp->vytyp = ' ';
 vyp->yfiles = NULL;
 vyp->vynxt = NULL;
 return(vyp);
}

struct warnsup_t {
  int32 rngbeg;
  int32 rngend;
};

const struct warnsup_t warnsuptab[] = {
 /* 1 to 399 - fatal errors */
 /* 400 to 679 suppressable normal informs and warnings */
 { 400, 679 },
 /* 680 to 1399 normal errors */ 
 /* iact errors 1400 to 1499 can be suppressed */
 { 1400, 1499 },
 /* 1500 to 1599 are SDF errors - not suppressable */
 /* 1600-1699 are iact warnings - can be suppressed */
 { 1600, 1699 },
 /* 1700 to 1999 are PLI errors */
 /* 2000 to 2199 are PLI warns and informs */
 { 2000, 2199 },
 /* 2200 to 2499 are vendor specific warns and informs */
 { 2200, 2499 },
 /* 2500 to 2599 are code gen warns and informs */
 { 2500, 2599 },

 /* 2600 - 2899 vendor specific errors or unused - not suppressable */
 /* 2900 - 2999 optimizer errors or unused - not suppressable */
 /* 3000 to 3099 are new Verilog 2000 informs - suppressable */
 /* 3100 to 3399 are new Verilog 2000 warns - suppressable */
 { 3000, 3399 },
 /* 3400 to 3799 Verilog 2000 errors - not suppressable */ 

 /* 3800 to 4299 are new SV informs - suppressable */
 /* 4300 to 4799 are new SV warns - suppressable */
 { 3800, 4799 },
 /* 4800 to 5500 are new SV errors - not suppressable */
 { -1, -1 }
};

/*
 * return T if error message is suppressable (i.e. inform or warn)
 */
extern int32 __enum_is_suppressable(int32 errnum)
{
 int32 i;

 for (i = 0;; i++)
  {
   if (warnsuptab[i].rngbeg == -1) break;

   if (errnum >= warnsuptab[i].rngbeg && errnum <= warnsuptab[i].rngend)
    return(TRUE);
  }
 return(FALSE);
}

/*
 * add each +num+ num to table of suppressed warnings (or in 1) 
 * this returns F on error 
 * know if + at end left off, will have been added
 */
static int32 add_suppwarn(char *pluslst, struct optlst_t *olp) 
{
 int32 ernum, len, noerr;
 char *cp, *cpbg;
 char s1[IDLEN];

 cpbg = &(pluslst[16]);
 for (noerr = TRUE, len = 0;;)
  {
   if ((cp = strchr(cpbg, '+')) == NULL || (len = cp - cpbg) >= IDLEN)
    {
     __misc_terr(__FILE__, __LINE__);
     return(FALSE);
    }
   strncpy(s1, cpbg, len);
   s1[len] = '\0';
   if (sscanf(s1, "%d", &ernum) != 1)
    {
     __gfwarn(513, olp->optfnam_ind, olp->optlin_cnt,
      "+suppress_warnings + separed string %s unreadable - ignored", s1); 
     noerr = FALSE;
     goto nxt_msg;
    }
   if (!__enum_is_suppressable(ernum))
    {
     __gfwarn(513, olp->optfnam_ind, olp->optlin_cnt,
      "+suppress_warnings number %d unknown warn or inform - ignored",
      ernum); 
     noerr = FALSE;
     goto nxt_msg;
    }

   /* SJM 06-21-09 - seroius bug - for cvc 64, wbits is wrong 64 */
   /* AIV 06/22/09 - make these all 32 not WBITS for 64 - always 32 */
   __wsupptab[ernum/INTBITS] |= (1 << (ernum % INTBITS)); 

nxt_msg:
   cpbg = ++cp;
   if (*cpbg == '\0') break;
  }
 return(noerr);
}

#include "cvc_wrhelp.h"

/*
 * write the help message to standard output and log file
 */
static void wrhelp(void)
{
 int32 i;

 for (i = 0; *txhelp[i] != '\0'; i++) __crit_msg("%s\n", txhelp[i]);
}

/*
 * BUILT IN INITIALIZATTON ROUTINES
 */

/* built-in Verilog gates */
/* gateid is, if has corresponding operator gate id, else G_ symbol */
static struct primtab_t prims[] = {
 /* special gate for continuous assign */
 /* notice since starts with number can never be found accidently */
 { G_ASSIGN, GC_LOGIC, NULL, "1-bit-assign" },
 { G_BITREDAND, GC_LOGIC , NULL, "and" },
 { G_BUF, GC_LOGIC, NULL, "buf" },
 { G_BUFIF0, GC_BUFIF, NULL, "bufif0" },
 { G_BUFIF1, GC_BUFIF, NULL, "bufif1" },
 { G_CMOS, GC_CMOS, NULL, "cmos" },
 { G_NAND, GC_LOGIC, NULL, "nand" },
 { G_NMOS, GC_MOS, NULL, "nmos" },
 { G_NOR, GC_LOGIC, NULL, "nor" },
 { G_NOT, GC_LOGIC, NULL, "not" },
 { G_NOTIF0, GC_BUFIF, NULL, "notif0" },
 { G_NOTIF1, GC_BUFIF, NULL, "notif1" },
 { G_BITREDOR, GC_LOGIC, NULL, "or" },
 { G_PMOS, GC_MOS, NULL, "pmos" },
 /* next 2 initialized so can drive fi>1 wires but do not exist */
 { G_PULLDOWN, GC_PULL, NULL, "pulldown" },
 { G_PULLUP, GC_PULL, NULL, "pullup" },
 { G_RCMOS, GC_CMOS, NULL, "rcmos" },
 { G_RNMOS, GC_MOS, NULL, "rnmos" },
 { G_RPMOS, GC_MOS, NULL, "rpmos" },
 { G_RTRAN, GC_TRAN, NULL, "rtran" },
 { G_RTRANIF0, GC_TRANIF, NULL, "rtranif0" },
 { G_RTRANIF1, GC_TRANIF, NULL, "rtranif1" },
 { G_TRAN, GC_TRAN, NULL, "tran" },
 { G_TRANIF0, GC_TRANIF, NULL, "tranif0" },
 { G_TRANIF1, GC_TRANIF, NULL, "tranif1" },
 { G_BITREDXOR, GC_LOGIC, NULL, "xor" },
 { G_REDXNOR, GC_LOGIC, NULL, "xnor" },
};
#define NPRIMS (sizeof(prims) / sizeof(struct primtab_t))

static void init_modsymtab(void)
{
 __cur_fnam_ind = 0;

 __cur_fnam = __in_fils[__cur_fnam_ind];
 __lin_cnt = 0;
 /* disguised trigger for expired copy expiration */
 __slotend_action = 0;
 /* this symbol table is not a symbol table of any symbol */
 __modsyms = __alloc_symtab(FALSE);
 __sym_addprims();
}

/*
 * add primitives to module type name symbol table - separate name space
 */
extern void __sym_addprims(void)
{
 int32 i;
 struct sy_t *syp;
 struct tnode_t *tnp;
 struct primtab_t *primp;

 for (i = 0, primp = prims; i < NPRIMS; i++, primp++)
  {
   /* spcial 1 bit continuous assign primitive - not searched in table */
   tnp = __vtfind(primp->gatnam, __modsyms);
   /* err if inconsistent primitive table */
   if (!__sym_is_new) __misc_terr(__FILE__, __LINE__);
   __add_sym(primp->gatnam, tnp);
   (__modsyms->numsyms)++;
   syp = tnp->ndp;
   syp->sytyp = SYM_PRIM;
   syp->sydecl = TRUE;
   syp->el.eprimp = primp;

   /* need global when 1 bit continuous assigns converted */
   if (primp->gateid == G_ASSIGN) __ca1bit_syp = syp;
  }
}

/*
 * predefined built-in system tasks
 *
 * system task arguments are defined by fixup checking code and follow
 * no pattern 
 *
 * SJM 03-22-14 - mostly in alphabetical order but do not need to be
 */
static struct systsk_t vsystasks[] = {
 { STN_CLEARDEBUG, "$cleardebug" },
 { STN_CLEAREVTRACE, "$clearevtrace" },
 { STN_CLEARTRACE, "$cleartrace" },
 { STN_DEFINEGROUPWAVES, "$define_group_waves" },
 { STN_DISPLAY, "$display" },
 { STN_DISPLAYB, "$displayb" },
 { STN_DISPLAYH, "$displayh" },
 { STN_DISPLAYO, "$displayo" },
 { STN_DUMPALL, "$dumpall" },
 { STN_DUMPFILE, "$dumpfile" },
 { STN_DUMPFLUSH, "$dumpflush" },
 { STN_DUMPLIMIT, "$dumplimit" },
 { STN_DUMPOFF, "$dumpoff" },
 { STN_DUMPON, "$dumpon" },
 { STN_DUMPPORTS, "$dumpports" },
 { STN_DUMPPORTSALL, "$dumpportsall" },
 { STN_DUMPPORTSFLUSH, "$dumpportsflush" },
 { STN_DUMPPORTSLIMIT, "$dumpportslimit" },
 { STN_DUMPPORTSOFF, "$dumpportsoff" },
 { STN_DUMPPORTSON, "$dumpportson" },
 { STN_DUMPVARS, "$dumpvars" },
 { STN_ERROR, "$error" },
 { STN_FATAL, "$fatal" },
 { STN_FCLOSE, "$fclose" },
 { STN_FDISPLAY, "$fdisplay" },
 { STN_FDISPLAYB, "$fdisplayb" },
 { STN_FDISPLAYH, "$fdisplayh" },
 { STN_FDISPLAYO, "$fdisplayo" },
 { STN_FINISH, "$finish" },
 { STN_FLUSHLOG, "$flushlog" }, 
 { STN_FMONITOR , "$fmonitor" },
 { STN_FMONITORB, "$fmonitorb" },
 { STN_FMONITORH, "$fmonitorh" },
 { STN_FMONITORO, "$fmonitoro" },
 { STN_FREEZEWAVES, "$freeze_waves" },
 { STN_FST_DUMPALL, "$fstDumpall" },
 { STN_FST_DUMPFILE, "$fstDumpfile" },
 { STN_FST_DUMPFLUSH, "$fstDumpflush" },
 { STN_FST_DUMPLIMIT, "$fstDumplimit" },
 { STN_FST_DUMPOFF, "$fstDumpoff" },
 { STN_FST_DUMPON, "$fstDumpon" },
 { STN_FST_DUMPREPACK, "$fstDumprepack" },
 { STN_FST_DUMPVARS, "$fstDumpvars" },
 { STN_FST_PARALLELOFF, "$fstParalleloff" },
 { STN_FST_PARALLELON, "$fstParallelon" },
 { STN_FSTROBE, "$fstrobe" },
 { STN_FSTROBEB, "$fstrobeb" },
 { STN_FSTROBEH, "$fstrobeh" },
 { STN_FSTROBEO, "$fstrobeo" },
 { STN_FWRITE, "$fwrite" },
 { STN_FWRITEB, "$fwriteb" },
 { STN_FWRITEH, "$fwriteh" },
 { STN_FWRITEO, "$fwriteo" },
 { STN_GRREMOTE, "$gr_remote" },
 { STN_GRREGS, "$gr_regs" },
 { STN_GRSYNCHON, "$gr_synchon" },
 { STN_GRWAVES, "$gr_waves" },
 { STN_HISTORY, "$history" },
 { STN_INCSAVE, "$incsave" },
 { STN_INFO, "$info" },
 { STN_INPUT, "$input" },
 { STN_KEEPCMDS, "$keepcommands" },
 { STN_KEY, "$key" },
 { STN_LIST, "$list" },
 { STN_LOG, "$log" },
 { STN_MEMUSE, "$memuse" },
 { STN_MONITOR, "$monitor" },
 { STN_MONITORB, "$monitorb" },
 { STN_MONITORH, "$monitorh" },
 { STN_MONITORO, "$monitoro" },
 { STN_MONITOROFF, "$monitoroff" },
 { STN_MONITORON, "$monitoron" },
 { STN_NOKEEPCMDS, "$nokeepcommands" },
 { STN_NOKEY, "$nokey" },
 { STN_NOLOG, "$nolog" },
 { STN_PRINTTIMESCALE, "$printtimescale" },
 { STN_PSWAVES, "$ps_waves" },
 { STN_Q_ADD, "$q_add" },
 { STN_Q_EXAM, "$q_exam" },
 { STN_Q_INITIALIZE, "$q_initialize" },
 { STN_Q_REMOVE, "$q_remove" },
 { STN_READMEMB, "$readmemb" },
 { STN_READMEMH, "$readmemh" },
 { STN_RESET, "$reset" },
 { STN_RESTART, "$restart" },
 { STN_SAVE, "$save" },
 { STN_SCOPE, "$scope" },
 { STN_SDF_ANNOTATE, "$sdf_annotate" },
 { STN_SETDEBUG, "$setdebug" },
 { STN_SETEVTRACE, "$setevtrace" },
 { STN_SETTRACE, "$settrace" },
 { STN_SHOWALLINSTANCES, "$showallinstances" },
 { STN_SHOWEXPANDEDNETS, "$showexpandednets" },
 { STN_SHOWSCOPES, "$showscopes" },
 { STN_SHOWVARIABLES, "$showvariables" },
 { STN_SHOWVARS, "$showvars" },
 { STN_SNAPSHOT, "$snapshot" },
 { STN_SREADMEMB, "$sreadmemb" },
 { STN_SREADMEMH, "$sreadmemh" },
 { STN_STOP, "$stop" },
 { STN_STROBE, "$strobe" },
 { STN_STROBEB, "$strobeb" },
 { STN_STROBEH, "$strobeh" },
 { STN_STROBEO, "$strobeo" },
 { STN_SUPWARNS, "$suppress_warns" },
 { STN_ALLOWWARNS, "$allow_warns" },
 { STN_SYSTEM, "$system" },
 { STN_TIMEFORMAT, "$timeformat" },
 { STN_TRACEFILE, "$tracefile" },
 { STN_WRITE, "$write" },
 { STN_WRITEB, "$writeb" },
 { STN_WRITEH, "$writeh" },
 { STN_WRITEMEMB, "$writememb" },
 { STN_WRITEMEMH, "$writememh" },
 { STN_WRITEO, "$writeo" },
 /* AIV 09/05/03 - added for fileio - only one that is sys task */
 { STN_FFLUSH, "$fflush"},
 /* SJM 09/05/03 - also add the new fileio string forms - see 2001 LRM */
 /* SJM 05/21/04 - these are sys tasks not functs (but LRM inconsistent) */
 { STN_SWRITE, "$swrite" },
 { STN_SWRITEB, "$swriteb" },
 { STN_SWRITEH, "$swriteh" },
 { STN_SWRITEO, "$swriteo" },
 /* same as $swrite except 2nd arg (can be var) must be only format string */
 { STN_SFORMAT, "$sformat" },
 /* patches for getting models to compile pli tasks -- */
 /* STN_LAI_INPUTS, "$lai_inputs", */
 /* STN_LAI_OUTPUTS, "$lai_outputs", */
 /* STN_ERRORNTL, "$errorNTL", */
 /* STN_SUSPENDCHECK, "$suspendCheck", */
 { STN_WARNING, "$warning" },
#ifdef __XPROP__
 { STN_XTRACE_ON, "$xtraceon" },
 { STN_XTRACE_OFF, "$xtraceoff" },
#endif
 { STN_TGL_STATE_RESET, "$toggle_state_reset" },
 { STN_TGL_RECORD_ON, "$toggle_record_on" },
 { STN_TGL_RECORD_OFF, "$toggle_record_off" },
 { STN_TGL_RECORD_OFF_SET_OLD_VAL_X, "$toggle_record_off_set_old_val_x" },
 { 0, "" }
};

/* predefined built-in system functions */
/* mostly alphabetical but for now really does not need to be */
/* and new transcendentals at end */ 
struct sysfunc_t __vsysfuncs[] = {
 /* { internal num., ret. type, signed (1), type, returned width, name } */
 { STN_BITSTOREAL, N_REAL, 1, 0, SYSF_BUILTIN, REALBITS, "$bitstoreal"},
 { STN_COUNT_DRIVERS, N_REG, 0, 0, SYSF_BUILTIN, WBITS, "$countdrivers"},
 { STN_DIST_CHI_SQUARE, N_REG, 1, 0, SYSF_BUILTIN, INTBITS, "$dist_chi_square"},
 { STN_DIST_ERLANG, N_REG, 1, 0, SYSF_BUILTIN, INTBITS, "$dist_erlang"},
 { STN_DIST_EXPONENTIAL, N_REG, 1, 0, SYSF_BUILTIN, INTBITS, 
    "$dist_exponential"},
 { STN_DIST_NORMAL, N_REG, 1, 0, SYSF_BUILTIN, INTBITS, "$dist_normal"},
 { STN_DIST_POISSON, N_REG, 1, 0, SYSF_BUILTIN, INTBITS, "$dist_poisson"},
 { STN_DIST_T, N_REG, 1, 0, SYSF_BUILTIN, INTBITS, "$dist_t"},
 { STN_DIST_UNIFORM, N_REG, 1, 0, SYSF_BUILTIN, INTBITS, "$dist_uniform"},
 { STN_FOPEN, N_REG, 1, 0, SYSF_BUILTIN, INTBITS, "$fopen"},
 /* width is really width of argument memory */
 /* only allow on rhs of cont. assign */
 { STN_GETPATTERN, N_REG, 0, 0, SYSF_BUILTIN, WBITS, "$getpattern"},
 { STN_ITOR, N_REAL, 1, 0, SYSF_BUILTIN, REALBITS, "$itor"},
 { STN_Q_FULL, N_REG, 0, 0, SYSF_BUILTIN, WBITS, "$q_full"},
 { STN_RANDOM, N_REG, 1, 0, SYSF_BUILTIN, INTBITS, "$random"},
 { STN_REALTIME, N_REAL, 1, 0, SYSF_BUILTIN, REALBITS , "$realtime"},
 /* this codes the real as 64 bit and b part */
 { STN_REALTOBITS, N_REG, 0, 0, SYSF_BUILTIN, 64, "$realtobits"},
 { STN_RESET_COUNT, N_REG, 0, 0, SYSF_BUILTIN, WBITS, "$reset_count" },
 { STN_RESET_VALUE, N_REG, 1, 0, SYSF_BUILTIN, WBITS, "$reset_value"},
 { STN_RTOI, N_REG, 1, 0, SYSF_BUILTIN, INTBITS, "$rtoi"},
 { STN_CEIL, N_REAL, 1, 0, SYSF_BUILTIN, WBITS, "$ceil"},
 { STN_FLOOR, N_REAL, 1, 0, SYSF_BUILTIN, WBITS, "$floor"},
 /* scale takes as argument the module whose scale to return */
 { STN_SCALE, N_REAL, 0, 0, SYSF_BUILTIN, REALBITS, "$scale"},
 /* SJM 10/01/03 - special conversion to signed - arg size is ret size */
 { STN_SIGNED, N_REG, 1, 0, SYSF_BUILTIN, 0, "$signed" }, 
 { STN_STIME, N_REG, 0, 0, SYSF_BUILTIN, INTBITS, "$stime"},
 { STN_TESTPLUSARGS, N_REG, 0, 0, SYSF_BUILTIN, WBITS, "$test$plusargs" },
 { STN_SCANPLUSARGS, N_REG, 0, 0, SYSF_BUILTIN, WBITS, "$scan$plusargs" },
 { STN_VALUEPLUSARGS, N_REG, 0, 0, SYSF_BUILTIN, WBITS, "$value$plusargs" },
 { STN_TIME, N_TIME, 0, 0, SYSF_BUILTIN, TIMEBITS, "$time"},
 /* cver system function extensions */
 { STN_STICKSTIME, N_REG, 0, 0, SYSF_BUILTIN, WBITS, "$stickstime"},
 { STN_TICKSTIME, N_TIME, 0, 0, SYSF_BUILTIN, TIMEBITS, "$tickstime"},
 /* SJM 10/01/03 - special conversion to signed - arg size is ret size */
 { STN_UNSIGNED, N_REG, 0, 0, SYSF_BUILTIN, 0, "$unsigned" }, 
 /* new transcendental functions */
 { STN_COS, N_REAL, 1, 0, SYSF_BUILTIN, WBITS, "$cos"},
 { STN_SIN, N_REAL, 1, 0, SYSF_BUILTIN, WBITS, "$sin"},
 { STN_TAN, N_REAL, 1, 0, SYSF_BUILTIN, WBITS, "$tan"},
 { STN_ACOS, N_REAL, 1, 0, SYSF_BUILTIN, WBITS, "$acos"},
 { STN_ASIN, N_REAL, 1, 0, SYSF_BUILTIN, WBITS, "$asin"},
 { STN_ATAN, N_REAL, 1, 0, SYSF_BUILTIN, WBITS, "$atan"},
 { STN_ATAN2, N_REAL, 1, 0, SYSF_BUILTIN, WBITS, "$atan2"},
 { STN_COSH, N_REAL, 1, 0, SYSF_BUILTIN, WBITS, "$cosh"},
 { STN_SINH, N_REAL, 1, 0, SYSF_BUILTIN, WBITS, "$sinh"},
 { STN_TANH, N_REAL, 1, 0, SYSF_BUILTIN, WBITS, "$tanh"},
 { STN_ACOSH, N_REAL, 1, 0, SYSF_BUILTIN, WBITS, "$acosh"},
 { STN_ASINH, N_REAL, 1, 0, SYSF_BUILTIN, WBITS, "$asinh"},
 { STN_ATANH, N_REAL, 1, 0, SYSF_BUILTIN, WBITS, "$atanh"},
 /* LOOKATME - think this should be removed - other ways to get sign */
 /* next 2 new transcendental except returns int32 */
 { STN_SGN, N_REG, 1, 0, SYSF_BUILTIN, WBITS, "$sgn"},
 { STN_INT, N_REG, 1, 0, SYSF_BUILTIN, WBITS, "$int"},
 { STN_LN, N_REAL, 1, 0, SYSF_BUILTIN, WBITS, "$ln"},
 { STN_LOG10, N_REAL, 1, 0, SYSF_BUILTIN, WBITS, "$log10"},
 { STN_ABS, N_REAL, 1, 0, SYSF_BUILTIN, WBITS, "$abs"},
 { STN_POW, N_REAL, 1, 0, SYSF_BUILTIN, WBITS, "$pow"},
 { STN_SQRT, N_REAL, 1, 0, SYSF_BUILTIN, WBITS, "$sqrt"},
 { STN_EXP, N_REAL, 1, 0, SYSF_BUILTIN, WBITS, "$exp"},
 { STN_MIN, N_REAL, 1, 0, SYSF_BUILTIN, WBITS, "$min"},
 { STN_MAX, N_REAL, 1, 0, SYSF_BUILTIN, WBITS, "$max"},
 { STN_HSQRT, N_REAL, 1, 0, SYSF_BUILTIN, WBITS, "$hsqrt" },
 { STN_HPOW, N_REAL, 1, 0, SYSF_BUILTIN, WBITS, "$hpow" },
 { STN_HPWR, N_REAL, 1, 0, SYSF_BUILTIN, WBITS, "$hpwr" },
 { STN_HLOG, N_REAL, 1, 0, SYSF_BUILTIN, WBITS, "$hlog" },
 { STN_HLOG10, N_REAL, 1, 0, SYSF_BUILTIN, WBITS, "$hlog10" },
 { STN_HDB, N_REAL, 1, 0, SYSF_BUILTIN, WBITS, "$hdb" },
 { STN_HSIGN, N_REAL, 1, 0, SYSF_BUILTIN, WBITS, "$hsign" },
 { STN_HYPOT, N_REAL, 1, 0, SYSF_BUILTIN, WBITS, "$hypot" },
 { STN_CLOG2, N_REG, 1, 0, SYSF_BUILTIN, INTBITS, "$clog2" },
 /* AIV 09/05/03 - add the fileio sy funcs */
 { STN_FGETC, N_REG, 1, 0, SYSF_BUILTIN, INTBITS, "$fgetc" },
 { STN_UNGETC, N_REG, 1, 0, SYSF_BUILTIN, INTBITS, "$ungetc" },
 { STN_FGETS, N_REG, 1, 0, SYSF_BUILTIN, INTBITS, "$fgets" },
 { STN_FTELL, N_REG, 1, 0, SYSF_BUILTIN, INTBITS, "$ftell" },
 { STN_REWIND, N_REG, 1, 0, SYSF_BUILTIN, INTBITS, "$rewind" },
 { STN_FSEEK, N_REG, 1, 0, SYSF_BUILTIN, INTBITS, "$fseek" },
 { STN_FERROR, N_REG, 1, 0, SYSF_BUILTIN, INTBITS, "$ferror" },
 { STN_FREAD, N_REG, 1, 0, SYSF_BUILTIN, INTBITS, "$fread" },
 { STN_FSCANF, N_REG, 1, 0, SYSF_BUILTIN, INTBITS, "$fscanf" },
 { STN_SSCANF, N_REG, 1, 0, SYSF_BUILTIN, INTBITS, "$sscanf" },
 { STN_FEOF, N_REG, 1, 0, SYSF_BUILTIN, INTBITS, "$feof" },
 /* SV functions below here */
 { STN_PSPRINTF, N_REG, 1, 0, SYSF_BUILTIN, INTBITS, "$psprintf" },
 { STN_DIMENSION, N_CINT, 1, 1, SYSF_BUILTIN, INTBITS, "$dimension" },
 { STN_UNPACKED_DIMENSION, N_CINT, 1, 1, SYSF_BUILTIN, INTBITS, 
   "$unpacked_dimension" },
 { STN_LEFT, N_CINT, 1, 1, SYSF_BUILTIN, INTBITS, "$left" },
 { STN_RIGHT, N_CINT, 1, 1, SYSF_BUILTIN, INTBITS, "$right" },
 { STN_LOW, N_CINT, 1, 1, SYSF_BUILTIN, INTBITS, "$low" },
 { STN_HIGH, N_CINT, 1, 1, SYSF_BUILTIN, INTBITS, "$high" },
 { STN_INCREMENT, N_CINT, 1, 1, SYSF_BUILTIN, INTBITS, "$increment" },
 { STN_SIZE, N_CINT, 1, 1, SYSF_BUILTIN, INTBITS, "$size" },
 { STN_ONEHOT, N_CINT, 0, 0, SYSF_BUILTIN, 1, "$onehot" },
 { STN_ONEHOT0, N_CINT, 0, 0, SYSF_BUILTIN, 1, "$onehot0" },
 { STN_ISUNKNOWN, N_CINT, 0, 0, SYSF_BUILTIN, 1, "$isunknown" },
 { STN_COUNTONES, N_CINT, 1, 0, SYSF_BUILTIN, INTBITS, "$countones" },
 { 0, 0, 0, 0, 0, 0, "" }
};

/*
 * initialize the system task symbol table
 * this is special symbol table used to find module and primitives
 * not in normal symbol table stack 
 */
static void init_stsymtab(void)
{
 int32 i;
 struct systsk_t *stbp;
 struct sysfunc_t *sfbp;

 /* system symbols handled specially - only tasks and funcs */
 /* this sets symbol table to emtpy also */
 /* not a symbol table of any symbol */
 __syssyms = __alloc_symtab(FALSE);
 __cur_fnam_ind = 0;
 __cur_fnam = __in_fils[__cur_fnam_ind];
 __lin_cnt = 0;

 /* add system tasks */
 /* then normal system tasks - var. (or unknown) args */
 for (i = 0;; i++)
  {
   stbp = &(vsystasks[i]);
   if (strcmp(stbp->stsknam, "") == 0) break;
   add_systsksym(stbp);
  }
 /* add system functions */
 for (i = 0;; i++)
  {
   sfbp = &(__vsysfuncs[i]);
   if (strcmp(sfbp->syfnam, "") == 0) break;
   add_sysfuncsym(sfbp);
  }

 /* SJM 07/08/02 - setup both old veriusertfs systf and new +loadpli1 */
 __setup_veriusertf_systfs();


 /* SJM 07/08/02 - handle all +loadvpi option dynamic lib loading */
 __process_pli_dynamic_libs(__vpi_dynlib_hd);

 /* because variable number of vpi_ systf (dynamic registering), must add */
 /* tf_ first, vpi_ registered systfs one after last tf_ */
 __call_vlog_startup_procs();
}

/*
 * add system tasks symbol to syssyms table
 */
static void add_systsksym(struct systsk_t *stbp)
{
 struct tnode_t *tnp;
 struct sy_t *syp;

 tnp = __vtfind(stbp->stsknam, __syssyms);
 /* built in system task table mis-coded */ 
 if (!__sym_is_new) __misc_terr(__FILE__, __LINE__);
 __add_sym(stbp->stsknam, tnp);
 (__syssyms->numsyms)++;
 syp = tnp->ndp;
 syp->sytyp = SYM_STSK;
 syp->sydecl = TRUE;
 syp->sylin_cnt = 0;
 syp->syfnam_ind = 0;
 syp->el.esytbp = stbp;
}

/*
 * add system function to system symbol symbol table
 */
static void add_sysfuncsym(struct sysfunc_t *sfbp)
{
 struct tnode_t *tnp;
 struct sy_t *syp;

 tnp = __vtfind(sfbp->syfnam, __syssyms);
 /* built in system function table mis-coded */ 
 if (!__sym_is_new) __misc_terr(__FILE__, __LINE__);
 __add_sym(sfbp->syfnam, tnp);
 (__syssyms->numsyms)++;
 syp = tnp->ndp;
 syp->sytyp = SYM_SF;
 syp->sydecl = TRUE;
 syp->sylin_cnt = 0;
 syp->syfnam_ind = 0;
 syp->el.esyftbp = sfbp;
}

/*
 * ROUTINES TO CHECK TOGGLE OPTION SELECTION CONSISTENCY
 */

/*
 * check to make sure toggle coverage report and recording options consistent
 */
static void chk_toggle_opt_consistent(void)
{
 if (__toggle_coverage || __has_tgl_optcfg_stmt)
  {
   if (!__old_toggle_rpt_instance
    && !__old_toggle_rpt_bits
    && !__old_toggle_rpt_uncovered
    && !__old_toggle_rpt_covered
    && !__drvn_const_rpt_concise
    && !__untgled_rpt_concise
    && !__wr_tgldat_on)
    {
     __pv_warn(3149,
      "-toggle or -optconfigfile cover_toggle statement enables toggle recording but no report option selected");
    }
  }
 else
  {
   if (__old_toggle_rpt_instance
    || __old_toggle_rpt_bits
    || __old_toggle_rpt_uncovered
    || __old_toggle_rpt_covered
    || __drvn_const_rpt_concise
    || __untgled_rpt_concise
    || __wr_tgldat_on)
    {
     __pv_warn(3158,
      "toggle report option selected but no -toggle or -optconfigfile cover_toggle statement - no toggle report/file written");
    }
  } 
}

/*
 * INPUT FILE PREPARATION ROUTINES
 */

/*
 * prepare the input file stack (know input files infiles[0:__last_inf])
 * macro expansions and `include put on top of stack
 * this puts one open file struct on tos and open 1st file with guts
 */
static void prep_vflist(void)
{
 int32 fi;

 /* no files since 0  and 1 are special */
 if (__last_inf == __last_optf)
  __pv_terr(301, "no Verilog input files specified");
 __last_lbf = __last_inf;

 /* set open file/macro exp./include stack to empty */
 for (fi = 0; fi < MAXFILNEST; fi++) __vinstk[fi] = NULL;
 __vin_top = -1;
 __lasttoktyp = UNDEF;
 __last_attr_prefix = FALSE;
 /* this builds the empty top of stack entry */
 __push_vinfil();
 /* fill with 1st file and open it */
 /* __in_fils[0] is no file "none" */
 /* set to one after last option file */
 __cur_infi = __last_optf + 1;
 if (!__open_sfil())
  __pv_terr(301, "no Verilog input - all files empty or cannot be opened");
}


/*
 * try to open the next input source file and fill top of stack with its info
 * file must be openable and have contents
 * return F on no sucess in opening any of succeeding files
 */
extern int32 __open_sfil(void)
{
again:
 /* if not first time, close previous file */
 if (__visp->vi_s != NULL)
  { __my_fclose(__visp->vi_s); __visp->vi_s = NULL; }
 __cur_fnam = __in_fils[__cur_infi];
 if ((__in_s = __tilde_fopen(__cur_fnam, "r")) == NULL)
  {
#ifndef __CVC_RT__
   __pv_err(700, "cannot open Verilog input file %s - skipped", __cur_fnam);
#else 
   __pv_err(700, "cannot open Verilog file %s - recompile using original source files", __cur_fnam);
#endif
try_next:
   if (__cur_infi + 1 > __last_inf) return(FALSE);
   __cur_infi++;
   goto again;
  }
 if (feof(__in_s))
  {
   __pv_warn(508, "Verilog input file %s empty", __cur_fnam);
   goto try_next;
  }
 /* whenever open new file must discard pushed back */
 __lasttoktyp = UNDEF;
 __visp->vi_s = __in_s;
 /* in fils of 0 is no file "none" */
 /* vilin_cnt always 0 when opened */
 __visp->vifnam_ind = __cur_infi;
 __cur_fnam_ind = __cur_infi;
 __cur_fnam = __in_fils[__cur_fnam_ind];
 __lin_cnt = 1;
 /* emit source filed compiled unless -q */
#ifndef __CVC_RT__
 __cv_msg("Elaborating source file \"%s\"\n", __cur_fnam);
#endif
 __file_just_op = TRUE;
 __first_num_eol = FALSE; 
 /* 06/22/00 - SJM - possible cross macro 2 token number off on new file */
 __macro_sep_width = FALSE;
 __maybe_2tok_sized_num = FALSE;
 __macro_sav_nwid = FALSE;
 return(TRUE);
}

/*
 * allocate a new Verilog input file stack element on top
 * this does not open or fill anything just builds the tos entry
 * this sets global __visp
 */
extern void __push_vinfil(void)
{
 if (++__vin_top >= MAXFILNEST)
  __pv_terr(308, "`define macro and `include nesting level too large (%d)",
   MAXFILNEST);
 if (__vinstk[__vin_top] == NULL)
  {
   __vinstk[__vin_top] = (struct vinstk_t *)
     __my_malloc(sizeof(struct vinstk_t));
  }
 __visp = __vinstk[__vin_top];
 __visp->vilin_cnt = 0;
 /* in fils of 0 is no file "none" */
 __visp->vifnam_ind = 0;
 __visp->vi_s = NULL;
 __visp->vichp = NULL;
 __visp->vichplen = -1;
 __visp->vichp_beg = NULL;
}

/*
 * previous file(s) eof encounted pop stack (know thing under open)
 */
extern int32 __pop_vifstk(void)
{
 /* first pop previous */
 if (__vin_top == 0)
  {
   /* PUT ME BACK */
   return(FALSE);
  }
 /* notice never pop below bottom open current source file */
 /* if reached end of current source file, pop */
 /* define stack should never be popped below bottom */
 if (__vin_top < 0) __misc_terr(__FILE__, __LINE__);

 /* close current top file if open or null out macro */
 __visp = __vinstk[__vin_top];
 if (__visp->vi_s != NULL)
  { __my_fclose(__visp->vi_s); __visp->vi_s = NULL; }
 if (__visp->vichp != NULL)
  {
   /* if -1, pointing to non arg macro in symbol table must not free */
   /* for use of fixed visp for parsing from history list will just be -1 */
   /* else len built for arg macro and must be freed */
   /* need original start which is - length since at ending 0 */
   if (__visp->vichplen != -1)
    __my_free(__visp->vichp_beg, __visp->vichplen + 1);
   __visp->vichp = NULL;
   __visp->vichp_beg = NULL;
   __visp->vichplen = -1;
  }

 /* once popped gone for ever except in_fils entry stays */
 __visp = __vinstk[--__vin_top];

 /* then access under - notice number of simultaneously open files may */
 /* be limited by os */

 /* handle nested macro expansion */
 /* notice here can never be first token for reprocessing `directive */
 /* since "`define xx `include "yy"" then line with `xx only is illegal */ 
 /* FIXME - this can never be exec because already set to nil ??? */
 if (__visp->vichp != NULL)
  {
   /* must not change file name and line number */
   __in_s = NULL;
   return(TRUE);
  }
 /* pop down to previously opened file - macro exp. end or `include */
 __cur_fnam_ind = __visp->vifnam_ind;
 __cur_fnam = __in_fils[__cur_fnam_ind];
 __lin_cnt = __visp->vilin_cnt;
 __in_s = __visp->vi_s;
 __file_just_op = TRUE;
 __first_num_eol = FALSE; 
 return(TRUE);
}

/*
 * return to print internally stored source
 * know only called if no errors
 *
 * must save cur iti num since this is debug routine that can be called
 * from anywhere
 */
extern void __do_decompile(void)
{
 struct mod_t *mdp;
 struct udp_t *udpp;
 int32 first_time;

 __cv_msg("  Reconstructing post elaboration source:\n");

 /* for debugging dump every inst. need flag for has IS forms */
 for (first_time = TRUE, mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   if (!mdp->msym->sydecl) continue;
   if (first_time)
    { __cur_units = 9; __cur_prec = 0; first_time = FALSE; }
   __push_wrkitstk(mdp, 0);
   __dmp_mod(stdout, mdp, FALSE);
   __pop_wrkitstk();
  }
 for (udpp = __udphead; udpp != NULL; udpp = udpp->udpnxt)
  __dmp_udp(stdout, udpp);
}

/*
 * TOP LEVEL SOURCE PROCESSING ROUTINES - ALSO DIRECTIVE HANDLING
 */

/*
 * read the Verilog source input
 * know 1st file and 1st token read
 */
extern void __rd_ver_src(void)
{
 __total_rd_lines = 0;
 /* go through loop once for each module */
 /* everything in Verilog in modules */
 /* enter loop with first token in toktyp */
 for (;;)
  {
   /* EOF is eof of all in files - get tok. will open next input if need */
   __get_vtok();
   if (__toktyp == TEOF) break;
   /* system tasks not allowed at top level - interacte mode handled */
   /* elsewhere - but may be a compiler directive */
   if (__toktyp >= CDIR_TOKEN_START && __toktyp <= CDIR_TOKEN_END)
    __process_cdir();
   /* if ever will have synced to one before file level thing */
   else
    {
     /* SJM 03/20/00 - build top level attribute if present */
     if (__attr_prefix)
      {
       __wrk_attr.attr_tok = MODULE;
       __wrk_attr.attr_seen = TRUE;
       __wrk_attr.attrnam = __pv_stralloc(__attrwrkstr);
       __wrk_attr.attr_fnind = __attr_fnam_ind;
       __wrk_attr.attrlin_cnt = __attr_lin_cnt;
      }
     else __wrk_attr.attr_seen = FALSE;

     __rding_top_level = FALSE;
     __rd_ver_mod();
     __rding_top_level = TRUE;
    }
   if (__toktyp == TEOF) break;
  }
}

/*
 * process built in compiler directives
 * know directive read and for now just reads what is needed
 * if `define form will be handled by get tok
 * directive here only if allowed (and probably required) outside of module
 */
extern void __process_cdir(void)
{
 int32 wtyp, savlin_cnt;
 char s1[RECLEN];

 if (!__chk_beg_line(__toktyp))
  {
   __pv_fwarn(605, "directive %s not first token on line - ignored",
    __prt_vtok());
   /* still skip rest of line */
   if (!__iact_state) __skipover_line();
   return;
  } 
 switch (__toktyp) {
  case CDIR_TIMESCALE:
   do_timescale();
   return;
  case CDIR_DFLNTYP:
   savlin_cnt = __lin_cnt;
   __toktyp = __get1_vtok(__in_s);
   if (savlin_cnt != __lin_cnt)
    {
     __pv_ferr(927,
      "`defaultnettype directive wire type must be on same line");
     __unget_vtok();
     return;
    }
   if ((wtyp = __fr_wtnam(__toktyp)) == -1)
    {
     /* AIV 05/17/11 - LRM states that `default_nettype none */
     /* means that all wires must be defined no implicit */
     if (strcmp(__token, "none") == 0)
      {
       __dflt_ntyp_is_none = TRUE; 
      }
     else
      {
       __pv_ferr(704,
        "`defaultnettype compiler directive not followed by wire type - %s read",
       __prt_vtok());
      }
    }
   else if (wtyp >= NONWIRE_ST || wtyp == N_SUPPLY0 || wtyp == N_SUPPLY1)
    {
     __pv_ferr(705, "`defaultnettype compiler directive wire type %s illegal",
      __to_wtnam2(s1, (word32) wtyp)); 
    }
   else __dflt_ntyp = wtyp;
   break;
  case CDIR_AEXPVECNETS:
  case CDIR_XPNDVNETS:
   /* this is default */
   __no_expand = FALSE;
   break;
  case CDIR_NOXPNDVNETS:
   __no_expand = TRUE;
   break;
  case CDIR_CELLDEF:
   __in_cell_region = TRUE;
   break;
  case CDIR_ECELLDEF:
   __in_cell_region = FALSE;
   break;
  /* this takes pull0 or pull1 and connects pull up to unc. input port ? */
  case CDIR_UNCONNDRIVE:
   savlin_cnt = __lin_cnt;
   __toktyp = __get1_vtok(__in_s);
   if (savlin_cnt != __lin_cnt)
    {
     __pv_ferr(1037,
      "`unconnected_drive directive strength must be on same line");
     __unget_vtok();
     return;
    }
   if (__toktyp != PULL0 && __toktyp != PULL1)
    {
     __pv_ferr(1041,
      "`unconnected_drive directive requires pull0 or pull1 argument - %s read",
      __prt_vtok());
     __unget_vtok();
     return;
    }
   __unconn_drive = __toktyp;
   break;
  case CDIR_NOUNCONNDRIVE:
   __unconn_drive = TOK_NONE;
   break;
  case CDIR_RESETALL:
   /* this does not effect `ifdef, `define, i.e. symbol tables left as is */
   set_tfmt_dflts();
   __dflt_ntyp = N_WIRE;
   __dflt_ntyp_is_none = FALSE;
   __in_cell_region = FALSE;
   __unconn_drive = TOK_NONE;
   __no_expand = FALSE;
   __cur_units = 9;
   __cur_prec = 0;
   break;
  /* these need to be supported */
  case CDIR_ENDPROTECT:
  case CDIR_ENDPROTECTED:
  case CDIR_PROTECT:
  case CDIR_PROTECTED:
   __pv_fwarn(619, "directive %s unimplemented", __prt_vtok());
   break;

  /* these do not do anything */
  case CDIR_ACCEL:
  case CDIR_NOACCEL:
  case CDIR_REMGATESNAMES:
  case CDIR_REMNETNAMES:
  case CDIR_NOREMGATENAMES:
  case CDIR_NOREMNETNAMES:
  case CDIR_DFLTDECAYTIME:
  case CDIR_DFLTTRIREGSTREN:
  case CDIR_DELMODEDIST:
  case CDIR_DELMODEPATH:
  case CDIR_DELMODEUNIT:
  case CDIR_DELMODEZERO:

   /* these are all one name and ignored for now */
   __finform(430, "directive %s has no effect", __prt_vtok());
   break;
  default: __case_terr(__FILE__, __LINE__);
 }
 /* this skip over anything else (such as comments) on line */
 __skipover_line();
}

/*
 * process the time scale directive
 * must be on line by itself and cannot tokenize
 * anything on line after `timescale not read - / * cannot start there
 * fomrmat is `timescale <time_unit>/<time_prec>
 * this sets globals cur_units and cur_prec 
 *
 * storage is time exponent - 1s is 1, 100 ms = 3, 1 ns = 9, 10 ns = 10, etc
 */
static void do_timescale(void)
{
 char *cp, *cp2;
 word32 tuexp, tpexp, tunit, tprec;
 struct sy_t *syp;
 int32 len, len2;
 char *chp, *chp2;
 char s1[RECLEN], s2[RECLEN];

 __collect_line();
 len = 0;
 /* AIV 05/12/09 - need to check the line for `timescale define */
 /* just scan entire line for ` and / producing expanded line */
 for (chp = __macwrkstr; *chp != '\0'; chp++)
  {
   /* need to get the macro and its string value */
   if (*chp == '`')
    {
     len2 = 0;
     /* build `name until a / or end of string */
     while (*chp != '\0' && *chp != '/')
      {
       s2[len2++] = *chp++;
      }
     s2[len2] = '\0';
     if ((syp = __get_sym(s2, __pv_defsyms)) == NULL || !syp->sydecl)
      {
       __pv_fwarn(654,
        "text macro %s undefined or possibly compiler directive for other tool - ignored",
      __macwrkstr);
      goto tscale_bad;
      }
     chp2 = syp->el.edfchp;
     if (strcmp(chp2, "") == 0) goto tscale_bad;
     len2 = strlen(chp2);
     /* copy in `str string value */
     memcpy(&(s1[len]), chp2, len2);
     len += len2;
     if (*chp == '/')
      {
       s1[len] = '/';
       len++;
      }
     else if (*chp == '\0') break;
     continue;
    }
   /* add one character */
   s1[len] = *chp;
   len++;
  }
 /* copy in old line or the expanded value */
 s1[len] = '\0';
 __macwrklen = len;
 strcpy(__macwrkstr, s1); 

 /* copy line removing all white space */
 for (cp2 = __macwrkstr, cp = s1; *cp2 != '\0'; cp2++)
  { if (!vis_nonnl_white_(*cp2)) *cp++ =  *cp2; }
 *cp = '\0';

 /* first expect 1, 10, or 100 */
 cp = s1;
 tunit = 0;
 tuexp = 0;
 if (*cp++ != '1') goto tscale_bad;
 if (*cp++ == '0') tuexp = 1; else { cp--; goto get_tunit; }
 if (*cp++ == '0') tuexp = 2; else cp--;

get_tunit:
 if ((cp = __get_tmult(cp, &tunit)) == NULL) goto tscale_bad;
 if (*cp != '/') goto tscale_bad;
 /* if second must be 1 */
 if (tunit == 0 && tuexp > 0) goto tscale_bad;
 cp++;
 tunit -= tuexp; 

 tpexp = 0;
 if (*cp++ != '1') goto tscale_bad;
 if (*cp++ == '0') tpexp = 1; else { cp--; goto get_tprec; }
 if (*cp++ == '0') tpexp = 2; else  cp--; 
get_tprec:
 if ((cp = __get_tmult(cp, &tprec)) == NULL) goto tscale_bad;
 /* if 10s and 100s illegal */
 if (tprec == 0 && tpexp > 0) goto tscale_bad;
 tprec -= tpexp;

 /* precision must be smaller or = tick or higher or = exponent */
 if (tprec < tunit)
  {
   __pv_ferr(936,
    "time unit %s cannot be smaller than precision %s - `timescale ignored",
     __to_timunitnam(__xs, tunit),  __to_timunitnam(__xs2, tprec));
   return;
  }
 /* cur units stored as inverse of exponenent so 1 ns 9 not -9 as returned */ 
 __cur_units = tunit;
 /* cur precision is amount to add to cur units */
 __cur_prec = tprec - __cur_units;
 /* warning if extra stuff on end of line - should not be there */
 if (!__bqline_emptytail(cp))
  __pv_fwarn(567, "`timescale non white space at end of line ignored");
 __des_has_timescales = TRUE;
 return;

tscale_bad:
 __pv_ferr(934, "`timescale directive format incorrect - time scale unchanged");
}

/*
 * get a time unit - returns NULL on error else ending cp
 */
extern char *__get_tmult(char *cp, word32 *num_zeros)
{
 switch (*cp) {
  case 'f': *num_zeros = 15; break;
  case 'p': *num_zeros = 12; break;
  case 'n': *num_zeros = 9; break;
  case 'u': *num_zeros = 6; break;
  case 'm': *num_zeros = 3; break;
  case 's': *num_zeros = 0; return(++cp);
  default: return(NULL);
 }
 if (*(++cp) != 's') return(NULL);
 return(++cp);
}

/*
 * SIGNAL SETUP DEFINES
 */

#ifndef __NOSIGS__
#ifdef __linux__
static const int32 sigtab[] = {
 SIGQUIT, SIGILL, SIGABRT, SIGFPE, SIGSEGV, SIGPIPE, SIGTERM,
 SIGSTKFLT, SIGXCPU, SIGXFSZ, SIGPWR
};
#define NSHNDS (sizeof(sigtab) / sizeof(int32))
#endif
#endif
 
/*
 * if running with +exe need to execute the compiled executable
 */
static void run_executable(void)
{
 struct stat sbuf;

 /* if running the excutable return */
 if (__running_cvc_exe) return;

 /* if not not run with +exe do not execute */
 if (__execute_compiled)
  {
   /* may have had compile problems */
   if (stat(__exe_name, &sbuf) != 0) 
    {
     __pv_err(2905, "executable not built - cannot execute"); 
    }
   else execl(__exe_name, __exe_name, (char *) NULL);
  }
}

static void my_sig_handler(int32 signum)
{
 /* DBG remove ---
 __my_fprintf(stdout, "got signal %d exception.\n", signum);
 --- */
 /* SJM 08/05/02 - for cvlic signal catching must always put default */ 
 /* action back - if user sets signals in PLI must be put back before */
 /* returning from PLI - now signal behave normally except for gdb quit cmd */
  signal(signum, SIG_DFL);
 raise(signum);
}

/*
 * AIV 09/10/09 - catch segv and print message with simulation time
 */
static void segv_handle(void)
{
 char s1[RECLEN];
 struct mod_t *mdp;

 /* AIV 02/03/10 - if segv occurs during compilation print out a different */
 /* message than the simulation time message */
 if (__run_state != SS_SIM)
  {
   if (__inst_mod != NULL)
    {
     strcpy(s1, __inst_mod->msym->synam);
    }
   else strcpy(s1, "unknown");

   __pv_ferr(315, "SEGV signal occured during compilation in module %s?. This is a bug.  Please provide details in a bug report.\n", s1);
   /* AIV 03/08/10 - this needs to exit not return */
   __my_exit(7, TRUE);
  }

 /* AIV 04/03/12 - added the module name if possible */
 if (__idp != NULL)
  {
   mdp = (struct mod_t *) __idp[MD_MDP];
   strcpy(s1, mdp->msym->synam);
  }
 else strcpy(s1, "unknown");
#ifdef __CVC32__
 /* AIV 08/02/10 - in DPI or VPI code could be user caused */
 if (__dpi_hdrp != NULL || __design_has_ld_pli_libs)
  {
   __pv_ferr(315, "SEGV signal occured at simulation time %llu in module %s?.  This is caused by either user created DPI/VPI bug or CVC.  If not DPI/PLI crash please provide details in a bug report.\n", __simtime, s1);
  }
 else
  {
   __pv_ferr(315, "SEGV signal occured at simulation time %llu in module %s?.  This is a bug.  Please provide details in a bug report.\n", __simtime, s1);
  }
#else
 if (__dpi_hdrp != NULL || __design_has_ld_pli_libs)
  {
   __pv_ferr(315, "SEGV signal occured at simulation time %lu in module %s?.  This is caused by either user created DPI/VPI bug or CVC.  If not DPI/PLI crash please provide details in a bug report.\n", __simtime, s1);
  }
 else
  {
   __pv_ferr(315, "SEGV signal occured at simulation time %lu in module %s?.  This is a bug.  Please provide details in a bug report.\n", __simtime, s1);
  }
#endif
 __my_exit(7, TRUE);
}

/*
 * SUMMARY AND DESIGN CONTENTS ROUTINES
 */

/*
 * routine to print the summary for entire run
 */
static int32 prt_summary(void)
{
 if (__pv_err_cnt != 0 || __pv_warn_cnt != 0 || __inform_cnt != 0)
  __cv_msg("  There were %d error(s), %d warning(s), and %d inform(s).\n",
   __pv_err_cnt, __pv_warn_cnt, __inform_cnt);

 if (__pv_err_cnt != 0 || __undef_mods > 0) return(1);
 if (__verbose)
  {
   if (__pv_warn_cnt == 0 && __inform_cnt == 0)
    __cv_msg("  No errors and no warnings.\n");
  }
 return(0);
}

/*
 * print the design wide stats
 */
static void prt_deswide_stats(void)
{
 struct udp_t *udpp;
 struct mod_t *mdp;
 int32 numudps, nummods, numsplitmods, num_tran_nets;

 for (numudps = 0, udpp = __udphead; udpp != NULL; udpp = udpp->udpnxt)
  numudps++;
 for (nummods = numsplitmods = 0, mdp = __modhdr; mdp != NULL;
  mdp = mdp->mnxt)
  {
   numsplitmods++;
   if (!mdp->msplit && !mdp->mpndsplit) nummods++;
  }

 if (__verbose) 
  {
   __cv_msg("  Verbose mode statistics:\n");
   __cv_msg("  %d source lines read (includes -v/-y library files).\n",
    __total_rd_lines);
   if (numsplitmods == nummods)
    __cv_msg("  Design contains %d module types.\n", nummods);
   else
    __cv_msg(
     "  Design contains %d module types (%d after parameter substitution).\n",
      nummods, numsplitmods);

   /* notice memory here goes to next higher 160k from end - i.e. 900k is 2m */
   if (numudps != 0)
    __cv_msg(
     "  %d instantiated udp tables of total size less than %d million bytes.\n",
     numudps, (__mem_udpuse + 1160000)/1000000);
   if (__num_glbs != 0 || __num_inmodglbs != 0)
    __cv_msg(
     "  There are %d cross module and %d intra module hierarchical references.\n",
     __num_glbs - __num_inmodglbs, __num_inmodglbs);
   if ((num_tran_nets = count_tran_nets()) != 0) 
    {
     __cv_msg(
      "  %d nets in inout or tran gate connecting transistor channels.\n",
      num_tran_nets);
    }
   if (__gates_removable != 0 || __contas_removable != 0)
    {
     __cv_msg(
      "  %d gates (%d flat) and %d assigns (%d flat) disconnected by gate eater.\n",
      __gates_removable, __flgates_removable, __contas_removable,
      __flcontas_removable);
    }
   if (__nets_removable != 0)
    {
     __cv_msg("  %d nets (%d flat) disconnected by gate eater.\n",
      __nets_removable, __flnets_removable);
    }
   __cv_msg("\n");
  }
}

/*
 * count design total nets in transistor or inout channels
 */
static int32 count_tran_nets(void)
{
 int32 ni;
 struct net_t *np;
 struct mod_t *mdp;
 int32 ntrnets;

 for (ntrnets = 0, mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   if (mdp->mnnum == 0 || (!mdp->mod_hasbidtran && !mdp->mod_hastran))
    continue;
   for (ni = 0, np = &(mdp->mnets[0]); ni < mdp->mnnum; ni++, np++)
    { if (np->ntraux != NULL) ntrnets++; }
  }
 return(ntrnets);
}

/*
 * print a message giving memory use
 */
static void mem_use_msg(int32 also_mems)
{ 
 double d1;

 if (__verbose)
  {
   __cv_msg("  Approximately %ld bytes storage allocated (excluding udps).\n",
    __mem_use);
   d1 = 100.0*((double) __arrvmem_use/(double) (__memstr_use + __mem_use)); 
   if (also_mems && __arrvmem_use != 0)
    {
     __cv_msg(
      "  Verilog arrays (memories) require %ld bytes (%.2lf%% of total).\n",
      __arrvmem_use, d1);
    }
   /* RELEASE remove --
   __prt_memstats();
   -- */
  }
}

/*
 * print all the design 1 line per module type tables
 */
static void prt_alldesmod_tabs(void)
{
 __cv_msg("+++ Printing Design Statistics +++\n");
 /* even if verbose print design wide statistics here */
 prt_deswide_stats();
 /* first general module. declarative counts - 1 line per mod */
 prt2_desmod_tab();
 /* then 1 line per mod of wire stats */
 prt2_permod_wiretab();
 /* 1 line per mod of strength wires stats if design has strength wires */
 st_prt2_permod_wiretab();
 /* print task both wire and numbers stats - 1 line per mod with tasks */
 prt2_permod_tasktabs();

 /* print the per module type usage tables */
 __prt2_mod_typetab(__prt_allstats);
 __cv_msg("+++ End of Design Statistics +++\n");
}

/*
 * print table of summary modules statistics for every module
 */
static void prt2_desmod_tab(void)
{
 struct mod_t *mdp;
 int32 num_cells, num_insts, num_gates, num_contas;
 int32 num_nets, tot_num_cells, tot_num_insts, tot_num_gates;
 int32 tot_num_contas, tot_num_nets;
 int32 fltot_num_cells, fltot_num_insts, fltot_num_gates, fltot_num_contas;
 int32 fltot_num_nets, num1bcas, fltot_insts_in;
 char s1[RECLEN];
 
 tot_num_cells = tot_num_insts = tot_num_gates = 0;
 tot_num_contas = tot_num_nets = 0;
 fltot_num_cells = fltot_num_insts = fltot_num_gates = fltot_num_contas = 0;
 fltot_num_nets = fltot_insts_in = 0;

 __cv_msg("  Design Module Table: %d modules (%d top level):\n",
  __dsgn_num_mods, __numtopm);
 __cv_msg(
  "Module            Level Cells-in Insts-in Primitives  Assigns    Nets");
 __cv_msg("  Insts-of\n");
 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   num_cells = count_cells(mdp);
   tot_num_cells += num_cells;
   fltot_num_cells += num_cells*(int32) mdp->flatinum;
   num_insts = (int32) mdp->minum - num_cells;
   tot_num_insts += num_insts;
   fltot_num_insts += num_insts*(int32) mdp->flatinum;
   num_gates = count_gates(mdp, &num1bcas);
   tot_num_gates += num_gates;
   fltot_num_gates += num_gates*(int32) mdp->flatinum;
   num_contas = num1bcas;
   num_contas += mdp->mcanum;
   tot_num_contas += num_contas;
   fltot_num_contas += num_contas*(int32) mdp->flatinum;
   num_nets = mdp->mnnum;
   tot_num_nets += num_nets;
   fltot_num_nets += num_nets*(int32) mdp->flatinum;
   fltot_insts_in += mdp->flatinum; 
   bld_modnam(s1, mdp, 20);
   __cv_msg("%-20s%3d   %6d   %6d     %6d   %6d  %6d    %6d\n", s1,
    mdp->mlpcnt, num_cells, num_insts, num_gates, num_contas,
    num_nets, mdp->flatinum);
  }
 __cv_msg(
  "                          ------   ------     ------   ------  ------");
 __cv_msg("    ------\n");
 __cv_msg("Static Total:            %7d  %7d    %7d  %7d %7d\n",
  tot_num_cells, tot_num_insts, tot_num_gates, tot_num_contas, tot_num_nets);
 __cv_msg("Flat Total:              %7d  %7d    %7d  %7d %7d   %7d\n",
  fltot_num_cells, fltot_num_insts, fltot_num_gates, fltot_num_contas,
  fltot_num_nets, fltot_insts_in);
}

/*
 * build mod name with trunc. and add (C) for cells
 * s must be big enough
 */
static void bld_modnam(char *s, struct mod_t *mdp, int32 fldsiz)
{
 int32 mlen;
  
 if (mdp->m_iscell)
  {
   mlen = strlen(mdp->msym->synam);
   if (mlen + 3 > fldsiz)
    {
     strncpy(s, mdp->msym->synam, fldsiz - 4);
     s[fldsiz - 4] = '-';
     s[fldsiz - 3] = '\0';
     strcat(s, "(C)");
    }
   else { strcpy(s, mdp->msym->synam); strcat(s, "(C)"); }
   return;
  }
 if ((mlen = strlen(mdp->msym->synam)) > fldsiz)
  {
   strncpy(s, mdp->msym->synam, fldsiz - 1);
   s[fldsiz - 1] = '-';
   s[fldsiz] = '\0';
  }
 else strcpy(s, mdp->msym->synam);
}

/*
 * count number of instances in module that are cells
 */
static int32 count_cells(struct mod_t *mdp)
{
 int32 ii;
 int32 cnum;
 struct inst_t *ip;
 struct mod_t *imdp;

 for (cnum = 0, ii = 0; ii < mdp->minum; ii++)
  {
   ip = &(mdp->minsts[ii]);
   imdp = ip->imsym->el.emdp;
   if (imdp->m_iscell) cnum++;
  }   
 return(cnum);
}

/*
 * count the number of gates in module (includes udps)
 * 
 * cannot just use number because 1 bit contas in gate array
 */
static int32 count_gates(struct mod_t *mdp, int32 *num1bitcas)
{
 int32 gi, gcnt, n1bcas;
 struct gate_t *gp;

 for (gcnt = 0, n1bcas = 0, gi = 0; gi < mdp->mgnum; gi++)
  {
   gp = &(mdp->mgates[gi]);
   if (gp->gmsym->el.eprimp->gateid == G_ASSIGN) n1bcas++; 
   else gcnt++;
  }
 *num1bitcas = n1bcas;
 return(gcnt);
}

/*
 * print the per module wiring table
 */
static void prt2_permod_wiretab(void)
{
 int32 prts, prtbits, wires, wirebits, regs, regbits, arrs, arrcells, arrbits;
 int32 tot_prts, tot_prtbits, tot_wires, tot_wirebits, tot_regs;
 int32 tot_regbits, tot_arrs, tot_arrcells, tot_arrbits;
 struct mod_t *mdp;
 char s1[RECLEN], s2[RECLEN], s3[RECLEN], s4[RECLEN], s5[RECLEN];

 tot_prts = tot_prtbits = 0;
 tot_wires = tot_wirebits = tot_regs = tot_regbits = tot_arrs = 0;
 tot_arrcells = tot_arrbits = 0;
 __cv_msg("\n  Per Module Wiring Table (Task Variables Excluded):\n");
 __cv_msg("Module           Ports(Bits)   Wires(Bits) Registers(Bits)");
 __cv_msg(" Memory(Cells, Bits)\n");
 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   prts = (int32) mdp->mpnum;
   prtbits = cnt_modprt_bits(mdp);
   cnt_modwires(mdp, &wires, &wirebits, &regs, &regbits, &arrs, &arrcells,
    &arrbits);
   
   tot_prts += prts*(int32) mdp->flatinum;
   tot_prtbits += prtbits*(int32) mdp->flatinum;    
   tot_wires += wires*(int32) mdp->flatinum;
   tot_wirebits += wirebits*(int32) mdp->flatinum;
   tot_regs += regs*(int32) mdp->flatinum;
   tot_regbits += regbits*(int32) mdp->flatinum;
   tot_arrs += arrs*(int32) mdp->flatinum;
   tot_arrcells += arrcells*(int32) mdp->flatinum;
   tot_arrbits += arrbits*(int32) mdp->flatinum;
   if (prts == 0) strcpy(s1, ""); else sprintf(s1, "%d(%d)", prts, prtbits);
   if (wires == 0) strcpy(s2, "");
   else sprintf(s2, "%d(%d)", wires, wirebits);
   if (regs == 0) strcpy(s3, ""); else sprintf(s3, "%d(%d)", regs, regbits);
   if (arrs == 0) strcpy(s4, ""); 
   else sprintf(s4, "%d(%d, %d)", arrs, arrcells, arrbits);
   bld_modnam(s5, mdp, 18);
   __cv_msg("%-18s%10s%14s%16s%20s\n", s5, s1, s2, s3, s4);   
  }
 __cv_msg("                ------------ ------------- ---------------");
 __cv_msg(" -------------------\n");
 if (tot_prts == 0) strcpy(s1, "");
 else sprintf(s1, "%d(%d)", tot_prts, tot_prtbits);
 if (tot_wires == 0) strcpy(s2, "");
 else sprintf(s2, "%d(%d)", tot_wires, tot_wirebits);
 if (tot_regs == 0) strcpy(s3, "");
 else sprintf(s3, "%d(%d)", tot_regs, tot_regbits);
 if (tot_arrs == 0) strcpy(s4, ""); 
 else sprintf(s4, "%d(%d, %d)", tot_arrs, tot_arrcells, tot_arrbits);
 __cv_msg("Flat total:    %13s%14s%16s%20s\n", s1, s2, s3, s4);
}

/*
 * count the number of module port bits
 */
static int32 cnt_modprt_bits(struct mod_t *mdp)
{ 
 int32 pi, modpbits;
 struct mod_pin_t *mpp;

 for (modpbits = 0, pi = 0; pi < mdp->mpnum; pi++)  
  {
   mpp = &(mdp->mpins[pi]);
   modpbits += (int32) mpp->mpwide;
  }
 return(modpbits);
}

/*
 * count the number of top level (non in task/func) wires and bits
 */
static void cnt_modwires(struct mod_t *mdp, int32 *wires, int32 *wirebits,
 int32 *regs, int32 *regbits, int32 *arrs, int32 *arrcells, int32 *arrbits)
{
 int32 ni;
 struct net_t *np;
 int32 acells;

 *wires = 0;
 *wirebits = 0;
 *regs = 0;
 *regbits = 0;
 *arrs = 0;
 *arrcells = 0;
 *arrbits = 0;

 /* mnets of 0 will not exist unless has at least one net */ 
 if (mdp->mnnum == 0) return;
 for (ni = 0, np = &(mdp->mnets[0]); ni < mdp->mnnum; ni++, np++)
  {
   /* module ports not counted here */
   if (np->iotyp != NON_IO) continue;
   if (np->ntyp < NONWIRE_ST)
    {
     (*wires)++;
     *wirebits += np->nwid;
     continue;
    }
   if (np->n_isarr)
    {
     (*arrs)++;
     acells = (int32) __get_arrwide(np);
     *arrcells += acells;
     *arrbits += acells*np->nwid;
     continue;
    }
   (*regs)++;
   *regbits += np->nwid;
  } 
} 

/*
 * print the per module strength wiring table
 */
static void st_prt2_permod_wiretab(void)
{
 int32 first_time;
 int32 prts, prtbits, wires, wirebits;
 int32 st_prts, st_prtbits, st_wires, st_wirebits;
 int32 tot_prts, tot_prtbits, tot_wires, tot_wirebits;
 int32 st_tot_prts, st_tot_prtbits, st_tot_wires, st_tot_wirebits;
 struct mod_t *mdp;
 char s1[RECLEN], s2[RECLEN], s3[RECLEN], s4[RECLEN], s5[RECLEN];

 if (__design_no_strens) return;

 tot_prts = tot_prtbits = st_tot_prts = st_tot_prtbits = 0;
 tot_wires = tot_wirebits = st_tot_wires = st_tot_wirebits = 0;
 first_time = TRUE;
 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   /* always need to count wires and ports even if no strengths */
   prts = (int32) mdp->mpnum;
   st_cnt_modprt_bits(mdp, &prtbits, &st_prts, &st_prtbits);
   st_cnt_modwires(mdp, &wires, &wirebits, &st_wires, &st_wirebits);
   tot_prts += prts*(int32) mdp->flatinum;
   tot_prtbits += prtbits*(int32) mdp->flatinum;    
   tot_wires += wires*(int32) mdp->flatinum;
   tot_wirebits += wirebits*(int32) mdp->flatinum;

   /* even if module no strengths, goes in total wires */
   if (!mdp->mhassts) continue;
   if (first_time)
    {
     __cv_msg("\n  Per Module Strength Wiring Table:\n");
     __cv_msg(
      "Module                Ports(Bits)       Percent      Wires(Bits)");
     __cv_msg("       Percent\n");
     first_time = FALSE;
    }
   st_tot_prts += st_prts*(int32) mdp->flatinum;
   st_tot_prtbits += st_prtbits*(int32) mdp->flatinum;    
   st_tot_wires += st_wires*(int32) mdp->flatinum;
   st_tot_wirebits += st_wirebits*(int32) mdp->flatinum;

   if (st_prts == 0) { strcpy(s1, ""); strcpy(s2, ""); }
   else
    {
     sprintf(s1, "%d(%d)", st_prts, st_prtbits);
     sprintf(s2, "%.1f(%.1f)", 100.0*((double) st_prts/prts),
      100.0*((double) st_prtbits/prtbits));
    }
   if (st_wires == 0) { strcpy(s3, ""); strcpy(s4, ""); }
   else
    {
     sprintf(s3, "%d(%d)", st_wires, st_wirebits);
     sprintf(s4, "%.1f(%.1f)", 100.0*((double) st_wires/wires),
      100.0*((double) st_wirebits/wirebits));
    }
   bld_modnam(s5, mdp, 20);
   __cv_msg("%-20s%13s  %12s  %15s  %12s\n", s5, s1, s2, s3, s4);   
  }
 __cv_msg(
  "                      -----------    ----------      -----------  ");
 __cv_msg("------------\n");
 if (st_tot_prts == 0) { strcpy(s1, ""); strcpy(s2, ""); }
 else
  {
   sprintf(s1, "%d(%d)", st_tot_prts, st_tot_prtbits);
   sprintf(s2, "%.1f(%.1f)", 100.0*((double) st_tot_prts/tot_prts),
    100.0*((double) st_tot_prtbits/tot_prtbits));
  }
 if (tot_wires == 0) { strcpy(s3, ""); strcpy(s4, ""); }
 else
  {
   sprintf(s3, "%d(%d)", st_tot_wires, st_tot_wirebits);
   sprintf(s4, "%.1f(%.1f)", 100.0*((double) st_tot_wires/tot_wires),
    100.0*((double) st_tot_wirebits/tot_wirebits));
  }
 __cv_msg("Strength total:   %15s   %11s%17s  %12s\n", s1, s2, s3, s4);
}

/*
 * count the number of strength module ports and bits
 */
static void st_cnt_modprt_bits(struct mod_t *mdp, int32 *prtbits, int32 *st_prts,
 int32 *st_prtbits)
{ 
 int32 pi, st_modpbits, modpbits, st_modprts;
 struct mod_pin_t *mpp;
 struct expr_t *mxp, *catxp; 

 st_modprts = 0;
 for (modpbits = st_modpbits = 0, pi = 0; pi < mdp->mpnum; pi++)  
  {
   mpp = &(mdp->mpins[pi]);
   modpbits += (int32) mpp->mpwide;
   mxp = mpp->mpref;
   if (!mxp->x_stren) continue;
   st_modprts++;
   if (mxp->optyp != LCB) { st_modpbits += (int32) mpp->mpwide; continue; }

   /* notice for concats some ports may be strength others not ? */
   for (catxp = mxp->ru.x; catxp != NULL; catxp = catxp->ru.x) 
    { if (catxp->lu.x->x_stren) st_modpbits += (int32) catxp->lu.x->szu.xclen; }
  }
 *prtbits = modpbits;
 *st_prts = st_modprts;
 *st_prtbits = st_modpbits;
}

/*
 * count the number of top level (non in task/func) wires and bits
 */
static void st_cnt_modwires(struct mod_t *mdp, int32 *wires, int32 *wirebits,
 int32 *st_wires, int32 *st_wirebits)
{
 int32 ni;
 int32 mwires, mwirebits, st_mwires, st_mwirebits;
 struct net_t *np;

 mwires = 0;
 mwirebits = 0;
 st_mwires = 0;
 st_mwirebits = 0;
 if (mdp->mnnum != 0)
  {
   for (ni = 0, np = &(mdp->mnets[0]); ni < mdp->mnnum; ni++, np++) 
    {
     /* module ports not counted here */
     if (np->iotyp != NON_IO) continue;
     if (np->ntyp >= NONWIRE_ST) continue;

     mwires++;
     mwirebits += np->nwid;
     if (!np->n_stren) continue;
     st_mwires++;
     st_mwirebits += np->nwid;
    } 
  }
 *wires = mwires;
 *wirebits = mwirebits;
 *st_wires = st_mwires;
 *st_wirebits = st_mwirebits;
} 

/*
 * print the per module task numbers
 * notice number of instances of module does not multiply here 
 */
static void prt2_permod_tasktabs(void)
{
 int32 inits, always, tasks, funcs, begblks, frks;
 int32 tot_inits, tot_always, tot_tasks, tot_funcs, tot_begblks, tot_frks;
 int32 first_time;
 struct mod_t *mdp;
 char s1[RECLEN];

 tot_inits = tot_always = tot_tasks = tot_funcs = tot_begblks = tot_frks = 0;
 for (first_time = TRUE, mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   if (mdp->mtasks == NULL) continue;
   if (first_time)
    {
     __cv_msg("\n  Per Module Task Definition Table:\n");
     __cv_msg(
     "Module            Initial  Always    Task  Function   Lab. Begin");
     __cv_msg("  Lab. Fork\n");
     first_time = FALSE;
    }

   cnt_modtasks(mdp, &inits, &always, &tasks, &funcs, &begblks, &frks);
   tot_inits += inits;
   tot_always += always;
   tot_tasks += frks;
   tot_funcs += funcs;
   tot_begblks += begblks;
   tot_frks += frks;
   bld_modnam(s1, mdp, 20);
   __cv_msg("%-20s%5d   %5d   %5d     %5d        %5d      %5d\n", s1, inits,
    always, tasks, funcs, begblks, frks);
  }
 if (!first_time)
  {
   __cv_msg("                    -----   -----   -----     -----        ");
   __cv_msg("-----      -----\n");
   __cv_msg("Static Total       %6d  %6d  %6d    %6d       %6d     %6d\n",
    tot_inits, tot_always, tot_tasks, tot_funcs, tot_begblks, tot_frks);
  }
}

/*
 * count the number of tasks, named blocks and funcs
 */
static void cnt_modtasks(struct mod_t *mdp, int32 *inits, int32 *always,
 int32 *tsks, int32 *funcs, int32 *begblks, int32 *frks)
{
 int32 iat;
 struct ialst_t *ialp;
 struct task_t *tskp;

 *inits = *always = *tsks = *funcs = *begblks = *frks = 0;
 for (ialp = mdp->ialst; ialp != NULL; ialp = ialp->ialnxt)
  {
   iat = ialp->iatyp;
   if (iat == INITial) (*inits)++;
   else if (iat == ALWAYS) (*always)++;
   /* AIV 07/12/12 - now supporting new SV always_* types */
   else if (iat == ALWAYS_COMB) (*always)++;
   else if (iat == ALWAYS_FF) (*always)++;
   else if (iat == ALWAYS_LATCH) (*always)++;
   else __case_terr(__FILE__, __LINE__);
  }
 for (tskp = mdp->mtasks; tskp != NULL; tskp = tskp->tsknxt)
  {
   if (tskp->tsktyp == FUNCTION) (*funcs)++;
   else if (tskp->tsktyp == TASK) (*tsks)++;
   else if (tskp->tsktyp == Begin) (*begblks)++;
   else if (tskp->tsktyp == FORK) (*frks)++;
   else __case_terr(__FILE__, __LINE__);
  }
}

/*
 * dump every module's table of instantiated types and gate statistics
 */
extern void __prt2_mod_typetab(int32 prt_all)
{
 int32 i, gid;
 int32 *gftab, *gstab, *cgftab, *mftab, *mstab, *uftab, *ustab, *cuftab;
 int32 num_mods, num_udps, mhasudps, first_time;
 int32 num_contas, tot_insts, tot_gates, tot_udps, tot_fcontas, tot_scontas;
 int32 tot_cells, tot_cellgates, tot_celludps, tot_cellassigns;
 struct mod_t *mdp, *imdp;
 struct udp_t *udpp;
 struct primtab_t *primp;
 struct sy_t *syp;
 char s1[RECLEN], s2[RECLEN], filref[RECLEN];

 /* allocate the needed tables */ 
 gftab = (int32 *) __my_malloc((LAST_GSYM + 1)*sizeof(int32));
 gstab = (int32 *) __my_malloc((LAST_GSYM + 1)*sizeof(int32));
 cgftab = (int32 *) __my_malloc((LAST_GSYM + 1)*sizeof(int32));

 for (num_mods = 0, mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   /* need to assign sequence no. to each module */
   /* NOTICE - lastinum used for mod splitting but no more needed by here */ 
   mdp->lastinum = num_mods;
   num_mods++;
  }
 /* know there will always be at least one inst or not get here */
 mftab = (int32 *) __my_malloc(num_mods*sizeof(int32));
 mstab = (int32 *) __my_malloc(num_mods*sizeof(int32));

 num_udps = 0;
 uftab = ustab = cuftab = NULL;
 if (__udphead != NULL)
  {
   for (udpp = __udphead; udpp != NULL; udpp = udpp->udpnxt)
    {
     /* need to assign sequence no. to each udp type */
     udpp->u_idnum = num_udps;
     num_udps++;
    }
   uftab = (int32 *) __my_malloc(num_udps*sizeof(int32));
   ustab = (int32 *) __my_malloc(num_udps*sizeof(int32));
   cuftab = (int32 *) __my_malloc(num_udps*sizeof(int32));
  }
 reset_cntabs(gftab, gstab, cgftab, mftab, mstab, num_mods, uftab, ustab,
  cuftab, num_udps);

 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   /* to get design totals do not zero fields each time through */
   accum_usecnts(mdp, gftab, gstab, cgftab, mftab, mstab, uftab, ustab,
    cuftab, &mhasudps);
  }
 /* print design wide totals */
 __cv_msg("\n  Design Usage Table:\n");
 __cv_msg("Type                      Class  Static   Flat   Location\n"); 
 __cv_msg("                                 Number  Number\n"); 
 /* first 1 line per mod inst - need sorted so must go through mods */
 tot_insts = tot_gates = tot_udps = tot_fcontas = tot_scontas = 0;
 tot_cells = tot_cellgates = tot_cellassigns = tot_celludps = 0;
 for (imdp = __modhdr; imdp != NULL; imdp = imdp->mnxt)
  {
   syp = imdp->msym;
   if (strlen(syp->synam) > 24)
    { strncpy(s1, syp->synam, 23); s1[23] = '-'; s1[24] = '\0'; }
   else strcpy(s1, syp->synam);

   if (imdp->minstnum == 0) strcpy(s2, "top");
   else if (imdp->m_iscell) strcpy(s2, "cell");
   else strcpy(s2, "module");
   __cv_msg("%-24s  %-6s%7d %7d  %s:%d\n", s1, s2, mstab[imdp->lastinum],
    mftab[imdp->lastinum], __schop(filref, __in_fils[syp->syfnam_ind]),
    syp->sylin_cnt); 
   tot_insts += (int32) mftab[imdp->lastinum];
   num_contas = imdp->mcanum;
   if (imdp->m_iscell)
    { 
     tot_cellassigns += (int32) imdp->flatinum*num_contas;
     tot_cells += (int32) mftab[imdp->lastinum];
    }
   tot_fcontas += (int32) imdp->flatinum*num_contas;
   tot_scontas += num_contas;
  }
 for (udpp = __udphead; udpp != NULL; udpp = udpp->udpnxt)
  {
   /* if udp defined list even if not used */
   syp = udpp->usym;
   if (strlen(syp->synam) > 24)
    { strncpy(s1, syp->synam, 23); s1[23] = '-'; s1[24] = '\0'; }
    else strcpy(s1, syp->synam);
   __cv_msg("%-24s  %-6s%7d %7d  %s:%d\n", s1, "udp", ustab[udpp->u_idnum],
    uftab[udpp->u_idnum], __schop(filref, __in_fils[syp->syfnam_ind]),
    syp->sylin_cnt); 

   tot_udps += (int32) uftab[udpp->u_idnum];
   tot_celludps += (int32) cuftab[udpp->u_idnum];
  }
 for (i = 0, primp = prims; i < NPRIMS; i++, primp++)
  {
   gid = primp->gateid;
   if (gstab[gid] == 0) continue;
   __cv_msg("%-24s  %-6s%7d %7d\n", primp->gatnam, "gate", gstab[gid],
    gftab[gid]);
   tot_gates += gftab[gid]; 
   tot_cellgates += cgftab[gid];
  }
 if (tot_fcontas != 0 || tot_scontas != 0)
  __cv_msg("%-24s  %-6s%7d %7d\n", "wide-assign", "assign", tot_scontas,
   tot_fcontas);

 if (tot_cells == 0)
  {
   __cv_msg(
    "\n  Flattened Design: %d instances, %d udps, %d gates and %d assigns.\n",
    tot_insts, tot_udps, tot_gates - gftab[G_ASSIGN],
    tot_fcontas + gftab[G_ASSIGN]);
  }
 else
  { 
   __cv_msg(
   "\n  Flattened Design: %d instances (%d of cells), %d udps (%d in cells),\n",
    tot_insts, tot_cells, tot_udps, tot_celludps);
   __cv_msg("   %d gates (%d in cells) and %d assigns (%d in cells).\n",
    tot_gates - gftab[G_ASSIGN], tot_cellgates - cgftab[G_ASSIGN],
    tot_fcontas + gftab[G_ASSIGN], tot_cellassigns + cgftab[G_ASSIGN]);
  }

 if (!prt_all) goto free_tabs;
 __cv_msg(
  "\n  Individual Modules Content Tables (Procedural Only Excluded)");
 first_time = TRUE;
 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   first_time = TRUE;
   reset_cntabs(gftab, gstab, cgftab, mftab, mstab, num_mods, uftab, ustab,
    cuftab, num_udps);
   accum_usecnts(mdp, gftab, gstab, cgftab, mftab, mstab, uftab, ustab,
    cuftab, &mhasudps);

   /* first 1 line per mod inst - need sorted so must go through mods */
   for (imdp = __modhdr; imdp != NULL; imdp = imdp->mnxt)
    {
     if (mstab[imdp->lastinum] == 0) continue;
     if (first_time) { prt_modhdr(mdp); first_time = FALSE; }
     if (strlen(imdp->msym->synam) > 24)
      { strncpy(s1, imdp->msym->synam, 23); s1[23] = '-'; s1[24] = '\0'; }
     else strcpy(s1, imdp->msym->synam);
     if (imdp->m_iscell) strcpy(s2, "cell"); else strcpy(s2, "module");
     __cv_msg("%-24s  %-6s        %10d      %10d\n", s1, s2,
      mstab[imdp->lastinum], mftab[imdp->lastinum]);
    }
   if (mhasudps)
    {
     for (udpp = __udphead; udpp != NULL; udpp = udpp->udpnxt)
      {
       if (ustab[udpp->u_idnum] == 0) continue;

       if (first_time) { prt_modhdr(mdp); first_time = FALSE; }
       if (strlen(udpp->usym->synam) > 24)
        { strncpy(s1, udpp->usym->synam, 23); s1[23] = '-'; s1[24] = '\0'; }
       else strcpy(s1, udpp->usym->synam);
       __cv_msg("%-24s  %-6s        %10d      %10d\n", s1, "udp",
        ustab[udpp->u_idnum], uftab[udpp->u_idnum]);
      }
    }
   if (mdp->mgates != NULL)
    {
     for (i = 0, primp = prims; i < NPRIMS; i++, primp++)
      {
       gid = primp->gateid;
       if (gstab[gid] == 0) continue;
       if (first_time) { prt_modhdr(mdp); first_time = FALSE; }
       __cv_msg("%-24s  gate          %10d      %10d\n", primp->gatnam,
        gstab[gid], gftab[gid]);
      }
    }
   num_contas = mdp->mcanum;
   if (num_contas != 0)
    {
     if (first_time) { prt_modhdr(mdp); first_time = FALSE; }
     __cv_msg("%-24s  %-12s  %10d      %10d\n", "wide-assign",
      "assign", num_contas, num_contas*(int32)mdp->flatinum);
    }
  }
 /* may somehow have no modules? */
 if (first_time) __cv_msg("\n");
free_tabs:;
 /* if no alloca would need frees here */

 __my_free(gftab, (LAST_GSYM + 1)*sizeof(int32));
 __my_free(gstab, (LAST_GSYM + 1)*sizeof(int32));
 __my_free(cgftab, (LAST_GSYM + 1)*sizeof(int32));
 __my_free(mftab, num_mods*sizeof(int32));
 __my_free(mstab, num_mods*sizeof(int32));
 if (uftab != NULL) __my_free(uftab, num_udps*sizeof(int32)); 
 if (ustab != NULL) __my_free(ustab, num_udps*sizeof(int32)); 
 if (cuftab != NULL) __my_free(cuftab, num_udps*sizeof(int32)); 
}

/*
 * print the module table header - if contains declared elements    
 */
static void prt_modhdr(struct mod_t *mdp)
{
 char s1[RECLEN], s2[RECLEN];

 if (!mdp->m_iscell) strcpy(s1, "Module"); else strcpy(s1, "Cell");
 if (mdp->minstnum == 0) strcpy(s2, "(top)");
 else sprintf(s2, "(Instantiated %d Times)", mdp->flatinum);
 __cv_msg("\n  %s %s %s Type Usage Table:\n", s1, mdp->msym->synam, s2);
 __cv_msg(
  "Type                      Class      Static Number     Flat Number\n");
} 

/*
 * reset all count tables
 */
static void reset_cntabs(int32 *gftab, int32 *gstab, int32 *cgftab, int32 *mftab,
 int32 *mstab, int32 nmods, int32 *uftab, int32 *ustab, int32 *cuftab, int32 nudps)
{
 if (gftab != NULL) memset(gftab, 0, (LAST_GSYM + 1)*sizeof(int32));
 if (gstab != NULL) memset(gstab, 0, (LAST_GSYM + 1)*sizeof(int32));
 if (cgftab != NULL) memset(cgftab, 0, (LAST_GSYM + 1)*sizeof(int32));

 if (mftab != NULL) memset(mftab, 0, nmods*sizeof(int32));
 if (mstab != NULL) memset(mstab, 0, nmods*sizeof(int32));
 if (uftab != NULL) memset(uftab, 0, nudps*sizeof(int32));
 if (ustab != NULL) memset(ustab, 0, nudps*sizeof(int32));
 if (cuftab != NULL) memset(cuftab, 0, nudps*sizeof(int32));
}

/*
 * accumulate usage statistics gates in one module 
 * must be reset to 0 before here - values accumulated 
 * if this module has udps sets has udp flag
 */
static void accum_usecnts(struct mod_t *mdp, int32 *gftab, int32 *gstab,
 int32 *cgftab, int32 *mftab, int32 *mstab, int32 *uftab, int32 *ustab, int32 *cuftab,
 int32 *mhasudps)
{
 int32 ii, gi, gid;
 struct inst_t *ip;
 struct mod_t *imdp;
 struct gate_t *gp;
 struct udp_t *udpp;

 /* notice previous call always reset each mod use count */
 /* first time starts at 0 */
 /* update both in this module count and design wide use count */
 for (ii = 0; ii < mdp->minum; ii++)
  {
   ip = &(mdp->minsts[ii]);
   imdp = ip->imsym->el.emdp;
   /* notice lastinum is just sequence no. assigned here - fld reused here */
   mstab[imdp->lastinum] += 1; 
   mftab[imdp->lastinum] += (int32) mdp->flatinum;
  }   
 /* finally do the counting */
 *mhasudps = FALSE;
 for (gi = 0; gi < mdp->mgnum; gi++)
  {
   gp = &(mdp->mgates[gi]);
   if (gp->g_class == GC_UDP)
    {
     *mhasudps = TRUE;
     udpp = gp->gmsym->el.eudpp;
     /* DBG remove --- */
     if (ustab == NULL) __misc_terr(__FILE__, __LINE__);
     if (uftab == NULL) __misc_terr(__FILE__, __LINE__);
     /* --- */
     ustab[udpp->u_idnum] += 1;
     uftab[udpp->u_idnum] += (int32) mdp->flatinum;
     continue;
    }
   gid = gp->gmsym->el.eprimp->gateid;
   gstab[gid] += 1;
   gftab[gid] += (int32) mdp->flatinum;
  }
 if (!mdp->m_iscell) return;
 
 for (gi = 0; gi < mdp->mgnum; gi++)
  {
   gp = &(mdp->mgates[gi]);
   if (gp->g_class == GC_UDP)
    {
     udpp = gp->gmsym->el.eudpp;
     /* DBG remove --- */
     if (cuftab == NULL) __misc_terr(__FILE__, __LINE__);
     /* --- */
     cuftab[udpp->u_idnum] += (int32) mdp->flatinum;
     continue;
    }
   gid = gp->gmsym->el.eprimp->gateid;
   cgftab[gid] += (int32) mdp->flatinum;
  }
}
