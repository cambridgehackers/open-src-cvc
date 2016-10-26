/* Copyright (c) 2011 Tachyon Design Automation */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "veriuser.h"
#include "cv_veriuser.h"
 
#define MAXSIZE 500
/* upto 10 parameters, MAXSIZE time values upto 64 bits long */ 
/* (16 chars plus 0 end byte) */
static char value_ar[10][MAXSIZE][17];  

static int time_ar[MAXSIZE];
static int total_nump;
static int last_entry = 0;
static char *setup_inst_p; 

/* local function prototypes */
static void vu_setup_values(void);
static void vu_update_values(int, int, int);
static void vu_doupdate(void);
static void vu_flash_values(void);

static void vu_setup_values(void)
{
 int nparam;

 s_tfexprinfo einfo_s;
 p_tfexprinfo info_p = &einfo_s;
 /* get total number of parameters */
 total_nump = tf_nump();
 /* get the setup instance for updating values */
 setup_inst_p = tf_getinstance();
 /* if this is a second call to setup and asynchronous updating has been */
 /* disabled then resume the asynchronous calls */
 tf_asynchon();
 for (nparam = 1; nparam <= total_nump; nparam++)
 { 
  /* check param lengths */
  tf_exprinfo(nparam, info_p);
  if (info_p->expr_ngroups > 2)
   {
    tf_error("parameters msut be less than 65 bits");
   }
 }
 /* save initial values */
 last_entry = 0; 
 vu_doupdate();
}

/* this routine is aynchronously called during simulation */
static void vu_update_values(int data, int reason, int pnum)
{
 /* test reason called */ 
 if (reason == reason_paramvc)
  {
   io_printf("now %d parameter %d changed - reason paramvc_sync\n",
    tf_gettime(), pnum);
   tf_synchronize();
  }
 else if (reason == reason_synch)
  {
   io_printf("now %d misctf called for #0 reason_sync\n", tf_gettime());
   vu_doupdate();
  }
}

static void vu_doupdate(void)
{
 int nparam;

 if (++last_entry == MAXSIZE)
  {
   /* the array is full. stop calling this routine */
   tf_asynchoff();
   return;
  } 
 /* obtain current simulation time */ 
 time_ar[last_entry] = tf_gettime();
 for (nparam = 1; nparam <= total_nump; nparam++)
  /* obtain hex value of the parameter number nparam */
  {
  strcpy(value_ar[nparam][last_entry], tf_istrgetp(nparam, 'h', setup_inst_p));
   io_printf("** now %d assign %s to param %d\n", time_ar[last_entry],
   value_ar[nparam][last_entry], nparam);
  }
}

/* this routine displays the values of variables at a given time */
static void vu_flash_values(void)
{
 int nparam, find_time, entry_num;
 /* get the value of time which is the only param */
 find_time = tf_getp(1);
 for (entry_num = last_entry; (entry_num > 0); entry_num--)
  if (time_ar[entry_num] <= find_time)
   break;
 io_printf("For time %d\n", find_time);
 /* this needs to go from 1 to number of params since task not func */ 
 for (nparam = 1; nparam <= total_nump; nparam++)
  io_printf("    value of parameter %d = %s\n", 
   nparam, value_ar[nparam][entry_num]);
} 

s_tfcell veriusertfs[] =
{
 {usertask, 0,
  0, 0, (int (*)()) vu_setup_values, (int (*)()) vu_update_values,
  "$setup_values", 0 }, 
 {usertask, 0,
  0, 0, (int (*)()) vu_flash_values, 0,
  "$flash_values", 0 }, 
 {0} /* this line must always be last */
};

/* dummy +loadpli1 boostrap routine - return old style veriusertfs tab */
s_tfcell *pli1_compat_bootstrap(void)
{
 return(veriusertfs);
}
