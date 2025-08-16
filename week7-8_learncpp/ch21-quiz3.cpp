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

    operator double() const;

    friend std::ostream& operator<< (std::ostream& out, const FixedPoint2& fp);

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

int main()
{
	FixedPoint2 a{ 0.01 };
	assert(static_cast<double>(a) == 0.01);

	FixedPoint2 b{ -0.01 };
	assert(static_cast<double>(b) == -0.01);

	FixedPoint2 c{ 1.9 }; // make sure we handle single digit decimal
	assert(static_cast<double>(c) == 1.9);

	FixedPoint2 d{ 5.01 }; // stored as 5.0099999... so we'll need to round this
	assert(static_cast<double>(d) == 5.01);

	FixedPoint2 e{ -5.01 }; // stored as -5.0099999... so we'll need to round this
	assert(static_cast<double>(e) == -5.01);

	// Handle case where the argument's decimal rounds to 100 (need to increase base by 1)
	FixedPoint2 f { 106.9978 }; // should be stored with base 107 and decimal 0
	assert(static_cast<double>(f) == 107.0);

	// Handle case where the argument's decimal rounds to -100 (need to decrease base by 1)
	FixedPoint2 g { -106.9978 }; // should be stored with base -107 and decimal 0
	assert(static_cast<double>(g) == -107.0);

	return 0;
}