/* ex1_cdlist.c */
#include <stdio.h>
#include <stdlib.h>
#include "cdlist.h"

static void print_cdlist(const CDList *list) {
    CDListNode *node = cdlist_head(list);
    int i = 0;

    if (cdlist_size(list) == 0) {
        printf("Empty Circular Doubly Linked List\n");
        return;
    }

    do {
        printf("cdlist.node[%03d]=%p, data=%p, prev=%p, next=%p\n", i, node, cdlist_data(node), cdlist_prev(node), cdlist_next(node));
        node = cdlist_next(node);
        i++;
    } while (node != cdlist_head(list));
}

int main(int argc, char **argv) {
    CDList list;
    CDListNode *node;
    int *data, i;

    cdlist_init(&list, free);

    // Insert nodes into the circular doubly linked list
    for (i = 1; i <= 5; ++i) {
        data = (int *)malloc(sizeof(int));
        *data = i;
        if (cdlist_ins_next(&list, cdlist_head(&list), data) != 0)
            return 1;
    }

    // Print the circular doubly linked list
    printf("Original Circular Doubly Linked List:\n");
    print_cdlist(&list);

    // Inserting 99 after the third node
    data = (int *)malloc(sizeof(int));
    *data = 99;
    node = cdlist_head(&list);
    for (i = 0; i < 2; ++i)
        node = cdlist_next(node);
    cdlist_ins_next(&list, node, data);
    printf("\nCircular Doubly Linked List after inserting 99 after the third node:\n");
    print_cdlist(&list);

    // Removing the second node
    node = cdlist_next(cdlist_head(&list));
    cdlist_rem(&list, node, (void **)&data);
    printf("\nCircular Doubly Linked List after removing the second node:\n");
    print_cdlist(&list);

    // Destroy the circular doubly linked list
    cdlist_destroy(&list);
    return 0;
}
