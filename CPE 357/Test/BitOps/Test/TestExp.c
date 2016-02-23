
#include <stdio.h>
#include "LZWExp.h"
#include "BitUnpacker.h"
#include "CodeSet.h"
#include "MyLib.h"
#include "SmartAlloc.h"

void SinkFunc(void *state, char *data, int numBytes) {
   while (data && numBytes--) {
      printf(state, *data);
      data++;
   }
}

int main() {
   UInt data = 0;
   int check = 0, sp = 0;
   LZWExp *exp = malloc(sizeof(LZWExp));
   
   LZWExpInit(exp, SinkFunc, "%c");

   while (scanf("%X", &data) != EOF && check != BAD_CODE)
      check = LZWExpDecode(exp, data);
   
   if (exp->bitUnpacker.bitsLeft) 
      if (exp->bitUnpacker.curData <<
       UINT_SIZE - exp->bitUnpacker.bitsLeft)
         check = BAD_CODE;
   if (check == BAD_CODE)
      printf("Bad code\n");
   else if (LZWExpStop(exp) == NO_EOD_CODE)
      printf("Missing EOD\n");

   LZWExpDestruct(exp);
   free(exp);
   
   if (sp = report_space())
      printf("Allocated Space %d", sp);
      
   return 0;
}
