#include <iostream>
#include <vector>
#include "AVL.h"
using namespace std;
int main() {
    AVLTree<int> tree;
    for (int i = 1; i <= 2000; i++) {
        tree.insert(i);
    }
    int count = 0;
    for (int i = 1; i <= 1000; i++) {
        count += tree.find(i);
        tree.erase(i);
    }
    tree.print(-999);
    cout << count << endl;
}