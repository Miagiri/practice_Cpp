#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void copyArray(int* dest, int* src, int n) {
    for (int i = 0; i < n; i++) {
        dest[i] = src[i];
    }
}

void merge(int* arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int* L = (int*)malloc(n1 * sizeof(int));
    int* R = (int*)malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int i = 0; i < n2; i++)
        R[i] = arr[mid + 1 + i];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }

    while (i < n1)
        arr[k++] = L[i++];
    while (j < n2)
        arr[k++] = R[j++];

    free(L);
    free(R);
}

void mergeSort(int* arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

int partition(int* arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;

    return i + 1;
}

void quickSort(int* arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void heapify(int* arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;
    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        heapify(arr, n, largest);
    }
}

void heapSort(int* arr, int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }

    for (int i = n - 1; i > 0; i--) {
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        heapify(arr, i, 0);
    }
}

void heapSortWrapper(int* arr, int left, int right) { heapSort(arr, right + 1); }

int compare(const void* a, const void* b) { return (*(int*)a - *(int*)b); }

double measureTime(void (*sortFunc)(int*, int, int), int* arr, int n) {
    clock_t start = clock();
    sortFunc(arr, 0, n - 1);
    clock_t end = clock();
    return ((double)(end - start)) / CLOCKS_PER_SEC * 1000;
}

double measureQsort(int* arr, int n) {
    clock_t start = clock();
    qsort(arr, n, sizeof(int), compare);
    clock_t end = clock();
    return ((double)(end - start)) / CLOCKS_PER_SEC * 1000;
}

int main() {
    int sizes[] = {1000, 10000, 100000};
    int numSizes = sizeof(sizes) / sizeof(sizes[0]);

    srand(12345);

    printf("+----------------+----------------+---------+---------+-----------+\n");
    printf("| Algorithm      | Complexity     | 1000    | 10000   | 100000    |\n");
    printf("+----------------+----------------+---------+---------+-----------+\n");

    double timesMerge[3] = {0}, timesQuick[3] = {0}, timesHeap[3] = {0}, timesQsort[3] = {0};

    for (int idx = 0; idx < numSizes; idx++) {
        int n = sizes[idx];

        int* original = (int*)malloc(n * sizeof(int));
        if (original == NULL) {
            printf("Memory allocation failed for size %d\n", n);
            return 1;
        }

        for (int i = 0; i < n; i++) {
            original[i] = rand() % 1000000;
        }

        int* arrMerge = (int*)malloc(n * sizeof(int));
        int* arrQuick = (int*)malloc(n * sizeof(int));
        int* arrHeap = (int*)malloc(n * sizeof(int));
        int* arrQsort = (int*)malloc(n * sizeof(int));

        if (!arrMerge || !arrQuick || !arrHeap || !arrQsort) {
            printf("Memory allocation failed\n");
            free(original);
            if (arrMerge)
                free(arrMerge);
            if (arrQuick)
                free(arrQuick);
            if (arrHeap)
                free(arrHeap);
            if (arrQsort)
                free(arrQsort);
            return 1;
        }

        copyArray(arrMerge, original, n);
        copyArray(arrQuick, original, n);
        copyArray(arrHeap, original, n);
        copyArray(arrQsort, original, n);

        timesMerge[idx] = measureTime(mergeSort, arrMerge, n);
        timesQuick[idx] = measureTime(quickSort, arrQuick, n);
        timesHeap[idx] = measureTime(heapSortWrapper, arrHeap, n);
        timesQsort[idx] = measureQsort(arrQsort, n);

        free(original);
        free(arrMerge);
        free(arrQuick);
        free(arrHeap);
        free(arrQsort);
    }

    printf("| Merge sort     | O(N log N)     | %-5.2f ms | %-6.2f ms | %-7.2f ms |\n",
           timesMerge[0], timesMerge[1], timesMerge[2]);
    printf("+----------------+----------------+---------+---------+-----------+\n");
    printf("| Quick sort     | O(N log N)     | %-5.2f ms | %-6.2f ms | %-7.2f ms |\n",
           timesQuick[0], timesQuick[1], timesQuick[2]);
    printf("+----------------+----------------+---------+---------+-----------+\n");
    printf("| Heap sort      | O(N log N)     | %-5.2f ms | %-6.2f ms | %-7.2f ms |\n",
           timesHeap[0], timesHeap[1], timesHeap[2]);
    printf("+----------------+----------------+---------+---------+-----------+\n");
    printf("| qsort (built-in)| O(N log N)    | %-5.2f ms | %-6.2f ms | %-7.2f ms |\n",
           timesQsort[0], timesQsort[1], timesQsort[2]);
    printf("+----------------+----------------+---------+---------+-----------+\n");

    return 0;
}