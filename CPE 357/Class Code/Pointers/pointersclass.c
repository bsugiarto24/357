#include <stdio.h>

void Double(float *arg) {
   *arg = *arg + *arg;
}

int main() {
   int i1, i2, *iPtr1, *iPtr2, *iPtr3;
   float f1, *fPtr;

   iPtr1 = &i1;
   iPtr2 = &i2;
   // Can also use %p
   printf("iPtr1 contains %d and iPtr2 contains %d\n", iPtr1, iPtr2);

   *iPtr1 = 5;
   i2 = 10;
   printf("i1 is %d and *iPtr2 is %d\n", i1, *iPtr2);

   iPtr2 = iPtr1;
   printf("iPtr2 is %d and *iPtr2 is %d\n", iPtr2, *iPtr2);
   i1 = 7;
   printf("*iPtr1 is %d and *iPtr2 is %d\n", *iPtr1, *iPtr2);

   fPtr = &f1;
   printf("Enter a value: ");
   scanf("%f", fPtr);                   // same as scanf("%f", &f1), but NO &
   printf("Double of %0.1f is: ", f1);
   Double(&f1);                         // or Double(fPtr);
   printf("%0.1f\n", f1);

   return 0;

   // Bad lines:
   // *iPtr3 = 10;    // Ptrs have a garbage address when first declared!!
                      // Forgetting this is the most common beginners bug
   // fPtr = iPtr1;   // Cannot mix pointer types.
   // iPtr1 = &10;    // Must have an "lvalue" to take address.
}

/* Sample run:
iPtr1 contains 9936   iPtr2 contains 9940
i1 is 5 and *iPtr2 is 10
iPtr2 is 9936 and *iPtr2 is 5
*iPtr1 is 7 and *iPtr2 is 7
Enter a value: 10
Double of 10.0 is: 20.0
*/