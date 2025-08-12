#include <iterator> 
#include <utility>
#include <iostream>
#include <cstring>

int main()
{
    int array[]{ 6, 3, 2, 9, 7, 1, 5, 4, 8 };

    for (int j = 0; j<std::size(array)-1; ++j)
    {
        int count = 0;
        for (int i = 0; i<std::size(array)-1-j; ++i)
        {
            if (array[i] > array[i+1])
            {
                std::swap(array[i], array[i+1]);
                count++;
            }
        }
        if (count == 0)
        {
            std::cout << "Array sorted on iteration " << j+1 << '\n';
            break;
        }
    }

    for (int i = 0; i<std::size(array); ++i)
    {
        std::cout << array[i];
    }
    std::cout << '\n';
    return 0;
}