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

    for (auto &disp : dispositivos)
    {
        float energiaLeida = disp.medirConsumo(horasSimuladas);

        std::cout << "Dispositivo ID " << disp.obtenerID()
                  << " (" << disp.obtenerNombre() << "): "
                  << energiaLeida << " Wh en esta lectura"
                  << std::endl;
    }

    std::cout << "\nResumen de energia total acumulada:\n";
    for (const auto &disp : dispositivos)
    {
        std::cout << "ID " << disp.obtenerID()
                  << " - " << disp.obtenerNombre()
                  << " - total = "
                  << disp.obtenerEnergiaAcumulada()
                  << " Wh"
                  << std::endl;
    }

    std::ofstream archivoReporte("reporte_consumo.txt");
    if (archivoReporte.is_open())
    {
        archivoReporte << std::fixed << std::setprecision(2);
        for (const auto &disp : dispositivos)
        {
            archivoReporte << "ID: " << disp.obtenerID()
                           << " | " << disp.obtenerNombre()
                           << " | Consumo total (Wh): "
                           << disp.obtenerEnergiaAcumulada()
                           << "\n";
        }
        archivoReporte.close();
    }

    return 0;
}
