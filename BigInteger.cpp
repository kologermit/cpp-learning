#include "BigInteger.h"
#include <iostream>
#include <cmath>

BigInteger::BigInteger(ll n = 0) {
    ll n2 = abs(n);
    this->size = 0;
    this->sign = n >= 0;
    while (n2) {
        n2 /= 10;
        this->size++;
    }
    if (!this->size) {
        this->size = 1;
        this->num = new short[1];
        this->num[0] = 0;
        return;
    }
    this->num = new short[this->size];
    n2 = abs(n);
    for (int i = 0; i < this->size; i++) {
        this->num[i] = n2 % 10;
        n2 /= 10;   
    }
}

BigInteger::BigInteger(const BigInteger& bi) {
    this->size = bi.size;
    this->num = new short[this->size];
    this->sign = this->sign;
    for (int i = 0; i < this->size; i++) {
        this->num[i] = bi.num[i];
    }
}

BigInteger::BigInteger(std::string s) {
    if (s == "0") {
        this->sign = true;
        this->size = 1;
        this->num = new short[1];
        this->num[0] = 0;
        return;
    }
    this->sign = true;
    this->size = s.size();
    this->num = new short[this->size];
    if (s[0] == '-') {
        this->sign = false;
        this->size = s.size() - 1;
    }
    for (int i = 0; i < this->size; i++) {
        this->num[i] = s[s.size() - i - 1] - '0';
    }
}

BigInteger::~BigInteger() {
    delete this->num;
}

std::string BigInteger::toString() {
    std::string res = "";
    if (!this->sign) {
        res += "-";
    }
    for (int i = 0; i < this->size; i++) {
        res += char(this->num[this->size - i - 1] + '0');
    }
    return res;
}

BigInteger& BigInteger::operator=(const BigInteger &bi) {
    delete this->num;
    this->size = bi.size;
    this->num = new short[this->size];
    this->sign = bi.sign;
    for (int i = 0; i < this->size; i++) {
        this->num[i] = bi.num[i];
    }
}

std::ostream& operator<<(std::ostream& out, BigInteger& bi) {
    return out << bi.toString();
}

std::istream& operator>>(std::istream& in,  BigInteger& obj) {
    std::string t;
    in >> t;
    obj = BigInteger(t);
    return in;
}
