#include <iostream>
#include <cmath>

struct Point
{
    double x, y;
};

double calcularMagnitud(Point p1)
{
    return std::sqrt(p1.x * p1.x + p1.y * p1.y);
}

void leerPuntos(Point puntos[], int n)
{
    char respuesta;
    std::cout << "¿Desea ingresar los puntos manualmente? (s/n): ";
    std::cin >> respuesta;

    if (respuesta == 's' || respuesta == 'S')
    {
        for (int i = 0; i < n; ++i)
        {
            std::cout << "Ingrese las coordenadas del punto " << i + 1 << " (x, y): ";
            char lp, comma, rp;
            std::cin >> lp >> puntos[i].x >> comma >> puntos[i].y >> rp; // Profe entendi que se da en este formato el vector (x, y)
        }
    }
    else
    {
        std::cout << "Usando puntos predeterminados...\n";
        Point pred[] = {{0, 0}, {3, 4}, {6, 8}, {9, 12}};
        for (int i = 0; i < n; ++i)
            puntos[i] = (i < 4) ? pred[i] : Point{0, 0};
    }
}

double calcularMayorMagnitud(Point puntos[], int n, int &indiceMayorMagnitud)
{
    indiceMayorMagnitud = 0;
    double mayorMagnitud = calcularMagnitud(puntos[0]);
    for (int i = 1; i < n; ++i)
    {
        double magnitud = calcularMagnitud(puntos[i]);
        if (magnitud > mayorMagnitud)
        {
            mayorMagnitud = magnitud;
            indiceMayorMagnitud = i;
        }
    }
    return mayorMagnitud;
}

void mostrarResultado(Point puntos[], int indiceMayorMagnitud, double mayorMagnitud)
{
    std::cout << "El punto de mayor magnitud es: ("
              << puntos[indiceMayorMagnitud].x << ", "
              << puntos[indiceMayorMagnitud].y << ")\n";
    std::cout << "La mayor magnitud del arreglo es: " << mayorMagnitud << std::endl;
}

int main()
{
    int n;

    std::cout << "Ingrese el número de puntos (mínimo 2): ";
    std::cin >> n;

    if (n < 2)
    {
        std::cout << "Se necesitan al menos 2 puntos para determinar la mayor magnitud.\n";
        return 1;
    }

    Point puntos[n];
    leerPuntos(puntos, n);

    int indiceMayorMagnitud;
    double mayorMagnitud = calcularMayorMagnitud(puntos, n, indiceMayorMagnitud);

    mostrarResultado(puntos, indiceMayorMagnitud, mayorMagnitud);
    return 0;
}
