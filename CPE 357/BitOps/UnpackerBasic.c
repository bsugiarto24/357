#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define UINT_SIZE 32
#define UINT_MASK 0xFFFFFFFF

typedef unsigned int UInt;

typedef struct {
   UInt curData;
   UInt nextData;
   int bitsLeft;
   int validNext;
} BitUnpacker;


void buInit(BitUnpacker * bu)
{
	bu->curData = 0;
	bu->nextData = 0;
	bu->bitsLeft = 0;
	bu->validNext = 0;
}

void buTakeData(BitUnpacker *bu, UInt ret)
{
	bu->nextData = ret;
	bu->validNext = 1;
}

int unpack(BitUnpacker *bp, int size, UInt *ret)
{
        if(bp->bitsLeft - size <= 0)
        {
		   if(bp->validNext)
		   {
			    int old = bp->bitsLeft;
			    //printf("bits left %d\n", bp->bitsLeft);
			    UInt left = bp->curData & UINT_MASK >> (UINT_SIZE - bp->bitsLeft);
				//printf("pre left %X\n", left);
				left<<= size - bp->bitsLeft;
				if(bp->bitsLeft ==0)
					left = 0;
				//	printf("left %x\n", left);
				bp->curData = bp->nextData;
				bp->validNext = 0;
				bp->bitsLeft = UINT_SIZE;
				//printf("mask %x\n", UINT_MASK >> (UINT_SIZE - size + old));
				//	printf("cur data %x\n", left);
				*ret  = (bp->curData >> (UINT_SIZE - size + old) & UINT_MASK >> (UINT_SIZE - size + old)) | left;
				bp->bitsLeft -= size; 
				bp->bitsLeft += old;
				return 1;
		   }
		   else
		   {
			   return 0;
		   }
		}
		if(bp->bitsLeft > 0)
		{
			/*printf("bits left %d\n", bp->bitsLeft);
			printf("cur data %x\n", bp->curData);
			printf("size %d\n", size);
			printf("mask %X\n", UINT_MASK << (UINT_SIZE - size) >> (UINT_SIZE - size));*/
			*ret  = bp->curData >> (bp->bitsLeft-size) & UINT_MASK >> (UINT_SIZE - size);
			bp->bitsLeft -= size; 
			return 1;
		}
		return 0;
}

int main() {
   BitUnpacker bu;
   int numBlocks, size, i;
   UInt ret, *temp;

   StompStack();

   scanf("%d", &numBlocks);
   temp = calloc(sizeof(UInt), numBlocks);

   for (i = 0; i < numBlocks; i++) {
      scanf(" %x", &temp[i]);
   }

   buInit(&bu);
   i = 0;

   while (scanf(" %d", &size) != EOF) {
      if (!unpack(&bu, size, &ret)) {
         if (i < numBlocks) {
            buTakeData(&bu, temp[i++]);
            unpack(&bu, size, &ret);
         }
         else {
            printf("Not enough data left.\n");
         }
      }
      printf(" %08X", ret);
   }
   printf("\n");
   free(temp);

   return 0;
}