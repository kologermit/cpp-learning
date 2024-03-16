#include <iostream>
#include <vector>
#include "AVL.h"
using namespace std;
int main() {
    AVLTree<int> tree;
    vector<int> v = {3, 1, 7, 0, 2, 5, 8};
    for (int i = 0; i < v.size(); i++) {
        tree.insert(v[i]);
    }
    tree.erase(3);
    tree.erase(2);
    tree.erase(1);
    tree.print(-999);
    // for (int i = 0; i < v.size(); ++i, ++it) {
    //     cout << i << ". " << *it << endl;
    // }
}