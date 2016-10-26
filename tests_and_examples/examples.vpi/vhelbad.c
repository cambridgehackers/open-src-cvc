/* Copyright (c) 2011 Tachyon Design Automation */

/* version of hello that does not work */
/* shows problem with tf_ style checking in vpi_ */

#include <stdio.h>
#include <string.h>

#include "vpi_user.h"
#include "cv_vpi_user.h"

/* local prototypes */
static void prtvpiemsg(struct t_vpi_error_info *);
static int count_systf_args(vpiHandle);

/* global prototypes */
extern PLI_INT32 hello_setup(char *);
extern PLI_INT32 hello_chk(struct t_cb_data *);
extern void register_my_systfs(void); 

/*
 * possible pattern for register vpi_ system tasks and functions
 */

/*
 * this is routine to implement registered systf call back
 *
 * notice vpi_user.h requires function return int so using dummy 0
 */
PLI_INT32 hello(void)
{
 vpi_printf("hello world\n");
 return(0);
}

/*
 * check each hello call, in struct as short but passed as int 
 *
 * dynamic nature of PLI 2.0 requires checking just before simulation 
 * because need to wait until simulation data structure is built
 */
PLI_INT32 hello_setup(char *data)
{
 vpiHandle href;
 struct t_cb_data *cbp;
 struct t_cb_data cbrec;
 
 vpi_printf("... executing vpi_ systf compiletf routine.\n");
 cbp = &cbrec;
 cbp->reason = cbEndOfCompile;
 cbp->cb_rtn = hello_chk;
 cbp->obj = NULL;
 cbp->time = NULL;
 cbp->value = NULL; 
 cbp->user_data = NULL;

 /* probably should check for error here */
 if ((href = vpi_register_cb(cbp)) == NULL)
  vpi_printf(
   "**ERR: $hello PLI 2.0 task cannot register end of compile check routine");
 /* if not registered will be no call backs */
 return(0);
}

/*
 * check - must be at end of compile after sim data structure set up
 */
PLI_INT32 hello_chk(struct t_cb_data *cbp)
{
 vpiHandle href, iref;
 struct t_vpi_error_info einfotab;

 vpi_printf("... executing EndOfCompile callback for checking.\n");
 href = vpi_handle(vpiSysTfCall, NULL); 
 if (vpi_chk_error(&einfotab))
  {  
   if (href != NULL) vpi_printf("... why is handle not nil\n"); 
   vpi_printf("** ERR: $hello PLI 2.0 can not access systf call handle\n");
   prtvpiemsg(&einfotab);
   /* vpi_sim_control(vpiFinish, 0); */
  }
 iref = vpi_iterate(vpiArgument, href);
 if (vpi_chk_error(&einfotab))
  {
   vpi_printf("** ERR: vpi_iterate error:\n");
   prtvpiemsg(&einfotab);
   vpi_sim_control(vpiFinish, 0);
  }
 if (iref != NULL) 
  { 
   vpi_printf(
    "** ERR: $hello PLI 2.0 task called with %d arguments but none allowed",
    count_systf_args(iref));
   vpi_free_object(iref);
   vpi_sim_control(vpiFinish, 0);
  }
 return(0);
}

/*
 * routine to build an error indication string 
 */
static void prtvpiemsg(struct t_vpi_error_info *einfop)
{
 char s1[128];

 if (einfop->state == vpiCompile) strcpy(s1, "vpiCompile");
 else if (einfop->state == vpiPLI) strcpy(s1, "vpiPLI");
 else if (einfop->state == vpiRun) strcpy(s1, "vpiRun");
 else strcpy(s1, "**unknown**");

 vpi_printf("%s: %s error (level %d) at **%s(%d):\n  %s\n",
  einfop->code, s1, einfop->level, einfop->file, einfop->line,
  einfop->message);
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
  { vpiSysTask, 0, "$hello", hello, hello_setup, NULL, NULL },
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
