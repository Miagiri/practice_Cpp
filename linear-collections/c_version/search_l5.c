#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TABLE_SIZE 10007

struct Node {
    int key;
    int value;
    struct Node* next;
};

struct HashTable {
    struct Node** buckets;
    int size;
};

int hash(int key, int table_size) {
    int h = key % table_size;
    if (h < 0)
        h = -h;
    return h;
}

struct HashTable* createHashTable(int size) {
    struct HashTable* table = (struct HashTable*)malloc(sizeof(struct HashTable));
    if (table == NULL) {
        return NULL;
    }

    table->size = size;
    table->buckets = (struct Node**)calloc(size, sizeof(struct Node*));
    if (table->buckets == NULL) {
        free(table);
        return NULL;
    }

    return table;
}

void insert(struct HashTable* table, int key, int value) {
    int h = hash(key, table->size);
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        return;
    }
    newNode->key = key;
    newNode->value = value;
    newNode->next = table->buckets[h];
    table->buckets[h] = newNode;
}

int search(struct HashTable* table, int key, int* probes) {
    int h = hash(key, table->size);
    *probes = 0;
    struct Node* current = table->buckets[h];
    while (current != NULL) {
        (*probes)++;
        if (current->key == key) {
            return current->value;
        }
        current = current->next;
    }
    return -1;
}

void freeHashTable(struct HashTable* table) {
    if (table == NULL)
        return;

    for (int i = 0; i < table->size; i++) {
        struct Node* current = table->buckets[i];
        while (current != NULL) {
            struct Node* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(table->buckets);
    free(table);
}

int linearSearch(int* arr, int n, int key, int* comparisons) {
    *comparisons = 0;
    for (int i = 0; i < n; i++) {
        (*comparisons)++;
        if (arr[i] == key) {
            return i;
        }
    }
    return -1;
}

int binarySearch(int* arr, int n, int key, int* comparisons) {
    *comparisons = 0;
    int binary_index = -1;
    int left = 0;
    int right = n - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        (*comparisons)++;

        if (arr[mid] == key) {
            binary_index = mid;
            break;
        }

        (*comparisons)++;
        if (arr[mid] < key) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return binary_index;
}

int compare(const void* a, const void* b) { return (*(int*)a - *(int*)b); }

int main() {
    int n = 10000;
    int* arr = (int*)malloc(n * sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    srand(12345);
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 100000;
    }

    struct HashTable* table = createHashTable(TABLE_SIZE);
    if (table == NULL) {
        printf("Hash table creation failed\n");
        free(arr);
        return 1;
    }

    for (int i = 0; i < n; i++) {
        int probes;
        int index = search(table, arr[i], &probes);
        if (index == -1) {
            insert(table, arr[i], i);
        }
    }

    int* sortedArr = (int*)malloc(n * sizeof(int));
    if (sortedArr == NULL) {
        printf("Memory allocation failed\n");
        free(arr);
        freeHashTable(table);
        return 1;
    }

    for (int i = 0; i < n; i++) {
        sortedArr[i] = arr[i];
    }
    qsort(sortedArr, n, sizeof(int), compare);

    int key = arr[rand() % n];

    int linearComparisons, binaryComparisons, hashProbes;
    int linearIndex, binaryIndex, hashIndex;

    linearIndex = linearSearch(arr, n, key, &linearComparisons);
    binaryIndex = binarySearch(sortedArr, n, key, &binaryComparisons);
    hashIndex = search(table, key, &hashProbes);

    int bucketIdx = hash(key, TABLE_SIZE);
    int chainLength = 0;
    struct Node* current = table->buckets[bucketIdx];
    while (current != NULL) {
        chainLength++;
        current = current->next;
    }

    printf("Search key: %d\n\n", key);

    printf("Linear search:\n");
    printf("  Index: %d\n", linearIndex);
    printf("  Comparisons: %d\n\n", linearComparisons);

    printf("Binary search:\n");
    printf("  Index: %d\n", binaryIndex);
    printf("  Comparisons: %d\n\n", binaryComparisons);

    printf("Hash table:\n");
    printf("  Index: %d\n", hashIndex);
    printf("  Probes: %d\n", hashProbes);
    printf("  Bucket count: %d\n", TABLE_SIZE);
    printf("  Load factor: %.2f\n", (float)n / TABLE_SIZE);
    printf("  Bucket #%d chain length: %d\n", bucketIdx, chainLength);

    free(arr);
    free(sortedArr);
    freeHashTable(table);

    return 0;
}