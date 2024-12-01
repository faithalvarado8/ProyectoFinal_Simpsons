#include "jugador.h"

Jugador::Jugador(unsigned short int vidasIniciales) : vidas(vidasIniciales) {}

unsigned short int Jugador::getVidas() const {
    return vidas;
}

void Jugador::perderVida() {
    if (vidas > 0) {
        vidas--;
    }
}
