
#include <stdio.h>

#define MAX 100

//AddToSort which will take in a sorted array, the index of the end of the array and the value to insert. 
//Fill in the blank such that when you insert the new value, the array is still sorted in increasing order.
void AddToSort(int *vals, int endNdx, int toInsert) {
	int *next = vals + 1, *loc = vals + endNdx, *pLoc = vals + endNdx - 1;
	while(*pLoc > toInsert && vals < loc) 
	{ 
		*loc-- = *pLoc--; 
	} 
	*loc = toInsert;
}

//insert Sort
void InsertSort(int *vals, int size) {
	int *next = vals + 1, *loc, *pLoc, *valsEnd = vals + size;
	int toInsert;

	while(--size) { 
		toInsert = *next; loc = next++; 
		while(loc>vals && toInsert <= *(loc-1)) { 
			*loc-- = *(loc-1); 
		} 
		*loc = toInsert; 
	}
}

//sorts two arrays by increasing order
void merge(int *arr, int *arr2, int *dest, int len1, int len2)
{
   while(len1 || len2)
   {
      if(len1 && (!len2 || *arr < *arr2))
      {
         *dest++ = *arr++;
         len1--;
      }
      else
      {
         *dest++ = *arr2++;
         len2--;
      } 
   }
}