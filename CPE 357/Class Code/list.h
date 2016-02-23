#ifndef LIST_H
#define LIST_H

typedef struct Node Node;

typedef struct {
   Node *head;
   Node *at;
   int count;
} List;

typedef enum {LIST_AT_START, LIST_AT_END} ListAddType;

/* Alternative 1
static const int LIST_AT_START = 0; 
static const int LIST_AT_END = 1;
*/

/* Alternative 2
#define LIST_AT_END 1
#define LIST_AT_START 0
*/

void ListCreate(List *list);
void ListDestroy(List *list);
int ListGetCount(List *list);
void ListAdd(List *list, double toAdd, ListAddType where);
int ListDrop(List *list, double toDrop);

// Iterators
void ListStart(List *list);
int ListHasNext(List *list);
double ListCurrent(List *list);
void ListAdvance(List *list);

#endif