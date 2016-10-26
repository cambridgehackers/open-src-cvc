/*
 * simplest asynchronously driven not "CPU" model 
 */

#include <stdio.h>
#include <string.h>

/* better to install the in include directory and use <> */
/* do not need the PLI 1.0 includes, but do not hurt */
#include "vpi_user.h"
#include "cv_vpi_user.h"

#define TRUE 1
#define FALSE 0


/* global function prototypes */
extern int my_delay_calculator(struct t_cb_data *);
extern int my_error_handler(struct t_cb_data *);
static void register_cbs(void);

/*
 * routine to calculate delays - this has dfpsetd.v connectivity built in
 *
 * real delay calculator would traverse design and process each cell type
 * according to probably some external tables
 */
int my_delay_calculator(struct t_cb_data *cbp)
{
 vpiHandle op, scope;
 s_vpi_delay drec;
 s_vpi_time delarr[12];
 s_vpi_value pval;

 /* set defparam for later evaluation to change delay control */
 /* this will change #d to #100 */ 
 op = vpi_handle_by_name("ffnand_test.d", NULL);
 /* DBG to test bad path op = vpi_handle_by_name("ffnand_test.dxx", NULL); */
 if (op == NULL)
  {
   vpi_mcd_printf(1, "**ERR unable to find instance for setting delays in");
   return(0);
  }
 pval.format = vpiIntVal;
 pval.value.integer = 100;
 vpi_put_value(op, &pval, NULL, vpiNoDelay);

 /* set ff1 r and f specparams - used to set path delays during elaboration */
 scope = vpi_handle_by_name("ffnand_test.ff1", NULL);
 op = vpi_handle_by_name("pr", scope);
 pval.format = vpiIntVal;
 pval.value.integer = 10;
 vpi_put_value(op, &pval, NULL, vpiNoDelay);

 op = vpi_handle_by_name("pf", scope);
 pval.format = vpiIntVal;
 pval.value.integer = 10;
 vpi_put_value(op, &pval, NULL, vpiNoDelay);

 op = vpi_handle_by_name("q1", scope);
 drec.da = &(delarr[0]);
 drec.no_of_delays = 2;
 drec.time_type = vpiSimTime;
 drec.mtm_flag = FALSE;
 drec.pulsere_flag = FALSE;
 drec.append_flag = FALSE;
 drec.da[0].type = vpiSimTime;
 drec.da[0].high = 0;
 drec.da[0].low = 6;
 drec.da[1].type = vpiSimTime;
 drec.da[1].high = 0;
 drec.da[1].low = 6;
 vpi_put_delays(op, &drec);

 op = vpi_handle_by_name("q2", scope);
 vpi_put_delays(op, &drec);
 
 vpi_mcd_printf(1, "... PLI delay setting complete.\n");  
 return(0);
}

/*
 * routine to build an error indication string
 * I usually start by running under debugger with breakpoint here
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

void register_cbs(void)
{
    vpiHandle href;
    p_cb_data ecbp, cbp;
    /* really need per instanc for these probably should b malloced */
    s_cb_data cbrec, ecbrec;

    /* notice cb records must be in global storage */
    ecbp = &ecbrec;
    ecbp->reason = cbPLIError;
    ecbp->cb_rtn = my_error_handler; 
    ecbp->obj = NULL;
    ecbp->time = NULL;
    ecbp->value = NULL; 
    ecbp->user_data = NULL;

    /* probably should access and emit explanatory error msg here */
    if ((href = vpi_register_cb(ecbp)) == NULL)
       vpi_printf("**ERR: can not register error handler callback.\n");

    /* register cbEndOfCompile call back */
    /* delay setting must be done here because internal net list built */
    /* so design traversal possible, but delays not yet elaborated */
    cbp = &cbrec;
    cbp->reason = cbEndOfCompile;
    cbp->cb_rtn = my_delay_calculator; 
    cbp->obj = NULL;
    cbp->time = NULL;
    cbp->value = NULL; 
    cbp->user_data = NULL;

    if ((href = vpi_register_cb(cbp)) == NULL)
       vpi_printf("**ERR: can not register end of compile callback.\n");

}

void (*vlog_startup_routines[]) () =
{
    register_cbs,
    0
};

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
