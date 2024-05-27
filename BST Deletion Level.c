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

// Function to perform non-recursive postorder traversal of the BST
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

// Function to find the minimum value node in a tree rooted at given node
struct Node* minValueNode(struct Node* node) {
    struct Node* current = node;

    // Loop down to find the leftmost leaf
    while (current && current->left != NULL)
        current = current->left;

    return current;
}

// Function to delete a node with given key from the BST
struct Node* deleteNode(struct Node* root, int key) {
    // Base case: if the tree is empty
    if (root == NULL) return root;

    // If the key to be deleted is smaller than the root's key, then it lies in the left subtree
    if (key < root->data)
        root->left = deleteNode(root->left, key);

    // If the key to be deleted is greater than the root's key, then it lies in the right subtree
    else if (key > root->data)
        root->right = deleteNode(root->right, key);

    // If the key is same as root's key, then this is the node to be deleted
    else {
        // Node with only one child or no child
        if (root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }

        // Node with two children: Get the inorder successor (smallest in the right subtree)
        struct Node* temp = minValueNode(root->right);

        // Copy the inorder successor's content to this node
        root->data = temp->data;

        // Delete the inorder successor
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

// Function to insert a new node with given key in BST
struct Node* insert(struct Node* node, int key) {
    // If the tree is empty, return a new node
    if (node == NULL) return createNode(key);

    // Otherwise, recur down the tree
    if (key < node->data)
        node->left = insert(node->left, key);
    else if (key > node->data)
        node->right = insert(node->right, key);

    // Return the (unchanged) node pointer
    return node;
}

// Function to display the BST in inorder
void inorder(struct Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

int main() {
    struct Node* root = NULL;

    // Insert nodes
    root = insert(root, 50);
    insert(root, 30);
    insert(root, 20);
    insert(root, 40);
    insert(root, 70);
    insert(root, 60);
    insert(root, 80);

    printf("BST before deletion:\n");
    inorder(root);
    printf("\n");

    // Delete node with key 20
    root = deleteNode(root, 20);
    printf("BST after deleting 20:\n");
    inorder(root);
    printf("\n");

    printf("Non-recursive postorder traversal:\n");
    postorderTraversal(root);
    printf("\n");

    return 0;
}
