//safe withdrawal
#include <iostream>
#include <string>
using namespace std;

class InsufficientFunds {
private:
    double balance, requested;

public:
    InsufficientFunds(double b, double r) : balance(b), requested(r) {}

    void report() const {
        cout << "Insufficient funds: balance = " << balance
             << ", requested = " << requested
             << ", short by " << (requested - balance) << endl;
    }
};

class BankAccount {
private:
    string holder;
    double balance;

public:
    BankAccount(const string& h, double b) : holder(h), balance(b) {}

    void deposit(double amount) { balance += amount; }

    void withdraw(double amount) {
        if (amount > balance)
            throw InsufficientFunds(balance, amount);   // instead of return false
        balance -= amount;
    }

    void display() const {
        cout << holder << " | Balance: " << balance << endl;
    }
};

int main() {
    BankAccount acc("Asha", 5000);
    acc.display();

    try {
        acc.withdraw(2000);
        cout << "Withdrew 2000\n";
        acc.display();

        acc.withdraw(4000);      // more than the remaining 3000 -> throws
        cout << "Withdrew 4000\n";   // skipped
    }
    catch (const InsufficientFunds& e) {
        e.report();
    }

    acc.display();   // balance unchanged by the failed withdrawal
    return 0;
}