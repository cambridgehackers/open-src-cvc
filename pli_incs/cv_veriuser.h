/******************************************************************************
* cv_veriuser.h
*
* Simulator specific veriuser (tf_ routine) include file
*
* This file contains the constant definitions, structure definitions
* specific to CVC simulator specific tfcell call mechanism that follows
* the original PLI LRM 1.0 calling mechanism
*
* It must be included after veriuser.h 
*
* This file also contains the tf_ routines that are enhancements not in
* the IEEE standard
*
* Copyright (c) 2012-2013 Tachyon Design Automation All rights reserved.
* Copyright 1995, IEEE. All rights reserved.
******************************************************************************/
#ifndef PVTFUSER_H
#define PVTFUSER_H

/*---------------------------------------------------------------------------*/
/*------------------------------- definitions -------------------------------*/
/*---------------------------------------------------------------------------*/

/*-------------- tfcell interface structure type field constants ------------*/
#define  usertask 1
#define  USERTASK 1
#define  userfunction 2
#define  USERFUNCTION 2
#define  userrealfunction 3
#define  USERREALFUNCTION 3

/*---- s_tfcell interface structure used in user code filled in by user ----*/
typedef struct t_tfcell
{
 short type;         /* either usertask or userfunction */
 short data;         /* parameter for the following routines */
 int (*checktf)();   /* routine for checking parameters */
 int (*sizetf)();    /* for providing size of function return value */
 int (*calltf)();    /* routine called during simulation */
 int (*misctf)();    /* miscellaneous routines (see below) */
 char *tfname;       /* the name of the system task or function */
 int forwref;        /* indicates special parameters allowed */
 /* not part of standard but present in some user models */
 char *tfveritool;   /* usually ignored */
 char *tferrmessage; /* usually ignored */

 /* The following fields are ignored by CVC */
 int hash;
 struct t_tfcell *left_p;
 struct t_tfcell *right_p;
 char *namecell_p;
 int warning_printed;
} s_tfcell, *p_tfcell;


/*---------------------------------------------------------------------------*/
/*--------------- Pver non standard routine definitions ---------------------*/
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

/* added returns name of file as string and sets line number of call */
EXTERN char *tf_getsourceloc PROTO_PARAMS((int *lineno));
EXTERN char *tf_igetsourceloc PROTO_PARAMS((int *lineno, char *inst));

/* added same as 0 delay strdelputp except immediate assign not #0 */ 
EXTERN int tf_istrputp PROTO_PARAMS ((int nparam, int bitlength, int format_char, char *value_p, char *inst));
EXTERN int tf_strputp PROTO_PARAMS ((int nparam, int bitlength, int format_char, char *value_p));

/* get simulation time in ticks (lowest precicision in design) */
/* not in LRM but supported by XL */
EXTERN int tf_getsimtime PROTO_PARAMS((void));

/* get simulation time in ticks - long 64 bit tim version */
EXTERN int tf_getlongsimtime PROTO_PARAMS((int *aof_hightime));

#ifdef DEFINED_PROTO_PARAMS
#undef DEFINED_PROTO_PARAMS
#undef  PROTO_PARAMS
#endif

#ifdef DEFINED_EXTERN
#undef DEFINED_EXTERN
#undef EXTERN
#endif

#endif /* PVTFUSER_H */
