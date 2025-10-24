#include "list.h"
#include <stdlib.h>
// TODO: Include any necessary header files here

/**
 * Returns the head of the linked list.
 * 
 * @param head Pointer to the first node of the linked list.
 * @return The head of the linked list. If the list is empty (NULL), returns NULL.
 */
struct ll_node *ll_head(struct ll_node *head) {
    return head;
}

/**
 * Returns the tail of the linked list.
 * @param head pointer to the first node of the linked list.
 * @return the tail of the linked list. If the list is empty (NULL), returns NULL.
 */
struct ll_node *ll_tail(struct ll_node *head) {
    if (!head) return NULL;

    struct ll_node *current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    return current;
}
/**
 * Returns the number of nodes in the linked list.
 * @param head Pointer to the first node of the linked list.
 * @return Number of nodes in the list.
 */
int ll_size(struct ll_node *head) {
    int count = 0;
    struct ll_node *current = head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

/**
 * Finds the first node with the specified value.
 * @param head Pointer to the first node of the linked list.
 * @param value The value to search for.
 * @return Pointer to the node containing the value. Returns NULL if not found.
 */
struct ll_node *ll_find(struct ll_node *head, int value) {
    struct ll_node *current = head;
    while (current != NULL) {
        if (current->data == value) return current;
        current = current->next;
    }
    return NULL;
}

/**
 * Converts the linked list into a dynamically allocated array of ints.
 * @param head Pointer to the first node of the linked list.
 * @return Pointer to a malloc'd array containing the node data. Returns NULL if the list is empty.
 */
int *ll_toarray(struct ll_node *head) {
    int size = ll_size(head);
    if (size == 0) return NULL;

    int *array = (int *)malloc(size * sizeof(int));
    if (!array) return NULL;

    struct ll_node *current = head;
    for (int i = 0; i < size; i++) {
        array[i] = current->data;
        current = current->next;
    }

    return array;
}

/**
 * Creates a new node with the given data.
 * @param data Integer value to store in the node.
 * @return Pointer to the newly created node. Returns NULL if malloc fails.
 */
struct ll_node *ll_create(int data) {
    struct ll_node *node = malloc(sizeof(struct ll_node));
    if (!node) return NULL;   // malloc failed
    node->data = data;
    node->next = NULL;
    return node;
}

/**
 * Frees all nodes in the linked list.
 * @param head Pointer to the first node of the linked list.
 */
void ll_destroy(struct ll_node *head) {
    struct ll_node *current = head;
    while (current != NULL) {
        struct ll_node *next = current->next;
        free(current);
        current = next;
    }
}

/**
 * Appends a new node with the given value to the tail of the list.
 * Assumes head is not NULL.
 * @param head Pointer to the first node of the linked list.
 * @param data Integer value to append.
 */
void ll_append(struct ll_node *head, int data) {
    if (!head) return;  // cannot append to NULL head

    struct ll_node *tail = head;
    while (tail->next != NULL) { // traverse to last node
        tail = tail->next;
    }
    tail->next = ll_create(data); // attach new node
}

/**
 * Creates a linked list from an array of integers.
 * @param data Pointer to the array of integers.
 * @param len Length of the array.
 * @return Pointer to the head of the newly created linked list. Returns NULL if len is 0 or data is NULL.
 */
struct ll_node *ll_fromarray(int* data, int len) {
    if (!data || len == 0) return NULL;

    struct ll_node *head = ll_create(data[0]);
    if (!head) return NULL;

    struct ll_node *tail = head;
    for (int i = 1; i < len; i++) {
        tail->next = ll_create(data[i]);
        tail = tail->next;
    }
    return head;
}

/**
 * Removes the first node with the specified value from the list.
 * @param head Pointer to the first node of the linked list.
 * @param value The value to remove.
 * @return Pointer to the new head of the list. Returns NULL if the list becomes empty.
 */
struct ll_node *ll_remove(struct ll_node *head, int value) {
    if (!head) return NULL;

    // Remove head if it matches value
    if (head->data == value) {
        struct ll_node *new_head = head->next;
        free(head);
        return new_head;
    }

    struct ll_node *current = head;
    while (current->next != NULL) {
        if (current->next->data == value) {
            struct ll_node *to_remove = current->next;
            current->next = current->next->next;
            free(to_remove);
            break;  // remove only the first occurrence
        }
        current = current->next;
    }
    return head;
}
