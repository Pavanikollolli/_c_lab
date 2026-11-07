//Employee hierarchy
#include <iostream>
#include <string>
using namespace std;

class Employee {
protected:
    string name;
    int id;

public:
    Employee(const string& n, int i) : name(n), id(i) {}

    void display() const {
        cout << "Name: " << name << ", ID: " << id << endl;
    }
};

class Manager : public Employee {
private:
    int teamSize;

public:
    Manager(const string& n, int i, int team)
        : Employee(n, i), teamSize(team) {}

    void display() const {
        cout << "[Manager]  ";
        Employee::display();
        cout << "           Team size: " << teamSize << endl;
    }
};

class Engineer : public Employee {
private:
    string skill;

public:
    Engineer(const string& n, int i, const string& s)
        : Employee(n, i), skill(s) {}

    void display() const {
        cout << "[Engineer] ";
        Employee::display();
        cout << "           Skill: " << skill << endl;
    }
};

int main() {
    Employee e("Ravi", 101);
    Manager m("Anita", 102, 8);
    Engineer g("Kiran", 103, "Embedded C");

    cout << "[Employee] "; e.display();
    m.display();
    g.display();
    return 0;
}