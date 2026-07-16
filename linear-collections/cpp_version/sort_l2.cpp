#include <algorithm>
#include <chrono>
#include <format>
#include <print>
#include <random>
#include <ranges>
#include <vector>

constexpr unsigned kSeed = 12345;

int main() {
    size_t n = 10000;
    std::vector<int> original(n);

    std::mt19937 gen(kSeed);
    std::uniform_int_distribution<> dis(0, 99999);

    std::ranges::generate(original, [&] { return dis(gen); });

    std::println("Original array (first 10 elements): {}", original | std::views::take(10));

    std::vector<int> arr1 = original;
    std::vector<int> arr2 = original;

    std::println("Sorting {} elements...", n);

    auto start = std::chrono::steady_clock::now();
    for (size_t i = 0; i < n - 1; i++) {
        for (size_t j = 0; j < n - i - 1; j++) {
            if (arr1[j] > arr1[j + 1]) {
                std::swap(arr1[j], arr1[j + 1]);
            }
        }
    }
    auto end = std::chrono::steady_clock::now();
    double time_taken = std::chrono::duration<double, std::milli>(end - start).count();

    std::println("Bubble sort: {}", arr1 | std::views::take(10));
    std::println("... | {:.3f}  ms", time_taken);

    start = std::chrono::steady_clock::now();
    std::ranges::sort(arr2);
    end = std::chrono::steady_clock::now();
    time_taken = std::chrono::duration<double, std::milli>(end - start).count();

    std::println("Built-in (sort): {}", arr2 | std::views::take(10));
    std::println("... | {:.3f}  ms", time_taken);

    return 0;
}