// Experiment 10: CSV reader/writer with fstream; store/retrieve student records;
// file pointers: seekg, seekp, tellg, tellp.
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

struct StudentRec {
    int id;
    string name;
    string course;
    double marks;
};

const string FILE_NAME = "students.csv";

void writeCSV(const vector<StudentRec>& v) {
    ofstream out(FILE_NAME);
    if (!out) { cerr << "Cannot open file for writing\n"; return; }
    out << fixed << setprecision(1);
    out << "id,name,course,marks\n";
    for (const auto& s : v) out << s.id << "," << s.name << "," << s.course << "," << s.marks << "\n";
    cout << "Wrote " << v.size() << " records. tellp() after write = " << out.tellp() << "\n";
}

vector<StudentRec> readCSV() {
    vector<StudentRec> v;
    ifstream in(FILE_NAME);
    if (!in) { cerr << "Cannot open file for reading\n"; return v; }
    string line;
    getline(in, line);                              // skip header
    cout << "After header, tellg() = " << in.tellg() << "\n";
    while (getline(in, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string id, name, course, marks;
        getline(ss, id, ','); getline(ss, name, ','); getline(ss, course, ','); getline(ss, marks, ',');
        v.push_back({stoi(id), name, course, stod(marks)});
    }
    return v;
}

void append(const StudentRec& s) {
    ofstream out(FILE_NAME, ios::app);
    out << fixed << setprecision(1);
    out << s.id << "," << s.name << "," << s.course << "," << s.marks << "\n";
    cout << "Appended id " << s.id << ", tellp() = " << out.tellp() << "\n";
}

// Random access: jump to the Nth record (1-based) using seekg
void readRecordN(int n) {
    ifstream in(FILE_NAME);
    string line;
    getline(in, line);                              // header
    streampos start = in.tellg();                   // remember data start
    for (int i = 1; i <= n && getline(in, line); ++i) {
        if (i == n) { cout << "Record " << n << ": " << line << "\n"; return; }
    }
    cout << "Record " << n << " not found\n";
    in.clear();
    in.seekg(start);                                // rewind to data start
}

int main() {
    vector<StudentRec> data = {
        {1, "Asha", "CSE", 88.5}, {2, "Ravi", "ECE", 72.0}, {3, "Meera", "CSE", 95.0}
    };
    writeCSV(data);
    append({4, "Kiran", "ME", 64.5});

    cout << "\n-- Read all --\n";
    auto recs = readCSV();
    cout << fixed << setprecision(1);
    for (const auto& s : recs)
        cout << "  " << s.id << " " << left << setw(8) << s.name << setw(6) << s.course << s.marks << "\n";

    cout << "\n-- seekg / tellg demo --\n";
    ifstream in(FILE_NAME);
    in.seekg(0, ios::end);
    cout << "File size (seekg end, tellg) = " << in.tellg() << " bytes\n";
    in.seekg(0, ios::beg);
    string first; getline(in, first);
    cout << "Header: " << first << " | position after = " << in.tellg() << "\n";
    in.close();

    cout << "\n-- seekp demo (overwrite in place) --\n";
    fstream io(FILE_NAME, ios::in | ios::out);
    string header; getline(io, header);
    string l1;  streampos l1pos = io.tellg(); getline(io, l1);
    io.seekp(l1pos);
    cout << "tellp before overwrite = " << io.tellp() << "\n";
    io << "1,Asha,CSE,90.0";                         // same length as "1,Asha,CSE,88.5"
    io.close();

    cout << "\n-- Random access --\n";
    readRecordN(1);
    readRecordN(3);
    readRecordN(9);
    return 0;
}
