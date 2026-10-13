//safe array
#include <iostream>
#include <stdexcept>
using namespace std;

class SafeArray {
private:
    int* data;
    int size;

public:
    SafeArray(int n) : size(n) {
        data = new int[size];
        for (int i = 0; i < size; i++)
            data[i] = 0;
    }

    // Deep copy so two objects never share one buffer
    SafeArray(const SafeArray& other) : size(other.size) {
        data = new int[size];
        for (int i = 0; i < size; i++)
            data[i] = other.data[i];
    }

    SafeArray& operator=(const SafeArray& other) {
        if (this != &other) {
            delete[] data;
            size = other.size;
            data = new int[size];
            for (int i = 0; i < size; i++)
                data[i] = other.data[i];
        }
        return *this;
    }

    ~SafeArray() { delete[] data; }

    // Returns a reference so it works for both reading and writing
    int& operator[](int index) {
        if (index < 0 || index >= size)
            throw out_of_range("Index " + to_string(index) +
                               " out of range (valid: 0 to " +
                               to_string(size - 1) + ")");
        return data[index];
    }

    // const version, for use on const SafeArray objects
    const int& operator[](int index) const {
        if (index < 0 || index >= size)
            throw out_of_range("Index " + to_string(index) +
                               " out of range (valid: 0 to " +
                               to_string(size - 1) + ")");
        return data[index];
    }

    int getSize() const { return size; }
};

int main() {
    SafeArray arr(5);

    for (int i = 0; i < arr.getSize(); i++)
        arr[i] = (i + 1) * 10;

    cout << "Valid access: ";
    for (int i = 0; i < arr.getSize(); i++)
        cout << arr[i] << " ";
    cout << endl;

    try {
        cout << "Accessing arr[7]...\n";
        cout << arr[7] << endl;
    }
    catch (const out_of_range& e) {
        cout << "Error caught: " << e.what() << endl;
    }

    try {
        arr[-1] = 5;
    }
    catch (const out_of_range& e) {
        cout << "Error caught: " << e.what() << endl;
    }

    cout << "Program continues safely.\n";
    return 0;
}