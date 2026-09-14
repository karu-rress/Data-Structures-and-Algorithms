#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char *elem_t;

typedef struct tagNode {
    elem_t data;
    struct tagNode *next_node;
} Node;

typedef struct tagStack {
    Node *list;
    Node *top;
} Stack;

void create_stack(Stack **stack) {
    *stack = (Stack *)malloc(sizeof(Stack));
    (*stack)->list = NULL;
    (*stack)->top = NULL;
}

Node *create_node(const char *data) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = (char *)malloc(strlen(data) + 1);
    strcpy(node->data, data);

    node->next_node = NULL;
    return node;
}

void destroy_node(Node *node) {
    free(node->data);
    free(node);
}

_Bool is_empty(Stack *stack) {
    return stack->list == NULL;
}

void push(Stack *stack, Node *node) {
    if (stack->list == NULL) {
        stack->list = node;
    }
    else {
        stack->top->next_node = node;
    }
    stack->top = node;
}

Node *pop(Stack *stack) {
    Node *top = stack->top;

    if (stack->list == stack->top) {
        stack->list = NULL;
        stack->top = NULL;
    }
    else {
        Node *current = stack->list;
        while (current != NULL && current->next_node != stack->top) {
            current = current->next_node;
        }
        stack->top = current;
        stack->top->next_node = NULL;
    }
    return top;
}

Node *top(Stack *stack) {
    return stack->top;
}

int get_size(Stack *stack) {
    int cnt = 0;
    Node *current = stack->list;

    while (current != NULL) {
        current = current->next_node;
        cnt++;
    }
    return cnt;
}

void destroy_stack(Stack *stack) {
    while (!is_empty(stack)) {
        destroy_node(pop(stack));
    }
    free(stack);
}

int main() {
    Stack *stack = NULL;

    create_stack(&stack);

    push(stack, create_node("abc"));
    push(stack, create_node("def"));
    push(stack, create_node("efg"));
    push(stack, create_node("hij"));

    int cnt = get_size(stack);
    printf("Size: %d, top: %s\n\n", cnt, top(stack)->data);

    for (int i = 0; i < cnt; i++) {
        if (is_empty(stack))
            break;

        Node *popped = pop(stack);

        printf("Popped: %s, ", popped->data);

        destroy_node(popped);

        if (!is_empty(stack))
            printf("Current top: %s\n", top(stack)->data);
        else
            puts("Stack is empty.");
    }

    destroy_stack(stack);

    return 0;
}