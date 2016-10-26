/* Copyright (c) 2011 Tachyon Design Automation */

/*
 * test of time related cbs
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vpi_user.h"
#include "cv_vpi_user.h"

int num_simstarttime_cbs;
int num_after_cbs;

/* local function prototypes */

/* global function prototypes */
extern int setup_delcbs(p_cb_data);
extern int cbtimstart_rtn(struct t_cb_data *);
extern int cbdel_rtn(p_cb_data);
extern int cbwrsync_rtn(p_cb_data);
extern int cbrosync_rtn(p_cb_data);
extern int cbnxttim_rtn(p_cb_data);
extern int my_error_handler(struct t_cb_data *);
extern void register_cbs(void);

int setup_delcbs(struct t_cb_data *cbp)
{
 struct t_cb_data cbrec;
 p_vpi_time timp;

 cbrec.reason = cbAtStartOfSimTime;
 cbrec.cb_rtn = cbtimstart_rtn;
 cbrec.obj = NULL; 
 /* just allocate once */
 timp = (p_vpi_time) malloc(sizeof(s_vpi_time));
 timp->type = vpiSimTime;
 timp->high = 0;
 timp->low = 22;
 cbrec.time = timp;
 cbrec.value = NULL;
 cbrec.index = 0;
 vpi_register_cb(&cbrec); 

 cbrec.reason = cbAfterDelay;
 cbrec.obj = NULL; 
 cbrec.cb_rtn = cbdel_rtn;
 timp->type = vpiSimTime;
 timp->high = 0;
 timp->low = 43;
 cbrec.time = timp;
 cbrec.value = NULL;
 cbrec.index = 0;
 vpi_register_cb(&cbrec); 
 return(0);
}

/*
 * call back for start of sim delays - schedule another one (total of 20)
 */
int cbtimstart_rtn(p_cb_data cbp)
{
 vpi_printf("*** start of simulation time wake up at %d\n", cbp->time->low);

 /* notice reusing passed call back for new register is really illegal */
 cbp->cb_rtn = cbtimstart_rtn;
 cbp->time->high = 0;
 cbp->time->low = 6;
 if (++num_simstarttime_cbs < 50) vpi_register_cb(cbp); 
 return(0);
}

/*
 * call back for normal delays 
 */
int cbdel_rtn(p_cb_data cbp)
{
 vpi_printf("*** normal delay time wake up at %d\n", cbp->time->low);

 /* notice reusing passed call back for new register is really illegal */
 cbp->reason = cbReadWriteSynch;
 cbp->cb_rtn = cbwrsync_rtn;
 cbp->time->high = 0;
 cbp->time->low = 0;
 vpi_register_cb(cbp); 
 return(0);
}

/*
 * ro sync cb routine
 */
int cbwrsync_rtn(p_cb_data cbp)
{
 vpi_printf("*** rw sync time wake up at %d\n", cbp->time->low);

 /* not sure if legal to usurp t_cb_data since removed when event happens */
 cbp->reason = cbReadOnlySynch;
 cbp->cb_rtn = cbrosync_rtn;
 cbp->obj = NULL;
 cbp->time->high = 0;
 cbp->time->low = 0;
 cbp->value = NULL;
 cbp->index = 0;
 vpi_register_cb(cbp); 
 return(0);
}

/*
 * ro sync cb routine - schedules 2 events
 */
int cbrosync_rtn(p_cb_data cbp)
{
 struct t_cb_data cbrec;
 p_vpi_time timp;

 vpi_printf("*** ro sync time wake up at %d\n", cbp->time->low);

 cbp->reason = cbNextSimTime;
 cbp->cb_rtn = cbnxttim_rtn;
 cbp->obj = NULL;
 cbp->time->high = 0;
 cbp->time->low = 0;
 cbp->value = NULL;
 cbp->index = 0;
 vpi_register_cb(cbp); 

 if (++num_after_cbs > 20) return(0);

 cbrec.reason = cbAfterDelay;
 cbrec.cb_rtn = cbdel_rtn;
 cbrec.obj = NULL;
 timp = (p_vpi_time) malloc(sizeof(s_vpi_time));
 timp->type = vpiSimTime;
 timp->high = 0;
 timp->low = 87;
 cbrec.time = timp;
 cbrec.value = NULL;
 cbrec.index = 0;
 vpi_register_cb(&cbrec); 
 return(0);
}

/*
 * next sim time cb routine - no new scheduling from here
 */
int cbnxttim_rtn(p_cb_data cbp)
{
 vpi_printf("*** next sim time wake up at %d\n", cbp->time->low);
 return(0);
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
 if (einfop->level == vpiError || einfop->level == vpiSystem
  || einfop->level == vpiInternal)
  {
   vpi_printf("**FATAL: encountered error - giving up\n");
   vpi_sim_control(vpiFinish, 0);
  }
 return(0);
}


/* Template functin table for added user systf tasks and functions.
   See file vpi_user.h for structure definition
   Note only vpi_register_systf and vpi_ or tf_ utility routines that 
   do not access the simulation data base may be called from these routines
*/ 

/* all routines are called to register cbs */
/* called just after all PLI 1.0 tf_ veriusertfs table routines are set up */
/* before source is read */ 
void (*vlog_startup_routines[]) () =
{
 register_cbs, 
 0
};

/* routine to do the systf registering - probably should go in other file */
/* usually only vpi_ PLI 2.0 systf or cb registering is done here */

/*
 * register the start of sim scan call back and set up error handling
 *
 * notice making version of CVC that prints some stuff to start but
 * is a normal CVC 
 *
 * since handle not save (passed back?), no way to find out cb info
 */
void register_cbs(void)
{
 vpiHandle href, href2;
 struct t_cb_data *ecbp, *cbp;
 struct t_cb_data cbrec;

 num_simstarttime_cbs = 0;
 num_after_cbs = 0;

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

 cbp = &cbrec;
 cbp->reason = cbStartOfSimulation;
 cbp->cb_rtn = setup_delcbs;
 cbp->obj = NULL;
 cbp->time = NULL;
 cbp->value = NULL; 
 cbp->user_data = NULL;

 /* probably should check for error here */
 if ((href2 = vpi_register_cb(cbp)) == NULL)
  vpi_printf(
   "**ERR: PLI 2.0 can not register start of sim setup callback.\n");
 /* if not registered will be no call backs */

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
