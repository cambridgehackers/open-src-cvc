/* Copyright (c) 2011 Tachyon Design Automation */
/*
 * example to find cause statements only in top module initial/always 
 *
 * real program would descend to all instances to find all modules
 * and keep track of seen module types to not repeat search
 */

#include <stdio.h>

#include "vpi_user.h"
#include "cv_vpi_user.h"
#include <string.h>

static int num_causes;

/* local prototypes */
static void blk_findcaus(vpiHandle);
static void blk_findcaus(vpiHandle);

/* global prototypes */
extern int findcaus(struct t_cb_data *);
extern int my_error_handler(struct t_cb_data *);
extern void register_scan_cb(void);

int findcaus(struct t_cb_data *cbp)
{
 int iatyp, sttyp, isiz;
 vpiHandle href, href2, href3;
 vpiHandle modiref, ia_iref;

 /* build the iterator for each module */
 modiref = vpi_iterate(vpiModule, NULL);
 isiz = vpi_get(vpiSize, modiref);
 vpi_printf("module iterator has size %d.\n", isiz);
 
 for (num_causes = 0;;)
  {
   if ((href = vpi_scan(modiref)) == NULL) break;
   vpi_printf("... processing instance %s\n", vpi_get_str(vpiFullName, href));
   
   /* build the initial/always process iterator */
   ia_iref = vpi_iterate(vpiProcess, href);
   isiz = vpi_get(vpiSize, ia_iref);
   vpi_printf("init/always iterator has size %d.\n", isiz);
   for (;;)
    {
     if ((href2 = vpi_scan(ia_iref)) == NULL) break;
     iatyp = vpi_get(vpiType, href2);
     if (iatyp == vpiInitial) vpi_printf("... processing initial\n");
     else if (iatyp == vpiAlways) vpi_printf("...processing always\n");
     else vpi_printf("... expected initial/always not found");

     href3 = vpi_handle(vpiStmt, href2); 
     sttyp = vpi_get(vpiType, href3);
     vpi_printf("... processing %d type.\n", sttyp);
     switch (sttyp) { 
      case vpiEventStmt: num_causes++; break;  
      case vpiBegin: case vpiFork: case vpiNamedBegin: case vpiNamedFork:  
       blk_findcaus(href3);
       break;
      default: ; /* anything else just ignored */
     }
    }
  }
 vpi_printf("There were %d total cause statements in top modules.\n",
  num_causes);
 return(0);
}

/*
 * find causes in blocks (maybe named and can be nested)
 */
static void blk_findcaus(vpiHandle blkhref)
{
 int sttyp, isiz;
 vpiHandle ihref, href;

 /* build the list of statements in block iterator */
 ihref = vpi_iterate(vpiStmt, blkhref);
 isiz = vpi_get(vpiSize, ihref);
 vpi_printf("block stmt iterator has size %d.\n", isiz);
 for (;;)
  {
   if ((href = vpi_scan(ihref)) == NULL) break;
   sttyp = vpi_get(vpiType, href);
   vpi_printf("... processing %d type.\n", sttyp);
   switch (sttyp) { 
    case vpiEventStmt: num_causes++; break;  
    case vpiBegin: case vpiFork: case vpiNamedBegin: case vpiNamedFork:  
     blk_findcaus(href);
     break;
    default: ; /* anything else just ignored */
   }
  }
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

 vpi_printf("%s: %s error (level %d) at **%s(%d):\n  %s\n",
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
 * since handle not saved (passed back?), no way to find out cb info
 */
void register_scan_cb(void)
{
 vpiHandle href, href2;
 struct t_cb_data *ecbp, *cbp;
 struct t_cb_data cbrec, cbrec2;

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
  vpi_printf(
   "**ERR: $hello PLI 2.0 task cannot register end of compile check routine");

 cbp = &cbrec2;
 cbp->reason = cbStartOfSimulation;
 cbp->cb_rtn = findcaus;
 cbp->obj = NULL;
 cbp->time = NULL;
 cbp->value = NULL; 
 cbp->user_data = NULL;

 /* probably should check for error here */
 if ((href2 = vpi_register_cb(cbp)) == NULL)
  vpi_printf(
   "**ERR: $hello PLI 2.0 task cannot register end of compile check routine");
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
