#include <iostream>

int main()
{
    int a, b;

    std::cout << "Calculo del Maximo Comun Divisor (MCD)\n";
    std::cout << "Ingrese el primer numero: ";
    std::cin >> a;
    std::cout << "Ingrese el segundo numero: ";
    std::cin >> b;

    while (b != 0)
    {
        int temp = b;
        b = a % b;
        a = temp;
    }

    std::cout << "El Maximo Comun Divisor de los numeros ingresados es: " << a << std::endl;
    return 0;
}
