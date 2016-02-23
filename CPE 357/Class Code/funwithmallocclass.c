#include <stdio.h>
#include <stdlib.h>

const int DIM1 = 5;
const int DIM2 = 10;

int main() {
   int i, *blk1, *blk2;
   
   blk1 = calloc(sizeof(int), DIM1);
   blk2 = calloc(sizeof(int), DIM2);

   printf("Block locations: %u %u\n", blk1, blk2);
   printf("Tag values %d %d\n", blk1[-1], blk2[-1]);

   for (i = 0; i < DIM2; i++)
      blk1[i] = i;
	  
   printf("Block2 tag: %d Block 2 content: ", blk2[-1]);
   for (i = 0; i < DIM2; i++)
      printf("%d ", blk2[i]);
   
   printf("\nFreeing block 2... ");
   free(blk2);
   printf(" ...and we're done\n");
   
   return 0;
}

/* Sample Run under Watcom C:
Block locations: 1510728 1510752
Tag values 25 49
Block2 tag: 5 Block 2 content: 6 7 8 9 0 0 0 0 0 0
The instruction at 0x0040198e referenced memory at 0x0000000f.
The memory could not be written.
Exception fielded by 0x00402980
<... deleted dump of register contents and stack ...>

Sample Run under gcc:
Block locations: 2147549776 2147549800
Tag values 27 51
Block2 tag: 5 Block 2 content: 6 7 8 9 0 0 0 0 0 0
Aborted (core dumped)
*/