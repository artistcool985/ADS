#include <stdio.h>
#include <stdlib.h>

// Definition of a node in the binary tree
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Function to create a sample binary tree
struct Node* createSampleTree() {
    struct Node* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);
    root->right->left = createNode(6);
    root->right->right = createNode(7);
    return root;
}

// Function to perform non-recursive Postorder Traversal
void postorderTraversal(struct Node* root) {
    if (root == NULL) return;

    struct Node* stack[100];
    int top = -1;
    struct Node* prev = NULL;

    do {
        while (root != NULL) {
            stack[++top] = root;
            root = root->left;
        }

        while (root == NULL && top != -1) {
            root = stack[top];
            if (root->right == NULL || root->right == prev) {
                printf("%d ", root->data);
                prev = root;
                top--;
                root = NULL;
            } else {
                root = root->right;
            }
        }
    } while (top != -1);
}

// Function to display leaf nodes
void displayLeafNodes(struct Node* root) {
    if (root == NULL) return;

    struct Node* stack[100];
    int top = -1;
    stack[++top] = root;

    while (top >= 0) {
        struct Node* current = stack[top--];

        if (current->left == NULL && current->right == NULL) {
            printf("%d ", current->data);
        }
        if (current->right) {
            stack[++top] = current->right;
        }
        if (current->left) {
            stack[++top] = current->left;
        }
    }
}

// Function to count total number of leaf nodes
int countLeafNodes(struct Node* root) {
    if (root == NULL) return 0;

    struct Node* stack[100];
    int top = -1;
    stack[++top] = root;
    int leafCount = 0;

    while (top >= 0) {
        struct Node* current = stack[top--];

        if (current->left == NULL && current->right == NULL) {
            leafCount++;
        }
        if (current->right) {
            stack[++top] = current->right;
        }
        if (current->left) {
            stack[++top] = current->left;
        }
    }

    return leafCount;
}

// Function to calculate height of the tree non-recursively
int treeHeight(struct Node* root) {
    if (root == NULL) return 0;

    struct Node* stack[100];
    int heights[100];
    int top = -1;
    stack[++top] = root;
    heights[top] = 1;
    int maxHeight = 0;

    while (top >= 0) {
        struct Node* current = stack[top];
        int currentHeight = heights[top--];

        if (current->left == NULL && current->right == NULL) {
            if (currentHeight > maxHeight) {
                maxHeight = currentHeight;
            }
        }
        if (current->right) {
            stack[++top] = current->right;
            heights[top] = currentHeight + 1;
        }
        if (current->left) {
            stack[++top] = current->left;
            heights[top] = currentHeight + 1;
        }
    }

    return maxHeight;
}

int main() {
    struct Node* root = createSampleTree();

    printf("Postorder Traversal: ");
    postorderTraversal(root);
    printf("\n");

    printf("Leaf Nodes: ");
    displayLeafNodes(root);
    printf("\n");

    int leafCount = countLeafNodes(root);
    printf("Total Leaf Nodes: %d\n", leafCount);

    int height = treeHeight(root);
    printf("Height of Tree: %d\n", height);

    return 0;
}
