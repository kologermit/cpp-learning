// Задача: сделать класс BigInteger, которой может 
// производить мат операции над ОЧЕНЬ большими числами,
// превосходящими long long

#include <iostream>
#include <vector>

class BigInteger {
    private:
        bool sign;
        // Сигнатура. число положительное или отрицательное
        // true - положительное, false - отрицательное
        std::vector<char> digits;
        void clear();
        void setZero();
        void fromString(const std::string& s);
        bool isZero() const;
        BigInteger abs() const;
    public:
        class ZeroDivisionException {
        public:
            const char* what() const {
                return "Error: Division by zero!";
            }
        };
        BigInteger();
        BigInteger(const long long& number);
        BigInteger(const std::string& s);
        BigInteger(const BigInteger& bi);
        explicit operator bool() const;
        bool operator==(const BigInteger& bi) const;
        bool operator!() const;
        bool operator!=(const BigInteger& bi) const;
        bool operator>(const BigInteger& bi) const;
        bool operator>=(const BigInteger& bi) const;
        bool operator<(const BigInteger& bi) const;
        bool operator<=(const BigInteger& bi) const;
        BigInteger& operator+=(const BigInteger& bi);
        BigInteger& operator-=(const BigInteger& bi);
        BigInteger& operator*=(const BigInteger& prod);
        BigInteger& operator/=(const BigInteger& div);
        BigInteger& operator%=(const BigInteger& div);
        BigInteger& operator++();
        BigInteger& operator--();
        BigInteger operator++(int);
        BigInteger operator--(int);
        BigInteger operator-() const;
        std::string toString() const;
        friend std::ostream& operator<<(std::ostream& out, const BigInteger& bi);
        friend std::istream& operator>>(std::istream& in, BigInteger& bi);      
};

BigInteger operator+(const BigInteger& bi1, const BigInteger& bi2);
BigInteger operator-(const BigInteger& bi1, const BigInteger& bi2);
BigInteger operator*(const BigInteger& bi1, const BigInteger& bi2);
BigInteger operator/(const BigInteger& bi1, const BigInteger& bi2);
BigInteger operator%(const BigInteger& bi1, const BigInteger& bi2);