/******************************************************************************
* veriuser.h
*
* IEEE 1364 1995 Verilog HDL Programming Language Interface (PLI).
*
* This file contains the constant definitions, structure definitions, and
* routine declarations used by the Verilog PLI procedural interface TF 
* task/function routines. 
*
* The file should be included with all C routines that use the PLI
* task/function routines.
******************************************************************************/
#ifndef VERIUSER_H
#define VERIUSER_H

/*---------------------------------------------------------------------------*/
/*------------------------------- definitions -------------------------------*/
/*---------------------------------------------------------------------------*/

/*----------------------------- general defines -----------------------------*/
#define bool                   int
#define true                   1
#define TRUE                   1
#define false                  0
#define FALSE                  0
#define null                   0L

/*---------------------- defines for error interception ---------------------*/
#define ERR_MESSAGE            1
#define ERR_WARNING            2
#define ERR_ERROR              3
#define ERR_INTERNAL           4
#define ERR_SYSTEM             5

/*-------------- values for reason parameter to misctf routines -------------*/

#define reason_checktf         1
#define REASON_CHECKTF         reason_checktf
#define reason_sizetf          2
#define REASON_SIZETF          reason_sizetf
#define reason_calltf          3
#define REASON_CALLTF          reason_calltf
#define reason_save            4
#define REASON_SAVE            reason_save
#define reason_restart         5
#define REASON_RESTART         reason_restart
#define reason_disable         6
#define REASON_DISABLE         reason_disable
#define reason_paramvc         7
#define REASON_PARAMVC         reason_paramvc
#define reason_synch           8
#define REASON_SYNCH           reason_synch
#define reason_finish          9
#define REASON_FINISH          reason_finish
#define reason_reactivate     10
#define REASON_REACTIVATE      reason_reactivate
#define reason_rosynch        11
#define REASON_ROSYNCH         reason_rosynch
#define reason_paramdrc       15
#define REASON_PARAMDRC        reason_paramdrc
#define reason_endofcompile   16
#define REASON_ENDOFCOMPILE    reason_endofcompile
#define reason_scope          17
#define REASON_SCOPE          reason_scope
#define reason_interactive    18
#define REASON_INTERACTIVE     reason_interactive
#define reason_reset          19
#define REASON_RESET           reason_reset
#define reason_endofreset     20
#define REASON_ENDOFRESET      reason_endofreset
#define reason_force          21
#define REASON_FORCE           reason_force
#define reason_release        22
#define REASON_RELEASE         reason_release
#define reason_startofsave    27
#define REASON_STARTOFSAVE reason_startofsave
#define reason_startofrestart 28
#define REASON_STARTOFRESTART reason_startofrestart
#define REASON_MAX            28

/*-- types used by tf_typep() and expr_type field in tf_exprinfo structure --*/
#define tf_nullparam           0
#define TF_NULLPARAM           tf_nullparam
#define tf_string              1
#define TF_STRING              tf_string
#define tf_readonly           10
#define TF_READONLY            tf_readonly
#define tf_readwrite          11
#define TF_READWRITE           tf_readwrite
#define tf_rwbitselect        12
#define TF_RWBITSELECT         tf_rwbitselect
#define tf_rwpartselect       13
#define TF_RWPARTSELECT        tf_rwpartselect
#define tf_rwmemselect        14
#define TF_RWMEMSELECT         tf_rwmemselect
#define tf_readonlyreal       15
#define TF_READONLYREAL        tf_readonlyreal
#define tf_readwritereal      16
#define TF_READWRITEREAL       tf_readwritereal

/*---------- types used by node_type field in tf_nodeinfo structure ---------*/
#define tf_null_node         100
#define TF_NULL_NODE           tf_null_node
#define tf_reg_node          101
#define TF_REG_NODE            tf_reg_node
#define tf_integer_node      102
#define TF_INTEGER_NODE        tf_integer_node
#define tf_time_node         103
#define TF_TIME_NODE           tf_time_node
#define tf_netvector_node    104
#define TF_NETVECTOR_NODE      tf_netvector_node
#define tf_netscalar_node    105
#define TF_NETSCALAR_NODE      tf_netscalar_node
#define tf_memory_node       106
#define TF_MEMORY_NODE         tf_memory_node
#define tf_real_node         107
#define TF_REAL_NODE           tf_real_node

/*---------------------------------------------------------------------------*/
/*-------------------------- structure definitions --------------------------*/
/*---------------------------------------------------------------------------*/

/*----- structure used with tf_exprinfo() to get expression information -----*/
typedef struct t_tfexprinfo
{
  short expr_type;
  short padding;
  struct t_vecval *expr_value_p;
  double real_value;
  char *expr_string;
  int expr_ngroups;
  int expr_vec_size;
  int expr_sign;
  int expr_lhs_select; 
  int expr_rhs_select;
} s_tfexprinfo, *p_tfexprinfo;

/*------- structure for use with tf_nodeinfo() to get node information ------*/
typedef struct t_tfnodeinfo
{
  short node_type;
  short padding;
  union
    {
      struct t_vecval *vecval_p;
      struct t_strengthval *strengthval_p;
      char *memoryval_p;
      double *real_val_p;
    } node_value;
  char *node_symbol;
  int node_ngroups;
  int node_vec_size;
  int node_sign;
  int node_ms_index;
  int node_ls_index;
  int node_mem_size;
  int node_lhs_element;
  int node_rhs_element;
  int *node_handle;
} s_tfnodeinfo, *p_tfnodeinfo;

/*--------------------- data structure of vector values ---------------------*/
typedef struct t_vecval
{
  int avalbits;
  int bvalbits;
} s_vecval, *p_vecval;

/*--------------- data structure of scalar net strength values --------------*/
typedef struct t_strengthval
{
    int strength0;
    int strength1;
} s_strengthval, *p_strengthval;

/*---------------------------------------------------------------------------*/
/*--------------------------- routine definitions ---------------------------*/
/*---------------------------------------------------------------------------*/
#if defined(__STDC__) || defined(__cplusplus)

#ifndef PROTO_PARAMS
#define PROTO_PARAMS(params) params
#define DEFINED_PROTO_PARAMS
#endif
#ifndef EXTERN
#define EXTERN
#define DEFINED_EXTERN
#endif

#else

#ifndef PROTO_PARAMS
#define PROTO_PARAMS(params) (/* nothing */)
#define DEFINED_PROTO_PARAMS
#endif
#ifndef EXTERN
#define EXTERN extern
#define DEFINED_EXTERN
#endif

#endif /* __STDC__ */

EXTERN void         io_mcdprintf PROTO_PARAMS((int mcd, char *format, ...));
EXTERN void         io_printf PROTO_PARAMS((char *format, ...));
EXTERN char        *mc_scan_plusargs PROTO_PARAMS((char *plusarg));
EXTERN void         tf_add_long PROTO_PARAMS((int *aof_lowtime1, int *aof_hightime1, int lowtime2, int hightime2));
EXTERN int          tf_asynchoff PROTO_PARAMS((void));
EXTERN int          tf_asynchon PROTO_PARAMS((void));
EXTERN int          tf_clearalldelays PROTO_PARAMS((void));
EXTERN int          tf_compare_long PROTO_PARAMS((unsigned int low1, unsigned int high1, unsigned int low2, unsigned int high2));
EXTERN int          tf_copypvc_flag PROTO_PARAMS((int nparam));
EXTERN void         tf_divide_long PROTO_PARAMS((int *aof_low1, int *aof_high1, int low2, int high2));
EXTERN int          tf_dofinish PROTO_PARAMS((void));
EXTERN int          tf_dostop PROTO_PARAMS((void));
EXTERN int          tf_error PROTO_PARAMS((char *fmt, ...));
EXTERN int          tf_evaluatep PROTO_PARAMS((int pnum));
EXTERN p_tfexprinfo tf_exprinfo PROTO_PARAMS((int pnum, p_tfexprinfo pinfo));
EXTERN char        *tf_getcstringp PROTO_PARAMS((int nparam));
EXTERN char        *tf_getinstance PROTO_PARAMS((void));
EXTERN int          tf_getlongp PROTO_PARAMS((int *aof_highvalue, int pnum));
EXTERN int          tf_getlongtime PROTO_PARAMS((int *aof_hightime));
EXTERN int          tf_getnextlongtime PROTO_PARAMS((int *aof_lowtime, int *aof_hightime));
EXTERN int          tf_getp PROTO_PARAMS((int pnum));
EXTERN int          tf_getpchange PROTO_PARAMS((int nparam));
EXTERN double       tf_getrealp PROTO_PARAMS((int pnum));
EXTERN double       tf_getrealtime PROTO_PARAMS((void));
EXTERN int          tf_gettime PROTO_PARAMS((void));
EXTERN int          tf_gettimeprecision PROTO_PARAMS((void));
EXTERN int          tf_gettimeunit PROTO_PARAMS((void));
EXTERN char        *tf_getworkarea PROTO_PARAMS((void));
EXTERN int          tf_iasynchoff PROTO_PARAMS((char *inst));
EXTERN int          tf_iasynchon PROTO_PARAMS((char *inst));
EXTERN int          tf_iclearalldelays PROTO_PARAMS((char *inst));
EXTERN int          tf_icopypvc_flag PROTO_PARAMS((int nparam, char *inst));
EXTERN int          tf_ievaluatep PROTO_PARAMS((int pnum, char *inst));
EXTERN p_tfexprinfo tf_iexprinfo PROTO_PARAMS((int pnum, p_tfexprinfo pinfo, char *inst));
EXTERN char        *tf_igetcstringp PROTO_PARAMS((int nparam, char *inst));
EXTERN int          tf_igetlongp PROTO_PARAMS((int *aof_highvalue, int pnum, char *inst));
EXTERN int          tf_igetlongtime PROTO_PARAMS((int *aof_hightime, char *inst));
EXTERN int          tf_igetp PROTO_PARAMS((int pnum, char *inst));
EXTERN int          tf_igetpchange PROTO_PARAMS((int nparam, char *inst));
EXTERN double       tf_igetrealp PROTO_PARAMS((int pnum, char *inst));
EXTERN double       tf_igetrealtime PROTO_PARAMS((char *inst));
EXTERN int          tf_igettime PROTO_PARAMS((char *inst));
EXTERN int          tf_igettimeprecision PROTO_PARAMS((char *inst));
EXTERN int          tf_igettimeunit PROTO_PARAMS((char *inst));
EXTERN char        *tf_igetworkarea PROTO_PARAMS((char *inst));
EXTERN char        *tf_imipname PROTO_PARAMS((char *cell));
EXTERN int          tf_imovepvc_flag PROTO_PARAMS((int nparam, char *inst));
EXTERN p_tfnodeinfo tf_inodeinfo PROTO_PARAMS((int pnum, p_tfnodeinfo pinfo, char *inst));
EXTERN int          tf_inump PROTO_PARAMS((char *inst));
EXTERN int          tf_ipropagatep PROTO_PARAMS((int pnum, char *inst));
EXTERN int          tf_iputlongp PROTO_PARAMS((int pnum, int lowvalue, int highvalue, char *inst));
EXTERN int          tf_iputp PROTO_PARAMS((int pnum, int value, char *inst));
EXTERN int          tf_iputrealp PROTO_PARAMS((int pnum, double value, char *inst));
EXTERN int          tf_irosynchronize PROTO_PARAMS((char *inst));
EXTERN int          tf_isetdelay PROTO_PARAMS((int delay, char *inst));
EXTERN int          tf_isetlongdelay PROTO_PARAMS((int lowdelay, int highdelay, char *inst));
EXTERN int          tf_isetrealdelay PROTO_PARAMS((double realdelay, char *inst));
EXTERN int          tf_isizep PROTO_PARAMS((int pnum, char *inst));
EXTERN char        *tf_ispname PROTO_PARAMS((char *cell));
EXTERN int          tf_istrdelputp PROTO_PARAMS((int nparam, int bitlength, int format_char, char *value_p, int delay, int delaytype, char *inst));
EXTERN char        *tf_istrgetp PROTO_PARAMS((int pnum, int format_char, char *inst));
EXTERN int          tf_istrlongdelputp PROTO_PARAMS((int nparam, int bitlength, int format_char, char *value_p, int lowdelay, int highdelay, int delaytype, char *inst));
EXTERN int          tf_istrrealdelputp PROTO_PARAMS((int nparam, int bitlength, int format_char, char *value_p, double realdelay, int delaytype, char *inst));
EXTERN int          tf_isynchronize PROTO_PARAMS((char *inst));
EXTERN int          tf_itestpvc_flag PROTO_PARAMS((int nparam, char *inst));
EXTERN int          tf_itypep PROTO_PARAMS((int pnum, char *inst));
EXTERN void         tf_long_to_real PROTO_PARAMS((int int_lo, int int_hi, double *aof_real));
EXTERN char         *tf_longtime_tostr PROTO_PARAMS((int lowtime, int hightime));
EXTERN int          tf_message PROTO_PARAMS((int level, char *facility, char *messno, char *message, ...));
EXTERN char        *tf_mipname PROTO_PARAMS((void));
EXTERN int          tf_movepvc_flag PROTO_PARAMS((int nparam));
EXTERN void         tf_multiply_long PROTO_PARAMS((int *aof_low1, int *aof_high1, int low2, int high2));
EXTERN p_tfnodeinfo tf_nodeinfo PROTO_PARAMS((int pnum, p_tfnodeinfo pinfo));
EXTERN int          tf_nump PROTO_PARAMS((void));
EXTERN int          tf_propagatep PROTO_PARAMS((int pnum));
EXTERN int          tf_putlongp PROTO_PARAMS((int pnum, int lowvalue, int highvalue));
EXTERN int          tf_putp PROTO_PARAMS((int pnum, int value));
EXTERN int          tf_putrealp PROTO_PARAMS((int pnum, double value));
EXTERN int          tf_read_restart PROTO_PARAMS((char *blockptr, int blocklen));
EXTERN void         tf_real_to_long PROTO_PARAMS((double real, int *aof_int_lo, int *aof_int_hi));
EXTERN int          tf_rosynchronize PROTO_PARAMS((void));
EXTERN void         tf_scale_longdelay PROTO_PARAMS((char *cell, int delay_lo, int delay_hi, int *aof_delay_lo, int *aof_delay_hi));
EXTERN void         tf_scale_realdelay PROTO_PARAMS((char *cell, double realdelay, double *aof_realdelay));
EXTERN int          tf_setdelay PROTO_PARAMS((int delay));
EXTERN int          tf_setlongdelay PROTO_PARAMS((int lowdelay, int highdelay));
EXTERN int          tf_setrealdelay PROTO_PARAMS((double realdelay));
EXTERN int          tf_setworkarea PROTO_PARAMS((char *workarea));
EXTERN int          tf_sizep PROTO_PARAMS((int pnum));
EXTERN char        *tf_spname PROTO_PARAMS((void));
EXTERN int          tf_strdelputp PROTO_PARAMS((int nparam, int bitlength, int format_char, char *value_p, int delay, int delaytype));
EXTERN char        *tf_strgetp PROTO_PARAMS((int pnum, int format_char));
EXTERN char        *tf_strgettime PROTO_PARAMS((void));
EXTERN int          tf_strlongdelputp PROTO_PARAMS((int nparam, int bitlength, int format_char, char *value_p, int lowdelay, int highdelay, int delaytype));
EXTERN int          tf_strrealdelputp PROTO_PARAMS((int nparam, int bitlength, int format_char, char *value_p, double realdelay, int delaytype));
EXTERN void         tf_subtract_long PROTO_PARAMS((int *aof_lowtime1, int *aof_hightime1, int lowtime2, int hightime2));
EXTERN int          tf_synchronize PROTO_PARAMS((void));
EXTERN int          tf_testpvc_flag PROTO_PARAMS((int nparam));
EXTERN int          tf_text PROTO_PARAMS((char *fmt, ...));
EXTERN int          tf_typep PROTO_PARAMS((int pnum));
EXTERN void         tf_unscale_longdelay PROTO_PARAMS((char *cell, int delay_lo, int delay_hi, int *aof_delay_lo, int *aof_delay_hi));
EXTERN void         tf_unscale_realdelay PROTO_PARAMS((char *cell, double realdelay, double *aof_realdelay));
EXTERN int          tf_warning PROTO_PARAMS((char *fmt, ...));
EXTERN int          tf_write_save PROTO_PARAMS((char *blockptr, int blocklen));

#ifdef DEFINED_PROTO_PARAMS
#undef DEFINED_PROTO_PARAMS
#undef  PROTO_PARAMS
#endif

#ifdef DEFINED_EXTERN
#undef DEFINED_EXTERN
#undef EXTERN
#endif

#endif /* VERIUSER_H */
