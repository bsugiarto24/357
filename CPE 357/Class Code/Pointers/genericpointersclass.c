#include <stdio.h>
#define NAME_LEN 20

typedef struct {
   int id;
   char name[NAME_LEN+1];
   double gpa;
} Student;

typedef struct {
   int id;
   char name[NAME_LEN+1];
} Teacher;

void genZero(char *v1, int size) {
   int x;
   
   for (x = 0; x < size; x++)
      v1[x] = '\0';    // Or, equivalently, *v1++ = 0;
}

void niceGenZero(void *v1, int size) {
   char *cp = v1;
   
   while (size--)        // or while (size-- > 0)
      *cp++ = 0;         //       ((char *)v1)[size] = 0;
}

int main() {
   Student s1 = {1, "Bob", 3.0},  *ps = &s1;
   int *pi = &s1.id;
   Teacher tch = {2, "Sue"};
   
   if (ps == pi)
      printf("Same address.\n");
   if (ps + 1 == pi + 1)
      printf("Not the same!\n");

   genZero((char *)ps, sizeof(Student));  // or genZero((char *)&tch, sizeof(tch));
   printf("\"%s\" has id %d and gpa %f\n", ps->name, ps->id, ps->gpa);
   
   niceGenZero(&tch, sizeof(tch));
   printf("\"%s\" has id %d\n", tch.name, tch.id);
}

/* Sample run
Same address.
"" has id 0 and gpa 0.000000
"" has id 0
*/


   