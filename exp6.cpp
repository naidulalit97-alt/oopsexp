// Experiment 6: Compile-time polymorphism - function overloading & operator overloading (Complex)
#include <iostream>
#include <string>
using namespace std;

// ---- Function overloading ----
int    add(int a, int b)                { return a + b; }
double add(double a, double b)          { return a + b; }
int    add(int a, int b, int c)         { return a + b + c; }
string add(const string& a, const string& b) { return a + b; }

// ---- Operator overloading ----
class Complex {
    double re, im;
public:
    Complex(double r = 0, double i = 0) : re(r), im(i) {}
    Complex operator+(const Complex& o) const { return {re + o.re, im + o.im}; }
    Complex operator-(const Complex& o) const { return {re - o.re, im - o.im}; }
    Complex operator*(const Complex& o) const { return {re * o.re - im * o.im, re * o.im + im * o.re}; }
    Complex operator/(const Complex& o) const {
        double d = o.re * o.re + o.im * o.im;
        return {(re * o.re + im * o.im) / d, (im * o.re - re * o.im) / d};
    }
    bool operator==(const Complex& o) const { return re == o.re && im == o.im; }
    Complex operator-() const { return {-re, -im}; }                 // unary minus
    Complex& operator+=(const Complex& o) { re += o.re; im += o.im; return *this; }
    Complex& operator++() { ++re; return *this; }                    // pre-increment
    Complex operator++(int) { Complex t = *this; ++re; return t; }   // post-increment
    friend ostream& operator<<(ostream& os, const Complex& c) {
        os << c.re << (c.im < 0 ? " - " : " + ") << (c.im < 0 ? -c.im : c.im) << "i";
        return os;
    }
    friend istream& operator>>(istream& is, Complex& c) { return is >> c.re >> c.im; }
};

int main() {
    cout << "=== Function overloading ===\n";
    cout << "add(2,3)        = " << add(2, 3) << "\n";
    cout << "add(2.5,3.5)    = " << add(2.5, 3.5) << "\n";
    cout << "add(1,2,3)      = " << add(1, 2, 3) << "\n";
    cout << "add(\"Hi \",\"C++\") = " << add("Hi ", "C++") << "\n";

    cout << "\n=== Operator overloading (Complex) ===\n";
    Complex a(3, 4), b(1, -2);
    cout << "a = " << a << ", b = " << b << "\n";
    cout << "a + b = " << a + b << "\n";
    cout << "a - b = " << a - b << "\n";
    cout << "a * b = " << a * b << "\n";
    cout << "a / b = " << a / b << "\n";
    cout << "-a    = " << -a << "\n";
    cout << "a == b? " << boolalpha << (a == b) << "\n";
    a += b;       cout << "a += b -> " << a << "\n";
    cout << "++a   = " << ++a << "\n";
    cout << "a++   = " << a++ << " (now " << a << ")\n";
    return 0;
}
