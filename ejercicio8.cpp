#include <iostream>
#include <cmath>

int main()
{
    double A, P, r, t;
    int n;

    std::cout << "Ingrese el monto inicial: ";
    std::cin >> P;

    std::cout << "Ingrese la tasa de interes anual (%): ";
    std::cin >> r;

    std::cout << "Ingrese la cantidad de años: ";
    std::cin >> t;

    std::cout << "Ingrese las veces que capitaliza al año (n): ";
    std::cin >> n;

    r = r / 100.0;
    A = P * std::pow(1.0 + (r / n), n * t);

    std::cout << "El monto final es: " << A << std::endl;
    return 0;
}
