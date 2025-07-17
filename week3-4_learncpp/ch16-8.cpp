#include <string>
#include <iostream>
#include <vector>

int main()
{
    std::vector<std::string_view> names {"Alex", "Betty", "Caroline", "Dave", "Emily", "Fred", "Greg", "Holly"};

    std::cout << "Enter a name: ";
    std::string guess;
    std::cin >> guess;

    for (std::string_view name : names)
    {
        if (guess == name) 
        {
            std::cout << guess << " was found.\n";
            return 0;
        }
    }

    std::cout << guess << " was not found.\n";
    return 0;
}