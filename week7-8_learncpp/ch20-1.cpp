#include <functional>
#include <iostream>

int plus(int x, int y)
{
    return x + y;
}

int multiply(int x, int y)
{
    return x * y;
}

int divide(int x, int y)
{
    return x / y;
}

int subtract(int x, int y)
{
    return x - y;
}

using ArithmeticFunction = std::function<int(int, int)>;

ArithmeticFunction getArithmeticFunction(char operation)
{
    switch (operation)
    {
        case '/' :
            return &divide;
        case '+' :
            return &plus;
        case '-' :
            return &subtract;
        case '*' :
            return &multiply;
        default:
            return &plus;
    }
}

int main()
{
    char input;
    int int1;
    int int2;
    std::cout << "Enter two integers and an operation (+,-,/,*).\nInt1: ";
    
    std::cin >> int1;

    std::cout << "Int2: ";

    std::cin >> int2;

    std::cout << "Operation: ";

    std::cin >> input;

    std::cout << "Result is: " << getArithmeticFunction(input)(int1, int2) << '\n';

    return 0;
}