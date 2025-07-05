#include <vector>
#include <string>
#include <iostream>

int main()
{
    std::vector<std::string> myStringVector;
    myStringVector.push_back("Hello");
    myStringVector.push_back("World");

    std::string firstString = myStringVector[0]; // Accesses "Hello"
    std::cout << firstString << '\n';
}