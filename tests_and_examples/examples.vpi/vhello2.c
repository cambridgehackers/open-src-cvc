/* Copyright (c) 2011 Tachyon Design Automation */

/* simple hello world pli 2.0 task and real function */

#include <stdio.h>
#include <string.h>

#include "vpi_user.h"
#include "cv_vpi_user.h"

/* local prototypes */
static void print_systfs(void);
static int count_systf_args(vpiHandle);
static void vpiset_to_real(vpiHandle, double);
static void prtvpiemsg(struct t_vpi_error_info *);

/* global prototypes */
extern PLI_INT32 hello(PLI_BYTE8 *);
extern void register_my_systfs(); 

/*
 * this is routine to implement registered systf call back
 *
 * notice vpi_user.h requires function return int so using dummy 0
 */
PLI_INT32 hello(PLI_BYTE8 *pargs)
{
 vpiHandle href, iref;

 /* quick test of systf iterator */
 print_systfs();

 href = vpi_handle(vpiSysTfCall, NULL); 
 if (href == NULL) 
  {
   vpi_printf("**ERR: $hello PLI 2.0 task registeration problem\n");
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
 * print a list of register systf routines
 */
static void print_systfs(void)
{
 vpiHandle iter, tfref; 
 s_vpi_systf_data systf_inf;
 p_vpi_systf_data tfinfp;

 vpi_printf("--------------------------------------------------------------\n");
 if ((iter = vpi_iterate(vpiUserSystf, NULL)) == NULL) 
  {
   vpi_printf("  No registers vpi_ system tasks or functions.\n");
   vpi_printf(
    "--------------------------------------------------------------\n");
   return;
  }
 /* user provides record that is filled but following current semantics */
 /* values pointed to by contents are shared (i.e. must be left as is) */
 tfinfp = &systf_inf;
 for (;;)
  {
   if ((tfref = vpi_scan(iter)) == NULL) break;
   vpi_get_systf_info(tfref, tfinfp);
   if (tfinfp->type == vpiSysTask)
    vpi_printf("vpi_ system task %s registered.\n", tfinfp->tfname);
   else
    {
     vpi_printf("vpi_ system function %s (ret. type %d) registered.\n",
     tfinfp->tfname, tfinfp->sysfunctype);
    }
  }
 vpi_printf(
  "--------------------------------------------------------------\n");
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

/*
 * real function that returns something and prints hello world
 * 
 * should probably call vpi_chk_error - not just check for null handle 
 * returns 0 because vpi_user.h requires register funcs be int returning
 */
PLI_INT32 realfhello(PLI_BYTE8 *pargs)
{
 vpiHandle href, iref;

 href = vpi_handle(vpiSysTfCall, NULL); 
 if (href == NULL) 
  {
   vpi_printf("** ERR: $realfhello PLI 2.0 can not access sysf call handle\n");
   return(0);
  }
 if ((iref = vpi_iterate(vpiArgument, href)) != NULL)
  { 
   vpi_printf(
    "**ERR: $realfhello PLI 2.0 task called with %d arguments but none allowed\n",
    count_systf_args(iref));
   return(0);
  }
 vpiset_to_real(href, 19.0);
 vpi_printf("hello world\n");
 return(0);
}

/*
 * set a handle to a real value
 *
 * user must make sure href can have have a value put into it
 * notice the key to vpi_ processing is to save and pass handles
 */
static void vpiset_to_real(vpiHandle href, double d1)
{
 struct t_vpi_value valrec;
 struct t_vpi_error_info einfotab;

 valrec.format = vpiRealVal;
  valrec.value.real = d1; 
 vpi_put_value(href, &valrec, NULL, vpiNoDelay);
 if (vpi_chk_error(&einfotab))
  {
   vpi_printf("** ERR: vpi_put_value of real error:\n");
   prtvpiemsg(&einfotab);
  }
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
  { vpiSysFunc, vpiRealFunc, "$realfhello", realfhello, NULL, NULL, NULL },
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
