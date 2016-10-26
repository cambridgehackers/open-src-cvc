/* Copyright (c) 2011 Tachyon Design Automation */

/*
 * print out all drives and loads for wire and regs
 *
 * this shows the advantage of type information carrying handles - values
 * can be printed without knowing much about Verilog constructs
 */

#include <stdio.h>
#include <string.h>

#include "vpi_user.h"
#include "cv_vpi_user.h"

int (*iproc_rtn)();

/* local function prototypes */
static void process_inst(vpiHandle); 
static void prt_1iter_drvlds(vpiHandle, vpiHandle);
static void prt_iter(vpiHandle, vpiHandle);
static void prt_1task_drvlds(vpiHandle);

/* global function prototypes */
extern int my_prt_vchg();
extern int prt_drvlds(vpiHandle);
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
 vpi_printf("  >>> All instances processed - continuing with simulation.\n");
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
 * print the loads and drivers for all nets in instance ihref
 */
int prt_drvlds(vpiHandle ihref)
{
 vpiHandle iter, thref;
 
 /* first all instance regs, wires, and variables */ 
 iter = vpi_iterate(vpiNet, ihref);
 if (iter != NULL) prt_1iter_drvlds(iter, ihref);
 iter = vpi_iterate(vpiReg, ihref);
 if (iter != NULL) prt_1iter_drvlds(iter, ihref);
 iter = vpi_iterate(vpiVariables, ihref);
 if (iter != NULL) prt_1iter_drvlds(iter, ihref);

 /* also monitor in scopes */
 iter = vpi_iterate(vpiInternalScope, ihref);
 for (;;)
  {
   if ((thref = vpi_scan(iter)) == NULL) break;
   prt_1task_drvlds(thref);
  }
 return(0);
}

/*
 * print all loads and drivers for nets in one iterator
 */
static void prt_1iter_drvlds(vpiHandle iter, vpiHandle ihref)
{
 register int bi;
 int ntyp;
 vpiHandle href, bref, bititer, lditer, drviter, ndxref;
 s_vpi_value tmpval;

 for (;;)
  {
   if ((href = vpi_scan(iter)) == NULL) break;
   /* can not pass real variable to load/driver iterator or will get err */  
   /* bits selects form real illegal in Verilog */
   if ((ntyp = vpi_get(vpiType, href)) == vpiRealVar) continue;

   /* for this test ignore scalars */
   if (vpi_get(vpiScalar, href)) continue; 

   /* should never be nil */
   if ((bititer = vpi_iterate(vpiBit, href)) == NULL) continue;
   for (;;)
    {
     if ((bref = vpi_scan(bititer)) == NULL) break;
     
     ndxref = vpi_handle(vpiIndex, bref);
     tmpval.format = vpiIntVal;
     /* need to evalate expr. even though since from iter know constant */
     vpi_get_value(ndxref, &tmpval);
     bi = tmpval.value.integer;

     /* print the drives and loads for 1 net */ 
     vpi_printf("... printing drivers and loads for %s[%d]:\n", 
      vpi_get_str(vpiFullName, bref), bi);

     lditer = vpi_iterate(vpiLocalLoad, bref);
     if (lditer != NULL)
      {
       vpi_printf("  Loads:\n");
       prt_iter(lditer, ihref);
      }    

     /* regs can only have loads because in CVC force/assign properties */
     /* not drivers */
     if (ntyp != vpiNetBit) continue;
  
     drviter = vpi_iterate(vpiLocalDriver, bref);
     if (drviter != NULL)
      {
       vpi_printf("  Drivers:\n");
       prt_iter(drviter, ihref);
      }

     lditer = vpi_iterate(vpiPathTerm, bref);
     if (lditer != NULL)
      {
       vpi_printf("  Path terminals:\n");
       prt_iter(lditer, ihref);
      }

     lditer = vpi_iterate(vpiTchkTerm, bref);
     if (lditer != NULL)
      {
       vpi_printf("  Timing check terminals:\n");
       prt_iter(lditer, ihref);
      }
    }
  }
}

/*
 * print contents of one iterator (any? non NULL)
 */
static void prt_iter(vpiHandle iter, vpiHandle ihref)
{
 int htyp;
 vpiHandle href, portihref;
 char *chp, s1[1025];

 for (;;)
  {
   if ((href = vpi_scan(iter)) == NULL) break;
  
   htyp = vpi_get(vpiType, href);
   /* must handle port as special case because can be module port */
   /* or up instance port connection */
   if (htyp == vpiModPathIn || htyp == vpiModPathOut) strcpy(s1, "**NONE(0)"); 
   else
    {
     if ((chp = vpi_get_str(vpiFile, href)) == NULL)
      strcpy(s1, "**NONE(0)"); 
     else sprintf(s1, "**%s(%d)", chp, vpi_get(vpiLineNo, href));
    } 
   if (htyp == vpiPort)
    {
     /* if ld/drv net in same instance as port then module port */ 
     /* else up instance connection */
     portihref = vpi_handle(vpiModule, href);
     if (vpi_compare_objects(ihref, portihref))
      {
       vpi_printf("   Port (vpiLowConn) object at %s\n", s1);
      }
     else
      {
       sprintf(s1, "**%s(%d)", vpi_get_str(vpiFile, portihref),
        vpi_get(vpiLineNo, portihref));
       vpi_printf("   Port (vpiHighConn) object at %s\n", s1);
      }
    }
   else vpi_printf("    %s object at %s\n", vpi_get_str(vpiType, href), s1);
  }
}

/*
 * print the drivers and loads for one task (should be no drivers?)
 *
 * drive and load print iterator routines passed nil instance context
 * because only needed for ports that are impossible in tasks
 */
static void prt_1task_drvlds(vpiHandle thref)
{
 vpiHandle iter;

 iter = vpi_iterate(vpiReg, NULL);
 if (iter != NULL) prt_1iter_drvlds(iter, NULL);
 iter = vpi_iterate(vpiVariables, thref);
 if (iter != NULL) prt_1iter_drvlds(iter, NULL);

 /* include all contained named blocks */
 iter = vpi_iterate(vpiInternalScope, thref);
 for (;;)
  {
   if ((thref = vpi_scan(iter)) == NULL) break;
   prt_1task_drvlds(thref);
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
 iproc_rtn = prt_drvlds;
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
