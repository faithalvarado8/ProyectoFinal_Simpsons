#include "jugador.h"

Jugador::Jugador(unsigned int vidasIniciales) : vidas(vidasIniciales) {}

unsigned int Jugador::getVidas() const {
    return vidas;
}

void Jugador::perderVida() {
    if (vidas > 0) {
        vidas--;
        qDebug() << "[Jugador] Vida perdida. Vidas restantes:" << vidas;
    } else if (vidas == 0) {
        qDebug() << "[Jugador] El jugador ha muerto.";
    }
}

// void Jugador::recuperarVida() {
//     if (vidas < 3) {
//         vidas++;
//     } else {
//         std::cout << "El jugador ya tiene el máximo de vidas." << std::endl;
//     }
// }

void Jugador::mostrarEstado() const {
    qDebug() << "[Jugador] Vidas actuales:" << vidas;
}
