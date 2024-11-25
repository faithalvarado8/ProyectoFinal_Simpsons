#ifndef BART_H
#define BART_H

#include "jugador.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QKeyEvent>
#include <QTimer>
#include <QMap>

class Bart: public Jugador{
    Q_OBJECT

public:
    Bart(QGraphicsScene* escena, QList<QGraphicsPixmapItem*> tumbasEscena);
    void keyPressEvent(QKeyEvent * event);
    void keyReleaseEvent(QKeyEvent *event);
    void municiones();
    void lanzarMunicion();
    void colisionTumba();

private slots:
    void actualizarAnimacion();
    void actualizarDisparo();

private:
    // Sprites
    QPixmap sprites;
    QPixmap spritesLado;
    QPixmap spritesArribaAbajo;
    QPixmap spritesArma;

    // Dimensiones hoja de sprites
    int anchoLado, altoLado;
    int anchoArribaAbajo, altoArribaAbajo;
    int anchoArma, altoArma;
    int ancho, alto;
    int columna;
    int fila;
    QTimer *timer;
    bool moving;
    int spriteX, spriteY;

    bool disparar;
    int numMuniciones;
    char direccion;
    QTimer* timerDisparo;
    QGraphicsPixmapItem* municion;
    double t;
    QPointF posInicialMunicion;
    char direccionDisparo;

    QList<QGraphicsPixmapItem*> tumbasEscena;
    QPointF nuevaPos;
    QPointF oldPos;

    QMap<int,bool>keys;
    QGraphicsScene* escena;
};

#endif // BART_H
