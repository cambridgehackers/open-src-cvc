/* Copyright (c) 2011 Tachyon Design Automation */
/*
 * test of all action call backs
 * shows sequences of events for action user callbacks
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vpi_user.h"
#include "cv_vpi_user.h"

/* local prototypes */
static char *cb_val_to_nam(char *, int);
static void prt_reg_cbs(char *);

/* global prototypes */
extern PLI_INT32 remove_all_actions(p_vpi_systf_data);
extern PLI_INT32 reg_all_actions(p_vpi_systf_data);
extern int setup_callbacks(struct t_cb_data *);
extern int cb_compend(p_cb_data);
extern int cbsimstart(p_cb_data);
extern int cbsimstart2(p_cb_data);
extern int cbresetstart(p_cb_data);
extern int cbresetend(p_cb_data);
extern int cbsimend(p_cb_data);
extern int cbtchkerr(p_cb_data);
extern int cbenteriact(p_cb_data);
extern int cbexitiact(p_cb_data);
extern int cbiactscopchg(p_cb_data);

extern int my_error_handler(struct t_cb_data *);
extern void register_cbs(void);
extern void register_systfs(void);

vpiHandle action_cbtab[64];

/*
 * remove all register action cbs
 */
PLI_INT32 remove_all_actions(p_vpi_systf_data tfdatp)
{
 vpiHandle cbhref;

 prt_reg_cbs("callbacks before $remove_all_actions");
 /* can't remove start of sim reset? */

 if ((cbhref = action_cbtab[cbStartOfReset]) != NULL)
  {
   vpi_remove_cb(cbhref);
   action_cbtab[cbStartOfReset] = NULL;
  }
 if ((cbhref = action_cbtab[cbEndOfReset]) != NULL)
  {
   vpi_remove_cb(cbhref);
   action_cbtab[cbEndOfReset] = NULL;
  }
 if ((cbhref = action_cbtab[cbEndOfSimulation]) != NULL)
  {
   vpi_remove_cb(cbhref);
   action_cbtab[cbEndOfSimulation] = NULL;
  }
 if ((cbhref = action_cbtab[cbTchkViolation]) != NULL)
  {
   vpi_remove_cb(cbhref);
   action_cbtab[cbTchkViolation] = NULL;
  }
 if ((cbhref = action_cbtab[cbEnterInteractive]) != NULL)
  {
   vpi_remove_cb(cbhref);
   action_cbtab[cbEnterInteractive] = NULL;
  }
 if ((cbhref = action_cbtab[cbExitInteractive]) != NULL)
  {
   vpi_remove_cb(cbhref);
   action_cbtab[cbExitInteractive] = NULL;
  }
 if ((cbhref = action_cbtab[cbInteractiveScopeChange]) != NULL)
  {
   vpi_remove_cb(cbhref);
   action_cbtab[cbInteractiveScopeChange] = NULL;
  }
 prt_reg_cbs("callbacks after $remove_all_actions");
 return(0);
}

/*
 * print all register call backs
 */
static void prt_reg_cbs(char *label)
{
 vpiHandle iter, cbref; 
 s_cb_data cb_inf;
 p_cb_data cbinfp;
 char s1[1025];
 
 vpi_printf(">>> %s <<<\n", label);
 /* get iterator of all registered callbacks */
 if ((iter = vpi_iterate(vpiCallback, NULL)) == NULL) 
  { vpi_printf("  **NONE**\n"); return; }

 /* user provides record that is filled but following current semantics */
 /* values pointed to by contents are shared (i.e. must be left as is) */
 cbinfp = &cb_inf;
 cbinfp->obj = NULL;
 cbinfp->time = NULL;
 cbinfp->value = NULL;
 cbinfp->index = 0;
 for (;;)
  {
   if ((cbref = vpi_scan(iter)) == NULL) break;
   vpi_get_cb_info(cbref, cbinfp);

   vpi_printf("  vpi_ callback type %s registered\n",
    cb_val_to_nam(s1, cbinfp->reason));
  }
}

/*
 * convert a callback reason constant to a name 
 *
 * some here not supported by CVC - will just never see 
 */
static char *cb_val_to_nam(char *s, int cbtyp)
{
 switch (cbtyp) {
  case cbValueChange: strcpy(s, "cbValueChange"); break;
  case cbStmt: strcpy(s, "cbStmt"); break;
  case cbForce: strcpy(s, "cbForce"); break;
  case cbRelease: strcpy(s, "cbRelease"); break;
  case cbAtStartOfSimTime: strcpy(s, "cbAtStartOfSimTime"); break;
  case cbReadWriteSynch: strcpy(s, "cbReadWriteSynch"); break;
  case cbReadOnlySynch: strcpy(s, "cbReadOnlySynch"); break;
  case cbNextSimTime: strcpy(s, "cbNextSimTime"); break;
  case cbAfterDelay: strcpy(s, "cbAfterDelay"); break;
  case cbEndOfCompile: strcpy(s, "cbEndOfCompile"); break;
  case cbStartOfSimulation: strcpy(s, "cbStartOfSimulation"); break;
  case cbEndOfSimulation: strcpy(s, "cbEndOfSimulation"); break;
  case cbError: strcpy(s, "cbError"); break;
  case cbPLIError: strcpy(s, "cbPLIError"); break;
  case cbTchkViolation: strcpy(s, "cbTchkViolation"); break;
  case cbStartOfSave: strcpy(s, "cbStartOfSave"); break; 
  case cbEndOfSave: strcpy(s, "cbEndOfSave"); break;
  case cbStartOfRestart: strcpy(s, "cbStartOfRestart"); break;
  case cbEndOfRestart: strcpy(s, "cbEndOfRestart"); break;
  case cbStartOfReset: strcpy(s, "cbStartOfReset"); break;
  case cbEndOfReset: strcpy(s, "cbEndOfReset"); break;
  case cbEnterInteractive: strcpy(s, "cbEnterInteractive"); break;
  case cbExitInteractive: strcpy(s, "cbExitInteractive"); break;
  case cbInteractiveScopeChange: strcpy(s, "cbInteractiveScopeChange"); break;
  case cbUnresolvedSystf: strcpy(s, "cbUnresolvedSystf"); break;
  default: strcpy(s, "**unknown**"); break;
 }
 return(s);
}

/*
 * reg all action cbs 
 * if user does not call after remove - will have 2 registerd
 */
int reg_all_actions(p_vpi_systf_data tfdatp)
{
 prt_reg_cbs("callbacks before $reg_all_actions");
 setup_callbacks(NULL);
 prt_reg_cbs("callbacks after $reg_all_actions");
 return(0);
}

/*
 * routine to setup call backs (called from start of simulation cb)
 */
int setup_callbacks(struct t_cb_data *cbp)
{
 vpiHandle cbhref;
 struct t_cb_data cbrec;

 /* these must be NULL or given well formed records maybe vpiSuppress... */
 cbrec.obj = NULL;
 cbrec.time = NULL;
 cbrec.value = NULL;
 cbrec.user_data = NULL;
 /* this schedules event so same action cb from action routine should work? */
 if (action_cbtab[cbStartOfSimulation] == NULL)
  {
   cbrec.reason = cbStartOfSimulation;
   cbrec.cb_rtn = cbsimstart2;
   cbhref = vpi_register_cb(&cbrec); 
   action_cbtab[cbStartOfSimulation] = cbhref;
  }

 if (action_cbtab[cbStartOfReset] == NULL)
  {
   cbrec.reason = cbStartOfReset;
   cbrec.cb_rtn = cbresetstart;
   cbhref = vpi_register_cb(&cbrec); 
   action_cbtab[cbStartOfReset] = cbhref;
  }

 if (action_cbtab[cbEndOfReset] == NULL)
  {
   cbrec.reason = cbEndOfReset;
   cbrec.cb_rtn = cbresetend;
   cbhref = vpi_register_cb(&cbrec); 
   action_cbtab[cbEndOfReset] = cbhref;
  }

 if (action_cbtab[cbEndOfSimulation] == NULL)
  {
   cbrec.reason = cbEndOfSimulation;
   cbrec.cb_rtn = cbsimend;
   cbhref = vpi_register_cb(&cbrec); 
   action_cbtab[cbEndOfSimulation] = cbhref;
  }

 if (action_cbtab[cbTchkViolation] == NULL)
  {
   cbrec.reason = cbTchkViolation;
   cbrec.cb_rtn = cbtchkerr;
   cbhref = vpi_register_cb(&cbrec); 
   action_cbtab[cbTchkViolation] = cbhref;
  }

 if (action_cbtab[cbEnterInteractive] == NULL)
  {
   cbrec.reason = cbEnterInteractive;
   cbrec.cb_rtn = cbenteriact;
   cbhref = vpi_register_cb(&cbrec); 
   action_cbtab[cbEnterInteractive] = cbhref;
  }

 if (action_cbtab[cbExitInteractive] == NULL)
  {
   cbrec.reason = cbExitInteractive;
   cbrec.cb_rtn = cbexitiact;
   cbhref = vpi_register_cb(&cbrec); 
   action_cbtab[cbExitInteractive] = cbhref;
  }

 if (action_cbtab[cbInteractiveScopeChange] == NULL)
  {
   cbrec.reason = cbInteractiveScopeChange;
   cbrec.cb_rtn = cbiactscopchg;
   cbhref = vpi_register_cb(&cbrec); 
   action_cbtab[cbInteractiveScopeChange] = cbhref;
  }
 return(0);
}

int cb_compend(p_cb_data cbp)
{
 vpi_printf("*** at end of compilation callback ***\n");
 return(0);
}

int cbsimstart(p_cb_data cbp)
{
 vpi_printf("*** at start of simulation callback (from vlog startup) ***\n");
 return(0);
}

int cbsimstart2(p_cb_data cbp)
{
 vpi_printf("*** at start of simulation callback ***\n");
 return(0);
}

int cbresetstart(p_cb_data cbp)
{
 vpi_printf("*** at start of reset callback ***\n");
 return(0);
}

int cbresetend(p_cb_data cbp)
{
 vpi_printf("*** at end of reset callback ***\n");
 return(0);
}
 
int cbsimend(p_cb_data cbp)
{
 vpi_printf("*** at end of simulation callback ***\n");
 return(0);
}

int cbtchkerr(p_cb_data cbp)
{
 char s1[1024];

 if (cbp->obj != NULL) strcpy(s1, vpi_get_str(vpiFullName, cbp->obj));
 vpi_printf("*** timing check violation at **%s(%d) in %s callback\n",
  vpi_get_str(vpiFile, cbp->obj), vpi_get(vpiLineNo, cbp->obj), s1);
 return(0);
}


int cbenteriact(p_cb_data cbp)
{
 vpi_printf("*** entering interactive mode callback ***\n");
 return(0);
}

int cbexitiact(p_cb_data cbp)
{
 vpi_printf("*** exiting interactive mode callback ***\n");
 return(0);
}

int cbiactscopchg(p_cb_data cbp)
{
 vpi_printf("*** changing interactive scope to %s callback ***\n",
  vpi_get_str(vpiFullName, cbp->obj));
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

 /* if serious error give up, ingore normal errors */
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
 register_systfs,
 0
};

/* routine to do the systf registering - probably should go in other file */
/* usually only vpi_ PLI 2.0 systf or cb registering is done here */

/*
 * register start of sim call backs and set up error handling
 *
 * since handle not save (passed back?), no way to find out cb info
 * start of sim is first when internal data base completed
 */
void register_cbs(void)
{
 vpiHandle href;
 struct t_cb_data *ecbp, *cbp;
 struct t_cb_data cbrec;

 /* notice cb records must be in global storage */
 ecbp = &cbrec;
 ecbp->reason = cbError;
 ecbp->cb_rtn = my_error_handler; 
 ecbp->obj = NULL;
 ecbp->time = NULL;
 ecbp->value = NULL; 
 ecbp->user_data = NULL;

 /* probably should check for error here */
 if ((href = vpi_register_cb(ecbp)) == NULL)
  vpi_printf("**ERR: can not register register error handler callback.\n");

 /* for this test only - setup cbs before start of sim */
 cbp = &cbrec; 
 cbp->cb_rtn = cb_compend;
 cbp->reason = cbEndOfCompile;
 /* notice rest already initialized from ecbp register */
 href = vpi_register_cb(cbp); 
 action_cbtab[cbEndOfCompile] = href;

 cbp->reason = cbStartOfSimulation;
 cbp->cb_rtn = setup_callbacks;
 /* notice rest already initialized from ecbp register */
 /* probably should check for error here */
 if ((href = vpi_register_cb(cbp)) == NULL)
  vpi_printf("**ERR: cannot register start of sim callback.\n");
 action_cbtab[cbStartOfSimulation] = href;
}

/*
 * register remove call back system task - to be called interactively
 */
void register_systfs(void)
{
 static struct t_vpi_systf_data tfdat, tfdat2;
 char s1[1024];
 
 tfdat.type = vpiSysTask;
 strcpy(s1, "$remove_all_actions");
 tfdat.tfname = malloc(strlen(s1) + 1);
 strcpy(tfdat.tfname, s1);
 tfdat.calltf = remove_all_actions;
 vpi_register_systf(&tfdat);

 tfdat2.type = vpiSysTask;
 strcpy(s1, "$reg_all_actions");
 tfdat2.tfname = malloc(strlen(s1) + 1);
 strcpy(tfdat2.tfname, s1);
 tfdat2.calltf = reg_all_actions;

 vpi_register_systf(&tfdat2);
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
