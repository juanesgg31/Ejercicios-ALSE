#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int maxProfit(vector<int> &prices)
    {
        int minPrice = INT_MAX;
        int maxProfit = 0;

        for (int price : prices)
        {
            if (price < minPrice)
            {
                minPrice = price;
            }
            else if (price - minPrice > maxProfit)
            {
                maxProfit = price - minPrice;
            }
        }
        return maxProfit;
    }
};

int main()
{
    Solution s;
    int n;
    cout << "Ingrese la cantidad de dias: ";
    cin >> n;

    vector<int> prices(n);
    cout << "Ingrese los precios por dia:\n";
    for (int i = 0; i < n; ++i)
        cin >> prices[i];

    cout << "\nLa maxima ganancia posible es: "
         << s.maxProfit(prices) << endl;

    return 0;
}