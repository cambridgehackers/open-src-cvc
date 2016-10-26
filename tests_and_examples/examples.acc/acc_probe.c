/* Copyright (c) 2011 Tachyon Design Automation */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <veriuser.h>
#include <cv_veriuser.h>
#include <acc_user.h>

#define MAXSIZE 500 
/* #define MAXSIZE 1 */

/* up to 10 parameters, MAXSIZE time values up to 64 bits long */ 
/* but must be vector */ 
/* (16 chars plus 0 end byte) */
static char value_ar[10][MAXSIZE][17];  
static int time_ar[MAXSIZE];
static int *udata_ar;

static int total_nump;
static int last_entry = 0;
static int setup_errors = FALSE;
static handle setup_inst_p = NULL; 

/* local function prototypes */
static void vu_setup_values(void);
static int vu_update_values(p_vc_record);
static void vu_doupdate(handle, int);
static void vu_flash_values(void);

static void vu_setup_checktf(int data, int reason)
{
 register int nparam;
 int htyp;
 handle argh, instref;

 acc_initialize();

 total_nump = tf_nump();
 /* get the setup instance for updating values */
 instref = acc_handle_tfinst();
 if (acc_error_flag)
  {
   tf_error("in vu_setup_check: acc_handle_tfinst failed.");
   setup_errors = TRUE;
  }
 for (nparam = 1; nparam <= total_nump; nparam++)
  { 
   argh = acc_handle_tfarg(nparam);
   htyp = acc_fetch_type(argh);
   /* variables autmotically legal */  
   if (htyp == accIntegerVar || htyp == accTimeVar) continue;

   if (htyp != accNet && htyp != accReg)
    {
     tf_error(
      "in vu_setup_check: argument pos. %d illegal - must be a variable");
     setup_errors = TRUE;
     continue;
    }
 
   /* net or reg must be vector */
   if (acc_fetch_size(argh) == 1)
    {
     tf_error(
      "in vu_setup_check: argument %s (pos. %d) illegal - must be vector",
      acc_fetch_name(argh), nparam);
     setup_errors = TRUE;
    }
  }
 acc_close();
}

/*
 * calltf routine called when $setup_value called
 */
static void vu_setup_values(void)
{
 register int nparam;
 handle argh;

 acc_initialize();
 if (setup_errors)
  {
   tf_error(
   "$setup_values did not setup value flashing - previous error");
   return;
  }
 acc_initialize();
 /* get total number of parameters */
 total_nump = tf_nump();

 /* get the setup instance for updating values */
 setup_inst_p = acc_handle_tfinst();
 if (acc_error_flag) tf_error("in vu_setup_value: acc_handle_tfinst failed.");
  
 last_entry = 0; 

 /* if this is a second call to setup and asynchronous updating has been */
 /* disabled then resume the asynchronous calls */
 /* notice acc_ pnums start at 1 */
 udata_ar = (int *) malloc((total_nump + 1)*sizeof(int)); 
 for (nparam = 1; nparam <= total_nump; nparam++)
 { 
  argh = acc_handle_tfarg(nparam);
  udata_ar[nparam] = nparam;
  /* setup call back */
  acc_vcl_add(argh, vu_update_values, (char *) &(udata_ar[nparam]),
   vcl_verilog_logic);  
  /* save initial value */
  vu_doupdate(argh, nparam);
 }
 acc_close();
}
 
/* 
 * here updating on any value change not just one at end of time slot
 */
static int vu_update_values(p_vc_record vcrp)
{
 handle argh;
 int pnum;
 char s1[1024];

 acc_initialize();
 /* SJM 01/10/02 - model was wrong - acc user_data is char - need cast */
 pnum = *((int *) (vcrp->user_data));
 argh = acc_handle_itfarg(pnum, setup_inst_p);
 if (acc_error_flag)
  {
   tf_error("in vu_update_values: acc_handle_itfarg failed.");
   return(0);
  }
 strcpy(s1, acc_fetch_name(argh));
 io_printf("now %d parameter %d (name is %s) changed\n", tf_gettime(), pnum,
  s1);
 vu_doupdate(argh, pnum);
 acc_close();
 return(0);
}

/*
 * update the value - version that does not use vcl info
 */
static void vu_doupdate(handle argh, int nparam)
{
 handle argh2;

 /* if flash table filled - emit error and remove callback from every arg */
 if (++last_entry == MAXSIZE)
  {
   io_printf("*** flash table filled - removing value change vcls ***\n");
   for (nparam = 1; nparam <= total_nump; nparam++)
    { 
     argh2 = acc_handle_tfarg(nparam);
     /* remove vcl */
     acc_vcl_delete(argh2, vu_update_values, (char *) &(udata_ar[nparam]),
      vcl_verilog_logic);  
    }
   return;
  } 
 /* after vcl's removed do nothing - LOOKATME - but think should get here */
 if (last_entry > MAXSIZE) return;

 /* obtain current simulation time */ 
 time_ar[last_entry] = tf_gettime();
 /* FIXME - also test acc_fetch_tfarg_str */
 strcpy(value_ar[nparam][last_entry], acc_fetch_value(argh, "%d", NULL));
 io_printf("** now %d assign %s to param %d\n", time_ar[last_entry],
  value_ar[nparam][last_entry], nparam);
}

/* this routine displays the values of variables at a given time */
static void vu_flash_values(void)
{
 int nparam, find_time, entry_num;

 if (last_entry >= MAXSIZE)
  {
   io_printf("*** flash table filled - values not flashed ***\n");
   return;
  }

 acc_initialize();
 /* get the value of time which is the only param */
 find_time = tf_getp(1);
 for (entry_num = last_entry; (entry_num > 0); entry_num--)
  if (time_ar[entry_num] <= find_time)
   break;
 io_printf("For time %d\n", find_time);
 /* this needs to go from 1 to number of params since task not func */ 
 for (nparam = 1; nparam <= total_nump; nparam++)
  io_printf("    value of parameter %d = %s\n", nparam,
   value_ar[nparam][entry_num]);
 acc_close();
} 

s_tfcell veriusertfs[] = {
 {usertask, 0, (int (*)()) vu_setup_checktf, 0, (int (*)()) vu_setup_values,
  0, "$setup_values", 0 }, 
 {usertask, 0, 0, 0, (int (*)()) vu_flash_values, 0, "$flash_values", 0 }, 
 {0} /* this line must always be last */
};

/* dummy +loadpli1 boostrap routine - return old style veriusertfs tab */
s_tfcell *pli1_compat_bootstrap(void)
{
 return(veriusertfs);
}
