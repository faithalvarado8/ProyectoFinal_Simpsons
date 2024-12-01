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

// void Jugador::recuperarVida() {
//     if (vidas < 3) {
//         vidas++;
//     } else {
//         std::cout << "El jugador ya tiene el máximo de vidas." << std::endl;
//     }
// }
