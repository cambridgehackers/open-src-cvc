#include "svdpi.h"
#include "veriuser.h"

void array_test(svLogicVecVal data[31])
{
 io_printf("data[0].aval = %d\n", data[0].aval);
 io_printf("data[1].aval = %d\n", data[1].aval);
 data[0].aval = 1;
 data[0].bval = 0;
 data[1].aval = 2;
 data[1].bval = 0;
}

void wide_array_test(svLogicVecVal *data[2])
{
 svLogicVecVal *ip0, *ip1;
 svLogicVecVal *svp0, *svp1;
  
 ip0 = data[0];
 svp0 = &(ip0[0]);
 svp1 = &(ip0[1]);
 io_printf("data[0].aval[0] = %x data[1].aval[1] = %x\n", svp0->aval, svp1->aval);
 svp0->aval = 0x11111111;
 svp1->aval = 0xeeeeeeee;

 ip1 = data[1];
 svp0 = &(ip1[0]);
 svp1 = &(ip1[1]);
 io_printf("data[1].aval[0] = %x data[1].aval[1] = %x\n", svp0->aval, svp1->aval);
 svp0->aval = 0xdddddddd;
 svp1->aval = 0x22222222;
}
