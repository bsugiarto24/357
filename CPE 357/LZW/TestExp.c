#include <stdio.h>
#include "SmartAlloc.h"
#include "LZWExp.h"
#include "MyLib.h"

void PrintData(void *sinkState, char *data,int numBytes) {
    if (data)
        while (numBytes) {
            printf(sinkState, *data++);
            numBytes--;
        }
}

void main() {//1 10 11 12 13 2 3 4 5 6 7 8 9
    LZWExp *exp = malloc(sizeof(LZWExp));
    int checkCode = 0, scanCheck = 1, stopCheck, leftCheck = 0;
    uint data = 0;
    
    LZWExpInit(exp, PrintData, "%c");
    
    while (scanCheck != EOF && !checkCode) {
        scanCheck = scanf("%X", &data);
        if (scanCheck != EOF)
            checkCode = LZWExpDecode(exp, data);
        if (!scanCheck)
            checkCode = BAD_CODE;
    }
    
    if (exp->leftover & 1 << exp->bitsLeft - 1)
        leftCheck = BAD_CODE;
    stopCheck = LZWExpStop(exp);
    
    if (checkCode == BAD_CODE || leftCheck)
        printf("Bad code\n");
    else if (stopCheck == NO_EOD_CODE)
        printf("Missing EOD\n");
    
    LZWExpDestruct(exp);
    free(exp);
}