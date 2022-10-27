#ifndef BIG_INT_H1313
#define BIG_INT_H1313
#include <vector>
#include <string>
#include <iostream>
#include <stdexcept>
#include <limits.h>
#ifdef TEST_72
#include <gtest/gtest.h>
#endif

class BigInt
{
private:
    std::vector<char> vec;
    char sign = 1;

    void erase_opening_nulls();
    BigInt unsigned_plus(const BigInt &) const;
    BigInt unsigned_minus(const BigInt &) const;
    BigInt short_multiply(const char) const;
    void to_bin(std::vector<bool> &) const;
    void from_bin(std::vector<bool> &);

public:
    BigInt();
    BigInt(int);
    BigInt(std::string); // бросать исключение std::invalid_argument при ошибке
    BigInt(const BigInt &);
    ~BigInt();

    BigInt &operator=(const BigInt &); //возможно присваивание самому себе!

    BigInt operator~() const;

    BigInt &operator++();
    const BigInt operator++(int) const;
    BigInt &operator--();
    const BigInt operator--(int) const;

    BigInt &operator+=(const BigInt &);
    BigInt &operator*=(const BigInt &);
    BigInt &operator-=(const BigInt &);
    BigInt &operator/=(const BigInt &);
    BigInt &operator^=(const BigInt &);
    BigInt &operator%=(const BigInt &);
    BigInt &operator&=(const BigInt &);
    BigInt &operator|=(const BigInt &);

    BigInt operator+() const; // unary +
    BigInt operator-() const; // unary -

    bool operator==(const BigInt &) const;
    bool operator!=(const BigInt &) const;
    bool operator<(const BigInt &) const;
    bool operator>(const BigInt &) const;
    bool operator<=(const BigInt &) const;
    bool operator>=(const BigInt &) const;

    operator int() const;
    operator std::string() const;

    size_t size() const; // size in bytes
};

BigInt operator+(const BigInt &, const BigInt &);
BigInt operator-(const BigInt &, const BigInt &);
BigInt operator*(const BigInt &, const BigInt &);
BigInt operator/(const BigInt &, const BigInt &);
BigInt operator^(const BigInt &, const BigInt &);
BigInt operator%(const BigInt &, const BigInt &);
BigInt operator&(const BigInt &, const BigInt &);
BigInt operator|(const BigInt &, const BigInt &);

std::ostream &operator<<(std::ostream &o, const BigInt &i);

#endif /*BIG_INT_H1313*/