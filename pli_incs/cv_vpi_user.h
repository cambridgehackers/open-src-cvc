/******************************************************************************
* cv_vpi_user.h
*
* Simulator specific vpi_user (vpi_ routine) include file
*
* This file contains the constant definitions, structure definitions
* used by the CVC simulator specific vpi mechanism that follows
* the IEEE P1364 standard
*
* It must be included after vpi_user.h
*
* This file also contains the vpi_ routines that are enhancements not in
* the IEEE standard
*
* Copyright (c) 2011-2013 Tachyon Design Automation All rights reserved.
******************************************************************************/
#ifndef CV_VPI_USER_H
#define CV_VPI_USER_H

#include <stdarg.h>

#ifdef  __cplusplus
extern "C" {
#endif

/*********** OBJECT TYPES **********/ 
/* numbers not yet assigned - using 500s (unassigned) until P1364 assigns */
#define vpiNetDriver    500        /* vpi_ added net driver */
#define vpiNetBitDriver 501        /* vpi_ added net bit driver */
#define vpiSchedBitEvent 502       /* vpi_ added wire driver per bit event */ 
#define vpiParamArray   503        /* new parameter array object */
#define vpiParamArrayWord 504      /* word of param array (same as memory) */

/*********** METHODS **********/ 
/*********** methods used to traverse 1 to 1 relationships **********/ 
/* currently no access to pound parameter expressions - will move */
#define vpiPoundParam 505

/* iterator to get one instance (vpiModule object) of each type */
/* 2nd argument to vpi_iterate must be NULL */
#define vpiOneOfEachMod  506       /* one instance of each type (CVC ext.) */

/* CVC start range (to not conflict with standard or other simulators */
#define CV_START_ONUMS 500

/*********** PROPERTIES ***********/ 
/*********** CVC added properties types ***********/ 

/*---------------------------------------------------------------------------*/
/*------------------------------- definitions -------------------------------*/
/*---------------------------------------------------------------------------*/
/* extra vpi_put_value 4th argument flag value to add driver terminal */
#define vpiAddDriver 16

/*********************** STRUCTURE DEFINITIONS ****************************/
/* cbLanguageLine call back per line record */ 
typedef struct t_vpi_languageline
{
    char *linep;
    char *file;
    int lineno;
} s_vpi_languageline, *p_vpi_languageline;

/* CVC specific call back record - starting at 500 to avoid conflicts */
#define cbLanguageLine 500

/* customer specific simulation control operations */
#define cbCustomer1 501

/* CVC extended vpi_control operations */
#define vpiInsertSource 500
#define vpiCustomer1 501
#define vpiFlushLog 502
#define vpiDumpVars 503
#define vpiEnableCb 504
#define vpiDisableCb 505

/*---------------------------------------------------------------------------*/
/*--------------- CVC non standard routine definitions ---------------------*/
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

/* SJM 11/13/03 - for backward compatibility - old name of vpi control */
#define vpi_sim_control vpi_control

/* added routine for copying - submitted to committee for inclusion */
EXTERN vpiHandle    vpi_copy_object     PROTO_PARAMS((vpiHandle obj));
/* added routine for dumping internal vpi handle contents */
EXTERN PLI_INT32    __vpi_show_object PROTO_PARAMS((vpiHandle obj));

#ifdef DEFINED_PROTO_PARAMS
#undef DEFINED_PROTO_PARAMS
#undef  PROTO_PARAMS
#endif

#ifdef DEFINED_EXTERN
#undef DEFINED_EXTERN
#undef EXTERN
#endif

#ifdef  __cplusplus
}
#endif

#endif /* CV_VPI_USER_H */
