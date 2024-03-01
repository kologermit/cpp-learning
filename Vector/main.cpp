#include <iostream>
#include <algorithm>
// #include <vector>
// #define Vector vector
#include "Vector.h"
using namespace std;
struct A {
    int a, b, c;
    A(int a = 0, int b = 0, int c = 0): a(a), b(b), c(c) {}
    friend std::ostream& operator<<(std::ostream& out, const A& a) {
        return out << "(" << a.a << " " << a.b << " " << a.c << ")";
    }
    ~A() {
        cout << "destr" << " ";
    }
};
int main() {
    Vector<A> v(0);
    cout << "v.size: " << v.size() << endl;
    cout << "v.capacity: " << v.capacity() << endl;
    cout << "v: "; for (int i = 0; i < v.size(); i++) cout << v[i] << " "; cout << endl;
    for (int i = 0; i < 10; i++) {
        v.emplace_back(i, i*2, i*3);
    }
    cout << "Push...\n";
    cout << "v.size: " << v.size() << endl;
    cout << "v.capacity: " << v.capacity() << endl;
    cout << "v: "; for (int i = 0; i < v.size(); i++) cout << v[i] << " "; cout << endl;
    for (int i = v.size() - 1; i >= 0; i--) {
        cout << v[i] << "; ";
        v.pop_back();
        cout << "size: " << v.size() << " ; cap: " << v.capacity() << endl;
    }
    Vector<int> v2(10);
    for (int i = 0; i < v2.size(); i++) {
        v2[i] = i;
    }
    cout << "Iterator output: ";
    for (Vector<int>::Iterator it = v2.begin(); it != v2.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
    cout << "Auto output: ";
    for (auto &number : v2) {
        cout << number << " ";
    } 
    cout << endl;
    cout << "for-each output: ";
    for_each (v2.begin(), v2.end(), [](int number){
        cout << number << " ";
    });
    cout << endl;
}