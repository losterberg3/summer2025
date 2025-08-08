#include <vector>
#include <string>
#include <cassert>
#include <iostream>

/*question 1
std::vector even {2, 4, 6, 8, 10, 12};

const std::vector constants {1.2, 3.4, 5.6, 7.8};

const std::vector<std::string_view> stringview {"Alex", "Brad", "Charles", "Dave"};

*/

namespace Items
{
    enum Type
    {
        health_potions,
        torches,
        arrows,
        numberOfItems
    };
}

int sum(const std::vector<int>& vector)
{
    int sum {0};
    for (auto i : vector)
    {
        sum+=i;
    }
    return sum;
}

std::string printItemName_s(int vectorElement, int index)
{
    if (vectorElement==1)
    {
        switch(index)
        {
            case Items::health_potions: return " health potion.";
            case Items::torches: return " torch.";
            case Items::arrows: return " arrow.";

            default: return "???";
        } 
    }
    else
    {
        switch(index)
        {
            case Items::health_potions: return " health potions.";
            case Items::torches: return " torches.";
            case Items::arrows: return " arrows.";

            default: return "???";
        }
    }

    return "nothing.";
}

int main()
{
    std::vector<int> numItem {1, 5, 10};
    assert(std::size(numItem) == Items::numberOfItems);

    int count = 0;
    for (auto i : numItem)
    {
        std::cout << "You have " << i << printItemName_s(i, count) << '\n';
        count++;
    }

    std::cout << "The total number of items is " << sum(numItem) << ".\n";
}

