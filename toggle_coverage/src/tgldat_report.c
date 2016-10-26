/* This is free and unencumbered software released into the public domain. */

/*
 * Program to report toggle information from a '.tgldat' file. 
 *
 * See the README.coverage-helper-programs document for explanation of  
 * .tgldat file format.
 *
 *  The following options are used for new style coverage report:
 *
 *   -untoggled_report_concise - new separate display untoggled in concise form
 *   -h       Dislplay help message.
 *
 *  The following options are used for old style coverage report:
 * 
 *   -ti      Display toggle coverage information per instance.
 *   -tu      Display uncovered nets - those without 100%% coverage.
 *   -tc      Display covered nets - those getting 100%% coverage.
 *   -tb      Display toggle coverage vectors per bit.
 *
 *  Notice argument order is slightly non linux style because the .tgldat file
 *  appears before the options
 *
 * This is intended to be template code with pattern and output service
 * procedures so users can change to other report formats if desired
 */

#define VERS "3.10"
#define OFDT "11/08/2013"

#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include <stdarg.h>

#include "tgldat.h"

/* externs vars usable in any file */

/* variables defined in this file for use here */
/* new style report vars */
int32 untgl_rpt_concise;
int32 **__net_count01;
int32 **__net_count10;

/* old style report vars */
int32 tgl_report_instance;/* report toggles for insts (default mods) */ 
int32 tgl_report_bits; /* report individual bits per line */    
int32 tgl_report_uncovered;/* report uncovered */      
int32 tgl_report_covered;/* inversre - report only covered */      

/* globals used by tgldat ms library - must be defined in every program */
char __token[RECLEN]; 
struct tgl_vardef_t **__tglvardefs;
int32 __last_tglvardef;/* last ndx of tgl var defs - num + 1 */
int32 __alloc_siz_tglvardefs;
char *__tglbits01;     /* for init from .tgldat file 01 list */
char *__tglbits10;     /* 10 list */
int32 __siz_tgl_lst;   /* current alloc size of list */
char *__tgl_modnam;    /* name of module for tgl net line */
char *__tgl_rtpthnam;  /* for init from .tgldat line rooted path */ 
int32 __siz_tgl_rtpthnam;/* and alloc size */
int32 *__tgl01tab;     /* tgl net's per bit toggle count tabs */ 
int32 *__tgl10tab;
int32 __tgl_r1;        /* first tgldat line range */
int32 __tgl_r2;        /* 2nd tgldat line range */
char **__scopnam_stk; 
char **__scopmdnam_stk; 
int32 __top_scopei;
int32 __siz_scope_stk;
char *__tgldat_pthcmps[MAXSCOPES];  /* tab of malloc pth comp strings */
int32 __last_tdpthi;   /* last used for current tgldat net line */ 
int32 __ix_insert;     /* for binary srch procs, place to insert */
struct td_netlist_t *__file_netlist; /* hdr of .tgldat vardefs d.s. */
int32 __emit_dup_rtpth_warn;/* flag on to emit td dup tgl line warns */

char __in_tvcd_fnam[RECLEN];
char __out_tgldat_fnam[RECLEN];
char __in_tgldat_fnam[RECLEN];
char __tvcd_date[RECLEN];
char __tvcd_version[RECLEN];
char __tgldat_writer_date[RECLEN];/* possible date string from .tgldat */
char __tgldat_writer_vers[RECLEN];/* possible writer info */
int32 __verbose;       /* T => print verbose messages */
int32 __lin_cnt;       /* current line number reading */
char __cur_fnam[RECLEN];
char __log_fnam[RECLEN];
FILE *__log_s;

/* protos for this file */
static void display_help_message(void);
static void prep_and_print_report(char *, char *);
static void print_old_style_tgl_rpt(FILE *, char *);
static void calc_one_mod_instnet_combined_tgls(struct td_mod_t *, int32,
 int32, int32);
static void fnd_netlist_maxes(struct td_netlist_t *, int32 *, int32 *, int32 *);
static void alloc_init_net_counts(int32, int32);
static void re_init_net_counts(int32, int32);
static void print_hits_misses(FILE *, char *, int32, int32, int32);
static int32 get_toggle_count(struct tgl_vardef_t *, int32 *, int32 *);
static int32 get_net_toggle_blen(struct tgl_vardef_t *);
static int32 print_toggle_net_coverage(FILE *, struct tgl_vardef_t *, char *,
 int32, int32 *, int32 *);
static void get_hexstr(char *, int32 *, int32);
static int32 unnormalize_ndx(struct tgl_vardef_t *, int32);
static void print_untoggled_concise_report(FILE *);
static void print_1sig_untgl(FILE *, struct tgl_vardef_t *);
static char *bld_unnormalized_rng_str(char *, int32, int32, int32, int32);
static int32 unnormalize2_ndx(int32, int32, int32);
static int32 fnd_same_tgl_select(struct tgl_vardef_t *, int32, int32 *);
static int32 all_sig_bits_tgl(struct tgl_vardef_t *, int32);
static int32 all_sig_bits_included(struct tgl_vardef_t *);
static int32 no_sig_bits_drvn_const(struct tgl_vardef_t *);
static void dsgn_tot_insts_sigs_bits(int32 *, int32 *, int32 *, int32 *,
 int32 *, int32 *, int32 *, int32 *, int32 *);
static void mod_tot_sigs_bits(struct td_mod_t *, int32 *, int32 *, int32 *,
 int32 *, int32 *, int32 *, int32 *, int32 *, int32 *);
static void add_tot_1inst_sigs_bits(struct td_inst_t *, int32 *,
 int32 *, int32 *, int32 *, int32 *, int32 *, int32 *, int32 *);

/* externs callable here define in tgldat ms file */
extern void __init_tgldat_api_glbs(void);
extern struct tgl_vardef_t *__rd_tgldat_to_vardefs(FILE *, char *);
extern void __bld_vardef_netlist(struct td_netlist_t *, struct tgl_vardef_t *,
 char *);
extern void __wr1_tgldat_line_from_tglvardef(FILE *, struct tgl_vardef_t *);
extern int32 __fnd_td_inst_vardefs(struct td_inst_t *, char *);

extern char *__my_stralloc(char *);
extern char *__my_malloc(size_t);
extern char *__my_realloc(void *, size_t, size_t);
extern void __my_free(void *, size_t);
extern ssize_t __my_getline(char **, size_t *, FILE *);
extern void __pv_fwarn(int32, char *, ...);
extern void __terr(int32, char *s, ...);
extern void __pv_terr(int32, char *s, ...);
extern ssize_t __my_getline(char **, size_t *, FILE *);
extern void Msg(char *s, ...);
extern void __my_fprintf(FILE *f, char *s, ...);
extern void __my_vfprintf(FILE *, char *, va_list, va_list);
extern int32 __my_putc(int32, FILE *);

/*
 * read in options and print the report
 */
int32 main(int32 argc, char **argv)
{
 int32 i;
 char *argcp, *filename, *outfile;

 __init_tgldat_api_glbs();
 strcpy(__log_fnam, "tgldat_report.log");
 if ((__log_s = fopen(__log_fnam, "w")) == NULL) 
  {
   __terr(1, "unable to open output log file %s - unable to continue.\n",
    __log_fnam);
  }

 Msg("  tgldat_report version %s of %s.\n", VERS, OFDT);
 
 tgl_report_instance = FALSE; 
 tgl_report_bits = FALSE;     
 untgl_rpt_concise = FALSE;
 tgl_report_uncovered = FALSE;      
 tgl_report_covered = FALSE;       

 outfile = filename = NULL;
 /* read the arguments */
 for (i = 1; i < argc; i++)
  {
   argcp = argv[i];
   /* options - [-tu/-tc/-ti/-tb]  */
   if (strcmp(argcp, "-ti") == 0) tgl_report_instance = TRUE;
   else if (strcmp(argcp, "-tu") == 0) tgl_report_uncovered = TRUE;
   else if (strcmp(argcp, "-tc") == 0) tgl_report_covered = TRUE;
   else if (strcmp(argcp, "-tb") == 0) tgl_report_bits = TRUE;
   else if (strcmp(argcp, "-untoggled_report_concise") == 0)
    {
     untgl_rpt_concise = TRUE;
    }
   else if (strcmp(argcp, "-h") == 0) display_help_message();
   /* -o - define output file */
   else if (strcmp(argcp, "-o") == 0)
    {
     i++;
     if (i >= argc) 
      {
       __terr(20, "must supply output file to -o");
      }
     outfile = argv[i];
    }
   else 
    {
     /* can only report one file per run */
     if (filename != NULL)
      {
       __terr(21,
        "can only print report one .tgldat file per run or illegal option : %s",
        argcp);
      }
     filename = argcp;
    }
  }

 /* need to pass in one file */
 if (filename == NULL) 
  {
   __terr(22, "need to pass at least one .tgldat file to print report from");
  }

 /* read in the file and do the report */
 prep_and_print_report(filename, outfile);
 return(0);
}

/*
 * print program help message
 */
static void display_help_message(void)
{
 Msg("tgldat_report - USAGE: [filename] [-tu/-tc/-ti/-tb/-untoggled_report_concise] -o [outfilename]\n");
 Msg("        Output a toggle report from an input .tgldat format file.\n");
 Msg("        Must pass one input file and any of the following options:\n");
 Msg("          -untoggled_report_concise - new style only list untoggled bits.\n");
 Msg("          -tu - report all uncovered variables.\n");
 Msg("          -tc - report all covered variables.\n");
 Msg("          -ti - modify [-tu/-tc] report adding per instance reporting.\n");
 Msg("          -tb - modify [-tu/-tc] report reporting variables per bit.\n");
 Msg("          -o [filename] - output to file, otherwise stdout.\n\n");
 Msg("        For old .tvcd format files written by CVC 6.32 or earlier, run\n");
 Msg("        the tvcd_to_tgldat program to convert from .tvcd to .tgldat.\n");
 Msg("        To print a report from multiple runs either use CVC to merge\n");
 Msg("        .tgldat files or run the merge_tgldat program.\n");
 exit(0);
}

/*
 * ROUTINES TO GENERATE NORMAL VERBOSE REPORT FROM TVCD FILE
 */
   
/*
 * process the .tgldat file and print report of the toggle information
 * icp - input file name
 * ocp - output file name
 */
static void prep_and_print_report(char *tgldat_infnam, char *rpt_outfnam)
{
 FILE *ofp, *ifp;
 struct tgl_vardef_t *f_tvd_hd;
 
 /* open the new report output file */
 ofp = NULL;
 if (rpt_outfnam != NULL)
  {
   if ((ofp = fopen(rpt_outfnam, "w")) == NULL)
    {
     __terr(23, "opening printed report output file '%s' : %s",
      rpt_outfnam, strerror(errno));
    }
  }

 /* open the .tgldat input file to generate report from */
 if ((ifp = fopen(tgldat_infnam, "r")) == NULL)
  {
   __terr(25, "unable to open .tgldat input file '%s' : %s", tgldat_infnam,
    strerror(errno));
  }

 /* rd .tgldat file and build vardefs list */
 f_tvd_hd = __rd_tgldat_to_vardefs(ifp, tgldat_infnam);
 if (f_tvd_hd == NULL)
  {
   __terr(29, "file '%s' contains no signals to print report from",
    tgldat_infnam);
  }
 fclose(ifp);
 __bld_vardef_netlist(__file_netlist, f_tvd_hd, tgldat_infnam);  
 __file_netlist->nl_tvd_hd = f_tvd_hd;

 if (untgl_rpt_concise)
  { 
   /* if no file print to stdout */
   if (ofp != NULL)
    {
     print_untoggled_concise_report(ofp);
     fclose(ofp);
    } 
   else print_untoggled_concise_report(stdout);
  }
 else
  {
   if (ofp != NULL)
    {
     print_old_style_tgl_rpt(ofp, rpt_outfnam);
     fclose(ofp);
    } 
   else print_old_style_tgl_rpt(stdout, "STDOUT");
  }
}
 
/*
 * print to fp the old style per mod toggle report
 *
 * this report format does not have real instance tree toggle information
 * but uses the net list tgl dat records from the .tgldat rooted path
 * to a net tgl state
 *
 * net_count[01,10] are ptrs to per bit int32 tab of toggle values rather
 * than bits as was used in old CVC toggle coverage code
 */
static void print_old_style_tgl_rpt(FILE *fp, char *out_fnam)
{
 int32 ni, mi, ii, max_net_slen, max_net_blen;
 int32 hits01, hits10, covered10, covered01;
 int32 mod_nbits, mod_hits01, mod_hits10;
 int32 inst_nbits, inst_hits01, inst_hits10;
 int32 accum_nbits, accum_hits01, accum_hits10;
 int32 some_printed, ninsts, max_inst_nets;
 struct td_mod_t *tdmdp;
 struct td_inst_t *tdip;
 struct tgl_vardef_t *tvdp;
 char s1[RECLEN];

 max_net_slen = 0;
 max_inst_nets = 0;
 max_net_blen = 0; 
 if (tgl_report_uncovered || tgl_report_covered)
  {
   fnd_netlist_maxes(__file_netlist, &(max_inst_nets), &(max_net_blen),
    &(max_net_slen));
   alloc_init_net_counts(max_inst_nets, max_net_blen);
  }

 __my_fprintf(fp, "\n \
                            ************************************************\n \
                            **                                            **\n \
                            **  CVC - Verilog Toggle Coverage Report      **\n \
                            **                                            **\n \
                            **                                            **\n \
                            ************************************************\n\n");
 __my_fprintf(fp, "+++ Written by toggle_report version %s of %s\n", VERS, OFDT);
 __my_fprintf(fp, "+++ .tgldat file created :  %s\n", __tgldat_writer_date);
 __my_fprintf(fp, "+++ .tgldat WRITER VERSION :  %s\n", __tgldat_writer_vers);
 __my_fprintf(fp, "\n\n\n");

 /* counts for entire design */
 accum_nbits = 0;
 accum_hits01 = 0;
 accum_hits10 = 0;
 
 /* info per mod that appeared in .tgldat file */
 for (mi = 0; mi < __file_netlist->num_td_mods; mi++)
  {
   tdmdp = __file_netlist->nlmods[mi];

   /* get the number of insts of this mod in the .tgldat file */
   /* know at least one inst in mod or will not be in vardef d.s. */
   /* some insts in design net list may be missing from excludes */
   ninsts = tdmdp->num_td_instsof;

   __my_fprintf(fp, "==================================================================================================\n");
   /* arbitrarily use first inst for number of nets - different excludes */
   /* in differenet insts possible but know at least one vardef in any tab */
   /* signal number is 0th - other may differ */
   __my_fprintf(fp, "MODULE : %s (%d INSTANCE(S), %d NET(S))\n",
    tdmdp->modnam, tdmdp->num_td_instsof,
    tdmdp->td_instsof[0]->td_num_nets);
   __my_fprintf(fp, "==================================================================================================\n");
   mod_nbits = 0;
   mod_hits01 = 0;
   mod_hits10 = 0;

   /* for every inst of module */
   for (ii = 0; ii < tdmdp->num_td_instsof; ii++)
    {
     tdip = tdmdp->td_instsof[ii];

     /* all insts of the module type are pointed to by the netvardefs tab */
     inst_nbits = 0;
     inst_hits01 = 0;
     inst_hits10 = 0;
     /* if reporting per inst and only one inst of module type in .tgldat */
     /* file use the module form - notice all nets may only have one */
     /* vardef tgl state entry (probably different for each inst) but if */
     /* more than one inst appears in .tgldat file, need inst report form */
     /* if only one inst of a module type, instance form same */ 
     if (tgl_report_instance && tdmdp->num_td_instsof > 1)
      {
       /* all vardefs will have same inst name */
       __my_fprintf(fp, "\n\n\tINSTANCE : %s  \n", tdip->netvardefs[0]->in_instnam);
      }
     
     ni = 0; 
     /* get the toggle count for each net */
     for (ni = 0; ni < tdip->td_num_nets; ni++)
      {
       tvdp = tdip->netvardefs[ni];
       
       covered10 = get_toggle_count(tvdp, tvdp->tglcnt_10, &(hits10));
       covered01 = get_toggle_count(tvdp, tvdp->tglcnt_01, &(hits01));

       inst_nbits += get_net_toggle_blen(tvdp);

       inst_hits10 += hits10;
       inst_hits01 += hits01;
      }

     /* if more than one module and per istance option */
     if (tdmdp->num_td_instsof > 1 && tgl_report_instance)
      {
       /* add extra length for [index] */
       if (tgl_report_bits) max_net_slen += 8;
 
       /* print instance coverage values */
       print_hits_misses(fp, "\t\t", inst_hits01, inst_hits10, inst_nbits);
       if (tgl_report_uncovered || tgl_report_covered)
        {
         __my_fprintf(fp, "\n\n\t\t------------------------------------\n");
         if (tgl_report_uncovered)
          {
           __my_fprintf(fp, "\t\t SIGNALS NOT GETTING 100%% COVERAGE \n");
          }
         else
          {
           __my_fprintf(fp, "\t\t SIGNALS GETTING 100%% COVERAGE \n");
          }
         __my_fprintf(fp, "\t\t------------------------------------\n");
         memset(s1, ' ', max_net_slen);
         s1[max_net_slen] = '\0';
         if (tgl_report_uncovered)
          { 
           __my_fprintf(fp, "\t\tSignal  %sToggle\n", s1);
          } 
         else __my_fprintf(fp, "\t\tSignal  %s\n", s1);
         __my_fprintf(fp,
          "\t\t-------------------------------------------------------------------------------------------\n");
         some_printed = FALSE;
         /* print the net coverage info */
         for (ni = 0; ni < tdip->td_num_nets; ni++)
          {
           tvdp = tdip->netvardefs[ni];
           some_printed |= print_toggle_net_coverage(fp, tvdp, "\t\t", 
            max_net_slen, tvdp->tglcnt_01, tvdp->tglcnt_10);
          }
         if (!some_printed) 
          {
           if (tgl_report_uncovered)
            __my_fprintf(fp, "\t\t ** ALL SIGNALS 100%% COVERED ** \n");
           else __my_fprintf(fp, "\t\t ** NO SIGNALS 100%% COVERED **\n");
          }
        }
      }
     /* add up all modules bits */
    mod_nbits += inst_nbits;
    mod_hits10 += inst_hits10;
    mod_hits01 += inst_hits01;
   }

  /* sum of instances if > 1 */
  if (tdmdp->num_td_instsof > 1)
   {
    __my_fprintf(fp, "\n\n\tACCUMULATED INSTANCES (%d) of MODULE %s:\n",
     tdmdp->num_td_instsof, tdmdp->modnam);
    }
   print_hits_misses(fp, "\t\t", mod_hits01, mod_hits10, mod_nbits);

   /* entire module (any instances) coverage */
   if (tgl_report_uncovered || tgl_report_covered)
    {
     __my_fprintf(fp, "\n\n\t-----------------------------------------------------------\n");
     if (tdmdp->num_td_instsof > 1)
      {
       __my_fprintf(fp, "\t-- MODULE (%s) ANY INSTANCE COVERAGE \n", tdmdp->modnam);
      }
     else
      {
       __my_fprintf(fp, "\t-- MODULE (%s) COVERAGE \n", tdmdp->modnam);
      }
     __my_fprintf(fp, "\t-----------------------------------------------------------\n");
     if (tdmdp->num_td_instsof > 1)
      {
       if (tgl_report_uncovered)
        {
         __my_fprintf(fp, "\t SIGNALS NOT GETTING 100%% COVERAGE OVER ANY INSTANCES\n");
        }
       else
        {
         __my_fprintf(fp, "\t SIGNALS GETTING 100%% COVERAGE OVER ANY INSTANCES\n");
        }
      }
     else
      {
       if (tgl_report_uncovered)
        {
         __my_fprintf(fp, "\t SIGNALS NOT GETTING 100%% COVERAGE\n");
        }
       else
        {
         __my_fprintf(fp, "\t SIGNALS GETTING 100%% COVERAGE\n");
        }
      }
 
     __my_fprintf(fp, "\t-----------------------------------------------------------\n");
     memset(s1, ' ', max_net_slen);
     s1[max_net_slen] = '\0';
     if (tgl_report_uncovered) __my_fprintf(fp, "\tSignal  %sToggle\n", s1);
     else __my_fprintf(fp, "\tSignal  %s\n", s1);
     __my_fprintf(fp, "\t-------------------------------------------------------------------------------------------\n");
     /* this is accumulated toggle states for all insts of net */
     some_printed = FALSE;
     /* SJM 10-24-13 - new convention - net counts that cumulative for all */
     /* insts match 0th inst since some bits may not be present in some */
     /* insts */
     tdip = tdmdp->td_instsof[0];
     for (ni = 0; ni < tdip->td_num_nets; ni++)
      {
       calc_one_mod_instnet_combined_tgls(tdmdp, ni, max_inst_nets,
        max_net_blen);
       tvdp = tdip->netvardefs[ni];
       some_printed |= print_toggle_net_coverage(fp, tvdp, "\t",
        max_net_slen, __net_count01[ni], __net_count10[ni]);
      }
     if (!some_printed) 
      {
       if (tgl_report_uncovered)
        __my_fprintf(fp, "\t ** ALL SIGNALS 100%% COVERED **\n");
       else __my_fprintf(fp, "\t ** NO SIGNALS 100%% COVERED ** \n");
      }
    }
   accum_hits10 += mod_hits10;
   accum_hits01 += mod_hits01;
   accum_nbits += mod_nbits;
   __my_fprintf(fp, "\n\n");
  }
 /* all toggled bits */
 __my_fprintf(fp, "==================================================================================================\n");
 __my_fprintf(fp, "ALL TOGGLED BITS:\n");
 print_hits_misses(fp, "\t", accum_hits01, accum_hits10, accum_nbits);
 /* should free net count including array of ptrs to since done just leak */
 /* memory */
}

/*
 * calculate combined toggle state for all insts of net
 *
 * tricky because some nets and bits may be excluded for net so each
 * net may have different number and therefore different ni - need to
 * use first inst and search
 */
static void calc_one_mod_instnet_combined_tgls(struct td_mod_t *tdmdp,
 int32 ni, int32 max_nets, int32 max_bits)
{
 int32 ii, ni2, bi;
 struct tgl_vardef_t *tvdp;

 tvdp = tdmdp->td_instsof[0]->netvardefs[ni];
 /* re init max size */
 re_init_net_counts(max_nets, max_bits);
 for (ii = 0; ii < tdmdp->num_td_instsof; ii++)
  {
   if (ii == 0) ni2 = ni;
   else
    {
    /* find net with same name in other than first inst, may not exist */
     ni2 = __fnd_td_inst_vardefs(tdmdp->td_instsof[ii], tvdp->netnam);
    }
   if (ni2 != -1)
    { 
     /* combine in net counts per bit but all insts combined */
     for (bi = 0; bi < tvdp->nbits; bi++)
      {
       /* SJM 10-21-13 - tglcnt only includes really toggled 1 in old */ 
       /* if excluded or not toggled, do not change all inst combined */
       if (tvdp->tglcnt_01[bi] == 1) __net_count01[ni2][bi] = 1;
       if (tvdp->tglcnt_10[bi] == 1) __net_count10[ni2][bi] = 1;
      }
    }
  } 
}

/*
 * re-init net counts
 */
static void re_init_net_counts(int32 max_nets, int32 max_bits)
{
 int32 ni, bi;
 for (ni = 0; ni < max_nets; ni++)
  {
   /* SJM - 11-05-13  should be max bits obviously - was causing core dump */
   for (bi = 0; bi < max_bits; bi++)
    {
     __net_count01[ni][bi] = 0;
     __net_count10[ni][bi] = 0;
    }
  }
}

/*
 * alloc init net counts 
 */
static void alloc_init_net_counts(int32 max_nets, int32 max_bits)
{
 int32 ni, bi;

 __net_count01 = (int32 **) __my_malloc(max_nets*sizeof(int32 *));
 __net_count10 = (int32 **) __my_malloc(max_nets*sizeof(int32 *));
 for (ni = 0; ni < max_nets; ni++)
  {
   __net_count01[ni] = (int32 *) __my_malloc(max_bits*sizeof(int32));
   __net_count10[ni] = (int32 *) __my_malloc(max_bits*sizeof(int32));
   
   /* SJM - 11-05-13  should be max bits obviously - was causing core dump */
   for (bi = 0; bi < max_bits; bi++)
    {
     __net_count01[ni][bi] = 0;
     __net_count10[ni][bi] = 0;
    }
  }
}

/*
 * alloc and initialize the max siz net count (tgl) accumulator
 */
static void fnd_netlist_maxes(struct td_netlist_t *nlp, int32 *max_nets,
 int32 *max_bits, int32 *max_net_slen)
{
 int32 mi, ii, ni, slen;
 struct td_mod_t *tdmdp;
 struct td_inst_t *tdip;
 struct tgl_vardef_t *tvdp;

 *max_nets = 0;
 *max_bits = 0;
 *max_net_slen = 0;
 for (mi = 0; mi < nlp->num_td_mods; mi++)
  {
   tdmdp = nlp->nlmods[mi];
   for (ii = 0; ii < tdmdp->num_td_instsof; ii++)
    {
     tdip = tdmdp->td_instsof[ii];
     if (*max_nets < tdip->td_num_nets) *max_nets = tdip->td_num_nets;
     for (ni = 0; ni < tdip->td_num_nets; ni++) 
      {
       tvdp = tdip->netvardefs[ni]; 
       slen = strlen(tvdp->netnam); 
       if (slen > *max_net_slen) *max_net_slen = slen;
       if (*max_bits < tvdp->nbits) *max_bits = tvdp->nbits;
      }
    }
  }
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
 if (nbits == 0) percenth01 = 0.0;
 else percenth01 = (int) 100.0*((double) hits01)/((double) nbits);
 if (nbits == 0) percenth10 = 0.0;
 else percenth10 = (int) 100.0*((double) hits10)/((double) nbits);

 __my_fprintf(fp, "%s", indentp);
 __my_fprintf(fp, "----------------------------         ----------------------------\n");
 __my_fprintf(fp, "%s", indentp);
 __my_fprintf(fp, "       TOGGLE 0 -> 1                      TOGGLE 1 -> 0\n");  
 __my_fprintf(fp, "%s", indentp);
 __my_fprintf(fp, "----------------------------         ----------------------------\n");
 sprintf(s1, "%shits : %d", indentp, hits01); 
 second_column = 37 + strlen(indentp);
 slen = strlen(s1);
 memset(s2, ' ', second_column - slen);
 s2[second_column - slen] = '\0';
 __my_fprintf(fp, "%s%shits : %d\n", s1, s2, hits10);

 sprintf(s1, "%smiss : %d", indentp, miss01); 
 slen = strlen(s1);
 memset(s2, ' ', second_column - slen);
 s2[second_column - slen] = '\0';
 __my_fprintf(fp, "%s%smiss : %d\n", s1, s2, miss10);


 sprintf(s1, "%sbits : %d", indentp, nbits); 
 slen = strlen(s1);
 memset(s2, ' ', second_column - slen);
 s2[second_column - slen] = '\0';
 __my_fprintf(fp, "%s%sbits : %d\n", s1, s2, nbits);

 sprintf(s1, "%spercent hit : %d%%", indentp, percenth01);
 slen = strlen(s1);
 memset(s2, ' ', second_column - slen);
 s2[second_column - slen] = '\0';
 __my_fprintf(fp, "%s%spercent hit : %d%%\n", s1, s2, percenth10);
}

/*
 * get a net's toggle count set to *hits - tglcnt_tab is array
 * of 4 possible ints (0 bit not tgl, 1 bit tgl, -1 ('?' in .tgldat file)
 * is bit excluded, -2 ('C' in .tgldat files) bit * tied to a constant (maybe
 * indirectly)
 *
 * return TRUE if 100% coverage
 *
 * SJM 11-18-13 - driven const does not exist in old report world so -2
 * is just normal untoggled to match old behavior - excluded still left out
 */
static int32 get_toggle_count(struct tgl_vardef_t *tvdp, int32 *tglcnt_tab,
 int32 *hits)
{
 int32 count, bi, nwid, num_included;

 count = 0;
 nwid = 1;
 /* scalar or 1 bit vector just get 0th */
 if (tvdp->nbits == 1)
  {
   num_included = 1;
   count = tglcnt_tab[0];
  }
 else
  {
   num_included = 0;
   for (bi = 0; bi < tvdp->nbits; bi++)
    {
     /* bit excluded */
     if (tglcnt_tab[bi] == -1) continue;
     num_included++;
     /* only really toggled counted in old style reports */
     if (tglcnt_tab[bi] == 1) count++;
    }
  }
 *hits = count;
 /* if hit count == included width then 100% of net covered so return T */
 return((count == num_included));
}

/*
 * return the number of bits for net which are not excluded (turned on)
 * know if 0->1 excluded so will 1->0 be excluded
 *
 * SJM 10-21-13 - in tglcnt 01 and 10 tabs (arrays) '?' excluded stored as -1
 * SJM 11-18-13 - in old report world, no driven const so just treat as untgl
 *                - old format could exclude bits which are not counted
 */         
static int32 get_net_toggle_blen(struct tgl_vardef_t *tvdp)
{
 int32 bi, num;

 for (num = 0, bi = 0; bi < tvdp->nbits; bi++)
  {
   if (tvdp->tglcnt_01[bi] != -1) num++;
  }
 return(num);
}

/*
 * print one net's toggle coverage 
 *
 * unlike old code tgl01p and tgl10p are arrays of ints of toggle number
 */
static int32 print_toggle_net_coverage(FILE *fp, struct tgl_vardef_t *tvdp,
 char *icp, int32 max_net_slen, int32 *tgl01p, int32 *tgl10p)
{
 int32 bi, biti, slen, some_printed;
 int32 hits01, hits10, covered10, covered01, bit_covered01, bit_covered10;
 char s1[RECLEN], s2[RECLEN], hexstr[RECLEN];

 /* get the toggle count for the net */
 covered01 = get_toggle_count(tvdp, tgl01p, &hits01);
 covered10 = get_toggle_count(tvdp, tgl10p, &hits10);
 some_printed = FALSE;
 /* report he uncovered nets */
 if (tgl_report_uncovered)
  {
   /* if not covered - report net */
   if (!covered10 || !covered01) 
    { 
     /* scalarize - if per bit */
     if (tgl_report_bits && tvdp->nbits > 1)
      {
       for (bi = 0; bi < tvdp->nbits; bi++)
        {
         /* SJM 11-08-13 - now exclude driven con too since can't toggle */
         /* if bit excluded do not print */
         /* SJM 11-18-13 - in old report world - driven con invisible */
         /* so count as normal untoggled - excluded bits exist */ 
         if (tgl01p[bi] == -1) continue;

         biti = unnormalize_ndx(tvdp, bi);
         /* AIV 03/04/11 - had these backwards 10/01 */
         /* only really toggled counted in old style report */
         bit_covered01 = (tgl01p[bi] == 1) ? 1 : 0;
         bit_covered10 = (tgl10p[bi] == 1) ? 1 : 0;
         if (!bit_covered01 || !bit_covered10)
          {
           sprintf(s1, "%s[%d]", tvdp->netnam, biti);
           slen = strlen(s1);
           memset(s2, '.', max_net_slen-slen+7);
           s2[max_net_slen-slen+7] = '\0';
           __my_fprintf(fp, "%s%s%s 0->1: %d\n", icp, s1, s2, bit_covered01);

           memset(s2, '.', max_net_slen+7);
           s2[max_net_slen+7] = '\0';
           __my_fprintf(fp, "%s%s 1->0: %d\n", icp, s2, bit_covered10);
           some_printed = TRUE;
          }
        }
      }
     else
      {
       /* if not per bit - print the toggle vector */
       get_hexstr(hexstr, tgl01p, tvdp->nbits);
       slen = strlen(tvdp->netnam);
       memset(s2, '.', max_net_slen-slen+7);
       s2[max_net_slen-slen+7] = '\0';
       __my_fprintf(fp, "%s%s%s 0->1: %d'h%s\n", icp, tvdp->netnam, s2, 
         tvdp->nbits, hexstr);
       memset(s2, '.', max_net_slen+7);
       s2[max_net_slen+7] = '\0';
       get_hexstr(hexstr, tgl10p, tvdp->nbits);
       __my_fprintf(fp, "%s%s 1->0: %d'h%s\n", icp, s2, tvdp->nbits, hexstr);
       some_printed = TRUE;
      }
    }
  }
 else
  {
   /* print the covered nets - this is toggle report covered option */
   if (tgl_report_bits && tvdp->nbits > 1)
    {
     for (bi = 0; bi < tvdp->nbits; bi++)
      {
       /* SJM 11-18-13 - in old report world no driven cons so treated as */
       /* untoggled */
       if (tgl01p[bi] == -1) continue;

       biti = unnormalize_ndx(tvdp, bi);
       /* SJM 10-22-13 - covered is only really toggled 1 in old style */
       bit_covered01 = (tgl01p[bi] == 1) ? 1 : 0;
       bit_covered10 = (tgl10p[bi] == 1) ? 1 : 0;
       if (bit_covered01 && bit_covered10)
        {
         __my_fprintf(fp, "%s%s[%d]\n", icp, tvdp->netnam, biti);
         some_printed = TRUE;
        }
      }
    }
   else if (covered10 && covered01) 
    { 
     __my_fprintf(fp, "%s%s\n", icp, tvdp->netnam);
     some_printed = TRUE;
    }
  }

 return(some_printed);
}

       
/*
 * take a tgl tab array of 4 tgl tab tgl state values and build a 
 * hex value string
 *
 * this converts 4 tab array values into one hex digit with 'C' becoming
 * 1 bit and '0' or excluded ('?') becoming 0 bit value
 * driven const become untoggled too
 */
static void get_hexstr(char *hexstr, int32 *tgltab, int32 nbits)
{
 int32 bi, nchars, extra_bits;
 word32 tmpa;
 char ch, endch;

 /* common 1 bit case */
 if (nbits == 1)
  {
   /* not toggled or excluded (-1) is 0 else 1 */
   /* SJM 10-24-13 - following old code excluded bits are considered not */
   /* toggled */
   if (tgltab[0] == 1) ch = '1'; else ch = '0';
   hexstr[0] = ch;
   hexstr[1] = '\0';
   return;
  }

 /* handle the last digit - maybe be 1 to 4 bits */
 /* here only reall 1 (toggle) is considered toggled */
 endch = '?';
 if ((nbits % 4) != 0) 
  {
   extra_bits = TRUE;
   /* max hex value here can be 7 here (3 bits extra) */
   if ((nbits % 4) == 1)
    {
     if (tgltab[nbits - 1] == 1) tmpa = 1; else tmpa = 0;
     nbits--;
    }
   else if ((nbits % 4) == 2)
    {
     if (tgltab[nbits - 1] == 1) tmpa = 0x2; else tmpa = 0;
     if (tgltab[nbits - 2] == 1) tmpa |= (tmpa | 0x1);
     nbits -= 2;
    }
   else 
    {
     if (tgltab[nbits - 1] == 1) tmpa = 0x4; else tmpa = 0;
     if (tgltab[nbits - 2] == 1) tmpa |= (tmpa | 0x2);
     if (tgltab[nbits - 3] == 1) tmpa |= (tmpa | 0x1);
     nbits -= 3;
    }
   endch = '0' + tmpa;
  }
 else extra_bits = FALSE;
 
 for (nchars = 0, bi = 0; bi < nbits; bi += 4)
  {
   /* know array stored X86 little endian world h:0 with arr index 0 bit 0 */
   if (tgltab[bi] == 1) tmpa = 0x8; else tmpa = 0;
   if (tgltab[bi + 1] == 1) tmpa |= (tmpa | 0x4); 
   if (tgltab[bi + 2] == 1) tmpa |= (tmpa | 0x2); 
   if (tgltab[bi + 3] == 1) tmpa |= (tmpa | 0x1); 
   ch = (((tmpa) < 10) ? '0' + (tmpa) : 'a' + (tmpa) - 10);
   hexstr[nchars++] = ch;
  }
 if (extra_bits) hexstr[nchars++] = endch;
 hexstr[nchars] = '\0';
}

/*
 * get the index of the net for bi
 */
static int32 unnormalize_ndx(struct tgl_vardef_t *tvdp, int32 bi)
{
 int32 r1, r2;

 r1 = tvdp->rng1;
 r2 = tvdp->rng2;
 if (r1 >= r2) return(r2 + bi); else return(r2 - bi);
}

/*
 * ROUTINES TO PRINT THE UNTOGGLED CONCISE REPORT
 */

/*
 * print to fp the untoggled concise report - eliminate anything toggled
 *
 * never called unless design has at least one net
 */
static void print_untoggled_concise_report(FILE *fp)
{
 int32 mi, ii, ni, mod_has_untgl, inst_has_untgl, dsgn_has_untgl;
 int32 tot_insts, tot_sigs, tot_bits, tot_tgls, tot_01_tgls, tot_10_tgls;
 int32 tot_excl_bits, tot_drvn_con_bits, tot_drvn_con_sigs;
 int32 tot_untgls, tot_cor_bits, tot_cor_sigs;
 double d1, d2;
 struct td_mod_t *tdmdp;
 struct td_inst_t *tdip;
 struct tgl_vardef_t *tvdp;

 __my_fprintf(fp, "** CVC Toggle Coverage from -untoggled_rpt_concise\n");
 __my_fprintf(fp, "** .tgldat File Written : %s\n", __tgldat_writer_date);
 __my_fprintf(fp, "** From .tgldat writer : %s\n", __tgldat_writer_vers);

 dsgn_has_untgl = FALSE;
 for (mi = 0; mi < __file_netlist->num_td_mods; mi++)
  {
   tdmdp = __file_netlist->nlmods[mi];

   mod_has_untgl = FALSE;
   for (ii = 0; ii < tdmdp->num_td_instsof; ii++)
    {
     inst_has_untgl = FALSE;  
     tdip = tdmdp->td_instsof[ii];

     for (ni = 0; ni < tdip->td_num_nets; ni++)
      {
       tvdp = tdip->netvardefs[ni];

       if (all_sig_bits_included(tvdp) && no_sig_bits_drvn_const(tvdp))
        { 
         if (all_sig_bits_tgl(tvdp, TRUE) && all_sig_bits_tgl(tvdp, FALSE))
          continue;
        }

       /* has a signal with some bits untoggled */
       if (!mod_has_untgl)
        {
         mod_has_untgl = TRUE;
         __my_fprintf(fp, "MODULE: %s (%d instances):\n", tdmdp->modnam,
          tdmdp->num_td_instsof);
        }
       if (!inst_has_untgl)
        {
         inst_has_untgl = TRUE;
         dsgn_has_untgl = TRUE;
         __my_fprintf(fp, "  INSTANCE %s (%d nets):\n",
          tdip->irtpthnam, tdip->td_num_nets);
        }
       print_1sig_untgl(fp, tvdp);
      }
     if (inst_has_untgl)
      {
       tot_sigs = 0;
       tot_bits = 0;
       tot_tgls = tot_01_tgls = tot_10_tgls = 0;
       tot_excl_bits = tot_drvn_con_bits = tot_drvn_con_sigs = 0; 
       /* SJM 11-10-13 - now do not count excluded or driven con bits at all */
       /* idea is that there are per bit 4 possibiities: untoggled, */
       /* toggled, only 0-1 toggle, only 1-0 toggle */
       add_tot_1inst_sigs_bits(tdip, &(tot_sigs), &(tot_bits), &(tot_tgls),
        &(tot_01_tgls), &(tot_10_tgls), &(tot_excl_bits), &(tot_drvn_con_bits),
        &(tot_drvn_con_sigs));
       /* SJM 10-08-13 - driven const and excluded bits not counted in stats */
       tot_cor_bits = tot_bits - tot_excl_bits - tot_drvn_con_bits;
       tot_cor_sigs = tot_sigs - tot_drvn_con_sigs;
       /* only emit something if there are some really untoggled */
       if (tot_cor_bits > 0)
        {
         tot_untgls = tot_cor_bits - (tot_tgls + tot_01_tgls + tot_10_tgls);
         d1 = 100.0*((double) tot_untgls)/((double) tot_cor_bits);
         __my_fprintf(fp,
         "  COVER [%d nets %d bits] untoggled %d bits (%.2f%%)\n",
          tot_cor_sigs, tot_cor_bits, tot_untgls, d1);

         if (tot_10_tgls != 0 || tot_01_tgls != 0)
          {
           d1 = 100.0*((double) tot_10_tgls)/((double) tot_cor_bits);
           d2 = 100.0*((double) tot_01_tgls)/((double) tot_cor_bits);
           __my_fprintf(fp,
            "    1->0 but not 0->1 %d (%.2f%%) 0->1 but not 1->0 %d (%.2f%%)\n",
            tot_10_tgls, d1, tot_01_tgls, d2);
          } 
        }
       if (tot_excl_bits != 0 || tot_drvn_con_bits != 0)
        {
         __my_fprintf(fp,
          "   %d driven to constant bits (%d entire nets), %d excluded bits\n",
          tot_drvn_con_bits, tot_drvn_con_sigs, tot_excl_bits);
        } 
      }
    } 
   if (mod_has_untgl && tdmdp->num_td_instsof > 1)
    {
     mod_tot_sigs_bits(tdmdp, &(tot_insts), &(tot_sigs), &(tot_bits),
      &(tot_tgls), &(tot_01_tgls), &(tot_10_tgls), &(tot_excl_bits),
      &(tot_drvn_con_bits), &(tot_drvn_con_sigs));
     tot_cor_bits = tot_bits - tot_excl_bits - tot_drvn_con_bits;
     tot_cor_sigs = tot_sigs - tot_drvn_con_sigs;
     /* SJM 11-13-13 - this needs to be cor bits or else div by 0 possible */
     if (tot_cor_bits > 0)
      {
       tot_untgls = tot_cor_bits - (tot_tgls + tot_01_tgls + tot_10_tgls);
       d1 = 100.0*((double) tot_untgls)/((double) tot_cor_bits);
       __my_fprintf(fp, "TOTAL MOD %s [%d nets %d bits] untoggled %d (%.2f%%)\n",
        tdmdp->modnam, tot_cor_sigs, tot_cor_bits, tot_untgls, d1);
       if (tot_10_tgls != 0 || tot_01_tgls != 0)
        {
         d1 = 100.0*((double) tot_10_tgls)/((double) tot_cor_bits);
         d2 = 100.0*((double) tot_01_tgls)/((double) tot_cor_bits);
         __my_fprintf(fp,
          "  1->0 but not 0->1 %d (%.2f%%) 0->1 but not 1->0 %d (%.2f%%)\n",
          tot_10_tgls, d1, tot_01_tgls, d2);
        }
      }
     if (tot_excl_bits != 0 || tot_drvn_con_bits != 0)
      {
       __my_fprintf(fp,
         "   %d driven to constant bits (%d entire nets), %d excluded bits\n",
         tot_drvn_con_bits, tot_drvn_con_sigs, tot_excl_bits);
      } 
    }
  }
 if (dsgn_has_untgl)
  { 
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
     __my_fprintf(fp,
      "** DESIGN [%d nets %d bits] untoggled %d bits (%.2f%%) toggled %d (%.2f%%)\n",
      tot_cor_sigs, tot_cor_bits, tot_untgls, d1, tot_tgls, d2);
     if (tot_10_tgls != 0 || tot_01_tgls != 0)
      {
       d1 = 100.0*((double) tot_10_tgls)/((double) tot_cor_bits);
       d2 = 100.0*((double) tot_01_tgls)/((double) tot_cor_bits);
       __my_fprintf(fp,
        "  1->0 but not 0->1 %d (%.2f%%) 0->1 but not 1->0 %d (%.2f%%)\n",
        tot_10_tgls, d1, tot_01_tgls, d2);
      }
    }
   if (tot_excl_bits != 0 || tot_drvn_con_bits != 0)
    {
     __my_fprintf(fp,
      "   %d driven to constant bits (%d entire nets), %d excluded bits\n",
      tot_drvn_con_bits, tot_drvn_con_sigs, tot_excl_bits);
    } 
  }
 else
  {
   __my_fprintf(fp,
    "** SUCCESS! EVERY NET IN DESIGN has BOTH 0->1 and 1->0 TOGGLES **\n");
  }
}

/*
 * routine to print per bit lines for one signal
 *
 * SJM 10-31-12 - key to this proc is that the char string in the .tvcd
 * file and the bit string built in tgl vardef first starting low bit is bit
 * 0 that is opposite PLI where low bit is rightmost bit of word
 */
static void print_1sig_untgl(FILE *fp, struct tgl_vardef_t *tvdp)
{
 int32 tgl_state, bi, nxt_down_bi;
 char s1[RECLEN], s2[RECLEN];

 /* case 1: scalar */
 if (tvdp->nbits == 1 && tvdp->rng1 == -1)
  {
   if (tvdp->tglcnt_01[0] == 0 && tvdp->tglcnt_10[0] == 0)
    {
     __my_fprintf(fp, "    %s: no toggles\n", tvdp->netnam); 
    }
   /* SJM 10-22-13 - driven const is -2 (but 'C' in .tgldat files) */
   else if (tvdp->tglcnt_01[0] == -2)
    {
     __my_fprintf(fp, "    %s: driven const\n", tvdp->netnam);
    }
   else if (tvdp->tglcnt_01[0] == 1 && tvdp->tglcnt_10[0] == 0)
    {
     __my_fprintf(fp, "    %s: no 1->0 toggles\n", tvdp->netnam);
    }
   else if (tvdp->tglcnt_01[0] == 0 && tvdp->tglcnt_10[0] == 1)
    {
     __my_fprintf(fp, "    %s: no 0->1 toggles\n", tvdp->netnam);
    }
   else
    { 
     __terr(10, "if scalar net %s excluded, should not be .tgldat file",
      tvdp->netnam);
    }
   return;
  }
 /* case 2: a vector */
 /* 0/1 string in the .tvcd file and then bit vector right most bit is */
 /* internal bit 0 because stored h:0 form like Verilog */
 /* move high to low because should print subvectors high to low */
 for (bi = tvdp->nbits - 1; bi >= 0; bi--)
  {
   /* first bit of bit string is bit 0 of vector */
   tgl_state = fnd_same_tgl_select(tvdp, bi, &(nxt_down_bi));
   /* if both toggle, no msg only untoggled or special case interesting */
   if (tgl_state == 2) { bi = nxt_down_bi; continue; }

   /* all of net means both high same as size-1 and low 0 */ 
   if (tvdp->nbits - 1 == bi && nxt_down_bi == 0)
    {
     sprintf(s2, "<all of net> ");
    }
   else if (bi - nxt_down_bi > 1) sprintf(s2, "<of %d> ", tvdp->nbits);
   else strcpy(s2, "");

   bld_unnormalized_rng_str(s1, bi, nxt_down_bi, tvdp->rng1, tvdp->rng2);
   if (tgl_state == -3)
    {
     __my_fprintf(fp, "    %s%s%s: exclude\n", tvdp->netnam, s1, s2); 
    } 
   else if (tgl_state == -2)
    {
     __my_fprintf(fp, "    %s%s%s: driven constant\n", tvdp->netnam, s1, s2); 
    }
   else if (tgl_state == 1)
    {
     /* SJM 11-18-13 - tgl state 1 means 0 to 1 toggled */
     __my_fprintf(fp, "    %s%s%s: no 1->0 toggles\n", tvdp->netnam, s1, s2); 
    }
   else if (tgl_state == 0)
    {
     /* SJM 11-18-13 - tgl state 0 means 1 to 0 toggled */
     __my_fprintf(fp, "    %s%s%s: no 0->1 toggles\n", tvdp->netnam, s1, s2); 
    }
   else
    {
     __my_fprintf(fp, "    %s%s%s: no toggles\n", tvdp->netnam, s1, s2); 
    }
   bi = nxt_down_bi - 1;
  }
}

/*
 * build unnormalized vector select range/bit
 */
static char *bld_unnormalized_rng_str(char *s, int32 hind, int32 lind,
 int32 rng1, int32 rng2)
{
 if (hind == lind)
  {
   sprintf(s, "[%d]", unnormalize2_ndx(hind, rng1, rng2));
  }
 else
  {
   sprintf(s, "[%d:%d]", unnormalize2_ndx(hind, rng1, rng2),
    unnormalize2_ndx(lind, rng1, rng2));
  }
 return(s);
}

/*
 * routine to map normalized h:0 form index back to input value
 * 2nd variant for multi-dim arrays where must pass the range
 */
static int32 unnormalize2_ndx(int32 indi, int32 mr1, int32 mr2)
{
 if (mr1 >= mr2) return(mr2 + indi);
 else return(mr2 - indi);
}

/*
 * in h:0 world, find range of same value signals and return info
 * return -1 for no tgl, 2 for both tgl, 0 for 1->0 tgl, 1 for 0->1 
 */
static int32 fnd_same_tgl_select(struct tgl_vardef_t *tvdp, int32 selbi,
 int32 *last_same_down_bi)
{
 int32 bi, last_tgl_state, nxt_tgl_state;

 last_tgl_state = -4;
 for (bi = selbi; bi >= 0; bi--)
  {
   /* know both same or .tgldat net list will not be read in and built */

   /* SJM 10-13-13 - LOOKATME - think .tgldat really in h:0 order so just */
   /* access */
   if (tvdp->tglcnt_01[bi] == -1) nxt_tgl_state = -3;
   else if (tvdp->tglcnt_01[bi] == -2) nxt_tgl_state = -2;
   else
    {
     if (tvdp->tglcnt_01[bi] == 1 && tvdp->tglcnt_10[bi] == 1)  
      nxt_tgl_state = 2;
     else if (tvdp->tglcnt_01[bi] == 0 && tvdp->tglcnt_10[bi] == 0)  
      nxt_tgl_state = -1; 
     else if (tvdp->tglcnt_01[bi] == 1) nxt_tgl_state = 1; 
     else nxt_tgl_state = 0; 
    } 
   if (last_tgl_state == -4) last_tgl_state = nxt_tgl_state;
   else if (last_tgl_state != nxt_tgl_state) break;
  }
 if (bi < 0) *last_same_down_bi = 0; else *last_same_down_bi = bi + 1;
 return(last_tgl_state);
}

/*
 * return T if all bits of signal 0->1 or 1->0 toggled
 * only toggled is 1 - all rest are untoggled since need 'C' and '?' in report
 */
static int32 all_sig_bits_tgl(struct tgl_vardef_t *tvdp, int32 for_01_tgl)
{
 int32 bi;
 int32 *tgltab;

 if (for_01_tgl) tgltab = tvdp->tglcnt_01; else tgltab = tvdp->tglcnt_10;
 for (bi = 0; bi < tvdp->nbits; bi++)
  {
   if (tgltab[bi] != 1) return(FALSE);
  }
 return(TRUE);
}

/*
 * return T if all sig bits included (no exclude -1 (? from .tgldat file
 * know both will be same so just use 0->1
 */
static int32 all_sig_bits_included(struct tgl_vardef_t *tvdp)
{
 int32 bi;

 for (bi = 0; bi < tvdp->nbits; bi++)
  {
    if (tvdp->tglcnt_01[bi] == -1) return(FALSE);
  }
 return(TRUE);
}

/*
 * return T if there are no driven const bits
 * know both will be same so just use 0->1
 */
static int32 no_sig_bits_drvn_const(struct tgl_vardef_t *tvdp)
{
 int32 bi;

 for (bi = 0; bi < tvdp->nbits; bi++)
  {
    if (tvdp->tglcnt_01[bi] == -2) return(FALSE);
  }
 return(TRUE);
}

/*
 * count total number of insts, signals and bits in entire .tgldat net list
 * d.s for one file
 */
static void dsgn_tot_insts_sigs_bits(int32 *tot_insts, int32 *tot_sigs,
 int32 *tot_bits, int32 *tot_tgls, int32 *tot_01_tgls, int32 *tot_10_tgls,
 int32 *tot_excl_bits, int32 *tot_drvn_con_bits, int32 *tot_drvn_con_sigs)
{
 int32 mi, ii;
 struct td_mod_t *tdmdp;
 struct td_inst_t *tdip;

 *tot_insts = 0;
 *tot_sigs = 0;
 *tot_bits = 0;
 *tot_tgls = *tot_01_tgls = *tot_10_tgls = 0;
 *tot_excl_bits = *tot_drvn_con_bits = *tot_drvn_con_sigs = 0;
 for (mi = 0; mi < __file_netlist->num_td_mods; mi++)
  {
   tdmdp = __file_netlist->nlmods[mi];
   *tot_insts += tdmdp->num_td_instsof;  
   for (ii = 0; ii < tdmdp->num_td_instsof; ii++)
    {
     tdip = tdmdp->td_instsof[ii];
     add_tot_1inst_sigs_bits(tdip, tot_sigs, tot_bits, tot_tgls, tot_01_tgls,
      tot_10_tgls, tot_excl_bits, tot_drvn_con_bits, tot_drvn_con_sigs);
    }
  }
}

/*
 * count total inst, signals and bits in one module
 * also count per bit toggles (both, 0->1 and 1-0)
 */
static void mod_tot_sigs_bits(struct td_mod_t *tdmdp, int32 *tot_insts,
 int32 *tot_sigs, int32 *tot_bits, int32 *tot_tgls, int32 *tot_01_tgls,
 int32 *tot_10_tgls, int32 *tot_excl_bits, int32 *tot_drvn_con_bits,
 int32 *tot_drvn_con_sigs)
{
 int32 ii;
 struct td_inst_t *tdip;

 *tot_insts = tdmdp->num_td_instsof;
 *tot_sigs = 0;
 *tot_bits = 0;
 *tot_tgls = *tot_01_tgls = *tot_10_tgls = 0;
 *tot_excl_bits = *tot_drvn_con_bits = *tot_drvn_con_sigs = 0;
 for (ii = 0; ii < tdmdp->num_td_instsof; ii++)
  {
   tdip = tdmdp->td_instsof[ii];
   add_tot_1inst_sigs_bits(tdip, tot_sigs, tot_bits, tot_tgls, tot_01_tgls,
    tot_10_tgls, tot_excl_bits, tot_drvn_con_bits, tot_drvn_con_sigs);
  }
}


/*
 * count total number of nets and bits for all insts of one mod 
 *
 * if both 0->1 and 1->0 toggle, add count to tot tgls else 01 or 10
 * SJM 11-08-13 - also count excl bits (excluded nets will just not be in
 * the file), and driven to const bits and nets  
 */
static void add_tot_1inst_sigs_bits(struct td_inst_t *tdip, int32 *tot_sigs,
 int32 *tot_bits, int32 *tot_tgls, int32 *tot_01_tgls, int32 *tot_10_tgls,
 int32 *tot_excl_bits, int32 *tot_drvn_con_bits, int32 *tot_drvn_con_sigs)
{
 int32 ni, bi, all_drvn_con;
 struct tgl_vardef_t *tvdp;

 for (ni = 0; ni < tdip->td_num_nets; ni++)
  {
   tvdp = tdip->netvardefs[ni];

   *tot_bits = *tot_bits + tvdp->nbits;
   (*tot_sigs)++;
   all_drvn_con = TRUE;
   for (bi = tvdp->nbits - 1; bi >= 0; bi--)
    {
     if (tvdp->tglcnt_01[bi] == -2)
      {
       /* internal -2 is drvn const */
       (*tot_drvn_con_bits)++; 
       continue;
      }
     all_drvn_con = FALSE;
     /* internal -1 is bit excluded */
     if (tvdp->tglcnt_01[bi] == -1) (*tot_excl_bits)++;
     else if (tvdp->tglcnt_01[bi] == 1 && tvdp->tglcnt_10[bi] == 1)
      (*tot_tgls)++; 
     else if (tvdp->tglcnt_01[bi] == 1 && tvdp->tglcnt_10[bi] == 0) 
      (*tot_01_tgls)++;
     else if (tvdp->tglcnt_01[bi] == 0 && tvdp->tglcnt_10[bi] == 1) 
      (*tot_10_tgls)++;
    }
   if (all_drvn_con) tot_drvn_con_sigs++;
  }
}
