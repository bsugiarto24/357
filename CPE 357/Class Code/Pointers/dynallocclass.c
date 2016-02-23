#include <stdio.h>
#include <stdlib.h>

int main() {
   double *pd;
   int i, *pi;
   
   pd = malloc(sizeof(double));
   pi = malloc(sizeof(int));
   printf("Values allocated at %u and %u\n", pd, pi);
   printf("Enter two values: ");
   scanf("%lf%d", pd, pi);
   printf("Sum is %0.2f\n", *pd + *pi);
   
   for (i = 0; i < 3; i++) {
      pd = malloc(sizeof(double));
      printf("New double at %u\n", pd);
   }
   
   printf("\nNow let's recycle memory.\n");
   for (i = 0; i < 3; i++) {
      pi = malloc(sizeof(int));
      printf("New int at %u\n", pi);
      free(pi);
   }
   
   printf("\nWTH, RAM is cheap: ");
   do {
      pi = malloc(800000000);
      printf("800M at %u.. ", pi);
   } while (pi != NULL);
	  
   return 0;
}

/* Sample run
Values allocated at 2147549784 and 2147549800
Enter two values: 1.2 3
Sum is 4.20
New double at 2147681168
New double at 2147681184
New double at 2147681200

Now let's recycle memory.
New int at 2147681216
New int at 2147681216
New int at 2147681216

WTH, RAM is cheap: 800M at 3494576136.. 800M at 2694512648.. 800M at 827129864.. 800M at 27066376.. 800M at 0..