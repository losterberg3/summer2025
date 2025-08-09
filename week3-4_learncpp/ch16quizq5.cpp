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

class Session
{
    private:
    
    std::string m_word { WordList::randomWord(WordList::words) };

    std::vector<bool> m_letterGuessed { std::vector<bool>(26) };

    std::string m_wordReveal {};
    std::string m_guessesLeft {};
    int m_numOfGuesses = 6;

    public:

    std::string get_word() const { return m_word; }
    
    bool isLetterGuessed(char letter) { return m_letterGuessed[ letter - 97]; }
    void setLetterGuessed(char letter) { m_letterGuessed[letter - 97] = true; }
    
    std::string get_wordReveal() const { return m_wordReveal; }
    void set_wordReveal(std::string wordRveal) { m_wordReveal = wordRveal; }
    
    std::string get_guessesLeft() const { return m_guessesLeft; }
    void set_guessesLeft(std::string guessesLeft) { m_guessesLeft = guessesLeft; }

    int get_numOfGuesses() const { return m_numOfGuesses; }
    void minus_numOfGuesses() { --m_numOfGuesses; }

};

void setState(Session& s)
{
    std::string wordReveal { };
    std::string wrongGuesses { };

    for (int i = 0; i < s.get_numOfGuesses(); i++)
    {
        wrongGuesses.push_back('+');
    }
    
    for (int i = 0; i < s.get_word().length(); i++)
    {
        wordReveal.push_back('_');
    }

    s.set_wordReveal(wordReveal);
    s.set_guessesLeft(wrongGuesses);
}

void displayState (const Session& s)
{
    std::cout << "The word is: " << s.get_wordReveal() << "\t\t";

    std::cout << "Wrong guesses left: " << s.get_guessesLeft() << '\n';
}

char getGuess (Session& s)
{
    std::cout << "Enter your guess for a letter: ";
        
    std::string guess;

    while (true)
    {
        std::cin >> guess;

        if (s.isLetterGuessed(guess[0]))
        {
            std::cout << "That letter has been guessed, try again: \n";
            continue;
        }

        if (guess.size() == 1 && guess[0] >= 'a' && guess[0] <= 'z') 
        {
            break; // valid input
        }

        std::cin.clear(); // put us back in 'normal' operation mode
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // and remove the bad input
        std::cout << "Invalid guess, enter again: "; 
    }

    std::cout << "Your guess is: " << guess << '\n';

    s.setLetterGuessed(guess[0]);

    return guess[0] ;
}

void guessCondition(Session& s, char c)
{
    bool correctGuess;
 
    for (int i = 0; i < s.get_word().length(); ++i)
    {
        if (c == s.get_word()[i])
        {
            s.set_wordReveal(s.get_wordReveal().replace(i, 1, 1, c));
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
        s.minus_numOfGuesses();
        std::string guessedLetters { s.get_guessesLeft() };
        guessedLetters.erase(0, 1);
        guessedLetters.append(1, c);
        s.set_guessesLeft(guessedLetters);
    }
}

bool winCondition(Session& s)
{
    if (s.get_numOfGuesses() == 0 || s.get_word() == s.get_wordReveal())
    {
        std::cout << "Game over, you ";
        s.get_numOfGuesses() == 0 ? std::cout << "lost.\n" : std::cout << "won!\n";
        return true;
    }
    else
    {
        return false;
    }
}


int main()
{
    std::cout << "Welcome to hangman!\nTo win, guess the word. To lose, run out of pluses.\n\n";

    Session s {};

    setState(s);

    while(!winCondition(s))
    {
        displayState(s);
        guessCondition(s, getGuess(s));
    }

    return 0;
}