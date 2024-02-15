// Задача: сделать класс BigInteger, которой может 
// производить мат операции над ОЧЕНЬ большими числами,
// превосходящими long long

#include <iostream>

class BigInteger {
    private:
        bool sign;
        int size;
        short* number;

    public:
        BigInteger();
        BigInteger(const long long n);
        BigInteger(std::string);
        BigInteger* operator+(BigInteger*);
        BigInteger* operator-(BigInteger*);
        BigInteger* operator*(BigInteger*);
        BigInteger* operator/(BigInteger*);
        BigInteger* operator%(BigInteger*);
        BigInteger* operator+=(BigInteger*);
        BigInteger* operator-=(BigInteger*);
        BigInteger* operator*=(BigInteger*);
        BigInteger* operator/=(BigInteger*);
        BigInteger* operator%=(BigInteger*);
        BigInteger* operator=(BigInteger*);
        BigInteger* operator+(const long long*);
        BigInteger* operator-(const long long*);
        BigInteger* operator*(const long long*);
        BigInteger* operator/(const long long*);
        BigInteger* operator%(const long long*);
        BigInteger* operator+=(const long long*);
        BigInteger* operator-=(const long long*);
        BigInteger* operator*=(const long long*);
        BigInteger* operator/=(const long long*);
        BigInteger* operator%=(const long long*);
        BigInteger* operator=(const long long*);
        friend std::ostream& operator<<(std::ostream& out, const BigInteger& obj);
        friend std::istream& operator>>(std::istream& in, BigInteger& obj);
};

int main() {

}