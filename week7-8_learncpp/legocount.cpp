#include <iostream>

int main()
{
    int onebyonebp {0};
    int onebyonepp {0};
    int twobyonepp {0};
    int threebyonepp {0};
    int fourbyonepp {0};
    int sixbyonepp {0};
    int input;

    while (true)
    {
        std::cout << "Place your numbers of each lego: ";
        std::cin >> input;

        switch(input)
        {
            case 0 : 
                ++onebyonebp;
            case 1 : 
                ++onebyonepp;
            case 2 : 
                ++twobyonepp;
            case 3 : 
                ++threebyonepp;
            case 4 : 
                ++fourbyonepp;
            case 5 : 
                ++sixbyonepp;
            case 9:  
                break; 
            default :
                continue;   
        }

        if (input == 9)
        {
            break;
        }
    }

    std::cout << "Your lego quantities: " << onebyonebp << ' ' << onebyonepp << ' ' << twobyonepp << ' ' << threebyonepp << ' ' << fourbyonepp << ' ' << sixbyonepp << '\n';
    
}