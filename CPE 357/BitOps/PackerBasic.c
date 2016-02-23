/*
 * Copyright Software Inventions 2014
 */

#include <stdio.h>
#define UINT_SIZE 32
#define CHAR_SIZE 8 

typedef unsigned char UChar;
typedef unsigned int UInt;

typedef struct {
   UInt packedData;
   int bitsUsed;
   int done;
} BitPacker;

void bpInit(BitPacker *bp)
{
   bp->bitsUsed = 0;
   bp->done = 0;
   bp->packedData = 0;
}

void bpPack(BitPacker *bp, char data)
{
	
	//printf("%d\n", bp->bitsUsed);
	bp->bitsUsed+= CHAR_SIZE;
	
	//UInt mask  = 0x0000;
	//mask |= data;
	
	bp->packedData<<=CHAR_SIZE;
	
	bp->packedData |= data;
	
	//printf("%X", mask);
	//printf("%d", bp->packedData);

	if(bp->bitsUsed == 32 || bp->done == 1)
	{
		printf("%X", bp->packedData);
		while(bp->bitsUsed < 32)
		{
			printf("00");
			bp->bitsUsed += CHAR_SIZE;
		}
		printf(" ");
		bp->bitsUsed = 0;
		bp->packedData = 0;
	}

}

int main() {
   int count;
   UChar data;
   BitPacker bp; 

   StompStack();

   bpInit(&bp);
   
   scanf("%d", &count);

   while(count--) {
      scanf(" %c", &data);
      bpPack(&bp, data);
      if (count == 1) {
         bp.done = 1;
      }   
   }   
   printf("\n");
   return 0;
}