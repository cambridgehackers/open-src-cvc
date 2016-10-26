#include "svdpi.h"
#include "veriuser.h"

void mult_array(svBitVecVal *ap, int size)
{
 int i;

 for (i = 0; i < size; i++)
  {
   ap[i] *= 10;
  }
}

void wide_array_test(svBitVecVal *data[2])
{
 svBitVecVal *ip0, *ip1;
 svBitVecVal *svp0, *svp1;
  
 ip0 = data[0];
 svp0 = &(ip0[0]);
 svp1 = &(ip0[1]);
 io_printf("data[0] = %x data[1] = %x\n", *svp0, *svp1);
 *svp0 = 0x11111111;
 *svp1 = 0xeeeeeeee;

 ip1 = data[1];
 svp0 = &(ip1[0]);
 svp1 = &(ip1[1]);
 io_printf("data[1] = %x data[1] = %x\n", *svp0, *svp1);
 *svp0 = 0xdddddddd;
 *svp1 = 0x22222222;
}
