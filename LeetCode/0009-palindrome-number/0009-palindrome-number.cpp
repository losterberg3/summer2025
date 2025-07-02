#include <string>
#include <algorithm>

class Solution {
public:
    bool isPalindrome(int x) {
        std::string y = std::to_string(x);
        std::string z = y;
        std::reverse(y.begin(), y.end());        
        return y == z;
    }
};