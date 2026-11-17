// Experiment 3: All constructor types + Rule of 5. Check with Valgrind.
#include <iostream>
#include <cstring>
#include <utility>
using namespace std;

class Buffer {
    char* data;
    size_t size;
    string tag;
public:
    // 1. Default constructor
    Buffer() : data(nullptr), size(0), tag("default") { cout << "Default ctor\n"; }

    // 2. Parameterized constructor
    Buffer(const char* s) : size(strlen(s)), tag("param") {
        data = new char[size + 1];
        strcpy(data, s);
        cout << "Parameterized ctor: " << data << "\n";
    }

    // 3. Destructor (Rule of 5 #1)
    ~Buffer() {
        cout << "Destructor (" << tag << ")\n";
        delete[] data;
    }

    // 4. Copy constructor (#2) - deep copy
    Buffer(const Buffer& o) : size(o.size), tag("copy") {
        data = o.data ? new char[size + 1] : nullptr;
        if (data) strcpy(data, o.data);
        cout << "Copy ctor\n";
    }

    // 5. Copy assignment (#3)
    Buffer& operator=(const Buffer& o) {
        cout << "Copy assignment\n";
        if (this != &o) {
            char* nd = o.data ? new char[o.size + 1] : nullptr;
            if (nd) strcpy(nd, o.data);
            delete[] data;
            data = nd;
            size = o.size;
        }
        return *this;
    }

    // 6. Move constructor (#4)
    Buffer(Buffer&& o) noexcept : data(o.data), size(o.size), tag("move") {
        o.data = nullptr;
        o.size = 0;
        cout << "Move ctor\n";
    }

    // 7. Move assignment (#5)
    Buffer& operator=(Buffer&& o) noexcept {
        cout << "Move assignment\n";
        if (this != &o) {
            delete[] data;
            data = o.data;
            size = o.size;
            o.data = nullptr;
            o.size = 0;
        }
        return *this;
    }

    void show(const char* label) const {
        cout << "  " << label << ": " << (data ? data : "(null)") << " [size=" << size << "]\n";
    }
};

Buffer makeBuffer() { return Buffer("temporary"); }

int main() {
    cout << "\n-- Default --\n";      Buffer a;           a.show("a");
    cout << "\n-- Parameterized --\n"; Buffer b("Hello");  b.show("b");
    cout << "\n-- Copy ctor --\n";    Buffer c(b);        c.show("c");
    cout << "\n-- Move ctor --\n";    Buffer d(std::move(c)); d.show("d"); c.show("c (moved-from)");
    cout << "\n-- Copy assign --\n";  a = b;              a.show("a");
    cout << "\n-- Move assign --\n";  Buffer e("Old"); e = makeBuffer(); e.show("e");
    cout << "\n-- End of main --\n";
    return 0;
}
// Verify: g++ -g -std=c++17 exp03.cpp -o exp03 && valgrind --leak-check=full ./exp03
