#include <iostream>
#include <vector>


template <typename T>
void printArray(const std::vector<T>& vec)
{
    for (std::size_t index{0}; index < vec.size(); ++index)
        std::cout << vec[index] << ' ';
    std::cout << '\n';
}

template <typename T>
int searchArray(const std::vector<T>& vec, T input)
{
    for (std::size_t index{0}; index < vec.size(); ++index)
    {
        if (input == vec[index])
            return static_cast<int>(index);
    }

    return -1;
}

template <typename T>
void printValuePlusIndex(T val, int index)
{
    if (index == -1)
    {
        std::cout << "The number " << val << " was not found.\n";
    }
    else
    {
        std::cout << "The number " << val << " has index " << index << '\n';
    }
}

template <typename T>
T getValidNumber(T help)
{
    T num {};

    while (num < 1 || num > 10)
    {
        std::cout << "Enter a number between 1 and 10: ";
        std::cin >> num;

        if (!std::cin)
        {
            std::cin.clear();
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    return num;
}

int main()
{
    std::vector arr{ 4.4, 6.6, 7.7, 3.3, 8.8, 2.2, 1.1, 9.9 };

    auto num { getValidNumber(1.0) };

    printArray(arr); // use function template to print array

    printValuePlusIndex(num , searchArray(arr, num));

    return 0;
}