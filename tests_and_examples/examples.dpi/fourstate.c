#include "svdpi.h"
#include "veriuser.h"

void reg_test(const svLogicVecVal *i)
{
 io_printf("REG aval=%d bval=%d\n", i->aval, i->bval);
}

void reg_assign(svLogicVecVal *i)
{
 io_printf("ASSIGN REG aval=%d bval=%d\n", i->aval, i->bval);
 i->aval = 12;
}

void reg_wide(svLogicVecVal *vp)
{
 int a0, a1;
 svLogicVecVal *ip0, *ip1;

 io_printf("ASSIGNING WIDE\n");
 ip0 = &(vp[0]);
 a0 = ip0->aval;
 ip1 = &(vp[1]);
 a1 = ip1->aval;
 io_printf("a0 =%x a1 = %x\n", a0, a1);
 ip0->aval = 0xbbbbbbbb;
 ip1->aval = 0xcccccccc;
}
