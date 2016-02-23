/*
 * Copyright Software Inventions 2014
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define UINT_SIZE 32

typedef unsigned int UInt;

typedef struct {
   UInt *data;
   int count;
} IntBlock;

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

IntBlock bpPack(BitPacker *bp, UInt data, int size)
{
	int s = 0;
	bp->bitsUsed += size;

	UInt *idata = malloc(sizeof(UInt)*2);
	*idata = data;
	
	if(bp->bitsUsed > UINT_SIZE && bp->done == 1)
	{
		s = 2;
		bp->bitsUsed -= UINT_SIZE;
		UInt temp = *idata;
		*idata = bp->packedData | temp >> (bp->bitsUsed);
		*(idata+1) = temp<<(UINT_SIZE - bp->bitsUsed);
	}
	else if(bp->bitsUsed >= UINT_SIZE )
	{
		s = 1;
		bp->bitsUsed -= UINT_SIZE;
		UInt temp = *idata;
		*idata = bp->packedData | temp >> (bp->bitsUsed);
		if(bp->bitsUsed ==0)
			bp->packedData = 0;
		else
			bp->packedData = temp<<(UINT_SIZE - bp->bitsUsed);
	}
	else if(bp->done == 1)
	{
		s = 1;
		*idata = bp->packedData | *idata << (UINT_SIZE - bp->bitsUsed);
	}
	else
	{	
		bp->packedData = bp->packedData | *idata << (UINT_SIZE - bp->bitsUsed);
	}
	
	IntBlock ret = {idata, s};
	return ret;
}


int main() {
   BitPacker bp;
   IntBlock iB;
   UInt data;
   int size, count, idx;

   scanf("%d", &count);

   bpInit(&bp);
   while (count--) {
      scanf("%u %d", &data, &size);
      iB = bpPack(&bp, data, size);
      for (idx = 0; idx < iB.count; idx++) {
         printf("%x ", *(iB.data + idx));
      }
      free(iB.data);
      if (count == 1) {
         bp.done = 1;
      }
   }
   printf("\n");
   printf("Allocated space left: %d\n", report_space());
   return 0;
}
