#include <stdio.h>

int main() {
   int i = 017634256034; // 01 111 110 011 100 010 101 110 000 011 100
   int j = 0x3A9BEC7D;   // 0011 1010 1001 1011 1110 1100 0111 1101
   unsigned short us;
   
   printf("i is %d or %X or %o\n", i, i, i);
   printf("j is %d or %x or %o\n", j, j, j);
   
   printf("\nOne bit masks:\n");
   for (us = 1; us != 0; us = us * 2)
      printf("0x%04x (%07o)\n", us, us);
}

/* Sample run:
i is 2121358364 or 7E715C1C or 17634256034
j is 983297149 or 3a9bec7d or 7246766175

One bit masks:
0x0001 (0000001)
0x0002 (0000002)
0x0004 (0000004)
0x0008 (0000010)
0x0010 (0000020)
0x0020 (0000040)
0x0040 (0000100)
0x0080 (0000200)
0x0100 (0000400)
0x0200 (0001000)
0x0400 (0002000)
0x0800 (0004000)
0x1000 (0010000)
0x2000 (0020000)
0x4000 (0040000)
0x8000 (0100000)  */