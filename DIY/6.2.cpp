//fraction I/O
#include <iostream>
using namespace std;

class Fraction {
private:
    int num, den;

    static int gcd(int a, int b) {
        a = a < 0 ? -a : a;
        b = b < 0 ? -b : b;
        while (b != 0) {
            int t = a % b;
            a = b;
            b = t;
        }
        return a;
    }

    // Divide by GCD and keep the denominator positive
    void simplify() {
        if (den == 0) {
            cout << "Error: zero denominator, setting to 0/1\n";
            num = 0;
            den = 1;
            return;
        }
        int g = gcd(num, den);
        if (g != 0) {
            num /= g;
            den /= g;
        }
        if (den < 0) {
            num = -num;
            den = -den;
        }
    }

public:
    Fraction(int n = 0, int d = 1) : num(n), den(d) {
        simplify();   // auto-simplify on construction
    }

    friend ostream& operator<<(ostream& out, const Fraction& f) {
        if (f.den == 1)
            out << f.num;
        else
            out << f.num << "/" << f.den;
        return out;
    }

    friend istream& operator>>(istream& in, Fraction& f) {
        char slash;
        in >> f.num >> slash >> f.den;   // expects input like 6/8
        f.simplify();
        return in;
    }
};

int main() {
    Fraction a(6, 8), b(10, 5), c(-4, -12), d(3, -9);

    cout << "6/8    -> " << a << endl;   // 3/4
    cout << "10/5   -> " << b << endl;   // 2
    cout << "-4/-12 -> " << c << endl;   // 1/3
    cout << "3/-9   -> " << d << endl;   // -1/3

    Fraction f;
    cout << "\nEnter a fraction (e.g. 15/25): ";
    cin >> f;
    cout << "Simplified: " << f << endl;
    return 0;
}