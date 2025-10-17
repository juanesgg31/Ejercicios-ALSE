#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int titleToNumber(string titulo_col)
    {
        long long acum = 0;
        for (char c : titulo_col)
        {
            int val = (c - 'A') + 1;
            acum = acum * 26 + val;
        }
        return (int)acum;
    }
};

int main()
{
    Solution sol;
    string titulo_col;
    cout << "Ingrese el titulo de la columna (por ejemplo AB): ";
    cin >> titulo_col;

    cout << "El numero de columna correspondiente es: "
         << sol.titleToNumber(titulo_col) << endl;
    return 0;
}