
// Function |insert| inserts block of ints |toInsert|, having |dim2| elements, into the
// middle of block of ints |blk|, which has |dim1| elements.  The inserted block starts at 
// offset |offset|.  Data in |blk| are moved down to make room; no data is lost.  
// |insert| makes a larger block to accommodate the inserted data, and returns a pointer 
// to this larger block, which the caller is expected to use instead of |blk|.A

void * insert(int *blk, int *toInsert, int s1, int s2, int off)
{
   int *ptr = malloc((s1+s2) * sizeof(int));
   memmove(ptr, blk, off* sizeof(int));
   memmove(ptr+off, toInsert, s2* sizeof(int));
   memmove(ptr+off+s2, blk+off, (s1-off) * sizeof(int));
   return ptr;
}


//frees stuff, you only need to free mallocs (not other vars)
typedef struct {
   void *v0;
   char *cp0;
} SomeStruct;


void FreeAll(SomeStruct *data) {
	SomeStruct *temp, *old;
	
	
	free(data[0].cp0);
	free(data[2].cp0);

	temp  = data[1].v0;
	old= temp->v0;
	temp = old->v0;
	//old = temp->v0;
	free(temp->cp0);
	free(temp);

	temp  = data[1].v0;
	old= temp->v0;
	free(old->cp0);
	free(old);
	free(temp);

	temp = data[2].v0 ;
	old = temp->v0;
	free(temp);
	
	
}



