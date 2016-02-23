#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
   int data;
   struct Node *next; 
} Node;

void Add(int data, Node **pHead) {
   Node *rtn = malloc(sizeof(Node));
   
   rtn->data = data;
   rtn->next = *pHead;
   *pHead = rtn;
}

// Remove method.  Search for a node containing "value", and if you find it, remove
// it from the list by routing the next pointer of the prior node (pointed to by |prior|)
// around it.  Return true if a node was removed.
int Remove(int value, Node **pHead) {
   Node *prior = NULL, *temp;
   
   for (temp = *pHead; temp != NULL && temp->data != value; temp = temp->next)
      prior = temp;
      
   if (temp != NULL)
      prior->next = temp->next;
   return temp != NULL;
}

// FreeAll method in need of writing
void FreeAll(Node **pHead) {
   Node *temp;
   
   
}

int main() {
   Node *head = NULL;
   
   Add(20, &head);
   Add(30, &head);
   Add(40, &head);
   printf("Top value is %d\n", head->data);
   
   Remove(30, &head);
   Remove(5, &head);
   Remove(40, &head);
   printf("Top value is %d\n", head->data);

   FreeAll(&head);	
}
/* Sample run:
Top value is 40
Top value is 20 */
