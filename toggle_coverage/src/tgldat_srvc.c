/* This is free and unencumbered software released into the public domain. */

/*
 * module from misc tgldat reading and I/O procs
 */

#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include <stdarg.h>
#include "tgldat.h"

/* procs local to misc API file - if called by user code change to extern */
static char *isolate_td_el(char *, int32);
static char *collect_cnv_td_rng(char *, int32 *, int32 *);
static int32 xtrct_short_tgl_values(char *, char *, char *);
static int32 bld_tgl_val_array_from_list(int32 *, int32, char *, char *);
static int32 get_tgl_val(char *, char *, int32 *, char *);
static void init_tgl_vardef(struct tgl_vardef_t *);
static void grow_td_mod_tab(struct td_netlist_t *);
static char *rm_net_from_rtpth(char *);
static struct td_mod_t *alloc_init_td_mod(char *);
static void grow_td_inst_tab(struct td_mod_t *);
static struct td_inst_t *alloc_init_td_inst(void);
static struct tgl_vardef_t *__copy_alloc_td_vardef(struct tgl_vardef_t *);
static void grow_inst_vardefs_tab(struct td_inst_t *);
static int32 rtpthnam_cmp(const void *, const void *);

/* externs defined and usable by any file */
extern void __init_tgldat_api_glbs(void);
extern struct tgl_vardef_t *__rd_tgldat_to_vardefs(FILE *, char *);
extern int32 __rd_one_net_tgldat_rec(FILE *, int32 *);
extern struct tgl_vardef_t *__fill_tglvar_rec(int32);
extern int32 __glbnam_to_strtab(char *);
extern void __bld_vardef_netlist(struct td_netlist_t *, struct tgl_vardef_t *,
 char *);
extern void __add_one_tgl_vardef_el(struct td_netlist_t *,
 struct tgl_vardef_t *);
extern int32 __merge_tgldat_toggle_state(struct tgl_vardef_t *,
 struct tgl_vardef_t *);
extern struct td_netlist_t *__alloc_init_tgldat_netlist(void);
extern int32 __fnd_td_mod(struct td_netlist_t *, char *);
extern struct td_mod_t *__insert_mod_in_netlist(struct td_netlist_t *,
 char *);
extern struct td_inst_t *__insert_inst_in_mod(struct td_mod_t *, char *);
extern struct tgl_vardef_t *__insert_vardef_in_inst(struct td_inst_t *,
 struct tgl_vardef_t *);
extern int32 __fnd_td_instof(struct td_mod_t *, char *);
extern int32 __fnd_td_inst_vardefs(struct td_inst_t *, char *);
extern void __wr_one_tgldat_line_from_tglvardef(FILE *, struct tgl_vardef_t *);
extern char *__to_val(char *, int32);
extern struct tgl_vardef_t *__bld_sort_td_vardefs(struct td_netlist_t *);
extern void __free_one_nl_mod(struct td_mod_t *);
extern void __free_one_nl_instof(struct td_inst_t *);
extern void __free_netlist(struct td_netlist_t *);
extern void __free_list_of_tgl_vardef(struct tgl_vardef_t *);
extern void __free_tgl_vardef(struct tgl_vardef_t *);

extern void __dbg_dump_one_netlist(struct td_netlist_t *);
extern void __dbg_dump_one_mod(struct td_mod_t *);
extern void __dbg_dump_one_inst(struct td_inst_t *);
extern void __dbg_dump_one_1vardef(struct tgl_vardef_t *);

extern char *__my_stralloc(char *);
extern char *__my_malloc(size_t);
extern char *__my_realloc(void *, size_t, size_t);
extern void __my_free(void *, size_t);
extern ssize_t __my_getline(char **, size_t *, FILE *);
extern void __warn(int32 id_num, char *s, ...);
extern void __pv_fwarn(int32, char *, ...);
extern void __terr(int32, char *s, ...);
extern void __pv_terr(int32, char *s, ...);
extern ssize_t __my_getline(char **, size_t *, FILE *);
extern void Msg(char *s, ...);
extern void __my_fprintf(FILE *f, char *s, ...);
extern void __my_vfprintf(FILE *, char *, va_list, va_list);
extern int32 __my_putc(int32, FILE *);

/*
 * INITIALIZE ROUTINES NEEDED TO USE .tgldat MISC PROCESSING ROUTINES
 */

/*
 * initialize tgldat API values - must be called during init to use procs here 
 */
extern void __init_tgldat_api_glbs(void)
{
 int32 pthi;

 /* init work globals */
 __tgl_modnam = __my_malloc(RECLEN);

 __tglbits01 = __my_malloc(RECLEN);
 __tglbits10 = __my_malloc(RECLEN);
 __siz_tgl_lst = RECLEN;
 /* this is glb ptr to current net list (needed for merging files) */ 
 __file_netlist = NULL;

 __tgl_rtpthnam = (char *) __my_malloc(RECLEN + 1);
 __siz_tgl_rtpthnam = RECLEN + 1;

 __tgl01tab = (int32 *) __my_malloc(MAXTGLVECSIZ*sizeof(int32));
 __tgl10tab = (int32 *) __my_malloc(MAXTGLVECSIZ*sizeof(int32));

 /* SJM 10-24-13 - alloc rooted path comps once to avoid alloc/free */
 /* know from  IDs in Verilog limited to 1024 chars */
 for (pthi = 0; pthi < MAXSCOPES; pthi++)
  {
   __tgldat_pthcmps[pthi] = (char *) __my_malloc(IDLEN + 1);
  }
 __last_tdpthi = -1;
 __ix_insert = -1;

 strcpy(__tgldat_writer_date, "<none>");
 strcpy(__tgldat_writer_vers, "<none>");
 __emit_dup_rtpth_warn = FALSE;

 /* alloc and initialize one global net list container */
 /* if only on file read, best to just use this net list container */ 
 /* first time file netlist used, must set file name */
 __file_netlist = __alloc_init_tgldat_netlist();
}

/*
 * ROUTINES TO READ .TGLDAT FILES
 */

/*
 * read a tgldat file and build a list of .tgldat vardefs in the file
 *
 * proc assumes good .tgldat file passed - run chk_tgldat to analyse if get
 * terminal error here
 */
extern struct tgl_vardef_t *__rd_tgldat_to_vardefs(FILE *fp, char *fnam)
{
 int32 rv, beg_lcnt;
 struct tgl_vardef_t *tvdp_hd, *tvdp_tail, *tvdp;

 strcpy(__cur_fnam, fnam);
 __lin_cnt = 0;
 tvdp_hd = tvdp_tail = NULL;
 for (;;)
  {
   /* this sets globals used to fill tgldat vardef record */
   if ((rv = __rd_one_net_tgldat_rec(fp, &(beg_lcnt))) == -1) break;
   if (rv == 0)
    {
     __pv_terr(10, "illegal line in .tgldat file %s",
      fnam);
    }
   /* assumes glb fully qualified name good - if no this has fatal error */
   /* for checking must call __glbnam_to_strtab before calling this */
   tvdp = __fill_tglvar_rec(beg_lcnt);

   if (tvdp_hd == NULL) tvdp_hd = tvdp_tail = tvdp;
   else tvdp_tail->tglvdnxt = tvdp;
   tvdp_tail = tvdp;
  }
 return(tvdp_hd);
}

/*
 * alloc and fill one tgldat vardef record
 */
extern struct tgl_vardef_t *__fill_tglvar_rec(int32 lcnt) 
{
 int32 bi, nwid;
 struct tgl_vardef_t *tvdp;

 tvdp = (struct tgl_vardef_t *)  __my_malloc(sizeof(struct tgl_vardef_t));
 init_tgl_vardef(tvdp);
 tvdp->rtpthnam = (char *) __my_stralloc(__tgl_rtpthnam);
 tvdp->in_modnam = (char *) __my_stralloc(__tgl_modnam);

 /* if caller wants to check a tgldat line and continue must call this */
 /* before calling fill to make sure line good */
 if (!__glbnam_to_strtab(__tgl_rtpthnam))
  {
   __pv_terr(11, "tgldat path %s illegal - run chk_tgldat to diagnose",
    tvdp->rtpthnam); 
  }
 /* to get the top mod above .tgldat net, use 0th index of tgldat pthcmps */
 tvdp->netnam = __my_stralloc(__tgldat_pthcmps[__last_tdpthi]);
 tvdp->in_instnam = __my_stralloc(__tgldat_pthcmps[__last_tdpthi - 1]);

 if (__tgl_r1 > __tgl_r2) nwid = __tgl_r1 - __tgl_r2 + 1;
 else nwid = __tgl_r2 - __tgl_r1 + 1;
 tvdp->nbits = nwid;
 tvdp->rng1 = __tgl_r1;
 tvdp->rng2 = __tgl_r2;

 /* inside tgldat vardefs, each toggle is stored as one int32 */ 
 tvdp->tglcnt_01 = (int32 *) __my_malloc(nwid*sizeof(int32));
 tvdp->tglcnt_10 = (int32 *) __my_malloc(nwid*sizeof(int32));
 if (!bld_tgl_val_array_from_list(tvdp->tglcnt_01, nwid, __tglbits01, "0->1"))
  {
   __pv_terr(12, "tgldat 0->1 toggle value list bad format");
  }
 if (!bld_tgl_val_array_from_list(tvdp->tglcnt_10, nwid, __tglbits10, "1->0"))
  {
   __pv_terr(12, "tgldat 1->0 toggle value list bad format");
  }
 /* check to make sure if 0->1 excluded or driven const so is 1->0 */
 for (bi = 0; bi < nwid; bi++)
  {
   if ((tvdp->tglcnt_10[bi] == -1 && tvdp->tglcnt_01[bi] != -1)
    || (tvdp->tglcnt_10[bi] == -2 && tvdp->tglcnt_01[bi] != -2)
    || (tvdp->tglcnt_01[bi] == -1 && tvdp->tglcnt_10[bi] != -1)
    || (tvdp->tglcnt_01[bi] == -2 && tvdp->tglcnt_10[bi] != -2))
    {
     __pv_terr(12,
      "tgldat driven const or excluded toggle values bit %d inconsistent", bi);
    }
  }
 tvdp->vardef_lcnt = lcnt;
 return(tvdp);
}

/*
 * ROUTINES TO READ ONE .TGLDATA FILE NET TOGGLE LINE
 */

/* SJM 07-28-13 - use defines so can have vi find match c brackets */
#define LSETBRAK '{'
#define RSETBRAK '}'
#define LSQBRAK '['
#define RSQBRAK ']'

/*
 * read one tgldat vector element into globals __tgl modnam, __tgl rtpthnam,
 * __tgl_r1, __tgl_r2 (-1 for scalar) and __tglbits [_01/_10] 
 *
 * returns -1 on EOF, 1 on success, 0 on error (with warning message)  
 * notice 0->1 and 1->0 toggle vectors include surrounding {}
 */
extern int32 __rd_one_net_tgldat_rec(FILE *fp, int32 *start_lcnt)
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
 *start_lcnt = __lin_cnt;

 /* SJM 09-13-13 - isolate a token - know will be modnam (maybe escaped) */
 endchp = isolate_td_el(tgl_line, ':');
 if (*endchp == '\0')
  {
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
 endchp = isolate_td_el(linep, LSQBRAK);
 /* otherwise know end chp is the searched for isolate end char */
 if (*endchp == '\0')
  {
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
    __siz_tgl_rtpthnam, 3*pthlen/2);
   __siz_tgl_rtpthnam = 3*pthlen/2;
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
   if ((endchp = collect_cnv_td_rng(linep, &(r1), &(r2))) == NULL)
    {
     __pv_fwarn(4317,
      "TGL: .tgldat line net range bad format or illegal ranges - skipped");
     return(0);
    } 
   __tgl_r1 = r1;
   __tgl_r2 = r2;
  } 
 /* SJM 09-23-13 - BEWARE - short form requires no space after range end ']' */
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
static char *isolate_td_el(char *linep, int32 endch)
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
static char *collect_cnv_td_rng(char *linep, int32 *rng1, int32 *rng2)
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
 * order is high to low bits in list, i.e. rng2 is right most
 * know tglvectab larg enough to hold all bits of net 
 *
 * here just use large vector - in CVC will know the width
 *
 * SJM 06-13-13 - .tgldat file always stored normalized { [h], ... [0] }
 * so first bit goes in high etc.
 *
 * SJM 10-22-13 - notice for net list tgldat format, emit the warnings
 * for problems, but caller will have a fatal error since here file
 * format must be right 
 *
 * SJM 11-02-13 - tgldat lists are stored in normal Verilog h:0 order
 * so first (leftmost) list element is the high bit and rightmost is
 * the low bit  
 */
static int32 bld_tgl_val_array_from_list(int32 *tglvaltab, int32 nbits,
 char *tglvecstr, char *errstr)
{
 int32 veci;
 int32 ival;
 char *chp, *chp2, *chp3;

 if (*tglvecstr != LSETBRAK)
  {
   __pv_fwarn(4328,
    "TGL: malformed .tgldat %s toggle value list - missing begin %c - skipped",
    errstr, LSETBRAK);
   return(FALSE);
  }
 chp = &(tglvecstr[1]);
 /* need to start one high than high bit interanl h:0 format */
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
   /* SJM 05-02-13 - was not assigning final value from ival */
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
 * convert global reference as string into global path expression
 * fill passed path tab of ptrs to char size must be MAXSCOPES size
 * so do not need to grow
 *
 * returns F (0) and emits warning on error, else returns T (1)
 *
 * can't fail but if bad path dies with fatal error
 * components malloced so caller must free when done using
 *
 * no white space allowed except to end escaped IDs
 * handles escaped IDs (\...[white space] and ending [<number>] for inst arrays 
 * source xmr's can have spaces but not allowed here - make sure documented
 *
 * notice number of path components including ending signal name is
 * __last_tdpthi + 1
 *
 * proc is used internal by proc that builds the tgl vardef record, but
 * can also be used by user code to access tdl vardef rooted path components
 */
extern int32 __glbnam_to_strtab(char *full_pthnam)
{
 int32 slen, esc_name;
 char *chp, *chp2, *chp3, *sepchp;
 char s1[RECLEN], s2[RECLEN];

 __last_tdpthi = -1;
 for (chp = full_pthnam;;)
  {
   /* separate out one component */
   /* case 1: escaped name */
   esc_name = FALSE;
   if (*chp == '\\') 
    {
     if (chp[1] == ' ') 
      {
       __pv_fwarn(61,
        "tgldat path %s illegal - empty escaped component illegal",
        full_pthnam); 
       return(FALSE);
      }
     if ((chp2 = strchr(chp, ' ')) == NULL)
      {
       __pv_fwarn(62, 
        "tgldat path %s illegal - escaped component ending space missing",
        full_pthnam); 
       return(FALSE);
      }
     /* include one space in escaped ID */
     chp2++;
     strncpy(s1, chp, chp2 - chp);
     /* escaped ID now extracted into s1 */
     s1[chp2 - chp] = '\0';
     while (*chp2 == ' ') chp2++;
     if (*chp2 == '[')
      {
       if ((chp3 = strchr(chp2, ']')) == NULL)
        {
         __pv_fwarn(63, 
          "tgldat path %s illegal - instance array select missing ']'",
          full_pthnam); 
         return(FALSE);
        }
       chp3++;
       strncpy(s2, chp2, chp3 - chp2); 
       s2[chp3 - chp2] = '\0';
       strcat(s1, s2); 
       /* one past ending ']' */ 
       sepchp = chp3;
      }
     else sepchp = chp2;
     esc_name = TRUE;
    }
   else
    { 
     /* case 2: non escaped maybe instance array select */ 
     if ((chp2 = strchr(chp, '.')) != NULL)
      {
       strncpy(s1, chp, chp2 - chp);
       s1[chp2 - chp] = '\0';
       /* point to '.' separator */
       sepchp = chp2;
      }
     else
      {
       strcpy(s1, chp);
       slen = strlen(chp);
       /* point to '\0' */
       sepchp = &(chp[slen]);
      }
    }
   /* s1 contains component maybe with select */
   strcpy(__tgldat_pthcmps[++__last_tdpthi], s1);

   /* sepchp points into separae iref string */
   if (*sepchp  == '\0') break;
   else if (*sepchp != '.') 
    {
     __pv_fwarn(64, 
      "tgldat path %s internal component %s not followed by '.' separator",
       full_pthnam, s1);
     return(FALSE);
    } 
   chp = sepchp;
   chp++;
  }
 return(TRUE);
}

/*
 * ROUTINES TO BUILD MOD-INST-NET VERILOG LIKE D.S. FROM TGLDAT VARDEF LIST
 */

/*
 * build a net list data structure (CVC type internal net list given that
 * file may have instance and bits excluded that are in design net list)
 */
extern void __bld_vardef_netlist(struct td_netlist_t *nlp,
 struct tgl_vardef_t *tvd_hd, char *fnam)
{
 struct tgl_vardef_t *tvdp, *tvdp2;

 nlp->netlist_fnam = __my_stralloc(fnam);
 for (tvdp = tvd_hd; tvdp != NULL;)
  {
   tvdp2 = tvdp->tglvdnxt;
   __add_one_tgl_vardef_el(nlp, tvdp);
   tvdp = tvdp2;
  }
}

/*
 * add1 vardef element to a net list
 *
 * caller must allocate and initialize net list record
 * sets cur fnam and lin cnt set but does not save - caller must save if needed
 * if duplicate nets in tgldat file, merged with possible warn here
 */
extern void __add_one_tgl_vardef_el(struct td_netlist_t *netlist1,
 struct tgl_vardef_t *tvdp)
{
 int32 mi, ii, tvdi;
 struct td_mod_t *tdmdp;
 struct td_inst_t *tdip;
 struct tgl_vardef_t *tvdp2;
 char *ipthnam;

 strcpy(__cur_fnam, netlist1->netlist_fnam);
 __lin_cnt = tvdp->vardef_lcnt;

 /* add to sorted net list's mod tab - repeated ok - sorted by mod name */
 if ((mi = __fnd_td_mod(netlist1, tvdp->in_modnam)) == -1)
  {
   tdmdp = __insert_mod_in_netlist(netlist1, tvdp->in_modnam);
  }
 else tdmdp = netlist1->nlmods[mi];
 
 /* build the inst path name with ending net removed */
 /* assigned malloc string here */
 ipthnam = rm_net_from_rtpth(tvdp->rtpthnam);
 /* add inst to mod - sorted by rooted path with ending net name removed */
 if ((ii = __fnd_td_instof(tdmdp, ipthnam)) == -1)
  {
   tdip = __insert_inst_in_mod(tdmdp, ipthnam);
  }
 else
  {
   __my_free(ipthnam, strlen(ipthnam) + 1);
   tdip = tdmdp->td_instsof[ii];
  }

 /* add net to vardefs tab - can just use net name since know path same */
 /* SJM 11-02-13 - if 2nd net to add inst path differs, won't get here */
 if ((tvdi = __fnd_td_inst_vardefs(tdip, tvdp->netnam)) == -1)
  {
   /* know ix insert set */
   tvdp2 = __insert_vardef_in_inst(tdip, tvdp);
  }
 else
  {
   tvdp2 = tdip->netvardefs[tvdi];
   /* know this is duplicate - merge tgldat data and emit warn warn if not */
   /* suppressed */
   if (__emit_dup_rtpth_warn)
    {
     __pv_fwarn(51,
      "identical tgldat net %s in mod %s inst %s - previous at **%s(%d)",
      tvdp2->netnam, tvdp2->in_modnam, tvdp2->in_instnam, tvdp2->netnam,
      netlist1->netlist_fnam, tvdp2->vardef_lcnt);
    }
   if (tvdp->nbits != tvdp2->nbits)
    {
     __pv_fwarn(52,
      "new tgldat line element net %s in mod %s inst %s different width %d previous %d",
      tvdp2->in_modnam, tvdp2->in_instnam, tvdp2->netnam, tvdp2->rtpthnam,
      tvdp2->nbits, tvdp->nbits);
    }
   /* here do not insert since already in net list */
   /* merge current into original that appeared earlier in list */
   __merge_tgldat_toggle_state(tvdp2, tvdp);
  } 
}

/*
 * remove net name from tgldat state element rooted path
 * returns malloc ipth string
 *
 * SJM 10-11-13 maybe more efficient to just find last comp and copy
 * but handling arrays of insts and escaped names tricky working from right
 * to left
 */
static char *rm_net_from_rtpth(char *rtpth)
{
 int32 pthi;
 char *chp, *ipthnam;

 __glbnam_to_strtab(rtpth);

 /* inst path string can never be larger than path with net */
 chp = (char *) __my_malloc(strlen(rtpth) + 1);
 strcpy(chp, __tgldat_pthcmps[0]);
 /* leave off last pth component which is net */
 for (pthi = 1; pthi < __last_tdpthi; pthi++)
  {
   strcat(chp, ".");
   strcat(chp, __tgldat_pthcmps[pthi]);
  }
 
 /* copy so malloced length is same as string len */
 ipthnam = __my_stralloc(chp);
 __my_free(chp, strlen(rtpth) + 1);
 __last_tdpthi = -1;
 return(ipthnam);
}

/*
 * alloc and initialize a tgldat file contents net list contents record
 */
extern struct td_netlist_t *__alloc_init_tgldat_netlist(void)
{
 struct td_netlist_t *nlp; 

 nlp = (struct td_netlist_t *) __my_malloc(sizeof(struct td_netlist_t));
 /* user must set this is stralloc proc */
 nlp->siz_td_mods_tab = 100; 
 nlp->nlmods = (struct td_mod_t **)
  __my_malloc(nlp->siz_td_mods_tab*sizeof(struct td_mod_t *));
 nlp->num_td_mods = 0;

 nlp->netlist_fnam = NULL;
 nlp->nl_tvd_hd = NULL;
 return(nlp);
}

/*
 * find a module name in tgldat mods - set ix insert global if not found
 */
extern int32 __fnd_td_mod(struct td_netlist_t *nlp, char *mnam)
{
 int32 cv, l, h, m;
 struct td_mod_t *tdmdp;

 if (nlp->num_td_mods <= 0) { __ix_insert = 0; return(-1); }
 l = 0; h = nlp->num_td_mods - 1;
 for (;;)
  {
   m = (l + h)/2;
   tdmdp = nlp->nlmods[m];
   if ((cv = strcmp(tdmdp->modnam, mnam)) == 0) return(m);
   if (cv < 0) l = m + 1; else h = m - 1;
   if (h < l) { __ix_insert = l; break; }
  }
 return(-1);
}

/* insert and alloc a tgldat mod after not found searching
 * return malloc tgldat mod record
 *
 * must call fnd tgldat mod first with not found that sets ix insert glb
 */
extern struct td_mod_t *__insert_mod_in_netlist(struct td_netlist_t *nlp,
 char *mnam)
{
 int32 mi;
 struct td_mod_t *tdmdp;

 if (nlp->num_td_mods + 2 >= nlp->siz_td_mods_tab) grow_td_mod_tab(nlp);
 /* SJM 10-08-13 - could use memcpy here */
 /* SJM 10-25-13 - order was backward - must start at top into unused new top */
 /* otherwise just propagate low up into every cell */
 /* in c, for loop index is tested before each iteration */
 for (mi = nlp->num_td_mods; mi > __ix_insert; mi--)
  {
   nlp->nlmods[mi] = nlp->nlmods[mi - 1];
  }
 nlp->num_td_mods++;
 tdmdp = alloc_init_td_mod(mnam);
 nlp->nlmods[__ix_insert] = tdmdp;
 return(tdmdp);
}

/*
 * grow tgldat mod ptr tab - assume adding one at a time
 */
static void grow_td_mod_tab(struct td_netlist_t *nlp)
{
 int32 obytsiz, nbytsiz;

 obytsiz = nlp->siz_td_mods_tab*sizeof(struct td_mod_t *);
 nbytsiz = (3*obytsiz)/2;
 nlp->siz_td_mods_tab  = (3*nlp->siz_td_mods_tab)/2 + 1;
 /* ptr get copied and do not change */
 nlp->nlmods = (struct td_mod_t **) __my_realloc(nlp->nlmods, obytsiz,
  nbytsiz); 
}

/*
 * initialize a tgldat mod record
 */
static struct td_mod_t *alloc_init_td_mod(char *mnam)
{
 struct td_mod_t *tdmdp;

 tdmdp = (struct td_mod_t *) __my_malloc(sizeof(struct td_mod_t)); 
 tdmdp->modnam = (char *) __my_stralloc(mnam);
 /* mods usually either have few or a large number of insts */
 tdmdp->siz_td_instsof_tab = 20;
 tdmdp->td_instsof = (struct td_inst_t **)
  __my_malloc(tdmdp->siz_td_instsof_tab*sizeof(struct td_inst_t *));
 tdmdp->num_td_instsof = 0;
 return(tdmdp);
}

/*
 * find inst in instof tab for a mod - need to use entire path except end net
 */
extern int32 __fnd_td_instof(struct td_mod_t *tdmdp, char *ipthnam)
{
 int32 cv, l, h, m;
 struct td_inst_t *tdip;

 if (tdmdp->num_td_instsof <= 0) { __ix_insert = 0; return(-1); }
 l = 0; h = tdmdp->num_td_instsof - 1;
 for (;;)
  {
   m = (l + h)/2;
   tdip = tdmdp->td_instsof[m];
   /* first sort by module name */
   if ((cv = strcmp(tdip->irtpthnam, ipthnam)) == 0) return(m);
   if (cv < 0) l = m + 1; else h = m - 1;
   if (h < l) { __ix_insert = l; break; }
  }
 return(-1);
}

/* insert and alloc a tgldat inst in a mod record after not found searching
 * return malloc tgldat mod record
 *
 * must call fnd tgldat mod first with not found that sets ix insert glb
 * ipthnam is already malloc so if matches caller needs to free but no 
 * need to alloc here
 *
 * SJM 11-02-13 - notice fnd td instof must be called to set ix insert
 * before here
 */
extern struct td_inst_t *__insert_inst_in_mod(struct td_mod_t *tdmdp,
 char *ipthnam)
{
 int32 ii;
 struct td_inst_t *tdip;

 if (tdmdp->num_td_instsof + 2 > tdmdp->siz_td_instsof_tab)
  grow_td_inst_tab(tdmdp);
 /* SJM 10-08-13 - could use memcpy here */
 /* copy up making room each time */
 for (ii = tdmdp->num_td_instsof; ii > __ix_insert;  ii--)
  {
   tdmdp->td_instsof[ii] = tdmdp->td_instsof[ii - 1];
  }
 tdmdp->num_td_instsof++;

 tdip = alloc_init_td_inst();
 tdmdp->td_instsof[__ix_insert] = tdip;
 /* SJM 11-01-13 - need to malloc this */
 tdip->irtpthnam = (char *) __my_stralloc(ipthnam);
 return(tdip);
}

/*
 * grow tgldat inst ptrs tab, contents is tab of ptrs to net records
 */
static void grow_td_inst_tab(struct td_mod_t *tdmdp)
{
 int32 obytsiz, nbytsiz;

 obytsiz = tdmdp->siz_td_instsof_tab*sizeof(struct td_inst_t *);
 nbytsiz = 2*obytsiz;
 tdmdp->siz_td_instsof_tab  = 2*tdmdp->siz_td_instsof_tab;
 tdmdp->td_instsof = (struct td_inst_t **)
  __my_realloc(tdmdp->td_instsof, obytsiz, nbytsiz); 
}

/*
 * initialize an in tgldat mod record inst record
 */
static struct td_inst_t *alloc_init_td_inst(void)
{
 struct td_inst_t *tdip;

 tdip = (struct td_inst_t *) __my_malloc(sizeof(struct td_inst_t)); 
 tdip->irtpthnam = NULL;
 /* insts usually either have few or a large number of nets */
 tdip->siz_td_nets_tab = 20;
 tdip->netvardefs = (struct tgl_vardef_t **)
  __my_malloc(tdip->siz_td_nets_tab*sizeof(struct tgl_vardef_t *));
 tdip->td_num_nets = 0;
 return(tdip);
}


/*
 * find a net name in tgldat inst record- set ix insert global if not found
 */
extern int32 __fnd_td_inst_vardefs(struct td_inst_t *tdip, char *nnam)
{
 int32 cv, l, h, m;
 struct tgl_vardef_t *tvdp;

 if (tdip->td_num_nets <= 0) { __ix_insert = 0; return(-1); }
 l = 0; h = tdip->td_num_nets - 1;
 for (;;)
  {
   m = (l + h)/2;
   tvdp = tdip->netvardefs[m];
   /* first sort by module name */
   if ((cv = strcmp(tvdp->netnam, nnam)) == 0) return(m);
   if (cv < 0) l = m + 1; else h = m - 1;
   if (h < l) { __ix_insert = l; break; }
  }
 return(-1);
}

/*
 * insert and alloc a tgldat inst in a mod record after not found searching
 * return malloc tgldat mod record
 *
 * must call fnd tgldat mod first with not found that sets ix insert glb
 */
extern struct tgl_vardef_t *__insert_vardef_in_inst(struct td_inst_t *tdip,
 struct tgl_vardef_t *tvdp)
{
 int32 ni;

 if (tdip->td_num_nets + 2 > tdip->siz_td_nets_tab)
  {
   grow_inst_vardefs_tab(tdip);
  }
 /* copy ptrs down */
 for (ni = tdip->td_num_nets; ni > __ix_insert; ni--)
  {
   tdip->netvardefs[ni] = tdip->netvardefs[ni - 1];
  }
 tdip->td_num_nets++;
 /* SJM 10-15-13 - need to copy and allocate - vardefs in read list */
 /* not the same if dups */
 tdip->netvardefs[__ix_insert] = __copy_alloc_td_vardef(tvdp);
 return(tdip->netvardefs[__ix_insert]);
}

/*
 * grow tgldat net ptrs tab, contents is tab of ptrs to var def rooted paths
 */
static void grow_inst_vardefs_tab(struct td_inst_t *tdip)
{
 int32 obytsiz, nbytsiz;

 obytsiz = tdip->siz_td_nets_tab*sizeof(struct tgl_vardef_t *);
 nbytsiz = 2*obytsiz;
 tdip->siz_td_nets_tab  = 2*tdip->siz_td_nets_tab;
 tdip->netvardefs = (struct tgl_vardef_t **)
  __my_realloc(tdip->netvardefs, obytsiz, nbytsiz); 
}

/*
 * merge tgldat data from 2nd file net list into first (which is reference
 * to use properties from) when know tgl vardef records same net
 * return T if merging made a change 
 *
 * silently ignores diffrent ranges if widths same (uses first ignores 2nd)
 * assumes file and lin cnt context set by caller
 */
extern int32 __merge_tgldat_toggle_state(struct tgl_vardef_t *tvdp1,
 struct tgl_vardef_t *tvdp2)
{
 int32 vdi, changed;

 changed = FALSE;
 /* if first short, just stop when all of old which is result merged in */
 /* extra at end of 2nd just ignored */ 
 /* SJM 11-02-13 - here working from low bit (right most in list but moved */
 /* to array so index 0 because need messages for one shorter */
 for (vdi = 0; vdi < tvdp1->nbits; vdi++)
  {
   /* new short so done - no more merging - i.e. rest of old unchanged */
   if (vdi >= tvdp2->nbits) { changed = TRUE; break; }

   /* case 1:, both same - nothing to do */
   if ((tvdp1->tglcnt_01[vdi] == tvdp2->tglcnt_01[vdi])
    && (tvdp1->tglcnt_10[vdi] == tvdp2->tglcnt_10[vdi])) continue;
   /* if new excluded, leave old - know both 0->1 and 1->0 will be excluded */
   /* excluded is '?' in strings but -1 in tglcnt arrays - needed when add */
   /* real tgl counting */
   if (tvdp2->tglcnt_01[vdi] == -1) continue;

   changed = TRUE; 
   /* case 2: if old exclude but not new, use new values */
   if (tvdp1->tglcnt_01[vdi] == -1) 
    {
     /* if old (first) excluded but not new (second) - copy new into old */ 
     tvdp1->tglcnt_01[vdi] = tvdp2->tglcnt_01[vdi];
     tvdp1->tglcnt_10[vdi] = tvdp2->tglcnt_10[vdi];
    }
   /* case 3: 2nd but not 1st driven const (C) - emit warn - use 1st */
   /* know both not same to get here */
   /* driven const 'C' in strings but -2 in tglcnt arrays - needed when add */
   /* real tgl counting */
   /* SJM 10-11-13 - LOOKATME - maybe this should turn off driven const */ 
   if (tvdp1->tglcnt_01[vdi] == -2)
    {
     __pv_fwarn(53,
      "tgldat rooted path %s in mod %s inst %s net %s current driven to constant but not previous - leaving driven const",
      tvdp1->rtpthnam, tvdp1->in_modnam, tvdp1->in_instnam, tvdp1->netnam);
     continue;
    }
   /* case 4: 1st2nd but not first driven const (C) - emit warn - use first */
   if (tvdp2->tglcnt_01[vdi] == -2)
    {
     __pv_fwarn(53,
      "tgldat rooted path %s in mod %s inst %s net %s previous driven to constant but not current - ignoring previous",
      tvdp2->rtpthnam, tvdp2->in_modnam, tvdp2->in_instnam, tvdp2->netnam);
     continue;
    }
   /* case 5: merge - know neither excluded or driven const */
   if (tvdp2->tglcnt_01[vdi] == 1) tvdp1->tglcnt_01[vdi] = 1;
   if (tvdp2->tglcnt_10[vdi] == 1) tvdp1->tglcnt_10[vdi] = 1;
  }
 return(changed);
}

/*
 * ROUTINES TO WRITE .TGLDAT RECORDS FROM INTERNAL TGLDAT D.S.
 */

/*
 * write a tlgdat file line from a tglvardef record
 * 
 * .tgldat line format is: [module in] : [rooted path] [<r1>:<r2>] {...} {...};
 *
 *  for scalar range is [] else range from net declaration
 *  for narrow both 0->1 and 1->0 {...} toggle lists on same line
 *  for wide first 0->1 tgl list on next line, then 1->0 on next next
 *  {...} list is comma separated list of 0 (not tgl), 1 {tgl},
 *  ? {excluded from tgl coverage}, C {can't tgl because either directly or
 *    indirectly driven to a constant or supply value
 */
extern void __wr_one_tgldat_line_from_tglvardef(FILE *fp,
 struct tgl_vardef_t *tvdp)
{
 int32 bi;
 char v01str[RECLEN], v10str[RECLEN];

 fprintf(fp, "%s : %s ", tvdp->in_modnam, tvdp->rtpthnam);
 if (tvdp->rng1 == -1) fprintf(fp, "[]");
 else fprintf(fp, "[%d:%d]", tvdp->rng1, tvdp->rng2); 
 if (tvdp->nbits > 32)
  {
   fputs("\n", fp);
   fprintf(fp, "{%s", __to_val(v01str, tvdp->tglcnt_01[tvdp->nbits - 1]));
   /* order is always h:0 even if range differs internal and written same */
   /* SJM 11-02-13 - h:0 means that high bit must be written first because */
   /* h:0 convention is high bit left most in list and low bit right most */
   for (bi = tvdp->nbits - 2; bi >= 0; bi--)
    {
     fprintf(fp, ",%s", __to_val(v01str, tvdp->tglcnt_01[bi]));
    }
   fprintf(fp, "}\n{%s", __to_val(v10str, tvdp->tglcnt_10[tvdp->nbits - 1]));
   for (bi = tvdp->nbits - 2; bi >= 0; bi--)
    {
     fprintf(fp, ",%s", __to_val(v10str, tvdp->tglcnt_10[bi]));
    }
   fputs("};\n", fp);
  }
 else
  {
   /* this works for scalar too */
   fprintf(fp, " {%s", __to_val(v01str, tvdp->tglcnt_01[tvdp->nbits - 1]));
   /* order is always h:0 even if range differs internal and written same */
   for (bi = tvdp->nbits - 2; bi >= 0; bi--)
    {
     fprintf(fp, ",%s", __to_val(v01str, tvdp->tglcnt_01[bi]));
    }
   fprintf(fp, "} {%s", __to_val(v10str, tvdp->tglcnt_10[tvdp->nbits - 1]));
   for (bi = tvdp->nbits - 2; bi >= 0; bi--)
    {
     fprintf(fp, ",%s", __to_val(v10str, tvdp->tglcnt_10[bi]));
    }
   fputs("};\n", fp);
  }
}

/*
 * convert an internal toggle value: 0, 1, -1 (?), -2 (C) to a string
 */
extern char *__to_val(char *s1, int32 tglval)
{
 if (tglval == -1) strcpy(s1, "?");
 else if (tglval == -2) strcpy(s1, "C");
 else sprintf(s1, "%d", tglval);
 return(s1);
}

/*
 * copy from a net list d.s. into a root path sorted var def list 
 *
 * orignal list cross linked - caller can free list after here
 */
extern struct tgl_vardef_t * __bld_sort_td_vardefs(struct td_netlist_t *nlp)
{
 int32 mi, ii, ni, num_vardefs;
 struct tgl_vardef_t *tvd_hd, *tvd_tail, *tvdp, *tvdp2, *tvdp3;
 struct td_mod_t *tdmdp;
 struct td_inst_t *tdip;
 struct tgl_vardef_t **tvdvardef_ndx;

 /* mods that have toggle net data in them - not excluded and has nets */
 tvd_hd = tvd_tail = NULL;
 num_vardefs = 0;
 for (mi = 0; mi < nlp->num_td_mods; mi++)
  {
   tdmdp = nlp->nlmods[mi];
   for (ii = 0; ii < tdmdp->num_td_instsof; ii++)
    {
     tdip = tdmdp->td_instsof[ii];
     for (ni = 0; ni < tdip->td_num_nets; ni++)
      {
       /* DBG remove ===
       {
        struct tgl_vardef_t *tvdp4;
 
        tvdp4 = tdip->netvardefs[ni]; 
        Msg(" +++:  mod (%d):%s or %s inst (%d):%s net (%d):%s full path %s.\n",
         mi, tdmdp->modnam, tvdp4->in_modnam, ii, tvdp4->in_instnam, ni,
         tvdp4->netnam, tvdp4->rtpthnam);
       }
       === */

       /* leave original vardef in net list - can be freed when all of */
       /* net list freed */
       tvdp = __copy_alloc_td_vardef(tdip->netvardefs[ni]);

       if (tvd_hd == NULL) tvd_hd = tvd_tail = tvdp;
       else { tvd_tail->tglvdnxt = tvdp; tvd_tail = tvdp; }
       num_vardefs++;
      }
    }
  }
 /* now sort into rooted path order */
 tvdvardef_ndx = (struct tgl_vardef_t **)
  __my_malloc(num_vardefs*sizeof(struct tgl_vardef_t *));
 for (ni = 0, tvdp2 = tvd_hd; tvdp2 != NULL; ni++)
  {
   tvdp3 = tvdp2->tglvdnxt;
   tvdvardef_ndx[ni] = tvdp2;
   tvdp2 = tvdp3;
  }
 /* DBG remove ==
 for (ni = 0; ni < num_vardefs; ni++)
  {
   Msg(" +++%d:  path %s.\n", ni, tvdvardef_ndx[ni]->rtpthnam);
  }
 == */
 /* sort to fully qualified rooted path name order */
 qsort(tvdvardef_ndx, num_vardefs, sizeof(struct tgl_vardef_t *),
  rtpthnam_cmp);

 /* DBG remove ==
 for (ni = 0; ni < num_vardefs; ni++)
  {
   Msg(" +++ AFTER sort (%d):  path %s.\n", ni, tvdvardef_ndx[ni]->rtpthnam);
  }
 == */

 /* rebild the list */
 tvd_hd = tvd_tail = NULL;
 for (ni = 0; ni < num_vardefs; ni++)
  {
   tvdp2 = tvdvardef_ndx[ni];
   if (tvd_hd == NULL) tvd_hd = tvd_tail = tvdp2;
   else { tvd_tail->tglvdnxt = tvdp2; tvd_tail = tvdp2; }
  }
 tvd_tail->tglvdnxt = NULL; 
 /* DBG remove ==== 
 {
  struct tgl_vardef_t *tvdp2;

  for (tvdp2 = tvd_hd; tvdp2 != NULL; tvdp2 = tvdp2->tglvdnxt)
   {
    Msg(" +++ AFTER sort (%d):  path %s.\n", ni, tvdp2->rtpthnam);
   }
 }
 ==== */

 /* free the ndx tab */
 __my_free(tvdvardef_ndx, num_vardefs*sizeof(struct tgl_vardef_t *));

 return(tvd_hd);
}

/*
 * module port name comparison routine
 */
static int32 rtpthnam_cmp(const void *tvdp1, const void *tvdp2)
{
 return(strcmp((*((struct tgl_vardef_t **) tvdp1))->rtpthnam,
  (*(struct tgl_vardef_t **) tvdp2)->rtpthnam));
}
 

/*
 * copy a tgldat vardef into a newly allocated one - can free old after copy
 */
static struct tgl_vardef_t *__copy_alloc_td_vardef(struct tgl_vardef_t *otvdp)
{
 int32 bi;
 struct tgl_vardef_t *ntvdp;

 ntvdp = (struct tgl_vardef_t *) __my_malloc(sizeof(struct tgl_vardef_t));
 /* think do not really need to initialize */
 init_tgl_vardef(ntvdp);

 ntvdp->rtpthnam = __my_stralloc(otvdp->rtpthnam);
 ntvdp->in_modnam = __my_stralloc(otvdp->in_modnam);
 ntvdp->in_instnam = __my_stralloc(otvdp->in_instnam);
 ntvdp->netnam = __my_stralloc(otvdp->netnam);
 /* this is string with ending \0 but maybe not used */
 if (otvdp->dvcod != NULL) ntvdp->dvcod = __my_stralloc(otvdp->dvcod);
 ntvdp->nbits = otvdp->nbits;
 ntvdp->rng1 = otvdp->rng1;
 ntvdp->rng2 = otvdp->rng2;
 ntvdp->tglcnt_01 = (int32 *) __my_malloc(otvdp->nbits*sizeof(int32));
 ntvdp->tglcnt_10 = (int32 *) __my_malloc(otvdp->nbits*sizeof(int32));
 for (bi = 0; bi < otvdp->nbits; bi++) 
  {
   ntvdp->tglcnt_01[bi] = otvdp->tglcnt_01[bi];
   ntvdp->tglcnt_10[bi] = otvdp->tglcnt_10[bi];
  }
 ntvdp->vardef_lcnt = otvdp->vardef_lcnt;
 /* caller must link in if needed */
 ntvdp->tglvdnxt = NULL;

 return (ntvdp);
} 

/*
 * free net list mod-inst-net vardef state d.s but not the list of vardefs
 */
extern void __free_netlist(struct td_netlist_t *nlp)
{
 int32 mi;

 for (mi = 0; mi < nlp->num_td_mods; mi++) 
  {
   __free_one_nl_mod(nlp->nlmods[mi]);
   nlp->nlmods[mi] = NULL;
  }
 __my_free(nlp->nlmods, nlp->siz_td_mods_tab*sizeof(struct td_mod_t *));
 __my_free(nlp->netlist_fnam, strlen(nlp->netlist_fnam) + 1);
}

/*
 * free one nl mod
 */
extern void __free_one_nl_mod(struct td_mod_t *tdmdp)
{
 int32 ii;
 __my_free(tdmdp->modnam, strlen(tdmdp->modnam) + 1);
  for (ii = 0; ii < tdmdp->num_td_instsof; ii++)
   {
    __free_one_nl_instof(tdmdp->td_instsof[ii]);
    tdmdp->td_instsof[ii] = NULL; 
   }
 __my_free(tdmdp->td_instsof,
   tdmdp->siz_td_instsof_tab*sizeof(struct td_inst_t *));
}

/*
 * free one nl instof
 */
extern void __free_one_nl_instof(struct td_inst_t *tdip)
{
 int32 ni;

 __my_free(tdip->irtpthnam, strlen(tdip->irtpthnam) + 1);
  for (ni = 0; ni < tdip->td_num_nets; ni++)
   {
    __free_tgl_vardef(tdip->netvardefs[ni]);
    tdip->netvardefs[ni] = NULL; 
   }
 __my_free(tdip->netvardefs,
   tdip->siz_td_nets_tab*sizeof(struct td_vardef_t *));
}

/*
 * free a tgl var def linked list
 *
 * usually called before rebuilt
 */
extern void __free_list_of_tgl_vardef(struct tgl_vardef_t *tvd_hd)
{
 struct tgl_vardef_t *tvdp, *tvdp2;

 for (tvdp = tvd_hd; tvdp != NULL;)
  {
   tvdp2 = tvdp->tglvdnxt;
   __free_tgl_vardef(tvdp);
   tvdp = tvdp2;
  }
}

/*
 * free a tgl vardef record
 */
extern void __free_tgl_vardef(struct tgl_vardef_t *tvdp)
{
 __my_free(tvdp->rtpthnam, strlen(tvdp->rtpthnam) + 1);
 tvdp->rtpthnam = NULL;
 __my_free(tvdp->in_modnam, strlen(tvdp->in_modnam) + 1);
 tvdp->in_modnam = NULL;
 __my_free(tvdp->in_instnam, strlen(tvdp->in_instnam) + 1);
 tvdp->in_instnam = NULL;
 __my_free(tvdp->netnam, strlen(tvdp->netnam) + 1);
 tvdp->netnam = NULL;
 if (tvdp->dvcod != NULL) __my_free(tvdp->dvcod, strlen(tvdp->dvcod) + 1);
 tvdp->dvcod = NULL;
 __my_free(tvdp->tglcnt_01, tvdp->nbits*sizeof(int32));
 tvdp->tglcnt_01 = NULL;
 __my_free(tvdp->tglcnt_10, tvdp->nbits*sizeof(int32));
 tvdp->tglcnt_10 = NULL;
 tvdp->tglvdnxt = NULL;
 /* finally free the vardef record itself */
 __my_free(tvdp, sizeof(struct tgl_vardef_t));
}

/*
 * VARDEF NET LIST DEBUGGING DUMP ROUTINES
 */

/*
 * for debugging dump one net list (all mods in one file)
 */
extern void __dbg_dump_one_netlist(struct td_netlist_t *nlp)
{
 int32 mi;
 char s1[RECLEN];

 if (nlp->netlist_fnam != NULL) strcpy(s1, nlp->netlist_fnam);
 else strcpy(s1, "");
 Msg("\n >>> TGL FILE %s NET LIST: %d mods (tab size %d)\n",
  s1, nlp->num_td_mods, nlp->siz_td_mods_tab);

 for (mi = 0; mi < nlp->num_td_mods; mi++)
  {
   __dbg_dump_one_mod(nlp->nlmods[mi]);
  }
 Msg("**** END OF NET LIST FILE %s ****\n\n", s1);
}

/*
 * for debugging dump one mod and its insts
 */
extern void __dbg_dump_one_mod(struct td_mod_t *tdmdp)
{
 int32 ii;

 Msg("\n TGL MOD: %s (insts %d of tab size %d)\n",
  tdmdp->modnam, tdmdp->num_td_instsof, tdmdp->siz_td_instsof_tab);
 for (ii = 0; ii < tdmdp->num_td_instsof; ii++)
  {
   __dbg_dump_one_inst(tdmdp->td_instsof[ii]);
  }
  /* SJM 10-21-13 - only dump first */
  __dbg_dump_one_inst(tdmdp->td_instsof[0]);
 Msg("**** END OF MOD %s ****\n\n", tdmdp->modnam); 
}

/*
 * for debugging dump one inst and its nets
 */
extern void __dbg_dump_one_inst(struct td_inst_t *tdip)
{ 
 int32 ii;

 Msg(" TGL INST: %s (nets %d of tab size %d)\n", tdip->irtpthnam,
  tdip->td_num_nets, tdip->siz_td_nets_tab);
 for (ii = 0; ii < tdip->td_num_nets; ii++) 
  { 
   __dbg_dump_one_1vardef(tdip->netvardefs[ii]);
  }
}

/*
 * for debugging dump one var def net list info
 *
 * tgldat merge to write the toggle state lists
 */
extern void __dbg_dump_one_1vardef(struct tgl_vardef_t *tvdp)
{
 char s1[RECLEN];

 if (tvdp->rng1 == -1) strcpy(s1, "");
 else sprintf(s1, "[%d:%d]", tvdp->rng1, tvdp->rng2);

 /* write to stdout with my printf also goes to log file */
 Msg("  ++ TGL VARDEF net %s%s in inst %s in mod %s width %d\n",
  tvdp->netnam, s1, tvdp->in_instnam, tvdp->in_modnam, tvdp->nbits);
}

/*
 * for debugging dump one var def net list info
 *
 * tgldat merge to write the toggle state lists
 */
extern void __dbg_dump_1vardef(struct tgl_vardef_t *tvdp)
{
 char s1[RECLEN];

 if (tvdp->rng1 == -1) strcpy(s1, "");
 else sprintf(s1, "[%d:%d]", tvdp->rng1, tvdp->rng2);

 /* write to stdout with my printf also goes to log file */
 Msg("  ++ TGL VARDEF net %s%s in inst %s in mod %s width %d\n",
  tvdp->netnam, s1, tvdp->in_instnam, tvdp->in_modnam, tvdp->nbits);
}

/* 
 * WRAPPERS TO SYSTEM ROUTINES
 */

/*
 * allocate a string 
 */
extern char *__my_stralloc(char *s)
{
 int32 slen;
 char *cp;

 if (*s == '\0') slen = 1; else slen = strlen(s) + 1;
 cp = __my_malloc(slen);
 /* this just copies '\0' for "" case */
 strcpy(cp, s);
 return(cp);
}

/*
 * my wrapper to malloc that dies if no memory available
 * normal OS memory allocation with error terminaton
 */
extern char *__my_malloc(size_t size)
{
 char *cp;

 if ((cp = (char *) malloc(size)) == NULL)
  {
   __terr(2, "No more memory");
  }
 return(cp);
}

/*
 * my wrapper to system realloc()
 * can only call with malloced mp or cannot realloc
 */
extern char *__my_realloc(void *mp, size_t osize, size_t nsize)
{
 void *cp;

 if ((cp = realloc(mp, nsize)) == NULL)
  {
   __terr(3, "realloc failed");
  }
 return(cp);
}

/*
 * my wrapper to free
 */
extern void __my_free(void *mp, size_t size)
{
 /* DBG remove --- 
 if (size <= 0) return;
  --- */
 free(mp);
}

/*VARARGS*/
extern void __warn(int32 id_num, char *s, ...)
{
 va_list va2, va3;

 __my_fprintf(stdout, "** WARN** [%d] ", id_num);

 /* SJM 10/13/99 - ansii std says varargs not usable after vprintf called */
 va_start(va2, s);
 va_start(va3, s);
 __my_vfprintf(stdout, s, va2, va3);
 va_end(va2);
 va_end(va3);
 __my_putc('\n', stdout);
}

/*VARARGS*/
extern void __pv_fwarn(int32 id_num, char *s, ...)
{
 va_list va2, va3;

 __my_fprintf(stdout, "**%s(%d) WARN** [%d] ", __cur_fnam, __lin_cnt, id_num);

 /* SJM 10/13/99 - ansii std says varargs not usable after vprintf called */
 va_start(va2, s);
 va_start(va3, s);
 __my_vfprintf(stdout, s, va2, va3);
 va_end(va2);
 va_end(va3);
 __my_putc('\n', stdout);
}

/*
 * error with fatal termination
 * arg s is a format specification string for sprintf
 *
 * notice error messages longer than 4k bytes will cause crash
 * caller of error routines must make sure no more than 4 ID called
 */
extern void __terr(int32 id_num, char *s, ...)
{
 va_list va, va2;

 Msg("**FATAL ERROR** [%d] ", id_num);
 va_start(va, s);
 vprintf(s, va);
 va_end(va);
 if (__log_s != NULL)
  {
   va_start(va2, s);
   vfprintf(__log_s, s, va2);  
   va_end(va2);
  }
 Msg("\n");
 exit(1);
}

/*
 * error with fatal termination and file/line location
 */
extern void __pv_terr(int32 id_num, char *s, ...)
{
 va_list va, va2;

 Msg("**%s(%d) FATAL ERROR** [%d] ", __cur_fnam, __lin_cnt, id_num);
 va_start(va, s);
 vprintf(s, va);
 va_end(va);
 if (__log_s != NULL)
  {
   va_start(va2, s);
   vfprintf(__log_s, s, va2);  
   va_end(va2);
  }
 Msg("\n");
 exit(1);
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
 * my fprintf - normal fprintf except if f is stdout then also to log file
 */
extern void Msg(char *s, ...)
{
 va_list va, va2;

 va_start(va, s);
 vfprintf(stdout, s, va);
 va_end(va);
 if (__log_s != NULL)
  {
   va_start(va2, s);
   vfprintf(__log_s, s, va2);
   va_end(va2);
  }
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

/*
 * putc to both stdout and log file
 */
extern int32 __my_putc(int32 c, FILE *f)
{
 fputc(c, f);
 if (f == stdout && __log_s != NULL) fputc(c, __log_s);
 return(c);
}
