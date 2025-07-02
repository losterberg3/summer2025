class Solution {
public:
    bool isPalindrome(int x) {
        long y = x;
        long z = 0;
        if (x < 0)
            return false;
        while (x > 0)
        {
            z *= 10;
            z += (x%10);
            x /= 10;
        }
        return (y==z);
    }
};