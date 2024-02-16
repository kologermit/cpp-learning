#include "BigInteger.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

void BigInteger::clear() {
    this->digits.clear();
    this->sign = true;
}

void BigInteger::setZero() {
    this->clear();
    this->digits.push_back(0);
}

void BigInteger::fromString(const std::string& s) {
    this->clear();
    if (s.empty()) {
        this->setZero();
        return;
    }
    std::string s2 = s;
    this->clear();
    if (s[0] == '-') {
        this->sign = false;
        s2.erase(0, 1);
    }
    for (int i = s2.size() - 1; i >= 0; i--) {
        this->digits.push_back(s2[i] - '0');
    }
}

bool BigInteger::isZero() const {
    return (this->sign && this->digits.size() == 1 && this->digits[0] == 0) || this->digits.size() == 0;
}

BigInteger::BigInteger() {
    this->setZero();
}

BigInteger::BigInteger(const long long& number) {
    this->clear();
    this->sign = number >= 0;
    int number2 = std::abs(number);
    do {
        this->digits.push_back(number2 % 10);
        number2 /= 10;
    } while (number2);
}

BigInteger::BigInteger(const std::string& s) {
    this->fromString(s);
}

BigInteger::BigInteger(const BigInteger& bi) {
    this->clear();
    this->digits.resize(bi.digits.size());
    std::copy(bi.digits.begin(), bi.digits.end(), this->digits.begin());
    this->sign = bi.sign;
}

BigInteger::operator bool() const {
    return !this->isZero();
}

bool BigInteger::operator==(const BigInteger& bi) const {
    return (bi.digits == this->digits) && (bi.sign == this->sign);
}

bool BigInteger::operator!() const {
    return this->isZero();
}

bool BigInteger::operator!=(const BigInteger& bi) const {
    return !(*this == bi);
}

bool BigInteger::operator>(const BigInteger& bi) const {
    if (this->sign != bi.sign) {
        return this->sign > bi.sign;
    }
    if (this->digits.size() != bi.digits.size()) {
        if (this->sign) {
            return this->digits.size() > bi.digits.size();
        } else {
            return this->digits.size() < bi.digits.size();
        }
    }
    for (int i = this->digits.size() - 1; i >= 0; i--) {
        if (this->digits[i] != bi.digits[i]) {
            if (this->sign) {
                return this->digits[i] > bi.digits[i];
            } else {
                return this->digits[i] < bi.digits[i];
            }
        }
    }
    return false;
}

bool BigInteger::operator>=(const BigInteger& bi) const {
    return (*this > bi) || (*this == bi);
}

bool BigInteger::operator<(const BigInteger& bi) const {
    return !(*this >= bi);
}

bool BigInteger::operator<=(const BigInteger& bi) const {
    return !(*this > bi);
}

BigInteger BigInteger::abs() const {
    BigInteger res(*this);
    if (!res.sign) {
        res.sign = !res.sign;
    }
    return res;
}

std::string BigInteger::toString() const {
    std::string res;
    if (!this->sign) {
        res = "-";
    }
    for (int i = this->digits.size() - 1; i >= 0; i--) {
        res += char(this->digits[i] + '0');
    }
    return res;
}

BigInteger& BigInteger::operator+=(const BigInteger& bi) {
    if (bi.isZero()) {
        return *this;
    }
    if (this->sign != bi.sign) {
        return (*this -= -bi);
    }
    if (this->digits.size() < bi.digits.size()) {
        this->digits.resize(bi.digits.size());
    }
    for (int i = 0; i < this->digits.size(); i++) {
        char t = this->digits[i] + (i < bi.digits.size() ? bi.digits[i] : 0);
        this->digits[i] = t % 10;
        if (t >= 10) {
            if (i == this->digits.size() - 1) {
                this->digits.push_back(t / 10);
            } else {
                this->digits[i + 1] += t / 10;
            }
        }
    }
    return *this;
}

BigInteger& BigInteger::operator-=(const BigInteger& bi) {
    if (bi.isZero()) {
        return  *this;
    }
    if (this->sign != bi.sign) {
        return (*this += -bi);
    }
    if (this->abs() >= bi.abs()) {
        for (int i = 0; i < this->digits.size(); i++) {
            char t = this->digits[i] - (i < bi.digits.size() ? bi.digits[i] : 0);
            if (t < 0) {
                this->digits[i] = 10 + t;
                this->digits[i + 1]--;
            } else {
                this->digits[i] = t;
            }
        }
        int end = 0;
        for (int i = 0; i < this->digits.size(); i++) {
            if (this->digits[i]) {
                end = i;
            }
        }
        this->digits.erase(this->digits.begin() + end + 1, this->digits.end());
    } else {
        BigInteger copy = *this;
        *this += bi;
        *this -= copy;
        *this -= copy;
        this->sign = !this->sign;
    }
    return *this;
}

BigInteger& BigInteger::operator*=(const BigInteger& prod) {
    this->sign = this->sign == prod.sign;
    if (prod.isZero() || this->isZero()) {
        this->setZero();
        return *this;
    }
    if (prod.abs() == 1) {
        return *this;
    }
    if (this->abs() == 1) {
        *this = prod;
        return *this;
    }
    BigInteger res;
    res.sign = this->sign;
    for (int p = prod.digits.size() - 1; p >= 0; p--) {
        int count = prod.digits[p];
        for (int i = 0; i < count; i++)  {
            res += *this;
        }
        if (p) {
            res.digits.insert(res.digits.begin(), 0);
        }
    }
    *this = res;
    return *this;
}


BigInteger& BigInteger::operator/=(const  BigInteger& div) {
    if (div.isZero()) {
        throw ZeroDivisionException();
    }
    if (div == 1LL || this->isZero()) {
        return *this;
    }
    bool sign = this->sign == div.sign;
    this->sign = true;
    BigInteger copyDiv = div;
    copyDiv.sign = true;
    BigInteger count(1);
    BigInteger res(0);
    while (copyDiv < *this) {
        copyDiv.digits.insert(copyDiv.digits.begin(), 0);
        count.digits.insert(count.digits.begin(), 0);
    }
    BigInteger divAbs = div.abs();
    while (*this >= divAbs) {
        if (copyDiv > *this) {
            if (!copyDiv.digits.empty()) {
                copyDiv.digits.erase(copyDiv.digits.begin());
            }
            if (!count.digits.empty()) {
                count.digits.erase(count.digits.begin());
            }
        } else {
            *this -= copyDiv;
            res += count;
        }
    }
    *this = res;
    this->sign = sign;
    return *this;
}

BigInteger& BigInteger::operator%=(const BigInteger& div) {
    return (*this = *this - (*this / div) * div);
}

BigInteger& BigInteger::operator++() {
    return (*this += 1);
}

BigInteger& BigInteger::operator--() {
    return (*this -= 1);
}

BigInteger BigInteger::operator++(int) {
    BigInteger temp = *this;
    *this += 1;
    return temp;
}

BigInteger BigInteger::operator--(int) {
    BigInteger temp = *this;
    *this -= 1;
    return temp;
}

BigInteger operator+(const BigInteger& bi1, const BigInteger& bi2) {
    BigInteger temp = bi1;
    return temp += bi2;
}

BigInteger operator-(const BigInteger& bi1, const BigInteger& bi2) {
    BigInteger temp = bi1;
    return temp -= bi2;
}

BigInteger operator*(const BigInteger& bi1, const BigInteger& bi2) {
    BigInteger temp = bi1;
    return temp *= bi2;
}

BigInteger operator/(const BigInteger& bi1, const BigInteger& bi2) {
    BigInteger temp = bi1;
    return temp /= bi2;
}

BigInteger operator%(const BigInteger& bi1, const BigInteger& bi2) {
    BigInteger temp = bi1;
    return temp %= bi2;
}

BigInteger BigInteger::operator-() const {
    BigInteger res(*this);
    if (!this->isZero()) {
        res.sign = !res.sign;
    }
    return res;
} 

std::ostream& operator<<(std::ostream& out, const BigInteger& bi) {
    return out << bi.toString();
}

std::istream& operator>>(std::istream& in, BigInteger& bi) {
    std::string t;
    in >> t;
    bi.fromString(t);
    return in;
}