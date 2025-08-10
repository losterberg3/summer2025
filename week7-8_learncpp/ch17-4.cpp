#include <array>
#include <iostream>
#include <string_view>

struct Item
{
    std::string_view name {};
    int gold {};
};

template <std::size_t N>
void printItems(const std::array<Item, N>& array)
{
    for (const auto& e : array)
    {
        std::cout << "A " << e.name << " costs " << e.gold << " gold.\n";
    }
}

int main()
{
    constexpr std::array items {Item{"sword", 5}, Item{"dagger", 3}, Item{"club", 2}, Item{"spear", 7}};

    printItems(items);
}