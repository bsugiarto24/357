#include "LZWExp.h"
#include "BitUnpacker.h"
#include "CodeSet.h"
#include "SmartAlloc.h"

#define INITIAL  9
#define INIT_SIZE 256

typedef struct CodeEntry {
   char data;
   int size;
   struct CodeEntry *pre;
   char *temp;
   int gets;
} CodeEntry;

typedef struct CodeSet {
   int size;
   CodeEntry *head;
} CodeSet;


void LZWExpInit(LZWExp *exp, DataSink sink, void *sinkState) {
   int ndx = 0;
   
   exp->sink = sink;
   exp->numBits = INITIAL;
   exp->sinkState = sinkState;
   exp->lastCode = INIT_SIZE;
   exp->maxCode = INIT_SIZE * 2 - 1;   
   buInit(&(exp->bitUnpacker));
   exp->EODSeen = 0; 
   exp->dict = CreateCodeSet(RECYCLE_CODE);
   
   while (ndx <= INIT_SIZE) {
      NewCode(exp->dict, ndx);
      ndx++;
   }
}


int PrintCode(LZWExp *exp, UInt unpacked) {
   Code code;
   
   if (exp->EODSeen) {
      if (exp->bitUnpacker.curData << 
       UINT_SIZE - exp->bitUnpacker.bitsLeft)
         return BAD_CODE;
      else
         return 0;
   }
   
   if (exp->lastCode < unpacked)
      return BAD_CODE;

   if (unpacked != INIT_SIZE) {
      code = GetCode(exp->dict, unpacked);
      SetSuffix(exp->dict, exp->lastCode, *code.data);
      exp->sink(exp->sinkState, code.data, code.size);
  
      ExtendCode(exp->dict, unpacked);
      exp->lastCode++;
      FreeCode(exp->dict, unpacked);
   } 
   else {
      exp->EODSeen = 1;
   }
   return 0;
}


int LZWExpDecode(LZWExp *exp, UInt bits) {
   BitUnpacker *bu = &exp->bitUnpacker;
   CodeSet *set = exp->dict;
   UInt unpacked;

   buTakeData(bu, bits); 
   while (!exp->EODSeen && unpack(bu, exp->numBits, &unpacked)) {
      if (exp->lastCode >= exp->maxCode) {
         exp->numBits++;
         exp->maxCode = (1 << exp->numBits) - 1;
      }
  
      if (PrintCode(exp, unpacked))
         return BAD_CODE;
   }
   
   if (exp->EODSeen && exp->bitUnpacker.bitsLeft) 
      if (exp->bitUnpacker.curData << 
       UINT_SIZE - exp->bitUnpacker.bitsLeft)
         return BAD_CODE;
   
   if (exp->EODSeen && exp->bitUnpacker.bitsLeft 
    == UINT_SIZE - INITIAL)
      if (scanf("%X", &unpacked) != EOF)
         return BAD_CODE;
   return 0;
}


/* Mark end of decoding.  Returns 0 if all OK, or NO_EOD
* if no terminating EOD code has been found 
*/
int LZWExpStop(LZWExp *exp) {
   if (exp->EODSeen)
      return 0;
   return NO_EOD_CODE;
}

/* Free all storage associated with LZWExp (not the sinkState, though,
* which is "owned" by the caller.  Must be called even if LZWExpInit
* returned an error.
*/
void LZWExpDestruct(LZWExp *exp) {
   DestroyCodeSet(exp->dict);
}
