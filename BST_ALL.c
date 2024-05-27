#include <stdio.h>
#include <stdlib.h>

struct TreeNode
{
    int key;
    struct TreeNode *left;
    struct TreeNode *right;
};

typedef struct TreeNode TreeNode;

// Function to create a new node
TreeNode *createNode(int key)
{
    TreeNode *newNode = (TreeNode *)malloc(sizeof(TreeNode));
    newNode->key = key;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to insert a key into the BST
TreeNode *insert(TreeNode *root, int key)
{
    if (root == NULL)
    {
        return createNode(key);
    }
    if (key < root->key)
    {
        root->left = insert(root->left, key);
    }
    else
    {
        root->right = insert(root->right, key);
    }
    return root;
}

// Function to find the node with the minimum value in a BST
TreeNode *minValueNode(TreeNode *node)
{
    TreeNode *current = node;
    while (current && current->left != NULL)
    {
        current = current->left;
    }
    return current;
}

// Function to delete a node from the BST
TreeNode *deleteNode(TreeNode *root, int key)
{
    if (root == NULL)
    {
        return root;
    }
    if (key < root->key)
    {
        root->left = deleteNode(root->left, key);
    }
    else if (key > root->key)
    {
        root->right = deleteNode(root->right, key);
    }
    else
    {
        if (root->left == NULL)
        {
            TreeNode *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            TreeNode *temp = root->left;
            free(root);
            return temp;
        }
        TreeNode *temp = minValueNode(root->right);
        root->key = temp->key;
        root->right = deleteNode(root->right, temp->key);
    }
    return root;
}

// Non-recursive function to mirror the BST
TreeNode *mirror(TreeNode *root)
{
    if (root == NULL)
    {
        return root;
    }
    TreeNode *queue[1000];
    int front = 0, rear = 0;
    queue[rear++] = root;
    while (front < rear)
    {
        TreeNode *current = queue[front++];
        TreeNode *temp = current->left;
        current->left = current->right;
        current->right = temp;
        if (current->left)
        {
            queue[rear++] = current->left;
        }
        if (current->right)
        {
            queue[rear++] = current->right;
        }
    }
    return root;
}

// Non-recursive function to perform level-order traversal
void levelOrderTraversal(TreeNode *root)
{
    if (root == NULL)
    {
        return;
    }
    TreeNode *queue[1000];
    int front = 0, rear = 0;
    queue[rear++] = root;
    while (front < rear)
    {
        TreeNode *current = queue[front++];
        printf("%d ", current->key);
        if (current->left != NULL)
        {
            queue[rear++] = current->left;
        }
        if (current->right != NULL)
        {
            queue[rear++] = current->right;
        }
    }
}

// Non-recursive function to find the height of the BST
int height(TreeNode *root)
{
    if (root == NULL)
    {
        return 0;
    }
    int maxHeight = 0;
    TreeNode *queue[1000];
    int level[1000];  // to store the level of each node
    int front = 0, rear = 0;
    queue[rear] = root;
    level[rear++] = 1;
    while (front < rear)
    {
        TreeNode *current = queue[front];
        int currentLevel = level[front++];
        if (currentLevel > maxHeight)
        {
            maxHeight = currentLevel;
        }
        if (current->left)
        {
            queue[rear] = current->left;
            level[rear++] = currentLevel + 1;
        }
        if (current->right)
        {
            queue[rear] = current->right;
            level[rear++] = currentLevel + 1;
        }
    }
    return maxHeight;
}

// Non-recursive function to display leaf nodes
void displayLeafNodes(TreeNode *root)
{
    if (root == NULL)
    {
        return;
    }
    TreeNode *queue[1000];
    int front = 0, rear = 0;
    queue[rear++] = root;
    while (front < rear)
    {
        TreeNode *current = queue[front++];
        if (current->left == NULL && current->right == NULL)
        {
            printf("%d ", current->key);
        }
        if (current->left)
        {
            queue[rear++] = current->left;
        }
        if (current->right)
        {
            queue[rear++] = current->right;
        }
    }
}

// Non-recursive function for inorder traversal
void inorderTraversal(TreeNode *root)
{
    if (root == NULL)
    {
        return;
    }
    TreeNode *stack[1000];
    int top = -1;
    TreeNode *current = root;
    while (current != NULL || top != -1)
    {
        while (current != NULL)
        {
            stack[++top] = current;
            current = current->left;
        }
        current = stack[top--];
        printf("%d ", current->key);
        current = current->right;
    }
}

// Non-recursive function for preorder traversal
void preorderTraversal(TreeNode *root)
{
    if (root == NULL)
    {
        return;
    }
    TreeNode *stack[1000];
    int top = -1;
    stack[++top] = root;
    while (top != -1)
    {
        TreeNode *current = stack[top--];
        printf("%d ", current->key);
        if (current->right)
        {
            stack[++top] = current->right;
        }
        if (current->left)
        {
            stack[++top] = current->left;
        }
    }
}

// Non-recursive function for postorder traversal
void postorderTraversal(TreeNode *root)
{
    if (root == NULL)
    {
        return;
    }
    TreeNode *stack1[1000];
    TreeNode *stack2[1000];
    int top1 = -1, top2 = -1;
    stack1[++top1] = root;
    while (top1 != -1)
    {
        TreeNode *current = stack1[top1--];
        stack2[++top2] = current;
        if (current->left)
        {
            stack1[++top1] = current->left;
        }
        if (current->right)
        {
            stack1[++top1] = current->right;
        }
    }
    while (top2 != -1)
    {
        printf("%d ", stack2[top2--]->key);
    }
}

int main()
{
    TreeNode *root = NULL;
    root = insert(root, 50);
    insert(root, 30);
    insert(root, 20);
    insert(root, 40);
    insert(root, 70);
    insert(root, 60);
    insert(root, 80);

    printf("Original BST: ");
    levelOrderTraversal(root);
    printf("\n");

    printf("Height of the tree: %d\n", height(root));

    printf("Inorder traversal: ");
    inorderTraversal(root);
    printf("\n");

    printf("Preorder traversal: ");
    preorderTraversal(root);
    printf("\n");

    printf("Postorder traversal: ");
    postorderTraversal(root);
    printf("\n");

    root = deleteNode(root, 20);
    printf("\nBST after deleting 20: ");
    levelOrderTraversal(root);
    printf("\n");

    root = mirror(root);
    printf("\nMirror Image of BST: ");
    levelOrderTraversal(root);
    printf("\n");

    printf("Leaf Nodes of BST: ");
    displayLeafNodes(root);
    printf("\n");

    return 0;
}