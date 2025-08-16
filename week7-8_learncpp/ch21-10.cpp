#include <iostream>
#include <string>
#include <string_view>

class MyString
{
    private: 

    std::string m_s{};

    public:

    MyString(std::string s) 
        : m_s{s}
    {}

    std::string_view operator()(int index, int length)
    {
        return std::string_view{m_s}.substr(index, length);
    }

    friend std::ostream& operator<< (std::ostream& out, const MyString& s);
};


std::ostream& operator<< (std::ostream& out, const MyString& s)
{
    out << s.m_s;

    return out;
}



int main()
{
    MyString s { "Hello, world!" };
    std::cout << s(7, 5) << '\n'; // start at index 7 and return 5 characters

    return 0;
}