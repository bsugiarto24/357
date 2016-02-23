 
#include <stdio.h>
#include <string.h>

//clones student! use strcpy for strings
void cloneStudent(Student *s1, Student *s2) {
	s2->id = s1->id; 
	s2->gpa = s1->gpa; 
	strcpy(s2->name,s1->name);
}


//compares pointers and swaps and then sorts
// One pair is "less" than another if either its val1 is less than the other's val1, or if
// val1's are tied, then if its val2 is less than the other's val2.
typedef struct {
int val1;
int val2;
} Pair;

// Takes in two Pairs and returns 1 if the first Pair is "greater" than the second Pair.else it returns 0
int compare(Pair *p1, Pair *p2)
{
   return (p1->val1 == p2->val1)? p1->val2 - p2->val2 > 0 : p1->val1 - p2->val1 > 0;
}

void swap(Pair *p1, Pair *p2)
{
    Pair temp;
    temp=*p1;
    *p1=*p2;
    *p2=temp;
}

//insert sort
void InsertSort(Pair vals[], int size) {
	Pair *next = vals + 1, *loc, *pLoc, *valsEnd = vals + size;
	while (next < valsEnd) {
		pLoc = next-1;
		loc = next++;
		while(compare(pLoc, loc) && loc >vals ) { 
			swap(pLoc--, loc--); 
		}
	}
}



//triple ints and stuff
//its the gold problem
//calloc sets stuff to 0

typedef struct {
int first;
int second;
int third;
} TripleInts;

typedef struct {
TripleInts *firstMax;
TripleInts *secondMax;
TripleInts *thirdMax;
} Stats;

//sets stats to have the max vals
void getStats(TripleInts *arr, int size, Stats *stats)
{
   TripleInts *m = stats->firstMax = (TripleInts *)calloc(1, sizeof(TripleInts));

   while(size--)
   {
      if(arr->first > m->first){
         m->first = arr->first;
      }
      if(arr->second > m->second){
         m->second = arr->second;
      }
      if(arr->third > m->third){
         m->third = arr->third;
      }
      arr++;
   }
}

//prints the max vals
printStats(Stats *stats)
{
   printf("firstMax: %d\n", stats->firstMax->first);
   printf("secondMax: %d\n", stats->firstMax->second);
   printf("thirdMax: %d\n", stats->firstMax->third);
}





