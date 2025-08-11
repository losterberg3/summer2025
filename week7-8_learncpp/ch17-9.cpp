#include <iostream>
#include <cstring>

void cStringPrint(const char arr[])
{
    auto __begin { arr };
    auto __end { arr + std::strlen(arr) };
    for (; __begin - 1 != __end; --__end)
    {
        std::cout << *__end << ' ';
    }
}

int main()
{
    char arr[] { "Hello, world!" };

    cStringPrint(arr);

    std::cout << '\n';
}
