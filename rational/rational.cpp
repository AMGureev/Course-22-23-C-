#include "rational.h"

#include <sstream>

void ReduceFraction(int& numerator, int& denominator);

void GetSign(int& numerator, int& denominator);

Rational::Rational() {
    this->Set(0, 1);
}

Rational::Rational(int value) {
    this->Set(value, 1);
}

Rational::Rational(int numerator, int denominator) {
    Set(numerator, denominator);
}

int Rational::GetNumerator() const {
    return numer_;
}

int Rational::GetDenominator() const {
    return denom_;
}

void Rational::SetNumerator(int value) {
    Set(value, denom_);
}

void Rational::SetDenominator(int value) {
    Set(numer_, value);
}

Rational& operator+=(Rational& lhs, const Rational& rhs) {
    lhs = lhs + rhs;
    return lhs;
}

Rational& operator*=(Rational& lhs, const Rational& rhs) {
    lhs = lhs * rhs;
    return lhs;
}

Rational& operator++(Rational& ratio) {
    ratio.numer_ = ratio.numer_ + ratio.denom_;
    return ratio;
}

Rational& operator--(Rational& ratio) {
    ratio.numer_ = ratio.numer_ - ratio.denom_;
    return ratio;
}

void GetSign(int& numerator, int& denominator) {
    if (denominator < 0) {
        numerator = -numerator;
        denominator = -denominator;
    }
}

std::istream& operator>>(std::istream& is, Rational& ratio) {
    std::string str;
    is >> str;
    int del = static_cast<int>(str.find('/'));
    if (del != -1) {
        int numerator = std::stoi(str.substr(0, del));
        int denominator = std::stoi(str.substr(del + 1, str.size()));
        if (denominator == 0) {
            throw RationalDivisionByZero();
        }
        GetSign(numerator, denominator);
        ReduceFraction(numerator, denominator);
        ratio.Set(numerator, denominator);
    } else {
        Rational new_rational = Rational(std::stoi(str.substr(0, str.size())));
        ratio.Set(new_rational.GetNumerator(), new_rational.GetDenominator());
    }
    return is;
}

void Rational::Set(int64_t numerator, int64_t denominator) {
    int64_t num = numerator;
    int64_t den = denominator;
    if (den == 0) {
        throw RationalDivisionByZero{};
    }
    if (den < 0) {
        den *= -1;
        num *= -1;
    }
    int64_t nod = std::gcd(num, den);
    num /= nod;
    den /= nod;
    numer_ = static_cast<int>(num);
    denom_ = static_cast<int>(den);
}

Rational operator+(const Rational& ratio) {
    return Rational(ratio.GetNumerator(), ratio.GetDenominator());
}

Rational operator-(const Rational& ratio) {
    return Rational(-ratio.GetNumerator(), ratio.GetDenominator());
}

Rational& operator-=(Rational& lhs, const Rational& rhs) {
    lhs = lhs - rhs;
    return lhs;
}

Rational& operator/=(Rational& lhs, const Rational& rhs) {
    lhs = lhs / rhs;
    return lhs;
}

Rational operator+(const Rational& lhs, const Rational& rhs) {
    int num1 = lhs.GetNumerator();
    int num2 = rhs.GetNumerator();
    int den1 = lhs.GetDenominator();
    int den2 = rhs.GetDenominator();
    int new_num = num1 * den2 + num2 * den1;
    int new_den = den1 * den2;
    GetSign(new_num, new_den);
    ReduceFraction(new_num, new_den);
    return Rational(new_num, new_den);
}

Rational operator-(const Rational& lhs, const Rational& rhs) {
    int num1 = lhs.GetNumerator();
    int num2 = rhs.GetNumerator();
    int den1 = lhs.GetDenominator();
    int den2 = rhs.GetDenominator();
    int new_num = num1 * den2 - num2 * den1;
    int new_den = den1 * den2;
    GetSign(new_num, new_den);
    ReduceFraction(new_num, new_den);
    return Rational(new_num, new_den);
}

Rational operator*(const Rational& lhs, const Rational& rhs) {
    int num1 = lhs.GetNumerator();
    int num2 = rhs.GetNumerator();
    int den1 = lhs.GetDenominator();
    int den2 = rhs.GetDenominator();
    int new_num = num1 * num2;
    int new_den = den1 * den2;
    GetSign(new_num, new_den);
    ReduceFraction(new_num, new_den);
    return Rational(new_num, new_den);
}

Rational operator/(const Rational& lhs, const Rational& rhs) {
    int num1 = lhs.GetNumerator();
    int num2 = rhs.GetNumerator();
    int den1 = lhs.GetDenominator();
    int den2 = rhs.GetDenominator();
    int new_num = num1 * den2;
    int new_den = den1 * num2;
    GetSign(new_num, new_den);
    ReduceFraction(new_num, new_den);
    return Rational(new_num, new_den);
}

Rational operator++(Rational& ratio, int) {
    Rational new_rational = Rational(ratio.GetNumerator(), ratio.GetDenominator());
    ++ratio;
    return new_rational;
}

Rational operator--(Rational& ratio, int) {
    Rational new_rational = Rational(ratio.GetNumerator(), ratio.GetDenominator());
    --ratio;
    return new_rational;
}

bool operator<(const Rational& lhs, const Rational& rhs) {
    if (lhs.GetNumerator() * rhs.GetDenominator() - lhs.GetDenominator() * rhs.GetNumerator() < 0) {
        return true;
    } else {
        return false;
    }
}

bool operator>(const Rational& lhs, const Rational& rhs) {
    if (lhs.GetNumerator() * rhs.GetDenominator() - lhs.GetDenominator() * rhs.GetNumerator() > 0) {
        return true;
    } else {
        return false;
    }
}

bool operator<=(const Rational& lhs, const Rational& rhs) {
    if (lhs.GetNumerator() * rhs.GetDenominator() - lhs.GetDenominator() * rhs.GetNumerator() <= 0) {
        return true;
    } else {
        return false;
    }
}

bool operator>=(const Rational& lhs, const Rational& rhs) {
    if (lhs.GetNumerator() * rhs.GetDenominator() - lhs.GetDenominator() * rhs.GetNumerator() >= 0) {
        return true;
    } else {
        return false;
    }
}

bool operator==(const Rational& lhs, const Rational& rhs) {
    if (lhs.GetNumerator() * rhs.GetDenominator() - lhs.GetDenominator() * rhs.GetNumerator() == 0) {
        return true;
    } else {
        return false;
    }
}

bool operator!=(const Rational& lhs, const Rational& rhs) {
    if (lhs.GetNumerator() * rhs.GetDenominator() - lhs.GetDenominator() * rhs.GetNumerator() != 0) {
        return true;
    } else {
        return false;
    }
}

std::ostream& operator<<(std::ostream& os, const Rational& ratio) {
    std::string str;
    int num = ratio.GetNumerator();
    int den = ratio.GetDenominator();
    GetSign(num, den);
    if (den == 1) {
        str += std::to_string(num);
    } else {
        str += std::to_string(num) + '/' + std::to_string(den);
    }
    os << str;
    return os;
}

void ReduceFraction(int& numerator, int& denominator) {
    int num_sign = (numerator > 0 ? 1 : -1);
    int den_sign = (numerator > 0 ? 1 : -1);
    numerator *= num_sign;
    denominator *= den_sign;
    int gcd = std::gcd(numerator, denominator);
    numerator /= gcd;
    denominator /= gcd;
    numerator *= num_sign;
    denominator *= den_sign;
}