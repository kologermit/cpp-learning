#include <iostream>
#include <functional>
#include <memory>
#include <iterator>

template<typename KeyType, typename CompareType = std::less<KeyType> >
class AVLTree {
private:
    struct Node;
    typedef std::shared_ptr<Node> NodePtr;
    typedef std::weak_ptr<Node> NodeWPtr;
    struct Node {
        KeyType _key;
        size_t _height = 0;
        NodeWPtr _parent;
        NodePtr _left;
        NodePtr _right;
        Node(
            const KeyType& key, 
            const size_t height = 0,
            std::shared_ptr<Node> parent = nullptr
        ): 
            _key(key),
            _height(height),
            _parent(parent),
            _left(nullptr),
            _right(nullptr) {};
    };
private:
    CompareType _less_cmp;
    NodePtr _root = nullptr;
    size_t _size = 0;
private:
    static void update_height(const NodePtr& node);
    void insert(const KeyType& key, NodePtr& node, NodePtr& parent);
    static void for_each(const std::function<void(const KeyType&)>& func, const NodePtr& node);
    void print(const KeyType& none, std::ostream& out, const NodePtr& node);
    void erase(const KeyType& value, NodePtr& node);
    NodePtr find(const KeyType& key, const NodePtr& node) const;
    NodePtr lower_bound(const KeyType& key, const NodePtr& node) const;
    NodePtr upper_bound(const KeyType& key, const NodePtr& node) const;
    static NodePtr extract_max(NodePtr& node);
    static void small_left_rotate(NodePtr& node);
    static void small_right_rotate(NodePtr& node);
    static void big_left_rotate(NodePtr& node);
    static void big_right_rotate(NodePtr& node);
    static int diff(NodePtr& node);
    static void rotate(NodePtr& node);
public:
    explicit AVLTree(CompareType less_cmp = CompareType()): _less_cmp(less_cmp), _root(nullptr)  {};
    void insert(const KeyType& key);
    void erase(const KeyType& value);
    void print(const KeyType& none, std::ostream& out = std::cout);
    size_t size() const;
    void for_each(const std::function<void(const KeyType&)>& func) const;
    class Iterator: public std::iterator<std::bidirectional_iterator_tag, KeyType> {
        private:
            NodeWPtr _current;
            explicit Iterator(NodePtr current): _current(current) {};
            void next();
            void back();
        public:
            class EndException: public std::exception {
            public:
                const char* what() const noexcept override {
                    return "Error: Iteranot in end";
                }
            };
            Iterator() {};
            Iterator& operator++();
            Iterator operator++(int);
            Iterator& operator--();
            Iterator operator--(int);
            bool operator==(const Iterator&) const;
            bool operator!=(const Iterator&) const;
            const KeyType& operator*();
            const KeyType* operator->();
            friend class AVLTree;
    };
    Iterator find(const KeyType& key) const;
    Iterator lower_bound(const KeyType& key) const;
    Iterator upper_bound(const KeyType& key) const;
    Iterator begin();
    Iterator end();
};

template<typename KeyType, typename CompareType>
void AVLTree<KeyType, CompareType>::update_height(const NodePtr& node) {
    if (!node) {
        return;
    }
    node->_height = 1 + std::max(
        (node->_left ? node->_left->_height : 0),
        (node->_right ? node->_right->_height : 0)
    );
}

template<typename KeyType, typename CompareType>
size_t AVLTree<KeyType, CompareType>::size() const {
    return this->_size;
}

template<typename KeyType, typename CompareType>
void AVLTree<KeyType, CompareType>::print(const KeyType& none, std::ostream& out, const NodePtr& node) {
    if (!node) {
        return;
    }
    print(none, out, node->_left);
    NodePtr parent = node->_parent.lock();
    out 
        << "k: " << node->_key << "; l: " 
        << (node->_left ? node->_left->_key : none) << "; r: " 
        << (node->_right ? node->_right->_key : none) << "; p: "
        << (parent ? parent->_key : none) << "; h: " 
        << node->_height << std::endl;
    print(none, out, node->_right);
}

template<typename KeyType, typename CompareType>
void AVLTree<KeyType, CompareType>::print(const KeyType& none, std::ostream& out) {
    this->print(none, out, this->_root);
}

template<typename KeyType, typename CompareType>
void AVLTree<KeyType, CompareType>::for_each(const std::function<void(const KeyType&)>& func, const NodePtr& node) {
    if (!node) {
        return;
    }
    for_each(func, node->_left);
    func(node->_key);
    for_each(func, node->_right);
}

template<typename KeyType, typename CompareType>
void AVLTree<KeyType, CompareType>::for_each(const std::function<void(const KeyType&)>& func) const {
    for_each(func, this->_root);
}

template<typename KeyType, typename CompareType>
void AVLTree<KeyType, CompareType>::insert(const KeyType& key, NodePtr& node, NodePtr& parent) {
    if (!node) {
        node = NodePtr(new Node(key, 1, parent));
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
std::shared_ptr<typename AVLTree<KeyType, CompareType>::Node> AVLTree<KeyType, CompareType>::extract_max(NodePtr& node) {
    if (!node->_right) {
        NodePtr ret = node;
        NodePtr parent = node->_parent.lock();
        node = node->_left;
        if (node) {
            node->_parent = parent;
        }
        update_height(node);
        return ret;
    }
    NodePtr ret = extract_max(node->_right);
    update_height(node);
    return ret;
}

template<typename KeyType, typename CompareType>
void AVLTree<KeyType, CompareType>::insert(const KeyType& key) {
    this->insert(key, this->_root, this->_root);
}

template<typename KeyType, typename CompareType>
void AVLTree<KeyType, CompareType>::erase(const KeyType& key, NodePtr& node) {
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
        NodePtr parent = node->_parent.lock();
        node = node->_right;
        node->_parent = parent;
    } else if (!node->_right && node->_left) {
        --this->_size;
        NodePtr parent = node->_parent.lock();
        node = node->_left;
        node->_parent = parent;
    } else {
        --this->_size;
        NodePtr _max = this->extract_max(node->_left);
        _max->_right = node->_right;
        if (_max->_right) {
            _max->_right->_parent = _max;
        }
        _max->_left = node->_left;
        if (_max->_left) {
            _max->_left->_parent = _max;
        }
        _max->_parent = node->_parent.lock();
        node = _max;
    }
    rotate(node);
    update_height(node);
}

template<typename KeyType, typename CompareType>
void AVLTree<KeyType, CompareType>::small_left_rotate(NodePtr& node) {
    NodePtr a = node;
    NodePtr a_parent = a->_parent.lock();
    NodePtr b = node->_right;
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
void AVLTree<KeyType, CompareType>::small_right_rotate(NodePtr& node) {
    NodePtr a = node;
    NodePtr a_parent = a->_parent.lock();
    NodePtr b = node->_left;
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
void AVLTree<KeyType, CompareType>::big_left_rotate(NodePtr& node) {
    small_right_rotate(node->_right);
    small_left_rotate(node);
}

template<typename KeyType, typename CompareType>
void AVLTree<KeyType, CompareType>::big_right_rotate(NodePtr& node) {
    small_left_rotate(node->_left);
    small_right_rotate(node);
}

template<typename KeyType, typename CompareType>
int AVLTree<KeyType, CompareType>::diff(NodePtr& node) {
    if (!node) {
        return 0;
    }
    return int(node->_left ? node->_left->_height : 0) - int(node->_right ? node->_right->_height : 0);
}

template<typename KeyType, typename CompareType>
void AVLTree<KeyType, CompareType>::rotate(NodePtr& node) {
    if (abs(diff(node)) <= 1) {
        return;
    }
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

template<typename KeyType, typename CompareType>
typename AVLTree<KeyType, CompareType>::Iterator AVLTree<KeyType, CompareType>::begin() {
    NodePtr _begin = this->_root;
    if (_begin) {
        while (_begin->_left) {
            _begin = _begin->_left;
        }
    }
    return Iterator(_begin);
}

template<typename KeyType, typename CompareType>
typename AVLTree<KeyType, CompareType>::Iterator AVLTree<KeyType, CompareType>::end() {
    return Iterator(nullptr);
}

template<typename KeyType, typename CompareType>
void AVLTree<KeyType, CompareType>::Iterator::next() {
    if (this->_current.expired()) {
        return;
    }
    NodePtr current = this->_current.lock();
    if (!current) {
        return;
    }
    if (current->_right) {
        current = current->_right;
        while (current->_left) {
            current = current->_left;
        }
    } else {
        NodePtr parent = current->_parent.lock();
        if (!parent) {
            this->_current = parent;
            return;
        }
        while (current == parent->_right) {
            current = parent;
            if (!current->_parent.lock()) {
                this->_current = current->_parent.lock();
                return;
            }
            parent = current->_parent.lock();
        }
        if (current->_right != parent) {
            current = parent;
        }
    }
    this->_current = current;
}

template<typename KeyType, typename CompareType>
void AVLTree<KeyType, CompareType>::Iterator::back() {
    if (this->_current.expired()) {
        return;
    }
    NodePtr current = this->_current.lock();
    if (!current) {
        return;
    }
    if (current->_left) {
        current = current->_left;
        while (current->_right) {
            current = current->_right;
        }
    } else {
        NodePtr parent = current->_parent.lock();
        if (!parent) {
            this->_current = parent;
            return;
        }
        while (current == parent->_left) {
            current = parent;
            if (!current->_parent) {
                this->_current = current->_parent.lock();
                return;
            }
            parent = current->_parent.lock();
        }
        if (current->_left != parent) {
            current = parent;
        }
    }
    this->_current = current;
}

template<typename KeyType, typename CompareType>
typename AVLTree<KeyType, CompareType>::Iterator& AVLTree<KeyType, CompareType>::Iterator::operator++() {
    this->next();
    return *this;
}

template<typename KeyType, typename CompareType>
typename AVLTree<KeyType, CompareType>::Iterator AVLTree<KeyType, CompareType>::Iterator::operator++(int) {
    Iterator ret = *this;
    this->next();
    return ret;
}

template<typename KeyType, typename CompareType>
typename AVLTree<KeyType, CompareType>::Iterator& AVLTree<KeyType, CompareType>::Iterator::operator--() {
    this->back();
    return *this;
}

template<typename KeyType, typename CompareType>
typename AVLTree<KeyType, CompareType>::Iterator AVLTree<KeyType, CompareType>::Iterator::operator--(int) {
    Iterator ret = *this;
    this->back();
    return ret;
}

template<typename KeyType, typename CompareType>
const KeyType& AVLTree<KeyType, CompareType>::Iterator::operator*() {
    if (this->_current.expired()) {
        throw EndException();
    }
    return this->_current.lock()->_key;
}

template<typename KeyType, typename CompareType>
const KeyType* AVLTree<KeyType, CompareType>::Iterator::operator->() {
    if (this->_current.expired()) {
        throw EndException();
    }
    return &(this->_current.lock()->_key);
}

template<typename KeyType, typename CompareType>
bool AVLTree<KeyType, CompareType>::Iterator::operator==(const Iterator& it) const {
    NodePtr first = this->_current.lock();
    NodePtr second = it._current.lock();
    return first == second;
}

template<typename KeyType, typename CompareType>
bool AVLTree<KeyType, CompareType>::Iterator::operator!=(const Iterator& it) const {
    return !this->operator==(it);
}

template<typename KeyType, typename CompareType>
typename AVLTree<KeyType, CompareType>::Iterator AVLTree<KeyType, CompareType>::find(const KeyType& key) const {
    return Iterator(this->find(key, this->_root));
}

template<typename KeyType, typename CompareType>
typename AVLTree<KeyType, CompareType>::NodePtr AVLTree<KeyType, CompareType>::find(const KeyType& key, const NodePtr& node) const {
    if (!node) {
        return node;
    }
    if (_less_cmp(key, node->_key)) {
        return find(key, node->_left);
    }
    if (_less_cmp(node->_key, key)) {
        return find(key, node->_right);
    }
    return node;
}

template<typename KeyType, typename CompareType>
typename AVLTree<KeyType, CompareType>::Iterator AVLTree<KeyType, CompareType>::lower_bound(const KeyType& key) const {
    return Iterator(this->lower_bound(key, this->_root));
}

template<typename KeyType, typename CompareType>
typename AVLTree<KeyType, CompareType>::NodePtr AVLTree<KeyType, CompareType>::lower_bound(const KeyType& key, const NodePtr& node) const {
    if (!node) {
        return node;
    }
    if (_less_cmp(node->_key, key)) {
        return lower_bound(key, node->_right);
    }
    NodePtr ret = lower_bound(key, node->_left);
    if (ret) {
        return ret;
    }
    return node;
}

template<typename KeyType, typename CompareType>
typename AVLTree<KeyType, CompareType>::Iterator AVLTree<KeyType, CompareType>::upper_bound(const KeyType& key) const {
    return Iterator(this->upper_bound(key, this->_root));
}

template<typename KeyType, typename CompareType>
typename AVLTree<KeyType, CompareType>::NodePtr AVLTree<KeyType, CompareType>::upper_bound(const KeyType& key, const NodePtr& node) const {
    if (!node) {
        return node;
    }
    if (!_less_cmp(node->_key, key)) {
        return upper_bound(key, node->_right);
    }
    NodePtr ret = upper_bound(key, node->_left);
    if (ret) {
        return ret;
    }
    return node;
}

