/* Copyright (c) 2011 Tachyon Design Automation */

/*
 * test of continous assign (decomposition and handle by lookup routines) 
 *
 * unit test of various ways to process lavlue expressions
 * test does nothing
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
static int decompose_expr(vpiHandle, int);

/* global function prototypes */
extern void register_scan_cb();
extern int process_contas(vpiHandle);
extern int my_error_handler(struct t_cb_data *);
extern void register_scan_cb(void);

/*
 * process all instances calling processing routine for each
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
 * process all continuous assignments
 */
int process_contas(vpiHandle ihref)
{
 vpiHandle iter, caref, lhsref, rhsref;
 
 if ((iter = vpi_iterate(vpiContAssign, ihref)) == NULL) return(0);
 for (;;)
  {
   if ((caref = vpi_scan(iter)) == NULL) break;
   lhsref = vpi_handle(vpiLhs, caref); 
   if (!decompose_expr(lhsref, TRUE))
    vpi_printf("  Why is concatenate left hand side not lvalue at **%s(%d)\n",  
     vpi_get_str(vpiFile, caref), vpi_get(vpiLineNo, caref)); 

   rhsref = vpi_handle(vpiRhs, caref); 
   decompose_expr(rhsref, FALSE);
  }
 return(0);
}

/*
 * process an expression - build most decomposed handles and print each
 * also look up names and compare to original handle
 */
static int decompose_expr(vpiHandle xref, int islhs)
{
 register int i;
 int xtyp, otyp, bad_lvalue, ps1, ps2, i2;
 vpiHandle varef, varef2, iter, scopref, ndxref, href, xref2;
 s_vpi_value tmpval;
 char nam[1025];

 xtyp = vpi_get(vpiType, xref);
 /* case 1: all lvalues except concatenate */
 if (xtyp != vpiOperation && xtyp != vpiConstant)
  {
   varef = xref;

   /* get scope for selects, need to get scope from parent */
   if (xtyp == vpiNetBit || xtyp == vpiRegBit || xtyp == vpiPartSelect)
    {
     varef = vpi_handle(vpiParent, varef);
     scopref = vpi_handle(vpiScope, varef);
     strcpy(nam, vpi_get_str(vpiName, varef)); 
    }
   else
    {
     scopref = vpi_handle(vpiScope, varef);
     /* test handle by name */
     /* strcpy(nam, vpi_get_str(vpiName, varef)); */ 
     strcpy(nam, vpi_get_str(vpiName, varef)); 
    }  
   
   /* if ((varef2 = vpi_handle_by_name(nam, NULL)) == NULL) */
   if ((varef2 = vpi_handle_by_name(nam, scopref)) == NULL)
    {
     vpi_printf("--- why is variable %s not in scope %s?\n", nam,
      vpi_get_str(vpiFullName, scopref));
     return(TRUE);
    }

   if (!vpi_compare_objects(varef, varef2))  
    vpi_printf("--- why did handle by name not return same object (%s)?\n",
     vpi_get_str(vpiFullName, varef));

   if (xtyp == vpiPartSelect)
    {
     ndxref = vpi_handle(vpiLeftRange, xref);
     tmpval.format = vpiIntVal;
     vpi_get_value(ndxref, &tmpval);
     ps1 = tmpval.value.integer;
     ndxref = vpi_handle(vpiRightRange, xref);
     tmpval.format = vpiIntVal;
     vpi_get_value(ndxref, &tmpval);
     ps2 = tmpval.value.integer;
     /* notice not normalized to h:0 form */
     if (ps1 > ps2) { i2 = ps1; ps1 = ps2; ps2 = i2; } 
     for (i = ps2; i >= ps1; i--)
      {
       /* notice must index variable part selected from not part select */
       href = vpi_handle_by_index(varef, i);
       ndxref = vpi_handle(vpiIndex, href);
       tmpval.format = vpiIntVal;
       vpi_get_value(ndxref, &tmpval);
       i2 = tmpval.value.integer;
       if (i2 != i)
        {
         vpi_printf(
          "--- part select index of %s by one method %d and by other %d\n",
          vpi_get_str(vpiFullName, varef), i2, i);
        } 
       else
        {
         vpi_printf("  Part select %s index %d processed.\n",
          vpi_get_str(vpiFullName, varef), i2);
        }
      }
    }
   else if (xtyp == vpiNetBit || xtyp == vpiRegBit)
    {
     ndxref = vpi_handle(vpiIndex, xref);
     tmpval.format = vpiIntVal;
     vpi_get_value(ndxref, &tmpval);
     i = tmpval.value.integer;
     href = vpi_handle_by_index(varef, i);
     ndxref = vpi_handle(vpiIndex, href);
     tmpval.format = vpiIntVal;
     vpi_get_value(ndxref, &tmpval);
     i2 = tmpval.value.integer;
     if (i2 != i)
      {
       vpi_printf("--- index of %s by one method %d and by other %d\n",
        vpi_get_str(vpiFullName, varef));
      }
     else
      {
       vpi_printf("  Bit select %s index %d processed.\n",
        vpi_get_str(vpiFullName, varef), i2);
      }
    }
   else vpi_printf("  Variable %s processed.\n",
    vpi_get_str(vpiFullName, varef), i2);
   return(TRUE);
  }
 /* non lvalue expression just ignore */
 if (xtyp != vpiOperation) return(FALSE);
 otyp = vpi_get(vpiOpType, xref); 
 if (otyp != vpiConcatOp) return(FALSE);

 vpi_printf(" --- processing a concatenate:\n");
 /* case 2: concatenate - notice use expr. handle not concat operator */
 iter = vpi_iterate(vpiOperand, xref);
 for (bad_lvalue = FALSE;;)
  {
   if ((xref2 = vpi_scan(iter)) == NULL) break;
   if (!decompose_expr(xref2, islhs)) bad_lvalue = TRUE;
  }
 vpi_printf(" === end of concatenate\n");
 return(!bad_lvalue);
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
 iproc_rtn = process_contas;
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
