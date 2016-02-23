#include <stdio.h>

// Square each element of the array pointed to by |array|.
void SquareArray(int *array, int dim)
{
   int ndx;

   for (ndx = 0; ndx < dim; ndx++)
      *(array+ndx) = *(array+ndx) *  *(array+ndx);
}

// int array[] is a synonym for int *array.  There is no array parameter!
void PrintArray(int array[], int dim) {
   int ndx;
   
   for (ndx = 0; ndx < dim; ndx++)
      printf("%d ", array[ndx]);
   printf("\n");
}

int main()
{
   int *iPtr;
   int intArr[5];

   printf("Enter 5 integers: ");
   
   iPtr = intArr;   // Same as iPtr = &intArr[0];
   
   // iPtr - intArr is the number of ints that iPtr is offset into intArr.
   while (iPtr - intArr < 5) {
      scanf("%d", iPtr);   // Once again, no &
      iPtr++;              // Advances iPtr by *one int*, not one byte
   }
   SquareArray(intArr, 5);
   PrintArray(intArr, 5);

   return 0;
}

/* Sample Run:
Enter 5 integers: 0 3 42 5 8
0 9 1764 25 64
*/