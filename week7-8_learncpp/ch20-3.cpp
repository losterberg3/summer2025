#include <iostream>

int factorial(int N)
{
    if (N > 1)
    {
        return N * factorial(N-1);
    }
    return 1;
}

int digitSum(int N)
{
    if (N >= 10)
    {
        return (N % 10) + digitSum(N / 10);
    }

    return N;
}

int main()
{
    std::cout << digitSum(427);
}