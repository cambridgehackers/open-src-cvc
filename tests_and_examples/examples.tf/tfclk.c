/* Copyright (c) 2011 Tachyon Design Automation */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "veriuser.h"
#include "cv_veriuser.h"

#define CLK_PER 100
/* set DBG to 1 to print some trace message */
#define DBG 0

static char *tfip;

/* local prototypes */
static void tfclk_checktf(void);
static void tfclkonoff_checktf(void);
static int tfclkoff_sizetf(void);
static void tfclk_calltf(int, int);
static void tfclk_misctf(int, int);
static void tfclkoff_calltf(int, int);
static void tfclkon_calltf(int, int);


/*
 * check parameters passed to tf system task/function call
 * must be one and must be rw non wire
 */
static void tfclk_checktf(void)
{
 int lno;
 char *ip, *chp;
 struct t_tfnodeinfo tfnode, *nip;
 
 ip = tf_getinstance();
 chp = tf_igetsourceloc(&lno, ip);
 
 if (tf_nump() != 1)
  tf_error(
  "$tfclk pli task called with %d arguments one expected from **%s(%d)",
   tf_nump(), chp, lno);    
 nip = &tfnode;
 nip = tf_nodeinfo(1, nip);
 if (nip == NULL || (nip->node_type != TF_REG_NODE
  && nip->node_type != TF_INTEGER_NODE && nip->node_type != TF_TIME_NODE)) 
  tf_error(
   "$tfclk invoked at **%s(%d) pli task argument must be read-write register",
   chp, lno);
 free(chp);
}

static void tfclkonoff_checktf(void)
{
 if (tf_nump() != 0)
  tf_error("$tfclkoff pli task called with %d arguments none allowed",
   tf_nump());    
}

/* clock off returns the time clock turned off */
static int tfclkoff_sizetf(void)
{
 return(64);
}

/*
 * start the set delay test clock
 * this assumes there will only be one call of tfclk since tfip overwritten
 * should add code to check for tfip already set and should initialize
 */
static void tfclk_calltf(int data, int reason)
{
 /* need to save instance for turning clock off */
 tfip = tf_getinstance();
 tf_putp(1, 0);
 tf_setdelay(CLK_PER);
}

static void tfclk_misctf(int data, int reason)
{
 int lno;
 char *ip, *chp;

 if (DBG == 1)
  {
   ip = tf_getinstance();
   chp = tf_igetsourceloc(&lno, ip);
   io_printf(
    "called misctf reason %d instance handle from file %s line %d\n",
    reason, chp, lno); 
   free(chp);
  }
 if (reason == REASON_REACTIVATE)
  {
   if ((chp = tf_strgetp(1, 'b')) == NULL)
    tf_message(ERR_INTERNAL, "", "",
    "$tfclk strgetp of misctf from delay expiration - strgetp failed");

   if (strcmp(chp, "0") == 0) tf_putp(1, 1); else tf_putp(1, 0);
   tf_setdelay(CLK_PER);
  }
 /* for ieee PLI lots of reasons that must just be ignored */
}

/*
 * clock off returns time clock stopped
 */
static void tfclkoff_calltf(int data, int reason)
{
 int ltime, htime;

 tf_iclearalldelays(tfip);
 ltime = tf_igetlongtime(&htime, tfip);
 tf_putlongp(0, ltime, htime);
}

static void tfclkon_calltf(int data, int reason)
{
 char *chp;

 if ((chp = tf_strgetp(1, 'b')) == NULL)
  tf_message(ERR_INTERNAL, "", "", "$tfclkon strgetp in calltf failed");
 
 if (strcmp(chp, "0") == 0) tf_iputp(1, 1, tfip); else tf_putp(1, 0);
 tf_setdelay(CLK_PER);
}

/* example that goes in user code */
s_tfcell veriusertfs[] = { 
 { usertask, 0, (int (*)()) tfclk_checktf, 0, (int (*)()) tfclk_calltf,
  (int (*)()) tfclk_misctf, "$tfclk", 0},
 { userfunction, 0, (int (*)()) tfclkonoff_checktf,
  (int (*)()) tfclkoff_sizetf, (int (*)()) tfclkoff_calltf, 0, "$tfclkoff", 0},
 { usertask, 0, (int (*)()) tfclkonoff_checktf, 0,
  (int (*)()) tfclkon_calltf, 0, "$tfclkon", 0},
 /* -- add extra entries here -- */
 {0} /* -- this line must always be last -- */
};

/* dummy +loadpli1 boostrap routine - return old style veriusertfs tab */
s_tfcell *pli1_compat_bootstrap(void)
{
 return(veriusertfs);
}
