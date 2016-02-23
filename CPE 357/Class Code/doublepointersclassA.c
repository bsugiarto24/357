#include <stdio.h>

void BadMakeNull(int *toNull) {
   toNull = NULL;
}

void GoodMakeNull(int **toNull) {
   *toNull = NULL;
}

int main() {
   int i = 42, *p = &i, **pp, ***ppp;
	
   pp = &p;
   printf("pp: %u p: %u\n", pp, p);
   printf("*pp: %u **pp: %d\n", *pp, **pp);

   ppp = &pp;
   printf("ppp: %u *ppp: %u **ppp: %u ***ppp: %d\n", ppp, *ppp, **ppp, ***ppp);

   BadMakeNull(p);
   printf("After BadMakeNull: %u\n", p);
   GoodMakeNull(&p);
   printf("After GoodMakeNull: %u\n", p);
}

/* Sample run:
pp: 2673796 p: 2673800
*pp: 2673800 **pp: 42
ppp: 2673792 *ppp: 2673796 **ppp: 2673800 ***ppp: 42
After BadMakeNull: 2673800
After GoodMakeNull: 0
*/