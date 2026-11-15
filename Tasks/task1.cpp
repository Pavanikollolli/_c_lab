#include <iostream>
#include <string>
using namespace std;

class Student {
private:                       // encapsulation: data is hidden
    string name;
    int rollNo;
    double marks;
    static int count;          // static member: number of Student objects alive

public:
    // Parameterized constructor
    Student(const string& n, int r, double m) : name(n), rollNo(r), marks(0) {
        setMarks(m);           // reuse the validation in setMarks
        count++;
    }

    // Copy constructor so copies are counted too
    Student(const Student& other)
        : name(other.name), rollNo(other.rollNo), marks(other.marks) {
        count++;
    }

    ~Student() { count--; }

    // ---- Overloaded functions ----
    // Version 1: set marks directly
    void setMarks(double m) {
        if (m < 0 || m > 100) {
            cout << "Invalid marks for " << name << " (must be 0-100)\n";
            return;
        }
        marks = m;
    }

    // Version 2: set marks as the average of three subjects
    void setMarks(double m1, double m2, double m3) {
        setMarks((m1 + m2 + m3) / 3.0);
    }

    // Overloaded display: without and with a label
    void display() const {
        cout << "Roll " << rollNo << " | " << name
             << " | Marks: " << marks << endl;
    }

    void display(const string& label) const {
        cout << label;
        display();
    }

    // ---- Getters (controlled access to private data) ----
    string getName() const { return name; }
    double getMarks() const { return marks; }

    // ---- Static member function ----
    static int getCount() { return count; }

    // ---- Overloaded > operator: compares students by marks ----
    bool operator>(const Student& other) const {
        return marks > other.marks;
    }

    // ---- Friend function: can read private data directly ----
    friend void printGrade(const Student& s);
};

// Definition of the static member (outside the class)
int Student::count = 0;

// Friend function: not a member, but it can access name and marks
void printGrade(const Student& s) {
    string grade;
    if (s.marks >= 90)      grade = "A+";
    else if (s.marks >= 80) grade = "A";
    else if (s.marks >= 70) grade = "B";
    else if (s.marks >= 60) grade = "C";
    else                    grade = "D";

    cout << s.name << "'s grade: " << grade << endl;
}

int main() {
    Student s1("Asha", 101, 85.5);
    Student s2("Ravi", 102, 78);
    Student s3("Meera", 103, 0);

    // Overloaded setMarks with three subject marks (average of 80, 90, 85)
    s3.setMarks(80, 90, 85);

    cout << "Total students: " << Student::getCount() << endl;

    // Overloaded display functions
    s1.display();
    s2.display();
    s3.display("Updated -> ");

    // Overloaded > operator
    cout << "\nComparison using overloaded > operator:\n";
    cout << s1.getName() << " > " << s2.getName() << " ? "
         << (s1 > s2 ? "Yes" : "No") << endl;
    cout << s2.getName() << " > " << s3.getName() << " ? "
         << (s2 > s3 ? "Yes" : "No") << endl;

    // Friend function
    cout << "\nFriend function output:\n";
    printGrade(s1);
    printGrade(s2);
    printGrade(s3);

    // Static counter changes as objects are created and destroyed
    cout << "\nStatic member demonstration:\n";
    {
        Student temp("Kiran", 104, 60);
        cout << "Inside block, total students: " << Student::getCount() << endl;
    }
    cout << "After block, total students: " << Student::getCount() << endl;

    return 0;
}