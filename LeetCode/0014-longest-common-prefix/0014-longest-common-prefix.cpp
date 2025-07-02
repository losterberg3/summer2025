class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        string pre = {""};
        string s2;
        string s1 {strs[0]};
        int i = 0;
        int j;
        while(i < (strs.size()))
        {
            s2 = strs[i];
            i++;
            j=0;
            while (j<(s1.length() < s2.length() ? s1.length() : s2.length()))
            {
                if (s1[j] == s2[j]) 
                {
                    pre += s1[j];
                    ++j;
                } 
                else 
                {
                    break;
                }
            }
            s1 = pre;
            if (pre.length() == 0)
            {
                break;
            }
            pre = {""}; 
        }
        return s1;  
    }
};