#include "BigInteger.h"
#include <iostream>
#include <cmath>

BigInteger::BigInteger(cll n = 0) {
    ll n2 = abs(n);
    this->size = 0;
    this->sign = n >= 0;
    while (n2) {
        n2 /= 10;
        this->size++;
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

BigInteger::BigInteger(const std::string s) {
    if (s[0] == '-') {
        this->sign = false;
        this->size = s.size() - 1;
        this->num = new short[this->size];
        for (int i = 0; i < this->size; i++) {
            this->num[i] = s[i+1] - '0';
        }
    } else {
        this->sign = true;
        if (s == "0") {
            this->size = 0;
        } else {
            this->size = s.size();
            this->num = new short[this->size];
            for (int i = 0; i < this->size; i++) {
                this->num[i] = s[i] - '0';
            }
        }
    }
}