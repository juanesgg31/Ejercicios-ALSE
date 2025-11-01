class Solution
{
public:
    bool isPalindrome(int x)
    {
        if (x < 0)
            return false;
        if (x != 0 && x % 10 == 0)
            return false;
        long invertida = 0;
        while (x > invertida)
        {
            invertida = invertida * 10 + x % 10;
            x /= 10;
        }
        return x == invertida || x == invertida / 10;
    }
};
