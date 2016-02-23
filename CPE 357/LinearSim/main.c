#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define BUF_SIZE 30
#define CHAR_SIZE sizeof(char)


char **CellArg(int num, ...) {
   char buffer[BUF_SIZE], **temp, **args;
   int size = strlen(buffer) + 1;
   int *input = ( &num);
   input++;

   
   int numArgs = num;

   args = temp = calloc(12, sizeof(char *));
   *temp++ = "exec";
   numArgs *= 2; 
	
   while (numArgs) {
      printf("num args: %d\n", numArgs);
      
	  if(numArgs % 2 == 0) {
	     printf("input: %c\n", *input);
         *temp = calloc(30, CHAR_SIZE);
		 **temp = 'C';
		 input++;
	  }
	  else {
	  
	     if(**temp == 'V') {
		    sprintf(buffer, "%lf", input);
	        strcpy(*temp + 1, buffer);
		    input += sizeof(double);
		 }
		 else {
		    sprintf(buffer, "%d", input);
	        strcpy((*temp) + 1, buffer);
			temp++;
		    input++;
		 }
	     
	  }
	  
	  numArgs--;
   }
   return args;
}

int main()
{
   char **args;
   char s = 'S', o = 'O';
   int a = 6, b = 4;
   args = CellArg(a, s, b, o,b, o, a,
          'I', a, 'I', b, 'D', b);
		  
   while(*args) {
      printf("%s\n", *args++);
   }
   return 0;
}
