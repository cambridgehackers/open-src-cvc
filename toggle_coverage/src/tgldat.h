/* includes for tvcd_to_tgl_dat program */

/* if need 64 bit version put in the ifdef */
typedef int int32;
/* for 64 bit should ifdef these */
typedef unsigned long long word64;
typedef unsigned long word32;

#define TRUE 1
#define FALSE 0
#define MAXSCOPES 4096        /* max scope depth */
#define IDLEN 1025            /* LRM max ID in Verilog is 1024 chars */
#define RECLEN 4096
#define MAXRTPATH 65536       /* max rooted path length */
#define MAXTGLVECSIZ 65536    /* max allow net vector width for this checker */

/* var types */
#define UNDEFINED 0
#define EVENT 1
#define INTEGER 2
#define REAL 3
#define REG 4
#define SUPPLY0 5
#define SUPPLY1 6
#define TIME 7
#define TRI 8
#define TRI0 9  
#define TRI1 10
#define TRIAND 11
#define TRIOR 12
#define TRIREG 13
#define WAND 14
#define WIRE 15
#define WOR 16
/* SV 2-state types */
#define INT 17
#define LONGINT 18
#define SHORTINT 19
#define BYTE 20
#define BIT 21
#define LOGIC 22
#define CHANDLE 23

/* value change dump (VCD) file keywords - .tvcd file uses unchanged */
#define VCD_COMMENT 0
#define VCD_DATE 1 
#define VCD_DUMPVARS 2 
#define VCD_END  3 
#define VCD_ENDDEF  4
#define VCD_SCOPE    5
#define VCD_TIMESCALE 6
#define VCD_UPSCOPE  7
#define VCD_VAR    8
#define VCD_VERSION  9

/* keyword and corresponding int */
struct keyword_t {
 char *vnam;
 int vnum;
};

/* net (var) tgl info - one per line of .tgldat file - var def of tgl state */
struct tgl_vardef_t {
 char *rtpthnam;              /* fully qualified rooted path name to tgl var */
 char *in_modnam;             /* mod type name net in in */
 char *in_instnam;            /* inst (one back from net name rt pth end */ 
 char *netnam;                /* inst (one back from net name rt pth end */ 
 char *dvcod;                 /* base 93 vcd dumpvars code */
 int nbits;                   /* width of net from tvcd file */
 int rng1;                    /* first of range (-1 for scalar) */
 int rng2;                     /* msb (2nd) of range */
 int32 *tglcnt_01;            /* ptr to per bit array of 0->1 toggle state */
 int32 *tglcnt_10;            /* and 1-0 state */
 int vardef_lcnt;             /* location of var def for this toggle */
 struct tgl_vardef_t *tglvdnxt;/* next if building list */
}; 

/* for each inst of record, the tab of ptrs to per net var def records */
struct td_inst_t {
 char *irtpthnam;             /* fully qualified rooted path name */
 /* key if more than one mod/inst-in/net vardef, combined on d.s bld */
 struct  tgl_vardef_t **netvardefs; /* one vardef per mod-instof-net */
 int32 td_num_nets;           /* num of all vardef (rooted paths) of net */
 int32 siz_td_nets_tab;       /* size of var def tab - grows */
};

/* one mod record containging tab of ptrs to instances of the mod */
struct td_mod_t {
 char *modnam;                /* name of mod */ 
 /* for every different rooted hierarchical path in .tgldat file */
 /* there will be one inst of with different */
 struct td_inst_t **td_instsof;/* for each inst ptr to one vardef */ 
 int32 num_td_instsof;        /* number of insts of this mod */
 int32 siz_td_instsof_tab;    /* size of insts of ptr tab - grows*/
};

/* per .tgldat file net list header record */
struct td_netlist_t {
 struct td_mod_t **nlmods;    /* for this nl, ptr to tab of ptrs to mods */
 int32 num_td_mods;           /* number of mods in tgldat file (design) */  
 int32 siz_td_mods_tab;       /* current size of mod ptr tab - grows */
 struct  tgl_vardef_t *nl_tvd_hd; /* head of read list of file tgldat lines */
 char *netlist_fnam;          /* name of file, net list (rtpth vd file) from */
};

/* externs vars usable in any file */
extern char __token[RECLEN]; 
extern struct tgl_vardef_t **__tglvardefs;
extern int32 __last_tglvardef;/* last ndx of tgl var defs - num + 1 */
extern int32 __alloc_siz_tglvardefs;
extern char *__tglbits01;     /* for init from .tgldat file 01 list */
extern char *__tglbits10;     /* 10 list */
extern int32 __siz_tgl_lst;   /* current alloc size of list */
extern char *__tgl_modnam;    /* name of module for tgl net line */
extern char *__tgl_rtpthnam;  /* for init from .tgldat line rooted path */ 
extern int32 __siz_tgl_rtpthnam;/* and alloc size */
extern int32 *__tgl01tab;     /* tgl net's per bit toggle count tabs */ 
extern int32 *__tgl10tab;
extern int32 __tgl_r1;        /* first tgldat line range */
extern int32 __tgl_r2;        /* 2nd tgldat line range */
extern char **__scopnam_stk; 
extern char **__scopmdnam_stk; 
extern int32 __top_scopei;
extern int32 __siz_scope_stk;
extern char *__tgldat_pthcmps[MAXSCOPES];  /* tab of malloc pth comp strings */
extern int32 __last_tdpthi;   /* last used for current tgldat net line */ 
extern int32 __ix_insert;     /* for binary srch procs, place to insert */
extern struct td_netlist_t *__file_netlist; /* hdr of .tgldat vardefs d.s. */
extern int32 __emit_dup_rtpth_warn;/* flag on to emit td dup tgl line warns */

extern char __in_tvcd_fnam[RECLEN];
extern char __out_tgldat_fnam[RECLEN];
extern char __in_tgldat_fnam[RECLEN];
extern char __tvcd_date[RECLEN];
extern char __tvcd_version[RECLEN];
extern char __tgldat_writer_date[RECLEN];/* possible date string from .tgldat */
extern char __tgldat_writer_vers[RECLEN];/* possible writer info */
extern int32 __verbose;       /* T => print verbose messages */
extern int32 __lin_cnt;       /* current line number reading */
extern char __cur_fnam[RECLEN];
extern char __log_fnam[RECLEN];
extern FILE *__log_s;
