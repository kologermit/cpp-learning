#include <iostream>
#include "Vector.h"
using namespace std;
struct A {
    int a, b, c;
    A(int a = 0, int b = 0, int c = 0): a(a), b(b), c(c) {}
    friend std::ostream& operator<<(std::ostream& out, const A& a) {
        return out << "(" << a.a << " " << a.b << " " << a.c << ")";
    }
    ~A() {
        cout << "destr" << endl;
    }
};
int main() {
    Vector<A> v(0);
    cout << "v.size: " << v.size() << endl;
    cout << "v.capacity: " << v.capacity() << endl;
    cout << "v: "; for (int i = 0; i < v.size(); i++) cout << v[i] << " "; cout << endl;
    for (int i = 0; i < 10; i++) {
        v.emplace_back(1, 2, 3);
    }
    cout << "Push...\n";
    cout << "v.size: " << v.size() << endl;
    cout << "v.capacity: " << v.capacity() << endl;
    cout << "v: "; for (int i = 0; i < v.size(); i++) cout << v[i] << " "; cout << endl;
    for (int i = v.size() - 1; i >= 0; i--) {
        cout << v[i] << "; size: ";
        v.pop_back();
        cout << v.size() << " ; cap: " << v.capacity() << endl;
    }
}