#include <iostream>

class Fraction
{
    private: 
    int m_num {0};
    int m_den {1};

    public:

    explicit Fraction(int num=0, int den=1) 
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

    friend std::ostream& operator<< (std::ostream& out, const Fraction& f);

    friend std::istream& operator>> (std::istream& in, Fraction& f);


    friend Fraction operator*(const Fraction& f1, int Int1);

    friend Fraction operator*(int Int1, const Fraction& f1);

    friend Fraction operator*(const Fraction& f1, const Fraction& f2);

};

std::ostream& operator<< (std::ostream& out, const Fraction& f)
{
    out << f.m_num << '/' << f.m_den;

    return out;
}

std::istream& operator>> (std::istream& in, Fraction& f)
{
    int numerator {};
    char ignore {};
    int denominator {};

    in >> numerator >> ignore >> denominator;
    if (denominator == 0)                       
        in.setstate(std::ios_base::failbit);    
    if (in)                                     
        f = Fraction {numerator, denominator}; 

    return in;
}


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
	Fraction f1{};
	std::cout << "Enter fraction 1: ";
	std::cin >> f1;

	Fraction f2{};
	std::cout << "Enter fraction 2: ";
	std::cin >> f2;

	std::cout << f1 << " * " << f2 << " is " << f1 * f2 << '\n'; // note: The result of f1 * f2 is an r-value

	return 0;
}