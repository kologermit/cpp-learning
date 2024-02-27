#include <cstddef>
#include <iostream>
#include <exception>
// T имеет:
// 1) Стандартный конструктор
// 2) Конструктор копирования
// 3) Оператор присваивания
template<typename T>
class Vector {
private:
    T* _begin_ptr;
    size_t _size;
    size_t _capacity;
    static size_t get_capacity_from_size(const size_t& size);
    void init(const size_t& size, const size_t& cap = -1);
    void double_memory();
public:
    class OutOfRangeException: public std::exception {
    public:
        const char* what() const noexcept override {
            return "Error: Index out of range";
        }
    };
    const T& operator[](const size_t& index) const;
    T& operator[](const size_t& index);
    ~Vector();
    Vector(const size_t size = 0, const T& val = T());
    void push_back(const T& val);
    template<typename... Args>
    void emplace_back(Args&&... args);
    void pop_back();
    size_t size() const;
    size_t capacity() const;

public:
    // std::random_access_iterator_tag
    class Iterator {
        Iterator begin();
        Iterator end();
    };

};

template<typename T>
size_t Vector<T>::get_capacity_from_size(const size_t& size) {
    size_t capacity = 1;
    while (capacity < size) {
        capacity *= 2;
    }
    return capacity;
}

template<typename T>
void Vector<T>::init(const size_t& size, const size_t& cap) {
    size_t capacity = cap == -1 ? this->get_capacity_from_size(size) : cap;
    this->_begin_ptr = new T[capacity];
    this->_size = size;
    this->_capacity = capacity;
}

template<typename T>
void Vector<T>::double_memory() {
    T* tmp_ptr = this->_begin_ptr;
    this->init(this->_size + 1, this->_capacity * 2);
    for (size_t i = 0; i < this->_size - 1; ++i) {
        this->_begin_ptr[i] = tmp_ptr[i];
    }
    delete[] tmp_ptr;
}

template<typename T>
size_t Vector<T>::size() const {
    return this->_size;
}

template<typename T>
size_t Vector<T>::capacity() const {
    return this->_capacity;
}

template<typename T>
const T& Vector<T>::operator[](const size_t& index) const {
    if (index >= this->_size || index < 0) {
        throw OutOfRangeException();
    }
    return this->_begin_ptr[index];
}

template<typename T>
T& Vector<T>::operator[](const size_t& index) {
    if (index >= this->_size) {
        throw OutOfRangeException();
    }
    return this->_begin_ptr[index];
}

template<typename T>
Vector<T>::Vector(const size_t size, const T& val) {
    this->init(size);
    for (size_t i = 0; i < size; ++i) {
        this->_begin_ptr[i] = val;
    }
}

template<typename T>
Vector<T>::~Vector() {
    delete[] this->_begin_ptr;    
}

template<typename T>
void Vector<T>::push_back(const T& val) {
    if (this->_size + 1 == this->_capacity) {
        this->double_memory();
        this->_begin_ptr[this->_size - 1] = val;
        return;
    }
    this->_begin_ptr[this->_size] = val;
    ++this->_size;
}

template<typename T>
template<typename... Args>
void Vector<T>::emplace_back(Args&&... args) {
    if (this->_size + 1 == this->_capacity) {
        this->double_memory();
        this->_begin_ptr[this->_size - 1] = T(args...);
        return;
    }
    this->_begin_ptr[this->_size] = T(args...);
    ++this->_size;
}

template<typename T>
void Vector<T>::pop_back() {
    --this->_size;
    if (this->_size <= this->_capacity / 4 && this->_capacity >= 4) {
        T* tmp_ptr = this->_begin_ptr;
        this->init(this->_size, this->_capacity / 2);
        for (size_t i = 0; i < this->_size; i++) {
            this->_begin_ptr[i] = tmp_ptr[i];
        }
        delete[] tmp_ptr;
    }
}