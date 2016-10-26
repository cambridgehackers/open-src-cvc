#include "svdpi.h"
#include "veriuser.h"

void set_array_vals(double *data, int size)
{
 int i;
 
 for (i = 0; i < size; i++)
  {
   data[i] = i + 0.123456;
  }
}

double mult_real(const double d)
{
 return(2*d);
}
