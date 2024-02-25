
// T имеет:
// 1) Стандартный конструктор
// 2) Конструктор копирования
// 3) Оператор присваивания
template<typename T>
class Vector {
private:
    T* begin_ptr;
    T* end_ptr;
    T* cap_ptr;
    size_t get_capacity_from_size(const size_t size) const;
public:
    class OutOfRange {
    public:
        const char* what() const {
            return "Error: Index out of range";
        }
    };
    T& operator[](const int& index);
    ~Vector();
    Vector(const size_t size = 0, const T& val = T());
    void push_back(const T& val);
    void pop_back();
    size_t size() const;
    const T& operator[](const int& idx) const;

public:
    // std::random_access_iterator_tag
    class Iterator {
        // Iterator methods
    }

    Iterator begin();
    Iterator end();

};

template<typename T>
size_t Vector<T>::get_capacity_from_size(const size_t size) const {
    size_t cap = 1;
    while (cap / 2 < size) {
        cap *= 2;
    }
    return cap;
}

template<typename T>
size_t Vector<T>::size() const {
    return this->end_ptr - this->begin_ptr;
}

template<typename T>
T& Vector<T>::operator[](const int& index) {
    if (index >= this->size()) {
        throw OutOfRange();
    }
    return *(this->begin_ptr + index);
}

template<typename T>
Vector<T>::Vector(const size_t size = 0, const T& val = T()) {
    size_t cap = this->get_capacity_from_size(size);
    this->begin_ptr = new T[cap];
    this->end_ptr = this->begin_ptr + size;
    this->cap_ptr = this->begin_ptr + cap;
    for (int i = 0; i < size; ++i) {
        *this[i] = val;
    }
}

template<typename T>
Vector<T>::~Vector() {
    delete this->begin_ptr;    
}