#include <iostream>
#include <string>

struct Monster
{
    std::string type;
    std::string name;
    int health;
};

void printMonster(Monster monster)
{
    std::cout << "This " << monster.type << " is named " << monster.name << " and has " << monster.health << " health.\n";
}

int main()
{
    Monster torg{"Ogre" , "Torg" , 145};
    Monster blurp{"Slime" , "Blurp" , 23};
    printMonster(torg);
    printMonster(blurp);
    return 0;
}