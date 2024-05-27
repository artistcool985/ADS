#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 6

// Function to perform Breadth-First Search (BFS) traversal on the graph
void BFS(int adjMatrix[MAX_VERTICES][MAX_VERTICES], int startVertex) {
    // Array to keep track of visited vertices
    int visited[MAX_VERTICES] = {0};

    // Queue for BFS traversal
    int queue[MAX_VERTICES];
    int front = 0, rear = -1;

    // Mark the start vertex as visited and enqueue it
    visited[startVertex] = 1;
    queue[++rear] = startVertex;

    // Perform BFS traversal
    while (front <= rear) {
        // Dequeue a vertex from the queue and print it
        int currentVertex = queue[front++];
        printf("%d ", currentVertex);

        // Visit all adjacent vertices of the dequeued vertex
        for (int i = 0; i < MAX_VERTICES; i++) {
            if (adjMatrix[currentVertex][i] && !visited[i]) {
                // Mark the adjacent vertex as visited and enqueue it
                visited[i] = 1;
                queue[++rear] = i;
            }
        }
    }
}

int main() {
    // Sample adjacency matrix representing a graph
    int adjMatrix[MAX_VERTICES][MAX_VERTICES] = {
        {0, 1, 1, 0, 0, 0},
        {1, 0, 0, 1, 0, 0},
        {1, 0, 0, 1, 1, 0},
        {0, 1, 1, 0, 0, 1},
        {0, 0, 1, 0, 0, 1},
        {0, 0, 0, 1, 1, 0}
    };

    // Print the adjacency matrix
    printf("Adjacency Matrix:\n");
    for (int i = 0; i < MAX_VERTICES; i++) {
        for (int j = 0; j < MAX_VERTICES; j++) {
            printf("%d ", adjMatrix[i][j]);
        }
        printf("\n");
    }

    // Perform BFS traversal starting from vertex 0
    printf("\nBFS Traversal starting from vertex 0: ");
    BFS(adjMatrix, 0);

    return 0;
}
