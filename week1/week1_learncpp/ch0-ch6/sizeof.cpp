#include <iostream>

int main()
{
    char ch1{ 'a' }; // (preferred)
    std::cout << ch1; // cout prints character 'a'

    char ch2{ 14 }; // code point for 'b' (not preferred)
    std::cout << ch2; // cout prints a character ('b')


    return 0;
}

/*
cmake ..
make
./io
*/