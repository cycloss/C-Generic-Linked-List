#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdbool.h>

typedef struct node {
    void* value;
    struct node* next;
} node;

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
void* removeValue(linkedList* l, void* pVal, bool (*comparator)(void*, void*));
void* removeFirst(linkedList* l);
void* removeLast(linkedList* l);
void* getValueAt(linkedList* l, int index);
void* getFirst(linkedList* l);
void* getLast(linkedList* l);
int getLastIndex(linkedList* l);
int findIndexOfValue(linkedList* l, void* value, bool (*comparator)(void*, void*));
int getListSize(linkedList* l);
void iterateListValues(linkedList* l, void (*iterator)(void*));
void reverseList(linkedList* l);
void clearList(linkedList* l, bool freeValues);
void freeList(linkedList* l, bool freeValues);

bool intComparator(void* searchVal, void* currentVal);
bool floatComparator(void* searchVal, void* currentVal);
bool doubleComparator(void* searchVal, void* currentVal);
bool longComparator(void* searchVal, void* currentVal);
bool charComparator(void* searchVal, void* currentVal);
bool stringComparator(void* searchVal, void* currentVal);

void** listToArrayShallowCpy(linkedList* l);
void** listToArrayDeepCpy(linkedList* l, void* (*memAllocFunc)(void*));

void* intMemAlloc(void* intToCpy);
void* floatMemAlloc(void* floatToCpy);
void* doubleMemAlloc(void* doubleToCpy);
void* longMemAlloc(void* longToCpy);
void* charMemAlloc(void* charToCpy);
void* stringMemAlloc(void* strToCpy);

#endif