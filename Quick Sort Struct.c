#include <stdio.h>
#include <string.h>

// Define the structure for an employee
typedef struct {
    char employee_name[100];
    int emp_no;
    float emp_salary;
} Employee;

// Function to swap two employees
void swap(Employee *a, Employee *b, int *swapCount) {
    Employee temp = *a;
    *a = *b;
    *b = temp;
    (*swapCount)++;
}

// Partition function for QuickSort
int partition(Employee arr[], int low, int high, int *swapCount) {
    int pivot = arr[high].emp_no;
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j].emp_no < pivot) {
            i++;
            swap(&arr[i], &arr[j], swapCount);
        }
    }
    swap(&arr[i + 1], &arr[high], swapCount);
    return i + 1;
}

// QuickSort function
void quickSort(Employee arr[], int low, int high, int *swapCount) {
    if (low < high) {
        int pi = partition(arr, low, high, swapCount);
        quickSort(arr, low, pi - 1, swapCount);
        quickSort(arr, pi + 1, high, swapCount);
    }
}

// Function to print the array of employees
void printArray(Employee arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("Employee Name: %s, Employee Number: %d, Employee Salary: %.2f\n",
               arr[i].employee_name, arr[i].emp_no, arr[i].emp_salary);
    }
}

// Driver code
int main() {
    Employee employees[] = {
        {"John Doe", 5, 50000.0},
        {"Jane Smith", 3, 60000.0},
        {"Emily Davis", 8, 55000.0},
        {"Michael Brown", 1, 45000.0},
        {"Chris Johnson", 7, 70000.0}
    };
    int n = sizeof(employees) / sizeof(employees[0]);
    int swapCount = 0;

    printf("Original array:\n");
    printArray(employees, n);

    quickSort(employees, 0, n - 1, &swapCount);

    printf("\nSorted array:\n");
    printArray(employees, n);
    printf("\nNumber of swaps performed: %d\n", swapCount);

    return 0;
}
