//TODO add makefile
//TODO mae install for makefile based of cs50 install
#include "list.h"
#include "stdio.h"

int main() {

    list* l = createList();
    for (int i = 1; i < 4; i++) {
        appendToList(l, i);
    }
    int res;
    int index = 4;
    if (getValueAt(l, index, &res)) {
        printf("Value at index %i: %i\n", index, res);
    }
    printList(l);
    reverseList(l);
    printList(l);

    int res2;
    int ind = 0;
    if (removeValueAt(l, ind, &res2)) {
        printf("Value removed at index %i: %i\n", ind, res2);
    }
    printList(l);

    if (!insertValueAt(l, 0, 8)) {
        puts("Could not add value");
    }
    printList(l);
    freeList(l);
}