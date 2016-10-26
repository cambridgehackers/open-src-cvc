/* Copyright (c) 2011 Tachyon Design Automation */

/*
 * test of get_value using value change call back mechanism 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vpi_user.h"
#include "cv_vpi_user.h"

/* added local record for saving old variable values */
struct fullpath_var_t {
 char *fullpthnam;
 s_vpi_value *oldvalp;
 struct fullpath_var_t *fullpnxt;
};

struct fullpath_var_t *full_path_vars;
int (*iproc_rtn)();

/* local function prototypes */
static void process_inst(vpiHandle); 
static void setup_1iter_chgcbs(vpiHandle);
static void setup_1task_chgcbs(vpiHandle);
static struct fullpath_var_t *find_add_fullpath_var(char *);
static char *vpival_to_str(char *, p_vpi_value, int);

/* global function prototypes */
extern int process_all_insts(struct t_cb_data *);
extern int setup_varchgcbs(vpiHandle);
extern int my_prt3_vchg(p_cb_data);
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
 * user cb routine handles getting values and time
 */
static void setup_1iter_chgcbs(vpiHandle iter)
{
 vpiHandle href;
 p_cb_data cbp;
 p_vpi_time timp;
 p_vpi_value valp;

 for (;;)
  {
   if ((href = vpi_scan(iter)) == NULL) break;

   /* notice this must persistent until cb removed */
   cbp = (p_cb_data) malloc(sizeof(s_cb_data));
   cbp->reason = cbValueChange;
   cbp->cb_rtn = my_prt3_vchg;  

   /* do not care about time or value - but must set to unused */
   /* nil here according to the standard causes core dump? */
   cbp->obj = href; 
   timp = (p_vpi_time) malloc(sizeof(s_vpi_time));
   timp->type = vpiSuppressTime;
   cbp->time = timp;
   valp = (p_vpi_value) malloc(sizeof(s_vpi_value)); 
   valp->format = vpiSuppressVal;
   cbp->value = valp;
   cbp->index = 0;

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
 *
 * since just print can reuse one handle
 */
int my_prt3_vchg(p_cb_data cbp)
{
 int blen;
 s_vpi_value val;
 s_vpi_time tim;
 struct fullpath_var_t *varp;
 char s1[1024], s2[1024], s3[1024];

 /* convert new value to string */
 val.format = vpiObjTypeVal;
 vpi_get_value(cbp->obj, &val); 
 blen = vpi_get(vpiSize, cbp->obj);
 vpival_to_str(s3, &val, blen);

 strcpy(s1, vpi_get_str(vpiFullName, cbp->obj));

 /* this will create first time variable changes */
 varp = find_add_fullpath_var(s1);   
 /* naybe should use x for first old value */
 if (varp->oldvalp == NULL) strcpy(s2, "<unknown>");
 else vpival_to_str(s2, varp->oldvalp, blen);

 tim.type = vpiScaledRealTime;
 vpi_get_time(cbp->obj, &tim);

 vpi_printf("--> now %g: %s changed from %s to %s.\n", tim.real,  
  s1, s2, s3);

 /* save old value - notice memory leak for malloced fields inside */
 /* s_vpi_val struct - should free */
 if (varp->oldvalp == NULL)
  varp->oldvalp = (p_vpi_value) malloc(sizeof(s_vpi_value));
 *(varp->oldvalp) = val;
 return(0);
}

/*
 * find-add value to symbol table - return NULL if first time seen
 *
 * note: should use hashing or binary search for this symbol table
 */
static struct fullpath_var_t *find_add_fullpath_var(char *s)
{
 register struct fullpath_var_t *varp, *last_varp;

 last_varp = NULL;
 for (varp = full_path_vars; varp != NULL; varp = varp->fullpnxt)
  {
   if (strcmp(varp->fullpthnam, s) == 0)
    return(varp); 
   last_varp = varp;
  }
 varp = (struct fullpath_var_t *) malloc(sizeof(struct fullpath_var_t));
 varp->fullpthnam = malloc(strlen(s) + 1);
 strcpy(varp->fullpthnam, s);
 varp->oldvalp = NULL;
 varp->fullpnxt = NULL;

 if (last_varp == NULL) full_path_vars = varp;
 else last_varp->fullpnxt = varp;
 return(varp);
}

static char *vpival_to_str(char *s, p_vpi_value valp, int blen)
{
 register int i;
 int numvals;
 char s1[1024];

 switch (valp->format) {
  case vpiBinStrVal: case vpiOctStrVal: case vpiDecStrVal: case vpiHexStrVal:
  case vpiStringVal:
   strcpy(s, valp->value.str);
   break;
  case vpiScalarVal:
   if (valp->value.scalar < 2) sprintf(s, "%x", valp->value.scalar);
   else if (valp->value.scalar == 3) strcpy(s, "x");
   else if (valp->value.scalar == 2) strcpy(s, "z");
   else strcpy(s, "?");  
   break;
  case vpiIntVal:
   sprintf(s, "%d", valp->value.integer);
   break;
  case vpiRealVal:
   sprintf(s, "%g", valp->value.real);
   break;
  case vpiVectorVal:
   /* not bothing to build a Verilog style value - just printing pairs */ 
   /* assuming int type always 32 bits */ 
   numvals = (blen + 31) >> 5;
   /* notice t_vpi_vecval is really array of the 2 integer a/b sections */
   strcpy(s, "");
   for (i = numvals - 1; i >= 0; i--)
    {
     sprintf(s1, "(av=%x,bv=%x)", valp->value.vector[i].aval,
      valp->value.vector[i].bval);
     strcat(s, s1);
    }
   break;
  case vpiStrengthVal:
   sprintf(s, "<s0=%d,s1=%d,v=%d>", valp->value.strength->s0,
    valp->value.strength->s1, valp->value.strength->logic);
   break;
  case vpiTimeVal:
   if (valp->value.time->type == vpiScaledRealTime)
    sprintf(s, "%f", valp->value.time->real);
   else sprintf(s, "%d", valp->value.time->low);
   break;
  case vpiObjTypeVal: case vpiSuppressVal:
   vpi_printf(
    "**ERR: can not copy vpiObjTypeVal or vpiSuppressVal formats - not for filled records.\n");
   return(NULL);
  default: 
   vpi_printf(
    "**ERR: can not copy t_vpi_value record - format code %d illegal.\n",
   valp->format);
  return(NULL);
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
 iproc_rtn = setup_varchgcbs;

 /* my variable initializes */
 full_path_vars = NULL;
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
