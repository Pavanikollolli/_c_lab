//stack with overflow
#include <iostream>
using namespace std;

class Overflow {
public:
    void report() const { cout << "Error: stack overflow (stack is full)\n"; }
};

class Underflow {
public:
    void report() const { cout << "Error: stack underflow (stack is empty)\n"; }
};

class Stack {
private:
    int* arr;
    int capacity;
    int topIndex;

public:
    Stack(int cap) : capacity(cap), topIndex(-1) {
        arr = new int[capacity];
    }

    ~Stack() { delete[] arr; }

    // Block copying to avoid a double delete
    Stack(const Stack&) = delete;
    Stack& operator=(const Stack&) = delete;

    void push(int value) {
        if (topIndex == capacity - 1)
            throw Overflow();
        arr[++topIndex] = value;
    }

    int pop() {
        if (topIndex == -1)
            throw Underflow();
        return arr[topIndex--];
    }
};

int main() {
    Stack s(3);

    try {
        s.push(10);
        s.push(20);
        s.push(30);
        cout << "Pushed 3 items\n";
        s.push(40);                    // full -> throws Overflow
        cout << "Pushed 40\n";         // skipped
    }
    catch (const Overflow& e) {
        e.report();
    }

    try {
        cout << "Popped: " << s.pop() << endl;
        cout << "Popped: " << s.pop() << endl;
        cout << "Popped: " << s.pop() << endl;
        cout << "Popped: " << s.pop() << endl;   // empty -> throws Underflow
    }
    catch (const Underflow& e) {
        e.report();
    }

    cout << "Program continues safely.\n";
    return 0;
}