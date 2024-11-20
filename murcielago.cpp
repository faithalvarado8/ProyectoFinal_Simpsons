#include "murcielago.h"
#include <cmath>

Murcielago::Murcielago(): spriteActual(0), angulo(0), radio(40) {

    sprites.append(QPixmap(":/Nivel3/Bat-1.png").scaled(50, 50, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    sprites.append(QPixmap(":/Nivel3/Bat-2.png").scaled(50, 50, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    sprites.append(QPixmap(":/Nivel3/Bat-3.png").scaled(50, 50, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    setPixmap(sprites[spriteActual]);

    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &Murcielago::actualizarAnimacion);
    timer->start(75);

    timerMov = new QTimer();
    connect(timerMov, &QTimer::timeout, this, &Murcielago::movimiento);
    timerMov->start(25);

    setPos(100, 100);
}

void Murcielago::actualizarAnimacion(){

    spriteActual = (spriteActual + 1) % sprites.size();
    setPixmap(sprites[spriteActual]);

}

void Murcielago::movimiento(){

    // Incrementar y reiniciar el ángulo si excede 360°
    angulo += 5;
    if (angulo >= 360) {
        angulo = 0;
    }

    double radianes = qDegreesToRadians(static_cast<double>(angulo));

    double x = radio * cos(radianes);     //x(t)= r * cos(θ)
    double y = radio * sin(radianes);     //y(t)= r * sen(θ)

    setPos(100+x, 100+y); // Actualizar posicion del objeto

}
