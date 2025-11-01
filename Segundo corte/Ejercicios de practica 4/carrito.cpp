#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>
using namespace std;

struct Producto
{
    int id;
    string nombre;
    double precio;
    int stock;
};

struct ItemCarrito
{
    int id_prod;
    string nombre;
    double precio;
    int cantidad;
    double subtotal() const { return precio * cantidad; }
};

struct Compra
{
    vector<ItemCarrito> items;
    double total = 0.0;
};

class Usuario
{
    string nombre;
    vector<Compra> historial;

public:
    Usuario(string n) : nombre(n) {}
    void agregar_compra(const Compra &c) { historial.push_back(c); }

    void ver_historial() const
    {
        if (historial.empty())
        {
            cout << "\nHistorial vacío.\n";
            return;
        }
        cout << fixed << setprecision(2);
        cout << "\n===== HISTORIAL DE COMPRAS =====\n";
        for (size_t k = 0; k < historial.size(); ++k)
        {
            cout << "\nCompra #" << (k + 1) << "\n";
            for (auto &it : historial[k].items)
            {
                cout << " - " << it.nombre << " x" << it.cantidad
                     << "  $" << it.precio << "  Subtotal: $" << it.subtotal() << "\n";
            }
            cout << "TOTAL: $" << historial[k].total << "\n";
        }
    }
};

class CarritoCompras
{
    vector<ItemCarrito> items;

public:
    int cantidad_en_carrito(int id_prod) const
    {
        for (auto &it : items)
            if (it.id_prod == id_prod)
                return it.cantidad;
        return 0;
    }

    void ver_carrito() const
    {
        cout << "\n===== CARRITO =====\n";
        if (items.empty())
        {
            cout << "Carrito vacío.\n";
            return;
        }
        cout << fixed << setprecision(2);
        for (auto &it : items)
        {
            cout << it.nombre << " (x" << it.cantidad << ")  $"
                 << it.precio << "  Subtotal: $" << it.subtotal() << "\n";
        }
        cout << "TOTAL: $" << total() << "\n";
    }

    bool agregar(const Producto &p, int cant)
    {
        if (cant <= 0)
            return false;
        for (auto &it : items)
        {
            if (it.id_prod == p.id)
            {
                it.cantidad += cant;
                return true;
            }
        }
        items.push_back({p.id, p.nombre, p.precio, cant});
        return true;
    }

    bool quitar(int id_prod, int cant)
    {
        if (cant <= 0)
            return false;
        for (size_t i = 0; i < items.size(); ++i)
        {
            if (items[i].id_prod == id_prod)
            {
                if (cant >= items[i].cantidad)
                    items.erase(items.begin() + i);
                else
                    items[i].cantidad -= cant;
                return true;
            }
        }
        return false;
    }

    double total() const
    {
        double t = 0.0;
        for (auto &it : items)
            t += it.subtotal();
        return t;
    }

    bool pagar(Usuario &u, vector<Producto> &catalogo)
    {
        if (items.empty())
        {
            cout << "Nada para pagar.\n";
            return false;
        }

        for (auto &it : items)
        {
            bool ok = false;
            for (auto &p : catalogo)
            {
                if (p.id == it.id_prod)
                {
                    if (p.stock < it.cantidad)
                    {
                        cout << "Stock insuficiente de \"" << p.nombre
                             << "\". Disponible: " << p.stock << "\n";
                        return false;
                    }
                    ok = true;
                }
            }
            if (!ok)
            {
                cout << "Producto inexistente.\n";
                return false;
            }
        }

        Compra c;
        for (auto &it : items)
        {
            for (auto &p : catalogo)
                if (p.id == it.id_prod)
                    p.stock -= it.cantidad;
            c.items.push_back(it);
            c.total += it.subtotal();
        }
        u.agregar_compra(c);
        items.clear();
        cout << "Pago exitoso. TOTAL: $" << fixed << setprecision(2) << c.total << "\n";
        return true;
    }
};

int buscar_idx(const vector<Producto> &cat, int id)
{
    for (size_t i = 0; i < cat.size(); ++i)
        if (cat[i].id == id)
            return (int)i;
    return -1;
}
template <typename T>
bool leer(T &x)
{
    if (cin >> x)
        return true;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return false;
}

int main()
{
    vector<Producto> catalogo = {
        {1, "Teclado", 120000, 10},
        {2, "Mouse", 80000, 15},
        {3, "Monitor 24\"", 650000, 5},
        {4, "USB 64GB", 45000, 30}};

    Usuario usuario("Invitado");
    CarritoCompras carrito;

    cout << fixed << setprecision(2);
    while (true)
    {
        cout << "\nMenu: 1)Ver catalogo 2)Agregar 3)Quitar 4)Ver carrito 5)Pagar 6)Historial 0)Salir\n";
        cout << "Opcion: ";
        int op;
        if (!leer(op))
            continue;
        if (op == 0)
            break;

        if (op == 1)
        {
            cout << "\n=== CATALOGO ===\n";
            for (auto &p : catalogo)
                cout << p.id << ") " << p.nombre << "  $" << p.precio << "  Stock: " << p.stock << "\n";
        }
        else if (op == 2)
        {
            int id, cant;
            cout << "ID: ";
            if (!leer(id))
                continue;
            cout << "Cantidad: ";
            if (!leer(cant))
                continue;
            int idx = buscar_idx(catalogo, id);
            if (idx < 0)
            {
                cout << "ID invalido.\n";
                continue;
            }
            int ya = carrito.cantidad_en_carrito(id);
            if (ya + cant > catalogo[idx].stock)
            {
                cout << "No hay stock suficiente. Disponible: " << catalogo[idx].stock - ya << "\n";
                continue;
            }
            carrito.agregar(catalogo[idx], cant);
            cout << "Agregado.\n";
        }
        else if (op == 3)
        {
            int id, cant;
            cout << "ID: ";
            if (!leer(id))
                continue;
            cout << "Cantidad a quitar: ";
            if (!leer(cant))
                continue;
            if (!carrito.quitar(id, cant))
                cout << "No se pudo quitar.\n";
            else
                cout << "Listo.\n";
        }
        else if (op == 4)
            carrito.ver_carrito();
        else if (op == 5)
            carrito.pagar(usuario, catalogo);
        else if (op == 6)
            usuario.ver_historial();
        else
            cout << "Opcion invalida.\n";
    }
    cout << "Chao!\n";
    return 0;
}
