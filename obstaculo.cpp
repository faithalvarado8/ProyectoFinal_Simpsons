#include "obstaculo.h"
#include <cstdlib>
#include <ctime>

Obstaculo::Obstaculo(QGraphicsScene *escena, QObject *parent)
    : QObject(parent), escena(escena) {
    srand(static_cast<unsigned int>(time(nullptr)));

    QStringList sprites = {":/Nivel2/Bomb.png", ":/Nivel2/Parachute.png", ":/Nivel2/Plane.png"};
    QPixmap sprite(sprites[rand() % sprites.size()]);
    setPixmap(sprite.scaled(60, 60, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    int posX = rand() % (static_cast<int>(escena->width()) - pixmap().width());
    setPos(posX, -pixmap().height());
    setZValue(1);

    timerMovimiento = new QTimer(this);
    connect(timerMovimiento, &QTimer::timeout, this, &Obstaculo::mover);
    timerMovimiento->start(10); // Movimiento cada 50 ms
}

Obstaculo::~Obstaculo() {
    delete timerMovimiento;
}

void Obstaculo::mover() {
    // Mover el obstáculo hacia abajo
    setY(y() + 5);

    // Eliminar el obstáculo si sale de la escena
    if (y() > escena->height()) {
        escena->removeItem(this);
        delete this;
    }
}
