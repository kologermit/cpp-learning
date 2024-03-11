#include <iostream>
#include "AVL.h"
using namespace std;
int main() {
    AVLTree<int> tree;
    for (int i = 0; i < 10; i++) {
        tree.insert((i % 2 ? -i : i));
    }
    cout << "size: " << tree.size() << endl;
    cout << "height: " << tree.height() << endl;
    AVLTree<int>::Node::update_height(tree._root);
    AVLTree<int>::Node::print(tree._root);
}