#include <stdio.h>
#include <stdlib.h>

typedef int elem_t;

typedef struct tagNode {
    elem_t data;
    struct tagNode *prev_node;
    struct tagNode *next_node;
} Node;

// CreateNode, DestoryNode : 노드를 메모리에서 삭제함
// AppendNode
// GetNodeAt
// RemoveNode : 리스트에서 노드를 제외함
// InsertAfter, InsertNewHead

Node *create_node(elem_t data) {
    Node *new_node = (Node *)malloc(sizeof(Node));

    new_node->data = data;
    new_node->prev_node = NULL;
    new_node->next_node = NULL;

    return new_node;
}

void destroy_node(Node *node) {
    free(node);
}

void append_node(Node **restrict head, Node *restrict node) {
    if ((*head) == NULL) {
        *head = node;
        (*head)->next_node = *head;
        (*head)->prev_node = *head;
        return;
    }
    Node *tail = (*head)->prev_node;

    tail->next_node->prev_node = node;
    tail->next_node = node;

    node->next_node = *head;
    node->prev_node = tail;
}

Node *get_node_at(Node *head, size_t index) {
    Node *current = head;

    for (size_t i = 0; i < index; i++) {
        if (current == NULL)
            return NULL;
        current = current->next_node;
    }
    return current;
}

void remove_node(Node **head, Node *remove) {
    if (*head == remove) {
        (*head)->prev_node->next_node = remove->next_node;
        (*head)->next_node->prev_node = remove->prev_node;

        *head = remove->next_node;
    }
    else {
        remove->prev_node->next_node = remove->next_node;
        remove->next_node->prev_node = remove->prev_node;
    }
    remove->prev_node = NULL;
    remove->next_node = NULL;
}

void insert_after(Node *current, Node *new) {
    new->next_node = current->next_node;
    new->prev_node = current;

    if (new->next_node != NULL) {
        current->next_node->prev_node = new;
        current->next_node = new;
    }
}

void insert_new_head(Node **head, Node *new) {
    if (*head == NULL) {
        *head = new;
        return;
    }
    new->next_node = *head;
    *head = new;
}

size_t get_node_count(Node *head) {
    size_t cnt = 0;
    for (Node *current = head; current != NULL;) {
        current = current->next_node;
        cnt++;

        if (current == head)
            break;
    }
    return cnt;
}

void print_node(Node *node) {
    if (node->prev_node == NULL)
        printf("Prev: NULL");
    else
        printf("Prev: %d", node->prev_node->data);

    printf("Current: %d", node->data);

    if (node->next_node == NULL)
        printf("Next: NULL\n");
    else
        printf("Next: %d\n", node->next_node->data);
}

int main() {
    int cnt = 0;
    Node *list = NULL;
    Node *current = NULL;
    Node *new_node = NULL;

    for (int i = 0; i < 5; i++) {
        new_node = create_node(i);
        append_node(&list, new_node);
    }

    cnt = get_node_count(list);
    for (int i = 0; i < cnt; i++) {
        current = get_node_at(list, i);
        printf("List[%d] : %d\n", i, current->data);
    }

    printf("\nInserting 3000 after [2]....\n\n");

    current = get_node_at(list, 2);
    new_node = create_node(3000);
    insert_after(current, new_node);

    printf("\nRemoving node at 2...\n");
    current = get_node_at(list, 2);
    remove_node(&list, current);
    destroy_node(current);

    cnt = get_node_count(list);
    for (int i = 0; i < cnt * 2; i++) {
        if (i == 0)
            current = list;
        else
            current = current->next_node;

        printf("List[%d] : %d\n", i, current->data);
    }

    printf("\nDestorying List...\n");

    for (int i = 0; i < cnt; i++) {
        current = get_node_at(list, 0);

        if (current != NULL) {
            remove_node(&list, current);
            destroy_node(current);
        }
    }

    return 0;
}