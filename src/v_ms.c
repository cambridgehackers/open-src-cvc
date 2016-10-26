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
 * miscellaneous routines
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <pwd.h> 

#include <sys/types.h>
#include <sys/timeb.h>
#include <sys/fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

#include <time.h>
#include <setjmp.h>
#include <ctype.h>
#include <errno.h>
#include <stdarg.h>

#ifdef __DBMALLOC__
#include "../malloc.h"
#endif

#include "v.h"
#include "cvmacros.h"

/* local prototypes */
static int32 rd_chk_ifdef_macnam_to_str(char *, int32); 
static char *expand_arg_macro(struct sy_t *, int32 *);
static void process_macdef(void);
static void dmp_macdef_exptab(char *, struct macexp_t *);
static void process_macundef(void);
static char *bld_macdef_arglist(int32 *);
static char *remchk_macdef_coms(char *);
static struct macexp_t *bld_mac_expandtab(char *, char *, int32);
static int32 find_mac_formal_arg(char *);
static void free_macexplst(struct macexp_t *);
static void do_argmacdefine(char *, struct macexp_t *, int32);
static int32 ifdef_skip_section(FILE *, int32);
static void handle_ifdef_skip_eof(int32, int32, int32);
static int32 my_getc(FILE *);
static int32 rd_comment(FILE *);
static int32 skipto_attr_end(FILE *); 
static void rd_attribute(FILE *);
static int32 vgetstr(FILE *);
static void str_tovval(void);
static void unget2_vtok(int32);
static int32 rd_num(FILE *, int32);
static void rem_lead_0chars(char *);
static int32 voverwhite(FILE *, int32);
static int32 chlen_to_bitlen(int32, int32);
static void chg_abwrklen(int32);
static void to_dec(int32 *);
static void wide_strtoverdec(int32);
static void to_bin(int32);
static void to_oct(int32);
static void to_hex(int32);
static int32 vnum_toowide(word32 *, int32);
static int32 nibblexz(word32, word32, int32);
static int32 octdigxz(word32 *, word32 *, int32);
static void widen_val(word32 *, int32, int32, word32);
static int32 get_vkeywrd(char *);
static int32 set_syncto_tokclass(int32);
static int32 set_specitem_class(void);
static int32 set_udpsyncto(int32);
static int32 get_cfgkeywrd(char *);
static int32 get_cmdcomment(FILE *);
static void one_rot(struct tnode_t *, struct tnode_t *, struct tnode_t *);
static void two_rot(struct tnode_t *, struct tnode_t *, struct tnode_t *);
static struct tnode_t *alloc_tnode(struct symtab_t *);
static char *__to_nppsubtyp(char *, word32);
static char *decompnum_to_str(char *, char *, int32, int32);
static char *nfbig_alloc(int32);
static char *tilde_expand(char *, int32 *);
static char *pv_stralloc2(char *);
static int32 try_chg_tononesc(void);
static int32 ch_tobits(word32 *, word32 *, int32);
static int32 ch_toocts(word32 *, word32 *, int32);
static int32 ch_tohexs(word32 *, word32 *, int32);

/* extern prototypes (maybe defined in this module) */
extern void __get_vtok(void);
extern int32 __chk_beg_line(int32);
extern void __collect_line(void);
extern void __skipover_line(void);
extern void __do_macdefine(char *, char *);
extern int32 __bqline_emptytail(char *);
extern void __do_include(void);
extern int32 __rd_ialine(void);
extern int32 __get1_vtok(FILE *);
extern void __vstr_to_vval(word32 *, char *, int32);
extern struct xstk_t *__cstr_to_vval(char *);
extern void __unget_vtok(void);
extern int32 __to_base(int32);
extern int32 __is_vdigit(int32, int32);
extern void __to_dhboval(int32, int32);
extern char *__prt_vtok(void);
extern char *__prt2_vtok(int32);
extern char *__to_opname(word32);
extern char *__get_vkeynam(char *, int32);
extern int32 __vskipto_modend(int32);
extern int32 __vskipto2_modend(int32, int32);
extern int32 __vskipto3_modend(int32, int32, int32);
extern int32 __vskipto_any(int32);
extern int32 __vskipto2_any(int32, int32);
extern int32 __vskipto3_any(int32, int32, int32);
extern int32 __vskipto4_any(int32, int32, int32, int32);
extern int32 __spec_vskipto_any(int32);
extern int32 __spec_vskipto2_any(int32, int32);
extern int32 __spec_vskipto3_any(int32, int32, int32);
extern int32 __udp_vskipto_any(int32);
extern int32 __udp_vskipto2_any(int32, int32);
extern int32 __udp_vskipto3_any(int32, int32, int32);
extern int32 __get_cmdtok(FILE *);
extern struct sy_t *__in_gen_scopes_get_sym_env(char *);
extern struct sy_t *__get_sym_env(char *);
extern struct sy_t *__find_sym(char *);
extern struct sy_t *__decl_sym(char *, struct symtab_t *);
extern void __add_sym(char *, struct tnode_t *);
extern struct sy_t *__get_sym(char *, struct symtab_t *);
extern struct tnode_t *__vtfind(char *, struct symtab_t *);
extern struct sy_t *__zget_sym(char *, struct sy_t **, word32);
extern struct symtab_t *__alloc_symtab(int32);
extern int32 __ip_indsrch(char *);
extern char *__to_idnam(struct expr_t *);
extern char *__to_mpnam(char *, char *);
extern int32 __fr_wtnam(int32);
extern char *__to_wtnam(char *, struct net_t *);
extern char *__to_wtnam2(char *, word32);
extern char *__to_ptnam(char *, word32);
extern char *__to_splt_nam(char *, int32);
extern word32 __fr_stren_nam(int32);
extern char *__to_stren_nam(char *, int32, int32);
extern char *__to_stval_nam(char *, word32);
extern char *__to1_stren_nam(char *, int32, int32);
extern int32 __is_capstren(int32);
extern int32 __fr_cap_size(int32);
extern word32 __to_cap_size(int32);
extern char *__to_sytyp(char *, word32);
extern char *__to_tsktyp(char *, word32);
extern char *__to_sttyp(char *, word32);
extern char *__to_qctyp(char *, word32);
extern char *__to_tetyp(char *, void *);
extern char *__to_npptyp(char *, struct net_pin_t *);
extern char *__to_deltypnam(char *, word32);
extern char *__to_tcnam(char *, word32);
extern int32 __fr_tcnam(char *);
extern char *__to_gonam(char *, struct gate_t *, word32);
extern char *__to_ginam(char *, struct gate_t *, word32, int32);
extern char *__to_vnam(char *, word32, word32);
extern char *__to_vvstnam(char *, word32);
extern char *__to_vvnam(char *, word32);
extern char *__to_uvvnam(char *, word32);
extern char __to_baselet(int32);
extern char *__to_timunitnam(char *, word32);
extern char *__to_edgenam(char *, word32);
extern char *__to_dcenam(char *, word32);
extern char *__pv_stralloc(char *);
extern char *__my_malloc(size_t);
extern void __my_free(void *, size_t);
extern char *__my_realloc(void *, size_t, size_t);
extern void __my_fclose(FILE *);
extern void __my_rewind(FILE *);
extern int32 __tilde_open(char *, int32);
extern FILE *__tilde_fopen(char *, char *);
extern FILE *__my_fopen(char *, char *);
extern int32 __tilde_creat(char *);
extern int32 __my_creat(char *);
extern char *__schop(char *, char *);
extern char *__bld_lineloc(char *, word32, int32);
extern void __init_sy(struct sy_t *);

extern void __crit_msg(char *, ...);
extern void __sysfatal_msg(char *, ...);
extern void __cv_msg(char *, ...);
extern void __cvsim_msg(char *, ...);
extern void __dbg_msg(char *, ...);
extern void __tr_msg(char *, ...);
extern void __os_exit_misc_terr(char *, int32);
extern void __os_exit_pv_terr(int32, char *, ...);
extern void __misc_terr(char *, int32);
extern void __misc_fterr(char *, int32);
extern void __misc_gfterr(char *, int32, word32, int32);
extern void __misc_sgfterr(char *, int32);
extern void __case_terr(char *, int32);
extern void __arg_terr(char *, int32);
extern void __pv_terr(int32, char *, ...);
extern void __fterr(int32, char *, ...);
extern void __sgfterr(int32, char *, ...);
extern void __gfterr(int32, word32, int32, char *, ...);
extern void __pv_err(int32, char *, ...);
extern void __pv_ferr(int32, char *, ...);
extern void __sgferr(int32, char *, ...);
extern void __gferr(int32, word32, int32, char *, ...);
extern void __ia_err(int32, char *, ...);
extern void __via_err(int32, char *, va_list, va_list);
extern void __pv_warn(int32, char *, ...);
extern void __pv_fwarn(int32, char *, ...);
extern void __sgfwarn(int32, char *, ...);
extern void __gfwarn(int32, word32, int32, char *, ...);
extern void __ia_warn(int32, char *, ...);
extern void __via_warn(int32, char *, va_list, va_list);
extern void __inform(int32, char *, ...);
extern void __finform(int32, char *, ...);
extern void __sgfinform(int32, char *, ...);
extern void __gfinform(int32, word32, int32, char *, ...);
extern int32 __em_suppr(int32);
extern void __my_fprintf(FILE *, char *, ...);
extern void __my_vfprintf(FILE *, char *, va_list, va_list);
extern void __vpi_error_trycall(void);
extern void __cberror_fill_einfo(int32, int32, char *, char *, int32);

extern void __o_dbg_msg(char *s, ...);
extern void __o_tr_msg(char *, ...);

extern int32 __pop_vifstk(void);
extern int32 __open_sfil(void);
extern void __push_vinfil(void);
extern void __grow_infils(int32);
extern void __grow_xstk(void);
extern void __chg_xstk_width(struct xstk_t *, int32);
extern double __my_strtod(char *, char **, int32 *);
extern word32 __my_strtoul(char *, char **, int *);
extern int32 __trim1_0val(word32 *, int32);
extern void __lmult(word32 *, word32 *, word32 *, int32);
extern void __ladd(word32 *, word32 *, word32 *, int32);
extern void __lhsbsel(word32 *, int32, word32);
extern void __lhspsel(word32 *, int32, word32 *, int32);
extern void __rhspsel(word32 *, word32 *, int32, int32);
extern void __my_exit(int32, int32);
extern char *__to_timstr(char *, word64 *);
extern char *__to_dispst_str(char *, word32);

extern void __process_conta_ev(void);
extern void __process_wire_ev(void);
extern void __process_mipd_nchg_ev(void);
extern void __process_nbpa_ev(void);
extern void __process_gatechg_ev(void);
extern void __process_trpthdst_ev(void);
extern void __process_vpidrv_ev(void);
extern void __setdel_call_misctf(void);
extern void __sync_call_misctf(void);
extern void __process_putpdel_ev(void);
extern void __process_vpi_varputv_ev(void);
extern void __process_thrd_ev(void);
extern void __delay_callback(void);

extern const struct opinfo_t __opinfo[];
extern const byte __stren_map_tab[];
extern const word32 __masktab[];

/* system stuff */
extern int32 errno;

/* jmp buf defined in v_dbg */
extern jmp_buf __iact_jmpbuf;
extern const char __pv_ctab[];

/*
 * ROUTINES THE INTERFACE TO GET TOKEN ROUTINES
 */

/*
 * get a Verilog token (outer routine for macro handling)
 *
 * routine sets globals __toktyp and __token and may set other for numbers
 * (modified from yylex in "The Unix Programming Environment" p. 337)
 *
 * BEWARE - need to be careful here because for efficiency using global 
 * strings ok to use __xs but not call __prt2_vtok more than once in error
 */
extern void __get_vtok(void)
{
 int32 ttyp, ifdtyp, len, ifdef_goto_lab;
 int32 ifdef_skip_endttyp;
 struct sy_t *syp, *tmpsyp;
 char macro_nam[IDLEN], *chp;

 /* assume no attribute prefix */
 __attr_prefix = FALSE; 
 if (__lasttoktyp != UNDEF)
  {
   __toktyp = __lasttoktyp;
   strcpy(__token, __lasttoken);
   __lasttoktyp = UNDEF;
   /* SJM 10/16/00 - must save and restore state of pending attr prefix */
   /* seen when tok is pushed back - happens for endmodule then read of */
   /* module to check for EOF */
   __attr_prefix = __last_attr_prefix;

   /* extremely rare number push back case */
   if (__toktyp == NUMBER)
    {
     word32 wlen; 

     __itokbase = __lastitokbase;
     __itoksized = __lastitoksized;
     __itok_sv_unbas_unsiz = __lastitok_sv_unbas_unsiz;  
     __itoksizdflt = __lastitoksizdflt;
     __itok_signed = __lastitok_signed;
     __itoklen = __lastitoklen;

     /* used malloc to save const value, now need to restore and free */
     wlen = wlen_(__itoklen);
     memcpy(__acwrk, __lastacwrk, wlen*WRDBYTES);
     __my_free(__lastacwrk, wlen*WRDBYTES);
     memcpy(__bcwrk, __lastbcwrk, wlen*WRDBYTES);
     __my_free(__lastbcwrk, wlen*WRDBYTES);
     __lastacwrk = __lastbcwrk = NULL;
    }
   else if (__toktyp == REALNUM)
    {
     __itokbase = __lastitokbase;
     __itoksized = __lastitoksized;
     __itok_sv_unbas_unsiz = __lastitok_sv_unbas_unsiz;  
     __itoksizdflt = __lastitoksizdflt;
     __itok_signed = __lastitok_signed;
     __itoklen = __lastitoklen;
     __itok_realval = __lastitok_realval;
    }
   return;
  }

vtagain:
 /* file will be NULL when reading from macro text */
 switch ((ttyp = __get1_vtok(__in_s))) {
  case TEOF:
   /* first try to pop some sort of outer nested thing */
   if (__pop_vifstk())
    {
     /* SJM 06/22/00 - for 2 stage 2 tok num - ready to read 2nd tok of num */ 
     if (__macro_sep_width)
      {
       __maybe_2tok_sized_num = TRUE;
       __macro_sep_width = FALSE;
      }
     goto vtagain;
    }
   /* next try to replace just finished 0th element with new input file */
   if (__cur_infi + 1 > __last_inf || __iact_state)
    { __toktyp = TEOF; return; }
   __cur_infi++; 
   if (!__open_sfil()) { __toktyp = TEOF; return; }
   /* know first token of file flag now on */
   goto vtagain;
  case CDIR_DEFINE:
   /* on return - know all of line read */
   process_macdef();
   goto vtagain;
  case CDIR_UNDEF:
   process_macundef();
   goto vtagain;
  case CDIR_INCLUDE:
   if (__iact_state)
    {
illegal_iact_dir:
     __ia_err(1401,
      "%s compiler directive illegal in interactive commands",
      __prt2_vtok(ttyp));

     /* SJM 01-24-24 - IFDEF ANYWHERE this is good since error recovery */
     __skipover_line();
     goto vtagain;
    }
   /* on return all of line read - trims tail of line for file name */ 
   if (!__chk_beg_line(CDIR_INCLUDE)) goto vtagain;
   /* collect line into mac wr kstrafter first skips white space to token */
   __collect_line();
   __do_include();
   goto vtagain;
  case CDIR_IFDEF: case CDIR_IFNDEF: 
   /* SJM 07-31-09 - ifdef to required endif region can only start here */
   if (__iact_state) goto illegal_iact_dir;
   ifdtyp = ttyp;

   /* SJM 07-27-09 - new routine to get mac nam after ifdef or elsif */
   ifdef_goto_lab = rd_chk_ifdef_macnam_to_str(macro_nam, ifdtyp); 
   /* SJM 07-31-09 - if error does not really start an `ifdef region */
   /* some kind of error where recovery is skip rest of line then continue */

   /* SJM 01-24-12 - IFDEF ANYWHERE this is good since error recovery */
   if (ifdef_goto_lab == 1) { __skipover_line(); goto vtagain; }

   /* some kind of error where recovery is reading next token */
   if (ifdef_goto_lab == 2) goto vtagain;

   __in_ifdef_level++;
   /* notice for macro with args. here still just use name */
   tmpsyp = __get_sym(macro_nam, __pv_defsyms);
   /* undeclare when macro undefed because no way to remove from symtab */
   if (tmpsyp != NULL && !tmpsyp->sydecl) tmpsyp = NULL;

   /* `ifndef reverses sense of `ifdef - following C preprocessor */
   if ((ifdtyp == CDIR_IFDEF && tmpsyp == NULL)
    || (ifdtyp == CDIR_IFNDEF && tmpsyp != NULL))
    {
     /* case 1: `ifdef symbol not defined (i.e. if fails) */
skip_again:

     /* SJM 07-31-09 - idea of this ifdef F code, is to keep looking for a */
     /* T (defined through any number of ifdefs at top level (level 0) */
     /* until either find an else which is T by default since if F or an */
     /* elsif - if elsif T then becomes normal ifdef from there on */

     /* SJM 01-24-12 - IFDEF ANYWHERE - this skip no more skip line */
     ifdef_skip_endttyp = ifdef_skip_section(__in_s, ifdtyp);
     /* DBG remove ---
     if (__debug_flg)
      {
       __dbg_msg(
        "==>>> call of ifdef skip section (line %d) - returned ttyp: %s\n",
        __lin_cnt, __prt2_vtok(ifdef_skip_endttyp));
      }
     --- */
     /* case 1a: read the end so done */ 
     if (ifdef_skip_endttyp == CDIR_ENDIF)
      {
       /* if this is `endif just skipped `ifdef (or `ifndef) so continue */
       /* if else enter look for else state */
       /* SJM 07-31-09 - done with this ifdef, rest elsif seen t flag and */
       /* go back to normal read and include tokens in Verilog src stream */
       /* SJM 08-05-09 - found endif set this level ignore rest to F and */
       /* then move up a level */
       __have_t_ignore_elsif[__in_ifdef_level] = FALSE;
       __in_ifdef_level--;

       /* DBG remove ---
       if (__debug_flg)
        {
         __dbg_msg(
          "== in skip got to endif - t ignore set to F (lin %d lev=%d)\n",
          __lin_cnt, __in_ifdef_level);
        }
       --- */
       goto vtagain;
      }
     /* case 1b: read `else - continue reading after skip end of line */
     /* when see end will adjust nesting and check for bad syntax */
     /* SJM 08-03-09 - only get here if found a T condition so need to skip */
     if (ifdef_skip_endttyp == CDIR_ELSE)
      {
       /* if have already seen a T ifdef or eslif, keep skipping */
       if (__have_t_ignore_elsif[__in_ifdef_level])
        {
         /* DBG remove ---
         if (__debug_flg)
          {
           __dbg_msg(
            "== in skip got to else - t ignore T keep skipping (lin %d lev=%d)\n",
            __lin_cnt, __in_ifdef_level);
          }
         --- */
         ifdtyp = CDIR_ELSE;
         // IFDEF ANYWHERE no longer skip line - __skipover_line();
         goto skip_again;
        }
      
       /* need to include `else in token stream - since no T cond up to here */
       /* DBG remove ---
       if (__debug_flg)
        {
         __dbg_msg(
          "== in skipping got to else - t ignore F put in tok stream(lin %d lev=%d)\n",
          __lin_cnt, __in_ifdef_level);
        }
       --- */
       // IFDEF ANYWHERE no longer skip line - __skipover_line();
       goto vtagain;
      }
     /* case 1c: read `elsif */
     /* SJM 08-03-09 - new complex case - must not check if previous T */
     if (ifdef_skip_endttyp == CDIR_ELSIF)
      {
       ifdtyp = CDIR_ELSIF;
       /* if have already seen a T elseif do not evaluate macro nam */
       if (__have_t_ignore_elsif[__in_ifdef_level])
        {
         /* DBG remove ---
         if (__debug_flg)
          {
           __dbg_msg(
            "== in skip got to elseif - t ignore T keep skipping (lin %d lev=%d)\n",
            __lin_cnt, __in_ifdef_level);
          }
         --- */
         ifdtyp = CDIR_ELSIF;
         // IFDEF ANYWHERE __skipover_line();
         goto skip_again;
        }

       /* have not seen T if or elsif yet, see if this macro name is T */
       ifdef_goto_lab = rd_chk_ifdef_macnam_to_str(macro_nam, ifdtyp); 
       /* if error, assume false, skip and continue as usual */
       /* IFDEF ANYWHERE 1 and 2 are errors */
       if (ifdef_goto_lab == 1 || ifdef_goto_lab == 2) goto skip_again;

       /* see if macro nam defined */
       tmpsyp = __get_sym(macro_nam, __pv_defsyms);
       /* undeclare when macro undefed because no way to remove from symtab */
       if (tmpsyp != NULL && !tmpsyp->sydecl) tmpsyp = NULL;
       /* if macro name not defined, skip some more */
       if (tmpsyp == NULL)
        { 
         /* SJM 01-20-11 - for errors with ifdef ignored, misc terr wrong */
         if (__pv_err_cnt <= 0 && __have_t_ignore_elsif[__in_ifdef_level])
          __misc_terr(__FILE__, __LINE__);
         /* DBG remove ----
         if (__debug_flg)
          {
           __dbg_msg(
            "== in skip got to elsif with t ignore F - %s undefined (lin %d lev=%d)\n",
            macro_nam, __lin_cnt, __in_ifdef_level);
          }
         --- */
         ifdtyp = CDIR_ELSIF;
         // IFDEF ANYWHERE __skipover_line();
         goto skip_again;
        }
       /* macro name defined - must include */
       /* this makes sure that when see future elsif, will always be F */ 
       /* SJM 08-05-09 for ifndef, tmpsyp can be nil and still get here */
       /* DBG remove  ---
       if (__debug_flg)
        {
         __dbg_msg(
          "== in skip got to elsif with t ignore F set to T - %s defined (lin %d lev=%d)\n",
          macro_nam, __lin_cnt, __in_ifdef_level);
        }
       --- */
       __have_t_ignore_elsif[__in_ifdef_level] = TRUE;
       // IFDEF ANYWHERE__skipover_line();
       goto vtagain;
      }
     else __case_terr(__FILE__, __LINE__);
    }
   /* case 2: outer level ifdef sym def - include tokens in src stream */
   /* to `else, `elsif or endif` */
   /* extract the macro nam */
   /* SJM 08-05-09 for ifndef, tmpsyp can be nil and still get here */
   /* DBG remove ---
   if (__debug_flg)
    {
     __dbg_msg(
      "== outer level ifdef %s defined set have t ignore to T - include tokens (lin %d lev=%d)\n",
      macro_nam, __lin_cnt, __in_ifdef_level);
    }
   --- */
   __have_t_ignore_elsif[__in_ifdef_level] = TRUE;
   /* must always skip over rest of line */
   // IFDEF ANYWHERE__skipover_line();
   goto vtagain;
  case CDIR_ELSIF:
   if (__iact_state) goto illegal_iact_dir;
   // IFDEF ANYWHERE if (!__chk_beg_line(CDIR_ELSIF)) goto vtagain;

   /* SJM 07-31-09 - new elsif algorithm - get here on end of first T */ 
   /* if or elsif */
   /* DBG remove ---
   if (__debug_flg)
    {
     __dbg_msg("== seen elsif after have t ignore T - just skip (lin %d lev=%d)\n",
      __lin_cnt, __in_ifdef_level);
    }
   --- */
   /* think this can never happen */
   if (__in_ifdef_level == 0)
    {
     __pv_ferr(925, "`elseif read but no previous matching initial `ifdef");
     goto vtagain;      
    }
   ifdtyp = CDIR_ELSIF;
   /* SJM 01-20-11 - for errors with ifdef ignored, misc terr wrong */
   /* DBG remove ---
   if (!__have_t_ignore_elsif[__in_ifdef_level])
    __misc_terr(__FILE__, __LINE__);  
   ---- */
   goto skip_again;
  case CDIR_ELSE:
   /* SJM 08-03-09 - need the iact check in case syntax err ifdef in iact */ 
   if (__iact_state) goto illegal_iact_dir;
   // IFDEF ANYWHERE - if (!__chk_beg_line(CDIR_ELSE)) goto vtagain;

   /* DBG remove ---
   if (__debug_flg)
    {
     __dbg_msg("== seen else know t ignore T - just skip (lin %d lev=%d)\n",
      __lin_cnt, __in_ifdef_level);
    }
   --- */

   /* SJM 01-20-11 - for errors with ifdef ignored, misc terr wrong */
   /* DBG remove --- 
   if (__pv_err_cnt <= 0 && !__have_t_ignore_elsif[__in_ifdef_level])
    __misc_terr(__FILE__, __LINE__);  
   ---- */
   /* know ifdef or an elsif was true - this is end and need to skip */
   ifdtyp = CDIR_ELSE;
   if (__in_ifdef_level == 0)
    {
     __pv_ferr(924, "`else read but no previous matching initial `ifdef");
     /* IFDEF ANYWHERE ok, since error condition */
     __skipover_line();
     goto skip_again;
    }
   // IFDEF ANYWHERE __skipover_line();
   goto skip_again;
  case CDIR_ENDIF:
   /* SJM 08-03-09 - can only get here at end of tokens included in src */
   /* i.e. last ifdef, elsif, or else was still a ignore t F so included */
   if (__iact_state) goto illegal_iact_dir;
   // IFDEF ANYWHERE if (!__chk_beg_line(CDIR_ENDIF)) goto vtagain;

   /* DBG remove ---
   if (__debug_flg)
    {
     __dbg_msg(
      "== seen endif just after included src toks set t ignore to F - (pre dec lev=%d)\n",
      __in_ifdef_level);
    }
  --- */
   __have_t_ignore_elsif[__in_ifdef_level] = FALSE;

   // IFDEF ANYWHERE__skipover_line();
   /* know have t ignore elsif T and must leave */
   /* think this can never happen */
   if (__in_ifdef_level == 0)
    {
     __pv_ferr(925, "`endif read but no previous matching initial `ifdef");
     goto vtagain;      
    }
   __in_ifdef_level--;
   /* end so go up one nested ifdef level */
   goto vtagain;
  /* SJM 09/18/99 - these need to be supported inside modules */
  /* SJM 09/18/99 - these need to be supported inside modules */
  case CDIR_ENDPROTECT:
  case CDIR_ENDPROTECTED:
  case CDIR_PROTECT:
  case CDIR_PROTECTED:
#ifndef __CVC_RT__
   __pv_fwarn(619, "directive %s unimplemented", __prt2_vtok(ttyp));
   /* IFDEF ANYWHERE skip ok for these directives - must be on one line */
   __skipover_line();
#endif
   goto vtagain;
  /* notice time scale can only appear outside modules*/
  case ID:
   /* user redefinition of compiler directive overwrites keyword */
   if (*__token == '$') goto ret_id;

   if (*__token == '`')
    {
     /* AIV 11/17/10 - added SV support for `__FILE__ and `__LINE__ */
     if (__sv_parse && strcmp(__token, "`__FILE__") == 0)
      {
       /* just make a string with the name of the current file */
       __file_just_op = FALSE;
       strcpy(__strtoken, __cur_fnam);
       __toktyp = LITSTR;
       __itoklen = strlen(__strtoken)*8;
       __itok_signed = FALSE;
       __itoksized = TRUE;
       str_tovval();
       break;
      }
     else if (__sv_parse && strcmp(__token, "`__LINE__") == 0)
      {
       /* just make a 32-bit nubmer with the current line number */
       __file_just_op = FALSE;
       __acwrk[0] =  __lin_cnt;
       __bcwrk[0] =  0;
       __toktyp = NUMBER;
       __itokbase = BDEC;
       __itoksized = FALSE;
       __itoksizdflt = FALSE;
       __itok_signed = FALSE;
       __itoklen = WBITS;
       break;
      }
     else if ((syp = __get_sym(__token, __pv_defsyms)) == NULL || !syp->sydecl)
      {
#ifndef __CVC_RT__
       __pv_fwarn(654,
        "text macro %s undefined or possibly compiler directive for other tool - ignored",
        __token);
#endif
       goto vtagain;
      }
     if (!syp->sy_argsmac)
      { 
       chp = syp->el.edfchp;
       /* `define macros can be empty from +define+ command arg */
       if (strcmp(chp, "") == 0) goto vtagain;
       len = -1;  
      } 
     else 
      {
       int32 sav_first_num_eol;

       /* save first tok state, if `xx expands to compiler dir. must be 1st */
       /* 2 stage num eol in get 1 vtok sets first of line */ 
       if (__first_linetok) sav_first_num_eol = TRUE;
       else sav_first_num_eol = FALSE;

       /* expand into malloced storage setting length to len */
       /* this may unget TEOF token */
       chp = expand_arg_macro(syp, &len);
       __first_num_eol = sav_first_num_eol;
       if (chp == NULL) goto vtagain;
      }
     /* if currently reading file, must preserve line count */
     if (__visp->vi_s != NULL) __visp->vilin_cnt = __lin_cnt;
     /* push string on top of read stack */
     __push_vinfil();
     __visp->vichp = __visp->vichp_beg = chp;
     __visp->vichplen = len;
     __in_s = NULL;
     /* DBG remove --- */
     if (__debug_flg)
      __dbg_msg("macro %s value [%s]\n", syp->synam, chp);
     /* --- */
     goto vtagain;
    }
ret_id:
   __file_just_op = FALSE;
   __toktyp = ID;
   break;
  default:
   /* if this is not directive, must indicate not at start of file */
   if (ttyp < CDIR_TOKEN_START || ttyp > CDIR_TOKEN_END)
    __file_just_op = FALSE;
   __toktyp = ttyp;
   break;
  }
 /* SJM 06/22/00 - using 2 state 2 token number - finished by here */ 
 __maybe_2tok_sized_num = FALSE;
 /* DBG remove --
 if (__debug_flg)
  {
   if (__toktyp == ID)
    {
     __dbg_msg("++ line %d returning token %s [%d]\n", __lin_cnt,
      __token, __toktyp);
    }
   else
    {
     __dbg_msg("++ line %d returning token %s [%d]\n", __lin_cnt, __prt_vtok(),
      __toktyp);
    }
  }
 --- */
}

/*
 * routine to read and convert token after `ifdef or `elsif to string 
 * returns 0 if good and continue, 1 if error and skip rest, 2 if erro
 * and read another token (vt again label)
 *
 * SJM 07-27-09 - new routine for `elsif since same reading macro to see
 * if defined
 */
static int32 rd_chk_ifdef_macnam_to_str(char *macro_s, int32 ifdtyp) 
{
 int32 savlin_cnt, ttyp;

 /* see if token `defined */
 savlin_cnt = __lin_cnt;
 strcpy(macro_s, "");
 if ((ttyp = __get1_vtok(__in_s)) != ID)
  {
   /* BEWARE */
   /* must use get vkeynam for compile directive (know only 2 possible) */
   /* because __prt2_vtok uses fixed storage */
   /* SJM 07-27-09 - notice seemingly must get ifdef name into macro_s */
   __pv_ferr(923, "%s not followed by text macro name - %s read",
    __get_vkeynam(macro_s, ifdtyp), __prt2_vtok(ttyp));
   return(1);
  }
 if (*__token == '`')
  {
   __pv_fwarn(570,
    "%s text macro name %s should not begin with ` - dropped",
    __get_vkeynam(__xs, ifdtyp), __token);
   strcpy(macro_s, __token);
   return(1);
  } 
 else
  {
   macro_s[0] = '`';
   strcpy(&(macro_s[1]), __token);
  }
 if (savlin_cnt != __lin_cnt)
  {
   __pv_ferr(921, "%s text macro name must be on same line",
    __get_vkeynam(__xs, ifdtyp));
   unget2_vtok(ttyp);
   /* to get here know moved to next line */
   return(2);
  }
 return(0);
}

/* macro for adding char and growing mac wrk str */
#define addto_macwrkstr_(c) \
 do { \
  int32 osize; \
  if (++len >= __macwrklen - 1) \
   { \
    osize = __macwrklen; \
    __macwrklen += IDLEN; \
    __macwrkstr = __my_realloc(__macwrkstr, osize, __macwrklen); \
    chp = &(__macwrkstr[len - 1]); \
   } \
  *chp++ = (c); \
 } while (0)

/*
 * expand a macro with arguments 
 *
 * collects , (...) list which may have syntax errors into mac work string
 * list cannot cross macro or include but can contain white space
 * build array of args that are malloced using __macwrkstr
 * processing within argument () special char not token scanning  
 * reads ending ) then stops reading 
 *
 * notice sections of text with unmatched ) or , are illegal since
 * in Verilog \ escapes an identifier
 */
static char *expand_arg_macro(struct sy_t *syp, int32 *explen)
{
 int32 c;
 int32 ttyp, par_cnt, setb_cnt, setb_err, last_argno, last_i, len;
 struct amac_t *amacp;
 struct macexp_t *mxp;
 struct macarg_t *macap, *macap2, *maca_hdr, *maca_end, **mactab;
 char *chp, *chp2;

 *explen = -1;
 if ((ttyp = __get1_vtok(__in_s)) != LPAR)
  {
   __pv_ferr(1270, "%s macro argument list ( expected - %s read",
    syp->synam, __prt2_vtok(ttyp));
   unget2_vtok(ttyp);
   return(NULL);
  } 
 /* get each argument first into mac wrk str then alloc */
 /* argument is string before next non nested , or ) */
 macap = maca_end = maca_hdr = NULL;
 for (c = -1, last_argno = 0;; last_argno++)
  {
   setb_err = FALSE;
   par_cnt = setb_cnt = 0;
   for (chp = __macwrkstr, len = 0;;)
    {
     c = my_getc(__in_s);
     switch (c) {   
      case EOF:
eof_err:
       __pv_ferr(1295,
        "%s macro argument no. %d **EOF** read before argument ending , or )",
        syp->synam, last_argno); 
       /* must put back eof */
       my_ungetc_(c, __in_s);
       /* allow memory leak on syntax eof error */ 
       return(NULL);
      case '(': par_cnt++; break;
      case ')': 
       /* if this is extra ) must end - error if in concat */
       if (par_cnt == 0)
        {
         if (setb_cnt > 0)
          __pv_ferr(1296,
          "%s macro argument no. %d list ending ) found but concatenate not ended",
          syp->synam, last_argno); 
         goto arg_end;
        }
       par_cnt--;
       break;
      case '{': setb_cnt++; break;
      case '}': 
       if (setb_cnt == 0 && !setb_err)
        {
         __pv_ferr(1297,
          "%s macro argument no. %d list nested concatenate illegal - too many }s",
          syp->synam, last_argno); 
         setb_err = TRUE;
        }
       else setb_cnt--;
       break;
      case ',': 
       if (par_cnt == 0 && setb_cnt == 0) goto arg_end; 
       break;
      /* copy all chars in quoted string - vgetstr used later to scan */ 
      case '"':
       addto_macwrkstr_(c);
       for (;;) 
        {
         c = my_getc(__in_s);
         /* must not end on escaped " */
         if (c == '\\') { addto_macwrkstr_(c); c = my_getc(__in_s); }  
         else if (c == '"') break;

         if (c == EOF) goto eof_err;  
         /* here collect embedded new line, error later */
         if (c == '\n') { __lin_cnt++; __total_rd_lines++; }
         addto_macwrkstr_(c);
        }
       break;
      /* copy from escape through white space since maybe esc. id */ 
      /* no escaping inside escaped ID */
      case '\\': 
       addto_macwrkstr_(c);
       for (;;) 
        {
         c = my_getc(__in_s);
         if (c == EOF) goto eof_err;
         if (vis_white_(c)) break;
         addto_macwrkstr_(c);
        }
       break;
     }
     if (c == '\n') { __lin_cnt++; __total_rd_lines++; }
     addto_macwrkstr_(c);
    }
arg_end:
   *chp = '\0';
   macap = (struct macarg_t *) __my_malloc(sizeof(struct macarg_t));
   macap->macargnam = __pv_stralloc(__macwrkstr);
   macap->macargnxt = NULL;
   if (maca_end == NULL) maca_hdr = maca_end = macap;
   else maca_end->macargnxt = macap;
   maca_end = macap;
   if (c == ')') break;
  }
 /* convert argument list to table for look up from sym mac exp. tab */
 mactab = (struct macarg_t **)
  __my_malloc((last_argno + 1)*sizeof(struct macarg_t *)); 
 for (last_i = -1, macap = maca_hdr; macap != NULL; macap = macap->macargnxt)
  mactab[++last_i] = macap;
 /* DBG remove */
 if (last_i != last_argno) __misc_terr(__FILE__, __LINE__);
 /* --- */
 amacp = syp->el.eamacp;
 if (last_i + 1 != amacp->num_formal_args)
  { 
   __pv_ferr(1298,
    "%s macro requires %d formal arguments - %d present", syp->synam,
    amacp->num_formal_args, last_i + 1);
   chp2 = NULL;
   goto done;
  }
 /* do the expansion */
 chp = __macwrkstr;
 for (len = 0, mxp = amacp->amxp; mxp != NULL; mxp = mxp->macexpnxt)
  {
   /* copy into chp the leading string */
   for (chp2 = mxp->leading_str; *chp2 != '\0'; chp2++)
    addto_macwrkstr_(*chp2);
   /* copy the actual argument, -1 for none (trailing part) */
   if (mxp->ins_argno != -1)
    {
     for (chp2 = mactab[mxp->ins_argno]->macargnam; *chp2 != '\0'; chp2++)
      addto_macwrkstr_(*chp2);
    } 
  }
 *chp = '\0';
 chp2 = __my_malloc(len + 1);
 strcpy(chp2, __macwrkstr);
 *explen = len;

 /* final step - free actual arg list */
done:
 for (macap = maca_hdr; macap != NULL;)
  {
   macap2 = macap->macargnxt;  
   __my_free(macap->macargnam, strlen(macap->macargnam) + 1); 
   __my_free(macap, sizeof(struct macarg_t));
   macap = macap2;
  }
 maca_hdr = NULL;
 __my_free(mactab, (last_argno + 1)*sizeof(struct macarg_t *)); 
 return(chp2);
}

/*
 * process one `define macro define
 * know `define read and consumes entire line
 * notice macro name must be in symbol table with `
 */
static void process_macdef(void)
{
 int32 ttyp, has_err, savlin_cnt, nargs, c, space_before_lpar;
 char *mactxt_chp, dnam[IDLEN];
 struct macexp_t *mxp;

 if (!__chk_beg_line(CDIR_DEFINE)) return;
 savlin_cnt = __lin_cnt;
 has_err = FALSE;
 if ((ttyp = __get1_vtok(__in_s)) != ID)
  {
   __pv_ferr(922, "`define not followed by text macro identifier - %s read",
    __prt2_vtok(ttyp));
   has_err = TRUE;
  }
 /* need to use get token that does not know about line breaks */
 if (__lin_cnt != savlin_cnt)
  {
   __pv_ferr(929, "`define text macro identifier name must be on same line");
   unget2_vtok(ttyp);
   return;
  }
 if (!has_err && __token[0] == '`')  
  {
   __pv_ferr(1291,
    "`define text macro identifier name %s cannot begin with `", __token);
   has_err = TRUE; 
  }
 if (!has_err) { strcpy(dnam, "`"); strcat(dnam, __token); }
 /* always collect entire line (with possible escaped nl) into mac wrk str */
  
 c = my_getc(__in_s); 
 /* if white space collect will skip anyway - no need to unget */
 if (vis_nonnl_white_(c)) space_before_lpar = TRUE;
 else
  {
   space_before_lpar = FALSE;
   my_ungetc_(c, __in_s);
  }
 __collect_line();

 /* if problem with definition but saw `define return after line read */
 if (has_err) return;

 if (get_vkeywrd(dnam) != ID)
  {
   __pv_ferr(1293,
    "macro name %s conflicts with predefined directive - redefinition illegal",
    dnam);
   return;
  }

 /* if has argument build list and return start of body in mac wrk str */ 
 /* returns nil if error (it emits the message) */
 /* SJM - 01/31/00 - now for arg macros ( must be next char (no intervening white space) */   
 /*                  otherwise ( treated as grouping param */
 if (!space_before_lpar && __macwrkstr[0] == '(')
  { 
   /* build the global formal argument list and skip over it */
   if ((mactxt_chp = bld_macdef_arglist(&nargs)) == NULL) return;

   /* remove all comments macro and replace multiple white space with 1 sp */
   /* also remove trailing white space */
   /* this replaces value in mac wrk str - will always be no longer */
   if ((mactxt_chp = remchk_macdef_coms(mactxt_chp)) == NULL) return;

   /* if expands to empty (could be some white space) make one space */ 
   if ((mxp = bld_mac_expandtab(dnam, mactxt_chp, nargs)) == NULL)
    { strcpy(__macwrkstr, " "); goto do_nonarg; }
   do_argmacdefine(dnam, mxp, nargs);
   if (__debug_flg) dmp_macdef_exptab(dnam, mxp);
  }
 else
  {
do_nonarg:
   /* SJM - 01/31/00 - continue to support old escaped scheme */
   if (__macwrkstr[0] == '\\' && __macwrkstr[1] == '(')
    mactxt_chp = &(__macwrkstr[1]);
   else mactxt_chp = __macwrkstr;
   if ((mactxt_chp = remchk_macdef_coms(mactxt_chp)) == NULL) return;
   __do_macdefine(dnam, mactxt_chp);
   if (__debug_flg) 
    __dbg_msg("+++ text macro %s defined with value [%s]\n", dnam,
     mactxt_chp);
  }
}

/*
 * dump the arg. macro expansion table for debugging
 */
static void dmp_macdef_exptab(char *dnam, struct macexp_t *mxp)
{
 int32 argno;

 __dbg_msg("+++ arg text macro %s defined - expands from:\n", dnam);
 for (argno = 1; mxp != NULL; mxp = mxp->macexpnxt, argno++)
  {
   __dbg_msg("    arg. %d: prefix [%s] insert actual %d\n", 
    argno, mxp->leading_str, mxp->ins_argno);
  }
 __dbg_msg("+++ end of formal args +++\n");
}

/*
 * undefine a macro
 */
static void process_macundef(void)
{
 int32 ttyp, has_err, savlin_cnt;
 struct sy_t *syp;
 char dnam[IDLEN];

 if (!__chk_beg_line(CDIR_UNDEF)) return;
 savlin_cnt = __lin_cnt;
 has_err = FALSE;
 if ((ttyp = __get1_vtok(__in_s)) != ID)
  {
   __pv_ferr(922, "`undef required text macro identifier missing - %s read",
    __prt2_vtok(ttyp));
   has_err = TRUE;
  }
 /* need to use get token that does not know about line breaks */
 if (__lin_cnt != savlin_cnt)
  {
   __pv_ferr(929, "`undef text macro identifier name must be on same line");
   unget2_vtok(ttyp);
   return;
  }
 if (!has_err && __token[0] == '`')  
  {
   __pv_ferr(1291,
    "`undef text macro identifier name %s cannot begin with `", __token);
   has_err = TRUE; 
  }
 if (!has_err) { strcpy(dnam, "`"); strcat(dnam, __token); }
 /* SJM 01-24-12 IFDEF ANYWHERE - need skip since undef on own line */
 __skipover_line();
 if (has_err) return;

 if (get_vkeywrd(dnam) != ID)
  {
   __pv_ferr(1293,
    "`undef of macro name %s illegal - cannot `undef predefined directive",
    dnam);
   return;
  }

 if ((syp = __get_sym(dnam, __pv_defsyms)) == NULL || !syp->sydecl)
  {
   __pv_fwarn(655, "`undef of %s does nothing - macro not defined", dnam);
   return;
  }
 if (syp->sy_argsmac)
  {
   free_macexplst(syp->el.eamacp->amxp);
   __my_free(syp->el.eamacp, sizeof(struct amac_t));
   syp->sy_argsmac = FALSE;
  }
 else __my_free(syp->el.edfchp, strlen(syp->el.edfchp) + 1);
 syp->el.edfchp = __pv_stralloc("");
 syp->sydecl = FALSE;
}

/*
 * return F and emit error if not at beginning of line
 * tricky case if first token file_just_op - this is really first token
 * in line but flag will be off - check for case and if found must turn
 * off file just open - if this check not called will get turned off
 * normally.
 *
 * problem here is caused by Verilog semantics that treat compiler directives
 * as having \n as token but in normal code not a token
 */
extern int32 __chk_beg_line(int32 cdtyp)
{
 /* ---
 if (__iact_state)
  { 
   __ia_err(1401,
    "compiler directives illegal in interactive commands - %s read",
    __get_vkeynam(__xs, cdtyp));
   return(FALSE); 
  }
 --- */
 if (!__first_linetok) 
  {
   if (__file_just_op) { __file_just_op = FALSE; return(TRUE); }
   else __pv_ferr(928, "compiler directive %s must be first token on line",
    __get_vkeynam(__xs, cdtyp));
   return(FALSE);
  }
 return(TRUE);
}

/*
 * collect a line into mac wrk str first skip over all leading white space
 * notice white space inside line kept and line can be arbitrarily long
 * with possible escaped new lines 
 * 
 * this sets length of used part of macro line
 * this can be arbitrarily long for mulitple line macros
 */
extern void __collect_line(void)
{
 int32 c;
 int32 len;
 char *chp;

 for (;;) { c = my_getc(__in_s); if (!vis_nonnl_white_(c)) break; }
 if (c == '\n' || c == EOF)
  {
   *__macwrkstr = '\0';
   my_ungetc_(c, __in_s);
   return;
  } 
 for (chp = __macwrkstr, len = 0;;)
  {
   /* \\n is line continuation and must become ' ' in macro string line */
   /* anything else added is part of escaped id */
   if (c == '\\') 
    {
     if ((c = my_getc(__in_s)) == '\n') { c = ' '; __lin_cnt++; }
     else { my_ungetc_(c, __in_s); c = '\\'; }
    }
   addto_macwrkstr_(c);
   c = my_getc(__in_s);
   if (c == '\n' || c == EOF) { my_ungetc_(c, __in_s); break; }
  }
 /* notice trailing new line or eof removed */
 *chp = '\0';
 __mac_line_len = len;
}

/*
 * skip over characters to a new line (skip ending or error stuff)
 * know current char never new line
 * this also skips over \\[newline]
 *
 * not counted as part of total source lines since skipped from ` conds
 */ 
extern void __skipover_line(void)
{
 int32 c;

 /* DBG remove */
 if (__debug_flg)
  {
   __dbg_msg("++ skipping line %d\n", __lin_cnt);
  }
 /* --- */
 for (;;)
  {
   if ((c = my_getc(__in_s)) == '\n' || c == EOF) break;
   if (c == '\\')
    {
     /* \\n is just white space not end of line but \\EOF is still eof */
     if ((c = my_getc(__in_s)) == EOF) break;
     /* not counting continuation lines in total */
     if (c == '\n') __lin_cnt++;
    }
  }
 if (c != EOF) { my_ungetc_(c, __in_s); };
}

/*
 * build the formal arg list and skip over 
 * passed with mac wrk str pointing to leading ( 
 * returns ptr to one after ending ) or nil if error 
 *
 * FIXME make table larger so can be 8 bit clean 
 */
static char *bld_macdef_arglist(int32 *nargs)
{
 char *chp;
 char *chp2, *chp3;
 int32 argno, arglen, toolong;
 struct macarg_t *marp, *macarg_end;
 char argnam[IDLEN];
 
 *nargs = 0;
 chp = &(__macwrkstr[1]);
 __macarg_hdr = NULL;
 macarg_end = NULL;
 for (argno = 1;; argno++)
  {
   toolong = FALSE;
   /* skip white space before arg */
   while (vis_nonnl_white_(*chp)) chp++;
   /* format argument can start with _ but not ` or $ */
   /* digit can be in id but not start it */
   if (__pv_ctab[(*chp & 0x7f)] != 0 || isdigit(*chp) || *chp == '$')
    {
     __pv_ferr(1292,
      "text macro formal argument %d identifier expected - %c read - if non argument macro, add ' ' before (",
      argno, *chp);
     /* on error just do not define macro */
     return(NULL);
    }
   arglen = 1;
   chp2 = chp++;
   chp3 = NULL;
   /* collect the chars in the formal name */  
   while(__pv_ctab[(*chp & 0x7f)] == 0)
    {
     if (++arglen >= IDLEN - 1)
      {
       if (!toolong)
        {
         __pv_ferr(944, 
          "text macro formal argument has too many characters (%d)",
          IDLEN - 1);
         toolong = TRUE;
         /* end is 1 past end where \0 will go */
         chp3 = chp;
        }
      }
     chp++;
    }
   if (chp3 == NULL) chp3 = chp; 
   strncpy(argnam, chp2, chp3 - chp2);
   argnam[chp3 - chp2] = '\0'; 
   marp = (struct macarg_t *) __my_malloc(sizeof(struct macarg_t));
   marp->macargnam = __pv_stralloc(argnam);
   marp->macargnxt = NULL;
   if (macarg_end == NULL) __macarg_hdr = macarg_end = marp; 
   else macarg_end->macargnxt = marp;
   macarg_end = marp;
   /* maybe skip white space */ 
   while (vis_nonnl_white_(*chp)) chp++;
   if (*chp == ')') break;
   if (*chp == ',') { chp++; continue; } 
   /* wrong separator */
   __pv_ferr(1294,
    "text macro formal argument %d not followed by , or ) - char %c read",
    argno, *chp);
   return(NULL);
  }
 chp++;
 /* notice something like "`define aa(a,b) )()(" is legal, err later */
 *nargs = argno;
 return(chp);
}

/*
 * remove any comments from macro body copy then build macwrkstr
 * error and return F if / * comment or string not completed
 *
 * only here for macro def. bodies, // \[escaped nl] is removed comment
 * / * can span escaped new lines - and always left as escaped in output
 * mchp must always point into mac wrk str
 *
 * this copies into temp and then puts back in macro string
 */
static char *remchk_macdef_coms(char *mchp)
{
 char *chp, *nchp;
 int32 llen, first_time;
 char *newwrkstr, *start_mchp;

 /* macro text starts with non white */
 while(vis_nonnl_white_(*mchp)) mchp++;
 start_mchp = mchp;

 /* region to allocate does not include possible args */
 llen = __mac_line_len - (mchp - __macwrkstr);  
 /* will never be wider but may be same length */
 newwrkstr = __my_malloc(llen + 1);
 
 for (first_time = TRUE, chp = mchp, nchp = newwrkstr; *chp != '\0';)
  {
   /* replace string of white space with one space */
   if (vis_nonnl_white_(*chp))
    {
     if (!first_time) *nchp++ = ' ';
     chp++;
     while(vis_nonnl_white_(*chp)) chp++;
    }
   first_time = FALSE;

   switch (*chp) {
    case '/':
     /* handle comments - no quoted strings in comments */ 
     chp++;
     /* remove // comment - can go to end of area (real nl or esc. nl) */
     if (*chp == '/') 
      { 
       chp++;
       while (*chp != '\0')   
        {
         /* both of these better be removed by collect line */
         if (*chp == '\n' || *chp == EOF) __misc_terr(__FILE__, __LINE__);
         chp++;
        }
       /* now skipped to end of // comment */
       *nchp = '\0';
       goto at_end;
      }
     /* remove / * comment - error if hit end of string */ 
     if (*chp == '*') 
      {
       chp++;
       while (*chp != '*')
        {
         if (*chp == '\n' || *chp == EOF) __misc_terr(__FILE__, __LINE__);
         if (*chp == '\0')
          {
           __pv_ferr(930, 
            "*/ in `define macro line without initial /* comment start");
           __my_free(newwrkstr, llen + 1);
           return(NULL);
          }
         if (*chp == '/' && chp[1] == '*')
          {
#ifndef __CVC_RT__
           __pv_fwarn(622, "nested /* in macro body /* style comment");
#endif
          }
         /* skip any escaped chars - can not end comment */ 
         if (*chp == '\\') { chp++; chp++; }
         chp++;
        }
       chp++;
       if (*chp == '/') { *nchp++ = ' '; chp++; continue; }
       break;
      }
     /* simple / so must keep in line */
     *nchp++ = '/';
     break;
    /* must copy any non white space escape and char */
    case '\\':
     /* escaped nl becomes space */
     if (chp[1] == '\n') { chp++; chp++; *nchp++ = ' '; break; }
     *nchp++ = *chp++;
     if (*chp == '\0')
      {
       __pv_ferr(931,
        "`define macro line ends with \\ - following escaped char required");
       return(NULL);
      }
     /* must copy any escaped char as is - cannot have any meaning */
     *nchp++ = *chp++; 
     break; 
    case '\0': goto at_end; 
    case '"':
     *nchp++ = *chp++;
     while (*chp != '"')
      {
       if (*chp == '\\') *nchp++ = *chp++;
       if (*chp == '\0')
        {
         __pv_ferr(932,
          "`define macro contains unterminated string - not defined"); 
         return(NULL);
        }
       *nchp++ = *chp++;
      }
     /* exit and copy " */     
   }
   *nchp++ = *chp++;
  }
at_end:
 /* remove trailing white space */
 for (;;)
  { 
   if (nchp == newwrkstr) break;
   nchp--; 
   if (!vis_white_(*nchp)) { nchp++; break; }
  }
 *nchp = '\0';

 /* DBG remove --- */ 
 if (nchp - newwrkstr > llen) __misc_terr(__FILE__, __LINE__); 
 /* --- */  
 strcpy(mchp, newwrkstr);
 __mac_line_len = (mchp - __macwrkstr) + (nchp - newwrkstr);
 __my_free(newwrkstr, llen + 1);
 return(start_mchp);
}

/*
 * process an argument macro definition 
 * know mac arg hdr global point to formal argument list
 *
 * know working out of collected line so new line impossible
 * expand arguments anywhere but within strings 
 * know all comments changed to 1 space and multiple white space to 1 space
 * also know all quoted strings completed
 * LOOKATME - is it true this cannot fail
 */
static struct macexp_t *bld_mac_expandtab(char *dnam, char *dval, int32 nargs)
{
 int32 andx;
 byte *argutab;
 struct macarg_t *marp;
 struct macexp_t *mxp, *mxp_hdr, *mxp_end;
 char *chp;
 char *startchp, *startid, idnam[IDLEN];

 argutab = (byte *) __my_malloc(nargs);
 memset(argutab, 0, nargs);
 mxp_hdr = mxp_end = NULL;
 startchp = dval;
 for (chp = dval; *chp != '\0';)
  {
   /* skip leading white space */ 
   while (vis_nonnl_white_(*chp)) chp++; 

   /* always skip quoted strings */
   if (*chp == '"')
    {
     chp++;
     /* must not match escaped quote */
     while (*chp != '"')
      {
       if (*chp == '\0')
        {  
         __pv_ferr(932,
          "macro %s value contains unterminated string - macro undefined",
          dnam); 
         return(NULL);
        }
       if (*chp == '\\') chp++;
       chp++;
      }
     chp++;
     continue;
    }
   /* if identifier or keyword remove and build record, else just skip */ 
   if (__pv_ctab[(*chp & 0x7f)] == 0 && (!isdigit(*chp) || *chp == '`'))
    {
     startid = chp;
     chp++;  
     while(__pv_ctab[(*chp & 0x7f)] == 0) chp++;
     /* see if this is formal argument */
     strncpy(idnam, startid, chp - startid);
     idnam[chp - startid] = '\0';
     /* if does not match left in literal copy part and at next char */
     if ((andx = find_mac_formal_arg(idnam)) == -1) continue;
     argutab[andx] = 1;
     /* this is formal */
     mxp = (struct macexp_t *) __my_malloc(sizeof(struct macexp_t)); 
     mxp->leading_str = __my_malloc(startid - startchp + 1);
     strncpy(mxp->leading_str, startchp, startid - startchp);
     mxp->leading_str[startid - startchp] = '\0';
     mxp->leadlen = startid - startchp;
     mxp->ins_argno = andx;
     mxp->macexpnxt = NULL;
     if (mxp_end == NULL) mxp_hdr = mxp_end = mxp;
     else mxp_end->macexpnxt = mxp;
     mxp_end = mxp;
     /* reset fill to one after ID */ 
     startchp = chp;
     continue;
    }
   chp++;
  }
 for (andx = 0, marp = __macarg_hdr; andx < nargs; andx++,
  marp = marp->macargnxt)
  {
   if (argutab[andx] == 0)
    {
     __pv_fwarn(640,
      "%s macro definition formal argument %s (no. %d) not used in macro body", 
      dnam, marp->macargnam, andx);
    }
  }
 __my_free(argutab, nargs);
 argutab = NULL;

 /* unless value is empty include trailing chars */
 /* if totally empty value, make it one space */ 
 if (chp == startchp && mxp_end == NULL)
  {
   __pv_fwarn(638, "argument macro %s expands to nothing - use `undef", dnam);
   return(NULL);
  }
 if (chp == startchp) return(mxp_hdr); 

 /* add the ending prefix with no argument to expand in */
 mxp = (struct macexp_t *) __my_malloc(sizeof(struct macexp_t)); 
 mxp->leading_str = __my_malloc(chp - startchp + 1);
 strncpy(mxp->leading_str, startchp, chp - startchp);
 mxp->leading_str[chp - startchp] = '\0';
 mxp->ins_argno = -1;
 mxp->macexpnxt = NULL;
 if (mxp_end == NULL) mxp_hdr = mxp_end = mxp;
 else mxp_end->macexpnxt = mxp;
 return(mxp_hdr);
}

/*
 * search an formal argument list to match a legal ID name
 * returns nil if not found
 */
static int32 find_mac_formal_arg(char *argnam)
{
 int32 anum;
 struct macarg_t *marp;

 anum = 0;
 for (marp = __macarg_hdr; marp != NULL; marp = marp->macargnxt, anum++)
  { if (strcmp(marp->macargnam, argnam) == 0) return(anum); }
 return(-1);
}

/*
 * define a text macro named dnam with value dval
 * this looks up in symbol table and stores "" ok and used for `ifdef 
 * dval here is really rest of line that may be ""
 */
extern void __do_macdefine(char *dnam, char *dval)
{
 struct tnode_t *tnp;
 struct sy_t *syp;

 tnp = __vtfind(dnam, __pv_defsyms);
 /* now add the symbol */
 if (__sym_is_new)
  {
   /* allocate symbol and fill symbol */
   __add_sym(dnam, tnp);
   __pv_defsyms->numsyms++;
   syp = tnp->ndp;
   syp->sytyp = SYM_DEF;
   syp->sydecl = TRUE;
  }
 else
  {
   syp = tnp->ndp;
   /* if `define follows undef just define - no message */
   if (syp->sydecl)
    {
     if (syp->sy_argsmac)
      {
       __finform(415,
        "textmacro name %s redefined - previous but not new had args", dnam);
        free_macexplst(syp->el.eamacp->amxp);
       __my_free(syp->el.eamacp, sizeof(struct amac_t));
       syp->sy_argsmac = FALSE;
      }
     else
      {
       __finform(415,
        "textmacro name %s redefined - neither has arguments", dnam);
       __my_free(syp->el.edfchp, strlen(syp->el.edfchp) + 1);
      }
    }
   /* if was undefined now defined */
   syp->sydecl = TRUE;
  }
 syp->el.edfchp = __pv_stralloc(dval);
}

/*
 * free an args macro expand list 
 */
static void free_macexplst(struct macexp_t *mxp)
{
 struct macexp_t *mxp2;

 for (; mxp != NULL;)
  {
   mxp2 = mxp->macexpnxt;
   __my_free(mxp->leading_str, mxp->leadlen + 1);
   __my_free(mxp, sizeof(struct macexp_t));
   mxp = mxp2;
  }
}

/*
 * define a text macro with arguments named dnam with value dval
 * and macro subsitution list macp
 *
 * this looks up in symbol table and stores "" ok and used for `ifdef 
 * dval here is really rest of line that may be ""
 * illegal conflicts with predefined compiler directives caught before here
 */
static void do_argmacdefine(char *dnam, struct macexp_t *mxp, int32 nformal_args)
{
 struct tnode_t *tnp;
 struct sy_t *syp;

 tnp = __vtfind(dnam, __pv_defsyms);
 /* now add the symbol */
 if (__sym_is_new)
  {
   /* allocate symbol and fill symbol */
   __add_sym(dnam, tnp);
   __pv_defsyms->numsyms++;
   syp = tnp->ndp;
   syp->sytyp = SYM_DEF;
   syp->sy_argsmac = TRUE;
   syp->sydecl = TRUE;
   syp->el.eamacp = (struct amac_t *) __my_malloc(sizeof(struct amac_t));
  }
 else
  {
   syp = tnp->ndp;
   if (syp->sydecl)
    {
     if (syp->sy_argsmac)
      {
       __finform(415,
        "textmacro name %s redefined - previous and new have args",
        dnam);
       free_macexplst(syp->el.eamacp->amxp);
      }
     else
      {
       __finform(415,
        "textmacro name %s redefined - only new has args", dnam);
       __my_free(syp->el.edfchp, strlen(syp->el.edfchp) + 1);
       syp->el.eamacp = (struct amac_t *) __my_malloc(sizeof(struct amac_t));
      }
    }
   syp->sydecl = TRUE;
  }
 syp->el.eamacp->amxp = mxp; 
 syp->el.eamacp->num_formal_args = nformal_args;
 syp->sy_argsmac = TRUE;
}

/*
 * return F if remainder of line contains anything but comment
 * know all white space has been removed before call
 * if / * comment but be completed on line
 * return T if good
 */
extern int32 __bqline_emptytail(char *cp)
{
 for (; *cp != '\0'; cp++)
  {
   switch (*cp) {
    case '/':
     cp++;
     if (*cp == '/') return(TRUE);
     if (*cp == '*') 
      {
       /* in / *  comment */ 
       for (cp++;; cp++)
        {
         if (*cp == '\0') return(FALSE);
         if (*cp == '*')
          {
           cp++;
           if (*cp == '/') goto nxt_white;
           cp--;
           continue;
          }
        }
      }
     continue;
    case '\\': cp++; continue;
    default: return(FALSE);
   }
nxt_white:;
  }
 return(TRUE);
}

/*
 * do the new `include directive - entire line consumed
 * must be called with file name (starting ") in token
 *
 * proc just changes file list all token reading must occur in get vtok 
 */
extern void __do_include(void)
{
 int32 idi;
 char *cp;
 int32 inflen, plen, space;
 FILE *f;
 struct incloc_t *ilp;
 char *chp, incfnam[RECLEN], incpth[RECLEN];
 struct sy_t *syp;

 cp = __macwrkstr;
 /* AIV 06/27/05 -  handle the special `include `FILE case */
 if (*cp == '`')
  {
   /* strip the white space at the end of the line */
   plen = strlen(cp) - 1;
   space = FALSE;
   for (idi = plen; idi >= 0; idi--) 
    {
     if (cp[idi] == ' ') 
      {
       space = TRUE;
       cp[idi] = '\0';
      }
     else if (space) break;
    }
    /* find `define variable to ge the file name */
   if ((syp = __get_sym(cp, __pv_defsyms)) == NULL || !syp->sydecl)
    {
     __pv_fwarn(937,
      "`include name - text macro %s undefined or possibly compiler directive for other tool - ignored", cp);
     return;
    }
  /* set the file name pointer */
  cp = syp->el.edfchp;
 }
 chp = cp;
 if (*chp != '"')
  {
bad_fnam:
   __pv_ferr(937,
    "`include name not surrounded by double quotation marks");
   return;
  } 
 /* fill token to ending " - white space in file names ok */
 for (chp++;; chp++)
  { 
   if (*chp == '\0') goto bad_fnam;
   if (*chp == '"') break; 
  } 
 /* replace ending quotes with \0 */
 *chp = '\0';
 /* cp now points file name skipping the first char (") */
 /* know not longer than 1024 because that is Verilog line length */
 strcpy(incfnam, &(cp[1]));

 if ((f = __tilde_fopen(incfnam, "r")) == NULL)
  {
   /* if file absolute, do not search incdir list */
   /* AIV 09/15/04 - ./[name] form is relative not absolute */
   if (incfnam[0] == '/' || incfnam[0] == '~') goto nonrel_notfnd; 

   if (__last_incdir >= 0)
    {
     inflen = strlen(incfnam);
     for (idi = 0; idi <= __last_incdir; idi++) 
      {
       plen = strlen(__incdirs[idi]) + inflen + 1;
       if (plen >= RECLEN)
        {
         chp = __my_malloc(plen);
         strcpy(chp, __incdirs[idi]); 
         strcat(chp, incfnam);
         __pv_fwarn(571,
          "`include file +incdir+ path name %s too long (%d) - ignored", chp,
           RECLEN); 
         __my_free(chp, plen);
         continue;
        }
       strcpy(incpth, __incdirs[idi]);
       strcat(incpth, incfnam); 
       /* DBG remove --
       __cv_msg("*** attempting to open include path %s\n", chp);
       --- */
       if ((f = __tilde_fopen(incpth, "r")) != NULL)
        { strcpy(incfnam, incpth); goto found_path; }
      }
     __pv_ferr(933,
      "unable to open `include file %s - not found in any +incdir+", incfnam);
     return;
    }
nonrel_notfnd:
   __pv_ferr(933, "unable to open `include file %s", incfnam);
   return;
  }

found_path:
 /* add include file to file list for error messages */
 /* __last_inf still used to find last non lib. input file */
 /* this dies if >64k */
 /* idea here is that initial build entire list of input then library files */
 /* while process arguments - when reading includes put on end of file list */
 /* so that contents can be read by debugger */
 if (++__last_lbf >= __siz_in_fils) __grow_infils(__last_lbf);
 __in_fils[__last_lbf] = __pv_stralloc(incfnam);

 /* have good include file, add to include location list */
 ilp = (struct incloc_t *) __my_malloc(sizeof(struct incloc_t));
 /* link on end */
 if (__inclst_hdr == NULL) __inclst_hdr = __inclst_end = ilp;  
 else __inclst_end->inclocnxt = ilp;
 ilp->inc_fnind = __last_lbf;
 ilp->incfrom_fnind = __cur_fnam_ind;
 ilp->incfrom_lcnt = __lin_cnt;
 ilp->inclocnxt = NULL;

 /* save current __lin_cnt before pushing */
 if (__visp->vi_s != NULL) __visp->vilin_cnt = __lin_cnt;
 /* push new file on tos */
 __push_vinfil();
 /* notice push sets __visp */
 __visp->vifnam_ind = __last_lbf;
 __visp->vi_s = __in_s = f;
 __cur_fnam = __in_fils[__visp->vifnam_ind];
 __cur_fnam_ind = __visp->vifnam_ind;
 __lin_cnt = 1;
#ifndef __CVC_RT__
 if (__lib_verbose || __verbose)
  {
   __cv_msg("  Elaborating `included source file \"%s\"\n", __cur_fnam);
  }
#endif
 __file_just_op = TRUE;
}

/*
 * skip to matching level else for `ifdef that is F
 * this reads ending `endif or `else and it line
 * returns -1 on not found error
 *
 * fortuntately never need to back up
 * this has a bug that needs to be documented - in sections that are
 * skipped only looks for match level `else or `endif - once starts skipping
 * a down level `ifdef does not catch extra `else's  
 * notice this routines only uses local variables
 *
 * SJM 01-24-24 - IFDEF ANYWHERE now so no line skipping just token read
 */
static int32 ifdef_skip_section(FILE *f, int32 begtok)
{
 int32 level, ttyp2, sav_lin_cnt, savfnam_ind;

 /* ifdef must be on line by itself - anything treated as comment */
 /* SJM 01-24-24 - IFDEF ANYWHERE */
 // IFDEF ANYWHER __skipover_line();
 /* save the line count */
 savfnam_ind = __cur_fnam_ind;
 sav_lin_cnt = __lin_cnt;
 /* SJM 12/04/00 - need flag when skipping for ifdef section to */
 /* not emit rd num warnings since parameter substitution not right */
 __ifdef_skipping = TRUE;
 /* AIV 07/13/09 - had a bug for new altera_mf.v cannot ifdef/endif */
 /* with a always@(*) - need this flag on to mark as not an attribute */
 __canbe_impl_evctrl = TRUE;
 /* know reading stars after directive line */
 for (level = 0;;)
  {
   switch ((byte) (ttyp2 = __get1_vtok(f))) {
    case TEOF:
     /* proc handle EOF - may need to move file to pop included or next */
     /* SJM 01-24-12 - IFDEF ANYWHERE - this just open include file */
     handle_ifdef_skip_eof(begtok, savfnam_ind, sav_lin_cnt);
     continue;
    case CDIR_IFDEF: case CDIR_IFNDEF: 
     /* notice will not see if not 1st token of line */ 
     // IFDEF ANYWHERE if (__chk_beg_line(ttyp2)) level++;
     // IFDEF ANYWHERE __skipover_line();
     /* SJM 01-24-12 - skipping an `if(n)def, so when see ifdef increase lev */
     level++;
     continue;
    case CDIR_ENDIF:
     // IFDEF ANYWHERE if (!__chk_beg_line(CDIR_ENDIF)) break;
     // IFDEF ANYWHERE __skipover_line();
     /* SJM 12/04/00 - when done skipping now need to turn off flag */
     /* flag needed because macros now allowed for number width */ 
     if (level == 0)
      { 
       /* reset flags */
       __ifdef_skipping = FALSE; 
       __canbe_impl_evctrl = FALSE;
       return(CDIR_ENDIF); 
      }
     level--;
     continue;
    case CDIR_ELSIF:
     // IFDEF ANYWHERE if (!__chk_beg_line(CDIR_ELSIF)) continue;

     /* if separate ifdef is lower level, swallow line and continue */
     /* SJM 07-31-09 - notice elsif does not change nesting level */
     /* SJM 07-19-10 - test for 1 - for elsif, these do not decrement */
     if (level > 0)
      {
       // IFDEF ANYWHERE __skipover_line();
       continue;
      }

     if (begtok == CDIR_ELSE)
      {
       __pv_ferr(1011,
        "`elseif line %s - illegal follows same nesting level `else",
         __bld_lineloc(__xs, (word32) savfnam_ind, sav_lin_cnt));  
      }
     /* skipping now when see top leve eslif - must return - caller then */
     /* may restart skipping - can't eat the line */
     /* AIV 06/01/11 - need to put this flag back to false on return */
     __canbe_impl_evctrl = FALSE;
     return(CDIR_ELSIF);
    case CDIR_ELSE:
     // IFDEF ANYWHERE if (!__chk_beg_line(CDIR_ELSE)) break;
     // IFDEF ANYWHERE __skipover_line();
     if (level == 0)
      {
       if (begtok == CDIR_ELSE)
        {
         __pv_ferr(1011,
          "`else line %s - followed by same nesting level `else",
          __bld_lineloc(__xs, (word32) savfnam_ind, sav_lin_cnt));  
         /* keep looking for `endif */
         continue;
        }
       __ifdef_skipping = FALSE;
       /* reset flag */
       __canbe_impl_evctrl = FALSE;
       return(CDIR_ELSE);
      }
     continue;
    case CDIR_TIMESCALE:
     /* SJM 12/02/99 - these require special scanning so can't just skip */
     /* must read line and ignore it - know always first on line */
     /* SJM 01-24-12 - IFDEF ANYWHERE timescale must be on own line */
     __skipover_line();
     continue; 
   }
  }
 /*UNREACHABLE*/
 __canbe_impl_evctrl = FALSE;
 __ifdef_skipping = FALSE;
 return(-1);
}

/*
 * routine to handle EOF when skipping ifdef section 
 *
 * routine used by if(n)def false, elsif false, or else when if true to deal
 * with eof - mostly needs to determine if need to move to another file
 *
 * SJM 07-31-09 - new routine since with elsif need different skip routines
 */  
static void handle_ifdef_skip_eof(int32 begtok, int32 savfnam_ind,
 int32 sav_lin_cnt)
{
 /* if finished include or macro expansion just continue reading tokens */
 if (__pop_vifstk()) return;

 /* next try to replace just finished 0th element with new input file */
 /* notice these can cross file boundaries - real eof is all files */
 /* exhausted */
 if (__cur_infi < __last_inf)
  {
   __cur_infi++;
   if (__open_sfil()) return;
  }
 /* for interactive can never get here since checking line begin fails */
 /* notice control here always ends with fata error */
 if (begtok == CDIR_IFDEF || begtok == CDIR_IFNDEF || begtok == CDIR_ELSIF)
  {
   __pv_terr(313,
    "`ifdef/`ifndef line %s - no matching `else, `elsif or `endif before **EOF**",
    __bld_lineloc(__xs, (word32) savfnam_ind, sav_lin_cnt));  
  }
 else
  {
   __pv_terr(313, "`else line %s - no matching `endif before **EOF**",
    __bld_lineloc(__xs, (word32) savfnam_ind, sav_lin_cnt));  
  }
}

/*
 * INTERACTIVE ENVIRONMENT GET TOKEN ROUTINES
 */

/*
 * read an interactive line - must handle \[new line] escapes which
 * are left in and treated as white space
 *
 * __iahwrkline grows but must start out at least IDLEN + 1 characters lone
 * this returns TEOF on at eof and nothing in line (or error?)
 * return TOK_NONE on good
 *
 * caller must handle key file and parsing tokenization of read line
 * (command) and any adding to history list
 * ending new line is removed
 */
extern int32 __rd_ialine(void)
{
 int32 len, totlen, intr_num;
 size_t osize;
 char *chp;
 FILE *f;

rd_again:
 __iahwrkline[0] = '\0';
 if (__cmd_s != NULL) { f = __cmd_s; __lin_cnt++; } else f = stdin;
 if (feof(f)) return(TEOF);

 for (totlen = 0;;)
  {
   /* will not return NULL if any chars read */
   chp = &(__iahwrkline[totlen]);
   /* when iact debugger run from pipe, under FlexLM may be interrupted */
   /* and need to restart */
   intr_num = 0;
again2:  
   clearerr(f);
   if (fgets(chp, IDLEN + 1, f) == NULL)
    {
     if (++intr_num >= 512)
      {
       __ia_err(1450,
        "interactive input call interrupted %d consecutive times - assuming EOF",
        intr_num); 
       break;
      }
     if (!feof(f) && errno == EINTR) goto again2;
     if (feof(f) && errno == EINTR)
      {
       __ia_warn(1603,
        "interactive input call interrupted (but EOF also seen?) - trying again");
       goto again2;
      }
     if (ferror(f))
      {
       __ia_err(1460,
        "interactive input call failed because: [%s] - assuming EOF", 
        strerror(errno));
      }
     break;
    }
   if (__pending_enter_iact && __iact_reason == IAER_CTRLC)
    {
     __pending_enter_iact = FALSE;
     __iact_reason = IAER_UNKN;
     
     if (__cmd_s == NULL) goto rd_again; 
     /* ^c (interrupt signal) during $input interrupts and closes file */
     __ia_err(1457,
      "interactive $input file processing terminated by interrupt (^c)");
     totlen = 0;
     __iahwrkline[0] = '\0';
     return(TEOF);
    }

   len = strlen(chp);
   if (len >= IDLEN) 
    {
     __ia_err(1402, "interactive line too long (%d) - truncated", IDLEN - 1);
     chp[IDLEN - 1] = '\0';  
     break;
    }
   totlen += len;
   /* know last char. always new line for fgets  - see if escaped */
   if (chp[len - 2] != '\\') break;
   /* if escaped keep reading but first see if need to grow work line */
   if (totlen >= __iahwrklen - IDLEN - 4)  
    {
     osize = __iahwrklen;
     __iahwrklen += IDLEN + 4;
     __iahwrkline = __my_realloc(__iahwrkline, osize, __iahwrklen);
    }
   /* if (f != NULL) __lin_cnt++; */
  }
 if (totlen == 0) return(TEOF);
 /* FIXME - lot file output only ?? */
 if (__echo_iactcmds_tolog && __log_s != NULL)
  __my_fprintf(__log_s, "%s", __iahwrkline);

 /* final step change final unescaped new line to blank */ 
 /* if not blank error such as omitted ; previous token not seen */
 __iahwrkline[totlen - 1] = ' '; 
 return(TOK_NONE);
} 

/*
 * ACTUAL TOKENIZATION CODE
 */

/*
 * ascii character table for processing end of ID tokens
 * 0: continue - legal ID char (letter, digit, _, $)
 * 1: end and don't back up (white space)
 * 2: end and back up (operators plus special back quote)
 * 3: inc lin_cnt and end - only new line
 * 4: illegal ID char
 *
 * notice special handling of . - if 1st char after comma or white space,
 * then dot part of .[name](port) for else . legal in ID, but can not
 * be 1st char of id
 * 0x24 is $ and 0x5f is _ both are legal starting and in IDs (value 0)
 */
char const __pv_ctab[128] = {
 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 3, 4, 1, 1, 4, 4, /* ^i,\n,\f,\r */
 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
 /* need to handle " */
 1, 2, 2, 2, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, /* sp,!,%,#,(,),*,',+,-,.,/ */
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, /* digits, :,;,<,=,>,? */
 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /* @, cap letters */
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 0, /* letters `,[,\\,],^, */
 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /* `, letters */
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2  /* letters, {, |, },~,EOF */
};

/*
 * DBG wrapper for dbg of get1_votk
 */
/* DBG remove ====================
extern int32 __get1_vtok(FILE *f)
{
 int32 ttyp;
 extern int32 __dbg_get1_vtok(FILE *);
 
 ttyp = __dbg_get1_vtok(f);
 -* DBG remove *-
 if (__debug_flg)
  {
   __dbg_msg("[TOKEN: %s(%d) line %d]\n", __token, ttyp, __lin_cnt); 
  }
 -* --- *-
 return(ttyp);
}
======= */

/*
 * get a Verilog token
 * (modified from yylex in "The Unix Programming Environment" p. 337)
 */
extern int32 __get1_vtok(FILE *f)
{
 int32 c, ctval;
 int32 c1, len, toolong;
 int32 t1typ;
 char *cp;

again:
 /* not first line token since always push back new line except number */
 /* ending line required scan to make sure not ' */
 if (__first_num_eol) { __first_linetok = TRUE; __first_num_eol = FALSE; }
 else __first_linetok = FALSE;

again3:
 do { ctval = __pv_ctab[(c = my_getc(f)) & 0x7f]; } while (ctval == 1);
 if (c == '\n')
  {
again2:
   __lin_cnt++;
   __total_rd_lines++;
   do { ctval = __pv_ctab[(c = my_getc(f)) & 0x7f]; } while (ctval == 1);
   if (c == '\n') goto again2; 
   __first_linetok = TRUE;
  }
 switch (c) {
  case ';': return(SEMI);
  case ',': return(COMMA);
  case ':': return(COLON);
  case '#': return(SHARP);
  case '(':
   if ((c1 = my_getc(f)) != '*') { my_ungetc_(c1, f); return(LPAR); }

   /* SJM 06/01/04 - for new @(*) form can't be attr - need to check */
   /* spaces possible because something like @(`star ) is possible */
   if (__canbe_impl_evctrl) { my_ungetc_(c1, f); return(LPAR); }

   /* collect attribute into global string */
   rd_attribute(f);
   goto again;
  case ')': return(RPAR);
  case '[': return(LSB);
  case ']': return(RSB);
  case '{': return(LCB);
  case '}': return(RCB);
  /* notice dot can not start real number in Verilog - digit or sign only */
  case '.': return(DOT);
  case '?': return(QUEST);
  case '@': return(AT);
  case '=':
   if ((c1 = my_getc(f)) != '=')
    {
     if (c1 == '>') return(PPTHCON);
     my_ungetc_(c1, f);
     return(EQ);
    }
   if ((c1 = my_getc(f)) != '=') { my_ungetc_(c1, f); return(RELEQ); }
   return(RELCEQ);
  case '\'':
   return(rd_num(f, c));
  case '+': 
   if ((c1 = my_getc(f)) != ':') 
    { 
     /* AIV 09/24/10 - if SV parse ++ */
     /* AIV 09/30/10 - if SV parse += */
     if (__sv_parse)
      {
       if (c1 == '+') return(INC);
       if (c1 == '=') return(PLUS_EQ);
      }
     my_ungetc_(c1, f); 
     return(PLUS); 
    }
   return(PARTSEL_NDX_PLUS);
  case '-':
   c1 = my_getc(f);
   if (c1 == '>') return(CAUSE);
   else if (c1 == ':') return(PARTSEL_NDX_MINUS);
   /* AIV 09/24/10 - if SV parse -- */
   /* AIV 09/30/10 - if SV parse -= */
   else if (__sv_parse) 
    {
     if (c1 == '-') return(DEC);
     if (c1 == '=') return(MINUS_EQ);
    }
   my_ungetc_(c1, f); 
   return(MINUS); 
  case '0': case '1': case '2': case '3': case '4': case '5':
  case '6': case '7': case '8': case '9':
   return(rd_num(f, c));
  case '*':
   c1 = my_getc(f);
   if (c1 == '>') return(FPTHCON);
   else if (c1 == '*') return(POWER);
   /* AIV 09/30/10 - if SV parse *= */
   else if (__sv_parse && c1 == '=') return(TIMES_EQ);
   else { my_ungetc_(c1, f); return(TIMES); }
  /* notice no C assignment op operators */
  case '/':
   if ((t1typ = rd_comment(f)) == UNDEF) goto again;
   if (t1typ == TEOF) return(TEOF);
   if (__sv_parse) 
    {
     c1 = my_getc(f);
     /* AIV 09/30/10 - if SV parse /= */
     if (c1 == '=') return(DIV_EQ);
     my_ungetc_(c1, f); 
    }
   return(DIV);
  case '%': 
   /* AIV 09/30/10 - if SV parse /= */
   if (__sv_parse) 
    {
     c1 = my_getc(f);
     if (c1 == '=') return(MOD_EQ);
     my_ungetc_(c1, f); 
    }
   return(MOD);
  case '~':
   /* notice ~& and ~| parse as 2 that must be unaries */
   /* a ~| b is meaningless - since ~ is unary only */
   /* but ~^ is alternative form of xnor (^~) */
   if ((c1 = my_getc(f)) == '^') return(REDXNOR);
   my_ungetc_(c1, f);
   return(BITNOT);
  case '&':
   /* AIV 09/30/10 - if SV parse &= */
   if (__sv_parse) 
    {
     c1 = my_getc(f);
     if (c1 == '=') return(AND_EQ);
     my_ungetc_(c1, f); 
    }
   if ((c1 = my_getc(f)) != '&') { my_ungetc_(c1, f); return(BITREDAND); }
   if ((c1 = my_getc(f)) != '&') { my_ungetc_(c1, f); return(BOOLAND); }
   return(TCHKEVAND);
  case '|':
   /* AIV 09/30/10 - if SV parse |= */
   if (__sv_parse) 
    {
     c1 = my_getc(f);
     if (c1 == '=') return(OR_EQ);
     my_ungetc_(c1, f); 
    }
   if ((c1 = my_getc(f)) != '|') { my_ungetc_(c1, f); return(BITREDOR); }
   return(BOOLOR);
  /* also ^~ 2 unaries or bitwise xor of unary bit wise not */
  case '^':
   if (__sv_parse) 
    {
     c1 = my_getc(f);
     if (c1 == '=') return(XOR_EQ);
     my_ungetc_(c1, f); 
    }
   /* notice ^~ is not bit wise xor of bit wise negated unary result */
   /* but special built in operator */
   if ((c1 = my_getc(f)) == '~') return(REDXNOR);
   my_ungetc_(c1, f);
   return(BITREDXOR);
  case '!':
   if ((c1 = my_getc(f)) != '=') { my_ungetc_(c1, f); return(NOT); }
   if ((c1 = my_getc(f)) != '=') { my_ungetc_(c1, f); return(RELNEQ); }
   return(RELCNEQ);
  case '>':
   if ((c1 = my_getc(f)) == '=') return(RELGE);
   else if (c1 == '>')
    {
     /* SJM 10/01/03 - add >>> arithmetic right shift */
     if ((c1 = my_getc(f)) == '>') 
      {
       /* AIV 09/30/10 - if SV parse >>>= */
       if (__sv_parse) 
        {
         c1 = my_getc(f);
         if (c1 == '=') return(ASHIFTR_EQ);
         my_ungetc_(c1, f); 
        }
       return(ASHIFTR);
      }
     /* AIV 09/30/10 - if SV parse <<= */
     if (__sv_parse) 
      {
       if (c1 == '=') return(SHIFTR_EQ);
      }
     my_ungetc_(c1, f);
     return(SHIFTR);
    }
   my_ungetc_(c1, f);
   return(RELGT);
  case '<':
   if ((c1 = my_getc(f)) == '=') return(RELLE);
   else if (c1 == '<')
    {
     /* SJM 10/01/03 - add <<< arithmetic left shift */
     if ((c1 = my_getc(f)) == '<') 
      {
       /* AIV 09/30/10 - if SV parse <<<= */
       if (__sv_parse) 
        {
         c1 = my_getc(f);
         if (c1 == '=') return(ASHIFTL_EQ);
         my_ungetc_(c1, f); 
        }
       return(ASHIFTL);
      }
     /* AIV 09/30/10 - if SV parse <<= */
     if (__sv_parse) 
      {
       if (c1 == '=') return(SHIFTL_EQ);
      }
     my_ungetc_(c1, f);
     return(SHIFTL);
    }
   my_ungetc_(c1, f);
   return(RELLT);
  case '\\':
   /* escaped new line is white space and inc line counter */
   /* removed from macro bodies */
   if ((c1 = my_getc(f)) == '\n')
    { __lin_cnt++; __total_rd_lines++; goto again3; } 
   else { my_ungetc_(c1, f); }

   /* handle escaped ID */
   for (toolong = FALSE, len = 0, cp = __token;;)
    {
     /* should never happen since max. line is same as IDLEN */
     if (++len >= IDCHARS - 1)
      {
       if (!toolong)
        {
         __pv_ferr(942,
          "Verilog escaped identifier too many characters (%d)", IDCHARS - 2);
          toolong = TRUE;
        }
      }
     else *cp++ = c;

     if ((c = my_getc(f)) == EOF) return(TEOF);
     /* 3 is new line, 1 end and don't back up (white space) */
     if ((ctval = __pv_ctab[c & 0x7f]) == 3) { my_ungetc_(c, f); break; }
     if (ctval == 1) break;
    }
   /* lrm says trailing white space not part of escaped ID */
   /* but must store space at end or name will not be output right */
   *cp++ = ' '; 
   *cp = '\0';
   /* according to P1364 must store escaped that is legal as non escaped */ 
   /* but can not escape keyword */
   if (!try_chg_tononesc()) return(UNDEF);
   return(ID);
  case '"': return(vgetstr(f));
  case EOF: return(TEOF);
 }
 /* here know digits eliminated so only letters, $, and _ have ct val 0 */
 if (ctval != 0 && c != '`')
  {
   __pv_ferr(943, "identifier starts with illegal char '%c' (%x)", c & 0xff,
    c & 0xff);
   goto again;
  }
 /* try to recognize some kind of id - only */
 for (toolong = FALSE, cp = __token, len = 0;;)
  {
   if (++len >= IDCHARS)
    {
     if (!toolong)
      {
       __pv_ferr(944, 
        "Verilog identifier has too many characters (%d)", IDCHARS - 1);
       toolong = TRUE;
      }
    }
   else *cp++ = c;

   c = my_getc(f);
   if (__pv_ctab[c & 0x7f] == 0) continue;

   /* must not process \n (3) until next time through */
   /* or lin_cnt wrong for errors */
   /* punctuation token end - unget it */
   /* must always put back char after token since even if white space */
   /* a .b .c is not xmr - even though think lrm says it is */
   /* unget causes any error to be caught later */
   my_ungetc_(c, f);
   goto end_id;
  }
end_id:
 *cp = '\0';
 /* only keywords ($ system tasks are not keywords) can be in keyword table */
 t1typ = get_vkeywrd(__token);
 return(t1typ);
}

/*
 * get character routine that can read from macro
 */
static int32 my_getc(FILE *f)
{
 int32 c;

again:
 if (f == NULL)
  {
   c = *__visp->vichp;
   /* for get ch from line form, must never move past \0 */
   if (c == '\0') return(EOF);
   (__visp->vichp)++;
  }
 else c = getc(f);

 if ((__pv_ctab[c & 0x7f] == 4 || c > 127) && !__rding_comment && c != EOF)
  {
   __finform(416, "illegal non printable character (%x) ignored", c & 0xff);
   goto again;
  }
 return(c);
}

/*
 * get a comment
 */
static int32 rd_comment(FILE *f)
{
 int32 c;
 int32 c2;

 /* // to EOL comment */
 if ((c2 = my_getc(f)) == '/')
  {
   __rding_comment = TRUE;
   while ((c = my_getc(f)) != '\n') if (c == EOF) return(TEOF);
   __rding_comment = FALSE;
   my_ungetc_(c, f);
   return(UNDEF);
  }
 /* slash-star comments don't nest */
 if (c2 == '*')
  {
more_comment:
   __rding_comment = TRUE;
   while ((c = my_getc(f)) != '*')
    {
     /* error if / * comments nested */
     if (c == '/')
      {
       if ((c2 = my_getc(f)) == '*')
        {
#ifndef __CVC_RT__
         __pv_fwarn(622, "nested /* in /* style comment");
#endif
         continue;
        }
       c = c2;
      }
     if (c == EOF)
      {
       if (__iact_state)
        __pv_ferr(960,
        "interactive /* comment cannot extend across multiple lines - */ added");
       __rding_comment = FALSE;
       return(TEOF);
      }
     if (c == '\n') { __lin_cnt++; __total_rd_lines++; } 
    }
got_star:
   if ((c = my_getc(f)) == '/')
    {
     __rding_comment = FALSE;
     return(UNDEF);
    }
   if (c == '*') goto got_star;
   if (c == '\n') { __lin_cnt++; __total_rd_lines++; } 
   goto more_comment;
  }
 /* not a comment so treat as name token */
 /* notice c2 here must be most recent because above if never falls through */
 my_ungetc_(c2, f);
 return(DIV);
}

/* macro for adding char and growing attr wrk str */
#define addto_attrwrkstr_(c) \
 do { \
  int32 osize; \
  if (++len >= __attrwrklen - 1) \
   { \
    osize = __attrwrklen; \
    __attrwrklen += IDLEN; \
    __attrwrkstr = __my_realloc(__attrwrkstr, osize, __attrwrklen); \
    chp = &(__attrwrkstr[len - 1]); \
   } \
  *chp++ = (c); \
 } while (0)

/*
 * read an attribute char by char into a saved line
 *
 * know (* read and reading ending ) of *) 
 * collected into attr wrk str - parsed later
 *
 * error if comments in attribute section
 * since parsed in separate parser subroutine `ifdefs must be self contained
 *
 * LOOKATME - adding ; at end - not clear from grammar if required
 *            assuming not for now
 */
static void rd_attribute(FILE *f)
{
 char *chp;
 int32 c, c2, len, wrk_fnam_ind, wrk_lin_cnt;

 wrk_fnam_ind = __cur_fnam_ind;
 wrk_lin_cnt = __lin_cnt;

 for (chp = __attrwrkstr, len = 0;;)
  {
   c = my_getc(f);
   if (c == EOF)
    {
hit_eof:
     my_ungetc_(c, f);
     __pv_ferr(940, "end of file read inside attribute_instance (* ... *)");
     return; 
    }
   switch (c) { 
    case '\\': 
     /* escaped can't end or comment */ 
     addto_attrwrkstr_(c);
     c = my_getc(__in_s);
     if (c == EOF) goto hit_eof;
     if (c == '\n') { __lin_cnt++; __total_rd_lines++; }
     addto_attrwrkstr_(c);
     continue;
    case '"':
     /* collect string to un-escaped " */
     addto_attrwrkstr_(c);
     for (;;)
      {
       if ((c = my_getc(f)) == EOF) goto hit_eof;
       if (c == '\\')
        {
         /* always also both escape and char after */
         addto_attrwrkstr_(c);
         c = my_getc(__in_s);
         if (c == EOF) goto hit_eof;
         if (c == '\n') { __lin_cnt++; __total_rd_lines++; }
         addto_attrwrkstr_(c);
         continue;
        }
       if (c == '"') { addto_attrwrkstr_(c); break; }
       if (c == '\n') { __lin_cnt++; __total_rd_lines++; }
       if (c == '\n' || c == '\r')
        {
         __pv_ferr(945,
          "string inside attribute_instance (* .. *) can not cross line boundary - must escape new line");
         if ((c = skipto_attr_end(f)) == EOF) goto hit_eof;
         return;
        }
       /* non speical char in string , just collect */ 
       addto_attrwrkstr_(c);
      }
     continue;
    case '/': 
     addto_attrwrkstr_(c);
     c = my_getc(f);
     if (c == '/' || c == '*')
      {
       __pv_ferr(3402,
        "/%c comment inside attribute_instance (* ... *) illegal - must be moved outside", c);
       if ((c = skipto_attr_end(f)) == EOF) goto hit_eof;
       return;
      }
     my_ungetc_(c, f);
     continue;
    case '(':
     /* know starting (* read before proc called, this is ( inside */
     addto_attrwrkstr_(c);
     c = my_getc(f);
     if (c == '*')
      {
       __pv_ferr(3403,
        "atttribute start sequence (* illegal inside attribute_instance");
      }
     /* still include it */
     my_ungetc_(c, f);
     continue;
    case '*':
     /* do not include leading (* or ending *) */  
     c2 = my_getc(f);
     if (c2 == ')') goto done; 
     addto_attrwrkstr_(c);
     my_ungetc_(c2, f);
     continue;
    default:
     addto_attrwrkstr_(c);
   }
  }
done:
 /* LOOKATME is semi required? */
 chp--;
 if (*chp != ';')
  {
   chp++;
   addto_attrwrkstr_(';');
  }
 else chp++;
 *chp = '\0'; 

 /* length does not include added \0 */
 __attr_line_len = len;
 
 if (__attr_prefix)
  {
   __finform(3015,
    "more than one attribute_instance in row - using last at %s instead of previous at %s",
    __bld_lineloc(__xs, (word32) wrk_fnam_ind, wrk_lin_cnt),
    __bld_lineloc(__xs2, (word32) __attr_fnam_ind, __attr_lin_cnt));
  }
 __attr_fnam_ind = wrk_fnam_ind;
 __attr_lin_cnt = wrk_lin_cnt;
 __attr_prefix = TRUE;
 /* DBG remove -- */
 if (__debug_flg)
  {
   __dbg_msg("&&& at %s attribute_instance string [%s])\n",
    __bld_lineloc(__xs, (word32) __attr_fnam_ind, __attr_lin_cnt),
    __attrwrkstr);
  }
 /* --- */
}

/*
 * skip to attribute ending *)
 */
static int32 skipto_attr_end(FILE *f) 
{
 int32 c;

 __attr_fnam_ind = 0;
 __attr_lin_cnt = 0;
 for (;;)
  {
   if ((c = my_getc(f)) == EOF) return(EOF);
   switch (c) {
    case '\\':
     if ((c = my_getc(f)) == EOF) return(EOF);
     continue;
    case '"':
     for (;;)
      {
       if ((c = my_getc(f)) == EOF) return(EOF);
       if (c == '\\')
        {
         if ((c = my_getc(f)) == EOF) return(EOF);
         continue;
        }
       if (c == '"') break;
      }
     continue;
    case '*':
     c = my_getc(f); 
     if (c == ')') goto done;
   } 
   /* non special keep reading */
  }
done:
 return(c); 
}

/*
 * read a string token - Verilog string are wide numbers
 * notice %% must be left here as 2 characters - processed by display
 * also value collected in token is not a 0 terminated c string (no \0) 
 */
static int32 vgetstr(FILE *f)
{
 char *cp;
 int32 c, c1, len, toolong, nsize;

 /* return string - should save length - Ver. strings not \0 terminated */
 if ((c = my_getc(f)) == '"')
  {
   /* "" is special case of 8 bit 0 */
   *__strtoken = '\0';
   len = 1;
   goto done;
  }
 for (toolong = FALSE, len = 0, cp = __strtoken;;)
  {
   switch (c) { 
    case '\n': case '\r':
     __pv_ferr(945,
      "string cannot cross line boundary (new line must be escaped)");
     goto done;
    case '\\':
     c1 = my_getc(f);
     switch (c1) {
      case 't': c = '\t'; break;
      case 'n': c = '\n'; break;
      case '\\': c = '\\'; break;
      case '"': c = '"'; break;
      case '0': case '1': case '2': case '3': case '4': case '5':
      case '6': case '7':
       /* c is escaped char value (octal) */
       c = c1 - '0';
       /* this always reads one past and puts back - read always pushed back */
       c1 = my_getc(f);
       if (isdigit(c1) && c1 != '8' && c1 != '9')
        {
         c = (c << 3) + c1 - '0';
         c1 = my_getc(f);
         if (isdigit(c1) && c1 != '8' && c1 != '9') c = (c << 3) + c1 - '0';
         else my_ungetc_(c1, f);
        }
       else my_ungetc_(c1, f);
       break;
      default:
       /* skip escape and use next char as is */
       __pv_fwarn(555, "string \\ escaped character '%c' (%x) same as '%c'",
        c1 & 0x7f, c1 & 0x7f, c1 & 0x7f);
       c = c1;
     }
     break;
    case '"': goto done;
   }
   /* should never happen since max. line is same as IDLEN - nd " room */
   /* SJM 03/20/00 - now allow up to 1M length strings */
   if (++len >= __strtok_wid)
    {
     if (len >= MAXNUMBITS) 
      {
       if (!toolong)
        {
         __pv_ferr(946, "string token has too many characters (%d)",
   MAXNUMBITS - 1);
         toolong = TRUE;
       }
      }
     else
      {
       /* LOOKATME - SJM 03/20/00 - doubling may be too fast growth */
       /* AIV 04/20/06 - was incorrectly using num should be str */
       nsize = 2*__strtok_wid;
       __strtoken = __my_realloc(__strtoken, __strtok_wid, nsize);
       __strtok_wid = nsize;
       /* AIV 04/20/06 - need to reset chp pointer due to realloc */ 
       cp = &(__strtoken[len - 1]); 
       *cp++ = c;
      }
    }
   else *cp++ = c;

   if ((c = my_getc(f)) == EOF)
    {
     if (__iact_state)
      __pv_ferr(947, "interactive string terminator missing");
     else __pv_ferr(947, "end of file read inside string");
     strcpy(__strtoken, "");
     len = 1;
     goto done;
    }
   /* if (__debug_flg) __dbg_msg("&&& vgetstr read %c (%x)\n", c , c); */
  }

done:
 /* except for expr. node string bit - this is now normal val. bit pattern */
 /* assuming 8 bit bytes - on serious error len can be 0 */
 if ((__itoklen = 8*len) == 0) __itoklen = 1;
 /* string are actually sized token - must work in concatenates */
 __itoksized = TRUE;
 /* puts string into ac wrk and bc wrk - may adjust size */
 str_tovval();
 /* if (__debug_flg) __dbg_msg("&&& vgstrread [%s]\n", __strtoken); */
 /* notice even though converted to value - can print input from __token */
 return(LITSTR);
}

/*
 * need to convert form escaped ID to normal if escaped (after \\ is legal)
 * notice although '$' is a class 0 and can go in IDs, it can not start ID
 */
static int32 try_chg_tononesc(void) 
{
 char *chp;
 int32 len, ctval;
 char s1[IDLEN];

 chp = __token;
 /* move past escape */
 chp++;  
 for (len = 0; *chp != '\0'; chp++)
  {
   if ((ctval = __pv_ctab[*chp & 0x7f]) != 0)
    {
     if (ctval == 1 || ctval == 3)
      {
       /* if next is end of ID \0, then found legal non escaped */
       if (chp[1] == '\0')
        {
         if (strcmp(__token, "\\ ") == 0)
          {
           __pv_ferr(942,
     "Verilog escaped identifier empty - at least one non white space character required");
           return(FALSE);
          }

         strcpy(s1, &(__token[1])); 
         /* remove the ending white space char */
         s1[len] = '\0';  
         strcpy(__token, s1);
         return(TRUE);
        }
      }  
     return(TRUE);
    }
   /* first is one after escape this is present at entry */
   /* SJM - 05/26/99 - fixed bug where \222 were getting un-escaped */
   if (len == 0)
    {
     if (*chp == '$' || isdigit(*chp)) return(TRUE);
     /* SJM-09/18/00- FIXME must not unescape or - need to handle as keywrd */
     if (strcmp(chp, "or ") == 0) return(TRUE);
    }
   len++;
  }
 return(TRUE);
}

/*
 * convert ascii user input string into ac wrk and bc wrk 
 *
 * notice __ac wrk and __bc wrk not necessarily contiguous
 */
static void str_tovval(void)
{
 int32 wlen;

 wlen = wlen_(__itoklen);
 if (wlen > __abwrkwlen || (__abwrkwlen > DFLTIOWORDS && wlen <= DFLTIOWORDS))
  chg_abwrklen(wlen);
 zero_allbits_(__bcwrk, __itoklen);
 __vstr_to_vval(__acwrk, __strtoken, __itoklen);
}

/*
 * convert Verilog literal style string to a Verilog numeric value
 * notice Verilog has built in 8 bit chars
 * know ap wide enough and all bits zeroed before called here
 * notice this has built in dependency on 32 bit words  
 */
extern void __vstr_to_vval(word32 *ap, char *s, int32 bitlen)
{
 int32 i;
 int32 bi;
 int32 slen;

 slen = bitlen/8;
 /* fill val from low char (right str) to high char (const left to right) */
 for (i = slen - 1, bi = 0; i >= 0; i--)
  {
   if (bi == 0) *ap = (word32) s[i];
   else *ap |= (((word32) s[i]) << bi);
#ifdef __CVC32__
   if (bi == 24) { bi = 0; ap++; } else bi += 8;
#else
   if (bi == 56) { bi = 0; ap++; } else bi += 8;
#endif
  }
}

/*
 * convert c style string to Verilog value
 * this pushes new v value onto stack
 */
extern struct xstk_t *__cstr_to_vval(char *s)
{
 int32 blen, slen;
 struct xstk_t *xsp;

 slen = strlen(s);
 blen = 8*slen;
 push_xstk_(xsp, blen);
 zero_allbits_(xsp->ap, blen);
 zero_allbits_(xsp->bp, blen);
 __vstr_to_vval(xsp->ap, s, blen);
 return(xsp);
} 

/*
 * push back for internal use by unget routines where get1_vtok value
 * must be pushed back
 */
static void unget2_vtok(int32 ttyp)
{
 int32 save_ttyp;

 save_ttyp = __toktyp;
 __toktyp = ttyp;
 __unget_vtok();
 __toktyp = save_ttyp;
}

/*
 * push back an already read token operator or keyword token
 */
extern void __unget_vtok(void)
{
 __lasttoktyp = __toktyp;
 strcpy(__lasttoken, __token);
 /* SJM 10/16/00 - save any pending attribte - because does not really read */
 /* token the actual attr string and other vars will be right and preserved */
 __last_attr_prefix = __attr_prefix;

 /* extremely rare number push back case */
 if (__toktyp == NUMBER) 
  {
   int32 wlen;

   __lastitokbase = __itokbase;
   __lastitoksized = __itoksized;
   __lastitok_sv_unbas_unsiz = __itok_sv_unbas_unsiz;  
   __lastitoksizdflt = __itoksizdflt;
   __lastitok_signed = __itok_signed;
   __lastitoklen = __itoklen;
    
   /* must malloc to save in rare pushed back case */
   /* SJM 03/20/00 - no unget of num token since already in a/b wrk as val */
   wlen = wlen_(__itoklen);
   __lastacwrk = (word32 *) __my_malloc(wlen*WRDBYTES);
   __lastbcwrk = (word32 *) __my_malloc(wlen*WRDBYTES);
   memcpy(__lastacwrk, __acwrk, wlen*WRDBYTES);
   memcpy(__lastbcwrk, __bcwrk, wlen*WRDBYTES);
   return;
  }
 if (__toktyp == REALNUM) 
  {
   __lastitokbase = __itokbase;
   __lastitoksized = __itoksized;
   __lastitok_sv_unbas_unsiz = __itok_sv_unbas_unsiz;  
   __lastitoksizdflt = __itoksizdflt;
   __lastitok_signed = __itok_signed;
   __lastitoklen = __itoklen;
   __lastitok_realval = __itok_realval;
  }
}

/*
 * read a verilog style number
 * know first char digit or ' and reads number end char
 * width if present left in nwidtoken and value in token
 *
 * notice that maximun number can be IDLEN - 1 digits must leave
 * since other sizes like max. no. of const. bits set to prevent possibility
 * of overflow
 *
 * notice '_' in number are just ignored and not added to token, is this ok
 */
static int32 rd_num(FILE *f, int32 c1)
{
 char *chp;
 int32 c;
 int32 len, toolong, isreal, errnum, blen, nsize, is_sv_unbase_unsized;
 word32 v, aval, bval;
 double d1;
 char *endp;
 /* SJM 03/20 - FIXME - for now limiting dec unsized to 16k digits */
 char nwidtoken[4*IDLEN];

 __itokbase = BDEC;
 __itoksized = FALSE;
 __itok_sv_unbas_unsiz = FALSE;
 __itoksizdflt = FALSE;
 __itok_signed = FALSE;
 __itoklen = WBITS;
 strcpy(nwidtoken, "");

 /* read the possible decimal size value or unsized unbased number */
 isreal = FALSE;
 len = 0;
 if ((c = c1) != '\'')
  {
   /* 06/22/00 - SJM - only 2 token number case if `[base][num] */ 
   __maybe_2tok_sized_num = FALSE;
   /* collect value */
   for (toolong = FALSE, chp = nwidtoken, len = 0;;)
    {
     while (c == '_') c = my_getc(f);
     switch (c) {
      case '0': case '1': case '2': case '3': case '4': case '5':
      case '6': case '7': case '8': case '9': break;
      /* - and + here */
      case 'e': case 'E': isreal = TRUE; break; 
      case '.': isreal = TRUE; break;
      case '-': case '+':
       /* + and minus after exponent legal else end of number */
       /* this can never cause a number to be real */
       if (*(chp - 1) == 'e' || *(chp - 1) == 'E') break;
       goto end_unsiz;
      default: goto end_unsiz;
     }
    if (++len >= 4*IDLEN)
     {
      if (!toolong)
       {
        __pv_ferr(948,
         "Verilog size prefix or unsized number too many characters (%d)",
         4*IDLEN);
        toolong = TRUE;
       }
     }
    else *chp++ = c;
    c = my_getc(f);
   }
end_unsiz:
  *chp = '\0';

  /* know c is not a digit - punctuation ok */
  if (__pv_ctab[c & 0x7f] == 0)
   {
    /* numbers can end with letter in udp tables */
    if (__letendnum_state) goto ok_letend;
    __pv_ferr(949,
     "unsized number terminated with illegal char '%c' (%x)", c & 0xff,
     c & 0xff);
    goto ok_letend;
   }
  /* this skips across new line */ 
  c = voverwhite(f, c);
  if (c == EOF) __macro_sep_width = TRUE;
 }

 /* know either c is char after unsized number or quote for Ver number */
ok_letend:
 if (c != '\'')
  {
   /* 06/22/00 - SJM - only 2 token number case if `[base][num] */ 
   __maybe_2tok_sized_num = FALSE;

   /* char after white space starts next token */
   /* this is case where next token is special first token on line */
   my_ungetc_(c, f);
   /* SJM - 03/20/00 - here just increase to size needed */
   if (len >= __numtok_wid) 
    {
     /* 06/26/00 - increase size with realloc but unsized not too wide */
     __numtoken = __my_realloc(__numtoken, __numtok_wid, __numtok_wid
      + RECLEN);
     __numtok_wid = len + RECLEN;
    }
   strcpy(__numtoken, nwidtoken);
   strcpy(nwidtoken, "");

   /* remove leading 0's  but if first char is . put 1 back */
   if (!__letendnum_state) rem_lead_0chars(__numtoken);
   /* allowing any legal c real here - but maybe should not allow dot not */
   /* surrounded by digits */
   if (isreal)
    {
     d1 = __my_strtod(__numtoken, &endp, &errnum);   
     if (errnum != 0 || *endp != '\0')
      __pv_ferr(950, "illegal real number %s", __numtoken);
     /* notice some compilers crash if doubles not 8 byte aligned ? */
     /* therefore need special routine for doubles */
     __itok_realval = d1;
     __itoklen = REALBITS;
     __itokbase = BDBLE;
     __macro_sep_width = FALSE;
     return(REALNUM);
    }
   /* SJM 10/02/03 - string of dec digits no '[base] is signed decimal */
   __itok_signed = TRUE;
   /* handle numbers that fit in 10 chars as special case */
   if (strlen(__numtoken) < 10) 
    {
     v = __my_strtoul(__numtoken, &endp, &errnum);
     if (errnum != 0 || *endp != '\0') __misc_terr(__FILE__, __LINE__); 
     __acwrk[0] = v;
     __bcwrk[0] = 0L;
     if (__macro_sep_width) __macro_sav_nwid = (int32) v; 
     return(NUMBER);
    }
   /* for implied WBITS number convert and truncate */
   goto do_convert;
  }

 /* know c is ' */
 /* know token read after this is not first token on line because */
 /* number becuase size number ' is on next line */
 /* know '[base] form is unsized and word32 but'[Ss][base] is signed */

 /* AIV 07/09/04 - special case to handle:  8'h`DEFINE */
 /* if `define macro contains a 'base it is illegal */
 if (__macbs_flag)
  {
   __pv_ferr(3418,
    "number with '[base] macro expansion %s contains extra '[base]", __token);
   /* AIV 07/12/04 - not sure what happens with error resync here */ 
   return(UNDEF);
  }

 /* if this is too wide will be caught later - this sets [size]' size */
 if (strcmp(nwidtoken, "") != 0)
  {
   blen = __my_strtoul(nwidtoken, &endp, &errnum);
   if (errnum != 0 || *endp != '\0')
    {
     __pv_ferr(952, "number size %s format bad", nwidtoken);
     __itoklen = WBITS;
    }
   else __itoklen = blen;

   /* saying 0'[base]... is legal and becomes WBITS */
   if (__itoklen == 0)
    {
     __pv_fwarn(557, "INTERNAL - zero number size changed to %d", WBITS);
     __itoklen = WBITS;
    }
   __itoksized = TRUE;
  }
 else
  {
   /* 06/22/00 - SJM - this is 2nd part of sized num */
   if (__maybe_2tok_sized_num)
    {
     /* flags turned off later */
     __itoklen = __macro_sav_nwid;
     __itoksized = TRUE;
    }
   else __itoksizdflt = TRUE;
  }

 /* '[base][number] is unsized 32 bits */
 if (__itoklen > MAXNUMBITS)
  {
   __pv_ferr(953, "number size too large (%d)", MAXNUMBITS);
   __itoklen = WBITS;
   __itoksized = FALSE;
  }

 /* SJM 10/01/03 - add code that get the optional base signed char */ 
 /* and set signed flag for use when expression token constructed */
 c = my_getc(f); 
 if (c == 's' || c == 'S')
  {
   __itok_signed = TRUE;
   c = my_getc(f); 
  }

 /* AIV 01/04/10 - parse SV '0/'1/'x/'z auto sized literal values */
 if (__sv_parse)
  {
   /* no sized declared and is 0/1/x/X/z/Z */
   if (!__itoksized)
    {
     is_sv_unbase_unsized = FALSE;
     switch (c) {
       case '0':
        aval = 0;
        bval = 0;
        is_sv_unbase_unsized = TRUE;
        break;
       case '1':
        aval = 1;
        bval = 0;
        is_sv_unbase_unsized = TRUE;
        break;
       case 'x':
       case 'X':
        aval = 1;
        bval = 1;
        is_sv_unbase_unsized = TRUE;
        break;
       case 'z':
       case 'Z':
        aval = 0;
        bval = 1;
        is_sv_unbase_unsized = TRUE;
        break;
      }
     
     /* if autosized just make one literal value and mark the expression */
     /* setting global __itok_sv_unba_unsiz */
     if (is_sv_unbase_unsized)
      {
       memset(__acwrk, aval, WRDBYTES);
       memset(__bcwrk, bval, WRDBYTES);
       __itoklen = 1;
       __itoksized = FALSE;
       __itok_sv_unbas_unsiz = TRUE;
       __itok_signed = FALSE;
       return(NUMBER);
      }
    }
  }

 if ((__itokbase = __to_base(c)) == -1)
  {
   __pv_ferr(954,
    "illegal Verilog number base %c - for compiler directive use back quote(`)", c);
   my_ungetc_(c, f);
   __macro_sep_width = FALSE;
   return(UNDEF);
  }
 c = my_getc(f);
 c = voverwhite(f, c);
 /* AIV 07/09/04 - special case to handle:  8'h`DEFINE */
 if (c == '`')
  {
   int32 stok;
   my_ungetc_(c, f);
   /* save the base */
   stok = __itokbase;
   /* set the flag to make sure macro doesn't contain a base */
   __macbs_flag = TRUE;
   /* AIV 07/12/04 - need recursive call but can't read another number */ 
   __get_vtok();
   __macbs_flag = FALSE;
   __itokbase = stok;
   goto do_convert;
  }

 /* know c is 1st character of sized number */
 toolong = FALSE;
 for (chp = __numtoken, len = 0;;)
  {
   while (c == '_') c = my_getc(f);
   c1 = __is_vdigit(c, __itokbase);
   if (c1 == -1) break;
   if (c1 == -2)
    {
     __pv_ferr(955, "digit %c illegal for base '%c", c,
      __to_baselet(__itokbase));
     c = c1 = '0';
    }
   /* using maximum length of Verilog line as 1024 (really ID len. max) */
   if (++len >= __numtok_wid)
    {
     if (len >= MAXNUMBITS) 
      {
       if (!toolong)
        {
         __pv_ferr(956,
          "Verilog sized number too many characters (%d)", MAXNUMBITS);
         toolong = TRUE;
        }
      }
     else
      {
       /* LOOKATME - SJM 03/20/00 - doubling may be too fast growth */
       nsize = 2*__numtok_wid;
       __numtoken = __my_realloc(__numtoken, __numtok_wid, nsize);
       __numtok_wid = nsize;
       /* AIV 04/20/06 - need to reset chp pointer due to realloc */ 
       chp = &(__numtoken[len - 1]); 
       *chp++ = c1;
      }
    }
   else *chp++ = c1;
   c = my_getc(f);
  }
 *chp = '\0';

 if (strcmp(__numtoken, "") == 0)
  {
   __pv_ferr(957, "sized number value part empty");
   strcpy(__numtoken, "0");
  }

 if (__pv_ctab[c & 0x7f] == 0)
  __pv_ferr(958, "sized number terminated with illegal char '%c' (%x)",
  c % 0xff, c & 0xff);
 my_ungetc_(c, f);
 /* finally do the conversion - know sizedness set and length in itok len */
 /* length never 0 */

 /* notice this can never generate error */
 /* wide numbers truncated in here - do all non real numbers here */
do_convert:
 /* this sets number bit length and allocates number if needed */
 __macro_sep_width = FALSE;
 __to_dhboval(__itokbase, TRUE);
 return(NUMBER);
}

/*
 * remove leading 0 characters from numer string in token
 * this works in place
 */
static void rem_lead_0chars(char *s)
{
 int32 i, j;
 int32 slen;

 /* first set index to first non 0 char */
 for (i = 0; ; i++)
  {
   /* number all zero convert to 1 0 */
   if (s[i] == '\0') { s[0] = '0'; s[1] = '\0'; return; }
   if (s[i] != '0') break;
  }
 if (i == 0) return;
 /* if leading is . then must add 1 leading 0 - know at least 0. at start */
 if (s[i] == '.') i--;  

 /* copy to remove all leading 0's */
 slen = strlen(s);
 for (j = 0; j < slen - i; j++) s[j] = s[i + j]; 
 s[slen - i] = '\0';
}

/*
 * skip over white space and return char just after
 * expects current character to be in c - no skip if current not white space
 */
static int32 voverwhite(FILE *f, int32 c)
{
 int32 ct;

 for (;; c = my_getc(f))
  {
   /* notice anthing escaped is not white space */
   if ((ct = __pv_ctab[c & 0x7f]) == 1) continue;
   if (ct == 3)
    { __lin_cnt++; __total_rd_lines++; __first_num_eol = TRUE; continue; }
   break;
  }
 return(c);
}

/*
 * convert a character to a Verilog number base
 */
extern int32 __to_base(int32 c)
{
 switch (c) {
  case 'b': case 'B': return(BBIN);
  case 'o': case 'O': return(BOCT);
  case 'd': case 'D': return(BDEC);
  case 'h': case 'H': return(BHEX);
 }
 return(-1);
}

/*
 * return TRUE if character can appear in Verilog number
 * return value if digit, -1 for non digit or -2 for out of range digit 
 * (ends number)
 */
extern int32 __is_vdigit(int32 c, int32 base)
{
 switch (c) {
  case 'x': case 'X': return('x');
  case '?': case 'z': case 'Z': return('z');
 }
 if (!isxdigit(c)) return(-1);
 switch (base) {
  case BBIN:
   if (c != '0' && c != '1') return(-2);
   break;
  case BOCT:
   if (c < '0' || c > '7') return(-2);
   break;
  case BDEC:
   if (!isdigit(c)) return(-2);
   break;
  case BHEX:
   if (c >= 'A' && c <= 'F') return(tolower(c));
   break;
  default: __case_terr(__FILE__, __LINE__);
 }
 return(c);
}

/*
 * ROUTINES TO CONVERT TO AB VALUE FROM SCANNED TOKEN
 */

/*
 * convert a scanned input number token to a h, b, or o value
 * this routines x/z extends from highest used digit if needed
 * warning if too many digits and truncates
 * this routine fills __ac wrk and __bc wrk, if needed will widen
 *
 * this is also used by tf_ string to value conversion routines 
 * sets values in __numtoken, __itoklen, __itok_signed
 */
extern void __to_dhboval(int32 base, int32 emit_warn)
{
 int32 chlen, wlen, srcwlen, ubits, srcblen;
 word32 aival, bival;
 char s1[RECLEN];

 chlen = strlen(__numtoken);
 /* must allow enough room in work string to convert number */
 /* even if much wider than itoklen - just at least wide estimate here */
 srcblen = chlen_to_bitlen(chlen, base);
 if (srcblen < __itoklen) srcblen = __itoklen; 

 /* SJM 10/02/03 now wide decimal or numbers with s/S base part signed */ 
 /* therefore itok is int32 global not accessed here */

 wlen = wlen_(srcblen);
 /* if need to widen or wider than default, change allocated length */
 /* notice left until maybe changed next time used */
 if (wlen > __abwrkwlen || (__abwrkwlen > DFLTIOWORDS && wlen <= DFLTIOWORDS))
  chg_abwrklen(wlen);

 /* now know __ac wrk and __bc wrk wide enough */
 memset(__acwrk, 0, wlen*WRDBYTES);
 memset(__bcwrk, 0, wlen*WRDBYTES);

 /* convert number in token into work constant values */
 /* notice previous guess of src blen, made exact here */
 switch (base) {
  /* notice must trucate/widen after conversion here */
  case BDEC: to_dec(&srcblen); strcpy(s1, "decimal"); break;
  case BBIN: to_bin(chlen); strcpy(s1, "binary"); srcblen = chlen; break;
  case BOCT: to_oct(chlen); strcpy(s1, "octal"); srcblen = 3*chlen; break;
  case BHEX: to_hex(chlen); strcpy(s1, "hex"); srcblen = 4*chlen; break;
  default: __case_terr(__FILE__, __LINE__);
 }

 /* words and occupied bits of number represented by chars */
 /* check case of number of character wider - maybe too wide number */
 /* __itoklen is number of bits that word32 must be stored in */
 /* srcblen is number of bits in source input number */
 if (srcblen > __itoklen)
  {
   srcwlen = wlen_(srcblen);
   if (vnum_toowide(__acwrk, srcblen) || vnum_toowide(__bcwrk, srcblen))
    {
     /* no warning for [3-1]'h[zx] or [2-1]'o[zx] in high position */
     /* notice for hex, must be in same word32 to have not too wide nibble */
     if (base == BHEX)
      {
       if (srcblen - __itoklen < 4 && wlen == srcwlen
 && nibblexz(__acwrk[wlen - 1], __bcwrk[wlen - 1], srcblen))
        goto do_mask;
      }
     else if (base == BOCT)
      {
       if (srcblen - __itoklen < 3 && octdigxz(__acwrk, __bcwrk, srcblen))
        goto do_mask; 
      }
     /* SJM 12/04/00 - no warn if skipping over ifdef because will not */
     /* parse `macro_width_name h [number] right */
     if (emit_warn && !__ifdef_skipping)
      { 
       if (__run_state == SS_SIM)
        __pv_warn(558, "redundant digit(s) in tf_strput number %s",
         decompnum_to_str(s1, __numtoken, base, __itoklen));
#ifndef __CVC_RT__
       else __pv_fwarn(558, "redundant digit(s) in number %s",
        decompnum_to_str(s1, __numtoken, base, __itoklen));
#endif
      }
    }
   /* if values 0 or vnum not too wide, no warn but still must mask */

   /* must truncate the values to __itoklen */
   /* this leave high words as is but since unused - if used will be zeroed */
   /* before use */
do_mask:
   ubits = ubits_(__itoklen);
   __acwrk[wlen - 1] &= __masktab[ubits];
   __bcwrk[wlen - 1] &= __masktab[ubits];
  }
 else if (srcblen < __itoklen)
  {
   /* case where widening needed */
   if (__numtoken[0] == 'z' || __numtoken[0] == 'Z')
    { aival = 0L; bival = 1L; }
   else if (__numtoken[0] == 'x' || __numtoken[0] == 'X')
    { aival = 1L; bival = 1L; }
   else { aival = 0L; bival = 0L; }

   widen_val(__acwrk, __itoklen, srcblen, aival);
   widen_val(__bcwrk, __itoklen, srcblen, bival);
  }
}

/*
 * computer number of bits + 1 needed to store number in base of chlen
 * worst case - could contain '_' place holders
 */
static int32 chlen_to_bitlen(int32 chlen, int32 base)
{
 int32 bitlen;
 double d1;

 switch (base) {
  case BDEC:
   /* here must make sure bit enough if rounding error */
   /* actual conversion will compute exact bit length */
   d1 = ((double) chlen)/LG2_DIV_LG10 + WBITS;
   bitlen = (int32) d1;
   break;
  case BBIN: bitlen = chlen; break;
  case BOCT: bitlen = 3*chlen; break;
  case BHEX: bitlen = 4*chlen; break;
  default: __case_terr(__FILE__, __LINE__); return(0);
 }
 return(bitlen);
}

/*
 * change __ac wrk (and bc) work area length from blen if needed
 * only gets here if either blen (__itoklen) or abwork len wider than default
 * notice __ac wrk and __bc wrk not necessary contiguous
 */
static void chg_abwrklen(int32 wlen)
{
 int32 olen, nlen;

 olen = WRDBYTES*__abwrkwlen;
 if (wlen <= DFLTIOWORDS) __abwrkwlen = DFLTIOWORDS; else __abwrkwlen = wlen;
 nlen = WRDBYTES*__abwrkwlen;
 __acwrk = (word32 *) __my_realloc(__acwrk, olen, nlen);
 __bcwrk = (word32 *) __my_realloc(__bcwrk, olen, nlen);
}

/*
 * convert a number scanned token to a decimal value
 * know number initialized to 0 of itoklen width
 * LOOKATME - could maybe speed up by using scanf if fits in one word?
 */
static void to_dec(int32 *blen) 
{
 /* know __ac wrk and __bc wrk set to 0 before this is called */
 if (strchr(__numtoken, 'z') != NULL)
  { one_allbits_(__bcwrk, __itoklen); *blen = __itoklen; return; }
 else if (strchr(__numtoken, 'x') != NULL)
  {
   /* 1 decimal digit will be at least this wide */
   one_allbits_(__acwrk, __itoklen);
   one_allbits_(__bcwrk, __itoklen);
   *blen = __itoklen;
   return;
  }
 /* do the conversion */
 wide_strtoverdec(*blen);
 /* finally, find real convert decimal number bit width by trimming */
 *blen = __trim1_0val(__acwrk, *blen); 
}

/*
 * convert a string in __numtoken into a decimal number in acwrk that is known
 * to be wide enough (blen width)
 * know all digits in token are legal decimal digits
 */
static void wide_strtoverdec(int32 blen)
{
 int32 wlen;
 char *chp;
 word32 *reg10, *newdig, *acc;
 struct xstk_t *xsp;

 wlen = wlen_(blen);
 push_xstk_(xsp, blen);
 /* build the constant 10 */
 reg10 = xsp->ap;
 memset(reg10, 0, wlen*WRDBYTES);
 reg10[0] = 10;
 /* and use b part to hold new digit to add */
 newdig = xsp->bp;
 memset(newdig, 0, wlen*WRDBYTES);
 push_xstk_(xsp, blen);
 acc = xsp->ap;
 memset(acc, 0, wlen*WRDBYTES);

 chp = __numtoken;
 __acwrk[0] = *chp - '0'; 
 /* notice start with high (left) digit */ 
 for (chp++; *chp != '\0'; chp++) 
  {
   /* 10 times current value plus new digit */
   __lmult(acc, __acwrk, reg10, blen);
   newdig[0] = *chp - '0';
   __ladd(acc, acc, newdig, blen); 
   /* notice the accumulator must be copied into ac wrk since lmult res */
   /* must be different value than u and v */
   memcpy(__acwrk, acc, wlen*WRDBYTES);
  } 
 /* value now in acwrk */
 __pop_xstk();
 __pop_xstk();
}

/*
 * convert a number scanned token to binary in work string (acwrk and bcwrk)
 * input in token and token length set
 * know will fit and correct
 * notice caller know to have zerod __ac wrk and __bc wrk
 */
static void to_bin(int32 slen)
{
 int32 i, bi;
 word32 a, b;

 /* fill val from low char (rght str) to high char (const left to rght) */
 for (i = slen - 1, bi = 0; i >= 0; i--, bi++)
  {
   ch_tobits(&a, &b, __numtoken[i]);
   __lhsbsel(__acwrk, bi, a);
   __lhsbsel(__bcwrk, bi, b);
  }
}

/*
 * convert binary plus z-x character to bit
 */
static int32 ch_tobits(word32 *ap, word32 *bp, int32 ch)
{
 *ap = *bp = 0L;
 switch (ch) {
  case 'z': case 'Z': *bp = 1L; break;
  case 'x': case 'X': *ap = 1L; *bp = 1L; break;
  case '0': break;
  case '1': *ap = 1L; break;
  default: return(FALSE);
 }
 return(TRUE);
}

/*
 * convert a number scanned token to octal in work string (acwrk and bcwrk)
 * input in token and token length set
 * know will fit and __ac wrk and __bc wrk zeroed 
 */
static void to_oct(int32 slen)
{
 int32 i, bi;
 word32 a, b;

 /* fill val from low char (rght str) to high char (const left to rght) */
 for (i = slen - 1, bi = 0; i >= 0; i--, bi += 3)
  {
   ch_toocts(&a, &b, __numtoken[i]);
   /* cant use literal shifts and mask because some octs split on boundary */
   __lhspsel(__acwrk, bi, &a, 3);
   __lhspsel(__bcwrk, bi, &b, 3);
  }
}

/*
 * convert octal digit plus z-x character to bit
 */
static int32 ch_toocts(word32 *ap, word32 *bp, int32 ch)
{
 *ap = *bp = 0L;
 switch (ch) {
  case 'z': case 'Z': *bp = 0x7L; break;
  case 'x': case 'X': *ap = 0x7L; *bp = 0x7L; break;
  default:
   if (ch < '0' || ch > '7') return(FALSE);
   *ap = (word32) ((ch - '0') & 0x7L);
  }
 return(TRUE);
}

/*
 * convert number scanned token to hex in work string (__ac wrk and __bc wrk)
 * input in token and itoklen set
 * know will fit and know acwrk and bcwrk already zeroed
 * sets tokval or tokptr if > WBITS
 */
static void to_hex(int32 slen)
{
 int32 i, bi;
 word32 *ap, *bp;
 word32 a, b;

 /* fill val from low char (right str) to high char (const left to right) */
 ap = __acwrk;
 bp = __bcwrk;
 for (i = slen - 1, bi = 0; i >= 0; i--)
  {
   /* know already checked for out of range before here */
   ch_tohexs(&a, &b, __numtoken[i]);
   if (bi == 0) { *ap = a; *bp = b; bi += 4; continue; }
   *ap |= a << bi;
   *bp |= b << bi;
#ifdef __CVC32__
   if (bi == 28) { bi = 0; ap++; bp++; } else bi += 4;
#else
   if (bi == 60) { bi = 0; ap++; bp++; } else bi += 4;
#endif
  }
}

/*
 * convert hex digit plus x and z to bit pattern
 */
static int32 ch_tohexs(word32 *ap, word32 *bp, int32 ch)
{
 *ap = *bp = 0L;
 switch (ch) {
  case 'z': case 'Z': *bp = 0xfL; break;
  case 'x': case 'X': *ap = 0xfL; *bp = 0xfL; break;
  default:
   if (ch >= '0' && ch <= '9')
    {
     *ap = (word32) ((ch - '0') & 0xfL);
     break;
    }
   if (isupper(ch)) ch = tolower(ch);
   if (ch >= 'a' && ch <= 'f')
    {
     *ap = (word32) ((10 + ch - 'a') & 0xfL);
     break;
    }
   /* should have already been caught */
   /* illegal 'h radix digit */
   return(FALSE);
  }
 return(TRUE);
}

/*
 * return T if source input number at wp of length srcblen wider
 * than __itoklen - if all high bits 0 returns F (not too wide)
 *
 * only called if srcblen > __itoklen
 * if too wide only because x or z hex or oct digit returns T here
 * but change to not too wide later
 */
static int32 vnum_toowide(word32 *wp, int32 srcblen)
{
 int32 i;
 int32 srcwlen, storwlen, storubits;

 srcwlen = wlen_(srcblen);
 storwlen = wlen_(__itoklen);
 storubits = ubits_(__itoklen);
 /* if high bits of high word32 from storage token length, too wide */
 if ((wp[storwlen - 1] & ~__masktab[storubits]) != 0L) return(TRUE);
 for (i = storwlen; i < srcwlen; i++) if (wp[i] != 0L) return(TRUE);
 return(FALSE);
}

/*
 * return T if high unused bits of high 4 bit nibble x or z
 * know shubits is aligned on 4 bit boundary and both in same word
 * know if all high bits 0 won't get here
 */
static int32 nibblexz(word32 aw, word32 bw, int32 srcblen)
{
 int32 itokubits;
 word32 tmp;

 /* know __itoklen has at least 1 high bit unused or will not get here */
 itokubits = ubits_(__itoklen);
 bw >>= itokubits;
 aw >>= itokubits;
 switch (srcblen - __itoklen) {
  case 1:
   /* notice this will shift so 1 extra bit is in low position not 8 pos. */
   if ((bw & 1L) == 0L) return(FALSE);
   break;
  case 2:
   /* if 2, b part bits are not 11 or a part 01 or 10 then not ok nibble */
   if ((bw & 3L) != 3L || ((tmp = aw & 3L) == 01L || tmp == 02L))
    return(FALSE);
   break;
  case 3:
   /* if 3 extra, b part bits 111 and a part not 000 or 111, not ok nibble */
   if ((bw & 7L) != 7L || ((tmp = aw & 7L) != 7L && tmp != 0L))
    return(FALSE);
   break;
  default: __case_terr(__FILE__, __LINE__);
 }
 return(TRUE);
}

/*
 * return T if high unused bits of high 3 bit nibble x or z
 */
static int32 octdigxz(word32 *ap, word32 *bp, int32 srcblen)
{
 word32 tmp, aw, bw;

 /* part select needed to isolate bits, oct can overlap word32 boundary */
 __rhspsel(&bw, bp, __itoklen - 1, 3);
 switch (srcblen - __itoklen) {
  case 1:
   if ((bw & 4L) != 0L) return(FALSE); break;
  case 2:
   if ((bw & 6L) != 6L) return(FALSE);
   __rhspsel(&aw, ap, __itoklen - 1, 3);
   /* for 2 bits must both be x aw=11? or z aw=00? */
   /* not a high x/z if 010 or 100 after masking */
   if ((tmp = aw & 6L) == 2L || tmp == 4L) return(FALSE);
   break;
  default: __case_terr(__FILE__, __LINE__);
 }
 return(TRUE);
}

/*
 * widen a shorter value into a longer value in place (either a or b)
 * highval determines kind of ext. (0 = 0, 1 = 1)
 * do not know what is in higher values
 * know valwp wide enough
 */
static void widen_val(word32 *vwp, int32 lngblen, int32 shblen, word32 highval)
{
 int32 i;
 word32 *wp;
 word32 mask;
 int32 shwlen, shubits, lngwlen, lngubits;

 shwlen = wlen_(shblen);
 shubits = ubits_(shblen);
 lngwlen = wlen_(lngblen);
 lngubits = ubits_(lngblen);
 /* first extend unused part of old short high word32 */
 if (shubits != 0)
  {
   mask = __masktab[shubits];
   vwp[shwlen - 1] &= mask;
   if (highval == 1L) vwp[shwlen - 1] |= ~mask;
  }
 /* done if widen up to max of WBITS or words same length */
 if (lngwlen == 1 || lngwlen == shwlen) goto done;

 /* next set all higher words to highval */
 if (highval == 0L) memset(&(vwp[shwlen]), 0, WRDBYTES*(lngwlen - shwlen));
 else
  {
   /* notice if incing wp cannot use indexed later */ 
   for (i = shwlen, wp = &(vwp[shwlen]); i < lngwlen; i++) *wp++ = ALL1W;
  }

done:
 /* finally zero unused portion of high word32 */
 vwp[lngwlen - 1] &= __masktab[lngubits];
}

/*
 * MISC. TOKEN HANDLING ROUTINES
 */

/*
 * version of print vtoken where value is not in global _toktyp  
 * for use inside get token routines
 */ 
extern char *__prt2_vtok(int32 ttyp)
{
 int32 save_ttyp;
 char *chp; 

 save_ttyp = __toktyp;
 __toktyp = ttyp;
 chp = __prt_vtok();
 __toktyp = save_ttyp;
 return(chp);
}

/*
 * print a token for error messages - indicate token is a keyword for msg
 *
 */
extern char *__prt_kywrd_vtok(void)
{
 char s1[RECLEN];

 /* SJM 02-07-13 - another SV err recovery problem, if no minus sv option */
 /* usually from sv lib and import in source, this will not be kyword */
 if (get_vkeywrd(__token) != ID && __toktyp >= BKEYS)
  {
   /* know pv varnam always has enough room for keyword */
   sprintf(s1, "Verilog keyword: %s",  __prt_vtok());
   strcpy(__pv_varnam, s1);
   return(__pv_varnam);
  }
 return(__prt_vtok());
}

/*
 * print the value of a token
 * only for current token (i.e. moves punct./op. to token)
 * i.e. typ cannot be old
 */
extern char *__prt_vtok(void)
{
 /* notice this must not change current val. of token */
 if (__toktyp >= BKEYS)
  { __get_vkeynam(__pv_varnam, __toktyp); return(__pv_varnam); }

 switch (__toktyp) {
  case TEOF:
   if (__run_state == SS_SIM && __cmd_s == NULL) strcpy(__token, "**EOL**");  
   else strcpy(__token, "**EOF**");
   break;
  case ID: return(__token);
  case NUMBER: return(__numtoken);
  case REALNUM: sprintf(__token, "%#g",  __itok_realval); break;
  case LITSTR: return(__strtoken);
  case SEMI: strcpy(__token, ";"); break;
  case COMMA: strcpy(__token, ","); break;
  case COLON: strcpy(__token, ":"); break;
  case SHARP: strcpy(__token, "#"); break;
  case LPAR: strcpy(__token, "("); break;
  case RPAR: strcpy(__token, ")"); break;
  case LSB: strcpy(__token, "["); break;
  case RSB: strcpy(__token, "]"); break;
  case LCB: strcpy(__token, "{"); break;
  case RCB: strcpy(__token, "}"); break;
  case DOT: strcpy(__token, "."); break;
  case QUEST: strcpy(__token, "?"); break;
  case AT: strcpy(__token, "@"); break;
  case CAUSE: strcpy(__token, "->"); break;
  case PLUS: strcpy(__token, "+"); break; 
  case MINUS: strcpy(__token, "-"); break;
  case TIMES: strcpy(__token, "*"); break;
  case POWER: strcpy(__token, "**"); break;
  case DIV: strcpy(__token, "/"); break;
  case MOD: strcpy(__token, "%"); break;
  case BITNOT: strcpy(__token, "~"); break;
  case BITREDAND: strcpy(__token, "&"); break;
  case BITREDOR: strcpy(__token, "|"); break;
  case BITREDXOR: strcpy(__token, "^"); break;
  /* notice ~ ^ are 2 unary operators */
  case REDXNOR: strcpy(__token, "^~"); break;
  case RELGE: strcpy(__token, ">="); break;
  case RELGT: strcpy(__token, ">"); break;
  case RELLE: strcpy(__token, "<="); break;
  case RELLT: strcpy(__token, "<"); break;
  case RELCEQ: strcpy(__token, "==="); break;
  case RELEQ: strcpy(__token, "=="); break;
  case RELCNEQ: strcpy(__token, "!=="); break;
  case RELNEQ: strcpy(__token, "!="); break;
  case BOOLAND: strcpy(__token, "&&"); break;
  case BOOLOR: strcpy(__token, "||"); break;
  case NOT: strcpy(__token, "!"); break;
  case SHIFTL: strcpy(__token, "<<"); break;
  case ASHIFTL: strcpy(__token, "<<<"); break;
  case SHIFTR: strcpy(__token, ">>"); break;
  case ASHIFTR: strcpy(__token, ">>>"); break;
  case EQ: strcpy(__token, "="); break;
  case FPTHCON: strcpy(__token, "*>"); break;
  case PPTHCON: strcpy(__token, "=>"); break;
  case TCHKEVAND: strcpy(__token, "&&&"); break;
  case UNDEF: strcpy(__token, "**NONE**"); break;
  case INC: strcpy(__token, "++"); break; 
  case DEC: strcpy(__token, "--"); break; 
  case PLUS_EQ: strcpy(__token, "+="); break; 
  case MINUS_EQ: strcpy(__token, "-="); break; 
  case TIMES_EQ: strcpy(__token, "*="); break;  
  case DIV_EQ: strcpy(__token, "/="); break; 
  case MOD_EQ: strcpy(__token, "%="); break; 
  case AND_EQ: strcpy(__token, "&="); break; 
  case OR_EQ: strcpy(__token, "|="); break; 
  case XOR_EQ: strcpy(__token, "^="); break; 
  case SHIFTL_EQ: strcpy(__token, "<<="); break; 
  case ASHIFTL_EQ: strcpy(__token, "<<<="); break; 
  case SHIFTR_EQ: strcpy(__token, ">>="); break; 
  case ASHIFTR_EQ: strcpy(__token, ">>>="); break; 
  default: __case_terr(__FILE__, __LINE__);
 }
 return(__token);
}

/*
 * convert a punct./operator token to a name
 * only for current token (i.e. moves punct./op. to token)
 * non expression token removed when tree built but included here
 * result 
 */
extern char *__to_opname(word32 otyp)
{
 /* token number %d illegal in expression */
 if (otyp > TEOF) __misc_fterr(__FILE__, __LINE__);
 return(__opinfo[otyp].opnam);
}

/* note! - must be kept in alphabetical order */
/* keyword types (already know token is a name) */
/* making as many things as possible Verilog since they are reserved */
struct vkeywds_t {
 char *vknam;
 int32 vknum;
};

static struct vkeywds_t vkeywds[] = {
 { "`accelerate", CDIR_ACCEL },
 { "`autoexpand_vectornets", CDIR_AEXPVECNETS },
 { "`celldefine", CDIR_CELLDEF },
 { "`default_decay_time", CDIR_DFLTDECAYTIME },
 { "`default_nettype", CDIR_DFLNTYP },
 { "`default_trireg_strength", CDIR_DFLTTRIREGSTREN },
 { "`define", CDIR_DEFINE },
 { "`delay_mode_distributed", CDIR_DELMODEDIST },
 { "`delay_mode_path", CDIR_DELMODEPATH },
 { "`delay_mode_unit", CDIR_DELMODEUNIT },
 { "`delay_mode_zero", CDIR_DELMODEZERO },
 { "`else", CDIR_ELSE },
 { "`elsif", CDIR_ELSIF },
 { "`endcelldefine", CDIR_ECELLDEF },
 { "`endif", CDIR_ENDIF },
 { "`endprotect", CDIR_ENDPROTECT },
 { "`endprotected", CDIR_ENDPROTECTED },
 { "`expand_vectornets", CDIR_XPNDVNETS },
 { "`ifdef", CDIR_IFDEF },
 { "`ifndef", CDIR_IFNDEF },
 { "`include", CDIR_INCLUDE },
 { "`noaccelerate", CDIR_NOACCEL },
 { "`noexpand_vectornets", CDIR_NOXPNDVNETS },
 { "`noremove_gatenames", CDIR_NOREMGATENAMES },
 { "`noremove_netnames", CDIR_NOREMNETNAMES },
 { "`nounconnected_drive", CDIR_NOUNCONNDRIVE },
 { "`protect", CDIR_PROTECT },
 { "`protected", CDIR_PROTECTED },
 { "`remove_gatenames", CDIR_REMGATESNAMES },
 { "`remove_netnames", CDIR_REMNETNAMES },
 { "`resetall", CDIR_RESETALL },
 { "`timescale", CDIR_TIMESCALE },
 { "`unconnected_drive", CDIR_UNCONNDRIVE },
 { "`undef", CDIR_UNDEF },

 { "always", ALWAYS },
 { "assign", ASSIGN },
 { "automatic", AUTOMATIC },
 { "begin", Begin },
 { "case", CASE },
 { "casex", CASEX },
 { "casez", CASEZ },
 { "deassign", DEASSIGN },
 { "default", DEFAULT },
 { "defparam", DEFPARAM },
 { "disable", DISABLE },
 { "edge", EDGE },
 { "else", ELSE },
 { "end", END },
 { "endcase", ENDCASE },
 { "endfunction", ENDFUNCTION },
 { "endgenerate", ENDGENERATE },
 { "endmodule", ENDMODULE },
 { "endprimitive", ENDPRIMITIVE },
 { "endspecify", ENDSPECIFY },
 { "endtable", ENDTABLE },
 { "endtask", ENDTASK },
 { "event", EVENT },
 { "for", FOR },
 { "force", FORCE },
 { "forever", FOREVER },
 { "fork", FORK },
 { "function", FUNCTION },
 { "generate", GENERATE },
 { "genvar", GENVAR },
 { "highz0", HIGHZ0 },
 { "highz1", HIGHZ1 },
 { "if", IF },
 { "ifnone", IFNONE }, 
 { "initial", INITial },
 { "inout", INOUT },
 { "input", INPUT },
 /* not int32 */
 { "integer", INTEGER },
 { "join", JOIN },
 { "large", LARGE },
 { "localparam", LOCALPARAM },
 { "macromodule", MACROMODULE },
 { "medium", MEDIUM },
 { "module", MODULE },
 { "negedge", NEGEDGE },
 { "output", OUTPUT },
 { "parameter", PARAMETER },
 { "posedge", POSEDGE },
 { "primitive", PRIMITIVE },
 { "pull0", PULL0 },
 { "pull1", PULL1 },
 { "real", REAL },
 { "realtime", REALTIME },
 { "reg", REG },
 { "release", RELEASE },
 { "repeat", REPEAT },
 { "scalared", SCALARED },
 { "signed", SIGNED },
 { "small", SMALL },
 { "specify", SPECIFY },
 { "specparam", SPECPARAM },
 { "strength", Strength },
 { "strong0", STRONG0 },
 { "strong1", STRONG1 },
 { "supply0", SUPPLY0 },
 { "supply1", SUPPLY1 },
 { "table", TABLE },
 { "task", TASK },
 { "time", TIME },
 { "tri", TRI },
 { "tri0", TRI0 },
 { "tri1", TRI1 },
 { "triand", TRIAND },
 { "trior", TRIOR },
 { "trireg", TRIREG },
 { "vectored", VECTORED },
 { "wait", WAIT },
 { "wand", WAND },
 { "weak0", WEAK0 },
 { "weak1", WEAK1 },
 { "while", WHILE },
 { "wire", WIRE },
 { "wor", WOR }
};
#define NVKEYWDS (sizeof(vkeywds) / sizeof(struct vkeywds_t))

/* AIV 08/25/10 - separate keyword table with SV keywords */
static struct vkeywds_t svkeywds[] = {
 { "`accelerate", CDIR_ACCEL },
 { "`autoexpand_vectornets", CDIR_AEXPVECNETS },
 { "`celldefine", CDIR_CELLDEF },
 { "`default_decay_time", CDIR_DFLTDECAYTIME },
 { "`default_nettype", CDIR_DFLNTYP },
 { "`default_trireg_strength", CDIR_DFLTTRIREGSTREN },
 { "`define", CDIR_DEFINE },
 { "`delay_mode_distributed", CDIR_DELMODEDIST },
 { "`delay_mode_path", CDIR_DELMODEPATH },
 { "`delay_mode_unit", CDIR_DELMODEUNIT },
 { "`delay_mode_zero", CDIR_DELMODEZERO },
 { "`else", CDIR_ELSE },
 { "`elsif", CDIR_ELSIF },
 { "`endcelldefine", CDIR_ECELLDEF },
 { "`endif", CDIR_ENDIF },
 { "`endprotect", CDIR_ENDPROTECT },
 { "`endprotected", CDIR_ENDPROTECTED },
 { "`expand_vectornets", CDIR_XPNDVNETS },
 { "`ifdef", CDIR_IFDEF },
 { "`ifndef", CDIR_IFNDEF },
 { "`include", CDIR_INCLUDE },
 { "`noaccelerate", CDIR_NOACCEL },
 { "`noexpand_vectornets", CDIR_NOXPNDVNETS },
 { "`noremove_gatenames", CDIR_NOREMGATENAMES },
 { "`noremove_netnames", CDIR_NOREMNETNAMES },
 { "`nounconnected_drive", CDIR_NOUNCONNDRIVE },
 { "`protect", CDIR_PROTECT },
 { "`protected", CDIR_PROTECTED },
 { "`remove_gatenames", CDIR_REMGATESNAMES },
 { "`remove_netnames", CDIR_REMNETNAMES },
 { "`resetall", CDIR_RESETALL },
 { "`timescale", CDIR_TIMESCALE },
 { "`unconnected_drive", CDIR_UNCONNDRIVE },
 { "`undef", CDIR_UNDEF },

 { "always", ALWAYS },
 { "always_comb", ALWAYS_COMB },
 { "always_ff", ALWAYS_FF },
 { "always_latch", ALWAYS_LATCH },
 { "assign", ASSIGN },
 { "automatic", AUTOMATIC },
 { "begin", Begin },
 { "bit", BIT },
 { "break", BREAK },
 { "byte", BYTE },
 { "case", CASE },
 { "casex", CASEX },
 { "casez", CASEZ },
 { "chandle", CHANDLE },
 { "context", CONTEXT },
 { "continue", CONTINUE },
 { "deassign", DEASSIGN },
 { "default", DEFAULT },
 { "defparam", DEFPARAM },
 { "disable", DISABLE },
 { "do", DO },
 { "edge", EDGE },
 { "else", ELSE },
 { "end", END },
 { "endcase", ENDCASE },
 { "endfunction", ENDFUNCTION },
 { "endgenerate", ENDGENERATE },
 { "endmodule", ENDMODULE },
 { "endprimitive", ENDPRIMITIVE },
 { "endspecify", ENDSPECIFY },
 { "endtable", ENDTABLE },
 { "endtask", ENDTASK },
 { "event", EVENT },
 { "export", EXPORT },
 { "for", FOR },
 { "force", FORCE },
 { "foreach", FOREACH },
 { "forever", FOREVER },
 { "fork", FORK },
 { "function", FUNCTION },
 { "generate", GENERATE },
 { "genvar", GENVAR },
 { "highz0", HIGHZ0 },
 { "highz1", HIGHZ1 },
 { "if", IF },
 { "ifnone", IFNONE }, 
 { "import", IMPORT },
 { "initial", INITial },
 { "inout", INOUT },
 { "input", INPUT },
 { "int", INT },
 /* not int32 */
 { "integer", INTEGER },
 { "join", JOIN },
 { "large", LARGE },
 { "localparam", LOCALPARAM },
 { "logic", LOGIC },
 { "longint", LONGINT },
 { "macromodule", MACROMODULE },
 { "medium", MEDIUM },
 { "module", MODULE },
 { "negedge", NEGEDGE },
 { "output", OUTPUT },
 { "parameter", PARAMETER },
 { "posedge", POSEDGE },
 { "primitive", PRIMITIVE },
 { "pull0", PULL0 },
 { "pull1", PULL1 },
 { "pure", PURE },
 { "real", REAL },
 { "realtime", REALTIME },
 { "reg", REG },
 { "release", RELEASE },
 { "repeat", REPEAT },
 { "return", RETURN },
 { "scalared", SCALARED },
 { "shortint", SHORTINT },
 { "shortreal", SHORTREAL },
 { "signed", SIGNED },
 { "small", SMALL },
 { "specify", SPECIFY },
 { "specparam", SPECPARAM },
 { "strength", Strength },
 { "string", STRING },
 { "strong0", STRONG0 },
 { "strong1", STRONG1 },
 { "supply0", SUPPLY0 },
 { "supply1", SUPPLY1 },
 { "table", TABLE },
 { "task", TASK },
 { "time", TIME },
 { "tri", TRI },
 { "tri0", TRI0 },
 { "tri1", TRI1 },
 { "triand", TRIAND },
 { "trior", TRIOR },
 { "trireg", TRIREG },
 { "unsigned", UNSIGNED },
 { "vectored", VECTORED },
 { "void", VOID },
 { "wait", WAIT },
 { "wand", WAND },
 { "weak0", WEAK0 },
 { "weak1", WEAK1 },
 { "while", WHILE },
 { "wire", WIRE },
 { "wor", WOR }
};
#define SVNKEYWDS (sizeof(svkeywds) / sizeof(struct vkeywds_t))

/*
 * determine type of keyword or ident
 * binary search because the table is so big
 */
static int32 get_vkeywrd(char *tstr)
{
 int32 l, h;
 int32 m, cv;

 /* AIV 08/25/10 - if using the new system verilog keywords with -sv switch */
 /* search larger SV keyword table */
 if (__sv_parse)
  {
   l = 0; h = SVNKEYWDS - 1;
   for (;;)
    {
     m = (l + h)/2;
     if ((cv = strcmp(svkeywds[m].vknam, tstr)) == 0) return(svkeywds[m].vknum);
     if (cv < 0) l = m + 1; else h = m - 1;
     if (h < l) break;
    }
  }
 else
  {
   l = 0; h = NVKEYWDS - 1;
   for (;;)
    {
     m = (l + h)/2;
     if ((cv = strcmp(vkeywds[m].vknam, tstr)) == 0) return(vkeywds[m].vknum);
     if (cv < 0) l = m + 1; else h = m - 1;
     if (h < l) break;
    }
  }
 return(ID);
}

/*
 * determine keyword name from number
 * must use linear search since not sorted
 */
extern char *__get_vkeynam(char *s, int32 knum)
{
 int32 vi;

 for (vi = 0; vi < NVKEYWDS; vi++)
  {
   if (vkeywds[vi].vknum == knum)
   {
    strcpy(s, vkeywds[vi].vknam);
    return(s);
   }
  }
 strcpy(s, "--none--");
 return(s);
}

/*
 * ROUTINES FOR RESYNCING AFTER ERROR
 */

/*
 * skip to symbol - if not found only end module/primitive ends
 * rest of module not checked
 * return T if found targ1 else F
 */
extern int32 __vskipto_modend(int32 targ1)
{
 int32 sav_letendnum;

 /* SJM 11/30/04 - save and restore edge illegal num errors when skip mod */
 sav_letendnum = __letendnum_state;
 __letendnum_state = TRUE;
 /* AIV 06/01/11 - need to set this flag to true is used to check for (* */
 /* between always (* and attribute - was complaing about always (* */
 /* during -v module skipping */
 __canbe_impl_evctrl = TRUE; 
 for (;;)
  {
   if (__toktyp == targ1)
    {
     __letendnum_state = sav_letendnum;
     __canbe_impl_evctrl = FALSE; 
     return(TRUE);
    }
   switch ((byte) __toktyp) {
    case ENDMODULE: case ENDPRIMITIVE:
     goto done;
    case PRIMITIVE: case MODULE: case MACROMODULE:
     __unget_vtok(); goto done;
   }
   if (__toktyp == TEOF)
    __fterr(315, "unexpected EOF while skipping to %s", __prt2_vtok(targ1));
   __get_vtok();
  }
done:
 __letendnum_state = sav_letendnum;
 __canbe_impl_evctrl = FALSE; 
 return(FALSE);
}

/*
 * skip to 2 symbols - if not found only end module/primitive ends
 * rest of module not checked
 * return T if found targ1 else F
 */
extern int32 __vskipto2_modend(int32 targ1, int32 targ2)
{
 int32 sav_letendnum;

 /* SJM 11/30/04 - save and restore edge illegal num errors when skip mod */
 sav_letendnum = __letendnum_state;
 __letendnum_state = TRUE;
 /* AIV 06/01/11 - need to set this flag to true is used to check for (* */
 /* between always (* and attribute - was complaing about always (* */
 /* during -v module skipping */
 __canbe_impl_evctrl = TRUE; 
 for (;;)
  {
   if (__toktyp == targ1 || __toktyp == targ2)
    {
     __letendnum_state = sav_letendnum;
     __canbe_impl_evctrl = FALSE; 
     return(TRUE);
    }
   switch ((byte) __toktyp) {
    case ENDMODULE: case ENDPRIMITIVE:
     goto done;
    case PRIMITIVE: case MODULE: case MACROMODULE:
    __unget_vtok();
    goto done;
   }
   if (__toktyp == TEOF)
    __fterr(315, "unexpected EOF while skipping to %s", __prt2_vtok(targ1));
   __get_vtok();
  }
done:
 __letendnum_state = sav_letendnum;
 __canbe_impl_evctrl = FALSE; 
 return(FALSE);
}

/*
 * skip to 3 symbols - if not found only end module/primitive ends
 * est of module not checked
 * return T if found targ1 else F
 */
extern int32 __vskipto3_modend(int32 targ1, int32 targ2, int32 targ3)
{
 int32 sav_letendnum;

 /* SJM 11/30/04 - save and restore edge illegal num errors when skip mod */
 sav_letendnum = __letendnum_state;
 __letendnum_state = TRUE;
 /* AIV 06/01/11 - need to set this flag to true is used to check for (* */
 /* between always (* and attribute - was complaing about always (* */
 /* during -v module skipping */
 __canbe_impl_evctrl = TRUE; 
 for (;;)
  {
   if (__toktyp == targ1 || __toktyp == targ2 || __toktyp == targ3)
    {
     __letendnum_state = sav_letendnum;
     __canbe_impl_evctrl = FALSE; 
     return(TRUE);
    }
   switch ((byte) __toktyp) {
    case ENDMODULE: case ENDPRIMITIVE:
     goto done;
    case PRIMITIVE: case MODULE: case MACROMODULE:
     __unget_vtok();
     goto done;
   }
   if (__toktyp == TEOF)
    __fterr(315, "unexpected EOF while skipping to %s", __prt2_vtok(targ1));
   __get_vtok();
  }
done:
 __letendnum_state = sav_letendnum;
 __canbe_impl_evctrl = FALSE; 
 return(FALSE);
}

/*
 * skip to any start of stmt/item symbol
 * general sync algorithm.
 *
 * if finds specific thing, return T
 * else sets syncto_class and return F
 *
 * possibilities are:
 *   SYNC_FLEVEL - file level mod/prim
 *   SYNC_MODLEVEL - module level declaration or item
 *   SYNC_STMT - start of statement
 *   SYNC_TARG - target found and return T
 */
extern int32 __vskipto_any(int32 targ1)
{
 /* for interactive just give up on any error - but must skip to end of line */
 if (__iact_state) longjmp(__iact_jmpbuf, 1);

 for (;;)
  {
   if (__toktyp == targ1) { __syncto_class = SYNC_TARG; return(TRUE); }
   if (set_syncto_tokclass(__toktyp)) break;
   if (__toktyp == TEOF)
    __fterr(315, "unexpected EOF while skipping to statement token %s",
     __prt2_vtok(targ1));
   __get_vtok();
  }
 return(FALSE);
}

extern int32 __vskipto2_any(int32 targ1, int32 targ2)
{
 if (__iact_state) longjmp(__iact_jmpbuf, 1);
 for (;;)
  {
   if (__toktyp == targ1 || __toktyp == targ2)
    { __syncto_class = SYNC_TARG; return(TRUE); }
   if (set_syncto_tokclass(__toktyp)) break;
   if (__toktyp == TEOF)
    __fterr(315, "unexpected EOF while skipping to statement token %s",
     __prt2_vtok(targ1));
   __get_vtok();
  }
 return(FALSE);
}

extern int32 __vskipto3_any(int32 targ1, int32 targ2, int32 targ3)
{
 if (__iact_state) longjmp(__iact_jmpbuf, 1);
 for (;;)
  {
   if (__toktyp == targ1 || __toktyp == targ2 || __toktyp == targ3)
    { __syncto_class = SYNC_TARG; return(TRUE); }
   if (set_syncto_tokclass(__toktyp)) break;
   if (__toktyp == TEOF)
    __fterr(315, "unexpected EOF while skipping to statement token %s",
     __prt2_vtok(targ1));
   __get_vtok();
  }
 return(FALSE);
}

extern int32 __vskipto4_any(int32 targ1, int32 targ2, int32 targ3, int32 targ4)
{
 if (__iact_state) longjmp(__iact_jmpbuf, 1);
 for (;;)
  {
   if (__toktyp == targ1 || __toktyp == targ2 || __toktyp == targ3
    || __toktyp == targ4)
    { __syncto_class = SYNC_TARG; return(TRUE); }
   if (set_syncto_tokclass(__toktyp)) break;
   if (__toktyp == TEOF)
    __fterr(315, "unexpected EOF while skipping to statement token %s",
     __prt2_vtok(targ1));
   __get_vtok();
  }
 return(FALSE);
}

/*
 * skip to end of list of port port decl element
 *
 * special case because resyncs at port name keyword ID 
 * notice can't be used for new list of parameters form
 */
extern int32 __vskipto_lofp_end()
{
 /* only for list of ports decl so can't be invoked from iact state */ 
 if (__iact_state) __misc_terr(__FILE__, __LINE__);

 for (;;)
  {
   /* semi can end because end of list ) always followed by ; */
   if (__toktyp == INPUT || __toktyp == OUTPUT || __toktyp == INOUT
    || __toktyp == RPAR || __toktyp == SEMI)
    { __syncto_class = SYNC_TARG; return(TRUE); }
   if (set_syncto_tokclass(__toktyp)) break;
   if (__toktyp == TEOF)
    __fterr(315,
     "unexpected EOF while skipping over list of port declaration");
   __get_vtok();
  }
 return(FALSE);
}

/*
 * skip to end of list of port port decl element from inside port name comma
 * list
 *
 * special case because resyncs at port name keyword ID 
 * notice can't be used for new list of parameters form
 */
extern int32 __vskipto2_lofp_end()
{
 /* only for list of ports decl so can't be invoked from iact state */ 
 if (__iact_state) __misc_terr(__FILE__, __LINE__);

 for (;;)
  {
   /* semi can end because end of list ) always followed by ; */
   if (__toktyp == INPUT || __toktyp == OUTPUT || __toktyp == INOUT
    || __toktyp == RPAR || __toktyp == SEMI || __toktyp == COMMA)
    { __syncto_class = SYNC_TARG; return(TRUE); }

   if (set_syncto_tokclass(__toktyp)) break;

   if (__toktyp == TEOF)
    __fterr(315,
     "unexpected EOF while skipping over list of port declaration");
   __get_vtok();
  }
 return(FALSE);
}

/*
 * set __token class - return T if not a sync to
 */
static int32 set_syncto_tokclass(int32 ttyp) 
{
 switch (ttyp) {
  /* file level item */
  case ENDMODULE: case ENDPRIMITIVE:
   __syncto_class = SYNC_FLEVEL;
   break;
  case PRIMITIVE: case MODULE: case MACROMODULE:
   __unget_vtok();
   __syncto_class = SYNC_FLEVEL;
   break;
  /* module item end - must assume next things is good item */
  /* because [id] [type](inst) is common */
  case ENDFUNCTION: case ENDTASK: case ENDSPECIFY: case AUTOMATIC:
   __syncto_class = SYNC_MODLEVEL;
   break;
  case INITial: case ALWAYS:
  case ALWAYS_COMB: case ALWAYS_FF: case ALWAYS_LATCH:
  case DEFPARAM: case SPECIFY: case TASK: case FUNCTION: 
  case PARAMETER: case LOCALPARAM: case ASSIGN:
  case INPUT: case OUTPUT: case INOUT:
  case WIRE: case TRI: case TRI0: case TRI1: case TRIAND: 
  case TRIOR: case TRIREG: case WAND: case WOR: case SUPPLY0:
  case SUPPLY1: case REG: case INTEGER: case TIME: case REAL: case REALTIME:
  case EVENT: case LOGIC:
   __unget_vtok();
   __syncto_class = SYNC_MODLEVEL;
   break;
  /* stmt begin things - sync so next get tok will be stmt start */
  /* these are likely module item previous ends and assume so */
  /* but could be part of wrong list of stmts */
  /* SJM 01/14/1999 - moved else from statement start case to stmt end */
  /* LOOKATME - is there a problem with this? */
  case END: case JOIN: case ENDCASE: case ELSE:
   __syncto_class = SYNC_STMT;
   break;
  case SHARP: case AT:
  case IF: case IFNONE: case CASE: case CASEX: case CASEZ:
  case Begin: case FORK: case CAUSE:
  case FOREVER: case REPEAT: case WHILE: case FOR: case WAIT:
  case DISABLE: case FORCE: case RELEASE:
   __unget_vtok();
   __syncto_class = SYNC_STMT;
   break;
  default: return(FALSE);
 } 
 return(TRUE);
}

/*
 * for specify normal skip to any except also specify item level
 */
extern int32 __spec_vskipto_any(int32 targ1)
{
 for (;;)
  {
   if (__toktyp == targ1) { __syncto_class = SYNC_TARG; return(TRUE); }
   if (set_syncto_tokclass(__toktyp))
    { 
     if (__toktyp == IF) __syncto_class = SYNC_SPECITEM;
     break;
    }
   if (set_specitem_class()) break;
   if (__toktyp == TEOF)
    __fterr(315, "unexpected EOF while skipping to statement token %s",
     __prt2_vtok(targ1));
   __get_vtok();
  }
 return(FALSE);
}

extern int32 __spec_vskipto2_any(int32 targ1, int32 targ2)
{
 for (;;)
  {
   if (__toktyp == targ1 || __toktyp == targ2)
    { __syncto_class = SYNC_TARG; return(TRUE); }
   if (set_syncto_tokclass(__toktyp))
    { 
     if (__toktyp == IF) __syncto_class = SYNC_SPECITEM;
     break;
    }
   if (set_specitem_class()) break;
   if (__toktyp == TEOF)
    __fterr(315, "unexpected EOF while skipping to statement token %s",
     __prt2_vtok(targ1));
   __get_vtok();
  }
 return(FALSE);
}

extern int32 __spec_vskipto3_any(int32 targ1, int32 targ2, int32 targ3)
{
 for (;;)
  {
   if (__toktyp == targ1 || __toktyp == targ2 || __toktyp == targ3)
    { __syncto_class = SYNC_TARG; return(TRUE); }
   if (set_syncto_tokclass(__toktyp))
    { 
     if (__toktyp == IF) __syncto_class = SYNC_SPECITEM;
     break;
    }
   if (set_specitem_class()) break;
   if (__toktyp == TEOF)
    __fterr(315, "unexpected EOF while skipping to statement token %s",
     __prt2_vtok(targ1));
   __get_vtok();
  }
 return(FALSE);
}

/*
 * set specify level for token that can begin specify section
 * returns T if found sync to place
 * this needs to access global toktyp and token 
 * notice - cannot sync to most common ( for path start
 */
static int32 set_specitem_class(void)
{
 if (__toktyp == ID && *__token == '$')
  {
   if (__fr_tcnam(__token) != -1)
    {
     __unget_vtok();
     __syncto_class = SYNC_SPECITEM;
     return(TRUE);
    } 
  }
 return(FALSE);
}

/*
 * skip to udp symbol
 */
/*
 * skip to udp symbol - 
 * return T if found targ1 else F
 */
extern int32 __udp_vskipto_any(int32 targ1)
{
 for (;;)
  {
   if (__toktyp == targ1) { __syncto_class = SYNC_TARG; return(TRUE); }
   if (set_udpsyncto(__toktyp)) break;
   if (__toktyp == TEOF)
    __fterr(315, "unexpected EOF while skipping to %s", __prt2_vtok(targ1));
   __get_vtok();
  }
 return(FALSE);
}

extern int32 __udp_vskipto2_any(int32 targ1, int32 targ2)
{
 for (;;)
  {
   if (__toktyp == targ1 || __toktyp == targ2)
    { __syncto_class = SYNC_TARG; return(TRUE); }
   if (set_udpsyncto(__toktyp)) break;
   if (__toktyp == TEOF)
    __fterr(315, "unexpected EOF while skipping to %s", __prt2_vtok(targ1));
   __get_vtok();
  }
 return(FALSE);
}

extern int32 __udp_vskipto3_any(int32 targ1, int32 targ2, int32 targ3)
{
 for (;;)
  {
   if (__toktyp == targ1 || __toktyp == targ2 || __toktyp == targ3)
    { __syncto_class = SYNC_TARG; return(TRUE); }
   if (set_udpsyncto(__toktyp)) break;
   if (__toktyp == TEOF)
    __fterr(315, "unexpected EOF while skipping to %s", __prt2_vtok(targ1));
   __get_vtok();
  }
 return(FALSE);
}

/*
 * set udp token class - return T if token not a sync to
 */
static int32 set_udpsyncto(int32 ttyp) 
{
 switch (ttyp) {
  /* file level item */
  case ENDMODULE: case ENDPRIMITIVE:
   __syncto_class = SYNC_FLEVEL;
   break;
  case PRIMITIVE: case MODULE: case MACROMODULE:
   __unget_vtok();
   __syncto_class = SYNC_FLEVEL;
   break;
 /* SJM 07-31-10 - notice sv udps do not allow new logic synonym for reg */
  case INPUT: case OUTPUT: case REG: case TABLE:
   __unget_vtok();
   __syncto_class = SYNC_UDPLEVEL;
   break;
  default: return(FALSE);
 }
 return(TRUE);
}

/*
 *  LIB. INPUT ROUTINES
 *  BEWARE - must open file, use all, close file before using other get func.
 */

/*
 * ascii character table for processing ID tokens
 * 0 - continue, 1 - end and don't back up, 2 - end and back up
 * notice here any non white space contiguous chars good since can be path
 */
static char __lbctab[128] = {
 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 0, 1, 1, 0, 0,  /* ^i,\n,\f \r */
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  /* sp */
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2   /* eof */
};

/*
 * get a -f file option token - only white space and semi separation
 * (modified from yylex in "The Unix Programming Environment" p. 337)
 * notice no push back token here
 * also handles normal / * and // comments
 */
extern int32 __get_cmdtok(FILE *f)
{
 /* the char must be an int32 for machine independence */
 int32 c;
 char *cp;
 int32 namlen;

again:
 while ((c = getc(f)) == ' ' || c == '\t' || c == '\f' || c == '\r') ;
 /* SJM 12/06/03 - only new line needs line cnt inc and pushed back */
 if (c == '\n') { __lin_cnt++; goto again; }

 /* // or / * comments legal */
 if (c == '/') if (get_cmdcomment(f)) goto again;

 /* get here by falling through case */
 for (cp = __token, namlen = 0;;)
  {
   if (++namlen >= IDCHARS - 1)
    __pv_ferr(919,
     "command option token too long (%d) - ignored", IDCHARS - 1);

   *cp++ = c;
   if ((c = getc(f)) == EOF) return(TEOF);
   switch (__lbctab[c & 0x7f]) {
    case 0: continue;         /* normal in ID char */
    case 1: goto end_nam;     /* white space token end - swallow it */
    /* or lin_cnt wrong for errors */
    case 2: ungetc(c, f); goto end_nam; /* non white space end token */
   }
  }
end_nam:
 *cp = '\0';
 /* does not need canonical token since not related to output */
 /* Verilog world options are case sensitive */
 return(ID);
}

/*
 * ascii character table for processing config tokens
 * 0 - continue, 1 - end and don't back up, 2 - end and back up
 * notice here any non white space contiguous chars good since can be path
 */
static char cfgctab[128] = {
 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 0, 1, 1, 0, 0,  /* ^i,\n,\f \r */
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0,  /* sp, , */
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0,  /* ; */
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2   /* eof */
};

/*
 * get a cfg -L or default map.lib file token 
 * (modified from yylex in "The Unix Programming Environment" p. 337)
 * AIV 10/30/03 - added for new 2001 cfg feature
 *
 * notice no push back token here and tok typ glb not set
 * also handles normal / * and // comments
 *
 * allowing ' and " quotes and back slash escaping of quotes in quoted
 * strings but not allowing embedded new lines in tokens
 * 
 * complicated because need warnings and must handle quoting and
 * escaping but only within quoted names 
 */
extern int32 __get_cfgtok(FILE *f)
{
 /* the char must be an int32 for machine independence */
 int32 c;
 char *cp;
 int32 namlen, ttyp, qchar;

again:
 while ((c = getc(f)) == ' ' || c == '\t' || c == '\f' || c == '\r') ;
 /* SJM 12/06/03 - only new line needs line cnt inc and pushed back */
 if (c == '\n') { __lin_cnt++; goto again; }
 /* AIV since push back ; if ';' */
 if (c == ';') return(CFG_SEMI);
 if (c == ',') return(CFG_COMMA);
 /* // or / * comments legal */
 if (c == '/') if (get_cmdcomment(f)) goto again;

 if (c == '\'' || c == '"')
  {
   qchar = c;
   c = getc(f);
   /* get here by falling through case */
   for (cp = __token, namlen = 0;;)
    {
     if (++namlen >= IDCHARS - 1)
      {
       __pv_ferr(919,
        "config file token (path?) too long (%d) - rest discarded",
        IDCHARS - 1);
       for (;;)
        {
         if (c == '\\') { c = getc(f); continue; }
         if (c == qchar) break;
         if (c == EOF) return(CFG_EOF);
         c = getc(f);
        }
       *cp = '\0';
       return(CFG_ID);
      }
     /* escaped chars legal but only in quoted strings */
     if (c == '\\')
      {
       c = getc(f);
       if (c == EOF) return(CFG_EOF);
       *cp++ = c;
      }
     else
      {
       /* ending quote not part of ID and can't be key word32 */
       if (c == qchar)
        {
         if (strcmp(__token, "") == 0)
          {
           __pv_fwarn(3125, "quoted map library token empty string");
          }
         break;
        }
      } 
     if (c == '\n')
      {
       if (strcmp(__token, "") == 0)
        {
         __pv_fwarn(3126,
          "quoted map library token contains embedded new line");
        }
      }
     *cp++ = c;
     c = getc(f);
    }
   *cp = '\0';
   return(CFG_ID);
  }

 /* get here by falling through case */
 for (cp = __token, namlen = 0;;)
  {
   if (++namlen >= IDCHARS - 1)
    __pv_ferr(919,
     "config file token (path?) too long (%d) - rest discarded", IDCHARS - 1);

   *cp++ = c;
   if ((c = getc(f)) == EOF) { __toktyp = CFG_EOF; return(CFG_EOF); }
   switch (cfgctab[c & 0x7f]) {
    case 0: continue;         /* normal in ID char */
    case 1: goto end_nam;     /* white space token end - swallow it */
    case 2: ungetc(c, f); goto end_nam; /* non white space end token */
   }
  }
end_nam:
 *cp = '\0';
 ttyp = get_cfgkeywrd(__token);
 return(ttyp);
}

/*
 * look up a cfg file ID and convert to a keyword NUMBER
 *
 * notice keyword numbers disjoint32 from and overlap Verilog keywords 
 * FIXME - should use binary search
 */
static int32 get_cfgkeywrd(char *tstr)
{
 if (strcmp(tstr, "library") == 0) return(CFG_LIBRARY);
 if (strcmp(tstr, "config") == 0) return(CFG_CFG);
 if (strcmp(tstr, "design") == 0) return(CFG_DESIGN);
 if (strcmp(tstr, "liblist") == 0) return(CFG_LIBLIST);
 if (strcmp(tstr, "instance") == 0) return(CFG_INSTANCE);
 if (strcmp(tstr, "cell") == 0) return(CFG_CELL);
 if (strcmp(tstr, "use") == 0) return(CFG_USE);
 if (strcmp(tstr, "endconfig") == 0) return(CFG_ENDCFG);
 if (strcmp(tstr, "default") == 0) return(CFG_DEFAULT);
 return(CFG_ID);
}

/*
 * convert cfg toktyp number to name
 */
extern char *__to_cfgtoknam(char *s, int32 ttyp)
{ 
 switch (ttyp) {
  case CFG_UNKNOWN: strcpy(s, "??CFG-UNKNOWN??"); break;
  case CFG_ID: strcpy(s, __token); break;
  case CFG_COMMA: strcpy(s, ","); break;
  case CFG_SEMI: strcpy(s, ";"); break;
  case CFG_EOF: strcpy(s, "**CFG EOF**"); break;
  case CFG_LIBRARY: strcpy(s, "library"); break;
  case CFG_CFG: strcpy(s, "config"); break;
  case CFG_INCLUDE: strcpy(s, "include"); break;
  case CFG_DESIGN: strcpy(s, "design"); break;
  case CFG_LIBLIST: strcpy(s, "liblist"); break;
  case CFG_INSTANCE: strcpy(s, "instance"); break;
  case CFG_CELL: strcpy(s, "cell"); break;
  case CFG_USE: strcpy(s, "use"); break;
  case CFG_ENDCFG: strcpy(s, "endconfig"); break; 
  case CFG_DEFAULT: strcpy(s, "default"); break;
  default: __case_terr(__FILE__, __LINE__);
 }
 return(s);
}

/*
 * get a comment
 */
static int32 get_cmdcomment(FILE *f)
{
 int32 c;
 int32 c2;

 /* // to EOL comment */
 if ((c2 = getc(f)) == '/')
  {
   while ((c = getc(f)) != '\n') if (c == EOF) { ungetc(c, f); return(TRUE); }
   ungetc(c, f);
   return(TRUE);
  }
 /* slash-star comments don't nest */
 if (c2 == '*')
  {
more_comment:
   while ((c = getc(f)) != '*')
    {
     if (c == EOF) { ungetc(c, f); return(TRUE); }
     if (c == '\n') __lin_cnt++;
     if (c == '/')
      {
       if ((c2 = getc(f)) == '*')
        {
#ifndef __CVC_RT__
         __pv_fwarn(622, "nested /* in /* style -f argument file comment");
#endif
         continue;
        }
       c = c2;
      }
    }

got_star:
   if ((c = getc(f)) == '/') return(TRUE);
   if (c == '*') goto got_star;
   if (c == '\n') __lin_cnt++;
   goto more_comment;
  }
 /* / not followed by / or * so put back and return SLASH token */
 ungetc(c2, f);
 return(FALSE);
}

/*
 * SYMBOL TABLE ROUTINES
 */

/*
 * find symbol (name) in normal t/f/lb scope, then gen blk scopes,
 * then top level module (know gen scope hierachy always at mod item level)
 *
 * SJM 12-11-12 - new generate algorithnm - now in v_src and v_src2 when
 * looking for variable in evironment nested scope - first go up task/func/lb
 * scopes until hit module level scope then before searching in module level,
 * search upward in gen blk scopes
 *
 * this routine can't be used for non initial source read scopes that
 * use scope tskp
 */
extern struct sy_t *__in_gen_scopes_get_sym_env(char *nam)
{
 int32 sti;
 struct sy_t *syp;
 struct symtab_t *sytp;

 /* SJM 12-15-08 if no current gen blk context just use norm get sym env */
 if (__cur_cntxt_gblk == NULL) return(__get_sym_env(nam));

 /* DBG remove -- */
 if (__iact_state) __misc_terr(__FILE__, __LINE__);
 /* --- */

 /* first serach venviron until hit module sym tab - better be 0 */
 for (sti = __top_sti; sti >= 0; sti--)
  {
   sytp = __venviron[sti];
   /* SJM 04-13-10 - for decl of task in gen scope may be no syp of sym tab */
   /* yet because task may never be generated */
   if (sytp->sypofsyt == NULL)
    {
     /* SJM 05-18-11 - gblk parent symtabs not yet linked because gen blk */
     /* may never make it into src, but within nested gblks v envion right */
     /* DBG remove -- */
     if (sytp->gblkofsyt == NULL) __misc_terr(__FILE__, __LINE__);
     /* --- */
     if ((syp = __get_sym(nam, sytp)) != NULL) return(syp);
     continue;
    }
   if (sytp->sypofsyt->sytyp == SYM_M)
    {
     /* DBG remove -- */
     if (sti != 0) __misc_terr(__FILE__, __LINE__);
     /* --- */
     goto found_mod;
    }
   if ((syp = __get_sym(nam, sytp)) != NULL) return(syp);
  }
 /* SJM 05-18-11 know must hit the known mod environ */
 /* DBG remove -- */
 __misc_terr(__FILE__, __LINE__);
 /* -- */

found_mod:
 /* DBG remove -- */
 if (sti != 0) __misc_terr(__FILE__, __LINE__);
 /* --- */
 /* finally search mod level symbol table */
 if ((syp = __get_sym(nam, __venviron[0])) != NULL) return(syp);
 return(NULL);
}

/*
 * locate a currently accessible symbol - for non path qualified names
 * use __find_sym if needs to be addded when not found
 * notice this works for frozen symbol tables since get sym determines type
 *
 * LOOKATME - could make variable routine if if in this inner loop to slow
 */
extern struct sy_t *__get_sym_env(char *nam)
{
 int32 sti;
 struct sy_t *syp;
 struct symtab_t *sytp;
 struct mod_t *mdp;

 /* LOOKATME - special convenience variable symbol table could go here */
 if (!__iact_state)
  {
   for (sti = __top_sti; sti >= 0; sti--)
    {
     sytp = __venviron[sti];
     if ((syp = __get_sym(nam, sytp)) != NULL) return(syp);
    }
   return(NULL);
  }

 if (__scope_tskp == NULL)
  {
   mdp = (struct mod_t *) __scope_idp[MD_MDP];
   __last_iasytp = mdp->msymtab;
  }
 else __last_iasytp = __scope_tskp->tsksymtab;
 /* know parent of task is top level module instance and of module is nil */
 for (; __last_iasytp != NULL; __last_iasytp = __last_iasytp->sytpar)
  { if ((syp = __get_sym(nam, __last_iasytp)) != NULL) return(syp); }
 return(NULL);
}

/*
 * find a symbol (will add SYM_UNKN symbol if needed)
 * if needs to be implicit wire decl. caller must add and set net
 */
extern struct sy_t *__find_sym(char *nam)
{
 int32 sti;
 struct sy_t *syp;
 struct tnode_t *tnp;
 struct symtab_t *sytp;

 /* top module level is lowest in task/function symbol table stack */
 for (sti = __top_sti; sti >= 0; sti--)
  {
   sytp = __venviron[sti];
   if ((syp = __get_sym(nam, sytp)) != NULL)
    { __sym_is_new = FALSE; return(syp); }
  }
 sytp = __venviron[__top_sti];
 tnp = __vtfind(nam, sytp);
 /* know symbol will be new */
 /* allocate symbol and fill symbol */
 __add_sym(nam, tnp);
 (__venviron[__top_sti]->numsyms)++;
 syp = tnp->ndp;
 return(syp);
}

/*
 * declare a symbol - caller determines where declared
 *
 * this is used to add sym to symbol table - sydecl not set
 * when real source declaration (maybe implicit) sydecl set
 */
extern struct sy_t *__decl_sym(char *nam, struct symtab_t *sytp)
{
 struct sy_t *syp;
 struct tnode_t *tnp;

 if ((syp = __get_sym(nam, sytp)) != NULL)
  { __sym_is_new = FALSE; return(syp); }
 tnp = __vtfind(nam, sytp);
 /* allocate symbol and fill symbol */
 __add_sym(nam, tnp);
 (sytp->numsyms)++;
 return(tnp->ndp);
}

/*
 * add a symbol, caller must fill and set type
 * expects symbol tree node to be inserted in avl tree and passed here
 * symbol always added to symbol table on top of module/task nesting stack
 */
extern void __add_sym(char *snam, struct tnode_t *tnp)
{
 struct sy_t *syp;

 syp = (struct sy_t *) __my_malloc(sizeof(struct sy_t));
 tnp->ndp = syp;
 __init_sy(syp);
 syp->synam = pv_stralloc2(snam);
}

/*
 * allocate a string from a big block
 * this must allocate the 1 char null string for `define as flag
 */
static char *pv_stralloc2(char *s)
{
 char *cp;
 int32 slen;

 if (*s == '\0') slen = 1; else slen = strlen(s) + 1;
 cp = nfbig_alloc(slen);
 __memstr_use += slen;
 /* this just copies '\0' for "" case */
 strcpy(cp, s);
 return(cp);
}

/*
 * initialize a symbol
 * requires set current file and line number
 */
extern void __init_sy(struct sy_t *syp)
{
 syp->synam = NULL;
 syp->sytyp = SYM_UNKN;
 /* notice all symbols add during input phase */
 syp->sydecl = FALSE;
 syp->syundefmod = FALSE;
 syp->cfg_needed = FALSE;
 syp->sy_impldecl = FALSE;
 syp->sy_argsmac = FALSE;
 syp->sy_giabase = FALSE;
 syp->sy_gia_added = FALSE;
 syp->sy_in_genblk = FALSE;
 syp->gen_add_mstab = FALSE;
 syp->gen_net_impldecl = FALSE;
 syp->el.enp = NULL;
 syp->syfnam_ind = __cur_fnam_ind;
 syp->sylin_cnt = __lin_cnt;
 syp->spltsy = NULL;
}

/*
 * BALANCED TREE ACCESS ROUTINES NETS
 * MUST GO HERE BECAUSE GLOBALS USE FIND_NET MECHANISM
 */

/*
 * search one symbol table and if found return sym node
 * call __vtfind if need to add if not found
 */
extern struct sy_t *__get_sym(char *nam, struct symtab_t *sytp)
{
 struct tnode_t *cur;
 int32 cv;

 /* interactive bld node accesses frozen symbol table */
 if (sytp->stsyms != NULL)
  return(__zget_sym(nam, sytp->stsyms, sytp->numsyms));

 /* FIXME - SJM - 09/16/99 when copied n_head may be non nil for empty tab */
 if (sytp->n_head == NULL || sytp->numsyms == 0) return(NULL);
 for (cur = sytp->n_head;;)
  {
   if ((cv = strcmp(nam, cur->ndp->synam)) == 0) return(cur->ndp);
   if ((cur = (cv < 0) ? cur->lp : cur->rp) == NULL) break;
  }
 return(NULL);
}

/*
 * special vpi/sdf version of get sym that fails for g/i array base name
 *
 * LOOKATME - change this if allowing vpi_ access to arrays of gates/insts
 */
extern struct sy_t *__get_nongia_sym(char *nam, struct symtab_t *sytp)
{
 struct sy_t *syp;

 if ((syp = __get_sym(nam, sytp)) == NULL) return(NULL);
 if (syp->sy_giabase) return(NULL);
 return(syp);
}

/*
 * find an entry in symbol node tree and add if needed
 * expects caller to connect in sy_t and fill it
 *
 * SJM 03-14-09 - notice sym is new glb always set
 */
extern struct tnode_t *__vtfind(char *nam, struct symtab_t *sytp)
{
 struct tnode_t *cur, *down;
 struct tnode_t *balpt_par, *bal_pt, *vtnew, *bal_down;
 int32 cv;

 /* DBG remove --
 if (sytp->stsyms != NULL) __misc_terr(__FILE__, __LINE__);
  --- */

 vtnew = NULL;
 if (sytp->n_head == NULL)
  { sytp->n_head = alloc_tnode(sytp); return(sytp->n_head); }
 for (balpt_par = NULL, bal_pt = cur = sytp->n_head;;)
  {
   if ((cv = strcmp(nam, cur->ndp->synam)) == 0)
    { __sym_is_new = FALSE; return(cur); }

   if (cv < 0) { cur->via_dir = BLEFT; down = cur->lp; }
   else { cur->via_dir = BRIGHT; down = cur->rp; }
   if (down == NULL)
    {
     down = alloc_tnode(sytp);
     if (cur->via_dir == BLEFT) cur->lp = down; else cur->rp = down;
     vtnew = down;
     break;
    }
   if (down->bal != BEVEN) { balpt_par = cur; bal_pt = down; }
   cur = down;
  }

 /* bal down is one below balance point */
 if (bal_pt->via_dir == BLEFT) bal_down = bal_pt->lp;
 else bal_down = bal_pt->rp;
 /* know all nodes from bal_pt down to but not including new had balance 0 */
 /* adjust up to but not including balance of new */
 for (cur = bal_down; cur != vtnew;)
  {
   cur->bal = cur->via_dir;
   if (cur->via_dir == BLEFT) cur = cur->lp; else cur = cur->rp;
  }
 /* since only unbalanced by 1 put off doing anything */
 if (bal_pt->bal == BEVEN) { bal_pt->bal = bal_pt->via_dir; return(vtnew); }

 /* tree got more balanced */
 /* check for bal and even dir opposite or both even */
 if ((bal_pt->bal == BEVEN && bal_pt->via_dir == BEVEN)
  || (bal_pt->bal == BLEFT && bal_pt->via_dir == BRIGHT)
  || (bal_pt->bal == BRIGHT && bal_pt->via_dir == BLEFT))
  {
   bal_pt->bal = BEVEN;
   return(vtnew);
  }

 __tmp_head = sytp->n_head;
 /* these routines may update global __tmp_head */
 /* tree more out of balance - needs rebalancing */
 if (bal_down->bal == bal_pt->via_dir) one_rot(bal_pt, bal_down, balpt_par);
 else two_rot(bal_pt, bal_down, balpt_par);
 sytp->n_head = __tmp_head;

 return(vtnew);
}

/*
 * single rotation
 */
static void one_rot(struct tnode_t *bal_pt, struct tnode_t *bal_down, 
 struct tnode_t *balpt_par)
{
 if (bal_pt->via_dir == BLEFT)
  {
   bal_pt->lp = bal_down->rp;
   bal_down->rp = bal_pt;
  }
 else
  {
   bal_pt->rp = bal_down->lp;
   bal_down->lp = bal_pt;
  }
 bal_pt->bal = bal_down->bal = BEVEN;

 if (balpt_par == NULL) __tmp_head = bal_down;
 else if (balpt_par->via_dir == BLEFT) balpt_par->lp = bal_down;
 else balpt_par->rp = bal_down;
}

/*
 * double rotation
 */
static void two_rot(struct tnode_t *bal_pt, struct tnode_t *bal_down,
 struct tnode_t *balpt_par)
{
 struct tnode_t *tmp;

 if (bal_pt->via_dir == BLEFT)
  {
   tmp = bal_down->rp;
   bal_down->rp = tmp->lp;
   tmp->lp = bal_down;
   bal_pt->lp = tmp->rp;
   tmp->rp = bal_pt;
  }
 else
  {
   tmp = bal_down->lp;
   bal_down->lp = tmp->rp;
   tmp->rp = bal_down;
   bal_pt->rp = tmp->lp;
   tmp->lp = bal_pt;
  }

 /* update the balances */
 if (tmp->bal == BEVEN) bal_pt->bal = bal_down->bal = BEVEN;
 else if (tmp->bal == bal_pt->via_dir)
  {
   if (bal_pt->via_dir == BRIGHT) bal_pt->bal = BLEFT;
   else if (bal_pt->via_dir == BLEFT) bal_pt->bal = BRIGHT;
   else bal_pt->bal = BEVEN;
   bal_down->bal = BEVEN;
  }
 else { bal_pt->bal = BEVEN; bal_down->bal = bal_pt->via_dir; }
 tmp->bal = BEVEN;

 /* point node above balance point to new high node */
 if (balpt_par == NULL) __tmp_head = tmp;
 else if (balpt_par->via_dir == BLEFT) balpt_par->lp = tmp;
 else balpt_par->rp = tmp;
}

/*
 * allocate a node
 */
static struct tnode_t *alloc_tnode(struct symtab_t *sytp)
{
 struct tnode_t *tnp;
 struct tnblk_t *tnbp; 

 if (!sytp->freezes)
  tnp = (struct tnode_t *) __my_malloc(sizeof(struct tnode_t));
 else
  {
   if (__tnblk_nxti == -1)
    {
     tnbp = (struct tnblk_t *) __my_malloc(sizeof(struct tnblk_t));
     tnbp->tnblks = (struct tnode_t *) __my_malloc(BIG_ALLOC_SIZE);
     tnbp->tnblknxt = __hdr_tnblks;
     __hdr_tnblks = tnbp;
     __tnblk_nxti = 0;
    }
   tnp = (struct tnode_t *) &(__hdr_tnblks->tnblks[__tnblk_nxti]);
   if (++__tnblk_nxti > ((BIG_ALLOC_SIZE/sizeof(struct tnode_t)) - 1))
     __tnblk_nxti = -1;
  }

 tnp->lp = tnp->rp = NULL;
 tnp->bal = BEVEN;
 tnp->via_dir = BEVEN;
 __sym_is_new = TRUE;
 tnp->ndp = NULL;
 return(tnp);
}

/*
 * find a symbol in the current scope
 */

/*
 * get a symbol in frozen table - notice nsyms is num. not last
 */
extern struct sy_t *__zget_sym(char *nam, struct sy_t **syms, word32 nsyms)
{
 int32 l, h, m, cv;

 if (nsyms == 0) return(NULL);
 l = 0; h = nsyms - 1;
 for (;;)
  {
   m = (l + h)/2;
   if ((cv = strcmp(syms[m]->synam, nam)) == 0) return(syms[m]);
   if (cv < 0) l = m + 1; else h = m - 1;
   if (h < l) break;
  }
 return(NULL);
}

/*
 * allocate a new empty symbol table
 */
extern struct symtab_t *__alloc_symtab(int32 freezes)
{
 struct symtab_t *sytp;

 sytp = (struct symtab_t *) __my_malloc(sizeof(struct symtab_t));
 sytp->n_head = NULL;
 sytp->stsyms = NULL;
 sytp->sytpar = NULL;
 sytp->sytsib = NULL;
 sytp->sytofs = NULL;
 sytp->sypofsyt = NULL;
 sytp->gblkofsyt = NULL;
 sytp->linkto_cp_osytp = NULL;
 sytp->numsyms = 0;
 sytp->freezes = freezes;
 return(sytp);
}

/*
 * MISC. REPRESENTATION CHANGE RROUTINES
 */

/*
 * routine to find index in ip table and it roots of top level module 
 *
 * here __top_ipind is sorted array of indexes into top_iptab which
 * is || to __it_roots
 */
extern int32 __ip_indsrch(char *nam)
{
 int32 l, h, m, cv;

 if (__numtopm == 0) return(-1);
 l = 0; h = __numtopm - 1;
 for (;;)
  {
   m = (l + h)/2;
   if ((cv = strcmp(__top_itab[__top_ipind[m]]->imsym->synam, nam)) == 0)
    return(__top_ipind[m]);
   if (cv < 0) l = m + 1; else h = m - 1;
   if (h < l) break;
  }
 return(-1);
}

/*
 * convert an identifier to either global or id name
 */
extern char *__to_idnam(struct expr_t *xp)
{
 char *chp; 

 if (xp->optyp == ID)
  {
   if (xp->locqualnam) return(xp->ru.qnchp); else return(xp->lu.sy->synam);
  }
 else if (xp->optyp == GLBREF) chp = xp->ru.grp->gnam;
 else { chp = NULL;  __case_terr(__FILE__, __LINE__); }
 return(chp);
}

/*
 * convert port name to string - maybe unnamed (chp nil) 
 */
extern char *__to_mpnam(char *s, char *chp)
{
 if (chp == NULL) strcpy(s, "*unnamed*"); else strcpy(s, chp);
 return(s);
}


/*
 * convert from a wire type token number to its wtyp value (-1 if no match)
 */
extern int32 __fr_wtnam(int32 ttyp)
{
 int32 wtyp;

 switch (ttyp) {
  case WIRE: wtyp = N_WIRE; break;
  case TRI: wtyp = N_TRI; break;
  case TRI0: wtyp = N_TRI0; break;
  case TRI1: wtyp = N_TRI1; break;
  case TRIOR: wtyp = N_TRIOR; break;
  case TRIAND: wtyp = N_TRIAND; break;
  case TRIREG: wtyp = N_TRIREG; break;
  case WAND: wtyp = N_WA; break;
  case WOR: wtyp = N_WO; break;
  /* notice pulls never explicitly declared */ 
  case SUPPLY0: wtyp = N_SUPPLY0; break;
  case SUPPLY1: wtyp = N_SUPPLY1; break;
  case REG: wtyp = N_REG; break;
  case LOGIC: wtyp = N_LOGIC; break;
  case TIME: wtyp = N_TIME; break;
  case INTEGER: wtyp = N_INT; break;
  case REAL: case REALTIME: wtyp = N_REAL; break;
  case EVENT: wtyp = N_EVENT; break;
  case BIT: wtyp = N_BIT; break;
  case BYTE: wtyp = N_BYTE; break;
  case INT: wtyp = N_CINT; break;
  case SHORTINT: wtyp = N_SHORTCINT; break;
  case LONGINT: wtyp = N_LONGCINT; break;
  case CHANDLE: wtyp = N_CHANDLE; break;
  case STRING: wtyp = N_STRING; break;
  default: wtyp = -1; break;
 }
 return(wtyp);
}

/*
 * convert a net to its wire type 
 */
extern char *__to_wtnam(char *s, struct net_t *np)
{
 return(__to_wtnam2(s, np->ntyp));
}

/*
 * convert a wire type value into a output name (2nd variant constant wtyp)
 * not for I/O port types
 */
extern char *__to_wtnam2(char *s, word32 typ)
{
 switch (typ) {
  case N_WIRE: strcpy(s, "wire"); break;
  case N_TRI: strcpy(s, "tri"); break;
  case N_TRI0: strcpy(s, "tri0"); break;
  case N_TRI1: strcpy(s, "tri1"); break;
  /* AIV 04/25/09 - these two tri types were wrong */
  case N_TRIOR: strcpy(s, "trior"); break;
  case N_TRIAND: strcpy(s, "triand"); break;
  case N_TRIREG: strcpy(s, "trireg"); break;
  case N_WA: strcpy(s, "wand"); break;
  case N_WO: strcpy(s, "wor"); break;
  case N_SUPPLY0: strcpy(s, "supply0"); break;
  case N_SUPPLY1: strcpy(s, "supply1"); break;

  /* these need special syntax for declaration */
  case N_BIT: strcpy(s, "bit"); break;
  case N_REG: strcpy(s, "reg"); break;
  case N_LOGIC: strcpy(s, "logic"); break;
  case N_CINT: strcpy(s, "int"); break;
  case N_INT: strcpy(s, "integer"); break;

  case N_TIME: strcpy(s, "time"); break;
  case N_REAL: strcpy(s, "real"); break;
  case N_EVENT: strcpy(s, "event"); break;
  case N_BYTE: strcpy(s, "byte"); break;
  case N_SHORTCINT: strcpy(s, "shortint"); break;
  case N_LONGCINT: strcpy(s, "longint"); break;
  case N_CHANDLE: strcpy(s, "chandle"); break;
  case N_STRING: strcpy(s, "string"); break;
  default: __case_terr(__FILE__, __LINE__);
 }
 return(s);
}

/*
 * convert an i/o port type to a name (use lower case for these)
 */
extern char *__to_ptnam(char *s, word32 ptyp)
{
 switch (ptyp) {
  case IO_IN: strcpy(s, "input"); break;
  case IO_OUT: strcpy(s, "output"); break;
  case IO_BID: strcpy(s, "inout"); break;
  case IO_UNKN: strcpy(s, "-unknown-"); break;
  case NON_IO: strcpy(s, "-non-io-"); break;
  default: __case_terr(__FILE__, __LINE__);
 }
 return(s);
}

/*
 * convert a wire splitting type to scalared/vectored state
 */
extern char *__to_splt_nam(char *s, int32 sptyp)
{
 if (sptyp == SPLT_SCAL) strcpy(s, "scalared");
 else if (sptyp == SPLT_VECT) strcpy(s, "vectored");
 else { __case_terr(__FILE__, __LINE__);  strcpy(s,""); }
 return(s);
}

/*
 * convert from a token type number to a strength symbolic constant
 * return NO_STREN on not a strength - checking must be elsewhere
 */
extern word32 __fr_stren_nam(int32 ttyp)
{
 switch (ttyp) {
  case HIGHZ0: case HIGHZ1: return(ST_HIGHZ);
  case SMALL: return(ST_SMALL);
  case MEDIUM: return(ST_MEDIUM);
  case WEAK0: case WEAK1: return(ST_WEAK);
  case LARGE: return(ST_LARGE);
  case PULL0: case PULL1: return(ST_PULL);
  case STRONG0: case STRONG1: return(ST_STRONG);
  case SUPPLY0: case SUPPLY1: return(ST_SUPPLY);
 }
 return(NO_STREN);
}

/*
 * convert a strength pair to a name
 * use this to write cap strength
 */
extern char *__to_stren_nam(char *s, int32 stren1, int32 stren2)
{
 char s1[RECLEN], s2[RECLEN];

 if (__is_capstren(stren1))
  sprintf(s, "(%s)", __to1_stren_nam(s1, stren1, 2));
 else sprintf(s, "(%s, %s)", __to1_stren_nam(s1, stren1, 0),
  __to1_stren_nam(s2, stren2, 1));
 return(s);
}

/*
 * convert a stval coded strength name
 * not for cap. strength
 * and notice value coded in 6 bits (i.e. no value in low 2 bits
 */
extern char *__to_stval_nam(char *s, word32 stval)
{
 int32 st0, st1;
 char s1[RECLEN], s2[RECLEN];

 st0 = (int32) (stval >> 3) & 7;
 st1 = (int32) (stval) & 7;
 sprintf(s, "(%s, %s)", __to1_stren_nam(s1, st0, 0),
  __to1_stren_nam(s2, st1, 1));
 return(s);
}

/*
 * convert from a strength type and 0/1 value to a strength name
 * this is source driving strength - not net strength value
 */
extern char *__to1_stren_nam(char *s, int32 st, int32 st01dir)
{
 switch (st) {
  case ST_HIGHZ: strcpy(s, "highz"); break;
  case ST_SMALL: strcpy(s, "small"); return(s);
  case ST_MEDIUM: strcpy(s, "medium"); return(s);
  case ST_WEAK: strcpy(s, "weak"); break;
  case ST_LARGE: strcpy(s, "large"); return(s);
  case ST_PULL: strcpy(s, "pull"); break;
  case ST_STRONG: strcpy(s, "strong"); break;
  case ST_SUPPLY: strcpy(s, "supply"); break;
  default: __case_terr(__FILE__, __LINE__);
 }
 if (st01dir == 0) strcat(s, "0");
 else if (st01dir == 1) strcat(s, "1");
 return(s);
}

/*
 * return T if strength value is cap. strength
 */
extern int32 __is_capstren(int32 st)
{
 switch (st) {
  case ST_SMALL: case ST_MEDIUM: case ST_LARGE: return(TRUE);
 }
 return(FALSE);
}

/*
 * convert from a capacitor size constant to a capacitor strength 
 */
extern int32 __fr_cap_size(int32 capsiz)
{
 int32 st;

 switch (capsiz) {
  case CAP_NONE: st = ST_STRONG; break;
  case CAP_SMALL: st = ST_SMALL; break;
  case CAP_MED: st = ST_MEDIUM; break;
  case CAP_LARGE: st = ST_LARGE; break;
  default: st = ST_STRONG; __case_terr(__FILE__, __LINE__);
 }
 return(st);
}

/*
 * convert to a capacitor size constant from a capacitor strength 
 * must catch non cap size strength input before here
 */
extern word32 __to_cap_size(int32 st)
{
 int32 capsiz;

 switch (st) {
  case ST_STRONG: capsiz = CAP_NONE; break;
  case ST_SMALL: capsiz = CAP_SMALL; break;
  case ST_MEDIUM: capsiz = CAP_MED; break;
  case ST_LARGE: capsiz = CAP_LARGE; break;
  default: capsiz = CAP_NONE; __case_terr(__FILE__, __LINE__);
 }
 return(capsiz);
}

/*
 * build a $display style 2 char strength string
 */
extern char *__to_dispst_str(char *s, word32 st)
{
 switch (st) {
  case ST_HIGHZ: strcpy(s, "Hi"); break;
  case ST_SMALL: strcpy(s, "Sm"); break;
  case ST_MEDIUM: strcpy(s, "Me"); break;
  case ST_WEAK: strcpy(s, "We"); break;
  case ST_LARGE: strcpy(s, "La"); break;
  case ST_PULL: strcpy(s, "Pu"); break;
  case ST_STRONG: strcpy(s, "St"); break;
  case ST_SUPPLY: strcpy(s, "Su"); break;
  default: __case_terr(__FILE__, __LINE__);
 }
 return(s);
}

/*
 * build a symbol class name
 */
extern char *__to_sytyp(char *s, word32 styp)
{
 switch (styp) {
  case SYM_UNKN: strcpy(s, "--unknown--"); break;
  case SYM_I: strcpy(s, "instance"); break;
  case SYM_M: strcpy(s, "module"); break;
  case SYM_PRIM: strcpy(s, "primitive"); break;
  case SYM_UDP: strcpy(s, "udp define"); break;
  case SYM_N: strcpy(s, "variable"); break;
  case SYM_TSK: strcpy(s, "task"); break;
  case SYM_STSK: strcpy(s, "systask"); break;
  case SYM_LB: strcpy(s, "named block"); break;
  case SYM_F: strcpy(s, "function"); break;
  case SYM_SF: strcpy(s, "sysfunction"); break;
  case SYM_DEF: strcpy(s, "preprocessor `define"); break;
  case SYM_CA: strcpy(s, "continuous assign"); break; 
  case SYM_PTH: strcpy(s, "delay path"); break;
  case SYM_TCHK: strcpy(s, "timing check"); break; 
  case SYM_LGB: strcpy(s, "generate block"); break;
  default: __case_terr(__FILE__, __LINE__);
 }
 return(s);
}

/*
 * build a task type name - tskt is token number
 */
extern char *__to_tsktyp(char *s, word32 tskt)
{
 switch (tskt) {
  case Begin: strcpy(s, "named begin"); break;
  case FORK: strcpy(s, "named fork"); break;
  case FUNCTION: strcpy(s, "function"); break;
  case TASK: strcpy(s, "task"); break;
 }
 return(s);
}

/*
 * build a statement type name
 */
extern char *__to_sttyp(char *s, word32 sttyp)
{
 switch (sttyp) {
  case S_NULL: strcpy(s, "empty"); break;
  case S_STNONE: strcpy(s, "empty block"); break;
  case S_PROCA: strcpy(s, "proc. assign"); break;
  case S_FORASSGN: strcpy(s, "for initial assign"); break;
  case S_NBPROCA: strcpy(s, "non-blocking proc. assign"); break;
  case S_RHSDEPROCA: strcpy(s, "proc. assign (rhs delay/event)"); break;
  case S_IF: strcpy(s, "if"); break;
  case S_CASE: strcpy(s, "case/casex/casez"); break;
  case S_FOREVER: strcpy(s, "forever"); break;
  case S_REPEAT: strcpy(s, "repeat"); break;
  case S_WHILE: strcpy(s, "while"); break;
  case S_DO_WHILE: strcpy(s, "do-while"); break;
  case S_WAIT: strcpy(s, "wait"); break;
  case S_FOR : strcpy(s, "for loop"); break;
  case S_DELCTRL: strcpy(s, "delay control"); break;
  case S_NAMBLK : strcpy(s, "named block"); break;
  case S_UNBLK : strcpy(s, "unnamed block"); break;
  case S_UNFJ: strcpy(s, "parallel block"); break;
  case S_TSKCALL: strcpy(s, "task enable"); break;
  case S_FUNCCALL: strcpy(s, "function void enable"); break;
  case S_QCONTA: strcpy(s, "quasi-continuous assign"); break;
  case S_QCONTDEA: strcpy(s, "quasi-continous deassign"); break;
  case S_CAUSE: strcpy(s, "cause"); break;
  case S_DSABLE: strcpy(s, "disable"); break;
  case S_REPSETUP: strcpy(s, "**added loop setup"); break;
  case S_REPDCSETUP: strcpy(s, "**added repeat event control setup"); break;
  case S_GOTO: strcpy(s, "**added goto"); break;
  case S_INC: strcpy(s, "increment ++"); break;
  case S_DEC: strcpy(s, "decrement --"); break;
  case S_BREAK: strcpy(s, "break"); break;
  case S_RETURN: strcpy(s, "return"); break;
  case S_CONTINUE: strcpy(s, "continue"); break;
  default: __case_terr(__FILE__, __LINE__);
 }
 return(s);
}

/*
 * build the quasi-continue statement type name 
 */
extern char *__to_qctyp(char *s, word32 qctyp)
{
 switch (qctyp) {
  case FORCE: strcpy(s, "force"); break;
  case RELEASE: strcpy(s, "release"); break;
  case ASSIGN: strcpy(s, "assign"); break;
  case DEASSIGN: strcpy(s, "deassign"); break;
  default: __case_terr(__FILE__, __LINE__);
 }
 return(s);
}

/*
 * build an event type name
 */
extern char *__to_tetyp(char *s, void *enterp) 
{
  if (enterp == __process_thrd_ev) strcpy(s, "procedural");
  else if (enterp == __process_gatechg_ev) strcpy(s, "gate assign");
  else if (enterp == __process_conta_ev) strcpy(s, "conta assign");
  else if (enterp == __process_wire_ev) strcpy(s, "wire delay"); 
  else if (enterp == __process_trpthdst_ev) strcpy(s, "inout path dest.");
  else if (enterp == __process_mipd_nchg_ev) strcpy(s, "MIPD change"); 
  else if (enterp == __process_nbpa_ev) strcpy(s, "NB assign");
  else if (enterp == __setdel_call_misctf) strcpy(s, "tf_ set delay");
  else if (enterp == __sync_call_misctf) strcpy(s, "tf_ #0 synchronize");
  else if (enterp == __process_putpdel_ev) strcpy(s, "tf_ delayed strputp");
  else if (enterp == __process_vpi_varputv_ev) strcpy(s, "vpi_ put value");
  else if (enterp == __process_vpidrv_ev) strcpy(s, "vpi_ add drv. chg.");
  else if (enterp == __delay_callback) strcpy(s, "vpi_ delay cb");
  else strcpy(s, "**UNKNOWN**");
 return(s);
}

/*
 * build a net-pin connection/action type
 */
extern char *__to_npptyp(char *s, struct net_pin_t *npp) 
{
 char s1[RECLEN];

 switch (npp->npntyp) {
  case NP_ICONN: strcpy(s, "instance port"); break;
  case NP_PB_ICONN: strcpy(s, "instance per bit port"); break;
  case NP_MDPRT: strcpy(s, "module port"); break;
  case NP_PB_MDPRT: strcpy(s, "module per bit port"); break;
  case NP_MIPD_NCHG: strcpy(s, "MIPD input/inout port"); break;
  case NP_CONTA:
   if (npp->elnpp.ecap->ca_pb_sim) strcpy(s, "per bit cont. assign lvalue"); 
   else strcpy(s, "cont. assign lvalue"); break;
   break;
  case NP_TFRWARG: strcpy(s, "tf_ PLI rw arg wire driver"); break;
  case NP_VPIPUTV: strcpy(s, "vpi_put_value wire driver"); break;
  case NP_GATE: strcpy(s, "gate terminal"); break;
  case NP_TRANIF: strcpy(s, "tranif enable"); break;
  case NP_TCHG:
   sprintf(s, "bit change(%s)", __to_nppsubtyp(s1, npp->chgsubtyp));
   break;
  case NP_PULL: strcpy(s, "pull driver"); break;
  default: __case_terr(__FILE__, __LINE__);
 }
 return(s);
}

/*
 * build the net change subtype name 
 */
static char *__to_nppsubtyp(char *s, word32 subtyp)
{
 switch (subtyp) {
  case NPCHG_TCSTART: strcpy(s, "tchk start ref."); break;
  case NPCHG_TCCHK: strcpy(s, "tchk data end"); break;
  case NPCHG_PTHSRC: strcpy(s, "path source"); break;
  default: __case_terr(__FILE__, __LINE__);
 }
 return(s);
}

/*
 * build a delay type name string
 */
extern char *__to_deltypnam(char *s, word32 dtyp)
{
 switch (dtyp) {
   case DT_NONE: strcpy(s, "?none?"); break; 
   case DT_1V: strcpy(s, "one"); break;
   case DT_IS1V: case DT_IS1V1: case DT_IS1V2:
    strcpy(s, "one instance specific");
    break;
   case DT_4V: strcpy(s, "(r, f, toz)"); break;
   case DT_IS4V: case DT_IS4V1: case DT_IS4V2:
    strcpy(s, "(r, f, toz) instance specific");
    break;
   case DT_16V: strcpy(s, "path 2,3,6,12 value"); break;
   case DT_IS16V: case DT_IS16V1: case DT_IS16V2:
     strcpy(s, "path 2,3,6,12 value instance specific");
     break;
   case DT_1X: strcpy(s, "one non constant"); break;
   case DT_4X: strcpy(s, "(r, f, toz) non constant"); break;
   case DT_PTHDST: strcpy(s, "internal path descriptor non"); break;
   case DT_CMPLST: strcpy(s, "translation time expression list"); break;
   default: __case_terr(__FILE__, __LINE__);
  }
 return(s);
}

/*
 * convert timing check type to name
 */
extern char *__to_tcnam(char *s, word32 tctyp) 
{
 switch (tctyp) {
  case TCHK_SETUP: strcpy(s, "$setup"); break;
  case TCHK_HOLD: strcpy(s, "$hold"); break;
  case TCHK_WIDTH: strcpy(s, "$width"); break;
  case TCHK_PERIOD: strcpy(s, "$period"); break;
  case TCHK_SKEW: strcpy(s, "$skew"); break;
  case TCHK_RECOVERY: strcpy(s, "$recovery"); break;
  case TCHK_SETUPHOLD: strcpy(s, "$setuphold"); break;
  case TCHK_NOCHANGE: strcpy(s, "$nochange"); break;
  /* SJM 12/15/03 - new 2001 timing checks - if used not read with warn */
  case TCHK_FULLSKEW: strcpy(s, "$fullskew"); break;
  case TCHK_REMOVAL: strcpy(s, "$removal"); break;
  case TCHK_RECREM: strcpy(s, "$recrem"); break;
  case TCHK_TIMESKEW: strcpy(s, "$timeskew"); break;
  default: __case_terr(__FILE__, __LINE__);
 }
 return(s);
}

/*
 * convert timing check name to type number - returns -1 if not found
 * expected the leading $ 
 */
extern int32 __fr_tcnam(char *tcnam)
{
 if (*tcnam != '$') return(-1);
 switch (tcnam[1]) {
  case 'f':
   if (strcmp(&(tcnam[2]), "ullskew") == 0) return(TCHK_FULLSKEW);
   break;
  case 'h': if (strcmp(&(tcnam[2]), "old") == 0) return(TCHK_HOLD); break;
  case 'n':
   if (strcmp(&(tcnam[2]), "ochange") == 0) return(TCHK_NOCHANGE); break;
  case 'p': if (strcmp(&(tcnam[2]), "eriod") == 0) return(TCHK_PERIOD); break;
  case 'r':
   /* SJM - 11/21/03 - must also recognize recrem */
   if (strcmp(&(tcnam[2]), "ecovery") == 0) return(TCHK_RECOVERY);
   if (strcmp(&(tcnam[2]), "ecrem") == 0) return(TCHK_RECREM);
   if (strcmp(&(tcnam[2]), "emoval") == 0) return(TCHK_REMOVAL);
   break;
  case 's':
   if (tcnam[2] == 'k')
    { if (strcmp(&(tcnam[3]), "ew") == 0) return(TCHK_SKEW); break; } 
   else if (strcmp(&(tcnam[2]), "etuphold") == 0) return(TCHK_SETUPHOLD);
   else if (strcmp(&(tcnam[2]), "etup") == 0) return(TCHK_SETUP);
   break;
  case 't':
   if (strcmp(&(tcnam[2]), "imeskew") == 0) return(TCHK_TIMESKEW);
   break;
  case 'w': if (strcmp(&(tcnam[2]), "idth") == 0) return(TCHK_WIDTH); break;
 }
 return(-1);
}

/*
 * output a number that is decomposed from input token but not yet converted
 * to value for errors during input number processing
 */
static char *decompnum_to_str(char *s, char *digs, int32 base, int32 width)
{
 sprintf(s, "%d'%c%s", width, __to_baselet(base), digs);
 return(s);
}

/*
 * convert gate output value to printable
 * tricky because depending on gate class and stval may or may not need stren
 */
extern char *__to_gonam(char *s, struct gate_t *gp, word32 v)
{
 switch (gp->g_class) { 
  case GC_LOGIC: case GC_UDP:
   if (gp->g_hasst)
    {
     if (v != 2) v |= (gp->g_stval << 2);
     __to_vvstnam(s, (word32) __stren_map_tab[v]);
    }
   else __to_vvnam(s, (word32) v); 
   break;
  case GC_TRANIF:
   /* here gate "output" is conducting state */
   if (v == 0) strcpy(s, "*OFF*");
   else if (v == 1) strcpy(s, "*ON*"); 
   else if (v == 3) strcpy(s, "*UNKNOWN*");
   else __misc_terr(__FILE__, __LINE__);
   break;
  case GC_TRAN: case GC_PULL:
   __case_terr(__FILE__, __LINE__); strcpy(s, ""); 
  /* mos and bufif outputs always strength */
  default: __to_vvstnam(s, (word32) v);
 } 
 return(s);
}

/*
 * convert gate value to printable
 * tricky because depending on gate class and stval may or may not need stren
 */
extern char *__to_ginam(char *s, struct gate_t *gp, word32 v, int32 i)
{
 switch (gp->g_class) { 
  /* bufif inputs non stength even though drives strength */
  /* tranif 3rd input non strength and value not just on/off */ 
  case GC_LOGIC: case GC_UDP: case GC_BUFIF: case GC_TRANIF:
   __to_vvnam(s, (word32) v);
   break;
  /* mos input 1 strength (added if needed) but control input non stren */
  case GC_MOS: case GC_CMOS: 
   /* only 1st mos or cmos input has strength not control(s) */
   if (i == 1) __to_vvstnam(s, (word32) v); else __to_vvnam(s, (word32) v);
   break;
  /* tran and pull cannot use this routine */
  default: __case_terr(__FILE__, __LINE__);
 } 
 return(s);
}

/*
 * convert net value to printable
 */
extern char *__to_vnam(char *s, word32 is_stren, word32 v)
{
 if (is_stren) __to_vvstnam(s, (word32) v); else __to_vvnam(s, (word32) v);
 return(s);
}

/*
 * convert a strength value to a 3 letter name string
 * know always 3 characters
 *
 * SJM 08/16/01 - BEWARE this routine must not be changed because it is
 * only way debug switch determines if mistake in table or algorithm
 * has caused one of the illegal 129 stren values to be created 
 * algorithms do something slightly and undectably wrong if this happens
 */
extern char *__to_vvstnam(char *s, word32 stval)
{
 word32 st0, st1;
 byte val;
 char ch;

 /* decode stren byte */
 val = (byte) stval & 3;
 st0 = (stval >> 5) & 7;
 st1 = (stval >> 2) & 7;

 switch (val) {
  case 0: ch = '0'; break;
  case 1: ch = '1'; break;
  case 2:
   /* real HiZ */ 
   if (st0 != 0 || st1 != 0)__misc_terr(__FILE__, __LINE__);
   strcpy(s, "HiZ");
   return(s);
  case 3:
   /* this should be Z not X */
   if (st0 == 0 && st1 == 0) __misc_terr(__FILE__, __LINE__); 

   /* z with hiz 0 strength component is H */
   if (st0 == 0) { __to_dispst_str(s, st1); s[2] = 'H'; s[3] = '\0'; }
   /* z with hiz 1 strength component is L */
   else if (st1 == 0) { __to_dispst_str(s, st0); s[2] = 'L'; s[3] = '\0'; }
   else { ch = 'X'; break; } 
   return(s);
  default: __case_terr(__FILE__, __LINE__); return(NULL);
 }

 /* finally known case strength is range with value */
 /* notice strength letters always 2 chars */
 if (st0 == st1)
  {
   /* DBG remove --- */
   /* for normal value strength cannot both be 0 */  
   if (st0 == 0) __misc_terr(__FILE__, __LINE__); 
   /* --- */
   __to_dispst_str(s, st0);
   s[2] = ch;
  }
 else { s[0] = '0' + st0; s[1] = '0' + st1; s[2] = ch; }
 s[3] = '\0';
 return(s);
}

/*
 * convert a 2 bit number to its verilog value name
 */
extern char *__to_vvnam(char *s, word32 v)
{
 switch (v) {
  case 0: strcpy(s, "0"); break;
  case 1: strcpy(s, "1"); break;
  case 2: strcpy(s, "z"); break;
  case 3: default: strcpy(s, "x"); break;
 }
 return(s);
}

/* same but for udp 3-values */
extern char *__to_uvvnam(char *s, word32 v)
{
 switch (v) {
  case 0: strcpy(s, "0"); break;
  case 1: strcpy(s, "1"); break;
  default: strcpy(s, "x"); break;
 }
 return(s);
}

/*
 * convert base code to letter
 */
extern char __to_baselet(int32 bcod)
{
 char ch;

 switch ((byte) bcod) {
  case BBIN: ch = 'b'; break;
  case BHEX: ch = 'h'; break;
  case BOCT: ch = 'o'; break;
  case BDEC: ch = 'd'; break;
  default: ch = '?'; __case_terr(__FILE__, __LINE__);
 }
 return(ch);
}

/*
 * convert time unit string (0-15) code to time unit name  
 */
extern char *__to_timunitnam(char *s, word32 unit)
{
 switch ((byte) unit) {
  case 0: strcpy(s, "1 s"); break; 
  case 1: strcpy(s, "100 ms"); break;
  case 2: strcpy(s, "10 ms"); break;
  case 3: strcpy(s, "1 ms"); break;
  case 4: strcpy(s, "100 us"); break;
  case 5: strcpy(s, "10 us"); break;
  case 6: strcpy(s, "1 us"); break;
  case 7: strcpy(s, "100 ns"); break;
  case 8: strcpy(s, "10 ns"); break;
  case 9: strcpy(s, "1 ns"); break;
  case 10: strcpy(s, "100 ps"); break;
  case 11: strcpy(s, "10 ps"); break;
  case 12: strcpy(s, "1 ps"); break;
  case 13: strcpy(s, "100 fs"); break;
  case 14: strcpy(s, "10 fs"); break;
  case 15: strcpy(s, "1 fs"); break;
  default: __case_terr(__FILE__, __LINE__);
 }
 return(s);
}

/*
 * convert an edge bit byte into an edge name string
 * if posedge or negedge use name else use [...] form
 */
extern char *__to_edgenam(char *s, word32 eval)
{
 int32 first_time;
 byte ebyte;
 
 switch ((ebyte = (byte) eval)) {
  case E_POSEDGE: strcpy(s, "posedge"); break; 
  case E_NEGEDGE: strcpy(s, "negedge"); break; 
  case NOEDGE: strcpy(s, ""); break;
  default:
   strcpy(s, "edge[");
   first_time = TRUE;
   if ((ebyte & EDGE01) != 0)
    {
     if (first_time) first_time = FALSE; else strcat(s, ", ");
     strcat(s, "01");
    }
   if ((ebyte & EDGE10) != 0)
    { 
     if (first_time) first_time = FALSE; else strcat(s, ", ");
     strcat(s, "10");
    }
   if ((ebyte & EDGE0X) != 0)
    {
     if (first_time) first_time = FALSE; else strcat(s, ", ");
     strcat(s, "0x");
    }
   if ((ebyte & EDGEX1) != 0)
    {
     if (first_time) first_time = FALSE; else strcat(s, ", ");
     strcat(s, "x1");
    }
   if ((ebyte & EDGE1X) != 0)
    {
     if (first_time) first_time = FALSE; else strcat(s, ", ");
     strcat(s, "1x");
    }
   if ((ebyte & EDGEX0) != 0)
    {
     if (first_time) first_time = FALSE; else strcat(s, ", ");
     strcat(s, "x0");
    }
   strcat(s, "]");
  }
 return(s);
}

/*
 * convert an delay control type to a name
 */
extern char *__to_dcenam(char *s, word32 dctyp)
{
 switch ((byte) dctyp) {
  case DC_NONE: strcpy(s, "**NONE?**"); break; 
  case DC_EVENT: strcpy(s,"event"); break;
  case DC_DELAY: strcpy(s, "delay"); break;
  case DC_RHSEVENT:strcpy(s,"rhs event"); break; 
  case DC_RHSDELAY:strcpy(s, "rhs delay"); break;
  case DC_WAITEVENT: strcpy(s,"wait event"); break;
  default: __case_terr(__FILE__, __LINE__);
 }
 return(s);
}

/*
 * convert a generate item type value into a name
 */
extern char *__to_genitem_nam(char *s, int32 gityp)
{
 switch ((byte) gityp) { 
  case GI_UNKN: strcpy(s, "GEN ITEM UNKN"); break;
  case GI_GBLK: strcpy(s, "GEN BLK"); break;
  case GI_GFOR: strcpy(s, "GEN FOR"); break;
  case GI_GIF: strcpy(s, "GEN IF"); break;
  case GI_GCASE: strcpy(s, "GEN CASE"); break;
  case GI_CONTA: strcpy(s, "GEN CONTA"); break;
  case GI_CELL: strcpy(s, "GEN CELL"); break;
  case GI_GATE: strcpy(s, "GEN GATE"); break;
  case GI_INST: strcpy(s, "GEN INSTANCE"); break;
  case GI_VARDECL: strcpy(s, "GEN REGION DECL"); break;
  case GI_INITALW: strcpy(s, "GEN INIT/ALWAYS"); break;
  case GI_GREF: strcpy(s, "GEN GREF"); break;
  case GI_DFPARM: strcpy(s, "GEN DFPARM"); break;
  default: __case_terr(__FILE__, __LINE__);
 }
 return(s);
}

/*
 * convert a hierarchical reference (XMR) component record type to a name
 * SJM 02-16-10 - new mechanism for XMR and defparms in generates
 */
extern char *__to_xmrcmp_nam(char *s, int32 gityp)
{
 switch ((byte) gityp) { 
  case XMP_UNKN: strcpy(s, "?UNKN?"); break;
  case XMP_MOD: strcpy(s, "MOD"); break;
  case XMP_INST: strcpy(s, "INST"); break;
  case XMP_INST_INGEN: strcpy(s, "INST_INGEN"); break;
  case XMP_GBLK: strcpy(s, "GBLK"); break;
  case XMP_TSK: strcpy(s, "TSK"); break;
  case XMP_NET: strcpy(s, "NET"); break;
  case XMP_NET_INGEN: strcpy(s, "NET_INGEN"); break;
  default: __case_terr(__FILE__, __LINE__);
 }
 return(s);
}

/*
 * SPECIAL MEMORY ALLOCATION ROUTINES
 * USES OWN STRUCT AND CONSTANTS BELOW
 */

/*
 * allocate a string for use during elaboration - adds the ending \0
 * this must allocate the 1 char null string for `define as flag
 */
extern char *__pv_stralloc(char *s)
{
 char *cp;
 int32 slen;

 if (*s == '\0') slen = 1; else slen = strlen(s) + 1;
 cp = __my_malloc(slen);
 __memstr_use += slen;
 /* this just copies '\0' for "" case */
 strcpy(cp, s);
 return(cp);
}

/*
 * memory allocator for non freed memory
 * and allocate small piece from a large allocated block
 * aligns on 4 byte boundaries for VAX and 68000 too
 * notice this is 32 bit word32 dependent
 *
 * could save space in pc by allocating only on bytes but would need always
 * at least 4 bytes - no since now using free by size header table
 */
static char *nfbig_alloc(int32 size)
{
 char *cp;
 int32 rem, real_size;

 if ((rem = size % 4) != 0) real_size = size + 4 - rem;
 else real_size = size;

 if ((__start_sp + real_size + 4) >= __end_sp)
  {
   __start_sp = __my_malloc(BIG_ALLOC_SIZE); 
   __end_sp = __start_sp + BIG_ALLOC_SIZE - 16;
  }
 cp = __start_sp;
 __start_sp += real_size;
 return(cp);
}

/*
 * call to malloc that dies if no memory available
 * these are normal OS memory allocation with error terminaton
 *
 * AIV 03/27/09 - must take size_t not int for 64-bit 
 */
extern char *__my_malloc(size_t size)
{
 char *cp;

#ifndef __CVC32__
 #ifdef __CVC_DEBUG__
  /* AIV 03/27/09 - for helping in debugging 64-bit overflow */
  if (size >= 0xffffffffUL) __misc_terr(__FILE__, __LINE__);
 #endif
#endif

 if ((cp = (char *) malloc(size)) == NULL)
  {
   __sysfatal_msg(
   "**fatal err[1]: No more memory - at file %s line %d allocated %ld bytes\n",
    __cur_fnam, __lin_cnt, __mem_use);
   __my_exit(4, TRUE);
  }
 __mem_use += size;
 __mem_allocated += size;
 /* DBG remove ---
 if (__debug_flg) __dbg_msg("my_malloc - allocated %d bytes - use %ld\n",
   size, __mem_use);
 --- */
 return(cp);
}

/*
 * call to free 
 *
 * AIV 03/27/09 - must take size_t not int for 64-bit 
 */
extern void __my_free(void *mp, size_t size)
{
 /* DBG remove --- 
 if (size <= 0) return;
  --- */
 free(mp);
 __mem_use -= size;
 __mem_freed += size;
 /* DBG remove ---
 if (__debug_flg) __dbg_msg("freeing %d bytes - memuse now %ld\n", size,
  __mem_use);
 --- */
 /* ---
 __my_fprintf(stdout, "freeing %d bytes - alloc=%lu freed=%lu\n", size,
  __mem_allocated, __mem_freed);
 --- */
}

/*
 * interface to system realloc()
 * can only call with malloced mp or cannot realloc
 *
 * AIV 03/27/09 - must take size_t not int for 64-bit 
 */
extern char *__my_realloc(void *mp, size_t osize, size_t nsize)
{
 void *cp;

 if ((cp = realloc(mp, nsize)) == NULL)
  {
   __sysfatal_msg(
    "**fatal err[1]: realloc failed - allocated %ld bytes\n", __mem_use);
   __my_exit(4, TRUE);
  }
 /* DBG remove ---
 if (__debug_flg)
  __dbg_msg("realloc: freeing %d byte and allocating %d bytes\n",
   osize, nsize);
 --- */
 __mem_use -= osize;
 __mem_use += nsize;
 return(cp);
}

/*
 *  INTERFACE TO OS ROUTINES
 */

/*
 * version of fclose that ends with fatal error if cannot close 
 * some unixes do not return anything on fclose failure
 */
extern void __my_fclose(FILE *f)
{
 if (f == NULL) __misc_terr(__FILE__, __LINE__);
 if (fclose(f) == EOF)
  {
   __crit_msg("**fatal err[1]: OS fclose failed: %s\n", strerror(errno));
   __my_exit(5, TRUE);
  }
}


/*
 * version of fd close that ends with fatal error if cannot close 
 * some unixes do not return anything on close failure
 */
extern void __my_close(int32 fd)
{
 if (fd == -1) __misc_terr(__FILE__, __LINE__);
 if (close(fd) == -1)
  {
   __crit_msg("**fatal err[1]: OS fclose failed: %s\n", strerror(errno));
   __my_exit(5, TRUE);
  }
}

/*
 * interface to system rewind routine
 */
extern void __my_rewind(FILE *f)
{
 if (fseek(f, 0L, 0) == -1)
  {
   __crit_msg("**fatal err[1]: OS rewind failed: %s\n", strerror(errno));
   __my_exit(5, TRUE);
  }
}

/*
 * version of unbuffered open that performs tilde expansion
 * FIXME - should allow ~[dir] form and look at some network directory
 * and allow ~ anywhere in path name
 */
extern int32 __tilde_open(char *pthnam, int32 opmask)
{
 int32 newlen;
 char *chp;
 int32 fd;

 if (*pthnam != '~') return(open(pthnam, opmask)); 
 if ((chp = tilde_expand(pthnam, &newlen)) == NULL) return(-1);
 fd = open(chp, opmask);
 __my_free(chp, newlen);
 return(fd);
}

/*
 * open with expand of leading tilde in file name using home
 */
extern FILE *__tilde_fopen(char *pthnam, char *opmod)
{
 int32 newlen;
 char *chp;
 FILE *f;

 if (*pthnam != '~') return(__my_fopen(pthnam, opmod)); 
 if ((chp = tilde_expand(pthnam, &newlen)) == NULL) return(NULL);
 f = __my_fopen(chp, opmod);
 __my_free(chp, newlen);
 return(f);
}

/*
 * perform prefix tilde expansion
 * only called if path starts with tilde
 * notice for now silently returns 
 *
 * LOOKATME could allow /~/ component anywhere in path name for net addrs? 
 */
static char *tilde_expand(char *pthnam, int32 *newlen)
{
 char *chp, *chp2;
 int32 hlen, plen;
 char usernam[RECLEN];

 /* first ~/ form */
 if (pthnam[1] == '/') { chp2 = __pv_homedir; goto bld_expanded; }

 /* ~[user] form - look up if possible */
 if ((chp = strchr(pthnam, '/')) == NULL) return(NULL);
 strncpy(usernam, &(pthnam[1]), chp - pthnam - 1);
 usernam[chp - pthnam - 1] = '\0';
 /* pathname now has / prefix but ~[name] removed */
 pthnam = chp - 1;

 /* if do not know system, assume vanilla non networked BSD unix */
 {
  struct passwd *pwp;

  if ((pwp = getpwnam(usernam)) == NULL) return(NULL);
  chp2 = pwp->pw_dir;
 }
 goto bld_expanded;

bld_expanded:
 /* know home dir does not have ending / and . if HOMEDIR not set */
 hlen = strlen(chp2);
 plen = strlen(pthnam);
 *newlen = hlen - 1 + plen + 1;
 chp = __my_malloc(*newlen);
 strcpy(chp, chp2);
 strcpy(&(chp[hlen]), &(pthnam[1]));
 return(chp);
}

/*
 * unbuffered creat for writing with expand leading tilde in file name using 
 */
extern int32 __tilde_creat(char *pthnam)
{
 int32 newlen;
 char *chp;
 int32 fd;

 if (*pthnam != '~') return(__my_creat(pthnam)); 
 if ((chp = tilde_expand(pthnam, &newlen)) == NULL) return(-1);
 fd = __my_creat(chp);
 __my_free(chp, newlen);
 return(fd);
}

/*
 * version of open that returns NULL when directory opened
 * unix allows opening directories for reading
 */
extern FILE *__my_fopen(char *fnam, char *opmod)
{
 FILE *f;
 struct stat sbuf;

 if ((f = fopen(fnam, opmod)) == NULL) return(NULL);
 if (fstat(fileno(f), &sbuf) == -1)
  {
   __crit_msg("**fatal err[1]: OS file stat operation failed: %s\n",
    strerror(errno));
   __my_exit(5, TRUE);
  }
 /* anything but directory is ok */
 if ((S_IFDIR & sbuf.st_mode) == 0) return(f);

 /* ---
 __inform(417, "open failed because %s is directory or special file", fnam);
 --- */
 __my_fclose(f);
 return(NULL);
}

/*
 * version of non buffered creat that returns -1 when directory opened
 * unix allows opening directories for reading
 */
extern int32 __my_creat(char *fnam)
{
 int32 fd;
 struct stat sbuf;

 if ((fd = creat(fnam, 0666)) == -1) return(-1);
 if (fstat(fd, &sbuf) == -1)
  {
   __crit_msg("**fatal err[1]: OS file stat operation failed: %s\n",
    strerror(errno));
   __my_exit(5, TRUE);
  }
 /* anything but directory is ok */
 if ((S_IFDIR & sbuf.st_mode) == 0) return(fd);

 /* ---
 __inform(417, "open failed because %s is directory or special file", fnam);
 --- */
 close(fd);
 return(-1);
}

/*
 * routine to truncate (chop) a string for output 
 * one constant per run value for ID string chopped length
 * notice this always copies
 */
extern char *__schop(char *s1, char *s2)
{
 int32 slen, sendi;

 slen = strlen(s2);
 if (slen < (sendi = MSGTRUNCLEN - 4)) strcpy(s1, s2);
 else { strncpy(s1, s2, sendi); strcpy(&s1[sendi], "..."); }
 return(s1);
}

/*
 * build a **<file>(<line. no.) reference
 * this chops file name so know will fit
 * s must be RECLEN wide
 */
extern char *__bld_lineloc(char *s, word32 fnind, int32 fnlcnt)
{
 char s1[RECLEN];

 sprintf(s, "**%s(%d)", __schop(s1, __in_fils[fnind]), fnlcnt);
 return(s);
}

/*
 * MESSAGE ROUTINES
 */

/*
 * intellectual property (IP) message unsuppressable except by special simctrlb
 * IP messages suppression also stops log
 */
/*VARARGS*/
extern void __ip_msg(char *s, ...)
{
 va_list va, va2;

 /* SJM 10/13/99 - ansii std says varargs not usable after vprintf called */
 va_start(va, s);
 va_start(va2, s);
 vfprintf(stdout, s, va);
 if (__log_s != NULL) vfprintf(__log_s, s, va2);
 va_end(va);
 va_end(va2);
}

/*
 * intellectual property (IP) message 
 *
 * suppressable before customer1 cb if -q flag
 * IP messages suppression also stops log
 */
/*VARARGS*/
extern void __ip2_msg(char *s, ...)
{
 va_list va, va2;

 if (__quiet_msgs) return;

 /* SJM 10/13/99 - ansii std says varargs not usable after vprintf called */
 va_start(va, s);
 va_start(va2, s);
 vfprintf(stdout, s, va);
 if (__log_s != NULL) vfprintf(__log_s, s, va2);
 va_end(va);
 va_end(va2);
}

/*
 * critical Copyright, licensing, OS failure, malloc failure etc. 
 * never suppressed 
 */
/*VARARGS*/
extern void __crit_msg(char *s, ...)
{
 va_list va, va2;


 /* SJM 10/13/99 - ansii std says varargs not usable after vprintf called */
 va_start(va, s);
 va_start(va2, s);
 vfprintf(stdout, s, va);
 if (__log_s != NULL) vfprintf(__log_s, s, va2);
 va_end(va);
 va_end(va2);
}

/*
 * never suppressed special OS failure (can't call malloc or os calls)
 * vendor 1 must detect -4 (inverse of vpi vpiSystem error level)
 * BEWARE - this can't call system or malloc
 */
/*VARARGS*/
extern void __sysfatal_msg(char *s, ...)
{
 va_list va, va2;


 /* SJM 10/13/99 - ansii std says varargs not usable after vprintf called */
 va_start(va, s);
 va_start(va2, s);
 vfprintf(stdout, s, va);
 if (__log_s != NULL) vfprintf(__log_s, s, va2);
 va_end(va);
 va_end(va2);
}

/*
 * all normal (supressable with -q) messages 
 * Cver progress, -d, status options
 */
/*VARARGS*/
extern void __cv_msg(char *s, ...)
{
 va_list va, va2;

 if (__quiet_msgs) return;

 /* SJM 10/13/99 - ansii std says varargs not usable after vprintf called */
 va_start(va, s);
 va_start(va2, s);
 vfprintf(stdout, s, va);
 if (__log_s != NULL) vfprintf(__log_s, s, va2);
 va_end(va);
 va_end(va2);
}

/*
 * cver simulation output messages (from system tasks such as $showvars)
 * version 1 to both stdout and log file
 *
 * also all debugger output since interchangeable with system tasks
 * never suppressed 
 */
/*VARARGS*/
extern void __cvsim_msg(char *s, ...)
{
 va_list va, va2;

 /* SJM 11-30-10 - need to write properly spaced source code for dpi */
 /* wrapper and user option select prototype files */
 /* special global flag, that is only on in dpi dumping */
 /* BEWARE - even worse using faked log file to write the c to??? */
 if (__dpi_file_writing)
  {
   va_start(va, s);
   vfprintf(__log_s, s, va);
   va_end(va);
   return;
  }

 /* SJM 10/13/99 - ansii std says varargs not usable after vprintf called */
 va_start(va, s);
 va_start(va2, s);
 vfprintf(stdout, s, va);
 if (__log_s != NULL) vfprintf(__log_s, s, va2);
 va_end(va);
 va_end(va2);
}

/*
 * cver simulation output messages - * version 2 to just stdout
 */
/*VARARGS*/
extern void __cvsim2_msg(char *s, ...)
{
 va_list va;

 va_start(va, s);
 vfprintf(stdout, s, va);
 va_end(va);
}

/*
 * cver simulation output messages
 * version 3 only to log file
 *
 * from system tasks such as $showvars and debugger output
 * never suppressed and log file not suppresable
 */
/*VARARGS*/
extern void __cvsim3_msg(char *s, ...)
{
 va_list va;

 va_start(va, s);
 if (__log_s != NULL) vfprintf(__log_s, s, va);
 va_end(va);
}

/*
 * debugger (not debugger output) messages - not callback stopable
 * goes to both stdout and log file
 */
/*VARARGS*/
extern void __dbg_msg(char *s, ...)
{
 va_list va;
 va_list va2;

 va_start(va, s);
 va_start(va2, s);
 __my_vfprintf(stdout, s, va, va2);
 va_end(va2);
 va_end(va);
}

extern void __o_dbg_msg(char *s, ...)
{
 va_list va;
 va_list va2;

 if (__run_state != SS_SIM) return;
 va_start(va, s);
 va_start(va2, s);
 __my_vfprintf(stdout, s, va, va2);
 va_end(va2);
 va_end(va);
}

/*
 * trace message printf - to trace file unless stdout (the default)
 * LOOKATME - maybe should default trace file to verilog.trace
 */
/*VARARGS*/
extern void __tr_msg(char *s, ...)
{
 va_list va, va2;

 /* SJM 10/13/99 - ansii std says varargs not usable after vprintf called */
 va_start(va, s);
 va_start(va2, s);
 vfprintf(__tr_s, s, va);
 if (__tr_s == stdout && __log_s != NULL) vfprintf(__log_s, s, va2);
 va_end(va);
 va_end(va2);
}

extern void __o_tr_msg(char *s, ...)
{
 va_list va, va2;

 if (__run_state != SS_SIM) return;

 /* SJM 10/13/99 - ansii std says varargs not usable after vprintf called */
 va_start(va, s);
 va_start(va2, s);
 vfprintf(__tr_s, s, va);
 if (__tr_s == stdout && __log_s != NULL) vfprintf(__log_s, s, va2);
 va_end(va);
 va_end(va2);
}

/*
 * TERMINAL ERROR MESSAGE ROUTINES EXIT TO OS FOR ROUTINES CALL FROM MY EXIT
 */

/*
 * miscellaneous (most) internal fatal errors 
 */
extern void __os_exit_misc_terr(char *fnam, int32 lno)
{
 /* SJM DBG REMOVE - malloc_chain_check(1); */
 /* AIV 05/03/10 - this string should be cver.lic not cvc.lic */
 if (lno == -1039)
  {
   __os_exit_pv_terr(304,
     "cvc.lic file or single job lock invalid or removed - run licprobe -lockcheck");
  }
 __os_exit_pv_terr(303,
  "MISC INTERNAL - source line **%s(%d) - maybe at **%s(%d) or **%s(%d)",
  fnam, lno, __cur_fnam, __lin_cnt, __in_fils[__sfnam_ind], __slin_cnt);
}

/*
 * real (not my exit) error with fatal termination
 * arg s is a format specification string for sprintf
 *
 * notice error messages longer than 4k bytes will cause crash
 * caller of error routines must make sure no more than 4 ID called
 */
extern void __os_exit_pv_terr(int32 id_num, char *s, ...)
{
 va_list va, va2, va3;
 int32 slen;
 char vpis1[IDLEN], vpis2[4*IDLEN], *vpichp; 

 if (__vpierr_cb_active && !__iact_state)
  {
   /* reset in case user called sim control operation from wrong place */
   __errorcb_suppress_msg = FALSE;

   sprintf(vpis1, "**FATAL ERROR** [%d] ", id_num);
   va_start(va, s);
   vsprintf(vpis2, s, va);
   va_end(va);
   
   slen = strlen(vpis1) + strlen(vpis2) + 1;
   vpichp = __my_malloc(slen);
   strcpy(vpichp, vpis1);
   strcat(vpichp, vpis2);

   __cberror_fill_einfo(FATAL, id_num, vpichp, "[NONE]", 0);
   __vpi_error_trycall();

   __my_free(vpichp, slen);
   /* if vpi_ontrol used to suppress emsg, used up so turned off here */ 
   if (__errorcb_suppress_msg)
    { __errorcb_suppress_msg = FALSE; __my_exit(1, TRUE); }
  }
 __my_fprintf(stdout, "**FATAL ERROR** [%d] ", id_num);

 /* SJM 10/13/99 - ansii std says varargs not usable after vprintf called */
 va_start(va2, s);
 va_start(va3, s);
 __my_vfprintf(stdout, s, va2, va3);
 va_end(va2);
 va_end(va3);
 my_putc_('\n', stdout);
 exit(1);
}

/*
 * ERROR MESSAGE ROUTINES
 */

/*
 * miscellaneous (most) internal fatal errors 
 */
extern void __misc_terr(char *fnam, int32 lno)
{
 /* SJM DBG REMOVE - malloc_chain_check(1); */
 /* AIV 05/03/10 - this string should be cver.lic not cvc.lic */
 if (lno == -1039)
  {
   __pv_terr(304,
     "cvc.lic file or single job lock invalid or removed - run licprobe -lockcheck");
  }
 __pv_terr(303,
  "MISC INTERNAL - source line **%s(%d) - maybe at **%s(%d) or **%s(%d)",
  fnam, lno, __cur_fnam, __lin_cnt, __in_fils[__sfnam_ind], __slin_cnt);
}

/*
 * file miscellaneous (most) internal fatal errors (input file place known) 
 */
extern void __misc_fterr(char *fnam, int32 lno)
{
 __fterr(303, "MISC INTERNAL - source line **%s(%d)", fnam, lno);
}

/*
 * global analysis phase internal error - object provides line number
 */
extern void __misc_gfterr(char *fnam, int32 lno, word32 gfnam_ind,
 int32 gflin_cnt)
{
 __gfterr(303, gfnam_ind, gflin_cnt,
  "MISC INTERNAL - source line **%s(%d)", fnam, lno);
}

/*
 * non execution statement type error __sfnam_ind contains location
 */
extern void __misc_sgfterr(char *fnam, int32 lno)
{
 __gfterr(303, __sfnam_ind, __slin_cnt,
  "MISC INTERNAL - source line **%s(%d)", fnam, lno);
}

/*
 * simple case fatal error - can always find with debugger
 */
extern void __case_terr(char *fnam, int32 lno)
{
 __pv_terr(324,
  "CASE INTERNAL - source line **%s(%d) - maybe at **%s(%d) or **%s(%d)",
  fnam, lno, __cur_fnam, __lin_cnt, __in_fils[__sfnam_ind], __slin_cnt);
}

/*
 * simple argument passed to routine internal error
 */
extern void __arg_terr(char *fnam, int32 lno)
{
 __pv_terr(322,
  "ARG INTERNAL - source line **%s(%d) - maybe at **%s(%d) or **%s(%d)",
  fnam, lno, __cur_fnam, __lin_cnt, __in_fils[__sfnam_ind], __slin_cnt);
}

/*
 * error with fatal termination
 * arg s is a format specification string for sprintf
 *
 * notice error messages longer than 4k bytes will cause crash
 * caller of error routines must make sure no more than 4 ID called
 */
extern void __pv_terr(int32 id_num, char *s, ...)
{
 va_list va, va2, va3;
 int32 slen;
 char vpis1[IDLEN], vpis2[4*IDLEN], *vpichp; 

 if (__vpierr_cb_active && !__iact_state)
  {
   /* reset in case user called sim control operation from wrong place */
   __errorcb_suppress_msg = FALSE;

   sprintf(vpis1, "**FATAL ERROR** [%d] ", id_num);
   va_start(va, s);
   vsprintf(vpis2, s, va);
   va_end(va);
   
   slen = strlen(vpis1) + strlen(vpis2) + 1;
   vpichp = __my_malloc(slen);
   strcpy(vpichp, vpis1);
   strcat(vpichp, vpis2);

   __cberror_fill_einfo(FATAL, id_num, vpichp, "[NONE]", 0);
   __vpi_error_trycall();

   __my_free(vpichp, slen);
   /* if vpi_ontrol used to suppress emsg, used up so turned off here */ 
   if (__errorcb_suppress_msg)
    { __errorcb_suppress_msg = FALSE; __my_exit(1, TRUE); }
  }
 __my_fprintf(stdout, "**FATAL ERROR** [%d] ", id_num);

 /* SJM 10/13/99 - ansii std says varargs not usable after vprintf called */
 va_start(va2, s);
 va_start(va3, s);
 __my_vfprintf(stdout, s, va2, va3);
 va_end(va2);
 va_end(va3);
 my_putc_('\n', stdout);
 __my_exit(1, TRUE);
}

/*
 * vpi error with fatal termination and no error cb try call
 * arg s is a format specification string for sprintf
 *
 * notice error messages longer than 4k bytes will cause crash
 * caller of error routines must make sure no more than 4 ID called
 */
extern void __pv_vpi_terr(int32 id_num, char *s, ...)
{
 va_list va, va2, va3;
 int32 slen;
 char vpis1[IDLEN], vpis2[4*IDLEN], *vpichp; 

 if (__vpierr_cb_active && !__iact_state)
  {
   /* reset in case user called sim control operation from wrong place */
   __errorcb_suppress_msg = FALSE;

   sprintf(vpis1, "**FATAL ERROR** [%d] ", id_num);
   va_start(va, s);
   vsprintf(vpis2, s, va);
   va_end(va);
   
   slen = strlen(vpis1) + strlen(vpis2) + 1;
   vpichp = __my_malloc(slen);
   strcpy(vpichp, vpis1);
   strcat(vpichp, vpis2);

   __my_free(vpichp, slen);
   /* if vpi_ontrol used to suppress emsg, used up so turned off here */ 
   if (__errorcb_suppress_msg)
    { __errorcb_suppress_msg = FALSE; __my_exit(1, TRUE); }
  }
 __my_fprintf(stdout, "**FATAL ERROR** [%d] ", id_num);

 /* SJM 10/13/99 - ansii std says varargs not usable after vprintf called */
 va_start(va2, s);
 va_start(va3, s);
 __my_vfprintf(stdout, s, va2, va3);
 va_end(va2);
 va_end(va3);
 my_putc_('\n', stdout);
 __my_exit(1, TRUE);
}

/*
 * note ferr forms all take a variable prefix for acc_ and tf_ and debugger
 */

/*VARARGS*/
extern void __fterr(int32 id_num, char *s, ...)
{
 va_list va, va2, va3;
 int32 slen;
 char vpis1[IDLEN], vpis2[4*IDLEN], *vpichp; 

 if (__vpierr_cb_active && !__iact_state)
  {
   /* reset in case user called sim control operation from wrong place */
   __errorcb_suppress_msg = FALSE;

   sprintf(vpis1, "**%s(%d) FATAL ERROR** [%d] ", __cur_fnam,
    __lin_cnt, id_num);
   va_start(va, s);
   vsprintf(vpis2, s, va);
   va_end(va);
   
   slen = strlen(vpis1) + strlen(vpis2) + 1;
   vpichp = __my_malloc(slen);
   strcpy(vpichp, vpis1);
   strcat(vpichp, vpis2);

   __cberror_fill_einfo(FATAL, id_num, vpichp, __cur_fnam, __lin_cnt);
   __vpi_error_trycall();

   __my_free(vpichp, slen);
   /* if vpi_control used to suppress emsg, used up so turned off here */ 
   if (__errorcb_suppress_msg)
    { __errorcb_suppress_msg = FALSE; __my_exit(2, TRUE); }
  }

 __my_fprintf(stdout, "**%s(%d) FATAL ERROR** [%d] ", __cur_fnam,
  __lin_cnt, id_num);

 /* SJM 10/13/99 - ansii std says varargs not usable after vprintf called */
 va_start(va2, s);
 va_start(va3, s);
 __my_vfprintf(stdout, s, va2, va3);
 va_end(va2);
 va_end(va3);
 my_putc_('\n', stdout);
 __my_exit(2, TRUE);
}

/*VARARGS*/
extern void __sgfterr(int32 id_num, char *s, ...)
{
 va_list va, va2, va3;
 int32 slen;
 char vpis1[IDLEN], vpis2[4*IDLEN], *vpichp; 
 char s1[RECLEN], s2[RECLEN];

 if (__run_state == SS_SIM) 
  sprintf(s1, " now %s", __to_timstr(s2, &__simtime)); 
 else strcpy(s1, "");

 if (__vpierr_cb_active && !__iact_state)
  {
   /* reset in case user called sim control operation from wrong place */
   __errorcb_suppress_msg = FALSE;

   sprintf(vpis1, "**%s(%d) FATAL ERROR**%s [%d] ", __in_fils[__sfnam_ind],
    __slin_cnt, s1, id_num);
   va_start(va, s);
   vsprintf(vpis2, s, va);
   va_end(va);
   
   slen = strlen(vpis1) + strlen(vpis2) + 1;
   vpichp = __my_malloc(slen);
   strcpy(vpichp, vpis1);
   strcat(vpichp, vpis2);

   __cberror_fill_einfo(FATAL, id_num, vpichp, __in_fils[__sfnam_ind],
    __slin_cnt);
   __vpi_error_trycall();

   __my_free(vpichp, slen);
   /* if vpi_control used to suppress emsg, used up so turned off here */ 
   if (__errorcb_suppress_msg)
    { __errorcb_suppress_msg = FALSE; __my_exit(2, TRUE); }
  }

 __my_fprintf(stdout, "**%s(%d) FATAL ERROR**%s [%d] ",
  __in_fils[__sfnam_ind], __slin_cnt, s1, id_num);

 /* SJM 10/13/99 - ansii std says varargs not usable after vprintf called */
 va_start(va2, s);
 va_start(va3, s);
 __my_vfprintf(stdout, s, va2, va3);
 va_end(va2);
 va_end(va3);
 my_putc_('\n', stdout);
 __my_exit(2, TRUE);
}

/*VARARGS*/
extern void __gfterr(int32 id_num, word32 gfnam_ind, int32 gflin_cnt,
 char *s, ...)
{
 va_list va, va2, va3;
 int32 slen;
 char vpis1[IDLEN], vpis2[4*IDLEN], *vpichp; 
 char s1[RECLEN], s2[RECLEN];

 if (__run_state == SS_SIM) 
  sprintf(s1, " now %s", __to_timstr(s2, &__simtime)); 
 else strcpy(s1, "");

 if (__vpierr_cb_active && !__iact_state)
  {
   /* reset in case user called sim control operation from wrong place */
   __errorcb_suppress_msg = FALSE;

   sprintf(vpis1, "**%s(%d) FATAL ERROR**%s [%d] ",
    __in_fils[gfnam_ind], gflin_cnt, s1, id_num);
   va_start(va, s);
   vsprintf(vpis2, s, va);
   va_end(va);
   
   slen = strlen(vpis1) + strlen(vpis2) + 1;
   vpichp = __my_malloc(slen);
   strcpy(vpichp, vpis1);
   strcat(vpichp, vpis2);

   __cberror_fill_einfo(FATAL, id_num, vpichp, __in_fils[gfnam_ind],
    gflin_cnt);
   __vpi_error_trycall();

   __my_free(vpichp, slen);
   /* if vpi_control used to suppress emsg, used up so turned off here */ 
   if (__errorcb_suppress_msg)
    { __errorcb_suppress_msg = FALSE; __my_exit(2, TRUE); }
  }

 __my_fprintf(stdout, "**%s(%d) FATAL ERROR**%s [%d] ",
  __in_fils[gfnam_ind], gflin_cnt, s1, id_num);

 /* SJM 10/13/99 - ansii std says varargs not usable after vprintf called */
 va_start(va2, s);
 va_start(va3, s);
 __my_vfprintf(stdout, s, va2, va3);
 va_end(va2);
 va_end(va3);
 my_putc_('\n', stdout);
 __my_exit(2, TRUE);
}

/*
 * serious but non-fatal error
 */
/*VARARGS*/
extern void __pv_err(int32 id_num, char *s, ...)
{
 va_list va, va2, va3;
 int32 slen;
 char vpis1[IDLEN], vpis2[4*IDLEN], *vpichp; 

 __pv_err_cnt++;
 if (!__no_errs)
  {
   if (__vpierr_cb_active && !__iact_state)
    {
     /* reset in case user called sim control operation from wrong place */
     __errorcb_suppress_msg = FALSE;

     sprintf(vpis1, "** ERROR** [%d] ", id_num);
     va_start(va, s);
     vsprintf(vpis2, s, va);
     va_end(va);
   
     slen = strlen(vpis1) + strlen(vpis2) + 1;
     vpichp = __my_malloc(slen);
     strcpy(vpichp, vpis1);
     strcat(vpichp, vpis2);

     __cberror_fill_einfo(ERROR, id_num, vpichp, "[NONE]", 0);
     __vpi_error_trycall();

     __my_free(vpichp, slen);
     /* if vpi_control used to suppress emsg, used up so turn off here */ 
     if (__errorcb_suppress_msg)
      { __errorcb_suppress_msg = FALSE; return; }
    }
   __my_fprintf(stdout, "** ERROR** [%d] ", id_num);

   /* SJM 10/13/99 - ansii std says varargs not usable after vprintf called */
   va_start(va2, s);
   va_start(va3, s);
   __my_vfprintf(stdout, s, va2, va3);
   va_end(va2);
   va_end(va3);

   my_putc_('\n', stdout);
  }
 if (__run_state == SS_SIM) 
 if ((__run_state == SS_COMP || __run_state == SS_LOAD) 
  && __max_errors != 0 && __pv_err_cnt > __max_errors)
  __pv_terr(id_num, "maximum error count exceeded");
}

/*VARARGS*/
extern void __pv_ferr(int32 id_num, char *s, ...)
{
 va_list va, va2, va3;
 int32 slen;
 char vpis1[IDLEN], vpis2[4*IDLEN], *vpichp; 

 __pv_err_cnt++;
 if (__iact_state)
  {
   /* SJM 10/13/99 - ansii std says varargs not usable after vprintf called */
   va_start(va, s);
   va_start(va2, s);
   __via_err(id_num, s, va, va2);
   va_end(va);
   va_end(va2);
   return;
  } 

 if (!__no_errs)
  {
   if (__vpierr_cb_active)
    {
     /* reset in case user called sim control operation from wrong place */
     __errorcb_suppress_msg = FALSE;

     sprintf(vpis1, "**%s(%d) ERROR** [%d] ", __cur_fnam, __lin_cnt, id_num);
     va_start(va, s);
     vsprintf(vpis2, s, va);
     va_end(va);
   
     slen = strlen(vpis1) + strlen(vpis2) + 1;
     vpichp = __my_malloc(slen);
     strcpy(vpichp, vpis1);
     strcat(vpichp, vpis2);

     __cberror_fill_einfo(ERROR, id_num, vpichp, __cur_fnam, __lin_cnt);
     __vpi_error_trycall();

     __my_free(vpichp, slen);
     /* if vpi_control used to suppress emsg, used up so turn off here */ 
     if (__errorcb_suppress_msg)
      { __errorcb_suppress_msg = FALSE; return; }
    }
   __my_fprintf(stdout, "**%s(%d) ERROR** [%d] ", __cur_fnam, __lin_cnt,
    id_num);

   /* SJM 10/13/99 - ansii std says varargs not usable after vprintf called */
   va_start(va2, s);
   va_start(va3, s);
   __my_vfprintf(stdout, s, va2, va3);
   va_end(va2);
   va_end(va3);
   my_putc_('\n', stdout);
  }
 if ((__run_state == SS_COMP || __run_state == SS_LOAD) 
  && __max_errors != 0 && __pv_err_cnt > __max_errors)
  __pv_terr(id_num, "maximum error count exceeded");
}

/*VARARGS*/
extern void __sgferr(int32 id_num, char *s, ...)
{
 va_list va, va2, va3;
 int32 slen;
 char vpis1[IDLEN], vpis2[4*IDLEN], *vpichp; 
 char s1[RECLEN], s2[RECLEN];

 __pv_err_cnt++;
 if (!__no_errs)
  {
   if (__run_state == SS_SIM)
    sprintf(s1, " now %s", __to_timstr(s2, &__simtime)); 
   else strcpy(s1, "");

   if (__vpierr_cb_active && !__iact_state)
    {
     /* reset in case user called sim control operation from wrong place */
     __errorcb_suppress_msg = FALSE;

     sprintf(vpis1, "**%s(%d) ERROR**%s [%d] ", __in_fils[__sfnam_ind],
      __slin_cnt, s1, id_num);
     va_start(va, s);
     vsprintf(vpis2, s, va);
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

   __my_fprintf(stdout, "**%s(%d) ERROR**%s [%d] ", __in_fils[__sfnam_ind],
    __slin_cnt, s1, id_num);

   /* SJM 10/13/99 - ansii std says varargs not usable after vprintf called */
   va_start(va2, s);
   va_start(va3, s);
   __my_vfprintf(stdout, s, va2, va3);
   va_end(va2);
   va_end(va3);
   my_putc_('\n', stdout);
  }
 if ((__run_state == SS_COMP || __run_state == SS_LOAD) 
  && __max_errors != 0 && __pv_err_cnt > __max_errors)
  __pv_terr(id_num, "maximum error count exceeded");
}

/*VARARGS*/
extern void __gferr(int32 id_num, word32 gfnam_ind, int32 gflin_cnt,
 char *s, ...)
{
 va_list va, va2, va3;
 int32 slen;
 char vpis1[IDLEN], vpis2[4*IDLEN], *vpichp; 
 char s1[RECLEN], s2[RECLEN];

 __pv_err_cnt++;
 if (!__no_errs)
  {
   if (__run_state == SS_SIM)
    sprintf(s1, " now %s", __to_timstr(s2, &__simtime)); 
   else strcpy(s1, "");

   if (__vpierr_cb_active && !__iact_state)
    {
     /* reset in case user called sim control operation from wrong place */
     __errorcb_suppress_msg = FALSE;

     sprintf(vpis1, "**%s(%d) ERROR**%s [%d] ", __in_fils[gfnam_ind],
      gflin_cnt, s1, id_num);
    
     va_start(va, s);
     vsprintf(vpis2, s, va);
     va_end(va);
   
     slen = strlen(vpis1) + strlen(vpis2) + 1;
     vpichp = __my_malloc(slen);
     strcpy(vpichp, vpis1);
     strcat(vpichp, vpis2);

     __cberror_fill_einfo(ERROR, id_num, vpichp, __in_fils[gfnam_ind],
      gflin_cnt);
     __vpi_error_trycall();

     __my_free(vpichp, slen);
     /* if vpi_control used to suppress emsg, used up so turn off here */ 
     if (__errorcb_suppress_msg)
      { __errorcb_suppress_msg = FALSE; return; }
    }

   __my_fprintf(stdout, "**%s(%d) ERROR**%s [%d] ", __in_fils[gfnam_ind],
    gflin_cnt, s1, id_num);

   /* SJM 10/13/99 - ansii std says varargs not usable after vprintf called */
   va_start(va2, s);
   va_start(va3, s);
   __my_vfprintf(stdout, s, va2, va3);
   va_end(va2);
   va_end(va3);
   my_putc_('\n', stdout);
  } 
 if ((__run_state == SS_COMP || __run_state == SS_LOAD) 
  && __max_errors != 0 && __pv_err_cnt > __max_errors)
  __pv_terr(id_num, "maximum error count exceeded");
}

/*
 * interactive command error
 * this output still goes to log file 
 * notice this routine does not increment err number
 */
/*VARARGS*/
extern void __ia_err(int32 id_num, char *s, ...)
{
 va_list va, va2;

 /* can suppress any interactive error */
 if (__em_suppr(id_num)) return;

 /* SJM 10/13/99 - ansii std says varargs not usable after vprintf called */
 va_start(va, s);
 va_start(va2, s);
 __via_err(id_num, s, va, va2);
 va_end(va);
 va_end(va2);
} 

/*VARARGS*/
extern void __via_err(int32 id_num, char *s, va_list args, va_list args2)
{
 if (__cmd_s == NULL) __my_fprintf(stdout, "--CMD ERROR** [%d] ", id_num);
 else __my_fprintf(stdout, "--%s(%d) CMD ERROR** [%d] ", __cmd_fnam,
  __lin_cnt, id_num);
 __my_vfprintf(stdout, s, args, args2);
 my_putc_('\n', stdout);
}

/*VARARGS*/
extern void __pv_warn(int32 id_num, char *s, ...)
{
 va_list va, va2, va3;
 int32 slen;
 char vpis1[IDLEN], vpis2[4*IDLEN], *vpichp; 

 __pv_warn_cnt++;
 if (__no_warns || __em_suppr(id_num)) return;

 if (__vpierr_cb_active && !__iact_state)
  {
   /* reset in case user called sim control operation from wrong place */
   __errorcb_suppress_msg = FALSE;

   sprintf(vpis1,"** WARN** [%d] ", id_num);
   va_start(va, s);
   vsprintf(vpis2, s, va);
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

 __my_fprintf(stdout,"** WARN** [%d] ", id_num);

 /* SJM 10/13/99 - ansii std says varargs not usable after vprintf called */
 va_start(va2, s);
 va_start(va3, s);
 __my_vfprintf(stdout, s, va2, va3);
 va_end(va2);
 va_end(va3);
 my_putc_('\n', stdout);
}

/*VARARGS*/
extern void __pv_fwarn(int32 id_num, char *s, ...)
{
 va_list va, va2, va3;
 int32 slen;
 char vpis1[IDLEN], vpis2[4*IDLEN], *vpichp; 

 __pv_warn_cnt++;
 if (__no_warns || __em_suppr(id_num)) { va_end(va); return; }

 if (__iact_state)
  {
   /* SJM 10/13/99 - ansii std says varargs not usable after vprintf called */
   va_start(va, s);
   va_start(va2, s);
   __via_err(id_num, s, va, va2);
   va_end(va);
   va_end(va2);
   return;
  } 

 if (__vpierr_cb_active)
  {
   /* reset in case user called sim control operation from wrong place */
   __errorcb_suppress_msg = FALSE;

   sprintf(vpis1, "**%s(%d) WARN** [%d] ", __cur_fnam, __lin_cnt, id_num);
   va_start(va, s);
   vsprintf(vpis2, s, va);
   va_end(va);
   
   slen = strlen(vpis1) + strlen(vpis2) + 1;
   vpichp = __my_malloc(slen);
   strcpy(vpichp, vpis1);
   strcat(vpichp, vpis2);

   __cberror_fill_einfo(WARN, id_num, vpichp, __cur_fnam, __lin_cnt);
   __vpi_error_trycall();

   __my_free(vpichp, slen);
   /* if vpi_control used to suppress emsg, used up so turn off here */ 
   if (__errorcb_suppress_msg)
    { __errorcb_suppress_msg = FALSE; return; }
  }

 __my_fprintf(stdout, "**%s(%d) WARN** [%d] ", __cur_fnam, __lin_cnt, id_num);

 /* SJM 10/13/99 - ansii std says varargs not usable after vprintf called */
 va_start(va2, s);
 va_start(va3, s);
 __my_vfprintf(stdout, s, va2, va3);
 va_end(va2);
 va_end(va3);
 my_putc_('\n', stdout);
}

/*VARARGS*/
extern void __sgfwarn(int32 id_num, char *s, ...)
{
 va_list va, va2, va3;
 int32 slen;
 char vpis1[IDLEN], vpis2[4*IDLEN], *vpichp; 
 char s1[RECLEN], s2[RECLEN];

 __pv_warn_cnt++;
 if (__no_warns || __em_suppr(id_num)) return;

 if (__run_state == SS_SIM)
  sprintf(s1, " now %s", __to_timstr(s2, &__simtime)); 
 else strcpy(s1, "");

 if (__vpierr_cb_active && !__iact_state)
  {
   /* reset in case user called sim control operation from wrong place */
   __errorcb_suppress_msg = FALSE;

   sprintf(vpis1, "**%s(%d) WARN**%s [%d] ", __in_fils[__sfnam_ind],
    __slin_cnt, s1, id_num);

   va_start(va, s);
   vsprintf(vpis2, s, va);
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

 __my_fprintf(stdout, "**%s(%d) WARN**%s [%d] ", __in_fils[__sfnam_ind],
  __slin_cnt, s1, id_num);

 /* SJM 10/13/99 - ansii std says varargs not usable after vprintf called */
 va_start(va2, s);
 va_start(va3, s);
 __my_vfprintf(stdout, s, va2, va3);
 va_end(va2);
 va_end(va3);
 my_putc_('\n', stdout);
}

/*VARARGS*/
extern void __gfwarn(int32 id_num, word32 gfnam_ind, int32 gflin_cnt,
 char *s, ...)
{
 va_list va, va2, va3;
 int32 slen;
 char vpis1[IDLEN], vpis2[4*IDLEN], *vpichp; 
 char s1[RECLEN], s2[RECLEN];

 __pv_warn_cnt++;
 if (__no_warns || __em_suppr(id_num)) return;

 if (__run_state == SS_SIM)
  sprintf(s1, " now %s", __to_timstr(s2, &__simtime)); 
 else strcpy(s1, "");

 if (__vpierr_cb_active && !__iact_state)
  {
   /* reset in case user called sim control operation from wrong place */
   __errorcb_suppress_msg = FALSE;

   sprintf(vpis1, "**%s(%d) WARN**%s [%d] ", __in_fils[gfnam_ind],
    gflin_cnt, s1, id_num);

   va_start(va, s);
   vsprintf(vpis2, s, va);
   va_end(va);
   
   slen = strlen(vpis1) + strlen(vpis2) + 1;
   vpichp = __my_malloc(slen);
   strcpy(vpichp, vpis1);
   strcat(vpichp, vpis2);

   __cberror_fill_einfo(WARN, id_num, vpichp, __in_fils[gfnam_ind],
    gflin_cnt);
   __vpi_error_trycall();

   __my_free(vpichp, slen);
   /* if vpi_control used to suppress emsg, used up so turn off here */ 
   if (__errorcb_suppress_msg)
    { __errorcb_suppress_msg = FALSE; return; }
  }

 __my_fprintf(stdout, "**%s(%d) WARN**%s [%d] ", __in_fils[gfnam_ind],
  gflin_cnt, s1, id_num);

 /* SJM 10/13/99 - ansii std says varargs not usable after vprintf called */
 va_start(va2, s);
 va_start(va3, s);
 __my_vfprintf(stdout, s, va2, va3);
 va_end(va2);
 va_end(va3);
 my_putc_('\n', stdout);
}

/*
 * interactive command warning
 * this output still goes to log file 
 * notice this routine does not increment warn number
 */
/*VARARGS*/
extern void __ia_warn(int32 id_num, char *s, ...)
{
 va_list va, va2;

 if (id_num >= 1700) __arg_terr(__FILE__, __LINE__);
 /* can suppress any interactive error */
 if (__em_suppr(id_num)) return;

 /* SJM 10/13/99 - ansii std says varargs not usable after vprintf called */
 va_start(va, s);
 va_start(va2, s);
 __via_warn(id_num, s, va, va2);
 va_end(va);
 va_end(va2);
} 

/*VARARGS*/
extern void __via_warn(int32 id_num, char *s, va_list args, va_list args2)
{
 if (__cmd_s == NULL) __my_fprintf(stdout, "--CMD WARN** [%d] ", id_num);
 else __my_fprintf(stdout, "--%s(%d) CMD WARN** [%d] ", __cmd_fnam,
  __lin_cnt, id_num);
 __my_vfprintf(stdout, s, args, args2);
 my_putc_('\n', stdout);
}

/*VARARGS*/
extern void __inform(int32 id_num, char *s, ...)
{
 va_list va, va2, va3;
 int32 slen;
 char vpis1[IDLEN], vpis2[4*IDLEN], *vpichp; 

 __inform_cnt++;
 if (__no_informs || __em_suppr(id_num)) return;

 if (__vpierr_cb_active && !__iact_state)
  {
   /* reset in case user called sim control operation from wrong place */
   __errorcb_suppress_msg = FALSE;

   sprintf(vpis1, "--INFORM: [%d] ", id_num);
   va_start(va, s);
   vsprintf(vpis2, s, va);
   va_end(va);
   
   slen = strlen(vpis1) + strlen(vpis2) + 1;
   vpichp = __my_malloc(slen);
   strcpy(vpichp, vpis1);
   strcat(vpichp, vpis2);

   __cberror_fill_einfo(INFORM, id_num, vpichp, "[NONE]", 0);
   __vpi_error_trycall();

   __my_free(vpichp, slen);
   /* if vpi_control used to suppress emsg, used up so turn off here */ 
   if (__errorcb_suppress_msg)
    { __errorcb_suppress_msg = FALSE; return; }
  }

 __my_fprintf(stdout, "--INFORM: [%d] ", id_num);

 /* SJM 10/13/99 - ansii std says varargs not usable after vprintf called */
 va_start(va2, s);
 va_start(va3, s);
 __my_vfprintf(stdout, s, va2, va3);
 va_end(va2);
 va_end(va3);
 my_putc_('\n', stdout);
}

/*VARARGS*/
extern void __finform(int32 id_num, char *s, ...)
{
 va_list va, va2, va3;
 int32 slen;
 char vpis1[IDLEN], vpis2[4*IDLEN], *vpichp; 

 __inform_cnt++;
 if (__no_informs || __em_suppr(id_num)) return;

 if (__vpierr_cb_active && !__iact_state)
  {
   /* reset in case user called sim control operation from wrong place */
   __errorcb_suppress_msg = FALSE;

   sprintf(vpis1, "--%s(%d) INFORM-- [%d] ", __cur_fnam, __lin_cnt, id_num);
   va_start(va, s);
   vsprintf(vpis2, s, va);
   va_end(va);
   
   slen = strlen(vpis1) + strlen(vpis2) + 1;
   vpichp = __my_malloc(slen);
   strcpy(vpichp, vpis1);
   strcat(vpichp, vpis2);

   __cberror_fill_einfo(INFORM, id_num, vpichp, __cur_fnam, __lin_cnt);
   __vpi_error_trycall();

   __my_free(vpichp, slen);
   /* if vpi_control used to suppress emsg, used up so turn off here */ 
   if (__errorcb_suppress_msg)
    { __errorcb_suppress_msg = FALSE; return; }
  }

 __my_fprintf(stdout, "--%s(%d) INFORM-- [%d] ", __cur_fnam,
  __lin_cnt, id_num);

 /* SJM 10/13/99 - ansii std says varargs not usable after vprintf called */
 va_start(va2, s);
 va_start(va3, s);
 __my_vfprintf(stdout, s, va2, va3);
 va_end(va2);
 va_end(va3);
 my_putc_('\n', stdout);
}

/*VARARGS*/
extern void __sgfinform(int32 id_num, char *s, ...)
{
 va_list va, va2, va3;
 int32 slen;
 char vpis1[IDLEN], vpis2[4*IDLEN], *vpichp; 
 char s1[RECLEN], s2[RECLEN];

 __inform_cnt++;
 if (__no_informs || __em_suppr(id_num)) return;

 if (__run_state == SS_SIM)
  sprintf(s1, " now %s", __to_timstr(s2, &__simtime)); 
 else strcpy(s1, "");

 if (__vpierr_cb_active && !__iact_state)
  {
   /* reset in case user called sim control operation from wrong place */
   __errorcb_suppress_msg = FALSE;

   sprintf(vpis1, "--%s(%d) INFORM--%s [%d] ", __in_fils[__sfnam_ind],
    __slin_cnt, s1, id_num);
   va_start(va, s);
   vsprintf(vpis2, s, va);
   va_end(va);
   
   slen = strlen(vpis1) + strlen(vpis2) + 1;
   vpichp = __my_malloc(slen);
   strcpy(vpichp, vpis1);
   strcat(vpichp, vpis2);

   __cberror_fill_einfo(INFORM, id_num, vpichp, __in_fils[__sfnam_ind],
    __slin_cnt);
   __vpi_error_trycall();

   __my_free(vpichp, slen);
   /* if vpi_control used to suppress emsg, used up so turn off here */ 
   if (__errorcb_suppress_msg)
    { __errorcb_suppress_msg = FALSE; return; }
  }

 __my_fprintf(stdout, "--%s(%d) INFORM--%s [%d] ", __in_fils[__sfnam_ind],
  __slin_cnt, s1, id_num);

 /* SJM 10/13/99 - ansii std says varargs not usable after vprintf called */
 va_start(va2, s);
 va_start(va3, s);
 __my_vfprintf(stdout, s, va2, va3);
 va_end(va2);
 va_end(va3);
 my_putc_('\n', stdout);
}

/*VARARGS*/
extern void __gfinform(int32 id_num, word32 gfnam_ind, int32 gflin_cnt,
 char *s, ...)
{
 va_list va, va2, va3;
 int32 slen;
 char vpis1[IDLEN], vpis2[4*IDLEN], *vpichp; 
 char s1[RECLEN], s2[RECLEN];

 __inform_cnt++;
 if (__no_informs || __em_suppr(id_num)) return;

 if (__run_state == SS_SIM)
  sprintf(s1, " now %s", __to_timstr(s2, &__simtime));
 else strcpy(s1, "");

 if (__vpierr_cb_active && !__iact_state)
  {
   /* reset in case user called sim control operation from wrong place */
   __errorcb_suppress_msg = FALSE;

   sprintf(vpis1, "--%s(%d) INFORM--%s [%d] ", __in_fils[gfnam_ind],
    gflin_cnt, s1, id_num);
   va_start(va, s);
   vsprintf(vpis2, s, va);
   va_end(va);
   
   slen = strlen(vpis1) + strlen(vpis2) + 1;
   vpichp = __my_malloc(slen);
   strcpy(vpichp, vpis1);
   strcat(vpichp, vpis2);

   __cberror_fill_einfo(INFORM, id_num, vpichp, __in_fils[gfnam_ind],
    gflin_cnt);
   __vpi_error_trycall();

   __my_free(vpichp, slen);
   /* if vpi_control used to suppress emsg, used up so turn off here */ 
   if (__errorcb_suppress_msg)
    { __errorcb_suppress_msg = FALSE; return; }
  }

 __my_fprintf(stdout, "--%s(%d) INFORM--%s [%d] ", __in_fils[gfnam_ind],
  gflin_cnt, s1, id_num);

 /* SJM 10/13/99 - ansii std says varargs not usable after vprintf called */
 va_start(va2, s);
 va_start(va3, s);
 __my_vfprintf(stdout, s, va2, va3);
 va_end(va2);
 va_end(va3);
 my_putc_('\n', stdout);
}

/*
 * return T if this message marked to be suppressed
 * if warnings off all suppressed
 */
extern int32 __em_suppr(int32 id)
{
 word32 w;
 int32 bi, wi;

 /* AIV 06/22/09 - make these all 32 not WBITS for 64 - always 32 */
 bi = id % INTBITS;
 wi = id / INTBITS;
 w = __wsupptab[wi];
 if ((w & (1L << bi)) != 0) return(TRUE);
 return(FALSE);
}

/*
 * my fprintf - normal fprintf except if f is stdout then also to log file
 *
 * SJM 10/13/99 - ansii std says varargs not usable after vprintf called
 */
/*VARARGS*/
extern void __my_fprintf(FILE *f, char *s, ...)
{
 va_list va, va2;

 va_start(va, s);
 va_start(va2, s);
 vfprintf(f, s, va);
 if (f == stdout && __log_s != NULL) vfprintf(__log_s, s, va2);
 va_end(va);
 va_end(va2);
}

/*
 * version of my fprintf when caller passed variable arg list 
 *
 * SJM 10/13/99 - ansii std says varargs not usable after vprintf called
 */
extern void __my_vfprintf(FILE *f, char *s, va_list args, va_list args2)
{
 vfprintf(f, s, args);
 if (f == stdout && __log_s != NULL) vfprintf(__log_s, s, args2);  
}
