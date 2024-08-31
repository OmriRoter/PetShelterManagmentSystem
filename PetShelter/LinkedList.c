#include "LinkedList.h"
#include <stdio.h>
#include <stdlib.h>

LinkedList* createLinkedList() {
    LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList));
    CHECK_ALLOCATION(list);  
    if (list == NULL) {
        printf("Failed to allocate memory for LinkedList.\n");
        return NULL;
    }
    list->head = NULL;
    list->size = 0;
    return list;
}

void insertNode(LinkedList* list, void* data) {
    if (list == NULL) return;

    Node* newNode = (Node*)malloc(sizeof(Node));
    CHECK_ALLOCATION(newNode);  


    newNode->data = data;
    newNode->next = list->head;
    list->head = newNode;
    list->size++;
}

bool deleteNode(LinkedList* list, void* data) {
    // This is a simplified version that assumes the data can be compared directly
    // and doesn't require a specialized comparison function. It also deletes the first occurrence.
    if (list == NULL || list->head == NULL) return false;

    Node* temp = list->head;
    Node* prev = NULL;

    while (temp != NULL) {
        if (temp->data == data) {
            if (prev == NULL) {
                list->head = temp->next;
            }
            else {
                prev->next = temp->next;
            }
            free(temp);
            list->size--;
            return true;
        }
        prev = temp;
        temp = temp->next;
    }
    return false;
}

void freeLinkedList(LinkedList* list) {
    if (list == NULL) return;

    Node* current = list->head;
    Node* next = NULL;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    free(list);
}

void displayLinkedList(LinkedList* list, void (*printData)(void*)) {
    if (list == NULL || printData == NULL) return;

    Node* current = list->head;
    while (current != NULL) {
        printData(current->data);
        current = current->next;
    }
}
