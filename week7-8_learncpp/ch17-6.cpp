#include <array>
#include <iostream>
#include <string_view>

namespace Animal
{
    enum animals
    {
        chicken, 
        dog, 
        cat, 
        elephant, 
        duck, 
        snake,
        max_animals
    };

    struct Data
    {
        std::string_view name;
        int numOfLegs;
        std::string_view sound;
    };

    constexpr std::array<Data, max_animals> animalData {{
        {"chicken", 2, "cluck"},
        {"dog", 4, "bark"},
        {"cat", 4, "meow"},
        {"elephant", 4, "yawoo"},
        {"duck", 2, "quack"},
        {"snake", 0, "hiss"}
    }}; 
}

void printAnimal(Animal::animals animalNumber)
{
    using namespace Animal;
    std::cout << "The " << animalData[animalNumber].name <<  " has " << animalData[animalNumber].numOfLegs << " legs and says " << animalData[animalNumber].sound << '\n';
}

std::istream& operator>> (std::istream& in, Animal::animals& animal)
{
    std::string input {};
    std::getline(in >> std::ws, input);

    for (std::size_t index=0; index < Animal::max_animals; ++index)
    {
        if (input == Animal::animalData[index].name)
        {
            animal = static_cast<Animal::animals>(index);
            return in;
        }
    }

    in.setstate(std::ios_base::failbit);

    return in;
}

int main()
{
    Animal::animals animal {Animal::max_animals};

    std::cout << "Put an animal name.\n";

    std::cin >> animal;

    if (!std::cin)
    {
        std::cout << "That animal couldn't be found. ";
    }
    else
    {
        printAnimal(animal);
    }

    std::cout <<  "Here's data for the rest of the animals.\n\n";

    for (int i = Animal::chicken; i<Animal::max_animals; ++i)
    {
        Animal::animals a = static_cast<Animal::animals>(i);

        if (a == animal)
        {
            continue;
        }

        printAnimal(a);
    }

}