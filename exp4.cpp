// Experiment 4: Single and Multilevel Inheritance - University Management
#include <iostream>
#include <string>
using namespace std;

class Person {
protected:
    string name;
    int age;
public:
    Person(string n, int a) : name(n), age(a) { cout << "Person ctor: " << name << "\n"; }
    virtual ~Person() { cout << "Person dtor: " << name << "\n"; }
    virtual void display() const { cout << "Name: " << name << ", Age: " << age << "\n"; }
};

// Single inheritance: Person -> Student
class Student : public Person {
protected:
    string rollNo;
    string course;
public:
    Student(string n, int a, string r, string c) : Person(n, a), rollNo(r), course(c) {
        cout << "Student ctor: " << rollNo << "\n";
    }
    ~Student() override { cout << "Student dtor: " << rollNo << "\n"; }
    void display() const override {
        Person::display();
        cout << "Roll No: " << rollNo << ", Course: " << course << "\n";
    }
};

// Multilevel inheritance: Person -> Student -> GraduateStudent
class GraduateStudent : public Student {
    string thesisTopic;
    string supervisor;
public:
    GraduateStudent(string n, int a, string r, string c, string t, string s)
        : Student(n, a, r, c), thesisTopic(t), supervisor(s) {
        cout << "GraduateStudent ctor: " << thesisTopic << "\n";
    }
    ~GraduateStudent() override { cout << "GraduateStudent dtor\n"; }
    void display() const override {
        Student::display();
        cout << "Thesis: " << thesisTopic << ", Supervisor: " << supervisor << "\n";
    }
};

int main() {
    cout << "=== Single inheritance ===\n";
    Student s("Meera", 20, "S101", "B.Tech CSE");
    s.display();

    cout << "\n=== Multilevel inheritance ===\n";
    GraduateStudent g("Arjun", 24, "G201", "M.Tech AI", "Neural Compression", "Dr. Rao");
    g.display();

    cout << "\n=== Base pointer to derived (virtual dispatch) ===\n";
    Person* p = new GraduateStudent("Kiran", 25, "G202", "PhD CS", "Graph Learning", "Dr. Iyer");
    p->display();
    delete p;

    cout << "\n=== Scope exit ===\n";
    return 0;
}
