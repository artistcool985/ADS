#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct StackNode {
    char data;
    struct StackNode* next;
} StackNode;

typedef struct Stack {
    StackNode* top;
} Stack;

void initStack(Stack* s) {
    s->top = NULL;
}

int isEmpty(Stack* s) {
    return s->top == NULL;
}

void push(Stack* s, char value) {
    StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
    newNode->data = value;
    newNode->next = s->top;
    s->top = newNode;
}

char pop(Stack* s) {
    if (isEmpty(s)) {
        printf("Stack Underflow\n");
        exit(1);
    }
    StackNode* temp = s->top;
    char poppedValue = temp->data;
    s->top = s->top->next;
    free(temp);
    return poppedValue;
}

char peek(Stack* s) {
    if (isEmpty(s)) {
        printf("Stack is empty\n");
        return -1;
    }
    return s->top->data;
}

int precedence(char op) {
    switch (op) {
        case '+':
        case '-': return 1;
        case '*':
        case '/': return 2;
        case '^': return 3;
        default: return 0;
    }
}

int isOperator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^';
}

void reverseString(char* str) {
    int n = strlen(str);
    for (int i = 0; i < n / 2; i++) {
        char temp = str[i];
        str[i] = str[n - i - 1];
        str[n - i - 1] = temp;
    }
}

void infixToPostfix(char* infix, char* postfix) {
    Stack s;
    initStack(&s);
    int i, k = 0;
    for (i = 0; infix[i] != '\0'; i++) {
        if (isspace(infix[i])) {
            continue;
        } else if (isdigit(infix[i])) {
            postfix[k++] = infix[i];
        } else if (infix[i] == '(') {
            push(&s, infix[i]);
        } else if (infix[i] == ')') {
            while (!isEmpty(&s) && peek(&s) != '(') {
                postfix[k++] = pop(&s);
            }
            pop(&s); // Remove '(' from stack
        } else if (isOperator(infix[i])) {
            while (!isEmpty(&s) && precedence(peek(&s)) >= precedence(infix[i])) {
                postfix[k++] = pop(&s);
            }
            push(&s, infix[i]);
        }
    }
    while (!isEmpty(&s)) {
        postfix[k++] = pop(&s);
    }
    postfix[k] = '\0';
}

void infixToPrefix(char* infix, char* prefix) {
    // Step 1: Reverse the infix expression
    reverseString(infix);
    
    // Step 2: Replace '(' with ')' and vice versa
    for (int i = 0; infix[i] != '\0'; i++) {
        if (infix[i] == '(') {
            infix[i] = ')';
        } else if (infix[i] == ')') {
            infix[i] = '(';
        }
    }
    
    // Step 3: Convert the modified infix expression to postfix
    char postfix[100];
    infixToPostfix(infix, postfix);
    
    // Step 4: Reverse the postfix expression to get the prefix expression
    reverseString(postfix);
    strcpy(prefix, postfix);
}

int evaluatePrefix(char* prefix) {
    Stack s;
    initStack(&s);
    int n = strlen(prefix);
    
    // Process the prefix expression from right to left
    for (int i = n - 1; i >= 0; i--) {
        if (isdigit(prefix[i])) {
            push(&s, prefix[i] - '0');
        } else if (isOperator(prefix[i])) {
            int operand1 = pop(&s);
            int operand2 = pop(&s);
            switch (prefix[i]) {
                case '+': push(&s, operand1 + operand2); break;
                case '-': push(&s, operand1 - operand2); break;
                case '*': push(&s, operand1 * operand2); break;
                case '/': push(&s, operand1 / operand2); break;
            }
        }
    }
    return pop(&s);
}

int main() {
    char infix[] = "(3+5)*(2-8)";
    char prefix[100];
    
    infixToPrefix(infix, prefix);
    
    printf("Infix Expression: %s\n", infix);
    printf("Prefix Expression: %s\n", prefix);
    
    int result = evaluatePrefix(prefix);
    printf("Result of Evaluation: %d\n", result);
    
    return 0;
}
