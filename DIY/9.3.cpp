//ordering demo
#include <iostream>
#include <string>
using namespace std;

class MathError {
protected:
    string message;

public:
    MathError(const string& m = "Math error") : message(m) {}
    virtual ~MathError() {}
    virtual string what() const { return message; }
};

class DivideByZero : public MathError {
public:
    DivideByZero() : MathError("Divide by zero") {}
};

double divide(double a, double b) {
    if (b == 0)
        throw DivideByZero();
    return a / b;
}

int main() {
    // WRONG ORDER: base class first, so it catches everything
    cout << "--- Wrong order (MathError first) ---\n";
    try {
        divide(10, 0);
    }
    catch (const MathError& e) {
        cout << "Caught by MathError handler: " << e.what() << endl;
    }
    catch (const DivideByZero& e) {
        cout << "Caught by DivideByZero handler: " << e.what() << endl;   // never runs
    }

    // CORRECT ORDER: most specific (derived) first
    cout << "\n--- Correct order (DivideByZero first) ---\n";
    try {
        divide(10, 0);
    }
    catch (const DivideByZero& e) {
        cout << "Caught by DivideByZero handler: " << e.what() << endl;
    }
    catch (const MathError& e) {
        cout << "Caught by MathError handler: " << e.what() << endl;
    }

    return 0;
}