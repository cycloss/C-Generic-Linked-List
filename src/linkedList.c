#include "linkedList.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void* fatalError(char* msg) {
    printf("Fatal error: %s\n", msg);
    exit(1);
    return NULL;
}

linkedList* createList() {
    linkedList* newListP = malloc(sizeof(linkedList));
    if (!newListP) {
        fatalError("Failed to create list");
    }
    linkedList l = { NULL, NULL, 0 };
    *newListP = l;
    return newListP;
}

static node* createNode(void* pVal) {
    node* np = malloc(sizeof(node));
    if (!np) {
        fatalError("Failed to create list node");
    }
    *np = (node) { pVal, NULL };
    return np;
}

bool appendToList(linkedList* l, void* pVal) {
    node* np = createNode(pVal);
    if (!np) {
        return false;
    }
    if (l->tail) {
        l->tail->next = np;
        l->tail = np;
    } else {
        l->head = l->tail = np;
    }
    l->_size++;
    return true;
}

bool prependToList(linkedList* l, void* pVal) {
    node* np = createNode(pVal);
    if (!np) {
        return false;
    }
    if (l->head) {
        np->next = l->head;
        l->head = np;
        l->_size++;
    } else {
        appendToList(l, pVal);
    }
    return true;
}

bool insertValueAt(linkedList* l, int index, void* pVal) {
    if (index > l->_size || index < 0) {
        fatalError("Index out of bounds");
        return false;
    } else {
        node* current = l->head;
        node* previous = NULL;
        while (index--) {
            previous = current;
            current = current->next;
        }
        node* newNode = createNode(pVal);
        if (!newNode) {
            return false;
        }
        if (current == l->head) {
            l->head = newNode;
            newNode->next = current;
        } else {
            previous->next = newNode;
            newNode->next = current;
        }
        l->_size++;
        return true;
    }
}

static void* traverseNode(node* n, int remaining) {
    if (remaining) {
        return traverseNode(n->next, remaining - 1);
    } else {
        return n->value;
    }
}

static void handleRemoval(linkedList* l, node* previous, node* current) {
    if (current == l->head) {
        l->head = current->next;
    }
    if (current == l->tail) {
        l->tail = previous;
    }
    if (previous) {
        previous->next = current->next;
    }
    l->_size--;
}

void* removeValueAt(linkedList* l, int index) {
    if (index >= l->_size || index < 0) {
        return fatalError("Index out of bounds");
    } else {
        node* previous = NULL;
        node* current = l->head;
        while (index--) {
            previous = current;
            current = current->next;
        }
        handleRemoval(l, previous, current);
        void* val = current->value;
        free(current);
        return val;
    }
}

/**
 * Removes first instance of a value
 * 
*/
void* removeValue(linkedList* l, void* pVal, bool (*comparator)(void*, void*)) {
    node* current = l->head;
    node* previous = NULL;
    while (current) {
        if (comparator(pVal, current->value)) {
            handleRemoval(l, previous, current);
            void* val = current->value;
            free(current);
            return val;
        }
        previous = current;
        current = current->next;
    }
    return NULL;
}

/**
 * Removes the first value.
 * @return a pointer to the removed first value, null pointer if no first value.
 */
void* removeFirst(linkedList* l) {
    if (l->_size == 0) {
        return NULL;
    } else {
        return removeValueAt(l, 0);
    }
}

void* removeLast(linkedList* l) {
    if (l->_size == 0) {
        return NULL;
    } else {
        return removeValueAt(l, l->_size - 1);
    }
}

void* getValueAt(linkedList* l, int index) {
    if (index >= l->_size || index < 0) {
        return fatalError("Index out of bounds");
    } else {
        return traverseNode(l->head, index);
    }
}

void* getFirst(linkedList* l) {
    return getValueAt(l, 0);
}

void* getLast(linkedList* l) {
    return l->tail ? l->tail->value : NULL;
}

int getLastIndex(linkedList* l) {
    return l->_size <= 0 ? -1 : l->_size - 1;
}

int findIndexOfValue(linkedList* l, void* value, bool (*comparator)(void*, void*)) {
    node* current = l->head;
    for (int i = 0; current; current = current->next, i++) {
        if (comparator(value, current->value)) {
            return i;
        }
    }
    return -1;
}

int getListSize(linkedList* l) {
    return l->_size;
}

void reverseList(linkedList* l) {
    node* current = l->head;
    node* previous = NULL;
    while (current) {
        node* next = current->next;
        if (next == NULL) {
            l->tail = l->head;
            l->head = current;
        }
        current->next = previous;
        previous = current;
        current = next;
    }
}

void iterateListValues(linkedList* l, void (*iterator)(void*)) {
    for (node* current = l->head; current; current = current->next) {
        iterator(current->value);
    }
}

static void iterateListNodes(linkedList* l, void (*iterator)(node*)) {
    node* current = l->head;
    while (current) {
        node* next = current->next;
        iterator(current);
        current = next;
    }
}

static void freeNodeAndValue(node* n) {
    free(n->value);
    free(n);
}

static void freeNode(node* n) {
    free(n);
}

/**
 * Removes all values from list
 * @param l a pointer to a linked list to remove values from
 * @param freeValues a bool for whether or not to free list value pointers from memory
 **/
void clearList(linkedList* l, bool freeValues) {
    if (freeValues) {
        iterateListNodes(l, freeNodeAndValue);
    } else {
        iterateListNodes(l, freeNode);
    }
    l->head = NULL;
    l->tail = NULL;
    l->_size = 0;
}

/**
 * Removes all values from list and frees the list from memory
 * @param l a pointer to a linked list to clear and free from memory
 * @param freeValues a bool for whether or not to free list value pointers from memory
 **/
void freeList(linkedList* l, bool freeValues) {
    clearList(l, freeValues);
    free(l);
}

bool intComparator(void* searchVal, void* currentVal) {
    return *(int*)searchVal == *(int*)currentVal;
}

bool floatComparator(void* searchVal, void* currentVal) {
    return *(float*)searchVal == *(float*)currentVal;
}

bool doubleComparator(void* searchVal, void* currentVal) {
    return *(double*)searchVal == *(double*)currentVal;
}

bool longComparator(void* searchVal, void* currentVal) {
    return *(long*)searchVal == *(long*)currentVal;
}

bool charComparator(void* searchVal, void* currentVal) {
    return *(char*)searchVal == *(char*)currentVal;
}

bool stringComparator(void* searchVal, void* currentVal) {
    for (char *str1 = (char*)searchVal, *str2 = (char*)currentVal; *str1 != '\0' || *str2 != '\0'; str1++, str2++) {
        if (*str1 != *str2) {
            return false;
        }
    }
    return true;
}

void** listToArrayShallowCpy(linkedList* l) {
    void** arr = malloc(getListSize(l) * sizeof(void*));
    node* current = l->head;
    for (int i = 0; current; i++) {
        arr[i] = current->value;
        current = current->next;
    }
    return arr;
}

void** listToArrayDeepCpy(linkedList* l, void* (*memAllocFunc)(void*)) {
    void** arr = malloc(getListSize(l) * sizeof(void*));
    node* current = l->head;
    for (int i = 0; current; i++) {
        arr[i] = memAllocFunc(current->value);
        current = current->next;
    }
    return arr;
}

static void* mallocAndAssign(size_t blockSize, void* valToAsssign) {
    void* blockp = malloc(blockSize);
    return memcpy(blockp, valToAsssign, blockSize);
}

void* intMemAlloc(void* intToCpy) {
    return mallocAndAssign(sizeof(int), intToCpy);
}

void* floatMemAlloc(void* floatToCpy) {
    return mallocAndAssign(sizeof(float), floatToCpy);
}

void* doubleMemAlloc(void* doubleToCpy) {
    return mallocAndAssign(sizeof(double), doubleToCpy);
}

void* longMemAlloc(void* longToCpy) {
    return mallocAndAssign(sizeof(long), longToCpy);
}

void* charMemAlloc(void* charToCpy) {
    return mallocAndAssign(sizeof(char), charToCpy);
}

void* stringMemAlloc(void* strToCpy) {
    return strdup((char*)strToCpy);
}