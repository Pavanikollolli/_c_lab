//object counter
#include <iostream>
using namespace std;

class Counter {
private:
    int value;
    static int totalCreated;   // objects ever created
    static int aliveCount;     // objects currently alive

public:
    Counter() : value(0) {
        totalCreated++;
        aliveCount++;
    }

    // Copies are objects too, so count them
    Counter(const Counter& other) : value(other.value) {
        totalCreated++;
        aliveCount++;
    }

    ~Counter() { aliveCount--; }

    void increment() { value++; }
    int getValue() const { return value; }

    static int getTotalCreated() { return totalCreated; }
    static int getAlive()        { return aliveCount; }
};

// Static members must be defined outside the class
int Counter::totalCreated = 0;
int Counter::aliveCount = 0;

int main() {
    cout << "Start  -> created: " << Counter::getTotalCreated()
         << ", alive: " << Counter::getAlive() << endl;

    Counter a, b;
    {
        Counter c, d, e;
        cout << "Inner  -> created: " << Counter::getTotalCreated()
             << ", alive: " << Counter::getAlive() << endl;
    }   // c, d, e destroyed here

    cout << "After  -> created: " << Counter::getTotalCreated()
         << ", alive: " << Counter::getAlive() << endl;

    Counter* p = new Counter;
    cout << "Heap   -> created: " << Counter::getTotalCreated()
         << ", alive: " << Counter::getAlive() << endl;
    delete p;

    cout << "End    -> created: " << Counter::getTotalCreated()
         << ", alive: " << Counter::getAlive() << endl;
    return 0;
}