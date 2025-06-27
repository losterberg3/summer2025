#include <iostream>

template <typename T>

T add(T x, T y)
{
	return x + y;
}

template <typename T>

T mult(T x, int y)
{
	return x * y;
}

template <typename T, typename U>

auto sub(T x, U y)
{
	return x - y;
}

template <typename T>
int count(T) // This is the same as int count(T x), except we're not giving the parameter a name since we don't use the parameter
{
    static int c { 0 };
    return ++c;
}

int main()
{
	std::cout << add(2, 3) << '\n';
	std::cout << add(1.2, 3.4) << '\n';

	std::cout << mult(2, 3) << '\n';
	std::cout << mult(1.2, 3) << '\n';

	std::cout << sub(3, 2) << '\n';
	std::cout << sub(3.5, 2) << '\n';
	std::cout << sub(4, 1.5) << '\n';

	std::cout << count(1) << '\n';
    std::cout << count(1) << '\n';
    std::cout << count(2.3) << '\n';
    std::cout << count<double>(1) << '\n'; // count<double> used to explicitly call double version of template count

	return 0;
}