#include <iostream>
#include "headers/Random.h"
#include <limits>

void ignoreLine()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

bool playhilo(int randomNumber, int guesses)
{
    int guess;

    while (true)
    {
        std::cout << "Guess a random number between 1 and 100.\n";
        std::cin >> guess;

        if (!std::cin || guess < 1 || guess > 100)
        {
            std::cin.clear();
            ignoreLine();
            std::cout << "Not a valid answer.\n";
            continue;
        }

        ignoreLine();

        if (guess == randomNumber)
        {
            std::cout << "You got it!\n";
            return true;
        }
        else if (guess < randomNumber)
        {
            std::cout << "Too low, you have " << guesses - 1 << " guess(es) left!\n";
            return false;
        }
        else
        {
            std::cout << "Too high, you have " << guesses - 1 << " guess(es) left!\n";
            return false;
        }
    }
}
    
bool playAgain()
{
	while (true)
	{
		char ch{};
		std::cout << "Would you like to play again (y/n)? ";
		std::cin >> ch;

        ignoreLine();

		if (ch == 'y')
		{
		    return true;
        }
        else if (ch == 'n')
        {
            return false;
        }
		else
        {
            std::cout << "Not a valid answer. ";
            continue;
        }
	}
}

int main()
{
    int randomNumber;
    int guesses;

    do
    {
        randomNumber = Random::get(1, 100);
        guesses = 7;

        std::cout << "Let's play hi-lo.\n";

        while (guesses > 0 && !playhilo(randomNumber, guesses))
        {
            --guesses;
        }
    } while (playAgain());
}