
typedef struct node {
    void* value;
    struct node* next;
} node;

void printNode(node* n);