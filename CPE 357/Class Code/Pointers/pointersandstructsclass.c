#include <stdio.h>
#include <string.h>

#define NAME_LEN 20
#define NUM_STUDENTS 3

typedef struct {
   int id;
   char name[NAME_LEN+1];
   double gpa;
} Student;

int IsEqual(Student *sa, Student *sb) {
   return sa->id == sb->id && sa->gpa == sb->gpa
    && strcmp(sa->name, sb->name) == 0;
}

int main() {
   Student s1 = {1, "Bob", 3.0}, s2 = {4, "Sue", 3.5};
   Student students[] = { {3, "Jim", 2.5}, {4, "Sue", 3.5},
      {5, "Kim", 3.3}
   };
   Student *ps;
   
   ps = &s1;
   printf("\"%s\" has id %d and gpa %f\n", (*ps).name, ps->id, ps->gpa);
   if (IsEqual(ps, &s2))
      printf("s1 and s2 are the same.\n");

   for (ps = students; ps - students < NUM_STUDENTS; ps++)
      if (IsEqual(ps, &s2))
         printf("S2 is at index %d in students array.\n", ps - students);
}

/* Sample run
"Bob" has id 1 and gpa 3.000000
S2 is at index 1 in students array.
*/

   