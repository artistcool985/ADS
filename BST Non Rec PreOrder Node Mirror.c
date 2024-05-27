#include <stdio.h>
#include <stdlib.h>

// Definition of a node in the binary tree
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Structure to represent a node and its state for preorder traversal
struct StackNode {
    struct Node* node;
    struct StackNode* next;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Function to push a node onto the stack
void push(struct StackNode** top, struct Node* node) {
    struct StackNode* newNode = (struct StackNode*)malloc(sizeof(struct StackNode));
    newNode->node = node;
    newNode->next = *top;
    *top = newNode;
}

// Function to pop a node from the stack
struct Node* pop(struct StackNode** top) {
    if (*top == NULL) return NULL;
    struct StackNode* temp = *top;
    struct Node* poppedNode = temp->node;
    *top = (*top)->next;
    free(temp);
    return poppedNode;
}

// Function to check if the stack is empty
int isEmpty(struct StackNode* top) {
    return top == NULL;
}

// Function to perform preorder traversal of the BST
void preorderTraversal(struct Node* root) {
    if (root == NULL) return;

    struct StackNode* stack = NULL;
    push(&stack, root);

    while (!isEmpty(stack)) {
        struct Node* current = pop(&stack);
        printf("%d ", current->data);

        if (current->right) push(&stack, current->right);
        if (current->left) push(&stack, current->left);
    }
}

// Function to count total number of nodes in the BST
int countNodes(struct Node* root) {
    if (root == NULL) return 0;

    struct StackNode* stack = NULL;
    push(&stack, root);

    int count = 0;
    while (!isEmpty(stack)) {
        struct Node* current = pop(&stack);
        count++;

        if (current->right) push(&stack, current->right);
        if (current->left) push(&stack, current->left);
    }

    return count;
}

// Function to display leaf nodes
void displayLeafNodes(struct Node* root) {
    if (root == NULL) return;

    struct StackNode* stack = NULL;
    push(&stack, root);

    while (!isEmpty(stack)) {
        struct Node* current = pop(&stack);

        if (current->left == NULL && current->right == NULL) {
            printf("%d ", current->data);
        }

        if (current->right) push(&stack, current->right);
        if (current->left) push(&stack, current->left);
    }
}

int main() {
    // Create sample binary search tree
    struct Node* root = createNode(5);
    root->left = createNode(3);
    root->right = createNode(8);
    root->left->left = createNode(2);
    root->left->right = createNode(4);
    root->right->left = createNode(6);
    root->right->right = createNode(9);

    // Preorder Traversal
    printf("Preorder Traversal: ");
    preorderTraversal(root);
    printf("\n");

    // Display Total Number of Nodes
    printf("Total Number of Nodes: %d\n", countNodes(root));

    // Display Leaf Nodes
    printf("Leaf Nodes: ");
    displayLeafNodes(root);
    printf("\n");

    return 0;
}
