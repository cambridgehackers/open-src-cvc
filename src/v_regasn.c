/* Copyright (c) 1991-2014 Tachyon Design Automation Corp. */

/* === INSERT LICENSE ===

OSS CVC dual licensing modified Artistic Open Source Software License

Copyright © 1991-2014 Tachyon Design Automation Corp.
All Rights reserved.  Licensed software subject to prohibitions and
restrictions.

PLEASE READ THIS SOFTWARE LICENSE AGREEMENT CAREFULLY BEFORE USING THE
SOFTWARE. BY USING THE SOFTWARE, YOU ARE AGREEING TO BE BOUND BY THE
TERMS OF THIS LICENSE. IF YOU ARE ACCESSING THE SOFTWARE ELECTRONICALLY,
SIGNIFY YOUR AGREEMENT TO BE BOUND BY THE TERMS OF THIS LICENSE BY
CLICKING THE "AGREE/ACCEPT" BUTTON. IF YOU DO NOT AGREE TO THE TERMS OF
THIS LICENSE, DO NOT USE THE SOFTWARE AND (IF APPLICABLE) RETURN OR DELETE
THE SOFTWARE OR, IF THE SOFTWARE WAS ACCESSED ELECTRONICALLY, CLICK
"DISAGREE/DECLINE".

Preamble

  The intent of this document is to state the conditions under which a
Package may be copied, such that the Copyright Holder maintains artistic
control over the development of the Package as granted by Copyright law.
The intent is also to give the users of the Package the
right to use and distribute the Package using the free software model
as long as the Package and all modified, linked or accompanying software
is redistributed also using the open source model with included or
available source.  The Modifications must meet some conditions to
retain the artistic integrity of the Package and to preserve the
Package Copyright Holder's commercial rights.

  OSS CVC is dual licensed so that to commercially distribute the Package,
with or without linked in or modified source code, or as a forked project
with closed commercial software, a commercial license or other distribution
arrangements must be purchased from the Copyright Holder.

Definitions:

  "Package" refers to the collection of files distributed by the Copyright
Holder, and derivatives of that collection of files created through textual
modification.

  "Standard Version" refers to such a Package if it has not been modified,
or has been modified in accordance with the wishes of the Copyright Holder.

  "Copyright Holder" is whoever is named in the copyright notice or
copyright registrations for the Package.

  "You" and “your” means any person who would like to copy, distribute or
modify the Package.

  "Reasonable Copying Fee" is whatever you can justify on the basis of media
cost, duplication charges, time of people involved, and so on.

  "Freely Available" means that no fee is charged for the item itself,
though there may be a Reasonable Copying Fee involved in handling the
item. It also means that recipients of the item may redistribute it under
the same conditions they received it.

1. You may use, make and give away verbatim copies of the source form of
the Standard Version without any linking in or modifications of this
Package provided that you duplicate this License and all of the original
copyright notices and associated disclaimers.

2. You may apply bug fixes, portability fixes and other modifications
made available from the Copyright Holder. A Package modified in such a
way shall still be considered the Standard Version, and Copyright holder
retains copyright to all such changes.

3. You may otherwise modify your copy of this Package in any way, provided
that you insert a prominent notice in each changed file stating how and
when you changed that file, and provided that you do at least ONE of
the following:

    a) place your modifications into the Public Domain or otherwise make them
Freely Available, or by allowing the Copyright Holder to include your
modifications in the Standard Version of the Package.

    b) use the modified Package only individually or within your corporation
or organization.

    c) rename any non-standard Package (forked project usually) so the names
do not conflict with standard executables, which must also be provided, and
provide documentation for each non-standard Package that clearly documents
how it differs from the Standard Version.  The non-standard version must
retain this license so all redistributions of the non-standard version
must be distributed with all modified, linked, and accompanying code
available in source form.

    d) make other distribution arrangements with the Copyright Holder.


All versions must retain and include this License and disclaimers, and all
redistributions of a non-standard version must be distributed with all
modified, linked, and accompanying code available in source form.

In particular OSS CVC is intended to use the dual licensing model so any
commercial redistribution of a modified version, a forked project, a
standard OSS CVC as a commercial product (sold for more than a reasonable
redistribution fee), or a version linked with commercial closed source
software will require other distribution arrangements and license with
the Copyright Holder. 

4. You may distribute the programs of this Package in object code or
executable form provided that such versions include this License and
disclaimers and that all of the Package, including any modifications or
other bundled elements, are distributed as open source made Freely
Available and provided you also do at least ONE of the following:

    a) distribute a Standard Version of the executables and library files,
together with instructions (in the manual page or equivalent) on where to
get the Standard Version.

    b) accompany the distribution with the machine-readable source of the
Package with your modifications, if any.

    c) accompany any non-standard executables with their corresponding
Standard Version executables, giving the non-standard executables
different names, and clearly documenting the differences, together
with instructions on where to get the Standard Version.

    d) make other distribution arrangements with the Copyright Holder.

5. You may charge a Reasonable Copying Fee for any distribution of this
Package. You may charge any fee you choose for support of this Package.

6. Any Verilog standard API PLI interface source or binary code supplied by
you and linked into this Package shall not be considered part of this
Package. You may license your PLI libraries as you wish.

7. Any use, modification, and distribution of the Standard Version or
non-standard versions is governed by this Artistic License. By using,
modifying or distributing the Package, you accept this License.
Do not use, modify, or distribute the Package, if you do not accept
this license.

8. If your non-standard version has been derived from a non-standard
version made by someone other than you, you are nevertheless required
to ensure that your non-standard version complies with the requirements
of this license.

9. The name of the Copyright Holder may not be used to endorse or promote
products derived from this software without specific prior written
permission.  This license does not grant you the right to use any
trademark, service mark, trade name, or logo of the Copyright Holder.

10. This license includes the non-exclusive, worldwide, free-of-charge
patent license to make, have made, use, offer to sell, sell, import and
otherwise transfer the Package with respect to any patent claims
licensable by the Copyright Holder that are necessarily infringed by
the Package.  If you institute patent litigation (including a cross-claim
or counterclaim) against any party alleging that the Package constitutes
direct or contributory patent infringement, then this Artistic License
to you shall terminate on the date that such litigation is filed.

11. DISCLAIMER OF WARRANTIES: THIS PACKAGE IS PROVIDED "AS IS" AND
WITHOUT ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION,
THE IMPLIED WARRANTIES OF MERCHANTIBILITY, FITNESS FOR A PARTICULAR PURPOSE,
OR NON-INFRINGEMENT.  THE COPYRIGHT HOLDER SHALL NOT BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL OR CONSEQUENTIAL DAMAGES ARISING IN ANY WAY
OUT OF THE USE OF THE PACKAGE, EVEN IF ADVISED OF THE POSSIBILITY
OF SUCH DAMAGE.

=== END INSERT === */

/*
 * routines to optimize and lower basic block form flow graph insns
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <math.h>
#include <unistd.h> 
#include <stdarg.h>

#ifdef __DBMALLOC__
#include "../malloc.h"
#endif

#include "v.h"
#include "cvmacros.h"
#include "igen.h"

static void rebld_tns_used_in_fgs(struct flowg_t *);
static int32 check_fg_uses_idp(struct flowg_t *);
static void check_used_insns(struct flowg_t *, struct avlnode_t **, int32);
static void build_register_def_use_list(struct flowg_t *);
static void remove_multiple_idp_set(struct flowg_t *);
static void init_insn_for_reg_alloc(struct insn_t *);
static int32 is_tn_general_reg(int32);
static int32 tmp_canbe_reg(int32);
static struct tn_list_t *alloc_tn_list(int32);
static int32 amode_dst_is_def(struct insn_t *);
static void add_tn_to_list(int32, int32);
static void tryadd_conflict_tns(struct tn_t *, int32);
static void add_tn_to_defuse_list(struct tn_list_t *, int32);
static void copy_tn_list(struct tn_list_t *, struct tn_list_t *);
static void set_union(struct tn_list_t *, struct tn_list_t *);
static void grow_work_array(int32);
static void add_tn_to_list_nodup(struct tn_list_t *, int32);
static void liveness_analysis(struct flowg_t *);
static int32 is_move_insn(int32);
static void add_conflict_edge(int32, int32);
static void build_reg_conflicts(struct flowg_t *);
static int32 is_call(int32);
static int32 assign_x86_reg_set(struct flowg_t *, struct tn_t *, int32 *, 
 int32, int32);
static void do_reg_assign(struct flowg_t *, struct avlnode_t **, int32, int32);
static struct tn_list_t *copy_tmp_list(struct tn_list_t *);
static int32 assign_tmpregs_to_regs(struct flowg_t *, struct avlnode_t **,
 int32, int32);
static int32 assign_regs(int32 *, int32, int32 *, int32, int32 *, int32, 
 int32 *, int32, int32 *, int32, int32, int32 *, struct flowg_t *);
static void init_tmp_flags(struct flowg_t *, struct avlnode_t **, int32);
static void mark_nonl_insn_and_wide_tns(struct insn_t *);
static int32 get_spill_wrd_ofs(struct flowg_t *, int32);
static int32 try_to_assign_overflow_reg(struct flowg_t *, int32 *, int32);
static void spill_tmp(struct tn_t *, struct flowg_t *, int32, int32 *, int32,
 int32);
static void dump_liveness_in_out_round(struct flowg_t *, int32);
static void dump_tmp_list(struct tn_list_t *);
static void dump_tmp_defuse_list(struct flowg_t *);
static void free_adj_info(struct flowg_t *, struct avlnode_t **, int32);
static void free_adj_insn_fields(struct insn_t *); 
static void free_tmp_list(struct tn_list_t *);
static int32 simple_coalesce(struct flowg_t *, int32 *, int32, int32, int32,
 int32, int32);
static void convert_all_adjregs(int32 *, int32, int32, int32);
static int32 find_tni(struct tn_list_t *, int32);
static void linkout_tni(struct tn_list_t *, int32);
static int32 int_cmp(const void *, const void *);

extern void __assign_regs_and_wides_adjacent(struct flowg_t *);
extern struct bblk_t *__find_add_conflct_tn(struct avlhd_t *, int32);

extern void __tryadd_tn_use_in_fg(struct flowg_t *, int32);
extern int32 __is_constant(int32);
extern int32 __is_mem_label(int32);
extern struct insn_info_t *__to_iinfo_rec(int32);
extern struct asl_info_t *__to_aslinfo_rec(int32);
extern int32 __get_tn_vec_size(struct tn_t *);
extern struct avlnode_t **__linearize_avl_tree(struct avlhd_t *, int32 *);
extern void __tn_dup_node_free(void *);
extern void __free_tn_avltree(struct avlhd_t *, void (*)(void *));
extern struct avlhd_t *__allocinit_avlhd(void);
extern void __insert_after_insn(struct insn_t *, struct insn_t *);
extern int32 __gen_tn(int32, int32);
extern struct insn_t *__insert_insn(struct insn_t *, int32, int32,
 int32, ...);
extern void __linkout_insn(struct insn_t *, int32);

extern char *__my_realloc(void *, size_t, size_t);
extern char *__my_malloc(size_t);
extern void __my_free(void *, size_t);

extern void __my_fprintf(FILE *, char *, ...);
extern void __misc_terr(char *, int32);
extern void __case_terr(char *, int32);

extern const char *__regs[];

//AIV FIXME - need to make extern in igen.h
//leaving for trying new method
static int32 *__work_array;
static int32 __work_array_size;
/* if TRUE doing safe register coalescing */
static int32 __do_safe_coal;

/*
 * ROUTINES TO IMPLEMENT ADJACENT MACHINE REG ASSIGN AND SPILL EBP OFFSET
 */

extern void __assign_regs_and_wides_adjacent(struct flowg_t *fgp)
{
 int32 num_tnrefs, use_idp_tmp;
 struct avlnode_t **tn_ref_avltab;

 /* if uses idp mark flowg graph as using esi */
//AIV IDP FIXME CVC - need to load the right thing into esi???????
 if (fgp->do_not_load_idp) 
  {
   use_idp_tmp = FALSE;
  }
 else
  {
   /* if uses design wide idp fix up the __design wides to use idp reg offs */
   use_idp_tmp = check_fg_uses_idp(fgp);
   /* AIV 01/08/08 - do not mark fgp as using esi no need for push/pops */
   /* of esi unless esi is never accessed via __idp then may use it */
   /* as regular reg */
  }



 /* SJM 01/19/07 - need to rebld set of tn's used in lowered machine insn */
 /* flow graph */
 rebld_tns_used_in_fgs(fgp);

 __work_array_size = 2048;
 __work_array = (int32 *) __my_malloc(__work_array_size*sizeof(int32));

 tn_ref_avltab = __linearize_avl_tree(fgp->fg_tn_ref_tree, &(num_tnrefs));

 /* AIV comment this out when working performance problem */
 /* DBG remove -- */
 // FOR DEBUGGING check_used_insns(fgp, tn_ref_avltab, num_tnrefs);
 /* ----- */
 build_register_def_use_list(fgp);
 if (__opt_debug_flg)
  {
   dump_tmp_defuse_list(fgp);
  }

 /* AIV 11/30/09 - if reg optimize remove extra idp (esi) setting */
 if (__opt_reg_alloc)
  {
   remove_multiple_idp_set(fgp); 
  }

 /* AIV 02/13/09 - for debugging - to check use/def of registers */
 //chk_tmp_defuse_list(fgp, tn_ref_avltab, num_tnrefs);

 liveness_analysis(fgp);
 /* dump the in/out array */
 if (__opt_debug_flg)
  {
   dump_liveness_in_out_round(fgp, -1); 
  }
 build_reg_conflicts(fgp);
 do_reg_assign(fgp, tn_ref_avltab, num_tnrefs, use_idp_tmp);
 /* free all info used for reg adj */
 /* AIV LOOKATME - freeing here because it uses alot of memory which is no */
 /* longer needed - don't need to make a seperate pass could do when */
 /* all of the flowg tmps are freed */
 free_adj_info(fgp, tn_ref_avltab, num_tnrefs);
 __my_free(__work_array, __work_array_size*sizeof(int32));
 __my_free(tn_ref_avltab, num_tnrefs*sizeof(struct avlnode_t *));
}

/*
 * rebuild the set of tn's used in a flow graph
 *
 * need for conflict graph register assign - linear scan build it whenu
 * assigning live regions
 *
 * since called after lowering to 2 addr machine insns
 *
 * do not need to build the per tn bblk's that tn is refs in here ` 
 */
static void rebld_tns_used_in_fgs(struct flowg_t *fgp)
{
 struct insn_t *ip;
 int32 tni;
 struct bblk_t *bbp;

 if (fgp->fg_tn_ref_tree != NULL)
  {
   __free_tn_avltree(fgp->fg_tn_ref_tree, __tn_dup_node_free);
   fgp->fg_tn_ref_tree = NULL;
  }
 for (bbp = fgp->fg_bblks; bbp != NULL; bbp = bbp->bbnxt)
  {
   for (ip = bbp->ihd; ip != NULL; ip = ip->inxt)
    {
     /* AIV LOOKAMTE - putting insn count here????? */
     __insn_count++; 
     /* DBG remove -- */
     if (ip->res_tni != -1) __misc_terr(__FILE__, __LINE__);
     /* --- */
     tni = ip->isrc.am_tni;
     if (tni != -1)
      {
       __tntab[tni].tn_coalesce_into = -1;
       if (!__is_constant(tni) && !__is_mem_label(tni))
        {
         __tryadd_tn_use_in_fg(fgp, tni);
        }
      }
     tni = ip->idst.am_tni;
     if (tni != -1)
      {
       __tntab[tni].tn_coalesce_into = -1;
       if (!__is_constant(tni) && !__is_mem_label(tni))
        {
         __tryadd_tn_use_in_fg(fgp, tni);
        }
      }
    }
  }
}
 
/*
 * return TRUE if fg uses the idp reg (almost always TRUE)
 */
static int32 check_fg_uses_idp(struct flowg_t *fgp) 
{
 struct insn_t *ip;
 struct bblk_t *bbp;
 struct amode_t *srcp, *dstp;

 for (bbp = fgp->fg_bblks; bbp != NULL; bbp = bbp->bbnxt)
  {
   for (ip = bbp->ihd; ip != NULL; ip = ip->inxt)
    {
     srcp = &(ip->isrc);
     if (srcp->am_tni == IDP_REG || srcp->x86_regno == IDP_REG)
      {
       fgp->uses_idp = TRUE;
       return(TRUE); 
      }
     dstp = &(ip->idst);
     if (dstp->am_tni == IDP_REG || dstp->x86_regno == IDP_REG)
      {
       fgp->uses_idp = TRUE;
       return(TRUE); 
      }
    }
  }
 return(FALSE);
}

/*
 *
 */
static void check_used_insns(struct flowg_t *fgp,
 struct avlnode_t **tn_ref_avltab, int32 num_tnrefs)
{
 struct insn_t *ip;
 struct bblk_t *bbp;
 struct tn_dup_t *tndup;
 struct asl_def_t *aslap;
 int32 ai, ti, ri, i, found;
 
 for (i = 0; i < num_tnrefs; i++)
  {
   tndup = (struct tn_dup_t *) tn_ref_avltab[i]->valp;
   ti = tndup->tni; 
   found = FALSE;
   for (bbp = fgp->fg_bblks; bbp != NULL; bbp = bbp->bbnxt)
    {
     for (ip = bbp->ihd; ip != NULL; ip = ip->inxt)
      {
       if (ip->opcod == I_CALL_ASLPROC || ip->opcod == I_CALL_ASLFUNC)
        {
         for (ai = 0; ai < ip->callasl_argnum; ai++)
          {
           aslap = &(ip->extrau.asl_ausedefs[ai]);
           if (ti == aslap->am_arg.am_tni)
            {
             found = TRUE;
             goto next;
            }
          }
         continue;
        }
       ri = ip->isrc.am_tni;
       if (ri == ti)
        {
         found = TRUE;
         goto next;
        }
       ri = ip->idst.am_tni;
       if (ri == ti)
        {
         found = TRUE;
         goto next;
        }
      }
    }
next:
   /* if tmp ti never used in an insn should never be in ref tree */
   if (!found) __misc_terr(__FILE__, __LINE__);
  }
}


/*
 * free all adjacent tmp info 
 * AIV LOOKATME - freeing here because it uses alot of memory which is no 
 * longer needed - don't need to make a seperate pass could do when 
 * all of the flowg tmps are freed 
 */
static void free_adj_info(struct flowg_t *fgp, 
 struct avlnode_t **tn_ref_avltab, int32 tnrefs)
{
 struct bblk_t *bbp;
 struct insn_t *ip;
 struct tn_dup_t *tndup;
 struct tn_t *tnp;
 int32 i;

 for (i = 0; i < tnrefs; i++)
  {
   tndup = (struct tn_dup_t *) tn_ref_avltab[i]->valp;
   tnp = &(__tntab[tndup->tni]); 
   if (tnp->tn_adj_lst != NULL)
    {
     free_tmp_list(tnp->tn_adj_lst);
     tnp->tn_adj_lst = NULL;
     __free_tn_avltree(tnp->tn_conflct_tree, NULL);
     tnp->tn_conflct_tree = NULL;
    }
  }

 for (bbp = fgp->fg_bblks; bbp != NULL; bbp = bbp->bbnxt)
  {
   for (ip = bbp->ihd; ip != NULL; ip = ip->inxt)
    {
     /* AIV 06/17/09 - need a routine call here because used else where */
     free_adj_insn_fields(ip);
    }
  }
}

/*
 * free the def/use list for an insn
 */
static void free_adj_insn_fields(struct insn_t *ip) 
{
 if (ip->optu.rap->tn_use_lst != NULL) free_tmp_list(ip->optu.rap->tn_use_lst);
 if (ip->optu.rap->tn_def_lst != NULL) free_tmp_list(ip->optu.rap->tn_def_lst);
 if (ip->optu.rap->tn_in_lst != NULL) free_tmp_list(ip->optu.rap->tn_in_lst);
 if (ip->optu.rap->tn_out_lst != NULL) free_tmp_list(ip->optu.rap->tn_out_lst);
 __my_free(ip->optu.rap, sizeof(struct reg_alloc_t));
 ip->optu.rap = NULL;
}

/*
 * build a register def/use list for each insn
 */
static void build_register_def_use_list(struct flowg_t *fgp)
{
 int32 ri;
 struct insn_info_t *iip;
 struct asl_info_t *aslp;
 struct insn_t *ip;
 struct bblk_t *bbp;
 
 for (bbp = fgp->fg_bblks; bbp != NULL; bbp = bbp->bbnxt)
  {
   for (ip = bbp->ihd; ip != NULL; ip = ip->inxt)
    {
     init_insn_for_reg_alloc(ip);
     /* AIV 12/30/08 - asl wrapper calls are now all expanded by here for */
     /* both 32/64 bit */
     /* DBG remove -- */
     if (ip->opcod == I_CALL_ASLPROC || ip->opcod == I_CALL_ASLFUNC)
        __misc_terr(__FILE__, __LINE__);
     /* ---- */
     /* if has source and is a tmp reg add to use list */
     ri = ip->isrc.am_tni;
     if (tmp_canbe_reg(ri))
      {
       /* don't add special control registers */
       if (ri != AR_SP && ri != AR_BP && ri != ST1)
        {
         add_tn_to_defuse_list(ip->optu.rap->tn_use_lst, ri);
        }
      }
     /* if insn has a dst and the insn writes the dst add to def list */
     iip = __to_iinfo_rec(ip->opcod);

     /* AIV 07/31/06 - if a asl call and it returns a value defines eax */
     if (iip->iclass == ICLASS_ASL) 
      {
       aslp = __to_aslinfo_rec(ip->idst.disp);
       if (aslp->asl_ret_typ != RE_VOID)
        {
         /* AIV 11/04/08 - notice eax wasn't getting added for 64-bit */
         /* since 64-bit are already expanded by here must add return */
         /* reg (eax) since this mallocs the adj list tn_adj_lst */
         tmp_canbe_reg(AR_AX);
         add_tn_to_defuse_list(ip->optu.rap->tn_def_lst, AR_AX);
        }
      }
     
     ri = ip->idst.am_tni;
     if (!tmp_canbe_reg(ri)) continue;

     if (amode_dst_is_def(ip))
      {
       if (ri == AR_SP || ri == AR_BP || ri == ST1) continue;
       add_tn_to_defuse_list(ip->optu.rap->tn_def_lst, ri);
       /* if is a binary it defines and uses */
       if (iip->iclass == ICLASS_BIN || iip->iclass == ICLASS_SHFT)
        {
         add_tn_to_defuse_list(ip->optu.rap->tn_use_lst, ri);
        }
      }
     else
      {
       /* if has dst and isn't a write opcod add to use list */
       if (ri == AR_SP || ri == AR_BP || ri == ST1) continue;
       add_tn_to_defuse_list(ip->optu.rap->tn_use_lst, ri);
      }
    }
  }
}

/*
 * compute the in/out reg analysis 
 * algorithm taken from the Appel book 10.3
 * AIV FIXME - should fix this to speed it up - either sort or pack lists
 */
static void liveness_analysis(struct flowg_t *fgp)
{
 struct insn_t *ip, *ip2;
 struct bblk_t *bbp, *bbp2;
 struct bbedge_t *bbep;
 int32 nround, val, i, val2;
 int32 sav_in_cnt, sav_out_cnt, changed;
 struct tn_list_t *in_tlstp, *out_tlstp, *def_tlstp;

 nround = 0;
 do {
    changed = FALSE;
    for (bbp = fgp->fg_bblkend; bbp != NULL; bbp = bbp->bbprev)
     {
      for (ip = bbp->itail; ip != NULL; ip = ip2)
       {
        in_tlstp = ip->optu.rap->tn_in_lst;
        out_tlstp = ip->optu.rap->tn_out_lst;
        sav_in_cnt = in_tlstp->ndx;
        sav_out_cnt = out_tlstp->ndx;
        def_tlstp = ip->optu.rap->tn_def_lst;
        /* def_list can only have a max of one */
        if (def_tlstp->ndx == 0)
         {
          copy_tn_list(in_tlstp, out_tlstp);
         }
        else
         {
          /* DBG remove -- */
          if (def_tlstp->ndx != 1) __misc_terr(__FILE__, __LINE__);
          /* ---- */
          /* look for the one reg */
          val = def_tlstp->values[0];
          in_tlstp->ndx = 0;
          if (out_tlstp->ndx == 0) 
           {
            copy_tn_list(in_tlstp, out_tlstp);
           }
          else
           {
            for (i = 0; i < out_tlstp->ndx; i++) 
             {
              val2 = out_tlstp->values[i];
              if (val == val2) continue;
              /* know there are no duplicates so just add to list */
              add_tn_to_list_nodup(in_tlstp, val2);
             }
           }
         }
        set_union(in_tlstp, ip->optu.rap->tn_use_lst);
        /* get the successor insns */
        /* look at the next insn */
        ip2 = ip->iprev;
        if (ip2 != NULL)
         {
          set_union(ip2->optu.rap->tn_out_lst, in_tlstp);
         }
        /* if jump look at next block insn head */
        if (ip == bbp->ihd)
         {
          for (bbep = bbp->bbe_prev; bbep != NULL; bbep = bbep->bbenxt)
           {
            bbp2 = bbep->eblkp;
            set_union(bbp2->itail->optu.rap->tn_out_lst, in_tlstp);
           }
         }
        if (in_tlstp->ndx != sav_in_cnt || out_tlstp->ndx != sav_out_cnt)
         {
          changed = TRUE; 
         }
       }
      }
   nround++;
/* -- PUTMEBACK FOR DEBUGGING
   if (__opt_debug_flg)
    {
     dump_liveness_in_out_round(fgp, nround); 
    }
------- */
  }
 while (changed);
}

/*
 * dump liveness calculation state
 */
static void dump_liveness_in_out_round(struct flowg_t *fgp, int32 nround)
{
 int32 ndx;
 struct insn_t *ip;
 struct bblk_t *bbp;

 __my_fprintf(stdout, "\n##################################### \n");
 if (nround == -1)
  {
   __my_fprintf(stdout, "########### X86 REGISTER LIVENESS FINAL\n");
  }
 else
  {
   __my_fprintf(stdout, "########### X86 REGISTER LIVENESS  ROUND %d\n", nround);
  }
 __my_fprintf(stdout, "##################################### \n");
 for (bbp = fgp->fg_bblks; bbp != NULL; bbp = bbp->bbnxt)
  {
   for (ip = bbp->ihd; ip != NULL; ip = ip->inxt)
    {
     ndx = ip->ndx;
     if (ip->optu.rap->tn_in_lst->ndx != 0
      || ip->optu.rap->tn_out_lst->ndx != 0)
      {
       __my_fprintf(stdout, "INSN%d: \n", ndx);
      }
     if (ip->optu.rap->tn_in_lst->ndx != 0)
      {
       __my_fprintf(stdout, "  IN: ");
       dump_tmp_list(ip->optu.rap->tn_in_lst);
      }
     if (ip->optu.rap->tn_out_lst->ndx != 0)
      {
       __my_fprintf(stdout, "  OUT: ");
       dump_tmp_list(ip->optu.rap->tn_out_lst);
      }
    }
  }
}

/*
 * dump a register def/use list of all of the flowgraphs insns
 */
static void dump_tmp_defuse_list(struct flowg_t *fgp)
{
 int32 indx;
 struct insn_t *ip;
 struct tn_list_t *tlstp;
 struct bblk_t *bbp;

 __my_fprintf(stdout, "\n##################################### \n");
 __my_fprintf(stdout, "########### X86 REGISTER DEF/USE LIST \n");
 __my_fprintf(stdout, "##################################### \n");
 for (bbp = fgp->fg_bblks; bbp != NULL; bbp = bbp->bbnxt)
  {
   for (ip = bbp->ihd; ip != NULL; ip = ip->inxt)
    {
     indx = ip->ndx;
     tlstp = ip->optu.rap->tn_use_lst;
     if (tlstp->ndx != 0)
      {
       __my_fprintf(stdout, "  USE%d : ", indx);
       dump_tmp_list(tlstp);
      }
     tlstp = ip->optu.rap->tn_def_lst;
     if (tlstp->ndx != 0)
      {
       __my_fprintf(stdout, "  DEF%d : ", indx);
       dump_tmp_list(tlstp);
      }
    }
  }
}

/*
 * dump a tmp list
 */
static void dump_tmp_list(struct tn_list_t *tlstp)
{
 int32 i;

 if (tlstp->ndx == 0)
  {
   __my_fprintf(stdout, "NONE\n");
   return;
  }
 for (i = 0; i < tlstp->ndx; i++)
  {
   __my_fprintf(stdout, "%d ", tlstp->values[i]);
  }
 __my_fprintf(stdout, "\n");
}


/*
 * remove extra idp (esi) setting 
 * remove setting of idp reg if never used
 * so if defined and then defined again prior to use remove the first define
 *
 *
 * movl	24(%eax), %esi  #remove these idp setting never used
 * movl	28(%eax), %ebx
 * movl	__idpdat_17 + 36, %eax
 * movl	%eax, __idpdat_18 + 56
 * movl	%ebx, %eax
 * movl	4(%eax), %ebx
 * jmp *%ebx
 *
 * AIV LOOKATME - this algorithm could work but work for other regs
 * but algorithm is bad and doesn't find many to remove
 */
static void remove_multiple_idp_set(struct flowg_t *fgp)
{
 int32 use_flag, one_block_fg;
 struct insn_t *ip, *ip2, *ip3;
 struct tn_list_t *utlstp, *dtlstp;
 struct bblk_t *bbp;

 /* only handle NPP net change fg - could do others but rarely finds */
 /* insns to remove - and algorithm is bad so only handle these */
 if (fgp->flowgtyp != FLOWG_NPP && fgp->flowgtyp != FLOWG_NCHG && 
     fgp->flowgtyp != FLOWG_PROCESS_NCHG) return;

 /* flag if fg is one block */
 if (fgp->fg_bblks->bbnxt == NULL) one_block_fg = TRUE;
 else one_block_fg = FALSE;

 for (bbp = fgp->fg_bblks; bbp != NULL; bbp = bbp->bbnxt)
  {
   __cur_bbp = bbp;
   for (ip = bbp->ihd; ip != NULL; ip = ip2)
    {
     ip2 = ip->inxt;
     /* get first def fg and see if it is idp reg */
     dtlstp = ip->optu.rap->tn_def_lst;
     if (dtlstp->ndx != 0) 
      {
       if (dtlstp->values[0] == IDP_REG)
        {
         use_flag = FALSE;
         /* check all insn from here forward checking for another set */
         /* of idp prior to a use */
         for (ip3 = ip->inxt; ip3 != NULL; ip3 = ip3->inxt)
          {
           /* if call must leave the insn */
           if (is_call(ip3->opcod))
            { 
             use_flag = TRUE;
             break;
            }
           
           /* mark usage of idp */
           utlstp = ip3->optu.rap->tn_use_lst;
           if (utlstp->ndx != 0) 
            {
             /* src or dst regs is idp it is used */
             if (utlstp->values[0] == IDP_REG)
              {
               use_flag = TRUE;
               break;
              }
             else if (utlstp->ndx > 1 && utlstp->values[1] == IDP_REG)
              {
               use_flag = TRUE;
               break;
              }
            }
           /* defined idp reg again link out insn */
           dtlstp = ip3->optu.rap->tn_def_lst;
           if (dtlstp->ndx != 0 && dtlstp->values[0] == IDP_REG)
            {
             __linkout_insn(ip, TRUE);
             use_flag = TRUE;
             break; 
            }
          }
         /* if one block fg and not used can link it out */
         if (!use_flag && one_block_fg) __linkout_insn(ip, TRUE);
        }
      }
    }
  }
}

/*
 * AIV 02/13/09 - this is used for checking of use/def of registers
 * if there is a def but no use there 'could be' some bad code produced
 * code which is good includes setting of idp (%esi) and then calling
 * another fg which means for is no use
 * - also tasks/mfi has code which also is correct but has def and no use
 *
 * AIV LOOKATME - could use this to remove some instructions but would
 * need to handle the correct cases
 *
 *  such as code to do a bit select of an array element were the element
 *  is wide, does a wide copy of tmp a[0] but only does bsel of low word
 *  therefore no need to copy > one word
 *  
 *   r = a[0][2]
 * 
 *
static void chk_tmp_defuse_list(struct flowg_t *fgp, 
 struct avlnode_t **tn_ref_avltab, int32 num_tnrefs)
{
 int32 i, ti, src_ti, dst_ti;
 struct insn_t *ip;
 struct tn_t *tnp;
 struct tn_dup_t *tndup;
 struct tn_list_t *utlstp, *dtlstp;
 struct bblk_t *bbp;

 if (fgp->flowgtyp == FLOWG_MULTFI) return;

 for (bbp = fgp->fg_bblks; bbp != NULL; bbp = bbp->bbnxt)
  {
   for (ip = bbp->ihd; ip != NULL; ip = ip->inxt)
    {
     utlstp = ip->optu.rap->tn_use_lst;
     src_ti = ip->isrc.am_tni;
     dst_ti = ip->idst.am_tni;

     if (utlstp->ndx != 0) 
      {
       if (utlstp->values[0] == src_ti)
        {
         tnp = &(__tntab[src_ti]);
         tnp->is_reg_use = TRUE;
        }
       else if (utlstp->ndx > 1 && utlstp->values[1] == src_ti)
        {
         tnp = &(__tntab[src_ti]);
         tnp->is_reg_use = TRUE;
        }
       if (utlstp->values[0] == dst_ti)
        {
         tnp = &(__tntab[dst_ti]);
         tnp->is_reg_use = TRUE;
        }
       else if (utlstp->ndx > 1 && utlstp->values[1] == dst_ti)
        {
         tnp = &(__tntab[dst_ti]);
         tnp->is_reg_use = TRUE;
        }
      }
     dtlstp = ip->optu.rap->tn_def_lst;
     if (dtlstp->ndx != 0) 
      {
       if (dtlstp->values[0] == dst_ti)
        {
         tnp = &(__tntab[dst_ti]);
         tnp->is_reg_def = TRUE;
         tnp->def_ndx = ip->ndx;
        }
       else if (dtlstp->values[0] == src_ti) __misc_terr(__FILE__, __LINE__);
       else if (dtlstp->ndx > 1) __misc_terr(__FILE__, __LINE__);
      }
    }
  }

 for (i = 0; i < num_tnrefs; i++)
  {
   tndup = (struct tn_dup_t *) tn_ref_avltab[i]->valp;
   ti = tndup->tni; 
   tnp = &(__tntab[ti]);
   if (tnp->is_reg_def)
    {
     if (!tnp->is_reg_use) __misc_terr(__FILE__, __LINE__);
    }
  }
}
*/

static void build_reg_conflicts(struct flowg_t *fgp)
{
 int32 i, reg, reg2, is_move, src_ti, count;
 struct tn_list_t *tlstp;
 struct insn_t *ip;
 struct bblk_t *bbp;
 struct tn_t *tnp;
 
 for (bbp = fgp->fg_bblks; bbp != NULL; bbp = bbp->bbnxt)
  {
   for (ip = bbp->ihd; ip != NULL; ip = ip->inxt)
    {
     /* if it is a class mark all reg-out regs as cross call */
     if (is_call(ip->opcod)) 
      {
       tlstp = ip->optu.rap->tn_out_lst;
       for (i = 0; i < tlstp->ndx; i++)
        {
         reg = tlstp->values[i];
         tnp = &(__tntab[reg]);
         tnp->t_used_cross_call = TRUE;
        }
      }

     is_move = is_move_insn(ip->opcod);
     tlstp = ip->optu.rap->tn_def_lst; 
     if (tlstp->ndx == 0) continue;
     if (tlstp->ndx != 1) __misc_terr(__FILE__, __LINE__);
     reg = tlstp->values[0];
     if (reg < 0 || reg > __tntab_nxti) __misc_terr(__FILE__, __LINE__);
     count = ip->optu.rap->tn_out_lst->ndx;
     src_ti = ip->isrc.am_tni;

     if (count <= 0) continue;
     for (i = 0; i < count; i++)
      {
       reg2 = ip->optu.rap->tn_out_lst->values[i]; 
       if (reg2 < 0 || reg2 > __tntab_nxti) __misc_terr(__FILE__, __LINE__);
       if (reg2 == reg) continue;
       if (is_move && reg == src_ti) continue;
  //AIV FIXME - AIV LOOKATME - skipping the stack and special real reg for now
       if (reg2 == AR_SP || reg == AR_SP) continue;
       if (reg2 == AR_BP || reg == AR_BP) continue;
       if (reg2 == ST1 || reg == ST1) continue;
       add_conflict_edge(reg, reg2);
      }
    }
  }
}

/*
 * return T if opcod is any kind of call insn
 */
static int32 is_call(int32 opcod)
{
 struct insn_info_t *iip;

 iip = __to_iinfo_rec(opcod);
 if (iip->iclass == ICLASS_CALL || iip->iclass == ICLASS_ASL) 
  {
   return(TRUE);
  }
 return(FALSE);
}


/*
 * do the actual register assign
 *  1) this is either a one step reg alloc which does conservative reg 
 *    coalescing which is known to not result in more spills
 *  2) or it does a two step,  which first the aggressive coalesce of the regs
 *     and then does the safe, if the aggressive results in less spills
 *     it is used as it removes more instructions
 *
 *  number 2 - results removes more move instructions but takes longer
 *  as it makes two passes
 */
static void do_reg_assign(struct flowg_t *fgp, 
 struct avlnode_t **tn_ref_avltab, int32 num_tnrefs, int32 uses_idp_tmp)
{
 int32 i, ti, safe_spill_count, spill_count, save_spill_area, wlen, use_safe;
 int32 uses_ebx, uses_ebp;
#ifdef __CVC32__
 int32 uses_edi, uses_esi;
#else
 int32 uses_r12, uses_r13, uses_r14, uses_r15; 
#endif
 struct tn_dup_t *tndup;
 struct tn_list_t *tlstp;
 struct reg_alloc_info_t *raip;
 struct bblk_t *bbp;
 struct insn_t *ip, *ip2;
 struct tn_t *tnp;

 use_safe = TRUE;
 /* if doing the save register assign with conversative register coalesce */
 if (!__opt_reg_alloc)
  {
   __do_safe_coal = TRUE;
   spill_count = assign_tmpregs_to_regs(fgp, tn_ref_avltab, num_tnrefs, 
    uses_idp_tmp);
   /* AIV 11/14/09 - need the spill count for non -O as well */
   if (spill_count > 0) __spill_nonw_count += spill_count; 
  }
 else
  {
   /* AIV 01/20/10 - need to alloc a ralloci for the fixed x86 regs as well */
   /* this was a rare bug on 64-bit which was getting a segv */
   for (ti = 0; ti <= HIGH_X86_REG; ti++)
    {
     tnp = &(__tntab[ti]);
     if (tnp->tn_adj_lst == NULL) continue;
     tlstp = tnp->tn_adj_lst;
     /* need to sort the adj list - order is not yet sorted */
     qsort(tlstp->values, tlstp->ndx, sizeof(int32), int_cmp);
     /* copy the now sorted list for saving the info form the first reg alloc */
     raip = (struct reg_alloc_info_t *) 
        __my_malloc(sizeof(struct reg_alloc_info_t));
      raip->tn_adj_lst = copy_tmp_list(tlstp);      
     tnp->ralloci = raip;
    }
   /* AIV 02/22/10 - if not optimize reg opt - there is no need to sort */
   /* the list */
   /* sort the adjacent list for temps and if doing two stage assign */
   /* allocate the saved reg assign info struct */
   for (i = 0; i < num_tnrefs; i++)
    {
     tndup = (struct tn_dup_t *) tn_ref_avltab[i]->valp;
     ti = tndup->tni; 
     tnp = &(__tntab[ti]);
     if (tnp->tn_adj_lst == NULL) continue;
     tlstp = tnp->tn_adj_lst;
     /* need to sort the adj list - order is not yet sorted */
     qsort(tlstp->values, tlstp->ndx, sizeof(int32), int_cmp);
     /* copy the now sorted list for saving the info form the first reg alloc */
     raip = (struct reg_alloc_info_t *) 
       __my_malloc(sizeof(struct reg_alloc_info_t));
     raip->tn_adj_lst = copy_tmp_list(tlstp);      
     tnp->ralloci = raip;
    }
   /* do the register assign without the conservative register coalesce */
   __do_safe_coal = FALSE;
   use_safe = FALSE;
   spill_count = assign_tmpregs_to_regs(fgp, tn_ref_avltab, num_tnrefs, 
    uses_idp_tmp);

   /* if has spilled register - try the second safe reg coalesce */
   if (spill_count > 0)
    {
     /* save spill assign area */
     save_spill_area = fgp->ebp_wrd_area_siz;
     /* save callee used regs */
    //AIV FIXME - this is ugly and should change to an array or something
     uses_ebx = fgp->uses_ebx;
     uses_ebp = fgp->uses_ebp;
#ifdef __CVC32__
     uses_edi =  fgp->uses_edi;
     uses_esi = fgp->uses_esi;
#else
     uses_r12 = fgp->uses_r12;
     uses_r13 = fgp->uses_r13;
     uses_r14 = fgp->uses_r14;
     uses_r15 = fgp->uses_r15;
#endif
     fgp->uses_ebx = FALSE;
     fgp->uses_ebp = FALSE;
#ifdef __CVC32__
     fgp->uses_edi = FALSE;
     fgp->uses_esi = FALSE;
#else
     fgp->uses_r12 = FALSE;
     fgp->uses_r13 = FALSE;
     fgp->uses_r14 = FALSE;
     fgp->uses_r15 = FALSE;
#endif
     for (i = 0; i < num_tnrefs; i++)
      {
       tndup = (struct tn_dup_t *) tn_ref_avltab[i]->valp;
       ti = tndup->tni; 
       tnp = &(__tntab[ti]);
       if ((raip = tnp->ralloci) == NULL) continue;
       /* save the first reg alloc info */
       raip->x86_regno = tnp->x86_regno;
       raip->spill_ebp_byt_ofs = tnp->spill_ebp_byt_ofs;
       raip->tn_assigned = tnp->tn_assigned;
       raip->tn_spilled = tnp->tn_spilled;
       raip->t_used_cross_call = tnp->t_used_cross_call;
       raip->t_used_in_bw_insn = tnp->t_used_in_bw_insn;
       raip->tn_coalesce_into = tnp->tn_coalesce_into;
  
       /* reset values for second alloc */
       tnp->spill_ebp_byt_ofs = -1;
       tnp->tn_coalesce_into = -1;
       tnp->tn_spilled = FALSE;
       tnp->tn_spill_fold = FALSE;
       tnp->tn_assigned = FALSE;
       tnp->t_used_cross_call = FALSE;
       tnp->t_used_in_bw_insn = FALSE;
       tnp->x86_regno = REG_NONE;
      }

     /* save the instructions which are marked for removal */
     for (bbp = fgp->fg_bblks; bbp != NULL; bbp = bbp->bbnxt)
      {
       for (ip = bbp->ihd; ip != NULL; ip = ip->inxt)
        {
         ip->is_coal_out2 = ip->is_coal_out;
         ip->is_coal_out = FALSE;
         /* AIV 1/20/09 - need to reset the cross call flag */
         if (is_call(ip->opcod)) 
          {
           tlstp = ip->optu.rap->tn_out_lst;
           for (i = 0; i < tlstp->ndx; i++)
            {
             ti = tlstp->values[i];
             tnp = &(__tntab[ti]);
             tnp->t_used_cross_call = TRUE;
            }
          }
        }
      }

    /* now do the reg assign with the safe (conveservative) assign */
    __do_safe_coal = TRUE;
    safe_spill_count = assign_tmpregs_to_regs(fgp, tn_ref_avltab, num_tnrefs, 
     uses_idp_tmp);
  
    /* if doesn't result is less spills use the aggressive assign */
    if (spill_count <= safe_spill_count)
     {
      use_safe = FALSE;
      for (i = 0; i < num_tnrefs; i++)
       {
        tndup = (struct tn_dup_t *) tn_ref_avltab[i]->valp;
        ti = tndup->tni; 
        tnp = &(__tntab[ti]);
        if ((raip = tnp->ralloci) == NULL) continue;
        /* restore original assignment with more coalesce regs */
        tnp->x86_regno = raip->x86_regno;
        tnp->spill_ebp_byt_ofs = raip->spill_ebp_byt_ofs;
        tnp->tn_assigned = raip->tn_assigned;
        tnp->tn_spilled = raip->tn_spilled;
        tnp->tn_coalesce_into = raip->tn_coalesce_into;
        tnp->t_used_cross_call = raip->t_used_cross_call;
        tnp->t_used_in_bw_insn = raip->t_used_in_bw_insn;
       }
      /* put back the used regs and spill area size */
      fgp->ebp_wrd_area_siz = save_spill_area;
      fgp->uses_ebx = uses_ebx;
      fgp->uses_ebp = uses_ebp;
#ifdef __CVC32__
      fgp->uses_edi = uses_edi;
      fgp->uses_esi = uses_esi;
#else
      fgp->uses_r12 = uses_r12;
      fgp->uses_r13 = uses_r13;
      fgp->uses_r14 = uses_r14;
      fgp->uses_r15 = uses_r15;
#endif
      /* record the spill count */
      __spill_nonw_count += spill_count; 
     }
    else
     {
      use_safe = TRUE;
      __spill_nonw_count += safe_spill_count; 
     }
    }
  }

 /* assign space for all wide and strength areas */
 for (i = 0; i < num_tnrefs; i++)
  {
   tndup = (struct tn_dup_t *) tn_ref_avltab[i]->valp;
   ti = tndup->tni; 
   tnp = &(__tntab[ti]);
   /* AIV 01/03/06 - need to skip set regs and those which cannot */
   /* be in a register */
   if (ti > HIGH_X86_REG && !is_tn_general_reg(ti))
    {
     wlen = __get_tn_vec_size(tnp);
     spill_tmp(tnp, fgp, wlen, NULL, -1, -1);
     __spill_count++; 
    }
   /* if has two reg alloc struct must free it */
   /* if if using the other alloc must set adj list to point to second */
   if ((raip = tnp->ralloci) == NULL) continue;
   if (!use_safe)
    {
     free_tmp_list(tnp->tn_adj_lst);
     tnp->tn_adj_lst = raip->tn_adj_lst;
    }
   else free_tmp_list(raip->tn_adj_lst);
   __my_free(raip, sizeof(struct reg_alloc_info_t));
   tnp->ralloci = NULL;
  }
 
 /* free the coalesced move instructions */
 for (bbp = fgp->fg_bblks; bbp != NULL; bbp = bbp->bbnxt)
  {
   for (ip = bbp->ihd; ip != NULL; ip = ip2)
    {
     ip2 = ip->inxt;
     __cur_bbp = bbp;
     /* either the first or the second coalesce */
     if (spill_count > 0 && !use_safe)
      {
       if (ip->is_coal_out2) 
        {
         /* AIV 06/17/09 - memory leak here need to free use/def */
         free_adj_insn_fields(ip);
         __linkout_insn(ip, TRUE);
         __coalesce_count++; 
        }
      }
     else if (ip->is_coal_out) 
      {
       /* AIV 06/17/09 - memory leak here need to free use/def */
       free_adj_insn_fields(ip);
       __linkout_insn(ip, TRUE);
       __coalesce_count++; 
      }
    }
  }
}

/*
 * copy a tmp adjacent list struct
 */
static struct tn_list_t *copy_tmp_list(struct tn_list_t *src_tlstp)
{
 struct tn_list_t *tlstp;
 int32 size;

 tlstp = (struct tn_list_t *) __my_malloc(sizeof(struct tn_list_t));
 tlstp->size = src_tlstp->size;
 tlstp->ndx = src_tlstp->ndx;
 size = src_tlstp->size*sizeof(int32);
 tlstp->values = (int32 *) __my_malloc(size);
 memcpy(tlstp->values, src_tlstp->values, src_tlstp->ndx*sizeof(int32));
 return(tlstp);
}

/*
 * assign actual tmp registers to x86 registers or spill overflow
 *
 * for now it assigns registers in the following order
 * 1) ebx - to regs used across calls and byte reg
 * 2) ebx, esi - to regs used across calls
 * 3) eax, ebx, edx - to regs used in byte insn 
 * 4) all remaining regs
 *
 * AIV NOTE AIV FIXME - ecx is currently saved for overflow handling
 */
#ifdef __CVC32__
static int32 assign_tmpregs_to_regs(struct flowg_t *fgp, 
 struct avlnode_t **tn_ref_avltab, int32 tn_refs, int32 uses_idp_tmp)
{
 int32 i, num_regs, ti, spill_ndx, num_using_over;
 int32 *regs, *spill_regs;
 int32 num_call_regs, num_gen_regs;
 struct tn_t *tnp;
 struct tn_dup_t *tndup;
 /* regs live across calls with a byte reg*/
 int32 call_byte_regs[] = {EBX}; 
 /* regs live across calls */
 int32 call_regs[4]; 
 /* regs that can be used as bytes */
 int32 byte_word_regs[] = {EAX, EBX, EDX, ECX}; 
 /* all gen regs */
 int32 all_gen_regs[7]; 

 /* if flow graph uses idp cannot use esi */
 /* AIV 01/08/08 - do not mark fgp as using esi no need for push/pops */
 /* of esi unless esi is never accessed via __idp then may use it */
 /* as regular reg */
 if (uses_idp_tmp)
  {
   num_call_regs = 3;
   call_regs[0] = EBX; 
   call_regs[1] = EDI; 
   call_regs[2] = EBP; 
   call_regs[3] = -1; 

   num_gen_regs = 6;
   all_gen_regs[0] = EAX;
   all_gen_regs[1] = EBX;
   all_gen_regs[2] = EDX;
   all_gen_regs[3] = EDI;
   all_gen_regs[4] = EBP;
   all_gen_regs[5] = ECX;
   all_gen_regs[6] = -6;
  }
 else
  {
   /* if uses idp mark flowg graph as using esi */
   num_call_regs = 4;
   call_regs[0] = EBX; 
   call_regs[1] = ESI; 
   call_regs[2] = EDI; 
   call_regs[3] = EBP; 

   num_gen_regs = 7;
   all_gen_regs[0] = EAX;
   all_gen_regs[1] = EBX;
   all_gen_regs[2] = EDX;
   all_gen_regs[3] = ESI;
   all_gen_regs[4] = EDI;
   all_gen_regs[5] = EBP;
   all_gen_regs[6] = ECX;
  }
 
 /* AIV 12/01/06 - need to start at 4 problems with -O2 ?????? */
 /* AIV 01/04/06 - fix/aesfix.v form aes_cores design causes seg fault */
 /* increase size to 8 for unknown reasons */
 /* AIV FIXME - why is this needed ?????????????????????? */
 /* MFI calls don't push onto stack????????? */
 fgp->ebp_wrd_area_siz = 8;

 /* AIV 05/23/12 - if DPI args must create area on stack so that */
 /* passing args do not overlap with those overflow tmps */
 /* this is needed as special case since there is no call expand for DPI */
 if (fgp->max_dpi_wrds > 2)
  {
   fgp->ebp_wrd_area_siz = fgp->max_dpi_wrds*WRDBYTES;
  }

 /* no registers to assign */
 if (tn_refs == -1) return(-1);

 /* AIV 01/20/06 - used to be done in linear scan - cannot be assumed */
 /* set here - need to mark the insn with use bytes/half words */
 init_tmp_flags(fgp, tn_ref_avltab, tn_refs);

 /* assign the low part of the reg tab to the actual x86 registers */
 for (i = 1; i <= HIGH_MACH_REG; i++)
  {
   __tntab[i].x86_regno = i;
  }

 regs = (int32 *) __my_malloc((tn_refs + 1)*sizeof(int32));
 spill_regs = (int32 *) __my_malloc((tn_refs + 1)*sizeof(int32));
 num_regs = 0;
 for (i = 0; i < tn_refs; i++)
  {
   tndup = (struct tn_dup_t *) tn_ref_avltab[i]->valp;
   ti = tndup->tni; 
   tnp = &(__tntab[ti]);
   if (is_tn_general_reg(ti))
    {
     regs[num_regs] = ti;
     num_regs++;
    }
  }

 /* no registers to assign */
 if (num_regs == 0) 
  {
   /* AIV 06/16/09 - memory leak here need to free alloc values then ret */
   __my_free(regs, (tn_refs + 1)*sizeof(int32));
   __my_free(spill_regs, (tn_refs + 1)*sizeof(int32));
   return(-1);
  }

 /* AIV 01/22/09 - now only coalesce when -O is turned on - to speed comp */
 if (__opt_reg_alloc)
  {
   num_regs = simple_coalesce(fgp, regs, num_regs, num_gen_regs, 4,
    num_call_regs, 1);
  }

 if (__opt_debug_flg) 
  {
   __my_fprintf(stdout, "\n ************ \n");
   __my_fprintf(stdout, " **** TMP ADJACENT LIST\n");
   __my_fprintf(stdout, " ************ \n");
   for (i = 0; i < num_regs; i++)
    {
     ti = regs[i];
     tnp = &(__tntab[ti]);
     if (tnp->tn_adj_lst->ndx == 0) continue;
     __my_fprintf(stdout, " r%d: ", ti);
     dump_tmp_list(tnp->tn_adj_lst);
    }
   __my_fprintf(stdout, "\n\n");
  }

 spill_ndx = assign_regs(regs, num_regs, call_byte_regs, 1, call_regs, 
  num_call_regs, byte_word_regs, 4, all_gen_regs, num_gen_regs, TRUE, 
  spill_regs, fgp);
 if (spill_ndx > 0)
  {
   for (i = 0; i < num_regs; i++)
    {
     ti = regs[i];
     tnp = &(__tntab[ti]);
     tnp->tn_spilled = FALSE;
     tnp->tn_spill_fold = FALSE;
     tnp->tn_assigned = FALSE;
     tnp->x86_regno = REG_NONE;
    }
   spill_ndx = assign_regs(regs, num_regs, call_byte_regs, 1, call_regs, 
    num_call_regs, byte_word_regs, 3, all_gen_regs, num_gen_regs - 1, FALSE, 
    spill_regs, fgp);
  }

 /* try to assign the overflow reg to the spilled registers */
 num_using_over = try_to_assign_overflow_reg(fgp, spill_regs, spill_ndx);
 
 __my_free(regs, (tn_refs + 1)*sizeof(int32));
 __my_free(spill_regs, (tn_refs + 1)*sizeof(int32));
 return(spill_ndx - num_using_over); 
}
#else
static int32 assign_tmpregs_to_regs(struct flowg_t *fgp, 
 struct avlnode_t **tn_ref_avltab, int32 tn_refs, int32 uses_idp_tmp)
{
 int32 i, num_regs, ti, spill_ndx, num_using_over;
 int32 *regs, *spill_regs;
 int32 num_call_regs, num_gen_regs;
 struct tn_t *tnp;
 struct tn_dup_t *tndup;
 /* regs live across calls with a byte reg*/
//AIV LOOKATME - could use R15 (idp reg) here???
 int32 call_byte_regs[] = {RBX, R12, R13, R14}; 
 /* regs live across calls */
 int32 call_regs[5]; 
 /* regs that can be used as bytes */
 int32 byte_word_regs[] = {RAX, RBX, RDX, R8, R9, R10, R11, R12, R13, 
  R14, RCX}; 
 /* all gen regs */
 int32 all_gen_regs[HIGH_GEN_REG]; 

 /* AIV 12/03/08 - can no use rbp since using no stack frame */
 /* if flow graph uses idp cannot use esi */
 /* idp is now in %r15 for 64-bit */
 num_call_regs = 5;
 /* 64-bit rbx and r12-r15 are preserved across calls */
 call_regs[0] = RBX; 
 call_regs[1] = R12; 
 call_regs[2] = R13; 
 call_regs[3] = R14; 
 call_regs[4] = RBP; 

 num_gen_regs = 13;
 /* first one callee save regs, then callee save regs, then overflow */
 all_gen_regs[0] = RAX;
 all_gen_regs[1] = RDX;
 all_gen_regs[2] = RDI;
 all_gen_regs[3] = R8;
 all_gen_regs[4] = R9;
 all_gen_regs[5] = R10;
 all_gen_regs[6] = RBX;
 all_gen_regs[7] = R11;
 all_gen_regs[8] = R12;
 all_gen_regs[9] = R13;
 all_gen_regs[10] = R14;
 all_gen_regs[11] = RBP;
 all_gen_regs[12] = RCX;
 
 /* AIV 12/01/06 - need to start at 4 problems with -O2 ?????? */
 /* AIV 01/04/06 - fix/aesfix.v form aes_cores design causes seg fault */
 /* increase size to 8 for unknown reasons */
 /* AIV FIXME - why is this needed ?????????????????????? */
 /* MFI calls don't push onto stack????????? */
 fgp->ebp_wrd_area_siz = 8;

 /* AIV 05/23/12 - if DPI args must create area on stack so that */
 /* passing args do not overlap with those overflow tmps */
 /* this is needed as special case since there is no call expand for DPI */
 if (fgp->max_dpi_wrds > 1)
  {
   fgp->ebp_wrd_area_siz = fgp->max_dpi_wrds*WRDBYTES;
  }

 /* no registers to assign */
 if (tn_refs == -1) return(-1);

 /* AIV 01/20/06 - used to be done in linear scan - cannot be assumed */
 /* set here - need to mark the insn with use bytes/half words */
 init_tmp_flags(fgp, tn_ref_avltab, tn_refs);

 /* assign the low part of the reg tab to the actual x86 registers */
 for (i = 1; i <= HIGH_MACH_REG; i++)
  {
   __tntab[i].x86_regno = i;
  }

 regs = (int32 *) __my_malloc((tn_refs + 1)*sizeof(int32));
 spill_regs = (int32 *) __my_malloc((tn_refs + 1)*sizeof(int32));
 spill_ndx = 0;

 num_regs = 0;
 for (i = 0; i < tn_refs; i++)
  {
   tndup = (struct tn_dup_t *) tn_ref_avltab[i]->valp;
   ti = tndup->tni; 
   tnp = &(__tntab[ti]);
   if (is_tn_general_reg(ti))
    {
     regs[num_regs] = ti;
     num_regs++;
    }
  }

 /* no registers to assign */
 if (num_regs == 0) 
  {
   /* AIV 06/16/09 - memory leak here need to free alloc values then ret */
   __my_free(regs, (tn_refs + 1)*sizeof(int32));
   __my_free(spill_regs, (tn_refs + 1)*sizeof(int32));
   return(-1);
  }

 /* AIV 12/30/08 - 64-bit has 11 byte/word registers */
 /* AIV 01/22/09 - now only coalesce when -O is turned on - to speed comp */
 if (__opt_reg_alloc)
  {
   num_regs = simple_coalesce(fgp, regs, num_regs, num_gen_regs, 11,
    num_call_regs, 1);
  }

 if (__opt_debug_flg) 
  {
   __my_fprintf(stdout, "\n ************ \n");
   __my_fprintf(stdout, " **** TMP ADJACENT LIST\n");
   __my_fprintf(stdout, " ************ \n");
   for (i = 0; i < num_regs; i++)
    {
     ti = regs[i];
     tnp = &(__tntab[ti]);
     if (tnp->tn_adj_lst->ndx == 0) continue;
     __my_fprintf(stdout, " r%d: ", ti);
     dump_tmp_list(tnp->tn_adj_lst);
    }
   __my_fprintf(stdout, "\n\n");
  }

 spill_ndx = assign_regs(regs, num_regs, call_byte_regs, 4, call_regs, 
  num_call_regs, byte_word_regs, 11, all_gen_regs, num_gen_regs, TRUE, 
  spill_regs, fgp);
 if (spill_ndx > 0)
  {
   for (i = 0; i < num_regs; i++)
    {
     ti = regs[i];
     tnp = &(__tntab[ti]);
     tnp->tn_spilled = FALSE;
     tnp->tn_spill_fold = FALSE;
     tnp->tn_assigned = FALSE;
     tnp->x86_regno = REG_NONE;
    }
   /* AIV 12/30/08 - this needs to be one less for byte/word regs */
   /* cannot use the last overflow reg */
   spill_ndx = assign_regs(regs, num_regs, call_byte_regs, 4, call_regs, 
    num_call_regs, byte_word_regs, 10, all_gen_regs, num_gen_regs - 1, FALSE, 
    spill_regs, fgp);
  }

 /* try to assign the overflow reg to the spilled registers */
 num_using_over = try_to_assign_overflow_reg(fgp, spill_regs, spill_ndx);
 
 /* add to the gen register spill count - minus number overflow reg asgn to */
 __my_free(regs, (tn_refs + 1)*sizeof(int32));
 __my_free(spill_regs, (tn_refs + 1)*sizeof(int32));
 return(spill_ndx - num_using_over); 
}
#endif

static int32 assign_regs(int32 *regs, int32 num_regs,
 int32 *call_byte_regs, int32 num_call_byte,
 int32 *call_regs, int32 num_call_regs, int32 *byte_word_regs,
 int32 num_byte_word_regs, int32 *all_gen_regs, int32 num_gen_regs, 
 int32 ret_on_spill, int32 *spill_regs, struct flowg_t *fgp)
{
 int32 i, ti, spill_ndx;
 struct tn_t *tnp;
#ifdef __CVC32__
 int32 shift_reg[1]; 
#else
 int32 arg;
 int32 p0[1]  = {RDI};
 int32 p1[1]  = {RSI};
 int32 p2[1]  = {RDX};
 int32 p3[1]  = {RCX};
 int32 p4[1]  = {R8};
 int32 p5[1]  = {R9};
 int32 *ip;
#endif

 spill_ndx = 0;
       
 /* AIV 02/19/08 - only if register optimize - attempt to use ecx for */
 /* variable shifts.  x86 uses ecx as the shift variable - this works */
 /* becuase the ret_on_spill flag attempts to use ecx - if spilled */
 /* it doens't use ecx */
#ifdef __CVC32__
 /* AIV 03/26/09 - this cannot work currently for 64 since large constants */
 /* need to be loaded into a tmps aka our fixup tmp %rcx */
 /* this would work if all large literal values are loaded into tmps at */
 /* code gen time for 64-bit - which it should do */
 if (__opt_reg_alloc)
  {
   if (ret_on_spill) 
    {
     shift_reg[0] = AR_CX;
     for (i = 0; i < num_regs; i++)
      {
       ti = regs[i];
       tnp = &(__tntab[ti]);
       if (tnp->t_used_cross_call) continue;
       if (tnp->tn_used_var_shift) 
        {
         if (!assign_x86_reg_set(fgp, tnp, shift_reg, 1, ti))
          {
           spill_regs[spill_ndx++] = ti;
           tnp->tn_spilled = TRUE;
          }
        }
      }
    }
  }
#endif

 for (i = 0; i < num_regs; i++)
  {
   ti = regs[i];
   tnp = &(__tntab[ti]);
   if (tnp->t_used_cross_call && tnp->t_used_in_bw_insn) 
    {
     if (!assign_x86_reg_set(fgp, tnp, call_byte_regs, num_call_byte, ti))
      {
       if (ret_on_spill) 
        {
         tnp->x86_regno = REG_NONE;
         return(TRUE);
        }
       spill_regs[spill_ndx++] = ti;
       tnp->tn_spilled = TRUE;
      }
    }
  }
         
 /* assign cross call regs */
 for (i = 0; i < num_regs; i++)
  {
   ti = regs[i];
   tnp = &(__tntab[ti]);
   if (tnp->tn_assigned || tnp->tn_spilled) continue;

   if (tnp->t_used_cross_call) 
    {
     if (!assign_x86_reg_set(fgp, tnp, call_regs, num_call_regs, ti))
      {
       if (ret_on_spill) 
        {
         tnp->x86_regno = REG_NONE;
         return(TRUE);
        }
       spill_regs[spill_ndx++] = ti;
       tnp->tn_spilled = TRUE;
      }
    }
  }

 /* assign byte registers */
 for (i = 0; i < num_regs; i++)
  {
   ti = regs[i];
   tnp = &(__tntab[ti]);
   if (tnp->tn_assigned || tnp->tn_spilled) continue;
   if (tnp->t_used_in_bw_insn) 
    {
     if (!assign_x86_reg_set(fgp, tnp, byte_word_regs, num_byte_word_regs, ti))
      {
       if (ret_on_spill) 
        {
         tnp->x86_regno = REG_NONE;
         return(TRUE);
        }
       spill_regs[spill_ndx++] = ti;
       tnp->tn_spilled = TRUE;
      }
    }
  }

#ifndef __CVC32__
 /* AIV 03/18/10 - for 64-bit make another pass and first attempt to place */
 /* tmps which are passed as args to wrapper calls into the passed regs */
 /* so can remove some moves - just place in rdi and this movq is removed */
 /*      movq    %rsi, %rdi  */
 /*      call	__asl_trigger_ectrl */
 ip = NULL;
 for (i = 0; i < num_regs; i++)
  {
   ti = regs[i];
   tnp = &(__tntab[ti]);
   if (tnp->tn_assigned || tnp->tn_spilled) continue;
   if ((arg = tnp->passed_args) != 0) 
    {
     /* get the argument 1 element set */
     switch (arg) {
      case 1: ip = p0; break;
      case 2: ip = p1; break;
      case 3: ip = p2; break;
      case 4: ip = p3; break;
      case 5: ip = p4; break;
      case 6: ip = p5; break;
      default: __case_terr(__FILE__, __LINE__); break;
     }
   
     /* try to assign the tmp to the passed reg */
     if (!assign_x86_reg_set(fgp, tnp, ip, 1, ti)) continue;
    }
  }
#endif

 /* assign all remaining registers */
 for (i = 0; i < num_regs; i++)
  {
   ti = regs[i];
   tnp = &(__tntab[ti]);
   if (tnp->tn_assigned || tnp->tn_spilled) continue;

   if (!assign_x86_reg_set(fgp, tnp, all_gen_regs, num_gen_regs, ti))
    {
     if (ret_on_spill) 
      {
       tnp->x86_regno = REG_NONE;
       return(TRUE);
      }
     spill_regs[spill_ndx++] = ti;
     tnp->tn_spilled = TRUE;
    }
  }
 return(spill_ndx);
}
     

/*
 * coalesce move instructions by combining move instructions into 
 * from reg to reg into one register
 */
static int32 simple_coalesce(struct flowg_t *fgp, int32 *regs, int32 num_regs,
 int32 num_gen_regs, int32 num_byte_regs, int32 num_call_regs,
 int32 num_call_byte_regs)
{
 int32 new_num_regs, rm_ndx, i, j, dst_tni, src_tni, reg, count;
 int32 cross_call_reg_count, byte_hw_reg_count, both_count, known_spilled;
 int32 *rm_regs;
 struct bblk_t *bbp;
 struct tn_t *src_tnp, *dst_tnp, *tnp;
 struct insn_t *ip, *ip2;
 struct tn_list_t *src_tlstp, *dst_tlstp;

 reg = -1;
 rm_regs = (int32 *) __my_malloc(num_regs*sizeof(int32));
 rm_ndx = 0;
 for (bbp = fgp->fg_bblks; bbp != NULL; bbp = bbp->bbnxt)
  {
   for (ip = bbp->ihd; ip != NULL; ip = ip2)
    {
     __cur_bbp = bbp;
     ip2 = ip->inxt;

     /* non-zeroing (no mozbl, etc) move instruction */
     if (ip->opcod != I_MOVA && ip->opcod != I_STOREA //) continue;
        && ip->opcod != I_MOVB && ip->opcod != I_STOREB
        && ip->opcod != I_MOVW && ip->opcod != I_STOREW) continue;


     src_tni = ip->isrc.am_tni;
     dst_tni = ip->idst.am_tni;
     /* maybe a unary case - tni is in dst - skip it */
     /* AIV 01/11/08 - dst can have -1 here as well for AM_NLO */
     if (src_tni == -1 || dst_tni == -1) continue;
     src_tnp = &(__tntab[src_tni]);
     dst_tnp = &(__tntab[dst_tni]);

 //AIV FIXME - only doing regular reg for now 
 //these are related - asl wrapper calls shouldn't depend on type
     if (ip->isrc.amode != AM_REG || ip->idst.amode != AM_REG) continue;
     
     if (src_tnp->tn_coalesce_into != -1) 
      {
       src_tni = src_tnp->tn_coalesce_into; 
       src_tnp = &(__tntab[src_tni]);
      }
     if (dst_tnp->tn_coalesce_into != -1) 
      {
       dst_tni = dst_tnp->tn_coalesce_into; 
       dst_tnp = &(__tntab[dst_tni]);
      }

     /* linkout copy to itself */
     /* AIV LOOKATME - these get coalesce anyway from bbopt move to itself */
     if (src_tni == dst_tni)
      {
       if (ip->isrc.amode == AM_REG && ip->idst.amode == AM_REG)
        {
         /* AIV 01/20/09 - now must mark these for later removal */
         ip->is_coal_out = TRUE;
         __coalesce_count++; 
        }
       continue;
      }

     /* can't coalesce if either is machine reg */
     /* may need special regs, shift, div */
     if (src_tni < HIGH_MACH_REG || dst_tni < HIGH_MACH_REG) continue;

     /* if either used wide, can't coalesce */
     if (!is_tn_general_reg(src_tni) || !is_tn_general_reg(dst_tni))
       continue;

     /* AIV 01/12/09 - could be using the two pass reg alloc */
     if (__do_safe_coal)
      {
       src_tlstp = src_tnp->tn_adj_lst;
       dst_tlstp = dst_tnp->tn_adj_lst;
      }
     else
      {
       src_tlstp = src_tnp->ralloci->tn_adj_lst;
       dst_tlstp = dst_tnp->ralloci->tn_adj_lst;
      }
     if (dst_tlstp == NULL || src_tlstp == NULL) 
        __misc_terr(__FILE__, __LINE__);

     /* dst is adjacent to the source cannot coalesce */
     if (find_tni(dst_tlstp, src_tni) != -1) continue;
 

     /* if the union of the dst and src tnis is greater than num regs cannot */
     /* coalesce with guarantee of no spill */
     /* AIV 01/12/09 - now doing a two pass which if safe do conversative */
     /* coalesce which is known to not cause more spills */
     if (__do_safe_coal)
      {
       /* AIV 12/15/09 - this should be only done here for the simple */
       /* which is to guarantee no spills */
       if (src_tlstp->ndx > num_gen_regs) continue;
 
       count = src_tlstp->ndx;
       cross_call_reg_count = 0;
       byte_hw_reg_count = 0;
       both_count = 0;
       for (i = 0; i < dst_tlstp->ndx; i++)
        {
         reg = dst_tlstp->values[i];
         tnp = &(__tntab[reg]);
         /* get total number of register count */
         if (find_tni(src_tlstp, reg) == -1) 
          {
           count++;
          }
         /* get special reg use counts */
         if (tnp->t_used_in_bw_insn)
          {
           if (tnp->t_used_cross_call)
            { 
             both_count++;
            }
           else byte_hw_reg_count++;
          }
         else if (tnp->t_used_cross_call)
          {
           cross_call_reg_count++;
          }
        }
  
       /* know if is going to spill may as well coalesce */
       known_spilled = ((both_count > num_call_byte_regs) || 
                        (cross_call_reg_count > num_call_regs) || 
                        (byte_hw_reg_count > num_byte_regs));
       if (!known_spilled)
        {
         /* has more than all general regs continue */
         if (count > num_gen_regs) continue;
  
         /* add all adj to the source now and get special regs count */
         for (i = 0; i < src_tlstp->ndx; i++)
          {
           /* shared adj tmp already been counted continue */
           reg = src_tlstp->values[i];
           if (find_tni(dst_tlstp, reg) != -1) continue;
  
           tnp = &(__tntab[reg]);
           if (tnp->t_used_in_bw_insn)
            {
             if (tnp->t_used_cross_call)
              { 
               both_count++;
              }
             else byte_hw_reg_count++;
            } 
           else if (tnp->t_used_cross_call)
            {
             cross_call_reg_count++;
            }
          }
         /* if adding the two now results in spilling do not combine the two */
         known_spilled = ((both_count > num_call_byte_regs) || 
                         (cross_call_reg_count > num_call_regs) || 
                         (byte_hw_reg_count > num_byte_regs));
         if (known_spilled) continue;
        }
      }
     else if (src_tlstp->ndx > (num_gen_regs+5)) continue;
     /* AIV 12/15/09 - AIV LOOKATME - really this continue stmt shouldn't */
     /* be here this is the aggressive coalesce - problem is with -O */
     /* it also inlines which can causes this to take way too long */
     /* cap at +5 - think should change -Ogate (opt reg) to -O and -O2 */

     if (__opt_debug_flg)
      {
       __my_fprintf(stdout, "[%d] TMP COALESCE R%d => R%d\n",
         ip->ndx, dst_tni, src_tni);
       dump_tmp_list(src_tlstp);
       dump_tmp_list(dst_tlstp);
      }
     set_union(src_tlstp, dst_tlstp);
     if (__opt_debug_flg)
      {
       dump_tmp_list(src_tlstp);
      }
     rm_regs[rm_ndx++] = dst_tni;
     if (src_tnp->tn_coalesce_into != -1) 
      dst_tnp->tn_coalesce_into = src_tnp->tn_coalesce_into; 
     else dst_tnp->tn_coalesce_into = src_tni;

//AIV FIXME????? WHAT ABOUT BYTES
     if (!src_tnp->t_used_cross_call && dst_tnp->t_used_cross_call)
      {
       src_tnp->t_used_cross_call = TRUE;
      }
     if (!src_tnp->t_used_in_bw_insn && dst_tnp->t_used_in_bw_insn)
      {
       src_tnp->t_used_in_bw_insn = TRUE;
      }
     convert_all_adjregs(regs, num_regs, dst_tni, src_tni);
     dst_tlstp->ndx = 0;
     /* AIV 12/30/08 - know this can never happen since it is checked above */
     /* this could change if coalesce other modes */
     //if (ip->isrc.amode != AM_REG || ip->idst.amode != AM_REG) continue;
     ip->is_coal_out = TRUE;
    }
  }
 
 /* no registers coalesced */
 if (rm_ndx == 0) 
  {
   __my_free(rm_regs, num_regs*sizeof(int32));
   return(num_regs); 
  }

 for (i = 0; i < rm_ndx; i++)
  {
   for (j = 0; j < num_regs; j++)
    {
     if (rm_regs[i] == regs[j]) 
      {
       regs[j] = -1;
      }
    }
  }
 new_num_regs = 0;
 for (i = 0; i < num_regs; i++)
  {
   if (regs[i] == -1) continue;
   regs[new_num_regs++] = regs[i]; 
  }
 __my_free(rm_regs, num_regs*sizeof(int32));
 return(new_num_regs);
}
      

/*
 * remove all the 'from_tni' from all the adjacent temps as from_tni
 * is coalesced into to_tni
 */
static void convert_all_adjregs(int32 *regs, int32 num_regs, int32 from_tni, 
 int32 to_tni)
{
 int32 tni, i, ndx;
 struct tn_list_t *tlstp, *tlstp2;
 struct tn_t *tnp;

 /* update all coalesce into to the new to_tni */
 for (i = 0; i < num_regs; i++)
  {
   if ((tni = regs[i]) == -1) continue;
   tnp = &(__tntab[tni]);
   if (tnp->tn_coalesce_into == from_tni) 
    {
     tnp->tn_coalesce_into = to_tni;
    }
  }

 /* AIV 01/12/09 - could be using the two pass reg alloc */
 tnp = &(__tntab[from_tni]);
 if (__do_safe_coal) tlstp = tnp->tn_adj_lst;
 else tlstp = tnp->ralloci->tn_adj_lst;

 /* AIV 01/22/09 - better to only do the adjacent regs as seperate loop */
 for (i = 0; i < tlstp->ndx; i++)
  {
   tni = tlstp->values[i];
   tnp = &(__tntab[tni]);
   /* if doesn't contain any from tni continue */
   if (__do_safe_coal) tlstp2 = tnp->tn_adj_lst;
   else tlstp2 = tnp->ralloci->tn_adj_lst;

   ndx = find_tni(tlstp2, from_tni);
#ifdef __CVC_DEBUG__
   /* DBG remove -- */
   if (ndx == -1) __misc_terr(__FILE__, __LINE__);
   /* ---- */
#endif
   /* if it is already in the list linkout the from_tni */
   if (find_tni(tlstp2, to_tni) != -1) 
    {
     linkout_tni(tlstp2, ndx);
    }
   else 
    {
     tlstp2->values[ndx] = to_tni;
     qsort(tlstp2->values, tlstp2->ndx, sizeof(int32), int_cmp);
    }
  }
}

/*
 * this version is better - but it's worse case due to the array growing
 * is alot slower
 *
static void convert_all_adjregs(int32 *regs, int32 num_regs, int32 from_tni, 
 int32 to_tni)
{
 int32 tni, i, ndx;
 struct tn_list_t *tlstp, *tlstp2;
 struct tn_t *tnp, *tnp2;

 if ((tlstp = __tn_coal_into[to_tni]) == NULL)
  {
   tlstp = alloc_tn_list(10);
   __tn_coal_into[to_tni] = tlstp;
  }
 add_tn_to_list_nodup(tlstp, from_tni); 

 tnp = &(__tntab[from_tni]);
 tlstp2 = __tn_coal_into[from_tni];
 if (tlstp2 != NULL)
  {
   for (i = 0; i < tlstp2->ndx; i++)
    {
     tni = tlstp2->values[i];
     tnp2 = &(__tntab[tni]);
     tnp2->tn_coalesce_into = to_tni;
     add_tn_to_list_nodup(tlstp, tni); 
    }
   tlstp2->ndx = 0;
  }
//SAME CODE
}
*/

/*
 * do a binary seach the sorted tlstp list for value 'val'
 * will return -1 if value in not found
 */
static int32 find_tni(struct tn_list_t *tlstp, int32 val)
{
 int32 l, h, aval, m;
 int32 *intp;

 if (tlstp->ndx == 0) return(-1);

 l = 0; h = tlstp->ndx - 1;
 intp = tlstp->values;
 for (;;)
  {
   m = (l + h)/2;
   aval = intp[m];
   if (aval == val) return(m);
   if (aval < val) l = m + 1; else h = m - 1;
   if (h < l) break;
  }
 return(-1);
}
          
/*
 * linkout out item in tlstp->values[ndx] - decrease the size by 1
 */
static void linkout_tni(struct tn_list_t *tlstp, int32 ndx)
{
 int32 byte_size;
 int32 *res;

 /* if last one just shrink by one and return */
 if ((tlstp->ndx-1) == ndx) 
  {
   tlstp->ndx--;
   return;
  }

 if (tlstp->ndx >= __work_array_size)
  {
   grow_work_array(tlstp->ndx);
  }

 res = __work_array;
 /* linkout first one */
 if (ndx == 0)
  {
   byte_size = (tlstp->ndx-1)*INTBYTES;
   memcpy(res, &(tlstp->values[1]), byte_size);
   tlstp->ndx--;
   byte_size = tlstp->ndx*INTBYTES;
   memcpy(tlstp->values, res, byte_size);
   return;
  }
//AIV LOOKATME - probably more efficient to just do a loop skipping the linkout
//index ????????

 /* linkout in the middle */
 byte_size = ndx*INTBYTES;
 memcpy(res, tlstp->values, byte_size);

 byte_size = ((tlstp->ndx - ndx) -1)*INTBYTES;
 memcpy(&(res[ndx]), &(tlstp->values[ndx+1]), byte_size);

 tlstp->ndx--;
 byte_size = tlstp->ndx*INTBYTES;
 memcpy(tlstp->values, res, byte_size);
}

/*
 * compare ints for sorting in qsort
 */
static int32 int_cmp(const void *c1, const void *c2)
{
 int32 i1, i2;

 i1 = (*(int32 *) c1);
 i2 = (*(int32 *) c2);

 /* AIV 02/12/09 - this should have been - not > - wrong for OSX */
 return(i1 - i2);
}

/*
 * initialize the tn_spilled & tn_assigned flags for all tmps
 * used in the flow graph
 * also mark all tmps used in non long insn in an entire flow graph
 */
static void init_tmp_flags(struct flowg_t *fgp,
 struct avlnode_t **tn_ref_avltab, int32 tn_refs)
{
 struct insn_t *ip;
 struct bblk_t *bbp;
 struct tn_dup_t *tndup;
 struct tn_t *tnp;
 int32 tni, i;
 
 for (i = 0; i < tn_refs; i++)
  {
   tndup = (struct tn_dup_t *) tn_ref_avltab[i]->valp;
   tni = tndup->tni; 
   tnp = &(__tntab[tni]);
   /* SJM 10/25/06 - only reset first time seen in this flow graph */
   tnp->tn_spilled = FALSE;
   tnp->tn_spill_fold = FALSE;
   tnp->tn_assigned = FALSE;
   /* AIV 04/26/07 - no children should be seen in by here */
   /* DBG remove -- */
   if (tnp->tag_parent_tni != -1) __misc_terr(__FILE__, __LINE__);
   /* ---- */

   if (tnp->tn_used_wide || (tnp->srtyp == SR_SVEC && tnp->svec_adr_add)) 
    {
     __tntab[tni].tn_spilled = TRUE; 
    }
  }
 for (bbp = fgp->fg_bblks; bbp != NULL; bbp = bbp->bbnxt)
  {
   for (ip = bbp->ihd; ip != NULL; ip = ip->inxt)
    {  
     mark_nonl_insn_and_wide_tns(ip);
    }
  }
}
     
/*
 * mark tmps that are used in insn which use non long (byte/half) operands
 */
static void mark_nonl_insn_and_wide_tns(struct insn_t *ip)
{
 int32 src_tni, dst_tni;
 struct insn_info_t *iip;

 iip = __to_iinfo_rec(ip->opcod);
 src_tni = ip->isrc.am_tni;
 dst_tni = ip->idst.am_tni;

 if (iip->rdwr_siz == SIZ_D || iip->rdwr_siz == SIZ_L
  || iip->rdwr_siz == SIZ_NONE) return;

 /* AIV 08/03/10 - added MOVL sizes for 64-bit movl 4-byte copies */
#ifdef __CVC32__
 if (iip->rdwr_siz == SIZ_BL || iip->rdwr_siz == SIZ_WL)
#else
 if (iip->rdwr_siz == SIZ_BL || iip->rdwr_siz == SIZ_WL || 
     iip->rdwr_siz == SIZ_QL)
#endif
  {
   if (!is_tn_general_reg(src_tni)) return;
   __tntab[src_tni].t_used_in_bw_insn = TRUE;
   return;
  }
#ifdef __CVC32__
 if (iip->rdwr_siz == SIZ_B || iip->rdwr_siz == SIZ_W)
#else
 if (iip->rdwr_siz == SIZ_B || iip->rdwr_siz == SIZ_W || 
     iip->rdwr_siz == SIZ_LL)
#endif
  {
   if (is_tn_general_reg(src_tni)) 
    {
     __tntab[src_tni].t_used_in_bw_insn = TRUE;
    }
  }
 if (is_tn_general_reg(dst_tni)) 
  {
   __tntab[dst_tni].t_used_in_bw_insn = TRUE;
  }
}

/*
 * try to assign the overflow reg to spilled regs
 * if no adjacent reg is also spilled can use overflow reg (ecx) 
 */
static int32 try_to_assign_overflow_reg(struct flowg_t *fgp, int32 *regs, 
 int32 num_regs)
{
 int32 i, j, ti, ti2, assign_overflow, num_using_over;
 struct tn_t *tnp;
 struct tn_list_t *tlstp;

 num_using_over = 0;
 for (i = 0; i < num_regs; i++)
  {
   ti = regs[i];
   tnp = &(__tntab[ti]);
   /* if used across call then cannot use current overflow reg ecx */
   if (tnp->t_used_cross_call)
    {
     spill_tmp(tnp, fgp, 1, regs, ti, i);
     continue;
    }
   /* DBG remove -- */
   if (!tnp->tn_spilled) __misc_terr(__FILE__, __LINE__);
   /* ----- */

   assign_overflow = TRUE;
   /* AIV 01/12/09 - could be using the two pass reg alloc */
   if (__do_safe_coal) tlstp = tnp->tn_adj_lst;
   else tlstp = tnp->ralloci->tn_adj_lst;

   for (j = 0; j < tlstp->ndx; j++)
    {
     ti2 = tlstp->values[j];
     /* if tmp adj tmp is spill cannot assign reg */
     if (__tntab[ti2].tn_spilled || __tntab[ti2].x86_regno == OFLW_REG)
      {
       assign_overflow = FALSE;
       break;
      }
    }
   /* if cannot assign to overflow reg spill it */
   if (!assign_overflow)
    {
     spill_tmp(tnp, fgp, 1, regs, ti, i);
    }
   else
    {
     /* unspill and assign overflow reg */
     tnp->tn_spilled = FALSE;
     tnp->tn_spill_fold = FALSE;
     tnp->tn_assigned = TRUE;
     tnp->x86_regno = OFLW_REG;
     num_using_over++;
     if (__opt_debug_flg)
      {
       __my_fprintf(stdout, "TMP USING OVERFLOW REG %d =>%s\n",
          regs[i], __regs[OFLW_REG]);
      }
    }
  }
 return(num_using_over);
}

/*
 * spill one reg - set overflow area
 */
static void spill_tmp(struct tn_t *tnp, struct flowg_t *fgp, int32 wlen,
 int32 *regs, int32 ti, int32 ndx)
{
 int32 spill_wrd_beg;
 int32 count, i, j, use_reg, adj_reg, is_adj;
 struct tn_list_t *use_tlstp, *ti_tlstp;
 struct tn_t *rtnp;

 fgp->has_overflow = TRUE;
 tnp->tn_spilled = TRUE;

 /* AIV 10/01/10 - if optimize reg alloc try to reuse previous spilled area */
 if (__opt_reg_alloc)
  {
   /* only seach up to the current index */
   for (i = 0; i < ndx; i++)
    {
     use_reg = regs[i];
     if (use_reg == ti) continue; 
     rtnp = &(__tntab[use_reg]);
     /* if not spilled or already folded continue */
     if (!rtnp->tn_spilled) continue;
     if (rtnp->tn_spill_fold) continue;

     /* make sure no adjacent reg is assigned the avail reg */
     if (__do_safe_coal) use_tlstp = rtnp->tn_adj_lst;
     else use_tlstp = rtnp->ralloci->tn_adj_lst;


     count = use_tlstp->ndx;
     is_adj = FALSE;
     /* if not an adjacent reg can use the same stack offset */
     /* looked into use find_tni - then sorting below - but was slower */
     for (j = 0; j < count; j++)
      {
       adj_reg = use_tlstp->values[j];
       if (adj_reg == ti) 
        {
         is_adj = TRUE;
         break;
        }
      }
     /* use previous overflow area and add adjacent regs to the adj list */
     /* of previous spilled tmp */
     if (!is_adj)
      {
       if (__do_safe_coal) ti_tlstp = tnp->tn_adj_lst;
       else ti_tlstp = tnp->ralloci->tn_adj_lst;
       tnp->tn_spill_fold = TRUE;
       set_union(use_tlstp, ti_tlstp);
       tnp->spill_ebp_byt_ofs = rtnp->spill_ebp_byt_ofs;
       return;
      }
    }
  }
 spill_wrd_beg = get_spill_wrd_ofs(fgp, wlen);
//AIV64 FIXME - why was this changed in 64-bit static cannot be right
 //tnp->spill_ebp_byt_ofs = INTBYTES*spill_wrd_beg;
 ////////////////////////////////////////////////
 tnp->spill_ebp_byt_ofs = WRDBYTES*spill_wrd_beg;
}

/*
 * AIV WRITME - currently doesn't reuse storage area
 */
static int32 get_spill_wrd_ofs(struct flowg_t *fgp, int32 spill_wlen) 
{
 int32 spill_wrd_beg;

 spill_wrd_beg = fgp->ebp_wrd_area_siz;
 fgp->ebp_wrd_area_siz += spill_wlen;
 return(spill_wrd_beg);
}

/*
 * try to assign a tmp register to an actual x86 register from the 'registers'
 * array
 * if the register doesn't have an adjacent register that has that register
 * assigned to it - it can be assigned
 */
static int32 assign_x86_reg_set(struct flowg_t *fgp, struct tn_t *tnp,
 int32 *registers, int32 avail_regs, int32 regno)
{
 int32 i, j, reg, adj_reg, count;
 int32 avail_registers[HIGH_GEN_REG];
 struct tn_list_t *tlstp;

 /* DBG remove -- */
 if (avail_regs > HIGH_GEN_REG) __misc_terr(__FILE__, __LINE__);
 /* ----- */

 /* AIV 01/12/09 - could be using the two pass reg alloc */
 if (__do_safe_coal) tlstp = tnp->tn_adj_lst;
 else tlstp = tnp->ralloci->tn_adj_lst;

 /* no adjacent registers just assign the first reg */
 if (tlstp->ndx == 0) 
  {
   tnp->x86_regno = registers[0];
   tnp->tn_assigned = TRUE;
   /* this can only be one register but check in case order changes */
   if (tnp->x86_regno == AR_BX) fgp->uses_ebx = TRUE;
   else if (tnp->x86_regno == AR_BP) fgp->uses_ebp = TRUE;
#ifdef __CVC32__
   else if (tnp->x86_regno == EDI) fgp->uses_edi = TRUE;
   else if (tnp->x86_regno == ESI) fgp->uses_esi = TRUE;
#else
   else if (tnp->x86_regno == R12) fgp->uses_r12 = TRUE;
   else if (tnp->x86_regno == R13) fgp->uses_r13 = TRUE;
   else if (tnp->x86_regno == R14) fgp->uses_r14 = TRUE;
   else if (tnp->x86_regno == R15) fgp->uses_r15 = TRUE;
#endif
   return(TRUE);
  }
 else
  {
   /* mark are regs as available */
   for (i = 0; i < avail_regs; i++) avail_registers[i] = TRUE;

   count = tlstp->ndx;
   /* make sure no adjacent reg is assigned the avail reg */
   for (i = 0; i < count; i++)
    {
     adj_reg = tlstp->values[i];
     reg = __tntab[adj_reg].x86_regno;
     /* AIV 02/19/09 - special case of try to assign variable shift */
     /* to register ecx */
     if (avail_regs == 1 && adj_reg == AR_CX) continue;
     /* AIV 01/12/09 - this has checking for != -1 - which was wrong */
     /* should be checking against REG_NONE */
     if (reg != REG_NONE) 
      {
       if (reg > HIGH_GEN_REG) __misc_terr(__FILE__, __LINE__);
       for (j = 0; j < avail_regs; j++)
        {
         /* reg is not available */
         if (reg == registers[j])
          {
           avail_registers[j] = FALSE;
           break;
          }
        }
      }
    }
   /* get the first available reg */
   for (reg = 0; reg < avail_regs; reg++) 
    {
     if (avail_registers[reg]) break;
    }
   /* overflow case */
   if (reg == avail_regs)
    {
     if (__opt_debug_flg) __my_fprintf(stdout, "REG OVERFLOW %d\n", regno);
     return(FALSE);
    }
   else 
    {
     if (__opt_debug_flg)
      {
       __my_fprintf(stdout, "REG TMP %d =>%s\n", regno, __regs[registers[reg]]);
      }
     /* assign available reg */
     tnp->x86_regno = registers[reg];
     tnp->tn_assigned = TRUE;
     if (tnp->x86_regno == AR_BX) fgp->uses_ebx = TRUE;
     else if (tnp->x86_regno == AR_BP) fgp->uses_ebp = TRUE;
#ifdef __CVC32__
     else if (tnp->x86_regno == EDI) fgp->uses_edi = TRUE;
     else if (tnp->x86_regno == ESI) fgp->uses_esi = TRUE;
#else
     else if (tnp->x86_regno == R12) fgp->uses_r12 = TRUE;
     else if (tnp->x86_regno == R13) fgp->uses_r13 = TRUE;
     else if (tnp->x86_regno == R14) fgp->uses_r14 = TRUE;
     else if (tnp->x86_regno == R15) fgp->uses_r15 = TRUE;
#endif
     return(TRUE);
    }
  }
 return(FALSE);
}

static void add_conflict_edge(int32 t1, int32 t2)
{
/* AIV CONFLICT
 __reg_conflict_graph[t1][r2] = TRUE;
 __reg_conflict_graph[r2][t1] = TRUE;
*/
 add_tn_to_list(t1, t2);
 add_tn_to_list(t2, t1);
}

static int32 is_move_insn(int32 opcod)
{
 struct insn_info_t *iip;

 iip = __to_iinfo_rec(opcod);
 if (iip->iclass == ICLASS_MOV || iip->iclass == ICLASS_STORE) return(TRUE);
 return(FALSE);
}

/*
 * combine two sets of lists
 * dst = r1 U r2
 */
static void set_union(struct tn_list_t *t1, struct tn_list_t *t2)
{
 int32 i, j, val, nsize, osize, ndx, t1ndx, t2ndx, num_remain;
 int32 *t1a, *t2a;
 int32 *res;

 /* if t1 empty copy t2 */
 if (t2->ndx == 0)
  {
   return;
  }

 /* if t2 empty copy t1 */
 if (t1->ndx == 0)
  {
   copy_tn_list(t1, t2);
   return;
  }

 ndx = 0;
 t1a = t1->values;
 t2a = t2->values;
 t1ndx = t1->ndx;
 t2ndx = t2->ndx;

 /* if sum of both sets is larger than both need to grow work array */
 /* must assume that the set elements share no common element */
 if (t1ndx + t2ndx >= __work_array_size)
  {
   grow_work_array(t1ndx + t2ndx);
  }

 res = __work_array;
 for (j = i = 0; i < t1ndx; i++)
  {
   val = t1a[i];
   for (; val > t2a[j]; )
    {
     res[ndx++] = t2a[j];
     if (++j == t2ndx) goto t2_empty;
    }
   if (t2a[j] != val) res[ndx++] = val;
  }
 
 if (j < t2ndx) 
  {
   num_remain = t2ndx - j;
   memcpy(&(res[ndx]), &(t2a[j]), num_remain*sizeof(int32));
   ndx += num_remain;
  }
 /* AIV LOOKATME - think it is faster to do memcpy
 for (; j < t2ndx; j++)
  {
   res[ndx++] = t2a[j];
  }
 */
goto done;

t2_empty:
 if (i < t1ndx) 
  {
   num_remain = t1ndx - i;
   memcpy(&(res[ndx]), &(t1a[i]), num_remain*sizeof(int32));
   ndx += num_remain;
  }

 /* AIV LOOKATME - think it is faster to do memcpy
 for (; i < t1ndx; i++)
  {
   res[ndx++] = t1a[i];
  }
 */

done:

 /* grow it if needed */
 if (ndx > t1->size)
  {
   osize = t1->size*sizeof(int32);
   nsize = 2*osize;
   if (nsize < ndx)
    {
     nsize = ndx;
    }
   t1->values = (int32 *) __my_realloc(t1->values, osize, nsize*sizeof(int32));
   t1->size = nsize;
  }
 memcpy(t1->values, res, sizeof(int32)*ndx);
 t1->ndx = ndx;
}
   
/*
 * grow the work int array
 */
static void grow_work_array(int32 need_size)
{
 
 __my_free(__work_array, __work_array_size*sizeof(int32));
 /* double the array if still not big enough set to needed size */
 __work_array_size *= 2;
 if (need_size > __work_array_size) 
  {
   __work_array_size = need_size + 1;
  }
 __work_array = (int32 *) __my_malloc(__work_array_size*sizeof(int32));
}

/*
 * copy the src list to the dst list
 */
static void copy_tn_list(struct tn_list_t *dst_tlstp, 
 struct tn_list_t *src_tlstp)
{
 int32 size, osize, nsize;


 /* if empty just return */
 if (src_tlstp->ndx == 0)
  {
   /* need to set the dst index to zero */
   dst_tlstp->ndx = 0;
   return;
  }

 if (dst_tlstp->size < src_tlstp->ndx) 
  {
   osize = dst_tlstp->size;
   __my_free(dst_tlstp->values, osize*sizeof(int32));
   nsize = 2*osize;
   if (nsize < src_tlstp->size)
    {
     nsize = src_tlstp->size;
    }
   dst_tlstp->size = nsize;
   nsize *= sizeof(int32);
   dst_tlstp->values = (int32 *) __my_malloc(nsize);
  }

 size = src_tlstp->ndx*sizeof(int32);
 memcpy(dst_tlstp->values, src_tlstp->values, size);
 dst_tlstp->ndx = src_tlstp->ndx;
}
     
static void init_insn_for_reg_alloc(struct insn_t *ip)
{
 /* DBG remove -- */
 /* --- */
 if (ip->optu.rap != NULL) __misc_terr(__FILE__, __LINE__);
 if (ip->opcod == I_CALL_ASLPROC || ip->opcod == I_CALL_ASLFUNC)
   __misc_terr(__FILE__, __LINE__);
 /* -- */
 ip->optu.rap = (struct reg_alloc_t *) __my_malloc(sizeof(struct reg_alloc_t));

 /* each insn can use a max of 2 regs */
 ip->optu.rap->tn_use_lst = alloc_tn_list(2);
 /* each insn can def a max of 1 reg */
 ip->optu.rap->tn_def_lst = alloc_tn_list(1);
 //AIV??? FIXME - good starting size approx???
 ip->optu.rap->tn_in_lst = alloc_tn_list(10);
 ip->optu.rap->tn_out_lst = alloc_tn_list(10);
}

/*
 * return T if tni can be in a register
 */
static int32 tmp_canbe_reg(int32 tni)
{
 struct tn_t *tnp;

 if (tni == -1) return(FALSE);

 tnp = &(__tntab[tni]);
 /* if it is going in x86 reg assign a number if it doesn't have one */
 if (tni <= HIGH_MACH_REG)
  {
   if (tnp->tn_adj_lst == NULL) tnp->tn_adj_lst = alloc_tn_list(10); 
   return(TRUE);
  }
 else if (is_tn_general_reg(tni))
  {
   if (tnp->tn_adj_lst == NULL) tnp->tn_adj_lst = alloc_tn_list(10); 
   return(TRUE);
  }
 return(FALSE);
}

/*
 * return T if tmp reg is going to be in an x86 regiseter
 */
static int32 is_tn_general_reg(int32 ti)
{
 struct tn_t *tnp;

 if (ti == -1) return(FALSE);

 tnp = &(__tntab[ti]);
 /* AIV 01/03/06 - all strength vectors currenlty cannot go in a reg */
 /* AIV FIXME - fix decompose to change strength bytes into words ????? */
 if (tnp->srtyp == SR_SVEC && tnp->svec_adr_add) return(FALSE);
 if (ti <= HIGH_X86_REG) return(FALSE);
 if (tnp->tn_used_wide) return(FALSE); 
 if (__is_constant(ti)) return(FALSE);
 if (tnp->comlab_typ != COMLAB_NONE) return(FALSE);
 return(TRUE);
}

/*
 * alloc a register value list
 */
static struct tn_list_t *alloc_tn_list(int32 val_size)
{
 struct tn_list_t *tlstp;

 tlstp = (struct tn_list_t *) __my_malloc(sizeof(struct tn_list_t));
 tlstp->size = val_size;
 tlstp->ndx = 0;
 tlstp->values = (int32 *) __my_malloc(val_size*sizeof(int32));
 return(tlstp);
}

/*
 * return T if insn writes to the destination
 */
static int32 amode_dst_is_def(struct insn_t *ip)
{
 struct insn_info_t *iip;

//AIV LOOKATME - more cases????????  
 if (ip->idst.amode != AM_REG) return(FALSE); 
 iip = __to_iinfo_rec(ip->opcod);
 if (iip->iclass == ICLASS_BIN || iip->iclass == ICLASS_STORE 
  || iip->iclass == ICLASS_MOV || iip->iclass == ICLASS_SHFT)
  {
   return(TRUE);
  }
 return(FALSE);
}

static void add_tn_to_defuse_list(struct tn_list_t *tlstp, int32 val)
{
 int32 ndx, i, j, tmp;
 int32 *ap;

 /* DBG remove -- */
 if (val == -1) __misc_terr(__FILE__, __LINE__);
 /* -------- */

 /* check for duplicates - don't add duplicates */
//AIV FIXME - why does this occur for use/def regs
 for (i = 0; i < tlstp->ndx; i++)
  {
   if (tlstp->values[i] == val) return;
  }

 /* should never grow def/use list */
 if (tlstp->ndx == tlstp->size) __misc_terr(__FILE__, __LINE__);
 /* store value and inc count */
 ndx = tlstp->ndx;
 tlstp->values[ndx] = val;
 tlstp->ndx++;
 ap = tlstp->values;
 /* since use/def list small this will do */
 for (i = 0; i < tlstp->ndx; i++)
  {
   for (j = i; j < tlstp->ndx; j++)
    {
     if (ap[i] > ap[j])
      {
       tmp = ap[i];
       ap[i] = ap[j];
       ap[j] = tmp;
      }
    }
  }
}

/*
 * add a new_val to the list if it isn't already in the list
 * if adding a new element must keep in sorted order
 *
 * AIV 01/21/07 - new version that uses set for conflict tn's
 */
static void add_tn_to_list(int32 orig_tni, int32 conflct_tni)
{
 struct tn_t *tnp;

 /* DBG remove -- */
 if (conflct_tni == -1) __misc_terr(__FILE__, __LINE__);
 /* -------- */

 /* check for duplicates - don't add duplicates */
 tnp = &(__tntab[orig_tni]);
 tryadd_conflict_tns(tnp, conflct_tni); 
 if (__avl_node_is_new) add_tn_to_list_nodup(tnp->tn_adj_lst, conflct_tni);
}

/*
 * add to simple avl tree (set) of bblk for building FUDs - no extra info
 */
static void tryadd_conflict_tns(struct tn_t *tnp, int32 conflct_tni) 
{
 if (tnp->tn_conflct_tree == NULL) tnp->tn_conflct_tree = __allocinit_avlhd();
 /* if allocated since avlhd value is just a ptr, will be set here if new */
 __find_add_conflct_tn(tnp->tn_conflct_tree, conflct_tni);
}

/* 
 * same as regular search but don't check for duplicates
 */
static void add_tn_to_list_nodup(struct tn_list_t *tlstp, int32 val)
{
 int32 osize, nsize, ndx;

 /* AIV 11/01/07 - no need to add idp reg to the adjacent list if using */
 /* esi reg alloc will never assign this reg to any tmps */
 if (val == IDP_REG) return;

 /* grow it if needed */
 if (tlstp->ndx == tlstp->size)
  {
   osize = tlstp->size*sizeof(int32);
   nsize = 2*osize;
   tlstp->values = (int32 *) __my_realloc(tlstp->values, osize, 
    nsize*sizeof(int32));
   tlstp->size = nsize;
  }
 /* store value and inc count */
 ndx = tlstp->ndx;
 tlstp->values[ndx] = val;
 tlstp->ndx++;
}

/*
 * free a register value list
 */
static void free_tmp_list(struct tn_list_t *tlstp)
{
 int32 size;

 size = tlstp->size*sizeof(int32);
 __my_free(tlstp->values, size);
 __my_free(tlstp, sizeof(struct tn_list_t));
}

/* AIV NOT USING FOR NOW BUT THIS IS HOW TO USE PUSH/POPS ACROSS CALLL
 ******************
extern void __asl_insert_caller_adj_saves(struct insn_t *ip)
{
 int32 i, tni, nd_eax_sav, nd_edx_sav, nd_ecx_sav;
 struct tn_list_t *tlstp;
 struct tn_t *tnp;

 tlstp = ip->optu.rap->tn_out_lst;
 nd_eax_sav = nd_edx_sav = nd_ecx_sav = FALSE;
 for (i = 0; i < tlstp->ndx; i++)
  {
   tni = tlstp->values[i];
   tnp = &(__tntab[tni]);
   if (!tnp->t_used_func_call)
    {
     if (tnp->x86_regno == EAX)
      {
       __insert_insn(ip, FALSE, I_PUSHL, AM_NONE, AM_REG, EAX);
       nd_eax_sav = TRUE;
       if (nd_edx_sav && nd_ecx_sav) break;
      }
    }
   if (tnp->x86_regno == EDX)
    {
     __insert_insn(ip, FALSE, I_PUSHL, AM_NONE, AM_REG, EDX);
     nd_edx_sav = TRUE;
     if (nd_eax_sav && nd_ecx_sav) break;
    }
   if (tnp->x86_regno == ECX)
    {
     __insert_insn(ip, FALSE, I_PUSHL, AM_NONE, AM_REG, ECX);
     nd_ecx_sav = TRUE;
     if (nd_edx_sav && nd_eax_sav) break;
    }
  }
 if (nd_eax_sav) __insert_insn(ip, TRUE, I_POPL, AM_NONE, AM_REG, EAX);
 if (nd_edx_sav) __insert_insn(ip, TRUE, I_POPL, AM_NONE, AM_REG, EDX);
 if (nd_ecx_sav) __insert_insn(ip, TRUE, I_POPL, AM_NONE, AM_REG, ECX);
}
*/
