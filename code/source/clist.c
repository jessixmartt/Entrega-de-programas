/* clist.c */
#include <stdlib.h>
#include "clist.h"

void clist_init(CList *list, void (*destroy)(void *data)) {
    list->size = 0;
    list->destroy = destroy;
    list->head = NULL;
}

void clist_destroy(CList *list) {
    void *data;
    while (clist_size(list) > 0) {
        if (clist_rem_next(list, clist_head(list), (void **)&data) == 0 && list->destroy != NULL) {
            list->destroy(data);
        }
    }
}

int clist_ins_next(CList *list, CListNode *node, const void *data) {
    CListNode *new_node;

    if ((new_node = (CListNode *)malloc(sizeof(CListNode))) == NULL)
        return -1;

    new_node->data = (void *)data;

    if (clist_size(list) == 0) {
        new_node->next = new_node;  // Circular list with only one node
        list->head = new_node;
    } else {
        new_node->next = node->next;
        node->next = new_node;
    }

    list->size++;
    return 0;
}

int clist_rem_next(CList *list, CListNode *node, void **data) {
    CListNode *old_node;

    if (clist_size(list) == 0)
        return -1;

    *data = node->next->data;
    old_node = node->next;

    if (node->next == node) {
        list->head = NULL;  // Removing the last node in the circular list
    } else {
        node->next = node->next->next;
        if (old_node == clist_head(list))
            list->head = node->next;
    }

    free(old_node);
    list->size--;
    return 0;
}
