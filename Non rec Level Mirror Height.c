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

// Function to perform level-wise display
void levelOrderTraversal(struct Node* root) {
    if (root == NULL) return;

    struct Node* queue[100];
    int front = 0, rear = -1;
    queue[++rear] = root;

    while (front <= rear) {
        struct Node* current = queue[front++];
        printf("%d ", current->data);

        if (current->left) {
            queue[++rear] = current->left;
        }
        if (current->right) {
            queue[++rear] = current->right;
        }
    }
}

// Function to get the mirror image of the binary tree
void mirrorImage(struct Node* root) {
    if (root == NULL) return;

    struct Node* queue[100];
    int front = 0, rear = -1;
    queue[++rear] = root;

    while (front <= rear) {
        struct Node* current = queue[front++];
        struct Node* temp = current->left;
        current->left = current->right;
        current->right = temp;

        if (current->left) {
            queue[++rear] = current->left;
        }
        if (current->right) {
            queue[++rear] = current->right;
        }
    }
}

// Function to calculate height of the tree non-recursively
int treeHeight(struct Node* root) {
    if (root == NULL) return 0;

    struct Node* queue[100];
    int front = 0, rear = -1;
    queue[++rear] = root;
    int height = 0;

    while (1) {
        int nodeCount = rear - front + 1;
        if (nodeCount == 0) break;
        height++;

        while (nodeCount > 0) {
            struct Node* current = queue[front++];
            if (current->left) {
                queue[++rear] = current->left;
            }
            if (current->right) {
                queue[++rear] = current->right;
            }
            nodeCount--;
        }
    }

    return height;
}

int main() {
    struct Node* root = createSampleTree();

    printf("Levelwise Display: ");
    levelOrderTraversal(root);
    printf("\n");

    printf("Mirror Image: ");
    mirrorImage(root);
    levelOrderTraversal(root);
    printf("\n");

    int height = treeHeight(root);
    printf("Height of Tree: %d\n", height);

    return 0;
}
