#include <stdio.h>
#include <stdlib.h>

// Structure for a node in adjacency list
struct Node {
    int vertex;
    struct Node* next;
};

// Structure for adjacency list
struct AdjList {
    struct Node* head;
};

// Structure for representing a graph
struct Graph {
    int numVertices;
    struct AdjList* array;
};

// Function to create a new node
struct Node* createNode(int vertex) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode) {
        newNode->vertex = vertex;
        newNode->next = NULL;
    }
    return newNode;
}

// Function to create a graph with given number of vertices
struct Graph* createGraph(int numVertices) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    if (graph) {
        graph->numVertices = numVertices;
        graph->array = (struct AdjList*)malloc(numVertices * sizeof(struct AdjList));
        for (int i = 0; i < numVertices; ++i) {
            graph->array[i].head = NULL;
        }
    }
    return graph;
}

// Function to add an edge to the graph
void addEdge(struct Graph* graph, int src, int dest) {
    struct Node* newNode = createNode(dest);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;

    // For undirected graph, add an edge from dest to src as well
    newNode = createNode(src);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}

// Function to perform Depth First Search (DFS) traversal
void DFSUtil(struct Graph* graph, int vertex, int visited[]) {
    visited[vertex] = 1;
    printf("%d ", vertex);

    struct Node* temp = graph->array[vertex].head;
    while (temp) {
        int adjVertex = temp->vertex;
        if (!visited[adjVertex]) {
            DFSUtil(graph, adjVertex, visited);
        }
        temp = temp->next;
    }
}

void DFS(struct Graph* graph, int startVertex) {
    int visited[graph->numVertices];
    for (int i = 0; i < graph->numVertices; ++i) {
        visited[i] = 0;
    }

    printf("DFS Traversal: ");
    DFSUtil(graph, startVertex, visited);
    printf("\n");
}

// Function to perform Breadth First Search (BFS) traversal
void BFS(struct Graph* graph, int startVertex) {
    int visited[graph->numVertices];
    for (int i = 0; i < graph->numVertices; ++i) {
        visited[i] = 0;
    }

    struct Node* queue[graph->numVertices];
    int front = 0, rear = 0;

    visited[startVertex] = 1;
    printf("BFS Traversal: ");
    printf("%d ", startVertex);
    queue[rear++] = graph->array[startVertex].head;

    while (front < rear) {
        struct Node* temp = queue[front++];
        while (temp) {
            int adjVertex = temp->vertex;
            if (!visited[adjVertex]) {
                visited[adjVertex] = 1;
                printf("%d ", adjVertex);
                queue[rear++] = graph->array[adjVertex].head;
            }
            temp = temp->next;
        }
    }
    printf("\n");
}

// Function to display the adjacency list representation of the graph
void displayGraph(struct Graph* graph) {
    printf("Adjacency List Representation:\n");
    for (int i = 0; i < graph->numVertices; ++i) {
        struct Node* temp = graph->array[i].head;
        printf("Vertex %d: ", i);
        while (temp) {
            printf("%d -> ", temp->vertex);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

int main() {
    // Create a graph with 5 vertices
    struct Graph* graph = createGraph(5);

    // Add edges
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 2, 4);
    addEdge(graph, 3, 4);

    displayGraph(graph);

    // Perform DFS starting from vertex 0
    DFS(graph, 0);

    // Perform BFS starting from vertex 0
    BFS(graph, 0);

    return 0;
}
