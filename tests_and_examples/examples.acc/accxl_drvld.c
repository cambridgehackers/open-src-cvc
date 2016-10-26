/* Copyright (c) 2011 Tachyon Design Automation */

/*
 * test of get_value using value change call back mechanism 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cv_veriuser.h"
#include "veriuser.h"
#include "acc_user.h"
#include "cv_acc_user.h"

/* int (*iproc_rtn)(handle); */

/* local function prototypes */
static void process_inst(handle); 
static void mei_count_drivers(handle, handle);
static void mei_count_loads(handle, handle);
static void mei_count_cellloads(handle, handle);
static int mei_isinside(handle, handle);

/* global function prototypes */
extern int process_all_insts(int, int);

/*
 * process instances top down
 */
int process_all_insts(int reason, int udata)
{
 handle topinst;

 for (topinst = NULL;;)
  {
   if ((topinst = acc_next_child(NULL, topinst)) == NULL) break;
   process_inst(topinst);
  }
 io_printf("  >>> All instances net drivers processed by acc_.\n");
 tf_dofinish();
 return(0);
}

/*
 * process one instance and recursively process all under instances
 * processing is top down depth first
 */
static void process_inst(handle upinst) 
{
 handle inst, net;

 io_printf("... processing instance %s.\n", acc_fetch_fullname(upinst));

 for (net = acc_next_net(upinst, NULL); net != NULL;
  net = acc_next_net(upinst, net))
  {
   mei_count_drivers(upinst, net);
   mei_count_loads(upinst, net);
   mei_count_cellloads(upinst, net);
  }
 
 for (inst = NULL;;)
  {
   if ((inst = acc_next_child(upinst, inst)) == NULL) return;
   process_inst(inst);
  }
}

/*
 * count and list all acc world (prim terminal) drivers
 */
void mei_count_drivers(handle inst, handle net)
{
 int count = 0;
 handle term;
 char s1[1024], s2[1024];
 
 io_printf(" ... processing drivers for %s:\n", acc_fetch_fullname(net));
 for (term = acc_next_driver(net, NULL); term != NULL;
  term = acc_next_driver(net, term))
  {
   if (mei_isinside(inst, term) == 1) { strcpy(s1, "inside"); count++; }
   else strcpy(s1, "outside");

   if (acc_fetch_type(term) == accTerminal)
    {
     sprintf(s2, "prim %s port %d", acc_fetch_fullname(acc_handle_parent(term)),
      acc_fetch_index(term));
    }
   else strcpy(s2, acc_fetch_fullname(term));

   io_printf(" +++ %s is %s driver of %s in %s.\n", s2,
    s1, acc_fetch_fullname(net), acc_fetch_fullname(inst));
  }
 io_printf("net %s has %d inside drivers.\n", acc_fetch_name(net), count);
}

/*
 * return 1 if obj inside inst
 */
int mei_isinside(handle inst, handle obj)
{
 handle parent;

 for (parent = acc_handle_parent(obj); parent != NULL;
  parent = acc_handle_parent(parent))
  {
   if (acc_compare_handles(parent, inst)) return(1);
  }
 return(0);
}

/*
 * count and list all acc world (prim terminal) drivers
 */
void mei_count_loads(handle inst, handle net)
{
 int count = 0;
 handle term;
 char s1[1024], s2[1024];
 
 io_printf(" ... processing loads for %s:\n", acc_fetch_fullname(net));
 for (term = acc_next_load(net, NULL); term != NULL;
  term = acc_next_load(net, term))
  {
   if (mei_isinside(inst, term) == 0) { strcpy(s1, "outside"); count++; }
   else strcpy(s1, "inside");

   if (acc_fetch_type(term) == accTerminal)
    {
     sprintf(s2, "prim %s port %d", acc_fetch_fullname(acc_handle_parent(term)),
      acc_fetch_index(term));
    }
   else strcpy(s2, acc_fetch_fullname(term));

   io_printf(" +++ %s is %s load of %s in %s.\n", s2,
    s1, acc_fetch_fullname(net), acc_fetch_fullname(inst));
  }
 io_printf("net %s has %d outside loads.\n", acc_fetch_name(net), count);
}

/*
 * count and list all acc world (prim terminal) drivers
 */
void mei_count_cellloads(handle inst, handle net)
{
 int count = 0;
 handle term;
 char s1[1024], s2[1024];
 
 io_printf(" ... processing cell loads for %s:\n", acc_fetch_fullname(net));
 for (term = acc_next_load(net, NULL); term != NULL;
  term = acc_next_load(net, term))
  {
   if (mei_isinside(inst, term) == 1) { strcpy(s1, "inside"); count++; }
   else strcpy(s1, "outside");

   if (acc_fetch_type(term) == accTerminal)
    {
     sprintf(s2, "prim %s port %d", acc_fetch_fullname(acc_handle_parent(term)),
      acc_fetch_index(term));
    }
   else strcpy(s2, acc_fetch_fullname(term));

   io_printf(" +++ %s is %s load of %s in %s.\n", s2,
    s1, acc_fetch_fullname(net), acc_fetch_fullname(inst));
  }
 io_printf("net %s has %d inside cell loads.\n", acc_fetch_name(net), count);
}

s_tfcell veriusertfs[] = {
 { usertask, 0, 0, 0, (int (*)()) process_all_insts, 0, "$test", 0 }, 
 {0} /* this line must always be last */
};

/* dummy +loadpli1 boostrap routine - return old style veriusertfs tab */
s_tfcell *pli1_compat_bootstrap(void)
{
 return(veriusertfs);
}
