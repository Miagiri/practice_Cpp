#include <algorithm>
#include <format>
#include <print>
#include <random>
#include <ranges>
#include <vector>

constexpr unsigned kSeed = 12345;

int main() {
    const size_t n = 10000;
    std::vector<int> arr(n);

    std::mt19937 gen(kSeed);
    std::uniform_int_distribution<int> dis(0, 99999);

    std::ranges::generate(arr, [&] { return dis(gen); });

    std::ranges::sort(arr);

    std::uniform_int_distribution<std::size_t> idx(0, n - 1);
    int key = arr[idx(gen)];

    std::println("Sorted array (first 20 elements): {}", arr | std::views::take(20));

    std::println("Search key: {}", key);

    size_t linear_compare = 0;
    auto linear_index = std::ranges::find_if(arr, [&](int x) {
        ++linear_compare;
        return x == key;
    });

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

    std::println("Linear search: {} comparisons (found at index {} )", linear_compare,
                 linear_index - arr.begin());
    std::println("Binary search: {} comparisons (found at index {} )", binary_compare,
                 binary_index);

    return 0;
}