#include <iostream>
#include <limits>
#include <sstream>

using namespace std;

class BigInt {
private:
    vector<int> _data;
public:
    BigInt() {
    }

    BigInt(const long long x) {
    }

    BigInt(const BigInt& other) {
    }

    BigInt& operator=(const BigInt& other) {
        return *this;
    }

    BigInt operator+(const BigInt& other) const {
    }

    BigInt operator*(const BigInt& other) const {
    }

    bool operator==(const BigInt& other) const {
    }

    bool operator!=(const BigInt& other) const {
    }

    bool operator<(const BigInt& other) const {
    }

    bool operator<=(const BigInt& other) const {
    }

    bool operator>(const BigInt& other) const {
    }

    bool operator>=(const BigInt& other) const {
    }

    friend std::ostream& operator<<(std::ostream& out, const BigInt& value);

};

std::ostream& operator<<(std::ostream& out, const BigInt& value) {
}

std::string toString(const BigInt& value)
{
    std::stringstream buf;
    buf << value;
    return buf.str();
}

void check(int64_t x, int64_t y)
{
    const BigInt bigX = x;
    const BigInt bigY = y;

    if (bigX + bigY != BigInt(x + y))
    {
        std::cout << x << " + " << y << " != " << x + y << " got " << bigX + bigY << '\n';
    }

    if (bigX * bigY != BigInt(x * y))
    {
        std::cout << x << " * " << y << " != " << x * y << " got " << bigX * bigY << '\n';
    }
}

void doCheckEqual(const BigInt& actual, const char* expected, size_t line)
{
    const auto str = toString(actual);
    if (str != expected)
    {
        std::cout << "at line " << line << ": " << str << " != " << expected << '\n';
    }
}

#define checkEqual(x, y) do { doCheckEqual((x), (y), __LINE__); } while(0)
#define checkTrue(cond) do { if (!(cond)) std::cout << "at line " << __LINE__ << ": " << #cond << '\n'; } while(0)

int main()
{
    BigInt x = 3;
    checkEqual(x, "3");
    BigInt y = x;
    checkEqual(y, "3");
    BigInt z;
    checkEqual(z, "0");

    checkTrue(x == y);
    checkTrue(y == x);
    checkTrue(x != z);
    checkTrue(z != x);

    z = y;
    checkEqual(z, "3");

    x = 100;
    checkEqual(x, "100");

    checkTrue(!(x < x));
    checkTrue(x < 200);
    checkTrue(BigInt(50) < x);

    checkTrue(!(x > x));
    checkTrue(BigInt(200) > x);
    checkTrue(x > BigInt(50));

    checkTrue(x <= x);
    checkTrue(x <= 200);
    checkTrue(BigInt(50) <= x);

    checkTrue(x >= x);
    checkTrue(BigInt(200) >= x);
    checkTrue(x >= BigInt(50));

    checkEqual(BigInt(10) + BigInt(10), "20");


    for (int i = 0; i <= 21; ++i)
    {
        for (int j = 0; j <= 21; ++j)
        {
            check(i, j);
        }
    }

    const int64_t step = std::numeric_limits<uint32_t>::max() / 99;
    const int64_t lower = std::numeric_limits<int32_t>::min() + step;
    const int64_t upper = std::numeric_limits<int32_t>::max() - step;

    for (int64_t i = (0 > lower ? 0 : lower); i < upper; i += step)
    {
        for (int64_t j = 0; j < 99; ++j)
        {
            check(i, j);
        }
    }

    const BigInt big1 = std::numeric_limits<int64_t>::max();
    checkEqual(big1, "9223372036854775807");

    const BigInt big2 = big1 * big1;
    std::cout << "9223372036854775807 * 9223372036854775807\n";
    checkEqual(big2, "85070591730234615847396907784232501249");

    const BigInt big3 = big2 * big2;
    std::cout << "85070591730234615847396907784232501249 * 85070591730234615847396907784232501249\n";
    checkEqual(big3, "7237005577332262210834635695349653859421902880380109739573089701262786560001");

    std::cout << "done\n";

    return 0;
}
