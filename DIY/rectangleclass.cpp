

#include <iostream>
#include <stdexcept>

class Rectangle {
private:
    double length;
    double width;

public:
    // Constructor
    Rectangle() : length(0), width(0) {}

    // Setters with validation
    void setLength(double l) {
        if (l < 0) {
            throw std::invalid_argument("Length cannot be negative.");
        }
        length = l;
    }

    void setWidth(double w) {
        if (w < 0) {
            throw std::invalid_argument("Width cannot be negative.");
        }
        width = w;
    }

    // Getters for computed properties
    double area() const {
        return length * width;
    }

    double perimeter() const {
        return 2 * (length + width);
    }
};

int main() {
    try {
        Rectangle rect;
        rect.setLength(5.0);
        rect.setWidth(4.0);
        
        std::cout << "Rectangle Area: " << rect.area() << "\n";
        std::cout << "Rectangle Perimeter: " << rect.perimeter() << "\n";
        
        // This will trigger the validation error
        rect.setLength(-3.0); 
    } 
    catch (const std::invalid_argument& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
    return 0;
}