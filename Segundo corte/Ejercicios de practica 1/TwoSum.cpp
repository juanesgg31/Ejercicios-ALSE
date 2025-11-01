#include <vector>
#include <unordered_map>
using namespace std;

class Solution
{
public:
    vector<int> twoSum(vector<int> &numeros, int objetivo)
    {
        unordered_map<int, int> indice;
        for (int i = 0; i < (int)numeros.size(); ++i)
        {
            int falta = objetivo - numeros[i];
            auto it = indice.find(falta);
            if (it != indice.end())
                return {it->second, i};
            indice[numeros[i]] = i;
        }
        return {};
    }
};
