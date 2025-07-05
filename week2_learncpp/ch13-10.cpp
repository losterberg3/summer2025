#include <iostream>

struct Ads
{
    int numberOfAds;
    double percentage;
    double earnings;
};

Ads askForInfo()
{
    Ads ask{};
    std::cout << "How many ads were watched?\n";
    std::cin >> ask.numberOfAds;

    std::cout << "What percentage of users clicked on ads?\n";
    std::cin >> ask.percentage;

    std::cout << "Average earnings per clicked ad?\n";
    std::cin >> ask.earnings;
    return ask;
}

void print(const Ads& ads)
{
    std::cout << ads.numberOfAds << " ads were watched.\n";
    std::cout << ads.percentage << R"(% of users clicked on an ad)" << "\n";
    std::cout << ads.earnings << "$ is the average earnings per clicked ad.\n";
    std::cout << "I made " << ads.numberOfAds * ads.percentage * ads.earnings << "$ today.\n";
}

int main()
{
    print(askForInfo());
    return 0;
}


