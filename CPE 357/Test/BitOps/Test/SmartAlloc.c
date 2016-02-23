/* Smartalloc.c       Copyright Clinton Staley 1991
 * 
 * Smartalloc provides an malloc version which checks for several possible
 * errors:
 *
 * 1. Failure of malloc or calloc call for any reason.
 * 2. Attempt to free memory not allocated by malloc/calloc, or already freed.
 * 3. Writing past the end or before the beginning of allocated memory.
 * 4. Failure to free memory by some point in the program.
 * 5. Use of data after it has been freed.
 * 6. Assumption that data returned by malloc is set to 0.
 *
 * Use smartalloc by including smartalloc.h in any file that calls malloc,
 * calloc or free.  Also, compile smartalloc.c along with your other .c files.
 * If you make any of errors 1-3 above, smartalloc will report the error
 * and the file/line on which it occured.  To find out if you have left
 * memory unfreed, call report_space().  If any unfreed memory is
 * outstanding, report_space will return the number of bytes of unfreed
 * memory.  If no memory is unfreed, report_space returns 0.
 * Use of freed data is "detected" by writing garbage into the freed data,
 * which will usually generate a runtime fault if the data is later used.
 *
 * All rights to this package are reserved by its author.  Duplication of
 * source or object code is permitted only with the author's permission.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PATTERN 0xA
#define MARGIN 4
#define OUT stdout

// Tracks one block of allocated memory.  Blocks are held in a list.
typedef struct Block {
   char *data;
   unsigned long space;
   struct Block *next;
} Block;

static Block *track = NULL;
static unsigned long allocated = 0;

void *smartalloc(unsigned long bytes, char *file, int line, char fill) {
   Block *temp;
   char *data;
   
   if ((temp = (Block *) malloc(sizeof(Block))) == NULL ||
    (data = malloc(bytes + 2*MARGIN)) == NULL) {
      fprintf(OUT, "Malloc failure in file %s on line %d\n", file, line);
      exit(1);
   }
   data += MARGIN;
   temp->data = data;

   memset(data, fill, bytes);
   allocated += bytes;
   memset(data-MARGIN, PATTERN, MARGIN);
   memset(data+bytes, PATTERN, MARGIN);
   temp->space = bytes;
   temp->next = track;
   track = temp;
   return data;
}

void smartfree(void *address, char *file, int line) {
   Block *temp, *to_free;
   int i;

   if (track == NULL) {
      fprintf(OUT, 
       "Attempt to free non-malloced space in file %s at line %d\n",
       file, line);
      return;
   }
   if (track->data == address) {
      to_free = track;
      track = track->next;
   } 
   else {
      for (temp = track; temp->next != NULL && temp->next->data != address;)
         temp = temp->next;
      if (temp->next == NULL) {
         fprintf(OUT, 
          "Attempt to free non-malloced space in file %s at line %d\n",
          file, line);
         return;
      }
      to_free = temp->next;
      temp->next = to_free->next;
   }
   for (i = 0; i < MARGIN; i++)
      if (to_free->data[to_free->space + i] != PATTERN ||
       to_free->data[-MARGIN + i] != PATTERN) {
         fprintf(OUT, 
          "Space freed in file %s at line %d has data written past bounds.\n",
          file, line);
         break;
      }
   memset(to_free->data, PATTERN, to_free->space);
   allocated -= to_free->space;
   free(to_free->data - MARGIN);
   free(to_free);
}

void *smartrealloc(void *address, unsigned long bytes, char *file, int line) {
   void *newData;
   Block *temp;   
   
   for (temp = track; temp != NULL && temp->data != address;)
      temp = temp->next;
      
   if (temp == NULL) {
      fprintf(OUT,
       "Attempt to realloc non-malloced space in file %s at line %d\n",
       file, line);
      return NULL;
   }
   newData = smartalloc(bytes, file, line, 0);
   
   memcpy(newData, address, temp->space); 
   smartfree(address, file, line);
   
   return newData;
}

unsigned long report_space() {
   return allocated;
}

void limit_space(unsigned long limit) {
   if (allocated > limit)
      fprintf(OUT, "Allocated space of %lu exceeds limit of %lu\n", allocated,
       limit);
}
