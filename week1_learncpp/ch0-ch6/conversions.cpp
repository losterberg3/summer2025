#include <iostream>

float doSomething()
{
    return 3.0000; // double value 3.0 implicitly converted to type float
}

int main()
{
    std::cout << doSomething() << '\n';
    return 0;
}