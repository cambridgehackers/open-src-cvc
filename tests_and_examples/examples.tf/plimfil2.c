/* Copyright (c) 2011 Tachyon Design Automation */

/* 
 * example illustrating using PLI tf_ utility routines to fill memory
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "veriuser.h"
#include "cv_veriuser.h"

int memsiz, memwid, last_i;
FILE *memval_s;
struct t_tfnodeinfo ninfo;
struct t_tfexprinfo xinfo;

/* static prototypes */
static int intsize(int, int);
static void plisetupmemfil2(int, int);
static void check_plimemfil2(int, int);
static void plimemfil2(int, int);

static int intsize(int data, int reason)
{
 return(32);
}

/*
 * routine to setup memory filling routine - set param to 0 on error else 1
 * function: $plisetupmemfill(memsiz, memwid)
 */
static void plisetupmemfil2(int data, int reason)
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
 if (memwid > 32)
  {
   tf_error("for tf_propagatep routine can only use scanf for < 32 bits");
   tf_putp(0, 0);
   return;
  }
 tf_putp(0, 1);
 /* assume memory goes from 1 to size */
 last_i = 0; 
}

/*
 * check the fill memory user PLI function
 * notice calling tf_error here will inhibit simulation
 * probably sould also check 2nd index argument 
 */
static void check_plimemfil2(int data, int reason)
{
 if (tf_nump() != 2)
  {
   tf_error("$pli_memfil2 has %d arguments - 2 required", tf_nump());
   return;
  }
 /* this associates nodeinfo struct with argument */
 tf_nodeinfo(1, &ninfo);
 if (ninfo.node_type != TF_MEMORY_NODE)
  {
   tf_error("$pli_memfil2 first argument not read/write memory select");
   return;
  }
}

/*
 * routine to set memory using tf_propagatep method  
 *
 * must be 32 bits or less otherwise would need to write vecval manipulation
 * routines
 *
 * function: $pli_memfil2(mem[i], i)
 * here tfputp would be better choice since only allows non x/z forms 
 */
static void plimemfil2(int data, int reason)
{
 int i;
 unsigned memval;
 struct t_vecval *vecp;

 i = tf_getp(2);
 if (i < 0 || i > memsiz) 
  {
   tf_error("cannot fill memory location %d - memory has only %d cells");
   tf_putp(0, 0);
   return;
  }
 if (fscanf(memval_s, "%u", &memval) != 1)
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

 tf_exprinfo(1, &xinfo);
 /* set value  - using 32 bit value else would need string to 0*/
 vecp = xinfo.expr_value_p;
 vecp[0].avalbits = (int) memval;
 vecp[0].bvalbits = 0;
 /* do assign - notice this forces re-evaluate of argument during assign */
 /* SJM 12/20/02 - following LRM, fail is 1 not 0 */
 if (tf_propagatep(1) == 1)
  {  
   tf_error("tf_propagatep of indexed memory failed");
   tf_putp(0, 0);
  }
 else tf_putp(0, 1);
}

/* example that goes in user code */
s_tfcell veriusertfs[] = 
{ 
 { userfunction, 0, 0, (int (*)()) intsize, (int (*)()) plisetupmemfil2, 0,
  "$pli_setupmemfil2", 0},
 { userfunction, 0, (int (*)()) check_plimemfil2, (int (*)()) intsize,
  (int (*)()) plimemfil2, 0, "$pli_memfil2", 0},
 /* -- add extra entries here -- */
 {0} /* -- this line must always be last -- */
};

/* dummy +loadpli1 boostrap routine - return old style veriusertfs tab */
s_tfcell *pli1_compat_bootstrap(void)
{
 return(veriusertfs);
}
