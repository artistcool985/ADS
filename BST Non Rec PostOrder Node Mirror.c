#include <stdio.h>
#include <stdlib.h>

// Definition of a node in the binary tree
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Structure to represent a node and its state for postorder traversal
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

// Function to perform postorder traversal of the binary tree
void postorderTraversal(struct Node* root) {
    if (root == NULL) return;

    struct StackNode* stack1 = NULL;
    struct StackNode* stack2 = NULL;

    push(&stack1, root);
    while (!isEmpty(stack1)) {
        struct Node* current = pop(&stack1);
        push(&stack2, current);

        if (current->left) push(&stack1, current->left);
        if (current->right) push(&stack1, current->right);
    }

    while (!isEmpty(stack2)) {
        printf("%d ", pop(&stack2)->data);
    }
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

// Function to get the mirror image of the binary tree
void mirrorImage(struct Node* root) {
    if (root == NULL) return;

    struct StackNode* stack = NULL;
    push(&stack, root);

    while (!isEmpty(stack)) {
        struct Node* current = pop(&stack);

        struct Node* tempNode = current->left;
        current->left = current->right;
        current->right = tempNode;

        if (current->right) push(&stack, current->right);
        if (current->left) push(&stack, current->left);
    }
}

int main() {
    // Create sample binary tree
    struct Node* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);
    root->right->left = createNode(6);
    root->right->right = createNode(7);

    // Postorder Traversal
    printf("Postorder Traversal: ");
    postorderTraversal(root);
    printf("\n");

    // Display Leaf Nodes
    printf("Leaf Nodes: ");
    displayLeafNodes(root);
    printf("\n");

    // Mirror Image
    printf("Mirror Image: ");
    mirrorImage(root);
    postorderTraversal(root);
    printf("\n");

    return 0;
}
