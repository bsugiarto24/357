#include <stdio.h>
#include <stdlib.h>

void  ReadEm(int vals[], int size) {
   int i;
   
   printf("Enter %d ints: ", size);
   for (i = 0; i < size; i++)
      scanf("%d", &vals[i]);
}

void PrintEm(char *label, int vals[], int size) {
   printf(label);
   while (size--)
      printf("%d ", *vals++);   // Print w/o []
   printf("\n");
}

int main() {
   int size, *iBlk;

   printf("How many ints do you want: ");
   scanf("%d", &size);
   iBlk = malloc(size * sizeof(int));   // NOT just "size" -- TRAP
   ReadEm(iBlk, size);
   PrintEm("Values are: ", iBlk, size);
   free(iBlk);
   
   printf("Now how many do you want: ");
   scanf("%d", &size);
   iBlk = malloc(size * sizeof(int));
   PrintEm("Uninitialized malloc: ", iBlk, size);
   ReadEm(iBlk, size);
   PrintEm("Second set of values: ", iBlk, size);
   free(iBlk);
   
   iBlk = calloc(size, sizeof(int));
   PrintEm("Initialized calloc: ", iBlk, size);
   return 0;   // Didn't do the final free.... What happens?
}

/* Sample run
How many ints do you want: 6
Enter 6 ints: 12 23 34 45 56 67
Values are: 12 23 34 45 56 67
Now how many do you want: 8
Uninitialized malloc: 1507360 1507360 34 45 56 67 0 61808
Enter 8 ints: 12 23 34 45 56 67 78 89
Second set of values: 12 23 34 45 56 67 78 89
Initialized calloc: 0 0 0 0 0 0 0 0         */