#include <stdio.h>
#include <stdlib.h>

typedef int elem_t;

typedef struct {
    elem_t data;
} Node;

typedef struct {
    int capacity;
    int front;
    int rear;
    Node *nodes;
} Queue;

void create_queue(Queue **q, int capacity) {
    *q = (Queue *)malloc(sizeof(Queue));
    (*q)->nodes = (Node *)calloc(capacity + 1, sizeof(Node));

    (*q)->capacity = capacity;
    (*q)->front = 0;
    (*q)->rear = 0;
}

void destroy_queue(Queue *q) {
    free(q->nodes);
    free(q);
}

void enqueue(Queue *q, elem_t data) {
    int pos = 0;
    if (q->rear == q->capacity) {
        pos = q->rear;
        q->rear = 0;
    }
    else
        pos = q->rear++;
    q->nodes[pos].data = data;
}

elem_t dequeue(Queue *q) {
    int pos = q->front;

    if (q->front == q->capacity)
        q->front = 0;
    else
        q->front++;
    return q->nodes[pos].data;
}

int get_size(const Queue *q) {
    if (q->front < q->rear)
        return q->rear - q->front;
    return q->capacity - q->front + q->rear + 1;
}

_Bool is_empty(const Queue *q) {
    return q->front == q->rear;
}

_Bool is_full(const Queue *q) {
    if (q->front < q->rear)
        return q->rear - q->front == q->capacity;
    return q->rear + 1 == q->front;
}

int main() {
    Queue *q;
    create_queue(&q, 10);
    enqueue(q, 1);
    enqueue(q, 2);
    enqueue(q, 3);
    enqueue(q, 4);

    for (int i = 0; i < 3; i++) {
        printf("Dequeue: %d, ", dequeue(q));
        printf("Front: %d, Rear: %d\n", q->front, q->rear);
    }

    for (int i = 100; !is_full(q); i++) {
        enqueue(q, i);
    }

    printf("Capacity: %d, Size: %d\n\n", q->capacity, get_size(q));

    while(!is_empty(q)) {
        printf("Dequeue: %d, ", dequeue(q));
        printf("Front: %d, Rear: %d\n", q->front, q->rear);
    }

    destroy_queue(q);

    return 0;
}