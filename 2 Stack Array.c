#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct {
    int data[MAX];
    int top1;
    int top2;
} TwoStacks;

// Initialize the stacks
void initializeStacks(TwoStacks* ts) {
    ts->top1 = -1;
    ts->top2 = MAX;
}

// Check if stack1 is empty
int isEmptyStack1(TwoStacks* ts) {
    return ts->top1 == -1;
}

// Check if stack2 is empty
int isEmptyStack2(TwoStacks* ts) {
    return ts->top2 == MAX;
}

// Check if the stacks are full
int isFull(TwoStacks* ts) {
    return ts->top1 + 1 == ts->top2;
}

// Push an element onto stack1
void pushStack1(TwoStacks* ts, int value) {
    if (isFull(ts)) {
        printf("Stack Overflow\n");
        return;
    }
    ts->data[++ts->top1] = value;
}

// Push an element onto stack2
void pushStack2(TwoStacks* ts, int value) {
    if (isFull(ts)) {
        printf("Stack Overflow\n");
        return;
    }
    ts->data[--ts->top2] = value;
}

// Pop an element from stack1
int popStack1(TwoStacks* ts) {
    if (isEmptyStack1(ts)) {
        printf("Stack Underflow\n");
        return -1;
    }
    return ts->data[ts->top1--];
}

// Pop an element from stack2
int popStack2(TwoStacks* ts) {
    if (isEmptyStack2(ts)) {
        printf("Stack Underflow\n");
        return -1;
    }
    return ts->data[ts->top2++];
}

// Display stack1
void displayStack1(TwoStacks* ts) {
    if (isEmptyStack1(ts)) {
        printf("Stack1 is empty\n");
        return;
    }
    printf("Stack1 elements:\n");
    for (int i = 0; i <= ts->top1; i++) {
        printf("%d ", ts->data[i]);
    }
    printf("\n");
}

// Display stack2
void displayStack2(TwoStacks* ts) {
    if (isEmptyStack2(ts)) {
        printf("Stack2 is empty\n");
        return;
    }
    printf("Stack2 elements:\n");
    for (int i = MAX - 1; i >= ts->top2; i--) {
        printf("%d ", ts->data[i]);
    }
    printf("\n");
}

int main() {
    TwoStacks ts;
    initializeStacks(&ts);

    pushStack1(&ts, 10);
    pushStack1(&ts, 20);
    pushStack1(&ts, 30);

    pushStack2(&ts, 40);
    pushStack2(&ts, 50);
    pushStack2(&ts, 60);

    printf("After pushing elements:\n");
    displayStack1(&ts);
    displayStack2(&ts);

    printf("Popped from stack1: %d\n", popStack1(&ts));
    printf("Popped from stack2: %d\n", popStack2(&ts));

    printf("After popping elements:\n");
    displayStack1(&ts);
    displayStack2(&ts);

    return 0;
}
