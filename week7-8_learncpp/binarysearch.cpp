#include <iostream>
#include <iterator>

int below;
int above;

int binarySearch(const int* array, int target, int min, int max)
{
    if (array[max] == target)
    {
        return max;
    }
    else if (array[min] == target)
    {
        return min;
    }
    else
    {
        if (array[min + (max - min)/2] == target)
        {
            return min + (max - min)/2;
        }
        else if (array[min + (max - min)/2] < target)
        {
            if (max - min < 2)
            {
                above++;
                if (above > 2)
                {
                    return -1;
                }
                return binarySearch(array, target, min + (max - min)/2, max);
            }
            else
            {
                return binarySearch(array, target, min + (max - min)/2, max);
            }
        }
        else
        {
            if (max - min < 2)
            {
                below++;
                if (below > 2)
                {
                    return -1;
                }
                return binarySearch(array, target, min, min + (max - min)/2);
            }
            else
            {
                return binarySearch(array, target, min, min + (max - min)/2);
            }
        }
    }
}

int main()
{
    constexpr int array[]{ 3, 6, 8, 12, 14, 17, 20, 21, 26, 32, 36, 37, 42, 44, 48 };
    constexpr int testValues[]{ 0, 3, 12, 13, 22, 26, 43, 44, 48, 49 };

    int expectedResult[]{ -1, 0, 3, -1, -1, 8, -1, 13, 14, -1 };

    static_assert(std::size(testValues) == std::size(expectedResult));

    int numTestValues { std::size(testValues) };
    
    for (int count{ 0 }; count < numTestValues; ++count)
    {
        int index{ binarySearch(array, testValues[count], 0, static_cast<int>(std::size(array)) - 1) };
        
        if (index == expectedResult[count])
             std::cout << "test value " << testValues[count] << " passed!\n";
        else 
             std::cout << "test value " << testValues[count] << " failed.  There's something wrong with your code!\n";
    }

    return 0;
}