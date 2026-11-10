//abstarct account
#include <iostream>
#include <string>
using namespace std;

class Account {
protected:
    string holder;
    double balance;

public:
    Account(const string& h, double b) : holder(h), balance(b) {}
    virtual ~Account() {}

    // pure virtual: makes Account abstract
    virtual double calculateInterest() const = 0;

    virtual string type() const = 0;

    void display() const {
        cout << type() << " | " << holder
             << " | Balance: " << balance
             << " | Interest: " << calculateInterest() << endl;
    }
};

class Savings : public Account {
public:
    Savings(const string& h, double b) : Account(h, b) {}
    double calculateInterest() const override { return balance * 0.04; }   // 4%
    string type() const override { return "Savings"; }
};

class Current : public Account {
public:
    Current(const string& h, double b) : Account(h, b) {}
    double calculateInterest() const override { return balance * 0.01; }   // 1%
    string type() const override { return "Current"; }
};

int main() {
    const int N = 4;
    Account* accounts[N] = {
        new Savings("Asha", 10000),
        new Current("Ravi", 25000),
        new Savings("Meera", 5000),
        new Current("Kiran", 8000)
    };

    double total = 0;
    for (int i = 0; i < N; i++) {
        accounts[i]->display();                    // runtime polymorphism
        total += accounts[i]->calculateInterest();
    }
    cout << "Total interest payable: " << total << endl;

    for (int i = 0; i < N; i++)
        delete accounts[i];                        // safe: virtual destructor

    return 0;
}
