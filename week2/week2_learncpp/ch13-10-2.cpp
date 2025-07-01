#include <iostream>

struct Fraction
{
    int numerator;
    int denominator;
};

Fraction read()
{
    Fraction fraction;
    std::cout << "Enter a value for the numerator.\n";
    std::cin >> fraction.numerator;
    std::cout << "Enter a value for the denominator.\n";
    std::cin >> fraction.denominator;
    return fraction;
}

void print(const Fraction& fraction)
{
    std::cout << fraction.numerator << "/" << fraction.denominator << '\n';
}

Fraction multiply(const Fraction& f1, const Fraction& f2)
{
    Fraction prod{f1.numerator*f2.numerator, f1.denominator*f2.denominator};
    return prod;
}

int main()
{
    Fraction f1 = read();
    Fraction f2 = read();
    Fraction prod = multiply(f1,f2);

    std::cout << "Your fractions multiplied together: ";
    print(prod);

}