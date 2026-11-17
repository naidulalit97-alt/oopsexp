// Experiment 8: STL containers (vector, map, unordered_map) and algorithms
// (sort, find_if, transform) to process a student marks dataset.
#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <numeric>
#include <string>
#include <iomanip>
using namespace std;

struct Student {
    int id;
    string name;
    double marks;
    string grade;
};

string gradeOf(double m) {
    if (m >= 90) return "A+";
    if (m >= 80) return "A";
    if (m >= 70) return "B";
    if (m >= 60) return "C";
    if (m >= 50) return "D";
    return "F";
}

void print(const vector<Student>& v, const string& title) {
    cout << "\n" << title << "\n";
    for (const auto& s : v)
        cout << "  " << setw(4) << s.id << setw(10) << s.name << setw(8) << s.marks << "  " << s.grade << "\n";
}

int main() {
    cout << fixed << setprecision(1) << left;
    vector<Student> students = {
        {1, "Asha", 88.5, ""}, {2, "Ravi", 72.0, ""}, {3, "Meera", 95.0, ""},
        {4, "Kiran", 45.5, ""}, {5, "Zoya", 67.0, ""}, {6, "Arjun", 81.0, ""}
    };

    // transform: compute grades
    transform(students.begin(), students.end(), students.begin(),
              [](Student s) { s.grade = gradeOf(s.marks); return s; });
    print(students, "Original with grades:");

    // sort: descending by marks
    sort(students.begin(), students.end(), [](const Student& a, const Student& b) { return a.marks > b.marks; });
    print(students, "Sorted by marks (desc):");

    // find_if: first failing student & first student above 90
    auto fail = find_if(students.begin(), students.end(), [](const Student& s) { return s.marks < 50; });
    if (fail != students.end()) cout << "\nFirst failing student: " << fail->name << "\n";
    auto topper = find_if(students.begin(), students.end(), [](const Student& s) { return s.marks >= 90; });
    if (topper != students.end()) cout << "Topper (>=90): " << topper->name << "\n";

    // statistics using accumulate
    double total = accumulate(students.begin(), students.end(), 0.0,
                              [](double acc, const Student& s) { return acc + s.marks; });
    cout << "Average marks: " << total / students.size() << "\n";
    cout << "Passed count: " << count_if(students.begin(), students.end(),
                                         [](const Student& s) { return s.marks >= 50; }) << "\n";

    // map: ordered grade -> names
    map<string, vector<string>> byGrade;
    for (const auto& s : students) byGrade[s.grade].push_back(s.name);
    cout << "\nGrade distribution (map, ordered):\n";
    for (const auto& [g, names] : byGrade) {
        cout << "  " << g << ": ";
        for (const auto& n : names) cout << n << " ";
        cout << "\n";
    }

    // unordered_map: fast lookup by id
    unordered_map<int, Student> lookup;
    for (const auto& s : students) lookup[s.id] = s;
    int q = 3;
    if (auto it = lookup.find(q); it != lookup.end())
        cout << "\nLookup id " << q << " -> " << it->second.name << " (" << it->second.marks << ")\n";
    return 0;
}
