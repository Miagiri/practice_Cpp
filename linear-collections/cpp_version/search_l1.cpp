#include <algorithm>
#include <print>
#include <vector>
#include <format>

int main() {
    const std::vector<int> data = {5, 2, 8, 2, 9, 1, 2, 7, 3, 2};
    const int K = 9;

    size_t comparisons = 0;
    auto it = std::ranges::find_if(data, [&](int x) {
        ++comparisons;
        return x == K;
    });

    std::println("Array: {}", data);

    std::println("Search key K = {} ", K);

    if (it != data.end()) {
        std::println("Index of first occurrence: {}", it - data.begin());
    } else {
        std::println("Index of first occurrence: -1 (number not found)");
    }
    std::println("Number of comparisons: {} ", comparisons);

    return 0;
}