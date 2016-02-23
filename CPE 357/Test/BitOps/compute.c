#include <math.h>
#include "compute.h"

int err;
char *errorMessage;

int divide(int num, int denom, double *ret)
{

      errorMessage = "Can not divide by 0\n";
      return 1;

}