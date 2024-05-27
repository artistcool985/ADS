#include<stdio.h>
#include<stdlib.h>
struct node
{
    int data;
    struct node*left,*right;
};
struct stack{
    struct node *T;
    struct stack* next;
};
struct node*Insert(int,struct node*);
struct node*newnode(int);
void preorder_non_recursive(struct node *);
void preorder(struct node *);
void push(struct node*,struct stack**);
struct node *pop(struct stack**);

struct node*Insert(int data,struct node*root)
{
    if (root==NULL)
    {
        root=newnode(data);
    }
    else if (data<root->data)
    {
        root->left=Insert(data,root->left);
    }
    else 
    {
        root->right=Insert(data,root->right);
    }
    return root;
}
struct node* newnode(int data)
{
    struct node *temp;
    temp=(struct node*)malloc(sizeof(struct node));
    temp->data=data;
    temp->left=temp->right=NULL;
    return temp;
}
void preorder(struct node *root)
{
    if (root!=NULL)
    {
    printf(" %d",root->data);
    preorder(root->left);
    preorder(root->right);
    }
}
void push(struct node*root,struct stack**top)
{
    struct stack*newBlock=(struct stack*)malloc(sizeof(struct stack));
    newBlock->T=root;
    newBlock->next=(*top);
    (*top)=newBlock;
}
struct node*pop(struct stack **top)
{
    struct stack*temp;
    temp=(*top);
    (*top)=(*top)->next;
    struct node*N=temp->T;
    free(temp);
    return N;
}
int isEmptystack(struct stack*top)
{
    return (top==NULL)?1:0;
}
void preorder_non_recursive(struct node * root)
{
    struct stack*top=NULL;

    while (root!=NULL)
    {
        printf(" %d",root->data);
        push(root,&top);
        root=root->left;
    }
    while (!isEmptystack(top))
    {
        root=pop(&top);
        root=root->right;
        while (root!=NULL)
        {
            printf(" %d",root->data);
            push(root,&top);
            root=root->left;
        }
        
    }
    
    
}
void Inorder(struct node *root)
{
if (root==NULL)
{
    return;
}

    Inorder(root->left);
    printf(" %d",root->data);
    Inorder(root->right);

}
void Inorder_non_recursive(struct node *root)
{
    struct stack*top=NULL;
    while (root!=NULL)
    {
        push(root,&top);
        root=root->left;
    }
    while (!isEmptystack(top))
    {
        root=pop(&top);
        printf(" %d",root->data);
        root=root->right;
        while (root!=NULL)
        {
            push(root,&top);
            root=root->left;
        }
           
    }  
}
void postorder(struct node*root)
{
    if (root==NULL)
    {
        return;
    }
    
    postorder(root->left);
    postorder(root->right);
    printf(" %d",root->data);
}
struct node *stackTop(struct stack*top)
{
    return (top!=NULL)?top->T:NULL;
}
void postorder_non_recursive(struct node *root) {
    struct stack *top = NULL;
    struct node *prev = NULL;
    struct node *T = root;

    // Push all left nodes to stack
    while (T != NULL) {
        push(T, &top);
        T = T->left;
    }

    while (!isEmptystack(top)) {
        T = stackTop(top);

        // If the right child is NULL or already visited
        if (T->right == NULL || T->right == prev) {
            printf("%d ", T->data);
            pop(&top);
            prev = T;
        } else {
            // Traverse the right subtree
            T = T->right;
            while (T != NULL) {
                push(T, &top);
                T = T->left;
            }
        }
    }
}


int main()
{
    struct node*root=NULL;
   root=Insert(50,root);
    Insert(40,root);
    Insert(60,root);
    Insert(30,root);
    Insert(45,root);
    Insert(55,root);
    Insert(70,root);
   // preorder(root);
    printf("\n\n Preorder: ");
    preorder_non_recursive(root);
    printf("\n\n Inorder: ");
    Inorder_non_recursive(root);
    printf("\n\n Postorder: ");
    postorder_non_recursive(root);
}
