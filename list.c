//TODO make generic version with generic print statement lambda
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

static node* createNode(int val) {
    node* np = malloc(sizeof(node));
    *np = (node) { val, NULL };
    return np;
}

void appendToList(list* l, int val) {
    node* np = createNode(val);
    if (l->tail) {
        l->tail->next = np;
        l->tail = np;
    } else {
        l->head = l->tail = np;
    }
    l->size++;
}

void prependToList(list* l, int val) {
    node* np = createNode(val);
    if (l->head) {
        np->next = l->head;
        l->head = np;
    } else {
        appendToList(l, val);
    }
    l->size++;
}

static int traverseNode(node* n, int remaining) {
    if (remaining) {
        return traverseNode(n->next, remaining - 1);
    } else {
        return n->value;
    }
}

bool getValueAt(list* l, int index, int* res) {
    if (index >= l->size || index < 0) {
        return false;
    } else {
        *res = traverseNode(l->head, index);
        return true;
    }
}

bool insertValueAt(list* l, int index, int val) {
    if (index > l->size || index < 0) {
        return false;
    } else {
        node* current = l->head;
        node* previous = NULL;
        while (index--) {
            previous = current;
            current = current->next;
        }
        node* newNode = createNode(val);
        if (current == l->head) {
            l->head = newNode;
            newNode->next = current;
        } else {
            previous->next = newNode;
            newNode->next = current;
        }
        l->size++;
        return true;
    }
}

bool removeValueAt(list* l, int index, int* res) {
    if (index >= l->size || index < 0) {
        return false;
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
        *res = current->value;
        free(current);
        l->size--;
        return true;
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

void printList(list* l) {
    puts("------------");
    node* current = l->head;
    for (int i = 0; current; i++) {
        printf("node at %i: ", i);
        printNode(current);
        current = current->next;
    }
    puts("------------");
}

void freeList(list* l) {
    node* current = l->head;
    while (current) {
        node* next = current->next;
        free(current);
        current = next;
    }
    free(l);
}
