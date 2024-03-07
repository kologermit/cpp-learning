#include <iostream>
#include "AVL.h"
using namespace std;
int main() {
    AVLTree<int> tree;
    for (int i = 0; i < 10; i++) {
        tree.insert(i);
    }
    cout << "size: " << tree.size() << endl;
    // cout << "height: " << tree.height() << endl;
    for (int i = 0; i < 10; i++) {
        cout << i << " "<< tree.find(i) << endl;
    }
}