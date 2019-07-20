class Solution {
public:
    int myAtoi(string str) 
    {
        int result = 0, sign = 1;
        int i = 0;
        for(; str[i] == ' '; i++);
        if(str[i] == '+')
        {
            sign = 1;
            i++;
        }
        else if(str[i] == '-')
        {
            sign = -1;
            i++;
        }
        for(; str[i] >= '0' && str[i] <= '9'; i++)
        {
            if(result > INT_MAX / 10 || (result == INT_MAX / 10 && str[i] > '7'))
            {
                return (sign == -1)? INT_MIN: INT_MAX;
            }
            result = result * 10 + (str[i] - '0');
        }
        return result * sign;
    }
};
