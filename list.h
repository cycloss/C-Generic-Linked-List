#include "node.h"
#include <stdbool.h>

typedef struct {
    node* head;
    node* tail;
    int size;
} list;

list* createList();
void appendToList(list* l, void* pVal);
void prependToList(list* l, void* pVal);
bool getValueAt(list* l, int index, void** res);
bool insertValueAt(list* l, int index, void* pVal);
bool removeValueAt(list* l, int index, void** res);
void printList(list* l, void (*printVal)(void*));
void reverseList(list* l);
void freeList(list* l);