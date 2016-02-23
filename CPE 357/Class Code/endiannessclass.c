#include <stdio.h>

int main() {
   unsigned int i = 0x12345678, byteNum;
   short s;
   char *cp = (char *)&i;
   
   for (byteNum = 0; byteNum < sizeof(int); byteNum++)
      printf("Byte %d: %X  ", byteNum, *cp++);
   
   printf("\nEnter a value (i is 0x%X): ", i);
   scanf("%d", &s);
   
   printf("You entered %d (i is 0x%X)\n", s, i);
  
   return 0;
}

/* Sample run:
Byte 0: 78  Byte 1: 56  Byte 2: 34  Byte 3: 12
Enter a value (i is 0x12345678): 42
You entered 42 (i is 0x12340000)
*/