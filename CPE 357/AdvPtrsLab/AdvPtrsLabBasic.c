#include <stdio.h>
#define UINT_SIZE 32
#define CHAR_SIZE 8 
#define CHAR_MAX 256
#define MAX_RANDOM_COUNT 100
#define SEED 42

typedef unsigned char UChar;
typedef unsigned int UInt;

typedef struct {
   UInt packedData;
   int bitsUsed;
   int done;
} BitPacker;

// Returns a random character. 
//If called more than MAX_RANDOM_COUNT times, it returns EOF.
int RandomCode(char *code) {
   static int counter = 0;
   *code = rand() % CHAR_MAX;
   return (counter++ > MAX_RANDOM_COUNT) ? EOF : 0;
}

// ReadCode reads in a character from standard input and stores it into code. 
//If there is no more input, return EOF.
int ReadCode(char *code) {
   return scanf(" %c", code);
}

// This function will take in a UInt and print it to screen in capital hex with a comma after it.
void printHCode(UInt in)
{
	printf("%X, ", in);
}


// This function will take in a UInt and print it to screen as a unsigned decimal with a bar (|) after it.
void printDCode(UInt in)
{
	printf("%u|", in);
}


// Same at bpInit from BitPackers Lab
void bpInit(BitPacker *bp)
{
   bp->bitsUsed = 0;
   bp->done = 0;
   bp->packedData = 0;
}

// Similar to bpPack from BitPackers Lab except for its parameters and how it outputs data.  
//This version takes a function pointer for its source and another for its sink.  The source function
// takes a character pointer and returns an integer.  The sink will be a function pointer that takes in an UInt and returns nothing.
// This function will use the source to obtain a code and if the source returns EOF, don't do anything and return. 
//When packedData has all bits used, you output using the sink.

void bpPack(BitPacker *bp, int (*src)(char*), void(*sink)(UInt) )
{
	UChar code;
	
	if(src(&code) != EOF){
		//printf("code: %d", code);
		bp->bitsUsed+= CHAR_SIZE;
		bp->packedData<<=CHAR_SIZE;
		bp->packedData |= code;
               if(bp->bitsUsed == UINT_SIZE || bp->done)
		{
			sink(bp->packedData<<(UINT_SIZE - bp->bitsUsed));
			bpinit(bp);
		}
    }
		
	
}


int main() {
    
	int count;UChar data;BitPacker bp;
   srand(SEED);
   bpInit(&bp);
   scanf("%d", &count);

   while(count--) {
      if (count == 0) {
         bp.done = 1;
      }
      bpPack(&bp, ReadCode, printHCode);
   }

   printf("\n");
   bpInit(&bp);
   scanf("%d", &count);

   while(count--) {
      if (count == 0) {
         bp.done = 1;
      }
      bpPack(&bp, RandomCode, printDCode);
   }
   printf("\n");
   return 0;
}