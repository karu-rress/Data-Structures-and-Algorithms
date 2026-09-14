#include <stdio.h>
#include <stdlib.h>

typedef int elem_t;

typedef struct tagNode {
    elem_t data;
} Node;

typedef struct tagStack {
    int capacity;
    int top;
    Node *nodes;
} Stack;

void create_stack(Stack **stack, int capacity) {
    *stack = (Stack *)malloc(sizeof(Stack));
    (*stack)->nodes = (Node *)calloc(capacity, sizeof(Node));

    (*stack)->capacity = capacity;
    (*stack)->top = -1;
}

void destroy_stack(Stack *stack) {
    free(stack->nodes);
    stack->nodes = NULL;

    free(stack);
}

_Bool is_full(Stack *stack) {
    return stack->capacity == stack->top + 1;
}

_Bool is_empty(Stack *stack) {
    return stack->top == -1;
}

void push(Stack *stack, elem_t data) {
    if (is_full(stack)) {
        stack->nodes = (Node *)realloc(stack->nodes, stack->capacity * 1.3);
    }
    stack->nodes[++stack->top].data = data;
}

elem_t pop(Stack *stack) {
    if (is_empty(stack))
        return 0;

    if (get_size(stack) < stack->capacity * 0.7)
        stack->nodes = (Node *)realloc(stack->nodes, stack->capacity * 0.7);

    return stack->nodes[stack->top--].data;
}

elem_t top(Stack *stack) {
    return stack->nodes[stack->top].data;
}

int get_size(Stack *stack) {
    return stack->top + 1;
}

int main() {
    Stack *stack = NULL;

    create_stack(&stack, 10);

    push(stack, 3);
    push(stack, 37);
    push(stack, 11);
    push(stack, 12);

    printf("Capacity: %d, Size: %d, Top: %d\n\n", stack->capacity, get_size(stack), top(stack));

    for (int i = 0; i < 4; i++) {
        if (is_empty(stack))
            break;

        printf("Popped: %d, ", pop(stack));

        if (!is_empty(stack))
            printf("Current top: %d\n", top(stack));
        else
            puts("Stack is empty.");
    }

    destroy_stack(stack);

    return 0;
}