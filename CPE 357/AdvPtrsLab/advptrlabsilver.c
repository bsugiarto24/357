


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define DIM1 6
#define DIM2 8
#define NAME_LEN 20

//#define qsort NOT_ALLOWED


typedef struct Name {
char first[NAME_LEN+1];
char last[NAME_LEN+1];
} Name;

// Support functions NameLess, NameGreater, DblLess, and StrLess
int StrLess(char** a, char **b)
{
   return strcmp(*a,*b) < 0;
}

int NameLess(Name* b, Name *a)
{
	if(strcmp(a->last, b->last) ==0)
		return strcmp(a->first, b->first) > 0;
	return strcmp(a->last, b->last)  > 0;
}

int NameGreater(Name* b, Name *a)
{
	if(strcmp(a->last, b->last) == 0)
		return strcmp(b->first, a->first)  > 0;
	return strcmp(b->last, a->last)  > 0;
}

int DblLess(double * a, double *b)
{
	return *a < *b;
}


// gen sort
void GenInsertSort(void *val, int size, int dataSize,  int (*rule)(void*, void*)) {
  
   int ndx, insNdx;
   char *vals = val;
   char *toInsert = calloc(1,dataSize);

   for (ndx = dataSize; ndx < size*dataSize; ndx+=dataSize) {
      insNdx = ndx;
      memcpy(toInsert,  vals + insNdx, dataSize);
      while (insNdx > 0 && rule(toInsert, vals + insNdx  -dataSize)) 
      {
		 memcpy(vals+insNdx, vals + insNdx  -dataSize, dataSize);
		 insNdx-=dataSize;
      }

      memcpy(vals+insNdx, toInsert,  dataSize);
	 
   }
   
}


 int main() {
	
	//printf("%d", sizeof(char*));
Name names[DIM1] = {{"John", "Smith"}, {"Jane", "Smith"}, {"Bill", "Jones"},
{"Sue", "Johnson"}, {"Susan", "Johnson"}, {"Jim", "Taylor"}
};
double vals[DIM2] = {1.1, -2.2, 3.3, -4.2, 5.5, -6.6, 7.7, -8.8};
char *words[DIM2]
= {"beta", "alpha", "gamma", "delta", "epsilon", "pi", "phi", "omega"};
int i;

GenInsertSort(names, DIM1, sizeof(Name), NameLess);
for (i = 0; i < DIM1; i++)
printf("%s %s\n", names[i].first, names[i].last);

GenInsertSort(names, DIM1, sizeof(Name), NameGreater);
for (i = 0; i < DIM1; i++)
printf("%s %s\n", names[i].first, names[i].last);

GenInsertSort(vals, DIM2, sizeof(double), DblLess);
for (i = 0; i < DIM2; i++)
printf("%f ", vals[i]);
printf("\n");

GenInsertSort(words, DIM2, sizeof(char *), StrLess);
for (i = 0; i < DIM2; i++)
printf("%s ", words[i]);
printf("\n");

return 0;
}
