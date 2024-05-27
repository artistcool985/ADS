#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to represent an employee record
struct Employee {
    int emp_id;
    char name[50];
    char department[50];
};

// Definition of a node in the binary search tree (BST)
struct Node {
    struct Employee data;
    struct Node *left, *right;
};

// Function to create a new node
struct Node* createNode(struct Employee emp) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = emp;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Function to insert a new node into the BST
struct Node* insert(struct Node* root, struct Employee emp) {
    // If the tree is empty, return a new node
    if (root == NULL) return createNode(emp);

    // Otherwise, recur down the tree
    if (emp.emp_id < root->data.emp_id)
        root->left = insert(root->left, emp);
    else if (emp.emp_id > root->data.emp_id)
        root->right = insert(root->right, emp);

    // Return the (unchanged) node pointer
    return root;
}

// Function to search for an employee record by emp_id
struct Node* search(struct Node* root, int emp_id) {
    // Base Cases: root is null or emp_id is present at root
    if (root == NULL || root->data.emp_id == emp_id)
        return root;

    // Emp_id is greater than root's key
    if (root->data.emp_id < emp_id)
        return search(root->right, emp_id);

    // Emp_id is smaller than root's key
    return search(root->left, emp_id);
}

// Function to perform inorder traversal of the BST
void inorder(struct Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("Emp ID: %d, Name: %s, Department: %s\n", root->data.emp_id, root->data.name, root->data.department);
        inorder(root->right);
    }
}

int main() {
    // Sample employee records
    struct Employee employees[] = {
        {103, "Alice Johnson", "Finance"},
        {105, "Eva Lee", "Operations"},
        {101, "John Doe", "HR"},
        {104, "Bob Brown", "Marketing"},
        {102, "Jane Smith", "IT"}
    };

    int n = sizeof(employees) / sizeof(employees[0]);

    // Initialize the root of the BST
    struct Node* root = NULL;

    // Insert employee records into the BST
    for (int i = 0; i < n; i++) {
        root = insert(root, employees[i]);
    }

    // Display sorted employee records (Inorder traversal)
    printf("Sorted Employee Records (Inorder Traversal):\n");
    inorder(root);

    // Search for an employee record by emp_id
    int search_id = 103;
    struct Node* found = search(root, search_id);
    if (found != NULL) {
        printf("\nEmployee Record with Emp ID %d Found:\n", search_id);
        printf("Emp ID: %d, Name: %s, Department: %s\n", found->data.emp_id, found->data.name, found->data.department);
    } else {
        printf("\nEmployee Record with Emp ID %d Not Found\n", search_id);
    }

    return 0;
}
