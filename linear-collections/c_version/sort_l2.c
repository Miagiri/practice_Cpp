#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int compare(const void* a, const void* b) { return (*(int*)a - *(int*)b); }

int main() {
    int n = 10000;

    int* original = malloc(n * sizeof(int));
    int* arr1 = malloc(n * sizeof(int));
    int* arr2 = malloc(n * sizeof(int));

    if (original == NULL || arr1 == NULL || arr2 == NULL) {
        printf("malloc failed\n");
        if (original)
            free(original);
        if (arr1)
            free(arr1);
        if (arr2)
            free(arr2);
        return 1;
    }

    srand((unsigned int)time(NULL));
    for (int i = 0; i < n; i++) {
        original[i] = rand() % 100000;
    }

    printf("Original array (first 10 elements): ");
    for (int i = 0; i < 10; i++) {
        printf("%d ", original[i]);
    }
    printf("...\n");

    for (int i = 0; i < n; i++) {
        arr1[i] = original[i];
        arr2[i] = original[i];
    }

    clock_t start, end;
    double time_taken;

    printf("\nSorting %d elements...\n\n", n);

    start = clock();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr1[j] > arr1[j + 1]) {
                int temp = arr1[j];
                arr1[j] = arr1[j + 1];
                arr1[j + 1] = temp;
            }
        }
    }
    end = clock();
    time_taken = ((double)(end - start)) / CLOCKS_PER_SEC * 1000;

    printf("Bubble sort:    ");
    for (int i = 0; i < 10; i++) {
        printf("%d ", arr1[i]);
    }
    printf("... | %.3f ms\n", time_taken);

    start = clock();
    qsort(arr2, n, sizeof(int), compare);
    end = clock();
    time_taken = ((double)(end - start)) / CLOCKS_PER_SEC * 1000;

    printf("Built-in (qsort): ");
    for (int i = 0; i < 10; i++) {
        printf("%d ", arr2[i]);
    }
    printf("... | %.3f ms\n", time_taken);

    free(original);
    free(arr1);
    free(arr2);

    return 0;
}