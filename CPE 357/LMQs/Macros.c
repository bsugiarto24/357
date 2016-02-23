/******** Basic ********/

#include <stdio.h>

#define InRangeBound(n,l,u) (n)<(l)?  l:(n)>(u)?  (u):n

int main() {
   printf("%d\n", InRangeBound(10, 0, 20));
   printf("%d\n", InRangeBound(-10, 0, 10));
   printf("%d\n", InRangeBound(5 * 5, 2 > 1, 7 & 3));
   printf("%d\n", InRangeBound(1 / 1 >> 0 << 0, 2 > 1, 7 & 3));
   printf("%d\n", InRangeBound(0 || 5 ? 6 : 2, 5 ^ 2, 256 | 127));
   return 0;
   
   
   
/******** BRONZE ********/
#include <stdio.h>

#define FixMacro(m, x, y)  (m((x), (y)))

#define BadMax(x, y) x > y ? x : y
#define BadProd(x, y) x * y
#define BadSqrDist(x, y) x*x + y*y

#define GoodMax(x, y) FixMacro(BadMax, x, y)
#define GoodProd(x, y) FixMacro(BadProd, x, y)
#define GoodSqrDist(x, y) FixMacro(BadSqrDist, x, y)

int main() {
   int x, y;
   
   printf("Bad: %d %d %d\n", BadMax(2, 1) + 3, BadProd(2+3, 3+4),
    BadSqrDist(1+2, 5-1) + 1);
   printf("Good: %d %d %d\n", GoodMax(2, 1) + 3, GoodProd(2+3, 3+4),
    GoodSqrDist(1+2, 5-1) + 1);

   return 0;
}

/***************** SILVER ****************/

#include <stdio.h>

#define Swap (x,y){\
   int *__Xvar = (&x), *__Yvar = (&y);\
   int __Temp = *__Xvar ;\
\
   *__Xvar = *__Yvar;\
   *__Yvar = __Temp;\
}\

int main() {
   int vals[] = {10, 4, 20000000, 1, 10000000, 0}, i = 3, j = 1;
   
   Swap(vals[++i], vals[++j]);
   Swap(vals[i], i);
   Swap(vals[j], j);
   Swap(vals[vals[5]], vals[5]);
   Swap(vals[3], vals[vals[3]]);
   
   printf("i: %d j: %d vals:", i, j);
   for (i = 0; i < 6; i++)
      printf(" %d", vals[i]);
   printf("\n");

   return 0;
}