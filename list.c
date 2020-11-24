#include "list.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

list* createList() {
    list* newListP = malloc(sizeof(list));
    list l = { NULL, NULL, 0 };
    *newListP = l;
    return newListP;
}

static node* createNode(void* pVal) {
    node* np = malloc(sizeof(node));
    *np = (node) { pVal, NULL };
    return np;
}

static void* fatalError(char* msg) {
    printf("Fatal error: %s\n", msg);
    exit(1);
    return NULL;
}

void appendToList(list* l, void* pVal) {
    node* np = createNode(pVal);
    if (l->tail) {
        l->tail->next = np;
        l->tail = np;
    } else {
        l->head = l->tail = np;
    }
    l->size++;
}

void prependToList(list* l, void* pVal) {
    node* np = createNode(pVal);
    if (l->head) {
        np->next = l->head;
        l->head = np;
    } else {
        appendToList(l, pVal);
    }
    l->size++;
}

static void* traverseNode(node* n, int remaining) {
    if (remaining) {
        return traverseNode(n->next, remaining - 1);
    } else {
        return n->value;
    }
}

void* removeValueAt(list* l, int index) {
    if (index >= l->size || index < 0) {
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
        l->size--;
        return val;
    }
}

void* getValueAt(list* l, int index) {
    if (index >= l->size || index < 0) {
        return fatalError("Index out of bounds");
    } else {
        return traverseNode(l->head, index);
    }
}

void* getFirst(list* l) {
    return getValueAt(l, 0);
}

void* getLast(list* l) {
    return getValueAt(l, l->size - 1);
}

void insertValueAt(list* l, int index, void* pVal) {
    if (index > l->size || index < 0) {
        fatalError("Index out of bounds");
    } else {
        node* current = l->head;
        node* previous = NULL;
        while (index--) {
            previous = current;
            current = current->next;
        }
        node* newNode = createNode(pVal);
        if (current == l->head) {
            l->head = newNode;
            newNode->next = current;
        } else {
            previous->next = newNode;
            newNode->next = current;
        }
        l->size++;
    }
}

void reverseList(list* l) {
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

void printList(list* l, void (*printVal)(void*)) {
    puts("------------");
    node* current = l->head;
    for (int i = 0; current; i++) {
        printf("node at %i: ", i);
        printVal(current->value);
        current = current->next;
    }
    puts("------------");
}

void freeList(list* l) {
    node* current = l->head;
    while (current) {
        node* next = current->next;
        free(current->value);
        free(current);
        current = next;
    }
    free(l);
}