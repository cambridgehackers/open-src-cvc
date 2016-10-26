#include "svdpi.h"
#include "veriuser.h"

char byte_test(const char i)
{
 io_printf("BYTE = %d\n", i);
 return(2*i);
}

short int shortint_test(const short int i)
{
 io_printf("SHORT INT = %d\n", i);
 return(2*i);
}

int int_test(const int i)
{
 io_printf("INT = %d\n", i);
 return(2*i);
}

double real_test(const double i)
{
 io_printf("REAL = %g\n", i);
 return(2.123*i);
}

svBit bit_test(const svBit i)
{
 io_printf("BIT = %d\n", i);
 return(0);
}

long long int longint_test(const long long int i)
{
 io_printf("LONG LONG INT = %llx\n", i);
 return(0xccccccccddddddddULL);
}
