/* Copyright (c) 2011 Tachyon Design Automation */

/*
 * test of set delays vpi_ tasks - read and sets (puts) same delay value
 * for primitives and paths only
 */

#include <stdio.h>
#include <string.h>

#include "vpi_user.h"
#include "cv_vpi_user.h"

#define TRUE 1
#define FALSE 0

int (*iproc_rtn)();

/* local function prototypes */
static void process_inst(vpiHandle); 
static char *get_tchknam(char *, int);

/* global function prototypes */
extern int process_all_insts(struct t_cb_data *);
extern int prt_inst_delays(vpiHandle);
extern int my_error_handler(struct t_cb_data *);
extern void register_scan_cb(void);

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
 vpi_printf("  All instances processed.\n");
 /* notice Verilog model is not run, just data for PLI */
 vpi_sim_control(vpiFinish, 0);
 return(0);
}

/*
 * process one instance and recursively process all under instances
 * processing is top down depth first
 */
static void process_inst(vpiHandle up_ihref) 
{
 int isiz;
 vpiHandle iter, ihref;

 iproc_rtn(up_ihref);
 if ((iter = vpi_iterate(vpiModule, up_ihref)) == NULL) return;
 isiz = vpi_get(vpiSize, iter);
 vpi_printf("  There are %d instances in %s.\n", isiz,
  vpi_get_str(vpiFullName, up_ihref));
  for (;;)
  {
   if ((ihref = vpi_scan(iter)) == NULL) break;
   process_inst(ihref);
  }
}

/*
 * simplest processing routine - just print delays
 */
int prt_inst_delays(vpiHandle ihref)
{
 register int di;
 int tctyp;
 vpiHandle iter, href;
 s_vpi_delay idrec, odrec;
 s_vpi_time idelarr[12], odelarr[12];
 char s1[1024], s2[1024];

 idrec.da = &(idelarr[0]);
 idrec.time_type = vpiSimTime;
 /* idrec.time_type = vpiScaledRealTime; */
 idrec.mtm_flag = FALSE;
 idrec.append_flag = FALSE;
 idrec.pulsere_flag = FALSE;
 /* gates - use scan returns nil, nil iterator pattern */ 
 idrec.no_of_delays = 3;

 odrec.da = &(odelarr[0]);
 odrec.time_type = idrec.time_type;
 odrec.mtm_flag = FALSE;
 odrec.append_flag = TRUE;
 odrec.pulsere_flag = FALSE;
 /* gates - use scan returns nil, nil iterator pattern */ 
 odrec.no_of_delays = 3;

 iter = vpi_iterate(vpiPrimitive, ihref);
 for (;;)
  {
   if ((href = vpi_scan(iter)) == NULL) break;
   if (vpi_iterate(vpiDelay, href) == NULL) continue;

   vpi_get_delays(href, &idrec);
   for (di = 0; di < idrec.no_of_delays; di++) odrec.da[di] = idrec.da[di]; 
   vpi_put_delays(href, &odrec);
   vpi_get_delays(href, &idrec);

   /* expect delays to always fit in 31 bits */
   if (vpi_get(vpiType, href) == vpiUdp) strcpy(s1, "udp");
   else strcpy(s1, "gate");
   strcpy(s2, vpi_get_str(vpiDefName, href));
   /* -- */
   vpi_printf("  %s %s %s has delay #(%d, %d, %d).\n",
    s2, s1, vpi_get_str(vpiFullName, href), idrec.da[0].low, idrec.da[1].low,
    idrec.da[2].low);
   /* --- */
   /* ---
   vpi_printf("  %s %s %s has delay #(%d, %d).\n",
    s2, s1, vpi_get_str(vpiFullName, href), idrec.da[0].low, idrec.da[1].low);
   --- */
  /* ---
   vpi_printf("  %s %s %s has delay #(%5.2f, %5.2f).\n",
    s2, s1, vpi_get_str(vpiFullName, href), idrec.da[0].real,
    idrec.da[1].real);
  --- */
  }
 /* contas */
 iter = vpi_iterate(vpiContAssign, ihref);
 for (;;)
  {
   if ((href = vpi_scan(iter)) == NULL) break;
   if (vpi_iterate(vpiDelay, href) == NULL) continue;

   vpi_get_delays(href, &idrec);
   /* expect delays to always fit in 31 bits */
   vpi_printf("  continuous assign at **%s(%d) has delay #(%d, %d, %d).\n",
    vpi_get_str(vpiFile, href), vpi_get(vpiLineNo, href),
    idrec.da[0].low, idrec.da[1].low, idrec.da[2].low);
  }
 /* paths */
 idrec.no_of_delays = 6;
 idrec.time_type = vpiScaledRealTime; 
 iter = vpi_iterate(vpiModPath, ihref);
 for (;;)
  {
   if ((href = vpi_scan(iter)) == NULL) break;

   vpi_get_delays(href, &idrec);
   for (di = 0; di < idrec.no_of_delays; di++) odrec.da[di] = idrec.da[di]; 
   vpi_put_delays(href, &odrec);
   vpi_get_delays(href, &idrec);
   /* expect delays to always fit in 31 bits */
   /* --- */
   vpi_printf("  path at **%s(%d) has delay #(%g, %g, %g, %g, %g, %g).\n",
    vpi_get_str(vpiFile, href), vpi_get(vpiLineNo, href),
    idrec.da[0].real, idrec.da[1].real, idrec.da[2].real, idrec.da[3].real,
    idrec.da[4].real, idrec.da[5].real);
   /* --- */ 
   /* ---
   vpi_printf("  path at **%s(%d) has delay #(%d, %d, %d, %d, %d, %d).\n",
    vpi_get_str(vpiFile, href), vpi_get(vpiLineNo, href),
    idrec.da[0].low, idrec.da[1].low, idrec.da[2].low, idrec.da[3].low,
    idrec.da[4].low, idrec.da[5].low);
   --- */
   /* ---
   vpi_printf(
    "  path at **%s(%d) has delay #(%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d).\n",
    vpi_get_str(vpiFile, href), vpi_get(vpiLineNo, href),
    idrec.da[0].low, idrec.da[1].low, idrec.da[2].low, idrec.da[3].low,
    idrec.da[4].low, idrec.da[5].low, idrec.da[6].low, idrec.da[7].low,
    idrec.da[8].low, idrec.da[9].low, idrec.da[10].low, idrec.da[11].low);
   --- */
   /* ---
   vpi_printf("  path at **%s(%d) has delay #(%d, %d).\n",
    vpi_get_str(vpiFile, href), vpi_get(vpiLineNo, href),
    idrec.da[0].low, idrec.da[1].low, idrec.da[2].low);
   --- */
  }
 /* timing checks */
 /* paths */
 /* drec.no_of_delays = 2; */
 idrec.time_type = vpiSimTime;
 /* drec.time_type = vpiScaledRealTime; */ 
 idrec.time_type = vpiScaledRealTime; 
 iter = vpi_iterate(vpiTchk, ihref);
 for (;;)
  {
   if ((href = vpi_scan(iter)) == NULL) break;
   tctyp = vpi_get(vpiTchkType, href);
   if (tctyp == vpiWidth || tctyp == vpiSetupHold) idrec.no_of_delays = 2;
   else idrec.no_of_delays = 1;
   vpi_get_delays(href, &idrec);
   get_tchknam(s1, tctyp);
   vpi_printf("  %s timing check at **%s(%d) limit %g.\n",
    s1, vpi_get_str(vpiFile, href), vpi_get(vpiLineNo, href), idrec.da[0].real);
   /* ---
   vpi_printf("  %s timing check at **%s(%d) 1st limit %d, 2nd limit %d.\n",
    s1, vpi_get_str(vpiFile, href), vpi_get(vpiLineNo, href),
    idrec.da[0].low, idrec.da[1].low);
   --- */    
  }
 return(0);
}

/*
 * notice need user routine - no str property
 */
char *get_tchknam(char *s, int ttyp)
{
 switch (ttyp) {
  case vpiSetup: strcpy(s, "$setup"); break;
  case vpiHold: strcpy(s, "$hold"); break;
  case vpiPeriod: strcpy(s, "$period"); break;
  case vpiWidth: strcpy(s, "$width"); break;
  case vpiSkew: strcpy(s, "$skew"); break;
  case vpiRecovery: strcpy(s, "$recovery"); break;
  case vpiNoChange: strcpy(s, "$nochange"); break;
  case vpiSetupHold: strcpy(s,  "$setuphold"); break;
  default: strcpy(s, "**out of range**");  break;
 } 
 return(s);
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
 iproc_rtn = prt_inst_delays;
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
