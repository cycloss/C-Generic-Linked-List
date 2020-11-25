#include "../src/linkedList.h"
#include <stdio.h>
#include <stdlib.h>

void printVal(void* val) {
    printf("%i\n", *(int*)val);
}

void printList(linkedList* l) {
    iterateList(l, printVal);
}

bool comparator(void* searchVal, void* currentVal) {
    return *(int*)searchVal == *(int*)currentVal;
}

int main() {

    puts("Creating list...");
    linkedList* l = createList();
    for (int i = 1; i < 6; i++) {
        int* pVal = malloc(sizeof(int));
        *pVal = i;
        appendToList(l, pVal);
    }
    printList(l);

    puts("Reversing list...");
    reverseList(l);
    printList(l);

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
    printList(l);

    int searchVal = 3;
    int foundIndex = findValue(l, &searchVal, comparator);
    foundIndex == -1 ? puts("Failed to find value") : printf("Found value %i at index: %i\n", searchVal, foundIndex);

    int lastIndex = getLastIndex(l);
    lastIndex == -1 ? puts("List empty") : printf("Last index is: %i\n", lastIndex);

    puts("Freeing list...");
    freeList(l);
}