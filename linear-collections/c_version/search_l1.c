#include <stdio.h>

int main() {

    int arr[] = {5, 2, 8, 2, 9, 1, 2, 7, 3, 2};
    int n = sizeof(arr) / sizeof(arr[0]);

    int K = 9;

    int index = -1;
    int count = 0;
    int i = 0;

    while (i < n && index == -1) {
        count++;
        if (arr[i] == K) {
            index = i;
        }
        i++;
    }

    printf("Array: ");
    i = 0;
    while (i < n) {
        printf("%d ", arr[i]);
        i++;
    }
    printf("\n");

    printf("Search key K = %d\n", K);

    if (index != -1) {
        printf("Index of first occurrence: %d\n", index);
    } else {
        printf("Index of first occurrence: -1 (number not found)\n");
    }

    printf("Number of comparisons: %d\n", count);

    return 0;
}