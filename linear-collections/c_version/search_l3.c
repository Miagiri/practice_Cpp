#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int compare(const void* a, const void* b) { return (*(int*)a - *(int*)b); }

int main() {
    int n = 10000;
    int* arr = (int*)malloc(n * sizeof(int));

    if (arr == NULL) {
        return 1;
    }

    srand((unsigned int)time(NULL));
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 100000;
    }

    qsort(arr, n, sizeof(int), compare);

    int key = arr[rand() % n];

    printf("Sorted array (first 20 elements):\n");
    for (int i = 0; i < 20 && i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n\n");

    printf("Search key: %d\n\n", key);

    int linear_compare = 0;
    int linear_index = -1;
    for (int i = 0; i < n; i++) {
        linear_compare++;
        if (arr[i] == key) {
            linear_index = i;
            break;
        }
    }

    int binary_compare = 0;
    int binary_index = -1;
    int left = 0, right = n - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        binary_compare++;

        if (arr[mid] == key) {
            binary_index = mid;
            break;
        }

        binary_compare++;
        if (arr[mid] < key) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    printf("Linear search: %d comparisons (found at index %d)\n", linear_compare, linear_index);
    printf("Binary search: %d comparisons (found at index %d)\n", binary_compare, binary_index);

    free(arr);
    return 0;
}