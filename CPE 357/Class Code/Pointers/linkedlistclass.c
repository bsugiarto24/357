#include <stdio.h>
#include <stdlib.h>


temp= malloc(sizeof(Node)); 
temp->data = data;

if(!head)
{
   temp->next = head;

}   
else if(head->next)
{
   temp->next = head->next;
   head->next = temp;
}
   
return temp;

//recent
temp = malloc(sizeof(Node));
temp->data = data;

if(head)
   head->next = temp;
else
   head = temp;

return head;


temp= malloc(sizeof(Node)); 
temp->data = data;

if(!head)
    head = temp;
else if( ! head->next)
    head->next = temp;
else
{
   temp->next = head->next->next;
   head->next = temp;
}   

return temp;



if(head && head ->next)
{
   temp = head->next;
   head->next = temp->next;
   free(temp);
}

typedef struct Node {
   int data;          // Could put any kind of data here
   struct Node *next; // Self-referential requires "struct"
} Node;

Node *Add(int data, Node *head) {
   Node *temp = malloc(sizeof(Node));
   
   temp->data = data;
   temp->next = head;
   return temp;
}

int IsOn(int value, Node *head) {
   Node *temp;
   
   for (temp = head; temp != NULL && temp->data != value; temp = temp->next)
      ;
   return temp != NULL;
}

Node *Remove(Node *head) {
   Node *temp = head->next;
   
   free(head);
   return temp;
}

void FreeAll(Node *head) {
   Node *temp;
   
   while (head != NULL) {
      temp = head->next;
	   free(head);
      head = temp;
   }
}

int main() {
   Node *head = NULL;
   
   head = Add(10, head);
   head = Add(20, head);
   head = Add(40, Add(30, head));
   
   printf("First value is %d and 20 %s on the list.\n", head->data, 
    IsOn(20, head) ? "is" : "is not");
	
   head = Remove(head);
   printf("First value is %d and 40 %s on the list.\n", head->data, 
    IsOn(10, head) ? "is" : "is not");

   FreeAll(head);	
}
/* Sample run:
First value is 40 and 20 is on the list.
First value is 30 and 40 is on the list.  */
