/* Copyright (c) 2011 Tachyon Design Automation */

/* vpi put value and tf_ style system task emulation test */
/* also shows how to keep track of one vpi_ task called from multiple */
/* instances */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vpi_user.h"
#include "cv_vpi_user.h"

/* should allocate dynamically depending on number of instances */
/* my local storage */
struct t_my_instid {
 int id;
 char *ifullnam;
};

vpiHandle last_schd_evh[100];
char *instnam_tab[100]; 
int last_evh;

/* local function prototypes */
static int getadd_inst_id(vpiHandle);
static vpiHandle get_vpi_driver(vpiHandle);
static p_vpi_value bld_valrec(p_vpi_value, int);

/* global function prototypes */
extern int vsetval(PLI_BYTE8 *);
extern int my_error_handler(struct t_cb_data *);
extern void register_my_systfs(void); 
extern void register_cbs(void);

/*
 * set a variable to value after delay
 *
 * form: vsetval([net/reg[bit] lvalue], value, delay, [optional delay mode]);
 * shows code similar to PLI 1.0 tf_strdelputp or tf_setdelay and tf_putp
 *
 * if put value event scheduled, sets global, call with no schedule leaves
 * last as it was
 *
 * here task follows Verilog semantics where only 1 set of of storage
 * even if multiple calls in one instance
 */
int vsetval(PLI_BYTE8 *pargs)
{
 int numargs, inst_id, vtyp, flags;
 vpiHandle href, mhref, iter, aref, lvalref, assign_ref; 
 p_vpi_value valp;
 s_vpi_value tmpval;
 p_vpi_time timp;
 char putv_type[128];

 /* get the task call handle */
 href = vpi_handle(vpiSysTfCall, NULL); 
 /* need vpiModule (instance) call in handle */ 
 mhref = vpi_handle(vpiScope, href);
 /* if $vsetval task invoked from system task, get module task def. in */  
 if (vpi_get(vpiType, mhref) != vpiModule)
  mhref = vpi_handle(vpiModule, mhref); 
 inst_id = getadd_inst_id(mhref);
 
 iter = vpi_iterate(vpiArgument, href);

 /* not sure if vpiSize property really in standard for iterators */
 numargs = vpi_get(vpiSize, iter);

 /* should set flags and check each inst first time called */
 /* or maybe better just save processed arg handles */
 /* 4th delay type name as string optional */
 if (iter == NULL || numargs < 3)
  {
bad_args:
   vpi_printf(
    "**ERR: $vsetval bad args, form: (net/reg[bit], value, time, [delay type])\n");
   return(0);
  }
 /* know iterator components must be expressions */
 /* first argument assigned to lvalue */
 if ((lvalref = vpi_scan(iter)) == NULL) goto bad_args;

 vtyp = vpi_get(vpiType, lvalref);
 /* must be lvalue */ 
 /* notice not allowing assignment to part select handle */
 /* could add part select assignments by decomposing to bit handles */ 
 if (vtyp == vpiMemoryWord || vtyp == vpiConstant || vtyp == vpiOperation
  || vtyp == vpiPartSelect) goto bad_args; 

 if ((aref = vpi_scan(iter)) == NULL) goto bad_args;
 /* idea here is let passed value object (net) type determine format */
 /* notice because get value uses internal reused works */
 tmpval.format = vpiObjTypeVal;
 vpi_get_value(aref, &tmpval);
 /* size is size of passed rhs new value expression */
 valp = bld_valrec(&tmpval, vpi_get(vpiSize, aref));

 if ((aref = vpi_scan(iter)) == NULL) goto bad_args;
 tmpval.format = vpiTimeVal;
 vpi_get_value(aref, &tmpval);
 timp = (p_vpi_time) malloc(sizeof(s_vpi_time));
 *timp = *(tmpval.value.time);

 /* if 4th arg omitted - assume inertial */
 if ((aref = vpi_scan(iter)) != NULL)
  {
   /* since user file needs vpi_user.h anyway, should use numeric constant */
   tmpval.format = vpiStringVal; 
   vpi_get_value(aref, &tmpval);
   strcpy(putv_type, tmpval.value.str); 
   if (strcmp(putv_type, "vpiInertialDelay") == 0)
    flags = vpiInertialDelay;  
   else if (strcmp(putv_type, "vpiTransportDelay") == 0)
    flags = vpiTransportDelay;  
   else if (strcmp(putv_type, "vpiPureTransportDelay") == 0)
    flags = vpiPureTransportDelay;  
   else if (strcmp(putv_type, "vpiNoDelay") == 0) flags = vpiNoDelay;
   else if (strcmp(putv_type, "vpiForceFlag") == 0) flags = vpiForceFlag;
   else if (strcmp(putv_type, "vpiReleaseFlag") == 0) flags = vpiReleaseFlag;
   else if (strcmp(putv_type, "vpiCancelEvent") == 0) flags = vpiCancelEvent;
   else goto bad_args;
  }
 else { strcpy(putv_type, "vpiInertialDelay"); flags = vpiInertialDelay; }

 /* allocate driver handle if non reg and non force/release/deschedule flag */
 if (vtyp == vpiNet || vtyp == vpiNetBit)
  {
   if (flags == vpiInertialDelay || flags == vpiTransportDelay
    || flags == vpiPureTransportDelay || flags == vpiNoDelay)
    {
     if ((assign_ref = get_vpi_driver(lvalref)) == NULL)
      {
       if ((assign_ref = vpi_put_value(lvalref, NULL, NULL, vpiAddDriver))
        == NULL) goto bad_args;
      }
    }
   else assign_ref = lvalref; 
  }
 /* for non wire lval and assign handles same */
 else assign_ref = lvalref; 

 if (flags == vpiInertialDelay)
  {
   /* works because already replaced lvalue with driver for wires */  
   last_schd_evh[inst_id] = vpi_put_value(assign_ref, valp, timp,
    flags | vpiReturnEvent);
  }
 else if (flags == vpiTransportDelay)
  {
   last_schd_evh[inst_id] = vpi_put_value(assign_ref, valp, timp,
    flags | vpiReturnEvent);
  }
 else if (flags == vpiPureTransportDelay)
  {
   last_schd_evh[inst_id] = vpi_put_value(assign_ref, valp, timp,
    flags | vpiReturnEvent);
  }
 else if (flags == vpiNoDelay)
  { 
   vpi_put_value(assign_ref, valp, NULL, vpiNoDelay);
  }
 else if (flags == vpiForceFlag)
  {
   /* here need wire not vpi_ added driver */
   vpi_put_value(lvalref, valp, NULL, vpiForceFlag);
  }
 /* here, value after release placed in valp - better be big enough */
 else if (flags == vpiReleaseFlag)
  {
   vpi_put_value(lvalref, valp, NULL, vpiReleaseFlag);
  }
 else if (flags == vpiCancelEvent) 
  {
   /* cancel last scheduled event if has not yet happened */
   if (last_schd_evh[inst_id] == NULL
    || !vpi_get(vpiScheduled, last_schd_evh[inst_id]))
     {
      vpi_printf(
       "**WARN: no previous scheduled event or previous event occurred\n");
     }
    /* for wire this will be event from driver assign */
    /* for vector this is table handle with even (if present) per bit */
    else vpi_put_value(last_schd_evh[inst_id], NULL, NULL, vpiCancelEvent);
  }
 else goto bad_args;
 return(0);
}

/*
 * get a vpi driver
 *
 * for vpiNetBit must be smae bit driver 
 * for vpiNet must be entire net driver
 */
static vpiHandle get_vpi_driver(vpiHandle wref)
{
 int wtyp, drvtyp;
 vpiHandle drviter, drvref, parref;
 s_vpi_value tmpval;
 char sval[1024], s1[1024];
 
 /* need to provide string storage for get value */
 tmpval.value.str = sval;

 wtyp = vpi_get(vpiType, wref);
 drviter = vpi_iterate(vpiDriver, wref);
 for (;;)
  {
   if ((drvref = vpi_scan(drviter)) == NULL) break;

   drvtyp = vpi_get(vpiType, drvref);
   if (wtyp == vpiNetBit)
    {
     if (drvtyp != vpiNetBitDriver) continue;
     parref = vpi_handle(vpiParent, drvref); 
     if (vpi_compare_objects(wref, parref))
      {
       strcpy(s1, vpi_get_str(vpiType, drvref));
       tmpval.format = vpiBinStrVal; 
       vpi_get_value(drvref, &tmpval);
       vpi_printf("reusing %s bit driver of %s current value %s.\n",
        s1, vpi_get_str(vpiFullName, parref), tmpval.value.str);

       return(drvref);
      }
    }
   else if (wtyp == vpiNet)
    {
     if (drvtyp != vpiNetDriver) continue;

     strcpy(s1, vpi_get_str(vpiType, drvref));
     tmpval.format = vpiBinStrVal; 
     vpi_get_value(drvref, &tmpval);
     vpi_printf("reusing %s entire net driver of %s current value %s.\n",
      s1, vpi_get_str(vpiFullName, wref), tmpval.value.str);

     return(drvref);
    }
   else
    { 
     vpi_printf("**ERR: illegal value %s passed to get_vpi_driver.\n",
      vpi_get_str(vpiType, wref));
     return(NULL);
    }
  }
 strcpy(s1, vpi_get_str(vpiType, wref));
 vpi_printf("new driver added for %s %s.\n", s1,
  vpi_get_str(vpiFullName, wref));
 return(NULL);
}

/*
 * add-get unique instance index
 *
 * better to use hashing or or least sorted array here
 * or, if an iterator to get all instances of a given were added to P1364
 * standard, this could be just a table index
 */
static int getadd_inst_id(vpiHandle mhref)
{
 register int i;
 char *chp;
 
 chp = vpi_get_str(vpiFullName, mhref);
 for (i = 0; i <= last_evh; i++)  
  { if (strcmp(instnam_tab[i], chp) == 0) return(i); }
 instnam_tab[++last_evh] = malloc(strlen(chp) + 1);
 strcpy(instnam_tab[last_evh], chp);
 return(last_evh);
} 

/*
 * routine to allocate and copy a t_vpi_value record
 *
 * needed because t_vpi_value filled value fields use one internal 
 * buffer that is over-written by next call to vpi_get_value
 *
 * if passed non valp will probably crash
 * needs width only for vpiVectorVal format, ignored otherwise
 */
static p_vpi_value bld_valrec(p_vpi_value valp, int blen)
{
 int numvals;
 s_vpi_value wrkval;
 p_vpi_value newvalp;

 /* copy to avoid need to fill non pointer cases */
 wrkval = *valp;
 switch (valp->format) {
  case vpiBinStrVal: case vpiOctStrVal: case vpiDecStrVal: case vpiHexStrVal:
  case vpiStringVal:
   wrkval.value.str = malloc(strlen(valp->value.str) + 1);
   strcpy(wrkval.value.str, valp->value.str);
   break;
  case vpiScalarVal: case vpiIntVal: case vpiRealVal:
   break;  
  case vpiVectorVal:
   /* assuming int type always 32 bits */ 
   numvals = (blen + 31) >> 5;
   /* notice t_vpi_vecval is really array of the 2 integer a/b sections */
   wrkval.value.vector = (p_vpi_vecval) malloc(numvals*sizeof(s_vpi_vecval));
#ifdef __sparc__
   /* notice this copies from arg1 to arg2 */
   bcopy((char *) valp->value.vector, (char *) wrkval.value.vector,
    numvals*sizeof(s_vpi_vecval));
#else
   memmove((char *) wrkval.value.vector, (char *) valp->value.vector,
    numvals*sizeof(s_vpi_vecval));
#endif
   break;
  case vpiStrengthVal:
   wrkval.value.strength = (p_vpi_strengthval)
    malloc(sizeof(s_vpi_strengthval));
   *(wrkval.value.strength) = *(valp->value.strength);
   break;
  case vpiTimeVal:
   wrkval.value.time = (p_vpi_time) malloc(sizeof(s_vpi_time));
   *(wrkval.value.time) = *(valp->value.time);
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
 newvalp = (p_vpi_value) malloc(sizeof(s_vpi_value));
 *newvalp = wrkval;
 return(newvalp);
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
 register int i;
 vpiHandle href;
 struct t_cb_data *ecbp, cbrec;

 /* notice cb records must be in global storage */
 ecbp = &cbrec;
 ecbp->reason = cbPLIError;
 ecbp->cb_rtn = my_error_handler; 
 ecbp->obj = NULL;
 ecbp->time = NULL;
 ecbp->value = NULL; 
 ecbp->user_data = NULL;

 if ((href = vpi_register_cb(ecbp)) == NULL)
  vpi_printf("**ERR: can not regiser register error handler callback.\n");

 /* my variable initialization can go here */
 for (i = 0; i < 100; i++) last_schd_evh[i] = NULL; 
 last_evh = -1;
}

/* Template function table for added user systf tasks and functions.
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
void register_my_systfs(void)
{
 p_vpi_systf_data systf_data_p;

 /* use predefined table form - could fill systf_data_list dynamically */
 static s_vpi_systf_data systf_data_list[] = {
  { vpiSysTask, 0, "$vsetval", vsetval, NULL, NULL, NULL },
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
