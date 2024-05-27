#include <stdio.h>

// Function to find the first inflection point (where order is violated)
int findFirst(int A[], int left, int right) {
    while (left < right) {
        int mid = left + (right - left) / 2;

        // Check if mid is the inflection point
        if (A[mid] > A[mid + 1]) {
            return mid;
        }

        // If the left part is sorted, move to the right part
        if (A[left] <= A[mid]) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    return left;
}

// Function to find the second inflection point (where order is violated)
int findSecond(int A[], int left, int right) {
    while (left < right) {
        int mid = left + (right - left) / 2;

        // Check if mid is the inflection point
        if (A[mid] > A[mid + 1]) {
            return mid + 1;
        }

        // If the right part is sorted, move to the left part
        if (A[mid] <= A[right]) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    return right;
}

// Function to identify the swapped elements and their positions
void findSwappedElements(int A[], int n) {
    // Find the first inflection point
    int first = findFirst(A, 0, n - 1);
    
    // Find the second inflection point starting from the first
    int second = findSecond(A, first, n - 1);

    // The swapped elements are A[first] and A[second]
    printf("Swapped elements are: %d and %d\n", A[first], A[second]);
    printf("Positions are: %d and %d\n", first, second);
}

// Driver code
int main() {
    int A[] = {1, 2, 3, 5, 4, 6, 7, 8};  // Example array
    int n = sizeof(A) / sizeof(A[0]);

    findSwappedElements(A, n);

    return 0;
}
