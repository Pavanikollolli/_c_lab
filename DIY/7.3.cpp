//diamond problem with a virtual base
#include <iostream>
#include <string>
using namespace std;

class Person {
protected:
    string name;

public:
    Person(const string& n = "Unknown") : name(n) {
        cout << "Person constructor (" << name << ")\n";
    }
    void showName() const { cout << "Name: " << name << endl; }
};

// virtual inheritance: only one shared Person subobject
class Student : virtual public Person {
protected:
    string course;

public:
    Student(const string& n, const string& c) : Person(n), course(c) {
        cout << "Student constructor\n";
    }
};

class Employee : virtual public Person {
protected:
    double salary;

public:
    Employee(const string& n, double s) : Person(n), salary(s) {
        cout << "Employee constructor\n";
    }
};

class TA : public Student, public Employee {
public:
    // The most derived class constructs the virtual base directly
    TA(const string& n, const string& c, double s)
        : Person(n), Student(n, c), Employee(n, s) {
        cout << "TA constructor\n";
    }

    void display() const {
        showName();   // unambiguous: only one Person exists
        cout << "Course: " << course << endl;
        cout << "Stipend: " << salary << endl;
    }
};

int main() {
    TA t("Meera", "Signals and Systems", 12000);
    cout << endl;
    t.display();
    cout << "\nsizeof(TA) = " << sizeof(TA) << " bytes\n";
    return 0;
}