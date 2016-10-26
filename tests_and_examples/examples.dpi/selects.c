#include "svdpi.h"
#include "veriuser.h"

/*
 * 2-state bit selects
 */
void bitsel_2state_test(svBitVecVal *val, int bi)
{
 svBit sb;

 sb = svGetBitselBit(val, bi);
 io_printf("2-state val[%d]=%d\n", bi, sb);
 /* now zero the bit */
 svPutBitselBit(val, bi, 0);
 /* one some bits */
 svPutBitselBit(val, 20, 1);
 svPutBitselBit(val, 35, 1);
 sb = svGetBitselBit(val, bi);
 io_printf("2-state val[%d]=%d\n", bi, sb);
}

/*
 * 4-state bit selects
 */
void bitsel_4state_test(svLogicVecVal *val, int bi)
{
 svLogic slb;

 slb = svGetBitselLogic(val, bi);
 io_printf("4-state val[%d]=%d\n", bi, slb);
 /* now zero the bit */
 svPutBitselLogic(val, bi, 0);
 /* one some bits */
 svPutBitselLogic(val, 20, 1);
 svPutBitselLogic(val, 35, 1);
 slb = svGetBitselLogic(val, bi);
 io_printf("4-state val[%d]=%d\n", bi, slb);
}

/*
 * 2-state part selects
 */
void partsel_2state_test(svBitVecVal *val, svBitVecVal *in)
{
 svBitVecVal val2;

 svGetPartselBit(val, in, 0, 16);
 val2 = 0xffffffff;
 svPutPartselBit(val, val2, 20, 8);
}

/*
 * 4-state part selects
 */
void partsel_4state_test(svLogicVecVal *val, svLogicVecVal *in)
{
 svLogicVecVal val2;

 svGetPartselLogic(val, in, 0, 16);
 val2.aval = 0xffffffff;
 val2.bval = 0x0;
 svPutPartselLogic(val, val2, 20, 8);
}
