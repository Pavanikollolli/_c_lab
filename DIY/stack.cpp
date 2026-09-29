#include <iostream>
using namespace std;

class Stack {
private:
    int* arr;
    int capacity;
    int topIndex;

    void grow() {
        int newCap = capacity * 2;
        int* bigger = new int[newCap];
        for (int i = 0; i <= topIndex; i++)
            bigger[i] = arr[i];
        delete[] arr;
        arr = bigger;
        capacity = newCap;
    }

public:
    Stack(int cap = 4) : capacity(cap), topIndex(-1) {
        arr = new int[capacity];
    }

    // Release the buffer
    ~Stack() {
        delete[] arr;
        cout << "Stack buffer released\n";
    }

    // Disable copying to avoid double-delete (shallow copy problem)
    Stack(const Stack&) = delete;
    Stack& operator=(const Stack&) = delete;

    void push(int value) {
        if (topIndex + 1 == capacity)
            grow();
        arr[++topIndex] = value;
    }

    int pop() {
        if (isEmpty()) {
            cout << "Stack underflow!\n";
            return -1;
        }
        return arr[topIndex--];
    }

    bool isEmpty() const { return topIndex == -1; }
};

int main() {
    Stack s;
    for (int i = 1; i <= 6; i++)   // more than initial capacity -> triggers grow()
        s.push(i * 10);

    cout << "Popping: ";
    while (!s.isEmpty())
        cout << s.pop() << " ";
    cout << endl;
    return 0;   // destructor runs here
}