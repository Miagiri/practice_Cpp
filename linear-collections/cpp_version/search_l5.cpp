#include <algorithm>
#include <iostream>
#include <random>
#include <unordered_map>
#include <vector>

int linearSearch(const std::vector<int>& arr, int key, size_t& comparisons) {
    comparisons = 0;
    for (size_t i = 0; i < arr.size(); i++) {
        comparisons++;
        if (arr[i] == key) {
            return static_cast<int>(i);
        }
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

int hashSearch(const std::unordered_map<int, int>& map, int key) {
    auto it = map.find(key);
    if (it != map.end()) {
        return it->second;
    }
    return -1;
}

int main() {
    int n = 10000;

    std::mt19937 gen(12345);
    std::uniform_int_distribution<int> dis(0, 99999);

    std::vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        arr[i] = dis(gen);
    }

    std::unordered_map<int, int> map;
    for (int i = 0; i < n; i++) {
        map.try_emplace(arr[i], i);
    }

    std::vector<int> sortedArr = arr;
    std::sort(sortedArr.begin(), sortedArr.end());

    int key = arr[dis(gen) % n];

    size_t linearComparisons, binaryComparisons;
    int linearIndex, binaryIndex, hashIndex;

    linearIndex = linearSearch(arr, key, linearComparisons);
    binaryIndex = binarySearch(sortedArr, key, binaryComparisons);
    hashIndex = hashSearch(map, key);

    size_t bucketIdx = map.bucket(key);
    size_t chainLength = map.bucket_size(bucketIdx);

    std::cout << "Search key: " << key << std::endl;
    std::cout << std::endl;

    std::cout << "Linear search:" << std::endl;
    std::cout << "  Index: " << linearIndex << std::endl;
    std::cout << "  Comparisons: " << linearComparisons << std::endl;
    std::cout << std::endl;

    std::cout << "Binary search:" << std::endl;
    std::cout << "  Index: " << binaryIndex << std::endl;
    std::cout << "  Comparisons: " << binaryComparisons << std::endl;
    std::cout << std::endl;

    std::cout << "Hash table:" << std::endl;
    std::cout << "  Index: " << hashIndex << std::endl;
    std::cout << "  Bucket count: " << map.bucket_count() << std::endl;
    std::cout << "  Load factor: " << map.load_factor() << std::endl;
    std::cout << "  Bucket #" << bucketIdx << " chain length: " << chainLength << std::endl;

    return 0;
}