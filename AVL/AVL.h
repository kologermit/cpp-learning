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
            static bool less(const KeyType& key1, const KeyType& key2);
            static bool equal(const KeyType& key1, const KeyType& key2);
            Node(KeyType key): _key(key), _height(0), _left(nullptr), _right(nullptr) {};
            static bool find(const Node* node, const KeyType& key);
            static size_t size(const Node* node);
            static size_t height(const Node* node);
            void insert(const KeyType& key);

        friend class AVLTree;
    };
    Node* _root;
    friend class Node;
public:

    AVLTree(): _root(nullptr) {};

    void insert(const KeyType& key);
    void erase(const KeyType& value);
    bool find(const KeyType& value) const;
    size_t size() const;
};

template<typename KeyType, typename CompareType>
bool AVLTree<KeyType, CompareType>::Node::less(const KeyType& key1, const KeyType& key2) {
    CompareType cmp;
    return cmp(key1, key2);
}

template<typename KeyType, typename CompareType>
bool AVLTree<KeyType, CompareType>::Node::equal(const KeyType& key1, const KeyType& key2) {
    CompareType cmp;
    return !cmp(key1, key2) && !cmp(key2, key1);
}

template<typename KeyType, typename CompareType>
bool AVLTree<KeyType, CompareType>::Node::find(const Node* node, const KeyType& key) {
    if (!node) {
        return false;
    }
    if (equal(node->_key, key)) {
        return true;
    }
    if (node->_left) {
        if (equal(node->_left->_key, key)) {
            return true;
        }
        if (less(key, node->_key)) {
            return find(node->_left, key);
        }
    }
    if (node->_right) {
        if (equal(node->_right->_key, key)) {
            return true;
        }
        if (less(node->_key, key)) {
            return find(node->_right, key);
        }
    }
    return false;
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
void AVLTree<KeyType, CompareType>::Node::insert(const KeyType& key) {
    if (less(key, this->_key)) {
        if (!this->_left) {
            this->_left = new Node(key);
            return;
        }
        this->_left->insert(key);
    } else {
        if (!this->_right) {
            this->_right = new Node(key);
            return;
        }
        this->_right->insert(key);
    }
}

template<typename KeyType, typename CompareType>
bool AVLTree<KeyType, CompareType>::find(const KeyType& key) const {
    return Node::find(this->_root, key);
}

template<typename KeyType, typename CompareType>
size_t AVLTree<KeyType, CompareType>::size() const {
    return Node::size(this->_root);
}

template<typename KeyType, typename CompareType>
void AVLTree<KeyType, CompareType>::insert(const KeyType& key) {
    if (Node::find(this->_root, key)) {
        return;
    }
    if (!this->_root) {
        this->_root = new Node(key);
        return;
    }
    this->_root->insert(key);
}