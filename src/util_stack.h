#ifndef __STACK_H__
#define __STACK_H__

#include <stdbool.h>
#include <stddef.h>

/**
 * @typedef stack_node_t
 * @brief
 *
 */
typedef struct stack_node_t {
    struct stack_node_t *next; /**< */
                   void *data; /**< */
} stack_node_t;

/**
 * @typedef stack_t
 * @brief
 *
 */
typedef struct stack_t {
    struct stack_node_t *top;    /**< */
                    int length; /**< */
} *stack_t;

/**
 * @fn stack_t stack_create()
 * @brief
 *
 * @return
 */
stack_t stack_create() {
    stack_t stack = (struct stack_t*) malloc(sizeof(struct stack_t));
    if (stack == NULL)
        return NULL;
    stack->length = 0;
    stack->top = NULL;
    return stack;
}

/**
 * @fn stack_t stack_push(stack_t, void*)
 * @brief
 *
 * @param stack
 * @param data
 * @return
 */
stack_t stack_push(stack_t stack, void *data) {
    stack_node_t *node = (struct stack_node_t*) malloc(sizeof(struct stack_node_t));
    if (node == NULL)
        return NULL;
    node->data = data;

    node->next = stack->top;
    stack->top = node;

    stack->length++;
    return stack;
}

void* stack_pop(stack_t stack) {
    stack_node_t *current = stack->top;
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
    stack_node_t *current, *next;
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

#endif
