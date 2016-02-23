#include <stdlib.h>
#include <assert.h>
#include "List.h"

struct Node {
   double data;
   struct Node *next;
};

static Node *freeList = NULL;

static Node *newNode() {
   Node *temp;
   
   if (freeList) {
      temp = freeList;
      freeList = temp->next;
   }
   else
      temp = malloc(sizeof(Node));
	  
   return temp;
}

static void freeNode(Node *toFree) {
   toFree->next = freeList;
   freeList = toFree;
}

int ListGetCount(List *list) {
   return list->count;
}

void ListCreate(List *list) {
   list->head = list->at = NULL;
   list->count = 0;
}

void ListDestroy(List *list) {
   Node *temp;
   
   while (list->head) {
      temp = list->head;
      list->head = temp->next;
      freeNode(temp);
   }
}

void ListAdd(List *list, double toAdd, ListAddType where) {
   Node *last, *temp = newNode();

   temp->data = toAdd;
   list->count++;   
   if (where == LIST_AT_START) {
      temp->next = list->head;
      list->head = temp;
   }
   else {
      for (last = list->head; last && last->next; last = last->next)
	      ;
      if (last)
	      last->next = temp;
      else
         list->head = temp;
	  temp->next = NULL;
   }
}
   
int ListDrop(List *list, double toDrop) {
   Node *prior = NULL, *temp;
   
   for (temp = list->head; temp && temp->data != toDrop; temp = temp->next)
      prior = temp;
   if (temp) {
      if (prior)
	      prior->next = temp->next;
      else
	      list->head->next = temp->next;
	   freeNode(temp);
   }
   list->count--;
}

void ListStart(List *list) {
   list->at = list->head;
}

int ListHasNext(List *list) {
   return list->at != NULL;
}

double ListCurrent(List *list) {
   assert(list->at != NULL);
   return list->at->data;
}

void ListAdvance(List *list) {
   assert(list->at != NULL);
   list->at = list->at->next;
}

void ListClearFreelist() {
   Node *temp;
   
   while (freeList) {
      temp = freeList;
      freeList = temp->next;
      free(temp);
   }
}