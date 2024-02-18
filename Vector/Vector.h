
// ValueType имеет:
// 1) Стандартный конструктор
// 2) Конструктор копирования
// 3) Оператор присваивания
template<typename ValueType>
class Vector {
public:
    Vector();
    Vector(size_t count, const ValueType& val);
    void push_back(const ValueType& val);
    void pop_back();
    size_t size() const;

    ValueType& operator[](const int& idx);
    const ValueType& operator[](const int& idx) const;

public:
    // std::random_access_iterator_tag
    class Iterator {
        // Iterator methods
    }

    Iterator begin();
    Iterator end();

}
