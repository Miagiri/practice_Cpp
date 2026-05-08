#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>
#include <vector>

int main() {
    const size_t n = 10000;
    std::vector<int> arr(n);

    std::mt19937 gen(
        static_cast<unsigned>(std::chrono::steady_clock::now().time_since_epoch().count()));
    std::uniform_int_distribution<int> dis(0, 99999);

    for (size_t i = 0; i < n; i++) {
        arr[i] = dis(gen);
    }

    std::sort(arr.begin(), arr.end());

    int key = arr[dis(gen) % n];

    std::cout << "Sorted array (first 20 elements):\n";
    for (size_t i = 0; i < 20; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << "\n\n";

    std::cout << "Search key: " << key << "\n\n";

    size_t linear_compare = 0;
    int linear_index = -1;
    for (size_t i = 0; i < n; i++) {
        linear_compare++;
        if (arr[i] == key) {
            linear_index = static_cast<int>(i);
            break;
        }
    }

    size_t binary_compare = 0;
    int binary_index = -1;
    size_t left = 0, right = n - 1;

    while (left <= right) {
        size_t mid = left + (right - left) / 2;
        binary_compare++;

        if (arr[mid] == key) {
            binary_index = static_cast<int>(mid);
            break;
        }

        binary_compare++;
        if (arr[mid] < key) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    std::cout << "Linear search: " << linear_compare << " comparisons (found at index "
              << linear_index << ")\n";
    std::cout << "Binary search: " << binary_compare << " comparisons (found at index "
              << binary_index << ")\n";

    return 0;
}