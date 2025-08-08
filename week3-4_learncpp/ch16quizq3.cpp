#include <vector>
#include <string>
#include <cassert>
#include <iostream>
#include <utility>

template <typename T>
std::pair<int, int> minmax(std::vector<T> Vector)
{
    int mincount = 0;
    int maxcount = 0;
    int count = 0;
    for (T i : Vector)
    {
        i > Vector[maxcount] ? maxcount = count : maxcount = maxcount;
        i < Vector[mincount] ? mincount = count : mincount = mincount;
        count++;
    }
    return std::pair<int, int> {mincount, maxcount};
}

//template <typename T>
std::vector<int> enterValues()
{
    int input;
    std::vector<int> output;
    std::cout << "Enter numbers for the vector (-1 to stop): ";
    while (input != -1)
    {
        std::cin >> input;
        output.push_back(input);
    }
    output.pop_back();
    if (output.size() == 0)
    {
        std::cout << "Returning empty vector.\n";
    }
    return output;
}

template <typename T>
void printVector(std::vector<T> Vector)
{
    std::cout << "With array ( ";
    int count = 0;
    for (T i : Vector)
    {
        count++;
        if (count < Vector.size())
        {
            std::cout << i << ", ";
        } 
    }
    std::cout << Vector[count-1] << " ):\n";
}

int main()
{
    std::vector v1 { 3, 8, 2, 5, 7, 8, 3 };
    std::vector v2 { 5.5, 2.7, 3.3, 7.6, 1.2, 8.8, 6.6 };

    std::vector<int> v3 {enterValues()};
    std::cout << "The min element has index " << minmax(v3).first << " and value " << v3[minmax(v3).first] << '\n';
    std::cout << "The max element has index " << minmax(v3).second << " and value " << v3[minmax(v3).second] << '\n';

    printVector(v1);
    std::cout << "The min element has index " << minmax(v1).first << " and value " << v1[minmax(v1).first] << '\n';
    std::cout << "The max element has index " << minmax(v1).second << " and value " << v1[minmax(v1).second] << '\n';

    printVector(v2);
    std::cout << "The min element has index " << minmax(v2).first << " and value " << v2[minmax(v2).first] << '\n';
    std::cout << "The max element has index " << minmax(v2).second << " and value " << v2[minmax(v2).second] << '\n';
}