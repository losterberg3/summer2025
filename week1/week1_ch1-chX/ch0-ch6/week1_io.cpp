#include <iostream>  // for std::cout and std::cin

int main()
{
    int x { 2 };
    std::cout << (x = 5) << "\n";

    return 0;
}

/*
cmake ..
make
./io
*/