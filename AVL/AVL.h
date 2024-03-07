#include <algorithm>
#include <iostream>
#include <functional>

template<typename KeyType, typename CompareType = std::less<KeyType>>
class AVLTree {
private:
    class Node {
        private:
            KeyType _key;
            size_t _height;
            Node* _left;
            Node* _right;
        public:
            Node(KeyType key): _key(key), _height(0), _left(nullptr), _right(nullptr) {};
            static bool find(const Node* node, const KeyType& key);
            static size_t size(const Node* node);
            static size_t height(const Node* node);

        friend class AVLTree;
    };
    Node* _root;
    friend class Node;
public:

    AVLTree(): _root(nullptr) {};

    void insert(const KeyType& value);
    void erase(const KeyType& value);
    bool find(const KeyType& value) const;
    size_t size() const;
};

template<typename KeyType, typename CompareType>
bool AVLTree<KeyType, CompareType>::Node::find(const Node* node, const KeyType& key) {
    if (!node) {
        return false;
    }
    if (node->_key == key) {
        return true;
    }
    return find(node->_left, key) + find(node->_right, key);
}

template<typename KeyType, typename CompareType>
size_t AVLTree<KeyType, CompareType>::Node::size(const Node* node) {
    if (!node) {
        return 0;
    }
    return 1 + size(node->_right) + size(node->_left);
}

template<typename KeyType, typename CompareType>
size_t AVLTree<KeyType, CompareType>::Node::height(const Node* node) {
    if (!node) {
        return 0;
    }
    return 1 + node->_height + 
        std::max(
            node->height(node->_left),
            node->height(node->_right)
        );
}

template<typename KeyType, typename CompareType>
bool AVLTree<KeyType, CompareType>::find(const KeyType& key) const {
    return this.Node.find(this->root, key);
}

template<typename KeyType, typename CompareType>
size_t AVLTree<KeyType, CompareType>::size() const {
    return this.Node.size(this->root);
}
