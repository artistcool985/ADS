#include <stdio.h>
#include <stdlib.h>

// Definition of a node in the binary tree
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Structure to represent a node and its state for inorder traversal
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

// Function to perform inorder traversal of the BST
void inorderTraversal(struct Node* root) {
    struct StackNode* stack = NULL;
    struct Node* current = root;

    while (current != NULL || !isEmpty(stack)) {
        while (current != NULL) {
            push(&stack, current);
            current = current->left;
        }
        
        current = pop(&stack);
        printf("%d ", current->data);
        current = current->right;
    }
}

// Function to count leaf nodes
int countLeafNodes(struct Node* root) {
    if (root == NULL) return 0;

    int count = 0;
    struct StackNode* stack = NULL;
    struct Node* current = root;

    while (current != NULL || !isEmpty(stack)) {
        while (current != NULL) {
            push(&stack, current);
            current = current->left;
        }
        
        current = pop(&stack);
        if (current->left == NULL && current->right == NULL) {
            count++;
        }
        current = current->right;
    }

    return count;
}

// Function to get the mirror image of the binary tree
void mirrorImage(struct Node* root) {
    if (root == NULL) return;

    struct StackNode* stack = NULL;
    struct Node* current = root;

    while (current != NULL || !isEmpty(stack)) {
        while (current != NULL) {
            push(&stack, current);
            current = current->left;
        }
        
        current = pop(&stack);

        // Swap left and right children
        struct Node* tempNode = current->left;
        current->left = current->right;
        current->right = tempNode;

        current = current->right;
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

    // Inorder Traversal
    printf("Inorder Traversal: ");
    inorderTraversal(root);
    printf("\n");

    // Display Number of Leaf Nodes
    printf("Number of Leaf Nodes: %d\n", countLeafNodes(root));

    // Mirror Image
    mirrorImage(root);
    printf("Mirror Image: ");
    inorderTraversal(root);
    printf("\n");

    return 0;
}
