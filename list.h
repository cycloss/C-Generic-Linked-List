#include "node.h"
#include <stdbool.h>

typedef struct {
    node* head;
    node* tail;
    //do not modify the size value manually
    int size;
} list;

list* createList();
void appendToList(list* l, void* pVal);
void prependToList(list* l, void* pVal);
void* removeValueAt(list* l, int index);
void* getValueAt(list* l, int index);
void* getFirst(list* l);
void* getLast(list* l);
void insertValueAt(list* l, int index, void* pVal);
void printList(list* l, void (*printVal)(void*));
void reverseList(list* l);
void freeList(list* l);