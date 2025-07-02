class Solution {
public:
    int romanToInt(string s) {
        int answer{};
        for (int i = s.length()-1; i>=0; --i)
        {
            switch(s[i])
            {
                case('I'):
                    answer+=1;
                    break;
                case('V'):
                    answer+=5;
                    if (i!=0 && s[i-1] == 'I')
                    {
                        answer-=1;
                        --i;
                    }
                    break;
                case('X'):
                    answer+=10;
                    if (i!=0 && s[i-1] == 'I')
                    {
                        answer-=1;
                        --i;
                    }
                    break;
                case('L'):
                    answer+=50;
                    if (i!=0 && s[i-1] == 'X')
                    {
                        answer-=10;
                        --i;
                    }
                    break;
                case('C'):
                    answer+=100;
                    if (i!=0 && s[i-1] == 'X')
                    {
                        answer-=10;
                        --i;
                    }
                    break;
                case('D'):
                    answer+=500;
                    if (i!=0 && s[i-1] == 'C')
                    {
                        answer-=100;
                        --i;
                    }
                    break;
                case('M'):
                    answer+=1000;
                    if (i!=0 && s[i-1] == 'C')
                    {
                        answer-=100;
                        --i;
                    }
                    break;
            }
        }
        return answer;
    }
};