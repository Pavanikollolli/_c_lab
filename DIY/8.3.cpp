//prove the bug
#include <iostream>
using namespace std;

class Base {
public:
    Base() { cout << "Base ctor\n"; }
    ~Base() { cout << "Base dtor\n"; }          // NOT virtual -> bug
};

class Derived : public Base {
private:
    int* data;

public:
    Derived() {
        data = new int[100];                    // Derived owns heap memory
        cout << "Derived ctor (allocated 400 bytes)\n";
    }
    ~Derived() {
        delete[] data;
        cout << "Derived dtor (freed memory)\n";
    }
};

int main() {
    Base* p = new Derived();
    delete p;       // only ~Base runs, so ~Derived is skipped and data leaks
    return 0;
}
