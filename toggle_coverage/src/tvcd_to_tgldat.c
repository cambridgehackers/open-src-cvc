/* This is free and unencumbered software released into the public domain. */

/*
 * Program to convert a .tvcd file with format simplified dumpvars like
 * to simple signal 0->1 and 1->0 toggle count ascii .dat file with
 * full signal name and 2 lists
 *  
 * for .tvcd input file:
 *   Time #0 -> #1 contains toggle vectors from 0->1 
 *   Time #1 -> #2 contains toggle vectors from 1->0 
 *
 * for .tgldat output file:
 *  [module name] : [hierachical net] [] or [r1:r2] {[list 0->1] {list 1->0]};
 *  for wide nets, {[list 0->1]} on next line and {[line 1->0]}; another line
 *  
 *   USAGE: tvcd_to_tgl_dat [.tvcd file name] -o [output .tgldat file][-h]
 *   if no -o option, output goes to stdout
 *
 * notice that this fie links with tgldat_srvc.c service routines but
 * does not use the mechanism and net list d.s.
 */

#define VERS "3.01"
#define OFDT "09/13/2013"

#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include <stdarg.h>

#include "tgldat.h"

/* variables local to this program */

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

static void display_help_message(void);
static void init_glbs(void);
static void cnvt_to_tgl_dat_fmt(char *, char *);
static void rd_bld_tvcd_vardefs_ndx(FILE *, char *);
static int32 push_scope(char *, char *);
static void pop_scope(void);
static void rd_add_var_to_tab(FILE *);
static struct tgl_vardef_t *alloc_init_tgl_vardef(void);
static void init_tgl_vardef(struct tgl_vardef_t *);
static int32 get_sig_wid(int32, int32); 
static char *bld_alloc_tvcd_rt_pth(char *);
static void rd_set_counts_from_tvcd_body(FILE *);
static void upd_net_tgl(char *, char *, int32);
static void fill_tglcnt_from_str(int32 *, char *, int32);
static struct tgl_vardef_t *get_sig_by_dvcod(struct tgl_vardef_t **, int32,
 char *);
static int32 sig_dvcod_cmp(const void *, const void *);
static int32 sig_rtpth_cmp(const void *, const void *);
static void wr_tgl_dat_out_file(FILE *, char *);
static void dbg_dmp_tglvardefs(struct tgl_vardef_t **, int32);
static int32 get_vcd_tok(FILE *);
static void collect_keyword_section(FILE *, char *, char *);
static void rd_to_vcd_end(FILE *);
static int32 get_vcd_keywrd(char *);
static int32 get_var_type(char *);


extern char *__my_stralloc(char *);
extern char *__my_malloc(size_t);
extern char *__my_realloc(void *, size_t, size_t);
extern void __my_free(void *, size_t);
extern void __terr(int32, char *s, ...);
extern void __pv_terr(int32, char *s, ...);
extern void Msg(char *s, ...);

/*
 * get program options and do the merging
 */
int main(int argc, char **argv)
{
 int32 i;
 char *argcp;

 Msg("  .tvcd to toggle .tgldat file converter %s of %s.\n", VERS, OFDT);
 
 strcpy(__log_fnam, "to_tgl_dat.log");
 if ((__log_s = fopen(__log_fnam, "w")) == NULL) 
  {
   __terr(1, "unable to open output log file %s - unable to continue.\n",
    __log_fnam);
  }
 /* read the arguments */
 for (i = 1; i < argc; i++)
  {
   argcp = argv[i];
   /* if option, -h - only option - displays a help message */
   if (strcmp(argcp, "-h") == 0) { display_help_message(); continue; }
   break;
  }
 if (argc - i < 2)  
  {
   __terr(2,
    "wrong number of args %d: exactly 2:  input .tvcd file and output .tgldat file required.\n",
    argc - i);
  }
 strcpy(__in_tvcd_fnam, argv[i]);
 strcpy(__out_tgldat_fnam, argv[i + 1]);
 init_glbs();

 cnvt_to_tgl_dat_fmt(__in_tvcd_fnam, __out_tgldat_fnam);
 return(0);
}

/*
 * print program help message
 */
static void display_help_message(void)
{
 Msg("\ntvcd_to_tgldat - USAGE: [options] [input .tvcd] [output .tgldat]\n");
 Msg("                    only option: -h for this help message.\n");
 Msg(
  "\n      Converts an old style .tvcd dumpvars format like file to new simple\n");
 Msg(
  "      text .tgldat with module name on line file with rooted path followed.\n");
 Msg("\n      Writes a log of progress messages to to_tgl_dat.log file.\n");
 exit(0);
}

/*
 * initialize globals 
 */
static void init_glbs(void)
{
 size_t nbytes;
 int32 i;

 __top_scopei = -1;
 __siz_scope_stk = MAXSCOPES;
 __scopnam_stk = (char **) __my_malloc(sizeof(char *)*MAXSCOPES);
 for (i = 0; i < MAXSCOPES; i++) __scopnam_stk[i] = NULL;
 __scopmdnam_stk = (char **) __my_malloc(sizeof(char *)*MAXSCOPES);
 for (i = 0; i < MAXSCOPES; i++) __scopmdnam_stk[i] = NULL;

 __alloc_siz_tglvardefs = 300;
 nbytes =  __alloc_siz_tglvardefs*sizeof(struct tgl_vardef_t *);
 __tglvardefs = (struct tgl_vardef_t **) __my_malloc(nbytes);
 __last_tglvardef = -1;
 strcpy(__tgldat_writer_date, "<none>");
 strcpy(__tgldat_writer_vers, "<none>");
}

/*
 * merge files f1cp and f2cp into file ocp 
 */
static void cnvt_to_tgl_dat_fmt(char *tvcd_fnam, char *tgldat_fnam)
{
 FILE *ofp, *ifp;
 char s1[RECLEN], *chp;
 
 if ((ifp = fopen(tvcd_fnam, "r")) == NULL)
  {
   /* try to add .tvcd suffix if does not have one and try again */
   if ((chp = rindex(tvcd_fnam, '.')) != NULL)
    {
     chp++;
     if (strcmp(chp, ".tvcd") != 0)
      {
       chp--;
       strcpy(s1, tgldat_fnam); 
       strcat(s1, chp);
       if ((ifp = fopen(tvcd_fnam, "r")) != NULL) strcpy(tgldat_fnam, s1);
      }
    }
   if (ifp == NULL)
    {  
     __terr(38, "can't open .tvcd input file '%s' or '%s' because %s",
      tvcd_fnam, s1, strerror(errno));
    }
  }
 __lin_cnt = 1;
 strcpy(__cur_fnam, tvcd_fnam);
 if ((ofp = fopen(tgldat_fnam, "w")) == NULL)
  {
   __terr(9, "can't open toggle .tgldat output file '%s' because %s",
    tgldat_fnam, strerror(errno));
  }
 /* build the definitions section of vcd (.tvcd form) signal index */
 rd_bld_tvcd_vardefs_ndx(ifp, tvcd_fnam);

 if (__last_tglvardef < 0)
  { 
   __terr(34, "No tgl variables records defined in input .tvcd file %s",
    __in_tvcd_fnam);
  }

 /* DBG remove --
 dbg_dmp_tglvardefs(__tglvardefs, __last_tglvardef + 1);
 --- */ 

 /* sort it */
 qsort(__tglvardefs, __last_tglvardef + 1, sizeof(struct tgl_vardef_t *),
 sig_dvcod_cmp);

 /* set the counts vectors (for now just 0 or 1) */ 
 rd_set_counts_from_tvcd_body(ifp);
 fclose(ifp);
 wr_tgl_dat_out_file(ofp, tgldat_fnam);

 if (ofp != stdout) fclose(ofp);

 /* print verbose write new .tgldat output file msg */
 Msg("\nWRITTEN - %d toggle cover signal .tgldat records to file %s\n",
  __last_tglvardef + 1, tgldat_fnam);
}

/*
 * read/parse a toggle VCD file
 *
 * SJM 03-16-13 - LOOKATME - maybe should not just emit fatal error on bad file
 */
static void rd_bld_tvcd_vardefs_ndx(FILE *fp, char *fname)
{
 char *tokp;
 char instnam[RECLEN], modnam[RECLEN];

 /* handle by token type */
 while (get_vcd_tok(fp) != EOF)
  {
   tokp = __token;
   /* move past the leading dollar */
   tokp++;
   switch (get_vcd_keywrd(tokp)) {
    case VCD_UPSCOPE:
     rd_to_vcd_end(fp);
     pop_scope();
     break;
    case VCD_SCOPE:
     /* vcd fmt for .tvcd is: $scope module <inst nam> <mod nam> $end */
     get_vcd_tok(fp);
     if (strcmp(__token, "module") != 0)
      {
       __pv_terr(3, "only module $scope allowed - %s read", __token);
      }
     /* get net name */
     get_vcd_tok(fp);
     strcpy(instnam, __token);
     /* SJM 09-13-13 - need to save module name for new .tgldat format */
     get_vcd_tok(fp);
     strcpy(modnam, __token); 
     rd_to_vcd_end(fp);
     push_scope(instnam, modnam);
     break;
    case VCD_DATE: 
     collect_keyword_section(fp, __tvcd_date,  "$date");
     break;
    case VCD_VERSION:
     collect_keyword_section(fp, __tvcd_version, "$version");
     break;
    case VCD_COMMENT: 
     rd_to_vcd_end(fp);
     break;
    case VCD_TIMESCALE:
     /* just ignore time scale */
     rd_to_vcd_end(fp);
     break;
    case VCD_ENDDEF:
     rd_to_vcd_end(fp);
     return;
    case VCD_VAR:
     /* read a vcd vardefs variable and add record to table */
     /* this reads end $end */
     rd_add_var_to_tab(fp);
     break;
    default:
     __pv_terr(4, "Unknown token: %s", __token);
     break;
   }	
  }
}

/*
 * push a scope name fifo (stack) from $scope vcd definitions section 
 */
static int32 push_scope(char *scopnam, char *modnam)
{
 if (++__top_scopei >= MAXSCOPES - 1)
  {
   __pv_terr(6, ".tvcd $scope directive nested too deeply (%d)\n",
    MAXSCOPES - 1);
  }
 __scopnam_stk[__top_scopei] = __my_stralloc(scopnam);
 __scopmdnam_stk[__top_scopei] = __my_stralloc(modnam);
 return(__top_scopei);
}

/*
 * pop a scope name fifo
 */
static void pop_scope(void)
{
 if (--__top_scopei < -1)
  {
   __pv_terr(7, ".tvcd $upscope stack underflow\n");
  }
}

/*
 * read a new var line - know $var token read and reads final $end
 *
 * $var wire 8 %1# count [7:0] $end
 *
 * new approach - now always need to read design with CVC so do not need
 * normal vcd info any more
 */
static void rd_add_var_to_tab(FILE *fp)
{
 struct tgl_vardef_t *tvdp;
 char netnam[RECLEN];
 char dvcodstr[10];
 int32  bits, r1, r2, ttyp;
 char type;
 
 /* type, nbits */
 get_vcd_tok(fp); 

 /* get the variable type  and check - not stored */
 type = get_var_type(__token);
 if (type < 0)
  {
   __pv_terr(8, "unknown variable type %s", __token);
  }

 /* get number of bits */
 get_vcd_tok(fp); 
 if (sscanf(__token, "%d", &(bits)) != 1)
  {
   __pv_terr(33, "illegal $var wire number of bits %s", __token);
  }

 /* dv code as string */
 get_vcd_tok(fp); 
 strcpy(dvcodstr, __token);
    
 /* SJM 04-16-13 - since old .tvcd could not handle all signal names */
 /* types, do not need to deal with any of it for this conversion prog */
 /* new simple .tgldat full rooted path name file will handle */
 /* variable name */
 get_vcd_tok(fp); 
 strcpy(netnam, __token);
		 
 get_vcd_tok(fp); 
 r1 = r2 = -1;
 /* if there is a space between the var name and the range concat to name */
 if (__token[0] == '[')
  {
   if (sscanf(__token, "[%d:%d]", &r1, &r2) != 2)
    {
     __pv_terr(10, "illegal width decalaration read - %s", __token);
    }
   get_vcd_tok(fp); 
  }

 if (get_sig_wid(r1, r2) != bits)
  {
   __pv_terr(11,
    "VCD .tvcd file vardecl section net %s range not same as width", netnam);
  }

 ttyp = get_vcd_keywrd(&(__token[1]));
 if (ttyp != VCD_END)
  {
   __pv_terr(29,
    "VCD .tvcd file $var record does not end with $end - ^%s read", __token);
  }

 tvdp = alloc_init_tgl_vardef();
 /* SJM 04-16-13 - LOOKATME - lots of duplicated rooted paths but gzlib */
 /* could be used to compress that will make small file */
 tvdp->rtpthnam = bld_alloc_tvcd_rt_pth(netnam);
 tvdp->in_modnam = __my_stralloc(__scopmdnam_stk[__top_scopei]);
 tvdp->dvcod = __my_stralloc(dvcodstr);
 tvdp->nbits = bits;
 /* SJM 06-13-13 - need to normalize to h:0 - that is tgldat format */
 /* { high_norm_bit, .., 0 } */
 if (r1 >= r2) 
  {
   /* [h:l] */
//SJM 10-13-13 - CHECKME rng1 now corresponds to old msb - must adjust  
   tvdp->rng1= r1 - r2;
   tvdp->rng2 = 0;
  }
 else
  {
   /* [l:h] */
   tvdp->rng1 = 0;
   tvdp->rng2 = r2 - r1;
  }
 tvdp->vardef_lcnt = __lin_cnt;
 /* tgl count per bit arrays not set here */
}

/*
 * get var definitions section vector width
 */
static int32 get_sig_wid(int32 r1, int32 r2) 
{
 if (r1 == -1)
  {
   if (r2 != -1)
    {
     __pv_terr(12, "illegal scalar range r1=%d but r2 != -1", r1);
    }
   return(1);
  }
 if (r1 >= r2) return(r1 - r2 + 1); 
 return(r2 - r1 + 1);
}


/*
 * alloc and init a new vardefs tab and element - grow tab if needed
 */
static struct tgl_vardef_t *alloc_init_tgl_vardef(void)
{
 size_t obytes, nbytes;
 struct tgl_vardef_t *tvdp;

 if (++__last_tglvardef >= __alloc_siz_tglvardefs - 1) 
  {
   obytes = __alloc_siz_tglvardefs*sizeof(struct tgl_vardef_t *);
   __alloc_siz_tglvardefs = (3*__alloc_siz_tglvardefs)/2;
   nbytes = __alloc_siz_tglvardefs*sizeof(struct tgl_vardef_t *);
   __tglvardefs = (struct tgl_vardef_t **) __my_realloc(__tglvardefs, obytes,
    nbytes);
  } 
 tvdp = (struct tgl_vardef_t *)  __my_malloc(sizeof(struct tgl_vardef_t));
 init_tgl_vardef(tvdp);
 __tglvardefs[__last_tglvardef] = tvdp;
 return(tvdp);
}

/*
 * initialize a tgl var def index (tab) record
 */
static void init_tgl_vardef(struct tgl_vardef_t *tvdp)
{
 tvdp->rtpthnam = NULL;
 tvdp->in_modnam = NULL;
 tvdp->in_instnam = NULL;
 tvdp->netnam = NULL;
 tvdp->dvcod = NULL;
 tvdp->nbits = -1;
 tvdp->rng1 = -1;
 tvdp->rng2 = -1;
 tvdp->tglcnt_01 = NULL;
 tvdp->tglcnt_10 = NULL;
 tvdp->vardef_lcnt = -1;
 tvdp->tglvdnxt = NULL;
} 

/*
 * build a vcd definitions rooted path 
 */
static char *bld_alloc_tvcd_rt_pth(char *netnam)
{
 int32 i;
 char *chp, s1[MAXRTPATH];

 strcpy(s1, "");
 for (i = 0; i <= __top_scopei; i++)
  {
   if (i > 0) strcat(s1, ".");
   strcat(s1, __scopnam_stk[i]);
  }
 strcat(s1, ".");
 strcat(s1, netnam);
 chp = __my_stralloc(s1);
 return(chp);
}

/*
 * read and update counts for .tvcd 
 *
 * know $enddefinitions $end line read - skips $dumpvars line, $comment
 * section then reads the first 0->1 toggles (at faked #0 time) then 1->0
 * toggles at faked +1 time
 *
 * tvcd virtual change section format is: 1) if signal dvcod appears without
 * a vector, then all bits toggled, if prefix is b<bit string> then 1 bits
 * in the string toggle
 *
 * SJM 11-18-13 - reading the vcd format string reads from leftmost (1st)
 * char to last.  First char in tvcd vcd files is the high bit and since
 * vectores always represented h:0 in vcd files, it is high bit of vector
 */
static void rd_set_counts_from_tvcd_body(FILE *fp)
{
 int32 is_01, typ;
 char c, *tokp, vector[RECLEN], dvcod[RECLEN];

 /* no signals in the header info */
 if (__last_tglvardef < 0)
  {
   __pv_terr(13, "illegal .tvcd input - empty vardefs section");
  }
 /* skip to the required #0 (0->1 transition section) */
 while (get_vcd_tok(fp) != EOF)
  {
   if (__token[0] == '#')
    {
     if (__token[1] != '0')
      {
       __pv_terr(14,
        "illegal .tvcd input - dumpvars section starts with %s not #0",
        __token);
      }
     goto found_0_to_1_section;  
    }
  }
 __pv_terr(28,
  "illegal .tvcd input - EOF while looking for 0->1 transition starting #0");

found_0_to_1_section: 
 is_01 = TRUE;
 while (get_vcd_tok(fp) != EOF)
  {
   tokp = __token;
   c = *tokp;
   tokp++;
   /* vector case */
   if (c == 'b')
    {
     /* this is the signal 0->1 toggle vector */
     strcpy(vector, tokp);
     get_vcd_tok(fp);
     upd_net_tgl(__token, vector, is_01);
     continue;
    }
   if (c == '$')
    {
     /* notice that #0 (0->1) section end with $end but (1->0) ends with #2*/
     /* if $end #1 - know it is now reading  1-> toggle */
     if (strcmp("$end", __token) != 0)
      {
       __pv_terr(16,
        "illegal .tvcd input: 0->1 section does not end with $end");
      }
     get_vcd_tok(fp);
     if (strncmp(__token, "#1", 2) != 0)
      {
       __pv_terr(17,
        "illegal .tvcd input: 1->0 toggle section does not start with #1");
      }
     is_01 = FALSE;
     /* then required $comment */
     get_vcd_tok(fp);
     typ = get_vcd_keywrd(&(__token[1]));
     if (typ != VCD_COMMENT) 
      {
       __pv_terr(18, "0->1 .tvcd input begin 1->0 $comment missing");
      }
     /* this reads commment $end */
     rd_to_vcd_end(fp);
     continue;
    }
   if (c == '#')
    {
     /* file ends with #2 */
     if (strcmp("#2", __token) != 0)
      {
       __pv_terr(19, "illegal .tvcd file %s: ending # not followed by 2");
      }
     break;
    }
   /* scalar case */
   if (c != '1' && c != '0')
    {
     __pv_terr(19, "illegal .tvcd input: scalar toggle must start with 0 or 1");
    }
   /* scalar vector is [0 or 1]<dv code> - no space */
   /* read the dvcod */
   sprintf(vector, "%c", c);
   strcpy(dvcod, tokp);
   upd_net_tgl(dvcod, vector, is_01);
  }
}

/*
 * update a signal from a toggle vector
 */
static void upd_net_tgl(char *dvcod, char *tgl_vector, int32 is_01)
{
 struct tgl_vardef_t *tvdp;

 tvdp = get_sig_by_dvcod(__tglvardefs, __last_tglvardef + 1, dvcod); 
 if (tvdp == NULL)
  {
   __pv_terr(20, "illegal .tvcd file %s - dvcod %s not found", dvcod);
  }

 /* SJM 10-10-13 - notice in .tvcd format excluded bits are '?' char */
 /* that is written into tgldat file as '?' - driven const 'C' not possible */
 /* but stored internally in tglcnt 01/10 values as -1 */
 if (strlen(tgl_vector) != tvdp->nbits)
  {
   __pv_terr(21,
    "illegal .tvcd input - vector tgl bit string width %d not same as signal width",
    tvdp->nbits);
  }
 if (is_01)
  {
   if (tvdp->tglcnt_01 != NULL)
    {
     __pv_terr(22, "illegal .tvcd input - same 0->1 dvcod %s repeated",
      dvcod);
    }
   else tvdp->tglcnt_01 = (int32 *) __my_malloc(tvdp->nbits*sizeof(int32));
   fill_tglcnt_from_str(tvdp->tglcnt_01, tgl_vector, tvdp->nbits);
   return;
  }
 if (tvdp->tglcnt_10 != NULL)
  {
   __pv_terr(23, "illegal .tvcd input - same 1->0 dvcod %s repeated", dvcod);
  }
 else tvdp->tglcnt_10 = (int32 *) __my_malloc(tvdp->nbits*sizeof(int32));
 fill_tglcnt_from_str(tvdp->tglcnt_10, tgl_vector, tvdp->nbits);
}

/*
 * fill a vector of int32 toggle counts from a bit string
 *
 * SJM 03-17-13 - proc only for current toggle not toggle counts - if change
 * need int64 for counts
 */
static void fill_tglcnt_from_str(int32 *cntvec, char *tglstr, int32 len)
{
 int32 bi, i;
 int32 lval;

 for (i = 0, bi = len - 1; i < len; i++, bi--)
  {
   /* SJM 11-18-13 - vcd binary vector bit 0 is high bit so goes in cnt vec */
   /* high bit - then written in high bit to low bit order later */
   if (tglstr[i] == '0') lval = 0;
   /* '?' is Verilog input x which is used for exclude form -optconfig file */
   else if (tglstr[i] == '?') lval = -1;
   else lval = 1;
   cntvec[bi] = lval;
  }
}

/*
 * binary search for verilog signal by id
 */
static struct tgl_vardef_t *get_sig_by_dvcod(struct tgl_vardef_t **tglvardefs,
 int32 num, char *vec_dvcod)
{
 int32 l, h;
 int32 m, cv;

 l = 0; h = num - 1;
 for (;;)
  {
   m = (l + h)/2;
   if ((cv = strcmp(tglvardefs[m]->dvcod, vec_dvcod)) == 0)
    {
     return(tglvardefs[m]);
    }
   if (cv < 0) l = m + 1; else h = m - 1;
   if (h < l) break;
  }
 return(NULL);
}

/*
 * compare for sort by dumpvars dv code
 */
static int32 sig_dvcod_cmp(const void *s1, const void *s2)
{
 return(strcmp((*((struct tgl_vardef_t **) s1))->dvcod,
  (*(struct tgl_vardef_t **) s2)->dvcod));
}

/*
 * compare for sort by rooted net path name 
 */
static int32 sig_rtpth_cmp(const void *s1, const void *s2)
{ 
 return(strcmp((*((struct tgl_vardef_t **) s1))->rtpthnam,
  (*(struct tgl_vardef_t **) s2)->rtpthnam));
}


/*
 * write the simple tgl .tgldat:
 * <full path> {comma 0-1 cnts list for all bits> } {comma 1-0 cnts list };
 *
 * SJM 10-10-13 - now must pass unknown ('?') which is really excluded bit
 * of vector (for conversion from tvcd excluded scalar impossible) into
 * .tgldat file as a -1 then become the '?' in the {<comma list>}
 * SJM 10-10-13 - NOTICE there is no driven const ('C') in old .tvcd format
 *                so -2 impossible
 */
static void wr_tgl_dat_out_file(FILE *ofp, char *tgldat_fnam)
{
 int32 si, bi;
 struct tgl_vardef_t *tvdp;
 char val01str[RECLEN], val10str[RECLEN];

 /* now sort by signal name and output */
 qsort(__tglvardefs, __last_tglvardef + 1, sizeof(struct tgl_vardef_t *),
  sig_rtpth_cmp);

 fprintf(ofp,
   "//writer version: tvcd_to_tgldat %s of %s - a top <none> a .tgldat input <none>\n", VERS, OFDT);
 fprintf(ofp, "//date: %s\n", __tvcd_date);

 for (si = 0; si <= __last_tglvardef; si++)
  { 
   tvdp = __tglvardefs[si];
   fprintf(ofp, "%s : %s", tvdp->in_modnam, tvdp->rtpthnam); 
   /* SJM 09-23-13 - .tvcd has a bug - scalars are treated as vector [0:0] */
   /* fixing it but means actual 1 bit [0:0] vector wrong */
   if (tvdp->rng1 == -1 || (tvdp->rng1 == 0 && tvdp->rng2 == 0))
    {
     if (tvdp->tglcnt_01[0] == -1) strcpy(val01str, "?");
     else sprintf(val01str, "%d", tvdp->tglcnt_01[0]);
     if (tvdp->tglcnt_10[0] == -1) strcpy(val10str, "?");
     else sprintf(val10str, "%d", tvdp->tglcnt_10[0]);

     fprintf(ofp, " [] {%s} {%s};\n",val01str, val10str);
     continue;
    }
   if (tvdp->nbits > 32) 
    {
     fprintf(ofp, " [%d:%d]\n{", tvdp->rng1, tvdp->rng2);
     for (bi = tvdp->nbits - 1; bi >= 0; bi--)
      {
       if (tvdp->tglcnt_01[bi] == -1) strcpy(val01str, "?");
       else sprintf(val01str, "%d", tvdp->tglcnt_01[bi]);
       fprintf(ofp, "%s", val01str);
       /* comma after all but last */
       if (bi != 0) fputc(',', ofp);
      }
     fputs("}\n{", ofp);
     for (bi = tvdp->nbits - 1; bi >= 0; bi--)
      {
       if (tvdp->tglcnt_10[bi] == -1) strcpy(val10str, "?");
       else sprintf(val10str, "%d", tvdp->tglcnt_10[bi]);
       fprintf(ofp, "%s", val10str);
       /* comma after all but last */
       if (bi != 0) fputc(',', ofp);
      }
     fputs("};\n", ofp);
     continue;
    }
   fprintf(ofp, " [%d:%d] {", tvdp->rng1, tvdp->rng2);
   for (bi = tvdp->nbits - 1; bi >= 0; bi--)
    {
     if (tvdp->tglcnt_01[bi] == -1) strcpy(val01str, "?");
     else sprintf(val01str, "%d", tvdp->tglcnt_01[bi]);
     fprintf(ofp, "%s", val01str);
     /* comma after all but last */
     if (bi != 0) fputc(',', ofp);
    }
   fputs("} {", ofp);
   for (bi = tvdp->nbits - 1; bi >= 0; bi--)
    {
     if (tvdp->tglcnt_10[bi] == -1) strcpy(val10str, "?");
     else sprintf(val10str, "%d", tvdp->tglcnt_10[bi]);
     fprintf(ofp, "%s", val10str);
     /* comma after all but last */
     if (bi != 0) fputc(',', ofp);
    }
   fputs("};\n", ofp);
  }
}

/*
 * DBG ROUTINES
 */
static void dbg_dmp_tglvardefs(struct tgl_vardef_t **tvgvds, int32 tvnum)
{ 
 int i;
 struct tgl_vardef_t *tvdp;

 Msg("\n");
 for (i = 0; i < tvnum; i++)
  {
   tvdp = tvgvds[i];
   if (tvdp == NULL)
    {
     __terr(24, "no body for tgl var def index=%d", i);
    }
//SJM 10-13-13 - ?? this is reversed since rng1 usually h:l - Ver internal */
   Msg("ndx=%d, rt path=%s dvcod=%s nbits=%d h=%d l=%d]\n", i, tvdp->rtpthnam,
    tvdp->dvcod, tvdp->nbits, tvdp->rng2, tvdp->rng1);
  }
}
 

/*
 * TOKENIZATION ROUTINES
 */

/*
 * get a new token from the file fp, and place in global token,
 * and return the length
 *
 * since global token, caller must save if needed
 */
static int32 get_vcd_tok(FILE *fp)
{
 int32 i, c; 

 i = 0;
 while ((c = fgetc(fp)) != EOF)
  {
   if (isspace(c))
    {
     if (c == '\n') __lin_cnt++; 	 
      continue;
    }
   break;
  }
 
 if (c == EOF) return EOF;
 __token[i++] = c;

 while (!isspace(c = fgetc(fp)))
  {
   if (c == EOF) return(EOF);
   else __token[i++] = c;
  }
 if (c == '\n') __lin_cnt++; 	 
 __token[i] = '\0';
 return(i); 
}

/*
 * collect a tvcd dumpvars style file element into a string - reads to $end
 */
static void collect_keyword_section(FILE *fp, char *kywd_str, char *keyword)
{
 int32 first_time;

 strcpy(kywd_str, "");
 first_time = TRUE;
 while (get_vcd_tok(fp) != EOF) 
  {
   if (strncmp(__token, "$end", 4) == 0) return;
   if (first_time) first_time = FALSE; else strcat(kywd_str, " ");
   strcat(kywd_str, __token);
  }
 __pv_terr(25, "EOF read before expected keyword %s", keyword);
}

/*
 * read the file until an $end is reached
 */
static void rd_to_vcd_end(FILE *fp)
{
 while (get_vcd_tok(fp) != EOF) 
  {
   if (!strncmp(__token, "$end", 4)) return;
  }
 __pv_terr(26, "EOF read while skipping to $end");
}

/*
 * ROUTINES TO CONVERT TO/FROM VCD KEYWORD NUMBERS
 */

/* verilog VCD keywords - table must be kept in alpabetical order */
static const struct keyword_t vcdkeywds[] = {
 { "comment", VCD_COMMENT},
 { "date", VCD_DATE},
 { "dumpvars", VCD_DUMPVARS},
 { "end", VCD_END },
 { "enddefinitions", VCD_ENDDEF},
 { "scope", VCD_SCOPE},
 { "timescale", VCD_TIMESCALE},
 { "upscope", VCD_UPSCOPE},
 { "var", VCD_VAR},
 { "version", VCD_VERSION} 
};
#define VCDKEYWDS (sizeof(vcdkeywds) / sizeof(struct keyword_t))

/*
 * binary search for verilog keyword to int
 */
static int32 get_vcd_keywrd(char *tstr)
{
 int32 l, h;
 int32 m, cv;

 l = 0; h = VCDKEYWDS - 1;
 for (;;)
  {
   m = (l + h)/2;
   if((cv = strcmp(vcdkeywds[m].vnam, tstr)) == 0)
    {
     return(vcdkeywds[m].vnum);
    }
   if(cv < 0) l = m + 1; else h = m - 1;
   if(h < l) break;
  }
 return(EOF);
}

/* verilog variable types  - table must be kept in alphabetical order */
static const struct keyword_t var_types[] = {
 {"bit", BIT},
 {"byte", BYTE},
 {"chandle", CHANDLE},
 {"event", EVENT},
 {"int", INT},
 {"integer", INTEGER},
 {"logic", LOGIC}, 
 {"longint", LONGINT}, 
 {"real", REAL}, 
 {"reg", REG},
 {"shortint", SHORTINT}, 
 {"supply0", SUPPLY0}, 
 {"supply1", SUPPLY1}, 
 {"time", TIME}, 
 {"tri", TRI}, 
 {"tri0", TRI0}, 
 {"tri1", TRI1}, 
 {"triand", TRIAND}, 
 {"trior", TRIOR}, 
 {"trireg", TRIREG}, 
 {"wand", WAND},  
 {"wire", WIRE},
 {"wor", WOR}
};
#define VARTYPE (sizeof(var_types) / sizeof(struct keyword_t))

/*
 * return the type of variable by doing binary search of type
 * return int value for type, -1 on failure
 * reg, wire, integer, etc
 */
static int32 get_var_type(char *tstr)
{
 int32 l, h;
 int32 m, cv;

 l = 0; h = VARTYPE - 1;
 for (;;)
  {
   m = (l + h)/2;
   if((cv = strcmp(var_types[m].vnam, tstr)) == 0)
    {
     return(var_types[m].vnum);
    }
   if(cv < 0) l = m + 1; else h = m - 1;
   if(h < l) break;
  }
 return(-1);
}
