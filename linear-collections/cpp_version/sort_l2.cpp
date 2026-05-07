#include <algorithm>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <random>
#include <vector>

int main() {
    size_t n = 10000;
    std::vector<int> original(n);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 99999);

    for (size_t i = 0; i < n; i++) {
        original[i] = dis(gen);
    }

    std::cout << "Original array (first 10 elements): ";
    for (size_t i = 0; i < 10; i++) {
        std::cout << original[i] << " ";
    }
    std::cout << "...\n";

    std::vector<int> arr1 = original;
    std::vector<int> arr2 = original;

    std::cout << "\nSorting " << n << " elements...\n\n";

    auto start = std::chrono::steady_clock::now();
    for (size_t i = 0; i < n - 1; i++) {
        for (size_t j = 0; j < n - i - 1; j++) {
            if (arr1[j] > arr1[j + 1]) {
                int temp = arr1[j];
                arr1[j] = arr1[j + 1];
                arr1[j + 1] = temp;
            }
        }
    }
    auto end = std::chrono::steady_clock::now();
    double time_taken = std::chrono::duration<double, std::milli>(end - start).count();

    std::cout << "Bubble sort:    ";
    for (size_t i = 0; i < 10; i++) {
        std::cout << arr1[i] << " ";
    }
    std::cout << "... | " << std::fixed << std::setprecision(3) << time_taken << " ms\n";

    start = std::chrono::steady_clock::now();
    std::sort(arr2.begin(), arr2.end());
    end = std::chrono::steady_clock::now();
    time_taken = std::chrono::duration<double, std::milli>(end - start).count();

    std::cout << "Built-in (sort): ";
    for (size_t i = 0; i < 10; i++) {
        std::cout << arr2[i] << " ";
    }
    std::cout << "... | " << std::fixed << std::setprecision(3) << time_taken << " ms\n";

    return 0;
}