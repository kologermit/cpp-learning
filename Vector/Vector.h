#include <cstddef>
#include <iostream>
// T имеет:
// 1) Стандартный конструктор
// 2) Конструктор копирования
// 3) Оператор присваивания
template<typename T>
class Vector {
private:
    T* begin_ptr;
    size_t _size;
    size_t _cap;
    size_t get_capacity_from_size(const size_t& size) const;
    void init(const size_t& size);
public:
    class OutOfRange {
    public:
        const char* what() const {
            return "Error: Index out of range";
        }
    };
    const T& operator[](const int& index);
    ~Vector();
    Vector();
    Vector(const size_t size);
    Vector(const size_t size, const T& val);
    void push_back(const T& val);
    void pop_back();
    size_t size() const;

public:
    // std::random_access_iterator_tag
    class Iterator {
        Iterator begin();
        Iterator end();
    };

};

template<typename T>
size_t Vector<T>::get_capacity_from_size(const size_t& size) const {
    size_t cap = 1;
    while (cap / 2 < size) {
        cap *= 2;
    }
    return cap;
}

template<typename T>
void Vector<T>::init(const size_t& size) {
    size_t cap = this->get_capacity_from_size(size);
    this->begin_ptr = new T[cap];
    this->_size = size;
    this->_cap = cap;
}

template<typename T>
size_t Vector<T>::size() const {
    return this->_size;
}

template<typename T>
const T& Vector<T>::operator[](const int& index) {
    if (index >= this->_size) {
        throw OutOfRange();
    }
    return *(this->begin_ptr + index);
}

template<typename T>
Vector<T>::Vector() {
    this->init(0);
    for (int i = 0; i < size; ++i) {
        this->begin_ptr[i] = T();
    }
}

template<typename T>
Vector<T>::Vector(const size_t size) {
    this->init(size);
    for (int i = 0; i < size; ++i) {
        this->begin_ptr[i] = T();
    }
}

template<typename T>
Vector<T>::Vector(const size_t size, const T& val) {
    this->init(size);
    for (int i = 0; i < size; ++i) {
        this->begin_ptr[i] = val;
    }
}

template<typename T>
Vector<T>::~Vector() {
    delete this->begin_ptr;    
}