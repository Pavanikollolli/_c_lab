//generic utilities
#include <iostream>
using namespace std;

template <typename T>
void swapVals(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}

template <typename T>
T findMax(T arr[], int n) {
    T maxVal = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > maxVal)
            maxVal = arr[i];
    return maxVal;
}

int main() {
    // int
    int a = 10, b = 20;
    cout << "Before swap: a = " << a << ", b = " << b << endl;
    swapVals(a, b);
    cout << "After swap:  a = " << a << ", b = " << b << endl;

    int nums[] = {4, 17, 9, 25, 3};
    cout << "Max of int array: " << findMax(nums, 5) << endl;

    // double
    double x = 1.5, y = 9.75;
    cout << "\nBefore swap: x = " << x << ", y = " << y << endl;
    swapVals(x, y);
    cout << "After swap:  x = " << x << ", y = " << y << endl;

    double vals[] = {2.5, 8.25, 3.14, 7.0};
    cout << "Max of double array: " << findMax(vals, 4) << endl;

    return 0;
}