#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tagNode {
    char *data;
    struct tagNode *next_node;
} Node;

typedef struct {
    Node *front;
    Node *rear;
    int count;
} Queue;

void create_queue(Queue **q) {
    *q = (Queue *)malloc(sizeof(Queue));
    (*q)->front = NULL;
    (*q)->rear = NULL;
    (*q)->count = 0;
}

Node *create_node(const char *str) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = (char *)malloc(strlen(str) + 1);
    strcpy(node->data, str);
    node->next_node = NULL;
    return node;
}

void destroy_node(Node *node) {
    free(node->data);
    free(node);
}

void enqueue(Queue *q, Node *node) {
    if (q->front == NULL) {
        q->front = node;
        q->rear = node;
        q->count++;
    }
    else {
        q->rear->next_node = node;
        q->rear = node;
        q->count++;
    }
}

Node *dequeue(Queue *q) {
    Node *front = q->front;
    if (q->front->next_node == NULL) {
        q->front = NULL;
        q->rear = NULL;
    }
    else {
        q->front = q->front->next_node;
    }
    q->count--;
    return front;
}

_Bool is_empty(Queue *q) {
    return q->front == NULL;
}

void destroy_queue(Queue *q) {
    while (!is_empty(q)) {
        Node *popped = dequeue(q);
        destroy_node(popped);
    }
    free(q);
}

int main() {
    Queue *q;
    create_queue(&q);

    enqueue(q, create_node("abc"));
    enqueue(q, create_node("def"));
    enqueue(q, create_node("efg"));
    enqueue(q, create_node("hij"));

    printf("Queue size: %d\n", q->count);

    while (!is_empty(q)) {
        Node *popped = dequeue(q);
        printf("Dequeue: %s \n", popped->data);
        destroy_node(popped);
    }
    destroy_queue(q);
    return 0;
}