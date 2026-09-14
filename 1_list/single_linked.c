#include <stdio.h>
#include <stdlib.h>

typedef int elem_t;

typedef struct tagNode {
    elem_t data;
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
    new_node->next_node = NULL;

    return new_node;
}

void destroy_node(Node *node) {
    free(node);
}

void append_node(Node **restrict head, Node *restrict node) {
    if ((*head) == NULL) {
        *head = node;
        return;
    }
    Node *tail = *head;
    while (tail->next_node != NULL)
        tail = tail->next_node;

    tail->next_node = node;
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
        *head = remove->next_node;
        return;
    }
    Node *current = *head;
    while (current != NULL && current->next_node != remove)
        current = current->next_node;

    if (current != NULL)
        current->next_node = remove->next_node;
}

void insert_after(Node *current, Node *new) {
    new->next_node = current->next_node;
    current->next_node = new;
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
    for (Node *current = head; current != NULL; current = current->next_node) {
        cnt++;
    }
    return cnt;
}

void print_node(Node *head) {
    Node *current = NULL;

    int cnt = get_node_count(head);
    for (int i = 0; i < cnt; i++) {
        current = get_node_at(head, i);
        printf("list[%d] : %d\n", i, current->data);
    }
}

void insert_before(Node **head, Node *current, Node *new_node) {
    if (*head == NULL) {
        *head = new_node;
        return;
    }

    if (*head == current) {
        new_node->next_node = *head;
        *head = new_node;
        return;
    }

    Node *prev = *head;
    while (prev != NULL && prev->next_node != current)
        prev = prev->next_node;

    if (prev != NULL) {
        new_node->next_node = current;
        prev->next_node = new_node;
    }
}

void destory_all_nodes(Node **list) {
    Node *current = *list;
    while (current != NULL) {
        Node *tmp = current;
        current = current->next_node;
        destroy_node(tmp);
    }
    *list = NULL;
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

    new_node = create_node(-1);
    insert_new_head(&list, new_node);

    print_node(list);

    printf("\nInserting 3000 after [2]....\n\n");

    current = get_node_at(list, 2);
    new_node = create_node(3000);
    insert_after(current, new_node);

    print_node(list);

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