class Solution {
public:
    int maxProfit(vector<int>& prices) 
    {
        int max = 0;
        int buy = prices[0];
        int length = prices.size();
        for (int i=1; i<length; ++i)
        {
            if (prices[i] < buy)
            {
                buy = prices[i];
            } 
            else if (prices[i] - buy > max)
            {
                max = prices[i] - buy;
            }
        }
        return max;
    }
};