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

// Function to find the minimum key in the BST
struct Node* minValueNode(struct Node* node) {
    struct Node* current = node;

    while (current && current->left != NULL) {
        current = current->left;
    }

    return current;
}

// Function to delete a key from the BST
struct Node* deleteNode(struct Node* root, int key) {
    if (root == NULL) {
        return root;
    }

    if (key < root->key) {
        root->left = deleteNode(root->left, key);
    } else if (key > root->key) {
        root->right = deleteNode(root->right, key);
    } else {
        if (root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }

        struct Node* temp = minValueNode(root->right);
        root->key = temp->key;
        root->right = deleteNode(root->right, temp->key);
    }

    return root;
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

// Function to perform level-wise display of BST
void levelOrderTraversal(struct Node* root) {
    if (root == NULL) return;

    struct Node* queue[100];
    int front = 0, rear = -1;
    queue[++rear] = root;

    while (front <= rear) {
        struct Node* current = queue[front++];
        printf("%d ", current->key);

        if (current->left) {
            queue[++rear] = current->left;
        }
        if (current->right) {
            queue[++rear] = current->right;
        }
    }
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
    levelOrderTraversal(root);
    printf("\n");

    int keyToDelete = 20;
    root = deleteNode(root, keyToDelete);
    printf("BST after deleting key %d: ", keyToDelete);
    levelOrderTraversal(root);
    printf("\n");

    int keyToFind = 40;
    struct Node* foundNode = find(root, keyToFind);
    if (foundNode != NULL) {
        printf("Key %d found in the BST\n", keyToFind);
    } else {
        printf("Key %d not found in the BST\n", keyToFind);
    }

    return 0;
}
