#include "svdpi.h"
#include "veriuser.h"

void verilogtask(svLogic, svLogic, svLogic);

void ctask(void)
{
 svLogic s,s2, s3;
 io_printf("C Task\n");
 s = 1;
 s2 = 0;
 s3 = 3;
 verilogtask(s, s2, s3);
}
