/* ex1_dlist.c */
#include <stdio.h>
#include <stdlib.h>
#include "dlist.h"

static void print_dlist(const DList *list) {
    DListNode *node = dlist_head(list);
    int index = 0;
    
    printf("Doubly Linked List:\n");
    while (node != NULL) {
        printf("Node %d: %d\n", index, *(int *)dlist_data(node));
        node = dlist_next(node);
        index++;
    }
    printf("List size: %d\n", dlist_size(list));
}

int main() {
    DList list;
    dlist_init(&list, free);

    int values[] = {1, 2, 3, 4, 5};
    int i;
    
    for (i = 0; i < sizeof(values) / sizeof(values[0]); ++i) {
        int *data = malloc(sizeof(int));
        *data = values[i];
        dlist_ins_next(&list, dlist_tail(&list), data);
    }

    printf("Original List:\n");
    print_dlist(&list);

    // Inserting a new node after the second node
    int new_value = 6;
    DListNode *node = dlist_head(&list);
    for (i = 0; i < 2; ++i) {
        node = dlist_next(node);
    }
    int *new_data = malloc(sizeof(int));
    *new_data = new_value;
    dlist_ins_next(&list, node, new_data);

    printf("\nList after inserting %d after the second node:\n", new_value);
    print_dlist(&list);

    // Removing the third node
    node = dlist_head(&list);
    for (i = 0; i < 3; ++i) {
        node = dlist_next(node);
    }
    int *removed_data;
    dlist_remove(&list, node, (void **)&removed_data);

    printf("\nList after removing the third node (%d):\n", *removed_data);
    print_dlist(&list);

    // Destroying the list
    dlist_destroy(&list);

    return 0;
}
