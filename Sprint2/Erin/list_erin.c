/* Example code for Software Systems at Olin College.
Based on an example from http://www.learn-c.org/en/Linked_lists
Copyright 2014 Allen Downey
License: Creative Commons Attribution-ShareAlike 3.0
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int val;
    struct node * next;
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
        printf("%d\n", current->val);
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

// Add a new element to the beginning of the list.
void push(Node **head, int val) {
    Node *new=make_node(val,*head);
    *head=new;
}

// Remove the first element with the given value; return the number
// of nodes removed.
int remove_by_value(Node **head, int val) {
    int count=0;
   	Node *current=*head;

   	if (current == NULL) { // If there is not actually a list
   		return 0;
   	}

   	while (current->val == val) { // If the matches are at the start of the list
   		int retval=pop(head);
   		count += 1;
   		current=*head; //try the new start value
   	}
    while (current->next != NULL) { // If the matches are in the middle/end
    	if (current->next->val == val) {
    		int retval=pop(&(current->next));
    		count += 1;
    	}
    	else{ // Because pop increments already
		current = current->next;
    	}
    }
    return count;
}

// // Reverse the elements of the list without allocating new nodes.
void reverse(Node **head) {
    // FILL THIS IN!
}


int main() {
    Node *test_list = make_node(1, NULL);
    test_list->next = make_node(1, NULL);
    test_list->next->next = make_node(3, NULL);
    test_list->next->next->next = make_node(1, NULL);
    test_list->next->next->next->next = make_node(1, NULL);

    int retval = pop(&test_list);
    push(&test_list, retval+00);
    print_list(test_list);
    int removed = remove_by_value(&test_list, 1);
    printf("Removed %i node(s) \n", removed);
    // remove_by_value(&test_list, 7);

    // reverse(&test_list);

    print_list(test_list);
}