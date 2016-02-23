#include <stdio.h>

void printArgs(int argc, char **argv) {  // or char argv[][]
   printf("First of %d args is %s. Rest are:", argc, *argv);
   while (--argc)
      printf(" %s", *++argv);
   printf("\n");
}

void printFlags(char **argv) {
   printf("Flags are: ");
   while (*++argv != NULL)
      if (*(*argv)++ == '-')
         while (**argv)
            printf("%c", *(*argv)++);
   printf("\n");
}

int main(int argc, char **argv) {
   char *arrOfPtr[3] = {"one", "two", "three"};
   
   printf("First 3 commandline args: %s %s %s\n", // Assumes there are 3
    argv[0], argv[1], argv[2]);
   printArgs(argc, argv);
   printArgs(3, arrOfPtr);
   printFlags(argv);
   
   return 0;
}

/* Sample run:
% argcargv -ab cd
First 3 commandline args: argcargv -ab cd
First of 3 args is argcargv. Rest are: -ab cd
First of 3 args is one. Rest are: two three
Flags are: ab
*/