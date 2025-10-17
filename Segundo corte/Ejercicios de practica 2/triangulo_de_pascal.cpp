#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    vector<vector<int>> generate(int numRows)
    {
        vector<vector<int>> triangle;

        for (int i = 0; i < numRows; ++i)
        {
            vector<int> row(i + 1, 1);
            for (int j = 1; j < i; ++j)
            {
                row[j] = triangle[i - 1][j - 1] + triangle[i - 1][j];
            }
            triangle.push_back(row);
        }
        return triangle;
    }
};

int main()
{
    Solution s;
    int numRows;
    cout << "Ingrese el numero de filas del triangulo de Pascal: ";
    cin >> numRows;

    vector<vector<int>> result = s.generate(numRows);

    cout << "\nTriangulo de Pascal con " << numRows << " filas:\n";
    for (auto &fila : result)
    {
        for (int num : fila)
            cout << num << " ";
        cout << "\n";
    }

    return 0;
}