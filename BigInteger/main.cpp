#include <iostream>
#include "BigInteger.h"
using namespace std;
int main() {
    BigInteger a, b;
    cout << "a   : "; cin >> a;
    cout << "b   : "; cin >> b;
    cout << "a/b : " << a / b << endl;
    cout << "a%b : " << a % b << endl;
    cout << "a*b : " << a * b << endl; 
    cout << "a+b : " << a + b << endl;
    cout << "b+a : " << b + a << endl;
    cout << "1+a : " << 1 + a << endl;
    cout << "1-a : " << 1 - a << endl;
    cout << "++a : " << ++a << endl;
    cout << "--a : " << --a << endl;
    cout << "a++ : " << a++ << endl;
    cout << "a-- : " << a-- << endl;
    cout << "a-b : " << a - b << endl;
    cout << "b-a : " << b - a << endl;
    cout << "a==b: " << (a == b) << endl;
    cout << "a!=b: " << (a!=b) << endl;
    cout << "a>b : " << (a>b) << endl;
    cout << "a>=b: " << (a>=b) << endl;
    cout << "a<b : " << (a<b) << endl;
    cout << "a<=b: " << (a<=b) << endl;
    cout << "-a  : " << -a << endl;
    cout << "-b  : " << -b << endl;
    cout << "!a  : " << !a << endl;
    cout << "!b  : " << !b << endl;
    cout << "a   : " << a << endl;
    cout << "b   : " << b << endl;
}