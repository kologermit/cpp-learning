#include <iostream>
#include "Vector.h"
// #include <vector>
using namespace std;
int main() {
    Vector<int> v(0);
    cout << "v.size: " << v.size() << endl;
    cout << "v.capacity: " << v.capacity() << endl;
    cout << "v: "; for (int i = 0; i < v.size(); i++) cout << v[i] << " "; cout << endl;
    v.pop_back();
    for (int i = 0; i < 10; i++) {
        v.push_back(i);
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