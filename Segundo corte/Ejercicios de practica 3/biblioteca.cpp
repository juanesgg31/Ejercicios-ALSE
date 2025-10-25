#include <iostream>
#include <vector>
#include <string>
#include <limits>

class Libro
{
private:
    std::string titulo;
    std::string autor;
    std::string isbn;
    bool disponible;

public:
    Libro() : titulo(""), autor(""), isbn(""), disponible(true) {}
    Libro(const std::string &t, const std::string &a, const std::string &i, bool disp = true)
        : titulo(t), autor(a), isbn(i), disponible(disp) {}

    const std::string &obtenerTitulo() const { return titulo; }
    const std::string &obtenerAutor() const { return autor; }
    const std::string &obtenerISBN() const { return isbn; }
    bool estaDisponible() const { return disponible; }

    void cambiarTitulo(const std::string &t) { titulo = t; }
    void cambiarAutor(const std::string &a) { autor = a; }
    void cambiarISBN(const std::string &i) { isbn = i; }
    void marcarPrestado() { disponible = false; }
    void marcarDisponible() { disponible = true; }

    void mostrar() const
    {
        std::cout << "Titulo: " << titulo
                  << " | Autor: " << autor
                  << " | ISBN: " << isbn
                  << " | Estado: " << (disponible ? "Disponible" : "Prestado")
                  << '\n';
    }
};

class Biblioteca
{
private:
    std::vector<Libro> libros;

    int buscarIndicePorISBN(const std::string &isbn) const
    {
        for (size_t i = 0; i < libros.size(); ++i)
        {
            if (libros[i].obtenerISBN() == isbn)
                return static_cast<int>(i);
        }
        return -1;
    }

public:
    bool agregarLibro(const Libro &libro)
    {
        if (buscarIndicePorISBN(libro.obtenerISBN()) != -1)
            return false;
        libros.push_back(libro);
        return true;
    }

    bool eliminarLibroPorISBN(const std::string &isbn)
    {
        int idx = buscarIndicePorISBN(isbn);
        if (idx == -1)
            return false;
        libros.erase(libros.begin() + idx);
        return true;
    }

    bool prestarPorISBN(const std::string &isbn)
    {
        int idx = buscarIndicePorISBN(isbn);
        if (idx == -1)
            return false;
        if (!libros[idx].estaDisponible())
            return false;
        libros[idx].marcarPrestado();
        return true;
    }

    bool devolverPorISBN(const std::string &isbn)
    {
        int idx = buscarIndicePorISBN(isbn);
        if (idx == -1)
            return false;
        if (libros[idx].estaDisponible())
            return false;
        libros[idx].marcarDisponible();
        return true;
    }

    std::vector<Libro> buscarPorTitulo(const std::string &parte) const
    {
        std::vector<Libro> resultado;
        for (const auto &l : libros)
        {
            if (l.obtenerTitulo().find(parte) != std::string::npos)
            {
                resultado.push_back(l);
            }
        }
        return resultado;
    }

    std::vector<Libro> buscarPorAutor(const std::string &parte) const
    {
        std::vector<Libro> resultado;
        for (const auto &l : libros)
        {
            if (l.obtenerAutor().find(parte) != std::string::npos)
            {
                resultado.push_back(l);
            }
        }
        return resultado;
    }

    void mostrarLibros() const
    {
        if (libros.empty())
        {
            std::cout << "No hay libros en la biblioteca.\n";
            return;
        }
        for (const auto &l : libros)
            l.mostrar();
    }

    void mostrarDisponibles() const
    {
        bool alguno = false;
        for (const auto &l : libros)
        {
            if (l.estaDisponible())
            {
                l.mostrar();
                alguno = true;
            }
        }
        if (!alguno)
            std::cout << "No hay libros disponibles.\n";
    }
};

std::string leerLinea(const std::string &mensaje)
{
    std::cout << mensaje;
    std::string s;
    std::getline(std::cin, s);
    return s;
}

void mostrarMenu()
{
    std::cout << "\n===== MENU BIBLIOTECA =====\n"
              << "1) Agregar libro\n"
              << "2) Eliminar libro por ISBN\n"
              << "3) Buscar por titulo\n"
              << "4) Buscar por autor\n"
              << "5) Mostrar todos los libros\n"
              << "6) Mostrar SOLO disponibles\n"
              << "7) Prestar libro (por ISBN)\n"
              << "8) Devolver libro (por ISBN)\n"
              << "0) Salir\n"
              << "Elige una opcion: ";
}

int main()
{
    Biblioteca biblio;
    int opcion = -1;

    auto limpiarEntrada = []()
    {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    };

    while (true)
    {
        mostrarMenu();
        if (!(std::cin >> opcion))
        {
            std::cin.clear();
            limpiarEntrada();
            std::cout << "Entrada no valida.\n";
            continue;
        }
        limpiarEntrada();

        if (opcion == 0)
        {
            std::cout << "Hasta luego!\n";
            break;
        }

        switch (opcion)
        {
        case 1:
        {
            std::string t = leerLinea("Titulo: ");
            std::string a = leerLinea("Autor: ");
            std::string i = leerLinea("ISBN: ");
            if (biblio.agregarLibro(Libro(t, a, i, true)))
                std::cout << "Libro agregado.\n";
            else
                std::cout << "No se pudo agregar (ISBN repetido).\n";
            break;
        }
        case 2:
        {
            std::string isbn = leerLinea("ISBN a eliminar: ");
            if (biblio.eliminarLibroPorISBN(isbn))
                std::cout << "Libro eliminado.\n";
            else
                std::cout << "No existe un libro con ese ISBN.\n";
            break;
        }
        case 3:
        {
            std::string parte = leerLinea("Escribe parte del titulo: ");
            auto v = biblio.buscarPorTitulo(parte);
            if (v.empty())
                std::cout << "No se encontraron coincidencias.\n";
            for (const auto &l : v)
                l.mostrar();
            break;
        }
        case 4:
        {
            std::string parte = leerLinea("Escribe parte del autor: ");
            auto v = biblio.buscarPorAutor(parte);
            if (v.empty())
                std::cout << "No se encontraron coincidencias.\n";
            for (const auto &l : v)
                l.mostrar();
            break;
        }
        case 5:
        {
            biblio.mostrarLibros();
            break;
        }
        case 6:
        {
            biblio.mostrarDisponibles();
            break;
        }
        case 7:
        {
            std::string isbn = leerLinea("ISBN a prestar: ");
            if (biblio.prestarPorISBN(isbn))
                std::cout << "Prestamo exitoso.\n";
            else
                std::cout << "No se pudo prestar.\n";
            break;
        }
        case 8:
        {
            std::string isbn = leerLinea("ISBN a devolver: ");
            if (biblio.devolverPorISBN(isbn))
                std::cout << "Devolucion exitosa.\n";
            else
                std::cout << "No se pudo devolver.\n";
            break;
        }
        default:
            std::cout << "Opcion no valida.\n";
        }
    }

    return 0;
}
