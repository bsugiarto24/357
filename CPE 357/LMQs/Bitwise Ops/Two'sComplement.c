#include <stdio.h>
#include <string.h>

void TwosComplement(char *in)
{

   char *start = in;
   while(*in)
   {
      if(*in == '0')
         ++*in;
      else
         --*in;
      in++;
   }

	while(--in >= start && *in == '1')
	{
		--*in;
	}
	 ++*in;
}

int main() {
   char number[100];
   
   while (EOF != scanf("%99s", number)) {
      TwosComplement(number);
      printf("%s\n", number);
   }

   return 0;
}
