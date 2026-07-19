#include <algorithm>
#include <format>
#include <iostream>
#include <print>
#include <ranges>
#include <vector>

constexpr int kSearchKey = 42;

int main() {
    std::vector<int> arr;

    int line_num = 0;

    int value;
    while (std::cin >> value) {
        ++line_num;
        arr.push_back(value);
    }

    int key = kSearchKey;

    if (std::cin.bad()) {
        std::println(stderr, "ошибка чтения потока");
        return 74;
    }
    if (std::cin.fail() && !std::cin.eof()) {
        std::println(stderr, "строка {}: ожидается целое число", line_num + 1);
        return 65;
    }
    if (arr.empty()) {
        std::println(stderr, "пустой ввод");
        return 66;
    }

    std::ranges::sort(arr);

    std::println("Sorted array (first 20 elements): {}", arr | std::views::take(20));

    std::println("Search key: {}", key);

    size_t linear_compare = 0;
    auto linear_index = std::ranges::find_if(arr, [&](int x) {
        ++linear_compare;
        return x == key;
    });

    size_t binary_compare = 0;
    int binary_index = -1;
    size_t left = 0, right = arr.size() - 1;

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

    bool found_std = std::ranges::binary_search(arr, key);
    auto lb = std::ranges::lower_bound(arr, key);
    std::ptrdiff_t std_index = (lb != arr.end() && *lb == key) ? (lb - arr.begin()) : -1;

    if ((binary_index != -1) != found_std || binary_index != std_index) {
        std::println(stderr, "Cross-check failed: manual index={}, std index={}", binary_index,
                     std_index);
        return 1;
    }
    std::println("Cross-check passed: both manual and std agree");

    return 0;
}