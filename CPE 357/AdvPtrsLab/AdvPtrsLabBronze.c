#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#define MAX_PER_LINE 4
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

typedef struct {
int charCount;
unsigned short checksum;
}CheckSumState;

typedef struct {
   int count;
}PrintState;

// CheckSum will take in a IntBlock and 
//add up every value it obtains mod 65535.
void CheckSum(IntBlock ib, CheckSumState *c)
{
   c->charCount+=ib.count;
   int idx;
   for(idx = 0; idx<ib.count; idx++)
       c->checksum += *(ib.data+idx) % USHRT_MAX;
   //c->checksum -= ib.count;

}   

//PrintData will print out the data with capital hex in the IntBlocks 
//but after 4 prints, it will print a newline and repeat this procedure. 

void PrintData(IntBlock ib, void *state)
{
   PrintState *pd = state;
   
   
   int idx;
   for(idx = 0; idx<ib.count; idx++)
   {
      if(pd->count >= 3){
         pd->count = 0;
         printf("%X\n", *(ib.data+idx));
      }
      else
      {
         printf("%X ", *(ib.data+idx));
         pd->count++;
      }
	}   
}

	
  





void bpInit(BitPacker *bp)
{
   bp->bitsUsed = 0;
   bp->done = 0;
   bp->packedData = 0;
}

void bpPack(BitPacker *bp, UInt data, int size, void *state, void(*sink)(IntBlock, void*))
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
	else if(bp->bitsUsed >= 32 )
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
        sink(ret,state);
}


int main() {
BitPacker bp1;
BitPacker bp2;
UInt data;
CheckSumState cksum = {0, 0};
PrintState print = {0};
int size, count, idx;

scanf("%d", &count);

bpInit(&bp1);
bpInit(&bp2);

while (count--) {
scanf("%u %d", &data, &size);

		bpPack(&bp1, data, size,&cksum,CheckSum  ); //&cksum,CheckSum
		bpPack(&bp2, data, size, &print,PrintData); //&print,PrintData


if (count == 1) {
bp1.done = 1;
bp2.done = 1;
}
}
printf("\nCheckSum is: %d\n", cksum.checksum);
printf("CharCount is: %d\n", cksum.charCount);

printf("Allocated space: %u\n", report_space());
return 0;
}
