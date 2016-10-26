/* This is free and unencumbered software released into the public domain. */

/*
 * Program to merge one or more .tgldat files.  .tgldat files are based on 
 * regular Verilog VCD files and are produced by CVC Verilog simulator.
 *  
 *   Time #0 -> #1 contains toggle vectors from 0->1 
 *   Time #1 -> #2 contains toggle vectors from 1->0 
 *  
 *   USAGE: [file list] -o [OUTPUTFILE] -v
 */

#define VERS "3.01"
#define OFDT "10/04/2013"

#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include <stdarg.h>

#include "tgldat.h"

/* variables local to this program */
/* counters of diffs (merges) */
int32 __num_vd_diffs;  /* number of nets same in both but tgl state differs */
int32 __num_mods_in_2nd_not_1st;
int32 __num_mods_in_2nd_and_1st;
int32 __num_insts_in_2nd_not_1st;
int32 __num_insts_in_2nd_and_1st;
int32 __num_nets_in_2nd_not_1st;
int32 __num_nets_in_2nd_and_1st;

/* externs vars usable in any file */
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
 
/* local prototypes */
static void display_help_message(void);
static void merge_diff_files(char **, int32, int32, char *);
static void insert_new_mod(struct td_netlist_t *, struct td_mod_t *);
static void insert_new_inst(struct td_mod_t *, struct td_inst_t *);
static int32 diff_vardefs(char *, struct tgl_vardef_t *,
 struct tgl_vardef_t *);
static int32 unnormalize_ndx(struct tgl_vardef_t *, int32);
static void diff_ipth_modnam_mismatch(struct td_netlist_t *,
 struct td_netlist_t *);

/* global procs defined in other files */
extern void __init_tgldat_api_glbs(void);
extern struct td_netlist_t *__alloc_init_tgldat_netlist(void);
extern struct tgl_vardef_t *__rd_tgldat_to_vardefs(FILE *, char *);
extern void __bld_vardef_netlist(struct td_netlist_t *, struct tgl_vardef_t *,
 char *);
extern void __diff_netlists(struct td_netlist_t *, struct td_netlist_t *);
extern struct tgl_vardef_t *__bld_sort_td_vardefs(struct td_netlist_t *);
extern void __free_netlist(struct td_netlist_t *);
extern void __wr_one_tgldat_line_from_tglvardef(FILE *, struct tgl_vardef_t *);
extern char *__to_val(char *, int32);
extern void __merge_netlists(struct td_netlist_t *, struct td_netlist_t *);
extern void __diff_netlists(struct td_netlist_t *, struct td_netlist_t *);
extern struct td_mod_t *__insert_mod_in_netlist(struct td_netlist_t *,
 char *);
extern int32 __fnd_td_mod(struct td_netlist_t *, char *);
extern int32 __fnd_td_instof(struct td_mod_t *, char *);
extern struct td_inst_t *__insert_inst_in_mod(struct td_mod_t *, char *);
extern struct tgl_vardef_t *__insert_vardef_in_inst(struct td_inst_t *,
 struct tgl_vardef_t *);
extern int32 __fnd_td_inst_vardefs(struct td_inst_t *, char *);
extern int32 __merge_tgldat_toggle_state(struct tgl_vardef_t *,
 struct tgl_vardef_t *);

extern char *__my_stralloc(char *);
extern char *__my_malloc(size_t);
extern char *__my_realloc(void *, size_t, size_t);
extern void __my_free(void *, size_t);
extern ssize_t __my_getline(char **, size_t *, FILE *);
extern void __warn(int32 id_num, char *s, ...);
extern void __pv_fwarn(int32, char *, ...);
extern void __terr(int32, char *s, ...);
extern void __pv_terr(int32, char *s, ...);
extern void Msg(char *s, ...);

/*
 * get program options and do the merging
 */
int main(int argc, char **argv)
{
 int nfiles, i, file_names_size, diff_files_instead;
 char *argcp, outfnam[RECLEN];
 char **files_to_merge;

 /* initialize the tgldat misc proc api */
 __init_tgldat_api_glbs();
 strcpy(__log_fnam, "tgldat_merge.log");
 if ((__log_s = fopen(__log_fnam, "w")) == NULL) 
  {
   __terr(1, "unable to open output log file %s - unable to continue.\n",
    __log_fnam);
  }
 Msg("  tgldat_merge (also -diff) version %s of %s.\n", VERS, OFDT);
 __init_tgldat_api_glbs();
 
 /* number of files - start at 10 but can grow */
 file_names_size = 10;
 files_to_merge = malloc(file_names_size*sizeof(char *));

 __verbose = FALSE;
 strcpy(outfnam, "");
 diff_files_instead = FALSE;
 nfiles = 0;
 /* read the arguments */
 for (i = 1; i < argc; i++)
  {
   argcp = argv[i];
   if (strcmp(argcp, "-h") == 0)
    {
     /* display exits after printing help message */
     display_help_message();
    }
   else if (strcmp(argcp, "-verbose") == 0) __verbose = TRUE;
   else if (strcmp(argcp, "-diff") == 0) diff_files_instead = TRUE;
   else if (strcmp(argcp, "-o") == 0)
    {
     if (i + 1 >= argc)  
      {
       __terr(2, "-o specify output file name not followed by name of file"); 
      }
     argcp = argv[++i];
     strcpy(outfnam, argcp);
    }
   else
    {
     /* may have to expand names of merge files */
     if (nfiles == file_names_size)
      {
       file_names_size *= 2;
       files_to_merge = realloc(files_to_merge, file_names_size*sizeof(char *));
      }
     files_to_merge[nfiles] = argcp;
     nfiles++;
    }
  }

 /* need to pass in at least two files to merge */
 if (nfiles < 2)
  {
   __terr(14,
    "need to pass at least 2 files for merging or difference finding");
  }
 merge_diff_files(files_to_merge, nfiles, diff_files_instead, outfnam);
 return(0);
}

/*
 * print program help message
 */
static void display_help_message(void)
{
 Msg("tgldat_merge - USAGE: <list of files> [optional -diff]\n");
 Msg("        Merge two or more .tgldat toggle coverage state files\n");
 Msg("        written using CVC's -write_toggle_data_file option.\n\n");
 Msg("        -o [file name] specifies the output file to write the merged\n");
 Msg("        .tgldat files to if no -o option add suffix 'merged.out' to\n");
 Msg("        name of first merge into file.\n\n");
 Msg("        If the -diff option is selected, find differences between files.\n");
 Msg("        each file in list is compared pairwise against the first file.\n\n");
 Msg("        Option: -verbose writes progress and messages even\n");
 Msg("        Option: -diff diffs all files aginst first file instead.\n");
 Msg("        if no differences.\n\n");
 Msg("    Writes a log of progress messages and -diff differences to\n");
 Msg("    tgldat_merge.log.\n");
 exit(0);
}

/*
 * ROUTINES TO MERGE TGLDAT NET LIST FILES
 */
   
/*
 * merge the list of files
 *
 * merge into first - need merge into semantics - can't do it pairwise
 */
static void merge_diff_files(char **files_to_merge, int32 nfiles,
 int32 diff_instead, char *outfnam)
{
 int32 fi;
 FILE *ofp, *ifp;
 struct tgl_vardef_t *tvd_hd, *tvdp;
 struct td_netlist_t *nlp1, *nlp2;

 if (!diff_instead) 
  {
   if (strcmp(outfnam, "") == 0)
    {
     strcpy(outfnam, files_to_merge[0]);
     strcat(outfnam, ".merged.out");
    }
   /* open the output file first, make sure it can be opened early */
   if ((ofp = fopen(outfnam, "w")) == NULL)
    {
     __terr(7, "error opening merge .tgldat files output file '%s' : %s",
      outfnam, strerror(errno));
    }
   Msg("  Merging input files into file: %s\n", outfnam);
  }
 else
  {
   ofp = NULL;
   Msg(
     "    -diff option selected - printing differences to terminal and log file\n");
  } 

 if ((ifp = fopen(files_to_merge[0], "r")) == NULL)
  {
   __terr(9,
    "can't open .tgldat first input file %s because %s - can't continue",
    files_to_merge[0], strerror(errno));
  }
 __lin_cnt = 0;
 strcpy(__cur_fnam, files_to_merge[0]);

 /* read the left merge into or diff master file into a tgldat net list d.s. */
 tvd_hd = __rd_tgldat_to_vardefs(ifp, files_to_merge[0]);
 fclose(ifp);

 /* build the tgldat net list d.s. for the first file */
 nlp1 = __alloc_init_tgldat_netlist(); 
 __bld_vardef_netlist(nlp1, tvd_hd, files_to_merge[0]);
 nlp1->nl_tvd_hd = tvd_hd;
 nlp1->netlist_fnam = __my_stralloc(files_to_merge[0]);

 /* then merge files 3-n into the output tgldat var def list */
 for (fi = 1; fi < nfiles; fi++)
  {
   if (!diff_instead)
    {
     Msg("  Merging file %s into %s\n", files_to_merge[fi], outfnam);
    }
   else
    {
     Msg("  Differencing file %s against reference file %s\n",
      files_to_merge[fi], files_to_merge[0]);
    }
   __num_vd_diffs = 0;
   __num_mods_in_2nd_not_1st = 0;
   __num_mods_in_2nd_and_1st = 0;
   __num_insts_in_2nd_not_1st = 0;
   __num_insts_in_2nd_and_1st = 0;
   __num_nets_in_2nd_not_1st = 0;
   __num_nets_in_2nd_and_1st = 0;
   if ((ifp = fopen(files_to_merge[fi], "r")) == NULL)
    {
     __warn(31, "can't open .tgldat file %s (pos. %d) because %s - skipping",
      files_to_merge[fi], fi, strerror(errno));
     continue; 
    }
   __lin_cnt = 0;
   strcpy(__cur_fnam, files_to_merge[fi]);

   /* read .tgldat file into list form */
   tvd_hd = __rd_tgldat_to_vardefs(ifp, files_to_merge[fi]);
   fclose(ifp);

   /* alloc and bld the tgldat net list d.s. */
   nlp2 = __alloc_init_tgldat_netlist();
  __bld_vardef_netlist(nlp2, tvd_hd, files_to_merge[fi]);
   nlp2->nl_tvd_hd = tvd_hd;
   nlp2->netlist_fnam = __my_stralloc(files_to_merge[fi]);

   if (!diff_instead) __merge_netlists(nlp1, nlp2);
   else __diff_netlists(nlp1, nlp2);

   if (__verbose)
    {
     Msg("  %d modules in both with %d modules in second but not first.\n",
      __num_mods_in_2nd_and_1st, __num_mods_in_2nd_not_1st);
     Msg("  %d instances in both with %d instances in second but not first.\n",
      __num_mods_in_2nd_and_1st, __num_mods_in_2nd_not_1st);
     Msg(
      "  %d nets in both (%d toggles differ) with %d nets in second but not first.\n",
      __num_nets_in_2nd_and_1st, __num_vd_diffs, __num_nets_in_2nd_not_1st);
    }
   __free_netlist(nlp2);
  }
 if (!diff_instead)
  {
   tvd_hd = __bld_sort_td_vardefs(nlp1);
   for (tvdp = tvd_hd; tvdp != NULL; tvdp = tvdp->tglvdnxt)
    {
     __wr_one_tgldat_line_from_tglvardef(ofp, tvdp);
    }
  }
}

/*
 * ROUTINES TO MERGE TGLDAT NET LIST FILES
 */

/*
 * merge into first file from second two files in net list d.s. form
 */
extern void __merge_netlists(struct td_netlist_t *nlp1,
 struct td_netlist_t *nlp2)
{
 int32 mi1, mi2, ii1, ii2, vdi1, vdi2; 
 struct td_mod_t *tdmdp1, *tdmdp2;
 struct td_inst_t *tdip1, *tdip2;
 struct tgl_vardef_t *tvdp2;

 /* for every module in 2nd */
 for (mi2 = 0; mi2 < nlp2->num_td_mods; mi2++) 
  {
   tdmdp2 = nlp2->nlmods[mi2];
   /* try to find in first */
   if ((mi1 = __fnd_td_mod(nlp1, tdmdp2->modnam)) == -1)
    {
     /* case 1: mod in 2nd but not 1st, insert it and done */
     __num_mods_in_2nd_not_1st++;
     insert_new_mod(nlp1, tdmdp2);
     continue;
    }
   /* mod in both - see if any instances in 2nd but not 1st */
   /* case 2: mod in both */
   __num_mods_in_2nd_and_1st++;
   tdmdp1 = nlp1->nlmods[mi1];
   for (ii2 = 0; ii2 < tdmdp2->num_td_instsof; ii2++) 
    {
     tdip2 = tdmdp2->td_instsof[ii2]; 
     /* try to find in first */
     /* firnd root path without ending net in 2nd */ 
     if ((ii1 = __fnd_td_instof(tdmdp1, tdip2->irtpthnam)) == -1) 
      {
      __num_insts_in_2nd_not_1st++;
       insert_new_inst(tdmdp1, tdip2);
       continue;
      }
     __num_insts_in_2nd_and_1st++;
     tdip1 = tdmdp1->td_instsof[ii1];
     /* found inst, try to insert new vardefs (nets) */
     for (vdi2 = 0; vdi2 < tdip2->td_num_nets; vdi2++)
      {
       tvdp2 = tdip2->netvardefs[vdi2];
       if ((vdi1 = __fnd_td_inst_vardefs(tdip1, tvdp2->netnam)) == -1)
        {
         __num_nets_in_2nd_not_1st++;
         __insert_vardef_in_inst(tdip1, tvdp2);
         continue;
        }
       /* vardef (net) already in 1st, merge toggle state */
       /* returns T if merge changed first */
       __num_nets_in_2nd_and_1st++;
       if (__merge_tgldat_toggle_state(tdip1->netvardefs[vdi1], tvdp2))
        {
         __num_vd_diffs++;
        }
      }
    }
  }
}
       

/*
 * insert a new mod into reference first arg module
 * after insert mod inserts the insts in it and the nets in the insts
 *
 * know search failed so ix insert glb set
 * makes new malloc copy
 */
static void insert_new_mod(struct td_netlist_t *nlp1, struct td_mod_t *tdmdp2)
{
 int32 mi1, ii1, ii2;
 struct td_mod_t *tdmdp1;
 struct td_inst_t *tdip2;
 
 /* search to set ix insert but fatal error if duplicated in 2nd */
 if ((mi1 = __fnd_td_mod(nlp1, tdmdp2->modnam)) != -1)
  {
   __terr(13, "to be inserted 2nd module has name %s", tdmdp2->modnam);
  }
 tdmdp1 = __insert_mod_in_netlist(nlp1, tdmdp2->modnam);
 for (ii2 =  0; ii2 < tdmdp2->num_td_instsof; ii2++)
  {
   tdip2 = tdmdp2->td_instsof[ii2];
   /* SJM 11-02-13 - need to use find to set ix insert so stays alphabetical */
   if ((ii1 = __fnd_td_instof(tdmdp1, tdip2->irtpthnam)) != -1)
    {
     __terr(14, "to be inserted 2nd from instance has repeated inst names %s", 
      tdip2->irtpthnam);
    }
   __num_insts_in_2nd_not_1st = 0;
   insert_new_inst(tdmdp1, tdip2);
  }
}

/*
 * insert a new instance into reference first arg module
 *
 * know search failed so ix insert glb set
 * makes new malloc copy
 * this uses first vardef (know at least one) of to be inserted inst to
 * get path info
 */
static void insert_new_inst(struct td_mod_t *tdmdp1, struct td_inst_t *tdip2)
{
 int32 vdi1, vdi2;
 struct td_inst_t *tdip1;
 struct tgl_vardef_t *tvdp2;
 
 /* insert new inst in mod */
 /* SJM 11-01-13 - need to pass inst rooted path, but here just comes */
 /* from being inserted in inst, when building need the string */
 tdip1 = __insert_inst_in_mod(tdmdp1, tdip2->irtpthnam);

 /* now fill new inst with nets (vardefs) */
 __num_nets_in_2nd_and_1st += tdip2->td_num_nets;
 for (vdi2 = 0; vdi2 < tdip2->td_num_nets; vdi2++)
  {
   tvdp2 = tdip2->netvardefs[vdi2];    

   /* successful finding of repeated in 2nd to be inserted inst fatal error */
   if ((vdi1 = __fnd_td_inst_vardefs(tdip1, tvdp2->netnam)) != -1)
    {
     __terr(14, "to be inserted 2nd instance has repeated net names %s", 
      tvdp2->netnam);
    }
   /* this makes malloced copy */
   __insert_vardef_in_inst(tdip1, tvdp2);
  }
}

/*
 * ROUTINES TO DIFF TGLDAT NET LIST FILES
 */

/*
 * diff 2 vardef file toggle state records stored as net list d.s.
 */
extern void __diff_netlists(struct td_netlist_t *nlp1,
 struct td_netlist_t *nlp2)
{
 int32 mi1, mi2, ii1, ii2, vdi1, vdi2;
 struct td_mod_t *tdmdp1, *tdmdp2;
 struct td_inst_t *tdip1, *tdip2;
 struct tgl_vardef_t *tvdp1, *tvdp2;

 if (__verbose)
  {
   Msg("\n ##### diffing .tgldat file %s and file %s.\n",
    nlp1->netlist_fnam, nlp2->netlist_fnam);
  }

 /* first find same inst path instances with different in module fields */
 diff_ipth_modnam_mismatch(nlp1, nlp2);

 /* check number of mods in each */
 if (nlp1->num_td_mods != nlp2->num_td_mods)
  {
   Msg(
    "  ++ first file %s contains %d modules but second file %s contains %d.\n",
    nlp1->netlist_fnam, nlp1->num_td_mods, nlp2->netlist_fnam,
    nlp2->num_td_mods);
  }

 /* then diff first mods against 2nd  - do not count here count 2nd vs. first */
 for (mi1 = 0; mi1 < nlp1->num_td_mods; mi1++) 
  {
   tdmdp1 = nlp1->nlmods[mi1];
   /* same inst rooted path, diffrent mod already has msg emitted */
   /* this assume different modules */
   if ((mi2 = __fnd_td_mod(nlp2, tdmdp1->modnam)) == -1)
    {
     /* case 1: mod in first not in 2nd */
     Msg("  < module %s in first file but not in second.\n", tdmdp1->modnam);
     continue;
    }
   /* case 2: mod in both */
   tdmdp2 = nlp2->nlmods[mi2];
   if (tdmdp1->num_td_instsof != tdmdp2->num_td_instsof)
    {
     Msg(
      "  ++ first file module %s contains %d instances but second contains %d.\n",
      tdmdp1->modnam, tdmdp1->num_td_instsof, tdmdp2->num_td_instsof);
    } 
   for (ii1 = 0; ii1 < tdmdp1->num_td_instsof; ii1++)
    {
     tdip1 = tdmdp1->td_instsof[ii1]; 
     /* firnd root path without ending net in 2nd */ 
     if ((ii2 = __fnd_td_instof(tdmdp2, tdip1->irtpthnam)) == -1) 
      {
       /* case 2a: inst in first not in 2nd */
       Msg("  < module %s instance path %s in first file but not in second.\n",
        tdmdp1->modnam, tdip1->irtpthnam);
       continue;
      }
     /* case 2b: inst in both */
     tdip2 = tdmdp2->td_instsof[ii2]; 
     if (tdip1->td_num_nets != tdip2->td_num_nets)
      {
       Msg(
        "  ++ first file instance %s (type %s) contains %d nets but second contains %d.\n",
       tdip1->irtpthnam, tdmdp1->modnam, tdip1->td_num_nets,
       tdip2->td_num_nets);   
      }
     /* now diff every var def in this instance tree instance */
     for (vdi1 = 0; vdi1 < tdip1->td_num_nets; vdi1++)
      {
       tvdp1 = tdip1->netvardefs[vdi1]; 
       if ((vdi2 = __fnd_td_inst_vardefs(tdip2, tvdp1->netnam)) == -1)
        {
         /* case 2b-1: net in first but not second */
         Msg(
          "  < module %s instance path %s net %s in first file but not in second.\n",
          tdmdp1->modnam, tdip1->irtpthnam, tvdp1->netnam);
         continue; 
        }
       tvdp2 = tdip2->netvardefs[vdi2];
       /* case 2b-2: same mod/inst/net in both - diff contents */
       if (diff_vardefs(tdmdp1->modnam, tvdp1, tvdp2))
        { 
         /* can count because 1st vs. 2nd and 2nd vs. 1st same if in both */
         __num_vd_diffs++;
        }
      } 
    }
  }

 /* also compare the other way - only emit messages for in 2nd not in 1st */
 /* file, then diff contents against each other if both in down to vardefs */
 for (mi2 = 0; mi2 < nlp2->num_td_mods; mi2++) 
  {
   tdmdp2 = nlp2->nlmods[mi2];
   /* same inst rooted path, diffrent mod already has msg emitted */
   /* this assume different modules */
   if ((mi1 = __fnd_td_mod(nlp1, tdmdp2->modnam)) == -1)
    {
     __num_mods_in_2nd_not_1st++;
     /* case 1: mod in 2nd but not in 1st */
     Msg("  > module %s in second file but not in first.\n", tdmdp2->modnam);
     continue;
    }
   /* case 2: mod in both - see if insts in 2nd but not in first */
   __num_mods_in_2nd_and_1st++;
   tdmdp1 = nlp1->nlmods[mi1];
   for (ii2 = 0; ii2 < tdmdp2->num_td_instsof; ii2++)
    {
     tdip2 = tdmdp2->td_instsof[ii2]; 
     if ((ii1 = __fnd_td_instof(tdmdp1, tdip2->irtpthnam)) == -1) 
      {
       /* case 2a: inst in 2nd but not in 1st */
       __num_insts_in_2nd_not_1st++;
       __num_nets_in_2nd_not_1st += tdip2->td_num_nets;
       Msg("  < module %s instance path %s in second file but not in first.\n",
        tdmdp2->modnam, tdip2->irtpthnam);
       continue;
      }
     /* case 2b: inst in both */
     __num_insts_in_2nd_and_1st++;
     tdip1 = tdmdp1->td_instsof[ii1]; 
     /* diff every var def in 2nd against first */
     for (vdi2 = 0; vdi2 < tdip2->td_num_nets; vdi2++)
      {
       tvdp2 = tdip2->netvardefs[vdi2]; 
       /* try to find this vardef in 1st */ 
       if (__fnd_td_inst_vardefs(tdip1, tvdp2->netnam) == -1)
        {
         __num_nets_in_2nd_not_1st++;
         /* case 2b-1: net in second but not first */
         Msg(
          "  < module %s instance path %s net %s in second file but not in first.\n",
          tdmdp2->modnam, tdip2->irtpthnam, tvdp2->netnam);
        }
      }
     /* diff every var def in 1st against second */
     for (vdi1 = 0; vdi1 < tdip1->td_num_nets; vdi1++)
      {
       tvdp1 = tdip1->netvardefs[vdi1]; 
       /* try to find this vardef in 2nd */ 
       if (__fnd_td_inst_vardefs(tdip2, tvdp1->netnam) == -1)
        {
         /* case 2b-1: net in first but not second */
         Msg(
          "  > module %s instance path %s net %s in first file but not in second.\n",
          tdmdp2->modnam, tdip2->irtpthnam, tvdp1->netnam);
        }
      }
    }
  }
}

/*
 * diff two vardefs know nets in same inst in first and second files
 * diffs the vardef contents
 *
 * return T if net tgldat states records have differences 
 *
 * SJM 10-22-13 - this was wrong in tglcnt 01/10 tab -1 is excluded
 * and -2 is driven const - in .tgldat file values are '?' and 'C'
 */
static int32 diff_vardefs(char *mnam, struct tgl_vardef_t *tvdp1,
 struct tgl_vardef_t *tvdp2)
{
 int32 bi, has_diffs;
 char s1[RECLEN], s2[RECLEN], vstr01[RECLEN], vstr10[RECLEN];

 has_diffs = FALSE;
 if (tvdp1->nbits != tvdp2->nbits)
  {
   Msg(
    "  ++ module %s path %s net %s widths differ first %d but second %d.\n",
     mnam, tvdp1->rtpthnam, tvdp1->netnam, tvdp1->nbits, tvdp2->nbits);
   has_diffs = TRUE;
  }
 /* only check if both non scalar */ 
 if (tvdp1->rng1 != -1 || tvdp2->rng1 != -1)
  {
   if (tvdp1->rng1 == -1) strcpy(s1, "Scalar");
   else sprintf(s1, "[%d:%d]", tvdp1->rng1, tvdp1->rng2);
   if (tvdp2->rng1 == -1) strcpy(s2, "Scalar");
   else sprintf(s2, "[%d:%d]", tvdp2->rng1, tvdp2->rng2);
   if (tvdp1->rng1 != tvdp2->rng1 || tvdp1->rng2 != tvdp2->rng2)
    {
     Msg(
      "  ++ module %s path %s net %s ranges differ first %s but second %s.\n",
     mnam, tvdp1->rtpthnam, s1, s2);
     has_diffs = TRUE;
    } 
  }

 /* compare bit toggle state values */
 /* if first short, just stop when all of old which is result merged in */
 /* extra at end of 2nd just ignored */ 
 /* SJM 11-02-13 - here can work from low bit to high because of short */
 /* problem - in file list the high bit comes first (right most) in list */
 /* but by here index 0 corresponds to bit 0 */
 for (bi = 0; bi < tvdp1->nbits; bi++)
  {
   /* make the bit references strings even if no diff messages */
   if (tvdp1->rng1 == -1) strcpy(s1, tvdp1->netnam); 
   else sprintf(s1, "%s[%d]", tvdp1->netnam, unnormalize_ndx(tvdp1, bi));
   if (tvdp2->rng1 == -1) strcpy(s2, tvdp2->netnam); 
   else sprintf(s2, "%s[%d]", tvdp2->netnam, unnormalize_ndx(tvdp2, bi));

   /* new short - emit message */
   if (bi >= tvdp2->nbits)
    {
     /* think if first scalar, 2nd can't be too short */
     Msg(
      "  < module %s path %s net bit %s in first file but not in too short second (%s).\n",
      mnam, tvdp1->rtpthnam, s1);
     has_diffs = TRUE;
     continue;
    }

   /* case 1:, both same - nothing to do */
   if ((tvdp1->tglcnt_01[bi] == tvdp2->tglcnt_01[bi])
    && (tvdp1->tglcnt_10[bi] == tvdp2->tglcnt_10[bi])) continue;

   /* case 2: 1st excluded, but not second */
   if (tvdp1->tglcnt_01[bi] == -1)
    {
     Msg(
      "  ++ module %s path %s net bit %s excluded but second 0->1 = %s and 1->0 = %s.\n",
      mnam, tvdp1->rtpthnam, s1, __to_val(vstr01, tvdp2->tglcnt_01[bi]),
      __to_val(vstr10, tvdp2->tglcnt_10[bi]));
    has_diffs = TRUE;
    continue;
    }

   /* case 3: 2nd excluded but first */
   if (tvdp2->tglcnt_01[bi] == -1) 
    {
     Msg(
      "  ++ module %s path %s net bit %s second excluded but first 0->1 = %s and 1->0 = %s.\n",
      mnam, tvdp1->rtpthnam, s2, __to_val(vstr01, tvdp1->tglcnt_01[bi]),
      __to_val(vstr10,  tvdp1->tglcnt_10[bi]));
    has_diffs = TRUE;
    continue;
    }

   /* case 4: 1st driven const (C) but not second */
   /* SJM 10-22-13 - in tglcnt 01/10 driven const is -2 but in .tgldat file */
   /* it is 'C' */
   if (tvdp1->tglcnt_01[bi] == -2)
    {
     Msg(
      "  ++ module %s path %s net bit %s first driven to constant but second 0->1 = %s and 1->0 = %s.\n",
      mnam, tvdp1->rtpthnam, s1, __to_val(vstr01, tvdp2->tglcnt_01[bi]),
      __to_val(vstr10, tvdp2->tglcnt_10[bi]));
     has_diffs = TRUE;
     continue;
    }

   /* case 5: 2nd driven const -2 (C) but not first */
   if (tvdp2->tglcnt_01[bi] == -2)
    {
     Msg(
      "  ++ module %s path %s net bit %s second driven to constant but first 0->1 = %s and 1->0 = %s.\n",
      mnam, tvdp1->rtpthnam, s2, __to_val(vstr01, tvdp1->tglcnt_01[bi]),
      __to_val(vstr10,  tvdp1->tglcnt_10[bi]));
     has_diffs = TRUE;
     continue;
    }
   /* know not exclued and not driven const so values number 0 or 1 only */
   if (tvdp1->tglcnt_01[bi] != tvdp2->tglcnt_01[bi])
    {
     Msg(
      "  ++ module %s path %s differ: first net bit %s 0->1 = %d but second %s 0->1 = %d.\n",
      mnam, tvdp1->rtpthnam, s1, tvdp1->tglcnt_01[bi], s2,
      tvdp2->tglcnt_01[bi]);
     has_diffs = TRUE;
    }
   if (tvdp1->tglcnt_10[bi] != tvdp2->tglcnt_10[bi])
    {
     Msg(
      "  ++ module %s path %s differ: first net bit %s 1->0 = %d but second %s 1->0 = %d.\n",
      mnam, tvdp1->rtpthnam, s1, tvdp1->tglcnt_10[bi], s2,
      tvdp2->tglcnt_10[bi]);
     has_diffs = TRUE;
    }
  }
 /* if 2nd wider need messages */
 if (bi <= tvdp2->nbits)
  {
   for (bi = tvdp1->nbits; bi < tvdp2->nbits; bi++)
    {
     if (tvdp2->rng1 == -1) strcpy(s2, tvdp2->netnam); 
     else sprintf(s2, "%s[%d]", tvdp2->netnam, unnormalize_ndx(tvdp2, bi));

     /* if 2nd scalar, 1st can't be too short */
     Msg(
      "  > module %s path %s net bit %s in second file but too short first.\n",
      mnam, tvdp1->rtpthnam, s1);
     has_diffs = TRUE;
    }
  }
 return(has_diffs);
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
 * given 2 net lists - find all different mods but same insts both directions
 * always emit a message 
 *
 * writes compare messages to stdout (and log file)
 * this is n squared log n operation in number of insts (not nets) - maybe
 * not needed
 *
 * only need to run once since same paths if ran other way are same
 *
 * no within one net list from tgldat var file checking because uses
 * all the fields to build - within an inst all irtpths must be same
 * and all nbits built from element range
 */
static void diff_ipth_modnam_mismatch(struct td_netlist_t *nlp1,
 struct td_netlist_t *nlp2)
{
 int32 mi1, mi2, ii1, ii2, match_ii;
 struct td_mod_t *tdmdp1, *tdmdp2;
 struct td_inst_t *tdip1, *tdip2;

 /* for every mod in 1st td net list look for same inst path in 2nd */
 for (mi1 = 0; mi1 < nlp1->num_td_mods; mi1++)
  {
   tdmdp1 = nlp1->nlmods[mi1];
   /* for every inst in */
   for (ii1 = 0; ii1 < tdmdp1->num_td_instsof; ii1++)
    {
     tdip1 = tdmdp1->td_instsof[ii1];

     /* for every mod in 2nd */
     for (mi2 = 0; mi2 < nlp2->num_td_mods; mi2++)
      {
       tdmdp2 = nlp2->nlmods[mi2]; 
       /* for every inst in second */
       for (ii2 = 0; ii2 < tdmdp2->num_td_instsof; ii2++)
        {
         tdip2 = tdmdp2->td_instsof[ii2];
         if ((match_ii = __fnd_td_instof(tdmdp1, tdip2->irtpthnam)) != -1) 
          {
           /* know all in modnam same within each net list file d.s, but */
           /* modules can be different but paths same */
           /* no fix since merge uses first as master and error messages */ 
           /* all will have same mod */
           if (strcmp(tdmdp1->modnam, tdip2->netvardefs[0]->in_modnam) != 0)
            {
             Msg(
              "  < same instance path %s: in module %s but mod name %s in second (%d nets) - merge will fix",
              tdip2->irtpthnam, tdmdp1->modnam, tdip2->netvardefs[0]->in_modnam,
              tdip2->td_num_nets);
            }
          }
        }
      }
    }
  }
}


