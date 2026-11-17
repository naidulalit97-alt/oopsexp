// Experiment 5: Runtime polymorphism - virtual functions, abstract base class, Shape hierarchy
#include <iostream>
#include <vector>
#include <memory>
#include <cmath>
#include <iomanip>
using namespace std;

class Shape {                                  // abstract base class
public:
    virtual double area() const = 0;           // pure virtual
    virtual double perimeter() const = 0;
    virtual string name() const = 0;
    virtual ~Shape() = default;
};

class Circle : public Shape {
    double r;
public:
    explicit Circle(double r) : r(r) {}
    double area() const override { return M_PI * r * r; }
    double perimeter() const override { return 2 * M_PI * r; }
    string name() const override { return "Circle"; }
};

class Rectangle : public Shape {
    double w, h;
public:
    Rectangle(double w, double h) : w(w), h(h) {}
    double area() const override { return w * h; }
    double perimeter() const override { return 2 * (w + h); }
    string name() const override { return "Rectangle"; }
};

class Triangle : public Shape {
    double a, b, c;
public:
    Triangle(double a, double b, double c) : a(a), b(b), c(c) {}
    double area() const override {             // Heron's formula
        double s = (a + b + c) / 2;
        return sqrt(s * (s - a) * (s - b) * (s - c));
    }
    double perimeter() const override { return a + b + c; }
    string name() const override { return "Triangle"; }
};

int main() {
    // Shape s;  // ERROR: abstract class cannot be instantiated
    vector<unique_ptr<Shape>> shapes;
    shapes.push_back(make_unique<Circle>(5));
    shapes.push_back(make_unique<Rectangle>(4, 6));
    shapes.push_back(make_unique<Triangle>(3, 4, 5));

    cout << fixed << setprecision(2);
    cout << left << setw(12) << "Shape" << setw(12) << "Area" << "Perimeter\n";
    double total = 0;
    for (const auto& s : shapes) {             // runtime dispatch via vtable
        cout << setw(12) << s->name() << setw(12) << s->area() << s->perimeter() << "\n";
        total += s->area();
    }
    cout << "Total area: " << total << "\n";
    return 0;
}
