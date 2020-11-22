
#include "list.h"
#include "stdio.h"

int main() {

    list* l = createList();
    for (int i = 1; i < 11; i++) {
        i % 2 == 0 ? appendToList(l, i) : prependToList(l, i);
    }
    int res;
    int index = 4;
    if (getValueAt(l, index, &res)) {
        printf("Value at index %i: %i\n", index, res);
    }
    printList(l);
}