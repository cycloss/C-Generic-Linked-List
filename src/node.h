#ifndef LIST_NODE_H
#define LIST_NODE_H

typedef struct node {
    void* value;
    struct node* next;
} node;

#endif