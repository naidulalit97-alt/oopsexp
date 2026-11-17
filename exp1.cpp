// Experiment 1: Data types, constants, variables, operators and I/O in C++
#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
using namespace std;

const double PI = 3.14159265358979;   // constant
#define MAX_MARKS 100                 // macro constant

int main() {
    // ---- Data types and their sizes ----
    int age = 20;
    float height = 5.8f;
    double weight = 65.5;
    char grade = 'A';
    bool passed = true;
    string name;

    cout << "=== Data Types & Sizes ===\n";
    cout << "int    : " << sizeof(int)    << " bytes\n";
    cout << "float  : " << sizeof(float)  << " bytes\n";
    cout << "double : " << sizeof(double) << " bytes\n";
    cout << "char   : " << sizeof(char)   << " bytes\n";
    cout << "bool   : " << sizeof(bool)   << " bytes\n";
    cout << "int range: " << numeric_limits<int>::min() << " to "
         << numeric_limits<int>::max() << "\n\n";

    // ---- Input ----
    cout << "Enter your name: ";
    getline(cin, name);
    cout << "Enter two integers: ";
    int a, b;
    cin >> a >> b;

    // ---- Operators ----
    cout << "\n=== Operators (a=" << a << ", b=" << b << ") ===\n";
    cout << "Arithmetic : a+b=" << a + b << " a-b=" << a - b << " a*b=" << a * b;
    if (b != 0) cout << " a/b=" << a / b << " a%b=" << a % b;
    cout << "\n";
    cout << "Relational : a>b=" << (a > b) << " a==b=" << (a == b) << " a!=b=" << (a != b) << "\n";
    cout << "Logical    : (a>0 && b>0)=" << (a > 0 && b > 0) << " (a>0 || b>0)=" << (a > 0 || b > 0)
         << " !(a>0)=" << !(a > 0) << "\n";
    cout << "Bitwise    : a&b=" << (a & b) << " a|b=" << (a | b) << " a^b=" << (a ^ b)
         << " a<<1=" << (a << 1) << " a>>1=" << (a >> 1) << "\n";
    int c = a;
    c += b;  cout << "Assignment : c += b -> " << c << "\n";
    cout << "Inc/Dec    : ++a=" << ++a << "\n";
    cout << "             b-- = " << b << " (before)";
    b--;
    cout << ", b now " << b << "\n";
    cout << "Ternary    : max = " << (a > b ? a : b) << "\n";

    // ---- Constants ----
    double radius = 2.5;
    cout << "\n=== Constants ===\n";
    cout << fixed << setprecision(2);
    cout << "Area of circle (r=" << radius << ") = " << PI * radius * radius << "\n";
    cout << "Max marks = " << MAX_MARKS << "\n";

    // ---- Output formatting ----
    cout << "\n=== Summary ===\n";
    cout << left << setw(10) << "Name" << ": " << name << "\n"
         << setw(10) << "Age" << ": " << age << "\n"
         << setw(10) << "Height" << ": " << height << "\n"
         << setw(10) << "Weight" << ": " << weight << "\n"
         << setw(10) << "Grade" << ": " << grade << "\n"
         << setw(10) << "Passed" << ": " << boolalpha << passed << "\n";
    return 0;
}
