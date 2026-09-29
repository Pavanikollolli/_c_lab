#include <iostream>

class Complex {
private:
    double real;
    double imag;

public:
    // Method to set data members
    void setData(double r, double i) {
        real = r;
        imag = i;
    }

    // Method to print the complex number
    void display() const {
        std::cout << real << " + " << imag << "i" << "\n";
    }
};

int main() {
    // Create a small array of complex numbers
    Complex numArr[3];

    // Initialize the numbers
    numArr[0].setData(2.5, 4.0);
    numArr[1].setData(-1.0, 7.5);
    numArr[2].setData(0.0, 3.2);

    // Print the array
    std::cout << "Complex Numbers List:\n";
    for (int i = 0; i < 3; i++) {
        std::cout << "Number " << i + 1 << ": ";
        numArr[i].display();
    }

    return 0;
}