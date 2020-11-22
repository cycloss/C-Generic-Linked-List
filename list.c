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
    if (index >= l->size) {
        return false;
    } else {
        *res = traverseNode(l->head, index);
        return true;
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
