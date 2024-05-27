#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 6

// Structure for a node in linked list
struct Node {
    int data;
    struct Node* next;
};

// Structure for representing a stack
struct Stack {
    struct Node* top;
};

// Structure for representing a queue
struct Queue {
    struct Node* front;
    struct Node* rear;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode) {
        newNode->data = data;
        newNode->next = NULL;
    }
    return newNode;
}

// Function to create an empty stack
struct Stack* createStack() {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    if (stack) {
        stack->top = NULL;
    }
    return stack;
}

// Function to create an empty queue
struct Queue* createQueue() {
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    if (queue) {
        queue->front = queue->rear = NULL;
    }
    return queue;
}

// Function to push an element onto the stack
void push(struct Stack* stack, int data) {
    struct Node* newNode = createNode(data);
    if (newNode) {
        newNode->next = stack->top;
        stack->top = newNode;
    } else {
        printf("Memory allocation failed\n");
    }
}

// Function to pop an element from the stack
int pop(struct Stack* stack) {
    if (stack->top) {
        int data = stack->top->data;
        struct Node* temp = stack->top;
        stack->top = stack->top->next;
        free(temp);
        return data;
    } else {
        printf("Stack underflow\n");
        return -1;
    }
}

// Function to check if the stack is empty
int isEmptyStack(struct Stack* stack) {
    return stack->top == NULL;
}

// Function to enqueue an element into the queue
void enqueue(struct Queue* queue, int data) {
    struct Node* newNode = createNode(data);
    if (newNode) {
        if (queue->rear == NULL) {
            queue->front = queue->rear = newNode;
        } else {
            queue->rear->next = newNode;
            queue->rear = newNode;
        }
    } else {
        printf("Memory allocation failed\n");
    }
}

// Function to dequeue an element from the queue
int dequeue(struct Queue* queue) {
    if (queue->front) {
        int data = queue->front->data;
        struct Node* temp = queue->front;
        queue->front = queue->front->next;
        if (queue->front == NULL) {
            queue->rear = NULL;
        }
        free(temp);
        return data;
    } else {
        printf("Queue underflow\n");
        return -1;
    }
}

// Function to check if the queue is empty
int isEmptyQueue(struct Queue* queue) {
    return queue->front == NULL;
}

// Function to add an edge between two vertices in the adjacency matrix
void addEdge(int adjMatrix[MAX_VERTICES][MAX_VERTICES], int vertex1, int vertex2) {
    if (vertex1 >= 0 && vertex1 < MAX_VERTICES && vertex2 >= 0 && vertex2 < MAX_VERTICES) {
        adjMatrix[vertex1][vertex2] = 1;
        adjMatrix[vertex2][vertex1] = 1; // For undirected graph (remove this line for directed graph)
        printf("Edge added between vertices %d and %d\n", vertex1, vertex2);
    } else {
        printf("Invalid vertices\n");
    }
}

// Function to perform Depth First Search (DFS) traversal
void DFS(int adjMatrix[MAX_VERTICES][MAX_VERTICES], int startVertex) {
    struct Stack* stack = createStack();
    int visited[MAX_VERTICES] = {0};
    push(stack, startVertex);
    visited[startVertex] = 1;
    printf("DFS Traversal: ");
    while (!isEmptyStack(stack)) {
        int currentVertex = pop(stack);
        printf("%d ", currentVertex);
        for (int i = 0; i < MAX_VERTICES; i++) {
            if (adjMatrix[currentVertex][i] && !visited[i]) {
                push(stack, i);
                visited[i] = 1;
            }
        }
    }
    printf("\n");
    free(stack);
}

// Function to perform Breadth First Search (BFS) traversal
void BFS(int adjMatrix[MAX_VERTICES][MAX_VERTICES], int startVertex) {
    struct Queue* queue = createQueue();
    int visited[MAX_VERTICES] = {0};
    enqueue(queue, startVertex);
    visited[startVertex] = 1;
    printf("BFS Traversal: ");
    while (!isEmptyQueue(queue)) {
        int currentVertex = dequeue(queue);
        printf("%d ", currentVertex);
        for (int i = 0; i < MAX_VERTICES; i++) {
            if (adjMatrix[currentVertex][i] && !visited[i]) {
                enqueue(queue, i);
                visited[i] = 1;
            }
        }
    }
    printf("\n");
    free(queue);
}

int main() {
    int adjMatrix[MAX_VERTICES][MAX_VERTICES] = {0};

    // Add edges (hardcoded input)
    addEdge(adjMatrix, 0, 1);
    addEdge(adjMatrix, 0, 2);
    addEdge(adjMatrix, 1, 3);
    addEdge(adjMatrix, 2, 3);
    addEdge(adjMatrix, 2, 4);
    addEdge(adjMatrix, 3, 5);
    addEdge(adjMatrix, 4, 5);

    // Perform DFS and BFS traversal
    DFS(adjMatrix, 0);
    BFS(adjMatrix, 0);

    return 0;
}
