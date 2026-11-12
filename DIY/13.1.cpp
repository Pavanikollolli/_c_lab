//raw to smart
#include <iostream>
#include <memory>

int main() {
    int n = 5;

    // Replaces: int* arr = new int[n];
    std::unique_ptr<int[]> arr = std::make_unique<int[]>(n);

    // Populate and print the dynamic array
    for (int i = 0; i < n; ++i) {
        arr[i] = (i + 1) * 10;
        std::cout << arr[i] << " ";
    }
    std::cout << "\n";

    // No 'delete[] arr;' needed! Memory is freed automatically here.
    return 0;
}