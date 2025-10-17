#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    vector<vector<int>> generate(int num_filas)
    {
        vector<vector<int>> triangulo;

        for (int i = 0; i < num_filas; ++i)
        {
            vector<int> fila(i + 1, 1);
            for (int j = 1; j < i; ++j)
            {
                fila[j] = triangulo[i - 1][j - 1] + triangulo[i - 1][j];
            }
            triangulo.push_back(fila);
        }
        return triangulo;
    }
};

int main()
{
    Solution sol;
    int num_filas;
    cout << "Ingrese el numero de filas del triangulo de Pascal: ";
    cin >> num_filas;

    vector<vector<int>> res = sol.generate(num_filas);

    cout << "\nTriangulo de Pascal con " << num_filas << " filas:\n";
    for (auto &fila : res)
    {
        for (int v : fila)
            cout << v << " ";
        cout << "\n";
    }
    return 0;
}
