#include <iostream>
#include <vector>
#include <cassert>

namespace Animals
{
    enum type
    {
        chicken,
        dog,
        cat,
        elephant,
        duck,
        snake,
        max_animals
    };

    const std::vector<int> numOfLegs {2, 4, 4, 4, 2, 0};
}


int main()
{
    assert(std::size(Animals::numOfLegs) == Animals::max_animals);
    
    std::cout << "The elephant has " << Animals::numOfLegs[Animals::elephant] << " legs.\n";
    
    return 0;
}
