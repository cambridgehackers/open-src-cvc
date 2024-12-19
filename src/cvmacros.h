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
 * various code macro definitions
 * mostly for speed in long value processing
 * notice these macros sometimes use globals and call procedures
 * that are assumed to be defined
 */
#define get_inst_mod_() ((struct mod_t *) __idp[MD_MDP])

#define get_inum_() ((int32) __idp[MD_INUM])

#define get_itp_() ((struct itree_t *) __idp[MD_ITP])


#define decl_idp_locals_ t_midat *save_idp

#define set_save_idp_(idp)\
	save_idp = __idp;\
__idp = idp;

#define set_idp_(idp)\
	__idp = idp;

#define restore_idp_()\
	__idp = save_idp;

#define set_save_idp_itp_(itp)\
	save_idp = __idp;\
__idp =  itp->it_idp;\

#define save_idp_();\
	save_idp = __idp;\

/* AIV 06/06/08 - get the time hash */
/* current algorithm just does xor of high/low does mult and mask */
/* if mask is a power of two the code for the heap is better since */
/* it is aligned */
/* #define PRIME 6151 */
/* these produces less conflicts - but worse code */
/* #define get_time_hash_(lw, hw) ((lw^hw)%PRIME)&(THASH_SIZE-1) */
/* #define get_time_hash_(lw, hw) ((lw^hw)*2654435761UL)%(PRIME) */
/* #define get_time_hash_(lw, hw) ((lw^hw))%(PRIME) */

#define get_time_hash_(lw, hw) ((lw^hw)*2654435761UL)&(THASH_SIZE-1)

/* DBG remove - */
extern void __push_itstk(struct itree_t *);
extern void __pop_itstk(void);
/* --- */

/* these make only 1 or 2 percent different in worse case now */
/* RELEASE NOLONGERUSED MAYBE ADD --
#define __push_itstk(itp) \
do { \
__itstk[++__itspi] = __inst_ptr = (itp); \
__inst_mod = __inst_ptr->itip->imsym->el.emdp; \
__inum = __inst_ptr->itinum; \
} while (0)
--- */

/* remove assign of nil to inst mod to improve speed if needed */
/* RELEASE NOLONGERUSED MAYBE ADD --
#define __pop_itstk() \
do { \
__inst_ptr = __itstk[--__itspi]; \
if (__itspi != -1) \
{ \
__inst_mod = __inst_ptr->itip->imsym->el.emdp; \
__inum = __inst_ptr->itinum; \
} \
-* else { __inst_mod = NULL; __inum = 0xffffffff; } *- \
else __inst_mod = NULL; \
} while (0)
-- */

/* DBG ??? add ---
extern void __pop_xstk(void);
 -- */

/* --- release add */
#define __pop_xstk() __xspi--
/* -- */

/* DBG ??? add --
extern struct xstk_t *__push_xstk(int32);
#define push_xstk_(xsp, blen) (xsp) = __push_xstk((blen))
--- */

/* BEWARE - a and b parts must be contiguous because often refed as only a */ 
/*--- release add --- */
#define push_xstk_(xsp, blen) \
 do { \
  if (++__xspi >= __maxxnest) __grow_xstk(); \
  (xsp) = __xstk[__xspi]; \
  if (wlen_(blen) > (xsp)->xsawlen) __chg_xstk_width((xsp), wlen_(blen)); \
  (xsp)->bp = &((xsp)->ap[wlen_(blen)]); \
  (xsp)->xslen = (blen); \
 } while (0)
/* --- */

/* DBG ??? add --
extern struct xstk_t *__eval_xpr(struct expr_t *);
--- */
/* --- release add */
#define __eval_xpr __eval2_xpr
/* --- */

/* DBG ??? add --- */
extern struct tev_t *__alloc_tev(void *, t_midat *, word64);
#define alloc_tev_(tevp, etyp, itp, absetime) \
 (tevp) = __alloc_tev((etyp), (itp), (absetime))
/*--- */

/* DBG ??? add --- */
extern struct tev_t *__alloc_cur_tev(void *, word64);
#define alloc_cur_tev_(tevp, etyp, absetime) \
 (tevp) = __alloc_cur_tev((etyp), (absetime))
/*--- */

/* -- ??? release add
#define alloc_tev_(tevpi, etyp, itp, absetime) \
 do { \
  struct tev_t *tevp__; \
  if (__tefreelsti != -1) \
   { tevpi = __tefreelsti; __tefreelsti = __tevtab[__tefreelsti].tenxti; } \
  else \
   { \
    if (++__numused_tevtab >= __size_tevtab) __grow_tevtab(); \
    tevpi = __numused_tevtab; \
   } \
  tevp__ = &(__tevtab[tevpi]); \
  memset(tevp__, 0, sizeof(struct tev_t)); \
  tevp__->tetyp = etyp; \
  tevp__->teitp = itp; \
  tevp__->etime = absetime; \
  tevp__->tenxti = -1; \
 } while (0)
-- */
#define ld_scalval_(ap, bp, scalwrd) \
 do { \
  (ap)[0] = scalwrd; \
  (bp)[0] = ((ap)[0] >> 1) & 1L; \
  (ap)[0] &= 1L; \
 } while(0)

#define ld_peri_scalval_(ap, bp, bytp) \
 do { \
  (ap)[0] = (word32) ((bytp)[inum]); \
  (bp)[0] = ((ap)[0] >> 1) & 1L; \
  (ap)[0] &= 1L; \
 } while(0)

/* LOOKATME _ notice this assumes av and bv values only occupy low bit */ 
#define st_scalval_(wp, av, bv) \
 (wp)[0] = (word32) ((av) | ((bv) << 1))

/* AIV 07/13/07 - notice prep still uses __inum - used during init values */
#define st_prep_peri_scalval_(bp, av, bv) \
 (bp)[__inum] = (byte) ((av) | ((bv) << 1))

#define st_peri_scalval_(bp, av, bv) \
 (bp)[inum] = (byte) ((av) | ((bv) << 1))

#define st2_peri_scalval_(bp, val) (bp)[inum] = (byte) (val)

#define chg_st_scalval_(wp, av, bv) \
 do { \
  word32 nval__; \
  nval__ = (av) | ((bv) << 1); \
  if (*(wp) != nval__) \
   { *(wp) = (byte) (nval__); __lhs_changed = TRUE; } \
 } while(0)

/* AIV REMOVEME - these are never used
#define chg_st_peri_scalval_(bp, av, bv) \
 do { \
  word32 nval__; \
  nval__ = (av) | ((bv) << 1); \
  if (((word32) (bp)[__inum]) != (nval__)) \
   { (bp)[__inum] = (byte) (nval__); __lhs_changed = TRUE; } \
 } while(0)

#define get_peri_stwire_addr_(sbp, np) \
 (sbp) = &((np)->nva.bp[np->nwid*__inum])
*/


/* DBG ??? add --
extern void __record_nchg(struct net_t *);
#define record_nchg_(np) __record_nchg(np)
--- */

/* SJM 08/08/03 - can't assume caller turns off chged flag any more */
/* but one record called, it must be off for dctrl processing - not needed */ 

/* recording var change macros */
/* DBG ??? release add --- */
/* SJM 09-27-08 - in interp this was wrongly also repeated in chglst proc */ 
/* SJM 09-27-08 - for dumpport dmp var now can't be used since file specific */
/* AIV 11/29/10 - need to check for toggle coverage */
#define record_nchg_(np) \
 do { \
  __lhs_changed = FALSE; \
  if (np->nchg_has_dces) \
   __wakeup_delay_ctrls(np, -1, -1); \
  if (np->ntgp != NULL) __add_togglelst_el(np); \
  if ((__idp[np->nchgaction_ofs] & NCHG_ALL_CHGED) == 0) __add_nchglst_el(np); \
  if ((__idp[np->nchgaction_ofs] & (NCHG_DMPVARNOW | NCHG_DMPVNOTCHGED)) \
   == (NCHG_DMPVARNOW | NCHG_DMPVNOTCHGED)) __add_dmpv_chglst_el(np); \
  if ((__idp[np->nchgaction_ofs] & (NCHG_DMPP_VARNOW | NCHG_DMPP_NOTCHGED)) \
   == (NCHG_DMPP_VARNOW | NCHG_DMPP_NOTCHGED)) __add_dp_chglst_el(np); \
 } while (0) 

/* --- */

/* DBG ??? add --- 
extern void __record_sel_nchg(struct net_t *, int32, int32);
#define record_sel_nchg_(np, i1, i2) __record_sel_nchg(np, i1, i2)
 --- */

/* SJM 08/08/03 - can't assume caller turns off chged flag any more */
/* but one record called, it must be off for dctrl processing - not needed */ 
/* DBG ??? release add --- */
/* AIV 11/29/10 - need to check for toggle coverage */
extern void __add_dmpv_chglst_el_sel(struct net_t *, int32);
#define record_sel_nchg_(np, i1, i2) \
 do { \
  __lhs_changed = FALSE; \
  if (np->nchg_has_dces) __wakeup_delay_ctrls(np, (i1), (i2)); \
  if (np->ntgp != NULL) __add_togglelst_el(np); \
  if ((__idp[np->nchgaction_ofs] & NCHG_ALL_CHGED) == 0) \
   __add_select_nchglst_el((np), (i1), (i2)); \
  if ((__idp[np->nchgaction_ofs] & (NCHG_DMPVARNOW | NCHG_DMPVNOTCHGED)) \
   == (NCHG_DMPVARNOW | NCHG_DMPVNOTCHGED)) \
   { \
    __add_dmpv_chglst_el_sel(np, i1); \
   } \
  if ((__idp[np->nchgaction_ofs] & (NCHG_DMPP_VARNOW | NCHG_DMPP_NOTCHGED)) \
   == (NCHG_DMPP_VARNOW | NCHG_DMPP_NOTCHGED)) __add_dp_chglst_el(np); \
 } while (0) 
/* --- */

/* conversion macros */
#define valtoch_(c) (((c) < 10) ? '0' + (c) : 'a' + (c) - 10)
/* conversion from real to int32 in Verilog is rounding away from 0 */
#define ver_rint_(x) ((int32) (((x) >= 0.0) \
  ? ((x) + 0.500000000) : ((x) - 0.500000000))) 
#define ver_rword(x) ((word32) ((x) + 0.500000000))

/* convert a 64 bit delay to no. of sim ticks */ 
#define cnv_num64to_ticks_(tickstim, inttim, mdp) \
 (tickstim) = __itoticks_tab[__des_timeprec - (mdp)->mtime_units]*(inttim)

/* value extraction macros */
#define get_packintowrd_(wp, arri, vecw) \
 (((vecw) <= 4) ? (word32) (((byte *) wp)[(arri)]) \
 : (((vecw) > 8) ? ((wp)[(arri)]) : (word32) (((hword *) wp)[(arri)])))

#define get_peri_packintowrd_(nva, inum, vecw) \
 (((vecw) <= 4) ? ((word32) (nva).bp[(inum)]) \
 : (((vecw) > 8) ? (nva).wp[(inum)] : (word32) (nva).hwp[(inum)]))

#define st_packintowrd_(wp, arri, uwrd, vecw) \
 (((vecw) <= 4) ? (((byte *) wp)[(arri)] = (byte) (uwrd)) \
 : (((vecw) > 8) ? ((wp)[(arri)] = (uwrd)) : \
 (((hword *) wp)[(arri)] = (hword) (uwrd))))

#define st_peri_packintowrd_(nva, ind, uwrd, vecw) \
 (((vecw) <= 4) ? ((nva).bp[(ind)] = (byte) (uwrd)) \
 : (((vecw) > 8) ? ((nva).wp[(ind)] = (uwrd)) : ((nva).hwp[(ind)] = (hword) (uwrd))))

/* macro for dpi since c side chunks always 32 bits */
#define wlen32_(blen) (((blen) + 31) >> 5)

#ifdef __CVC32__
/* 32-bit macros */
#define ubits_(blen) ((blen) & 0x1f)
#define wlen_(blen) (((blen) + 31) >> 5)
#define get_wofs_(bi) ((bi) >> 5)
#define get_bofs_(bi) ((bi) & 0x1f)
#else
/* 64-bit macros */
#define ubits_(blen) ((blen) & 0x3f)
#define wlen_(blen) (((blen) + 63) >> 6)
#define get_wofs_(bi) ((bi) >> 6)
#define get_bofs_(bi) ((bi) & 0x3f)
#endif

/* version of ubits that returns 32 for all used not 0 */
#define ubits2_(blen) (((blen & 0x1f) == 0) ? WBITS : (blen & 0x1f))

/* get conducting tranif state for cur. instance (for non input 3rd gate) */
/* possibilities are 1 on, 0 off, or 3 unknown */
#define get_tranif_onoff_(gp) \
  (((gp)->gstate.wp[get_wofs_(2*inum)] >> get_bofs_(2*inum)) & 3L)

/* -- unused */
/* #define cmpxlen(w1, b1, w2, b2) \ */
/*  (((w1)==(w2)) ? ((b1) - (b2)) : ((w1) - (w2))) */

/* comparison macros */
#define cvt_wrdbool_(av, bv)  \
 ((((av) & ~(bv)) != 0L) ? 1 : (((bv) != 0L) ? 3 : 0))

#define vval_is0_(wp, blen) \
 (((blen) <= WBITS) ? (*(wp) == 0L) : __wide_vval_is0((wp), (blen)))

/* comparing entire 2 wlen section - unused in both must be 0 */
#define cmp_vval_(wp1, wp2, blen) \
 memcmp((wp2), (wp1), (WRDBYTES*(wlen_(blen))))
#define cmp_wvval_(wp1, wp2, wlen) memcmp((wp2), (wp1), (WRDBYTES*wlen))

/* bit load and store macros */
#define rhsbsel_(wp, bi) ((wp)[get_wofs_(bi)] >> get_bofs_(bi)) & 1L

/* value change macros - can't assume no overlap here */
#define cp_walign_(dwp, swp, blen) \
 memmove((dwp), (swp), (int32) (WRDBYTES*(wlen_(blen)))); \
 (dwp)[wlen_(blen) - 1] &= __masktab[ubits_(blen)]

#define zero_allbits_(wp, blen) memset(((wp)), 0, \
 (int32) (WRDBYTES*(wlen_(blen))))

#define one_allbits_(wp, blen) \
 do { int32 __i; \
  for (__i = 0; __i < wlen_(blen); __i++) (wp)[__i] = ALL1W; \
  (wp)[(wlen_(blen)) - 1] &= __masktab[ubits_(blen)]; \
 } while (0)

/* macro must be passed a byte pointer */
#define set_byteval_(sbp, len, stval) \
 do { int32 __i; \
  for (__i = 0; __i < (len); __i++) (sbp)[__i] = ((byte) (stval)); \
 } while (0)

/* this macro may need to be surrounded by { } in some places */
#define set_regtox_(ap, bp, len) \
 one_allbits_((ap), len); one_allbits_((bp), len);

/* map index from source [i1:i2] to internal h:0 */
#define normalize_ndx_(ndxval, mi1, mi2) \
 (((mi1) >= (mi2)) ? (ndxval - mi2) : (mi2 - ndxval))

/* misc macros */
#define reg_fr_inhibit_(np) \
 (np->nu2.qcval[2*inum].qc_active \
 || np->nu2.qcval[2*inum + 1].qc_active)

/* i/o macros */

#define vis_white_(c) \
 ((((__pv_ctv = __pv_ctab[(c) & 0x7f]) == 1) || __pv_ctv == 3) ? TRUE : FALSE)

#define vis_nonnl_white_(c) ((__pv_ctab[(c) & 0x7f] == 1) ? TRUE : FALSE)

/* notice this does not leave line null terminated */
#define addch_(ch) \
 do { \
  if (__cur_sofs >= __exprlinelen - 1) __chg_xprline_size(1); \
  __exprline[__cur_sofs++] = (ch); \
 } while (0)

#define my_puts_(s, f) \
 do { \
   fputs((s), (f)); \
   if ((f) == stdout && __log_s != NULL) fputs((s), __log_s); \
  } while (0)

#define my_putc_(c, f) \
 do { \
   fputc((c), (f)); \
   if ((f) == stdout && __log_s != NULL) fputc((c), __log_s); \
  } while (0)

#define my_ungetc_(c, f) \
 if (f == NULL) \
 { if (c == EOF) *__visp->vichp = '\0'; else *(--__visp->vichp) = c; } \
 else ungetc(c, f)

/* must follow convention only immediately read char can be pushed back */
/* --- DBG remove --- 
#define my_ungetc_(c, f) \
  if (f == NULL) \
   { \
    if (c == EOF) \
     { \
      if (*__visp->vichp != '\0') __arg_terr(__FILE__, __LINE__); \
      *__visp->vichp = '\0'; \
     } \
    else \
     { \
      (__visp->vichp)--; \
      if (*__visp->vichp != c) __arg_terr(__FILE__, __LINE__); \
      *(__visp->vichp) = c; \
     } \
   } \
  else ungetc(c, f) \
---- */ 
