/**
 * @file util_stack.h
 * @brief simple generic stack
 * @copyright 2022 Emiliano Augusto Gonzalez (hiperiondev). This project is released under MIT license. Contact: egonzalez.hiperion@gmail.com
 * @see Project Site: https://github.com/hiperiondev/iec61131lib
 * @note This is based on other projects. Please contact their authors for more information.
 *
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#ifndef UTIL_STACK_H_
#define UTIL_STACK_H_

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
    struct stack_node_t *top;   /**< */
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

#endif /* UTIL_STACK_H_ */
