void normal(char * str)
{
   printf("\"%s\"\n", str);
}

void upper(char* str)
{
   while(*str)
   {
      putchar(toupper(*str++));
   }
   printf("\n");	
}

void GeneralPrint(char *str, void (*f)(char *))
{
    f(str);
}

int main() {
   GeneralPrint("Hello", normal);
   GeneralPrint("Hello", upper);
   GeneralPrint("World", normal);
   GeneralPrint("World", upper);
   return 0;
}


/***************BRONZE**************/

#include <stdio.h>
#define DIM 8
int IsLess(double v1, double v2) {
   return v1 > v2;
}
int IsGreater(double v1, double v2) {
   return v1 < v2;
}
int IsAbsLess(double v1, double v2) {
   return fabs(v1)> fabs(v2);
}
// Iterate through "vals" (by incrementing vals itself for conciseness) to
// find the best value, as defined by parameter "better".  Assume "dim"
// is at least 1.  Careful definition of "better" will be essential.
double FindBest(double vals[], int dim, int ((*fp)(double,double)))
{
	double best, *end = vals + dim;
	best = *vals;
	while(++vals != end)
	{
		if(fp(best, *vals))
			best = *vals;
	}
	return best;
}

int main() {
   double vals[DIM];
   int i;
   for (i = 0; i < DIM; i++)
      scanf("%lf", vals+i);
   printf("Min value %0.3f\n", FindBest(vals, DIM, IsLess));
   printf("Max value %0.3f\n", FindBest(vals, DIM, IsGreater));
   printf("Lowest absolute value %0.3f\n", FindBest(vals, DIM, IsAbsLess));
   return 0;
}


/******************SIVLER************/
typedef struct {
   double sum;
   double avg;
   int count;
}Sum;

void aPrint(Sum *s)
{
      printf("Average is: %.02f\n", s->avg);
}

void sPrint(Sum *s)
{
      printf("Sum of Squares is: %.02f\n", s->sum);     
}

int nsum(int val, Sum *state)
{
      state->avg *=state->count;
      state->avg +=val;
      state->count++;
      state->avg/=state->count;
}

void squaresum(int val, Sum *state)
{
      state->sum += sqrt(val);
}

void ProcessInts(int numVals, int *vals, void (*fp)(int, void*), void *state, void (*printFunc)(void *))
{
	int ndx;
   for (ndx = 0; ndx < numVals; ndx++) {
      fp(vals[ndx], state);
   }   
   printFunc(state);
}

int main() {
   double total = 0;
   Sum s = {0}; //<<<this part
   int count, ndx, *vals;
   scanf("%d", &count);
   vals = malloc(sizeof(int) * count);
   for(ndx = 0; ndx < count; ndx++) {
      scanf("%d", &vals[ndx]);
   }   

   ProcessInts(count, vals, nsum,    &s    , aPrint); //<<<this part
   ProcessInts(count, vals, squaresum, &s,  sPrint);//<<<this part
   return 0;
}
