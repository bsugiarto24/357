
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
   int data;
   struct Node *next; 
} Node;


void ReadList(Node **pHead) {
   int data;
   Node *nd, *temp;  // You may use temp, but don't have to.
   
  *pHead = NULL;
   do
   { 
         scanf("%d", &data);
         nd = malloc(sizeof(Node));
         nd->data = data;
         nd->next = NULL;
         if(data)
            *pHead = nd;
         pHead = &(nd->next);
         
   }while(data);
   
}


Node **GetFinalPtr(Node **head) {

	while(*head)
	{
		head = &(*head)->next;
	}
	return head;
}

void ConcatLists(Node **head1, Node **head2) {
   
	*GetFinalPtr(head1) = *head2;		
	*head2 = NULL;
}     

void PrintList(Node *head) {
   while (head) {
      printf("%d ", head->data);
	  head = head->next;
   }
   printf("\n");
}

//gold 
void ConcatLists(Node **head1, Node **head2) {
   Node *temp; // You may use this, but you don't have to.
    while(*head1)
	{
	   head1 = &(*head1)->next;
	}
	*head1 = *head2;
   	*head2 = NULL;
}	  


int main() {
   Node *head1, *head2;

   ReadList(&head1);
   ReadList(&head2);
   ConcatLists(&head1, &head2);
   PrintList(head1);
   PrintList(head2);

   return 0;
}
