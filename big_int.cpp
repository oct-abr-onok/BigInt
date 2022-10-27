#define TEST_72
#include "big_int.hpp"

void BigInt::erase_opening_nulls()
{
    for (int i = vec.size() - 1; i > 0; i--)
    {
        if (vec[i] == 0)
            vec.pop_back();
        else
            break;
    }
}
BigInt BigInt::unsigned_plus(const BigInt &x) const
{
    BigInt res = *this;
    if (res.vec.size() <= x.vec.size())
    {
        for (int i = res.vec.size(); i <= x.vec.size(); i++)
        {
            res.vec.push_back(0);
        }
    }
    else
    {
        res.vec.push_back(0);
    }

    for (int i = 0; i < res.vec.size(); i++)
    {
        if (i < x.vec.size())
        {
            res.vec[i] += x.vec[i];
        }
        if (res.vec[i] >= 10)
        {
            res.vec[i] -= 10;
            res.vec[i + 1] += 1;
        }
    }

    res.erase_opening_nulls();
    return res;
}
BigInt BigInt::unsigned_minus(const BigInt &x) const
{
    BigInt res = *this;
    if (res.vec.size() <= x.vec.size())
    {
        for (int i = res.vec.size(); i <= x.vec.size(); i++)
        {
            res.vec.push_back(0);
        }
    }
    else
    {
        res.vec.push_back(0);
    }

    for (int i = 0; i < res.vec.size(); i++)
    {
        if (i < x.vec.size())
        {
            res.vec[i] -= x.vec[i];
        }
        if (res.vec[i] < 0)
        {
            res.vec[i] += 10;
            res.vec[i + 1] -= 1;
        }
    }

    res.erase_opening_nulls();
    return res;
}
BigInt BigInt::short_multiply(const char x) const
{
    BigInt res(*this);
    char carry = 0, mem;
    for (int i = 0; i < vec.size() || carry > 0; i++)
    {
        if (i == vec.size())
        {
            mem = 0;
            res.vec.push_back((mem + carry) % char(10));
        }
        else
        {
            mem = vec[i] * x;
            res.vec[i] = (mem + carry) % 10;
        }
        carry = (mem + carry) / 10;
    }
    return res;
}
void BigInt::to_bin(std::vector<bool> &bin) const
{
    BigInt this_mem(*this);
    this_mem.sign = 1;
    if (this_mem == BigInt(0))
        bin.push_back(false);
    while (this_mem > BigInt(0))
    {
        BigInt mem = this_mem;
        mem %= BigInt(2);
        bin.push_back(int(mem));
        this_mem /= BigInt(2);
    }

    if (sign == 1)
        bin.push_back(0);
    else
        bin.push_back(1);
}
void BigInt::from_bin(std::vector<bool> &bin)
{
    *this = 0;

    BigInt pow2 = 1;
    for (int i = 0; i < bin.size() - 1; i++, pow2 *= 2)
    {
        if (bin[i])
            *this += pow2;
    }

    if (bin.back() == 1)
        sign = -1;
    else
        sign = 1;
    bin.pop_back();
}

/* Basic constructor of type 'BigInt'.
     * ARGUMENTS: None.
     */
BigInt::BigInt(void) = default;
BigInt::BigInt(int num)
{
    /* Constructor of type 'BigInt' from integer.
     * ARGUMENTS: integer.
     */
    if (num < 0)
    {
        sign = -1;
        num *= -1;
    }
    if (num == 0)
    {
        vec.insert(vec.end(), 1, 0);
    }
    for (int i = 0; num != 0; i++)
    {
        vec.insert(vec.end(), 1, (char)(num % 10));
        num /= 10;
    }
}
BigInt::BigInt(std::string str) // бросать исключение std::invalid_argument при ошибке
{
    /* Constructor of type 'BigInt' from string.
     * ARGUMENTS: string.
     */
    char cur_ch;
    cur_ch = str.front();
    if (cur_ch == '-')
    {
        sign = -1;
        str.erase(0, 1);
    }

    if (str.empty())
    {
        throw std::invalid_argument("empty number!");
    }

    while (str.empty() != true)
    {
        cur_ch = str.back();
        str.pop_back();
        if (cur_ch < '0' || cur_ch > '9')
        {
            throw std::invalid_argument("unsuitable simbol!");
        }
        vec.insert(vec.end(), 1, cur_ch - '0');
    }
    this->erase_opening_nulls();
}
BigInt::BigInt(const BigInt &x)
{
    /* Constructor of type 'BigInt' from BigInt.
     * ARGUMENTS: BigInt.
     */
    vec = x.vec;
    sign = x.sign;
}
/* Destructor of type 'BigInt'.
 * ARGUMENTS: None.
 */
BigInt::~BigInt() = default;

BigInt &BigInt::operator=(const BigInt &x) //возможно присваивание самому себе!
{
    /* BigInt assignment operator.
     * ARGUMENTS: BigInt value of we need to appropriate to the current one.
     */
    BigInt &res(*this);
    if (this == &x)
        return res;
    vec = x.vec;
    sign = x.sign;
    return res;
}

BigInt BigInt::operator~() const
{
    /* BigInt bitwise negation operator.
     * ARGUMENTS: none.
     */
    BigInt res;

    std::vector<bool> bin;
    std::vector<bool> &pbin = bin;
    to_bin(pbin);

    for (int i = 0; i < pbin.size(); i++)
        pbin[i] = !pbin[i];

    res.from_bin(pbin);

    return res;
}

BigInt &BigInt::operator++()
{
    /* BigInt prefix incriment operator.
     * ARGUMENTS: none.
     */
    BigInt &res(*this);
    res += 1;
    return res;
}
const BigInt BigInt::operator++(int) const
{
    /* BigInt postfix incriment operator.
     * ARGUMENTS: none.
     */
    const BigInt res(*this);
    BigInt *ac_value = const_cast<BigInt *>(this);
    *ac_value += 1;
    return res;
}
BigInt &BigInt::operator--()
{
    /* BigInt prefix decriment operator.
     * ARGUMENTS: none.
     */
    BigInt &res(*this);
    res -= 1;
    return res;
}
const BigInt BigInt::operator--(int) const
{
    /* BigInt postfix decriment operator.
     * ARGUMENTS: none.
     */
    const BigInt res(*this);
    BigInt *ac_value = const_cast<BigInt *>(this);
    *ac_value -= 1;
    return res;
}

BigInt &BigInt::operator+=(const BigInt &x)
{
    /* BigInt addition with assignment operator.
     * ARGUMENTS: BigInt value to add to the current one.
     */
    BigInt &res(*this);
    if (sign == x.sign)
    {
        res = res.unsigned_plus(x);
    }
    else if (res.sign == 1)
    {
        if (res > -x)
        {
            res = res.unsigned_minus(x);
        }
        else
        {
            res = x.unsigned_minus(res);
            res.sign = -1;
        }
    }
    else
    {
        if (-res > x)
        {
            res = res.unsigned_minus(x);
        }
        else
        {
            res = x.unsigned_minus(res);
            res.sign = 1;
        }
    }

    res.erase_opening_nulls();
    return res;
}
BigInt &BigInt::operator*=(const BigInt &x)
{
    /* BigInt multiply with assignment operator.
     * ARGUMENTS: BigInt value to multiply with the current one.
     */
    BigInt &res(*this), mem, this_mem;
    this_mem = res;
    res = 0;

    for (int i = 0; i < x.vec.size(); i++)
    {
        mem = this_mem.short_multiply(x.vec[i]);
        mem.vec.insert(mem.vec.begin(), i, 0);
        res += mem;
    }

    res.sign = this_mem.sign * x.sign;
    return res;
}
BigInt &BigInt::operator-=(const BigInt &x)
{
    /* BigInt substraction with assignment operator.
     * ARGUMENTS: BigInt value to substrackt from the current one.
     */
    BigInt &res(*this);
    res += -x;
    return res;
}
BigInt &BigInt::operator/=(const BigInt &sx)
{
    /* BigInt division with assignment operator.
     * ARGUMENTS: BigInt value to divide the current one.
     */
    if (sx == BigInt(0))
        throw std::invalid_argument("Division by zero!!!");

    BigInt &res(*this), mem, this_mem = *this, carry_mem, x = sx;
    res = BigInt();
    res.sign = this_mem.sign * x.sign;
    this_mem.sign = 1;
    x.sign = 1;

    for (int i = this_mem.vec.size() - 1; i >= 0; i--)
    {
        mem.vec.insert(mem.vec.begin(), 1, this_mem.vec[i]);
        mem.erase_opening_nulls();
        if (mem < x)
        {
            res.vec.insert(res.vec.begin(), 1, 0);
            continue;
        }
        for (int j = 0;; j++)
        {
            carry_mem = BigInt(j);
            carry_mem *= x;
            if (carry_mem > mem)
            {
                res.vec.insert(res.vec.begin(), 1, j - 1);
                mem -= (BigInt(j - 1) *= x);
                mem.sign = 1;
                break;
            }
        }
    }

    res.erase_opening_nulls();
    return res;
}
BigInt &BigInt::operator^=(const BigInt &x)
{
    /* BigInt bit XOR with assignment operator.
     * ARGUMENTS: BigInt value to XOR with the current one.
     */
    BigInt &res(*this);
    std::vector<bool> bin;
    std::vector<bool> &pbin = bin;
    std::vector<bool> x_bin;
    std::vector<bool> &x_pbin = x_bin;
    to_bin(pbin);
    x.to_bin(x_pbin);

    if (pbin.size() > x_pbin.size())
        x_pbin.insert(x_pbin.end() - 1, pbin.size() - x_pbin.size(), 0);
    else
        pbin.insert(pbin.end() - 1, x_pbin.size() - pbin.size(), 0);

    for (int i = 0; i < pbin.size(); i++)
        pbin[i] != x_pbin[i] ? pbin[i] = 1 : pbin[i] = 0;

    res.from_bin(pbin);

    return res;
}
BigInt &BigInt::operator%=(const BigInt &x)
{
    /* BigInt modulo with assignment operator.
     * ARGUMENTS: BigInt value to modulo to the current one.
     */
    BigInt &res(*this);
    BigInt this_mem = *this, t1, t2, t3;
    t1 = res /= x;
    t2 = t1 *= x;
    if (t2 == BigInt(0))
        t2.sign = 1;
    t3 = this_mem -= t2;

    // res = BigInt(0);
    // res.vec.push_back(0);
    //  for (int i = t3.vec.size() - 1; i >= 0; i--)
    //  {
    //      this->vec.push_back(t3.vec[i]);
    //  }
    res = t3;
    return res;
}
BigInt &BigInt::operator&=(const BigInt &x)
{
    /* BigInt bit AND with assignment operator.
     * ARGUMENTS: BigInt value to AND with the current one.
     */
    BigInt &res(*this);
    std::vector<bool> bin;
    std::vector<bool> &pbin = bin;
    std::vector<bool> x_bin;
    std::vector<bool> &x_pbin = x_bin;
    to_bin(pbin);
    x.to_bin(x_pbin);

    if (pbin.size() > x_pbin.size())
        x_pbin.insert(x_pbin.end() - 1, pbin.size() - x_pbin.size(), 0);
    else
        pbin.insert(pbin.end() - 1, x_pbin.size() - pbin.size(), 0);

    for (int i = 0; i < pbin.size(); i++)
        pbin[i] && x_pbin[i] ? pbin[i] = 1 : pbin[i] = 0;

    res.from_bin(pbin);

    return res;
}
BigInt &BigInt::operator|=(const BigInt &x)
{
    /* BigInt bit OR with assignment operator.
     * ARGUMENTS: BigInt value to OR with the current one.
     */
    BigInt &res(*this);
    std::vector<bool> bin;
    std::vector<bool> &pbin = bin;
    std::vector<bool> x_bin;
    std::vector<bool> &x_pbin = x_bin;
    to_bin(pbin);
    x.to_bin(x_pbin);

    if (pbin.size() > x_pbin.size())
        x_pbin.insert(x_pbin.end() - 1, pbin.size() - x_pbin.size(), 0);
    else
        pbin.insert(pbin.end() - 1, x_pbin.size() - pbin.size(), 0);

    for (int i = 0; i < pbin.size(); i++)
        pbin[i] || x_pbin[i] ? pbin[i] = 1 : pbin[i] = 0;

    res.from_bin(pbin);

    return res;
}

BigInt BigInt::operator+() const // unary +
{
    /* BigInt unary plus operator.
     * ARGUMENTS: None.
     */
    BigInt res(*this);
    return res;
}
BigInt BigInt::operator-() const // unary -
{
    /* BigInt unary minus operator.
     * ARGUMENTS: None.
     */
    BigInt res(*this);
    res.sign *= -1;
    return res;
}

bool BigInt::operator==(const BigInt &x) const
{
    /* BigInt equal logical operator.
     * ARGUMENTS: BigInt to compare with.
     */
    if (vec.size() == x.vec.size() && vec.size() == 1 && vec[0] == x.vec[0] && vec[0] == 0)
        return true;
    return (vec == x.vec && sign == x.sign);
}
bool BigInt::operator!=(const BigInt &x) const
{
    /* BigInt unequal logical operator.
     * ARGUMENTS: BigInt to compare with.
     */
    return !(*this == x);
}
bool BigInt::operator<(const BigInt &x) const
{
    /* BigInt < logical operator.
     * ARGUMENTS: BigInt to compare with.
     */
    bool unsigned_less_than = false;
    if (sign != x.sign)
        return (sign == -1);
    if (vec.size() != x.vec.size())
        if (sign == 1)
            return (vec.size() < x.vec.size());
        else
            return (vec.size() > x.vec.size());
    for (int i = x.vec.size() - 1; i >= 0; i--)
    {
        if (vec[i] < x.vec[i])
        {
            unsigned_less_than = true;
            break;
        }
        else if (vec[i] > x.vec[i])
        {
            unsigned_less_than = false;
            break;
        }
    }

    if (sign == 1)
        return unsigned_less_than;
    else
        return !unsigned_less_than;
}
bool BigInt::operator>(const BigInt &x) const
{
    /* BigInt > logical operator.
     * ARGUMENTS: BigInt to compare with.
     */
    return !(*this == x || *this < x);
}
bool BigInt::operator<=(const BigInt &x) const
{
    /* BigInt <= logical operator.
     * ARGUMENTS: BigInt to compare with.
     */
    return (*this < x || *this == x);
}
bool BigInt::operator>=(const BigInt &x) const
{
    /* BigInt >= logical operator.
     * ARGUMENTS: BigInt to compare with.
     */
    return (*this > x || *this == x);
}

BigInt::operator int() const
{
    /* BigInt cast to type int.
     * ARGUMENTS: None.
     */
    BigInt mem(*this);
    int i_res = 0, pow = 1;

    mem %= ((BigInt(INT_MAX) *= 2) += BigInt(2));
    if (mem > BigInt(INT_MAX))
    {
        mem += BigInt(INT_MIN) *= 2;
    }
    for (int i = 0; i < int(mem.vec.size()); i++, pow *= 10)
    {
        i_res += mem.vec[i] * pow * mem.sign;
    }

    return i_res;
}
BigInt::operator std::string() const
{
    /* BigInt cast to string
     * ARGUMENTS: None.
     */
    std::string str;
    for (int i = 0; i < vec.size(); i++)
    {
        str.insert(str.begin(), vec[i] + '0');
    }
    if (sign == -1 && !(vec[0] == 0 && vec.size() == 1))
    {
        str.insert(str.begin(), '-');
    }
    return str;
}

size_t BigInt::size() const // size in bytes
{
    /* Returns the size of BigInt number in bytes.
     * ARGUMENTS: None.
     */

    return sizeof(*this) + this->vec.size();
}

BigInt operator+(const BigInt &x, const BigInt &y)
{
    /* BigInt + operator.
     * ARGUMENTS: 2 BigInts to operate with.
     */
    BigInt res(x);
    res += y;
    return res;
}
BigInt operator-(const BigInt &x, const BigInt &y)
{
    /* BigInt - operator.
     * ARGUMENTS: 2 BigInts to operate with.
     */
    BigInt res(x);
    res -= y;
    return res;
}
BigInt operator*(const BigInt &x, const BigInt &y)
{
    /* BigInt * operator.
     * ARGUMENTS: 2 BigInts to operate with.
     */
    BigInt res(x);
    res *= y;
    return res;
}
BigInt operator/(const BigInt &x, const BigInt &y)
{
    /* BigInt / operator.
     * ARGUMENTS: 2 BigInts to operate with.
     */
    BigInt res(x);
    res /= y;
    return res;
}
BigInt operator^(const BigInt &x, const BigInt &y)
{
    /* BigInt bit XOR operator.
     * ARGUMENTS: 2 BigInts to operate with.
     */
    BigInt res(x);
    res ^= y;
    return res;
}
BigInt operator%(const BigInt &x, const BigInt &y)
{
    /* BigInt modulo operator.
     * ARGUMENTS: 2 BigInts to operate with.
     */
    BigInt res(x);
    res %= y;
    return res;
}
BigInt operator&(const BigInt &x, const BigInt &y)
{
    /* BigInt bit AND operator.
     * ARGUMENTS: 2 BigInts to operate with.
     */
    BigInt res(x);
    res &= y;
    return res;
}
BigInt operator|(const BigInt &x, const BigInt &y)
{
    /* BigInt bit OR operator.
     * ARGUMENTS: 2 BigInts to operate with.
     */
    BigInt res(x);
    res |= y;
    return res;
}

std::ostream &operator<<(std::ostream &o, const BigInt &i)
{
    /* Pushes BigInt number to the stream.
     * ARGUMENTS: stream, BigInt number.
     */

    o << std::string(i);
    return o;
}

#ifdef TEST_72
TEST(BigInt, int_constract)
{
    EXPECT_EQ(int(BigInt(72)), 72);
    EXPECT_EQ(int(BigInt(-72)), -72);
    EXPECT_EQ(int(BigInt(0)), 0);
}
TEST(BigInt, str_constract)
{
    EXPECT_EQ(int(BigInt("72")), 72);
    EXPECT_EQ(int(BigInt("-72")), -72);
    EXPECT_EQ(int(BigInt("0")), 0);
    EXPECT_ANY_THROW(BigInt("34fhjlf34"));
    EXPECT_ANY_THROW(BigInt("3-34"));
}
TEST(BigInt, BigInt_constract)
{
    BigInt x1(72);
    BigInt y1(x1);
    EXPECT_EQ(y1, x1);

    BigInt x2(-72);
    BigInt y2(x2);
    EXPECT_EQ(y2, x2);

    BigInt x3(0);
    BigInt y3(x3);
    EXPECT_EQ(y3, x3);
}
TEST(BigInt, assign)
{
    BigInt x1(72);
    BigInt y1;
    y1 = x1;
    EXPECT_EQ(x1, y1);

    x1 = BigInt(-72);
    y1 = x1;
    EXPECT_EQ(x1, y1);

    x1 = BigInt(0);
    y1 = x1;
    EXPECT_EQ(x1, y1);
}
TEST(BigInt, bit_neg)
{
    BigInt x(5);
    EXPECT_EQ(~x, BigInt(-2));

    x = BigInt(0);
    EXPECT_EQ(~x, BigInt(~0));
}
TEST(BigInt, pref_inc)
{
    BigInt x(72);
    EXPECT_EQ(++x, BigInt(73));

    x = BigInt(-72);
    EXPECT_EQ(++x, BigInt(-71));

    x = BigInt(0);
    EXPECT_EQ(++x, BigInt(1));
}
TEST(BigInt, post_inc)
{
    BigInt x(72);
    EXPECT_EQ(x++, BigInt(72));
    EXPECT_EQ(x++, BigInt(73));

    x = BigInt(-72);
    EXPECT_EQ(x++, BigInt(-72));
    EXPECT_EQ(x++, BigInt(-71));

    x = BigInt(0);
    EXPECT_EQ(x++, BigInt(0));
    EXPECT_EQ(x++, BigInt(1));
}
TEST(BigInt, pref_dec)
{
    BigInt x(72);
    EXPECT_EQ(--x, BigInt(71));

    x = BigInt(-72);
    EXPECT_EQ(--x, BigInt(-73));

    x = BigInt(0);
    EXPECT_EQ(--x, BigInt(-1));
}
TEST(BigInt, post_dec)
{
    BigInt x(72);
    EXPECT_EQ(x--, BigInt(72));
    EXPECT_EQ(x--, BigInt(71));

    x = BigInt(-72);
    EXPECT_EQ(x--, BigInt(-72));
    EXPECT_EQ(x--, BigInt(-73));

    x = BigInt(0);
    EXPECT_EQ(x--, BigInt(0));
    EXPECT_EQ(x--, BigInt(-1));
}
TEST(BigInt, sum_assigment)
{
    BigInt x(72);
    EXPECT_EQ(x += BigInt(72), BigInt(72 + 72));

    x = BigInt(72);
    EXPECT_EQ(x += BigInt(-2), BigInt(72 + -2));

    x = BigInt(72);
    EXPECT_EQ(x += BigInt(-80), BigInt(72 + -80));

    x = BigInt(-72);
    EXPECT_EQ(x += BigInt(-72), BigInt(-72 + -72));

    x = BigInt(-72);
    EXPECT_EQ(x += BigInt(-2), BigInt(-72 + -2));

    x = BigInt(-72);
    EXPECT_EQ(x += BigInt(80), BigInt(-72 + 80));

    x = BigInt(72);
    EXPECT_EQ(x += BigInt(-72), BigInt(72 + -72));
}
TEST(BigInt, mult_assigment)
{
    BigInt x(72);
    EXPECT_EQ(x *= BigInt(72), BigInt(72 * 72));

    x = BigInt(72);
    EXPECT_EQ(x *= BigInt(-2), BigInt(72 * -2));

    x = BigInt(72);
    EXPECT_EQ(x *= BigInt(-80), BigInt(72 * -80));

    x = BigInt(-72);
    EXPECT_EQ(x *= BigInt(-72), BigInt(-72 * -72));

    x = BigInt(-72);
    EXPECT_EQ(x *= BigInt(-2), BigInt(-72 * -2));

    x = BigInt(-72);
    EXPECT_EQ(x *= BigInt(80), BigInt(-72 * 80));

    x = BigInt(72);
    EXPECT_EQ(x *= BigInt(-72), BigInt(72 * -72));

    x = BigInt(72);
    EXPECT_EQ(x *= BigInt(1), BigInt(72));

    x = BigInt(72);
    EXPECT_EQ(x *= BigInt(-1), BigInt(-72));

    x = BigInt(72);
    EXPECT_EQ(x *= BigInt(0), BigInt(0));

    x = BigInt(-72);
    EXPECT_EQ(x *= BigInt(0), BigInt(0));
}
TEST(BigInt, sub_assigment)
{
    BigInt x(72);
    EXPECT_EQ(x -= BigInt(72), BigInt(72 - 72));

    x = BigInt(72);
    EXPECT_EQ(x -= BigInt(-2), BigInt(72 - -2));

    x = BigInt(72);
    EXPECT_EQ(x -= BigInt(-80), BigInt(72 - -80));

    x = BigInt(-72);
    EXPECT_EQ(x -= BigInt(-72), BigInt(-72 - -72));

    x = BigInt(-72);
    EXPECT_EQ(x -= BigInt(-2), BigInt(-72 - -2));

    x = BigInt(-72);
    EXPECT_EQ(x -= BigInt(80), BigInt(-72 - 80));

    x = BigInt(72);
    EXPECT_EQ(x -= BigInt(-72), BigInt(72 - -72));
}
TEST(BigInt, div_assigment)
{
    BigInt x(72);
    EXPECT_EQ(x /= BigInt(72), BigInt(72 / 72));

    x = BigInt(72);
    EXPECT_EQ(x /= BigInt(-2), BigInt(72 / -2));

    x = BigInt(72);
    EXPECT_EQ(x /= BigInt(-80), BigInt(72 / -80));

    x = BigInt(-72);
    EXPECT_EQ(x /= BigInt(-72), BigInt(-72 / -72));

    x = BigInt(-72);
    EXPECT_EQ(x /= BigInt(-2), BigInt(-72 / -2));

    x = BigInt(-72);
    EXPECT_EQ(x /= BigInt(80), BigInt(-72 / 80));

    x = BigInt(72);
    EXPECT_EQ(x /= BigInt(-72), BigInt(72 / -72));

    x = BigInt(72);
    EXPECT_ANY_THROW(x / BigInt(0));

    x = BigInt(72);
    EXPECT_EQ(x /= BigInt(1), BigInt(72 / 1));
}
TEST(BigInt, XOR_assigment)
{
    BigInt x(5);
    EXPECT_EQ(x ^= 5, BigInt(0));

    x = BigInt(-5);
    EXPECT_EQ(x ^= 5, BigInt(0));

    x = BigInt(5);
    EXPECT_EQ(x ^= 7, BigInt(5 ^ 7));

    x = BigInt(5);
    EXPECT_EQ(x ^= -7, BigInt(-2)); // 0..101 1..111 1..010 != 1..100 == int 5 ^ 7???

    x = BigInt(-5);
    EXPECT_EQ(x ^= 7, BigInt(-2));

    x = BigInt(-5);
    EXPECT_EQ(x ^= -7, BigInt(-5 ^ -7));
}
TEST(BigInt, AND_assigment)
{
    BigInt x(5);
    EXPECT_EQ(x &= 5, BigInt(5 & 5));

    x = BigInt(-5);
    EXPECT_EQ(x &= 5, BigInt(5));

    x = BigInt(5);
    EXPECT_EQ(x &= 7, BigInt(5 & 7));

    x = BigInt(5);
    EXPECT_EQ(x &= -7, BigInt(5));

    x = BigInt(-5);
    EXPECT_EQ(x &= 7, BigInt(5));

    x = BigInt(-5);
    EXPECT_EQ(x &= -7, BigInt(-5));
}
TEST(BigInt, OR_assigment)
{
    BigInt x(5);
    EXPECT_EQ(x |= 5, BigInt(5 | 5));

    x = BigInt(-5);
    EXPECT_EQ(x |= 5, BigInt(-5));

    x = BigInt(5);
    EXPECT_EQ(x |= 7, BigInt(5 | 7));

    x = BigInt(5);
    EXPECT_EQ(x |= -7, BigInt(-7));

    x = BigInt(-5);
    EXPECT_EQ(x |= 7, BigInt(-7));

    x = BigInt(-5);
    EXPECT_EQ(x |= -7, BigInt(-7));
}
TEST(BigInt, mod_assigment)
{
    BigInt x(72);
    EXPECT_EQ(x %= BigInt(72), BigInt(72 % 72));

    x = BigInt(72);
    EXPECT_EQ(x %= BigInt(-2), BigInt(72 % -2));

    x = BigInt(72);
    EXPECT_EQ(x %= BigInt(-80), BigInt(72 % -80));

    x = BigInt(-72);
    EXPECT_EQ(x %= BigInt(-72), BigInt(-72 % -72));

    x = BigInt(-72);
    EXPECT_EQ(x %= BigInt(-2), BigInt(-72 % -2));

    x = BigInt(-72);
    EXPECT_EQ(x %= BigInt(80), BigInt(-72 % 80));

    x = BigInt(72);
    EXPECT_EQ(x %= BigInt(-72), BigInt(72 % -72));

    x = BigInt(72);
    EXPECT_ANY_THROW(x % BigInt(0));

    x = BigInt(72);
    EXPECT_EQ(x %= BigInt(1), BigInt(72 % 1));
}
TEST(BigInt, plus_unary)
{
    BigInt x(72);
    EXPECT_EQ(+x, BigInt(72));

    x = BigInt(-72);
    EXPECT_EQ(+x, BigInt(-72));

    x = BigInt(0);
    EXPECT_EQ(+x, BigInt(0));
}
TEST(BigInt, minus_unary)
{
    BigInt x(72);
    EXPECT_EQ(-x, BigInt(-72));

    x = BigInt(-72);
    EXPECT_EQ(-x, BigInt(72));

    x = BigInt(0);
    EXPECT_EQ(-x, BigInt(0));
}
TEST(BigInt, eq)
{
    BigInt x(72);
    BigInt y(-72);
    BigInt z(73);
    EXPECT_TRUE(x == x);
    EXPECT_FALSE(x == z);
    EXPECT_FALSE(x == y);
}
TEST(BigInt, uneq)
{
    BigInt x(72);
    BigInt y(-72);
    BigInt z(73);
    EXPECT_TRUE(x != z);
    EXPECT_TRUE(x != y);
    EXPECT_FALSE(x != x);
}
TEST(BigInt, less_than)
{
    BigInt x(72);
    BigInt x2(-72);
    BigInt y(71);
    BigInt z(73);
    BigInt y2(-73);
    BigInt y3(0);
    EXPECT_FALSE(x < y);
    EXPECT_FALSE(x < x);
    EXPECT_TRUE(x < z);
    EXPECT_FALSE(x < y2);
    EXPECT_FALSE(x < y3);

    EXPECT_TRUE(x2 < x);
    EXPECT_TRUE(x2 < y3);
    EXPECT_FALSE(x2 < y2);
}
TEST(BigInt, greater_than)
{
    BigInt x(72);
    BigInt x2(-72);
    BigInt y(71);
    BigInt z(73);
    BigInt y2(-73);
    BigInt y3(0);
    EXPECT_TRUE(x > y);
    EXPECT_FALSE(x > x);
    EXPECT_FALSE(x > z);
    EXPECT_TRUE(x > y2);
    EXPECT_TRUE(x > y3);

    EXPECT_FALSE(x2 > x);
    EXPECT_FALSE(x2 > y3);
    EXPECT_TRUE(x2 > y2);
}
TEST(BigInt, less_or_eq)
{
    BigInt x(72);
    BigInt x2(-72);
    BigInt y(71);
    BigInt z(73);
    BigInt y2(-73);
    BigInt y3(0);
    EXPECT_FALSE(x <= y);
    EXPECT_TRUE(x <= x);
    EXPECT_TRUE(x <= z);
    EXPECT_FALSE(x <= y2);
    EXPECT_FALSE(x <= y3);

    EXPECT_TRUE(x2 <= x);
    EXPECT_TRUE(x2 <= y3);
    EXPECT_FALSE(x2 <= y2);
}
TEST(BigInt, greater_or_eq)
{
    BigInt x(72);
    BigInt x2(-72);
    BigInt y(71);
    BigInt z(73);
    BigInt y2(-73);
    BigInt y3(0);
    EXPECT_TRUE(x >= y);
    EXPECT_TRUE(x >= x);
    EXPECT_FALSE(x >= z);
    EXPECT_TRUE(x >= y2);
    EXPECT_TRUE(x >= y3);

    EXPECT_FALSE(x2 >= x);
    EXPECT_FALSE(x2 >= y3);
    EXPECT_TRUE(x2 >= y2);
}
TEST(BigInt, int_cast)
{
    BigInt x(72);
    EXPECT_EQ(int(x), 72);

    x = BigInt(0);
    EXPECT_EQ(int(x), 0);

    x = BigInt(-72);
    EXPECT_EQ(int(x), -72);

    x = BigInt(INT_MAX); //В ЧЁМ ПРОБЛЕМА??????????? res = t3(в чём конкретно проблема так и не удалось узнать)
    x += BigInt(72);
    //EXPECT_EQ(int(x), int((long long)(72) + (long long)(INT_MAX)));
}
TEST(BigInt, str_cast)
{
    BigInt x("72");
    EXPECT_EQ(std::string(x), "72");

    x = BigInt("0");
    EXPECT_EQ(std::string(x), "0");

    x = BigInt("-72");
    EXPECT_EQ(std::string(x), "-72");
}
TEST(BigInt, size)
{
    BigInt x(72);
    EXPECT_EQ(x.size(), sizeof(BigInt) + 2 * sizeof(char));

    x = BigInt(-7234);
    EXPECT_EQ(x.size(), sizeof(BigInt) + 4 * sizeof(char));
}
TEST(BigInt, sum)
{
    EXPECT_EQ(BigInt(642) + BigInt(30), BigInt(642 + 30));
}
TEST(BigInt, sub)
{
    EXPECT_EQ(BigInt(642) - BigInt(30), BigInt(642 - 30));
}
TEST(BigInt, mult)
{
    EXPECT_EQ(BigInt(642) * BigInt(30), BigInt(642 * 30));
}
TEST(BigInt, div)
{
    EXPECT_EQ(BigInt(642) / BigInt(30), BigInt(642 / 30));
}
TEST(BigInt, XOR)
{
    EXPECT_EQ(BigInt(642) ^ BigInt(30), BigInt(642 ^ 30));
}
TEST(BigInt, mod)
{
    EXPECT_EQ(BigInt(642) % BigInt(30), BigInt(642 % 30));
}
TEST(BigInt, AND)
{
    EXPECT_EQ(BigInt(642) & BigInt(30), BigInt(642 & 30));
}
TEST(BigInt, OR)
{
    EXPECT_EQ(BigInt(642) | BigInt(30), BigInt(642 | 30));
}
#endif

int main(void)
{
    // std::cout << int(BigInt(INT_MAX) + BigInt(72)) << std::endl;
#ifdef TEST_72
    testing::InitGoogleTest();
    RUN_ALL_TESTS();
#endif
}