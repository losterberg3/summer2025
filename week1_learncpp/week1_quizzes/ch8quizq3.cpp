#include <iostream>
#include "headers/Random.h"

bool playhilo(int randomNumber, int guesses)
{
    int guess;

    std::cout << "Guess a random number between 1 and 100.\n";
    std::cin >> guess;
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
    
bool playAgain()
{
	while (true)
	{
		char ch{};
		std::cout << "Would you like to play again (y/n)? ";
		std::cin >> ch;

		switch (ch)
		{
		case 'y': return true;
		case 'n': return false;
		}
        std::cout << "What? ";
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