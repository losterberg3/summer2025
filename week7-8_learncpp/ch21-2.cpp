#include <iostream>

class Fraction
{
    private: 
    int m_num {0};
    int m_den {1};

    public:

    explicit Fraction(int num, int den=1) 
        : m_num{num}, m_den{den}
    {
        reduce();
    }

    void print()
    {
        std::cout << m_num << '/' << m_den << '\n';
    }

    int gcd(int a, int b) 
    {
        return (b == 0) ? std::abs(a) : gcd(b, a % b);
    }

    void reduce()
    {
        int GCD = gcd(m_num, m_den);
        m_num/=GCD;
        m_den/=GCD;
    }

    Fraction friend operator*(const Fraction& f1, int Int1);

    Fraction friend operator*(int Int1, const Fraction& f1);

    Fraction friend operator*(const Fraction& f1, const Fraction& f2);

};

Fraction operator*(const Fraction& f1, const Fraction& f2)
{
    return Fraction {f1.m_num*f2.m_num, f1.m_den*f2.m_den};
}

Fraction operator*(const Fraction& f1, int Int1)
{
    return Fraction {f1.m_num*Int1, f1.m_den};
}

Fraction operator*(int Int1, const Fraction& f1)
{
    return Fraction {f1 * Int1};
}

int main()
{
    Fraction f1{2, 5};
    f1.print();

    Fraction f2{3, 8};
    f2.print();

    Fraction f3{ f1 * f2 };
    f3.print();

    Fraction f4{ f1 * 2 };
    f4.print();

    Fraction f5{ 2 * f2 };
    f5.print();

    Fraction f6{ Fraction{1, 2} * Fraction{2, 3} * Fraction{3, 4} };
    f6.print();

    Fraction f7{0, 6};
    f7.print();

    return 0;
}