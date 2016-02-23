#include <stdio.h>
#include <assert.h>

int main() {
   short s1 = 30000;
   
   //this changed
   int count, step1 = 10000, step2= 71072;


   
   assert(step1 > 0 && step2 > 0);
   for (count = 0; count < 4; count++) {
      s1 += step1;
      printf("%d ", s1);
   }
   printf("\n");

   for (count = 0; count < 4; count++) {
      s1 += step2;
      printf("%d ", s1);
   }
   printf("\n");

   return 0;
}

//1out -25536 -15536 -5536 4464
//2out 10000 15536 21072 26608