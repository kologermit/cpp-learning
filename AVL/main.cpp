#include <iostream>
#include <vector>
#include <fstream>
#include "AVL.h"
using namespace std;
int main() {
    AVLTree<int> tree;
    vector<int> v = {0, -4, 4, -6, -2, 2, 6, -7, -5, -3, 1, 3, 5, 7};
    for (int i = 0; i < v.size(); i++) {
        tree.insert(v[i]);
    }
    tree.erase(-4);
    tree.print();
}