#include <iostream>
#include <cmath>
using namespace std;

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
    cout << "¿Desea ingresar los puntos manualmente? (s/n): ";
    cin >> respuesta;

    if (respuesta == 's')
    {
        for (int i = 0; i < n; ++i)
        {
            cout << "Ingrese las coordenadas del punto " << i + 1 << " (x, y): ";
            char lp, comma, rp;
            cin >> lp >> puntos[i].x >> comma >> puntos[i].y >> rp;
        }
    }
    else
    {
        cout << "Usando puntos predeterminados...\n";
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
    cout << "El punto de mayor magnitud es: ("
         << puntos[indiceMayorMagnitud].x << ", "
         << puntos[indiceMayorMagnitud].y << ")\n";
    cout << "La mayor magnitud del arreglo es: " << mayorMagnitud << endl;
}

int main()
{
    int n;
    cout << "Ingrese el número de puntos (mínimo 2): ";
    cin >> n;
    if (n < 2)
    {
        cout << "Se necesitan al menos 2 puntos para determinar la mayor magnitud.\n";
        return 1;
    }
    Point puntos[n];
    leerPuntos(puntos, n);
    int indiceMayorMagnitud;
    double mayorMagnitud = calcularMayorMagnitud(puntos, n, indiceMayorMagnitud);
    mostrarResultado(puntos, indiceMayorMagnitud, mayorMagnitud);
    return 0;
}
