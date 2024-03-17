#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include "AVL.h"
using namespace std;

int main() {
    AVLTree<int> tree;
    int count = 100;
    for (int i = 0; i < count; i++) {
        tree.insert(i);
    }
    cout << "1. size: " << tree.size() << endl;
    for (int i = 0; i < count / 2; i++) {
        tree.find(i);
        tree.erase(i);
        tree.find(i + count / 2);
        tree.erase(i + count / 2);
    }
    tree.for_each([](const int& x) {
        cout << x * 2 << endl;
    });
    cout << "2. size: " << tree.size() << endl;
    for (int i = 0; i < count; i++) {
        tree.insert(i);
    }
    cout << "3. size: " << tree.size() << endl;
    for (auto it = tree.begin(); it != tree.end(); ++it) {
        cout << *it * 4 << endl;
    }
    cout << "4. size: " << tree.size() << endl;
    
}