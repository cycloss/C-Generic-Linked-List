#include "linkedList.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

//TODO add toArray method, make sure to copy values else there will be problems if list is freed
//TODO add benchmark

linkedList* createList() {
    linkedList* newListP = malloc(sizeof(linkedList));
    if (!newListP) {
        return NULL;
    }
    linkedList l = { NULL, NULL, 0 };
    *newListP = l;
    return newListP;
}

static node* createNode(void* pVal) {
    node* np = malloc(sizeof(node));
    if (!np) {
        return NULL;
    }
    *np = (node) { pVal, NULL };
    return np;
}

static void* fatalError(char* msg) {
    printf("Fatal error: %s\n", msg);
    exit(1);
    return NULL;
}

static void checkNull(linkedList* l) {
    if (!l) {
        fatalError("linkedList was null");
    }
}

bool appendToList(linkedList* l, void* pVal) {
    checkNull(l);
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
    checkNull(l);
    node* np = createNode(pVal);
    if (!np) {
        return false;
    }
    if (l->head) {
        np->next = l->head;
        l->head = np;
    } else {
        appendToList(l, pVal);
    }
    l->_size++;
    return true;
}

bool insertValueAt(linkedList* l, int index, void* pVal) {
    checkNull(l);
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

void* removeValueAt(linkedList* l, int index) {
    checkNull(l);
    if (index >= l->_size || index < 0) {
        return fatalError("Index out of bounds");
    } else {
        node* previous = NULL;
        node* current = l->head;
        while (index--) {
            previous = current;
            current = current->next;
        }
        if (current == l->head) {
            l->head = current->next;
        }
        if (current == l->tail) {
            l->tail = previous;
        }
        if (previous) {
            previous->next = current->next;
        }
        void* val = current->value;
        free(current);
        l->_size--;
        return val;
    }
}

void* getValueAt(linkedList* l, int index) {
    checkNull(l);
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
    return getValueAt(l, l->_size - 1);
}

int getLastIndex(linkedList* l) {
    checkNull(l);
    return l->_size <= 0 ? -1 : l->_size - 1;
}

int findIndexOfValue(linkedList* l, void* value, bool (*comparator)(void*, void*)) {
    checkNull(l);
    node* current = l->head;
    for (int i = 0; current; current = current->next, i++) {
        if (comparator(value, current->value)) {
            return i;
        }
    }
    return -1;
}

void reverseList(linkedList* l) {
    checkNull(l);
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
    checkNull(l);
    for (node* current = l->head; current; current = current->next) {
        iterator(current->value);
    }
}

static void iterateListNodes(linkedList* l, void (*iterator)(node*)) {
    checkNull(l);
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

//TODO: fix bug as not properly clearing list
void clearList(linkedList* l) {
    iterateListNodes(l, freeNodeAndValue);
    l->_size = 0;
}

void freeList(linkedList* l) {
    checkNull(l);
    clearList(l);
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