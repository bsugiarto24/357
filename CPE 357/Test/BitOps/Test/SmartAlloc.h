#ifndef SMARTALLOC_H
#define SMARTALLOC_H

/* Smartalloc.h       Copyright Clinton Staley 1991
 * 
 * Smartalloc provides an malloc version which checks for several possible
 * errors:
 *
 * 1. Failure of malloc or calloc call for any reason.
 * 2. Attempt to free memory not allocated by malloc, or calloc 
 *    or already freed.
 * 3. Writing past the end or before the beginning of allocated memory.
 * 4. Failure to free memory by some point in the program.
 * 5. Use of freed storage after freeing it.
 * 6. Assumption that data returned by malloc is set to 0.
 *
 * Use smartalloc by including smartalloc.h in any file that calls malloc,
 * calloc, or free.  Also, compile smartalloc.c along with your other .c files.
 * If you make any of errors 1-3 above, smartalloc will report the error
 * and the file/line on which it occured.  To find out if you have left
 * memory unfreed, call report_space().  If any unfreed memory is
 * outstanding, report_space will return the number of bytes of unfreed
 * memory.  If no memory is unfreed, report_space returns 0.  Errors 5
 * and 6 are "detected" by filling the memory block with random bit-patterns, 
 * so that runtime errors are likely to result from those two errors.
 *
 * All rights to this package are reserved by its author.  Duplication of
 * source or object code is permitted only with the author's written
 * consent.
 */

#define malloc(x)     smartalloc((x), __FILE__, __LINE__, 0x55)
#define calloc(x, y)  smartalloc((x)*(y), __FILE__, __LINE__, 0)
#define realloc(x, s) smartrealloc((x), (s), __FILE__, __LINE__) 
#define free(x)       smartfree((x), __FILE__, __LINE__)

void *smartalloc(unsigned long, char *, int, char);
void *smartrealloc(void *, unsigned long, char *, int);
void smartfree(void *, char *, int);
unsigned long report_space();
void limit_space(unsigned long limit);

#endif
