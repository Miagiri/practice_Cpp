#include <iostream>
using namespace std;

int main() {

    int arr[] = {5, 2, 8, 2, 9, 1, 2, 7, 3, 2};
    int n = sizeof(arr) / sizeof(arr[0]);

    int K = 9;

    int index = -1;
    int count = 0;
    int i = 0;

    while (i < n && index == -1) {
        count++;
        if (arr[i] == K) {
            index = i;
        }
        i++;
    }

    cout << "Array: ";
    i = 0;
    while (i < n) {
        cout << arr[i] << " ";
        i++;
    }
    cout << endl;

    cout << "Search key K = " << K << endl;

    if (index != -1) {
        cout << "Index of first occurrence: " << index << endl;
    } else {
        cout << "Index of first occurrence: -1 (number not found)" << endl;
    }

    cout << "Number of comparisons: " << count << endl;

    return 0;
}