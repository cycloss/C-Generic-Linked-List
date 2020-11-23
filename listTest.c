//TODO add makefile
//TODO mae install for makefile based of cs50 install
#include "list.h"
#include "stdio.h"
#include "stdlib.h"

void printVal(void* val) {
    printf("%i\n", *(int*)val);
}

int main() {

    list* l = createList();
    for (int i = 1; i < 4; i++) {
        int* pVal = malloc(sizeof(int));
        *pVal = i;
        appendToList(l, pVal);
    }
    void* res;
    int index = 4;
    if (getValueAt(l, index, &res)) {
        printf("Value at index %i: %i\n", index, *(int*)res);
    }
    printList(l, printVal);
    reverseList(l);
    printList(l, printVal);

    void* res2;
    int ind = 0;
    if (removeValueAt(l, ind, &res2)) {
        printf("Value removed at index %i: %i\n", ind, *(int*)res2);
        free(res2);
    }
    printList(l, printVal);
    int* pVal = malloc(sizeof(int));
    *pVal = 8;
    if (!insertValueAt(l, 0, pVal)) {
        puts("Could not add value");
    }
    printList(l, printVal);
    freeList(l);
}