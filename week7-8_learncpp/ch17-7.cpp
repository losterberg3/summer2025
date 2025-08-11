#include <iostream>

int main()
{
    const int perfSquare[4] {0, 1, 4, 9};

    std::cout << "Enter a single digit integer, -1 to quit.\n";

    int input;

    std::cin >> input;

    if (input == -1)
    {
        std::cout << "Bye.\n";
        return 0;
    }
    for (auto e : perfSquare)
    {
        if (e == input)
        {
            std::cout << e << " is a perfect square.\n";
            return 0;
        }
    }

    std::cout << input << " is not a perfect square.\n";

    return 0;
}