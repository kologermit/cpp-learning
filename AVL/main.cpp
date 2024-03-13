#include <iostream>
#include <vector>
#include <fstream>
#include "AVL.h"
using namespace std;
int main() {
    AVLTree<int> tree;
    ofstream out("test");
    vector<int> v = {0, -3, -1, -2, 3};
    for (int i = 0; i < v.size(); i++) {
        tree.insert(v[i]);
    }
    // cout << tree.extract_max(tree._root->_left)->_key << endl;
    tree.erase(-1);
    tree.print();
}