#include <iostream>

int main()
{
    int num[5];
    int suma = 0;

    std::cout << "Digite 5 números enteros:" << std::endl;

    for (int i = 0; i < 5; i++)
    {
        std::cout << "Número " << (i + 1) << ": ";
        std::cin >> num[i];
        suma += num[i];
    }

    std::cout << "La suma de los números ingresados es: " << suma << std::endl;

    return 0;
}