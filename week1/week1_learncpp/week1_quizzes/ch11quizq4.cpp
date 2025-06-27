#include <iostream>

int foo(int n)
{
    return n + 10;
}

template <typename T>
int foo(T n)
{
    return n;
}

int main()
{
    std::cout << foo(1) << '\n'; // #1

    short s { 2 };
    std::cout << foo(s) << '\n'; // #2

    std::cout << foo<int>(4) << '\n'; // #3

    std::cout << foo<int>(s) << '\n'; // #4

    std::cout << foo<>(6) << '\n'; // #5

    int x = 2;

    std::cout << x << '\n';

    return 0;
}

/* output
11
2
4
2
6
*/ 