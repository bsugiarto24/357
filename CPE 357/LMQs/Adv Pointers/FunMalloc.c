#include <stdio.h>
#include <stdlib.h>

int main() {
   int *ptr = malloc(sizeof(int)*10), temp;
   const int *ptr2 = malloc(sizeof(int));  // Can't change ptr2
   
   printf("Enter two integers: ");
   scanf("%d%d", ptr+4, ptr+5);
   free(ptr);
   free(ptr2);
   temp = ptr - ptr2;
   ptr = NULL;
   
   //this line was changed                    \/                 \/
   printf("Your integers were %d %d\n", *(ptr2+temp+4), *(ptr2+temp+5));

   return 0;
}