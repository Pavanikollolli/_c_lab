#include <iostream>
using namespace std;

class Complex {
private:
    double real;
    double imag;

public:
    // Default constructor so arrays of Complex can be created
    Complex() : real(0), imag(0) {}

    // Set the real and imaginary parts
    void setData(double r, double i) {
        real = r;
        imag = i;
    }

    // Print in the form a + bi (or a - bi)
    void display() const {
        cout << real;
        if (imag >= 0)
            cout << " + " << imag << "i";
        else
            cout << " - " << -imag << "i";
        cout << endl;
    }
};

int main() {
    const int N = 4;
    Complex arr[N];

    // Fill the array
    arr[0].setData(3, 4);
    arr[1].setData(1.5, -2.5);
    arr[2].setData(0, 1);
    arr[3].setData(-7, 0);

    // Print the array
    cout << "Array of complex numbers:" << endl;
    for (int i = 0; i < N; i++) {
        cout << "arr[" << i << "] = ";
        arr[i].display();
    }

    return 0;
}