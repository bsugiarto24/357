#include <stdio.h>

int fa(int a, int b) {
   fb(b, a);
}

int fb(int c, int d) {
   return c/d;  // Faults if d == 0
}

void fc(int x) {
   int *p = (int*)3; // Bad pointer, bad!
   
   *p = x;
}

int main()
{
   int x, y;
   
   while (2 == scanf("%d %d", &x, &y))
      printf("Result: %d\n", fa(x, y));
   
   fc(x);
   return 1;
}