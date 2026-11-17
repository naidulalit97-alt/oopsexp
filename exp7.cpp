// Experiment 7: Generic Stack and Queue using templates; tested with int, float, std::string
#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;

template <typename T>
class Stack {
    T* arr;
    int top, capacity;
    void grow() {
        capacity *= 2;
        T* n = new T[capacity];
        for (int i = 0; i <= top; ++i) n[i] = arr[i];
        delete[] arr;
        arr = n;
    }
public:
    explicit Stack(int cap = 4) : arr(new T[cap]), top(-1), capacity(cap) {}
    ~Stack() { delete[] arr; }
    Stack(const Stack&) = delete;
    Stack& operator=(const Stack&) = delete;

    void push(const T& v) { if (top + 1 == capacity) grow(); arr[++top] = v; }
    T pop() { if (empty()) throw runtime_error("Stack underflow"); return arr[top--]; }
    const T& peek() const { if (empty()) throw runtime_error("Stack empty"); return arr[top]; }
    bool empty() const { return top == -1; }
    int size() const { return top + 1; }
};

template <typename T>
class Queue {
    T* arr;
    int front, count, capacity;
public:
    explicit Queue(int cap = 4) : arr(new T[cap]), front(0), count(0), capacity(cap) {}
    ~Queue() { delete[] arr; }
    Queue(const Queue&) = delete;
    Queue& operator=(const Queue&) = delete;

    void enqueue(const T& v) {
        if (count == capacity) {               // grow, keeping order
            T* n = new T[capacity * 2];
            for (int i = 0; i < count; ++i) n[i] = arr[(front + i) % capacity];
            delete[] arr;
            arr = n; front = 0; capacity *= 2;
        }
        arr[(front + count) % capacity] = v;
        ++count;
    }
    T dequeue() {
        if (empty()) throw runtime_error("Queue underflow");
        T v = arr[front];
        front = (front + 1) % capacity;
        --count;
        return v;
    }
    bool empty() const { return count == 0; }
    int size() const { return count; }
};

template <typename T>
void testStackQueue(const string& label, T a, T b, T c) {
    cout << "--- " << label << " ---\n";
    Stack<T> s;
    s.push(a); s.push(b); s.push(c);
    cout << "Stack (LIFO) pop order: ";
    while (!s.empty()) cout << s.pop() << " ";
    cout << "\n";
    Queue<T> q;
    q.enqueue(a); q.enqueue(b); q.enqueue(c);
    cout << "Queue (FIFO) dequeue order: ";
    while (!q.empty()) cout << q.dequeue() << " ";
    cout << "\n";
}

int main() {
    testStackQueue<int>("int", 10, 20, 30);
    testStackQueue<float>("float", 1.5f, 2.5f, 3.5f);
    testStackQueue<string>("std::string", "alpha", "beta", "gamma");

    // growth + error handling
    Stack<int> big(2);
    for (int i = 1; i <= 10; ++i) big.push(i);
    cout << "Grown stack size: " << big.size() << ", top = " << big.peek() << "\n";
    try { Stack<int> e; e.pop(); }
    catch (const exception& ex) { cout << "Caught: " << ex.what() << "\n"; }
    return 0;
}
