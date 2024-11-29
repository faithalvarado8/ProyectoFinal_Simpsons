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

Enemigo::Enemigo(QList<QPointF> posicionesZombies, Bart* bart): bart(bart){

    // Crear el zombie
    spritesZombie = QPixmap(":/Nivel3/Zombie.png");

    ancho=419;
    alto=642;
    columna = 0;
    fila = 1;

    QPixmap zombie = spritesZombie.copy(0,642, ancho, alto);
    setPixmap(zombie.scaled(90, 90, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    int random_number1 = rand() % posicionesZombies.size();

    setPos(posicionesZombies[random_number1]); // Posición inicial del zombie
    setZValue(3);

    // Temporizador para mover el zombie
    zombieTimer = new QTimer();
    connect(zombieTimer, &QTimer::timeout, this, &Enemigo::moverZombie);
    zombieTimer->start(30);

    timerAnimarZombie = new QTimer();
    connect(timerAnimarZombie, &QTimer::timeout, this, &Enemigo::actualizarZombie);
    timerAnimarZombie->start(220);
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

void Enemigo::moverZombie(){
    // Coordenadas del zombie y el personaje
    posZombie = pos();
    posPersonaje = bart->pos();

    // Calcular dirección hacia el personaje
    dx = posPersonaje.x() - posZombie.x();
    dy = posPersonaje.y() - posZombie.y();

    qreal velocidad = 1.6; // Velocidad del zombie

    // Mover solo en el eje X o Y
    if (std::abs(dx) > std::abs(dy)) {
        // Mover en el eje X
        dx = (dx > 0 ? velocidad : -velocidad);
        dy = 0;
    } else {
        // Mover en el eje Y
        dy = (dy > 0 ? velocidad : -velocidad);
        dx = 0;
    }

    setPos(posZombie.x() + dx, posZombie.y() + dy);
}

void Enemigo::actualizarZombie(){
    if (dx > 0) {        // Movimiento hacia la derecha
        fila = 2;
    } else if (dx < 0) { // Movimiento hacia la izquierda
        fila = 3;
    } else if (dy > 0) { // Movimiento hacia abajo
        fila = 1;
    } else if (dy < 0) { // Movimiento hacia arriba
        fila = 0;
    }

    QPixmap zombie = spritesZombie.copy(columna*ancho, fila*alto, ancho, alto);
    setPixmap(zombie.scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    columna= (columna+1)%3;
}

Enemigo::~Enemigo(){
    if (timer){
        timer->stop();
        disconnect(timer, nullptr, this, nullptr);
        delete timer;
        timer=nullptr;
    }

    if (timerMov){
        timerMov->stop();
        disconnect(timerMov, nullptr, this, nullptr);
        delete timerMov;
        timerMov=nullptr;
    }

    if (zombieTimer){
        zombieTimer->stop();
        disconnect(zombieTimer, nullptr, this, nullptr);
        delete zombieTimer;
        zombieTimer=nullptr;
    }

    if (timerAnimarZombie){
        timerAnimarZombie->stop();
        disconnect(timerAnimarZombie, nullptr, this, nullptr);
        delete timerAnimarZombie;
        timerAnimarZombie=nullptr;
    }
}
