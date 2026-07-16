#include <algorithm>
#include <format>
#include <print>
#include <random>
#include <ranges>
#include <unordered_map>
#include <vector>

constexpr unsigned kSeed = 12345;

int linearSearch(const std::vector<int>& arr, int key, size_t& comparisons) {
    comparisons = 0;
    auto it = std::ranges::find_if(arr, [&](int x) {
        ++comparisons;
        return x == key;
    });
    if (it != arr.end()) {
        return static_cast<int>(it - arr.begin());
    }
    return -1;
}

int binarySearch(const std::vector<int>& arr, int key, size_t& comparisons) {
    comparisons = 0;
    int binary_index = -1;
    int left = 0;
    int right = static_cast<int>(arr.size()) - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        comparisons++;

        if (arr[mid] == key) {
            binary_index = mid;
            break;
        }

        comparisons++;
        if (arr[mid] < key) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return binary_index;
}

ptrdiff_t hashSearch(const std::unordered_map<int, ptrdiff_t>& map, int key) {
    auto it = map.find(key);
    if (it != map.end()) {
        return it->second;
    }
    return -1;
}

int main() {
    size_t n = 10000;

    std::mt19937 gen(kSeed);
    std::uniform_int_distribution<int> dis(0, 99999);

    std::vector<int> arr(n);
    std::ranges::generate(arr, [&] { return dis(gen); });

    std::unordered_map<int, ptrdiff_t> map;
    for (auto [i, val] : arr | std::views::enumerate) {
        map.try_emplace(val, i);
    }

    std::vector<int> sortedArr = arr;
    std::ranges::sort(sortedArr);

    std::uniform_int_distribution<std::size_t> idx(0, n - 1);
    int key = arr[idx(gen)];

    size_t linearComparisons, binaryComparisons;
    int linearIndex, binaryIndex;
    ptrdiff_t hashIndex;

    linearIndex = linearSearch(arr, key, linearComparisons);
    binaryIndex = binarySearch(sortedArr, key, binaryComparisons);
    hashIndex = hashSearch(map, key);

    size_t bucketIdx = map.bucket(key);
    size_t chainLength = map.bucket_size(bucketIdx);

    std::println("Search key: {}\n", key);

    std::println("Linear search:");
    std::println("  Index: {}", linearIndex);
    std::println("  Comparisons: {}\n", linearComparisons);

    std::println("Binary search:");
    std::println("  Index: {}", binaryIndex);
    std::println("  Comparisons: {}\n", binaryComparisons);

    std::println("Hash table:");
    std::println("  Index: {}", hashIndex);
    std::println("  Bucket count: {}", map.bucket_count());
    std::println("  Load factor: {}\n", map.load_factor());
    std::println("  Bucket #{} chain length: {}", bucketIdx, chainLength);

    return 0;
}