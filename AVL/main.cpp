#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include "AVL.h"
using namespace std;
int main() {
    AVLTree<int> tree;
    vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    for (int i = 0; i < v.size(); i++) {
        tree.insert(v[i]);
    }
    cout << boolalpha;
    auto it = tree.begin();
    cout << *it << endl;
    cout << *(++it) << endl;
    cout << *(--it) << endl;
}