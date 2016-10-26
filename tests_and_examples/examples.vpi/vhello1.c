/* Copyright (c) 2011 Tachyon Design Automation */

/* simple hello world pli 2.0 task */
/* this is simplest vpi_ 2.0 style c program */

#include <stdio.h>
#include <string.h>

#include "vpi_user.h"
#include "cv_vpi_user.h"

#define TRUE 1
#define FALSE 0

/* local prototypes */
static int count_systf_args(vpiHandle);

/* global prototypes */
PLI_INT32 hello(PLI_BYTE8 *);
extern void register_my_systfs(void); 
extern void register_my_systfs(void);

/*
 * possible pattern for register vpi_ system tasks and functions
 */

/*
 * this is routine to implement registered systf call back
 *
 * notice vpi_user.h requires function return int so using dummy 0
 */
PLI_INT32 hello(PLI_BYTE8 *pargs)
{
 vpiHandle href, iref;

 href = vpi_handle(vpiSysTfCall, NULL); 
 if (href == NULL) 
  {
   vpi_printf("** ERR: $hello PLI 2.0 can not access systf call handle\n");
   return(0);
  }
 if ((iref = vpi_iterate(vpiArgument, href)) != NULL)
  { 
   vpi_printf(
    "**ERR: $hello PLI 2.0 task called with %d arguments but none allowed\n",
    count_systf_args(iref));
   return(0);
  }
 vpi_printf("hello world\n");
 return(0);
}

/*
 * count arguments
 */
static int count_systf_args(vpiHandle iref)
{
 int anum = 0;

 while (vpi_scan(iref) != NULL) anum++;
 return(anum);
}

/* Template functin table for added user systf tasks and functions.
   See file vpi_user.h for structure definition
   Note only vpi_register_systf and vpi_ or tf_ utility routines that 
   do not access the simulation data base may be called from these routines
*/ 

/* all routines are called to register system tasks */
/* called just after all PLI 1.0 tf_ veriusertfs table routines are set up */
/* before source is read */ 
void (*vlog_startup_routines[]) () =
{
 register_my_systfs, 
 0
};

/* routine to do the systf registering - probably should go in other file */
/* usually only vpi_ PLI 2.0 systf registering is done here */

/*
 * register all vpi_ PLI 2.0 style user system tasks and functions
 */
void register_my_systfs(void)
{
 p_vpi_systf_data systf_data_p;

 /* use predefined table form - could fill systf_data_list dynamically */
 static s_vpi_systf_data systf_data_list[] = {
  { vpiSysTask, 0, "$hello", hello, NULL, NULL, NULL },
  { 0, 0, NULL, NULL, NULL, NULL, NULL }
 };

 systf_data_p = &(systf_data_list[0]);
 while (systf_data_p->type != 0) vpi_register_systf(systf_data_p++);
}

/* dummy +loadvpi= boostrap routine - mimics old style exec all routines */
/* in standard PLI vlog_startup_routines table */
void vpi_compat_bootstrap(void)
{
 int i;

 for (i = 0;; i++) 
  {
   if (vlog_startup_routines[i] == NULL) break; 
   vlog_startup_routines[i]();
  }
}
