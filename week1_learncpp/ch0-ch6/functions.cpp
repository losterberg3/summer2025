#include <iostream>

int readNumber()
{
    int input;
    std::cout << "Input a number" << '\n';

    std::cin >> input;

    return input;
}

void writeAnswer(int Answer)
{
    std::cout << Answer << '\n';
}