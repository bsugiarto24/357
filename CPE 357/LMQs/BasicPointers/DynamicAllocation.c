
// reads two doubles

#include <stdio.h>
#include "SmartAlloc.h"

void readAndPrintDoubles(double *d1, double *d2) {
d1 = malloc(sizeof(double));
d2 = malloc(sizeof(double));
scanf("%lf%lf", d1, d2);
printf("%.01f %1.01f\n", *d1, *d2);
free(d1);
free(d2);

}

int main() {
   double *d1 = NULL, *d2 = NULL;

   readAndPrintDoubles(d1, d2);

   printf("Final space: %d\n", report_space());

   return 0;
}


// read ints

scanf("%d", p2);
*p2 += total;
free(p2);

free(p1);