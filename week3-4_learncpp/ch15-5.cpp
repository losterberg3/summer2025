#include <iostream>
#include <string>

template <typename T, typename P, typename Q>
class Triad
{
private: 
    T int1{};
    P int2{};
    Q int3{};

public:
    Triad(const T& INT1, const P& INT2, const Q& INT3)
    : int1{INT1}
    , int2{INT2}
    , int3{INT3}
    {
        std::cout << "Constructor constructed :)\n";  
    }

    const T& first() const
    {
        return int1;
    }

    const P& second() const
    {
        return int2;
    }

    const Q& third() const
    {
        return int3;
    }

    void print() const;
};

template <typename T, typename P, typename Q>
void Triad<T, P, Q>::print() const
{
    std::cout << "[" << int1 << ", " << int2 << ", " << int3 << "]\n";
}

int main()
{
	Triad<int, int, int> t1{ 1, 2, 3 };
	t1.print();
	std::cout << '\n';
	std::cout << t1.first() << '\n';

	using namespace std::literals::string_literals;
	const Triad t2{ 1, 2.3, "Hello"s };
	t2.print();
	std::cout << '\n';

	return 0;
}