#include "murcielago.h"

Murcielago::Murcielago() {

    sprites.append(QPixmap(":/Nivel3/Bat-1.png"));
    sprites.append(QPixmap(":/Nivel3/Bat-2.png"));
    sprites.append(QPixmap(":/Nivel3/Bat-3.png"));

    setPixmap(sprites[spriteActual].scaled(50, 50, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &Murcielago::actualizarAnimacion);
    timer->start(75);

    setPos(100, 100);
}

void Murcielago::actualizarAnimacion(){

    spriteActual = (spriteActual + 1) % sprites.size();
    setPixmap(sprites[spriteActual].scaled(50, 50, Qt::KeepAspectRatio, Qt::SmoothTransformation));

}
