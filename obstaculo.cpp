#include "obstaculo.h"

Obstaculo::Obstaculo(QGraphicsScene *escena, QObject *parent)
    : QObject(parent), escena(escena) {
    srand(static_cast<unsigned int>(time(nullptr)));

    QStringList sprites = {":/Nivel2/Bomb.png", ":/Nivel2/Parachute.png", ":/Nivel2/Plane.png"};
    QPixmap sprite(sprites[rand() % sprites.size()]);
    setPixmap(sprite.scaled(60, 60, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    unsigned int posX = rand() % (930 - 280 + 1) + 280;
    setPos(posX, -pixmap().height());
    setZValue(1);

    timerMovimiento = new QTimer(this);
    connect(timerMovimiento, &QTimer::timeout, this, &Obstaculo::mover);
    timerMovimiento->start(10); // Movimiento cada 10 ms
}

Obstaculo::~Obstaculo() {
    if (timerMovimiento){
        timerMovimiento->stop();
        delete timerMovimiento;
        timerMovimiento=nullptr;
    }
}

void Obstaculo::mover() {
    setY(y() + 8);
    // Eliminar el obstáculo si sale de la escena
    if (y() > escena->height()) {
        escena->removeItem(this);
        delete this;
    }
}
