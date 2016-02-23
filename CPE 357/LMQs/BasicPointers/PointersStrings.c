 

//shifts the character and wraps around
#include <stdio.h>

#define NUM_LETTERS 26
#define MAX_MESSAGE 100
#define CAPITAL_A 'A'

void encrypt( char *message, int shift)
{
   while(*message)
   {
      *message += shift;
      if(*message >= CAPITAL_A + NUM_LETTERS)
         *message-=NUM_LETTERS;
      message++;
   }

}

//translates string
void TrStr(char *str1, char *tr)
{
   while(*str1)
   {
      int ndx = 0;
      while(*(tr+ndx) != *str1 && *(tr+ndx))
      {

         ndx+=2;
      }
      if(*(tr+ndx) == *str1)
         *str1 = *(tr+ndx+1);
      *str1++;
   }
}

int main() {
   char str1[20], str2[20], *test = "";

   TrStr(test, "abcd");
   printf("Empty translates to |%s|\n", test);

   while (EOF != scanf("%s %s", str1, str2)) {
      TrStr(str1, "");
      printf("%s -> ", str1);
      TrStr(str1, str2);
      printf("%s\n", str1);
   }
   
   return 0;
}


//removes blanks
#include <stdio.h>
void RemoveBlanks(char *s1)
{
   char *ptr = s1;
   do
   {    if(*s1 != ' ')
         *ptr++ = *s1;

   }
   while(*s1++);

}

int main() {
   char s1[] = "  ", s2[] = "", s3[] = "a (b) c  ", s4[] = " ab ",
    s5[] = " aaab  ab abbb "; 
   
   RemoveBlanks(s1);
   RemoveBlanks(s2);
   RemoveBlanks(s3);
   RemoveBlanks(s4);
   RemoveBlanks(s5);
   
   printf("|%s| |%s| |%s| |%s| |%s|\n", s1, s2, s3, s4, s5);

   return 0;
}



//lower complexity translate string
void TrStr(char *str1, char *tr)
{
   char *ndx;
   while(*str1)
   {
      ndx = tr;
      while(*ndx != *str1 && *ndx)
      {
         ndx+=2;
      }
      if(*ndx )
         *str1 = *++ndx;
      str1++;
   } 
}



