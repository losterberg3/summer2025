#include <string>
#include <iostream>
#include <vector>

template <typename T>
bool isValueInArray(const std::vector<T>& vec, const T& val)
{
    for (const auto& name : vec)
    {
        if (val == name) 
        {
            std::cout << val << " was found.\n";
            return true;
        }
    } 

    std::cout << val << " was not found.\n";
    return false;
}


int main()
{
    std::vector<std::string_view> names {"Alex", "Betty", "Caroline", "Dave", "Emily", "Fred", "Greg", "Holly"};

    std::cout << "Enter a name: ";
    std::string guess;
    std::cin >> guess;

    isValueInArray<std::string_view>(names, guess);

    return 0;
}