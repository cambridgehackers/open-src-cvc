#include "svdpi.h"
#include "veriuser.h"

char cstr1[] = "CHANDLE STRING 1";
char cstr2[] = "CHANDLE STRING 2";

char *get_address(int i)
{
 char *cp;

 if (i == 1) cp = cstr1;
 else cp = cstr2;
 return(cp);
}

void print_str(char *str)
{
 io_printf("PASSED STRING:  %s\n", str);
}
