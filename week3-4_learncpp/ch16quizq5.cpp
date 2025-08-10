#include <vector>
#include <string>
#include <cassert>
#include <iostream>
#include <utility>
#include "headers/Random.h"


namespace WordList
{
    std::vector<std::string> words {"mystery", "broccoli" , "account", "almost", "spaghetti", "opinion", "beautiful", "distance", "luggage"};
    std::string randomWord(const std::vector<std::string>& words)
    {
        return words[Random::get(1, words.size()) - 1];
    }
}

class Session
{
    private:
    
    std::string m_word;
    std::vector<bool> m_letterGuessed;
    int m_guessesLeft;

    std::string m_wordReveal;
    std::string m_wrongLetters;

    public:

    Session() : 
        m_word(WordList::randomWord(WordList::words)),
        m_letterGuessed(26),
        m_guessesLeft(6)
    {
        initialize();
    }

    void initialize()
    {
        for (int i = 0; i < m_guessesLeft; i++)
        {
            m_wrongLetters.push_back('+');
        }
        
        for (int i = 0; i < m_word.length(); i++)
        {
            m_wordReveal.push_back('_');
        }
    }

    void displayState()
    {
        std::cout << "The word is: " << m_wordReveal << "\t\t";

        std::cout << "Wrong guesses left: " << m_wrongLetters << '\n';
    }

    char getGuess ()
    {
        std::cout << "Enter your guess for a letter: ";
            
        std::string guess;

        while (true)
        {
            std::cin >> guess;

            if (guess.size() != 1 || guess[0] < 'a' || guess[0] > 'z')
            {
                std::cin.clear(); // put us back in 'normal' operation mode
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // and remove the bad input
                std::cout << "Invalid guess, enter again: "; 
                continue;
            }

            if (m_letterGuessed[guess[0] - 'a'])
            {
                std::cout << "That letter has been guessed, try again: ";
                continue;
            }

            break;        
        }

        std::cout << "Your guess is: " << guess << '\n';

        m_letterGuessed[guess[0] - 'a'] = true;

        return guess[0] ;
    }

    void guessCondition(char c)
    {
        bool correctGuess = false;
    
        for (int i = 0; i < m_word.length(); ++i)
        {
            if (c == m_word[i])
            {
                m_wordReveal.replace(i, 1, 1, c);
                correctGuess = true;     
            }
        }

        if (correctGuess)
        {
            std::cout << "Correct guess!\n"; 
        }
        else
        {
            std::cout << "Wrong guess!\n";
            --m_guessesLeft;
            m_wrongLetters.erase(0, 1);
            m_wrongLetters.append(1, c);
        }
    }

    bool winCondition()
    {
        if (m_guessesLeft == 0 || m_word == m_wordReveal)
        {
            std::cout << "Game over, you ";
            m_guessesLeft == 0 ? std::cout << "lost.\n" : std::cout << "won!\n";
            return true;
        }
        else
        {
            return false;
        }
    }
};

int main()
{
    std::cout << "Welcome to hangman!\nTo win, guess the word. To lose, run out of pluses.\n\n";

    Session s {};

    while(!s.winCondition())
    {
        s.displayState();
        s.guessCondition(s.getGuess());
    }

    return 0;
}