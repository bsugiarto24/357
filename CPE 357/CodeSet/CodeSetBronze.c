typedef struct CodeEntry {
	char data;
	int size;
	struct CodeEntry *pre;
	char *temp;
} CodeEntry;


typedef struct CodeSet{
	int size;
	void *head;
}CodeSet;


/* Allocate, initialize, and return a CodeSet object, via void *
 * The CodeSet will have room for |numCodes| codes, though it will
 * initially be empty. */ 
void *CreateCodeSet(int numCodes)
{
   CodeSet *codes = calloc(sizeof(CodeSet),1);
   codes->size = numCodes;
   codes->head = calloc(numCodes, sizeof(CodeEntry));
   return codes;
}

/* Add a new 1-byte code to |codeSet|, returning its index, with
 * the first added code having index 0.  The new code's byte is
 * equal to |val|.  Assume (and assert if needed) that there
 * is room in the |codeSet| for a new code. */
int NewCode(void *codeSet, char val)
{
   int ndx = 0;
   CodeEntry *code = ((CodeSet *) codeSet)->head;
   while(code->size)
   {
	   code++;
	   ndx++;
   }
   code->data = val;
   code->size = 1;
   code->pre = NULL;
   code->temp = NULL;
   return ndx;
}



/* Create a new code by copying the existing code at index
 * |oldCode| and extending it by one zero-valued byte.  Any
 * existing code might be extended, not just the most recently
 * added one. Return the new code's index.  Assume |oldCode| 
 * is a valid index and that there is enough room for a new code. */
int ExtendCode(void *codeSet, int oldCode)
{
	int ndx = 0;
	CodeEntry *ptr = ((CodeSet *) codeSet)->head;
	
	CodeEntry *code = ((CodeSet *) codeSet)->head;
	
	//get code to copy
	while(oldCode--)
		code++;
		
	int s = code->size;
	
	//increment
	while(ptr->size)
	{
		ndx++;
		ptr++;
	}
	
	ptr->data = 0;
	ptr->pre = code;
	ptr-> size = s + 1;
	ptr->temp = NULL;

	return ndx;
}

/* Set the final byte of the code at index |code| to |suffix|.  
 * This is used to override the zero-byte added by ExtendCode. 
 * If the code in question has been returned by a GetCode call,
 * and not yet freed via FreeCode, then the changed final byte
 * will also show in the Code data that was returned from GetCode.*/
void SetSuffix(void *codeSet, int code, char suffix)
{
	
	CodeEntry *ptr = ((CodeSet *) codeSet)->head;
    while(code--)
		ptr++;
	/*char *data = ptr->data;
	
	while(*data)
		data++;*/

	ptr->data = suffix;
}



/* Return the code at index |code| */
Code GetCode(void *codeSet, int code)
{	
    	CodeEntry *c = ((CodeSet *) codeSet)->head;
	while(code--)
		c++;
	
	int s = c->size;
	int r = s;
	
	char *data = malloc(s * sizeof(char));
	c->temp = data;
	data+=((s-1)*sizeof(char));

	*data = c->data;
	while(c->pre)
	{
		c = c->pre;
		data--;
		*data = c->data;
	}
	
	char *d = data;
	printf("%d", *data);
	data++;
	s--;
	while(s--)
	{
		printf(" %d", *data);
		data++;
	}
		 	
	printf("\n");
	
	
	Code ret = {d, r};	
    	return ret;
}

/* Mark the code at index |code| as no longer needed, until a new
 * GetCode call is made for that code. */
void FreeCode(void *codeSet, int code)
{
	CodeEntry *c = ((CodeSet *) codeSet)->head;
	while(code--)
		c++;
	if(c->temp){
		free(c->temp);
		c->temp = NULL;
	}
}

/* Free all dynamic storage associated with |codeSet| */
void DestroyCodeSet(void *codeSet)
{
	CodeSet *set = (CodeSet *) codeSet;
	CodeEntry *c = set->head;
	int s = set->size;
	while(s--)
	{
		if(c->temp)
		{
			free(c->temp);
			c->temp = NULL;
		}
		c++;
	}
	
	free(set->head);
        free(codeSet);
}
