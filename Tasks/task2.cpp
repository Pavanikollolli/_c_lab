#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <exception>
using namespace std;

const int SUBJECTS = 3;
const int PASS_MARK = 40;
const string SUBJECT_NAMES[SUBJECTS] = {"Maths", "Physics", "Chemistry"};

// ---------- Custom exception for invalid marks ----------
class InvalidMarks : public exception {
private:
    string message;

public:
    InvalidMarks(const string& m) : message(m) {}
    const char* what() const noexcept override { return message.c_str(); }
};

// ---------- Base class ----------
class Student {
protected:
    string name;
    int rollNo;

public:
    Student(const string& n, int r) : name(n), rollNo(r) {}
    virtual ~Student() {}                       // virtual destructor

    // Virtual functions: overridden in Result
    virtual void displayDetails() const {
        cout << "Roll: " << rollNo << " | Name: " << name << endl;
    }
    virtual void displayMarks() const { cout << "  No marks recorded\n"; }
    virtual int getTotal() const { return 0; }
    virtual string getResult() const { return "N/A"; }
    virtual string toRecord() const { return to_string(rollNo) + " " + name; }

    string getName() const { return name; }
    int getRollNo() const { return rollNo; }
};

// ---------- Derived class ----------
class Result : public Student {
private:
    int marks[SUBJECTS];

public:
    Result(const string& n, int r, int m1, int m2, int m3) : Student(n, r) {
        int m[SUBJECTS] = {m1, m2, m3};
        for (int i = 0; i < SUBJECTS; i++) {
            if (m[i] < 0 || m[i] > 100)
                throw InvalidMarks("Invalid marks for " + name + ": " +
                                   SUBJECT_NAMES[i] + " = " + to_string(m[i]) +
                                   " (must be between 0 and 100)");
            marks[i] = m[i];
        }
    }

    void displayMarks() const override {
        cout << "  ";
        for (int i = 0; i < SUBJECTS; i++) {
            cout << SUBJECT_NAMES[i] << ": " << marks[i];
            if (i < SUBJECTS - 1) cout << ", ";
        }
        cout << endl;
    }

    int getTotal() const override {
        int total = 0;
        for (int i = 0; i < SUBJECTS; i++)
            total += marks[i];
        return total;
    }

    // Pass only if every subject is at least PASS_MARK
    string getResult() const override {
        for (int i = 0; i < SUBJECTS; i++)
            if (marks[i] < PASS_MARK)
                return "FAIL";
        return "PASS";
    }

    string toRecord() const override {
        return to_string(rollNo) + " " + name + " " + to_string(marks[0]) +
               " " + to_string(marks[1]) + " " + to_string(marks[2]);
    }
};

// ---------- Helper functions ----------
void addStudent(vector<Student*>& v, const string& n, int r,
                int m1, int m2, int m3) {
    try {
        v.push_back(new Result(n, r, m1, m2, m3));
        cout << "Added: " << n << endl;
    }
    catch (const InvalidMarks& e) {
        cout << "Error: " << e.what() << endl;
        cout << "Student not added.\n";
    }
}

void saveToFile(const vector<Student*>& v, const string& filename) {
    ofstream fout(filename.c_str());
    if (!fout) {
        cout << "Error: could not create " << filename << endl;
        return;
    }
    for (const Student* s : v)
        fout << s->toRecord() << endl;
    cout << "Saved " << v.size() << " records to " << filename << endl;
}

void loadFromFile(vector<Student*>& v, const string& filename) {
    ifstream fin(filename.c_str());
    if (!fin) {
        cout << "Error: could not open " << filename << endl;
        return;
    }

    string name;
    int roll, m1, m2, m3;
    int loaded = 0;

    while (fin >> roll >> name >> m1 >> m2 >> m3) {
        try {
            v.push_back(new Result(name, roll, m1, m2, m3));
            loaded++;
        }
        catch (const InvalidMarks& e) {
            cout << "Skipped bad record: " << e.what() << endl;
        }
    }
    cout << "Loaded " << loaded << " records from " << filename << endl;
}

void clearAll(vector<Student*>& v) {
    for (Student* s : v)
        delete s;
    v.clear();
}

int main() {
    vector<Student*> students;

    cout << "--- Adding students ---\n";
    addStudent(students, "Asha", 101, 85, 90, 78);
    addStudent(students, "Ravi", 102, 56, 42, 61);
    addStudent(students, "Meera", 103, 92, 88, 95);
    addStudent(students, "Kiran", 104, 35, 60, 48);
    addStudent(students, "Divya", 105, 70, 65, 80);
    addStudent(students, "Arun", 106, 105, 70, 60);   // invalid -> exception

    // Store the records in a file, then read them back
    cout << endl;
    saveToFile(students, "results.txt");
    clearAll(students);
    loadFromFile(students, "results.txt");

    // Runtime polymorphism: base-class pointers call the Result versions
    cout << "\n--- All Student Results (read from file) ---\n";
    for (const Student* s : students) {
        s->displayDetails();
        s->displayMarks();
        cout << "  Total: " << s->getTotal() << " / " << SUBJECTS * 100
             << " | Result: " << s->getResult() << endl << endl;
    }

    // STL algorithm + lambda: students scoring above a given total
    int cutoff = 200;
    vector<Student*> above;
    copy_if(students.begin(), students.end(), back_inserter(above),
            [cutoff](const Student* s) { return s->getTotal() > cutoff; });

    cout << "--- Students scoring above " << cutoff << " ---\n";
    for_each(above.begin(), above.end(), [](const Student* s) {
        cout << s->getName() << " (" << s->getTotal() << ")\n";
    });
    cout << "Count: " << above.size() << endl;

    // Topper using max_element with a lambda
    if (!students.empty()) {
        auto top = max_element(students.begin(), students.end(),
            [](const Student* a, const Student* b) {
                return a->getTotal() < b->getTotal();
            });
        cout << "\nTopper: " << (*top)->getName()
             << " with " << (*top)->getTotal() << endl;
    }

    clearAll(students);   // free the memory
    return 0;
}