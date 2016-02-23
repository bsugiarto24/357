#include <stdio.h>

int main() {
   int i = 0x7DBEA395;          // 0111 1101 1011 1110 1010 0011 1001 0101
   int j = 0x66F028C9;          // 0110 0110 1111 0000 0010 1000 1100 1001
   int k = 0x80000000, mask, bit1, bit2, lsbCount;
   unsigned short us = 0xB5CD;
   
   printf("i&j: %8X  i|j: %8X  i^j: %8X  ~i: %8X\n\n", i&j, i|j, i^j, ~i);
   
   printf("i&0x7F0: %08X  i|0x7F0: %08X  i&~0x7F0: %08X\n\n",
    i&0x7F0, i|0x7F0, i&~0x7F0);
    
   printf("i<<4: %08X  i>>6: %08X  k>>24: %08X  i<<32: %08X\n\n",
    i<<4, i>>6, k>>24, i<<32);
   
   us = us << 8 | us >> 8;
   printf("us swapped: %4X\n\n", us);

   printf("Enter bit to set and to clear: ");
   scanf("%d%d", &bit1, &bit2);
   printf("%08X\n\n", (i | 1 << bit1) & ~(1 << bit2));
   
   printf("Keep how many LSBs? ");
   scanf("%d", &lsbCount);
   printf("%08X\n", j & (1 << lsbCount) - 1);
}

/* Sample run:
i&j: 64B02081  i|j: 7FFEABDD  i^j: 1B4E8B5C  ~i: 82415C6A

i&0x7F0: 00000390  i|0x7F0: 7DBEA7F5  i&~0x7F0: 7DBEA005

i<<4: DBEA3950  i>>6: 01F6FA8E  k>>24: FFFFFF80  i<<32: 7DBEA395

us swapped: CDB5

Enter bit to set and to clear: 6 8
7DBEA2D5

Keep how many LSBs? 7
00000049
*/