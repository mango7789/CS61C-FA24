#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    char *data;
    struct Node *next;
};

void add_to_front(struct Node **head_ptr, char *data) {
    struct Node *node = (struct Node *)malloc(sizeof(struct Node));
    node->data = (char *)malloc(strlen(data) + 1);  // null-terminator
    strcpy(node->data, data);                       // copies null terminator as well
    node->next = *head_ptr;
    *head_ptr = node;
}

void print_list(struct Node *head) {
    for (struct Node *curr = head; curr != NULL; curr = curr->next) {
        printf("\"%s\" -> ", curr->data);
    }
    printf("NULL\n");
}

void free_list(struct Node *head) {
    while (head != NULL) {
        struct Node *temp = head->next;
        free(head->data);
        free(head);
        head = temp;
    }
}

int main() {
    struct Node *head = NULL;
    add_to_front(&head, "aaardvark");
    add_to_front(&head, "bat");
    add_to_front(&head, "cat");
    add_to_front(&head, "dog");

    print_list(head);

    free_list(head);
    return 0;
}