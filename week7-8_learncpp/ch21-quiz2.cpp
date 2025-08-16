#include <iostream>
#include <cassert>

class IntArray
{
    private:

    int* m_arr;
    size_t m_len;

    public:

    IntArray(size_t length)
        :  m_arr{new int[length]}, m_len{length}
    {}

    int& operator[](int i);

    friend std::ostream& operator<< (std::ostream& out, IntArray arr);

    IntArray& operator= (const IntArray& arr);
};

int& IntArray::operator[](int i)
{
    assert(i < m_len);
    return m_arr[i];
}

std::ostream& operator<< (std::ostream& out, IntArray arr)
{
    for (size_t i = 0; i < arr.m_len; ++i)
    {
        out << arr.m_arr[i];
    }

    return out;
}

IntArray& IntArray::operator= (const IntArray& arr)
{
    if (this == &arr)
    {
        return *this;
    }

    m_len = arr.m_len;

    m_arr = new int[m_len]{};

    for (size_t i = 0; i < m_len; ++i)
    {
        m_arr[i] = arr.m_arr[i];
    }

    return *this;
}

IntArray fillArray()
{
	IntArray a(5);

	a[0] = 5;
	a[1] = 8;
	a[2] = 2;
	a[3] = 3;
	a[4] = 6;

	return a;
}

int main()
{
	IntArray a{ fillArray() };

	std::cout << a << '\n';

	auto& ref{ a }; // we're using this reference to avoid compiler self-assignment errors
	a = ref;

	IntArray b(1);
	b = a;

	a[4] = 7;

	std::cout << b << '\n';

	return 0;
}