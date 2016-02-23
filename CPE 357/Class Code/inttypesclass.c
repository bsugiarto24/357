#include <stdio.h> 
#include <limits.h>

int main() {
   signed char c = SCHAR_MAX;
   short s = SHRT_MAX;
   int i = INT_MAX;
   long li;

   unsigned char uc = UCHAR_MAX;
   unsigned short us = 2*s;
   unsigned int ui = 2*i;
   unsigned long uli;
   
   printf("Twice INT_MAX: %u  UINT_MAX: %u\n", ui, UINT_MAX);
   printf("Twice SHRT_MAX: %u  USHRT_MAX: %u\n", us, USHRT_MAX);

   printf("INT_MAX+1: %d UINT_MAX+1: %u INT_MIN-1: %d (0-1): %u\n",
    i+1, UINT_MAX+1, INT_MIN-1, 0U - 1);
   printf("Computed value: %d\n\n", 1000000 * 3000 / 3);
    
   scanf("%hd %hu %ld %lu", &s, &us, &li, &uli);
   printf("Chars: %d %u  Shorts: %d %u  Longs: %ld %lu\n",
    c, uc, s, us, li, uli);
    
   printf("Truncated values: %d %d\n", c = li, s = li);
    
   return 0;
}
/* Sample run:
Twice INT_MAX: 4294967294  UINT_MAX: 4294967295
Twice SHRT_MAX: 65534  USHRT_MAX: 65535
INT_MAX+1: -2147483648 UINT_MAX+1: INT_MIN-1: 2147483647 0 (0-1): 4294967295
Computed value: -431655765

12345 56789 1073750017 4294967295
Chars: 127 255  Shorts: 12345 56789  Longs: 1073750017 4294967295
Truncated values: 1 8193
*/