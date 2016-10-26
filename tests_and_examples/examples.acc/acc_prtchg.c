/* Copyright (c) 2011 Tachyon Design Automation */

/*
 * test of acc vcls
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "acc_user.h"
#include "cv_acc_user.h"
#include "veriuser.h"
#include "cv_veriuser.h"

/* local function prototypes */
static int process_inst(handle); 
static void setup_1scope_chgcbs(handle);
static void add_vcl(handle);

/* global function prototypes */
extern int process_all_insts(int, int);
extern int setup_varchgcbs(handle);
extern int wire_prt_vclchg(p_vc_record);
extern int var_prt_vclchg(p_vc_record);

/*
 * routine to get and zero all delays in design 
 */
int process_all_insts(int reason, int udata)
{
 handle topinst;

 for (topinst = NULL;;)
  {
   if ((topinst = acc_next_child(NULL, topinst)) == NULL) break;
   process_inst(topinst);
  }
 io_printf("  >>> All instances processed\n");
 return(0);
}

/*
 * process one instance and recursively process all under instances
 * processing is top down depth first
 */
static int process_inst(handle upinst) 
{
 handle scope, inst, net, bit, var, prim, term, port;
 static int varlist[] = { accReg, accIntegerVar, accTimeVar, 0 };

 io_printf("... setting up vcls for instance %s\n",
  acc_fetch_fullname(upinst));

 /* first strength vcls on all nets */
 /* first add vcls for nets */
 io_printf("... vcls for wires\n");
 for (net = acc_next_net(upinst, NULL); net != NULL;
  net = acc_next_net(upinst, net))
  {
   if (acc_fetch_size(net) == 1) add_vcl(net);
   else
    {
     /* for vector wires, must put vcl on bit - need to access strength */
     for (bit = acc_next_bit(net, NULL); bit != NULL;
      bit = acc_next_bit(net, bit)) add_vcl(bit);
    }
  }
 /* then variables */
 io_printf("... vcls for variables\n"); 
 for (var = acc_next(varlist, upinst, NULL); var != NULL;
  var = acc_next(varlist, upinst, var)) add_vcl(var);

 io_printf("... vcls for primitive terminals\n"); 
 /* then primitives output terminals */
 for (prim = acc_next_primitive(upinst, NULL); prim != NULL;
  prim = acc_next_primitive(upinst, prim))
   {
    for (term = acc_next_terminal(prim, NULL); term != NULL;
     term = acc_next_terminal(prim, term))
     {
      /* only output terminals can have vcl added */
      if (acc_fetch_direction(term) == accInput) continue;
      add_vcl(term);
     }
   }

 /* then module ports */
 io_printf("... vcls for ports\n"); 
 for (port = acc_next_port(upinst, NULL); port != NULL;
  port = acc_next_port(upinst, port))
  {
   if (acc_fetch_size(port) == 1) add_vcl(port);
   else
    {
     /* for vector ports, must put vcl on bit - need to access strength */
     for (bit = acc_next_bit(port, NULL); bit != NULL;
      bit = acc_next_bit(port, bit)) add_vcl(bit);
    }
  }

 /* finally all variables in contained scopes */
 for (scope = acc_next_scope(upinst, NULL); scope != NULL;
  scope = acc_next_scope(upinst, scope))
  {
   /* final step setup vcls for contained scopes */
   setup_1scope_chgcbs(scope);
  }

 for (inst = NULL;;)
  {
   if ((inst = acc_next_child(upinst, inst)) == NULL) break;
   process_inst(inst);
  }
 return(0);
}

/*
 * set up change call back for all nets/regs of some type in iter
 *
 * now sure how acc_supposed to work - scopes inside module instance
 * are all tasks, functions, and labeled blocks in init/always blocks
 */
static void setup_1scope_chgcbs(handle scope)
{
 static int varlist[] = { accReg, accIntegerVar, accTimeVar, 0 };
 handle inscope, var;

 io_printf("... setting up vcls for scope %s\n", acc_fetch_fullname(scope));

 /* set up value change call backs for all variables in this scope */
 for (var = acc_next(varlist, scope, NULL); var != NULL;
  var = acc_next(varlist, scope, var)) add_vcl(var);

 /* also or all contained scopes */
 for (inscope = acc_next_scope(scope, NULL); inscope != NULL;
  inscope = acc_next_scope(scope, inscope)) setup_1scope_chgcbs(inscope);
}

/*
 * routine to add vcl to one net/reg/var/event
 */
static void add_vcl(handle net)
{
 int typ, fulltyp;
 char s1[1024];

 /* DBG remove -- */
 typ = acc_fetch_type(net);
 fulltyp = acc_fetch_fulltype(net);
 if (typ != accTerminal) strcpy(s1, acc_fetch_fullname(net));
 else strcpy(s1, "**terminal**");
 io_printf("Adding vcl for %s type %s (fulltype %s)\n", s1,
  acc_fetch_type_str(typ), acc_fetch_type_str(fulltyp));
 /* --- */

 if (typ == accNet)
  {
   acc_vcl_add(net, wire_prt_vclchg, (void *) net, vcl_verilog_strength);  
  }
 else acc_vcl_add(net, var_prt_vclchg, (void *) net, vcl_verilog_logic);  
}

/*
 * wire strength change value change call back routine
 */
int wire_prt_vclchg(p_vc_record vcp)
{
 /* unsigned long long now, chgtim; */
 int typ, ltime, htime;
 handle net;
 char s1[1024], s2[1024], s3[1024];

 /* current time */
 ltime = tf_getlongsimtime(&htime);
 /* ---
 now = ((unsigned long long) ((unsigned long) htime)) << 32
  | ((unsigned long long) ((unsigned long) ltime));

 -* vc record time *- 
 chgtim = ((unsigned long long) ((unsigned long) vcp->vc_hightime)) << 32
  | ((unsigned long long) ((unsigned long) vcp->vc_lowtime));
 --- */

 /* net handle assigned to user data field */
 net = (handle) vcp->user_data; 

 /* build strength value string */
 sprintf(s1, "<%d, %d>=%d", (int) vcp->out_value.strengths_s.strength1, 
  (int) vcp->out_value.strengths_s.strength2,   
  (int) vcp->out_value.strengths_s.logic_value);
 
 /* also get value as internal strength %v string */
 strcpy(s2, acc_fetch_value(net, "%v", NULL));

 if (vcp->vc_reason != strength_value_change)
  {
   io_printf("*** ERROR: wire change reason %d - strength change expected\n",
    vcp->vc_reason);
  }
 /* ---
 io_printf("--> now %uL (chg time %uL): %s=%s(%s)\n", now, chgtim,
 -- */

 /* terminals do not have names */
 typ = acc_fetch_type(net);
 if (typ != accTerminal) strcpy(s3, acc_fetch_fullname(net));
 else strcpy(s3, "**terminal**");

 io_printf("--> now %d (chg time %d): %s=%s(%s)\n", ltime, vcp->vc_lowtime,
  s3, s2, s1); 
 return(0);
}

/*
 * variable value change call back routine
 */
int var_prt_vclchg(p_vc_record vcp)
{
 /* unsigned long long now, chgtim; */
 int otyp, ltime, htime;
 handle net;
 char s1[1024], s2[1024], s3[1024];

 /* current time */
 ltime = tf_getlongsimtime(&htime);
 /* -- 
 now = ((unsigned long long) ((unsigned long) htime)) << 32
  | ((unsigned long long) ((unsigned long) ltime));

 -* vc record time *- 
 chgtim = ((unsigned long long) ((unsigned long) vcp->vc_hightime)) << 32
  | ((unsigned long long) ((unsigned long) vcp->vc_lowtime));
 -- */

 /* net handle assigned to user data field */
 net = (handle) vcp->user_data; 
 otyp = acc_fetch_type(net);

 if (vcp->vc_reason != event_value_change)
  {
   /* these do not have value, i.e. get va8ue return NULL with error */
   if (otyp == accPort || otyp == accPortBit || otyp == accTerminal)
    {
     sprintf(s1, "obj=%s", acc_fetch_type_str(otyp));
    }
   else strcpy(s1, acc_fetch_value(net, "%b", NULL));
  }

 switch (vcp->vc_reason) {
  case logic_value_change:
   sprintf(s2, "scalar=%u(%s)", (unsigned) vcp->out_value.logic_value, s1); 
   break;
  case sregister_value_change:
   sprintf(s2, "sr-scalar=%u(%s)", (unsigned) vcp->out_value.logic_value, s1); 
   break;
  case real_value_change: case realtime_value_change:
   sprintf(s2, "**error**");
   break;
  case event_value_change:
   strcpy(s2, "**event**");
   break;
  default:
   sprintf(s2, "vector=%s", s1);
 }  

 /* --
 io_printf("--> now %uL (chg time %uL): %s=%s\n", now, chgtim,
 -- */

 if (otyp != accTerminal) strcpy(s3, acc_fetch_fullname(net));
 else strcpy(s3, "**terminal**");

 io_printf("--> now %d (chg time %d): %s=%s\n", ltime, vcp->vc_lowtime, s3,
  s2); 
 return(0);
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
