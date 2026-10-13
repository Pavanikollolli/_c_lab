//friend comparison
#include <iostream>
using namespace std;

class Time {
private:
    int hh, mm;

public:
    Time(int h = 0, int m = 0) : hh(h), mm(m) {}

    void display() const {
        if (hh < 10) cout << '0';
        cout << hh << ":";
        if (mm < 10) cout << '0';
        cout << mm;
    }

    // friend: can access private hh and mm
    friend Time laterOf(Time t1, Time t2);
};

Time laterOf(Time t1, Time t2) {
    if (t1.hh > t2.hh) return t1;
    if (t1.hh < t2.hh) return t2;
    return (t1.mm >= t2.mm) ? t1 : t2;   // same hour: compare minutes
}

int main() {
    Time a(9, 45), b(14, 5), c(14, 30);

    cout << "Later of ";  a.display(); cout << " and "; b.display();
    cout << " is ";       laterOf(a, b).display(); cout << endl;

    cout << "Later of ";  b.display(); cout << " and "; c.display();
    cout << " is ";       laterOf(b, c).display(); cout << endl;

    return 0;
}