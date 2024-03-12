#include <algorithm>
#include <iostream>
#include <functional>
#include <memory>

template<typename KeyType, typename CompareType = std::less<KeyType> >
class AVLTree {
private:
    struct Node {
        KeyType _key;
        size_t _height;
        std::shared_ptr<Node> _left = nullptr;
        std::shared_ptr<Node> _right = nullptr;
        Node(const KeyType& key, const size_t height = 0): _key(key), _height(height) {};
        ~Node() {this->_left.reset(); this->_right.reset();};
    };
    std::shared_ptr<Node> _root = nullptr;
    size_t _size = 0;
    CompareType _less_cmp;
    void insert(const KeyType& key, std::shared_ptr<Node>& node);
    bool find(const KeyType& key, const std::shared_ptr<Node>& node) const;
    void print(std::ostream& out, const std::shared_ptr<Node>& node);
    void erase(const KeyType& value, std::shared_ptr<Node>& node);
    std::shared_ptr<Node>& extract_max(std::shared_ptr<Node>& node);
public:

    AVLTree(CompareType less_cmp = CompareType()): _less_cmp(less_cmp), _root(nullptr) {};

    void insert(const KeyType& key);
    void erase(const KeyType& value);
    bool find(const KeyType& key) const;
    size_t size() const;
    void print(std::ostream& out = std::cout);
};

template<typename KeyType, typename CompareType>
bool AVLTree<KeyType, CompareType>::find(const KeyType& key, const std::shared_ptr<Node>& node) const {
    if (!node) {
        return false;
    }
    if (this->_less_cmp(key, node->_key)) {
        return find(key, node->_left);
    }
    if (this->_less_cmp(node->_key, key)) {
        return find(key, node->_right);
    }
    return true;
}

template<typename KeyType, typename CompareType>
bool AVLTree<KeyType, CompareType>::find(const KeyType& key) const {
    return find(key, this->_root);
}

template<typename KeyType, typename CompareType>
size_t AVLTree<KeyType, CompareType>::size() const {
    return this->_size;
}

template<typename KeyType, typename CompareType>
void AVLTree<KeyType, CompareType>::print(std::ostream& out, const std::shared_ptr<Node>& node) {
    if (!node) {
        return;
    }
    out 
        << "key: " << node->_key << "; left: " 
        << (node->_left ? node->_left->_key : -999) << "; right: " 
        << (node->_right ? node->_right->_key : -999) << "; height: "
        << node->_height << std::endl;
    print(out, node->_left);
    print(out, node->_right);
}

template<typename KeyType, typename CompareType>
void AVLTree<KeyType, CompareType>::print(std::ostream& out) {
    print(out, this->_root);
}

template<typename KeyType, typename CompareType>
void AVLTree<KeyType, CompareType>::insert(const KeyType& key, std::shared_ptr<Node>& node) {
    if (!node) {
        node = std::make_shared<Node>(key, 1);
        ++this->_size;
        return;
    }
    if (this->_less_cmp(key, node->_key)) {
        this->insert(key, node->_left);
    } else if (this->_less_cmp(node->_key, key)) {
        this->insert(key, node->_right);
    } else {
        return;
    }
    node->_height = std::max(
        (node->_left ? node->_left->_height : 0),
        (node ->_right ? node->_right->_height : 0)
    ) + 1;
}

template<typename KeyType, typename CompareType>
std::shared_ptr<typename AVLTree<KeyType, CompareType>::Node>& AVLTree<KeyType, CompareType>::extract_max(std::shared_ptr<Node>& node) {
    if (!node->_right) {
        return node;
    }
    return this->extract_max(node->_right);
}

template<typename KeyType, typename CompareType>
void AVLTree<KeyType, CompareType>::insert(const KeyType& key) {
    this->insert(key, this->_root);
}

template<typename KeyType, typename CompareType>
void AVLTree<KeyType, CompareType>::erase(const KeyType& key, std::shared_ptr<Node>& node) {
    if (!node) {
        return;
    }
    if (this->_less_cmp(key, node->_key)) {
        this->erase(key, node->_left);
        return;
    }
    if (this->_less_cmp(node->_key, key)) {
        this->erase(key, node->_right);
        return;
    }
    --this->_size;
    if (!node->_left && !node->_right) {
        node.reset();
        return;
    }
    if (!node->_left && node->_right) {
        node = node->_right;
        return;
    }
    if (!node->_right && node->_left) {
        node = node->_left;
        return;
    }
    std::shared_ptr<Node>* _max = &this->extract_max(node->_left);
    node->_key = (*_max)->_key;
    if ((*_max)->_left) {
        (*_max) = (*_max)->_left;
    } else {
        _max->reset();
    }
}

template<typename KeyType, typename CompareType>
void AVLTree<KeyType, CompareType>::erase(const KeyType& key) {
    this->erase(key, this->_root);
}