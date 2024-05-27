#include <stdio.h>
#include <stdlib.h>

// Definition of a node in the BST
struct Node {
    int key;
    struct Node* left;
    struct Node* right;
};

// Function to create a new node
struct Node* createNode(int key) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->key = key;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Function to insert a key into the BST
struct Node* insert(struct Node* root, int key) {
    if (root == NULL) {
        return createNode(key);
    }

    if (key < root->key) {
        root->left = insert(root->left, key);
    } else if (key > root->key) {
        root->right = insert(root->right, key);
    }

    return root;
}

// Function to perform inorder traversal of the BST
void inorderTraversal(struct Node* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%d ", root->key);
        inorderTraversal(root->right);
    }
}

// Function to get the mirror image of the binary tree
void mirrorImage(struct Node* root) {
    if (root == NULL) return;

    struct Node* temp = root->left;
    root->left = root->right;
    root->right = temp;

    mirrorImage(root->left);
    mirrorImage(root->right);
}

// Function to find a key in the BST
struct Node* find(struct Node* root, int key) {
    if (root == NULL || root->key == key) {
        return root;
    }

    if (key < root->key) {
        return find(root->left, key);
    }

    return find(root->right, key);
}

// Function to calculate height of the tree
int treeHeight(struct Node* root) {
    if (root == NULL) return 0;

    int leftHeight = treeHeight(root->left);
    int rightHeight = treeHeight(root->right);

    return (leftHeight > rightHeight) ? (leftHeight + 1) : (rightHeight + 1);
}

int main() {
    struct Node* root = NULL;

    // Static input for demonstration purposes
    root = insert(root, 50);
    insert(root, 30);
    insert(root, 20);
    insert(root, 40);
    insert(root, 70);
    insert(root, 60);
    insert(root, 80);

    printf("BST after insertion: ");
    inorderTraversal(root);
    printf("\n");

    printf("Mirror Image of BST: ");
    mirrorImage(root);
    inorderTraversal(root);
    printf("\n");

    int keyToFind = 40;
    struct Node* foundNode = find(root, keyToFind);
    if (foundNode != NULL) {
        printf("Key %d found in the BST\n", keyToFind);
    } else {
        printf("Key %d not found in the BST\n", keyToFind);
    }

    int height = treeHeight(root);
    printf("Height of Tree: %d\n", height);

    return 0;
}
