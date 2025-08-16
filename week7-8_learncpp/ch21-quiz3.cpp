#include <cassert>
#include <iostream>
#include <cmath>
#include <cstdlib>

class FixedPoint2
{
    private:

    uint16_t m_nonfractional {};
    uint8_t m_fractional {}; 
    bool m_negative {};

    public:

    explicit FixedPoint2(int nonf, int f)
        : m_nonfractional{static_cast<uint16_t>(std::abs(nonf))},
        m_fractional{static_cast<uint8_t>(std::abs(f))},
        m_negative{((nonf < 0) || (f < 0))}
    {
        if (m_fractional > 99) 
        {
            m_nonfractional += 1;
            m_nonfractional -= 100;
        }
    }

    explicit FixedPoint2(double dbl)
        : m_nonfractional{static_cast<u_int16_t>(std::abs(dbl))},
        m_fractional{static_cast<u_int8_t>(std::round((std::abs(dbl) - static_cast<int>(std::abs(dbl))) * 100))},
        m_negative{dbl < 0}
    {
        if (m_fractional == 100) 
        {
            m_nonfractional += 1;
            m_fractional = 0;
        }
    }

    friend FixedPoint2 operator+ (const FixedPoint2& fp1, const FixedPoint2& fp2);

    operator double() const;

    friend std::istream& operator>> (std::istream& in, FixedPoint2& fp);

    friend std::ostream& operator<< (std::ostream& out, const FixedPoint2& fp);

    friend bool operator== (const FixedPoint2& fp1, const FixedPoint2& fp2);

    friend bool testDecimal(const FixedPoint2 &fp);
};

FixedPoint2::operator double() const
{
    return m_negative ? 
        - (static_cast<double>(m_nonfractional) + static_cast<double>(m_fractional)/100)
        : (static_cast<double>(m_nonfractional) + static_cast<double>(m_fractional)/100);
}

std::ostream& operator<< (std::ostream& out, const FixedPoint2& fp)
{
    out << static_cast<double>(fp);

    return out;
}

std::istream& operator>> (std::istream& in, FixedPoint2& fp)
{
    double input;
    in >> input;

    fp = FixedPoint2 {input};

    return in;
}

FixedPoint2 operator+ (const FixedPoint2& fp1, const FixedPoint2& fp2)
{
    return FixedPoint2{ static_cast<double>(fp1) + static_cast<double>(fp2) };
}

bool operator== (const FixedPoint2& fp1, const FixedPoint2& fp2)
{
    return (fp1.m_fractional == fp2.m_fractional && fp1.m_negative == fp2.m_negative && fp1.m_nonfractional == fp2.m_nonfractional);
}

int main()
{
	assert(FixedPoint2{ 0.75 } == FixedPoint2{ 0.75 });    // Test equality true
	assert(!(FixedPoint2{ 0.75 } == FixedPoint2{ 0.76 })); // Test equality false

	// Test additional cases -- h/t to reader Sharjeel Safdar for these test cases
	assert(FixedPoint2{ 0.75 } + FixedPoint2{ 1.23 } == FixedPoint2{ 1.98 });    // both positive, no decimal overflow
	assert(FixedPoint2{ 0.75 } + FixedPoint2{ 1.50 } == FixedPoint2{ 2.25 });    // both positive, with decimal overflow
	assert(FixedPoint2{ -0.75 } + FixedPoint2{ -1.23 } == FixedPoint2{ -1.98 }); // both negative, no decimal overflow
	assert(FixedPoint2{ -0.75 } + FixedPoint2{ -1.50 } == FixedPoint2{ -2.25 }); // both negative, with decimal overflow
	assert(FixedPoint2{ 0.75 } + FixedPoint2{ -1.23 } == FixedPoint2{ -0.48 });  // second negative, no decimal overflow
	assert(FixedPoint2{ 0.75 } + FixedPoint2{ -1.50 } == FixedPoint2{ -0.75 });  // second negative, possible decimal overflow
	assert(FixedPoint2{ -0.75 } + FixedPoint2{ 1.23 } == FixedPoint2{ 0.48 });   // first negative, no decimal overflow
	assert(FixedPoint2{ -0.75 } + FixedPoint2{ 1.50 } == FixedPoint2{ 0.75 });   // first negative, possible decimal overflow

	FixedPoint2 a{ -0.48 };
	assert(static_cast<double>(a) == -0.48);
	assert(static_cast<double>(-a) == 0.48);

	std::cout << "Enter a number: "; // enter 5.678
	std::cin >> a;
	std::cout << "You entered: " << a << '\n';
	assert(static_cast<double>(a) == 5.68);

	return 0;
}