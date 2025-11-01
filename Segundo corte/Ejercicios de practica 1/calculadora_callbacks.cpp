#include <iostream>
#include <string>
#include <unordered_map>
#include <functional>

int main(int argc, char *argv[])
{
    using namespace std;

    if (argc != 4)
    {
        cout << "Uso: " << argv[0] << " <operando1> <operador> <operando2>\n";
        return 1;
    }

    string texto1 = argv[1];
    string operador = argv[2];
    string texto2 = argv[3];

    size_t p1 = 0, p2 = 0;
    double operando1, operando2;
    try
    {
        operando1 = stod(texto1, &p1);
        operando2 = stod(texto2, &p2);
        if (p1 != texto1.size() || p2 != texto2.size())
            throw invalid_argument("x");
    }
    catch (...)
    {
        cout << "Error: operandos invalidos. Use numeros (se permiten decimales).\n";
        return 1;
    }

    unordered_map<string, function<double(double, double)>> op;
    op["+"] = [](double a, double b)
    { return a + b; };
    op["-"] = [](double a, double b)
    { return a - b; };
    op["*"] = [](double a, double b)
    { return a * b; };
    op["x"] = op["*"];
    op["X"] = op["*"];
    op["/"] = [](double a, double b)
    { return a / b; };

    if (!op.count(operador))
    {
        cout << "Error: operador invalido. Use +, -, *, x, X o /.\n";
        return 1;
    }
    if ((operador == "/") && operando2 == 0.0)
    {
        cout << "Error: division por cero.\n";
        return 1;
    }

    double resultado = op[operador](operando1, operando2);
    cout << "Resultado: " << resultado << "\n";
    return 0;
}
