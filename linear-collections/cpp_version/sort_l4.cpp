#include <algorithm>
#include <chrono>
#include <format>
#include <print>
#include <random>
#include <ranges>
#include <vector>

constexpr unsigned kSeed = 12345;

void merge(std::vector<int>& arr, ptrdiff_t left, ptrdiff_t mid, ptrdiff_t right) {
    ptrdiff_t n1 = mid - left + 1;
    ptrdiff_t n2 = right - mid;

    std::vector<int> L(n1), R(n2);

    for (ptrdiff_t i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (ptrdiff_t i = 0; i < n2; i++)
        R[i] = arr[mid + 1 + i];

    ptrdiff_t i = 0, j = 0, k = left;

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

void mergeSort(std::vector<int>& arr, ptrdiff_t left, ptrdiff_t right) {
    if (left < right) {
        ptrdiff_t mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

ptrdiff_t partition(std::vector<int>& arr, ptrdiff_t low, ptrdiff_t high) {
    int pivot = arr[high];
    ptrdiff_t i = low - 1;

    for (ptrdiff_t j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }

    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(std::vector<int>& arr, ptrdiff_t low, ptrdiff_t high) {
    if (low < high) {
        ptrdiff_t pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void heapify(std::vector<int>& arr, ptrdiff_t n, ptrdiff_t i) {
    ptrdiff_t largest = i;
    ptrdiff_t left = 2 * i + 1;
    ptrdiff_t right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;
    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(std::vector<int>& arr, ptrdiff_t n) {
    for (ptrdiff_t i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }

    for (ptrdiff_t i = n - 1; i > 0; i--) {
        std::swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

void heapSortWrapper(std::vector<int>& arr, ptrdiff_t /*left*/, ptrdiff_t right) {
    heapSort(arr, right + 1);
}

template <typename Func> double measureTime(Func sortFunc, std::vector<int>& arr, ptrdiff_t n) {
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

    std::mt19937 gen(kSeed);
    std::uniform_int_distribution<int> dis(0, 999999);

    std::println("+----------------+----------------+---------+---------+-----------+");
    std::println("| Algorithm      | Complexity     | 1000    | 10000   | 100000    |");
    std::println("+----------------+----------------+---------+---------+-----------+");

    std::vector<double> timesMerge, timesQuick, timesHeap, timesStdSort;

    for (ptrdiff_t n : sizes) {
        std::vector<int> original(n);
        std::ranges::generate(original, [&] { return dis(gen); });

        std::vector<int> arrMerge = original;
        std::vector<int> arrQuick = original;
        std::vector<int> arrHeap = original;
        std::vector<int> arrStd = original;

        timesMerge.push_back(measureTime(mergeSort, arrMerge, n));
        timesQuick.push_back(measureTime(quickSort, arrQuick, n));
        timesHeap.push_back(measureTime(heapSortWrapper, arrHeap, n));
        timesStdSort.push_back(measureStdSort(arrStd));
    }

    std::println("| Merge sort     | O(N log N) | {:>5.2f} ms | {:>5.2f} ms | {:>7.2f} ms | ",
                 timesMerge[0], timesMerge[1], timesMerge[2]);
    std::println("+----------------+----------------+---------+---------+-----------+");
    std::println("| Quick sort     | O(N log N) | {:>5.2f} ms | {:>5.2f} ms | {:>7.2f} ms | ",
                 timesQuick[0], timesQuick[1], timesQuick[2]);
    std::println("+----------------+----------------+---------+---------+-----------+");
    std::println("| Heap sort      | O(N log N) | {:>5.2f} ms | {:>5.2f} ms | {:>7.2f} ms | ",
                 timesHeap[0], timesHeap[1], timesHeap[2]);
    std::println("+----------------+----------------+---------+---------+-----------+");
    std::println("| std::sort      | O(N log N) | {:>5.2f} ms | {:>5.2f} ms | {:>7.2f} ms | ",
                 timesStdSort[0], timesStdSort[1], timesStdSort[2]);
    std::println("+----------------+----------------+---------+---------+-----------+");

    return 0;
}