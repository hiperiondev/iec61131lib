/* https://github.com/LookCos/learn-data-structures */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "iec_stack.h"

stack_t stack_create() {
    stack_t stack = (struct stack*) malloc(sizeof(struct stack));
    if (stack == NULL)
        return NULL;
    stack->length = 0;
    stack->top = NULL;
    return stack;
}

stack_t stack_push(stack_t stack, void *data) {
    stack_node *node = (struct stack_node*) malloc(sizeof(struct stack_node));
    if (node == NULL)
        return NULL;
    node->data = data;

    node->next = stack->top;
    stack->top = node;

    stack->length++;
    return stack;
}

void* stack_pop(stack_t stack) {
    stack_node *current = stack->top;
    if (current == NULL)
        return NULL;
    void *data = current->data;
    stack->top = stack->top->next;

    free(current);
    stack->length--;
    return data;
}

void stack_flush(stack_t stack) {
    int length = stack->length;
    stack_node *current, *next;
    current = stack->top;
    while (length--) {
        next = current->next;
        free(current);
        current = next;
    }

    stack->length = 0;
    stack->top = NULL;
}

int stack_size(stack_t stack) {
    return stack->length;
}

bool stack_empty(stack_t stack) {
    return stack->length == 0 ? 1 : 0;
}

void stack_release(stack_t stack) {
    stack_empty(stack);
    free(stack);
}
