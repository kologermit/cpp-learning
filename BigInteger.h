// Задача: сделать класс BigInteger, которой может 
// производить мат операции над ОЧЕНЬ большими числами,
// превосходящими long long

#include <iostream>
#define ll long long

class BigInteger {
    private:
        bool sign;
        // Сигнатура. число положительное или отрицательное
        // true - положительное, false - отрицательное
        int size;
        // Размер числа
        short* num;
        // Само число. Хранится ввиде массива цифр

    public:
        BigInteger(ll);
        BigInteger(std::string);
        BigInteger(const BigInteger&);
        ~BigInteger();
        std::string toString();
        BigInteger& operator+(BigInteger&);
        BigInteger& operator-(BigInteger&);
        BigInteger& operator&(BigInteger&);
        BigInteger& operator/(BigInteger&);
        BigInteger& operator%(BigInteger&);
        BigInteger& operator+=(BigInteger&);
        BigInteger& operator-=(BigInteger&);
        BigInteger& operator&=(BigInteger&);
        BigInteger& operator/=(BigInteger&);
        BigInteger& operator%=(BigInteger&);
        BigInteger& operator=(const BigInteger&);
        BigInteger& operator+(ll&);
        BigInteger& operator-(ll&);
        BigInteger& operator&(ll&);
        BigInteger& operator/(ll&);
        BigInteger& operator%(ll&);
        BigInteger& operator+=(ll&);
        BigInteger& operator-=(ll&);
        BigInteger& operator&=(ll&);
        BigInteger& operator/=(ll&);
        BigInteger& operator%=(ll&);
        BigInteger& operator=(ll&);
        friend std::ostream& operator<<(std::ostream& out, BigInteger& obj);
        friend std::istream& operator>>(std::istream& in, BigInteger& obj);
};