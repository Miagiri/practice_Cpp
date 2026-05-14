#include <iostream>
#include <vector>
#include <optional>

int main() {
    const std::vector<int> data = {5, 2, 8, 2, 9, 1, 2, 7, 3, 2};
    const int K = 9;
    
    size_t comparisons = 0;
    std::optional<size_t> found;
    
    for (size_t i = 0; i < data.size(); ++i) {
        ++comparisons;
        if (data[i] == K) {
            found = i;
            break;
        }
    }
    
    std::cout << "Array: ";
    for (const auto& x : data) {
        std::cout << x << ' ';
    }
    std::cout << '\n';
    
    std::cout << "Search key K = " << K << '\n';
    
    if (found.has_value()) {
        std::cout << "Index of first occurrence: " << *found << '\n';
    } else {
        std::cout << "Index of first occurrence: -1 (number not found)\n";
    }
    std::cout << "Number of comparisons: " << comparisons << '\n';
    
    return 0;
}