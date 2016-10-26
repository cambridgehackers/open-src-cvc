/* Copyright (c) 2011 Tachyon Design Automation */

/* 
 * example illustrating using PLI tf_ utility routines to fill memory
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "veriuser.h"
#include "cv_veriuser.h"

/* define this to use CVC's immediate assign tf_strputp routine */
/* #define __HAS_STRPUTP__ */

int memsiz, memwid, last_i;
FILE *memval_s;

/* local prototypes */
int intsize(int, int);
static void plisetupmemfill(int, int);
static void check_plimemfill(int, int);
static void plimemfill(int, int);

int intsize(int data, int reason)
{
 return(32);
}

/*
 * routine to setup memory filling routine - set param to 0 on error else 1
 * function: $plisetupmemfill(memsiz, memwid)
 */
static void plisetupmemfill(int data, int reason)
{
 char *chp;

 /* get file name as + verilog argument */
 if ((chp = mc_scan_plusargs("memfile+")) == NULL || strcmp(chp, "") == 0)
  {
   tf_error("missing or empty +memfile+[file name] memory file argument");
   tf_putp(0, 0);
   return;
  }
 /* open the file */
 if ((memval_s = fopen(chp, "r")) == NULL)
  {  
   tf_error("unable to open +memfile+ memory file %s", chp); 
   tf_putp(0, 0);
   return;
  }
 /* need memory size for checking */
 memsiz = tf_getp(1);
 memwid = tf_getp(2);
 tf_putp(0, 1);
 /* assume memory goes from 1 to size */
 last_i = 0; 
}

/*
 * check the fill memory user PLI function
 * notice calling tf_error here will inhibit simulation
 * probably sould also check 2nd index argument 
 */
static void check_plimemfill(int data, int reason)
{
 struct t_tfexprinfo xinfo;

 if (tf_nump() != 2)
  {
   tf_error("$pli_memfill has %d arguments - 2 required", tf_nump());
   return;
  }
 tf_exprinfo(1, &xinfo);
 if (xinfo.expr_type != TF_RWMEMSELECT)
  {
   tf_error("$pli_memfill first argument not read/write memory select");
   return;
  }
}

/*
 * routine to set memory 
 * function: $pli_memfill(mem[i], i)
 */
static void plimemfill(int data, int reason)
{
 int i;
 char memval[1024];

 i = tf_getp(2);
 if (i < 0 || i > memsiz) 
  {
   tf_error("cannot fill memory location %d - memory has only %d cells");
   tf_putp(0, 0);
   return;
  }
 if (fscanf(memval_s, "%s", memval) != 1)
  {
   /* problably should access OS error name here */
   tf_error("error reading memory value for cell %d", i);
   tf_putp(0, 0);
   return;
  }
 /* probably should add code to check for memval as legal binary number */
 /* but can be any width since putp assignment will widen or truncate */

 /* make sure index i is legal - since must have used i in memory select */
 /* only for checking */
 if (i != last_i + 1)
  {
   tf_error("memory index %d non in sequence - %d expected", i, last_i + 1);
   tf_putp(0, 0);
   return;
  }
 last_i = i;

 /* this is #0, in CVC you would use extension routine tf_strputp */
 /* it is identical to tf_strdelputp except string assignment immediate */
#ifdef __HAS_STRPUTP__
 /* notice need final delay type parameter since may need to cancel */
 /* events if delay form used elsewhere */
 printf("*** using tf_strputp\n"); 
 if (tf_strputp(1, memwid, 'b', memval) == 0)
#else
 if (tf_strdelputp(1, memwid, 'b', memval, 0, 0) == 0)
#endif
  {
   tf_error("strdelput of index memory failed");
   tf_putp(0, 0);
   return;
  }
 tf_putp(0, 1);
}

/* example that goes in user code */
s_tfcell veriusertfs[] = 
{ 
 { userfunction, 0, 0, (int (*)()) intsize, (int (*)()) plisetupmemfill, 0,
   "$pli_setupmemfill", 0},
 { userfunction, 0, (int (*)()) check_plimemfill, (int (*)()) intsize,
  (int (*)()) plimemfill, 0, "$pli_memfill", 0},
 /* -- add extra entries here -- */
 {0} /* -- this line must always be last -- */
};

/* dummy +loadpli1 boostrap routine - return old style veriusertfs tab */
s_tfcell *pli1_compat_bootstrap(void)
{
 return(veriusertfs);
}
