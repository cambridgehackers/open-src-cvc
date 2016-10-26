/* Copyright (c) 2011 Tachyon Design Automation */

/* implement Verilog $fopen using PLI 2.0 vpi_ routines */

#include <stdio.h>
#include <string.h>

#include "vpi_user.h"
#include "cv_vpi_user.h"


/* local function prototypes */

/* global function prototypes */
extern int vpi_fopen(PLI_BYTE8 *);
extern int fopensiz(PLI_BYTE8 *);
int my_error_handler(struct t_cb_data *);
extern void register_my_systfs(void); 

/*
 * ignore the user data field
 */
int vpi_fopen(PLI_BYTE8 *pargs)
{
 unsigned int mcd;
 vpiHandle href, iter, aref;
 struct t_vpi_value valrec;
 s_vpi_value tmpval;

 valrec.format = vpiIntVal;

 valrec.value.integer = (int) 0; 

 href = vpi_handle(vpiSysTfCall, NULL); 
 /* if error after here will return 0 */
 vpi_put_value(href, &valrec, NULL, vpiNoDelay);

 if ((iter = vpi_iterate(vpiArgument, href)) == NULL) return(0);
 if (vpi_get(vpiSize, iter) != 1) return(0);

 if ((aref = vpi_scan(iter)) == NULL) return(0);

 tmpval.format = vpiStringVal;
 /* evaluate expression */
 vpi_get_value(aref, &tmpval);

 mcd = vpi_mcd_open(tmpval.value.str);
 if (mcd != 0) valrec.value.integer = (int) mcd;
 vpi_put_value(href, &valrec, NULL, vpiNoDelay);
 return(0);
}

/*
 * fopen return 32 bit size (unsigned) mcd descriptor word
 */
int fopensiz(PLI_BYTE8 *pargs)
{
 return(32);
}

/*
 * routine to build an error indication string 
 */
int my_error_handler(struct t_cb_data *cbp)
{
 struct t_vpi_error_info einfotab;
 struct t_vpi_error_info *einfop;
 char s1[128];

 einfop = &einfotab;
 vpi_chk_error(einfop);

 if (einfop->state == vpiCompile) strcpy(s1, "vpiCompile");
 else if (einfop->state == vpiPLI) strcpy(s1, "vpiPLI");
 else if (einfop->state == vpiRun) strcpy(s1, "vpiRun");
 else strcpy(s1, "**unknown**");

 vpi_printf("**ERR(%s) %s (level %d) at **%s(%d):\n  %s\n",
  einfop->code, s1, einfop->level, einfop->file, einfop->line,
  einfop->message);

 /* if serious error give up */
 if (einfop->level == vpiSystem || einfop->level == vpiInternal)
  {
   vpi_printf("**FATAL: encountered error - giving up\n");
   vpi_sim_control(vpiFinish, 0);
  }
 /* will just return and leave 0 in vpi_fopen return value */
 return(0);
}

/*
 * register call backs
 */
void register_cbs(void)
{
 vpiHandle href;
 struct t_cb_data *ecbp;
 struct t_cb_data cbrec;

 /* notice cb records must be in global storage */
 ecbp = &cbrec;
 ecbp->reason = cbPLIError;
 ecbp->cb_rtn = my_error_handler; 
 ecbp->obj = NULL;
 ecbp->time = NULL;
 ecbp->value = NULL; 
 ecbp->user_data = NULL;

 /* probably should check for error here */
 if ((href = vpi_register_cb(ecbp)) == NULL)
  vpi_printf("**ERR: PLI 2.0 can not register error handler callback.\n");
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
 register_cbs, 
 0
};

/* routine to do the systf registering - probably should go in other file */
/* usually only vpi_ PLI 2.0 systf registering is done here */

/*
 * register all vpi_ PLI 2.0 style user system tasks and functions
 */
void register_my_systfs()
{
 p_vpi_systf_data systf_data_p;

 /* use predefined table form - could fill systf_data_list dynamically */
 static s_vpi_systf_data systf_data_list[] = {
  { vpiSysFunc, vpiSizedFunc, "$vpi_fopen", vpi_fopen, NULL, fopensiz, NULL },
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
