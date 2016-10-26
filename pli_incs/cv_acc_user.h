
/******************************************************************************
* cv_acc_user.h
*
* Simulator specific acc_user.h (acc_ routines) include file
*
* This file contains the constant definitions, structure definitions
* used in IEEE P1364 LRM but not defined in acc_user.h file in appendix.
*
* It must be included after acc_user.h 
*
*
* This file also contains the acc_ routines that are in common use but
* not in the IEEE standard
*
* Copyright (c) 2011-2013 Tachyon Design Automation All rights reserved.
* Copyright 1995, IEEE. All rights reserved.
******************************************************************************/
#ifndef CVACCUSER_H
#define CVACCUSER_H

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

/* added routine for dumping internal acc_ handle contents */
EXTERN int   __acc_show_object PROTO_PARAMS((handle obj));

#ifdef DEFINED_PROTO_PARAMS
#undef DEFINED_PROTO_PARAMS
#undef  PROTO_PARAMS
#endif

#ifdef DEFINED_EXTERN
#undef DEFINED_EXTERN
#undef EXTERN
#endif

#endif /* CV_ACC_USER_H */
