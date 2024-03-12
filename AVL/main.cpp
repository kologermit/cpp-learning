#include <iostream>
#include "AVL.h"
using namespace std;
int main() {
    AVLTree<int> tree;
    tree.insert(1);
    tree.insert(-1);
    tree.insert(0);
    tree.insert(-2);
    tree.insert(3);
    tree.insert(2);
    tree.insert(4);
    tree.erase(1);
    tree.print();
}