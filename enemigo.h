#ifndef ENEMIGO_H
#define ENEMIGO_H

#include <QGraphicsPixmapItem>
#include <QTimer>
#include "bart.h"
#include <QObject>

class Enemigo:public QObject, public QGraphicsPixmapItem {
    Q_OBJECT

public:
    Enemigo(int rangoIzq, int rangoDer);  //Constructor Krusty
    Enemigo(unsigned short int cont);   //Constructor murcielago
    Enemigo(QList<QPointF> posicionesZombies, Bart* bart); // Constructor zombies
    ~Enemigo();

private slots:
    void movimientoKrusty();
    void animacionKrusty();
    void actualizarAnimacion();
    void movimiento();
    void moverZombie();
    void actualizarZombie();

private:

    // Sprites
    QVector<QPixmap> sprites;
    int spriteActual;
    Bart* bart;

    // Timers
    QTimer *timer;
    QTimer *timerMov;

    // Movimiento
    int rangoIzquierdo;
    int rangoDerecho;
    bool moviendoDerecha;
    float velocidad;

    int angulo;
    int radio;
    unsigned short int contM;

    int ancho, alto;
    int columna;
    int fila;
    QPixmap spritesZombie;
    QTimer* zombieTimer;
    QTimer* timerAnimarZombie;
    qreal dx;
    qreal dy;
    QPointF posPersonaje;
    QPointF posZombie;
};

#endif // ENEMIGO_H
