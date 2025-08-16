#include <iostream>


class Average
{
    private:

    std::int32_t m_sum{};
    std::int32_t m_totalnumbers{};

    public:

    friend std::ostream& operator<< (std::ostream& out, Average avg);

    Average& operator+= (int i);

};

std::ostream& operator<< (std::ostream& out, Average avg)
{
    out << ((avg.m_sum == 0) ? 0 : static_cast<double>(avg.m_sum) / static_cast<double>(avg.m_totalnumbers));
    return out;
}

Average& Average::operator+= (int i)
{
    m_sum += i;
    m_totalnumbers += 1;
    return *this;
}

int main()
{
	Average avg{};
	std::cout << avg << '\n';

	avg += 4;
	std::cout << avg << '\n'; // 4 / 1 = 4

	avg += 8;
	std::cout << avg << '\n'; // (4 + 8) / 2 = 6

	avg += 24;
	std::cout << avg << '\n'; // (4 + 8 + 24) / 3 = 12

	avg += -10;
	std::cout << avg << '\n'; // (4 + 8 + 24 - 10) / 4 = 6.5

	(avg += 6) += 10; // 2 calls chained together
	std::cout << avg << '\n'; // (4 + 8 + 24 - 10 + 6 + 10) / 6 = 7

	Average copy{ avg };
	std::cout << copy << '\n';

	return 0;
}