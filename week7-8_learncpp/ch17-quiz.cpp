#include <iostream>
#include <array>
#include <vector>
#include <iterator>
#include <cstring>
#include <string_view>
#include "headers/Random.h"

namespace Potion
{
    enum Type
    {
        healing,
        mana,
        speed,
        invisibility,
        max_potions
    };

    constexpr std::array<int, max_potions> costs { 20, 30, 12, 50 };

    constexpr std::array<std::string_view, max_potions> names { "healing", "mana", "speed", "invisibility" };
}

class Player
{
    private: 

    std::string_view m_name;
    std::array<int, Potion::max_potions> m_potionInventory;
    int m_gold;

    public:

    Player() :
        m_gold(Random::get(80, 120)),
        m_potionInventory()
        {
            initialize();
        }
    
    void initialize()
    {
        std::string input;
        std::cout << "Welcome to Roscoe's potion emporium!\nEnter your name: ";
        
        std::cin >> input;

        m_name = input;

        std::cout << "Hello, " << m_name << ", you have " << m_gold << " gold.\n\n";
    }

    void shop(bool& keepBuying)
    {
        using namespace Potion;
        std::cout << "Here is our selection for today:\n";
        for (std::size_t i = 0; i < static_cast<std::size_t>(max_potions); i++)
        {
            std::cout << i << ") " << names[i] << " costs " << costs[i] << " gold.\n";
        }
        std::cout << "Enter the number for the selection you want, q to quit: ";

        std::string input;
        
        while(true)
        {
            std::cin >> input;

            if (input[0] == 'q' && input.length() < 2)
            {
                std::cout << "Your inventory contains:\n";
                for (int i = 0; i < max_potions; ++i)
                {
                    std::cout << m_potionInventory[i] << "x " << names[i] << '\n';
                }
                std::cout << "Thanks for shopping at Roscoe's!\n";
                keepBuying = false;
                break;
            }

            if (input.length() > 1 || input[0] < '0' || input[0] >= '4')
            {
                std::cout << "Invalid input. Go again: ";
                continue;
            }

            if (costs[input[0] - '0'] > m_gold)
            {
                std::cout << "You don't have enough gold for that. Try a different item: ";
                continue;
            }

            m_gold -= costs[input[0] - '0'];
            std::cout << "You purchased " << names[input[0] - '0'] << ". You have " << m_gold << " left.\n";
            m_potionInventory[input[0] - '0']++;
            break;
        }
    }
};

int main()
{
    Player p;

    bool keepBuying = true;

    while (keepBuying)
    {
        p.shop(keepBuying);
    }
    
    return 0;
}