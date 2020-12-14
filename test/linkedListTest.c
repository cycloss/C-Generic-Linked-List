#include "../src/linkedList.h"
#include "linkedListTest.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {

    puts("Creating list...");
    linkedList* l = createList();
    int nums[] = { 1, 2, 3, 4, 5 };
    int len = sizeof(nums) / sizeof(int);
    for (int i = 0; i < len; i++) {
        appendToList(l, &nums[i]);
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
    }

    int val = 8;
    printf("Inserting %i at index %i\n", val, ind);
    insertValueAt(l, ind, &val);
    printIntList(l);

    int searchVal = 3;
    int foundIndex = findIndexOfValue(l, &searchVal, intComp);
    foundIndex == -1 ? puts("Failed to find search int") : printf("Found value %i at index: %i\n", searchVal, foundIndex);

    int lastIndex = getLastIndex(l);
    lastIndex == -1 ? puts("List empty") : printf("Last index is: %i\n", lastIndex);

    puts("Creating deep copy array from list...");
    int** arr = (int**)listToArrayDeepCpy(l, intMemAlloc);
    printIntArray(arr, getListSize(l));
    freeArray(arr, getListSize(l));

    puts("Clearing list...");
    clearList(l, false);

    puts("Creating string list...");
    char* strs[] = { "London", "Paris", "Berlin", "Moscow", "Beijing", "Tokyo" };
    int len2 = sizeof(strs) / sizeof(char*);
    for (int i = 0; i < len2; i++) {
        char* str = malloc(sizeof(char) * (strlen(strs[i]) + 1));
        strcpy(str, strs[i]);
        appendToList(l, str);
    }
    printStringList(l);

    char* searchStr = "Tokyo";
    int foundIndex2 = findIndexOfValue(l, searchStr, strComp);
    foundIndex2 == -1 ? puts("Failed to find search string") : printf("Found value %s at index: %i\n", searchStr, foundIndex2);

    char* valueToRemove = "Berlin";
    char* removed = removeValue(l, valueToRemove, strComp);
    removed ? printf("Removed: %s\n", valueToRemove) : printf("Failed to remove %s\n", valueToRemove);
    free(removed);

    puts("Creating deep copy array from list...");
    char** arr2 = (char**)listToArrayDeepCpy(l, stringMemAlloc);
    printStringArray(arr2, getListSize(l));
    freeArray(arr2, getListSize(l));

    puts("Freeing list...");
    freeList(l, true);
}

void printInt(void* val) {
    printf("%i -> ", *(int*)val);
}

void printIntList(linkedList* l) {
    iterateListValues(l, printInt);
    puts("");
}

void printString(void* val) {
    printf("%s -> ", (char*)val);
}

void printStringList(linkedList* l) {
    iterateListValues(l, printString);
    puts("");
}

void printStringArray(char** arr, int len) {
    printf("Array: ");
    for (int i = 0; i < len; i++) {
        printf("%s, ", arr[i]);
    }
    puts("");
}

void printIntArray(int** arr, int len) {
    printf("Array: ");
    for (int i = 0; i < len; i++) {
        printf("%i, ", *arr[i]);
    }
    puts("");
}

void freeArray(void* arr, int len) {
    void** arrp = (void**)arr;
    for (int i = 0; i < len; i++) {
        free(arrp[i]);
    }
    free(arr);
}