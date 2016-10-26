/* This is free and unencumbered software released into the public domain. */

/*
 * Program to chk a .tgldat file used to initialize toggle states from 
 * previous CVC -toggle (or -optconfig toggle statement runs
 *
 * Idea is that multiple .tgldat files can be read by cvc so users
 * may want to use scripts for building the ascii .tgldat files.  This
 * program makes sure the format is good.
 *  
 *   USAGE: chk_tgldat.c [.tgldat file]
 */

#define VERS "2.02"
#define OFDT "10/11/2013"

#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include <stdarg.h>

#include "tgldat.h"

/* externs declared here */
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

static void chk_tgldat_fmt(char *);
static int32 cnt_tgldat_nets_in_fil(struct td_netlist_t *, int32 *);
static void bld_prt_tgldat_rt_mods(struct td_netlist_t *);
static int32 fnd_topmod(char **, int32, char *);

extern void __init_tgldat_api_glbs(void);
extern int32 __rd_one_net_tgldat_rec(FILE *, int32 *);
extern struct tgl_vardef_t *__fill_tglvar_rec(int32);
extern int32 __glbnam_to_strtab(char *);
extern void __bld_vardef_netlist(struct td_netlist_t *, struct tgl_vardef_t *,
 char *);
extern struct tgl_vardef_t *__bld_sort_td_vardefs(struct td_netlist_t *);
extern void __free_list_of_tgl_vardef(struct tgl_vardef_t *);

/* OS interface prototypes from tgldat ms file */
extern char *__my_stralloc(char *);
extern char *__my_malloc(size_t);
extern char *__my_realloc(void *, size_t, size_t);
extern void __my_free(void *, size_t);
extern ssize_t __my_getline(char **, size_t *, FILE *);
extern void __pv_fwarn(int32, char *, ...);
extern void __terr(int32, char *s, ...);
extern void __pv_terr(int32, char *s, ...);
extern void Msg(char *s, ...);
extern void __my_fprintf(FILE *f, char *s, ...);
extern void __my_vfprintf(FILE *, char *, va_list, va_list);
extern int32 __my_putc(int32, FILE *);

/*
 * get program options and do the merging
 */
int main(int argc, char **argv)
{
 Msg("  Program to check .tgldat file format %s of %s.\n", VERS, OFDT);

 __init_tgldat_api_glbs();
 strcpy(__log_fnam, "chk_tgldat.log");
 if ((__log_s = fopen(__log_fnam, "w")) == NULL) 
  {
   __terr(1, "unable to open output log file %s - unable to continue.\n",
    __log_fnam);
  }
 if (argc < 1)  
  {
   __terr(2,
    "wrong number of args %d: exactly 1 input .tgldat file required", argc);
  } 
 strcpy(__in_tgldat_fnam, argv[1]);

 chk_tgldat_fmt(__in_tgldat_fnam);
 
 return(0);
}

/*
 * merge files f1cp and f2cp into file ocp 
 */
static void chk_tgldat_fmt(char *tgldat_fnam)
{
 int32 rv, num_bad_lines, beg_lcnt;
 FILE *fp;
 struct tgl_vardef_t *tvdp, *tvdp_hd, *tvdp_tail;
 
 if ((fp = fopen(tgldat_fnam, "r")) == NULL)
  {
   __terr(3, "can't open .tgldat input file %s because %s",
    tgldat_fnam, strerror(errno));
  }
 __lin_cnt = 0;
 strcpy(__cur_fnam, tgldat_fnam);

 tvdp_hd = tvdp_tail = NULL;
 for (num_bad_lines = 0;;)
  {
   if ((rv = __rd_one_net_tgldat_rec(fp, &(beg_lcnt))) == -1) break;
   if (rv == 0) { num_bad_lines++; continue; }
   /* check the fully qualified rooted path to net part of tgldat line */ 
   /* needed because filling will fail if path bad */
   if (!__glbnam_to_strtab(__tgl_rtpthnam))
    {
     __pv_fwarn(20, "tgldat rooted path %s parsing failed", __tgl_rtpthnam);
     num_bad_lines++;
    __last_tdpthi = -1;
     continue;
    }  
   tvdp = __fill_tglvar_rec(beg_lcnt); 

   /* link on to list */
   if (tvdp_hd == NULL) tvdp_hd = tvdp; else tvdp_tail->tglvdnxt = tvdp;
   tvdp_tail = tvdp;
  }
 if (tvdp_hd == NULL)
  {
   __terr(4, "  File %s not a .tgldat file or empty - can't continue.\n",
    tgldat_fnam);
  }
 if (num_bad_lines > 0)
  {
   Msg("  File %s has %d bad .tgldat format lines - can't build net list.\n",
    tgldat_fnam, num_bad_lines);
   exit(0);
  }

 Msg("  File %s has good .tgldat format.\n", tgldat_fnam);
 Msg("  Read toggle state from .tgldat file:\n");
 Msg("    %s\n", __tgldat_writer_vers);
 Msg("    %s\n", __tgldat_writer_date); 

 Msg("  Building tgldat netlist ...\n"); 
 
 /* want to see duplicates which are automatically combined */
 __emit_dup_rtpth_warn = TRUE;

 /* this will always build something - maybe with warns */
 __bld_vardef_netlist(__file_netlist, tvdp_hd, tgldat_fnam);
 /* free the original read in tvd linked list and rebuild */
 __free_list_of_tgl_vardef(tvdp_hd);

 /* build tgl vardef list after building net list form since may have chged */ 
 tvdp_hd = __bld_sort_td_vardefs(__file_netlist);
 __file_netlist->nl_tvd_hd = tvdp_hd;

 bld_prt_tgldat_rt_mods(__file_netlist);
}

/*
 * code to locally bld and print names of rooted modules
 *
 * example code for traversing new tgldat * net list data structure
 */
static void bld_prt_tgldat_rt_mods(struct td_netlist_t *nlp)
{
 int32 num_tdvars_in_file, ntopm, num_elements_in_file;
 int32 topmi, mi, ii, num_tot_instsof;
 struct td_mod_t *tdmdp;
 struct td_inst_t *tdip;
 struct tgl_vardef_t *tvdp;
 char **rtmodnams, s1[RECLEN];

 /* just make top mod tab biggest possible - i.e. different for every net */
 num_tdvars_in_file = cnt_tgldat_nets_in_fil(nlp, &(num_tot_instsof));
 rtmodnams = (char **) __my_malloc(num_tdvars_in_file*sizeof(char *)); 

 /* mods that have toggle net data in them - not excluded and has nets */
 ntopm = 0;
 for (mi = 0; mi < nlp->num_td_mods; mi++)
  {
   tdmdp = nlp->nlmods[mi];
   for (ii = 0; ii < tdmdp->num_td_instsof; ii++)
    {
     tdip = tdmdp->td_instsof[ii];

     /* instance may have many net tgldat state information, but only care */
     /* about head of path to the inst which is the top level module */
     __glbnam_to_strtab(tdip->irtpthnam);
     strcpy(s1, __tgldat_pthcmps[0]);
     __last_tdpthi = -1;

     if (fnd_topmod(rtmodnams, ntopm, s1) == -1)
      {
       /* need to insert - notice assuming rt mod nams one bigger */
       for (topmi = ntopm; topmi > __ix_insert; topmi--)
        {
         rtmodnams[topmi] = rtmodnams[topmi - 1]; 
        }
       ntopm++;
       rtmodnams[__ix_insert] = __my_stralloc(s1);
      }
    }
  }

 /* for checking next count number of elements in original .tgldat file */
 num_elements_in_file = 0;  
 for (tvdp = nlp->nl_tvd_hd; tvdp != NULL; tvdp = tvdp->tglvdnxt)
  { 
   num_elements_in_file++;
  }
 if (num_tdvars_in_file != num_elements_in_file)
  {
   Msg(
    "  ++ number of elements in file %d not same as elments in net list %d.\n",
    num_elements_in_file, num_tdvars_in_file);
  }
 else
  {
   Msg("  %d total mods %d total insts of mods %d .tgldat state nets in file.\n",
    nlp->num_td_mods, num_tot_instsof, num_tdvars_in_file);
  }


 Msg("  %d top level modules in %s:\n", ntopm, nlp->netlist_fnam);
 for (mi = 0; mi < ntopm; mi++)
  {
   Msg(" TOP MOD: %s\n", rtmodnams[mi]);
  }
}

/*
 * count number of tgldat nets in file
 *
 * could just traverse input tgl vardef list without building td net list
 * data structure - this shows how to process built net list
 */
static int32 cnt_tgldat_nets_in_fil(struct td_netlist_t *nlp,
  int32 *num_tot_instsof)
{
 int32 mi, ii, num_tgldat_nets;
 struct td_mod_t *tdmdp;
 struct td_inst_t *tdip;

 /* mods that have toggle net data in them - not excluded and has nets */
 num_tgldat_nets = 0;
 *num_tot_instsof = 0;
 for (mi = 0; mi < nlp->num_td_mods; mi++)
  {
   tdmdp = nlp->nlmods[mi];
   *num_tot_instsof += tdmdp->num_td_instsof; 
   for (ii = 0; ii < tdmdp->num_td_instsof; ii++)
    {
     tdip = tdmdp->td_instsof[ii];
     num_tgldat_nets += tdip->td_num_nets; 
    }
  }
 return(num_tgldat_nets);
}

/*
 * find a module name in top mod tab
 *
 * slight variation of tgldat ms __fnd_td_mod proc 
 * if not found sets ix insert to place to insert and copy down
 */
static int32 fnd_topmod(char **rtmodnams, int32 num_top_mods, char *topmnam)
{
 int32 cv, l, h, m;
 char *chp;

 if (num_top_mods <= 0) { __ix_insert = 0; return(-1); }
 l = 0; h = num_top_mods - 1;
 for (;;)
  {
   m = (l + h)/2;
   chp = rtmodnams[m];
   if ((cv = strcmp(chp, topmnam)) == 0) return(m);
   if (cv < 0) l = m + 1; else h = m - 1;
   if (h < l) { __ix_insert = l; break; }
  }
 return(-1);
}
      
