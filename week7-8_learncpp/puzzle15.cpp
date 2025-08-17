#include <iostream>
#include "headers/Random.h"
#include <vector>
#include <array>


constexpr int g_consoleLines{ 25 };

class Direction
{
    public:

    enum Type
    {
        up,
        down,
        left,
        right,
        maxDirections
    };

    private:

    Type m_dir{};

    public:

    Direction(Type t)
        : m_dir{t}
    {}

    Type getType()
    {
        return m_dir;
    }

    static Direction randomDirection()
    {
        return Direction {static_cast<Type>(Random::get(0, Type::maxDirections - 1))};
    }


    Direction operator-() const
    {
        switch(m_dir)
        {
            case up:
                return down;
            case down:
                return up;
            case left:
                return right;
            case right:
                return left;
            default:    
                break;
        }

        assert(0 && "Unsupported direction was passed!");
        return Direction{ up };
    }

    friend std::ostream& operator<<(std::ostream& out, const Direction& d)
    {
        switch(d.m_dir)
        {
            case up:
                out << "up";
                return out;
            case down:
                out << "down";
                return out;
            case left:
                out << "left";
                return out;
            case right:
                out << "right";
                return out;
            default:                
                break;
        }
        
        assert(0 && "Unsupported direction was passed!");
        return (out << "unknown direction");
    }
};

struct Point
{
    int m_x {};
    int m_y {};

    Point getAdjacentPoint(Direction dir) const
    {
        switch(dir.getType())
        {
            case Direction::up:
                return Point{m_x, m_y - 1};
            case Direction::down:
                return Point{m_x, m_y + 1};
            case Direction::left:
                return Point{m_x - 1, m_y};
            case Direction::right:
                return Point{m_x + 1, m_y};
            default:                
                break;
        }

        assert(0 && "Unsupported direction was passed!");
        return *this;
    }

    friend bool operator== (Point p1, Point p2)
    {
        return (p1.m_x == p2.m_x) && (p1.m_y == p2.m_y);
    }

    friend bool operator!= (Point p1, Point p2)
    {
        return !(p1==p2);
    }
};

namespace UserInput
{
    bool isValidCommand(char ch)
    {
        return ch == 'w'
            || ch == 'a'
            || ch == 's'
            || ch == 'd'
            || ch == 'q';
    }

    void ignoreLine()
    {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    char getCharacter()
    {
        char operation{};
        std::cin >> operation;
        ignoreLine(); // remove any extraneous input
        return operation;
    }

    char getCommandFromUser()
    {
        char ch{};
        while (!isValidCommand(ch))
            ch = getCharacter();

        return ch;
    }

    Direction charConvert(char ch)
    {
        switch(ch)
        {
            case 'w':
                return Direction{Direction::up};
            case 's':
                return Direction{Direction::down};
            case 'a':
                return Direction{Direction::left};
            case 'd':
                return Direction{Direction::right};
        }

        assert(0 && "Unsupported direction was passed!");
        return Direction{ Direction::up };
    }
};

class Tile
{
    private:

    int m_tileval{ 0 };

    public:

    Tile() = default;

    Tile(int number)
        : m_tileval{number}
    {}

    int getNum() const
    {
        return m_tileval;
    }

    bool isEmpty()
    {
        return m_tileval == 0;
    }

    friend bool operator!=(Tile t1, Tile t2)
    {
        return t1.m_tileval != t2.m_tileval;
    }
};

std::ostream& operator<< (std::ostream& out, Tile tile)
{
    if (tile.getNum() > 9)
        out << " " << tile.getNum() << " ";
    else if (tile.getNum() > 0)
        out << "  " << tile.getNum() << " ";
    else if (tile.getNum() == 0)
        out << "    ";
    return out;
}

class Board
{
    private:

    static constexpr int m_size {4};

    Tile m_board[m_size][m_size]
    {
        {{1}, {2}, {3}, {4}}, {{5}, {6}, {7}, {8}}, {{9}, {10}, {11}, {12}}, {{13}, {14}, {15}, {0}}
    };

    public:

    Board() = default;

    Point findZero()
    {
        for (int i = 0; i < m_size; ++i)
        {
            for (int j = 0; j < m_size; ++j)
            {
                if (m_board[i][j].isEmpty())
                {
                    return Point{j, i};
                }
            }
        }

        return Point{0, 0};
    }



    void moveTile(Direction d)
    {
        Point point = findZero();
        Point adjacent = point.getAdjacentPoint(-d);

        if (adjacent.m_x < 0 || (adjacent.m_x > m_size - 1) || adjacent.m_y < 0 || (adjacent.m_y > m_size - 1))
        {}
        else
        {
            m_board[point.m_y][point.m_x] = m_board[adjacent.m_y][adjacent.m_x];
            m_board[adjacent.m_y][adjacent.m_x] = Tile();
        }
    }

    void randomizeBoard()
    {
        for (int i = 0; i < 1; ++i)
        {
            moveTile(Direction::randomDirection());
        }
    }

    friend bool operator== (const Board& b1, const Board& b2)
    {
        for (int i = 0; i < m_size; ++i)
        {
            for (int j = 0; j < m_size; ++j)
            {
                if (b1.m_board[i][j].getNum() != b2.m_board[i][j].getNum())
                {
                    return false;
                }
            }
        }
        return true;
    }

    bool playerWon() const
    {
        static Board s_solved{};  // generate a solved board
        return s_solved == *this; // player wins if current board == solved board
    }

    friend std::ostream& operator<< (std::ostream& out, Board board)
    {
        for (int i = 0; i < g_consoleLines; ++i)
        {
            std::cout << '\n';
        }
        for (int i = 0; i < board.m_size; ++i)
        {
            for (int j = 0; j < board.m_size; ++j)
            {
                out << board.m_board[i][j];
            }
            out << '\n';
        }

        return out;
    }
};


int main()
{
    Board board{};
    board.randomizeBoard();
    std::cout << board;


    while (true)
    {
        char ch{ UserInput::getCommandFromUser() };

        if (ch == 'q')
        {
            std::cout << "\n\nBye!\n\n";
            return 0;
        }

        Direction dir{ UserInput::charConvert(ch) };

        board.moveTile(dir);

        std::cout << board;

        if (board.playerWon())
            break;
    }

    std::cout << "You won!\n";

    return 0;
}
