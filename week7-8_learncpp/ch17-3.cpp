/*
#include <array>
#include <iostream>

template <typename T, std::size_t N>
void printArray(std::array<T, N> array)
{
    std::cout << "The array (";
    for (int i = 0; i < array.size() - 1; ++i)
    {
        std::cout << array.at(i) << ", ";
    }
    std::cout << array.back() << ") has length " << array.size() << '\n'; 
}


int main()
{
    constexpr std::array arr1 { 1, 4, 9, 16 };
    printArray(arr1);

    constexpr std::array arr2 { 'h', 'e', 'l', 'l', 'o' };
    printArray(arr2);

    return 0;
}
*/

#include <array>
#include <iostream>

template <typename T, std::size_t N>
void printArray(const std::array<T, N>& arr)
{
    std::cout << "The array (";

    auto separator {""};
    for (const auto& e: arr)
    {
        std::cout << separator << e;
        separator = ", ";
    }

    std::cout << ") has length " << N << '\n';
}

int main()
{
    constexpr std::array arr1 { 1, 4, 9, 16 };
    printArray(arr1);

    constexpr std::array arr2 { 'h', 'e', 'l', 'l', 'o' };
    printArray(arr2);

    return 0;
}