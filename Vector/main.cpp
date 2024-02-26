#include <iostream>
#include "Vector.h"
using namespace std;
int main() {
    Vector<int> v(0);
    cout << "v.size: " << v.size() << endl;
    cout << "v.capacity: " << v.capacity() << endl;
    cout << "v: "; for (int i = 0; i < v.size(); i++) cout << v[i] << " "; cout << endl;
    for (int i = 0; i < 10; i++) {
        v.push_back(i);
    }
    cout << "Push...\n";
    cout << "v.size: " << v.size() << endl;
    cout << "v.capacity: " << v.capacity() << endl;
    cout << "v: "; for (int i = 0; i < v.size(); i++) cout << v[i] << " "; cout << endl;
}