#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdbool.h>
#include <stdio.h>
#include "Utility.h"

/**
 * @struct Node
 * @brief Represents a node in the linked list.
 */
typedef struct Node {
    void* data;          /**< Pointer to the data stored in the node */
    struct Node* next;   /**< Pointer to the next node in the list */
} Node;

/**
 * @struct LinkedList
 * @brief Represents a linked list.
 */
typedef struct {
    Node* head;  /**< Pointer to the head node of the list */
    int size;    /**< Number of nodes in the list */
} LinkedList;

/**
 * @brief Creates a new linked list.
 * @return Pointer to the newly created linked list, or NULL if memory allocation fails.
 */
LinkedList* createLinkedList();

/**
 * @brief Inserts a new node with the given data at the beginning of the linked list.
 * @param list Pointer to the linked list.
 * @param data Pointer to the data to be stored in the new node.
 */
void insertNode(LinkedList* list, void* data);

/**
 * @brief Deletes the first occurrence of a node with the given data from the linked list.
 * @param list Pointer to the linked list.
 * @param data Pointer to the data to be deleted.
 * @return true if a node was deleted, false otherwise.
 */
bool deleteNode(LinkedList* list, void* data);

/**
 * @brief Frees the memory allocated for the linked list and its nodes.
 * @param list Pointer to the linked list.
 * @note This function assumes that the data stored in the nodes does not require any special deallocation.
 */
void freeLinkedList(LinkedList* list);

/**
 * @brief Displays the data stored in each node of the linked list.
 * @param list Pointer to the linked list.
 * @param printData Function pointer to a function that prints the data stored in a node.
 */
void displayLinkedList(LinkedList* list, void (*printData)(void*));


#endif // LINKEDLIST_H