#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 10 // Maximum size of the array

// Structure to represent two queues in a single array
struct TwoQueues {
    int array[MAX_SIZE];
    int front1, rear1, front2, rear2;
};

// Function to create an empty structure for two queues
struct TwoQueues* createTwoQueues() {
    struct TwoQueues* queues = (struct TwoQueues*)malloc(sizeof(struct TwoQueues));
    queues->front1 = -1;
    queues->rear1 = -1;
    queues->front2 = MAX_SIZE;
    queues->rear2 = MAX_SIZE;
    return queues;
}

// Function to check if queue 1 is empty
int isEmptyQueue1(struct TwoQueues* queues) {
    return queues->front1 == -1;
}

// Function to check if queue 2 is empty
int isEmptyQueue2(struct TwoQueues* queues) {
    return queues->front2 == MAX_SIZE;
}

// Function to check if the array is full
int isFull(struct TwoQueues* queues) {
    return queues->rear1 + 1 == queues->rear2;
}

// Function to enqueue an element into queue 1
void enqueueQueue1(struct TwoQueues* queues, int item) {
    if (isFull(queues)) {
        printf("Queue 1 is full. Cannot enqueue.\n");
        return;
    }
    if (queues->front1 == -1) {
        queues->front1 = 0;
    }
    queues->array[++queues->rear1] = item;
    printf("%d enqueued to Queue 1.\n", item);
}

// Function to enqueue an element into queue 2
void enqueueQueue2(struct TwoQueues* queues, int item) {
    if (isFull(queues)) {
        printf("Queue 2 is full. Cannot enqueue.\n");
        return;
    }
    if (queues->front2 == MAX_SIZE) {
        queues->front2 = MAX_SIZE - 1;
    }
    queues->array[--queues->rear2] = item;
    printf("%d enqueued to Queue 2.\n", item);
}

// Function to dequeue an element from queue 1
int dequeueQueue1(struct TwoQueues* queues) {
    if (isEmptyQueue1(queues)) {
        printf("Queue 1 is empty. Cannot dequeue.\n");
        return -1;
    }
    int item = queues->array[queues->front1];
    if (queues->front1 == queues->rear1) {
        queues->front1 = queues->rear1 = -1; // Queue 1 becomes empty
    } else {
        queues->front1++;
    }
    return item;
}

// Function to dequeue an element from queue 2
int dequeueQueue2(struct TwoQueues* queues) {
    if (isEmptyQueue2(queues)) {
        printf("Queue 2 is empty. Cannot dequeue.\n");
        return -1;
    }
    int item = queues->array[queues->front2];
    if (queues->front2 == queues->rear2) {
        queues->front2 = queues->rear2 = MAX_SIZE; // Queue 2 becomes empty
    } else {
        queues->front2--;
    }
    return item;
}

// Function to display the elements of queue 1
void displayQueue1(struct TwoQueues* queues) {
    if (isEmptyQueue1(queues)) {
        printf("Queue 1 is empty.\n");
        return;
    }
    printf("Queue 1: ");
    for (int i = queues->front1; i <= queues->rear1; i++) {
        printf("%d ", queues->array[i]);
    }
    printf("\n");
}

// Function to display the elements of queue 2
void displayQueue2(struct TwoQueues* queues) {
    if (isEmptyQueue2(queues)) {
        printf("Queue 2 is empty.\n");
        return;
    }
    printf("Queue 2: ");
    for (int i = queues->front2; i >= queues->rear2; i--) {
        printf("%d ", queues->array[i]);
    }
    printf("\n");
}

int main() {
    struct TwoQueues* queues = createTwoQueues();

    // Static operations
    enqueueQueue1(queues, 10);
    enqueueQueue1(queues, 20);
    enqueueQueue1(queues, 30);

    enqueueQueue2(queues, 40);
    enqueueQueue2(queues, 50);
    enqueueQueue2(queues, 60);

    displayQueue1(queues);
    displayQueue2(queues);

    printf("Dequeued from Queue 1: %d\n", dequeueQueue1(queues));
    printf("Dequeued from Queue 2: %d\n", dequeueQueue2(queues));

    displayQueue1(queues);
    displayQueue2(queues);

    // Free allocated memory
    free(queues);

    return 0;
}
