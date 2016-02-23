#include <math.h>
#include "compute.h"

int err;
char *errorMessage;

int divide(int num, int denom, double *ret)
{
	if(denom == 0){
		errorMessage = "Can not divide by 0\n";
		return 1;
	}

	*ret = (double)num/denom;
	return 0;
	  

}