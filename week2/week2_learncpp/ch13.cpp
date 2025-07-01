#include <iostream>

namespace Monsters
{
    enum MonsterType
{
    orc,
    goblin,
    troll,
    ogre,
    skeleton,
};
};

int main()
{
    Monsters::MonsterType Troll1{ Monsters::troll };
    return 0;
}


