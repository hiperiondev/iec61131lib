/* https://github.com/LookCos/learn-data-structures */

#ifndef __STACK_H__
#define __STACK_H__

typedef struct stack_node {
    struct stack_node *next;
    void *data;
} stack_node;

typedef struct stack {
    struct stack_node *top;
    int length;
} *stack_t;

stack_t stack_create();
stack_t stack_push(stack_t stack, void *data);
  void* stack_pop(stack_t stack);
    int stack_size(stack_t stack);
   void stack_flush(stack_t stack);
   bool stack_empty(stack_t stack);
   void stack_release(stack_t stack);

#endif
