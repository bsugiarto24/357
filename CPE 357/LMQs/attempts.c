head = cur->next;

while(cur && cur->next)
{
   next = cur->next;
   cur->next = next->next;
   next->next = cur;
   cur = cur->next;
}

return head;

head = cur->next;

temp = cur;//prev

while(cur && cur->next)
{
   next = cur->next;
   cur->next = next->next;
   next->next = cur;
   temp->next = next;
   temp = cur;
   cur = cur->next;
}

return head;

free(data[0].cp0);


free(data[2].cp0);

   temp  = data[1].v0;
   old= temp->v0;
   temp = old->v0;
   old = temp->v0;
   //free(old->cp0);
  // free(old);
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








int compare(Pair *p1, Pair *p2)
{
   if(p1->val1 == p2->val1)
      return p1->val2 - p2->val2 > 0;
   return p1->val1 - p2->val1 > 0;
}

void swap(Pair *p1, Pair *p2)
{
    Pair temp;
    temp=*p1;
    *p1=*p2;
    *p2=temp;
}


while(compare(pLoc, loc) && loc >vals )
{
   swap(pLoc--, loc--);
}

int SameId(void *a, void *b)
{
   return ((Person*)a)->id == ((Person*)b)->id;
}

fillArray(void *arr, int dim, void *val, int size)
{
   char *data = arr, *in = val;
   while(dim--)
   {
      memcpy(data+=size, in, size);
   }
}

fillArray(void *arr, int dim, void *val, int size)
{
   char *data = arr, *in = val;
   
   while(dim--)
   {
      memcpy(data, in, size);
      data+=size;
   }

}

void getStats(TripleInts *arr, int size, Stats *stats)
{
   stats->firstMax = (TripleInts *)calloc(1, sizeof(TripleInts));
   stats->secondMax = (TripleInts *)calloc(1, sizeof(TripleInts));
   stats->thirdMax = (TripleInts *)calloc(1, sizeof(TripleInts));

   while(size--)
   {
      if(arr->first >= stats->firstMax->first){
         stats->firstMax = arr;
      }
      if(arr->second >= stats->secondMax->second){
         stats->secondMax = arr;
      }
      if(arr->third >= stats->thirdMax->third){
         stats->thirdMax = arr;
      }
   }
}
printStats(Stats *stats)
{
   printf("firstMax: %d\n", stats->firstMax->first);
   printf("secondMax: %d\n", stats->secondMax->second);
   printf("thridMax: %d", stats->thirdMax->third);
}





