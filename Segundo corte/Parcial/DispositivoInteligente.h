#ifndef DISPOSITIVO_INTELIGENTE_H
#define DISPOSITIVO_INTELIGENTE_H

#include <string>

class DispositivoInteligente
{
private:
    int id;
    std::string nombre;
    bool estado;
    float consumoEnergia; // consumo en Wh por hora de uso
    bool bloqueado;
    float energiaAcumulada; // energía total consumida (Wh)

public:
    DispositivoInteligente(int idDispositivo,
                           const std::string &nombreDispositivo,
                           bool estadoInicial,
                           float consumoPorHora,
                           bool bloqueadoInicial);

    void encender();
    void apagar();
    float medirConsumo(float horas);
    void bloquearControlRemoto();

    int obtenerID() const;
    std::string obtenerNombre() const;
    float obtenerEnergiaAcumulada() const;
    bool estaEncendido() const;
};

#endif
