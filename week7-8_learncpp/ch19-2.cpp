#include <string>
#include <iostream>

int main()
{
    int numOfNames;
    std::cout << "Enter how many names you want to enter: ";
    std::cin >> numOfNames;

    std::string* array{ new std::string[numOfNames]{}};

    for (std::size_t i = 0; i < numOfNames; ++i)
    {
        std::cout << "Name #" << i << ' ';
        std::cin >> array[i];
    }

    int arrayLength = numOfNames;
    std::sort(array, array + arrayLength);

    std::cout << "Here's your sorted names: \n";

    for (std::size_t i = 0; i < numOfNames; ++i)
    {
        std::cout << "Name #" << i << ": " << array[i] << '\n';
    }
}