#include <algorithm>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <random>
#include <vector>

void merge(std::vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    std::vector<int> L(n1), R(n2);

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
}

void mergeSort(std::vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

int partition(std::vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }

    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void heapify(std::vector<int>& arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;
    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(std::vector<int>& arr, int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }

    for (int i = n - 1; i > 0; i--) {
        std::swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

void heapSortWrapper(std::vector<int>& arr, int left, int right) { heapSort(arr, right + 1); }

template <typename Func> double measureTime(Func sortFunc, std::vector<int>& arr, int n) {
    auto start = std::chrono::high_resolution_clock::now();
    sortFunc(arr, 0, n - 1);
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration<double, std::milli>(end - start).count();
}

double measureStdSort(std::vector<int>& arr) {
    auto start = std::chrono::high_resolution_clock::now();
    std::sort(arr.begin(), arr.end());
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration<double, std::milli>(end - start).count();
}

int main() {
    std::vector<int> sizes = {1000, 10000, 100000};

    std::mt19937 gen(12345);
    std::uniform_int_distribution<int> dis(0, 999999);

    std::cout << "+----------------+----------------+---------+---------+-----------+\n";
    std::cout << "| Algorithm      | Complexity     | 1000    | 10000   | 100000    |\n";
    std::cout << "+----------------+----------------+---------+---------+-----------+\n";

    std::vector<double> timesMerge, timesQuick, timesHeap, timesStdSort;

    for (int n : sizes) {
        std::vector<int> original(n);
        for (int i = 0; i < n; i++) {
            original[i] = dis(gen);
        }

        std::vector<int> arrMerge = original;
        std::vector<int> arrQuick = original;
        std::vector<int> arrHeap = original;
        std::vector<int> arrStd = original;

        timesMerge.push_back(measureTime(mergeSort, arrMerge, n));
        timesQuick.push_back(measureTime(quickSort, arrQuick, n));
        timesHeap.push_back(measureTime(heapSortWrapper, arrHeap, n));
        timesStdSort.push_back(measureStdSort(arrStd));
    }

    std::cout << std::fixed << std::setprecision(2);

    std::cout << "| Merge sort     | O(N log N)     | " << std::setw(5) << timesMerge[0] << " ms | "
              << std::setw(5) << timesMerge[1] << " ms | " << std::setw(7) << timesMerge[2]
              << " ms |\n";
    std::cout << "+----------------+----------------+---------+---------+-----------+\n";
    std::cout << "| Quick sort     | O(N log N)     | " << std::setw(5) << timesQuick[0] << " ms | "
              << std::setw(5) << timesQuick[1] << " ms | " << std::setw(7) << timesQuick[2]
              << " ms |\n";
    std::cout << "+----------------+----------------+---------+---------+-----------+\n";
    std::cout << "| Heap sort      | O(N log N)     | " << std::setw(5) << timesHeap[0] << " ms | "
              << std::setw(5) << timesHeap[1] << " ms | " << std::setw(7) << timesHeap[2]
              << " ms |\n";
    std::cout << "+----------------+----------------+---------+---------+-----------+\n";
    std::cout << "| std::sort      | O(N log N)     | " << std::setw(5) << timesStdSort[0]
              << " ms | " << std::setw(5) << timesStdSort[1] << " ms | " << std::setw(7)
              << timesStdSort[2] << " ms |\n";
    std::cout << "+----------------+----------------+---------+---------+-----------+\n";

    return 0;
}