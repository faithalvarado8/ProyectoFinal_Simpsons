#ifndef BART_H
#define BART_H

#include "jugador.h"
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QKeyEvent>
#include <QTimer>
#include <QMap>

class Bart: public Jugador{
    Q_OBJECT

public:
    Bart(); 
    void keyPressEvent(QKeyEvent * event);
    void keyReleaseEvent(QKeyEvent *event);
    void municiones();

private slots:
    void actualizarAnimacion();

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

    bool disparar;

    QTimer *timer;

    QMap<int,bool>keys;

};

#endif // BART_H
