#include <algorithm>
#include <iostream>
#include <functional>

template<typename ValueType, typename CompareType = std::less<ValueType>>
class AVLTree {
public:
    AVLTree();

    void insert(ValueType value);
    void erase(const ValueType& value);

    size_t size() const;

public:
    // std::bidirectional_iterator_tag
    class Iterator {

    }

    Iterator begin();
    Iterator end();

    Iterator find(const ValueType& value) const;
    Iterator lower_bound(const ValueType& value) const;
    Iterator upper_bound(const ValueType& value) const;

}
