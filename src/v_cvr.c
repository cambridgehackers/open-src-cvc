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
 * file to write various toggle reports and also initialization of tgl counts
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdarg.h>

#ifdef __linux__
#include <sys/types.h>
#include <sys/wait.h>
#endif

#ifndef __NOSIGS__
#include <signal.h>
#endif

#ifdef __DBMALLOC__
#include "../malloc.h"
#endif

#include "v.h"
#include "cvmacros.h"

/* local prototypes */
static void write_toggle_coverage_report(void);
static void bld_tgl_mods_ndx(void);
static int mod_name_cmp(const void *, const void *);
static void write_old_style_tgl_coverage_report(FILE *);
static int32 any_bit_can_tgl(struct mod_t *, struct net_t *, int32);
static int32 get_net_toggle_blen(struct mod_t *, struct net_t *);
static int32 print_toggle_net_coverage(FILE *, struct mod_t *, struct net_t *,
 char *, int32, word32 *, word32 *, word32 *);
static int32 get_net_toggle_blen(struct mod_t *, struct net_t *);
static void print_hits_misses(FILE *, char *, int32, int32, int32);
static int32 get_toggle_count(struct mod_t *, struct net_t *, word32 *,
 int32 *);
static void set_peribits_excluded_from_optcfg_as_tgl(void);
static void concise_untoggled_report(FILE *);
//SJM 08-26-13 PUTMEBACK? - static void output_1sig_untgl(FILE *, struct rt_tgl_t *);
extern void __output_1sig_untgl(FILE *, struct rt_tgl_t *, int32);
static char *bld_unnormalized_rng_str(char *s, int32, int32, int32, int32);
static int32 fnd_same_tgl_select(struct rt_tgl_t *, int32, int32 *, int32);
// SJM 08-26-13 PUTMEBACK?? - static int32 all_sig_bits_tgl(struct rt_tgl_t *, int32);
extern int32 __all_sig_bits_tgl(struct rt_tgl_t *, int32);
static int32 all_sig_bits_included(struct net_t *, int32, int32 *);
static int32 no_sig_bits_drvn_const(struct net_t *, int);
static void dsgn_tot_insts_sigs_bits(int32 *, int32 *, int32 *, int32 *,
 int32 *, int32 *, int32 *, int32 *, int32 *);
static void mod_tot_sigs_bits(struct mod_t *, int32 *, int32 *, int32 *,
 int32 *, int32 *, int32 *, int32 *, int32 *, int32 *);
static void add_tot_1inst_sigs_bits(struct itree_t *, int32 *, int32 *,
 int32 *, int32 *, int32 *, int32 *, int32 *, int32 *);

static void write_tgldat_file(void);
static void wr_1net_tgldat(FILE *, struct itree_t *, char *, struct net_t *);
static char *tgldat_itree_to_rtpth(struct itree_t *);

static void set_1fil_tgl_seen_flds(FILE *);
static int32 rd_1net_tgldat_rec(FILE *);
static char *isolate_tgldat_el(char *, int32);
static char *collect_cnv_tgldat_rng(char *, int32 *, int32 *);
static int32 xtrct_short_tgl_values(char *, char *, char *);
static int32 bld_tgl_val_array_from_list(int32 *, int32, char *, char *);
static int32 get_tgl_val(char *, char *, int32 *, char *);
static struct net_t *match_tgldat_rtpth_to_inst_net(char *, char *, int32,
 int32, struct itree_t **);
static void set_1net_init_tgl_state(struct net_t *, struct itree_t *,
 int32 *, int32 *);

static int32 skip_stmt_cover(struct st_t *);
static int32 skip_ahead_one_stmt(struct st_t *);
static void set_drvn_const_as_if_tgled(void);
static void bld_perib_drvn_const_tab(void);
static void get_npp_const_id_rng(struct net_pin_t *, struct itree_t *,
 int32 *, int32 *, int32 *, int32 *);
static int32 rhs_net_no_perbit_drvn_con(struct net_t *, struct expr_t *);
static struct xstk_t *cnvrt_rhs_xpr_to_con_bit_string(struct itree_t *,
 struct expr_t *);
static int32 try_set_xpr_cant_be_const(struct expr_t *);
static int32 tgl_xpr_all_known_const_wires(struct itree_t *, struct expr_t *);
static int32 tgl_is_const_xpr(struct expr_t *);
static int32 try_set_1inst_drvn_const_bits(struct net_t *, struct itree_t *,
 int32, int32);
static int32 net_itree_loc_allbits_marked(struct itree_t *, struct net_t *); 
static int32 net_itree_loc_rngbits_marked(struct itree_t *, struct net_t *,
 int32, int32);
static int32 net_itree_loc_allbits_marked(struct itree_t *, struct net_t *); 
static void alloc_drvn_const_rec(void);
static void free_drvn_const_tgl_ds(void);
static void concise_drvn_const_report(FILE *);
static void print_1sig_drvn_const(FILE *, struct net_t *, struct itree_t *);
static int32 fnd_same_drvn_const_select(struct net_t *, int32, int32 *,
 struct itree_t *itp);
static void add_tot_1inst_drvn_const_bits(struct itree_t *, int32 *, int32 *,
 int32 *);
static void dsgn_tot_insts_drvn_const_bits(int *, int32 *, int32 *, int32 *);
static void mod_tot_drvn_const_bits(struct mod_t *, int32 *, int32 *,
 int32 *, int32 *);

/* extern prototypes (maybe defined in this module) */
extern void __process_exit_tgl_output(void);
extern void __dbg_dmp_bad_tgl_ofs(struct mod_t *, t_midat *, struct net_t *,
 struct net_toggle_t *, char *);
extern void __rd_set_from_tgldat_toggled(void);
extern void __write_not_triggered_events(void);
extern void __write_uncovered_stmts(void);

extern void __write_dctrl(FILE *, struct delctrl_t *);
extern void __dmp_stmt(FILE *, struct st_t *, int32);
extern int32 __unnormalize_ndx(struct net_t *, int32);
extern int32 __unnormalize2_ndx(int32, int32, int32);
extern void __getwir_range(struct net_t *, int32 *, int32 *);
extern void __regab_disp(word32 *, word32 *, int32, int32, int32, int32);
extern void __lhsbsel(word32 *, int32, word32);
extern void __grow_xstk(void);
extern void __chg_xstk_width(struct xstk_t *, int32);
extern struct xstk_t *__eval2_xpr(struct expr_t *);
extern int32 __wide_vval_is0(word32 *, int32);
extern int32 __vval_is1(word32 *, int32);
extern int32 __is_const_expr(struct expr_t *);
extern int32 __isleaf(struct expr_t *);
extern ssize_t __my_getline(char **, size_t *, FILE *);
extern char *__my_malloc(size_t);
extern char *__my_realloc(void *, size_t, size_t);
extern void __my_free(void *, size_t);
extern FILE *__tilde_fopen(char *, char *);
extern void __my_fclose(FILE *);
extern char __tgldat_writer_date[RECLEN]; /* id info from input .tgldat file */
extern struct sy_t *__get_sym(char *, struct symtab_t *);
extern struct expr_t *__glbnam_to_expr(char *);
extern int32 __ip_indsrch(char *);
extern char *__to_glbcmp_nam(struct expr_t *);
extern char *__bld_glbcmp_ginam(char *, struct expr_t *);
extern char *__pv_stralloc(char *);
extern char *__msg_idp_blditree(char *, t_midat *, struct task_t *);
extern char *__msg2_blditree(char *, struct itree_t *);
extern char *__to_sytyp(char *, word32);

extern void __dbg_msg(char *, ...);
extern void __cv_msg(char *, ...);
extern void __pv_warn(int32, char *,...);
extern void __pv_fwarn(int32, char *, ...);
extern void __os_exit_misc_terr(char *, int32);

extern const word32 __masktab[];

/* some local to this module variables since report writing separate */
static struct mod_t **__tgl_mods_ndx;
static int32 __tgl_num_mods;


/*
 * ROUTINES TO DUMP TOGGLE INFORMATION
 */

/*
 * routine to process toggle coverage - maybe need to build const
 * only called if some kind of toggle coverage output needed (tgl cvrge on)
 *
 * data structure to simplify and dump data here also
 */
extern void __process_exit_tgl_output(void)
{
 if (__verbose)
  {
   __cv_msg("  Processing exit toggle data and producing toggle reports.\n");
  }

 if (__drvn_const_as_tgled)
  { 
   bld_perib_drvn_const_tab();
   /* set the constant bits that can never toggled as toggled so do */ 
   /* not appear in report which is looking for un exercised logic */
   set_drvn_const_as_if_tgled();
   /* need report or tracing? */
  }
 write_toggle_coverage_report();

 if (__wr_tgldat_on) write_tgldat_file();

 /* SJM 11-04-12 - only free if allocated */ 
 /* SJM 10-28-13 - now needed by writing toggle so can only free last */
 if (__drvn_const_as_tgled) free_drvn_const_tgl_ds();
}

/*
 * wrapper so additional different types of toggle reports can be written
 */
static void write_toggle_coverage_report(void)
{
 FILE *fp;

 /* open file to write to */
 if ((fp = __tilde_fopen(__toggle_coverage_file_name, "w")) == NULL)
  {
   __pv_warn(4331, 
    "cannot open toggle coverage file %s - skipping toggle coverage report",
     __toggle_coverage_file_name);
   return;
  }

//SJM 11-03-12 - LOOKATME? - if choose concise other older reports ignored
 /* new style concise toggle coverage reporting */
 if (__untgled_rpt_concise || __drvn_const_rpt_concise)
  {
   /* build sorted indices if not built - only need if writing reports */
   /* or emit tgldat file */
   if (__tgl_mods_ndx == NULL) bld_tgl_mods_ndx();

 
   if (__drvn_const_rpt_concise)
    {
     if (!__drvn_const_as_tgled)
      {
       __pv_warn(4333, 
        "no report of driven by chains of constant drivers wires written - option -mark_driven_const_toggled not used.");
      }
     else
      {
       concise_drvn_const_report(fp);
       if (__verbose)
        {
         __cv_msg(
          "  New toggle wire bits driven by constants report written to %s.\n",
          __toggle_coverage_file_name);
        }
      }
    }

   if (__untgled_rpt_concise)
    {
     /* first mark all bits which are set to untoggled from optconfig file */
     /* as toggled - whether or not they were really toggled */
     /* SJM 04-26-13 - too slow to exclude recording of bits */
     set_peribits_excluded_from_optcfg_as_tgl();

     concise_untoggled_report(fp);
 
    if (__verbose)
     {
      __cv_msg( "  New style untoggled coverage report written to %s.\n",
      __toggle_coverage_file_name);
     }
    } 
   __my_fclose(fp);
   return;
  }

 /* SJM 10-31-12 - currently old style coverage reports do not use sorting */ 
 write_old_style_tgl_coverage_report(fp);
 __my_fclose(fp);
 if (__verbose)
  {
   __cv_msg( "  Old style untoggled coverage report written to %s.\n",
   __toggle_coverage_file_name);
  }
}

/*
 * build the mods ndx - needed for untgl concise rpt and .tgldat writing
 * only called if not already built
 *
  * build a sorted module name index for order in report file
  * just a convenient ordering
 */
static void bld_tgl_mods_ndx(void)
{
 int32 mi;
 struct mod_t *mdp;

 /* count but leave out those without toggle coverage */
 for (__tgl_num_mods = 0, mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   if (!mdp->m_has_toggle_cover) continue;
   __tgl_num_mods++;
  }
 __tgl_mods_ndx = (struct mod_t **)
  malloc(__tgl_num_mods*sizeof(struct mod_t *));

 for (mi = 0, mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   if (!mdp->m_has_toggle_cover) continue;
   __tgl_mods_ndx[mi++] = mdp;
  }
 qsort(__tgl_mods_ndx, __tgl_num_mods, sizeof(struct mod_t *), mod_name_cmp);
}

/*
 * sort by module name
 */
static int32 mod_name_cmp(const void *m1, const void *m2)
{
 return(strcmp((*((struct mod_t **) m1))->msym->synam,
  (*(struct mod_t **) m2)->msym->synam));
}

// ##########################################################################
// ##########################################################################
// ##########################################################################

/*
 * BEGINNING OF OLD STYLE REPORTING ROUTINES
 */

/*
 * emit a toggle report
 * format depends on following options:
 * __old toggle rpt_instance;    // T => report per instance
 * __old toggle rpt_bits;        // T => report per bit 
 * __old toggle rpt.uncovered;          // T => report uncoverd bits 
 * __old toggle rpt covered;            // T => report covered bits 
 *
 * default is per module without dumping individual net toggle values
 */
static void write_old_style_tgl_coverage_report(FILE *fp)
{
 int32 ni, i, wi, max_net_slen, slen, max_net_blen, ninsts;
 int32 hits01, hits10, nnets;
 int32 mod_nbits, mod_hits01, mod_hits10;
 int32 inst_nbits, inst_hits01, inst_hits10;
 int32 accum_nbits, accum_hits01, accum_hits10;
 int32 max_net_count, wlen, some_printed;
 word32 **net_count01, **net_count10;
 word32 *zero_bp, *c01wp, *c10wp;
 t_midat *idp;
 struct mod_t *mdp;
 struct net_t *np;
 struct rt_tgl_t *togp;
 struct inst_t *ip;
 char s1[RECLEN];

 /* print header info */
 fprintf(fp, "\n \
                            ************************************************\n \
                            **                                            **\n \
                            **  CVC - Verilog Toggle Coverage Report      **\n \
                            **                                            **\n \
                            **  Generated :  %s                           **\n \
                            ************************************************", 
    __pvdate);

 fprintf(fp, "\n\n\n");
 net_count01 = net_count10 = NULL;
 max_net_slen = 0;
 max_net_blen = 0;
 max_net_count = 0;
 /* need toggle info storage if dumping per net coverage info */
 if (__old_toggle_rpt_uncovered || __old_toggle_rpt_covered)
  {
   for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
    {
     if (!mdp->m_has_toggle_cover) continue;
     if (mdp->mnnum > max_net_count) max_net_count = mdp->mnnum;
    }
   net_count01 = (word32 **) __my_malloc(max_net_count*sizeof(word32));
   net_count10 = (word32 **) __my_malloc(max_net_count*sizeof(word32));
  }


 accum_nbits = 0;
 accum_hits01 = 0;
 accum_hits10 = 0;
 /* get info per module */
 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   if (!mdp->m_has_toggle_cover) continue;
   /* get the number of instances with toggle coverage on */
   ninsts = 0;
   for (i = 0; i < mdp->flatinum; i++)
    {
     if (mdp->m_itps_tgl_cover[i] == 0) continue;
     ninsts++;
    }

   /* get the number of nets with toggle coverage on */
   nnets = 0;
   for (ni = 0, np = &(mdp->mnets[0]); ni < mdp->mnnum; ni++, np++) 
    {
     if (!np->n_has_toggle) continue;
     nnets++;
    }

   if (ninsts == 0) ninsts = 1;
   fprintf(fp, "==================================================================================================\n");
   fprintf(fp, "MODULE : %s (%d INSTANCE(S), %d NET(S)) [%s : %d]\n", 
     mdp->msym->synam, ninsts, nnets, 
     __in_fils[mdp->msym->syfnam_ind], mdp->msym->sylin_cnt);
   fprintf(fp, "==================================================================================================\n");
   mod_nbits = 0;
   mod_hits01 = 0;
   mod_hits10 = 0;
   /* get coverage totals per instance */
   for (i = 0; i < mdp->flatinum; i++)
    {
     if (mdp->m_itps_tgl_cover[i] == 0) continue;
     idp = mdp->moditps[i]->it_idp;

     inst_nbits = 0;
     inst_hits01 = 0;
     inst_hits10 = 0;
     if (mdp->flatinum > 1 && __old_toggle_rpt_instance)
      {
       __cur_sofs = 0;
       __msg_idp_blditree(__xs, idp, NULL);
       ip = mdp->moditps[i]->itip;
       fprintf(fp, "\n\n\tINSTANCE : %s  [%s : %d]\n", 
        __xs, __in_fils[ip->isym->syfnam_ind], ip->isym->sylin_cnt);
      }
     
     max_net_slen = 0;
     max_net_blen = 0;
     /* get coverage totals for each net */
     for (ni = 0, np = &(mdp->mnets[0]); ni < mdp->mnnum; ni++, np++) 
      {
       if (!np->n_has_toggle) continue;
       /* DBG remove -- */
       if (np->ntgp == NULL) __os_exit_misc_terr(__FILE__, __LINE__);
       /* --- */
       togp = (struct rt_tgl_t *) idp[np->ntgp->toggle_ofs];
       /* get the toggle counts */
       get_toggle_count(mdp, np, togp->seen10p, &hits10);
       get_toggle_count(mdp, np, togp->seen01p, &hits01);
       /* AIV 03/05/11 - can now turn off toggle per bit */
       /* SJM 04-26-13 - now if any inst included counts as not excluded */
       if (np->n_has_tglbits_excl) inst_nbits += get_net_toggle_blen(mdp, np);
       else inst_nbits += np->nwid;
       inst_hits10 += hits10;
       inst_hits01 += hits01;

       /* record per net coverage info */
       if (net_count01 != NULL)
        {
         wlen = wlen_(np->nwid);
         if (i == 0)
          {
           c01wp = (word32 *) __my_malloc(wlen*WRDBYTES);
           c10wp = (word32 *) __my_malloc(wlen*WRDBYTES);
           memset(c01wp, 0, wlen*WRDBYTES);
           memset(c10wp, 0, wlen*WRDBYTES);
           net_count01[ni] = c01wp;
           net_count10[ni] = c10wp;
          }
         else
          {
           c01wp = net_count01[ni];
           /* AIV 09/15/11 - this was the wrong one should be 10 */
           c10wp = net_count10[ni];
          }
         /* or in the values for module coverage - any instance */
         for (wi = 0; wi < wlen; wi++)
          {
           c01wp[wi] |= togp->seen01p[wi];
           c10wp[wi] |= togp->seen10p[wi];
          }
         slen = strlen(np->nsym->synam);
         if (slen > max_net_slen) max_net_slen = slen;
         if (np->nwid > max_net_blen) max_net_blen = np->nwid;
        }
      }
      /* dummy zeroed b part area  */
     zero_bp = (word32 *) __my_malloc(wlen_(max_net_blen)*WRDBYTES);
     memset(zero_bp, 0, wlen_(max_net_blen)*WRDBYTES);
     /* if more than one module and per istance option */
     if (mdp->flatinum > 1 && __old_toggle_rpt_instance)
      {
       /* add extra length for [index] */
       if (__old_toggle_rpt_bits) max_net_slen += 8;

       /* print instance coverage values */
       print_hits_misses(fp, "\t\t", inst_hits01, inst_hits10, inst_nbits);
       if (__old_toggle_rpt_uncovered || __old_toggle_rpt_covered)
        {
         fprintf(fp, "\n\n\t\t------------------------------------\n");
         if (__old_toggle_rpt_uncovered)
          {
           fprintf(fp, "\t\t SIGNALS NOT GETTING 100%% COVERAGE \n");
          }
         else
          {
           fprintf(fp, "\t\t SIGNALS GETTING 100%% COVERAGE \n");
          }
         fprintf(fp, "\t\t------------------------------------\n");
         memset(s1, ' ', max_net_slen);
         s1[max_net_slen] = '\0';
         if (__old_toggle_rpt_uncovered)
          {
           fprintf(fp, "\t\tSignal  %sToggle\n", s1);
          }
         else fprintf(fp, "\t\tSignal  %s\n", s1);
         fprintf(fp, "\t\t-------------------------------------------------------------------------------------------\n");
         some_printed = FALSE;
         /* print the net coverage info */
         for (ni = 0, np = &(mdp->mnets[0]); ni < mdp->mnnum; ni++, np++) 
          {
           if (!np->n_has_toggle) continue;

           /* DBG remove -- */
           if (np->ntgp == NULL) __os_exit_misc_terr(__FILE__, __LINE__);
           /* --- */
           togp = (struct rt_tgl_t *) idp[np->ntgp->toggle_ofs];
           some_printed |= print_toggle_net_coverage(fp, mdp, np, "\t\t", 
             max_net_slen, togp->seen01p, togp->seen10p, zero_bp);
          }
         if (!some_printed) 
          {
           if (__old_toggle_rpt_uncovered)
            {
             fprintf(fp, "\t\t ** ALL SIGNALS 100%% COVERED ** \n");
            }
           else fprintf(fp, "\t\t ** NO SIGNALS 100%% COVERED **\n");
          }
         
         __my_free(zero_bp, wlen_(max_net_blen)*WRDBYTES);
        }
      }

     /* add up all modules bits */
     mod_nbits += inst_nbits;
     mod_hits10 += inst_hits10;
     mod_hits01 += inst_hits01;
    }
     
   /* sum of instances if > 1 */
   if (mdp->flatinum > 1)
    {
     fprintf(fp, "\n\n\tACCUMULATED INSTANCES (%d) of MODULE %s:\n", 
      ninsts, mdp->msym->synam);
    }
   print_hits_misses(fp, "\t\t", mod_hits01, mod_hits10, mod_nbits);

   /* entire module (any instances) coverage */
   if (__old_toggle_rpt_uncovered || __old_toggle_rpt_covered)
    {
     fprintf(fp, "\n\n\t-----------------------------------------------------------\n");
     if (mdp->flatinum > 1)
      {
       fprintf(fp, "\t-- MODULE (%s) ANY INSTANCE COVERAGE \n", 
        mdp->msym->synam);
      }
     else
      {
       fprintf(fp, "\t-- MODULE (%s) COVERAGE \n", mdp->msym->synam);
      }
     fprintf(fp, "\t-----------------------------------------------------------\n");
     if (mdp->flatinum > 1)
      {
       if (__old_toggle_rpt_uncovered)
        {
         fprintf(fp, "\t SIGNALS NOT GETTING 100%% COVERAGE OVER ANY INSTANCES\n");
        }
       else
        {
         fprintf(fp, "\t SIGNALS GETTING 100%% COVERAGE OVER ANY INSTANCES\n");
        }
       }
     else
      {
       if (__old_toggle_rpt_uncovered)
        {
         fprintf(fp, "\t SIGNALS NOT GETTING 100%% COVERAGE\n");
        }
       else
        {
         fprintf(fp, "\t SIGNALS GETTING 100%% COVERAGE\n");
        }
       }
 
     fprintf(fp, "\t-----------------------------------------------------------\n");
     zero_bp = (word32 *) __my_malloc(wlen_(max_net_blen)*WRDBYTES);
     memset(zero_bp, 0, wlen_(max_net_blen)*WRDBYTES);

     memset(s1, ' ', max_net_slen);
     s1[max_net_slen] = '\0';
     if (__old_toggle_rpt_uncovered) fprintf(fp, "\tSignal  %sToggle\n", s1);
     else fprintf(fp, "\tSignal  %s\n", s1);
     fprintf(fp, "\t-------------------------------------------------------------------------------------------\n");
     some_printed = FALSE;
     for (ni = 0, np = &(mdp->mnets[0]); ni < mdp->mnnum; ni++, np++) 
      {
       if (!np->n_has_toggle) continue;
       some_printed |= print_toggle_net_coverage(fp, mdp, np, "\t",
        max_net_slen, net_count01[ni], net_count10[ni], zero_bp);
      }
     if (!some_printed) 
      {
       if (__old_toggle_rpt_uncovered)
            fprintf(fp, "\t ** ALL SIGNALS 100%% COVERED **\n");
       else fprintf(fp, "\t ** NO SIGNALS 100%% COVERED ** \n");
       }
     }
   accum_hits10 += mod_hits10;
   accum_hits01 += mod_hits01;
   accum_nbits += mod_nbits;
   fprintf(fp, "\n\n");
  }
 fprintf(fp, "==================================================================================================\n");
 /* all toggled bits */
 fprintf(fp, "ALL TOGGLED BITS:\n");
 print_hits_misses(fp, "\t", accum_hits01, accum_hits10, accum_nbits);
 /* leaking memory for array of pointers - but exiting after this */
 if (net_count01 != NULL)
  {
   __my_free(net_count01, max_net_count*sizeof(word32));
   __my_free(net_count10, max_net_count*sizeof(word32));
  }
}

/*
 * return T if any bit not excluded - called bit toggled (meaning bit can
 * toggle I think)
 */
static int32 any_bit_can_tgl(struct mod_t *mdp, struct net_t *np, int32 bi)
{
 int32 ii, bval;
 word32 *excl_wp;

 /* DBG remove -- */
 if (np->ntgp == NULL) __os_exit_misc_terr(__FILE__, __LINE__);
 /* --- */
 excl_wp = np->ntgp->peribits_tgl_rpt_exclude;
 /* no exclude records so not all excluded */
 if (excl_wp == NULL) return(TRUE);

 for (ii = 0; ii < mdp->flatinum; ii++)
  {
   if (np->ntgp->peri_tgl_on[ii] == 0) continue;

   bval = rhsbsel_(excl_wp, (ii*mdp->flatinum) + bi);
   /* 1 is excluded - once found one, return T */
   if (bval == 0) return(TRUE);
  }
 return(FALSE);
}

/*
 * return the number of bits not excluded for net which has some bits excluded
 * SJM 04-26-13 - notice this returns the number turned on
 */         
static int32 get_net_toggle_blen(struct mod_t *mdp, struct net_t *np)
{
 int32 bi, ii, num, bsel, bval;
 word32 *wp;

 num = 0;
 /* for each bit see if bit is turned on and inc count */
 wp = np->ntgp->peribits_tgl_rpt_exclude;
 /* if no exclude mechanism, then blen is net width */
 if (wp == NULL) return(np->nwid);

 for (bi = 0; bi < np->nwid; bi++)
  {
   bsel = 0;
   for (ii = 0; ii < mdp->flatinum; ii++)
    {
     /* if excluded, i.e. turned off, return 1 so 0 is turned on */ 
     bval = rhsbsel_(wp, (ii*np->nwid) + bi);
     /* if bit turned off, then net toggle - really not excluded count */
     if (bval == 0) bsel = 1;
    }
   if (bsel) num++;
  }
 return(num);
}
     
/*
 * print one nets toggle coverage 
 */
static int32 print_toggle_net_coverage(FILE *fp, struct mod_t *mdp,
struct net_t *np, char *icp, int32 max_net_slen, word32 *seen01p,
 word32 *seen10p, word32 *zero_bp)
{
 int32 bi, biti, slen, some_printed, bit_toggled;
 int32 hits01, hits10, covered10, covered01, bit_covered01, bit_covered10;
 char s1[RECLEN], s2[RECLEN];

 /* get the toggle count for the net */
 covered10 = get_toggle_count(mdp, np, seen10p, &hits10);
 covered01 = get_toggle_count(mdp, np, seen01p, &hits01);
 some_printed = FALSE;
 /* report the uncovered nets */
 if (__old_toggle_rpt_uncovered)
  {
   /* if not covered - report net */
   if (!covered10 || !covered01) 
    { 
     /* scalarize - if per bit */
     if (__old_toggle_rpt_bits && np->nwid > 1)
      {
       for (bi = 0; bi < np->nwid; bi++)
        {
         /* AIV 03/05/11 - can now turn off toggle per bit */
         if (any_bit_can_tgl(mdp, np, bi)) bit_toggled = 1;
         else bit_toggled = 0;

         /* this is reallty bit can toggle */ 
         if (!bit_toggled) continue;
 
         biti = __unnormalize_ndx(np, bi);
         /* AIV 03/04/11 - had these backwars 10/01 */
         bit_covered01 = rhsbsel_(seen01p, bi);
         bit_covered10 = rhsbsel_(seen10p, bi);
         if (!bit_covered01 || !bit_covered10)
          {
           sprintf(s1, "%s[%d]", np->nsym->synam, biti);
           slen = strlen(s1);
           memset(s2, '.', max_net_slen-slen+7);
           s2[max_net_slen-slen+7] = '\0';
           fprintf(fp, "%s%s%s 0->1: %d\n", icp, s1, s2, bit_covered01);

           memset(s2, '.', max_net_slen+7);
           s2[max_net_slen+7] = '\0';
           fprintf(fp, "%s%s 1->0: %d\n", icp, s2, bit_covered10);
           some_printed = TRUE;
          }
        }
      }
     else
      {
       /* if not per bit - print the toggle vector */
       __cur_sofs = 0;
       __regab_disp(seen01p, zero_bp, np->nwid, BHEX, -1, FALSE);
       slen = strlen(np->nsym->synam);
       memset(s2, '.', max_net_slen-slen+7);
       s2[max_net_slen-slen+7] = '\0';
       fprintf(fp, "%s%s%s 0->1: %d'h%s\n", icp, np->nsym->synam, s2, 
         np->nwid, __exprline);
       memset(s2, '.', max_net_slen+7);
       s2[max_net_slen+7] = '\0';
       __cur_sofs = 0;
       __regab_disp(seen10p, zero_bp, np->nwid, BHEX, -1, FALSE);
       fprintf(fp, "%s%s 1->0: %d'h%s\n", icp, s2, np->nwid, __exprline);
       some_printed = TRUE;
      }
    }
  }
 else
  {
   /* print the covered nets */
   if (__old_toggle_rpt_bits && np->nwid > 1)
    {
     for (bi = 0; bi < np->nwid; bi++)
      {
       /* AIV 03/05/11 - can now turn off toggle per bit */
       if (any_bit_can_tgl(mdp, np, bi)) bit_toggled = 1; else bit_toggled = 0;
       if (!bit_toggled) continue;

       biti = __unnormalize_ndx(np, bi);
       bit_covered01 = rhsbsel_(seen10p, bi);
       bit_covered10 = rhsbsel_(seen01p, bi);
       if (bit_covered01 && bit_covered10)
        {
         fprintf(fp, "%s%s[%d]\n", icp, np->nsym->synam, biti);
         some_printed = TRUE;
        }
      }
    }
   else if (covered10 && covered01) 
    { 
     fprintf(fp, "%s%s\n", icp, np->nsym->synam);
     some_printed = TRUE;
    }
  }
 return(some_printed);
}

/*
 * print the number of hits/misses
 */
static void print_hits_misses(FILE *fp, char *indentp, int32 hits01, 
 int32 hits10, int32 nbits)
{
 int32 percenth01, percenth10, second_column;
 int32 miss01, miss10, slen;
 char s1[RECLEN], s2[RECLEN];

 miss01 = nbits - hits01;
 miss10 = nbits - hits10;

 if (nbits == 0) percenth01 = 0;
 else percenth01 = (int32) (100.0*((double) hits01)/((double) nbits));
 if (nbits == 0) percenth10 = 0;
 else percenth10 = (int32) (100.0*((double) hits10)/((double) nbits));

 fprintf(fp, "%s", indentp);
 fprintf(fp, "----------------------------         ----------------------------\n");
 fprintf(fp, "%s", indentp);
 fprintf(fp, "       TOGGLE 0 -> 1                      TOGGLE 1 -> 0\n");  
 fprintf(fp, "%s", indentp);
 fprintf(fp, "----------------------------         ----------------------------\n");
 sprintf(s1, "%shits : %d", indentp, hits01); 
 second_column = 37 + strlen(indentp);
 slen = strlen(s1);
 memset(s2, ' ', second_column - slen);
 s2[second_column - slen] = '\0';
 fprintf(fp, "%s%shits : %d\n", s1, s2, hits10);

 sprintf(s1, "%smiss : %d", indentp, miss01); 
 slen = strlen(s1);
 memset(s2, ' ', second_column - slen);
 s2[second_column - slen] = '\0';
 fprintf(fp, "%s%smiss : %d\n", s1, s2, miss10);


 sprintf(s1, "%sbits : %d", indentp, nbits); 
 slen = strlen(s1);
 memset(s2, ' ', second_column - slen);
 s2[second_column - slen] = '\0';
 fprintf(fp, "%s%sbits : %d\n", s1, s2, nbits);

 sprintf(s1, "%spercent hit : %d%%", indentp, percenth01);
 slen = strlen(s1);
 memset(s2, ' ', second_column - slen);
 s2[second_column - slen] = '\0';
 fprintf(fp, "%s%spercent hit : %d%%\n", s1, s2, percenth10);
}
                   
/*
 * get a net's toggle count set to *hits
 * return TRUE if 100% coverage
 */
static int32 get_toggle_count(struct mod_t *mdp, struct net_t *np,
 word32 *seenp, int32 *hits)
{
 int32 count, wlen, i, i2, bit_toggled, bit_on, nwid;

 count = 0;
 /* scalar just get the low word */
 nwid = 1;
 if (!np->n_isavec)
  {
   count = seenp[0];
  }
 else
  {
   /* AIV 03/05/11 - can now turn off toggle per bit */
   /* SJM - new per inst bit toggle on requires changing this */
   /* DBG remove -- */
   if (np->ntgp->peribits_tgl_rpt_exclude == NULL)
    __os_exit_misc_terr(__FILE__, __LINE__);
   /* --- */
   nwid = 0;
   for (i = 0; i < np->nwid; i++)
    {
     bit_toggled = any_bit_can_tgl(mdp, np, i);
     /* if toggle bit on see if it is on */
     if (bit_toggled)
      {
       nwid++;
       bit_on = rhsbsel_(seenp, i);
       if (bit_on) count++;
      }
     else
      {
       /* get entire word (maybe wide) toggle count */
       nwid = np->nwid;
       wlen = wlen_(nwid);
       for (i2 = 0; i2 < wlen; i2++)
        {
         count += __builtin_popcountl(seenp[i2]);
        }
      }
    }
  }
 /* if hit count == width 100% coverage */
 *hits = count;
 return((count == nwid));
}

/*
 * END OF OLD STYLE REPORTING ROUTINES
 */

// ##########################################################################
// ##########################################################################
// ##########################################################################

/*
 * ROUTINES TO PRINT THE UNTOGGLED CONCISE REPORT
 */

/*
 * first step before printing concise untoggled report mark excluded toggled
 *
 * after here excluded bits will not be seen because market toggled
 * driven const also marked toggled in other place - untogged rep
 *
 */
static void set_peribits_excluded_from_optcfg_as_tgl(void)
{
 int32 ni, ii, bi, bit_excld;
 word32 *excl_wp;
 t_midat *idp;
 struct mod_t *mdp;
 struct net_t *np; 
 struct rt_tgl_t *togp;

 /* all mods all nets with tgl on */
 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   if (!mdp->m_has_toggle_cover) continue;

   for (ni = 0, np = &(mdp->mnets[0]); ni < mdp->mnnum; ni++, np++)
    { 
     if (!np->n_has_toggle) continue;
     /* if know no bits excluded, nothing to do - common case */
     if (!np->n_has_tglbits_excl) continue;

     /* DBG remove -- */
     if (np->ntgp == NULL || np->ntgp->peribits_tgl_rpt_exclude == NULL)
      __os_exit_misc_terr(__FILE__, __LINE__);
     /* --- */
     for (ii = 0; ii < mdp->flatinum; ii++)
      {
       /* if inst toggle coverage not on, do not check bit excludes */
       if (np->ntgp->peri_tgl_on[ii] == 0) continue;

       /* get the run time recorded change vals from idp area */
       idp = mdp->moditps[ii]->it_idp;
       /* SJM 08-30-13 - check toggle offset bad */ 
       /* DBG REMOVEME 10-24-13 -- */ 
       if (np->ntgp->toggle_ofs == 0)
        { 
         __dbg_dmp_bad_tgl_ofs(mdp, idp, np, np->ntgp, "mark excluded");
        }
       /* --- */
       togp = (struct rt_tgl_t *) idp[np->ntgp->toggle_ofs];

       /* SJM 06-13-13 - here any order works - using the bsel */
       for (bi = 0; bi < np->nwid; bi++)
        {
         /* excluded means bit is 1 */
         excl_wp = np->ntgp->peribits_tgl_rpt_exclude;
         /* SJM 11-18-13 - think possible for no vector if no excluding */
         if (excl_wp == NULL) bit_excld = 0;
         else bit_excld = rhsbsel_(excl_wp, (ii*mdp->flatinum) + bi); 

         /* excluded means bit position is a 1, not excluded is 0 */
         if (bit_excld == 0) continue;
 
         /* SJM 10-09-13 - seen 0->1/1->0 not used if drvn con or exclude */
         /* bit is excluded so mark that both 0->1 and 1->0 tgls seen */
         __lhsbsel(togp->seen01p, bi, 1);
         __lhsbsel(togp->seen10p, bi, 1);
        }
      } 
    }
  }
}

/*
 * DBG proc to dump bad toggle ofs field
 *
 * SJM 08-30-13 - passing tgp so can look at on/exclude bits if needed
 */
extern void __dbg_dmp_bad_tgl_ofs(struct mod_t *mdp, t_midat *idp,
 struct net_t *np, struct net_toggle_t *ntgp, char *locmsg)
{
 __cv_msg("==> in %s mod %s net %s no tgl record area from %s\n",
  __msg_idp_blditree(__xs, idp, NULL), mdp->msym->synam, np->nsym->synam,
  locmsg);
 __os_exit_misc_terr(__FILE__, __LINE__);
}

/*
 * print to fp the untoggled concise report - eliminate anything toggled
 *
 * never called unless design has at least one net
 *
 * SJM 04-26-13 - only new change is that itree include/exclude from 
 * optconfigfil not right and if peri per net bits excluded not seen
 * as untoggled in this report now 
 *
 * SJM 10-09-13 - now reports have excl bits and drvn const bits in reports
 * and totals
 */
static void concise_untoggled_report(FILE *fp)
{
 int32 mi, ii, ni, mod_has_untgl, inst_has_untgl, dsgn_has_untgl;
 int32 tot_insts, tot_sigs, tot_bits, tot_tgls, tot_01_tgls, tot_10_tgls;
 int32 tot_untgls, tot_excl_bits, tot_drvn_con_bits, all_excluded;
 int32 tot_drvn_con_sigs, tot_cor_bits, tot_cor_sigs;
 double d1, d2;
 t_midat *idp;
 struct itree_t *itp;
 struct mod_t *mdp;
 struct net_t *np;
 struct rt_tgl_t *togp;

 fprintf(fp, "** CVC Toggle Coverage from -untoggled_rpt_concise\n");
 fprintf(fp, "** Written : %s\n", __pv_timestamp);
 fprintf(fp, "** By Version : %s%s of %s\n", __vers, __vers2, __ofdt);

 dsgn_has_untgl = FALSE;
 tot_untgls = 0;
 for (mi = 0; mi < __tgl_num_mods; mi++)
  {
   /* SJM 04-30-13 - mod's not included in tgl cover not in mods ndx */
   mdp = __tgl_mods_ndx[mi];

   mod_has_untgl = FALSE;
   for (ii = 0; ii < mdp->flatinum; ii++)
    {
     if (mdp->m_itps_tgl_cover[ii] == 0) continue;

     itp = mdp->moditps[ii]; 
     idp = itp->it_idp;
     inst_has_untgl = FALSE;  
//SJM 10-30-12 - LEAVING OUT TASK VAR COMPLETELY - THINK RIGHT SINCE
//they will be found with better statatement tracing - don't care if task/func
//vars toggled
     for (ni = 0, np = &(mdp->mnets[0]); ni < mdp->mnnum; ni++, np++) 
      {
       if (!np->n_has_toggle) continue;
       /* DBG remove -- */
       if (np->ntgp == NULL) __os_exit_misc_terr(__FILE__, __LINE__);
       /* --- */

       /* SJM 08-30-13 - check toggle offset bad */ 
       /* DBG remove -- */ 
       if (np->ntgp->toggle_ofs == 0)
        { 
         __dbg_dmp_bad_tgl_ofs(mdp, idp, np, np->ntgp, "gen report");
        }
       /* --- */

       togp = (struct rt_tgl_t *) idp[np->ntgp->toggle_ofs];

       if (all_sig_bits_included(np, ii, &(all_excluded))
        && no_sig_bits_drvn_const(np, ii))
        { 
         /* SJM 11-18-13 - T is 01 toggle, F is 10 */
         if (__all_sig_bits_tgl(togp, TRUE)
          && __all_sig_bits_tgl(togp, FALSE)) continue;
        }
       /* SJM 10-28-13 - if entire net exclude, do not include in report */
       if (all_excluded) continue;

       /* has a signal with some bits untoggled */
       if (!mod_has_untgl)
        {
         mod_has_untgl = TRUE;

         fprintf(fp, "MODULE: %s (%d instances) [%s : %d]:\n",
          mdp->msym->synam, mdp->flatinum, __in_fils[mdp->msym->syfnam_ind],
          mdp->msym->sylin_cnt);
        }
       if (!inst_has_untgl)
        {
         inst_has_untgl = TRUE;
         dsgn_has_untgl = TRUE;

         fprintf(fp, "  INSTANCE %s (%d nets) [%s : %d]:\n",
          __msg2_blditree(__xs, itp), mdp->mnnum,
         __in_fils[itp->itip->isym->syfnam_ind], itp->itip->isym->sylin_cnt);
        }
       __output_1sig_untgl(fp, togp, ii);
      }
     if (inst_has_untgl)
      {
       tot_sigs = 0;
       tot_bits = 0;
       tot_tgls = tot_01_tgls = tot_10_tgls = 0;
       tot_excl_bits = tot_drvn_con_bits = tot_drvn_con_sigs = 0; 
       /* SJM 10-24-13 - for inst init is here - was not init excl/drvn con */ 
       /* SJM 11-10-13 - now do not count excluded or driven con bits at all */
       /* idea is that there are per bit 4 possibiities: untoggled, */
       /* toggled, only 0-1 toggle, only 1-0 toggle */
       add_tot_1inst_sigs_bits(itp, &(tot_sigs), &(tot_bits), &(tot_tgls),
        &(tot_01_tgls), &(tot_10_tgls), &(tot_excl_bits), &(tot_drvn_con_bits),
        &(tot_drvn_con_sigs));
       /* SJM 10-08-13 - driven const and excluded bits not counted in stats */
       tot_cor_bits = tot_bits - tot_excl_bits - tot_drvn_con_bits;
       tot_cor_sigs = tot_sigs - tot_drvn_con_sigs;
       if (tot_cor_bits > 0)
        {
         tot_untgls = tot_cor_bits - (tot_tgls + tot_01_tgls + tot_10_tgls);
         d1 = 100.0*((double) tot_untgls)/((double) tot_bits);
         fprintf(fp, "  COVER [%d nets %d bits] untoggled %d bits (%.2f%%)\n",
          tot_cor_sigs, tot_cor_bits, tot_untgls, d1);
         if (tot_10_tgls != 0 || tot_01_tgls != 0)
          {
           d1 = 100.0*((double) tot_10_tgls)/((double) tot_cor_bits);
           d2 = 100.0*((double) tot_01_tgls)/((double) tot_cor_bits);
           fprintf(fp,
            "    1->0 but not 0->1 %d (%.2f%%) 0->1 but not 1->0 %d (%.2f%%)\n",
            tot_10_tgls, d1, tot_01_tgls, d2);
          } 
        }
       if (tot_excl_bits != 0 || tot_drvn_con_bits != 0)
        {
         fprintf(fp,
          "   %d driven to constant bits (%d entire nets), %d excluded bits\n",
          tot_drvn_con_bits, tot_drvn_con_sigs, tot_excl_bits);
        } 
      }
    } 
   /* know will not get here unless toggle coverage on for this mod */ 
   if (mod_has_untgl && mdp->flatinum > 1)
    {
     mod_tot_sigs_bits(mdp, &(tot_insts), &(tot_sigs), &(tot_bits),
      &(tot_tgls), &(tot_01_tgls), &(tot_10_tgls), &(tot_excl_bits),
      &(tot_drvn_con_bits), &(tot_drvn_con_sigs));
     tot_cor_bits = tot_bits - tot_excl_bits - tot_drvn_con_bits;
     tot_cor_sigs = tot_sigs - tot_drvn_con_sigs;
     /* SJM 11-13-13 - this needs to be cor bits or else div by 0 possible */
     if (tot_cor_bits > 0)
      {
       tot_untgls = tot_cor_bits - (tot_tgls + tot_01_tgls + tot_10_tgls);
       d1 = 100.0*((double) tot_untgls)/((double) tot_cor_bits);
       fprintf(fp, "TOTAL MOD %s [%d nets %d bits] untoggled %d (%.2f%%)\n",
        mdp->msym->synam, tot_sigs, tot_bits, tot_untgls, d1);
       if (tot_10_tgls != 0 || tot_01_tgls != 0)
        {
         d1 = 100.0*((double) tot_10_tgls)/((double) tot_cor_bits);
         d2 = 100.0*((double) tot_01_tgls)/((double) tot_cor_bits);
         fprintf(fp,
          "  1->0 but not 0->1 %d (%.2f%%) 0->1 but not 1->0 %d (%.2f%%)\n",
          tot_10_tgls, d1, tot_01_tgls, d2);
        }
      }
     if (tot_excl_bits != 0 || tot_drvn_con_bits != 0)
      {
       fprintf(fp,
        "   %d driven to constant bits (%d entire nets), %d excluded bits\n",
        tot_drvn_con_bits, tot_drvn_con_sigs, tot_excl_bits);
      } 
    }
  }
 tot_cor_bits = 0;
 if (dsgn_has_untgl)
  { 
   if (__has_tgl_optcfg_stmt)
    {
     fprintf(fp,
      "   [TOTALS NOT FOR ENTIRE DESIGN:  -optconfigfile cover_toggle used]\n");
    } 

   dsgn_tot_insts_sigs_bits(&(tot_insts), &(tot_sigs), &(tot_bits),
    &(tot_tgls), &(tot_01_tgls), &(tot_10_tgls), &(tot_excl_bits),
    &(tot_drvn_con_bits), &(tot_drvn_con_sigs));

   tot_cor_bits = tot_bits - tot_excl_bits - tot_drvn_con_bits;
   tot_cor_sigs = tot_sigs - tot_drvn_con_sigs;
   /* SJM 11-13-13 - this needs to be cor bits or else div by 0 possible */
   if (tot_cor_bits > 0)
    {
     tot_untgls = tot_cor_bits - (tot_tgls + tot_01_tgls + tot_10_tgls);
     d1 = 100.0*((double) tot_untgls)/((double) tot_cor_bits);
     d2 = 100.0*((double) tot_tgls)/((double) tot_cor_bits);
     /* SJM 11-13-13 - this needs to be cor bits or else div by 0 possible */
     if (tot_cor_bits > 0)
      {
       tot_untgls = tot_cor_bits - (tot_tgls + tot_01_tgls + tot_10_tgls);
       d1 = 100.0*((double) tot_untgls)/((double) tot_cor_bits);
       d2 = 100.0*((double) tot_tgls)/((double) tot_cor_bits);
       fprintf(fp,
        "** DESIGN [%d nets %d bits] untoggled %d bits (%.2f%%) toggled %d (%.2f%%)\n",
        tot_cor_sigs, tot_cor_bits, tot_untgls, d1, tot_tgls, d2);
       if (tot_10_tgls != 0 || tot_01_tgls != 0)
        {
         d1 = 100.0*((double) tot_10_tgls)/((double) tot_cor_bits);
         d2 = 100.0*((double) tot_01_tgls)/((double) tot_cor_bits);
         fprintf(fp,
          "  1->0 but not 0->1 %d (%.2f%%) 0->1 but not 1->0 %d (%.2f%%)\n",
          tot_10_tgls, d1, tot_01_tgls, d2);
        }
      }
     if (tot_excl_bits != 0 || tot_drvn_con_bits != 0)
      {
       fprintf(fp,
        "   %d driven to constant bits (%d entire nets), %d excluded bits\n",
        tot_drvn_con_bits, tot_drvn_con_sigs, tot_excl_bits);
      } 
    }
  }
 /* SJM 11-18-13 - because of exclude and driven const - may not really */
 /* have untgl */ 
 if (!dsgn_has_untgl || tot_untgls <= 0)
  {
   fprintf(fp,
    "** SUCCESS! EVERY NET IN DESIGN has BOTH 0->1 and 1->0 TOGGLES **\n");
  }
}

/*
 * routine to print per bit lines for one signal
 */
extern void __output_1sig_untgl(FILE *fp, struct rt_tgl_t *togp, int32 ii)
{
 int32 tgl_state, tgl01, tgl10, is_drvn_con, is_excl, bi, nxt_down_bi, r1, r2;
 int32 is_excluded;
 struct net_t *np;
 char s1[RECLEN], s2[RECLEN];

 np = togp->np;
 /* DBG remove -- */
 if (np->n_isarr) __os_exit_misc_terr(__FILE__, __LINE__);
 /* --- */
 /* case 1: scalar */
 if (!togp->np->n_isavec)
  {
   /* for scalar - all is same as the one bit */
   is_excl = !all_sig_bits_included(np, ii, &(is_excluded));
   is_drvn_con = !no_sig_bits_drvn_const(np, ii);
   /* togp is in idp, so is already correct itree (itp/idp) location */
   tgl01 =  __all_sig_bits_tgl(togp, TRUE);
   tgl10 =  __all_sig_bits_tgl(togp, FALSE);
   if (is_excl)
    {
     fprintf(fp, "    %s: excluded\n", togp->np->nsym->synam); 
    }
   else if (is_drvn_con)
    {
     fprintf(fp, "    %s: driven constant\n", togp->np->nsym->synam); 
    }
   else
    { 
     if (tgl01 && tgl10) return;

     if (!tgl01 && !tgl10) 
      {
       fprintf(fp, "    %s: no toggles\n", togp->np->nsym->synam); 
      }
     else if (tgl01)
      {
       fprintf(fp, "    %s: no 1->0 toggles\n", togp->np->nsym->synam);
      }
     else
      {
       fprintf(fp, "    %s: no 0->1 toggles\n", togp->np->nsym->synam);
      }
    }
   return;
  }
 /* case 2: a vector */
 /* internal storage always h:0 even if l:h form */
 for (bi = togp->np->nwid - 1; bi >= 0; bi--)
  {
   tgl_state = fnd_same_tgl_select(togp, bi, &(nxt_down_bi), ii);
   /* if both toggle, no msg only untoggled interesting */
   /* SJM 05-05-13 - fixed bug can't move down here and have for loop move */
   /* down - say nxt_down_bi is 2 (2 low bits 1 and 0 untgl) then */
   /* this moves to 1 and for moves to 0 - continue caused the dec */
   if (tgl_state == 2) { bi = nxt_down_bi; continue; }

   /* SJM 10-31-12 - all of net means both high same as size-1 and low 0 */ 
   if (togp->np->nwid - 1 == bi && nxt_down_bi == 0)
    {
     sprintf(s2, "<all of net> ");
    }
   else if (bi - nxt_down_bi > 1) sprintf(s2, "<of %d> ", togp->np->nwid);
   else strcpy(s2, "");

   __getwir_range(np, &(r1), &(r2));
   bld_unnormalized_rng_str(s1, bi, nxt_down_bi, r1, r2);
   if (tgl_state == -3)
    {
     fprintf(fp, "    %s%s%s: exclude\n", togp->np->nsym->synam, s1, s2); 
    } 
   else if (tgl_state == -2)
    {
     fprintf(fp, "    %s%s%s: driven constant\n", togp->np->nsym->synam,
      s1, s2); 
    }
   else if (tgl_state == 1)
    {
     /* SJM 11-18-13 - tgl state 1 means 0 to 1 toggled */
     fprintf(fp, "    %s%s%s: no 1->0 toggles\n", togp->np->nsym->synam,
      s1, s2); 
    }
   else if (tgl_state == 0)
    {
     /* SJM 11-18-13 - tgl state 0 means 1 to 0 toggled */
     fprintf(fp, "    %s%s%s: no 0->1 toggles\n", togp->np->nsym->synam,
      s1, s2); 
    }
   else
    {
     fprintf(fp, "    %s%s%s: no toggles\n", togp->np->nsym->synam, s1, s2); 
    }
   /* SJM 05-05-13 - again can't dec here since for loop decs */
   bi = nxt_down_bi;
  }
}

/*
 * build unnormalized vector select range/bit
 */
static char *bld_unnormalized_rng_str(char *s, int32 hind, int32 lind,
 int32 mr1, int32 mr2)
{
 if (hind == lind)
  {
   sprintf(s, "[%d]", __unnormalize2_ndx(hind, mr1, mr2));
  }
 else
  {
   sprintf(s, "[%d:%d]", __unnormalize2_ndx(hind, mr1, mr2),
    __unnormalize2_ndx(lind, mr1, mr2));
  }
 return(s);
}

/*
 * in h:0 world, find range of same value signals and return info
 * return -3 for excluded, -2 for drvn const, -1 for no tgl, 2 for both tgl,
 * 0 for 1->0 tgl, 1 for 0->1 
 *
 * SJM 10-22-13 - notice here separate masks are used for excluded and driven 
 * const so do not need to check for tglcnt 01/10 -1 and -2
 */
static int32 fnd_same_tgl_select(struct rt_tgl_t *togp, int32 selbi,
 int32 *last_same_down_bi, int32 ii)
{
 int32 base, bi, last_tgl_state, nxt_tgl_state, tgl01, tgl10;
 word32 *drvn_con_wp, *excl_wp;
 struct net_t *np;

 np = togp->np;
 base = 0;
 if (np->ntgp->peribits_tgl_rpt_exclude != NULL) 
  { 
   /* SJM 11-18-13 notice per inst bit excluded array is packed to the bit */
   /* 1 is exlcuded, 0 included */
   base = ii*np->nwid;
   excl_wp = np->ntgp->peribits_tgl_rpt_exclude;
  }
 else excl_wp = NULL;

 if (np->ntgp->peribits_drvn_const != NULL)
  {
   drvn_con_wp = np->ntgp->peribits_drvn_const[ii];
  }
 else drvn_con_wp = NULL;

 /* init at impossible value */
 last_tgl_state = -4;
 for (bi = selbi; bi >= 0; bi--)
  {
   /* excluded is 1 */
   if (excl_wp != NULL && (rhsbsel_(excl_wp, base + bi)) == 1)
     nxt_tgl_state = -3;  
   /* SJM 10-24-13 - driven const is 1 not 0 */
   else if (drvn_con_wp != NULL && (rhsbsel_(drvn_con_wp, bi)) == 1)
    nxt_tgl_state = -2;  
   else
    {
     tgl01 = rhsbsel_(togp->seen01p, bi);
     tgl10 = rhsbsel_(togp->seen10p, bi);
     if (tgl01 && tgl10) nxt_tgl_state = 2;
     else if (!tgl01 && !tgl10) nxt_tgl_state = -1;
     else if (tgl01) nxt_tgl_state = 1;
     else nxt_tgl_state = 0; 
    }
   if (last_tgl_state == -4) last_tgl_state = nxt_tgl_state;
   /* notice if this statement breaks, then bit 0 differs */
   else if (last_tgl_state != nxt_tgl_state) break;
  }
 /* if fall thru, i.e entire net, then bi will be -1 */
 if (bi < 0) *last_same_down_bi = 0; else *last_same_down_bi = bi + 1;
 return(last_tgl_state);
}


/*
 * return T if all bits of signal 0->1 or 1->0 toggle
 *
 * scalars still have packed seen01p and seen10p but only low bit of word
 * used
 */
extern int32 __all_sig_bits_tgl(struct rt_tgl_t *togp, int32 for_01_tgl)
{
 int32 bi;
 word32 *wp;

 if (for_01_tgl) wp = togp->seen01p; else wp = togp->seen10p;
 for (bi = 0; bi < togp->np->nwid; bi++)
  {
   if ((rhsbsel_(wp, bi)) == 0) return(FALSE); 
  }
 return(TRUE);
}

/*
 * return T if some signal (net) bits are excluded from toggle coverage
 *
 * SJM 10-09-13 - need new 3rd possibility in report .tgldat file, namely
 * '?' for excluded (usually coded as -1 in internal tgl arrays but not
 * simulation time d.s.)
 *
 * excluded means per inst bit position is turned on to 1 - included is 0
 */
static int32 all_sig_bits_included(struct net_t *np, int32 ii,
 int32 *all_excluded)
{
 int32 bi, base;
 word32 *excl_wp;

 *all_excluded = FALSE; 
 if (!np->n_has_tglbits_excl) return(TRUE);
 /* if no toggle bits at all excluded will not get here */
 /* DBG remove --- */
 if (np->ntgp->peribits_tgl_rpt_exclude == NULL)
  {
   __os_exit_misc_terr(__FILE__, __LINE__);
  }
 /* --- */
 base = ii*np->nwid;
 excl_wp = np->ntgp->peribits_tgl_rpt_exclude;
 /* if no 1, all bits included */
 for (bi = 0; bi < np->nwid; bi++) 
  {
   if ((rhsbsel_(excl_wp, base + bi)) == 1) return(FALSE);
  }
 return(TRUE);
}

/*
 * return T if no signal (net) bits are driven const
 *
 * driven constant for inst bit means value 1
 */
static int32 no_sig_bits_drvn_const(struct net_t *np, int32 ii)
{
 word32 *drvn_con_wp;

 /* if not using driven const at all or a reg, never driven const */
 if (!__drvn_const_as_tgled) return(TRUE);
 if (np->ntyp >= NONWIRE_ST) return(TRUE);

 /* SJM 10-24-13 - know all wires have drivn const if driven const */ 
 /* option selected */
 /* DBG remove -- */
 if (np->ntgp->peribits_drvn_const == NULL)
  {
   __os_exit_misc_terr(__FILE__, __LINE__);
  }
 /* --- */
 drvn_con_wp = np->ntgp->peribits_drvn_const[ii];
 /* if any 1 (some bit driven const) return F */
 if (vval_is0_(drvn_con_wp, np->nwid)) return(TRUE);
 return(FALSE);
}

/*
 * count total number of insts, signals and bits in entire tvcd file (design)
 * also count per bit toggles (both, 0->1 and 1-0)
 */
static void dsgn_tot_insts_sigs_bits(int *tot_insts, int32 *tot_sigs,
 int32 *tot_bits, int32 *tot_tgls, int32 *tot_01_tgls, int32 *tot_10_tgls,
 int32 *tot_excl_bits, int32 *tot_drvn_con_bits, int32 *tot_drvn_con_sigs)
{
 int32 mi, ii;
 struct mod_t *mdp;
 struct itree_t *itp;

 *tot_insts = 0;
 *tot_sigs = 0;
 *tot_bits = 0;
 *tot_tgls = *tot_01_tgls = *tot_10_tgls = 0;
 *tot_excl_bits = *tot_drvn_con_bits = *tot_drvn_con_sigs = 0;
 for (mi = 0; mi < __tgl_num_mods; mi++)
  {
   mdp = __tgl_mods_ndx[mi];

   for (ii = 0; ii < mdp->flatinum; ii++)
    {
     if (mdp->m_itps_tgl_cover[ii] == 0) continue;
     
     itp = mdp->moditps[ii];
     add_tot_1inst_sigs_bits(itp, tot_sigs, tot_bits, tot_tgls, tot_01_tgls,
      tot_10_tgls, tot_excl_bits, tot_drvn_con_bits, tot_drvn_con_sigs);
    }
  }
}

/*
 * count total inst, signals and bits of one module
 * also count per bit toggles (both, 0->1 and 1-0)
 *
 * know will not be called unless toggle coverage on for this mod
 */
static void mod_tot_sigs_bits(struct mod_t *mdp, int32 *tot_insts,
 int32 *tot_sigs, int32 *tot_bits, int32 *tot_tgls, int32 *tot_01_tgls,
 int32 *tot_10_tgls, int32 *tot_excl_bits, int32 *tot_drvn_con_bits,
 int32 *tot_drvn_con_sigs)
{
 int32 ii;
 struct itree_t *itp;

 *tot_insts = 0;
 *tot_sigs = 0;
 *tot_bits = 0;
 *tot_tgls = *tot_01_tgls = *tot_10_tgls = 0;
 *tot_excl_bits = *tot_drvn_con_bits = *tot_drvn_con_sigs = 0;
 /* for every inst of mod type */
 for (ii = 0; ii < mdp->flatinum; ii++)
  {
   /* it is possible for some instance to have toggle cover off */
   if (mdp->m_itps_tgl_cover[ii] == 0) continue;

   (*tot_insts)++;
   itp = mdp->moditps[ii];
   add_tot_1inst_sigs_bits(itp, tot_sigs, tot_bits, tot_tgls, tot_01_tgls,
    tot_10_tgls, tot_excl_bits, tot_drvn_con_bits, tot_drvn_con_sigs);
  }
}

/*
 * count total number of nets and bits for one inst of one mod 
 * if both 0->1 and 1->0 toggle, add count to tot tgls else 01 or 10
 *
 * caller must initialize - this just adds to counts
 */
static void add_tot_1inst_sigs_bits(struct itree_t *itp, int32 *tot_sigs,
 int32 *tot_bits, int32 *tot_tgls, int32 *tot_01_tgls, int32 *tot_10_tgls,
 int32 *tot_excl_bits, int32 *tot_drvn_con_bits, int32 *tot_drvn_con_sigs)
{
 int32 ni, base, bi, tgl01, tgl10, all_of_net_drvn_con;
 word32 *excl_wp, *drvn_con_wp;
 struct mod_t *mdp;
 struct net_t *np;
 struct rt_tgl_t *togp;
 t_midat *idp;

 all_of_net_drvn_con = TRUE;
 mdp = itp->itip->imsym->el.emdp;
 /* mnets tab also has all the net for tasks at end - include */
 for (ni = 0, np = &(mdp->mnets[0]); ni < mdp->mnnum; ni++, np++) 
  {
   if (!np->n_has_toggle) continue;

   /* DBG remove -- */
   if (np->ntgp == NULL) __os_exit_misc_terr(__FILE__, __LINE__);
   /* --- */

   (*tot_sigs)++;
   idp = itp->it_idp;

   /* SJM 08-30-13 - check toggle offset bad */ 
   /* DBG remove -- */ 
   if (np->ntgp->toggle_ofs == 0)
    { 
     __dbg_dmp_bad_tgl_ofs(mdp, idp, np, np->ntgp, "calc totals");
    }
   /* --- */
   togp = (struct rt_tgl_t *) idp[np->ntgp->toggle_ofs];
   *tot_bits = *tot_bits + np->nwid;

   base = 0;
   if (!np->n_has_tglbits_excl) { *tot_excl_bits = 0; excl_wp = NULL; }
   else
    { 
     /* DBG remove */
     if (np->ntgp->peribits_tgl_rpt_exclude == NULL)
      __os_exit_misc_terr(__FILE__, __LINE__);
     /* --- */
     excl_wp = np->ntgp->peribits_tgl_rpt_exclude;
     base = itp->itinum*np->nwid;
    }
   if (np->ntgp->peribits_drvn_const != NULL)
    {
     drvn_con_wp = np->ntgp->peribits_drvn_const[itp->itinum];
    }
   else drvn_con_wp = NULL;
   /* if entire net for this inst driven const, inc tot drvn con sigs */
   /* and do not print anything */

   all_of_net_drvn_con = TRUE;
   for (bi = np->nwid - 1; bi >= 0; bi--)
    {
     if (excl_wp != NULL)
      {
       if ((rhsbsel_(excl_wp, base + bi)) == 1)
        {
         (*tot_excl_bits)++;
         /* SJM 11-13-13 - if any excluded bits, then all of net can't */
         /* be driven const */
         all_of_net_drvn_con = FALSE;
         continue;
        }
      }
     /* driven const is value 1 */
     if (drvn_con_wp != NULL && (rhsbsel_(drvn_con_wp, bi)) == 1)
      {
       (*tot_drvn_con_bits)++;
       continue; 
      }
     all_of_net_drvn_con = FALSE;
     tgl01 = rhsbsel_(togp->seen01p, bi);
     tgl10 = rhsbsel_(togp->seen10p, bi);
     if (tgl01 == 1 && tgl10 == 1) (*tot_tgls)++; 
     else if (tgl01 == 1 && tgl10 == 0) (*tot_01_tgls)++;
     else if (tgl01 == 0 && tgl10 == 1) (*tot_10_tgls)++;
    }
   /* SJM 11-13-13 - need to count nets with all bits drvn con */
   if (all_of_net_drvn_con) (*tot_drvn_con_sigs)++;
  }
}

/*
 * ROUTINES TO DUMP A TGLDAT SIMPLE ASCII FORMAT TGL RECORD FILE
 */

/*
 * write a .tgldat simple ascii file
 *
 * each net starts with module name ':' rooted path name <range>, then 3
 * alternatives:
 *
 * scalar: {0/1};
 * <32 bit vector: {[0/1], ...}{[0/1], ...};
 * >32 bit vector (3 lines):
 *  <module name> : <rooted path <scalar []> or <vector [r1:r2]>
 *  {[0/1], ...}
 *  {[0/1], ...};
 */
static void write_tgldat_file(void)
{
 int32 mi, ii, ni;
 FILE *fp;
 struct mod_t *mdp;
 struct net_t *np;
 struct itree_t *itp;
 char s1[RECLEN];

 /* compiling - just return */
 if (__compiled_sim && !__running_cvc_exe) return;

 /* build sorted indices if not built */
 if (__tgl_mods_ndx == NULL) bld_tgl_mods_ndx();

 /* open file for writing */
 if ((fp = __tilde_fopen(__wr_tgldat_file, "w")) == NULL)
  {
   __pv_warn(4332, 
    "TGL: cannot open .tgldat output coverage results file %s - skipping",
    __wr_tgldat_file);
   return;
  }
 /* nomal header info */
 if (__tgldat_infils_lst_hd == NULL) strcpy(s1, "<none>");
 else strcpy(s1, __tgldat_infils_lst_hd->in_tgldat_fnam);
 fprintf(fp,
  "//writer version: %s%s of %s - a top %s - a .tgldat input %s\n",
  __vers, __vers2, __ofdt, __top_itab[0]->imsym->synam, s1);
 fprintf(fp, "//date: %s\n", __pv_timestamp);

 /* dump all insts - do not need rooted scope downward now */
 /* can just go through mod's itps */
 for (mi = 0; mi < __tgl_num_mods; mi++)
  {
   mdp = __tgl_mods_ndx[mi];

   /* DBG remove -- */
   if (!mdp->m_has_toggle_cover) __os_exit_misc_terr(__FILE__, __LINE__);
   /* --- */

   for (ii = 0; ii < mdp->flatinum; ii++)
    {
     /* if this inst not included, do not write to tgldat file */
     if (mdp->m_itps_tgl_cover[ii] == 0) continue;
     itp = mdp->moditps[ii];
     tgldat_itree_to_rtpth(itp);

     for (ni = 0, np = &(mdp->mnets[0]); ni < mdp->mnnum; ni++, np++)
      {
       if (!np->n_has_toggle) continue;
       /* DBG remove -- */
       if (np->ntgp == NULL) __os_exit_misc_terr(__FILE__, __LINE__);
       /* --- */
       if (np->ntgp->peri_tgl_on[ii] == 0) continue;

       wr_1net_tgldat(fp, itp, __tgl_rtpthnam, np);
      }
    }
  }
}

/*
 * write the tgl dat record for one net
 *
 * SJM 04-20-13 - LOOKATME - this eventually needs tgl counts not 0/1 bits
 * SJM 05-05-13 - notice this will not handle more than 32 bit counts in
 * 32 bit cvc, maybe need ifdefs cvc64 works for 64 bits counts when added
 */
static void wr_1net_tgldat(FILE *fp, struct itree_t *itp, char *rtpth,
 struct net_t *np)
{
 int32 base, bi, nr1, nr2;
 word32 bval, bval01, bval10, *excl_wp, *drvn_con_wp, *wp01, *wp10;
 struct rt_tgl_t *togp;
 t_midat *idp;
 char netrtpth[4*RECLEN], val01str[RECLEN], val10str[RECLEN];

 idp = itp->it_idp;
 sprintf(netrtpth, "%s.%s", rtpth, np->nsym->synam);

 /* SJM 08-30-13 - check toggle offset bad */ 
 /* DBG remove -- */ 
 if (np->ntgp->toggle_ofs == 0)
  { 
   __dbg_dmp_bad_tgl_ofs(itp->itip->imsym->el.emdp, idp, np, np->ntgp,
    "writing 1 net tgl");
  }
 /* --- */
 togp = (struct rt_tgl_t *) idp[np->ntgp->toggle_ofs];
 wp01 = togp->seen01p;
 wp10 = togp->seen10p;

 base = itp->itinum*np->nwid;
 if (np->n_has_tglbits_excl)
  {
   excl_wp = np->ntgp->peribits_tgl_rpt_exclude;
  }
 else excl_wp = NULL;
 /* notice drvn con is a peri ptr unlike excl wp which is peri bit tab */ 
 if (np->ntgp->peribits_drvn_const != NULL)
  {
   drvn_con_wp = np->ntgp->peribits_drvn_const[itp->itinum];
  }
 else drvn_con_wp = NULL;

 /* case 1: scalar */
 if (!np->n_isavec)
  { 
   strcpy(val01str, "");

   if (excl_wp != NULL && (rhsbsel_(excl_wp, base)) == 1)
    {
     strcpy(val01str, "?"); 
     strcpy(val10str, "?");
    }
   /* driven const is value 1 */
   else if (drvn_con_wp != NULL && (rhsbsel_(drvn_con_wp, 0)) == 1)
    {
     strcpy(val01str, "C"); 
     strcpy(val10str, "C"); 
    }
   else
    {
     bval01 = rhsbsel_(wp01, 0);
     sprintf(val01str, "%lu", bval01);
     bval10 = rhsbsel_(wp10, 0);
     sprintf(val10str, "%lu", bval10);
    }
   fprintf(fp, "%s : %s [] {%s} {%s};\n", itp->itip->imsym->synam, netrtpth,
    val01str, val10str);
   return;
  }
 /* case 2: on one line because <32 */
 if (np->nwid <= 32)
  {
   /* DBG remove -- */
   if (!np->n_isavec) __os_exit_misc_terr(__FILE__, __LINE__);
   /* --- */
   __getwir_range(np, &(nr1), &(nr2));
   fprintf(fp, "%s : %s [%d:%d]", itp->itip->imsym->synam, netrtpth,
    nr1, nr2);
   fputs(" {", fp);

   /* SJM 06-13-13 - to be consistent with reader and tvcd and dumpvars */
   /* vectors the high bit (assuming h:0 before l:h normalize) is first */
   /* bit on line */
   /* SJM 11-02-13 - storage is h:0 just as for Verilog vectors in wbits */
   /* words, here rightmost element of comma separated list is low bit */
   for (bi = np->nwid - 1; bi >= 0; bi--)
    {
     if (excl_wp != NULL && (rhsbsel_(excl_wp, base + bi)) == 1)
      {
       strcpy(val01str, "?");
      }
     else if (drvn_con_wp != NULL
      && (rhsbsel_(drvn_con_wp, bi)) == 1) strcpy(val01str, "C");
     else
      { 
       bval = rhsbsel_(wp01, bi);
       sprintf(val01str, "%lu", bval);
      } 
     fprintf(fp, "%s", val01str);
     /* comma after all but last one (low bit rightmost) */
     if (bi != 0) fputc(',', fp);
    }
   fputs("} {", fp);
   /* internal normalized ver h:0 order */
   for (bi = np->nwid - 1; bi >= 0; bi--)
    {
     /* excluded means bit value 1 - do not know if tgled  */
     if (excl_wp != NULL && (rhsbsel_(excl_wp, base + bi)) == 1)
      {   
       strcpy(val10str, "?");
      }
     else if (drvn_con_wp != NULL && (rhsbsel_(drvn_con_wp, bi)) == 1)
      {
       strcpy(val10str, "C");
      }  
     else
      {
       bval = rhsbsel_(wp10, bi);
       sprintf(val10str, "%lu", bval);
      }
     fprintf(fp, "%s", val10str);
     if (bi != 0) fputc(',', fp);
    }
   fputs("};\n", fp);
   return;
  } 
 /* case 3: wider than 32 (not wbits for this) - need 3 lines */
 /* DBG remove -- */
 if (!np->n_isavec) __os_exit_misc_terr(__FILE__, __LINE__);
 /* --- */
 __getwir_range(np, &(nr1), &(nr2));
 fprintf(fp, "%s : %s [%d:%d]\n{", itp->itip->imsym->synam, netrtpth,
  nr1, nr2);
 /* SJM 06-13-13 - need h:0 like internal ver order (low bit 0 rightmost */
 for (bi = np->nwid - 1; bi >= 0; bi--)
  {
   /* excluded means bit value 1 - do not know if tgled  */
   if (excl_wp != NULL && (rhsbsel_(excl_wp, base + bi)) == 1)
    {
     strcpy(val01str, "?");
    } 
   /* driven const is value 1 */
   else if (drvn_con_wp != NULL
    && (rhsbsel_(drvn_con_wp, bi)) == 1) strcpy(val01str, "C");
   else
    {
     bval = rhsbsel_(wp01, bi);
     sprintf(val01str, "%lu", bval);
    } 
   fprintf(fp, "%s", val01str);
   /* comma after all but last one (low bit rightmost) */
   if (bi != 0) fputc(',', fp);
  }
 fputs("}\n{", fp);
 for (bi = np->nwid - 1; bi >= 0; bi--)
  {
   /* excluded means bit value  1 - do not know if tgled  */
   if (excl_wp != NULL && (rhsbsel_(excl_wp, base + bi)) == 1)
    {
     strcpy(val10str, "?");
    }
   /* driven const is value 1 */
   else if (drvn_con_wp != NULL && (rhsbsel_(drvn_con_wp, bi)) == 1)
    {
     strcpy(val10str, "C");
    }
   else
    { 
     bval = rhsbsel_(wp10, bi);
     sprintf(val10str, "%lu", bval);
    }
   fprintf(fp, "%s", val10str);
   if (bi != 0) fputc(',', fp);
  }
 fputs("};\n", fp);
}

/*
 * bld a scope name without task into passed file from itree loc 
 * needed because other routines trunc for error mesages 
 *
 * SJM 04-29-13 - must fill rooted path into glg that can grow in size
 */
static char *tgldat_itree_to_rtpth(struct itree_t *itp)
{
 int32 gi, save_gi;
 int32 slen;

 /* fill from front to end - know at least one component */
 for (gi = 0;;)
  {
   __glbsycmps[gi] = itp->itip->isym;
   /* virtual tops modules have no up entry */
   itp = itp->up_it;
   if (itp == NULL) break;
   if (++gi >= MAXGLBCOMPS) __os_exit_misc_terr(__FILE__, __LINE__);
  }
 /* then fill top end to front - know string nil terminated by last __adds */
 save_gi = gi;
 for (slen = 0; gi >= 0; gi--)
  { 
   slen += strlen(__glbsycmps[gi]->synam); 
   if (gi > 0) slen++;
  }
 slen++;
 gi = save_gi;

 /* if tgl rooted path longer than glb rt path work var, make it large */ 
 if (slen + 5 > __siz_tgl_rtpthnam)
  {
   __tgl_rtpthnam = (char *) __my_realloc(__tgl_rtpthnam, __siz_tgl_rtpthnam,
   slen + RECLEN);
  __siz_tgl_rtpthnam = slen + RECLEN;
  }
 
 strcpy(__tgl_rtpthnam, __glbsycmps[gi]->synam); 
 gi--;
 for (; gi >= 0; gi--)
  { 
   strcat(__tgl_rtpthnam, "."); 
   strcat(__tgl_rtpthnam, __glbsycmps[gi]->synam); 
  }
 return(__tgl_rtpthnam);
}

/*
 * ROUTINES TO READ AND INITIALIZE TOGGLE DATA FROM PREVOUS RUN BEFORE SIM
 */

/*
 * go through list of tgldat infils and set tgled bits when set in file
 * in toggle seen01(10) idp area - called after IDP area set up and inited  
 *
 * only called if at least one .tgldat file specified and only called once
 *
 * SJM 05-02-13 - algorithm is that if a 0->1 or 1->0 bit in init .tgldat
 * list for one net is is 0, no change, but if 1, that bit is marked toggled
 * before sim.  If only on -set_toggled_from_file option then intiaiizes
 * toggle state to its values since 0's match already initialized value.
 * If more, then the set to toggle (tgl state 1) is the or in total of
 * all toggle 1's.  The 0's are ignored
 */
extern void  __rd_set_from_tgldat_toggled(void)
{
 int32 sav_lcnt;
 struct tgldat_in_lst_t *tglifp;
 char sav_curfnam[RECLEN];

 strcpy(sav_curfnam, __cur_fnam);
 sav_lcnt = __lin_cnt;

 /* know mod name ID can not be wider than 1k chars so RECLEN big enough */
 __tgl_modnam = __my_malloc(RECLEN);

 /* assuming size of char is 1 */
 __tglbits01 = __my_malloc(RECLEN);
 __tglbits10 = __my_malloc(RECLEN);
 __siz_tgl_lst = RECLEN;
 __tgl_rtpthnam = __my_malloc(RECLEN);
 __siz_tgl_rtpthnam = RECLEN;
 __siz_tgltabs = 256;
 /* every vector location of net size set so do not init to 0 */
 /* SJM - normal tgl recording values are words but packed to the bit and */ 
 /* masked - but tgl [01/10] tab is an array of toggle bits so int */
 __tgl01tab = (int32 *) __my_malloc(__siz_tgltabs*sizeof(int32));
 __tgl10tab = (int32 *) __my_malloc(__siz_tgltabs*sizeof(int32));

 /* go thru list of tgldat files to start from */
 tglifp = __tgldat_infils_lst_hd; 
 for (; tglifp != NULL; tglifp = tglifp->tgldat_in_nxt)
  {
   __cur_fnam = tglifp->in_tgldat_fnam;
   __lin_cnt = 0;
   strcpy(__tgldat_writer_date, "<none>");
   strcpy(__tgldat_writer_vers, "<none>");
   if ((__in_s = __tilde_fopen(__cur_fnam, "r")) == NULL)
    {
     __pv_warn(4315,
      "TGL: cannot open -init_toggle_from_file .tgldat file %s - skipped",
      __cur_fnam);
      continue;
     }
   if (feof(__in_s))
    {
     __pv_warn(4313,
      "TGL: -set_toggled_from_file .tgldat file %s empty - skipped",
      __cur_fnam);
     continue;
    }
   set_1fil_tgl_seen_flds(__in_s);
   if (__verbose || __tgl_verbose)
    {
     __cv_msg(
      "TGL:  set 0->1 and 1->0 toggled bits from file %s before sim start.\n",
      tglifp->in_tgldat_fnam);
    }
  }

 /* assuming size of char is 1 */
 __my_free(__tglbits01, __siz_tgl_lst);
 __my_free(__tglbits10, __siz_tgl_lst);
 __my_free(__tgl_rtpthnam, __siz_tgl_rtpthnam);
 __my_free(__tgl01tab, __siz_tgltabs*sizeof(int32));
 __my_free(__tgl10tab, __siz_tgltabs*sizeof(int32));

 /* not using includeable get tok type reading so can just copy back */
 /* SJM 04-23-13 - need to str alloc because size may change */
 /* think not really needed but once start reallocing cur fnam must */
 /* always do it */
 __cur_fnam = __pv_stralloc(sav_curfnam);
 __lin_cnt = sav_lcnt;
}

/*
 * initialize the toggle record in idp area seen 01 and 10 toggle bits from
 * one .tgldat file
 *
 * idea is to read .tgldat file entries if can't read,skip
 * if does not match a current design rooted path, skip
 */
static void set_1fil_tgl_seen_flds(FILE *fp)
{
 int32 rv, obytes, nbytes, old_siz_tgltabs;
 struct itree_t *itp;
 struct net_t *np;

 for (;;)
  {
   /* this fill (and maybe grows) one tgl dat net entry into globals */
   /* returns -1 on EOF */
   if ((rv = rd_1net_tgldat_rec(fp)) == -1) break;
   if (rv == 0) continue;

   /* take apart path name - and try to match */
   /* know rooted path to tgl net and tgl initialize vectors in tgl glbs */
   /* if design inst tree has changed, non matches just skipped */
   if ((np = match_tgldat_rtpth_to_inst_net(__tgl_rtpthnam, __tgl_modnam,
    __tgl_r1, __tgl_r2, &(itp))) == NULL) continue;

   if (np->nwid > __siz_tgltabs - 3)
    { 
     old_siz_tgltabs = __siz_tgltabs;
     __siz_tgltabs = (3*old_siz_tgltabs)/2;
     if (__siz_tgltabs < np->nwid + 1024) __siz_tgltabs = np->nwid + 1024;
     obytes = sizeof(int32)*old_siz_tgltabs;
     nbytes = sizeof(int32)*__siz_tgltabs;
     __tgl01tab = (int32 *) __my_realloc(__tgl01tab, obytes, nbytes);
     __tgl10tab = (int32 *) __my_realloc(__tgl10tab, obytes, nbytes);
    }
   if (!bld_tgl_val_array_from_list(__tgl01tab, np->nwid, __tglbits01,
    "0->1")) continue;
   if (!bld_tgl_val_array_from_list(__tgl10tab, np->nwid, __tglbits10,
    "1->0")) continue;
   
   /* use vector to set idp area bits */
   set_1net_init_tgl_state(np, itp, __tgl01tab, __tgl10tab);
  }
}

/* SJM 07-28-13 - use defines so can have vi find match c brackets */
#define LSETBRAK '{'
#define RSETBRAK '}'
#define LSQBRAK '['
#define RSQBRAK ']'

/*
 * read one tgldat vector element into globals __tgl modnam, __tgl rtpthnam,
 * __tgl_r1, __tgl_r2 (-1 for scalar) and __tglbits [_01/_10] 
 *
 * returns -1 on EOF, 1 on success, 0 on error  
 * notice 0->1 and 1->0 toggle vectors include surrounding {}
 * SJM 11-03-13 - this just gets the line as a string - convention is low
 * bit is right most list element but this does not deal with that
 */
static int32 rd_1net_tgldat_rec(FILE *fp)
{
 int32 llen, pthlen, has_err, r1, r2;
 size_t buflen; 
 char *endchp, *linep, *tgl_line;

 tgl_line = NULL;
 has_err = FALSE;
 /* first read one line - know will have at least: [modnam] : [path] [ */
 /* starting point guess, if line longer, proc will update */
 buflen = 4*RECLEN - 1;
 /* get line passed nil so allocs buffer big enough */
 if ((llen = __my_getline(&(tgl_line), &(buflen), fp)) == -1)   
  {
   if (feof(fp)) return(-1);
   __pv_fwarn(4317, "TGL: OS error reading tgldat line - skipped"); 
   return(0);
  }
 /* new line included - remove */
 tgl_line[llen - 1] = '\0';

 /* SJM 09-13-13 - isolate a token - know will be modnam (maybe escaped) */
 endchp = isolate_tgldat_el(tgl_line, ':');
 if (*endchp == '\0')
  {
   /* DBG remove -- */
   if (endchp[-1] != ' ') __os_exit_misc_terr(__FILE__, __LINE__);
   /* --- */
   __pv_fwarn(4317,
    "TGL: .tgldat line module name not follow by ' :' - line skipped"); 
   return(0);
  }
 /* do not include space */
 strncpy(__tgl_modnam, tgl_line, endchp - tgl_line - 1);  
 __tgl_modnam[endchp - tgl_line - 1] = '\0';
 /* move to start of heirarchical path - know separator is " : " */
 linep = endchp + 2;
  
 /* SJM 09-19-13 - read hierarchical path ending with " [" */
 endchp = isolate_tgldat_el(linep, LSQBRAK);
 /* otherwise know end chp is the searched for isolate end char */
 if (*endchp == '\0')
  {
   /* DBG remove -- */
   if (endchp[-1] != ' ') __os_exit_misc_terr(__FILE__, __LINE__);
   /* --- */
   __pv_fwarn(4317,
    "TGL: .tgldat line net hierachical name not followed by range start %c - skipped",
    LSQBRAK);
   return(0);
  }
 pthlen = endchp - linep - 1;
 /* may need to grow line - length does not have room for ending \0 */
 if (pthlen - 3 > __siz_tgl_rtpthnam)
  {
   __tgl_rtpthnam = (char *) __my_realloc(__tgl_rtpthnam,
    __siz_tgl_rtpthnam, pthlen + 100);
   __siz_tgl_rtpthnam = pthlen + 100;
  }
 strncpy(__tgl_rtpthnam, linep, pthlen);
 __tgl_rtpthnam[pthlen] = '\0';
 linep = endchp;

 if (linep[1] == RSQBRAK) 
  {
   /* scalar is [] */
   __tgl_r1 = __tgl_r2 = -1;
   endchp = linep + 2;
  }
 else
  {
   /* collect range  */
   if ((endchp = collect_cnv_tgldat_rng(linep, &(r1), &(r2))) == NULL)
    {
     __pv_fwarn(4317,
      "TGL: .tgldat line net range bad format or illegal ranges - skipped");
     return(0);
    } 
   __tgl_r1 = r1;
   __tgl_r2 = r2;
  } 
 if (*endchp == ' ')
  {
   /* case 1: narrow so toggle groups on same line */
   linep = ++endchp;
   if (*linep != LSETBRAK)
    {
     __pv_fwarn(4317, "TGL: expected 0->1 %c%c narrow toggle group missing - skipped",
      LSETBRAK, RSETBRAK);
     return(0);
    }
   /* the set bracket surrounded comma separated 0->1 tgl and 1->0 extracted */ 
   if (!xtrct_short_tgl_values(linep, __tglbits01, __tglbits10)) return(0);
   return(1);
  } 
 if (*endchp != '\0')
  {
   __pv_fwarn(4317,
     "TGL: wide toggle group net name line extra chars after net range");
   return(0);
  }
 /* case 2: wide vector - 0->1 on next lines and 1->0 on line after */
 /* SJM 09-20-13 - line can be million bits wide since system getline */
 /* mallocs buffer big enough */ 
 if ((llen = __my_getline(&(tgl_line), &(buflen), fp)) == -1)   
  {
   __pv_fwarn(4317,
    "TGL: OS error reading wide vector 0->1 toggle line - skipped");
   has_err = TRUE;
   /* need to try to read both 0->1 and 1->0 even if error */
   goto rd_10_line;
  }
 /* adjust since new line included */ 
 llen--;
 if (tgl_line[0] != LSETBRAK || tgl_line[llen - 1] != RSETBRAK)
  {
   __pv_fwarn(4317,
    "TGL: wide vector 0->1 toggle line malformed - not surrounde by set brackets -skipped");
   has_err = TRUE;
   goto rd_10_line;
  }
 /* know both 0->1 and 1->0 toggle lines will be the same length */
 /* tglbits 01 has comma separate list with surrounding set brackets */
 if (llen - 3 > __siz_tgl_lst)
  {
   __tglbits01 = (char *) __my_realloc(__tglbits01, __siz_tgl_lst,
    llen + 100);
   __tglbits10 = (char *) __my_realloc(__tglbits10, __siz_tgl_lst,
    llen + 100);
   __siz_tgl_lst = llen + 100;
  }
 strcpy(__tglbits01, tgl_line); 
 __tglbits01[llen] = '\0';

rd_10_line:
 if ((llen = __my_getline(&(tgl_line), &(buflen), fp)) == -1)   
  {
   __pv_fwarn(4317, "TGL: OS error reading wide vector 1->0 toggle - skipped");
   return(0);
  }
 /* new line included - remove */
 tgl_line[llen - 1] = '\0';
 llen--;
 if (tgl_line[llen - 1] != ';')
  {
   __pv_fwarn(4317,
    "TGL: wide vector 1->0 toggle line malformed - does not end with ';' - skipped");
  }
 if (tgl_line[0] != LSETBRAK || tgl_line[llen - 2] != RSETBRAK)
  {
   __pv_fwarn(4317,
    "TGL: wide vector 1->0 toggle line malformed - not surrounded by %c%c group or missing ; - skipped",
     LSETBRAK, RSETBRAK);
   return(0);
  }
 /* remove the ending semicolon */
 tgl_line[llen - 1] = '\0';
 strcpy(__tglbits10, tgl_line); 
 if (has_err) return(0);
 return(1);
} 

/*
 * isolate ending char in toggle string - returns ptr to end
 * ptr to end can only point to nil (for EOL) or passed endch in line
 * 
 * if ends with end of line return ptr to nil 
 *
 * format is easy to read because every element ends with space that
 * means escaped IDs just work - needed because escaped spaces legal
 * in escaped IDs 
 */
static char *isolate_tgldat_el(char *linep, int32 endch)
{
 char *chp;

 for (chp = linep;; chp++)
  {
   if (*chp == '\0') return(chp);
   if (*chp == endch)
    {
     if (chp[-1] == ' ')
      {
       if (chp - linep >= 2 && chp[-2] != '\\') break;
      }
    }
  }
 return(chp);
}

/*
 * collect and convert r1:r2 into rng1 and rng2
 *
 * returns one past ending right square bracket - can be EOS for wide form
 * on error, returns nil
 *
 * know not called for [] scalar and has format [<r1 val>:<r2 val>]
 * linep points to the leading left square bracket
 * only decimal numbers allowed
 */
static char *collect_cnv_tgldat_rng(char *linep, int32 *rng1, int32 *rng2)
{
 char *chp, numstr[RECLEN];

 for (chp = ++linep;; chp++)
  {
   if (*chp == '\0' || *chp == RSQBRAK || *chp == LSETBRAK || *chp == RSETBRAK)
    return (NULL);
   if (*chp == ':') break;
  }
 strncpy(numstr, linep, chp - linep); 
 numstr[chp - linep] = '\0';
 if (sscanf(numstr, "%d", rng1) != 1) return(NULL);
 if (*rng1 < 0) return(NULL);
 linep = ++chp;
 for (;; chp++)
  {
   if (*chp == '\0') return (NULL);
   if (*chp == RSQBRAK) break;
  }
 strncpy(numstr, linep, chp - linep); 
 numstr[chp - linep] = '\0';
 if (sscanf(numstr, "%d", rng2) != 1) return(NULL);
 if (*rng2 < 0) return(NULL);
 return(++chp); 
}

/*
 * wrapper to lib getline that skips // comment lines
 */
extern ssize_t __my_getline(char **lineptr, size_t *n, FILE *stream)
{
 ssize_t llen;

 for (;;)
  {
   __lin_cnt++;
   if ((llen = getline(lineptr, n, stream)) != -1)   
    { 
     if ((*lineptr)[0] != '/' || (*lineptr)[1] != '/') break; 
     if (strncmp(*lineptr, "//date:", 7) == 0) 
      {
       (*lineptr)[llen - 1] = '\0';
       strcpy(__tgldat_writer_date, &((*lineptr)[7]));
      }
     else if (strncmp(*lineptr, "//writer version:", 17) == 0) 
      {
       (*lineptr)[llen - 1] = '\0';
       strcpy(__tgldat_writer_vers, &((*lineptr)[17]));
      } 
     /* always skip comment lines */
     continue;
    }
   break;
  }
 return(llen);
}

/*
 * extract short scalar or less up to 32 bit vectors scalar vector lists
 * passed list from starting left set bracket 
 *
 * know tgl bits pass ptrs point to string malloc at least REC LEN
 * which is known wide enough for short
 */
static int32 xtrct_short_tgl_values(char *veclst, char *tglbits01,
 char *tglbits10)
{
 char *chp, *chp2;

 if ((chp = index(veclst, RSETBRAK)) == NULL)
  {
   __pv_fwarn(4317,
    "TGL: malformed .tgldat scalar/short 0->1 toggle list - missing ending %c - skipped",
    RSETBRAK);
   return(FALSE);
  }
 /* include the right set bracket here */ 
 strncpy(tglbits01, veclst, chp - veclst + 1);
 tglbits01[chp - veclst + 1] = '\0';
 chp++;
 if (*chp != ' ' || *(++chp) != LSETBRAK)
  {
bad_10:
   __pv_fwarn(4317,
    "TGL: malformed .tgldat scalar/short 1->0 toggle list - missing starting %c - skipped",
     LSETBRAK);
   return(FALSE);
  }
 if ((chp2 = index(chp, RSETBRAK)) == NULL) goto bad_10;
 /* include ending right bracket */
 strncpy(tglbits10, chp, chp2 - chp + 1);
 /* line does not contain set brackets */
 tglbits10[chp2 - chp + 1] = '\0';
 return(TRUE);
}

/*
 * convert a .tgldat scalar or vector {[val], ... } list to an array of values
 * return FALSE on error 
 *
 * error if number of bits in list does not match passed value
 * order is high to low bits in list, i.e. lsb is right most
 * know tglvectab larg enough to hold all bits of net 
 *
 * here just use large vector - in CVC will know the width
 *
 * SJM 06-13-13 - .tgldat file always stored normalized { [h], ... [0] }
 * so first (rightmost) list element is high bit
 */
static int32 bld_tgl_val_array_from_list(int32 *tglvaltab, int32 nbits,
 char *tglvecstr, char *errstr)
{
 int32 veci, ival;
 char *chp, *chp2, *chp3;

 if (*tglvecstr != LSETBRAK)
  {
   __pv_fwarn(4328,
    "TGL: malformed .tgldat %s toggle value list - missing begin %c - skipped",
    errstr, LSETBRAK);
   return(FALSE);
  }
 chp = &(tglvecstr[1]);
 /* need to start one high than high bit internal h:0 format */
 /* SJM 11-03-13 - fill tab high to low stored h:0 with right bit low bit */ 
 for (veci = nbits;;)
  {
   if ((chp2 = index(chp, ',')) != NULL)
    {
     /* inside list, ends with comma */
     chp3 = chp2 - 1;
     if (!get_tgl_val(chp, chp3, &(ival), errstr)) return(FALSE);
     chp = chp2 + 1;
     goto set_vec;
    }
   if ((chp2 = index(chp, RSETBRAK)) == NULL) 
    {
     __pv_fwarn(4328,
      "TGL: malformed .tgldat %s toggle value list - missing list ending %c - skipped",
      errstr, RSETBRAK);
    }
   /* last element in list, ends with right set bracket */
   chp3 = chp2 - 1;
   if (!get_tgl_val(chp, chp3, &(ival), errstr)) return(FALSE);
   if (--veci != 0)
    {   
     /* SJM 05-02-13 - must match net width exactly */
     __pv_fwarn(4328,
      "TGL: .tgldat %s toggle initial list wrong length %d found but %d expected - skipped",
      errstr, veci + 1, nbits);
     return(FALSE);
    }
   /* SJM 05-02-13 - was not assigning final value from wval */
   tglvaltab[veci] = ival;
   return(TRUE);

set_vec:
   if (--veci < 0)
    {
     __pv_fwarn(4328,
      "TGL: .tgldat %s toggle initial list longer than expected %d - skipped",
      errstr, nbits);
     return(FALSE);
    }
   tglvaltab[veci] = ival;
  }
}

/*
 * scan a number from a value string in a toggle count isolated string
 * returns 1 on success
 *
 * SJM 10-09-13 - new scheme returns -1 for excluded ('?') and -2 for
 * driven to constant ('C')
 */
static int32 get_tgl_val(char *st_chp, char *end_chp, int32 *ival,
 char *errstr)
{
 char valwrk[RECLEN];

 strncpy(valwrk, st_chp, end_chp - st_chp + 1);
 valwrk[end_chp - st_chp + 1] = '\0';
 if (strcmp(valwrk, "?") == 0) *ival = -1;
 else if (strcmp(valwrk, "C") == 0) *ival = -2;
 else if (sscanf(valwrk, "%d", ival) != 1)
  {
   __pv_fwarn(4328, "TGL: illegal toggle value %s in %s list - skipped",
    valwrk, errstr);
   return(FALSE);
  }
 return(TRUE);
}

/*
 * take apart tgldat rooted path and match to [instance tree, net] pair location
 *
 * here only stylized rooted all instance to ending net paths names allowed 
 */
static struct net_t *match_tgldat_rtpth_to_inst_net(char *rtpthnam,
 char *net_modnam, int32 tgl_r1, int32 tgl_r2, struct itree_t **ret_itp)
{
 int32 ii, nr1, nr2, twid;
 byte *bp1, *bp2;
 struct expr_t *glbndp, *gcmp_ndp;
 struct itree_t *itp;
 struct mod_t *mdp;
 struct sy_t *isyp, *arr_isyp;
 struct inst_t *ip;
 struct net_t *np;
 char *chp, s1[RECLEN];
 
 /* convert rooted path name into component as XMR not fixed up expr */
 /* this handles inst selects and escaped names */
 if ((glbndp = __glbnam_to_expr(rtpthnam)) == NULL)
  {
   __pv_fwarn(4342,
    "TGL: illegal .tgldat rooted path %s format - toogle data record skipped",
    rtpthnam);
   return(NULL);
  }

 /* work down from a root inst (same as mod) to last comp next */
 gcmp_ndp = glbndp->ru.x;
 /* know top level rooted first component never indexed */
 chp = __to_glbcmp_nam(gcmp_ndp);

 if ((ii = __ip_indsrch(chp)) == -1)
  {
   __pv_fwarn(4342,
    "TGL: .tgldat net %s first path component %s not a design top level module - skipped", 
     rtpthnam, chp);
   return(NULL);
  }
 itp = __it_roots[ii];
 gcmp_ndp = gcmp_ndp->ru.x;

 /* this is for getting type, on inst '*' form */ 
 for (;gcmp_ndp != NULL; gcmp_ndp = gcmp_ndp->ru.x)
  {
   mdp = itp->itip->imsym->el.emdp;
   chp = __to_glbcmp_nam(gcmp_ndp);
   /* look up component in module symbol table */
   if ((isyp = __get_sym(chp, mdp->msymtab)) == NULL)
    {
     __pv_fwarn(4342,
      "TGL: .tgldat net %s path component %s not defined in module %s - skipped",
      rtpthnam, chp, mdp->msym->synam);
     return(NULL);
    }
   if (isyp->sytyp == SYM_I) 
    {
     ip = isyp->el.eip; 

     if (ip->i_giap == NULL)
      {
       /* case 1: not array of insts */
       /* must be ID component */
       if (gcmp_ndp->lu.x->optyp != XMRID)
        {
         __pv_fwarn(4342,
          "TGL: .tgldat net select of non-instance array %s - skipped",
          ip->isym->synam);
        return(NULL);
        }
      }
     else
      {
       /* DBG remove -- */
       if (!isyp->sy_giabase) __os_exit_misc_terr(__FILE__, __LINE__);
       /* --- */

       /* must be inst select component */
       if (gcmp_ndp->lu.x->optyp != LSB)
        {
         __pv_fwarn(4342,
          "TGL: .tgldat net %s array %s missing select of instance - skipped",
          rtpthnam, isyp->synam);
         return(NULL);
        }
       __bld_glbcmp_ginam(s1, gcmp_ndp->lu.x);
       if ((arr_isyp = __get_sym(s1, mdp->msymtab)) == NULL)
        {
         __pv_fwarn(4342,
          "TGL: .tgldat net %s path array of instances component %s undefined in module %s - skipped",
          rtpthnam, s1, mdp->msym->synam);
         return(NULL);
        }
       /* both prongs of if set ip */
       ip = arr_isyp->el.eip;
       /* DBG remove -- */
       if (ip->i_giap == NULL) __os_exit_misc_terr(__FILE__, __LINE__);
       /* --- */
      }
     bp1 = (byte *) ip;
     bp2 = (byte *) mdp->minsts;
     ii = (bp1 - bp2)/sizeof(struct inst_t);
     itp = &(itp->in_its[ii]);
     continue;
    }
   if (isyp->sytyp == SYM_N) 
    {
     /* SJM 09-13-13 - also tgl verbose only warn if mod names not match */
     np = isyp->el.enp;    
     if (strcmp(net_modnam, itp->itip->imsym->synam) != 0)
      {  
       if (__tgl_verbose) 
        {
         __pv_fwarn(4351,
          "TGL: .tgldat net %s module %s name does not match design module %s - used",
         rtpthnam,  net_modnam, itp->itip->imsym->synam);
        }
       return(NULL);
      }
     if (!np->n_isavec)
      {
       if (tgl_r1 != -1 || tgl_r2 != -1)  
        {
         /* if range mis match skip but if width same use */
         __pv_fwarn(4342,
          "TGL: net %s in %s is a scalar but .tgldat line range is [%d:%d] - skipped",
          rtpthnam, net_modnam, tgl_r1, tgl_r2); 
         return(NULL);
        }
      }
     else
      {
       __getwir_range(np, &(nr1), &(nr2));
       if (nr1 != tgl_r1 || nr2 != tgl_r2)
        {
         /* if range mis match but width dame still use */
         if (tgl_r1 > tgl_r2) twid = tgl_r1 - tgl_r2 + 1; 
         else twid = tgl_r2 - tgl_r1 + 1;
         if (twid == np->nwid)
          {  
           if (__tgl_verbose) 
            {
             __pv_fwarn(4351,
              "TGL: net %s in %s same width %d but net range [%d:%d] does not match .tgldat line range [%d:%d] - used",
              rtpthnam, net_modnam, np->nwid, nr1, nr2, tgl_r1, tgl_r2); 
            }   
          }
         else
          {
           __pv_fwarn(4342,
            "TGL: net %s in %s width %d but net range [%d:%d] .tgldat line range [%d:%d] and width mismatch - skipped",
           rtpthnam, net_modnam, np->nwid, nr1, nr2, tgl_r1, tgl_r2); 
           return(NULL);
          }
        }
      }
     *ret_itp = itp;
     return(np);
    }
   /* finally illegal sym type */ 
   __pv_fwarn(4342,
    "TGL: .tgldat net %s path end %s in module %s wrong symbol type %s- skipped",
    rtpthnam, isyp->synam, mdp->msym->synam, __to_sytyp(__xs, isyp->sytyp));
   break;
  } 
 return(NULL);
}

/*
 * set per inst per bit seen 01 and seen 10 bits
 *
 * idea is that if a wire is only driven by one constant driver, can
 * never toggle but that should not be in report
 *
 * SJM 10-24-13 - notice that tgl01arr are tabs of tgl state one per bit
 * converted from the internal mask forms - must be ints because -1 is
 * excluded and -2 is driven const for tgldat separate processing
 */
static void set_1net_init_tgl_state(struct net_t *np, struct itree_t *itp,
 int32 *tgl01arr, int32 *tgl10arr)
{
 t_midat *idp;
 struct rt_tgl_t *togp;
 struct mod_t *mdp;
 int32 bi, bval01, bval10;

// SJM 04-25-13 - FIXME? check per inst/net toggle tracking too
 /* SJM 03-12-13 - if this inst, tgl coverage off, there will be no idp */
 /* area so must not try to set tgl bits */
 /* SJM 05-01-13 - regs can have toggle tracking to only need chg store */
 mdp = itp->itip->imsym->el.emdp;
 if (!mdp->m_has_toggle_cover || mdp->m_itps_tgl_cover[itp->itinum] == 0
  ||!np->n_has_toggle) 
  {
   if (__tgl_verbose)
    {
     __pv_fwarn(4352,
      "can't initialize toggle state for net %s in instance %s not included in toggle cover recording - skipped",
      np->nsym->synam, __msg2_blditree(__xs, itp));
    }
   return;    
  }
 /* DBG remove -- */
 if (np->ntgp == NULL) __os_exit_misc_terr(__FILE__, __LINE__);
 /* --- */
 idp = itp->it_idp;

 /* SJM 08-30-13 - check toggle offset bad */ 
 /* DBG remove -- */ 
 if (np->ntgp->toggle_ofs == 0)
  { 
   __dbg_dmp_bad_tgl_ofs(itp->itip->imsym->el.emdp, idp, np, np->ntgp,
    "mark excluded");
  }
 /* --- */

 /* SJM 11-03-13 convention is that low array index corresponds to bit 0 */
 /* of vector - normal h:0 Verilog form, can just access and fill since */
 /* bit index for lhs select is same as array index for tab */
 togp = (struct rt_tgl_t *) idp[np->ntgp->toggle_ofs];
 for (bi = 0; bi < np->nwid; bi++)
   {
    /* can init a net bit many times so also need to set to untgl 0 too */
    bval01 = tgl01arr[bi];

    /* SJM 10-09-13 - LOOKATME - if excluded in file or driven const */
    /* does not effect driven const or excluded masks becaus optconfig */ 
    /* determines inside CVC */
    /* excluded - do not know so do not change */ 
    /* if driven const - do not set any state, cvc option controls */
    if (bval01 == -1 || bval01 == -2) bval01 = 0;
    if (bval01 == 1) __lhsbsel(togp->seen01p, bi, 1);

    bval10 = tgl10arr[bi];
    if (bval10 == -1 || bval10 == -2) bval10 = 0;
    if (bval10 == 1) __lhsbsel(togp->seen10p, bi, bval10);
  }
}

/*
 * ROUTINES TO DUMP DELAY CONTROL EVENTS WHICH DID NOT TRIGGER
 */

/*
 * report all @ events which were never triggered
 */
extern void __write_not_triggered_events(void)
{
 int32 si, number_missed, any_missed;
 struct st_t *stp;
 struct delctrl_t *dctp, *head_dctp;
 struct mod_t *mdp; 
 FILE *fp;


 /* compiling - just return */
 if (__compiled_sim && !__running_cvc_exe) return;

 /* open file to write to */
 if ((fp = __tilde_fopen(__event_coverage_file_name, "w")) == NULL)
  {
   __pv_warn(4337, 
    "cannot open event coverage file %s - skipping toggle coverage report", 
    __toggle_coverage_file_name);
   return;
  }
 /* print header info */
 fprintf(fp, "\n \
                            ************************************************\n \
                            **                                            **\n \
                            **  CVC - Events Not Covered Report           **\n \
                            **                                            **\n \
                            **  Generated :  %s     **\n \
                            ************************************************", 
    __pvdate);

 fprintf(fp, "\n\n\n");
 any_missed = FALSE;
 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   if (!mdp->m_has_event_cover) continue;
   if (mdp->mstnum == 0) continue;

   /* first pass to see if any are missed */
   number_missed = 0;
   for (si = 0; si < mdp->mstnum; si++)
    {
     stp = mdp->mstmts[si];
     stp->dmp_stmt = FALSE;
     if (stp->stmttyp != S_DELCTRL) continue;
     dctp = stp->st.sdc;
     if (dctp->dctyp != DC_EVENT) continue;
     /* could be merged into one block for the compiler */
     if (dctp->head_dctp != NULL) 
      {
       head_dctp = dctp->head_dctp;
      }
     else head_dctp = dctp;

     /* if not covered count it */
     if (!__event_covered[head_dctp->dc_id_ndx]) number_missed++;
    }
   /* if none missed - check next mod */
   if (number_missed == 0) continue;

   fprintf(fp, "=============================================================================================================\n");
   fprintf(fp, "MODULE : %s HAS %d EVENT(S) WHICH DO NOT TRIGGER\n", 
     mdp->msym->synam, number_missed);
   fprintf(fp, "=============================================================================================================\n\n");

   any_missed = TRUE;
   /* second pass does the reporting */
   for (si = 0; si < mdp->mstnum; si++)
    {
     stp = mdp->mstmts[si];
     if (stp->stmttyp != S_DELCTRL) continue;
     dctp = stp->st.sdc;
     if (dctp->dctyp != DC_EVENT) continue;

     if (dctp->head_dctp != NULL) 
      {
       head_dctp = dctp->head_dctp;
      }
     else head_dctp = dctp;
     if (__event_covered[head_dctp->dc_id_ndx]) continue;
     __cur_sofs = 0;
     __write_dctrl(NULL, dctp);
     __exprline[__cur_sofs] = '\0';

     fprintf(fp, "\t%s [ %s : %d ]\n", __exprline,  __in_fils[stp->stfnam_ind], 
       stp->stlin_cnt);
    }
  }
 /* all @ events were triggered */
 if (!any_missed) 
  fprintf(fp, " **** ALL DELAY CONTROL EVENTS TRIGGERED ****\n");

 __my_fclose(fp);
}

/*
 * ROUTINES TO DUMP UNCOVERED STATEMENTS
 */

/*
 * report all statements which were never executed
 */
extern void __write_uncovered_stmts(void)
{
 int32 si, number_missed, any_missed, num_tasks_missed;
 struct task_t *tskp;
 struct st_t *stp;
 struct mod_t *mdp; 
 FILE *fp;


 /* compiling - just return */
 if (__compiled_sim && !__running_cvc_exe) return;

 /* open file to write to */
 if ((fp = __tilde_fopen(__stmt_coverage_file_name, "w")) == NULL)
  {
   __pv_warn(4339, 
    "cannot open statement coverage file %s - skipping toggle coverage report", 
    __stmt_coverage_file_name);
   return;
  }
 /* print header info */
 fprintf(fp, "\n \
                            ************************************************\n \
                            **                                            **\n \
                            **  CVC - Never Executed Statements Report    **\n \
                            **                                            **\n \
                            **  Generated :  %s     **\n \
                            ************************************************", 
    __pvdate);

 fprintf(fp, "\n\n\n");
 any_missed = FALSE;
 /* need to set this global to force dump to this file - no cvc log file */
 __force_dmp_fp = fp;
 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   if (!mdp->m_has_stmt_cover) continue;
   if (mdp->mstnum == 0) continue;
   number_missed = 0;
   /* first pass check for missed stmts */
   for (si = 0; si < mdp->mstnum_no_task; si++)
    {
     stp = mdp->mstmts[si];
     stp->dmp_stmt = FALSE;
     /* delay controls - skip ahead one statement */
     if (skip_ahead_one_stmt(stp)) si++;
     /* some stmts are internal control */
     if (skip_stmt_cover(stp)) continue;
     if (!__stmt_covered[stp->stmt_id_ndx]) number_missed++;
    }

   /* if including tasks stmts */
   num_tasks_missed = 0;
   if (__stmt_coverage_tasks)
    {
     for (; si < mdp->mstnum; si++)
      {
       stp = mdp->mstmts[si];
       stp->dmp_stmt = FALSE;
       if (skip_ahead_one_stmt(stp)) si++;
       if (skip_stmt_cover(stp)) continue;
       if (!__stmt_covered[stp->stmt_id_ndx]) num_tasks_missed++;
      }
    }

   /* no stmts missed in mod or tasks */
   if (number_missed == 0 && num_tasks_missed == 0) continue;

   fprintf(fp, "=============================================================================================================\n");
   fprintf(fp, "MODULE : %s HAS %d STATEMENT(S) NEVER EXECUTED\n", 
     mdp->msym->synam, number_missed);
   fprintf(fp, "=============================================================================================================\n\n");
   any_missed = TRUE;
   /* report the missed statements */
   for (si = 0; si < mdp->mstnum_no_task; si++)
    {
     stp = mdp->mstmts[si];
     if (skip_ahead_one_stmt(stp)) si++;
     if (skip_stmt_cover(stp)) continue;
     if (stp->dmp_stmt) continue; 
     if (__stmt_covered[stp->stmt_id_ndx]) continue;

     __pv_stlevel = 2;
     __outlinpos = 0;
     fprintf(fp, "\nSTATEMENT [ %s : %d ]\n",  __in_fils[stp->stfnam_ind], 
       stp->stlin_cnt);
     __dmp_stmt(fp, stp, FALSE);
     fprintf(fp, "\n");
    }

   /* now do the same thing with tasks/functions */
   if (__stmt_coverage_tasks && num_tasks_missed != 0)
    {
     for (tskp = mdp->mtasks; tskp != NULL; tskp = tskp->tsknxt)
      {
       if (tskp->tsktyp != FUNCTION && tskp->tsktyp != TASK) continue;

       num_tasks_missed = 0;
       for (si = mdp->mstnum_no_task; si < tskp->end_of_stmtndx; si++)
        {
         stp = mdp->mstmts[si];
         if (skip_ahead_one_stmt(stp)) si++;
         if (skip_stmt_cover(stp)) continue;
         if (!__stmt_covered[stp->stmt_id_ndx]) num_tasks_missed++;
        }
       if (num_tasks_missed == 0) continue;

       fprintf(fp, "=============================================================================================================\n");
       if (tskp->tsktyp == TASK)
        {
         fprintf(fp, "TASK : %s HAS %d STATEMENT(S) NEVER EXECUTED\n", 
           tskp->tsksyp->synam, num_tasks_missed);
        }
       else
        {
         fprintf(fp, "FUNCTION : %s HAS %d STATEMENT(S) NEVER EXECUTED\n", 
           tskp->tsksyp->synam, num_tasks_missed);
        }
       fprintf(fp, "=============================================================================================================\n\n");

       for (si = mdp->mstnum_no_task; si < tskp->end_of_stmtndx; si++)
        {
         stp = mdp->mstmts[si];
         if (skip_ahead_one_stmt(stp)) si++;
         if (skip_stmt_cover(stp)) continue;
         if (__stmt_covered[stp->stmt_id_ndx]) continue;
         if (stp->dmp_stmt) continue; 

     
         __pv_stlevel = 2;
         __outlinpos = 0;
         fprintf(fp, "\nSTATEMENT [ %s : %d ]\n",  __in_fils[stp->stfnam_ind], 
           stp->stlin_cnt);
          __dmp_stmt(fp, stp, FALSE);
          fprintf(fp, "\n");
        }
      }
    }
  }

 /* all stmts executed */
 if (!any_missed) fprintf(fp, " **** ALL STATEMENTS EXECUTED ****\n");
 __force_dmp_fp = NULL;
 fprintf(fp, "\n");
 __my_fclose(fp);
}

/*
 * internal statement types to skip reporting
 */
static int32 skip_stmt_cover(struct st_t *stp)
{
         
 switch (stp->stmttyp) {
  case S_NULL: 
  case S_STNONE: 
  case S_GOTO: 
  case S_REPSETUP:
  case S_REPDCSETUP:
  case S_FORASSGN:
  case S_BRKPT:  
   return(TRUE);
 }
 return(FALSE);
}

/*
 * delay controls - skip ahead one statement 
 */
static int32 skip_ahead_one_stmt(struct st_t *stp)
{
 struct delctrl_t *dctp;

 switch (stp->stmttyp) {
  case S_DELCTRL: 
   dctp = stp->st.sdc;
   if (dctp->dctyp == DC_RHSDELAY || dctp->dctyp == DC_RHSEVENT)
    {
     return(TRUE);
    }
   break;
  case S_REPDCSETUP: return(TRUE);
 }
 return(FALSE);
}

/*
 * AFTER TGL SIMULATION ROUTINES TO MARK CONST CANT TOGGLE AS TOGGLED
 */

/*
 * routine to find driven to constant per inst bits and set the toggle
 * per inst per bit seen 01 and seen 10 bits
 *
 * idea is that if a wire is only driven by one constant driver, can
 * never toggle but that should not be in report
 */
static void set_drvn_const_as_if_tgled(void)
{
 int32 ii, ni, bi, bval;
 word32 *wp;
 t_midat *idp;
 struct mod_t *mdp;
 struct net_t *rhs_np;
 struct itree_t *itp;
 struct rt_tgl_t *togp;

 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   /* SJM 04-30-13 - per inst mod has cover tab unused if mod bit off */
   if (!mdp->m_has_toggle_cover) continue;

   for (ii = 0; ii < mdp->flatinum; ii++)
    {
     itp = mdp->moditps[ii];
     idp = itp->it_idp;

     /* SJM 03-12-13 - if this inst, tgl coverage off, there will be no idp */
     /* area so must not try to set tgl bits */
     if (!mdp->m_has_toggle_cover) continue;
     if (mdp->m_itps_tgl_cover[ii] == 0) continue;

     for (ni = 0, rhs_np = &(mdp->mnets[0]); ni < mdp->mnnum; ni++, rhs_np++)
      {
       /* if not toggle or reg, can not be const driven */
       if (!rhs_np->n_has_toggle) continue;
       if (rhs_np->ntyp >= NONWIRE_ST) continue;

       /* DBG remove -- */
       if (rhs_np->ntgp == NULL) __os_exit_misc_terr(__FILE__, __LINE__);
       if (rhs_np->ntgp->peribits_drvn_const == NULL)
        __os_exit_misc_terr(__FILE__, __LINE__);
       /* --- */

       wp = rhs_np->ntgp->peribits_drvn_const[itp->itinum];

       /* SJM 08-30-13 - check toggle offset bad */ 
       /* DBG remove -- */ 
       if (rhs_np->ntgp->toggle_ofs == 0)
        { 
         __dbg_dmp_bad_tgl_ofs(mdp, idp, rhs_np, rhs_np->ntgp,
          "setting drvn const");
        }
       /* --- */
       togp = (struct rt_tgl_t *) idp[rhs_np->ntgp->toggle_ofs];
       for (bi = 0; bi < rhs_np->nwid; bi++)
        {
         bval = rhsbsel_(wp, bi);
         if (bval == 0) continue;
         __lhsbsel(togp->seen01p, bi, 1);
         __lhsbsel(togp->seen10p, bi, 1);
        }
      }
    }
  }
}

/*
 * ROUTINES TO CALCULATE CONST DRIVEN CONST PER BIT PER INST DS AND MARK
 * AS IF TOGGLED 
 */

/*
 * mark all constant per inst per bit wires that can't toggle
 *
 * notice this data structure is purely for output not runtime, does
 * not use idp area for run time storage at all and allocated here
 * and free when run time recorded IDP area bits marked as toggled
 */
static void bld_perib_drvn_const_tab(void)
{
 int32 ii, ni, bi, bval, wid, i1, i2, catrhsi1, catrhsi2;
 int32 some_progress, first_time, num_passes;
 word32 *wp;
 struct mod_t *mdp;
 struct conta_t *cap;
 struct gate_t *gp;
 struct net_t *np, *rhs_np;
 struct expr_t *rhsx;
 struct net_pin_t *npp;
 struct itree_t *itp, *lhs_itp, *rhs_itp;
 struct mod_t *downmdp;
 struct mod_pin_t *mpp;
 struct xstk_t *xsp;

 /* alloc the work per bit/inst const cant toggle work tab */
 alloc_drvn_const_rec();

 /* notice need the const cant toggle tab for every net even if tgl */
 /* reporting/tvcd dumping turned off for net or inst or mod because */ 
 /* still need the propagation of constantness through ports */
 num_passes = 0;
 for (first_time = TRUE;;)
  {
   some_progress = FALSE;
   num_passes++;

   /* DBG remove ---
   if (__verbose)
    {
     __cv_msg("  .. pass %d of building drvn constant table completed.\n",
      num_passes);
    }
   --- */

   /* first set all non per inst const bits cant toggle bits */
   for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
    {
     /* SJM 04-12-13 - if toggle not enabled for this mod, nothing to do */
     /* if any insts enabled will be on - if mod not included in tgl cover, */
     /* will never be any untoggled, still looks across ports for drvn const */
     if (!mdp->m_has_toggle_cover) continue;

     for (ni = 0, np = &(mdp->mnets[0]); ni < mdp->mnnum; ni++, np++)
      {
       /* SJM 04-12-13 - if toggle not enabled for this net, nothing to do */
       /* if can't toggle will not be seen in toggle reports */
       if (!np->n_has_toggle) continue;

       /* if non wire or not exactly one driver - nothing to do */
       if (np->ntyp >= NONWIRE_ST) continue;
       npp = np->ndrvs;
       if (npp == NULL || npp->npnxt != NULL) continue;

       /* XMR drivers can never be constant */ 
       if (npp->npproctyp != NP_PROC_INMOD) continue; 

       /* only conta and port drivers can be non tgl constant */
       /* and 2 terminal gates */
       switch (npp->npntyp) {
        case NP_CONTA:
         break;
        case NP_ICONN: case NP_PB_ICONN:
         break;
        case NP_MDPRT: case NP_PB_MDPRT:
         /* SJM 04-12-13 - if down mod port tgl tracking off, no insts */
         /* can be tied to const - if any insts tgl on, need to check all  */
         downmdp = npp->elnpp.emdp; 
         if (!downmdp->m_has_toggle_cover) continue;
         break;
        case NP_GATE:
         /* only 2 port logic gates can be const driven */
         if (npp->elnpp.egp->gpnum == 2) break;
         continue;
        default: continue;
       }

       /* need to set const cant tgl bits for each inst - even though */
       /* for conta and gates all the same - closure nets maybe not */

       /* some insts may not be selected by toggle config stmt still mark */
       /* reports will omit */
       /* SJM 04-30-13 - notice need all modules here not just */ 
       for (ii = 0; ii < mdp->flatinum; ii++)
        {
         itp = mdp->moditps[ii];

         /* if entire net is already marked, can't toggle, nothting to do */
         if (net_itree_loc_allbits_marked(itp, np))
          {
           /* DBG remove -- */
           if (__debug_flg)
            {
             __dbg_msg("++ wire %s in %s already marked as const driving.\n",
              np->nsym->synam, __msg2_blditree(__xs, itp));
            }
           /* --- */
           continue;
          }

         /* first entire design all non per inst possible const drivers */
         switch (npp->npntyp) {
          case NP_CONTA:
           cap = npp->elnpp.ecap;
           if (cap->ca_pb_sim) cap = &(cap->pbcau.pbcaps[npp->pbi]);
           rhsx = cap->rhsx;
           if (first_time)
            {
             try_set_xpr_cant_be_const(rhsx);
            }
           if (rhsx->tgl_cant_be_const) continue;
           lhs_itp = rhs_itp = itp;
           get_npp_const_id_rng(npp, lhs_itp, &(i1), &(i2), &(catrhsi1),
            &(catrhsi2));
           break;
          case NP_GATE:
           gp = npp->elnpp.egp;
           rhsx = gp->gpins[1];
            if (first_time)
             {
              try_set_xpr_cant_be_const(rhsx);
             }
            if (rhsx->tgl_cant_be_const) continue;

           lhs_itp = rhs_itp = itp;
           get_npp_const_id_rng(npp, lhs_itp, &(i1), &(i2), &(catrhsi1),
            &(catrhsi2));
           break;
          case NP_ICONN: case NP_PB_ICONN:
           /* net is in up mod, driver rhs in down itree mod port */
           lhs_itp = itp;
           rhs_itp = &(lhs_itp->in_its[npp->elnpp.eii]);
           downmdp = rhs_itp->itip->imsym->el.emdp; 
           mpp = &(downmdp->mpins[npp->obnum]);
           if (npp->npntyp == NP_PB_ICONN) mpp = &(mpp->pbmpps[npp->pbi]);
           rhsx = mpp->mpref;
           if (first_time)
            {
             try_set_xpr_cant_be_const(rhsx);
            }
           if (rhsx->tgl_cant_be_const) continue;
           get_npp_const_id_rng(npp, lhs_itp, &(i1), &(i2), &(catrhsi1),
            &(catrhsi2));
           break;
          case NP_MDPRT:
           /* net is in down mod, drvr rhs xp in up mod and itree loc down */
           rhs_itp = itp->up_it;
           lhs_itp = itp;
           if (npp->npntyp == NP_PB_MDPRT)
            {
             rhsx = lhs_itp->itip->pb_ipins_tab[npp->obnum][npp->pbi];
            }
           else rhsx = lhs_itp->itip->ipins[npp->obnum];
           if (first_time)
            {
             try_set_xpr_cant_be_const(rhsx);
            }
           if (rhsx->tgl_cant_be_const) continue;
           get_npp_const_id_rng(npp, lhs_itp, &(i1), &(i2), &(catrhsi1),
            &(catrhsi2));
           break;
          default: continue;
         }
         /* if entire rhs expr is constant - mark and done */
         /* only get here for expr's that can potentially be known const */
         if (tgl_is_const_xpr(rhsx))
          {
           /* returns T if some bits set that were not set */
           if (try_set_1inst_drvn_const_bits(np, lhs_itp, i1, i2))
            {
             some_progress = TRUE;
            }
          }
         else if (rhsx->optyp == ID)
          {
           rhs_np = rhsx->lu.sy->el.enp;
           /* if rhs is reg, then no way to tell if const */
           if (rhs_net_no_perbit_drvn_con(rhs_np, rhsx)) continue;

           /* if rhs xpr net not all bits market as const driven, blocked */
           if (!net_itree_loc_allbits_marked(rhs_itp, rhs_np)) continue;

           /* returns T if some bit newly set */
           if (try_set_1inst_drvn_const_bits(np, lhs_itp, i1, i2))
            {
             some_progress = TRUE;
            }
          }
         else if (rhsx->optyp == LSB && __is_const_expr(rhsx->ru.x)) 
          {
           /* if array will not get here */
           /* this is constant bit select */
           wp = &(__contab[rhsx->ru.x->ru.xvi]);
           bi = wp[0];
           rhs_np = rhsx->lu.sy->el.enp;
           if (rhs_net_no_perbit_drvn_con(rhs_np, rhsx)) continue;
 
           /* check rhs expr bit so see if set */
           wp = rhs_np->ntgp->peribits_drvn_const[rhs_itp->itinum];
           bval = rhsbsel_(wp, bi);
           if (bval == 0) continue;
 
           /* notice bi is rhs index while i1 (same as i2) lhs drvn bit */
           /* returns T if some bit newly set */
           if (try_set_1inst_drvn_const_bits(np, lhs_itp, i1, i2))
            {
             some_progress = TRUE;
            } 
          }
         else if (catrhsi1 != -1)
          {
           /* this is lhs concat so must select matching bits from rhs expr */
           /*  this gets entire rhs driving expr */
           /* if xsp nil, then expr is structurally non const else if bit 1 */
           /* then know that bit const */
           xsp = cnvrt_rhs_xpr_to_con_bit_string(rhs_itp, rhsx);
           if (xsp == NULL) continue;

           /* need to check all bits of drvr matching lhs concat section */
           /* h:l form so check in that order */ 
           for (bi = catrhsi1; bi >= catrhsi2; bi--) 
            {
             bval = rhsbsel_(xsp->ap, bi); 
             /* SJM 02-16-13 - was wrong to pop xstk in loop, need to set */
             /* found one bit that is non constant know expr non const */
             if (bval != 1) goto nxt_inst;
            }
           /* notice lhs being driven can't be concat - will appear as non */
           /* const */
           /* know lhs cat, rhs xstk bits all set, set lhs net bits */
           /* returns T if some bit newly set */
           if (try_set_1inst_drvn_const_bits(np, lhs_itp, i1, i2))
            {
             some_progress = TRUE;
            }
           __pop_xstk();
          }
         else if (rhsx->optyp == LCB)
          {
           /* know lhs not a concat or wil not get here */
           /* eval rhs driving into per bit (1 const) xsp ap val */
           xsp = cnvrt_rhs_xpr_to_con_bit_string(rhs_itp, rhsx);
           /* give up if too complicated a concat or all bits non const */
           if (xsp == NULL) continue;

           /* entire rhs expr evals into xsp ap mask (1 bit is const) */
           /* need to check bit by bit - not actual selecting here */
           /* check concatenated rhs expr starting at 0 since know lhs */
           /* not concatente for width bits */
           if (i1 == -1) wid = np->nwid; else wid = i2 - i1 + 1;
           for (bi = 0; bi < wid; bi++)
            {
             bval = rhsbsel_(xsp->ap, bi);
             /* if any bit in rhs concat range, non const, then drvr non */
             /* const */ 
             if (bval != 1) goto nxt_inst;
            }
           /* know lhs cat, rhs xstk bits all set, set lhs net bits */
           /* returns T if some bit newly set */
           if (try_set_1inst_drvn_const_bits(np, lhs_itp, i1, i2))
            {
             some_progress = TRUE;
            }
           __pop_xstk();
          }
         else
          {
           /* SJM 11-02-12 - LOOKATME - think is everything in expr const */ 
           /* even with complex operators then expr value const */

           /* this is weaker case, not bit by bit for say <lhs cat> */
           /* driven by rhs cat or som expr on rhs driving */ 
           if (tgl_xpr_all_known_const_wires(rhs_itp, rhsx))
            {
             /* returns T if some bit newly set */
             if (try_set_1inst_drvn_const_bits(np, lhs_itp, i1, i2))
              { 
               some_progress = TRUE;
              }
            } 
          }
nxt_inst:;
        }
      }
    }
   if (!some_progress) break;
   first_time = FALSE;
  }
 /* only one pass if nene constant - length will be 0 */
 if (__verbose)
  {
   __cv_msg(
     "  Constant driven wire detection complete - longest constant chain %d.\n",
    num_passes - 1);
  }
}

/*
 * proc to extract range values from a driver net pin record
 *
 * [i2:i1] are lhs sub range for select type npp driver, in case
 * driver is part of lhs concat, [catrhi2:catrhi1] are select of rhs
 * concat that are the driving bits
 */
static void get_npp_const_id_rng(struct net_pin_t *npp,
 struct itree_t *lhs_itp, int32 *i1, int32 *i2, int32 *catrhsi1,
 int32 *catrhsi2)
{
 word32 *wp;
 struct npaux_t *npauxp;

 *i1 = *i2 = -1;
 *catrhsi1 = *catrhsi2 = -1;
 
 if ((npauxp = npp->npaux) == NULL) return; 
 if (npauxp->nbi1 == -2)
  {
   wp = &(__contab[npauxp->nbi2.xvi]);
   wp = &(wp[2*lhs_itp->itinum]);
   *i1 = *i2 = (int32) wp[0];
  }
 else
  {
   *i1 = npauxp->nbi1;
   *i2 = npauxp->nbi2.i;
  }
 *catrhsi1 = npauxp->lcbi1; 
 *catrhsi2 = npauxp->lcbi2; 
}

/*
 * return T and cant possible be const driven top level bit
 */
static int32 rhs_net_no_perbit_drvn_con(struct net_t *rhs_np,
 struct expr_t *rhsx)
{
 /* SJM 04-12-13 - if rhs driving net not cover tgl tracked, no can */
 /* never be driven const */
 if (!rhs_np->n_has_toggle) return(TRUE);

 /* SJM 02-16-13 - no const driven for array (not part of tgl coverage) */
 /* and if reg - can't tell bit by if const driven */
 if (rhs_np->ntyp >= NONWIRE_ST || rhs_np->n_isarr)
  {
   /* if rhs net not a wire, then blocks lhs wire from ever */
   /* being const driven - set expr bit */
   rhsx->tgl_cant_be_const = TRUE;
   return(TRUE);
  }
 return(FALSE);
}

/*
 * convert rhs expr (from cat) to szu xclen is const bit string (word32 chunks)
 * only a part used and if constant rhs set to 1 if non const set to 0
 *
 * sets bit string on interpreter expr stack, return NULL if no const bits
 * not called if concat top expr already marked as no const components
 *
 * will not get here if rhs expr known to structurally not be cant tgl
 */
static struct xstk_t *cnvrt_rhs_xpr_to_con_bit_string(struct itree_t *itp,
 struct expr_t *rhsx)
{
 int32 catxlen, bi, bi1, bofs;
 word32 *wp, *wp2, bval;
 struct expr_t *catrhsx, *catndp;
 struct xstk_t *xsp, *xsp2;
 struct net_t *rhs_np;

 push_xstk_(xsp, rhsx->szu.xclen);
 zero_allbits_(xsp->ap, rhsx->szu.xclen); 
 
 if (rhsx->optyp == ID) 
  { 
   rhs_np = rhsx->lu.sy->el.enp;
   /* if rhs not per bit lhs can't be tied to const */
   if (rhs_net_no_perbit_drvn_con(rhs_np, rhsx)) return(NULL);

   wp = rhs_np->ntgp->peribits_drvn_const[itp->itinum];
   /* here bofs in net and bi in xstk are the same */
   for (bofs = 0; bofs < rhs_np->nwid; bofs++)
    {
     bval = rhsbsel_(wp, bofs);
     __lhsbsel(xsp->ap, bofs, bval);
    }
   return(xsp);
  }
 else if (rhsx->optyp == LSB && tgl_is_const_xpr(rhsx->ru.x))
  {
   rhs_np = rhsx->lu.x->lu.sy->el.enp;

   /* if rhs not per bit lhs can't be tied to const */
   if (rhs_net_no_perbit_drvn_con(rhs_np, rhsx)) return(NULL);

   wp = rhs_np->ntgp->peribits_drvn_const[itp->itinum];
   wp2 = &(__contab[rhsx->ru.x->ru.xvi]);
   bofs = wp2[0];
   bval = rhsbsel_(wp, bofs);
   /* put the one bit in the low position of the xstk */
   __lhsbsel(xsp->ap, 0, bval);
   return(xsp);
  } 
 else if (rhsx->optyp == PARTSEL)
  {
   wp = &(__contab[rhsx->ru.x->ru.x->ru.xvi]);
   /* bi is low bit of concenate in rhs net */
   bofs = (int32) wp[0];
   rhs_np = rhsx->lu.x->lu.sy->el.enp;

   /* if rhs not per bit lhs can't be tied to const */
   if (rhs_net_no_perbit_drvn_con(rhs_np, rhsx)) return(NULL);

   wp = rhs_np->ntgp->peribits_drvn_const[itp->itinum];
   /* here bi is low bit of xstk while bofs is low bit of psel in rhs net */
   for (bi = 0; bi < rhsx->szu.xclen; bi++, bofs++)
    {
     bval = rhsbsel_(wp, bofs);
     __lhsbsel(xsp->ap, bi, bval);
    }
   return(xsp);
  }
 else if (rhsx->optyp != LCB) 
  {
   __pop_xstk();
   return(NULL);
  } 

 /* last case - rhs concat */
 for (catndp = rhsx->ru.x; catndp != NULL; catndp = catndp->ru.x)
  {
   /* catrhsx actual rhs concat component expr. with width catxlen */
   catrhsx = catndp->lu.x;
   catxlen = catrhsx->szu.xclen;
   /* catndp comma node is dist. to low bit, bi1 is low bit of rhs psel */
   bi1 = catndp->szu.xclen - catxlen;
   /* direct const */
   if (tgl_is_const_xpr(catrhsx))
    {
     for (bofs = bi1; bofs < bi1+catxlen; bofs++)
      {
       __lhsbsel(xsp->ap, bofs, 1);
      }
     continue;
    }
   if (catrhsx->optyp == ID)
    {
     /* set the id tgl know const bits in concat tgl const mask */
     rhs_np = catrhsx->lu.sy->el.enp;

     /* if rhs not per bit lhs can't be tied to const */
     if (rhs_net_no_perbit_drvn_con(rhs_np, rhsx)) return(NULL);

     wp = rhs_np->ntgp->peribits_drvn_const[itp->itinum];
     for (bofs = bi1, bi = 0; bofs < bi1+catxlen; bofs++, bi++)
      { 
       bval = rhsbsel_(wp, bi);
       __lhsbsel(xsp->ap, bofs, bval);
      }
     continue;
    }
   if (catrhsx->optyp == LSB)
    { 
     rhs_np = catrhsx->lu.sy->el.enp;

     /* if rhs not per bit lhs can't be tied to const */
     if (rhs_net_no_perbit_drvn_con(rhs_np, rhsx)) return(NULL);

     wp = rhs_np->ntgp->peribits_drvn_const[itp->itinum];

     xsp2 = __eval_xpr(catrhsx->ru.x); 
     /* if constant bit select x/z, then non const - do not know which bit */
     if (!vval_is0_(xsp2->bp, xsp2->xslen)) __lhsbsel(wp, bi1, 0);
     else 
      {
       bval = rhsbsel_(wp, xsp2->ap[0]);
       __lhsbsel(xsp->ap, bi1, bval);
      }
     __pop_xstk();
     continue;
    }
   if (catrhsx->optyp == PARTSEL)
    {
     rhs_np = catrhsx->lu.sy->el.enp;

     /* if rhs not per bit lhs can't be tied to const */
     if (rhs_net_no_perbit_drvn_con(rhs_np, rhsx)) return(NULL);

     wp = rhs_np->ntgp->peribits_drvn_const[itp->itinum];
     /* know psel non x/z by here or will be x expr */
     wp2 = &(__contab[catrhsx->ru.x->ru.x->ru.xvi]); 
     /* bi is low bit of rhs psel net index */
     bi = wp2[0];
     for (bofs = bi1; bofs < bi1+catxlen; bofs++, bi++)
      { 
       bval = rhsbsel_(wp, bi);
       __lhsbsel(xsp->ap, bofs, bval);
      }
     continue;
    }
   /* anything else such as expr or XMRs go here - cant be const */
   __pop_xstk();
   return(NULL);
  } 
 return(xsp);
}

/*
 * mark expression that can't possibility be const even if the
 * variable on rhs driving expression is known to only be const 
 *
 * once cant be seen, stop further descent trying to propagate constantness
 *
 * this is general expr structural property that does not depend on itree loc
 *
 * SJM 02-17-13 - LOOKATME? - non constant bit and ndx psel's could
 * conceivably be constant if variable select from entire wire but not
 * considering here 
 */
static int32 try_set_xpr_cant_be_const(struct expr_t *rhsx)
{
 struct net_t *np;
 struct expr_t *fax;

 /* assume can be const expr */
 rhsx->tgl_cant_be_const = FALSE;
 switch (rhsx->optyp) {
  /* ident can be const */
  case ID:
   np = rhsx->lu.sy->el.enp;
   if (np->ntyp == N_REAL || np->n_isarr)
    {
     rhsx->tgl_cant_be_const = TRUE;
     return(TRUE);
    }
   return(FALSE);
  case GLBREF: rhsx->tgl_cant_be_const = TRUE; return(TRUE);
  case NUMBER: return(FALSE);
  case LSB:
   /* SJM 02-17-13 - if select non const from known const wire still const */
   np = rhsx->lu.x->lu.sy->el.enp;
   if (np->ntyp == N_REAL || np->n_isarr || rhsx->lu.x->optyp == GLBREF)
    {
     rhsx->tgl_cant_be_const = TRUE;
     return(TRUE);
    }
/* SJM 02-17-13 - maybe PUTMEBACK
// variable bit select from constant wire still can't toggle
   if (!__is_const_expr(rhsx->ru.x)) 
    { 
     rhsx->tgl_cant_be_const = TRUE;
     return(TRUE);
    }
==== */
   return(FALSE);
  case PARTSEL_NDX_PLUS: case PARTSEL_NDX_MINUS: 
   np = rhsx->lu.x->lu.sy->el.enp;
   if (np->ntyp == N_REAL || np->n_isarr || rhsx->lu.x->optyp == GLBREF)
    {
     rhsx->tgl_cant_be_const = TRUE;
     return(TRUE);
    }
   return(FALSE);

   /* these are always assumed to not be const - wrong if entire wire const */
/* SJM 02-17-13 - maybe PUTMEBACK
   rhsx->tgl_cant_be_const = TRUE;
   return(TRUE);
==== */
  case PARTSEL:
   np = rhsx->lu.x->lu.sy->el.enp;
   if (np->ntyp == N_REAL || np->n_isarr || rhsx->lu.x->optyp == GLBREF)
    {
     rhsx->tgl_cant_be_const = TRUE;
     return(TRUE);
    }
   return(FALSE);
  case FCALL:
   rhsx->tgl_cant_be_const = TRUE;
   return(TRUE);
  case LCB:
   /* if any components of concat can't be const, then expr can't */
   for (fax = rhsx->ru.x; fax != NULL; fax = fax->ru.x)
    {
     if (!try_set_xpr_cant_be_const(fax->lu.x)) return(FALSE);
    }
   rhsx->tgl_cant_be_const = TRUE;
   return(TRUE);
  default:
   /* SJM 02-17-13 - logic was wrong - only can't be const if both */
   if (rhsx->lu.x != NULL)
    {
     if (!try_set_xpr_cant_be_const(rhsx->lu.x)) return(FALSE);
    }
   if (rhsx->ru.x != NULL)
    {
     if (!try_set_xpr_cant_be_const(rhsx->ru.x)) return(FALSE);
    }
   rhsx->tgl_cant_be_const = TRUE;
   return(TRUE);
  }
}

/*
 * return T if every net in expr is a non is constant
 */
static int32 tgl_xpr_all_known_const_wires(struct itree_t *itp,
 struct expr_t *rhsx)
{
 int32 ndx1, ndx2;
 word32 *wp;
 struct net_t *np;

 switch (rhsx->optyp) { 
  case ID:
   /* check entire per inst net */
   np = rhsx->lu.sy->el.enp;
chk_entire_wire:
   /* if rhs is reg, then no way to tell if const */
   if (rhs_net_no_perbit_drvn_con(np, rhsx)) return(FALSE);

   if (net_itree_loc_allbits_marked(itp, np)) return(TRUE);
   return(FALSE); 
  case GLBREF:
   /* SJM 02-17-13 - XMR - in expr must be F */
   return(FALSE);
  case OPEMPTY: case NUMBER: case ISNUMBER: return(TRUE);
 case REALNUM: case ISREALNUM: return(FALSE);
  case LSB:
   np = rhsx->lu.x->lu.sy->el.enp;
   if (np->n_isarr || rhsx->lu.x->optyp == GLBREF) return(FALSE);

   /* SJM 02-17-13 - if index is known const, still need to check */
   /* entire wire because do not know value here */
   if (!__is_const_expr(rhsx->ru.x)) goto chk_entire_wire;

   /* DBG remove -- */
   if (rhsx->ru.x->optyp != NUMBER) __os_exit_misc_terr(__FILE__, __LINE__);
   /* ---*/
   wp = &(__contab[rhsx->ru.x->ru.xvi]);
   ndx1 = wp[0];
   /* if rhs is reg, then no way to tell if const */
   if (rhs_net_no_perbit_drvn_con(np, rhsx)) return(FALSE);
   if (net_itree_loc_rngbits_marked(itp, np, ndx1, ndx1)) return(TRUE);
   return(FALSE);
  case PARTSEL_NDX_PLUS: case PARTSEL_NDX_MINUS: 

   /* for variable first index part select and variable index bit select */
   /* if entire wire is const cant toggle, then expr cant toggle too */ 
   np = rhsx->lu.x->lu.sy->el.enp;
   if (np->n_isarr || rhsx->lu.x->optyp == GLBREF) return(FALSE);
   /* SJM 02-17-13 - FIXME? - for now assuming even if 1st base xpr const */
   /* entire wire needs to be drvn const */
   goto chk_entire_wire;
  case PARTSEL:
   np = rhsx->lu.x->lu.sy->el.enp;
   if (np->n_isarr || rhsx->lu.x->optyp == GLBREF) return(FALSE);

   wp = &(__contab[rhsx->ru.x->lu.x->ru.xvi]);
   ndx1 = (int32) wp[0];
   wp = &(__contab[rhsx->ru.x->ru.x->ru.xvi]);
   ndx2 = (int32) wp[0];

   /* if rhs is reg, then no way to tell if const */
   if (rhs_net_no_perbit_drvn_con(np, rhsx)) return(FALSE);

   if (net_itree_loc_rngbits_marked(itp, np, ndx1, ndx2)) return(TRUE);
   return(FALSE);
  }
 if (rhsx->lu.x != NULL)
  { if (!tgl_xpr_all_known_const_wires(itp, rhsx->lu.x)) return(FALSE); }
 if (rhsx->ru.x != NULL)
  { if (!tgl_xpr_all_known_const_wires(itp, rhsx->ru.x)) return(FALSE); }
 return(TRUE);
}

/*
 * tgl is const
 *
 * SJM 11-01-12- SJM LOOKATME - maybe should handle real toggles too
 */
static int32 tgl_is_const_xpr(struct expr_t *rhsx)
{
 struct net_t *rhs_np;

 if (rhsx->optyp == NUMBER) return(TRUE);
 if (rhsx->optyp == ID)
  {
   rhs_np = rhsx->lu.sy->el.enp;
   /* SJM 11-03-12 - LOOKATME? - rtrans can reduce supply 0 stren */
   /* but still think constant */
   if (rhs_np->ntyp == N_SUPPLY0 || rhs_np->ntyp == N_SUPPLY1) return(TRUE);
   if (rhs_np->n_isaparam) return(TRUE);
  }
 /* any other leaf is not a non is tgl const */
 if (__isleaf(rhsx)) return(FALSE);

 if (rhsx->lu.x != NULL)
  { if (!tgl_is_const_xpr(rhsx->lu.x)) return(FALSE); }
 if (rhsx->ru.x != NULL)
  { if (!tgl_is_const_xpr(rhsx->ru.x)) return(FALSE); }
 return(TRUE);
}

/*
 * mark a net section (or entire) for one itree loc
 * return F if no change else T
 */
static int32 try_set_1inst_drvn_const_bits(struct net_t *np,
 struct itree_t *itp, int32 h, int32 l)
{
 int32 bi, bval, none_set;
 word32 *wp;

 /* SJM 04-12-13 - it is possible for this net to be not monitored for */
 /* tgl coverage but other nets in mod to be */
 if (!np->n_has_toggle) return(FALSE);

 /* DBG remove -- */
 if (np->ntgp == NULL || np->ntgp->peribits_drvn_const == NULL)
  { 
   __os_exit_misc_terr(__FILE__, __LINE__);
  }
 /* --- */

 wp = np->ntgp->peribits_drvn_const[itp->itinum];
 if (h == -1 || (l == 0 && np->nwid - 1 == h))
  {
   /* all set as const, nothing to do return F */
   if (__vval_is1(wp, np->nwid)) return(FALSE);
   one_allbits_(wp, np->nwid);
  }
 else
  {
   for (none_set = TRUE, bi = l; bi < h; bi++)
    {
     bval = rhsbsel_(wp, bi);
     if (bval == 0) none_set = FALSE;
     __lhsbsel(wp, bi, 1);
    }
   if (none_set) return(FALSE);
  }

/* DBG remove === maybe add back as dbg flg output?
 if (__verbose && itp->itinum == 0)
  {
   char s1[RECLEN];

   if (h == -1) strcpy(s1, ""); else sprintf(s1, " [%d:%d]", h, l); 
   __cv_msg("==> setting net %s%s in %s\n", np->nsym->synam, s1,
    __msg2_blditree(__xs, itp));
  }
==== */
 return(TRUE);
}

/*
 * return T if all bits of this net/itree loc are set as driven const 
 */
static int32 net_itree_loc_allbits_marked(struct itree_t *itp,
 struct net_t *np) 
{
 word32 *wp;

 /* SJM 05-05-13 - it is possible for this net to be not monitored for */
 /* tgl coverage but other nets in mod to be */
 if (!np->n_has_toggle) return(FALSE);
 
 wp = np->ntgp->peribits_drvn_const[itp->itinum];
 if (__vval_is1(wp, np->nwid)) return(TRUE);
 return(FALSE);
}

/*
 * all bit of net range marked
 */
static int32 net_itree_loc_rngbits_marked(struct itree_t *itp,
 struct net_t *np, int32 h, int32 l)
{
 int32 bi, bval;
 word32 *wp;

 /* DBG remove -- */
 if (np->ntgp == NULL || np->ntgp->peribits_drvn_const == NULL)
  __os_exit_misc_terr(__FILE__, __LINE__);
 /* --- */ 

 wp = np->ntgp->peribits_drvn_const[itp->itinum];
 for (bi = l; bi < h; bi++) 
  {
   bval = rhsbsel_(wp, bi);
   if (bval == 0) return(FALSE); 
  }
 return(TRUE);
}

/*
 * allocate the per inst/bit const cant toggle table for 1 net
 *
 * this goes in the net's compile time (not in idp area) toggle info
 * record only allocated if toggle coverage on
 */
static void alloc_drvn_const_rec(void)
{
 int32 ni, ii, wlen;
 struct mod_t *mdp;
 struct net_t *np;
 struct net_toggle_t *togp;
 
 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   /* SJM 02-15-13 - task/func vars are always excluded from tgl coverage */
   for (ni = 0, np = &(mdp->mnets[0]); ni < mdp->mnnum; ni++, np++)
    {
     /* SJM 02-15-13 - can only exclude wires because tracing procedural */
     /* regs means full conditional expansion that is impossible */
     /* this is case where may have toggle coverage on but know never const */
     if (np->ntyp >= NONWIRE_ST) continue;

     /* SJM 02-15-13 - if excluded from toggle coverage not used but */
     /* this means there can be a chain of driven const that is broken */
//SJM 02-15-13 - DOCUMENT ME?
     /* config file can turn off toggling in arbitrary ways - no pattern */ 
     /* here to check */
     if (!np->n_has_toggle)
      {
       /* DBG remove -- */ 
       if (np->ntgp != NULL) __os_exit_misc_terr(__FILE__, __LINE__);
       /* --- */
       continue;
      }

     /* DBG remove -- */ 
     if (np->ntgp == NULL) __os_exit_misc_terr(__FILE__, __LINE__);
     /* --- */

     wlen = wlen_(np->nwid);
     togp = np->ntgp;
     /* know only driven const records only called once if needed */
     /* DBG remove -- */
     if (togp->peribits_drvn_const != NULL)
      {
       __os_exit_misc_terr(__FILE__, __LINE__);
      }
     /* --- */
     /* SJM 04-12-13 - drvn const (tied to) alloc for every inst even if */
     /* inst tgl coverage off */
     togp->peribits_drvn_const = (word32 **)
      __my_malloc(mdp->flatinum*sizeof(word32 *));
     for (ii = 0; ii < mdp->flatinum; ii++)
      {
       togp->peribits_drvn_const[ii] = (word32 *) __my_malloc(wlen*WRDBYTES);
       memset(togp->peribits_drvn_const[ii], 0, WRDBYTES*wlen);
      }
    }
  }
}

/*
 * freee the per inst/bit const cant toggle table
 */
static void free_drvn_const_tgl_ds(void)
{
 int32 ni, ii, wlen;
 struct mod_t *mdp;
 struct net_t *np;
 struct net_toggle_t *togp;

 for (mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   for (ni = 0, np = &(mdp->mnets[0]); ni < mdp->mnnum; ni++, np++)
    {
     /* if net not toggled nothing to do */
     if (np->ntgp == NULL)
      {
       if (np->n_has_toggle) __os_exit_misc_terr(__FILE__, __LINE__);
       continue;
      } 
     togp = np->ntgp;
     /* SJM 02-17-13 - regs will not have peribits tgl (other?) */
     if (togp->peribits_drvn_const == NULL) continue;

     wlen = wlen_(np->nwid);
     for (ii = 0; ii < mdp->flatinum; ii++)
      { 
       __my_free(togp->peribits_drvn_const[ii], WRDBYTES*wlen);
       togp->peribits_drvn_const[ii] = NULL;
      }
     __my_free(togp->peribits_drvn_const, mdp->flatinum*sizeof(word32 *));
     togp->peribits_drvn_const = NULL;
    }
  }
}

// #####################################################

/*
 * print to fp the cant change constant wire bit report
 *
 * never called unless design has at least one net
 *
 * BEWARE - SJM 04-26-13 - excluded bits are not used in driven const
 * calculation or report
 */
static void concise_drvn_const_report(FILE *fp)
{
 int32 mi, ii, ni, bi, nwires, bval;
 int32 mod_has_drvn_const, inst_has_drvn_const, dsgn_has_drvn_const;
 int32 tot_insts, tot_wires, tot_bits, tot_drvn_const;
 word32 *wp;
 double d1, d2;
 struct itree_t *itp;
 struct mod_t *mdp;
 struct net_t *np;

 fprintf(fp, "** CVC driven to never toggles constant bit report.\n");
 fprintf(fp, "** Written : %s\n", __pv_timestamp);
 fprintf(fp, "** By Version : %s%s of %s\n", __vers, __vers2, __ofdt);

 dsgn_has_drvn_const = FALSE;
 for (mi = 0; mi < __tgl_num_mods; mi++)
  {
   mdp = __tgl_mods_ndx[mi];

   /* SJM 04-30-13 - per inst mod has cover tab unused if mod bit off */
   if (!mdp->m_has_toggle_cover) continue;

   mod_has_drvn_const = FALSE;
   for (ii = 0; ii < mdp->flatinum; ii++)
    {
     itp = mdp->moditps[ii];
     if (mdp->m_itps_tgl_cover[ii] == 0) continue;

     inst_has_drvn_const = FALSE;  
     nwires = 0; 
     for (ni = 0, np = &(mdp->mnets[0]); ni < mdp->mnnum; ni++, np++) 
      {
       if (np->ntyp >= NONWIRE_ST) continue; 
       if (!np->n_has_toggle) continue;
      
       nwires++;
       wp = np->ntgp->peribits_drvn_const[itp->itinum];
       for (bi = 0; bi < np->nwid; bi++) 
        { 
         bval = rhsbsel_(wp, bi);
         if (bval == 1) goto some_can_toggle;
        }
       /* no bits for this net in given itree location are driven by a */
       /* constant so nothing to print */
       continue;

some_can_toggle:
       /* has a signal with some bits driven to constant by exactly 1 drvr */
       if (!mod_has_drvn_const)
        {
         mod_has_drvn_const = TRUE;
         fprintf(fp, "MODULE: %s (%d instances) [%s : %d]:\n",
          mdp->msym->synam, mdp->flatinum, __in_fils[mdp->msym->syfnam_ind],
          mdp->msym->sylin_cnt);
        }

       if (!inst_has_drvn_const)
        {
         inst_has_drvn_const = TRUE;
         dsgn_has_drvn_const = TRUE;

         fprintf(fp, "  INSTANCE %s (%d wires) [%s : %d]:\n",
          __msg2_blditree(__xs, itp), nwires,
          __in_fils[itp->itip->isym->syfnam_ind], itp->itip->isym->sylin_cnt);
        }
       print_1sig_drvn_const(fp, np, itp);
      }
     if (inst_has_drvn_const)
      {
       tot_wires = 0;
       tot_bits = 0;
       tot_drvn_const = 0;
       /* for driven const data struct only 2 state (drvn const and not) */
       add_tot_1inst_drvn_const_bits(itp, &(tot_wires), &(tot_bits),
         &(tot_drvn_const));
       if (tot_bits > 0)
        {
         d1 = 100.0*((double) tot_drvn_const)/((double) tot_bits);
         fprintf(fp,
           "  CONST DRIVEN [of %d nets %d bits] %d bits (%.2f%%)\n",
          tot_wires, tot_bits, tot_drvn_const, d1);
        }
      }
    } 
   /* know will not get here unless toggle coverage on for this mod */ 
   if (mod_has_drvn_const && mdp->flatinum > 1)
    {
     mod_tot_drvn_const_bits(mdp, &(tot_insts), &(tot_wires), &(tot_bits),
      &(tot_drvn_const));
     if (tot_bits > 0)
      {
       d1 = 100.0*((double) tot_drvn_const)/((double) tot_bits);
       fprintf(fp,
         "TOTAL MOD %s [%d wires %d bits] const driven bits %d (%.2f%%)\n",
        mdp->msym->synam, tot_wires, tot_bits, tot_drvn_const, d1);
      }
    }
  }
 if (dsgn_has_drvn_const)
  { 
   if (__has_tgl_optcfg_stmt)
    {
      fprintf(fp,
       "   [TOTALS NOT FOR ENTIRE DESIGN: -toggle or -optconfigfile cover_toggle used]\n");
    } 

   dsgn_tot_insts_drvn_const_bits(&(tot_insts), &(tot_wires), &(tot_bits),
    &(tot_drvn_const));
   d1 = 100.0*((double) tot_drvn_const)/((double) tot_bits);
   d2 = 100.0*((double) (tot_bits - tot_drvn_const))/((double) tot_bits);
   fprintf(fp,
     "** DESIGN [%d wires %d bits] const driven %d (%.2f%%) normal driven %d (%.2f%%)\n",
    tot_wires, tot_bits, tot_drvn_const, d1, tot_bits - tot_drvn_const, d2);
  }
 else
  {
   fprintf(fp,
    "** NOTE! NO WIRES IN DESIGN ARE DRIVEN BY CONSTANTS\n");
  }
 fprintf(fp, "\n\n");
}

/*
 * routine to print per bit can't toggle lines for one signal
 */
static void print_1sig_drvn_const(FILE *fp, struct net_t *np,
 struct itree_t *itp)
{
 int32 bval, drvn_const_state, bi, nxt_down_bi, r1, r2;
 word32 *wp;
 char s1[RECLEN], s2[RECLEN];

 /* SJM 01-22-13 - n isarr vector for wires go here - the individual bits */
 /* are normal wires (fixed name) with normal chg events so can print */
 /* DBG remove -- */
 if (np->n_isarr) __os_exit_misc_terr(__FILE__, __LINE__);
 /* --- */
 /* case 1: scalar */
 if (!np->n_isavec)
  {
   wp = np->ntgp->peribits_drvn_const[itp->itinum];
   bval = rhsbsel_(wp, 0); 
   
   if (bval == 0) return;
   fprintf(fp, "    %s: scalar driven by constant\n", np->nsym->synam); 
   return;
  }

 /* case 2: a vector */
 /* internal storage always h:0 even if l:h form */
 for (bi = np->nwid - 1; bi >= 0; bi--)
  {
   drvn_const_state = fnd_same_drvn_const_select(np, bi, &(nxt_down_bi), itp);
   /* if both toggle, no msg only untoggled interesting */

   /* if both toggle, no msg only untoggled interesting */
   /* SJM 05-05-13 - fixed bug can't move down here and have for loop move */
   /* down - say nxt_down_bi is 2 (2 low bits 1 and 0 untgl) then */
   /* this moves to 1 and for moves to 0 - continue caused the dec */
   if (drvn_const_state == 0) { bi = nxt_down_bi; continue; }

   /* SJM 10-31-12 - all of net means both high same as size-1 and low 0 */ 
   if (np->nwid - 1 == bi && nxt_down_bi == 0)
    {
     sprintf(s2, "<all of net> ");
    }
   else if (bi - nxt_down_bi > 1) sprintf(s2, "<of %d> ", np->nwid);
   else strcpy(s2, "");

   __getwir_range(np, &(r1), &(r2));
   bld_unnormalized_rng_str(s1, bi, nxt_down_bi, r1, r2);
   if (drvn_const_state == 1)
    {
     fprintf(fp, "    %s%s%s: driven by constant\n", np->nsym->synam, s1, s2); 
    }
   /* can't dec here because for loop decs */
   bi = nxt_down_bi;
  }
}


/*
 * in h:0 world, find range of can't toggle bit
 * return -1 for no cant toggle constants (recursively calculated)
 */
static int32 fnd_same_drvn_const_select(struct net_t *np, int32 selbi,
 int32 *last_same_down_bi, struct itree_t *itp)
{
 int32 bi, bval, last_drvn_const_state, nxt_drvn_const_state;
 word32 *wp;

 wp = np->ntgp->peribits_drvn_const[itp->itinum];
 last_drvn_const_state = -2;
 for (bi = selbi; bi >= 0; bi--)
  {
   bval = rhsbsel_(wp, bi);
   if (bval == 1) nxt_drvn_const_state = 1; else nxt_drvn_const_state = 0; 

   if (last_drvn_const_state == -2)
    {
     last_drvn_const_state = nxt_drvn_const_state;
    }
   else if (last_drvn_const_state != nxt_drvn_const_state) break;
  }
 if (bi < 0) *last_same_down_bi = 0; else *last_same_down_bi = bi + 1;
 return(last_drvn_const_state);
}

/*
 * count total number of nets and bits for one inst of one mod 
 * that are driven by consts either directly or driven by net that
 * is driven with on drivers by consts through chain
 */
static void add_tot_1inst_drvn_const_bits(struct itree_t *itp,
 int32 *tot_wires, int32 *tot_bits, int32 *tot_drvn_const)
{
 int32 ni, bi, bval;
 word32 *wp;
 struct mod_t *mdp;
 struct net_t *np;

 mdp = itp->itip->imsym->el.emdp;
 for (ni = 0, np = &(mdp->mnets[0]); ni < mdp->mnnum; ni++, np++) 
  {
   if (!np->n_has_toggle) continue;

   /* DBG remove -- */
   if (np->ntgp == NULL) __os_exit_misc_terr(__FILE__, __LINE__);
   /* --- */

   (*tot_wires)++;
   *tot_bits = *tot_bits + np->nwid;

   /* SJM 11-18-13 - tgl recorded nets may not have any driven const info */
   if (np->ntgp->peribits_drvn_const == NULL) continue;

   wp = np->ntgp->peribits_drvn_const[itp->itinum];
   for (bi = np->nwid - 1; bi >= 0; bi--)
    {
     bval = rhsbsel_(wp, bi);
     if (bval == 1) (*tot_drvn_const)++;
    }
  }
}

/*
 * count total number of insts, signals and bits in entire design
 * also count per bit toggles (both, 0->1 and 1-0)
 */
static void dsgn_tot_insts_drvn_const_bits(int *tot_insts, int32 *tot_wires,
 int32 *tot_bits, int32 *tot_drvn_const)
{
 int32 mi, ii;
 struct mod_t *mdp;
 struct itree_t *itp;

 *tot_insts = 0;
 *tot_wires = 0;
 *tot_bits = 0;
 *tot_drvn_const = 0;
 for (mi = 0; mi < __tgl_num_mods; mi++)
  {
   mdp = __tgl_mods_ndx[mi];

   /* SJM 04-30-13 - per inst mod has cover tab unused if mod bit off */
   /* mod's not included in toggle cover not counted */
   if (!mdp->m_has_toggle_cover) continue;

   for (ii = 0; ii < mdp->flatinum; ii++)
    {
     itp = mdp->moditps[ii];
     if (mdp->m_itps_tgl_cover[ii] == 0) continue;
     (*tot_insts)++;

     add_tot_1inst_drvn_const_bits(itp, tot_wires, tot_bits, tot_drvn_const);
    }
  }
}

/*
 * count total inst, signals and bits of one module
 * also count per bit const driven wires for the  
 *
 * know will not be called unless toggle coverage on for this mod
 */
static void mod_tot_drvn_const_bits(struct mod_t *mdp, int32 *tot_insts,
 int32 *tot_wires, int32 *tot_bits, int32 *tot_drvn_const)
{
 int32 ii;
 struct itree_t *itp;

 *tot_wires = 0;
 *tot_bits = 0;
 *tot_drvn_const = 0;
 /* for every inst of mod type */
 for (ii = 0; ii < mdp->flatinum; ii++)
  {
   itp = mdp->moditps[ii];
   /* it is possible for some instance to have toggle cover off */
   if (mdp->m_itps_tgl_cover[ii] == 0) continue;

   (*tot_insts)++;
   add_tot_1inst_drvn_const_bits(itp, tot_wires, tot_bits, tot_drvn_const);
  }
}
