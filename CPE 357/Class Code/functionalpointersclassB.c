#include <stdio.h>
#define DIM 5

void PrintVals(int val, void *fmt) {
   printf(fmt, val);
}

void SumVals(int val, void *sum) {
   *(int *)sum += val;
}

void ProcessVals(void (*fp)(int, void *), void *data) {
   int i, val;
   
   for (i = 0; i < DIM; i++) {
      scanf("%d", &val);
	     fp(val, data);
   }
}

int main() {
   int i, total = 0;
   char *format = "-- %d --\n";
   
   ProcessVals(PrintVals, format);
   ProcessVals(SumVals, &total);
   printf("Total i s: %d\n", total);
}
            
/* Sample run
1 2 3 4 5
-- 1 --
-- 2 --
-- 3 --
-- 4 --
-- 5 --
10 20 30 40 50
Total is: 150
*/