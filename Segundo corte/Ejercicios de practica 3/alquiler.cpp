#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <memory>

class Vehiculo
{
protected:
    std::string marca;
    std::string modelo;
    std::string placa;
    bool disponible;

public:
    Vehiculo(const std::string &m, const std::string &mo, const std::string &p)
        : marca(m), modelo(mo), placa(p), disponible(true) {}
    virtual ~Vehiculo() = default;
    const std::string &obtenerPlaca() const { return placa; }
    bool estaDisponible() const { return disponible; }
    void marcarAlquilado() { disponible = false; }
    void marcarDisponible() { disponible = true; }
    virtual void mostrarInformacion() const
    {
        std::cout << "Marca: " << marca
                  << " | Modelo: " << modelo
                  << " | Placa: " << placa
                  << " | Estado: " << (disponible ? "Disponible" : "Alquilado");
    }
};

class Auto : public Vehiculo
{
    int capacidadPasajeros;

public:
    Auto(const std::string &m, const std::string &mo, const std::string &p, int cap)
        : Vehiculo(m, mo, p), capacidadPasajeros(cap) {}
    void mostrarInformacion() const override
    {
        Vehiculo::mostrarInformacion();
        std::cout << " | Capacidad: " << capacidadPasajeros << " pasajeros\n";
    }
};

class Bicicleta : public Vehiculo
{
    std::string tipo;

public:
    Bicicleta(const std::string &m, const std::string &mo, const std::string &p, const std::string &t)
        : Vehiculo(m, mo, p), tipo(t) {}
    void mostrarInformacion() const override
    {
        Vehiculo::mostrarInformacion();
        std::cout << " | Tipo: " << tipo << '\n';
    }
};

class SistemaAlquiler
{
    std::vector<std::unique_ptr<Vehiculo>> vehiculos;

    int buscarIndicePorPlaca(const std::string &p) const
    {
        for (size_t i = 0; i < vehiculos.size(); ++i)
            if (vehiculos[i]->obtenerPlaca() == p)
                return static_cast<int>(i);
        return -1;
    }

public:
    bool registrarAuto(const std::string &marca, const std::string &modelo, const std::string &placa, int capacidad)
    {
        if (buscarIndicePorPlaca(placa) != -1)
            return false;
        vehiculos.push_back(std::make_unique<Auto>(marca, modelo, placa, capacidad));
        return true;
    }

    bool registrarBicicleta(const std::string &marca, const std::string &modelo, const std::string &placa, const std::string &tipo)
    {
        if (buscarIndicePorPlaca(placa) != -1)
            return false;
        vehiculos.push_back(std::make_unique<Bicicleta>(marca, modelo, placa, tipo));
        return true;
    }

    bool alquilarPorPlaca(const std::string &placa)
    {
        int idx = buscarIndicePorPlaca(placa);
        if (idx == -1)
            return false;
        if (!vehiculos[idx]->estaDisponible())
            return false;
        vehiculos[idx]->marcarAlquilado();
        return true;
    }

    bool devolverPorPlaca(const std::string &placa)
    {
        int idx = buscarIndicePorPlaca(placa);
        if (idx == -1)
            return false;
        if (vehiculos[idx]->estaDisponible())
            return false;
        vehiculos[idx]->marcarDisponible();
        return true;
    }

    void mostrarDisponibles() const
    {
        bool alguno = false;
        for (const auto &v : vehiculos)
        {
            if (v->estaDisponible())
            {
                v->mostrarInformacion();
                alguno = true;
            }
        }
        if (!alguno)
            std::cout << "No hay vehiculos disponibles\n";
    }

    void mostrarTodos() const
    {
        if (vehiculos.empty())
        {
            std::cout << "No hay vehiculos registrados\n";
            return;
        }
        for (const auto &v : vehiculos)
            v->mostrarInformacion();
    }
};

std::string leerLinea(const std::string &mensaje)
{
    std::cout << mensaje;
    std::string s;
    std::getline(std::cin, s);
    return s;
}

int leerEntero(const std::string &mensaje)
{
    while (true)
    {
        std::string s = leerLinea(mensaje);
        try
        {
            size_t pos = 0;
            int x = std::stoi(s, &pos);
            if (pos == s.size())
                return x;
        }
        catch (...)
        {
        }
        std::cout << "Valor no valido\n";
    }
}

void mostrarMenu()
{
    std::cout << "\n===== MENU ALQUILER =====\n"
              << "1) Registrar auto\n"
              << "2) Registrar bicicleta\n"
              << "3) Alquilar por placa\n"
              << "4) Devolver por placa\n"
              << "5) Mostrar vehiculos disponibles\n"
              << "6) Mostrar todos los vehiculos\n"
              << "0) Salir\n"
              << "Elige una opcion: ";
}

int main()
{
    SistemaAlquiler sistema;
    int opcion = -1;

    while (true)
    {
        mostrarMenu();
        if (!(std::cin >> opcion))
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Entrada no valida\n";
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (opcion == 0)
        {
            std::cout << "Hasta luego\n";
            break;
        }

        if (opcion == 1)
        {
            std::string marca = leerLinea("Marca: ");
            std::string modelo = leerLinea("Modelo: ");
            std::string placa = leerLinea("Placa: ");
            int capacidad = leerEntero("Capacidad de pasajeros: ");
            if (sistema.registrarAuto(marca, modelo, placa, capacidad))
                std::cout << "Auto registrado\n";
            else
                std::cout << "No se pudo registrar (placa repetida)\n";
        }
        else if (opcion == 2)
        {
            std::string marca = leerLinea("Marca: ");
            std::string modelo = leerLinea("Modelo: ");
            std::string placa = leerLinea("Placa: ");
            std::string tipo = leerLinea("Tipo de bicicleta (montana/urbana/otra): ");
            if (sistema.registrarBicicleta(marca, modelo, placa, tipo))
                std::cout << "Bicicleta registrada\n";
            else
                std::cout << "No se pudo registrar (placa repetida)\n";
        }
        else if (opcion == 3)
        {
            std::string placa = leerLinea("Placa a alquilar: ");
            if (sistema.alquilarPorPlaca(placa))
                std::cout << "Alquiler exitoso\n";
            else
                std::cout << "No se pudo alquilar\n";
        }
        else if (opcion == 4)
        {
            std::string placa = leerLinea("Placa a devolver: ");
            if (sistema.devolverPorPlaca(placa))
                std::cout << "Devolucion exitosa\n";
            else
                std::cout << "No se pudo devolver\n";
        }
        else if (opcion == 5)
        {
            sistema.mostrarDisponibles();
        }
        else if (opcion == 6)
        {
            sistema.mostrarTodos();
        }
        else
        {
            std::cout << "Opcion no valida\n";
        }
    }
    return 0;
}