/* Copyright (c) 2011 Tachyon Design Automation */

/*
 * test of get_value using value change call back mechanism 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <cv_veriuser.h>
#include <veriuser.h>
#include <acc_user.h>
#include <cv_acc_user.h>

/* int (*iproc_rtn)(handle); */

/* local function prototypes */
static void process_inst(handle); 

/* global function prototypes */
extern int process_all_insts(int, int);

/*
 * process instance from top
 */
int process_all_insts(int reason, int udata)
{
 int isiz;
 handle topiref;

 isiz = acc_count(acc_next_child, NULL);
 io_printf("  There are %d top level modules.\n", isiz);
 /* iproc_rtn = ???; */
 /* build the iterator for each module */
 for (topiref = NULL;;)
  {
   if ((topiref = acc_next_child(NULL, topiref)) == NULL) break;
   process_inst(topiref);
  }
 io_printf("  >>> All instances processed by acc_.\n");
 return(0);
}

/*
 * process one instance and recursively process all under instances
 * processing is top down depth first
 */
static void process_inst(handle up_ihref) 
{
 int isiz;
 handle ihref;

 /* iproc_rtn(up_ihref); */
 isiz = acc_count(acc_next_child, up_ihref);
 io_printf("  There are %d instances in %s.\n", isiz,
  acc_fetch_fullname(up_ihref));
 for (ihref = NULL;;)
  {
   if ((ihref = acc_next_child(up_ihref, ihref)) == NULL) return;
   process_inst(ihref);
  }
}

s_tfcell veriusertfs[] = {
 {usertask, 0, 0, 0, (int (*)()) process_all_insts, 0, "$dump_contents", 0 }, 
 {0} /* this line must always be last */
};

/* dummy +loadpli1 boostrap routine - return old style veriusertfs tab */
s_tfcell *pli1_compat_bootstrap(void)
{
 return(veriusertfs);
}
