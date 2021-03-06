#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "SmartAlloc.h"
#include "CodeSet.h"

typedef struct CodeEntry {
   char data;
   int size;
   struct CodeEntry *pre;
   char *temp;
   int gets;
}CodeEntry;

typedef struct CodeSet {
   int size;
   CodeEntry *head;
}CodeSet;

/* Allocate, initialize, and return a CodeSet object, via void *
* The CodeSet will have room for |numCodes| codes, though it will
* initially be empty. */ 
void *CreateCodeSet(int numCodes) {
   CodeSet *codes = calloc(sizeof(CodeSet), 1);
   
   codes->size = numCodes;
   codes->head = calloc(numCodes, sizeof(CodeEntry));
   return codes;
}

/* Add a new 1-byte code to |codeSet|, returning its index, with
* the first added code having index 0.  The new code's byte is
* equal to |val|.  Assume (and assert if needed) that there
* is room in the |codeSet| for a new code. */
int NewCode(void *codeSet, char val) {
   int ndx = 0;
   CodeEntry *code = ((CodeSet *) codeSet)->head;
   
   while (code->size) {
      code++;
      ndx++;
   }
   
   code->data = val;
   code->size = 1;
   code->pre = NULL;
   code->temp = NULL;
   code->gets = 0;
   
   return ndx; 
}


/* Create a new code by copying the existing code at index
* |oldCode| and extending it by one zero-valued byte.  Any
* existing code might be extended, not just the most recently
* added one. Return the new code's index.  Assume |oldCode| 
* is a valid index and that there is enough room for a new code. */
int ExtendCode(void *codeSet, int oldCode) {
   int ndx = 0;
   CodeEntry *ptr = ((CodeSet *) codeSet)->head;
   CodeEntry *code = ptr + oldCode;
   
   //increment
   while (ptr->size) {
      ndx++;
      ptr++;
   }

   ptr->data = 0;
   ptr->pre = code;
   ptr->size = code->size + 1;
   ptr->temp = NULL;
   ptr->gets = 0;
   
   return ndx;
}

/* Set the final byte of the code at index |code| to |suffix|.  
* This is used to override the zero-byte added by ExtendCode. 
* If the code in question has been returned by a GetCode call,
* and not yet freed via FreeCode, then the changed final byte
* will also show in the Code data that was returned from GetCode.*/
void SetSuffix(void *codeSet, int code, char suffix) {
   CodeEntry *ptr = ((CodeSet *) codeSet)->head + code;
   
   ptr->data = suffix;
   if (ptr->temp)
      *(ptr->temp + ptr->size - 1) = suffix;
}

/* Return the code at index |code| */
Code GetCode(void *codeSet, int code) {
   CodeEntry *entry = ((CodeSet *) codeSet)->head + code;
   int size = entry->size;
   char *data;
   Code ret = {data, size};
   
   if (entry->temp)
      data = entry->temp;
   else
      data = malloc(size * sizeof(char));

   ret.data = data;
   entry->temp = data;
   entry->gets++;
   data += ((size - 1) * sizeof(char));
   *data = entry->data;

   while (entry = entry->pre) {
      *--data = entry->data;
   }
   
   return ret;
}

/* Mark the code at index |code| as no longer needed, until a new
* GetCode call is made for that code. */
void FreeCode(void *codeSet, int code) {
   CodeEntry *entry = ((CodeSet *) codeSet)->head + code;

   if (entry->gets-- == 1 && entry->temp) {
      free(entry->temp);
      entry->temp = NULL;
   }
}

/* Free all dynamic storage associated with |codeSet| */
void DestroyCodeSet(void *codeSet) {
   CodeSet *set = (CodeSet *) codeSet;
   CodeEntry *code = set->head;
   
   while (set->size--) {
      if (code->temp) {
         free(code->temp);
         code->temp = NULL;
      }
      code++;
   }
   
   free(set->head);
   free(codeSet);
}
