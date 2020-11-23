#include "node.h"
#include <stdbool.h>
typedef struct {
    node* head;
    node* tail;
    int size;
} list;

list* createList();
void appendToList(list* l, int val);
void prependToList(list* l, int val);
bool getValueAt(list* l, int index, int* res);
void printList(list* l);
void reverseList(list* l);
bool removeValueAt(list* l, int index, int* res);
bool insertValueAt(list* l, int index, int val);
void freeList(list* l);