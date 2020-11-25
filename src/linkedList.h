#include "node.h"
#include <stdbool.h>

typedef struct {
    node* head;
    node* tail;
    //do not modify the size value manually
    int _size;
} linkedList;

linkedList* createList();
bool appendToList(linkedList* l, void* pVal);
bool prependToList(linkedList* l, void* pVal);
bool insertValueAt(linkedList* l, int index, void* pVal);
void* removeValueAt(linkedList* l, int index);
void* getValueAt(linkedList* l, int index);
void* getFirst(linkedList* l);
void* getLast(linkedList* l);
int getLastIndex(linkedList* l);
int findValue(linkedList* l, void* value, bool (*comparator)(void*, void*));
void iterateList(linkedList* l, void (*iterator)(void*));
void reverseList(linkedList* l);
void freeList(linkedList* l);