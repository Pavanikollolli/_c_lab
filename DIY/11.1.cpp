#include <iostream>
using namespace std;

template <typename T>
void swapVals(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}

int main() {
    int a = 10, b = 20;
    cout << "Before swap: a = " << a << ", b = " << b << endl;
    swapVals(a, b);
    cout << "After swap:  a = " << a << ", b = " << b << endl;
    return 0;
}