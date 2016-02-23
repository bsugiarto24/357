#include <stdio.h>
#include <stdlib.h>
#include "compute.h"

int main() {
   
   char c;
   int num, denom, err = 0;
   double ret;
   scanf(" %c", &c);

      if (c == 'd') {
         scanf(" %d %d", &num, &denom);
         if (!(err = divide(num, denom, &ret))) {
            printf("%d/%d = %0.2lf\n", num, denom, ret);
         }
      }   
      else if (c == 'l') {
         scanf(" %d", &num);
         if (!(err = logBase10(num, &ret))) {
            printf("log10(%d) = %0.2lf\n", num, ret);
         }
      }   
      else if (c == 's') {
         scanf(" %d", &num);
         if (!(err = squareRoot(num, &ret))) {
            printf("sqrt(%d) = %0.2lf\n", num, ret);
         }
      }   
      if (err) {
         fprintf(stderr, "%s", errorMessage);
      }
      else {
         fprintf(stderr, "No Error\n");
      }
   
   return 0;
}int main() {
   
   char c;
   int num, denom, err = 0;
   double ret;
   scanf(" %c", &c);

      if (c == 'd') {
         scanf(" %d %d", &num, &denom);
         if (!(err = divide(num, denom, &ret))) {
            printf("%d/%d = %0.2lf\n", num, denom, ret);
         }
      }   
      else if (c == 'l') {
         scanf(" %d", &num);
         if (!(err = logBase10(num, &ret))) {
            printf("log10(%d) = %0.2lf\n", num, ret);
         }
      }   
      else if (c == 's') {
         scanf(" %d", &num);
         if (!(err = squareRoot(num, &ret))) {
            printf("sqrt(%d) = %0.2lf\n", num, ret);
         }
      }   
      if (err) {
         fprintf(stderr, "%s", errorMessage);
      }
      else {
         fprintf(stderr, "No Error\n");
      }
   
   return 0;
}