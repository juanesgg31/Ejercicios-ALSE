#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int titleToNumber(string columnTitle)
    {
        long long result = 0;
        for (char c : columnTitle)
        {
            int value = (c - 'A') + 1;
            result = result * 26 + value;
        }
        return (int)result;
    }
};

int main()
{
    Solution s;
    string columnTitle;
    cout << "Ingrese el titulo de la columna (por ejemplo AB): ";
    cin >> columnTitle;

    cout << "El numero de columna correspondiente es: "
         << s.titleToNumber(columnTitle) << endl;

    return 0;
}