#include <stdio.h>
#include "LZWExp.h"
#include "CodeSet.h"
#include "SmartAlloc.h"

#define RECYCLE_CODE 4096
#define INIT_BITS 9
#define BITLENGTH 32
#define EOD 256

void AddStartCodes(LZWExp *exp) {
    int codeCount;
    
    for (codeCount = 0; codeCount <= EOD; codeCount++)
        newCode(exp->dict, codeCount);
}

void PrintSym(LZWExp *exp, Code code) {
    setSuffix(exp->dict, exp->lastCode, *code.data);
    exp->sink(exp->sinkState, code.data, code.size);
}



void LZWExpInit(LZWExp *exp, DataSink sink, void *sinkState) {
    exp->dict = createCodeSet(RECYCLE_CODE);
    AddStartCodes(exp);
    exp->sink = sink;
    exp->sinkState = sinkState;
    exp->lastCode = EOD;
    exp->numBits = INIT_BITS;
    exp->maxCode = (1 << INIT_BITS) - 1;
    exp->leftover = 0;
    exp->bitsLeft = 0;
    exp->EODSeen = 0;
}

int LZWExpDecode(LZWExp *exp, uint bits) {
    int currentBits = BITLENGTH;
    uint bitsCode, temp;
    
    while (currentBits >= exp->numBits) {
        if (exp->maxCode < exp->lastCode)
            exp->maxCode = (1 << ++(exp->numBits)) - 1;
        
        if (currentBits == BITLENGTH && exp->bitsLeft) {
            currentBits = exp->bitsLeft - exp->numBits + BITLENGTH;
            bitsCode = exp->leftover << exp->numBits - exp->bitsLeft;
            bitsCode = bitsCode | bits >> currentBits;
            bitsCode = bitsCode & exp->maxCode;
        }
        else {
            bitsCode = bits >> currentBits - exp->numBits;
            bitsCode = bitsCode & exp->maxCode;
            currentBits = currentBits - exp->numBits;
        }
        
        if (DictCheck(exp, bitsCode))
            return BAD_CODE;
			
					int DictCheck(LZWExp *exp, uint dataCode) {
						if (exp->EODSeen)
							return dataCode ? BAD_CODE : 0;
						
						if (exp->lastCode < dataCode)
							return BAD_CODE;
						
						if (dataCode != EOD) {
							PrintSym(exp, getCode(exp->dict, dataCode));
							if (exp->lastCode < RECYCLE_CODE - 1) {
								extendCode(exp->dict, dataCode);
							}
							exp->lastCode++;
						}
						else
							exp->EODSeen = 1;
						
						return 0;
					}
        
        if (exp->lastCode == RECYCLE_CODE) {
            destroyCodeSet(exp->dict);
            exp->dict = createCodeSet(RECYCLE_CODE);
            
            exp->maxCode = (1 << INIT_BITS) - 1;
            exp->numBits = INIT_BITS;
            exp->lastCode = EOD;
        }
		
   if (exp->lastCode == RECYCLE_CODE) {
      int ndx = 0;
      destroyCodeSet(exp->dict);
      exp->dict = createCodeSet(RECYCLE_CODE);
      while (ndx <= INIT_SIZE ){
         NewCode(exp->dict, ndx);
         ndx++;
      }
      exp->maxCode = (1 << INITIAL) - 1;
      exp->numBits = INITIAL;
      exp->lastCode = INIT_SIZE;
   }
		
		
		
		
		
    }
    exp->leftover = bits;
    exp->bitsLeft = currentBits;
    
    temp = bits & exp->maxCode >> exp->numBits - exp->bitsLeft;
    if (exp->EODSeen && temp)
        return BAD_CODE;
    return 0;
}

int LZWExpStop(LZWExp *exp) {
    if (exp->EODSeen)
        return 0;
    return NO_EOD_CODE;
}

void LZWExpDestruct(LZWExp *exp) {
    destroyCodeSet(exp->dict);
}