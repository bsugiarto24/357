#include <stdio.h>
#define DIM 10

int IsLess(int a, int b) {
   return a < b;
}

int IsGreater(int a, int b) {
   return a > b;
}

void InsertSort(int vals[], int size, int (*rule)(int, int)) {
   int ndx, insNdx, toInsert;

   for (ndx = 1; ndx < size; ndx++) {
      toInsert = vals[insNdx = ndx];
      while (insNdx > 0 && (*rule)(toInsert, vals[insNdx-1])) {
         vals[insNdx] = vals[insNdx-1];
         insNdx--;
      }
      vals[insNdx] = toInsert;
   }
}

int main() {
   int i, vals[DIM];
   int (*fp)(int, int);
   char order;
   
   fp = IsGreater;
   printf("IsGreater's code starts at %u\n", fp);
   for (i = 0; i < DIM; i++)
      scanf("%d", &vals[i]);

   if ((*fp)(vals[0], vals[1]))
      printf("%d is greater than %d. \n", vals[0], vals[1]);

   do {
      printf("Enter <, > or q: ");
      scanf(" %c", &order);
	  if (order != 'q') {
         fp = order == '<' ? IsLess : IsGreater;
         printf("Call *fp on first two ints: %d. ", (*fp)(vals[0], vals[1]));
   
         printf("Full Sort: ");
         InsertSort(vals, DIM, fp);
         for (i = 0; i < DIM; i++)
            printf(" %d", vals[i]);
         printf("\n");
      }
   } while (order != 'q');
}
            
/* Sample run
IsGreater's code starts at 4198785
4 1 42 34 9 4 8 12 -9 6
4 is greater than 1.
Enter <, > or q: >
Call *fp on first two ints: 1. Full Sort:  42 34 12 9 8 6 4 4 1 -9
Enter <, > or q: <
Call *fp on first two ints: 0. Full Sort:  -9 1 4 4 6 8 9 12 34 42
Enter <, > or q: q */