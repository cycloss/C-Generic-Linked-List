#include "../src/linkedList.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printInt(void* val) {
    printf("%i\n", *(int*)val);
}

void printIntList(linkedList* l) {
    iterateListValues(l, printInt);
}

void printString(void* val) {
    puts((char*)val);
}

void printStringList(linkedList* l) {
    iterateListValues(l, printString);
}

int main() {

    puts("Creating list...");
    linkedList* l = createList();
    for (int i = 1; i < 6; i++) {
        int* pVal = malloc(sizeof(int));
        *pVal = i;
        appendToList(l, pVal);
    }
    printIntList(l);

    puts("Reversing list...");
    reverseList(l);
    printIntList(l);

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
    printIntList(l);

    int searchVal = 3;
    int foundIndex = findIndexOfValue(l, &searchVal, intComparator);
    foundIndex == -1 ? puts("Failed to find search int") : printf("Found value %i at index: %i\n", searchVal, foundIndex);

    int lastIndex = getLastIndex(l);
    lastIndex == -1 ? puts("List empty") : printf("Last index is: %i\n", lastIndex);

    puts("Clearing list...");
    clearList(l);

    puts("Creating string list...");
    char* strs[] = { "London", "Paris", "Berlin", "Moscow", "Beijing", "Tokyo" };
    int len = sizeof(strs) / sizeof(char*);
    for (int i = 0; i < len; i++) {
        char* str = malloc(sizeof(char) * (strlen(strs[i]) + 1));
        strcpy(str, strs[i]);
        appendToList(l, str);
    }
    printStringList(l);

    char* searchStr = "Tokyo";
    int foundIndex2 = findIndexOfValue(l, searchStr, stringComparator);
    foundIndex2 == -1 ? puts("Failed to find search string") : printf("Found value %s at index: %i\n", searchStr, foundIndex2);

    puts("Freeing list...");
    freeList(l);
}