#include <iostream>
#include <array>
#include "headers/Random.h"

namespace Settings
{
    const int bust = 21;
    const int stop = 17;
}

struct Card
{
    enum Rank
    {
        rank_ace,
        rank_2,
        rank_3,
        rank_4,
        rank_5,
        rank_6,
        rank_7,
        rank_8,
        rank_9,
        rank_10,
        rank_jack,
        rank_queen,
        rank_king,

        max_ranks
    };

    enum Suit
    {
        suit_club,
        suit_diamond,
        suit_heart,
        suit_spade,

        max_suits
    };

    Rank rank{};
    Suit suit{};

    friend std::ostream& operator<<(std::ostream& out, const Card &card)
    {
        static constexpr std::array ranks { 'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K' };
        static constexpr std::array suits { 'C', 'D', 'H', 'S' };

        out << ranks[card.rank] << suits[card.suit];// print your card rank and suit here
        return out;
    }

    static constexpr std::array allRank { rank_ace, rank_2, rank_3, rank_4, rank_5, rank_6, rank_7, rank_8, rank_9, rank_10, rank_jack, rank_queen, rank_king };
    static constexpr std::array allSuits { suit_club, suit_diamond, suit_heart, suit_spade };

    int value() const
    {
        constexpr std::array val { 11, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10 };
        return val[rank];
    }
};

class Deck
{
    private:

    std::array<Card, 52> m_cards {};
    std::size_t m_nextCardIndex { 0 };

    public:

    Deck() 
    {
        int i = 0;
        for (Card::Suit s : Card::allSuits)
        {
            for (Card::Rank r : Card::allRank)
            {
                m_cards[i].rank = r;
                m_cards[i].suit = s;
                i++;
            }
        }
    }  

    void shuffle()
    {
        std::shuffle(m_cards.begin(), m_cards.end(), Random::mt);
        m_nextCardIndex = 0;
    }

    Card dealCard()
    {
        assert(m_nextCardIndex != 52 && "Deck::dealCard ran out of cards");
        return m_cards[m_nextCardIndex++];
    }

};

struct Player
{
    int playerScore{};
    int aceCount{};

    void addToScore(Card card)
    {
        playerScore += card.value();
        if (card.rank == Card::rank_ace)
            ++aceCount;
        consumeAces();
    }

    void consumeAces()
    {
        while (playerScore > Settings::bust && aceCount > 0)
        {
            playerScore -= 10;
            --aceCount;
        }
    }

};

enum winCondition
{
    win,
    lose,
    tie
};

winCondition blackjack()
{
    Player dealer;
    Player player;
    Deck deck;
    Card card;
    
    deck.shuffle();
    dealer.addToScore(deck.dealCard());
    player.addToScore(deck.dealCard());

    std::cout << "The dealer is showing: " << dealer.playerScore << '\n';
    std::cout << "You have score: " << player.playerScore << '\n';

    while (true)
    {
        char c;
        std::cout << "Press (h) to hit, (s) to stand: ";
        std::cin >> c;
        if (c == 'h')
        {
            Card card = deck.dealCard();
            player.addToScore(card);
            std::cout << "You flipped a " << card << ". You now have " << player.playerScore << ".\n";
            if (player.playerScore > Settings::bust)
            {
                std::cout << "You went bust.\n";
                return winCondition::lose;
            }
            continue;
        }
        else if (c == 's')
        {
            break;
        }
        else
        {
            std::cout << "Invalid input, try again.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    while (dealer.playerScore < Settings::stop)
    {
        Card card = deck.dealCard();
        dealer.addToScore(card);
        std::cout << "The dealer flips a " << card << ". They now have " << dealer.playerScore << ".\n";
        if (dealer.playerScore > Settings::bust)
        {
            std::cout << "The dealer went bust.\n";
            return winCondition::win;
        }
    }

    if (player.playerScore == dealer.playerScore)
        return winCondition::tie;

    return (player.playerScore > dealer.playerScore ? winCondition::win : winCondition::lose);
}

int main()
{
    switch(blackjack())
    {
        case winCondition::win:
            std::cout << "You win!\n";
            return 0;
        case winCondition::lose:
            std::cout << "You lose!\n";
            return 0;
        case winCondition::tie:
            std::cout << "You tied!\n";
            return 0;
    }
    return 0;
}