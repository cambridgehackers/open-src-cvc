/******************************************************************************
* acc_user.h
*
* IEEE 1364 1995 Verilog HDL Programming Language Interface (PLI).
*
* This file contains the constant definitions, structure definitions, and
* routine declarations used by the Verilog PLI procedural interface TF 
* task/function routines. 
*
* The file should be included with all C routines that use the PLI ACC
* routines.
******************************************************************************/
#ifndef ACC_USER_H
#define ACC_USER_H

/*---------------------------------------------------------------------------*/
/*------------------------------- definitions -------------------------------*/
/*---------------------------------------------------------------------------*/

/*----------------------------- general defines -----------------------------*/
typedef int    *HANDLE;
typedef int    *handle;

#define bool   int
#define true   1
#define TRUE   1
#define false  0
#define FALSE  0

#define glboal extern
#define exfunc
#define local  static
#define null   0L

/*------------------------------- object types ------------------------------*/
#define    accModule               20
#define    accScope                21
#define    accNet                  25
#define    accReg                  30
#define    accRegister             accReg
#define    accPort                 35
#define    accTerminal             45
#define    accInputTerminal        46
#define    accOutputTerminal       47
#define    accInoutTerminal        48
#define    accCombPrim            140
#define    accSeqPrim             142
#define    accAndGate             144
#define    accNandGate            146
#define    accNorGate             148
#define    accOrGate              150
#define    accXorGate             152
#define    accXnorGate            154
#define    accBufGate             156
#define    accNotGate             158
#define    accBufif0Gate          160
#define    accBufif1Gate          162
#define    accNotif0Gate          164
#define    accNotif1Gate          166
#define    accNmosGate            168
#define    accPmosGate            170
#define    accCmosGate            172
#define    accRnmosGate           174
#define    accRpmosGate           176
#define    accRcmosGate           178
#define    accRtranGate           180
#define    accRtranif0Gate        182
#define    accRtranif1Gate        184
#define    accTranGate            186
#define    accTranif0Gate         188
#define    accTranif1Gate         190
#define    accPullupGate          192
#define    accPulldownGate        194
#define    accIntegerParam        200
#define    accIntParam            accIntegerParam
#define    accRealParam           202
#define    accStringParam         204
#define    accTchk                208
#define    accPrimitive           210
#define    accBit                 212
#define    accPortBit             214
#define    accNetBit              216
#define    accRegBit              218
#define    accParameter           220
#define    accSpecparam           222
#define    accTopModule           224
#define    accModuleInstance      226
#define    accCellInstance        228
#define    accModPath             230
#define    accWirePath            232
#define    accInterModPath        236
#define    accScalarPort          250
#define    accBitSelectPort       252
#define    accPartSelectPort      254
#define    accVectorPort          256
#define    accConcatPort          258
#define    accWire                260
#define    accWand                261
#define    accWor                 262
#define    accTri                 263
#define    accTriand              264
#define    accTrior               265
#define    accTri0                266
#define    accTri1                267
#define    accTrireg              268
#define    accSupply0             269
#define    accSupply1             270
#define    accNamedEvent          280
#define    accEventVar            accNamedEvent
#define    accIntegerVar          281
#define    accIntVar              281
#define    accRealVar             282
#define    accTimeVar             283
#define    accScalar              300
#define    accVector              302
#define    accCollapsedNet        304
#define    accExpandedVector      306
#define    accUnExpandedVector    307
#define    accProtected           308
#define    accSetup               366
#define    accHold                367
#define    accWidth               368
#define    accPeriod              369
#define    accRecovery            370
#define    accSkew                371
#define    accNochange            376
#define    accNoChange            accNochange
#define    accSetuphold           377
#define    accInput               402
#define    accOutput              404
#define    accInout               406
#define    accMixedIo             407
#define    accPositive            408
#define    accNegative            410
#define    accUnknown             412
#define    accPathTerminal        420
#define    accPathInput           422
#define    accPathOutput          424
#define    accDataPath            426
#define    accTchkTerminal        428
#define    accBitSelect           500
#define    accPartSelect          502
#define    accTask                504
#define    accFunction            506
#define    accStatement           508
#define    accTaskCall            510
#define    accFunctionCall        512
#define    accSystemTask          514
#define    accSystemFunction      516
#define    accSystemRealFunction  518
#define    accUserTask            520
#define    accUserFunction        522
#define    accUserRealFunction    524
#define    accNamedBeginStat      560
#define    accNamedForkStat       564
#define    accConstant            600
#define    accConcat              610
#define    accOperator            620
#define    accMinTypMax           696
#define    accModPathHasIfnone    715

/*------------------ parameter values for acc_configure() -------------------*/
#define    accPathDelayCount        1
#define    accPathDelimStr          2
#define    accDisplayErrors         3
#define    accDefaultAttr0          4
#define    accToHiZDelay            5
#define    accEnableArgs            6
#define    accDisplayWarnings       8
#define    accDevelopmentVersion   11
#define    accMapToMipd            17
#define    accMinTypMaxDelays      19

/*------------ edge information used by acc_handle_tchk(), etc.  ------------*/
#define accNoedge                   0
#define accNoEdge                   0
#define accEdge01                   1
#define accEdge10                   2
#define accEdge0x                   4
#define accEdgex1                   8
#define accEdge1x                  16
#define accEdgex0                  32
#define accPosedge                 13
#define accPosEdge                 accPosedge
#define accNegedge                 50
#define accNegEdge                 accNegedge

/*------------------------------- delay modes -------------------------------*/
#define accDelayModeNone            0
#define accDelayModePath            1
#define accDelayModeDistrib         2
#define accDelayModeUnit            3
#define accDelayModeZero            4
#define accDelayModeVeritime        5

/*------------ values for type field in t_setval_delay structure ------------*/
#define accNoDelay                  0
#define accInertialDelay            1
#define accTransportDelay           2
#define accPureTransportDelay       3
#define accForceFlag                4
#define accReleaseFlag              5
#define accAssignFlag               6
#define accDeassignFlag             7

/*------------ values for type field in t_setval_value structure ------------*/
#define accBinStrVal                1
#define accOctStrVal                2
#define accDecStrVal                3
#define accHexStrVal                4
#define accScalarVal                5
#define accIntVal                   6
#define accRealVal                  7
#define accStringVal                8
#define accVectorVal               10

/*------------------------------ scalar values ------------------------------*/
#define acc0                        0
#define acc1                        1
#define accX                        2
#define accZ                        3

/*---------------------------- VCL scalar values ----------------------------*/
#define vcl0                        acc0
#define vcl1                        acc1
#define vclX                        accX
#define vclZ                        accZ

/*----------- values for vc_reason field in t_vc_record structure -----------*/
#define logic_value_change          1
#define strength_value_change       2
#define real_value_change           3
#define vector_value_change         4
#define event_value_change          5
#define integer_value_change        6
#define time_value_change           7
#define sregister_value_change      8
#define vregister_value_change      9
#define realtime_value_change      10


/*--------------------------- VCL strength values ---------------------------*/
#define vclSupply                   7
#define vclStrong                   6
#define vclPull                     5
#define vclLarge                    4
#define vclWeak                     3
#define vclMedium                   2
#define vclSmall                    1
#define vclHighZ                    0


/*----------------------- flags used with acc_vcl_add -----------------------*/
#define vcl_verilog_logic           2
#define VCL_VERILOG_LOGIC           vcl_verilog_logic
#define vcl_verilog_strength        3
#define VCL_VERILOG_STRENGTH        vcl_verilog_strength


/*---------------------- flags used with acc_vcl_delete ---------------------*/
#define vcl_verilog                 vcl_verilog_logic
#define VCL_VERILOG                 vcl_verilog


/*---------- values for the type field in the t_acc_time structure --------- */
#define accTime                     1
#define accSimTime                  2
#define accRealTime                 3


/*------------------------------ product types ------------------------------*/
#define accSimulator                1
#define accTimingAnalyzer           2
#define accFaultSimulator           3
#define accOther                    4

/*---------------------------------------------------------------------------*/
/*---------------------- global variable definitions ------------------------*/
/*---------------------------------------------------------------------------*/
extern bool acc_error_flag;
typedef int (*consumer_function)();

/*---------------------------------------------------------------------------*/
/*-------------------------- structure definitions --------------------------*/
/*---------------------------------------------------------------------------*/

/*---------------- data structure used with acc_set_value() -----------------*/
typedef struct t_acc_time
{
  int type;
  int low, 
      high;
  double real;
} s_acc_time, *p_acc_time;

/*---------------- data structure used with acc_set_value() -----------------*/
typedef struct t_setval_delay
{
  s_acc_time time;
  int model;
} s_setval_delay, *p_setval_delay;

/*-------------------- data structure of vector values ----------------------*/
typedef struct t_acc_vecval
{
  int aval;
  int bval;                                    
} s_acc_vecval, *p_acc_vecval;

/*----- data structure used with acc_set_value() and acc_fetch_value() ------*/
typedef struct t_setval_value
{
 int format;
 union
   {
    char *str;
    int scalar;
    int integer;
    double real;
    p_acc_vecval vector;
   } value;
} s_setval_value, *p_setval_value, s_acc_value, *p_acc_value;

/*---------------------- structure for VCL strengths ------------------------*/
typedef struct t_strengths
{
  unsigned char logic_value;
  unsigned char strength1;
  unsigned char strength2;
} s_strengths, *p_strengths;

/*-------------- structure passed to callback routine for VCL ---------------*/
typedef struct t_vc_record
{
 int vc_reason;
 int vc_hightime;
 int vc_lowtime;
 char *user_data;
 union
   {
    unsigned char logic_value;
    double real_value;
    handle vector_handle;
    s_strengths strengths_s;
   } out_value;
} s_vc_record, *p_vc_record;

/*------------ structure used with acc_fetch_location() ---------------------*/
typedef struct t_location
{
 int line_no;
 char *filename;
} s_location, *p_location;

/*--------- structure used with acc_fetch_timescale_info() routine ----------*/
typedef struct t_timescale_info
{
 short unit;
 short precision;
} s_timescale_info, *p_timescale_info;

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

EXTERN bool    acc_append_delays PROTO_PARAMS((handle object, ...));
EXTERN bool    acc_append_pulsere PROTO_PARAMS((handle object, double val1,
                   double val1x, ...));
EXTERN void    acc_close PROTO_PARAMS((void));
EXTERN handle *acc_collect PROTO_PARAMS((handle (*p_next_routine)(),
                   handle scope_object, int *aof_count));
EXTERN bool    acc_compare_handles PROTO_PARAMS((handle h1, handle h2));
EXTERN int     acc_count PROTO_PARAMS((handle (*next_function)(),
                   handle object_handle));
EXTERN bool    acc_configure PROTO_PARAMS((int item, char *value));
EXTERN int     acc_fetch_argc PROTO_PARAMS((void));
EXTERN void  **acc_fetch_argv PROTO_PARAMS((void));
EXTERN double  acc_fetch_attribute PROTO_PARAMS((handle object, ...));
EXTERN int     acc_fetch_attribute_int PROTO_PARAMS((handle object, ...));
EXTERN char   *acc_fetch_attribute_str PROTO_PARAMS((handle object, ...));
EXTERN char   *acc_fetch_defname PROTO_PARAMS((handle object_handle));
EXTERN int     acc_fetch_delay_mode PROTO_PARAMS((handle object_p));
EXTERN bool    acc_fetch_delays PROTO_PARAMS((handle object, ...));
EXTERN int     acc_fetch_direction PROTO_PARAMS((handle object_handle));
EXTERN int     acc_fetch_edge PROTO_PARAMS((handle acc_object));
EXTERN char   *acc_fetch_fullname PROTO_PARAMS((handle object_handle));
EXTERN int     acc_fetch_fulltype PROTO_PARAMS((handle object_h));
EXTERN int     acc_fetch_index PROTO_PARAMS((handle object_handle));
EXTERN double  acc_fetch_itfarg PROTO_PARAMS((int n, handle tfinst));
EXTERN int     acc_fetch_itfarg_int PROTO_PARAMS((int n, handle tfinst));
EXTERN char   *acc_fetch_itfarg_str PROTO_PARAMS((int n, handle tfinst));
EXTERN int     acc_fetch_location PROTO_PARAMS((p_location location_p,
                   handle object));
EXTERN char   *acc_fetch_name PROTO_PARAMS((handle object_handle));
EXTERN int     acc_fetch_paramtype PROTO_PARAMS((handle param_p));
EXTERN double  acc_fetch_paramval PROTO_PARAMS((handle param));
EXTERN int     acc_fetch_polarity PROTO_PARAMS((handle path));
EXTERN int     acc_fetch_precision PROTO_PARAMS((void));
EXTERN bool    acc_fetch_pulsere PROTO_PARAMS((handle path_p, double *val1r,
                   double *val1e, ...));
EXTERN int     acc_fetch_range PROTO_PARAMS((handle node, int *msb,
                   int *lsb));
EXTERN int     acc_fetch_size PROTO_PARAMS((handle obj_h));
EXTERN double  acc_fetch_tfarg PROTO_PARAMS((int n));
EXTERN int     acc_fetch_tfarg_int PROTO_PARAMS((int n));
EXTERN char   *acc_fetch_tfarg_str PROTO_PARAMS((int n));
EXTERN void    acc_fetch_timescale_info PROTO_PARAMS((handle obj,
                   p_timescale_info aof_timescale_info));
EXTERN int     acc_fetch_type PROTO_PARAMS((handle object_handle));
EXTERN char   *acc_fetch_type_str PROTO_PARAMS((int type));
EXTERN char   *acc_fetch_value PROTO_PARAMS((handle object_handle,
                   char *format_str, p_acc_value acc_value_p));
EXTERN void    acc_free PROTO_PARAMS((handle *array_ptr));
EXTERN handle  acc_handle_by_name PROTO_PARAMS((char *inst_name,
                   handle scope_p));
EXTERN handle  acc_handle_condition PROTO_PARAMS((handle obj));
EXTERN handle  acc_handle_conn PROTO_PARAMS((handle term_p));
EXTERN handle  acc_handle_datapath PROTO_PARAMS((handle path));
EXTERN handle  acc_handle_hiconn PROTO_PARAMS((handle port_ref));
EXTERN handle  acc_handle_interactive_scope PROTO_PARAMS((void));
EXTERN handle  acc_handle_itfarg PROTO_PARAMS((int n, handle tfinst));
EXTERN handle  acc_handle_loconn PROTO_PARAMS((handle port_ref));
EXTERN handle  acc_handle_modpath PROTO_PARAMS((handle mod_p,
                   char *pathin_name, char *pathout_name, ...));
EXTERN handle  acc_handle_notifier PROTO_PARAMS((handle tchk));
EXTERN handle  acc_handle_object PROTO_PARAMS((char *object_name));
EXTERN handle  acc_handle_parent PROTO_PARAMS((handle object_p));
EXTERN handle  acc_handle_path PROTO_PARAMS((handle source,
                   handle destination));
EXTERN handle  acc_handle_pathin PROTO_PARAMS((handle path_p));
EXTERN handle  acc_handle_pathout PROTO_PARAMS((handle path_p));
EXTERN handle  acc_handle_port PROTO_PARAMS((handle mod_handle,
                   int port_num));
EXTERN handle  acc_handle_scope PROTO_PARAMS((handle object));
EXTERN handle  acc_handle_simulated_net PROTO_PARAMS((handle net_h));
EXTERN handle  acc_handle_tchk PROTO_PARAMS((handle mod_p, int tchk_type,
                   char *arg1_conn_name, int arg1_edgetype, ...));
EXTERN handle  acc_handle_tchkarg1 PROTO_PARAMS((handle tchk));
EXTERN handle  acc_handle_tchkarg2 PROTO_PARAMS((handle tchk));
EXTERN handle  acc_handle_terminal PROTO_PARAMS((handle gate_handle,
                   int terminal_index));
EXTERN handle  acc_handle_tfarg PROTO_PARAMS((int n));
EXTERN handle  acc_handle_tfinst PROTO_PARAMS((void));
EXTERN bool    acc_initialize PROTO_PARAMS((void));
EXTERN handle  acc_next PROTO_PARAMS((int *type_list, handle h_scope,
                   handle h_object));
EXTERN handle  acc_next_bit PROTO_PARAMS((handle vector, handle bit));
EXTERN handle  acc_next_cell PROTO_PARAMS((handle scope, handle cell));
EXTERN handle  acc_next_cell_load PROTO_PARAMS((handle net_handle,
                   handle load));
EXTERN handle  acc_next_child PROTO_PARAMS((handle mod_handle, handle child));
EXTERN handle  acc_next_driver PROTO_PARAMS((handle net, handle driver));
EXTERN handle  acc_next_hiconn PROTO_PARAMS((handle port, handle hiconn));
EXTERN handle  acc_next_input PROTO_PARAMS((handle path, handle pathin));
EXTERN handle  acc_next_load PROTO_PARAMS((handle net, handle load));
EXTERN handle  acc_next_loconn PROTO_PARAMS((handle port, handle loconn));
EXTERN handle  acc_next_modpath PROTO_PARAMS((handle mod_p, handle path));
EXTERN handle  acc_next_net PROTO_PARAMS((handle mod_handle, handle net));
EXTERN handle  acc_next_output PROTO_PARAMS((handle path, handle pathout));
EXTERN handle  acc_next_parameter PROTO_PARAMS((handle module_p,
                   handle param));
EXTERN handle  acc_next_port PROTO_PARAMS((handle ref_obj_p, handle port));
EXTERN handle  acc_next_portout PROTO_PARAMS((handle mod_p, handle port));
EXTERN handle  acc_next_primitive PROTO_PARAMS((handle mod_handle,
                   handle prim));
EXTERN handle  acc_next_scope PROTO_PARAMS((handle ref_scope_p,
                   handle scope));
EXTERN handle  acc_next_specparam PROTO_PARAMS((handle module_p,
                   handle sparam));
EXTERN handle  acc_next_tchk PROTO_PARAMS((handle mod_p, handle tchk));
EXTERN handle  acc_next_terminal PROTO_PARAMS((handle gate_handle,
                   handle term));
EXTERN handle  acc_next_topmod PROTO_PARAMS((handle topmod));
EXTERN bool    acc_object_of_type PROTO_PARAMS((handle object, int type));
EXTERN bool    acc_object_in_typelist PROTO_PARAMS((handle object,
                   int *type_list));
EXTERN int     acc_product_type PROTO_PARAMS((void));
EXTERN char   *acc_product_version PROTO_PARAMS((void));
EXTERN int     acc_release_object PROTO_PARAMS((handle obj));
EXTERN bool    acc_replace_delays PROTO_PARAMS((handle object, ...));
EXTERN bool    acc_replace_pulsere PROTO_PARAMS((handle object, double val1r,
                   double val1x, ...));
EXTERN void    acc_reset_buffer PROTO_PARAMS((void));
EXTERN bool  acc_set_interactive_scope PROTO_PARAMS((handle scope,
                   int callback_flag));
EXTERN bool    acc_set_pulsere PROTO_PARAMS((handle path_p, double val1r,
                   double val1e));
EXTERN char  *acc_set_scope PROTO_PARAMS((handle object, ...));
EXTERN int     acc_set_value PROTO_PARAMS((handle obj,
                   p_setval_value setval_p, p_setval_delay delay_p));
EXTERN void    acc_vcl_add PROTO_PARAMS((handle object_p, int (*consumer)(),
                   char *user_data, int vcl_flags));
EXTERN void    acc_vcl_delete PROTO_PARAMS((handle object_p,
                   int (*consumer)(), char *user_data, int vcl_flags));
EXTERN char   *acc_version PROTO_PARAMS((void));

#ifdef DEFINED_PROTO_PARAMS
#undef DEFINED_PROTO_PARAMS
#undef  PROTO_PARAMS
#endif

#ifdef DEFINED_EXTERN
#undef DEFINED_EXTERN
#undef EXTERN
#endif

/*---------------------------------------------------------------------------*/
/*------------------------------- definitions -------------------------------*/
/*---------------------------------------------------------------------------*/
/* --- UNPORTABLE XL Specific code - must use acc routine 
#define acc_handle_calling_mod_m acc_handle_parent((handle)tf_getinstance())
--- */
#define acc_handle_calling_mod_m acc_handle_parent(acc_handle_tfinst())

#endif /* ACC_USER_H */
