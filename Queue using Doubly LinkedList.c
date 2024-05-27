#include <stdio.h>
#include <stdlib.h>

// Node structure for the doubly linked list
struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (!newNode) {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

// Function to add an element to the queue (enqueue)
void enqueue(struct Node** head_ref, struct Node** tail_ref, int data) {
    struct Node* newNode = createNode(data);
    if (*tail_ref == NULL) { // If the queue is empty
        *head_ref = *tail_ref = newNode;
    } else {
        (*tail_ref)->next = newNode;
        newNode->prev = *tail_ref;
        *tail_ref = newNode;
    }
    printf("%d enqueued to the queue.\n", data);
}

// Function to delete an element from the queue (dequeue)
int dequeue(struct Node** head_ref, struct Node** tail_ref) {
    if (*head_ref == NULL) {
        printf("Queue underflow. Unable to dequeue.\n");
        return -1;
    }
    struct Node* temp = *head_ref;
    int dequeuedData = temp->data;
    *head_ref = temp->next;
    if (*head_ref != NULL) {
        (*head_ref)->prev = NULL;
    } else {
        *tail_ref = NULL;
    }
    free(temp);
    return dequeuedData;
}

// Function to display the queue
void displayQueue(struct Node* head) {
    if (head == NULL) {
        printf("Queue is empty.\n");
        return;
    }
    printf("Queue: ");
    while (head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

int main() {
    struct Node* head = NULL;
    struct Node* tail = NULL;

    // Enqueue elements to the queue
    enqueue(&head, &tail, 10);
    enqueue(&head, &tail, 20);
    enqueue(&head, &tail, 30);

    // Display the queue
    displayQueue(head);

    // Dequeue elements from the queue
    printf("Dequeued element: %d\n", dequeue(&head, &tail));
    printf("Dequeued element: %d\n", dequeue(&head, &tail));

    // Display the queue
    displayQueue(head);

    return 0;
}