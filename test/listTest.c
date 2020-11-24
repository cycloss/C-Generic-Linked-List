#include "../src/list.h"
#include <stdio.h>
#include <stdlib.h>

//passed as an argument for printList function
void printVal(void* val) {
    printf("%i\n", *(int*)val);
}

int main() {

    puts("Creating list...");
    list* l = createList();
    for (int i = 1; i < 6; i++) {
        int* pVal = malloc(sizeof(int));
        *pVal = i;
        appendToList(l, pVal);
    }
    printList(l, printVal);

    puts("Reversing list...");
    reverseList(l);
    printList(l, printVal);

    int index = 3;
    void* res = getValueAt(l, index);
    printf("Value at index %i: %i\n", index, *(int*)res);

    int ind = 0;
    void* res2 = removeValueAt(l, ind);
    if (res2) {
        printf("Value removed at index %i: %i\n", ind, *(int*)res2);
        free(res2);
    }

    int* pVal = malloc(sizeof(int));
    *pVal = 8;
    printf("Inserting %i at index %i\n", *pVal, ind);
    insertValueAt(l, ind, pVal);
    printList(l, printVal);

    puts("Freeing list...");
    freeList(l);
}