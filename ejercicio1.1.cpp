#include <iostream>
#include <cmath>

int main()
{
    int n;
    std::cout << "Calculadora de Costo Total en una Tienda de Abastos\n";
    std::cout << "Ingrese la cantidad de productos distintos: ";
    std::cin >> n;

    double subtotal = 0.0;

    for (int i = 0; i < n; i++)
    {
        double precio;
        int cantidad;

        std::cout << "Precio del producto " << i + 1 << ": ";
        std::cin >> precio;

        std::cout << "Cantidad del producto " << i + 1 << ": ";
        std::cin >> cantidad;

        subtotal += precio * cantidad;
    }

    double impuesto = subtotal * 0.08;
    double total = subtotal + impuesto;

    double descuento = 0.0;
    if (total > 100.0)
    {
        descuento = total * 0.10;
        total -= descuento;
    }

    subtotal = std::round(subtotal * 100.0) / 100.0;
    impuesto = std::round(impuesto * 100.0) / 100.0;
    descuento = std::round(descuento * 100.0) / 100.0;
    total = std::round(total * 100.0) / 100.0;

    std::cout << "Subtotal: $" << subtotal << "\n";
    std::cout << "Impuesto (8%): $" << impuesto << "\n";
    if (descuento > 0.0)
    {
        std::cout << "Descuento (10%): -$" << descuento << "\n";
    }
    std::cout << "Costo total: $" << total << std::endl;

    return 0;
}
