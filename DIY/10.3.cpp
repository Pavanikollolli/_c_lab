//records into object
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Student {
private:
    string name;
    int marks;

public:
    Student() : name(""), marks(0) {}

    void set(const string& n, int m) {
        name = n;
        marks = m;
    }

    string getName() const { return name; }
    int getMarks() const { return marks; }

    void display() const {
        cout << name << " - " << marks << endl;
    }
};

int main() {
    // Step 1: store name/marks pairs in a file
    ofstream fout("students.txt");
    if (!fout) {
        cout << "Error: could not create students.txt\n";
        return 1;
    }
    fout << "Asha 91\n";
    fout << "Ravi 78\n";
    fout << "Meera 88\n";
    fout << "Kiran 95\n";
    fout << "Divya 82\n";
    fout.close();

    // Step 2: read them back into an array of Student objects
    ifstream fin("students.txt");
    if (!fin) {
        cout << "Error: could not open students.txt\n";
        return 1;
    }

    const int MAX = 100;
    Student students[MAX];
    int n = 0;
    string name;
    int marks;

    while (n < MAX && fin >> name >> marks) {
        students[n].set(name, marks);
        n++;
    }
    fin.close();

    cout << "Read " << n << " students:\n";
    for (int i = 0; i < n; i++)
        students[i].display();

    // Step 3: find and print the topper
    if (n > 0) {
        int top = 0;
        for (int i = 1; i < n; i++)
            if (students[i].getMarks() > students[top].getMarks())
                top = i;

        cout << "\nTopper: " << students[top].getName()
             << " with " << students[top].getMarks() << " marks\n";
    }
    return 0;
}