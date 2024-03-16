#include <algorithm>
#include <iostream>
#include <functional>
#include <memory>
#include <cmath>
#include <stack>
template<typename KeyType, typename CompareType = std::less<KeyType> >
class AVLTree {
private:
    struct Node {
        KeyType _key;
        size_t _height = 0;
        std::shared_ptr<Node> _parent = nullptr;
        std::shared_ptr<Node> _left = nullptr;
        std::shared_ptr<Node> _right = nullptr;
        explicit Node(
            const KeyType& key, 
            const size_t height = 0,
            std::shared_ptr<Node> parent = nullptr,
            std::shared_ptr<Node> right = nullptr,
            std::shared_ptr<Node> left = nullptr
        ): 
            _key(key),
            _height(height),
            _parent(parent),
            _right(right),
            _left(left) {};
    };
    size_t _size = 0;
    CompareType _less_cmp;
    void update_height(const std::shared_ptr<Node>& node);
    void insert(const KeyType& key, std::shared_ptr<Node>& node, std::shared_ptr<Node> parent);
    bool find(const KeyType& key, const std::shared_ptr<Node>& node) const;
    void _for_each(const std::function<void(const KeyType&)>& func, const std::shared_ptr<Node>& node) const;
    void print(const KeyType& none, std::ostream& out, const std::shared_ptr<Node>& node);
    void erase(const KeyType& value, std::shared_ptr<Node>& node);
    std::shared_ptr<Node> _root = nullptr;
    std::shared_ptr<Node> extract_max(std::shared_ptr<Node>& node);
    void small_left_rotate(std::shared_ptr<Node>& node);
    void small_right_rotate(std::shared_ptr<Node>& node);
    void big_left_rotate(std::shared_ptr<Node>& node);
    void big_right_rotate(std::shared_ptr<Node>& node);
    static int diff(std::shared_ptr<Node>& node);
    void rotate(std::shared_ptr<Node>& node);
public:
    explicit AVLTree(CompareType less_cmp = CompareType()): _less_cmp(less_cmp), _root(nullptr)  {};
    void insert(const KeyType& key);
    void erase(const KeyType& value);
    bool find(const KeyType& key) const;
    void print(const KeyType& none, std::ostream& out = std::cout);
    size_t size() const;
    void for_each(const std::function<void(const KeyType&)>& func) const;
    class Iterator {
        private:
            bool _is_end;
            std::shared_ptr<Node> _begin;
            std::shared_ptr<Node> _end;
            std::shared_ptr<Node> _current;
            explicit Iterator(bool is_end=true): _is_end(is_end) {};
            void next();
            void back();
        public:
            Iterator() {};
            Iterator& operator++();
            Iterator& operator++(int);
            Iterator& operator--();
            Iterator& operator--(int);
            Iterator& operator==(const Iterator&) const;
            Iterator& operator!=(const Iterator&) const;
            const KeyType& operator*();
            friend class AVLTree;
    };
    Iterator begin();
    Iterator end();
};

template<typename KeyType, typename CompareType>
void AVLTree<KeyType, CompareType>::update_height(const std::shared_ptr<Node>& node) {
    if (!node) {
        return;
    }
    node->_height = 1 + std::max(
        (node->_left ? node->_left->_height : 0),
        (node->_right ? node->_right->_height : 0)
    );
}

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
void AVLTree<KeyType, CompareType>::print(const KeyType& none, std::ostream& out, const std::shared_ptr<Node>& node) {
    if (!node) {
        return;
    }
    out 
        << "k: " << node->_key << "; l: " 
        << (node->_left ? node->_left->_key : none) << "; r: " 
        << (node->_right ? node->_right->_key : none) << "; p: "
        << (node->_parent ? node->_parent->_key : none) << "; h: " 
        << node->_height << std::endl;
    print(none, out, node->_left);
    print(none, out, node->_right);
}

template<typename KeyType, typename CompareType>
void AVLTree<KeyType, CompareType>::print(const KeyType& none, std::ostream& out) {
    this->print(none, out, this->_root);
}

template<typename KeyType, typename CompareType>
void AVLTree<KeyType, CompareType>::_for_each(const std::function<void(const KeyType&)>& func, const std::shared_ptr<Node>& node) const {
    if (!node) {
        return;
    }
    _for_each(func, node->_left);
    func(node->_key);
    _for_each(func, node->_right);
}

template<typename KeyType, typename CompareType>
void AVLTree<KeyType, CompareType>::for_each(const std::function<void(const KeyType&)>& func) const {
    _for_each(func, this->_root);
}

template<typename KeyType, typename CompareType>
void AVLTree<KeyType, CompareType>::insert(const KeyType& key, std::shared_ptr<Node>& node, std::shared_ptr<Node> parent) {
    if (!node) {
        node = std::shared_ptr<Node>(new Node(key, 1, parent));
        ++this->_size;
        return;
    }
    if (this->_less_cmp(key, node->_key)) {
        this->insert(key, node->_left, node);
    } else if (this->_less_cmp(node->_key, key)) {
        this->insert(key, node->_right, node);
    } else {
        return;
    }
    rotate(node);
    update_height(node);
}

template<typename KeyType, typename CompareType>
std::shared_ptr<typename AVLTree<KeyType, CompareType>::Node> AVLTree<KeyType, CompareType>::extract_max(std::shared_ptr<Node>& node) {
    if (!node->_right) {
        std::shared_ptr<Node> ret = node;
        std::shared_ptr<Node> parent = node->_parent;
        node = node->_left;
        if (node) {
            node->_parent = parent;
        }
        update_height(node);
        return ret;
    }
    std::shared_ptr<Node> ret = this->extract_max(node->_right);
    update_height(node);
    return ret;
}

template<typename KeyType, typename CompareType>
void AVLTree<KeyType, CompareType>::insert(const KeyType& key) {
    this->insert(key, this->_root, nullptr);
}

template<typename KeyType, typename CompareType>
void AVLTree<KeyType, CompareType>::erase(const KeyType& key, std::shared_ptr<Node>& node) {
    if (!node) {
        return;
    }
    if (this->_less_cmp(key, node->_key)) {
        this->erase(key, node->_left);
    } else if (this->_less_cmp(node->_key, key)) {
        this->erase(key, node->_right);
    } else if (!node->_left && !node->_right) {
        --this->_size;
        node.reset();
    } else if (!node->_left && node->_right) {
        --this->_size;
        node = node->_right;
    } else if (!node->_right && node->_left) {
        --this->_size;
        node = node->_left;
    } else {
        --this->_size;
        std::shared_ptr<Node> _max = this->extract_max(node->_left);
        _max->_right = node->_right;
        if (_max->_right) {
            _max->_right->_parent = _max;
        }
        _max->_left = node->_left;
        if (_max->_left) {
            _max->_left->_parent = _max;
        }
        _max->_parent = node->_parent;
        node = _max;
    }
    rotate(node);
    update_height(node);
}

template<typename KeyType, typename CompareType>
void AVLTree<KeyType, CompareType>::small_left_rotate(std::shared_ptr<Node>& node) {
    std::shared_ptr<Node> a = node;
    std::shared_ptr<Node> a_parent = a->_parent;
    std::shared_ptr<Node> b = node->_right;
    if (b->_left) {
        b->_left->_parent = a;
    }
    a->_right = b->_left;
    update_height(a);
    b->_left = a;
    a->_parent = b;
    b->_parent = a_parent;
    update_height(b);
    node = b;
}

template<typename KeyType, typename CompareType>
void AVLTree<KeyType, CompareType>::small_right_rotate(std::shared_ptr<Node>& node) {
    std::shared_ptr<Node> a = node;
    std::shared_ptr<Node> a_parent = a->_parent;
    std::shared_ptr<Node> b = node->_left;
    if (b->_right) {
        b->_right->_parent = a;
    }
    a->_left = b->_right;
    update_height(a);
    b->_right = a;
    a->_parent = b;
    b->_parent = a_parent;
    update_height(b);
    node = b;
}

template<typename KeyType, typename CompareType>
void AVLTree<KeyType, CompareType>::big_left_rotate(std::shared_ptr<Node>& node) {
    small_right_rotate(node->_right);
    small_left_rotate(node);
}

template<typename KeyType, typename CompareType>
void AVLTree<KeyType, CompareType>::big_right_rotate(std::shared_ptr<Node>& node) {
    small_left_rotate(node->_left);
    small_right_rotate(node);
}

template<typename KeyType, typename CompareType>
int AVLTree<KeyType, CompareType>::diff(std::shared_ptr<Node>& node) {
    if (!node) {
        return 0;
    }
    return int(node->_left ? node->_left->_height : 0) - int(node->_right ? node->_right->_height : 0);
}

template<typename KeyType, typename CompareType>
void AVLTree<KeyType, CompareType>::rotate(std::shared_ptr<Node>& node) {
    if (abs(diff(node)) <= 1) {
        return;
    }
    std::cout << "kk1" << std::endl;
    if (node->_right) {
        int diff_a = diff(node), diff_b = diff(node->_right), diff_c;
        if (diff_a == -2) {
            if (diff_b == -1 || diff_b == 0) {
                small_left_rotate(node);
            } else if (diff_b == 1 && node->_right->_left) {
                diff_c = diff(node->_right->_left);
                if (diff_c >= -1 && diff_c <= 1) {
                    big_left_rotate(node);
                }
            }
        }
    }
    if (node->_left) {
        int diff_a = diff(node), diff_b = diff(node->_left), diff_c;
        if (diff_a == 2) {
            if (diff_b == 1 || diff_b == 0) {
                small_right_rotate(node);
            } else if (diff_b == -1 && node->_left->_right) {
                diff_c = diff(node->_left->_right);
                if (diff_c >= -1 && diff_c <= 1) {
                    big_right_rotate(node);
                }
            }
        }
    }
}

template<typename KeyType, typename CompareType>
void AVLTree<KeyType, CompareType>::erase(const KeyType& key) {
    this->erase(key, this->_root);
}
