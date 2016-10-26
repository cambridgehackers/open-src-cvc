/* Copyright (c) 2011 Tachyon Design Automation */

/*
 * test of value change call backs
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vpi_user.h"
#include "cv_vpi_user.h"

int (*iproc_rtn)();

/* local function prototypes */
static int process_inst(vpiHandle); 
static void setup_1iter_chgcbs(vpiHandle);
static void setup_1task_chgcbs(vpiHandle);

/* global function prototypes */
extern int process_all_insts(struct t_cb_data *);
extern int setup_varchgcbs(vpiHandle);
extern int my_error_handler(struct t_cb_data *);
extern void register_scan_cb();
extern int my_prt_vchg(p_cb_data);

/*
 * routine to get and zero all delays in design 
 */
int process_all_insts(struct t_cb_data *cbp)
{
 int isiz;
 vpiHandle topiter, topiref;

 /* build the iterator for each module */
 topiter = vpi_iterate(vpiModule, NULL);
 isiz = vpi_get(vpiSize, topiter);
 vpi_printf("  There are %d top level modules.\n", isiz);
 for (;;)
  {
   if ((topiref = vpi_scan(topiter)) == NULL) break;
   process_inst(topiref);
  }
 vpi_printf("  >>> All instances processed - continuing with simulation.\n");
 return(0);
}

/*
 * process one instance and recursively process all under instances
 * processing is top down depth first
 */
static int process_inst(vpiHandle up_ihref) 
{
 int isiz;
 vpiHandle iter, ihref;

 iproc_rtn(up_ihref);
 if ((iter = vpi_iterate(vpiModule, up_ihref)) == NULL) return(0);
 isiz = vpi_get(vpiSize, iter);
 vpi_printf("  There are %d instances in %s.\n", isiz,
  vpi_get_str(vpiFullName, up_ihref));
  for (;;)
  {
   if ((ihref = vpi_scan(iter)) == NULL) break;
   process_inst(ihref);
  }
 return(0);
}

/*
 * simplest processing routine - just print full path name
 */
int setup_varchgcbs(vpiHandle ihref)
{
 vpiHandle iter, thref;
 
 /* first all instance regs, wires, and variables */ 
 iter = vpi_iterate(vpiNet, ihref);
 if (iter != NULL) setup_1iter_chgcbs(iter);
 iter = vpi_iterate(vpiReg, ihref);
 if (iter != NULL) setup_1iter_chgcbs(iter);
 iter = vpi_iterate(vpiVariables, ihref);
 if (iter != NULL) setup_1iter_chgcbs(iter);

 /* also monitor in scopes */
 iter = vpi_iterate(vpiInternalScope, ihref);
 for (;;)
  {
   if ((thref = vpi_scan(iter)) == NULL) break;
   setup_1task_chgcbs(thref);
  }
 return(0);
}

/*
 * set up change call back for all nets/regs of some type in iter
 */
static void setup_1iter_chgcbs(vpiHandle iter)
{
 int ntyp;
 vpiHandle href;
 p_cb_data cbp;
 p_vpi_time timp;
 p_vpi_value valp;

 for (;;)
  {
   if ((href = vpi_scan(iter)) == NULL) break;
   /*  illegal to monitor change value of events */
   /* if (vpi_get(vpiNetType, href) == vpiNamedEvent) continue; */

   /* DBG remove --- */
   if ((ntyp = vpi_get(vpiType, href)) == vpiNet || ntyp == vpiNetBit)
    vpi_printf("Net type %d\n", vpi_get(vpiNetType, href)); 

   /* notice this must persistent until cb removed */
   cbp = (p_cb_data) malloc(sizeof(s_cb_data));
   cbp->reason = cbValueChange;
   cbp->cb_rtn = my_prt_vchg;  

   timp = (p_vpi_time) malloc(sizeof(s_vpi_time));
   timp->type = vpiSimTime;
   timp->high = timp->low = 0;
   cbp->time = timp;
   valp = (p_vpi_value) malloc(sizeof(s_vpi_value)); 
   valp->format = vpiBinStrVal;
   /* standard called for value in work string where call back sets ptr to */
   valp->value.str = NULL;
   cbp->value = valp;
   cbp->obj = href; 
   vpi_register_cb(cbp);
  }
}

/*
 * setup variables in task for monitoring
 */
static void setup_1task_chgcbs(vpiHandle thref)
{
 vpiHandle iter;

 iter = vpi_iterate(vpiReg, thref);
 if (iter != NULL) setup_1iter_chgcbs(iter);
 iter = vpi_iterate(vpiVariables, thref);
 if (iter != NULL) setup_1iter_chgcbs(iter);

 /* include all contained named blocks */
 iter = vpi_iterate(vpiInternalScope, thref);
 for (;;)
  {
   if ((thref = vpi_scan(iter)) == NULL) break;
   setup_1task_chgcbs(thref);
  }
}

/*
 * value change call back routine - print the value information
 */
int my_prt_vchg(p_cb_data cbp)
{
 vpi_printf("--> now %d: %s=%s.\n", cbp->time->low,  
  vpi_get_str(vpiFullName, cbp->obj), cbp->value->value.str);
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
 register_scan_cb, 
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
void register_scan_cb(void)
{
 vpiHandle href, href2;
 struct t_cb_data *ecbp, *cbp;
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

 cbp = &cbrec;
 cbp->reason = cbStartOfSimulation;
 cbp->cb_rtn = process_all_insts;
 cbp->obj = NULL;
 cbp->time = NULL;
 cbp->value = NULL; 
 cbp->user_data = NULL;

 /* probably should check for error here */
 if ((href2 = vpi_register_cb(cbp)) == NULL)
  vpi_printf(
   "**ERR: PLI 2.0 can not register start of sim setup callback.\n");
 /* if not registered will be no call backs */

 /* set the processing routine */
 iproc_rtn = setup_varchgcbs;
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
