#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include "DispositivoInteligente.h"

int main()
{
    std::vector<DispositivoInteligente> dispositivos;

    DispositivoInteligente bombilloSala(
        1,
        "Bombillo sala",
        false,
        10.0f,
        false);

    DispositivoInteligente neveraCocina(
        2,
        "Nevera cocina",
        true,
        80.0f,
        false);

    dispositivos.push_back(bombilloSala);
    dispositivos.push_back(neveraCocina);

    float horasSimuladas = 2.5f;

    for (auto &disp : dispositivos)
    {
        if (!disp.estaEncendido())
        {
            disp.encender();
        }
    }

    // Registramos consumo
    for (auto &disp : dispositivos)
    {
        float energiaLeida = disp.medirConsumo(horasSimuladas);

        std::cout << "Dispositivo ID " << disp.obtenerID()
                  << " (" << disp.obtenerNombre() << "): "
                  << "energia en esta lectura = "
                  << energiaLeida << " Wh"
                  << std::endl;
    }

    std::cout << std::endl;
    std::cout << "Resumen de energia total acumulada:" << std::endl;

    for (const auto &disp : dispositivos)
    {
        std::cout << "ID " << disp.obtenerID()
                  << " - " << disp.obtenerNombre()
                  << " - total acumulado = "
                  << disp.obtenerEnergiaAcumulada()
                  << " Wh"
                  << std::endl;
    }

    // BONUS
    std::ofstream archivoReporte("reporte_consumo.txt");

    if (archivoReporte.is_open())
    {
        archivoReporte << "REPORTE DE CONSUMO POR DISPOSITIVO\n";
        archivoReporte << "---------------------------------\n";
        archivoReporte << std::fixed << std::setprecision(2);

        for (const auto &disp : dispositivos)
        {
            archivoReporte << "ID: " << disp.obtenerID()
                           << " | Nombre: " << disp.obtenerNombre()
                           << " | Consumo total (Wh): "
                           << disp.obtenerEnergiaAcumulada()
                           << "\n";
        }

        archivoReporte.close();
        std::cout << "\nArchivo reporte_consumo.txt generado." << std::endl;
    }
    else
    {
        std::cout << "No se pudo crear el archivo de reporte." << std::endl;
    }

    return 0;
}
