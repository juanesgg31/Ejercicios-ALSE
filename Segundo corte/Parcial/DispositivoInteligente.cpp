#include "DispositivoInteligente.h"

DispositivoInteligente::DispositivoInteligente(int idDispositivo,
                                               const std::string &nombreDispositivo,
                                               bool estadoInicial,
                                               float consumoPorHora,
                                               bool bloqueadoInicial)
    : id(idDispositivo),
      nombre(nombreDispositivo),
      estado(estadoInicial),
      consumoEnergia(consumoPorHora),
      bloqueado(bloqueadoInicial),
      energiaAcumulada(0.0f)
{
}

void DispositivoInteligente::encender()
{
    estado = true;
}

void DispositivoInteligente::apagar()
{
    estado = false;
}

float DispositivoInteligente::medirConsumo(float horas)
{
    float energia = consumoEnergia * horas;
    if (estado)
    {
        energiaAcumulada += energia;
    }
    return energia;
}

void DispositivoInteligente::bloquearControlRemoto()
{
    bloqueado = true;
}

int DispositivoInteligente::obtenerID() const
{
    return id;
}

std::string DispositivoInteligente::obtenerNombre() const
{
    return nombre;
}

float DispositivoInteligente::obtenerEnergiaAcumulada() const
{
    return energiaAcumulada;
}

bool DispositivoInteligente::estaEncendido() const
{
    return estado;
}
