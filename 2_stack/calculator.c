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

typedef enum {
    LEFT_PARENTHESIS = '(',
    RIGHT_PARENTHESIS = ')',
    PLUS = '+',
    MINUS = '-',
    MULTIPLY = '*',
    DEVIDE = '/',
    SPACE = ' ',
    OPERAND
} SYMBOL;

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

_Bool is_number(char cipher) {
    static char number[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '.' };
    for (int i = 0; i < sizeof number; i++) {
        if (cipher == number[i])
            return 1;
    }
    return 0;
}

unsigned int get_next_token(const char *expr, char *token, int *type) {
    unsigned int i;
    for (i = 0; expr[i] != '\0'; i++) {
        token[i] = expr[i];
        if (is_number(expr[i])) {
            *type = OPERAND;
            if (!is_number(expr[i + 1]))
                break;
        }
        else {
            *type = expr[i];
            break;
        }
    }
    token[++i] = '\0';
    return i;
}

int get_priority(char op, int in_stack) {
    int priority = -1;
    switch (op) {
    case LEFT_PARENTHESIS:
        if (in_stack)
            priority = 3;
        else
            priority = 0;
        break;

    case MULTIPLY:
    case DEVIDE:
        priority = 1;
        break;

    case PLUS:
    case MINUS:
        priority = 2;
        break;
    }
    return priority;
}

_Bool is_prior(char op_in_stack, char op_in_token) {
    return (get_priority(op_in_stack, 1) > get_priority(op_in_token, 0));
}

void get_postfix(const char *infix, char *postfix) {
    Stack *stack;

    char token[32];
    int type = -1;
    unsigned int pos = 0;
    unsigned int length = strlen(infix);

    create_stack(&stack);

    while (pos < length) {
        pos += get_next_token(&infix[pos], token, &type);
        if (type == OPERAND) {
            strcat(postfix, token);
            strcat(postfix, " ");
        }
        else if (type == RIGHT_PARENTHESIS) {
            while (!is_empty(stack)) {
                Node *popped = pop(stack);

                if (popped->data[0] == LEFT_PARENTHESIS) {
                    destroy_node(popped);
                    break;
                }
                else {
                    strcat(postfix, popped->data);
                    destroy_node(popped);
                }
            }
        }
        else {
            while (!is_empty(stack) && !is_prior(top(stack)->data[0], token[0])) {
                Node *popped = pop(stack);

                if (popped->data[0] != LEFT_PARENTHESIS)
                    strcat(postfix, popped->data);

                destroy_node(popped);
            }
            push(stack, create_node(token));
        }
    }

    while (!is_empty(stack)) {
        Node *popped = pop(stack);
        if (popped->data[0] != LEFT_PARENTHESIS)
            strcat(postfix, popped->data);
        destroy_node(popped);
    }
    destroy_stack(stack);
}

double calculate(const char *postfix) {
    Stack *stack;
    Node *result_node;

    double result;
    char token[32];
    int type = -1;
    unsigned int read = 0;
    unsigned int length = strlen(postfix);

    create_stack(&stack);

    while (read < length) {
        read += get_next_token(&postfix[read], token, &type);

        if (type == SPACE)
            continue;

        if (type == OPERAND) {
            Node *node = create_node(token);
            push(stack, node);
        }
        else {
            char result_str[32];
            double op1, op2, tmp;
            Node *op_node;

            op_node = pop(stack);
            op2 = atof(op_node->data);
            destroy_node(op_node);

            op_node = pop(stack);
            op1 = atof(op_node->data);
            destroy_node(op_node);

            switch (type) {
            case PLUS:
                tmp = op1 + op2;
                break;
            case MINUS:
                tmp = op1 - op2;
                break;
            case MULTIPLY:
                tmp = op1 * op2;
                break;
            case DEVIDE:
                tmp = op1 / op2;
                break;
            }

            sprintf(result_str, "%f", tmp);
            push(stack, create_node(result_str));
        }
    }

    result_node = pop(stack);
    result = atof(result_node->data);
    destroy_node(result_node);
    destroy_stack(stack);

    return result;
}

int main() {
    char infix[100] = "";
    char postfix[100] = "";

    double result = 0.0;

    memset(infix, '\0', sizeof infix);
    memset(postfix, '\0', sizeof postfix);

    printf("Enter infix expression: ");
    scanf("%s", infix);

    get_postfix(infix, postfix);
    printf("infix: %s\npostfix: %s\n", infix, postfix);
    result = calculate(postfix);

    printf("Result: %f\n", result);
    return 0;
}