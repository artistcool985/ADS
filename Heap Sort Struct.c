#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 10

typedef struct {
    char student_name[20];
    int student_roll_no;
    int total_marks;
} Student;

void swap(Student* a, Student* b) {
    Student temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(Student arr[], int n, int i, int* swaps) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left].student_roll_no > arr[largest].student_roll_no) {
        largest = left;
    }

    if (right < n && arr[right].student_roll_no > arr[largest].student_roll_no) {
        largest = right;
    }

    if (largest!= i) {
        swap(&arr[i], &arr[largest]);
        (*swaps)++;
        heapify(arr, n, largest, swaps);
    }
}

void heapSort(Student arr[], int n) {
    int swaps = 0;

    // Build heap
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i, &swaps);
    }

    // Extract elements one by one
    for (int i = n - 1; i >= 0; i--) {
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0, &swaps);
    }

    printf("Number of swaps performed: %d\n", swaps);
}

void printArray(Student arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%s %d %d\n", arr[i].student_name, arr[i].student_roll_no, arr[i].total_marks);
    }
}

int main() {
    Student arr[MAX_STUDENTS] = {
        {"John", 10, 80},
        {"Alice", 5, 90},
        {"Bob", 15, 70},
        {"Charlie", 20, 85},
        {"David", 7, 95},
        {"Eve", 12, 75},
        {"Frank", 18, 80},
        {"George", 3, 90},
        {"Helen", 11, 85},
        {"Ivan", 9, 95}
    };

    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original array:\n");
    printArray(arr, n);

    heapSort(arr, n);

    printf("Sorted array:\n");
    printArray(arr, n);

    return 0;
}