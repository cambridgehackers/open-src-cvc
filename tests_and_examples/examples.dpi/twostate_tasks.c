#include "svdpi.h"
#include "veriuser.h"

void byte_test(const char i, char *o)
{
 io_printf("BYTE = %d\n", i);
 *o = 2*i;
}

void shortint_test(const short int i, short int *o)
{
 io_printf("SHORT INT = %d\n", i);
 *o = 2*i;
}

void int_test(const int i, int *o)
{
 io_printf("INT = %d\n", i);
 *o = 2*i;
}

void real_test(const double i, double *o)
{
 io_printf("REAL = %g\n", i);
 *o = 2.123*i;
}

void bit_test(const svBit i, svBit *o)
{
 io_printf("BIT = %d\n", i);
 *o = 0;
}

void bit_vec_test(const svBitVecVal *i, svBitVecVal *o)
{
 io_printf("BIT VECTOR = %d\n", *i);
 *o = 2*(*i);
}

void bit_vec_wide_test(const svBitVecVal *i, svBitVecVal *o)
{
 io_printf("BIT VECTOR WIDE = %x %x %x %x\n", i[3], i[2], i[1], i[0]);
 o[3] = 0xaaaaaaaa;
 o[2] = 0xbbbbbbbb;
 o[1] = 0xcccccccc;
 o[0] = 0xdddddddd;
}
