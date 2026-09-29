#include <iostream>
using namespace std;

class Tracer {
    int id;
public:
    Tracer(int i) : id(i) { cout << "  Construct #" << id << endl; }
    ~Tracer()            { cout << "  Destruct  #" << id << endl; }
};

int main() {
    cout << "Enter block\n";
    {
        Tracer a(1), b(2);
        cout << "  ...working...\n";
    }
    cout << "Left block\n\n";

    cout << "Heap-allocated Tracers (with delete):\n";
    for (int i = 10; i < 13; i++) {
        Tracer* t = new Tracer(i);
        delete t;                    // destructor runs immediately
    }

    cout << "\nHeap-allocated Tracers (forgot delete -> leak):\n";
    for (int i = 20; i < 23; i++) {
        Tracer* t = new Tracer(i);
        // delete t;   <-- forgotten! destructor never runs, memory leaks
        (void)t;
    }

    return 0;
}