/* Copyright (c) 2011 Tachyon Design Automation */

/*
 * for every port in design check various acess methods
 *
 * FIXME - there are port expression cases for which this will core dump
 */

#include <stdio.h>
#include <string.h>

#include "vpi_user.h"
#include "cv_vpi_user.h"

#define TRUE 1
#define FALSE 0

unsigned mcd;
int (*iproc_rtn)();

/* local function prototypes */
static void process_inst(vpiHandle);
static int obj_in_iterator(vpiHandle, vpiHandle);
static char *bld_varbitnam(char *, vpiHandle);
static int is_lvalue(vpiHandle);
static vpiHandle map_lvalue_to_var(vpiHandle);
static void my_prt_vlog_info(void);
static void print_nest_argv(char **, int);

/* global function prototypes */
extern int chk_ports(vpiHandle);
extern int my_error_handler(struct t_cb_data *);
extern int my_chk_for_error(char *);
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
 my_chk_for_error("module iterate");

 isiz = vpi_get(vpiSize, topiter);
 vpi_mcd_printf(mcd, "  There are %d top level modules.\n", isiz);
 for (;;)
  {
   if ((topiref = vpi_scan(topiter)) == NULL) break;
   process_inst(topiref);
  }
 vpi_mcd_printf(mcd, "name of extra output file is [%s].\n",  
  vpi_mcd_name(mcd & ~0x1)); 
 vpi_mcd_printf(mcd,
  "  >>> All instances processed - done - using CVC PLI only for checking.\n");
 vpi_mcd_close(mcd & ~0x1);
 vpi_sim_control(vpiFinish, 0);
 return(0);
}

/*
 * process one instance and recursively process all under instances
 *
 * processing is top down depth first 
 */
static void process_inst(vpiHandle up_ihref)
{
 int isiz;
 vpiHandle iter, ihref;

 iproc_rtn(up_ihref);
 /* ignore all but bottom (no containing instances) */  
 iter = vpi_iterate(vpiModule, up_ihref);
 if ((my_chk_for_error("module iterate")) || iter == NULL) return;

 isiz = vpi_get(vpiSize, iter);
 vpi_mcd_printf(mcd, "  There are %d instances in %s.\n", isiz,
  vpi_get_str(vpiFullName, up_ihref));
 for (;;)
  {
   if ((ihref = vpi_scan(iter)) == NULL) break;
   process_inst(ihref);
  }
}

/*
 * from instance if has ports check cross and back for same object
 */
int chk_ports(vpiHandle ihref)
{
 int iconn_siz, mdprt_siz, pndx, bi, prtwid;
 int ntyp;
 vpiHandle iter, iter2, ihref2, pref, icref, mpref, varef;
 vpiHandle pbref, p2ref;
 char nnam[1025], s1[1025], s2[1025];

 /* case 1: no ports */
 if ((iter = vpi_iterate(vpiPort, ihref)) == NULL) return(0);
 /* case 2: has ports */
 for (;;)
  {
   if ((pref = vpi_scan(iter)) == NULL) break;
   pndx = vpi_get(vpiPortIndex, pref);

   strcpy(s1, vpi_get_str(vpiFullName, ihref));
   vpi_mcd_printf(mcd, "  Processing port %s.%s (index %d):\n", s1,
    vpi_get_str(vpiName, pref), pndx);

   ihref2 = vpi_handle(vpiModule, pref);
   my_chk_for_error("port handle of module");
   if (ihref2 == NULL || !vpi_compare_objects(ihref, ihref2))
    {
     vpi_mcd_printf(mcd,
      "**ERR: port %s (index %d) vpiModule (in 1-to-1 method) failed.\n",
      vpi_get_str(vpiName, pref), pndx);
    }

   /* this is up instance connection */
   icref = vpi_handle(vpiHighConn, pref);
   my_chk_for_error("high conn of port");
   /* this is down module port expression */
   mpref = vpi_handle(vpiLowConn, pref);
   my_chk_for_error("low conn of port");

   /* DBG remove ---
   if ((ntyp = vpi_get(vpiType, icref)) == vpiNet || ntyp == vpiNetBit)
    vpi_printf("Net type %d\n", vpi_get(vpiNetType, icref)); 
   if ((ntyp = vpi_get(vpiType, mpref)) == vpiNet || ntyp == vpiNetBit)
    vpi_printf("Net type %d\n", vpi_get(vpiNetType, mpref)); 
   --- */
 if ((ntyp = vpi_get(vpiType, icref)) == vpiNet || ntyp == vpiNetBit) {
     vpi_printf("    high conn: %s; net type: %d\n",
                vpi_get_str(vpiFullName, icref),
                vpi_get(vpiNetType, icref));
 }
 if ((ntyp = vpi_get(vpiType, mpref)) == vpiNet || ntyp == vpiNetBit) {
     vpi_printf("    low conn: %s; net type: %d\n",
                vpi_get_str(vpiFullName, mpref),
                vpi_get(vpiNetType, mpref));
 }

   /* check for width mismatch */
   iconn_siz = vpi_get(vpiSize, icref);
   mdprt_siz = vpi_get(vpiSize, mpref);
   if (iconn_siz != mdprt_siz)
    {
     vpi_mcd_printf(mcd,
      "--WARN: port %s (index %d) width %d but connection width %d.\n",
      vpi_get_str(vpiName, pref), pndx, mdprt_siz, iconn_siz);
    }
   /* get up net if lvalue - check to make sure net connects to port */ 
   if (!is_lvalue(icref))
    {
     vpi_mcd_printf(mcd,
      "++INFORM: port %s (index %d) connection not simple lvalue.\n",
      vpi_get_str(vpiName, pref), pndx);
    }
   else
    {
     varef = map_lvalue_to_var(icref);
     /* iterator for High Conn wire instance ports it connects to */
     /* notice in looping scanning iter, if used here will over-write */
     iter2 = vpi_iterate(vpiPortInst, varef);
     my_chk_for_error("port inst iterate");
     if (iter2 == NULL || !obj_in_iterator(iter2, pref))
      {
       strcpy(nnam, vpi_get_str(vpiName, icref));
       vpi_mcd_printf(mcd,
        "**ERR: port %s (index %d) variable %s no vpiPortInst connection.\n",
        vpi_get_str(vpiName, pref), pndx, nnam);
      }
     else
      {
       /* in CVC, this frees handle (standard needs to define) */
       if (iter2 != NULL)
        {
         vpi_free_object(iter2);
         my_chk_for_error("port inst iter2 free");
        }
       /* since for non nil case (usual), traversed iterator, must */
       /* recreate the iterator */
       iter2 = vpi_iterate(vpiPortInst, varef);
       my_chk_for_error("port inst iterate of var");
       for (;;)
        {
         if ((p2ref = vpi_scan(iter2)) == NULL) break;
         if (vpi_compare_objects(p2ref, pref)) continue; 
         strcpy(s1, vpi_get_str(vpiFullName, ihref)); 
         vpi_mcd_printf(mcd, "Also port %s.%s is a vpiPortInst.\n", s1,
          vpi_get_str(vpiName, p2ref));
        }
      }
    }

   /* get down net (ignore concatenate) - check to make sure net connects */
   if (mpref == NULL || !is_lvalue(mpref))
    {
     vpi_mcd_printf(mcd,
      "**ERR: port %s (index %d) expression not simple lvalue.\n",
      vpi_get_str(vpiName, pref), pndx);
    }
   else
    {
     varef = map_lvalue_to_var(mpref);
     /* get net's module connecting ports (usually just 1) */
     iter2 = vpi_iterate(vpiPort, varef);
     if (iter2 == NULL || !obj_in_iterator(iter2, pref))
      {
       if (mpref == NULL) strcpy(nnam, "*none*");
       else strcpy(nnam, vpi_get_str(vpiName, varef));
       vpi_mcd_printf(mcd,
        "**ERR: port %s (index %d) variable %s no vpiPortInst connection.\n",
        vpi_get_str(vpiName, pref), pndx, nnam);
      }
     else
      {
       /* in CVC, this frees handle (standard needs to define) */
       if (iter2 != NULL)
        {
         vpi_free_object(iter2);
         my_chk_for_error("port ref iter2 free");
        }
       /* since for non nil case (usual), traversed iterator, must */
       /* recreate the iterator */
       iter2 = vpi_iterate(vpiPort, varef);
       for (;;)
        {
         if ((p2ref = vpi_scan(iter2)) == NULL) break;
         if (vpi_compare_objects(p2ref, pref)) continue; 
         vpi_mcd_printf(mcd, "Also port %s is a vpiPort.\n",
          vpi_get_str(vpiName, p2ref));
        }
      }
    }
   /* final test - for every vector port - get bit high and low conns */
   if (vpi_get(vpiScalar, pref)) continue;
   vpi_printf("... processing port %s\n", vpi_get_str(vpiName, pref));
   if ((iter2 = vpi_iterate(vpiBit, pref)) == NULL)
    {    
     my_chk_for_error("port bit iterate");
     vpi_mcd_printf(mcd,
      "**ERR: vector port %s (index %d) vpiBit iterator failed.\n",
       vpi_get_str(vpiName, pref), pndx);
     continue;
    }
   /* just assuming high to low for port bits (not port connecting net) */
   prtwid = vpi_get(vpiSize, pref);
   /* bit iterators always go from lsb to msb - needed for unc. */
   for (bi = 0; bi < prtwid; bi++)
    {
     if ((pbref = vpi_scan(iter2)) == NULL) break;
     /* notice ref's here either variable or vpiNetBit or vpiRegBit */ 
     /* but for vpiPort (not port bit) conn's are expressions */
     if ((icref = vpi_handle(vpiHighConn, pbref)) == NULL) continue;
     if ((mpref = vpi_handle(vpiLowConn, pbref)) == NULL) continue;
     vpi_mcd_printf(mcd,
      "Port %d bit %d vpiLowConn %s connects to vpiHighConn %s.\n",
      pndx, bi, bld_varbitnam(s1, mpref), bld_varbitnam(s2, icref));
    }
  }
 return(0);
}

/*
 * return T if object is simple lvalue (non concatenate) 
 * can be reg 
 */
static int is_lvalue(vpiHandle xref)
{
 int xtyp;

 xtyp = vpi_get(vpiType, xref);
 switch (xtyp) {
  case vpiNet: case vpiReg: case vpiIntegerVar: case vpiTimeVar:
  case vpiNetBit: case vpiRegBit: case vpiVarSelect: case vpiMemoryWord:
  case vpiPartSelect:
   break; 
  default:
   return(FALSE);
 } 
 return(TRUE);
}

/*
 * map lvalue to variable
 *
 * for variables returns argument else for selects returns parent
 */
static vpiHandle map_lvalue_to_var(vpiHandle lvalref)
{
 int lvtyp;
 vpiHandle varef;

 lvtyp = vpi_get(vpiType, lvalref);
 switch (lvtyp) {
  case vpiNet: case vpiReg: case vpiIntegerVar: case vpiTimeVar:
   break;
  case vpiNetBit: case vpiRegBit: case vpiVarSelect: case vpiMemoryWord:
  case vpiPartSelect:
   varef = vpi_handle(vpiParent, lvalref);
   return(varef);
  default: 
   /* this is error that should never happen - will catch later */
   break;
 } 
 return(lvalref);
}

/*
 * return T if object in iterator 
 * notice this scans so must free iterator and use vpi_iterate to scan again
 */
static int obj_in_iterator(vpiHandle iter, vpiHandle obj)
{
 vpiHandle iobj;

 for (;;)
  {
   if ((iobj = vpi_scan(iter)) == NULL) break;
   if (vpi_compare_objects(iobj, obj)) return(TRUE); 
  }
 /* notice T and F constants come from veriuser.h include */ 
 return(FALSE);
}

/*
 * build a 1 bit scalar or variable bit handle full (qualified) name
 */
static char *bld_varbitnam(char *s, vpiHandle href)
{
 int i1;
 int otyp = vpi_get(vpiType, href); 
 vpiHandle ndxref, varef;
 s_vpi_value tmpval;
 char s1[1025];
 
 varef = map_lvalue_to_var(href);
 strcpy(s, vpi_get_str(vpiFullName, varef));
 if (otyp == vpiRegBit || otyp == vpiNetBit)
  {
   strcpy(s1, s);
   ndxref = vpi_handle(vpiIndex, href);
   my_chk_for_error("index handle");
   tmpval.format = vpiIntVal;
   vpi_get_value(ndxref, &tmpval);
   i1 = tmpval.value.integer;
   sprintf(s, "%s[%d]", s1, i1);
  }
 return(s);
}

/*
 * proc to check 
 * I usually start by running under debugger with breakpoint here
 */
int my_chk_for_error(char *calltochk_str)
{
    int rv;
    struct t_vpi_error_info einfotab;
    struct t_vpi_error_info *einfop;
    char s1[128];

    einfop = &einfotab;
    rv = vpi_chk_error(einfop);
    if (rv == 0) return(0);

    if (einfop->state == vpiCompile) strcpy(s1, "vpiCompile");
    else if (einfop->state == vpiPLI) strcpy(s1, "vpiPLI");
    else if (einfop->state == vpiRun) strcpy(s1, "vpiRun");
    else strcpy(s1, "**unknown**");

    /* if fatal give up */
    if (einfop->level == vpiSystem || einfop->level == vpiInternal)
      {
       vpi_printf("**FATAL: vpi state %s checking %s call - giving up\n",
        s1, calltochk_str); 
       vpi_sim_control(vpiFinish, 0);
      }


    vpi_printf("**ERR(%s) %s checking %s call (level %d) at **%s(%d):\n  %s\n",
       einfop->code, s1, calltochk_str, einfop->level, einfop->file,
       einfop->line, einfop->message);

    return(1);
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

 /* if fatal error give up - continue after vpiError */
 if (einfop->level == vpiSystem || einfop->level == vpiInternal)
  {
   vpi_printf("**FATAL: encountered System/Internal error - giving up\n");
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
  vpi_printf("**ERR: PLI 2.0 can not register error handler callback.\n");

 cbp = &cbrec2;
 cbp->reason = cbStartOfSimulation;
 cbp->cb_rtn = process_all_insts;
 cbp->obj = NULL;
 cbp->time = NULL;
 cbp->value = NULL; 
 cbp->user_data = NULL;

 /* probably should check for error here */
 if ((href2 = vpi_register_cb(cbp)) == NULL)
  vpi_printf("**ERR: PLI 2.0 can not register start of sim setup callback.\n");

 /* open a file to write to in addition to stdout and log */
 if ((mcd = vpi_mcd_open("fff9")) == 0)
  vpi_printf("***ERR: unable to open additional output file fff9\n");  
 mcd |= 5;
 /* set the processing routine */
 iproc_rtn = chk_ports;
 /* print out verilog information - mostly simulator specific */
 my_prt_vlog_info();
}

/*
 * print out simulator information to stdout and log file
 */
static void my_prt_vlog_info(void)
{
 register int i;
 s_vpi_vlog_info vlog_inf;
 p_vpi_vlog_info infp;

 /* user must provide record filled by routine */
 infp = &vlog_inf; 
 if (!vpi_get_vlog_info(infp))
  {
   vpi_printf("**ERR: call to vpi_get_vlog_info failed.\n"); 
   return;
  } 
 
 vpi_printf("--------------------------------------------------------------\n");
 vpi_printf("VLOG PRODUCT: %s - VERSION: %s\n", infp->product, infp->version); 
 if (infp->argc == 0) vpi_printf("  There are no command line arguments.\n");
 else  
  {
   for (i = 0; i < infp->argc; i++)
    {
     if (strcmp(infp->argv[i], "-f") == 0)
      {
       vpi_printf("  Argument %d: %s\n", i, infp->argv[i]); 
       vpi_printf("  Argument %d: NESTED ARGV\n", i + 1); 
       if (i + 1 < infp->argc)
        {
         print_nest_argv((char **) infp->argv[i + 1], 1);
         /* move past nested **argv structure */
         i++;
        }
      }
     else vpi_printf("  Argument %d: %s\n", i, infp->argv[i]); 
    }
  }
 vpi_printf("--------------------------------------------------------------\n");
}

/*
 * print nested argument list (recursive)
 *
 * format is -f followed by pointer to argv list with no argc but nil end
 */
static void print_nest_argv(char **argv, int lev)
{
 register int i;

 if (argv[0] == NULL)
  {
   vpi_printf("  Level %d: No Arguments\n", lev);
   return;
  }
 for (i = 0;; i++)
  {
   if (argv[i] == NULL)
    {
     vpi_printf("  Level %d: Argument %d: **NULL**\n", lev, i);
     break;
    }

   if (strcmp(argv[i], "-f") == 0)
    {
     vpi_printf("  Level %d: Argument %d: %s\n", lev, i, argv[i]); 
     vpi_printf("  Level %d: Argument %d: NESTED ARGV\n", lev, i + 1); 
     print_nest_argv((char **) argv[i + 1], lev + 1);
     i++;
    }
   else vpi_printf("  Level %d: Argument %d: %s\n", lev, i, argv[i]); 
  }
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
