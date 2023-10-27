/* ex1_clist.c */
#include <stdio.h>
#include <stdlib.h>
#include "clist.h"

static void print_clist(const CList *list) {
    CListNode *node = clist_head(list);
    int i = 0;

    if (clist_size(list) == 0) {
        printf("Empty Circular List\n");
        return;
    }

    do {
        printf("clist.node[%03d]=%p, data=%p, next=%p\n", i, node, clist_data(node), clist_next(node));
        node = clist_next(node);
        i++;
    } while (node != clist_head(list));
}

int main(int argc, char **argv) {
    CList list;
    CListNode *node;
    int *data, i;

    clist_init(&list, free);

    // Insert nodes into the circular list
    for (i = 10; i <= 20; ++i) {
        data = (int *)malloc(sizeof(int));
        *data = i;
        if (clist_ins_next(&list, clist_head(&list), data) != 0)
            return 1;
    }

    // Print the circular list
    printf("Original Circular List:\n");
    print_clist(&list);

    // Removing a node after the third node
    node = clist_head(&list);
    for (i = 0; i < 2; ++i)
        node = clist_next(node);
    clist_rem_next(&list, node, (void **)&data);
    printf("\nCircular List after removing a node after the third node:\n");
    print_clist(&list);

    // Inserting 99 after the second node
    data = (int *)malloc(sizeof(int));
    *data = 99;
    node = clist_head(&list);
    clist_ins_next(&list, clist_next(node), data);
    printf("\nCircular List after inserting 99 after the second node:\n");
    print_clist(&list);

    // Destroy the circular list
    clist_destroy(&list);
    return 0;
}
