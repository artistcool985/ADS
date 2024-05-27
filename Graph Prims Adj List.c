#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Structure for a node in adjacency list
struct Node {
    int dest;
    int weight;
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
struct Node* createNode(int dest, int weight) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode) {
        newNode->dest = dest;
        newNode->weight = weight;
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
void addEdge(struct Graph* graph, int src, int dest, int weight) {
    struct Node* newNode = createNode(dest, weight);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;

    newNode = createNode(src, weight);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}

// Function to find the vertex with minimum key value
int minKey(int key[], int mstSet[], int numVertices) {
    int min = INT_MAX, min_index;
    for (int v = 0; v < numVertices; ++v) {
        if (!mstSet[v] && key[v] < min) {
            min = key[v];
            min_index = v;
        }
    }
    return min_index;
}

// Function to print the constructed MST stored in parent array
void printMST(int parent[], struct Graph* graph) {
    printf("Edge   Weight\n");
    for (int i = 1; i < graph->numVertices; ++i) {
        printf("%d - %d    %d \n", parent[i], i, graph->array[i].head->weight);
    }
}

// Function to implement Prim's algorithm to find the minimum spanning tree
void primMST(struct Graph* graph) {
    int parent[graph->numVertices]; // Array to store constructed MST
    int key[graph->numVertices];    // Key values used to pick minimum weight edge in cut
    int mstSet[graph->numVertices]; // To represent set of vertices not yet included in MST

    // Initialize all keys as INFINITE
    for (int i = 0; i < graph->numVertices; ++i) {
        key[i] = INT_MAX;
        mstSet[i] = 0;
    }

    // Always include first vertex in MST
    key[0] = 0;
    parent[0] = -1; // First node is always root of MST

    // The MST will have (numVertices - 1) edges
    for (int count = 0; count < graph->numVertices - 1; ++count) {
        // Pick the minimum key vertex from the set of vertices not yet included in MST
        int u = minKey(key, mstSet, graph->numVertices);
        mstSet[u] = 1; // Add the picked vertex to the MST set

        // Update key value and parent index of the adjacent vertices of the picked vertex.
        // Consider only those vertices which are not yet included in MST
        struct Node* temp = graph->array[u].head;
        while (temp) {
            int v = temp->dest;
            if (!mstSet[v] && temp->weight < key[v]) {
                parent[v] = u;
                key[v] = temp->weight;
            }
            temp = temp->next;
        }
    }

    // Print the constructed MST
    printMST(parent, graph);
}

int main() {
    // Create a graph with 5 vertices
    struct Graph* graph = createGraph(5);

    // Add edges to the graph
    addEdge(graph, 0, 1, 2);
    addEdge(graph, 0, 3, 6);
    addEdge(graph, 1, 2, 3);
    addEdge(graph, 1, 3, 8);
    addEdge(graph, 1, 4, 5);
    addEdge(graph, 2, 4, 7);
    addEdge(graph, 3, 4, 9);

    // Find and print the minimum spanning tree using Prim's algorithm
    printf("Minimum Spanning Tree using Prim's Algorithm:\n");
    primMST(graph);

    return 0;
}
