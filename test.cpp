#include <iostream>
using namespace std;
int main() {
    short* ptr;
    delete ptr;
    cout << *ptr;
    return 0;
}