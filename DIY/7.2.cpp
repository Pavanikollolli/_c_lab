#include <iostream>
#include <string>
using namespace std;

class Shape {
protected:
    string color;

public:
    Shape(const string& c) : color(c) {
        cout << "Shape constructor (color = " << color << ")\n";
    }
    ~Shape() { cout << "Shape destructor\n"; }
};

class Polygon : public Shape {
protected:
    int sides;

public:
    Polygon(const string& c, int s) : Shape(c), sides(s) {
        cout << "Polygon constructor (sides = " << sides << ")\n";
    }
    ~Polygon() { cout << "Polygon destructor\n"; }
};

class Rectangle : public Polygon {
private:
    double width;

public:
    Rectangle(const string& c, int s, double w) : Polygon(c, s), width(w) {
        cout << "Rectangle constructor (width = " << width << ")\n";
    }
    ~Rectangle() { cout << "Rectangle destructor\n"; }

    void display() const {
        cout << "Rectangle: color=" << color << ", sides=" << sides
             << ", width=" << width << endl;
    }
};

int main() {
    cout << "Creating Rectangle:\n";
    {
        Rectangle r("Blue", 4, 5.5);
        r.display();
        cout << "\nLeaving scope:\n";
    }
    return 0;
}