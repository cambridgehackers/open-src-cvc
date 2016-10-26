/*
 * simplest asynchronously driven not "CPU" model 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* better to install the in include directory and use <> */
#include "vpi_user.h"
#include "cv_vpi_user.h"

/* really need per instance for each of these probably in malloced storage */
static vpiHandle outdrvh;  

/* local function prototypes */
static PLI_INT32 pli_not(void);
static int do_pli_not(s_cb_data *);
static int my_error_handler(struct t_cb_data *);

/* global function prototypes */
extern void register_my_systfs(void);
extern void register_cbs(void);

/*
 * one call in procedural code to set up not model
 *
 * returns 0 since required by vpi_user.h types but unused
 */
static PLI_INT32 pli_not(void)
{
    int numargs;
    vpiHandle href, iter, inh, outh;
    s_vpi_time tmptim;
    s_vpi_value outval, inval;
    s_cb_data cbrec, *cbp;

    href = vpi_handle(vpiSysTfCall, NULL); 
    iter = vpi_iterate(vpiArgument, href);
    /* maybe ... <code to check arguments (include bad_args label)> */
    numargs = vpi_get(vpiSize, iter);

    if ((outh = vpi_scan(iter)) == NULL)
     {
bad_args:
      /* need error message here */
      return(0);
     }
    if ((inh = vpi_scan(iter)) == NULL) goto bad_args;

    /* add the driver */
    outdrvh = vpi_put_value(outh, NULL, NULL, vpiAddDriver);

    /* make sure output starts as x */
    outval.format = vpiScalarVal;
    outval.value.scalar = vpiX; 
    /* because driver always initialized to z (tristate), must set to x */
    vpi_put_value(outdrvh, &outval, NULL, vpiNoDelay);

    /* cb records must be in global storage because used inside PLI */
    cbp = &cbrec;
    cbp->reason = cbValueChange;
    cbp->cb_rtn = do_pli_not;
    cbp->obj = inh;
    /* do not need to have input handle change time recorded */
    tmptim.type = vpiSuppressTime; 
    cbp->time = &tmptim;

    /* but need changed input value - records value on change */
    inval.format = vpiScalarVal; 
    cbp->value = &inval;

    cbp->user_data = NULL;
    vpi_register_cb(cbp);
    return(0);
}

/*
 * call back routine - called whenever not input changes (model goes here)
 */
static int do_pli_not(s_cb_data *cbp)
{
    int outv, inv;
    vpiHandle eventh;
    s_vpi_value outval;
    s_vpi_time tmptim;

    /* better would be to use callback value field */
    inv = cbp->value->value.scalar;
    if (inv == vpi1) outv = vpi0;
    else if (inv == vpi0) outv = vpi1;
    else outv = vpiX;

    /* assume all nots have delay 5 - could be vpiNoDelay */
    tmptim.type = vpiScaledRealTime;
    tmptim.real = 5.0;
    outval.format = vpiScalarVal;
    outval.value.scalar = outv; 
    /* return event but not used in "not" version 1 */
    /* could use eventh to implement CPU pin C code timing checks */
    eventh = vpi_put_value(outdrvh, &outval, &tmptim,
      (vpiInertialDelay | vpiReturnEvent));
    return(0);
}

/*
 * routine to build an error indication string
 * I usually start by running under debugger with breakpoint here
 */
static int my_error_handler(struct t_cb_data *cbp)
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

void register_cbs(void)
{
    vpiHandle href;
    p_cb_data ecbp;
    s_cb_data ecbrec;

    /* notice cb records must be in global storage */
    ecbp = &ecbrec;
    ecbp->reason = cbPLIError;
    ecbp->cb_rtn = my_error_handler; 
    ecbp->obj = NULL;
    ecbp->time = NULL;
    ecbp->value = NULL; 
    ecbp->user_data = NULL;

    /* probably should check for error here */
    if ((href = vpi_register_cb(ecbp)) == NULL)
       vpi_printf("**ERR: can not regiser register error handler callback.\n");
}

/* Template functin table for added user systf tasks and functions.
   See file vpi_user.h for structure definition
   Note only vpi_register_systf and vpi_ or tf_ utility routines that 
   do not access the simulation data base may be called from these routines
*/ 

void (*vlog_startup_routines[]) () =
{
    register_my_systfs, 
    register_cbs,
    0
};

void register_my_systfs(void)
{
    p_vpi_systf_data systf_data_p;

    static s_vpi_systf_data systf_data_list[] = {
       { vpiSysTask, 0, "$pli_not", pli_not, NULL, NULL, NULL },
       { 0, 0, NULL, NULL, NULL, NULL, NULL }
    };

    systf_data_p = &(systf_data_list[0]);
    while (systf_data_p->type != 0) vpi_register_systf(systf_data_p++);
}

/* dummy +loadvpi= boostrap routine - mimics old style exec all routines */
/* in standard PLI vlog_startup_routines */
void vpi_compat_bootstrap(void)
{
 int i;

 for (i = 0;; i++) 
  {
   if (vlog_startup_routines[i] == NULL) break; 
   vlog_startup_routines[i]();
  }
}
