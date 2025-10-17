#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int maxProfit(vector<int> &precios)
    {
        int min_precio = INT_MAX;
        int mejor_gan = 0;

        for (int p : precios)
        {
            if (p < min_precio)
            {
                min_precio = p;
            }
            else if (p - min_precio > mejor_gan)
            {
                mejor_gan = p - min_precio;
            }
        }
        return mejor_gan;
    }
};

int main()
{
    Solution sol;
    int n;
    cout << "Ingrese la cantidad de dias: ";
    cin >> n;

    vector<int> precios(n);
    cout << "Ingrese los precios por dia:\n";
    for (int i = 0; i < n; ++i)
        cin >> precios[i];

    cout << "\nLa maxima ganancia posible es: "
         << sol.maxProfit(precios) << endl;
    return 0;
}