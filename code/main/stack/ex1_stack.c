/* 
ex1_stack.c
*/
#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

int main() {
    Stack stack;
    stack_init(&stack, free);

    int values[] = {1, 2, 3, 4, 5};
    int i;

    printf("Pushing elements onto the stack:\n");
    for (i = 0; i < sizeof(values) / sizeof(values[0]); ++i) {
        int *data = malloc(sizeof(int));
        *data = values[i];
        stack_push(&stack, data);
        printf("%d ", *data);
    }
    printf("\n");

    printf("Stack size: %d\n", stack_size(&stack));

    printf("Popping elements from the stack:\n");
    while (stack_size(&stack) > 0) {
        int *data;
        stack_pop(&stack, (void **)&data);
        printf("%d ", *data);
        free(data);
    }
    printf("\n");

    printf("Stack size after popping all elements: %d\n", stack_size(&stack));

    stack_destroy(&stack);

    return 0;
}
