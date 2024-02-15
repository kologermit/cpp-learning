// Задача: сделать класс BigInteger, которой может 
// производить мат операции над ОЧЕНЬ большими числами,
// превосходящими long long

#include <iostream>
#define ll long long
#define cll const ll

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
        BigInteger(cll);
        BigInteger(const std::string);
        BigInteger(const BigInteger&);
        ~BigInteger();
        BigInteger& operator+(const BigInteger&);
        BigInteger& operator-(const BigInteger&);
        BigInteger& operator&(const BigInteger&);
        BigInteger& operator/(const BigInteger&);
        BigInteger& operator%(const BigInteger&);
        BigInteger& operator+=(const BigInteger&);
        BigInteger& operator-=(const BigInteger&);
        BigInteger& operator&=(const BigInteger&);
        BigInteger& operator/=(const BigInteger&);
        BigInteger& operator%=(const BigInteger&);
        BigInteger& operator=(const BigInteger&);
        BigInteger& operator+(cll&);
        BigInteger& operator-(cll&);
        BigInteger& operator&(cll&);
        BigInteger& operator/(cll&);
        BigInteger& operator%(cll&);
        BigInteger& operator+=(cll&);
        BigInteger& operator-=(cll&);
        BigInteger& operator&=(cll&);
        BigInteger& operator/=(cll&);
        BigInteger& operator%=(cll&);
        BigInteger& operator=(cll&);
        friend std::ostream& operator<<(std::ostream& out, const BigInteger& obj);
        friend std::istream& operator>>(std::istream& in, const BigInteger& obj);
};