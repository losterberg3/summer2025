#include <string>
#include <iostream>
#include "headers/Random.h"

class Monster
{
public:

    enum Type
    {
        dragon,
        goblin,
        ogre,
        orc,
        skeleton,
        troll,
        vampire,
        zombie,
        maxMonsterTypes,
    };

private:

    Type m_type{};
    std::string m_name{"?"};
    std::string m_roar{"?"};
    int m_hitPoints{};

public:

    Monster(Type type, std::string name, std::string roar, int hitPoints)
    : m_type{ type }, m_name{ name }, m_roar{ roar }, m_hitPoints{ hitPoints }
    {}

    const std::string getTypeString() const
    {
        switch (m_type)
        {
        case dragon:   return "dragon";
        case goblin:   return "goblin";
        case ogre:     return "ogre";
        case orc:      return "orc";
        case skeleton: return "skeleton";
        case troll:    return "troll";
        case vampire:  return "vampire";
        case zombie:   return "zombie";
        default:       return "???";
        }
    }

    void print() const
    {
        if (m_hitPoints != 0)
        {
            std::cout << m_name << " the " << getTypeString() << " has " << m_hitPoints << " hit points and says " << m_roar << ".\n";
        }
        else
        {
            std::cout << m_name << " the " << getTypeString() << " is dead.\n";
        }
    }

};

namespace MonsterGenerator
{
    const Monster::Type getType()
    {
        int num = Random::get(0, 7);
        Monster::Type type {static_cast<Monster::Type>(num)};
        return type;
    }

    const std::string getName()
    {
        int num = Random::get(0, 5);
        switch(num)
        {
        case 5: return "Lars";
        case 4: return "Ben";
        case 3: return "Matteo";
        case 2: return "George";
        case 1: return "Moisés";
        case 0: return "Hayes";
        default: return "???";
        }
    }

    const std::string getRoar()
    {
        int num = Random::get(0, 5);
        switch(num)
        {
        case 5: return "ROAR";
        case 4: return "roar";
        case 3: return "rOaR";
        case 2: return "meow";
        case 1: return "ROAr";
        case 0: return "rOAR";
        default: return "???";
        }
    }

    const int getHitPoints()
    {
        return Random::get(1, 100);
    }

    Monster generate()
    {
        return Monster{ getType(), getName(), getRoar(), getHitPoints()};
    }

};

int main()
{
	Monster m{ MonsterGenerator::generate() };
	m.print();

	return 0;
}