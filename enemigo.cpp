#include "enemigo.h"
#include <cmath>

Enemigo::Enemigo(unsigned short int cont): spriteActual(0), angulo(0), radio(70) {

    contM=cont;

    sprites.append(QPixmap(":/Nivel3/Bat-1.png").scaled(50, 50, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    sprites.append(QPixmap(":/Nivel3/Bat-2.png").scaled(50, 50, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    sprites.append(QPixmap(":/Nivel3/Bat-3.png").scaled(50, 50, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    setPixmap(sprites[spriteActual]);

    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &Enemigo::actualizarAnimacion);
    timer->start(75);

    timerMov = new QTimer();
    connect(timerMov, &QTimer::timeout, this, &Enemigo::movimiento);
    timerMov->start(30);

    setZValue(2);

    if (cont==1){
        setPos(800, 400);
    }
    else if (cont==2){
        setPos(1090, 150);
    }
    else if (cont==3){
        setPos(150, 155);
    }
    else if (cont==4){
        setPos(700, 200);
    }
    else{
        setPos(250, 420);
    }

}

void Enemigo::actualizarAnimacion(){

    spriteActual = (spriteActual + 1) % sprites.size();
    setPixmap(sprites[spriteActual]);

}

void Enemigo::movimiento(){

    // Incrementar y reiniciar el ángulo si excede 360°
    angulo += 5;
    if (angulo >= 360) {
        angulo = 0;
    }

    double radianes = qDegreesToRadians(static_cast<double>(angulo));

    double x = radio * cos(radianes);     //x(t)= r * cos(θ)
    double y = radio * sin(radianes);     //y(t)= r * sen(θ)

    if (contM==1){
        setPos(800+x, 400+y);
    }
    else if (contM==2){
        setPos(1090+x, 150+y);
    }
    else if (contM==3){
        setPos(150+x, 155+y);
    }
    else if (contM==4){
        setPos(700+x, 200+y);
    }
    else{
        setPos(250+x, 420+y);
    }

}
