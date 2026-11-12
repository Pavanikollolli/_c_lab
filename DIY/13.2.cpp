//shape factory
#include <iostream>
#include <memory>
#include <string>
#include <vector>

// Base class
class Shape {
public:
    virtual void draw() const = 0;
    virtual ~Shape() = default; // Virtual destructor is essential for polymorphism
};

// Derived classes
class Circle : public Shape {
public:
    void draw() const override { std::cout << "Drawing a Circle\n"; }
};

class Rectangle : public Shape {
public:
    void draw() const override { std::cout << "Drawing a Rectangle\n"; }
};

class Triangle : public Shape {
public:
    void draw() const override { std::cout << "Drawing a Triangle\n"; }
};

// Factory function
std::unique_ptr<Shape> createShape(const std::string& type) {
    if (type == "circle")    return std::make_unique<Circle>();
    if (type == "rectangle") return std::make_unique<Rectangle>();
    if (type == "triangle")  return std::make_unique<Triangle>();
    return nullptr;
}

int main() {
    std::vector<std::unique_ptr<Shape>> shapes;
    std::string input;

    std::cout << "Enter shapes (circle, rectangle, triangle) or 'done' to finish:\n";
    while (std::cin >> input && input != "done") {
        auto shape = createShape(input);
        if (shape) {
            shapes.push_back(std::move(shape));
        } else {
            std::cout << "Unknown shape. Try again.\n";
        }
    }

    std::cout << "\n--- Rendering Stored Shapes ---\n";
    for (const auto& s : shapes) {
        s->draw();
    }

    return 0;
}