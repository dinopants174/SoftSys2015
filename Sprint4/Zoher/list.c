/* Example code for Software Systems at Olin College.
Based on an example from http://www.learn-c.org/en/Linked_lists
Copyright 2014 Allen Downey
License: Creative Commons Attribution-ShareAlike 3.0
*/

#include <stdio.h>
#include <stdlib.h>
#include "minunit.h"

typedef struct node {
    int val;
    struct node *next;
} Node;

Node *make_node(int val, Node *next) {
    Node *node = malloc(sizeof(Node));
    node->val = val;
    node->next = next;
    return node;
}

void print_list(Node *head) {
    Node *current = head;

    while (current != NULL) {
        printf("%i\n", current->val);
        current = current->next;
    }
}

int pop(Node **head) {
    int retval;
    Node *next_node;

    if (*head == NULL) {
        return -1;
    }

    next_node = (*head)->next;
    retval = (*head)->val;
    free(*head);
    *head = next_node;

    return retval;
}

int pop_modified(Node **head) {
    int retval;
    Node *next_node;
    Node *first = *head;

    if (first == NULL) {
        return -1;
    }

    next_node = (first)->next;
    retval = (first)->val;
    free(first);
    *head = next_node;

    return retval;
}

static char * test_pop_modified(**head) {
    mu_assert("error, pop_modified is not working", pop_modified(head) == 1);
    return 0;
}

// Add a new element to the beginning of the list.
void push(Node **head, int val) {
    // FILL THIS IN!
    Node *new_head = make_node(val, *head);
    *head = new_head;
}

// Remove the first element with the given value; return the number
// of nodes removed.
int remove_by_value(Node **head, int val) {
    // FILL THIS IN!
    int count = 0;
    Node *i = *head;
    Node *remove_node;

    if (i == NULL){
        return -1;
    }

    if (i -> val == val){
        pop(head);
        count++;
    }

    for (; i->next != NULL; i = i -> next){
        if (i -> next -> val == val){
            remove_node = i -> next;
            i -> next = remove_node -> next;
            free(remove_node);
            count++;
        }
    }

    return count;
}

static char * test_remove_by_value(**head){
    mu_assert("error, remove_by_value is not working", remove_by_value(head, 2) == 1);
    return 0;
}

// Reverse the elements of the list without allocating new nodes.
void reverse(Node **head) {
    // FILL THIS IN!
    Node *current_node = *head;
    Node *next_node, *temp;

    next_node = current_node -> next;
    current_node -> next = NULL;

    while (next_node != NULL){
        temp = next_node -> next;
        next_node -> next = current_node;
        current_node = next_node;
        next_node = temp;
    }
    *head = current_node;
}

//find middle element of linked list on pass through once
void find_middle(Node *head){
    Node *speedone = head;
    Node *speedhalf = head;
    int count = 0;
    for (; speedone->next != NULL; speedone = speedone -> next){
        count++;
        if (count == 2){
        speedhalf = speedhalf -> next;
        count = 0;
        }
    }
    printf("%i\n", speedhalf->val);
}

int main() {
    Node *test_list = make_node(1, NULL);
    test_list->next = make_node(2, NULL);
    test_list->next->next = make_node(3, NULL);
    test_list->next->next->next = make_node(4, NULL);
    test_list->next->next->next->next = make_node(5, NULL);

    char *result = test_pop_modified(&test_list);
    char *result2 = test_remove_by_value(&test_list);
    // result will be the failed test message if a test fails
    if (result || result2 != 0) {
        printf("%s\n", result);
    }
    else {
        printf("ALL TESTS PASSED\n");
    }

    return 0;

    // int retval = pop_modified(&test_list);

    // push(&test_list, retval+10);

    // remove_by_value(&test_list, 3);
    // remove_by_value(&test_list, 7);

    // reverse(&test_list);

    // print_list(test_list);
}
