#include <vector>
#include <string>
#include <cassert>
#include <iostream>
#include <utility>
#include "headers/Random.h"


namespace WordList
{
    std::vector<std::string> words {"mystery", "broccoli" , "account", "almost", "spaghetti", "opinion", "beautiful", "distance", "luggage"};
    std::string randomWord(std::vector<std::string> words)
    {
        return words[Random::get(1, words.size()) - 1];
    }
}



int main()
{
    std::cout << "Welcome to hangman!\nTo win, guess the word. To lose, run out of pluses.\n\n";

    std::string word = WordList::randomWord(WordList::words);
    int wordLength = word.length();
    bool win = {false};
    bool guess = {false};
    std::string wordReveal;
    std::string wrongGuesses {"++++++"};
    for (int i = 0; i < wordLength; i++)
    {
        wordReveal.push_back('_');
    }

    while (!win)
    {
        std::cout << "The word is: " << wordReveal << "\t\t";

        std::cout << "Wrong guesses left: " << wrongGuesses << '\n';

        std::cout << "Enter your guess for a letter: ";
        
        std::string guess;

        while (true)
        {
            std::cin >> guess;

            if (guess.size() == 1 && guess[0] >= 'a' && guess[0] <= 'z') 
            {
                break; // valid input
            }

            std::cin.clear(); // put us back in 'normal' operation mode
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // and remove the bad input
            std::cout << "Invalid guess, enter again: "; 
        }

        std::cout << "Your guess is: " << guess << '\n';

        for (int i = 0; i < wordLength; ++i)
        {
            if (guess[0] == word[i])
            {
                wordReveal.replace(static_cast<size_t>(i), 1, 1, word[i]);
            }
        }
    }
}