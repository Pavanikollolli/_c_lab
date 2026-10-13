//money arithmetic
#include <iostream>
using namespace std;

class Money {
private:
    long rupees;
    int paise;   // always kept in 0..99

    // Total value in paise (negative amounts handled via sign of total)
    long toPaise() const { return rupees * 100 + paise; }

    void fromPaise(long total) {
        rupees = total / 100;
        paise = total % 100;
    }

public:
    Money(long r = 0, int p = 0) {
        fromPaise(r * 100 + p);   // normalises e.g. (5, 150) -> 6.50
    }

    Money operator+(const Money& other) const {
        Money result;
        result.fromPaise(toPaise() + other.toPaise());
        return result;
    }

    Money operator-(const Money& other) const {
        Money result;
        result.fromPaise(toPaise() - other.toPaise());
        return result;
    }

    void display() const {
        cout << "Rs " << rupees << "." << (paise < 10 ? "0" : "") << paise;
    }
};

int main() {
    Money a(10, 75), b(5, 50), c(3, 40);

    Money sum = a + b;           // 10.75 + 5.50 = 16.25 (carry: 125 paise -> 1 rupee)
    Money diff = a - c;          // 10.75 - 3.40 = 7.35
    Money borrow = Money(10, 25) - Money(3, 80);   // 10.25 - 3.80 = 6.45 (borrow)

    cout << "a + b = ";  sum.display();    cout << endl;
    cout << "a - c = ";  diff.display();   cout << endl;
    cout << "10.25 - 3.80 = "; borrow.display(); cout << endl;
    return 0;
}